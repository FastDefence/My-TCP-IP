#!/bin/bash
sudo ip link set tap0 up
sudo ip addr add 10.0.0.1/24 dev tap0

ping -c 1 10.0.0.2

sudo arp -s 10.0.0.2 aa:bb:cc:dd:ee:ff
ping -c 1 10.0.0.2