# OuroborOS Microkernel Whitepaper

## Introduction

OuroborOS is a microkernel with a simple design philosophy: move as much logic
out of the kernel as possible. In other words, much of the functionality that
a kernel would normally do (even memory management) is implemented as a
userspace program. The purpose of this design is to maximize modularity, by
breaking the kernel down into smaller components, and security, by keeping
drivers separate from each other.

This design is accomplished by splitting the kernel into two parts: the "inner
kernel" and the "outer kernel." The inner kernel is what we traditionally think
of as the kernel: it intercepts interrupts, provides a means of context
switching, and provide a layer of abstraction over the hardware. However, this
is the full extent of the inner kernel's responsibilities. It provides only the
bare minimum needed for the outer kernel to function.

The outer kernel is where all of the logic lives. It is a userspace program (or
perhaps a collection of userspace programs) that decides how the machine's
resources will be allocated (memory, TLB entries, hardware thread contexts,
etc.) The inner kernel only executes policies as directed by the outer kernel.

## Context Switching

The crux of the OuroborOS microkernel is the context switch operation. It is
the bread and butter of OuroborOS. A context switch consists of several
operations:

1. Save the current context into a buffer. This buffer will hold current
register values, the program counter, address space ID, and various other CPU
status data.
2. Load a set of TLB entries into the memory management unit.
3. Load a new context from a buffer.
4. Designate a buffer into which to save the current context upon a CPU
exception.
5. Designate a buffer from which to load TLB entries upon a CPU exception.
6. Designate a buffer from which to load the new context upon a CPU exception.

All exception handling occurs in userspace. Upon any CPU exception (misaligned
read/write, TLB miss, interrupt, etc.) the inner kernel saves the current
userspace context into the designated buffer, loads the designated TLB entries,
and loads the new userspace context from the designated buffer, while also
providing information on the exception that occurred. The exception-handling
userspace context then decides how to handle the last generated exception.

A context buffer always represents a userspace context. If it was allowed to
represent a kernel space context, this would allow arbitrary code execution in
kernel space. For this reason, any CPU exception that occurs while in kernel
space is always grounds for an immediate kernel panic. The inner kernel always
executes with interrupts disabled and expects the outer kernel to not create
the conditions for a non-interrupt exception in the inner kernel.

There are several exceptions to the rule that all exceptions get deferred to
userspace. If the current context is configured to enable kernel system calls,
then the kernel will handle the system call instead of deferring it to
userspace. This exception is crucial to allow the outer kernel to execute the
context switch operation. If this flag is not set, then system calls get
deferred to userspace like all other exceptions. In addition, if there is no
registered exception handler (for example, when already handling a previous
exception) then this will result in a kernel panic.

There are multiple conditions that cause a kernel panic in OuroborOS that would
appear to be normal operation in a traditional kernel. The reason for this is
that the outer kernel is responsible for ensuring that there is no condition
that would cause a kernel panic. For example, if a userspace program triggers a
TLB miss, the outer kernel must ensure that all necessary pages for the
exception handler get loaded before the exception handler is executed.

### Rationale

Allowing the userspace program to load arbitrary TLB entries and interrupt
handlers may sound like a complete nullification of security. Normally, this
would be true, but since there is a flag for enabling/disabling the inner
kernel's system calls in a userspace context, security is preserved. If a
userspace program that is not inside the outer kernel attempts to execute the
context switch system call, the outer kernel can handle it in any way it
desires. It can terminate the program, emulate the system call with different
behavior than the inner kernel, or do something else entirely.

This model creates a great deal of flexibility to implement whatever userspace
ABI is desired. Because system calls can be configured with any desired
behavior, you could emulate a Linux kernel, a BSD kernel, or even a Windows
kernel with full binary compatiblity by simply writing a program that runs in
the outer kernel to execute this behavior. You could even have multiple such
kernels running at the same time, with some programs running in Linux mode and
some running in FreeBSD mode as an example.

This does not necessarily mean that you can emulate a full Linux-compatible
system, since there are some operations in a Linux program that are highly
Linux-specific, such as kernel module loading. This would obviously have no
compatible equivalent in OuroborOS, since Linux kernel modules are heavily tied
to the Linux kernel's internal API. On the other hand, basic features such as
file reading/writing, and even some Linux-specific features such as epoll, are
trivial to implement on top of OuroborOS, with the exact same syscall ABI that
the program would expect if it was running on Linux.
