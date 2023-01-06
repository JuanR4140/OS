global _start;
[bits 32]

_start:
  [extern kernel_main] ; Define point for calling kernel
  call kernel_main     ; Call C function, jumping to kernel
  jmp $