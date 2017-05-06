# OuroborOS Microkernel

## Introduction

OuroborOS is an experimental microkernel written in C and assembly language.
The design philosophy of OuroborOS is simple: defer as much functionality and
decision-making to userspace as possible. Anything involving "permissions",
"algorithms", etc. should be moved into userspace.

For the time being, this is only a hobby operating system. It is not intended
to serve some purpose in the open-source community, though if someone finds it
useful, more power to them. Currently, OuroborOS only supports the MIPS CPU
architecture, though it may be ported to other architectures in the future.

One of the goals of OuroborOS is to provide a framework for writing higher-
level operating systems. OuroborOS takes care of the lower-level details of
memory management, interrupts, etc. while providing a framework to build a more
user-friendly OS on top of it. The goal of OuroborOS is that you can write a
compatibility layer for Linux, the various BSDs, or even Windows on top of the
microkernel. This is not "yet another Unix/BSD/Linux clone", though there are
plans to eventually write its own Unix-like OS on top of it, called Ouroborix.

## The Name

The ouroboros is an ancient Greek symbol depicting a snake or dragon eating its
own tail. It is one of the oldest known symbols in mythology, and represents
infinity and the cycle of life. However, in the context of this operating
system, it does not have any particular meaning. It is only a cool-sounding
name. The fact that it ends in "OS" is simply a convenient coincidence.

## Architecture Overview

The OuroborOS microkernel actually consists of two parts: the "inner kernel"
and the "outer kernel". The inner kernel is an exceptionally dumb piece of
software; its only purpose is to provide a way to switch from one address
space to another, to catch interrupts, and to notify the outer kernel of any
exceptions that happen during code execution.

The outer kernel is where all of the decision-making happens. In order to
switch address spaces, the outer kernel issues a "context switch" command to
the inner kernel, detailing what TLB entries to load, what values to put in
the various registers, etc. In order to handle exceptions (interrupts,
segfaults, etc.) it also pre-registers another context switch with the inner
kernel, which is then executed upon any CPU exception. The code that then gets
executed decides how to handle the exception.

The outer kernel is also responsible for managing memory. All of the inner
kernel's memory is statically allocated, and it cannot allocate more than it
starts with. Therefore, the outer kernel must ensure that any data structures
it passes to the inner kernel for later use are not overwritten or lost; when
passing an address to the inner kernel, that is the exact address it will use
to refer to the data structure at all points in the future.

For more technical details, please see the technical whitepaper.

## Licensing

For now, all OuroborOS original code is licensed under GPLv3 or later, but it
may eventually be switched to an MIT/BSD style license. This does not apply to
code that has been incorporated into OuroborOS from other sources; that code
will provide the details for its own license. Please not that ALL code
incorporated into OuroborOS is GPL-compatible.

## Building

OuroborOS uses CMake for its build scripts. Currently, it only supports MIPS
and a GCC compiler, so you will need to build a mips-elf-gcc cross-compiler to
compile OuroborOS. You will also need a CMake toolchain file. A toolchain file
with the minimum requirements has been provided below:

    set(CMAKE_SYSTEM_PROCESSOR mips)
    set(CMAKE_SYSTEM_NAME Generic)

    set(tools "$ENV{HOME}/development/tools")
    set(prefix "${tools}/bin/mips-elf-")
    set(CMAKE_C_COMPILER "${prefix}gcc")
    set(CMAKE_OBJCOPY "${prefix}objcopy" CACHE FILEPATH "The toolchain objcopy command" FORCE)

Note that you must include objcopy, as the build script uses it to produce the
kernel binaries.

Once you have your toolchain file, do the following to build OuroborOS:

    $ mkdir build
    $ cd build
    $ cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN_FILE}
    $ make

Once you've built it, you will find a U-Boot compatible flattened image tree at
build/fit/image.itb. Pass this to U-Boot to boot OuroborOS.

Happy hacking!
