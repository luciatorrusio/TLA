#!/bin/bash

if [ $EUID != 0 ]; then
    sudo "$0" "$@"
    exit $?
fi

sudo apt update
sudo apt-get install python3
sudo apt-get install python3-pip
sudo pip3 install numpy
sudo pip3 install opencv-python
sudo apt-get install python3-matplotlib
sudo pip3 install imutils
make all