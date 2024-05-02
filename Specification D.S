#include <avr/io.h>

; RED 3 PE5
; YEL 4 PG5
; GRN 5 PE3
; BLU 6 PH3

; BTN 2 PE4

.global main
main:
      ldi    r16,lo8(RAMEND)
      sts    SPL,r16
      ldi    r16,hi8(RAMEND)
      sts    SPH,r16 

      ldi    r16,0b00100000
      out    _SFR_IO_ADDR(DDRE),r16
      ldi    r16,0b00100000
      out    _SFR_IO_ADDR(DDRG),r16
      ldi    r16,0b00001000
      sts    DDRH,r16

      ldi    r16,0b00000000
      ldi    r17,0b00100000 ; mask for 5
      ldi    r18,0b00001000 ; mask for 3
      ldi    r19,0b00010000 ; mask for 4
      ldi    r20,0b00000100 ; mask for 2

      ldi    r21, 0 ; variable to store LED state

loop:
      in     r22, _SFR_IO_ADDR(PINE) ; read the state of the button
      sbrc   r22, 2                    ; check if button is pressed
      rjmp   btn_pressed               ; if button is pressed, jump to btn_pressed

      lsl    r21                        ; rotate LED state left
      brcc   red                        ; if carry is clear, jump to red
      brcc   yel                        ; if carry is clear, jump to yellow
      brcc   grn                        ; if carry is clear, jump to green
      rjmp   blu                        ; if carry is set, jump to blue

btn_pressed:
      call   delay_100ms                ; debounce delay

btn_pressed_loop:
      in     r22, _SFR_IO_ADDR(PINE)   ; read button state
      sbrc   r22, 2                     ; check if button is still pressed
      rjmp   btn_pressed_loop           ; if button is pressed, loop

      rjmp   loop                       ; button released, resume main loop

red:
      sts    PORTH, r16                 ; turn off other LEDs
      out    _SFR_IO_ADDR(PORTE), r17  ; turn on red LED
      rjmp   delay_and_continue

yel:
      out    _SFR_IO_ADDR(PORTG), r17  ; turn on yellow LED
      out    _SFR_IO_ADDR(PORTE), r16  ; turn off other LEDs
      rjmp   delay_and_continue

grn:
      out    _SFR_IO_ADDR(PORTE), r18  ; turn on green LED
      out    _SFR_IO_ADDR(PORTG), r16  ; turn off other LEDs
      rjmp   delay_and_continue

blu:
      sts    PORTH, r18                 ; turn off other LEDs
      out    _SFR_IO_ADDR(PORTE), r16  ; turn on blue LED
      rjmp   delay_and_continue

delay_and_continue:
      call   delay_200ms
      rjmp   loop

end:
      rjmp   end

; 16MHz clock: 16 clock cycles/us
; 16000 clock cycles/ms
; 4 cycles: call
; ret 4 cycles
; 8 nops remaining
delay_us:
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      ret           

; overhead: 22 clock cycles
; need 198 delay_us + 10 nop
delay_200ms:
      ldi    r18, 198     ; 1 cycle
delay_200ms_loop:
      call   delay_us     ; 4 cycles
      dec    r18          ; 1 cycle
      brne   delay_200ms_loop ; 1/2 cycles if not taken, 2 cycles if taken
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      nop                 ; 1 cycle
      ret                 ; 4 cycles

; overhead: 22 clock cycles
; need 18 delay_us + 10 nop
delay_100ms:
      ldi    r18, 18     ; 1 cycle
delay_100ms_loop:
      call   delay_us    ; 4 cycles
      dec    r18         ; 1 cycle
      brne   delay_100ms_loop ; 1/2 cycles if not taken, 2 cycles if taken
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      nop                ; 1 cycle
      ret                ; 4 cycles
