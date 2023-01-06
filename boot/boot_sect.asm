[org 0x7c00]
KERNEL_OFFSET equ 0x1000

  mov [BOOT_DRIVE], dl

  mov bp, 0x9000                            ; Set stack
  mov sp, bp

  call print_nl

  mov bx, MSG_REAL_MODE                     ; Move 16 bit message into bx
  call print_string                         ; Print message in bx register
  call print_nl

  call load_kernel                          ; Call function to load kernel

  call switch_to_pm                         ; Once kernel loaded, switch to 32 bit

  jmp $                                     ; Hang

%include "boot/print_string.asm"                 ; Includes
%include "boot/disk_load.asm"
%include "boot/gdt.asm"
%include "boot/print_string_pm.asm"
%include "boot/switch_to_pm.asm"
%include "boot/print_hex.asm"

[bits 16]
load_kernel:
  mov bx, MSG_LOAD_KERNEL                   ; Move kernel message into bx
  call print_string                         ; Call 16 bit print string function
  call print_nl

  mov bx, KERNEL_OFFSET                     ; Move address offset of kernel into bx
  mov dh, 35                                ; Read 20 sectors (1 suffices as of now, but as os gets bigger, more sectors are needed)
  mov dl, [BOOT_DRIVE]                      ; Move BOOT_DRIVE into dl
  call disk_load                            ; Call function to read disk
  ret                                       ; Return from function

[bits 32]
; This is where we land after switching and initalizing protected mode
BEGIN_PM:
  mov ebx, MSG_PROT_MODE                    ; Move 32 bit message into ebx register
  call print_string_pm                      ; call function to print message from ebx

  call KERNEL_OFFSET                        ; Jump to the kernel offset address (0x1000)

  jmp $                                     ; Hang

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode.", 0
MSG_PROT_MODE db "Successful switch to 32-bit Protected Mode.", 0
MSG_LOAD_KERNEL db "Loading kernel into memory.....", 0

; Boot sector padding

times 510-($-$$) db 0
dw 0xaa55