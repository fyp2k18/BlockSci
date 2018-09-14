#!/bin/bash

PORT=88
IMAGE_NAME=pubuduwelagedara/blocksci

docker run -it -v /home/uthpala/Uthpala/Uthpala/blocksci/blocksci-data:/root/bitcoin-data -v ./../src:/root/BlockSci/src -p $PORT:8888 $IMAGE_NAME
