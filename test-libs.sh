#!/bin/bash

ls -d */ > .subfolder.tmp

while IFS= read -r subfolder
do
    if [ ! -d "$subfolder/Docker.build.sh" ]
    then
        echo "-- [Futag]: Testing library $subfolder:"
        cd "$subfolder"
        echo "-- [Futag]: Build Docker container..."
        ./Docker.build.sh
        echo "-- [Futag]: Run Docker container..."
        ./Docker.run.sh
        cd ..
    fi
done < ".subfolder.tmp"

echo "-- [Futag]: All tests are done!"