# bstd - Makefile
#
# Copyright (c) 2023 hexaheximal
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


.PHONY: all

CC=gcc

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=bin/%.o)

EXAMPLE_SRC=$(wildcard src/example/*.c)
EXAMPLE_OBJ=$(EXAMPLE_SRC:src/example/%.c=bin/%.o)

CFLAGS=-Wall -Werror -ggdb -Iinclude
all: bin/libbstd.so

$(OBJ): $(SRC)
	if [ ! -d bin ]; then mkdir bin; fi
	gcc -fpic $(CFLAGS) $(LIBS) -o $@ -c $^

bin/libbstd.so: $(OBJ)
	$(CC) -shared -o bin/libbstd.so $(OBJ)

$(EXAMPLE_OBJ): $(EXAMPLE_SRC)
	gcc -c $^ -Lbin -lbstd $(CFLAGS) $(LIBS) -o $@

bin/example: bin/libbstd.so include/bstd.h $(EXAMPLE_OBJ)
	$(CC) $(EXAMPLE_OBJ) -Lbin -lbstd $(LIBS) -o bin/example

test: bin/example
	LD_LIBRARY_PATH=bin ./bin/example

clean:
	rm bin/*