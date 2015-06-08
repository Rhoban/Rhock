.id 1
.variable x 0

main:
    push x
    call printv
    call println
    push 1
    pop x
    push x
    call printv 
    call println
    push 100
    call sleep
    push x
    call printv
    call println
    kill
    
