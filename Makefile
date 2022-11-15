CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99
CPPFLAGS = -Isrc/

TEST_LDLIBS = -lcriterion

TEST_OBJS = $(addprefix tests/, test_all.o)
OBJ = $(addprefix src/, my_fnmatch.o)

check: test_all
	./test_all

test_all: $(OBJ) $(TEST_OBJS)
	$(CC) -o $@ $(TEST_LDLIBS) $^

libfnmatch.a: $(OBJ)
	ar csr libfnmatch.a $(OBJ)

library: libfnmatch.a

clean:
	rm -f libfnmatch.a test_all $(TEST_OBJS) $(OBJ)

.PHONY: clean all
