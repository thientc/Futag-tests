/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#include "first.h"
#include <stdio.h>
#line 5 "../../src/configparser.y"

#include "first.h"
#include "base.h"
#include "configfile.h"
#include "buffer.h"
#include "array.h"
#include "http_header.h" /* http_header_hkey_get() */
#include "request.h" /* http_request_host_normalize() */

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

__attribute_pure__
static data_config * configparser_get_data_config(const array *a, const char *k, const size_t klen) {
  return (data_config *)array_get_data_unset(a, k, klen);
}

__attribute_noinline__
static void configparser_push_data_config_list(data_config_list *v, data_config *dc) {
    if (v->size == v->used) {
        ck_realloc_u32((void **)&v->data, v->size, 4, sizeof(*v->data));
        v->size += 4;
    }
    v->data[v->used++] = dc;
}

static void configparser_push(config_t *ctx, data_config *dc, int isnew) {
  if (isnew) {
    dc->context_ndx = ctx->all_configs->used;
    force_assert(dc->context_ndx > ctx->current->context_ndx);
    array_insert_unique(ctx->all_configs, (data_unset *)dc);
    dc->parent = ctx->current;
    configparser_push_data_config_list(&dc->parent->children, dc);
  }
  if (ctx->configs_stack.used > 0 && ctx->current->context_ndx == 0) {
    fprintf(stderr, "Cannot use conditionals inside a global { ... } block\n");
    exit(-1);
  }
  configparser_push_data_config_list(&ctx->configs_stack, ctx->current);
  ctx->current = dc;
}

static data_config *configparser_pop(config_t *ctx) {
  data_config *old = ctx->current;
  force_assert(ctx->configs_stack.used);
  ctx->current = ctx->configs_stack.data[--ctx->configs_stack.used];
  force_assert(old && ctx->current);
  return old;
}

/* return a copied variable */
static data_unset *configparser_get_variable(config_t *ctx, const buffer *key) {
  const data_unset *du;
  data_config *dc;

#if 0
  fprintf(stderr, "get var %s\n", key->ptr);
#endif
  for (dc = ctx->current; dc; dc = dc->parent) {
#if 0
    fprintf(stderr, "get var on block: %s\n", dc->key.ptr);
    array_print(dc->value, 0);
#endif
    if (NULL != (du = array_get_element_klen(dc->value, BUF_PTR_LEN(key)))) {
      data_unset *du_copy = du->fn->copy(du);
      buffer_clear(&du_copy->key);
      return du_copy;
    }
  }
  return NULL;
}

/* op1 is to be eat/return by this function if success, op1->key is not cared
   op2 is left untouch, unreferenced
 */
static data_unset *configparser_merge_data(data_unset *op1, const data_unset *op2) {
  /* type mismatch */
  if (op1->type != op2->type) {
    if (op1->type == TYPE_STRING && op2->type == TYPE_INTEGER) {
      data_string *ds = (data_string *)op1;
      buffer_append_int(&ds->value, ((data_integer*)op2)->value);
      return op1;
    } else if (op1->type == TYPE_INTEGER && op2->type == TYPE_STRING) {
      data_string *ds = array_data_string_init();
      buffer_append_int(&ds->value, ((data_integer*)op1)->value);
      buffer_append_string_buffer(&ds->value, &((data_string*)op2)->value);
      op1->fn->free(op1);
      return (data_unset *)ds;
    } else {
      fprintf(stderr, "data type mismatch, cannot merge\n");
      op1->fn->free(op1);
      return NULL;
    }
  }

  switch (op1->type) {
    case TYPE_STRING:
      buffer_append_string_buffer(&((data_string *)op1)->value, &((data_string *)op2)->value);
      break;
    case TYPE_INTEGER:
      ((data_integer *)op1)->value += ((data_integer *)op2)->value;
      break;
    case TYPE_ARRAY: {
      array *dst = &((data_array *)op1)->value;
      array *src = &((data_array *)op2)->value;
      const data_unset *du, *ddu;
      size_t i;

      for (i = 0; i < src->used; i ++) {
        du = (data_unset *)src->data[i];
        if (du) {
          if (buffer_is_unset(&du->key)
              || !(ddu = array_get_element_klen(dst, BUF_PTR_LEN(&du->key)))){
            array_insert_unique(dst, du->fn->copy(du));
          } else {
            fprintf(stderr, "Duplicate array-key '%s'\n", du->key.ptr);
            if (ddu->type == du->type) {
              /*(ignore if new key/value pair matches existing key/value)*/
              if (du->type == TYPE_STRING
                  && buffer_is_equal(&((data_string *)du)->value,
                                     &((data_string *)ddu)->value))
                  continue;
              if (du->type == TYPE_INTEGER
                  && ((data_integer*)du)->value == ((data_integer*)ddu)->value)
                  continue;
            }
            op1->fn->free(op1);
            return NULL;
          }
        }
      }
      break;
    }
    default:
      force_assert(0);
      break;
  }
  return op1;
}

__attribute_pure__
static comp_key_t
configparser_comp_key_id(const buffer * const obj_tag, const buffer * const comp_tag)
{
  /* $REQUEST_HEADER["..."] */
  /* $SERVER["socket"] */
  /* $HTTP["..."] */
  if (buffer_eq_slen(obj_tag, CONST_STR_LEN("REQUEST_HEADER")))
    return COMP_HTTP_REQUEST_HEADER;
  else if (buffer_eq_slen(obj_tag, CONST_STR_LEN("SERVER")))
    return (buffer_eq_slen(comp_tag, CONST_STR_LEN("socket")))
      ? COMP_SERVER_SOCKET
      : COMP_UNSET;
  else if (buffer_eq_slen(obj_tag, CONST_STR_LEN("HTTP"))) {
    static const struct {
      comp_key_t comp;
      uint32_t len;
      const char *comp_tag;
    } comps[] = {
      { COMP_HTTP_URL,            CONST_LEN_STR("url"           ) },
      { COMP_HTTP_HOST,           CONST_LEN_STR("host"          ) },
      { COMP_HTTP_REQUEST_HEADER, CONST_LEN_STR("referer"       ) },
      { COMP_HTTP_USER_AGENT,     CONST_LEN_STR("useragent"     ) },
      { COMP_HTTP_REQUEST_HEADER, CONST_LEN_STR("user-agent"    ) },
      { COMP_HTTP_LANGUAGE,       CONST_LEN_STR("language"      ) },
      { COMP_HTTP_REQUEST_HEADER, CONST_LEN_STR("cookie"        ) },
      { COMP_HTTP_REMOTE_IP,      CONST_LEN_STR("remoteip"      ) },
      { COMP_HTTP_REMOTE_IP,      CONST_LEN_STR("remote-ip"     ) },
      { COMP_HTTP_QUERY_STRING,   CONST_LEN_STR("querystring"   ) },
      { COMP_HTTP_QUERY_STRING,   CONST_LEN_STR("query-string"  ) },
      { COMP_HTTP_REQUEST_METHOD, CONST_LEN_STR("request-method") },
      { COMP_HTTP_SCHEME,         CONST_LEN_STR("scheme"        ) }
    };

    for (uint32_t i = 0; i < sizeof(comps)/sizeof(comps[0]); ++i) {
      if (buffer_eq_slen(comp_tag, comps[i].comp_tag, comps[i].len))
        return comps[i].comp;
    }
  }
  return COMP_UNSET;
}

