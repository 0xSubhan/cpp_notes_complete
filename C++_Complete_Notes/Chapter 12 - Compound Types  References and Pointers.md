
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
### 💡 **Expressions in C++**

An **expression** in C++ is anything that can be evaluated to produce a **value**.

Example:

```cpp
2 + 3   // This is an expression. It produces 5.
```

But expressions can also:

- Produce **side effects** (like modifying a variable) // ++x
    
- Evaluate to an **object** or **function** (we’ll see this when we discuss references)
    

### 🧠 **Two Important Properties of Expressions**

Every expression in C++ has two key properties:

### 1. ✅ **Type**

This is **what kind** of value the expression evaluates to — like `int`, `double`, etc.

Example:

```cpp
auto v1 = 12 / 4;   // int / int → int → v1 is int
auto v2 = 12.0 / 4; // double / int → double → v2 is double
```

C++ uses this information:

- To check if your code is valid
    
- For **type inference** using `auto`
    

If you do:

```cpp
print("foo"); // Error: "foo" is a const char*, but print expects an int
```

The **type mismatch** causes a compile-time error.

### 2. 📦 **Value Category**

This tells us **how** a value behaves — can we assign to it? Can we move from it?

There are **5 value categories**, but let’s start with the basic two:

#### 🔹 Lvalue (locator value)

- Has a name (an identifier) and is **addressable**
    
- Can appear **on the left side** of assignment
    
- **Refers to an object** that exists in memory
    

Examples:

```cpp
int x = 5; x = 6;   // x is an lvalue
```

#### 🔹 Rvalue (read value)

- A **temporary** value, doesn’t have a name
    
- **Can’t** be assigned to
    
- **Exists only during that expression**
    

Examples:

```cpp
x = 5;   // 5 is an rvalue 5 = x;   // ❌ error: 5 is not assignable
```

So:

```cpp
int x{}; x = 5;   // ✅ valid: lvalue = rvalue 5 = x;   // ❌ invalid: rvalue = lvalue (makes no sense)
```

To support **move semantics** (which help optimize performance by "moving" rather than "copying" objects), C++11 added **three more categories**:

- glvalue
- prvalue
- xvalue

### Summary

- **Expressions** produce values, objects, or functions.
    
- They have a **type** and a **value category**.
    
- **Type** tells the compiler what kind of value is involved (e.g., `int`, `double`, etc.).
    
- **Value category** tells how the value behaves (can it be assigned to, moved from, etc.).
    
- You need to understand **lvalue vs rvalue** to write legal and efficient C++ code.

---
### Lvalue and rvalue expressions

#### 🔹 What is an **Lvalue**?

- **Lvalue** = “locator value” or “left value”
    
- An **lvalue expression** evaluates to an **identifiable object** or function — meaning it has a location in memory, so you can take its **address** (`&x`) and **refer to it again**.
    

#### ✅ Example:

```cpp
int x = 5;
int y = x;  // "x" is an lvalue (has an identity, name, and location)
```

- `x` refers to a **named variable** that lives in memory → ✅ it's an **lvalue**.
    

#### ✳️ Subtypes of Lvalues:

##### 1. **Modifiable lvalues**:

- Can be changed.
    

```cpp
int x = 5;   // x is a modifiable lvalue
x = 10;      // ok
```

##### 2. **Non-modifiable lvalues**:

- Cannot be changed (because they are `const` or `constexpr`).
    

```cpp
const double d = 3.14;  // d is a non-modifiable lvalue
d = 2.71;               // ❌ error: cannot modify a const variable
```

Both `x` and `d` are **lvalues**, but `x` is modifiable, `d` is not.

#### 🔸 What is an **Rvalue**?

- **Rvalue** = “right value”
    
- An **rvalue expression** is a value **without an identity**.
    
- It's a **temporary result** that:
    
    - Can’t be assigned to
        
    - Has no name
        
    - Lives only during that expression
        

#### ✅ Examples:


```cpp
int x = 5;              // 5 is an rvalue (a literal)
int z = x + 1;          // x + 1 is an rvalue
int w = return5();      // return5() is an rvalue (returns a temporary value)
int q = static_cast<int>(3.14); // rvalue: result of the cast
```

These expressions produce **values**, but not **named memory locations**. That’s why they’re rvalues.

#### ✅ Key Insight (Very Important!)

| Expression Type | Evaluates to             | Has Identity? | Can Modify?            |
| --------------- | ------------------------ | ------------- | ---------------------- |
| Lvalue          | An identifiable object   | ✅ Yes         | ✅ Maybe (if not const) |
| Rvalue          | Just a value (temporary) | ❌ No          | ❌ No                   |

--> Important Example:

```cpp
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```

>You may be wondering why `return5()`, `x + 1`, and `static_cast<int>(d)` are rvalues: the answer is because these expressions produce temporary values that are not identifiable objects.

>[!Tip]
>Lvalue expressions evaluate to an identifiable object.  
Rvalue expressions evaluate to a value.

---
### Value categories and operators

>Unless otherwise specified, operators expect their operands to be rvalues. For example, binary `operator+` expects its operands to be rvalues:

```cpp
#include <iostream>

int main()
{
    std::cout << 1 + 2; // 1 and 2 are rvalues, operator+ returns an rvalue

    return 0;
}
```

The literals `1` and `2` are both rvalue expressions. `operator+` will happily use these to return the rvalue expression `3`.

Now we can answer the question about why `x = 5` is valid but `5 = x` is not: an assignment operation requires its left operand to be a modifiable lvalue expression. The latter assignment (`5 = x`) fails because the left operand expression `5` is an rvalue, not a modifiable lvalue.

```cpp
int main()
{
    int x{};

    // Assignment requires the left operand to be a modifiable lvalue expression and the right operand to be an rvalue expression
    x = 5; // valid: x is a modifiable lvalue expression and 5 is an rvalue expression
    5 = x; // error: 5 is an rvalue expression and x is a modifiable lvalue expression

    return 0;
}
```

---
### Lvalue-to-rvalue conversion

>assignment operations expect the right operand to be an rvalue expression, you might be wondering why the following works:

```cpp
int main()
{
    int x{ 1 };
    int y{ 2 };

    x = y; // y is not an rvalue, but this is legal

    return 0;
}
```

In cases where an rvalue is expected but an lvalue is provided, the lvalue will undergo an lvalue-to-rvalue conversion so that it can be used in such contexts. This basically means the lvalue is evaluated to produce its value, which is an rvalue.

