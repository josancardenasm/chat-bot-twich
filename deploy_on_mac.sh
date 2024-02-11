#!/bin/bash

#info: https://doc.qt.io/qt-6/macos-deployment.html

OSX_ARCHITECTURES="x86_64;arm64"
TOOLCHAIN_PATH="/Users/goonie/Qt/6.5.3/macos"

if [ -d "build" ]; then
    echo "Removing existing build folder..."
    rm -rf build
fi

cmake -DCMAKE_PREFIX_PATH=$TOOLCHAIN_PATH -DCMAKE_OSX_ARCHITECTURES=$OSX_ARCHITECTURES -B "build" -G Ninja

cd build; ninja

#Copy the frameworks
# mkdir appchat-bot-twich.app/Contents/Frameworks

$TOOLCHAIN_PATH/bin/macdeployqt appchat-bot-twich.app -qmldir=./.. -dmg


