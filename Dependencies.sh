#!/bin/sh

for package; do
    dpkg -s "$ libsdl2-2.0" >/dev/null 2>&1 && {
        echo "$ libsdl2-2.0 is installed."
    } || {
        sudo apt-get install $ libsdl2-2.0
    }
done