>[!Important Key insight]
>An lvalue will implicitly convert to an rvalue. This means an lvalue can be used anywhere an rvalue is expected.  
An rvalue, on the other hand, will not implicitly convert to an lvalue.

Now consider the following example:

```cpp
int main()
{
    int x { 2 };

    x = x + 1;

    return 0;
}
```

>In this statement, the variable `x` is being used in two different contexts. On the left side of the assignment operator (where an lvalue expression is required), `x` is an lvalue expression that evaluates to variable `x`. On the right side of the assignment operator, `x` undergoes an lvalue-to-rvalue conversion and is then evaluated so that its (`2`) can be used as the left operand of `operator+`. `operator+` returns the rvalue expression `3`, which is then used as the right operand for the assignment.

---
### How to differentiate lvalues and rvalues

You may still be confused about what kind of expressions qualify as an lvalue vs an rvalue. For example, is the result of `operator++` an lvalue or an rvalue? We’ll cover various methods you can use to determine which is which here.

>[!Tip]
>A rule of thumb to identify lvalue and rvalue expressions:
>
>>- Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression.
>>- Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression.
>

---
### Lvalue references

>In C++, a **reference** is an alias for an existing object. Once a reference has been defined, any operation on the reference is applied to the object being referenced. This means we can use a reference to read or modify the object being referenced.

Modern C++ contains two types of references: lvalue references, and rvalue references.

---
### Lvalue reference types

>An **lvalue reference** acts as an alias for an existing lvalue (such as a variable).

#### 🔹 1. **Regular Types vs Reference Types**

##### ✅ `int`

- This is a **regular type**.
    
- It represents a plain integer — **not** a reference.
    

```cpp
int x = 5;
```

Here, `x` holds a copy of the value `5`.

##### ✅ `int&`

- This is a **reference type**.
    
- It means: “a reference to an `int`”.
    
- More precisely: **an lvalue reference to a modifiable `int`**.
    

```cpp
int x = 5;
int& ref = x; // ref refers to x
```

Now `ref` is another name for `x`. Changing `ref` will change `x`.

##### ✅ `const int&`

- This is an **lvalue reference to a const int**.
    
- That means: it can **refer to an `int`**, but **you can't modify it through the reference**.
    

```cpp
int x = 10;
const int& ref = x; // ref refers to x, but you can't change x through ref
```

>[!Tip]
>A type that specifies a reference (e.g. `int&`) is called a **reference type**. The type that can be referenced (e.g. `int`) is called the **referenced type**.
>
>>int x = 5;
int& ref = x; 
>> //  `ref` is a **reference** to `x`, and its **type** is `int&` → this is the **reference type**.  
>> The **referenced type** is `int`, because that's the type being referred to.

--> What if referenced type was of different type than reference type:

```cpp
double x = 5;
int& ref = x; // ❌ ERROR
```

This **will NOT compile**. Here's why:

🚫 Why it fails

C++ does **not** allow you to bind an `int&` (reference to `int`) to a `double` variable, because:

- `x` is of **type `double`**
    
- `ref` wants to reference an **actual `int` object** — but `x` is not an `int`
    
- Even though the value `5` can be **converted** from `double` to `int`, C++ will not create a **temporary `int` object** just to bind it to a **non-const lvalue reference**
    

So this is an **invalid type mismatch**.

---
### Lvalue reference variables

>One of the things we can do with an lvalue reference type is create an lvalue reference variable. An **lvalue reference variable** is a variable that acts as a reference to an lvalue (usually another variable).

To create an lvalue reference variable, we simply define a variable with an lvalue reference type:

```cpp
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    return 0;
}
```

>From the compiler’s perspective, it doesn’t matter whether the ampersand is “attached” to the type name (`int& ref`) or the variable’s name (`int &ref`), and which you choose is a matter of style. Modern C++ programmers tend to prefer attaching the ampersand to the type, as it makes clearer that the reference is part of the type information, not the identifier.

>[!Best Practice]
>When defining a reference, place the ampersand next to the type (not the reference variable’s name).

>For those of you already familiar with pointers, the ampersand in this context does not mean “address of”, it means “lvalue reference to”.

---
### Modifying values through a non-const lvalue reference

In the above example, we showed that we can use a reference to read the value of the object being referenced. We can also use a non-const reference to modify the value of the object being referenced:

```cpp
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```

This code prints:

55
66
77

In the above example, `ref` is an alias for `x`, so we are able to change the value of `x` through either `x` or `ref`.

---
### 🧠 What is _Reference Initialization_?

**Reference initialization** is the process of assigning a variable or function to a reference at the time the reference is declared.

> Just like `const` variables, **all references must be initialized immediately** — you **can’t** create an empty reference and assign to it later.

#### ❌ Invalid Example

```cpp
int& invalidRef; // ❌ ERROR: Reference must be initialized
```

#### ✅ Valid Reference Initialization

```cpp
int x { 5 };
int& ref { x }; // ✅ OK: ref is now an alias for x
```

Now, anything you do to `ref` will affect `x` because `ref` is **bound to** `x`.

#### 💬 Key Vocabulary

- **Reference binding**: The act of associating a reference with an object or function.
    
- **Referent**: The object/function being referenced.
    

In the example above:

- `ref` is a **reference**.
    
- `x` is the **referent**.
    
- The process of doing `int& ref { x };` is called **reference binding**.
    

#### 🧱 Reference Binding Rules

##### ✔️ Non-const Lvalue References:

```cpp
int x = 5;
int& ref = x; // ✅ okay
```

> ✅ Can **only bind to a modifiable lvalue**

But NOT to these:

```cpp
const int y = 5;
int& invalidRef = y;  // ❌ ERROR: can't bind to const

int& invalidRef2 = 0; // ❌ ERROR: can't bind to rvalue
```

##### Why? 🚫

Because then you could write code like this:

```cpp
const int y = 5;
int& ref = y; // ❌ invalid
ref = 10;     // 😱 would change a const value!
```

That would **break the rules of `const`** — so C++ disallows it.

##### ❓Why can't we bind to rvalues?

```cpp
int& r = 5; // ❌ ERROR: rvalue (temporary) can't be bound to non-const reference
```

Because `5` is a **temporary value**, and you’re not allowed to change a temporary via a reference (it doesn’t make sense).

✅ However, **const references** _can_ bind to rvalues:

```cpp
const int& r = 5; // ✅ allowed
```

This is legal because the compiler ensures the temporary lives long enough and you can't modify it.

