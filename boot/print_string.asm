print_string:
  pusha                ; Push all registers to stack

string_loop:
  mov al, [bx]         ; Set al to value of contents of bx
  cmp al, 0            ; Check for null terminator
  jne print_char       ; If not null, print character at al
                       ; Otherwise, string is finished and function ends

  popa                 ; Pop original register values from stack
  ret

print_char:
  mov ah, 0x0e         ; BIOS tele-type function routine for character printing
  int 0x10             ; call BIOS routine, printing char at al register
  add bx, 1            ; add 1 to bx, shifting to next char of string
  jmp string_loop      ; loop back to string_loop label

print_nl:
  pusha

  mov ah, 0x0e
  mov al, 0x0d
  int 0x10
  mov al, 0x0a
  int 0x10

  popa
  ret