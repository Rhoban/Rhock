# Context & data

[« Back to the index](index.md)

## Execution context

The program have a context containing all variables. It should be an
array of size **variables**. Each variables are numbered from 0 to n.

Each "thread" have its own context. This context should contain:

* A program counter (PC)
* A values stack
* A call/frame pointer stack
* A tick flag (true: playing, false: stop)

## Variables values

Variable values (that are on the values stack) are 32 bits and can be:

* Numeric values: point-fixed values, these are 32 bits values, with 10
  last bits as decimals.
* String values: the string is actually an adress on the sections zone. A 
  string is represented with a byte containing its `length` and `length`
  bytes containing its value. 

OL: il manque peut-être un concept de list/tableau. Je pencherai pour des 
listes non typées à la LISP, avec ca, on pourrait faire un scan, ou alors 
résoudre un labyrinthe avec une pile comme là: https://www.youtube.com/watch?v=QuHL17jx_7g
L'utilisation peut en être simple. On peut aussi facilement décrire une spline.

## Call stack

The call stack is 16 bytes stack representing return addresses.

## Frame pointer stack

The frame pointer stack is a stack containing values of the stack top when calling.

