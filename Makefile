CC     = gcc
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
ASAN_LIBS = -static-libasan
CFLAGS := -Wall -Werror --std=gnu99 -g3
LDFLAGS += -lpthread

all: hello hello_struct hello_threads

hello_threads: tiny_queue.o hello_threads.o
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) $(CURL_LIBS) $(ASAN_LIBS)

hello_struct: tiny_queue.o hello_struct.o
	$(CC) -o $@ $(CFLAGS) $^

hello: tiny_queue.o hello.o
	$(CC) -o $@ $(CFLAGS) $^

tiny_queue: tiny_queue.o
	$(CC) -o $@ $(CFLAGS) $^

%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $(ASAN_FLAGS) $<

clean:
	rm tiny_queue.o hello.o
	rm hello
	rm hello_struct
	rm hello_threads