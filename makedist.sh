#!/bin/bash
FILES="*.cpp *.h testdata README PreflowPushExcessScaling PreflowPushFIFO PreflowPushHighestLabel PreflowPushRandom"
TARGET=PreflowPush-dist

echo "Running make clean"
make clean || true
make -f OurMakefile clean || true

rm -rf "$TARGET"
mkdir "$TARGET"

echo "Copying files to staging directory"
for file in $FILES; do
  cp -r "$file" "${TARGET}/";
done

cp -r OurMakefile "${TARGET}/Makefile"

echo "Creating tar ball"
tar cjf "${TARGET}.tar.bz2" $TARGET

echo "Done. See ${TARGET}.tar.bz2"
