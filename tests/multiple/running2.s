.id 2

# This program with id=2 will be runned by running1.s

.thread
main:
    pushs "Program2 runned"
    call prints
    call println
    kill
