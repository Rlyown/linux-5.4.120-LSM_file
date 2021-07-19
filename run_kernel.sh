#!/bin/bash


print_help() {
    echo "Usage: run_kernel.sh [-a <append>] -m <method>"
    echo "    -h: Show this message."
    echo "    -a: append cmdline argument to the kernel running in the qemu. This argument should set before -m."
    echo "    -m: Choose method."
    echo "         'debug': Start a qemu virtual machine."
    echo "         'init': Package the initramfs directory to the initramfs.cpio.gz. It used in qemu."
    echo "         'build': Build the linux kernel just with stderr. Additionally, it will run make clean before."
}

if [ $# -eq 0 ]
then
    print_help
fi

while getopts "hm:a:" optname
do
    case "$optname" in
        "h")
            print_help
            ;;
        "a")
            CMDLINE="$OPTARG"
            ;;
        "m")
            if [ "$OPTARG"x = "debug"x ]
            then
                # if the process 'qemu-system-x86_64' is running in the background, kill the process
                pid=`ps -ef | grep 'qemu-system-x86_64' | grep -v 'grep' | awk '{print $2}'`
                if [ ! $pid ]
                then
                    echo "the process 'qemu-system-x86_64' is not run!!!"
                else
                    echo "the process 'qemu-system-x86_64' is running!!!"
                    kill -9 $pid
                    echo "the process 'qemu-system-x86_64' has been killed!!"
                fi
                echo run kernel in qemu for debug
                qemu-system-x86_64 --enable-kvm -s -kernel ./vmlinux -initrd ./initramfs.cpio.gz -nographic -append "console=ttyS0 $CMDLINE"
            elif [ "$OPTARG"x = "init"x ]
            then
                echo package the initramfs
                echo "Copy Device file, permission needed!"
                cd initramfs
                sudo rm -rf dev/ proc/ sys/
                mkdir sys proc dev
                sudo cp -a /dev/{null,console,tty,tty1,tty2,tty3,tty4} dev/
                find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs.cpio.gz
                cd -
            elif [ "$OPTARG"x = 'build'x ]
            then
                echo start build linux kernel
                make clean
                time make -j$(nproc) > /dev/null
            fi
            ;;
        "?")
            print_help
            ;;
    esac
done

