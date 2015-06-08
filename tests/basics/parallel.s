.name "Parallel"

# There is two thread here, each is outputing data at
# a different rate.

main:
    pushs "Main"
    call prints
    call println
    push 500
    call sleep 
    jmp main

    .thread
parallel:
    pushs "Parallel"
    call prints
    call println
    push 1100
    call sleep
    jmp parallel