static config_cond_t
configparser_simplify_regex(buffer * const b)
{
    /* translate simple regex anchored with ^ and/or $ to simpler match types
     * (note: skips if regex contains any '\\', even if some could be removed,
     *  though we special-case "\.ext"; skips if other '.' found in str)
     * (currently assumes CONFIG_COND_MATCH input, not CONFIG_COND_NOMATCH) */
    uint32_t len = buffer_clen(b);
    config_cond_t cond = CONFIG_COND_MATCH;
    int off = 0;
    if (len && b->ptr[len-1] == '$') {
        cond = CONFIG_COND_SUFFIX;
        if (b->ptr[0] == '\\' && b->ptr[1] == '.')
            off = 2;
        else if (b->ptr[0] == '^') {
            off = 1;
            cond = CONFIG_COND_EQ;
        }
        --len;
    }
    else if (b->ptr[0] == '^') {
        off = 1;
        cond = CONFIG_COND_PREFIX;
    }
    else
        return CONFIG_COND_MATCH;

    static const char regex_chars[] = "\\^$.|?*+()[]{}";
    if (strcspn(b->ptr+off, regex_chars) != len - off)
        return CONFIG_COND_MATCH;
    if (off) { /*(remove only first char if (off == 2) to keep '.' in "\.")*/
        memmove(b->ptr, b->ptr+1, len-1);
        --len;
    }
    buffer_truncate(b, len);
    return cond;
}

static void
configparser_parse_condition(config_t * const ctx, const buffer * const obj_tag, const buffer * const comp_tag, config_cond_t cond, buffer * const rvalue)
{
    const comp_key_t comp = configparser_comp_key_id(obj_tag, comp_tag);
    if (cond == CONFIG_COND_MATCH && comp != COMP_SERVER_SOCKET)
        cond = configparser_simplify_regex(rvalue);

    const char *op = NULL;
    switch(cond) {
    case CONFIG_COND_NE:      op = "!="; break;
    case CONFIG_COND_EQ:      op = "=="; break;
    case CONFIG_COND_NOMATCH: op = "!~"; break;
    case CONFIG_COND_MATCH:   op = "=~"; break;
    case CONFIG_COND_PREFIX:  op = "=^"; break;
    case CONFIG_COND_SUFFIX:  op = "=$"; break;
    default:
      force_assert(0);
      return; /* unreachable */
    }

    const uint32_t comp_offset = buffer_clen(&ctx->current->key)+3;
    buffer * const tb = ctx->srv->tmp_buf;
    buffer_clear(tb);
    struct const_iovec iov[] = {
      { BUF_PTR_LEN(&ctx->current->key) }
     ,{ CONST_STR_LEN(" / ") }   /* comp_offset */
     ,{ CONST_STR_LEN("$") }
     ,{ BUF_PTR_LEN(obj_tag) } /*(HTTP, REQUEST_HEADER, SERVER)*/
     ,{ CONST_STR_LEN("[\"") }
     ,{ BUF_PTR_LEN(comp_tag) }
     ,{ CONST_STR_LEN("\"] ") }
     ,{ op, 2 }
     ,{ CONST_STR_LEN(" \"") }
     ,{ BUF_PTR_LEN(rvalue) }
     ,{ CONST_STR_LEN("\"") }
    };
    buffer_append_iovec(tb, iov, sizeof(iov)/sizeof(*iov));

    data_config *dc;
    if (NULL != (dc = configparser_get_data_config(ctx->all_configs,
                                                   BUF_PTR_LEN(tb)))) {
      configparser_push(ctx, dc, 0);
    }
    else {
      dc = data_config_init();
      dc->cond = cond;
      dc->comp = comp;

      buffer_copy_buffer(&dc->key, tb);
      buffer_copy_buffer(&dc->comp_tag, comp_tag);
      dc->comp_key = dc->key.ptr + comp_offset;

      if (COMP_UNSET == dc->comp) {
          fprintf(stderr, "error comp_key %s", dc->comp_key);
          ctx->ok = 0;
      }
      else if (COMP_HTTP_LANGUAGE == dc->comp) {
        dc->comp = COMP_HTTP_REQUEST_HEADER;
        buffer_copy_string_len(&dc->comp_tag, CONST_STR_LEN("Accept-Language"));
      }
      else if (COMP_HTTP_USER_AGENT == dc->comp) {
        dc->comp = COMP_HTTP_REQUEST_HEADER;
        buffer_copy_string_len(&dc->comp_tag, CONST_STR_LEN("User-Agent"));
      }
      else if (COMP_HTTP_REMOTE_IP == dc->comp
               && (dc->cond == CONFIG_COND_EQ     ||
                   dc->cond == CONFIG_COND_NE     ||
                   dc->cond == CONFIG_COND_PREFIX ||
                   dc->cond == CONFIG_COND_SUFFIX)) {
        if (!config_remoteip_normalize(rvalue, tb)) {
          fprintf(stderr, "invalid IP addr: %s\n", rvalue->ptr);
          ctx->ok = 0;
        }
      }
      else if (COMP_SERVER_SOCKET == dc->comp) {
        /*(redundant with parsing in network.c; not actually required here)*/
        if (rvalue->ptr[0] != ':' /*(network.c special-cases ":" and "[]")*/
            && !(rvalue->ptr[0] == '[' && rvalue->ptr[1] == ']')
            && !(rvalue->ptr[0] == '/' || rvalue->ptr[0] == '\\')) { /*(UDS)*/
          if (http_request_host_normalize(rvalue, 0)) {
            fprintf(stderr, "invalid IP addr: %s\n", rvalue->ptr);
            ctx->ok = 0;
          }
        }
      }
      else if (COMP_HTTP_HOST == dc->comp) {
        if (dc->cond == CONFIG_COND_EQ     ||
            dc->cond == CONFIG_COND_NE     ||
            dc->cond == CONFIG_COND_PREFIX ||
            dc->cond == CONFIG_COND_SUFFIX) {
          if (http_request_host_normalize(rvalue, 0)) {
            fprintf(stderr, "invalid IP addr: %s\n", rvalue->ptr);
            ctx->ok = 0;
          }
        }
      }

      if (COMP_HTTP_REQUEST_HEADER == dc->comp) {
        dc->ext = http_header_hkey_get(BUF_PTR_LEN(&dc->comp_tag));
      }

      buffer_move(&dc->string, rvalue);

      if (ctx->ok)
        configparser_push(ctx, dc, 1);
      else
        dc->fn->free((data_unset*) dc);
    }
}

