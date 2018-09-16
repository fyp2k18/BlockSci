#!/bin/bash

PORT=90
IMAGE_NAME=pubuduwelagedara/blockscitemp
NAME=fypBlockScitemp

sudo docker run -it -d --name $NAME -v /home/uthpala/Uthpala/Uthpala/blocksci/blocksci-data:/root/bitcoin-data -v /home/uthpala/Uthpala/research/BlockSci/src:/root/BlockSci/src -p $PORT:8888 $IMAGE_NAME