##### 🧠 Key Insight Recap

> Non-const lvalue references **must bind to modifiable lvalues.**  
> Why? To avoid allowing mutation of values that are supposed to be constant or temporary.

##### ⚠️ Extra Note:

> **Lvalue references to `void` are disallowed.**

```cpp
void x();
void& ref = x; // ❌ ERROR: reference to void makes no sense
```

Because `void` means "no type / no value" — what would it even point to?

---
### A reference will (usually) only bind to an object matching its referenced type

In most cases, a reference will only bind to an object whose type matches the referenced type, (there are some exceptions to this rule that we’ll discuss when we get into inheritance).

If you try to bind a reference to an object that does not match its referenced type, the compiler will try to implicitly convert the object to the referenced type and then bind the reference to that.

>[!Key insight]
Since the result of a conversion is an rvalue, and a non-const lvalue reference can’t bind to an rvalue, trying to bind a non-const lvalue reference to an object that does not match its referenced type will result in a compilation error.

```cpp
int main()
{
    int x { 5 };
    int& ref { x };            // okay: referenced type (int) matches type of initializer

    double d { 6.0 };
    int& invalidRef { d };     // invalid: conversion of double to int is narrowing conversion, disallowed by list initialization
    double& invalidRef2 { x }; // invalid: non-const lvalue reference can't bind to rvalue (result of converting x to double)

    return 0;
}
```

---
### References can’t be reseated (changed to refer to another object)

Once initialized, a reference in C++ cannot be **reseated**, meaning it cannot be changed to reference another object.

New C++ programmers often try to reseat a reference by using assignment to provide the reference with another variable to reference. This will compile and run -- but not function as expected. Consider the following program:

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { 6 };

    int& ref { x }; // ref is now an alias for x

    ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
    // The above line does NOT change ref into a reference to variable y!

    std::cout << x << '\n'; // user is expecting this to print 5

    return 0;
}
```

Perhaps surprisingly, this prints:

6

When a reference is evaluated in an expression, it resolves to the object it’s referencing. So `ref = y` doesn’t change `ref` to now reference `y`. Rather, because `ref` is an alias for `x`, the expression evaluates as if it was written `x = y` -- and since `y` evaluates to value `6`, `x` is assigned the value `6`.

---
### References and referents have independent lifetimes

With one exception (that we’ll cover next lesson), the lifetime of a reference and the lifetime of its referent are independent. In other words, both of the following are true:

- A reference can be destroyed before the object it is referencing.
- The object being referenced can be destroyed before the reference.

When a reference is destroyed before the referent, the referent is not impacted. The following program demonstrates this:

```cpp
#include <iostream>

int main()
{
    int x { 5 };

    {
        int& ref { x };   // ref is a reference to x
        std::cout << ref << '\n'; // prints value of ref (5)
    } // ref is destroyed here -- x is unaware of this

    std::cout << x << '\n'; // prints value of x (5)

    return 0;
} // x destroyed here
```

The above prints:

5
5

When `ref` dies, variable `x` carries on as normal, blissfully unaware that a reference to it has been destroyed.

---
### Dangling references

When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists. Such a reference is called a **dangling reference**. Accessing a dangling reference leads to undefined behavior.

---
### References aren't objects

Perhaps surprisingly, references are not objects in C++. A reference is not required to exist or occupy storage. If possible, the compiler will optimize references away by replacing all occurrences of a reference with the referent. However, this isn’t always possible, and in such cases, references may require storage.

This also means that the term “reference variable” is a bit of a misnomer, as variables are objects with a name, and references aren’t objects.

Because references aren’t objects, they can’t be used anywhere an object is required (e.g. you can’t have a reference to a reference, since an lvalue reference must reference an identifiable object). In cases where you need a reference that is an object or a reference that can be reseated.

Consider the following variables:

```cpp
int var{};
int& ref1{ var };  // an lvalue reference bound to var
int& ref2{ ref1 }; // an lvalue reference bound to var
```

Because `ref2` (a reference) is initialized with `ref1` (a reference), you might be tempted to conclude that `ref2` is a reference to a reference. It is not. Because `ref1` is a reference to `var`, when used in an expression (such as an initializer), `ref1` evaluates to `var`. So `ref2` is just a normal lvalue reference (as indicated by its type `int&`), bound to `var`.

```cpp
int var = 5;

int& ref1 = var;  // ref1 is alias for var
int& ref2 = ref1; // ref1 evaluates to var → ref2 is also alias for var

ref1 = 10;
std::cout << var << '\n'; // prints 10

ref2 = 15;
std::cout << var << '\n'; // prints 15

```

All three (`var`, `ref1`, `ref2`) refer to the **same int in memory**.

>[!tip]
>In **expressions**, a reference (like `ref1`) **automatically converts to the object it refers to**. compiler does that.

---
>As we know lvalue reference binding to const variable is not allowed.

```cpp
int main()
{
    const int x { 5 }; // x is a non-modifiable (const) lvalue
    int& ref { x }; // error: ref can not bind to non-modifiable lvalue

    return 0;
}
```

But what if we want to have a const variable we want to create a reference to? A normal lvalue reference (to a non-const value) won’t do.

---
### Lvalue reference to const 

>By using the `const` keyword when declaring an lvalue reference, we tell an lvalue reference to treat the object it is referencing as const. Such a reference is called an **lvalue reference to a const value** (sometimes called a **reference to const** or a **const reference**).

Lvalue references to const can bind to non-modifiable lvalues:

```cpp
int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    return 0;
}
```

Because lvalue references to const treat the object they are referencing as const, they can be used to access but not modify the value being referenced:

```cpp
#include <iostream>

int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    return 0;
}
```

---
### Initializing an lvalue reference to const with a modifiable lvalue

Lvalue references to const can also bind to modifiable lvalues. In such a case, the object being referenced is treated as const when accessed through the reference (even though the underlying object is non-const):

```cpp
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we can not modify an object through a const reference

    x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    return 0;
}
```

In the above program, we bind const reference `ref` to modifiable lvalue `x`. We can then use `ref` to access `x`, but because `ref` is const, we can not modify the value of `x` through `ref`. However, we still can modify the value of `x` directly (using the identifier `x`).

>[!Best Practice]
>Favor `lvalue references to const` over `lvalue references to non-const` unless you need to modify the object being referenced.

---
### Initializing an lvalue reference to const with an rvalue

>Perhaps surprisingly, lvalues references to const can also bind to rvalues:

```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // okay: 5 is an rvalue

    std::cout << ref << '\n'; // prints 5

    return 0;
}
```

When this happens, a temporary object is created and initialized with the rvalue, and the reference to const is bound to that temporary object.

---
### nitializing an lvalue reference to const with a value of a different type

Lvalue references to const can even bind to values of a different type, so long as those values can be implicitly converted to the reference type:

```cpp
#include <iostream>

