#!/bin/bash

set -e

for PROJECT in de.morknet.sct.qt.example.*
do
   cd $PROJECT
   ant
   cd ..
done
