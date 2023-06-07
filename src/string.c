/* bstd - src/string.c

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

#include "bstd.h"

// Creates a string

String* String_new(size_t length) {
	size_t byte_length = sizeof(char) * length;
	
	String* str = malloc(byte_length);

	// Set the initial length
	
	str->length = length;
	str->buffer_length = byte_length + sizeof(char); // We need the buffer to have one more character so we can null terminate it for compatibility with C strings
	
	str->data = malloc(str->buffer_length);
	
	// Make sure that the data pointer isn't null

	if (str->data == NULL) {
		free(str);
		return NULL;
	}

	return str;
}

// Creates a new string from a C string
// NOTE: This creates a copy of the original cstr data, you will need to call free() later to remove the original C string from memory

String* String_fromcstr(char* cstr) {
	// Make sure that the C string pointer isn't null
	
	if (cstr == NULL) {
		return NULL;
	}
	
	// Initialize the string
	// yes, we need to divide the length by the size of the char type - strlen() returns the number of bytes, not the character length.

	String* str = String_new(strlen(cstr) / sizeof(char));
	
	// Copy the bytes
	
	size_t i;
	
	for (i = 0; i < str->length; i++) {
		str->data[i] = cstr[i];
	}

	return str;
}

// Resize a string, returns true if it succeeds

bool String_resize(String* str, size_t new_length) {
	// Make sure that the string pointer isn't null
	
	if (str->data == NULL) {
		return false;
	}
	
	str->length = new_length;
	str->buffer_length = (new_length + 1) * sizeof(char);
	str->data = realloc(str->data, str->buffer_length);
	
	// Make sure that the data pointer isn't null
	
	if (str->data == NULL) {
		return false;
	}
	
	return true;
}

// Concatenate a string to the end of another string, returns true if it succeeds

bool String_concat(String* to, String* from) {
	// Make sure that the string pointers aren't null
	
	if (from == NULL) {
		return false;
	}

	if (to == NULL) {
		return false;
	}
	
	// Get the original length
	
	size_t original_length = to->length;
	
	// Resize the target string
	
	String_resize(to, original_length + from->length);
	
	// Copy the data
	
	size_t i;
	
	for (i = 0; i < from->length; i++) {
		to->data[original_length + i] = from->data[i];
	}

	return true;
}

// Prints a string

void print(String* str) {
	// Make sure that the str pointer isn't null
	
	if (str == NULL) {
		return;
	}
	
	size_t i;
	
	for (i = 0; i < str->length; i++) {
		putchar(str->data[i]);
		//printf("%c", str->data[i]);
	}
}

// print(), but with an extra newline

void println(String* str) {
	print(str);
	putchar('\n');
	//printf("\n");
}

// A safe string-specific wrapper for free()

void String_free(String* str) {
	if (str == NULL) {
		return;
	}

	free(str->data);
	free(str);
}