int main()
{
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    return 0;
}
```

In case 1, a temporary object of type `double` is created and initialized with int value `5`. Then `const double& r1` is bound to that temporary double object.

In case 2, a temporary object of type `int` is created and initialized with char value `a`. Then `const int& r2` is bound to that temporary int object.

In both cases, the type of the reference and the type of the temporary match.

>[!Tip]
>Also note that when we print `r2` it prints as an int rather than a char. This is because `r2` is a reference to an int object (the temporary int that was created), not to char `c`.

```cpp
char c{ 'A' };                // 'A' has ASCII value 65
const int& r2{ c };          // Binding const int& to a char

```

#### 🔍 What's happening here?

1. You're trying to bind a `const int&` (reference to const `int`) to a `char`.
    
2. But `c` is of type `char`, and you're binding it to a reference of a **different type** (`int`).
    
3. Since this is **not allowed directly** (you can't bind a non-const reference to a different type), the compiler does something smart:
    

#### ⚙️ Compiler's Behavior:

- It **creates a temporary `int` object**, say `temp`, initialized with the value of `c` (which is `'A'`, or `65`).
    
- Then it **binds `r2` to this temporary `int` object**.
    
- So `r2` becomes a reference to this temporary `int` (which holds value `65`), not to the original `char c`.
    

#### 🖨️ Why does it print as an `int`?

```cpp
std::cout << r2;  // prints 65
```

- `r2` is a reference to an `int`, not a `char`.
    
- So it prints the `int` value (`65`), not the character `'A'`.

--> Important Must Read!  

>[!Warning]
>We normally assume that a reference is identical to the object it is bound to -- but this assumption is broken when a reference is bound to a temporary copy of the object or a temporary resulting from the conversion of the object instead. Any modifications subsequently made to the original object will not be seen by the reference (as it is referencing a different object), and vice-versa.
>Here’s a silly example showing this:
```cpp
#include <iostream>

int main()
{
    short bombs { 1 };         // I can has bomb! (note: type is short)

    const int& you { bombs };  // You can has bomb too (note: type is int&)
    --bombs;                   // Bomb all gone

    if (you)                   // You still has?
    {
        std::cout << "Bombs away!  Goodbye, cruel world.\n"; // Para bailar la bomba
    }

    return 0;
}
```
>[!Warning]
>In the above example, `bombs` is a `short` and `you` is a `const int&`. Because `you` can only bind to an `int` object, when `you` is initialized with `bombs`, the compiler will implicitly convert `bombs` to an `int`, which results in the creation of a temporary `int` object (with value `1`). `you` ends up bound to this temporary object rather than `bombs`.
>When `bombs` is decremented, `you` is not affected because it is referencing a different object. So although we expect `if (you)` to evaluate to `false`, it actually evaluates to `true`.

---
### Const references bound to temporary objects extend the lifetime of the temporary object

>Temporary objects are normally destroyed at the end of the expression in which they are created.

Given the statement `const int& ref { 5 };`, consider what would happen instead if the temporary object created to hold rvalue `5` was destroyed at the end of the expression that initializes `ref`. Reference `ref` would be left dangling (referencing an object that had been destroyed), and we’d get undefined behavior when we tried to access `ref`.

>To avoid dangling references in such cases, C++ has a special rule: When a const lvalue reference is _directly_ bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference.

```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // The temporary object holding value 5 has its lifetime extended to match ref

    std::cout << ref << '\n'; // Therefore, we can safely use it here

    return 0;
} // Both ref and the temporary object die here
```

In the above example, when `ref` is initialized with rvalue `5`, a temporary object is created and `ref` is bound to that temporary object. The lifetime of the temporary object matches the lifetime of `ref`. Thus, we can safely print the value of `ref` in the next statement. Then both `ref` and the temporary object go out of scope and are destroyed at the end of the block.

>[!Tip]
>Lvalue references can only bind to modifiable lvalues.
>Lvalue references to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. This makes them a much more flexible type of reference.

---
### Constexpr lvalue references Optional

When applied to a reference, `constexpr` allows the reference to be used in a constant expression. Constexpr references have a particular limitation: they can only be bound to objects with static duration (either globals or static locals). This is because the compiler knows where static objects will be instantiated in memory, so it can treat that address as a compile-time constant.

A constexpr reference cannot bind to a (non-static) local variable. This is because the address of local variables is not known until the function they are defined within is actually called.

```cpp
int g_x { 5 };

int main()
{
    [[maybe_unused]] constexpr int& ref1 { g_x }; // ok, can bind to global

    static int s_x { 6 };
    [[maybe_unused]] constexpr int& ref2 { s_x }; // ok, can bind to static local

    int x { 6 };
    [[maybe_unused]] constexpr int& ref3 { x }; // compile error: can't bind to non-static object

    return 0;
}
```

When defining a constexpr reference to a const variable, we need to apply both `constexpr` (which applies to the reference) and `const` (which applies to the type being referenced).

```cpp
int main()
{
    static const int s_x { 6 }; // a const int
    [[maybe_unused]] constexpr const int& ref2 { s_x }; // needs both constexpr and const

    return 0;
}
```

Given these limitations, constexpr references typically don’t see much use.

---
### Pass By lvalue reference

>[!Tip]
>fundamental types are cheap to copy.
#### Some objects are expensive to copy

>Most of the types provided by the standard library (such as `std::string`) are class types. Class types are usually expensive to copy. Whenever possible, we want to avoid making unnecessary copies of objects that are expensive to copy, especially when we will destroy those copies almost immediately.

```cpp
#include <iostream>
#include <string>

void printValue(std::string y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" }; // x is a std::string

    printValue(x); // x is passed by value (copied) into parameter y (expensive)

    return 0;
}
```
Hello, world!

---
### Pass by reference

>One way to avoid making an expensive copy of an argument when calling a function is to use `pass by reference` instead of `pass by value`. When using **pass by reference**, we declare a function parameter as a reference type (or const reference type) rather than as a normal type. When the function is called, each reference parameter is bound to the appropriate argument. Because the reference acts as an alias for the argument, no copy of the argument is made.

```cpp
#include <iostream>
#include <string>

