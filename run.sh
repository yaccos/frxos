#!/bin/bash
qemu-system-i386 -kernel "$(dirname "${BASH_SOURCE[0]}")/frxos.elf" -serial mon:stdio
