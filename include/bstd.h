/* bstd - include/bstd.h

Copyright (c) 2023 hexaheximal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef BSTD_H
#define BSTD_H

//
// Imports
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>

#define null NULL
#define nil NULL

//
// Strings
//

typedef struct {
	size_t length;
	size_t buffer_length;
	char* data;
} String;

// Creates a string

extern String* String_new(size_t length);

// Creates a new string from a C string
// NOTE: This creates a copy of the original cstr data, you will need to call free() later to remove the original C string from memory

extern String* String_fromcstr(char* cstr);

// Resize a string, returns true if it succeeds

extern bool String_resize(String* str, size_t new_length);

// Concatenate a string to the end of another string, returns true if it succeeds

extern bool String_concat(String* to, String* from);

// Prints a string

extern void print(String* str);

// print(), but with an extra newline

extern void println(String* str);

// A safe string-specific wrapper for free()

extern void String_free(String* str);

#endif