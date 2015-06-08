.name "1 to 10"

# Display numbers from 1 to 10
.variable n

main:
    # Load 1 into n
    push 1
    pop n
    # Push 10 into the stack (loop counter)
    pushf 10
loop:
    # Prints n
    push n
    call printv
    call println
    # Increments n by one
    push n
    push 1
    add
    pop n
    # Decrements the loop counter
    pushf 1
    sub
    dup
    pushf 0
    testg
    jmpc loop
    smash 1
    stop
