#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  SELF="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done

THIS_DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

pushd $THIS_DIR

# you need the -P !! --> http://stackoverflow.com/questions/32477816/safely-replacing-text-with-m4-disabling-new-defines

PREPROCESS="m4 -P -D DEBUG= macro-setup.m4 "

# m4 -P macro-setup.m4 -F m4setup.m4f

if [ ! -z "$DEBUG" ]; then
	echo "DEBUG IS ON!"
	PREPROCESS="m4 -P -D DEBUG=\$@ macro-setup.m4 "
fi

if [ ! -z "$PRETEND" ]; then
	echo "PRETEND IS ON!"
fi


for f in $(find "./src" -name '*.go'); do
	echo "--> "$f
#	echo `basename $f`
	FILENAME=`basename $f`
	DIR1=`dirname $f`
	DIR1=${DIR1#*/}
#	echo "------"
	if [ "$DIR1" != "src" ]; then
		echo "mkdir -p $DIR1"
		mkdir -p $DIR1
#		echo "--->"$DIR1"<--"
#		echo "****"
#		echo "output: $DIR1/$FILENAME"
		echo $PREPROCESS "src/$DIR1/$FILENAME" "> $DIR1/$FILENAME"
		if [ -z "$PRETEND" ]; then $PREPROCESS src/$DIR1/$FILENAME > $DIR1/$FILENAME; fi
	else
#		echo "output: $FILENAME"
		echo $PREPROCESS "src/$FILENAME" "> $FILENAME"
		if [ -z "$PRETEND" ]; then $PREPROCESS src/$FILENAME > $FILENAME; fi
	fi
done

popd


if [ ! -e "${THIS_DIR}/deps/lib/libgrease.a" ]; then
    echo ""
    echo "Build dependencies first!!!!!!!"
    echo ""
fi

pushd $THIS_DIR

make clean
if [ ! -z "$DEBUG" ]; then
	make bindings.a-debug
else
	make bindings.a
fi
go build github.com/WigWagCo/greasego
go install github.com/WigWagCo/greasego

popd