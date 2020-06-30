#!/bin/bash

#Delete
docker rmi $(docker images -q) --force

#Build
docker build -t simq_ubuntu:1.0 -f ubuntu.Dockerfile .