void printValue(std::string& y) // type changed to std::string&
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" };

    printValue(x); // x is now passed by reference into reference parameter y (inexpensive)

    return 0;
}
```

This program is identical to the prior one, except the type of parameter `y` has been changed from `std::string` to `std::string&` (an lvalue reference). Now, when `printValue(x)` is called, lvalue reference parameter `y` is bound to argument `x`. Binding a reference is always inexpensive, and no copy of `x` needs to be made. Because a reference acts as an alias for the object being referenced, when `printValue()` uses reference `y`, it’s accessing the actual argument `x` (rather than a copy of `x`).

>The following program demonstrates that a value parameter is a separate object from the argument, while a reference parameter is treated as if it were the argument:

```cpp
#include <iostream>

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

int main()
{
    int x { 5 };
    std::cout << "The address of x is: " << &x << '\n';
    printAddresses(x, x);

    return 0;
}
```
The address of x is: 0x7ffd16574de0
The address of the value parameter is: 0x7ffd16574de4
The address of the reference parameter is: 0x7ffd16574de0

---
### Pass by reference allows us to change the value of an argument

>When an object is passed by value, the function parameter receives a copy of the argument. This means that any changes to the value of the parameter are made to the copy of the argument, not the argument itself.

However, since a reference acts identically to the object being referenced, when using pass by reference, any changes made to the reference parameter _will_ affect the argument:

```cpp
#include <iostream>

void addOne(int& y) // y is bound to the actual object x
{
    ++y; // this modifies the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has been modified

    return 0;
}
```

>[!Note]
>Passing values by reference to non-const allows us to write functions that modify the value of arguments passed in.

>[!Example]
>The ability for functions to modify the value of arguments passed in can be useful. Imagine you’ve written a function that determines whether a monster has successfully attacked the player. If so, the monster should do some amount of damage to the player’s health. If you pass your player object by reference, the function can directly modify the health of the actual player object that was passed in. If you pass the player object by value, you could only modify the health of a copy of the player object, which isn’t as useful.

---
### Pass by reference can only accept modifiable lvalue arguments

Because a reference to a non-const value can only bind to a modifiable lvalue (essentially a non-const variable), this means that pass by reference only works with arguments that are modifiable lvalues. In practical terms, this significantly limits the usefulness of pass by reference to non-const, as it means we can not pass const variables or literals. For example:

```cpp
#include <iostream>

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue

    const int z { 5 };
    printValue(z); // error: z is a non-modifiable lvalue

    printValue(5); // error: 5 is an rvalue

    return 0;
}
```

Fortunately, there’s an easy way around this, which we will discuss next lesson. We’ll also take a look at when to pass by value vs. pass by reference.

---
### Pass by cosnt lvalue reference

>Unlike a reference to non-const (which can only bind to modifiable lvalues), a reference to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. Therefore, if we make a reference parameter const, then it will be able to bind to any type of argument:

```cpp
#include <iostream>

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printRef(x);   // ok: x is a modifiable lvalue, y binds to x

    const int z { 5 };
    printRef(z);   // ok: z is a non-modifiable lvalue, y binds to z

    printRef(5);   // ok: 5 is rvalue literal, y binds to temporary int object

    return 0;
}
```


>Passing by const reference offers the same primary benefit as pass by non-const reference (avoiding making a copy of the argument), while also guaranteeing that the function can _not_ change the value being referenced.

For example, the following is disallowed, because `ref` is const:

```cpp
void addOne(const int& ref)
{
    ++ref; // not allowed: ref is const
}
```

In most cases, we don’t want our functions modifying the value of arguments.

>[!Best Practice]
>Favor passing by const reference over passing by non-const reference unless you have a specific reason to do otherwise (e.g. the function needs to change the value of an argument).

Now we can understand the motivation for allowing const lvalue references to bind to rvalues: without that capability, there would be no way to pass literals (or other rvalues) to functions that used pass by reference!

---
### Passing arguments of a different type to a const lvalue reference parameter

>we noted that a const lvalue reference can bind to a value of a different type, as long as that value is convertible to the type of the reference. The conversion creates a temporary object that the reference parameter can then bind to.

```cpp
#include <iostream>

void printVal(double d)
{
    std::cout << d << '\n';
}

void printRef(const double& d)
{
    std::cout << d << '\n';
}

