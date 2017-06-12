## Tiny Queue

This is a tiny queue written in C. I don't know C, so don't expect this to be good. Do expect it to be tiny.

If you have a suggestion for how to do something better please open up a pull request.

## Contents

Code is in `tiny_queue.c` headers are in `tiny_quue.h`. The generic tiny queue struct is `tiny_queue_t`. See `run.c` for an example of how to use it.

## Build

There are several examples of queue usage. To run them first run `make` and then run the executable directly.

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

The queue is threadsafe. You can use it with threads. Lets say that we need to add a bunch of numbers as fast as possible. Build a consumer pool to do the work and have a producer fill the queue.

```
$ make && ./hello_threads
