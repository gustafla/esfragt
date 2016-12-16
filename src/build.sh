#!/bin/sh

git clone https://github.com/luutifa/lib3dapp.git
(cd lib3dapp && git pull)
make clean
make $1
