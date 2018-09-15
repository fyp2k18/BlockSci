#!/bin/bash

PORT=88
IMAGE_NAME=pubuduwelagedara/blocksci

#sudo docker run -it -d --name fypBlockSci -v /home/uthpala/Uthpala/Uthpala/blocksci/blocksci-data:/root/bitcoin-data -v /home/uthpala/Uthpala/research/BlockSci/src:/root/BlockSci/src -p $PORT:8888 $IMAGE_NAME
sudo docker run -it -d --name fypBlockSci -v /home/wasn/bitcoin-data/blocksci-514496:/root/bitcoin-data -v /home/wasn/BlockSci/src:/root/BlockSci/src -p $PORT:8080 $IMAGE_NAME
