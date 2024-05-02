#include <avr/io.h>

; RED 3  PE5
; YEL 4  PG5
; GRN 5  PE3
; BLU 6  PH3

; BTN 2  PE4

; TRG 15 PJ0
; ECH 14 PJ1

.global main
main:
      ldi	r16,lo8(RAMEND)
      sts	SPL,r16
      ldi	r16,hi8(RAMEND)
      sts	SPH,r16

      ldi R25,0b10001000
      ldi R16,0b00101000
      out _SFR_IO_ADDR(DDRE),R16
      ldi R16,0b00100000
      out _SFR_IO_ADDR(DDRG),R16
      ldi R16,0b00001000
      sts DDRH,R16 ; H's address is too high, must use sts instead of out
      ldi R16,0b00000001
      sts DDRJ,R16 ; J's address is too high, must use sts instead of out
      ldi R17,0b00000000
      ldi R22,0b00100000
      ldi R23,0b00001000
      ldi R24,0b00000001
      
      sts PORTJ,R17
      rjmp testing

trigger:      
      call delay_100ms
      sts PORTJ,R16
      call delay_10us
      sts PORTJ,R17

      ldi R19,0

echo_loop:
      lds R18,PINJ
      andi R18,2
      breq echo_loop

      ldi R19,0
      ldi R20,0
      ldi R21,0
measure:
      call delay_us
      inc R19
      brne check_pin
      inc R20
      brne check_pin
      inc R21
      breq led_select
check_pin:
      lds R18,PINJ
      andi R18,2
      brne measure

led_select:
      cpi R20,0
      breq blu_led
      cpi R20,15
      brsh red_led
      cpi R20,30
      brlt yel_led
      
      out _SFR_IO_ADDR(PORTE),R23
      out _SFR_IO_ADDR(PORTG),R17
      sts PORTH,R17
      rjmp trigger

blu_led:
      out _SFR_IO_ADDR(PORTE),R17
      out _SFR_IO_ADDR(PORTG),R17
      sts PORTH,R23
      rjmp trigger

red_led:
      out _SFR_IO_ADDR(PORTE),R22
      out _SFR_IO_ADDR(PORTG),R17
      sts PORTH,R17
      rjmp trigger

yel_led:
      out _SFR_IO_ADDR(PORTE),R17
      out _SFR_IO_ADDR(PORTG),R22
      sts PORTH,R17
      rjmp trigger    

end:
      rjmp end


; 16MHz clock: 16 clock cycles/us
; 16000 clock cycles/ms
; call 4 cycles
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

; overhead: 13 cycles
; 73 x 2 cycles/loop + 13 cycles overhead = 159
; need 1 nop
delay_10us:           ; 4
      push R16        ; 2
      ldi R16,73     ; 1
loop_10us:
      dec R16         ; 1
      brne loop_10us  ; 1
      nop
      
      ret             ; 4

; overhead: 22 clock cycles
; need 998 delay_us + 10 nop
delay_ms:           ; 4
      push R17      ; 2
      push R18      ; 2
      ldi R17, 249  ; 1
      ldi r18, 4    ; 1
loop_ms:
      call delay_us
      dec R17       ; 1
      brne loop_ms  ; 1
      dec R18       ; 1
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
      pop R18       ; 2
      pop R17       ; 2
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
      nop
      nop
      nop
      nop
      nop
      nop

testing:
      out _SFR_IO_ADDR(PORTG),R17
      sts PORTH,R17
      out _SFR_IO_ADDR(PORTE),R22
      call delay_100ms
      out _SFR_IO_ADDR(PORTE),R17
      call delay_100ms
      rjmp testing
