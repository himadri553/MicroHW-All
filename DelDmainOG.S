#include <avr/io.h>

; RED 3 PE5
; YEL 4 PG5
; GRN 5 PE3
; BLU 6 PH3

; BTN 2 PE4

.global main
main:
      ldi	r16,lo8(RAMEND)
      sts	SPL,r16
      ldi	r16,hi8(RAMEND)
      sts	SPH,r16	
      
      ldi R16,0b00100000
      out _SFR_IO_ADDR(DDRE),R16
      ldi R16,0b00100000
      out _SFR_IO_ADDR(DDRG),R16
      ldi R16,0b00001000
      sts DDRH,R16 ; H's address is too high, must use sts instead of out

      ldi R16,0b00000000
      ldi R17,0b00100000 ; mask for 5
      ldi R18,0b00001000 ; mask for 3
      ldi R20,0b00010000 ; mask for 4

loop:

red:
      sts PORTH,R16
      out _SFR_IO_ADDR(PORTE),R17
red_loop:
      in R19,_SFR_IO_ADDR(PINE)
      and R19,R20
      breq red_loop

      call delay_100ms
      call delay_100ms

yel:
      out _SFR_IO_ADDR(PORTE),R16
      out _SFR_IO_ADDR(PORTG),R17
yel_loop:
      in R19,_SFR_IO_ADDR(PINE)
      and R19,R20
      breq yel_loop

      call delay_100ms
      call delay_100ms

grn:
      out _SFR_IO_ADDR(PORTG),R16
      out _SFR_IO_ADDR(PORTE),R18
grn_loop:
      in R19,_SFR_IO_ADDR(PINE)
      and R19,R20
      breq grn_loop

      call delay_100ms
      call delay_100ms

blu:
      out _SFR_IO_ADDR(PORTE),R16
      sts PORTH,R18
blu_loop:
      in R19,_SFR_IO_ADDR(PINE)
      and R19,R20
      breq blu_loop

      call delay_100ms
      call delay_100ms

      rjmp loop

end:
      rjmp end




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
; need 998 delay_us + 10 nop
delay_ms:           ; 4
      ldi R18, 249  ; 1
      ldi R20, 4    ; 1
loop_ms:
      call delay_us
      dec R18       ; 1
      brne loop_ms  ; 1
      dec R20       ; 1
      brne loop_ms  ; 1
      call delay_us
      call delay_us
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      ret           ; 4

; overhead negligible
delay_100ms:
      push R16
      ldi R16,100
loop_100:
      call delay_ms
      dec R16
      brne loop_100
      pop R16
      ret

; overhead negligible
delay_500ms:
      push R16
      ldi R16,5
loop_500:
      call delay_100ms
      dec R16
      brne loop_500
      pop R16
      ret
