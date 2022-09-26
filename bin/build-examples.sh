#!/bin/bash

set -e

test -e Makefile && make distclean
qmake -r
make -j `nproc`
