
.variable x

# Pushing a variable that does not exists
main:
    pushf 1
    pop x
    pushv 1
    kill
