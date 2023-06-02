#!/bin/bash

# Install git and pip3
sudo apt-get install git -y
sudo apt-get install python3-pip -y

# Install python3-setuptools using apt-get
sudo apt-get install python3-setuptools -y

# Install pyftdi using pip3
sudo pip3 install pyftdi

# Install gcc-riscv64-unknown-elf using apt-get
sudo apt-get install gcc-riscv64-unknown-elf -y

# Print message "Setup complete"        
echo "***************************"
echo "Setup complete"
echo "***************************"
