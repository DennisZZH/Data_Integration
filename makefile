CC = g++
CFLAGS += -std=c++11
SQLITE = -l sqlite3

frontend: frontend.cpp
	$(CC) $(CFLAGS) $(SQLITE) $^ -o $@

midend: frontend.cpp midend.cpp
	$(CC) $(CFLAGS) $(SQLITE) $^ -o $@

backend: frontend.cpp midend.cpp backend.cpp
	$(CC) $(CFLAGS) $(SQLITE) $^ -o $@

clean:
	rm frontend midend backend