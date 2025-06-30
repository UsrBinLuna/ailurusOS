#!/bin/bash

dd if=/dev/zero bs=1M count=0 seek=64 of=ailurus.hdd

PATH=$PATH:/usr/sbin:/sbin sgdisk ailurus.hdd -n 1:2048 -t 1:ef00 -m 1

[[ -d limine ]]; git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1 --single-branch

make -C limine

./limine/limine bios-install ailurus.hdd

mformat -i ailurus.hdd@@1M

mmd -i ailurus.hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine

mcopy -i ailurus.hdd@@1M bin/ailurus ::/boot
mcopy -i ailurus.hdd@@1M limine.conf limine/limine-bios.sys ::/boot/limine
mcopy -i ailurus.hdd@@1M limine/BOOTX64.EFI ::/EFI/BOOT
mcopy -i ailurus.hdd@@1M limine/BOOTIA32.EFI ::/EFI/BOOT