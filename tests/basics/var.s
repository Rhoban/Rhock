.name "Variables"

# There is 2 variables here, let's call them x and y
.variable x 1
.variable y 2

main:
    pushs "x+y="
    call prints

    push x
    push y
    add
    call printv
    call println
    stop
