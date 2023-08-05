# Build json-c contexts

## Prepare json-c
- Run ./prepare-json-c.sh to extract archive
- Run python build-json-c.py to build the library

## Find usage context of json-c in gdal
- Run ./prepare-gdal.sh to extract archive
- Run python3 build-gdal-context.py to generate fuzz drivers for contexts

## Find usage context of json-c in libstorj
- Run ./prepare-storj.sh to extract archive
- Run python3 build-storj-context.py to generate fuzz drivers for contexts
