#!/bin/bash

USERID=$(id -u)
USERGROUP=$(id -g)
echo $USERID:$USERGROUP
docker run -d -i \
       --name  simq_container \
       --mount type=bind,source=$(pwd),target=/src \
       --mount type=bind,source=$(pwd)/bin,target=/dst_bin \
       --mount type=bind,source=$(pwd)/build,target=/dst_build \
       --mount type=bind,source=$(pwd)/evaluation_scripts,target=/evaluation_scripts \
       --mount type=bind,source=$(pwd)/benchmark,target=/benchmark \
       --user=$USERID:$USERGROUP \
       simq_ubuntu:1.0

