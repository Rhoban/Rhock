.id 1

# This waits 50ms, freezes the program 2 durring 50ms and then run
# it again
# Since the program 2 is sleeping 200ms, the total execution time
# should be near 300ms, and NOT 200ms.
# This test checks that the elapsed time is well freezed and restored.

main:
    push 1
    call sleep
    freeze 2
    push 100
    call sleep
    run 2
    kill
