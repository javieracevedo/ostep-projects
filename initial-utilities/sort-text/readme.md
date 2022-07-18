
# Introduction

The goal is to write small program that sorts text. It should be invoked in the following ways:

```
./sort-text
./sort-text input.txt
./sort-text input.txt output.txt
```

- **The first invocation**: implies that the program can read the text from the `stdin` and print the sorted text to `stdout`.
- **The second invocation**: implies that the program can read the text from file and print the sorted text to `stdout`.
- **The third invocation**: implies the same as the second invocation, except the output gets printed to a file (the second argument).

The file's text should be sorted line by line. Read one line, sort it by character and then move on to the next line, until EOF. Then print the result to stdout or an output file.

# Details

- **Invalid files**: if you try to open a file and fail, print an error message to stderr.
- **Too many arguments**: if sort-text is executed with more arguments than needed, print an error to stderr.
- **Malloc fails**: always check if malloc failed. If so, print an error to stderr, stating that malloc failed.
- **Sorting**: use any sorting algorithm you want. I think it would be helpful to start with bubble sort first.

# Tips

**Start with a simple sorting algorithm**, regardless of it being slow. If motivated, try to implement more efficient sorting algoritms. Make sure you understand how the given sorting algorithm works before trying to implement it.

**Memcheck**, use valgrind's memcheck along the way, to check for pottentially memory issues.

**Testing**, It is extremly helpful and a good practice to test your code while you write it. It can potentially help you catch bugs early on and it makes refactoring the code easier, in case you want to improve it. It also helps you organize your ideas in terms of how the code should work. It makes you think how let's say a function should be used and what it should return. For testing a small program like this I recommend [Minunit](http://pantras.free.fr/articles/minunit.html), but you can use anything you want ofcourse.

# Potentially Useful Routines and Frameworks

You can use `fopen` to open files and `fwrite` to write to a existing file. When printing errors you can use `fprintf` to print a string with the error trough the desired standard stream (stdout, stdin or stderr).


