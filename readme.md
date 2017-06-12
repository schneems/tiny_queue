## Tiny Queue

This is a tiny queue written in C. I don't know C, so don't expect this to be good. Do expect it to be tiny.

If you have a suggestion for how to do something better please open up a pull request.

## Contents

Code is in `tiny_queue.c` headers are in `tiny_quue.h`. The generic tiny queue struct is `tiny_queue_t`. There are several examples that show usage in increasing complexity

- hello
- hello_struct
- hello_threads

There is a description below of how to build and run the examples, and a more detailed explanation of what each one does.

Here's the interface

- tiny_queue_create() creates an instance of `tiny_queue_t` and returns it
- tiny_queue_push(tiny_queue_t *, void *) pushes a pointer onto the tiny queue, this operation is threadsafe
- tiny_queue_pop(tiny_queue_t *) pops a pointer off of the tiny queue, this will block if the queue is empty.

## Build

There are several examples of queue usage. To run them first run `make` and then run the executable directly. Directions and an explanation of each executable are in sections below.

There is a vagrant file in this repo.

To run install vagrant, then:

```
$ vagrant up
$ vagrant ssh
vagrant@vagrant-ubuntu-trusty-64:~$ cd /vagrant
vagrant@vagrant-ubuntu-trusty-64:/vagrant$ make
```

When you are done you can exit and then run `vagrant suspend`.

If you know how to [write a makefile that works with address sanatizer on mac and linux](https://stackoverflow.com/questions/44501833/makefile-for-linux-and-mac-with-address-sanitizer) please let me know.


### Hello

The queue can accept any data type because it stores a pointer instead of a data type directly. You do have to know the data type you're putting into the queue though.

This example pushes three strings "hello", "there" and "neigbor" into the queue in a single thread then retrieves them in the correct order.

```
$ make && ./hello
Popped: hello
Popped: there
Popped: neighbor
```

### Hello Struct


You can push arbitrary data types such as structs onto the queue. In this example we created a fictious data type called `cities_t` it has an integer `rank` and string `name`.


```
$ make && ./hello_struct
Popped: Austin ranked 1
Popped: Atlanta ranked 2
```

## Hello Threads

The queue is threadsafe. You can use it with threads. Lets say that we need to multiply a bunch of numbers as fast as possible. Build a consumer pool to do the work and have a producer fill the queue.

```
$ make && ./hello_threads
(2 * 4) = 8
(3 * 6) = 18
(4 * 8) = 32
(5 * 10) = 50
(6 * 12) = 72
(7 * 14) = 98
(8 * 16) = 128
(9 * 18) = 162
(1 * 2) = 2
(10 * 20) = 200
```

Notice how the output is out of order, this is because all the work is happening async with threads.

The call to `tiny_queue_pop` will block until there are elements in the queue. Each call to `tiny_queue_push` will wake up one consumer and tell it to do work.

This simple example, the thread only does one calculation, outputs to stdout and then exits. In a real application you would likely do work in a loop until you sent some kind of a signal to tell the worker threads (consumers) to stop. For example "poisioning" the queue is simple and effective.


## License

MIT (modified) see LICENSE for details.
