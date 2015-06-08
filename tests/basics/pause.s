
# This program has two thread
# The first one will pauses the second for 100ms
# The second one is sleeping 300ms
# The total execution time should be 400ms

main:
    # Sleep a little
    push 1
    call sleep
    # Pauses the task
    pause task
    # Sleep 100ms
    push 100
    call sleep
    # Starting the task again
    start task
    stop

.thread
task:
    # Sleeping 300ms
    push 300
    call sleep
    stop

