#!/bin/bash


docker exec fypBlockScitemp sh -c "cd /root/BlockSci/release  && CC=gcc-7 CXX=g++-7 cmake -DCMAKE_BUILD_TYPE=Release .. && make && make install"
