#/bin/bash
# the directory of the script

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# the temp directory used, within $DIR
# omit the -p parameter to create a temporal directory in the default location
WORK_DIR=`mktemp -d -p "$DIR"`

# check if tmp dir was created
if [[ ! "$WORK_DIR" || ! -d "$WORK_DIR" ]]; then
  echo "Could not create temp dir"
  exit 1
fi

# deletes the temp directory
function cleanup {      
  rm -rf "$WORK_DIR"
  echo "Deleted temp working directory $WORK_DIR"
}

# register the cleanup function to be called on the EXIT signal
trap cleanup EXIT

# implementation of script starts here
project_name="SM64_Save_File_Converter"
url="https://github.com/sonich2401/SM64_Save_File_Converter.git"

cd "$WORK_DIR"
git clone "$url" > nostdout.deletethis

echo
echo
echo Compiling $project_name ...
cd "$project_name"
sudo make install
