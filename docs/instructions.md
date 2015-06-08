# Core instructions

[« Back to the index](index.md)

* **Stack & variables control**
    * `0x10`: **pushf f**, pushes an immediate float value on the value stack.
    * `0x11`: **pushs s**, pushes a string on the value stack. The opcode should be
      followed by a string value.
    * `0x12`: **pushv #v** a variable value on the value stack. #v is the number of
      the variable (1 byte).
    * `0x13`: **pushr pid #v** a variable value of another process on the value stack.
      #v is the number of the variable (1 byte).
    * `0x14`: **load a**, pushes the nth element from the frame pointer 0, 1, 2... 
       are local variables and -1, -2 ... are the function parameters.
    * `0x15`: **sto a**, sets the value of the nth element from the frame pointer,
      this will pop the stacks to do it.
    * `0x16`: **dup**, pushes the top of the stack
    * `0x20`: **pop #v** sets a variable with the value on the top of the stack (popped)
    * `0x21`: **popr pid #v** sets a variable of another process with the value on the top of the 
      stack (popped).
    * `0x22`: **smash n**, smashes n values on the top of stack

* **Execution control**
    * `0x30`: **jmp m**, immediate inconditional jump to immediate address.
    * `0x31`: **jmpc m**, pops the values stack, and jumps if the address is different from 0.
    * `0x32`: **jmpn m**, pops the values stack, and jumps if the address is 0.
    * `0x33`: **call m**, jumps to the immediate address, and pushes the current program counter on
      the call stack. The function arguments should have been placed on the values stack.
      Note that special addresses may be reserved to implement native functions.
    * `0x34`: **args n**, this will simply move the framepointer backware by **n** bytes, telling that
      the current method has n arguments.
    * `0x35`: **ret**, returns from the method, the new top of the stack is the current frame pointer,
      the frame pointer and the pc are popped from stacks.
    * `0x36`: **retv**, returns from the method with value, the top of the stack is copied to the
      frame_pointer+1 address in the stack, which becomes the new top of the stack.
    * `0x3a`: **start tid**, starts a thread with the given id
    * `0x3b`: **stop tid**, stops a thread with the given id
    * `0x3c`: **pause tid**, pauses a thread with the given id
    * `0x3d`: **startr pid tid**, starts a thread with the given id, on the remote program pid
    * `0x3e`: **stopr pid tid**, stops a thread with the given id, on the remote program pid
    * `0x3f`: **pauser pid tid**, pauses a thread with the given id, on the remote program pid
    * `0x40`: **stops**, the thread will stop itself
    * `0x41`: **pauses**, the thread will pause itself
    * `0x42`: **run pid**, runs the program pid
    * `0x43`: **freeze pid**, freeze the program pid
    * `0x44`: **kill pid**, kill the program pd
    * `0x45`: **freezes**, freeze the corrent program
    * `0x46`: **kills**, kill the current program

* **unary ops** pops the value that is on the value stack and compute a new
  value and put it on the stack. The next byte ``op`` selects the operation to do.
  * `0x60` **not**, for ! (int/bool operation)
  * `0x61` **testz**, to test if it equals 0
  * `0x62` **testnz**, to test if it is different of 0
  * `0x63` **testgz**, to test if it is > to 0
  * `0x64` **testlz**, to test if it is < to 0
  * `0x65` **testgez**, to test if it is >= to 0
  * `0x66` **testlez**, to test if it is <= to 0
  * `0x67` **inc**, increments the value on the stack
  * `0x68` **dec**, decrements the value on the stack

* **binary ops** pops two values that are on the value stack to
  compute a new value and put it on the stack. The next byte``op`` selects the operation to do.
  * `0x80` **add**, for +
  * `0x81` **sub**, for -
  * `0x82` **mul**, for *
  * `0x83` **div** for /
  * `0x84` **and** for && (int/bool operation)
  * `0x85` **or** for || (int/bool operation)
  * `0x86` **teste** for =
  * `0x87` **testne** for !=
  * `0x88` **testl** for <
  * `0x89` **testle** for <=
  * `0x8a` **testg** for >
  * `0x8b` **testge** for >=

* **events**
    * `0xa0` **emitn id**, emits an event of given id, there is no arguments here
    * `0xa1` **emitv id args**, emits an event of given id, args is the number of arguments
    * `0xa2` **wait id**, waits for an event to occur, this will stall the current context until
      the event is emmited. It can be emmitted natively or by another process. The event args will
      be placed on the stack and should be smashed.
