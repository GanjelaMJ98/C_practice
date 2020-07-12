#!/bin/bash
echo "Hello World"
echo "Compiling..."
gcc -o my-service main.c
echo "Copy..."
sudo cp my-service.service /lib/systemd/system
sudo cp my-service /usr/bin/
echo "Systemctl reload..."
sudo systemctl daemon-reload
echo "Systemctl enable..."
sudo systemctl enable my-service
echo "Systemctl start..."
sudo systemctl start my-service
echo "Systemctl status..."
sudo systemctl status my-service

#journalctl --unit my-service --follow