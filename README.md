# frxos

**frxos** is my little pet project. The goal is to get a very basic, but working, operating system up and running.

## Current and planned features

* [x] Serial input/output
* [x] Easy debugging
  * [ ] Press <kbd>Break</kbd> to show current state (registers, stack, stack trace, disassembly etc.)
* [ ] Memory management
* [ ] Keyboard input
* [ ] Display output
* [ ] Basic shell
* [ ] Hard drive access
* [ ] User-space programs

## Build

To build, ensure that you have an `i686-elf` toolchain installed ([precompiled binaries available here][1]) and `make`.

To build, run `make all`.

To run locally with QEMU, run `run.sh` (requires qemu-system-i386 in `PATH`) or run `qemu-system-i386 -kernel frxos.elf`.

[1]: https://github.com/lordmilko/i686-elf-tools/releases
