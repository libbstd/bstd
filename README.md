# bstd

The better standard library for C.

# Why?

C is a very old language, and it has it's flaws.  

Most notably, C used null-terminated strings which were a very dangerous way to implement strings.  

Another great example is the in-band signaling of errors using `NULL`.  

The goal of bstd is to implement a better standard library which solves these problems while keeping backwards-compatibility.  

However, Please note that this project **DOES NOT** attempt to replace the C standard library.  

Instead, it's built on top of the C standard library and adds more modern functionality  