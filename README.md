# print_trace.cpp readme

## Purpose of Function
Sometimes a debugger's stack trace is not enough to determine the calling path to your function,  because your function may be called multiple times through different paths. 

This print_trace allows you to print the current function's calling path function names whatever depth you choose. You can limit the depth of the stack so as not to get unhelpful functions beyond what is necessary for your debugging purposes.


### Installation

The easiest way is to to copy the file print_trace.cpp into your code base preferably an include directory or the current function debugging directory. Make sure you have the following libraries available:

```c++
#include <cxxabi.h> // needed for abi::__cxa_demangle
#include <libunwind.h>
#include <memory>
```

### Usage
Include the print_trace.cpp file at the top of your code where your function resides. Then to print the calling functions path, add `print_trace()` as in the example below line (can be anywhere in the function).

```c++

#include "print_trace.cpp"

void your_function(){
    print_trace();
}
```

When your function is called `print_trace()` will print the stack trace path of function names that called your function. The default is 10 but you can change that by passing a stack depth integer number. The functions printed includes the test function name itself.

### How it Works

The ```print_trace()``` function uses two libraries. **libunwind** and **cxxabi**. **libunwind** retrieves the mangled function names starting with the test function, while **cxxabi** is used to demangle the names to print them out in a readable format. In addition **libunwind** provides the program counter location of each function on the stack.

### Testing Demo

Copy the test_trace.cpp and print_trace.cpp into a project folder. Compile and run. (You can use the included files for task/launch settings for VSCode.)

You should see the following output:
```
0x10000304e: (0)  _some_func_C23()
0x100003030: (1)  _some_func_B1(int)

0x100002ffa: (0)  MyClass::myMethod2(char const*)
0x100002fd0: (1)  MyClass::myMethod1(int*)
0x100003087: (2)  main
```
The 1st trace is limited to a depth of 2, while the 2nd trace is no dept limit.


### Libraries:
[<libunwind.h>](https://www.nongnu.org/libunwind/)  
[<cxxabi.h>](https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html)  
