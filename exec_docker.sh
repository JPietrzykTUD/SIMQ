#!/bin/bash

NAME="${1:-empty}"
SCRIPT="${2}"
PARAMS="${@:3}"

[ $# -eq 1 ] && docker exec -ti "${NAME}" bash -l
[ $# -gt 2 ] && docker exec -ti "${NAME}" bash -l -c "cd src/ && ${SCRIPT} ${PARAMS}"


