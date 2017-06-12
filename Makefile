CC     = gcc
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
ASAN_LIBS = -static-libasan
CFLAGS := -Wall -Werror --std=gnu99 -g3
LDFLAGS += -lpthread

all: hello hello_struct hello_threads

hello_threads: tiny_queue.o hello_threads.o
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) #$(CURL_LIBS) $(ASAN_LIBS)

hello_struct: tiny_queue.o hello_struct.o
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) #$(CURL_LIBS) $(ASAN_LIBS)

hello: tiny_queue.o hello.o
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) #$(CURL_LIBS) $(ASAN_LIBS)

tiny_queue: tiny_queue.o
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) #$(CURL_LIBS) $(ASAN_LIBS)

%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $(ASAN_FLAGS) $<

clean:
	rm -f tiny_queue.o hello.o hello_struct.o hello_threads.o
	rm -f hello
	rm -f hello_struct
	rm -f hello_threads