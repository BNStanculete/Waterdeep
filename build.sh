#!/bin/bash

function iwyu() {
    CC="clang" CXX="clang++" cmake -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE=include-what-you-use -B build -S .
    cmake --build build
}

function build() {
    cmake -B build -S .
    cmake --build build
}

function cppcheck() {
    cppcheck source/
}