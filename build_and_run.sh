#!/bin/bash
set -xe

make clean
make
bash create_disk_image.sh
qemu-system-x86_64 -m 1G -drive file=ailurus.hdd,format=raw