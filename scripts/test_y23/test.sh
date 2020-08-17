#!/bin/bash

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
#export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libVertexRestorer.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libmyFastJetProcessor.so"

Marlin test_7637_00001.xml
