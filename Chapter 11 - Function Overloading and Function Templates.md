
### Function overloading

>**Function overloading** allows us to create multiple functions with the same name, so long as each identically named function has different parameter types (or the functions can be otherwise differentiated). Each function sharing a name (in the same scope) is called an **overloaded function** (sometimes called an **overload** for short).

To overload our `add()` function, we can simply declare another `add()` function that takes double parameters:

```cpp
double add(double x, double y)
{
    return x + y;
}
```

We now have two versions of `add()` in the same scope:

```cpp
int add(int x, int y) // integer version
{
    return x + y;
}

double add(double x, double y) // floating point version
{
    return x + y;
}

int main()
{
    return 0;
}
```

The above program will compile. Although you might expect these functions to result in a naming conflict, that is not the case here. Because the parameter types of these functions differ, the compiler is able to differentiate these functions, and will treat them as separate functions that just happen to share a name.

>[!Key Insight]
>Functions can be overloaded so long as each overloaded function can be differentiated by the compiler. If an overloaded function can not be differentiated, a compile error will result.

---
### Introduction to overload resolution

>Additionally, when a function call is made to a function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function call. This is called **overload resolution**.

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

double add(double x, double y)
{
    return x + y;
}

int main()
{
    std::cout << add(1, 2); // calls add(int, int)
    std::cout << '\n';
    std::cout << add(1.2, 3.4); // calls add(double, double)

    return 0;
}
```

---
### Making it compile

In order for a program using overloaded functions to compile, two things have to be true:

1. Each overloaded function has to be differentiated from the others. (We will talk about it in a bit).
2. When you call a function that has multiple overloaded versions, the compiler **must be able to choose exactly one matching function** based on the arguments **without ambiguity or confusion**.

>[!warning]
>If an overloaded function is not differentiated, or if a function call to an overloaded function can not be resolved to an overloaded function, then a compile error will result.

>[!Best Practice]
>Use function overloading to make your program simpler.

---
### How overloaded functions are differentiated

|Function property|Used for differentiation|Notes|
|---|---|---|
|Number of parameters|Yes||
|Type of parameters|Yes|Excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses.|
|Return type|No|
For member functions, additional function level qualifiers are also considered:

1. const 
2. Reference

---
### Overloading based on number of parameters

>An overloaded function is differentiated so long as each overloaded function has a different number of parameters

---
### Overloading based on type of parameters

>A function can also be differentiated so long as each overloaded function’s list of parameter types is distinct. For example, all of the following overloads are differentiated:

```cpp
int add(int x, int y); // integer version
double add(double x, double y); // floating point version
double add(int x, double y); // mixed version
double add(double x, int y); // mixed version
```

Because type aliases (or typedefs) are not distinct types, overloaded functions using type aliases are not distinct from overloads using the aliased type. For example, all of the following overloads are not differentiated (and will result in a compile error):

```cpp
typedef int Height; // typedef
using Age = int; // type alias

void print(int value);
void print(Age value); // not differentiated from print(int)
void print(Height value); // not differentiated from print(int)
```

>For parameters passed by value, the const qualifier is also not considered. Therefore, the following functions are not considered to be differentiated:

```cpp
void print(int);
void print(const int); // not differentiated from print(int)
```

---
### The return type of a function is not considered for differentiation

A function’s return type is not considered when differentiating overloaded functions.

Consider the case where you want to write a function that returns a random number, but you need a version that will return an int, and another version that will return a double. You might be tempted to do this:

```cpp
int getRandomValue();
double getRandomValue();
```

Error: error C2556: 'double getRandomValue(void)': overloaded function differs only by return type from 'int getRandomValue(void)'

>This makes sense. If you were the compiler, and you saw this statement:

```cpp
getRandomValue();
```

Which of the two overloaded functions would you call? It’s not clear.

---
### Type signature

>[!Important]
>The following question was asked in an interview as a basic question.
>

>A function’s **type signature** (generally called a **signature**) is defined as the parts of the function header that are used for differentiation of the function. In C++, this includes the function name, number of parameters, parameter type, and function-level qualifiers. It notably does _not_ include the return type.

>[!As an aside]
>When the compiler compiles a function, it performs **name mangling**, which means the compiled name of the function is altered (“mangled”) based on various criteria, such as the number and type of parameters, so that the linker has unique names to work with.
For example, a function with prototype `int fcn()` might compile to mangled name `__fcn_v`, whereas `int fcn(int)` might compile to mangled name `__fcn_i`. So while in the source code, the two overloaded functions share the name `fcn()`, in compiled code, the mangled names are unique (`__fcn_v` vs `__fcn_i`).
There is no standardization on how names should be mangled, so different compilers will produce different mangled names.

---
