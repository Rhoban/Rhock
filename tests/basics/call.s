

# This methods returns 2*x
f:
args 1
load 0
pushf 2
mul
retv

# This method just returns f(x)
g:
args 1
load 0
call f
retv

# This methods returns g(x)-250
h:
args 1
load 0
call g
pushf 200
sub
retv

# Now let's call h(123), should be 46
main:
push 123
call h
call printv
call println
kill
