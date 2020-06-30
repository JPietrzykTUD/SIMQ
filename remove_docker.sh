#!/bin/bash

DOCKERID=$(docker images --format="{{.Repository}} {{.ID}}" | grep "^simq_ubuntu " | cut -d' ' -f2)
docker image rm $DOCKERID --force