int main()
{
    printVal(5); // 5 converted to temporary double, copied to parameter d
    printRef(5); // 5 converted to temporary double, bound to parameter d

    return 0;
}
```

With pass-by-value, we expect a copy to be made, so if a conversion occurs first (resulting in an additional copy) it’s rarely an issue (and the compiler will likely optimize one of the two copies away).

However, we often use pass by reference when we _don’t_ want a copy to be made. If a conversion occurs first, this will typically result in a (possibly expensive) copy being made, which can be suboptimal.

>[!Warning]
>With pass by reference, ensure the type of the argument matches the type of the reference, or it will result in an unexpected (and possibly expensive) conversion.

---
### When to use pass by value vs pass by reference

--> Thumb of rule:

>[!Best Practice]
>- As a rule of thumb, pass fundamental types by value and class types by const reference.
>- If you aren’t sure what to do, pass by const reference, as you’re less likely to encounter unexpected behavior.

[Here’s a partial list of other interesting cases!](https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/#:~:text=Tip,Object%20slicing)

---
### 1. **What happens when you pass by value vs pass by reference**

When a function is called, the way parameters are passed affects both:

- **The cost of setting up the parameter** (copying vs binding)
    
- **The cost of accessing the parameter** inside the function
    

Let’s analyze both.

#### **Pass by Value**

When you pass by value:

```cpp
void func(MyClass obj) { /* ... */ }
```

the compiler **makes a copy** of the argument before entering the function.

**Cost:**

1. **Copy construction cost** — depends on:
    
    - **Object size** — copying a big object = more memory moves.
        
    - **Setup costs** — some classes do extra work when constructed (allocate memory, open files, initialize buffers).
        
2. **Access inside the function** — the copy is _yours_ inside the function.
    
    - Can often be stored in a CPU register (fast).
        
    - No need to check where it points — just access it directly.
        

#### **Pass by Reference**

When you pass by reference:

```cpp
void func(MyClass& obj) { /* ... */ }
```

the compiler **does not copy the object** — instead, it creates a **reference** (like an alias) to the original.

**Cost:**

1. **Binding cost** — minimal; just store the address of the object.
    
    - Roughly the cost of copying a pointer (very fast).
        
2. **Access inside the function** — every time you use the reference:
    
    - You first need to read the reference (pointer) to find the actual object.
        
    - Then you access the object itself.
        
    - This means **an extra memory access step** compared to value.
        

#### 2. **Performance trade-offs**

##### **Step 1: Cost of Initialization**

- **Value** — expensive if copying is heavy (large object or costly setup).
    
- **Reference** — always cheap to bind (like copying a pointer).
    

##### **Step 2: Cost of Access**

- **Value** — direct access (1 memory/register read).
    
- **Reference** — indirect access (read pointer → read object).
    
- If the object is **small enough** to fit into registers, pass-by-value can be _faster_.
    

##### **Step 3: Compiler Optimizations**

The compiler sometimes optimizes better with **pass-by-value** because:

- No **aliasing** — the copy is independent from the original, so compiler knows no outside code can modify it.
    
- With **pass-by-reference**, compiler must be careful because:
    
    - The reference might point to something else also being modified elsewhere.
        
    - That means fewer optimizations.

#### 3. **Why not “always pass by reference”**

- For small cheap-to-copy types, **value can be faster**:
    
    - No extra pointer indirection.
        
    - Better compiler optimizations.
        
- For large expensive-to-copy types, **reference is faster**:
    
    - Avoids unnecessary copy.

#### **Example Performance Scenario**

Let’s say we have a small struct:

```cpp
struct Small { int x; int y; }; // 8 bytes
```

Call:

```cpp
void process(Small s); // pass-by-value
void process_ref(const Small& s); // pass-by-reference
```

- Pass-by-value:
    
    - Copy 8 bytes into a register → done.
        
    - Every use = direct register access.
        
- Pass-by-reference:
    
    - Store pointer (8 bytes).
        
    - Every use = dereference pointer → access object in RAM.
        

In this case, **pass-by-value wins**.

>[!Important]
>when a reference parameter is used, there is usually an extra step. The running program must first directly access the storage location (CPU register or RAM) allocated to the reference, in order to determine which object is being referenced. Only then can it access the storage location of the referenced object (in RAM).
>Therefore, each use of a value parameter is a single CPU register or RAM access, whereas each use of a reference parameter is a single CPU register or RAM access plus a second RAM access.

--> Under the hood:

#### pass-by-value:

```cpp
void func(int x) {
    int y = x + 1;
}
```

When `func` runs:

- `x` is either:
    
    - In a **CPU register** (very fast), or
        
    - In your stack frame in **RAM**.
        
- When you use `x`, you **directly read** its value from that register or RAM slot.  
    **→ 1 access**.

#### pass-by-reference:

```cpp
void func(const int& x) {
    int y = x + 1;
}
```

When `func` runs:

- `x` is not an `int`, it’s a hidden pointer to the caller’s `int`.
    
- When you use `x`:
    
    1. First, **read the pointer** (CPU register or RAM) to find out _where_ the real object lives.
        
    2. Then, **read the real object** from that memory address (almost always in RAM).
        

**→ 2 accesses**:

1. Access reference storage to get the address.
    
2. Access that address to get the actual value.

---
###  function parameters, prefer `std::string_view` over `const std::string&` in most cases [](https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/#stringparameter)

>One question that comes up often in modern C++: when writing a function that has a string parameter, should the type of the parameter be `const std::string&` or `std::string_view`?

In most cases, `std::string_view` is the better choice, as it can handle a wider range of argument types efficiently. A `std::string_view` parameter also allows the caller to pass in a substring without having to copy that substring into its own string first. (since it just changes pointer & length)

There are a few cases where using a `const std::string&` parameter may be more appropriate:

- If you’re using C++14 or older, `std::string_view` isn’t available.
- If your function needs to call some other function that takes a C-style string or `std::string` parameter, then `const std::string&` may be a better choice, as `std::string_view` is not guaranteed to be null-terminated (something that C-style string functions expect) and does not efficiently convert back to a `std::string`.

- A `std::string_view` is just:
        
```cpp
    pointer-to-char + length
```
    
- It **does not** store a null terminator (`'\0'`), because it doesn’t own the data.
    
- Many **C-style functions** (like `strlen`, `printf("%s")`, `strcmp`) expect a **null-terminated string** — they’ll keep reading until they find `'\0'`.  
    If the data is not null-terminated, those functions will read garbage or crash.


>[!Best Practice]
>Prefer passing strings using `std::string_view` (by value) instead of `const std::string&`, unless your function calls other functions that require C-style strings or `std::string` parameters.

---
### Why `std::string_view` parameters are more efficient than `const std::string&` Advanced

In C++, a string argument will typically be a `std::string`, a `std::string_view`, or a C-style string/string literal.

As reminders:

- If the type of an argument does not match the type of the corresponding parameter, the compiler will try to implicitly convert the argument to match the type of the parameter.
- Converting a value creates a temporary object of the converted type.
- Creating (or copying) a `std::string_view` is inexpensive, as `std::string_view` does not make a copy of the string it is viewing.
- Creating (or copying) a `std::string` can be expensive, as each `std::string` object makes a copy of the string.

Here’s a table showing what happens when we try to pass each type:

|Argument Type|std::string_view parameter|const std::string& parameter|
|---|---|---|
|std::string|Inexpensive conversion|Inexpensive reference binding|
|std::string_view|Inexpensive copy|Expensive explicit conversion to `std::string`|
|C-style string / literal|Inexpensive conversion|Expensive conversion|

With a `std::string_view` value parameter:

- If we pass in a `std::string` argument, the compiler will convert the `std::string` to a `std::string_view`, which is inexpensive, so this is fine.
- If we pass in a `std::string_view` argument, the compiler will copy the argument into the parameter, which is inexpensive, so this is fine.
- If we pass in a C-style string or string literal, the compiler will convert these to a `std::string_view`, which is inexpensive, so this is fine.

As you can see, `std::string_view` handles all three cases inexpensively.

With a `const std::string&` reference parameter:

- If we pass in a `std::string` argument, the parameter will reference bind to the argument, which is inexpensive, so this is fine.
- If we pass in a `std::string_view` argument, the compiler will refuse to do an implicit conversion, and produce a compilation error. We can use `static_cast` to do an explicit conversion (to `std::string`), but this conversion is expensive (since `std::string` will make a copy of the string being viewed). Once the conversion is done, the parameter will reference bind to the result, which is inexpensive. But we’ve made an expensive copy to do the conversion, so this isn’t great.
- If we pass in a C-style string or string literal, the compiler will implicitly convert this to a `std::string`, which is expensive. So this isn’t great either.

Thus, a `const std::string&` parameter only handles `std::string` arguments inexpensively.

Additionally, we need to consider the cost of accessing the parameter inside the function. Because a `std::string_view` parameter is a normal object, the string being viewed can be accessed directly. Accessing a `std::string&` parameter requires an additional step to get to the referenced object before the string can be accessed.

Finally, if we want to pass in a substring of an existing string (of any type), it is comparatively cheap to create a `std::string_view` substring, which can then be cheaply passed to a `std::string_view` parameter. In comparison, passing a substring to a `const std::string&` is more expensive, as the substring must at some point be copied into the `std::string` that the reference parameter binds to.

---
### Setup before pointers:

>Consider a normal variable, like this one:

```cpp
char x {}; // chars use 1 byte of memory
```

Simplifying a bit, when the code generated for this definition is executed, a piece of memory from RAM will be assigned to this object. For the sake of example, let’s say that the variable `x` is assigned memory address `140`. Whenever we use variable `x` in an expression or statement, the program will go to memory address `140` to access the value stored there.

The nice thing about variables is that we don’t need to worry about what specific memory addresses are assigned, or how many bytes are required to store the object’s value. We just refer to the variable by its given identifier, and the compiler translates this name into the appropriately assigned memory address. The compiler takes care of all the addressing.

>This is also true with references:

```cpp
int main()
{
    char x {}; // assume this is assigned memory address 140
    char& ref { x }; // ref is an lvalue reference to x (when used with a type, & means lvalue reference)

    return 0;
}
```

Because `ref` acts as an alias for `x`, whenever we use `ref`, the program will go to memory address `140` to access the value. Again the compiler takes care of the addressing, so that we don’t have to think about it.

#### The address-of operator (&)

>Although the memory addresses used by variables aren’t exposed to us by default, we do have access to this information. The **address-of operator** (&) returns the memory address of its operand. This is pretty straightforward:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    return 0;
}
```
5
0027FEA0 (Gives address in hexadecimal)

