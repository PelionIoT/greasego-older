#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do 
    SELF="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
    SOURCE="$(readlink "$SOURCE")"
    [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" 
done

SELF="$( cd -P "$( dirname "$SOURCE" )" && pwd )" # script's directory

cd $SELF
mkdir -p deps/bin deps/lib deps/include deps/src

cd $SELF/deps/src


GREASE_LIB="greaseLib"
GREASE_LIB_REPO="https://github.com/WigWagCo/greaseLib.git"
GREASE_LIB_BRANCH="master"

echo ">>>>>>>>> Getting greaselib repo: $GREASE_LIB_REPO @branch $GREASE_LIB_BRANCH"
if [ ! -d $GREASE_LIB ]; then
    git clone $GREASE_LIB_REPO
fi

cd $GREASE_LIB
if [ -d ".git" ]; then
    git pull
    git checkout $GREASE_LIB_BRANCH
fi

if [ "$1" != "skipdeps" ]; then
    echo ">>>>>>>>> Building libgrease dependencies..."
    # install the libgrease dependencies
    deps/install-deps.sh
else
    echo ">>>>>>>>> Ok. Skipping dependencies"
fi

echo "Building libgrease.a (debug)"
# make sure we build fresh
rm -f *.o *.a
# make the server version - which basically just bypasses checks for symbols
# on the client logging code
make libgrease.a-server-debug
make libgrease.so.1-debug
cp *.h $SELF/deps/include


if [ -e libgrease.a ]; then
    # migrate all of the greaselib dependencies up to the folder Go will use
    cp -r deps/build/lib/* $SELF/deps/lib
    cp -r deps/build/include/* $SELF/deps/include
    # move our binary into lib - static is all we use
    cp libgrease.a $SELF/deps/lib
    cp *.h $SELF/deps/include
    echo ">>>>>>>>> Success. libgrease.a ready."
else
    echo ">>>>>>>>> ERROR: libgrease.a missing or not built."
fi


if [ -e libgrease.so.1-debug ]; then
    # migrate all of the greaselib dependencies up to the folder Go will use
    cp -r deps/build/lib/* $SELF/deps/lib
    cp -r deps/build/include/* $SELF/deps/include
    cp $SELF/deps/src/greaseLib/deps/libuv-v1.10.1/include/uv* $SELF/deps/include
    # move our binary into lib - static is all we use
    cp libgrease.so.1-debug $SELF/deps/lib/libgrease.so.1
    cp *.h $SELF/deps/include
    echo ">>>>>>>>> Success. libgrease.so.1 ready."
    cd $SELF/deps/lib
    ln -s libgrease.so.1 libgrease.so 
    echo ">>>>>>>>> Success. libgrease.so link ready."
else
    echo ">>>>>>>>> ERROR: libgrease.so.1 missing or not built."
fi




