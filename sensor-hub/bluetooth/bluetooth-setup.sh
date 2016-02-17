#!/usr/bin/env bash

# Install Python stuff
sudo apt-get install python python-pip
sudo pip install pyserial --upgrade

# Install BlueZ latest version
cd ~
sudo apt-get --purge remove bluez
sudo apt-get install libusb-dev libdbus-1-dev libglib2.0-dev libudev-dev libical-dev libreadline-dev
sudo rm -rf bluez-5.37.tar.*
sudo rm -rf bluez-5.37
wget https://www.kernel.org/pub/linux/bluetooth/bluez-5.37.tar.xz
tar xvf bluez-5.37.tar.xz
cd bluez-5.37
./configure --disable-systemd
make
sudo make install
sudo cp attrib/gatttool /usr/local/bin/
sudo cp ./src/bluetoothd /usr/local/bin/
sudo bluetoothd &
sudo hciconfig hci0 down
sudo hciconfig hci0 up

# Install Python Bluepy library
cd ~
sudo apt-get install build-essential libglib2.0-dev libdbus-1-dev
git clone https://github.com/IanHarvey/bluepy.git
cd bluepy
git checkout 04bcf931b625cbd49634e72bcfe2738149c33013
git reset --hard
cd bluepy
# Upgrade to use bluez 5.37
sed -i 's|^BLUEZ_PATH=.*|BLUEZ_PATH=../../bluez-5.37|g' Makefile
sed -i 's|.*attrib = g_attrib_new.*|attrib = g_attrib_new(iochannel, mtu, false);|g' bluepy-helper.c
make
sudo cp bluepy-helper /usr/local/lib/python2.7/site-packages/
sudo cp btle.py /usr/local/lib/python2.7/site-packages/
sudo cp get_services.py /usr/local/lib/python2.7/site-packages/
