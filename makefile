CC = g++
CFLAGS += -std=c++11
SQLITE = -l sqlite3

proj: frontend.cpp
	$(CC) $(CFLAGS) $(SQLITE) $^ -o $@

clean:
	rm proj
	rm output.txt