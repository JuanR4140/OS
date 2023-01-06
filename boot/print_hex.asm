print_hex:
  pusha                 ; push all registers to stack

  mov cx, 4             ; Start counter for 4 bytes

char_loop:
  dec cx                ; Decrement counter by 1
  mov ax, dx            ; Copy dx into ax to mask for last 4 digits  
  shr dx, 4             ; Shift dx 4 bits to the left
  and ax, 0xf           ; Mask ax to get last 4 bits

  mov bx, HEX_OUT       ; Set bx to memory address of string (used by print_string)
  add bx, 2             ; Add 2 to bx to skip '0x'
  add bx, cx            ; Add current counter to address

  cmp ax, 0xa           ; Check to see if it's a letter or number
  jl set_letter         ; If number, skip to setting the value

  add byte [bx], 7      ; If letter, add 7
                        ; ASCII letters start after 17 chars after decimal
                        ; If our value is a letter, it's already over 10, so add 7

  jl set_letter         ; set value

set_letter:
  add byte[bx], al       ; Add value of byte to char at bx

  cmp cx, 0              ; Check counter against 0
  je print_hex_done      ; If counter is 0, finish
  jmp char_loop          ; If counter is not 0, loop again

print_hex_done:
  mov bx, HEX_OUT        ; print the string pointed by bx
  call print_string      ; call print string function

string_reset:
  mov bx, HEX_OUT        ; Move HEX_OUT memory address into bx

  mov byte [bx], '0'     ; Hacky way of resetting '0x0000' HEX_OUT string
  add bx, 1
  mov byte [bx], 'x'
  add bx, 1
  mov byte [bx], '0'
  add bx, 1
  mov byte [bx], '0'
  add bx, 1
  mov byte [bx], '0'
  add bx, 1
  mov byte [bx], '0'

  popa                   ; Pop all registers from stack
  ret                    ; Return from function

HEX_OUT: db '0x0000', 0  ; Template string for hex value