>[!tip]
>The & symbol tends to cause confusion because it has different meanings depending on context:
>>- When following a type name, & denotes an lvalue reference: `int& ref`.
>>- When used in a unary context in an expression, & is the address-of operator: `std::cout << &x`.
>>- When used in a binary context in an expression, & is the Bitwise AND operator: `std::cout << x & y`.

#### The dereference operator (*)

Getting the address of a variable isn’t very useful by itself.

The most useful thing we can do with an address is access the value stored at that address. The **dereference operator** (*) (also occasionally called the **indirection operator**) returns the value at a given memory address as an lvalue:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)

    return 0;
}
```

On the author’s machine, the above program printed:

5
0027FEA0
5

This program is pretty simple. First we declare a variable `x` and print its value. Then we print the address of variable `x`. Finally, we use the dereference operator to get the value at the memory address of variable `x` (which is just the value of `x`), which we print to the console.

>[!Key Insight]
>Given a memory address, we can use the dereference operator (*) to get the value at that address (as an lvalue).
>The address-of operator (&) and dereference operator (*) work as opposites: address-of gets the address of an object, and dereference gets the object at an address.

--> You can distinguish multipication operator and dereference operator by the context of unary or binary.

---
### Pointers

>A **pointer** is an object that holds a _memory address_ (typically of another variable) as its value. This allows us to store the address of some other object to use later.

>[!Key Insight]
>In modern C++, the pointers we are talking about here are sometimes called "Raw pointers" or "Dumb pointers" to help differentiate them from "smart pointers".

A type that specifies a pointer (e.g. `int*`) is called a **pointer type**. Much like reference types are declared using an ampersand (&) character, pointer types are declared using an asterisk (*):

```cpp
int;  // a normal int
int&; // an lvalue reference to an int value

int*; // a pointer to an int value (holds the address of an integer value)
```

To create a pointer variable, we simply define a variable with a pointer type:

```cpp
int main()
{
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)

    int* ptr;       // a pointer to an integer

    return 0;
}
```

Note that this asterisk is part of the declaration syntax for pointers, not a use of the dereference operator.

>[!Best Practice]
>When declaring a pointer type, place the asterisk next to the type name.

>[!Warning]
>Although you generally should not declare multiple variables on a single line, if you do, the asterisk has to be included with each variable.
>Although this is sometimes used as an argument to not place the asterisk with the type name (instead placing it next to the variable name), it’s a better argument for avoiding defining multiple variables in the same statement.
```cpp
int* ptr1, ptr2;   // incorrect: ptr1 is a pointer to an int, but ptr2 is just a plain int!
int* ptr3, * ptr4; // correct: ptr3 and ptr4 are both pointers to an int
```

---
### Pointer initialization

Like normal variables, pointers are _not_ initialized by default. A pointer that has not been initialized is sometimes called a **wild pointer**. Wild pointers contain a garbage address, and dereferencing a wild pointer will result in undefined behavior. Because of this, you should always initialize your pointers to a known value.

>[!Best practice]
>Always initialize your pointers.

```cpp
int main()
{
    int x{ 5 };

    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x

    return 0;
}
```

>Since pointers hold addresses, when we initialize or assign a value to a pointer, that value has to be an address. Typically, pointers are used to hold the address of another variable (which we can get using the address-of operator (&)).

Once we have a pointer holding the address of another object, we can then use the dereference operator (*) to access the value at that address. For example:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x

    int* ptr{ &x }; // ptr holds the address of x
    std::cout << *ptr << '\n'; // use dereference operator to print the value at the address that ptr is holding (which is x's address)

    return 0;
}
```
5
5


