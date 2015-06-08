.name "thread"

.thread
main:
    # Step1, waiting a little
    pushs "Main: waiting"
    call prints
    call println
    pushf 1000
    call sleep
    # Step2, starting task
    start task
    pushs "Main: starting task"
    call prints
    call println
    pushf 1000
    call sleep
    # Step3, pausing task
    pause task
    pushs "Main: paused task"
    call prints
    call println
    pushf 1000
    call sleep
    # Step4, resuming
    pushs "Main: resuming"
    start task
    call prints
    call println
    pushf 1000
    call sleep
    # Step5, stopping
    stop task
    pushs "Main: stopped"
    call prints
    call println
    pushf 1000
    call sleep
    # Step6, running again
    pushs "Main: starting task again"
    start task
    call prints
    call println
    pushf 1000
    call sleep
    stop task
    stop

.thread
.stopped
task:
    # x = 0
    pushf 0
loop:
    # x = x+1
    load 0
    pushf 1
    add
    sto 0
    # call print("thread working", x)
    pushs "Thread working "
    call prints
    load 0
    call printv
    call println
    # waiting
    pushf 100
    call sleep
    jmp loop
