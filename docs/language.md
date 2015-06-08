# Language

## Metadata

The program name and id can be defined using the special `name()` and `id()`

    name("example");
    id(123);

## Comments

C and C++ style comments are allowed

    // This is a comment
    /* This is a 
       multiline comment
    */

## Variables 

Variables can be local or global, using the keywords `var` or `global`

    global g;
    var x, y;

It can be affected when declared.

    global g=17;
    var x=0, y;

There can be two local variables with the same name, if in another context.
A variable can be affected to a number or a boolean.

    var x = 1.23;
    var y = true;

Strings are actually convenient constant values.

## Structure

Blocks are using parenthesis and brackets.

## if, while and for

The classical if, while and for are allowed

    if (x > 10) {
    }

    while (i != 10) {
    }

    for (var i=0; i<10; i++) {
    }

## Functions

A function is defined using the `function` keyword:

    function double(x) {
        return 2*x;
    }

Calling a method that is not defined is not a problem, because it can be
a native method. Thus, the hello world is simply:

    print("Hello world\n")

### Threads and tasks

All the code will be placed in the main task, excepted if it is in a `task()`
block:

    while (true) {
        print("main\n");
        sleep(1000);
    }

    task (parallel) {
        while (true) {
            print("parallel\n");
            sleep(1000);
        }
    }

Here, the two process will run simultaneously. Threads can be controlled using
`start()`, `stop()` and `pause()`

    print("waiting");
    sleep(1000);
    print("running print_numbers");
    start(print_numbers);
    sleep(1000);
    print("pausing print_numbers");
    pause(print_numbers);
    sleep(1000);
    print("resuming print_numbers");
    start(print_numbers);
    sleep(1000);
    print("restarting print_numbers");
    stop(print_numbers);
    start(print_numbers);
    sleep(1000);
    kill();

    // Prints a new number each 100ms
    task (print_numbers) {
        var i = 1;
        print(i);
        println();
        i++;
        sleep(100);
    }

A task can be initially stopped

    task_stopped (print_hello) {
        print("Hello world\n");
    }

    start(print_hello);

## Events

There is special keywords to handle events. First, `when()`:

    when (buttonPressed()) {
        print("Hello world!\n");
    }

    // *Exactly like*
    
    task (event) {
        while(buttonPressed());
        while(!buttonPressed());
        print("Hello world!\n");
    }

And then `whenever()`:

    whenever (buttonPressed()) {
        print("The button is pressed\n");
        sleep(500);
    }

    // *Exactly lke*

    task (event) {
        while (buttonpressed()) {
            print("The button is pressed\n");
        }
    }

You can also use named events, using on keyword:

    on(myEvent, x)  {
        print(x);
        println();
    }

And emit it:

    emit(myEvent, 123);

We also introduce a convenient `wait()` method:

    print("Press the button\n");
    wait(buttonPressed());
    print("You pressed the button");

    // *Exactly like*

    print("Press the button\n");
    while(!buttonPressed());
    print("You pressed the button");

