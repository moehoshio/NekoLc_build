#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Usage: $0 <path_to_executable> <destination_directory>"
  exit 1
fi

PROGRAM=$1
DEST_DIR=$2

if [ -z "$PROGRAM" ]; then
    echo "Error: Program not found archive PROGRAM"
    exit 1
fi

mkdir -p $DEST_DIR

# for lib in $(otool -L $PROGRAM | awk '{print $1}' | tail -n +2); do
#   if ["$lib" == /System/*]; then
#     echo "Skipping system library: $lib"
#     continue
#   fi

#   $BASENAME=$(basename "$lib")
#   echo "Copying $lib to $DEST_DIR/$BASENAME..."
#   cp "$lib" "$DEST_DIR/$BASENAME"

  
  
# done
cp "/opt/homebrew/opt/qt/lib/QtWidgets.framework/Versions/A/QtWidgets" "$DEST_DIR/QtWidgets"
cp "/opt/homebrew/opt/qt/lib/QtGui.framework/Versions/A/QtGui" "$DEST_DIR/QtGui"
cp "/opt/homebrew/opt/openssl@3/lib/libssl.3.dylib" "$DEST_DIR/libssl.3.dylib"
cp "/opt/homebrew/opt/openssl@3/lib/libcrypto.3.dylib" "$DEST_DIR/libcrypto.3.dylib"

install_name_tool -change "/opt/homebrew/opt/qt/lib/QtWidgets.framework/Versions/A/QtWidgets" "@executable_path/$DEST_DIR/QtWidgets" "$PROGRAM"
install_name_tool -change "/opt/homebrew/opt/qt/lib/QtGui.framework/Versions/A/QtGui" "@executable_path/$DEST_DIR/QtGui" "$PROGRAM"
install_name_tool -change "/opt/homebrew/opt/openssl@3/lib/libssl.3.dylib" "@executable_path/$DEST_DIR/libssl.3.dylib" "$PROGRAM"
install_name_tool -change "/opt/homebrew/opt/openssl@3/lib/libcrypto.3.dylib" "@executable_path/$DEST_DIR/libcrypto.3.dylib" "$PROGRAM"

echo "All dependencies copied and paths updated."