

# Waits for the event 1 and print "event"
.thread
waiter:
wait 1
push "event"
call prints
call println
load 0
call printv
call println
load 1
call printv
call println
load 2
call printv
call println
smash 3
stop

# Main sleeps 1s and emit event 1
main:
push 10
call sleep
push 123
push 456
push 789
emit 1 3
stop
