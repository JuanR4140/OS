[bits 16]
; Switch to protected mode
switch_to_pm:
  cli                          ; Disable interrupts until protected mode interrupt vector is setup,
                               ; otherwise, interrupts will behave erratically

  lgdt [gdt_descriptor]        ; Load gdt descriptor that defines protected mode segments (eg code, data)

  mov eax, cr0                 ; To switch to 32-bit protected mode, we set first bit of cr0, a control register
  or eax, 0x1
  mov cr0, eax

  jmp CODE_SEG:init_pm         ; Issue far jump to new segment containing 32-bit code, forcing the CPU to flush
                               ; its cache of pre-fetched and real-mode decoded instructions, that can cause
                               ; erratic behavior.


[bits 32]
; Initialize registers and stack once in PM
init_pm:
  mov ax, DATA_SEG             ; in PM, old segments are meaningless,
  mov ds, ax                   ; so point segment registers to data selector
  mov ss, ax                   ; defined in gdt
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ebp, 0x90000             ; Update stack position so it is right
  mov esp, ebp                 ; at the top of the free space.
  call BEGIN_PM                ; Finally, call some well-known label