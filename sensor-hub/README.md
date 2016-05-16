The sensor hub is a central hardware component which consumes data from one or more
sensor devices and processes that data in some way. In this case, it will forward that data
to the backend for storage and analytics.

The sensor hub here is implemented using a Raspberry Pi and Bluetooth LE for communications
with the sensor device(s). It has a wi-fi dongle configured to send data to a remote backend.

Hardware
--------
- Raspberry Pi + micro USB power adaptor
- 8GB SD card
- WiFi USB adaptor (e.g. Edimax EW-7811UN 150Mbps Wireless Nano USB Adapter)
- Bluetooth LE USB adaptor (e.g. Plugable USB Bluetooth 4.0 LE Micro Adapter)

Raspberry Pi Base Setup
-----------------------
1. [Install Raspbian Jessie on the SD card](https://www.raspberrypi.org/documentation/installation/installing-images/mac.md)
2. Plug in the SD card to the Pi
3. Plug in the WiFi USB dongle
4. Plug in a keyboard via USB
5. Connect Pi to TV via HDMI
6. Boot up the Pi
7. Open terminal
8. Run `sudo apt-get update; sudo apt-get upgrade;`
9. `sudo raspi-config` (via terminal)
  1. Expand filesystem to use full SD card
  2. (Optional) Choose to boot to Console (rather than the X GUI for the OS)
10. [Configure WiFi](http://www.savagehomeautomation.com/projects/raspberry-pi-installing-the-edimax-ew-7811un-usb-wifi-adapte.html)
  - Sample network configuration files in Git:
    - wpa_supplicant.conf (/etc/wpa_supplicant/wpa_supplicant.conf)
    - network-interfaces (/etc/network/interfaces)
  - Once wlan0 is up and connected to the network, you could then set a reserved DHCP IP
11. Install SSH server
  - Should already be installed and running
  - Otherwise do this from raspi-config
12. SSH from a remote machine to the Pi
  - e.g. `ssh pi@192.168.x.x`
  - password: raspberry
13. Unplug the keyboard now that you have SSH access
14. Plug in the Bluetooth LE USB dongle
  - This may reboot your Pi, this is OK just SSH back in once booted
15. (Optional) Configure VNC server

Raspberry Pi Bluetooth Stack
----------------------------
This script will install bluez and bluepy to enable interactaction between the Bluetooth LE controller and remote peripheral BLE devices.

- Copy the bluetooth-setup.sh to the Pi home (~) directory
- Run the setup script
  - `sudo sh bluetooth-setup.sh`

Raspberry Pi Bluetooth Verification
-----------------------------------
Once the Bluetooth stack is installed, and the Arduino is advertising a BLE service, there are a few checks to ensure all is working OK:

- `lsusb`
  - should show connected USB adapter e.g. Broadcom Corp. BCM20702A0 Bluetooth 4.0
- `sudo hcitool lescan`
  - Should show remote BLE device/service with MAC address
- `gatttool -I -b <remote device MAC address>`
  - connect
- `sudo bluetoothctl`
  1. `list` (list local controllers)
  2. `select 5C:F3:70:76:B4:5E` (select controller)
  3. `power on`
  4. `scan on`
  5. `devices` (should show exposed device/service from Arduino)
  6. `paired-devices` (should show paired devices)
  7. `info 98:4F:EE:0D:05:6A` (get detailed info of remote device)
  8. `pair 98:4F:EE:0D:05:6A` (may not need to do this if already paired)
  9. `connect 98:4F:EE:0D:05:6A` (pin 13 led on Arduino should turn on)
  10. You can select and read attributes from here. Type 'help' for details on how to do this.
  11. `disconnect 98:4F:EE:0D:05:6A` (pin 13 led on Arduino should turn off)

Sensor Listener Service
-----------------------
TODO - This is work in progress. At present the data is received from the sensor device, but not decoded or sent to the remote backend.

Troubleshooting
---------------
1. Ensure bluetoothd is running
  - `sudo bluetoothd &`
2. Ensure device is up
  - `hciconfig`
  - `sudo hciconfig hci0 up`

Resources
---------
######Wi-fi Setup
* http://www.savagehomeautomation.com/projects/raspberry-pi-installing-the-edimax-ew-7811un-usb-wifi-adapte.html

######Bluetooth LE Concepts
* https://learn.adafruit.com/downloads/pdf/introduction-to-bluetooth-low-energy.pdf

######Raspberry Pi/Linux Bluetooth LE
* http://www.elinux.org/RPi_Bluetooth_LE
* http://www.instructables.com/id/Bluetooth-Low-Energy-Read-Write-to-Sensor-Network-/
* http://stackoverflow.com/questions/24853597/ble-gatttool-cannot-connect-even-though-device-is-discoverable-with-hcitool-lesc
* https://wiki.archlinux.org/index.php/bluetooth_keyboard
* https://learn.adafruit.com/bluefruit-le-python-library/overview
