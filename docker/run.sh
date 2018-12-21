 #!/bin/bash

PORT=88
IMAGE_NAME=pubuduwelagedara/blocksci
NAME=fypBlockScitemp

 sudo docker run -it --privileged -d --name $NAME -v /home/uthpala/Uthpala/Uthpala/DockerVolume/blocksci-data:/root/bitcoin-data -v /home/uthpala/Uthpala/Uthpala/DockerVolume/BlockSci/tools:/root/BlockSci/tools -v /home/uthpala/Uthpala/Uthpala/DockerVolume/BlockSci/src:/root/BlockSci/src -p $PORT:8888 $IMAGE_NAME
 #sudo docker run -it -d --name $NAME -p $PORT:8888 $IMAGE_NAME
