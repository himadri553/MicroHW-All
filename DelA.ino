#include <avr/io.h>
.global main
main:
; Define I/O port addresses
BUTTON_PORT equ 0x0001 ; Address of the button input port
LED_PORT    equ 0x0002 ; Address of the LED output port

; Define constants
BUTTON_MASK equ 0x01   ; Mask for the button input
LED_MASK    equ 0x02   ; Mask for the LED output

section .text
global _start

_start:
    ; Initialize ports
    mov bx, BUTTON_PORT
    mov ax, 0xFFFF         ; Set all pins of the button port as inputs
    out bx, ax

    mov bx, LED_PORT
    mov ax, 0x0000         ; Set all pins of the LED port as outputs
    out bx, ax

poll_button:
    ; Read the state of the button
    mov bx, BUTTON_PORT
    in ax, bx
    test ax, BUTTON_MASK   ; Check if the button is pressed
    jnz turn_on_led        ; If the button is pressed, jump to turn_on_led
    jmp turn_off_led       ; Otherwise, jump to turn_off_led

turn_on_led:
    ; Turn on the LED
    mov bx, LED_PORT
    in ax, bx
    or ax, LED_MASK        ; Set the LED pin to high
    out bx, ax
    jmp poll_button        ; Go back to polling the button

turn_off_led:
    ; Turn off the LED
    mov bx, LED_PORT
    in ax, bx
    and ax, not LED_MASK   ; Set the LED pin to low
    out bx, ax
    jmp poll_button        ; Go back to polling the button