static void
configparser_parse_else_condition(config_t * const ctx)
{
    data_config * const dc = data_config_init();
    dc->cond = CONFIG_COND_ELSE;
    buffer_append_str2(&dc->key, BUF_PTR_LEN(&ctx->current->key),
                                 CONST_STR_LEN(" / "
                                               "else_tmp_token"));
    configparser_push(ctx, dc, 1);
}


#line 355 "./configparser.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/*
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands.
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    configparserTOKENTYPE     is the data type used for minor tokens given
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is configparserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.
**    configparserARG_SDECL     A static variable declaration for the %extra_argument
**    configparserARG_PDECL     A parameter declaration for the %extra_argument
**    configparserARG_STORE     Code to store %extra_argument into yypParser
**    configparserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
/*  */
#define YYCODETYPE unsigned char
#define YYNOCODE 53
#define YYACTIONTYPE unsigned char
#define configparserTOKENTYPE buffer *
typedef union {
  configparserTOKENTYPE yy0;
  buffer * yy9;
  data_config * yy18;
  array * yy38;
  data_unset * yy59;
  config_cond_t yy69;
  int yy105;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define configparserARG_SDECL config_t *ctx;
#define configparserARG_PDECL ,config_t *ctx
#define configparserARG_FETCH config_t *ctx = yypParser->ctx
#define configparserARG_STORE yypParser->ctx = ctx
#define YYNSTATE 72
#define YYNRULE 46
#define YYERRORSYMBOL 29
#define YYERRSYMDT yy105
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static YYACTIONTYPE yy_action[] = {
 /*     0 */     2,    3,    4,    5,   14,   15,   72,   16,    7,   48,
 /*    10 */    98,   21,    8,   17,   29,   28,   34,   44,   11,   43,
 /*    20 */    26,   23,   35,   49,   12,   16,    9,   10,   21,   21,
 /*    30 */    24,   25,   27,   63,   65,   11,   68,   43,   13,   67,
 /*    40 */    20,   49,   29,   28,   38,  119,    1,   31,   26,   23,
 /*    50 */    35,   63,   65,   16,   29,   52,   20,   21,   36,   16,
 /*    60 */    26,   23,   53,   21,  107,   43,   20,   47,  100,   49,
 /*    70 */    45,   43,  115,   71,   46,   49,   29,   52,   51,   63,
 /*    80 */    65,   50,   26,   23,   64,   63,   65,   57,   58,   59,
 /*    90 */    60,   61,   62,   21,   55,   24,   25,   27,   30,   29,
 /*   100 */    52,  108,   29,   19,   49,   26,   23,   66,   26,   23,
 /*   110 */    29,   37,   29,   40,   29,   42,   26,   23,   26,   23,
 /*   120 */    26,   23,   29,   56,   18,   39,   41,   22,   26,   23,
 /*   130 */     6,   32,   33,   26,   23,   54,   70,   69,  100,  100,
 /*   140 */   100,  100,  100,  100,  100,   99,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */    32,   33,   34,   35,   36,   37,    0,    1,   48,   41,
 /*    10 */    16,    5,   16,   45,   38,   39,   40,   49,   50,   13,
 /*    20 */    44,   45,   46,   17,   14,    1,   41,   42,    5,    5,
 /*    30 */     7,    8,    9,   27,   28,   50,   51,   13,   31,   15,
 /*    40 */     6,   17,   38,   39,   40,   30,   31,   43,   44,   45,
 /*    50 */    46,   27,   28,    1,   38,   39,    6,    5,   12,    1,
 /*    60 */    44,   45,   46,    5,   14,   13,    6,   15,   14,   17,
 /*    70 */    14,   13,   12,   15,   31,   17,   38,   39,   19,   27,
 /*    80 */    28,   18,   44,   45,   46,   27,   28,   21,   22,   23,
 /*    90 */    24,   25,   26,    5,   47,    7,    8,    9,   10,   38,
 /*   100 */    39,   14,   38,   39,   17,   44,   45,   46,   44,   45,
 /*   110 */    38,   39,   38,   39,   38,   39,   44,   45,   44,   45,
 /*   120 */    44,   45,   38,   39,    2,    3,    4,   38,   44,   45,
 /*   130 */     1,   10,   11,   44,   45,   20,   31,   14,   52,   52,
 /*   140 */    52,   52,   52,   52,   52,   16,
};
#define YY_SHIFT_USE_DFLT (-7)
static short yy_shift_ofst[] = {
 /*     0 */    -7,    6,   -7,   -7,   -7,  129,   -6,   -4,   87,   -7,
 /*    10 */    -7,   10,   -7,   24,   -7,   -7,   -7,  122,   23,   34,
 /*    20 */    23,   -7,   -7,   -7,   -7,   -7,   -7,   88,   60,   -7,
 /*    30 */    -7,  121,   -7,   23,   -7,   46,   23,   34,   -7,   23,
 /*    40 */    34,   23,   34,   54,   56,   -7,   52,   -7,   -7,   63,
 /*    50 */    59,   23,   34,  115,   66,   23,   50,   -7,   -7,   -7,
 /*    60 */    -7,   -7,   -7,   23,   -7,   23,   -7,   -7,  123,   -7,
 /*    70 */    58,   -7,
};
#define YY_REDUCE_USE_DFLT (-41)
static signed char yy_reduce_ofst[] = {
 /*     0 */    15,  -32,  -41,  -41,  -41,  -40,  -41,  -41,  -15,  -41,
 /*    10 */   -41,  -41,    7,  -32,  -41,  -41,  -41,  -41,   64,  -41,
 /*    20 */    89,  -41,  -41,  -41,  -41,  -41,  -41,    4,  -41,  -41,
 /*    30 */   -41,  -41,  -41,  -24,  -41,  -41,   72,  -41,  -41,   74,
 /*    40 */   -41,   76,  -41,  -41,  -41,   43,  -32,  -41,  -41,  -41,
 /*    50 */   -41,   16,  -41,  -41,   47,   84,  -41,  -41,  -41,  -41,
 /*    60 */   -41,  -41,  -41,   38,  -41,   61,  -41,  -41,  -41,  105,
 /*    70 */   -32,  -41,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */    74,  118,   73,   75,   76,  118,   77,  118,  118,  102,
 /*    10 */   103,  118,   74,  118,   78,   79,   80,  118,  118,   81,
 /*    20 */   118,   84,   85,   87,   88,   89,   90,  118,   96,   86,
 /*    30 */    91,  118,   92,   94,   93,  118,  118,   97,   95,  118,
 /*    40 */    82,  118,   83,  118,  118,   74,  118,  101,  104,  118,
 /*    50 */   118,  118,  115,  118,  118,  118,  118,  109,  110,  111,
 /*    60 */   112,  113,  114,  118,  116,  118,  117,  105,  118,   74,
 /*    70 */   118,  106,
};
#define YY_SZ_ACTTAB (sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
**
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  int stateno;       /* The state-number */
  int major;         /* The major token value.  This is the code
                     ** number for the token at this stack level */
  YYMINORTYPE minor; /* The user-supplied minor token value.  This
                     ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
  int yyerrcnt;                 /* Shifts left before out of the error */
  configparserARG_SDECL                /* A place to hold %extra_argument */
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = NULL;
static char *yyTracePrompt = NULL;
#endif /* NDEBUG */

#ifndef NDEBUG
/*
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
#if 0
void configparserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *yyTokenName[] = {
  "$",             "EOL",           "ASSIGN",        "FORCE_ASSIGN",
  "APPEND",        "LKEY",          "PLUS",          "STRING",      
  "INTEGER",       "LPARAN",        "RPARAN",        "COMMA",       
  "ARRAY_ASSIGN",  "GLOBAL",        "LCURLY",        "RCURLY",      
  "ELSE",          "DOLLAR",        "SRVVARNAME",    "LBRACKET",    
  "RBRACKET",      "EQ",            "MATCH",         "NE",          
  "NOMATCH",       "PREFIX",        "SUFFIX",        "INCLUDE",     
  "INCLUDE_SHELL",  "error",         "input",         "metalines",   
  "metaline",      "varline",       "global",        "condlines",   
  "include",       "include_shell",  "value",         "expression",  
  "aelement",      "condline",      "cond_else",     "aelements",   
  "array",         "key",           "stringop",      "cond",        
  "eols",          "globalstart",   "context",       "context_else",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *yyRuleName[] = {
 /*   0 */ "input ::= metalines",
 /*   1 */ "metalines ::= metalines metaline",
 /*   2 */ "metalines ::=",
 /*   3 */ "metaline ::= varline",
 /*   4 */ "metaline ::= global",
 /*   5 */ "metaline ::= condlines EOL",
 /*   6 */ "metaline ::= include",
 /*   7 */ "metaline ::= include_shell",
 /*   8 */ "metaline ::= EOL",
 /*   9 */ "varline ::= key ASSIGN expression",
 /*  10 */ "varline ::= key FORCE_ASSIGN expression",
 /*  11 */ "varline ::= key APPEND expression",
 /*  12 */ "key ::= LKEY",
 /*  13 */ "expression ::= expression PLUS value",
 /*  14 */ "expression ::= value",
 /*  15 */ "value ::= key",
 /*  16 */ "value ::= STRING",
 /*  17 */ "value ::= INTEGER",
 /*  18 */ "value ::= array",
 /*  19 */ "array ::= LPARAN RPARAN",
 /*  20 */ "array ::= LPARAN aelements RPARAN",
 /*  21 */ "aelements ::= aelements COMMA aelement",
 /*  22 */ "aelements ::= aelements COMMA",
 /*  23 */ "aelements ::= aelement",
 /*  24 */ "aelement ::= expression",
 /*  25 */ "aelement ::= stringop ARRAY_ASSIGN expression",
 /*  26 */ "eols ::= EOL",
 /*  27 */ "eols ::=",
 /*  28 */ "globalstart ::= GLOBAL",
 /*  29 */ "global ::= globalstart LCURLY metalines RCURLY",
 /*  30 */ "condlines ::= condlines eols ELSE condline",
 /*  31 */ "condlines ::= condlines eols ELSE cond_else",
 /*  32 */ "condlines ::= condline",
 /*  33 */ "condline ::= context LCURLY metalines RCURLY",
 /*  34 */ "cond_else ::= context_else LCURLY metalines RCURLY",
 /*  35 */ "context ::= DOLLAR SRVVARNAME LBRACKET stringop RBRACKET cond expression",
 /*  36 */ "context_else ::=",
 /*  37 */ "cond ::= EQ",
 /*  38 */ "cond ::= MATCH",
 /*  39 */ "cond ::= NE",
 /*  40 */ "cond ::= NOMATCH",
 /*  41 */ "cond ::= PREFIX",
 /*  42 */ "cond ::= SUFFIX",
 /*  43 */ "stringop ::= expression",
 /*  44 */ "include ::= INCLUDE stringop",
 /*  45 */ "include_shell ::= INCLUDE_SHELL stringop",
};
#endif /* NDEBUG */

