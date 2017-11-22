#!/usr/bin/env bash

for file in *.proto
do
    echo "Compiling $file file"
    protoc --cpp_out=./ProtoCompiled/ ${file}
done
