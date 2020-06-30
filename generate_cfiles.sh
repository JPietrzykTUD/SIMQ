#!/bin/bash
SCRIPTPATH="${1:-empty}"

[ $# -eq 0 ] && exit 1

cd $SCRIPTPATH || exit
python3 create_simq.py
