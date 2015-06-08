.id 123
.name "Hello world"

.variable x

# This prints Hello world

main:
    push "Hello world"
    call prints
    call println
    kill
