.name "call example"

# This define a function double(x) that returns 2*x
# and call it with x=3

# This demostrates the call convention, using stack
# pushing and smashing after the call

main:
    push 3
    call double
    call printv
    call println
    stop

double:
    args 1
    load 0
    push 2
    mul
    retv
