
```cpp
#include <iostream>

int main()
{
    // Our first fraction
    int num1 {};
    int den1 {};

    // Our second fraction
    int num2 {};
    int den2 {};

    // Used to eat (remove) the slash between the numerator and denominator
    char ignore {};

    std::cout << "Enter a fraction: ";
    std::cin >> num1 >> ignore >> den1;

    std::cout << "Enter a fraction: ";
    std::cin >> num2 >> ignore >> den2;

    std::cout << "The two fractions multiplied: "
        << num1 * num2 << '/' << den1 * den2 << '\n';

    return 0;
}
```
Enter a fraction: 1/2
Enter a fraction: 3/4
The two fractions multiplied: 3/8

>While this program works, it introduces a couple of challenges for us to improve upon. First, each pair of integers is only loosely linked -- outside of comments and the context of how they are used in the code, there’s little to suggest that each numerator and denominator pair are related. Second, following the DRY (don’t repeat yourself) principle, we should create a function to handle the user inputting a fraction (along with some error handling). However, functions can only return a single value, so how would we return the numerator and denominator back to the caller?

Now imagine another case where you’re writing a program that needs to keep a list of employee IDs. How might you do so? You might try something like this:

```cpp
int main()
{
    int id1 { 42 };
    int id2 { 57 };
    int id3 { 162 };
    // and so on
}
```

But what if you had 100 employees? First, you’d need to type in 100 variable names. And what if you needed to print them all? Or pass them to a function? We’d be in for a lot of typing. This simply doesn’t scale.

Clearly fundamental types will only carry us so far.

---
### Compound data types

>Fortunately, C++ supports a second set of data types: **compound data types** (also sometimes called **composite data types**) are types that are defined in terms of other existing data types. Compound data types have additional properties and behaviors that make them useful for solving certain types of problems.

#### C++ supports the following compound types:

- Functions

- C-style Arrays

- Pointer types:

	- Pointer to object
	- Pointer to function

- Pointer to member types:

	- Pointer to data member
	- Pointer to member function

- Reference types:

	- L-value references
	- R-value references

- Enumerated types:

	- Unscoped enumerations
	- Scoped enumerations

- Class types:

	- Structs
	- Classes
	- Unions


>We've been using one compound type regularly which is function which is a compound type:

```cpp
void doSomething(int x, double y)
{
}
```

The type of this function is `void(int, double)`. Note that this type is composed of fundamental types, making it a compound type. Of course, functions also have their own special behaviors as well (e.g. being callable).

>[!Key insight]
>A **class type** is a type that is a struct, class, or union.

---
