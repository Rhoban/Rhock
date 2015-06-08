.name "blink"

.native ledOn 30
.native ledOff 31

main:
    call ledOn
    pushf 1000
    call sleep
    call ledOff
    pushf 1000
    call sleep
    jmp main
