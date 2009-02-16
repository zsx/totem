#!/bin/sh
./configure --prefix=/c/totem --datadir=/c/totem/share --without-smclient --disable-browser-plugins --disable-nautilus --enable-python --enable-vala --disable-scrollkeeper "$@"
