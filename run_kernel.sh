#!/bin/bash
# run kernel in qemu for debug
qemu-system-x86_64 -s -kernel ./vmlinux -initrd ./initramfs.cpio.gz -nographic -append "console=ttyS0 $*"