![](https://www.learncpp.com/images/CppTutorial/Section6/6-Pointer.png)

>This is where pointers get their name from -- `ptr` is holding the address of `x`, so we say that `ptr` is “pointing to” `x`.

>[!Note]
>A note on pointer nomenclature: “X pointer” (where X is some type) is a commonly used shorthand for “pointer to an X”. So when we say, “an integer pointer”, we really mean “a pointer to an integer”. This understanding will be valuable when we talk about const pointers.

>Much like the type of a reference has to match the type of object being referred to, the type of the pointer has to match the type of the object being pointed to:

```cpp
int main()
{
    int i{ 5 };
    double d{ 7.0 };

    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object

    return 0;
}
```

With one exception that we’ll discuss next lesson, initializing a pointer with a literal value is disallowed:

```cpp
int* ptr{ 5 }; // not okay
int* ptr{ 0x0012FF7C }; // not okay, 0x0012FF7C is treated as an integer literal
```

---
### Pointers and assignment

We can use assignment with pointers in two different ways:

1. To change what the pointer is pointing at (by assigning the pointer a new address)
2. To change the value being pointed at (by assigning the dereferenced pointer a new value)

First, let’s look at a case where a pointer is changed to point at a different object:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr initialized to point at x

    std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

    int y{ 6 };
    ptr = &y; // // change ptr to point at y

    std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)

    return 0;
}
```

The above prints:

5
6

In the above example, we define pointer `ptr`, initialize it with the address of `x`, and dereference the pointer to print the value being pointed to (`5`). We then use the assignment operator to change the address that `ptr` is holding to the address of `y`. We then dereference the pointer again to print the value being pointed to (which is now `6`).

Now let’s look at how we can also use a pointer to change the value being pointed at:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // initialize ptr with address of variable x

    std::cout << x << '\n';    // print x's value
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

    std::cout << x << '\n';
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    return 0;
}
```

This program prints:

5
5
6
6

In this example, we define pointer `ptr`, initialize it with the address of `x`, and then print the value of both `x` and `*ptr` (`5`). Because `*ptr` returns an lvalue, we can use this on the left hand side of an assignment statement, which we do to change the value being pointed at by `ptr` to `6`. We then print the value of both `x` and `*ptr` again to show that the value has been updated as expected.

>[!Key Insight]
>When we use a pointer without a dereference (`ptr`), we are accessing the address held by the pointer. Modifying this (`ptr = &y`) changes what the pointer is pointing at.
When we dereference a pointer (`*ptr`), we are accessing the object being pointed at. Modifying this (`*ptr = 6;`) changes the value of the object being pointed at.

---
### Pointers behave much like lvalue references

Pointers and lvalue references behave similarly. Consider the following program:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int& ref { x };  // get a reference to x
    int* ptr { &x }; // get a pointer to x

    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (5)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

    ref = 6; // use the reference to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (6)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

    *ptr = 7; // use the pointer to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (7)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

    return 0;
}
```

This program prints:

555
666
777

In the above program, we create a normal variable `x` with value `5`, and then create an lvalue reference and a pointer to `x`. Next, we use the lvalue reference to change the value from `5` to `6`, and show that we can access that updated value via all three methods. Finally, we use the dereferenced pointer to change the value from `6` to `7`, and again show that we can access the updated value via all three methods.

Thus, pointers and references both provide a way to indirectly access another object. The primary difference is that with pointers, we need to explicitly get the address to point at, and we have to explicitly dereference the pointer to get the value. With references, the address-of and dereference happens implicitly.

There are some other differences between pointers and references worth mentioning:

- References must be initialized, pointers are not required to be initialized (but should be).
- References are not objects, pointers are.
- References can not be reseated (changed to reference something else), pointers can change what they are pointing at.
- References must always be bound to an object, pointers can point to nothing (we’ll see an example of this in the next lesson).
- References are “safe” (outside of dangling references), pointers are inherently dangerous (we’ll also discuss this in the next lesson).
---
### The address-of operator returns a pointer

It’s worth noting that the address-of operator (&) doesn’t return the address of its operand as a literal (as C++ doesn’t support address literals). Instead, it returns a pointer to the operand (whose value is the address of the operand). In other words, given variable `int x`, `&x` returns an `int*` holding the address of `x`.

We can see this in the following example:

```cpp
#include <iostream>
#include <typeinfo>

int main()
{
	int x{ 4 };
	std::cout << typeid(x).name() << '\n';  // print the type of x
	std::cout << typeid(&x).name() << '\n'; // print the type of &x

	return 0;
}
```

On Visual Studio, this printed:

int
int *

With gcc, this printed `i` (int) and `pi` (pointer to int) instead. Because the result of typeid().name() is compiler-dependent, your compiler may print something different, but it will have the same meaning.

---
### The size of pointers

The size of a pointer is dependent upon the architecture the executable is compiled for -- a 32-bit executable uses 32-bit memory addresses -- consequently, a pointer on a 32-bit machine is 32 bits (4 bytes). With a 64-bit executable, a pointer would be 64 bits (8 bytes). Note that this is true regardless of the size of the object being pointed to:

```cpp
#include <iostream>

int main() // assume a 32-bit application
{
    char* chPtr{};        // chars are 1 byte
    int* iPtr{};          // ints are usually 4 bytes
    long double* ldPtr{}; // long doubles are usually 8 or 12 bytes

    std::cout << sizeof(chPtr) << '\n'; // prints 4
    std::cout << sizeof(iPtr) << '\n';  // prints 4
    std::cout << sizeof(ldPtr) << '\n'; // prints 4

    return 0;
}
```

The size of the pointer is always the same. This is because a pointer is just a memory address, and the number of bits needed to access a memory address is constant.

---
### Dangling pointers

>Much like a dangling reference, a **dangling pointer** is a pointer that is holding the address of an object that is no longer valid (e.g. because it has been destroyed).

Dereferencing a dangling pointer (e.g. in order to print the value being pointed at) will lead to undefined behavior, as you are trying to access an object that is no longer valid.

Perhaps surprisingly, the standard says “Any other use of an invalid pointer _value_ has implementation-defined behavior”. This means that you can assign an invalid pointer a new value, such as nullptr (because this doesn’t use the invalid pointer’s value). However, any other operations that use the invalid pointer’s value (such as copying or incrementing an invalid pointer) will yield implementation-defined behavior.

Key insight

Dereferencing an invalid pointer will lead to undefined behavior. Any other use of an invalid pointer value is implementation-defined.

Here’s an example of creating a dangling pointer:

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x };

    std::cout << *ptr << '\n'; // valid

    {
        int y{ 6 };
        ptr = &y;

        std::cout << *ptr << '\n'; // valid
    } // y goes out of scope, and ptr is now dangling

    std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer

    return 0;
}
```

The above program will probably print:

5
6
6

But it may not, as the object that `ptr` was pointing at went out of scope and was destroyed at the end of the inner block, leaving `ptr` dangling.

💡 **Best practice**:  

Whenever an object goes out of scope or memory is freed, **immediately set the pointer to `nullptr`** to avoid dangling pointers:

```cpp
ptr = nullptr;
```

---
