#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_
#include "first.h"

typedef struct tree_node {
    struct tree_node * left, * right;
    int key;
    void *data;
} splay_tree;


splay_tree * splaytree_splay (splay_tree *t, int key);
splay_tree * splaytree_insert(splay_tree *t, int key, void *data);
splay_tree * splaytree_delete(splay_tree *t, int key);


#include "algo_md.h"

__attribute_pure__
static inline int32_t splaytree_djbhash(const char *str, const uint32_t len);
static inline int32_t splaytree_djbhash(const char *str, const uint32_t len)
{
    /* strip highest bit of hash value for splaytree */
    return (int32_t)(djbhash(str,len,DJBHASH_INIT) & ~(((uint32_t)1) << 31));
}


#endif
