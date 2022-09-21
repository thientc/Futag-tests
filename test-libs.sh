#!/bin/bash

ls -d */ > .subfolder.tmp

while IFS= read -r subfolder
do
    if [ ! -d "$subfolder/build.py" ]
    then
        echo "-- [Futag]: Testing library $subfolder:"
        cd "$subfolder"
        echo "-- [Futag]: Preparing..."
        ./prepare.sh
        echo "-- [Futag]: Executing Futag on library:"
        python build.py
        cd ..
    fi
done < ".subfolder.tmp"

echo "-- [Futag]: All tests are done!"