/*
** This function returns the symbolic name associated with a token
** value.
*/
#if 0
const char *configparserTokenName(int tokenType){
#ifndef NDEBUG
  if( tokenType>0 && (size_t)tokenType<(sizeof(yyTokenName)/sizeof(yyTokenName[0])) ){
    return yyTokenName[tokenType];
  }else{
    return "Unknown";
  }
#else
  return "";
#endif
}
#endif

/*
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to configparser and configparserFree.
*/
void *configparserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
#line 387 "../../src/configparser.y"
{ buffer_free((yypminor->yy0)); }
#line 784 "./configparser.c"
      break;
    case 38:
#line 378 "../../src/configparser.y"
{ if ((yypminor->yy59)) (yypminor->yy59)->fn->free((yypminor->yy59)); }
#line 789 "./configparser.c"
      break;
    case 39:
#line 379 "../../src/configparser.y"
{ if ((yypminor->yy59)) (yypminor->yy59)->fn->free((yypminor->yy59)); }
#line 794 "./configparser.c"
      break;
    case 40:
#line 380 "../../src/configparser.y"
{ if ((yypminor->yy59)) (yypminor->yy59)->fn->free((yypminor->yy59)); }
#line 799 "./configparser.c"
      break;
    case 43:
#line 381 "../../src/configparser.y"
{ array_free((yypminor->yy38)); }
#line 804 "./configparser.c"
      break;
    case 44:
#line 382 "../../src/configparser.y"
{ array_free((yypminor->yy38)); }
#line 809 "./configparser.c"
      break;
    case 45:
#line 383 "../../src/configparser.y"
{ buffer_free((yypminor->yy9)); }
#line 814 "./configparser.c"
      break;
    case 46:
