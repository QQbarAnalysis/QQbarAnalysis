#!/bin/sh

if [ -d "$HOME/QQbarAnalysis/build" ]; then
	rm -rf "$HOME/QQbarAnalysis/build"
fi

mkdir "$HOME/QQbarAnalysis/build"
cd "$HOME/QQbarAnalysis/build"
cmake -C $ILCSOFT/ILCSoft.cmake ..
make
make install
