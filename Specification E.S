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
      ldi    r16,lo8(RAMEND)
      sts    SPL,r16
      ldi    r16,hi8(RAMEND)
      sts    SPH,r16

      ldi    r25,0b10001000
      ldi    r16,0b00101000
      out    _SFR_IO_ADDR(DDRE),r16
      ldi    r16,0b00100000
      out    _SFR_IO_ADDR(DDRG),r16
      ldi    r16,0b00001000
      sts    DDRH,r16
      ldi    r16,0b00000001
      sts    DDRJ,r16

      ldi    r17,0b00000000
      ldi    r22,0b00100000
      ldi    r23,0b00001000
      ldi    r24,0b00000001
      
      sts    PORTJ,r17
      rjmp   trigger

trigger:      
      call   delay_100ms
      sts    PORTJ,r16
      call   delay_10us
      sts    PORTJ,r17

      ldi    r19,0
      ldi    r20,0
      ldi    r21,0
measure:
      call   delay_us
      inc    r19
      brne   check_pin
      inc    r20
      brne   check_pin
      inc    r21
      breq   led_select
check_pin:
      in     r18,PINJ
      tst    r18
      breq   measure

led_select:
      cpi    r20,0
      breq   blu_led
      cpi    r20,15
      brsh   red_led
      cpi    r20,30
      brlt   yel_led
      
      out    _SFR_IO_ADDR(PORTE),r23
      out    _SFR_IO_ADDR(PORTG),r17
      sts    PORTH,r17
      rjmp   trigger

blu_led:
      out    _SFR_IO_ADDR(PORTE),r17
      out    _SFR_IO_ADDR(PORTG),r17
      sts    PORTH,r23
      rjmp   trigger

red_led:
      out    _SFR_IO_ADDR(PORTE),r22
      out    _SFR_IO_ADDR(PORTG),r17
      sts    PORTH,r17
      rjmp   trigger

yel_led:
      out    _SFR_IO_ADDR(PORTE),r17
      out    _SFR_IO_ADDR(PORTG),r22
      sts    PORTH,r17
      rjmp   trigger    

end:
      rjmp   end


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
delay_10us:
      push   r16
      ldi    r16,73
loop_10us:
      dec    r16
      brne   loop_10us
      nop
      pop    r16
      ret

; overhead: 22 clock cycles
; need 998 delay_us + 10 nop
delay_ms:
      push   r17
      push   r18
      ldi    r17,249
      ldi    r18,4
loop_ms:
      call   delay_us
      dec    r17
      brne   loop_ms
      dec    r18
      brne   loop_ms
      call   delay_us
      call   delay_us
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
      pop    r18
      pop    r17
      ret

; overhead negligible
delay_100ms:
      push   r16
      ldi    r16,100
loop_100:
      call   delay_ms
      dec    r16
      brne   loop_100
      pop    r16
      ret

; overhead negligible
delay_500ms:
      push   r16
      ldi    r16,5
loop_500:
      call   delay_100ms
      dec    r16
      brne   loop_500
      pop    r16
      ret

end:
      rjmp   end