#line 384 "../../src/configparser.y"
{ buffer_free((yypminor->yy9)); }
#line 819 "./configparser.c"
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos;

  if( pParser->yyidx<0 ) return 0;
  yytos = &pParser->yystack[pParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor( yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/*
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from configparserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void configparserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==NULL ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
  (*freeProc)((void*)pParser);
}

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;

  /* if( pParser->yyidx<0 ) return YY_NO_ACTION;  */
  i = yy_shift_ofst[stateno];
  if( i==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || (size_t)i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
    int iFallback;            /* Fallback token */
    if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
           && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
           yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
      }
#endif
      return yy_find_shift_action(pParser, iFallback);
    }
#endif
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;

  i = yy_reduce_ofst[stateno];
  if( i==YY_REDUCE_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || (size_t)i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
  if( yypParser->yyidx>=YYSTACKDEPTH ){
     configparserARG_FETCH;
     yypParser->yyidx--;
#ifndef NDEBUG
     if( yyTraceFILE ){
       fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
     }
#endif
     while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
     /* Here code is inserted which will execute if the parser
     ** stack every overflows */
     configparserARG_STORE; /* Suppress warning about unused %extra_argument var */
     return;
  }
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 30, 1 },
  { 31, 2 },
  { 31, 0 },
  { 32, 1 },
  { 32, 1 },
  { 32, 2 },
  { 32, 1 },
  { 32, 1 },
  { 32, 1 },
  { 33, 3 },
  { 33, 3 },
  { 33, 3 },
  { 45, 1 },
  { 39, 3 },
  { 39, 1 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 38, 1 },
  { 44, 2 },
  { 44, 3 },
  { 43, 3 },
  { 43, 2 },
  { 43, 1 },
  { 40, 1 },
  { 40, 3 },
  { 48, 1 },
  { 48, 0 },
  { 49, 1 },
  { 34, 4 },
  { 35, 4 },
  { 35, 4 },
  { 35, 1 },
  { 41, 4 },
  { 42, 4 },
  { 50, 7 },
  { 51, 0 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 46, 1 },
  { 36, 2 },
  { 37, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  configparserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE ) {
    if (yyruleno>=0
        && (size_t)yyruleno<sizeof(yyRuleName)/sizeof(yyRuleName[0]) ){
      fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
        yyRuleName[yyruleno]);
    } else {
      return; /*(should not happen)*/
    }
  }
#endif /* NDEBUG */

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0:
        /* No destructor defined for metalines */
        break;
      case 1:
        /* No destructor defined for metalines */
        /* No destructor defined for metaline */
        break;
      case 2:
        break;
      case 3:
        /* No destructor defined for varline */
        break;
      case 4:
        /* No destructor defined for global */
        break;
      case 5:
#line 360 "../../src/configparser.y"
{ yymsp[-1].minor.yy18 = NULL; }
#line 1100 "./configparser.c"
  yy_destructor(1,&yymsp[0].minor);
        break;
      case 6:
        /* No destructor defined for include */
        break;
      case 7:
        /* No destructor defined for include_shell */
        break;
      case 8:
  yy_destructor(1,&yymsp[0].minor);
        break;
      case 9:
