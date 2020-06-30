#!/bin/bash
ROOTPATH=$(pwd)
cd bin
FILELIST=$(find ./ -type f -executable -print0 | xargs -0 -I {} echo "{}")
FID=0
declare -a FILE_ARRAY
for file in $FILELIST
do
   echo "[$FID]: $file"
   FILE_ARRAY[$FID]=$file
   FID=$((FID+1))
done
echo -n "Choose file to execute (0-$((FID-1))): "
read FID_SELECTED
if ! [[ "$FID_SELECTED" =~ ^[0-9]+$ ]]; then
   echo "Wrong format."
   exit 1
fi
if [[ "$FID_SELECTED" -ge "$FID" ]]; then
   echo "Wrong value."
   exit 1
fi
FILE_RELATIVE=${FILE_ARRAY[FID_SELECTED]}
FILE_NAME=$(basename $FILE_RELATIVE)
FILE_PATH=$(dirname $FILE_RELATIVE)
echo $FILE_PATH
echo $FILE_NAME
cd $FILE_PATH
BENCHMARKFILE=$(./$FILE_NAME)
echo "DONE."
FILE_PATH=${FILE_PATH//.\//}
mkdir -p $ROOTPATH/benchmark/$FILE_PATH/raw
mkdir -p $ROOTPATH/benchmark/$FILE_PATH/processed
mv $BENCHMARKFILE $ROOTPATH/benchmark/$FILE_PATH/raw
cd $ROOTPATH

./run_docker.sh
./exec_docker.sh simq_container ./run_evaluation.sh "evaluation_scripts/$FILE_NAME.py benchmark/$FILE_PATH $BENCHMARKFILE"
docker rm simq_container --force
