.id 1

# This program will print the value of the variable x of
# the program 2

main:
    pushf 100
    call sleep
    push 2 x
    call printv
    call println
    kill
