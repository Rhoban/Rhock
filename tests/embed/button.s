.name "button"

.native ledOn 30
.native ledOff 31
.native button 32

waitButton:
    call button
    not
    jmpc waitButton
waitOn:
    call button
    jmpc waitOn
    ret

main:
    call waitButton
    call ledOn
    call waitButton
    call ledOff
    jmp main
