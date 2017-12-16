#!/bin/bash

set -e

for PROJECT in de.morknet.sct.qt.example.*
do
   cd $PROJECT
   test -e Makefile && make distclean
   qmake
   make -j 2
   cd ..
done
