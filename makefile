CC = g++
CFLAGS += -std=c++11

frontend: frontend.cpp
	$(CC) $(CFLAGS) $^ -o $@

midend: frontend.cpp midend.cpp
	$(CC) $(CFLAGS) $^ -o $@

backend: frontend.cpp midend.cpp backend.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm frontend midend backend