#!/bin/sh

rm lib3dapp
git clone https://github.com/luutifa/lib3dapp.git
make clean
make $1
