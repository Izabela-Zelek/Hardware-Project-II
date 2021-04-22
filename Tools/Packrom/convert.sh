#!/bin/sh
for file in `find . -name '*.hex'`
do
        FILENAME=`basename $file | cut -d '.' -f1`
        echo name=$FILENAME >> gameinfo.properties
        echo author=Unknown >> gameinfo.properties
        echo year=0000 >> gameinfo.properties
        echo genre=0 >> gameinfo.properties
        wine packrom.exe $file $FILENAME.uze gameinfo.properties 
        rm gameinfo.properties
done