#line 389 "../../src/configparser.y"
{
  if (ctx->ok) {
    buffer_copy_buffer(&yymsp[0].minor.yy59->key, yymsp[-2].minor.yy9);
    if (strncmp(yymsp[-2].minor.yy9->ptr, "env.", sizeof("env.") - 1) == 0) {
      fprintf(stderr, "Setting env variable is not supported in conditional %d %s: %s\n",
          ctx->current->context_ndx,
          ctx->current->key.ptr, yymsp[-2].minor.yy9->ptr);
      ctx->ok = 0;
    } else if (NULL == array_get_element_klen(ctx->current->value, BUF_PTR_LEN(&yymsp[0].minor.yy59->key))) {
      array_insert_unique(ctx->current->value, yymsp[0].minor.yy59);
      yymsp[0].minor.yy59 = NULL;
    } else {
      fprintf(stderr, "Duplicate config variable in conditional %d %s: %s\n",
              ctx->current->context_ndx,
              ctx->current->key.ptr, yymsp[0].minor.yy59->key.ptr);
      ctx->ok = 0;
    }
  }
  buffer_free(yymsp[-2].minor.yy9);
  yymsp[-2].minor.yy9 = NULL;
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1137 "./configparser.c"
  yy_destructor(2,&yymsp[-1].minor);
        break;
      case 10:
#line 413 "../../src/configparser.y"
{
  if (ctx->ok) {
    if (strncmp(yymsp[-2].minor.yy9->ptr, "env.", sizeof("env.") - 1) == 0) {
      fprintf(stderr, "Setting env variable is not supported in conditional %d %s: %s\n",
              ctx->current->context_ndx,
              ctx->current->key.ptr, yymsp[-2].minor.yy9->ptr);
      ctx->ok = 0;
    } else {
      buffer_copy_buffer(&yymsp[0].minor.yy59->key, yymsp[-2].minor.yy9);
      array_replace(ctx->current->value, yymsp[0].minor.yy59);
      yymsp[0].minor.yy59 = NULL;
    }
  }
  buffer_free(yymsp[-2].minor.yy9);
  yymsp[-2].minor.yy9 = NULL;
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1160 "./configparser.c"
  yy_destructor(3,&yymsp[-1].minor);
        break;
      case 11:
#line 432 "../../src/configparser.y"
{
  if (ctx->ok) {
    array *vars = ctx->current->value;
    data_unset *du;

    if (strncmp(yymsp[-2].minor.yy9->ptr, "env.", sizeof("env.") - 1) == 0) {
      fprintf(stderr, "Appending env variable is not supported in conditional %d %s: %s\n",
          ctx->current->context_ndx,
          ctx->current->key.ptr, yymsp[-2].minor.yy9->ptr);
      ctx->ok = 0;
    } else if (NULL != (du = array_extract_element_klen(vars, BUF_PTR_LEN(yymsp[-2].minor.yy9))) || NULL != (du = configparser_get_variable(ctx, yymsp[-2].minor.yy9))) {
      du = configparser_merge_data(du, yymsp[0].minor.yy59);
      if (NULL == du) {
        ctx->ok = 0;
      }
      else {
        buffer_copy_buffer(&du->key, yymsp[-2].minor.yy9);
        array_insert_unique(ctx->current->value, du);
      }
    } else {
      buffer_copy_buffer(&yymsp[0].minor.yy59->key, yymsp[-2].minor.yy9);
      array_insert_unique(ctx->current->value, yymsp[0].minor.yy59);
      yymsp[0].minor.yy59 = NULL;
    }
  }
  buffer_free(yymsp[-2].minor.yy9);
  yymsp[-2].minor.yy9 = NULL;
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1195 "./configparser.c"
  yy_destructor(4,&yymsp[-1].minor);
        break;
      case 12:
#line 463 "../../src/configparser.y"
{
  if (strchr(yymsp[0].minor.yy0->ptr, '.') == NULL) {
    buffer_copy_string((yygotominor.yy9 = buffer_init()), "var.");
    buffer_append_string_buffer(yygotominor.yy9, yymsp[0].minor.yy0);
  } else {
    yygotominor.yy9 = yymsp[0].minor.yy0;
    yymsp[0].minor.yy0 = NULL;
  }
  buffer_free(yymsp[0].minor.yy0);
  yymsp[0].minor.yy0 = NULL;
}
#line 1211 "./configparser.c"
        break;
      case 13:
#line 475 "../../src/configparser.y"
{
  yygotominor.yy59 = NULL;
  if (ctx->ok) {
    yygotominor.yy59 = configparser_merge_data(yymsp[-2].minor.yy59, yymsp[0].minor.yy59);
    yymsp[-2].minor.yy59 = NULL;
    if (NULL == yygotominor.yy59) {
      ctx->ok = 0;
    }
  }
  if (yymsp[-2].minor.yy59) yymsp[-2].minor.yy59->fn->free(yymsp[-2].minor.yy59);
  yymsp[-2].minor.yy59 = NULL;
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1229 "./configparser.c"
  yy_destructor(6,&yymsp[-1].minor);
        break;
      case 14:
#line 490 "../../src/configparser.y"
{
  yygotominor.yy59 = yymsp[0].minor.yy59;
  yymsp[0].minor.yy59 = NULL;
}
#line 1238 "./configparser.c"
        break;
      case 15:
#line 495 "../../src/configparser.y"
{
  yygotominor.yy59 = NULL;
  if (ctx->ok) {
    if (strncmp(yymsp[0].minor.yy9->ptr, "env.", sizeof("env.") - 1) == 0) {
      char *env;

      if (NULL != (env = getenv(yymsp[0].minor.yy9->ptr + 4))) {
        data_string *ds;
        ds = array_data_string_init();
        buffer_append_string(&ds->value, env);
        yygotominor.yy59 = (data_unset *)ds;
      }
      else {
        fprintf(stderr, "Undefined env variable: %s\n", yymsp[0].minor.yy9->ptr + 4);
        ctx->ok = 0;
      }
    } else if (NULL == (yygotominor.yy59 = configparser_get_variable(ctx, yymsp[0].minor.yy9))) {
      fprintf(stderr, "Undefined config variable: %s\n", yymsp[0].minor.yy9->ptr);
      ctx->ok = 0;
    }
  }
  buffer_free(yymsp[0].minor.yy9);
  yymsp[0].minor.yy9 = NULL;
}
#line 1266 "./configparser.c"
        break;
      case 16:
#line 520 "../../src/configparser.y"
{
  yygotominor.yy59 = (data_unset *)array_data_string_init();
  /* assumes array_data_string_init() result does not need swap, buffer_free()*/
  memcpy(&((data_string *)yygotominor.yy59)->value, yymsp[0].minor.yy0, sizeof(*yymsp[0].minor.yy0));
  free(yymsp[0].minor.yy0);
  yymsp[0].minor.yy0 = NULL;
}
#line 1277 "./configparser.c"
        break;
      case 17:
#line 528 "../../src/configparser.y"
{
  char *endptr;
  yygotominor.yy59 = (data_unset *)array_data_integer_init();
  errno = 0;
  ((data_integer *)(yygotominor.yy59))->value = strtol(yymsp[0].minor.yy0->ptr, &endptr, 10);
  /* skip trailing whitespace */
  if (endptr != yymsp[0].minor.yy0->ptr) while (isspace(*(unsigned char *)endptr)) endptr++;
  if (0 != errno || *endptr != '\0') {
    fprintf(stderr, "error parsing number: '%s'\n", yymsp[0].minor.yy0->ptr);
    ctx->ok = 0;
  }
  buffer_free(yymsp[0].minor.yy0);
  yymsp[0].minor.yy0 = NULL;
}
#line 1295 "./configparser.c"
        break;
      case 18:
#line 542 "../../src/configparser.y"
{
  yygotominor.yy59 = (data_unset *)array_data_array_init();
  /* assumes array_data_array_init() result does not need swap, array_free() */
  memcpy(&((data_array *)(yygotominor.yy59))->value, yymsp[0].minor.yy38, sizeof(*yymsp[0].minor.yy38));
  free(yymsp[0].minor.yy38);
  yymsp[0].minor.yy38 = NULL;
}
#line 1306 "./configparser.c"
        break;
      case 19:
#line 549 "../../src/configparser.y"
{
  yygotominor.yy38 = array_init(8);
}
#line 1313 "./configparser.c"
  yy_destructor(9,&yymsp[-1].minor);
  yy_destructor(10,&yymsp[0].minor);
        break;
      case 20:
#line 552 "../../src/configparser.y"
{
  yygotominor.yy38 = yymsp[-1].minor.yy38;
  yymsp[-1].minor.yy38 = NULL;
}
#line 1323 "./configparser.c"
  yy_destructor(9,&yymsp[-2].minor);
  yy_destructor(10,&yymsp[0].minor);
        break;
      case 21:
#line 557 "../../src/configparser.y"
{
  yygotominor.yy38 = NULL;
  if (ctx->ok) {
    if (buffer_is_unset(&yymsp[0].minor.yy59->key) ||
        NULL == array_get_element_klen(yymsp[-2].minor.yy38, BUF_PTR_LEN(&yymsp[0].minor.yy59->key))) {
      array_insert_unique(yymsp[-2].minor.yy38, yymsp[0].minor.yy59);
      yymsp[0].minor.yy59 = NULL;
    } else {
      fprintf(stderr, "Error: duplicate array-key: %s. Please get rid of the duplicate entry.\n",
              yymsp[0].minor.yy59->key.ptr);
      ctx->ok = 0;
    }

    yygotominor.yy38 = yymsp[-2].minor.yy38;
    yymsp[-2].minor.yy38 = NULL;
  }
  array_free(yymsp[-2].minor.yy38);
  yymsp[-2].minor.yy38 = NULL;
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1350 "./configparser.c"
  yy_destructor(11,&yymsp[-1].minor);
        break;
      case 22:
#line 579 "../../src/configparser.y"
{
  yygotominor.yy38 = yymsp[-1].minor.yy38;
  yymsp[-1].minor.yy38 = NULL;
}
#line 1359 "./configparser.c"
  yy_destructor(11,&yymsp[0].minor);
        break;
      case 23:
#line 584 "../../src/configparser.y"
{
  yygotominor.yy38 = NULL;
  if (ctx->ok) {
    yygotominor.yy38 = array_init(4);
    array_insert_unique(yygotominor.yy38, yymsp[0].minor.yy59);
    yymsp[0].minor.yy59 = NULL;
  }
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1374 "./configparser.c"
        break;
      case 24:
#line 595 "../../src/configparser.y"
{
  yygotominor.yy59 = yymsp[0].minor.yy59;
  yymsp[0].minor.yy59 = NULL;
}
#line 1382 "./configparser.c"
        break;
      case 25:
#line 599 "../../src/configparser.y"
{
  yygotominor.yy59 = NULL;
  if (ctx->ok) {
    buffer_copy_buffer(&yymsp[0].minor.yy59->key, yymsp[-2].minor.yy9);

    yygotominor.yy59 = yymsp[0].minor.yy59;
    yymsp[0].minor.yy59 = NULL;
  }
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
  buffer_free(yymsp[-2].minor.yy9);
  yymsp[-2].minor.yy9 = NULL;
}
#line 1399 "./configparser.c"
  yy_destructor(12,&yymsp[-1].minor);
        break;
      case 26:
  yy_destructor(1,&yymsp[0].minor);
        break;
      case 27:
        break;
      case 28:
#line 616 "../../src/configparser.y"
{
  data_config *dc;
  dc = configparser_get_data_config(ctx->srv->config_context, CONST_STR_LEN("global"));
  force_assert(dc);
  configparser_push(ctx, dc, 0);
}
#line 1415 "./configparser.c"
  yy_destructor(13,&yymsp[0].minor);
        break;
      case 29:
#line 623 "../../src/configparser.y"
{
  configparser_pop(ctx);
}
#line 1423 "./configparser.c"
        /* No destructor defined for globalstart */
  yy_destructor(14,&yymsp[-2].minor);
        /* No destructor defined for metalines */
  yy_destructor(15,&yymsp[0].minor);
        break;
      case 30:
#line 627 "../../src/configparser.y"
{
  yygotominor.yy18 = NULL;
  if (ctx->ok) {
    if (yymsp[-3].minor.yy18->context_ndx >= yymsp[0].minor.yy18->context_ndx) {
      fprintf(stderr, "unreachable else condition\n");
      ctx->ok = 0;
    }
    if (yymsp[-3].minor.yy18->cond == CONFIG_COND_ELSE) {
      fprintf(stderr, "unreachable condition following else catch-all\n");
      ctx->ok = 0;
    }
    yymsp[0].minor.yy18->prev = yymsp[-3].minor.yy18;
    yymsp[-3].minor.yy18->next = yymsp[0].minor.yy18;
    yygotominor.yy18 = yymsp[0].minor.yy18;
  }
  yymsp[-3].minor.yy18 = NULL;
  yymsp[0].minor.yy18 = NULL;
}
#line 1449 "./configparser.c"
        /* No destructor defined for eols */
  yy_destructor(16,&yymsp[-1].minor);
        break;
      case 31:
#line 646 "../../src/configparser.y"
{
  yygotominor.yy18 = NULL;
  if (ctx->ok) {
    if (yymsp[-3].minor.yy18->context_ndx >= yymsp[0].minor.yy18->context_ndx) {
      fprintf(stderr, "unreachable else condition\n");
      ctx->ok = 0;
    }
    if (yymsp[-3].minor.yy18->cond == CONFIG_COND_ELSE) {
      fprintf(stderr, "unreachable condition following else catch-all\n");
      ctx->ok = 0;
    }
  }
  if (ctx->ok) {
    size_t pos;
    data_config *dc;
    dc = (data_config *)array_extract_element_klen(ctx->all_configs, BUF_PTR_LEN(&yymsp[0].minor.yy18->key));
    force_assert(yymsp[0].minor.yy18 == dc);
    buffer_copy_buffer(&yymsp[0].minor.yy18->key, &yymsp[-3].minor.yy18->key);
    yymsp[0].minor.yy18->comp_key = yymsp[0].minor.yy18->key.ptr + (yymsp[-3].minor.yy18->comp_key - yymsp[-3].minor.yy18->key.ptr);
    yymsp[0].minor.yy18->comp = yymsp[-3].minor.yy18->comp;
    /*buffer_copy_buffer(&yymsp[0].minor.yy18->string, &yymsp[-3].minor.yy18->string);*/
    /* -2 for "==" and minus 3 for spaces and quotes around string (in key) */
    pos = buffer_clen(&yymsp[0].minor.yy18->key) - buffer_clen(&yymsp[-3].minor.yy18->string) - 5;
    switch(yymsp[-3].minor.yy18->cond) {
    case CONFIG_COND_NE:
      yymsp[0].minor.yy18->key.ptr[pos] = '='; /* opposite cond */
      /*buffer_copy_string_len(yymsp[0].minor.yy18->op, CONST_STR_LEN("=="));*/
      break;
    case CONFIG_COND_EQ:
      yymsp[0].minor.yy18->key.ptr[pos] = '!'; /* opposite cond */
      /*buffer_copy_string_len(yymsp[0].minor.yy18->op, CONST_STR_LEN("!="));*/
      break;
    case CONFIG_COND_NOMATCH:
      yymsp[0].minor.yy18->key.ptr[pos] = '='; /* opposite cond */
      /*buffer_copy_string_len(yymsp[0].minor.yy18->op, CONST_STR_LEN("=~"));*/
      break;
    case CONFIG_COND_MATCH:
      yymsp[0].minor.yy18->key.ptr[pos] = '!'; /* opposite cond */
      /*buffer_copy_string_len(yymsp[0].minor.yy18->op, CONST_STR_LEN("!~"));*/
      break;
    case CONFIG_COND_PREFIX:
      yymsp[0].minor.yy18->key.ptr[pos] = '!'; /* opposite cond */
      /*buffer_copy_string_len(yymsp[0].minor.yy18->op, CONST_STR_LEN("!^"));*/
      break;
    case CONFIG_COND_SUFFIX:
      yymsp[0].minor.yy18->key.ptr[pos] = '!'; /* opposite cond */
      /*buffer_copy_string_len(yymsp[0].minor.yy18->op, CONST_STR_LEN("!$"));*/
      break;
    default: /* should not happen; CONFIG_COND_ELSE checked further above */
      force_assert(0);
    }

    if (NULL == (dc = configparser_get_data_config(ctx->all_configs, BUF_PTR_LEN(&yymsp[0].minor.yy18->key)))) {
      /* re-insert into ctx->all_configs with new yymsp[0].minor.yy18->key */
      array_insert_unique(ctx->all_configs, (data_unset *)yymsp[0].minor.yy18);
      yymsp[0].minor.yy18->prev = yymsp[-3].minor.yy18;
      yymsp[-3].minor.yy18->next = yymsp[0].minor.yy18;
    } else {
      fprintf(stderr, "unreachable else condition\n");
      ctx->ok = 0;
      yymsp[0].minor.yy18->fn->free((data_unset *)yymsp[0].minor.yy18);
      yymsp[0].minor.yy18 = dc;
    }

    yygotominor.yy18 = yymsp[0].minor.yy18;
  }
  yymsp[-3].minor.yy18 = NULL;
  yymsp[0].minor.yy18 = NULL;
}
#line 1524 "./configparser.c"
        /* No destructor defined for eols */
  yy_destructor(16,&yymsp[-1].minor);
        break;
      case 32:
#line 716 "../../src/configparser.y"
{
  yygotominor.yy18 = yymsp[0].minor.yy18;
  yymsp[0].minor.yy18 = NULL;
}
#line 1534 "./configparser.c"
        break;
      case 33:
#line 721 "../../src/configparser.y"
{
  yygotominor.yy18 = NULL;
  if (ctx->ok) {
    yygotominor.yy18 = configparser_pop(ctx);
  }
}
#line 1544 "./configparser.c"
        /* No destructor defined for context */
  yy_destructor(14,&yymsp[-2].minor);
        /* No destructor defined for metalines */
  yy_destructor(15,&yymsp[0].minor);
        break;
      case 34:
#line 728 "../../src/configparser.y"
{
  yygotominor.yy18 = NULL;
  if (ctx->ok) {
    yygotominor.yy18 = configparser_pop(ctx);
  }
}
#line 1558 "./configparser.c"
        /* No destructor defined for context_else */
  yy_destructor(14,&yymsp[-2].minor);
        /* No destructor defined for metalines */
  yy_destructor(15,&yymsp[0].minor);
        break;
      case 35:
#line 735 "../../src/configparser.y"
{

  if (ctx->ok && yymsp[0].minor.yy59->type != TYPE_STRING) {
    fprintf(stderr, "rvalue must be string");
    ctx->ok = 0;
  }

  if (ctx->ok) {
    configparser_parse_condition(ctx, yymsp[-5].minor.yy0, yymsp[-3].minor.yy9, yymsp[-1].minor.yy69, &((data_string *)yymsp[0].minor.yy59)->value);
  }

  buffer_free(yymsp[-5].minor.yy0);
  yymsp[-5].minor.yy0 = NULL;
  buffer_free(yymsp[-3].minor.yy9);
  yymsp[-3].minor.yy9 = NULL;
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1584 "./configparser.c"
  yy_destructor(17,&yymsp[-6].minor);
  yy_destructor(19,&yymsp[-4].minor);
  yy_destructor(20,&yymsp[-2].minor);
        break;
      case 36:
#line 754 "../../src/configparser.y"
{
  if (ctx->ok) {
    configparser_parse_else_condition(ctx);
  }
}
#line 1596 "./configparser.c"
        break;
      case 37:
#line 760 "../../src/configparser.y"
{
  yygotominor.yy69 = CONFIG_COND_EQ;
}
#line 1603 "./configparser.c"
  yy_destructor(21,&yymsp[0].minor);
        break;
      case 38:
#line 763 "../../src/configparser.y"
{
  yygotominor.yy69 = CONFIG_COND_MATCH;
}
#line 1611 "./configparser.c"
  yy_destructor(22,&yymsp[0].minor);
        break;
      case 39:
#line 766 "../../src/configparser.y"
{
  yygotominor.yy69 = CONFIG_COND_NE;
}
#line 1619 "./configparser.c"
  yy_destructor(23,&yymsp[0].minor);
        break;
      case 40:
#line 769 "../../src/configparser.y"
{
  yygotominor.yy69 = CONFIG_COND_NOMATCH;
}
#line 1627 "./configparser.c"
  yy_destructor(24,&yymsp[0].minor);
        break;
      case 41:
#line 772 "../../src/configparser.y"
{
  yygotominor.yy69 = CONFIG_COND_PREFIX;
}
#line 1635 "./configparser.c"
  yy_destructor(25,&yymsp[0].minor);
        break;
      case 42:
#line 775 "../../src/configparser.y"
{
  yygotominor.yy69 = CONFIG_COND_SUFFIX;
}
#line 1643 "./configparser.c"
  yy_destructor(26,&yymsp[0].minor);
        break;
      case 43:
#line 779 "../../src/configparser.y"
{
  yygotominor.yy9 = NULL;
  if (ctx->ok) {
    if (yymsp[0].minor.yy59->type == TYPE_STRING) {
      buffer_copy_buffer((yygotominor.yy9 = buffer_init()), &((data_string*)yymsp[0].minor.yy59)->value);
    } else if (yymsp[0].minor.yy59->type == TYPE_INTEGER) {
      yygotominor.yy9 = buffer_init();
      buffer_append_int(yygotominor.yy9, ((data_integer *)yymsp[0].minor.yy59)->value);
    } else {
      fprintf(stderr, "operand must be string");
      ctx->ok = 0;
    }
  }
  if (yymsp[0].minor.yy59) yymsp[0].minor.yy59->fn->free(yymsp[0].minor.yy59);
  yymsp[0].minor.yy59 = NULL;
}
#line 1664 "./configparser.c"
        break;
      case 44:
#line 796 "../../src/configparser.y"
{
  if (ctx->ok) {
    if (0 != config_parse_file(ctx->srv, ctx, yymsp[0].minor.yy9->ptr)) {
      ctx->ok = 0;
    }
  }
  buffer_free(yymsp[0].minor.yy9);
  yymsp[0].minor.yy9 = NULL;
}
#line 1677 "./configparser.c"
  yy_destructor(27,&yymsp[-1].minor);
        break;
      case 45:
#line 806 "../../src/configparser.y"
{
  if (ctx->ok) {
    if (0 != config_parse_cmd(ctx->srv, ctx, yymsp[0].minor.yy9->ptr)) {
      ctx->ok = 0;
    }
  }
  buffer_free(yymsp[0].minor.yy9);
  yymsp[0].minor.yy9 = NULL;
}
#line 1691 "./configparser.c"
  yy_destructor(28,&yymsp[-1].minor);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yypParser,yygoto);
  if( yyact < YYNSTATE ){
    yy_shift(yypParser,yyact,yygoto,&yygotominor);
  }else if( yyact == YYNSTATE + YYNRULE + 1 ){
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  configparserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 351 "../../src/configparser.y"

  ctx->ok = 0;

#line 1725 "./configparser.c"
  configparserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  configparserARG_FETCH;
  UNUSED(yymajor);
  UNUSED(yyminor);
#define TOKEN (yyminor.yy0)
  configparserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  configparserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  configparserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "configparserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void configparser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  configparserTOKENTYPE yyminor       /* The value for the token */
  configparserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
    if( yymajor==0 ) return;
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  configparserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      if( yyendofinput && yypParser->yyidx>=0 ){
        yymajor = 0;
      }else{
        yymajor = YYNOCODE;
      }
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else if( yyact == YY_ERROR_ACTION ){
      int yymx;
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_shift_action(yypParser,YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }else{
      yy_accept(yypParser);
      yymajor = YYNOCODE;
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
