#!/bin/bash
SCRIPT_FILE="${1:-empty}"
DATA_PATH="${2:-empty}"
FILE_NAME="${3:-empty}"
python3 $SCRIPT_FILE $DATA_PATH $FILE_NAME
echo "Done."
