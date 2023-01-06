disk_load:
  push dx               ; Store dx on stack for future recall of requested sectors

  mov ah, 0x02          ; BIOS read sector function
  mov al, dh            ; Read dh sectors
  mov ch, 0x00          ; Select cylinder 0
  mov dh, 0x00          ; Select head 0
  mov cl, 0x02          ; Start reading from 2nd sector (after boot sector)

  int 0x13              ; BIOS interrupt

  jc disk_error         ; Jump if read error (carry flag set)

  pop dx                ; Restore dx from stack
  cmp dh, al            ; If al (sectors read) != dh (sectors expected)
  jne disk_error        ; Display error message
  ret

disk_error:
  mov bx, DISK_ERROR_MSG
  call print_string
  jmp $

DISK_ERROR_MSG db "Disk read error!", 0