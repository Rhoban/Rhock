.id 1

# This program will freeze the program 2 after 100ms

main:
    pushf 50
    call sleep
    freeze 2
    kill
