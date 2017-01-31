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
git pull
git checkout $GREASE_LIB_BRANCH

if [ "$1" != "skipdeps" ]; then
    echo ">>>>>>>>> Building libgrease dependencies..."
    # install the libgrease dependencies
    deps/install-deps.sh
else
    echo ">>>>>>>>> Ok. Skipping dependencies"
fi

echo "Building libgrease.a"
# make sure we build fresh
rm -f *.o *.a
make libgrease.a

if [ -e libgrease.a ]; then
    cp libgrease.a $SELF/deps/lib
    echo ">>>>>>>>> Success. libgrease.a ready."
else
    echo ">>>>>>>>> ERROR: libgrease.a missing or not built."
fi




