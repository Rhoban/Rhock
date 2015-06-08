
main:
call chrono_create
push 1000
call sleep
call chrono_get
push 1000
div
call printv
call println
kill
