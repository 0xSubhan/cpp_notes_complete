
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
### Null Pointers

>Besides a memory address, there is one additional value that a pointer can hold: a null value. A **null value** (often shortened to **null**) is a special value that means something has no value. When a pointer is holding a null value, it means the pointer is not pointing at anything. Such a pointer is called a **null pointer**.

The easiest way to create a null pointer is to use value initialization:

```cpp
int main()
{
    int* ptr {}; // ptr is now a null pointer, and is not holding an address

    return 0;
}
```

>[!Best Practice]
>Value initialize your pointers (to be null pointers) if you are not initializing them with the address of a valid object.

>Because we can use assignment to change what a pointer is pointing at, a pointer that is initially set to null can later be changed to point at a valid object:

```cpp
#include <iostream>

int main()
{
    int* ptr {}; // ptr is a null pointer, and is not holding an address

    int x { 5 };
    ptr = &x; // ptr now pointing at object x (no longer a null pointer)

    std::cout << *ptr << '\n'; // print value of x through dereferenced ptr

    return 0;
}
```

---
### The nullptr keyword

Much like the keywords `true` and `false` represent Boolean literal values, the **nullptr** keyword represents a null pointer literal. We can use `nullptr` to explicitly initialize or assign a pointer a null value.

```cpp
int main()
{
    int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer

    int value { 5 };
    int* ptr2 { &value }; // ptr2 is a valid pointer
    ptr2 = nullptr; // Can assign nullptr to make the pointer a null pointer

    someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter

    return 0;
}
```

In the above example, we use assignment to set the value of `ptr2` to `nullptr`, making `ptr2` a null pointer.

>[!Best Practice]
>Use `nullptr` when you need a null pointer literal for initialization, assignment, or passing a null pointer to a function.

---
### Dereferencing a null pointer results in undefined behavior

```cpp
#include <iostream>

int main()
{
    int* ptr {}; // Create a null pointer
    std::cout << *ptr << '\n'; // Dereference the null pointer

    return 0;
}
```

>Much like dereferencing a dangling (or wild) pointer leads to undefined behavior, dereferencing a null pointer also leads to undefined behavior. In most cases, it will crash your application.

Conceptually, this makes sense. Dereferencing a pointer means “go to the address the pointer is pointing at and access the value there”. A null pointer holds a null value, which semantically means the pointer is not pointing at anything. So what value would it access?

>[!Warning]
>Whenever you are using pointers, you’ll need to be extra careful that your code isn’t dereferencing null or dangling pointers, as this will cause undefined behavior (probably an application crash).

---
### Checking for null pointers

Much like we can use a conditional to test Boolean values for `true` or `false`, we can use a conditional to test whether a pointer has value `nullptr` or not:

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    if (ptr == nullptr) // explicit test for equivalence
        std::cout << "ptr is null\n";
    else
        std::cout << "ptr is non-null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr==nullptr ? "null\n" : "non-null\n"); // explicit test for equivalence

    return 0;
}
```

The above program prints:

ptr is non-null
nullPtr is null

>In lesson [4.9 -- Boolean values](https://www.learncpp.com/cpp-tutorial/boolean-values/), we noted that integral values will implicitly convert into Boolean values: an integral value of `0` converts to Boolean value `false`, and any other integral value converts to Boolean value `true`.

Similarly, pointers will also implicitly convert to Boolean values: a null pointer converts to Boolean value `false`, and a non-null pointer converts to Boolean value `true`. This allows us to skip explicitly testing for `nullptr` and just use the implicit conversion to Boolean to test whether a pointer is a null pointer. The following program is equivalent to the prior one:

```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    // pointers convert to Boolean false if they are null, and Boolean true if they are non-null
    if (ptr) // implicit conversion to Boolean
        std::cout << "ptr is non-null\n";
    else
        std::cout << "ptr is null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n"); // implicit conversion to Boolean

    return 0;
}
```

>[!Warning]
>Conditionals can only be used to differentiate null pointers from non-null pointers. There is no convenient way to determine whether a non-null pointer is pointing to a valid object or dangling (pointing to an invalid object).

---
### Use nullptr to avoid dangling pointers

Use nullptr to avoid dangling pointers

Above, we mentioned that dereferencing a pointer that is either null or dangling will result in undefined behavior. Therefore, we need to ensure our code does not do either of these things.

We can easily avoid dereferencing a null pointer by using a conditional to ensure a pointer is non-null before trying to dereference it:

```cpp
// Assume ptr is some pointer that may or may not be a null pointer
if (ptr) // if ptr is not a null pointer
    std::cout << *ptr << '\n'; // okay to dereference
else
    // do something else that doesn't involve dereferencing ptr (print an error message, do nothing at all, etc...)
```

But what about dangling pointers? Because there is no way to detect whether a pointer is dangling, we need to avoid having any dangling pointers in our program in the first place. We do that by ensuring that any pointer that is not pointing at a valid object is set to `nullptr`.

That way, before dereferencing a pointer, we only need to test whether it is null -- if it is non-null, we assume the pointer is not dangling.

>[!Best Practice]
>A pointer should either hold the address of a valid object, or be set to nullptr. That way we only need to test pointers for null, and can assume any non-null pointer is valid.

>[!Warning]
>When an object is destroyed, any pointers to the destroyed object will be left dangling (they will not be automatically set to `nullptr`). It is your responsibility to detect these cases and ensure those pointers are subsequently set to `nullptr`.

---
### [Both `0` and `NULL` should be avoided in modern C++](https://www.learncpp.com/cpp-tutorial/null-pointers/#:~:text=Legacy%20null%20pointer,part%202)

---
### Favor references over pointers whenever possible

Pointers and references both give us the ability to access some other object indirectly.

Pointers have the additional abilities of being able to change what they are pointing at, and to be pointed at null. However, these pointer abilities are also inherently dangerous: A null pointer runs the risk of being dereferenced, and the ability to change what a pointer is pointing at can make creating dangling pointers easier:

```cpp
int main()
{
    int* ptr { };

    {
        int x{ 5 };
        ptr = &x; // assign the pointer to an object that will be destroyed (not possible with a reference)
    } // ptr is now dangling and pointing to invalid object

    if (ptr) // condition evaluates to true because ptr is not nullptr
        std::cout << *ptr; // undefined behavior

    return 0;
}
```

Since references can’t be bound to null, we don’t have to worry about null references. And because references must be bound to a valid object upon creation and then can not be reseated, dangling references are harder to create.

Because they are safer, references should be favored over pointers, unless the additional capabilities provided by pointers are required.

>[!Best Practice]
>Favor references over pointers unless the additional capabilities provided by pointers are needed.

---
### Why should we set pointers that aren’t pointing to a valid object to ‘nullptr’?

We can not determine whether a non-null pointer is valid or dangling, and accessing a dangling pointer will result in undefined behavior. Therefore, we need to ensure that we do not have any dangling pointers in our program.

If we ensure all pointers are either pointing to valid objects or set to `nullptr`, then we can use a conditional to test for null to ensure we don’t dereference a null pointer, and assume all non-null pointers are pointing to valid objects.

---
### Pointers and const 

```cpp
int main()
{
    const int x { 5 }; // x is now const
    int* ptr { &x };   // compile error: cannot convert from const int* to int*

    return 0;
}
```

>The above snippet won’t compile -- we can’t set a normal pointer to point at a const variable. This makes sense: a const variable is one whose value cannot be changed. Allowing the programmer to set a non-const pointer to a const value would allow the programmer to dereference the pointer and change the value. That would violate the const-ness of the variable.

#### Pointer to const value

A **pointer to a const value** (sometimes called a `pointer to const` for short) is a (non-const) pointer that points to a constant value.

To declare a pointer to a const value, use the `const` keyword before the pointer’s data type:

```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // okay: ptr is pointing to a "const int"

    *ptr = 6; // not allowed: we can't change a const value

    return 0;
}
```

In the above example, `ptr` points to a `const int`. Because the data type being pointed to is const, the value being pointed to can’t be changed.

However, because a pointer to const is not const itself (it just points to a const value), we can change what the pointer is pointing at by assigning the pointer a new address:

```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // ptr points to const int x

    const int y{ 6 };
    ptr = &y; // okay: ptr now points at const int y

    return 0;
}
```

Just like a reference to const, a pointer to const can point to non-const variables too. A pointer to const treats the value being pointed to as constant, regardless of whether the object at that address was initially defined as const or not:

```cpp
int main()
{
    int x{ 5 }; // non-const
    const int* ptr { &x }; // ptr points to a "const int"

    *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
    x = 6; // allowed: the value is still non-const when accessed through non-const identifier x

    return 0;
}
```

>[!Note]
>because a pointer to const is not const itself (it just points to a const value), we can change what the pointer is pointing at by assigning the pointer a new address

---
### Const pointers

>We can also make a pointer itself constant. A **const pointer** is a pointer whose address can not be changed after initialization.

To declare a const pointer, use the `const` keyword after the asterisk in the pointer declaration:

```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // const after the asterisk means this is a const pointer

    return 0;
}
```

In the above case, `ptr` is a const pointer to a (non-const) int value.

>Just like a normal const variable, a const pointer must be initialized upon definition, and this value can’t be changed via assignment:

```cpp
int main()
{
    int x{ 5 };
    int y{ 6 };

    int* const ptr { &x }; // okay: the const pointer is initialized to the address of x
    ptr = &y; // error: once initialized, a const pointer can not be changed.

    return 0;
}
```

>However, because the _value_ being pointed to is non-const, it is possible to change the value being pointed to via dereferencing the const pointer:

```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // ptr will always point to x

    *ptr = 6; // okay: the value being pointed to is non-const

    return 0;
}
```

---
### Const pointer to a const value

Finally, it is possible to declare a **const pointer to a const value** by using the `const` keyword both before the type and after the asterisk:

```cpp
int main()
{
    int value { 5 };
    const int* const ptr { &value }; // a const pointer to a const value

    return 0;
}
```

A const pointer to a const value can not have its address changed, nor can the value it is pointing to be changed through the pointer. It can only be dereferenced to get the value it is pointing at.

---
### Pointer and const recap

To summarize, you only need to remember 4 rules, and they are pretty logical:

- A non-const pointer (e.g. `int* ptr`) can be assigned another address to change what it is pointing at.
- A const pointer (e.g. `int* const ptr`) always points to the same address, and this address can not be changed.

- A pointer to a non-const value (e.g. `int* ptr`) can change the value it is pointing to. These can not point to a const value.
- A pointer to a const value (e.g. `const int* ptr`) treats the value as const when accessed through the pointer, and thus can not change the value it is pointing to. These can be pointed to const or non-const l-values (but not r-values, which don’t have an address).

Keeping the declaration syntax straight can be a bit challenging:

- A `const` before the asterisk (e.g. `const int* ptr`) is associated with the type being pointed to. Therefore, this is a pointer to a const value, and the value cannot be modified through the pointer.
- A `const` after the asterisk (e.g. `int* const ptr`) is associated with the pointer itself. Therefore, this pointer cannot be assigned a new address.

```cpp
int main()
{
    int v{ 5 };

    int* ptr0 { &v };             // points to an "int" but is not const itself.  We can modify the value or the address.
    const int* ptr1 { &v };       // points to a "const int" but is not const itself.  We can only modify the address.
    int* const ptr2 { &v };       // points to an "int" and is const itself.   We can only modify the value.
    const int* const ptr3 { &v }; // points to a "const int" and is const itself.  We can't modify the value nor the address.

    // if the const is on the left side of the *, the const belongs to the value
    // if the const is on the right side of the *, the const belongs to the pointer

    return 0;
}
```

---
### Pass by address

C++ provides a third way to pass values to a function, called pass by address. With **pass by address**, instead of providing an object as an argument, the caller provides an object’s _address_ (via a pointer). This pointer (holding the address of the object) is copied into a pointer parameter of the called function (which now also holds the address of the object). The function can then dereference that pointer to access the object whose address was passed.

Here’s a version of the above program that adds a pass by address variant:

```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    return 0;
}
```

Note how similar all three of these versions are. Let’s explore the pass by address version in more detail.

First, because we want our `printByAddress()` function to use pass by address, we’ve made our function parameter a pointer named `ptr`. Since `printByAddress()` will use `ptr` in a read-only manner, `ptr` is a pointer to a const value.

```cpp
void printByAddress(const std::string* ptr)
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}
```

Inside the `printByAddress()` function, we dereference `ptr` parameter to access the value of the object being pointed to.

Second, when the function is called, we can’t just pass in the `str` object -- we need to pass in the address of `str`. The easiest way to do that is to use the address-of operator (&) to get a pointer holding the address of `str`:

```cpp
printByAddress(&str); // use address-of operator (&) to get pointer holding address of str
```

When this call is executed, `&str` will create a pointer holding the address of `str`. This address is then copied into function parameter `ptr` as part of the function call. Because `ptr` now holds the address of `str`, when the function dereferences `ptr`, it will get the value of `str`, which the function prints to the console.

That’s it.

Although we use the address-of operator in the above example to get the address of `str`, if we already had a pointer variable holding the address of `str`, we could use that instead:

```cpp
int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    std::string* ptr { &str }; // define a pointer variable holding the address of str
    printByAddress(ptr); // pass str by address, does not make a copy of str

    return 0;
}
```

---
### Pass by address does not make a copy of the object being pointed to

Consider the following statements:

```cpp
std::string str{ "Hello, world!" };
printByAddress(&str); // use address-of operator (&) to get pointer holding address of str
```

As we noted in [12.5 -- Pass by lvalue reference](https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/), copying a `std::string` is expensive, so that’s something we want to avoid. When we pass a `std::string` by address, we’re not copying the actual `std::string` object -- we’re just copying the pointer (holding the address of the object) from the caller to the called function. Since an address is typically only 4 or 8 bytes, a pointer is only 4 or 8 bytes, so copying a pointer is always fast.

Thus, just like pass by reference, pass by address is fast, and avoids making a copy of the argument object.

---
### Pass by address allows the function to modify the argument’s value

>When we pass an object by address, the function receives the address of the passed object, which it can access via dereferencing. Because this is the address of the actual argument object being passed (not a copy of the object), if the function parameter is a pointer to non-const, the function can modify the argument via the pointer parameter:

```cpp
#include <iostream>

void changeValue(int* ptr) // note: ptr is a pointer to non-const in this example
{
    *ptr = 6; // change the value to 6
}

int main()
{
    int x{ 5 };

    std::cout << "x = " << x << '\n';

    changeValue(&x); // we're passing the address of x to the function

    std::cout << "x = " << x << '\n';

    return 0;
}
```
x = 5
x = 6

#### 1. **Two different uses of `const` with pointers**

When you see `const` in a pointer parameter, it can mean two very different things depending on its position:

##### **A. `const` before the type → "pointer-to-const"**

```cpp
void changeValue(const int* ptr);
```

- Here, `ptr` points to a **const int**.
    
- You **cannot modify** the value being pointed to (`*ptr` is read-only inside the function).
    
- The **caller** knows their passed-in variable **won’t be changed** by the function.
    
- **Significant** because it affects how the function can interact with the caller’s data.
    

#####  **B. `const` after the `*` → "const pointer"**

```cpp
void changeValue(int* const ptr);
```

- Here, `ptr` itself **cannot be changed** to point somewhere else inside the function.
    
- But the value pointed to (`*ptr`) **can still be changed**.
    
- **No impact on the caller** — this only matters to the function implementation.
    
- Mostly just a **self-reminder/documentation** for the implementer.
    
- Often considered **noise** unless there's a very specific reason to enforce that the pointer won't be reassigned.
    

#### 2. **Why pointer-to-const is preferred**

If your function is **not supposed to modify** the data being pointed to, making it `pointer-to-const`:

- Prevents accidental modification.
    
- Communicates the contract to the caller.
    
- Example:
    

```cpp
void printArray(const int* arr, int size); // clearly read-only
```

#### 3. **Why const-pointer parameters are usually avoided**

If you start using `const` for **const pointers** everywhere, it becomes harder to visually spot the important case: pointer-to-const.

Example from your snippet:

```cpp
void foo(const char* source, char* dest, int count);
```

- Easy to see:
    
    - `source` is **pointer-to-const char** (read-only)
        
    - `dest` is **pointer-to-non-const char** (can be modified)
        

Now compare:

```cpp
void foo(const char* const source, char* const dest, int count);
```

- Both parameters have `const` in them, but:
    
    - `source` is **const pointer to const char** (read-only data, pointer itself fixed)
        
    - `dest` is **const pointer to non-const char** (can still modify data!)  
        That subtlety can be **easy to miss**.
        

This is why adding `const` to the pointer itself often makes code harder to read without providing real benefit.

>[!Best Practice]
>Prefer pointer-to-const function parameters over pointer-to-non-const function parameters, unless the function needs to modify the object passed in.  
Do not make function parameters const pointers unless there is some specific reason to do so.

---
### Null checking

Now consider this fairly innocent looking program:

```cpp
#include <iostream>

void print(int* ptr)
{
	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };
	print(&x);

	int* myPtr {};
	print(myPtr);

	return 0;
}
```

When this program is run, it will print the value `5` and then most likely crash.

In the call to `print(myPtr)`, `myPtr` is a null pointer, so function parameter `ptr` will also be a null pointer. When this null pointer is dereferenced in the body of the function, undefined behavior results.

When passing a parameter by address, care should be taken to ensure the pointer is not a null pointer before you dereference the value. One way to do that is to use a conditional statement:

```cpp
#include <iostream>

void print(int* ptr)
{
    if (ptr) // if ptr is not a null pointer
    {
        std::cout << *ptr << '\n';
    }
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

In the above program, we’re testing `ptr` to ensure it is not null before we dereference it. While this is fine for such a simple function, in more complicated functions this can result in redundant logic (testing if ptr is not null multiple times) or nesting of the primary logic of the function (if contained in a block).

In most cases, it is more effective to do the opposite: test whether the function parameter is null as a precondition ([9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/)) and handle the negative case immediately:

```cpp
#include <iostream>

void print(int* ptr)
{
    if (!ptr) // if ptr is a null pointer, early return back to the caller
        return;

    // if we reached this point, we can assume ptr is valid
    // so no more testing or nesting required

    std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

If a null pointer should never be passed to the function, an `assert` (which we covered in lesson [9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/)) can be used instead (or also) (as asserts are intended to document things that should never happen):

```cpp
#include <iostream>
#include <cassert>

void print(const int* ptr) // now a pointer to a const int
{
	assert(ptr); // fail the program in debug mode if a null pointer is passed (since this should never happen)

	// (optionally) handle this as an error case in production mode so we don't crash if it does happen
	if (!ptr)
		return;

	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```

---
### Prefer pass by (const) reference

Note that function `print()` in the example above doesn’t handle null values very well -- it effectively just aborts the function. Given this, why allow a user to pass in a null value at all? Pass by reference has the same benefits as pass by address without the risk of inadvertently dereferencing a null pointer.

Pass by const reference has a few other advantages over pass by address.

First, because an object being passed by address must have an address, only lvalues can be passed by address (as rvalues don’t have addresses). Pass by const reference is more flexible, as it can accept lvalues and rvalues:

```cpp
#include <iostream>

void printByValue(int val) // The function parameter is a copy of the argument
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    printByValue(5);     // valid (but makes a copy)
    printByReference(5); // valid (because the parameter is a const reference)
    printByAddress(&5);  // error: can't take address of r-value

    return 0;
}
```

Second, the syntax for pass by reference is natural, as we can just pass in literals or objects. With pass by address, our code ends up littered with ampersands (&) and asterisks (*).

In modern C++, most things that can be done with pass by address are better accomplished through other methods. Follow this common maxim: “Pass by reference when you can, pass by address when you must”.

>[!Best Practice]
>Prefer pass by reference to pass by address unless you have a specific reason to use pass by address.

---
### Pass by address for “optional” arguments

One of the more common uses for pass by address is to allow a function to accept an “optional” argument. This is easier to illustrate by example than to describe:

```cpp
#include <iostream>

void printIDNumber(const int *id=nullptr)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(&userid); // we know the user's ID now

    return 0;
}
```

This example prints:

Your ID number is not known.
Your ID number is 34.

In this program, the `printIDNumber()` function has one parameter that is passed by address and defaulted to `nullptr`. Inside `main()`, we call this function twice. The first call, we don’t know the user’s ID, so we call `printIDNumber()` without an argument. The `id` parameter defaults to `nullptr`, and the function prints `Your ID number is not known.`. For the second call, we now have a valid id, so we call `printIDNumber(&userid)`. The `id` parameter receives the address of `userid`, so the function prints `Your ID number is 34.`.

However, in many cases, function overloading is a better alternative to achieve the same result.

---
### Changing what a pointer parameter points at

When we pass an address to a function, that address is copied from the argument into the pointer parameter (which is fine, because copying an address is fast). Now consider the following program:

```cpp
#include <iostream>

// [[maybe_unused]] gets rid of compiler warnings about ptr2 being set but not used
void nullify([[maybe_unused]] int* ptr2)
{
    ptr2 = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```

This program prints:

ptr is non-null
ptr is non-null

As you can see, changing the address held by the pointer parameter had no impact on the address held by the argument (`ptr` still points at `x`). When function `nullify()` is called, `ptr2` receives a copy of the address passed in (in this case, the address held by `ptr`, which is the address of `x`). When the function changes what `ptr2` points at, this only affects the copy held by `ptr2`.

So what if we want to allow a function to change what a pointer argument points to?

---
### Pass by address… by reference?

Yup, it’s a thing. Just like we can pass a normal variable by reference, we can also pass pointers by reference. Here’s the same program as above with `ptr2` changed to be a reference to an address:

```cpp
#include <iostream>

void nullify(int*& refptr) // refptr is now a reference to a pointer
{
    refptr = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```

This program prints:

ptr is non-null
ptr is null

Because `refptr` is now a reference to a pointer, when `ptr` is passed as an argument, `refptr` is bound to `ptr`. This means any changes to `refptr` are made to `ptr`.

---
### [Why using `0` or `NULL` is no longer preferred (optional)](https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/#:~:text=In%20this%20subsection,a%20pointer%20type.)

---
### [std::nullptr_t (optional)](https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/#:~:text=Since%20nullptr%20can,just%20in%20case.)

---
### There is only pass by value under the hood

#### 1. **The normal picture**

In C++, we talk about:

- **Pass by value** → function gets its own copy of the argument
    
- **Pass by reference** → function gets an alias to the caller’s variable
    
- **Pass by address** → function gets a pointer to the caller’s variable
    

At the language level, these _feel_ different.  
But under the hood, the CPU doesn’t think in “references” — it only moves **values** around.

#### 2. **What’s really going on**

A CPU register or stack slot just stores **bits**.  
When you pass anything to a function, the function parameter is **assigned** some bits — always a copy.

##### A. Pass-by-value

```cpp
`void foo(int x) { x = 10; } int main() {     int a = 5;     foo(a); // copy of a into x }`
```

- The integer value `5` is copied into parameter `x`.
    
- Changes to `x` don’t affect `a` because they’re different memory locations.
    

##### B. Pass-by-address (pointer)

```cpp
`void foo(int* p) { *p = 10; } int main() {     int a = 5;     foo(&a); // copy of address of a into p }`
```

- The **address** of `a` (e.g., `0x7ffe...`) is **copied** into parameter `p`.
    
- Because `p` stores `a`’s location, dereferencing `*p` changes the caller’s variable.
    
- The pointer itself is **still passed by value** — just the _value happens to be an address_.
    

##### C. Pass-by-reference

```cpp
`void foo(int& r) { r = 10; } int main() {     int a = 5;     foo(a); // compiler secretly passes &a }`
```

- A reference in C++ is _usually_ implemented internally as a pointer that the compiler hides from you.
    
- Under the hood, the compiler takes the **address of `a`** and **passes it by value** to the function.
    
- Inside `foo`, `r` is just an alias for whatever the pointer points to.
    

#### 3. **So why “everything is pass-by-value” is true**

At the hardware level:

- **Always a copy** is made — either:
    
    - A copy of the actual object’s value (pass-by-value), or
        
    - A copy of the address pointing to the object (pass-by-address / pass-by-reference).
        
- “Pass-by-reference” is just “pass the address by value” + “automatically dereference it whenever used”.
    

The _difference_ between these mechanisms is **what that copied value represents** and whether the function can use it to affect the caller’s data.

#### 4. **Key takeaway**

- **Pass-by-value**: copy of the actual data → can’t modify caller’s variable.
    
- **Pass-by-address**: copy of the variable’s address → can modify caller’s variable by dereferencing.
    
- **Pass-by-reference**: compiler-generated pass-by-address that looks like you’re working directly with the original variable.

---
### Return by reference and return by address

>when returning by value: a copy of the return value is passed back to the caller. If the return type of the function is a class type, this can be expensive.

```cpp
std::string returnByValue(); // returns a copy of a std::string (expensive)
```

### Return by reference

>In cases where we’re passing a class type back to the caller, we may (or may not) want to return by reference instead. **Return by reference** returns a reference that is bound to the object being returned, which avoids making a copy of the return value. To return by reference, we simply define the return value of the function to be a reference type:

```cpp
std::string&       returnByReference(); // returns a reference to an existing std::string (cheap)
const std::string& returnByReferenceToConst(); // returns a const reference to an existing std::string (cheap)
```

Here is an academic program to demonstrate the mechanics of return by reference:

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // returns a const reference
{
    static const std::string s_programName { "Calculator" }; // has static duration, destroyed at end of program

    return s_programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName();

    return 0;
}
```

This program prints:

This program is named Calculator

Because `getProgramName()` returns a const reference, when the line `return s_programName` is executed, `getProgramName()` will return a const reference to `s_programName` (thus avoiding making a copy). That const reference can then be used by the caller to access the value of `s_programName`, which is printed.

---
### The object being returned by reference must exist after the function returns

>Using return by reference has one major caveat: the programmer _must_ be sure that the object being referenced outlives the function returning the reference. Otherwise, the reference being returned will be left dangling (referencing an object that has been destroyed), and use of that reference will result in undefined behavior.

In the program above, because `s_programName` has static duration, `s_programName` will exist until the end of the program. When `main()` accesses the returned reference, it is actually accessing `s_programName`, which is fine, because `s_programName` won’t be destroyed until later.

Now let’s modify the above program to show what happens in the case where our function returns a dangling reference:

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName()
{
    const std::string programName { "Calculator" }; // now a non-static local variable, destroyed when function ends

    return programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName(); // undefined behavior

    return 0;
}
```

>[!Warning]
>Objects returned by reference must live beyond the scope of the function returning the reference, or a dangling reference will result. Never return a (non-static) local variable or temporary by reference.

---
### Lifetime extension doesn’t work across function boundaries

####  **1. What lifetime extension normally does**

Normally, when you bind a **const reference** directly to a **temporary**, the compiler extends the lifetime of that temporary until the reference goes out of scope.

Example:

```cpp
const int& ref = 5; // temporary int(5) lives as long as ref
```

Here:

- Compiler creates a temporary holding `5`.
    
- `ref` binds directly to that temporary.
    
- Lifetime is extended to match `ref`’s lifetime → safe.
    

#### **2. Why it fails across function boundaries**

When you introduce a **function call** in between, the binding is no longer direct.

Example:

```cpp
const int& returnByConstReference() {
    return 5; // const ref to a temporary
}

const int& ref = returnByConstReference(); // looks similar, but...
```

What actually happens:

1. Inside `returnByConstReference()`:
    
    - A temporary holding `5` is created.
        
    - A const reference binds to it.
        
    - **Lifetime extension applies here** — but only _inside the function_.
        
2. When the function returns:
    
    - The temporary is destroyed (end of function scope).
        
    - The returned reference is now **dangling**.
        
3. Caller binds this dangling reference to `ref` — too late to save it.
    

The rule:

> Lifetime extension **only applies at the point of the original binding**.  
> If you “bounce” the reference through a function, it’s not considered the same binding anymore.

#### **3. The indirect binding trap**

Your second example shows the subtle version:

```cpp
const int& returnByConstReference(const int& ref) {
    return ref;
}

const int& ref2 = returnByConstReference(5); // dangling!
```

- Temporary `int(5)` is created in the caller.
    
- It’s bound to the parameter `ref` **inside the function** → lifetime extension happens _inside_ the function.
    
- When the function ends, the parameter `ref` goes out of scope → temporary destroyed.
    
- The caller gets a dangling reference.
    

It’s _indirect_ because:

```sql
temporary → parameter (in function) → returned reference → new variable in caller
```

Lifetime extension **only works for**:

```bash
temporary → reference (direct in caller scope)
```

Example:

```cpp
#include <iostream>

const int& returnByConstReference(const int& ref)
{
    return ref;
}

int main()
{
    // case 1: direct binding
    const int& ref1 { 5 }; // extends lifetime
    std::cout << ref1 << '\n'; // okay

    // case 2: indirect binding
    const int& ref2 { returnByConstReference(5) }; // binds to dangling reference
    std::cout << ref2 << '\n'; // undefined behavior

    return 0;
}
```

>In case 2, a temporary object is created to hold value `5`, which function parameter `ref` binds to. The function just returns this reference back to the caller, which then uses the reference to initialize `ref2`. Because this is not a direct binding to the temporary object (as the refrence was bounced through a function), lifetime extension doesn’t apply. This leaves `ref2` dangling, and its subsequent use is undefined behavior.

>[!Warning]
>Reference lifetime extension does not work across function boundaries.

---
### Don’t return non-const static local variables by reference

>In the original example above, we returned a const static local variable by reference to illustrate the mechanics of return by reference in a simple way. However, returning non-const static local variables by reference is fairly non-idiomatic, and should generally be avoided. Here’s a simplified example that illustrates one such problem that can occur:

```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

int main()
{
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << id1 << id2 << '\n';

    return 0;
}
```

This program prints:

22

This happens because `id1` and `id2` are referencing the same object (the static variable `s_x`), so when anything (e.g. `getNextId()`) modifies that value, all references are now accessing the modified value.

This above example can be fixed by making `id1` and `id2` normal variables (rather than references) so they save a copy of the return value rather than a reference to `s_x`.

>Here’s another example with a less obvious version of the same problem:

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string& getName()
{
    static std::string s_name{};
    std::cout << "Enter a name: ";
    std::cin >> s_name;
    return s_name;
}

void printFirstAlphabetical(const std::string& s1, const std::string& s2)
{
    if (s1 < s2)
        std::cout << s1 << " comes before " << s2 << '\n';
    else
        std::cout << s2 << " comes before " << s1 << '\n';
}

int main()
{
    printFirstAlphabetical(getName(), getName());

    return 0;
}
```

Here’s the result from one run of this program:

Enter a name: Dave
Enter a name: Stan
Stan comes before Stan

In this example, `getName()` returns a reference to static local `s_name`. Initializing a `const std::string&` with a reference to `s_name` causes that `std::string&` to bind to `s_name` (not make a copy of it).

Thus, both `s1` and `s2` end up viewing `s_name` (which was assigned the last name we entered).

Note that if we use `std::string_view` parameters instead, the first `std::string_view` parameter will be invalidated when the underlying `std::string` is changed.

>Another issue that commonly occurs with programs that return a non-const static local by reference is that there is no standardized way to reset `s_x` back to the default state. Such programs must either use a non-conventional solution (e.g. a reset function parameter), or can only be reset by quitting and restarting the program.

>[!Best Practice]
>Avoid returning references to non-const local static variables.

>Returning a const reference to a _const_ local static variable is sometimes done if the local variable being returned by reference is expensive to create and/or initialize (so we don’t have to recreate the variable every function call). But this is rare.

>Returning a const reference to a _const_ global variable is also sometimes done as a way to encapsulate access to a global variable.

---
### Assigning/initializing a normal variable with a returned reference makes a copy

If a function returns a reference, and that reference is used to initialize or assign to a non-reference variable, the return value will be copied (as if it had been returned by value).

```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 };
    ++s_x;
    return s_x;
}

int main()
{
    const int id1 { getNextId() }; // id1 is a normal variable now and receives a copy of the value returned by reference from getNextId()
    const int id2 { getNextId() }; // id2 is a normal variable now and receives a copy of the value returned by reference from getNextId()

    std::cout << id1 << id2 << '\n';

    return 0;
}
```

In the above example, `getNextId()` is returning a reference, but `id1` and `id2` are non-reference variables. In such a case, the value of the returned reference is copied into the normal variable. Thus, this program prints:

12

Also note that if a program returns a dangling reference, the reference is left dangling before the copy is made, which will lead to undefined behavior:

```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // will return a const reference
{
    const std::string programName{ "Calculator" };

    return programName;
}

int main()
{
    std::string name { getProgramName() }; // makes a copy of a dangling reference
    std::cout << "This program is named " << name << '\n'; // undefined behavior

    return 0;
}
```

---
### It’s okay to return reference parameters by reference

>There are quite a few cases where returning objects by reference makes sense, and we’ll encounter many of those in future lessons. However, there is one useful example that we can show now.

If a parameter is passed into a function by reference, it’s safe to return that parameter by reference. This makes sense: in order to pass an argument to a function, the argument must exist in the scope of the caller. When the called function returns, that object must still exist in the scope of the caller.

Here is a simple example of such a function:

```cpp
#include <iostream>
#include <string>

// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int main()
{
	std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world) << '\n';

	return 0;
}
```

This prints:

Hello

In the above function, the caller passes in two std::string objects by const reference, and whichever of these strings comes first alphabetically is passed back by const reference. If we had used pass by value and return by value, we would have made up to 3 copies of std::string (one for each parameter, one for the return value). By using pass by reference/return by reference, we can avoid those copies.

---
### It’s okay for an rvalue passed by const reference to be returned by const reference

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

When an argument for a const reference parameter is an rvalue, it’s still okay to return that parameter by const reference.

This is because rvalues are not destroyed until the end of the full expression in which they are created.

First, let’s look at this example:

```cpp
#include <iostream>
#include <string>

std::string getHello()
{
    return "Hello"; // implicit conversion to std::string
}

int main()
{
    const std::string s{ getHello() };

    std::cout << s;

    return 0;
}
```

In this case, `getHello()` returns a `std::string` by value, which is an rvalue. This rvalue is then used to initialize `s`. After the initialization of `s`, the expression in which the rvalue was created has finished evaluating, and the rvalue is destroyed.

Now let’s take a look at this similar example:

```cpp
#include <iostream>
#include <string>

const std::string& foo(const std::string& s)
{
    return s;
}

std::string getHello()
{
    return "Hello"; // implicit conversion to std::string
}

int main()
{
    const std::string s{ foo(getHello()) };

    std::cout << s;

    return 0;
}
```

#### Step-by-step (safe case):

**1. `getHello()` runs**

- Creates **temporary std::string("Hello")** — call it `tempHello`.
    

**2. `foo()` is called**

- `paramRef` (inside `foo`) is bound to `tempHello`.
    
- `foo()` returns a reference to `tempHello`.
    

**3. Back in `main()`**

- The returned reference to `tempHello` is immediately used to **copy-construct** `myString` in `main`.
    
- Now `myString` has **its own separate copy** of `"Hello"`.
    

**4. End of full expression**

- `tempHello` is destroyed here, but `myString` is fine because it’s a separate object with its own storage.

#### ---> Confusion:

#### 1. Inside `foo`

```cpp
const std::string& foo(const std::string& s)
{
    return s;
}
```

- `s` is **just a reference variable** — it’s not an object itself.
    
- It’s bound to the **temporary object `"Hello"`** created by `getHello()`.
    
- When `foo` returns `s`, it’s not returning the `s` variable — it’s returning **the same reference** to `"Hello"`.
    

#### 2. When `foo` ends

- The parameter variable `s` (the reference itself) goes out of scope.
    
- This **does not** destroy `"Hello"` — because references don’t control an object’s lifetime.
    
- The temporary `"Hello"` still exists until the **end of the full expression** in `main`.
    

#### 3. Back in `main`

```cpp
const std::string str{ foo(getHello()) };
```

- The returned reference to `"Hello"` is **immediately** used to **copy-construct** `str`.
    
- That copy happens **before** the temporary `"Hello"` is destroyed.
    
- `"Hello"` is destroyed only after the statement finishes executing — but `str` already has its own independent copy.
    

#### ✅ So:

- `s` being destroyed **doesn’t matter**, because it’s only a reference — it doesn’t own `"Hello"`.
    
- The actual `"Hello"` object stays alive long enough for `main` to copy it.

---
### The caller can modify values through the reference

>When an argument is passed to a function by non-const reference, the function can use the reference to modify the value of the argument.

Similarly, when a non-const reference is returned from a function, the caller can use the reference to modify the value being returned.

Here’s an illustrative example:

```cpp
#include <iostream>

// takes two integers by non-const reference, and returns the greater by reference
int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7

    std::cout << a << b << '\n';

    return 0;
}
```

In the above program, `max(a, b)` calls the `max()` function with `a` and `b` as arguments. Reference parameter `x` binds to argument `a`, and reference parameter `y` binds to argument `b`. The function then determines which of `x` (`5`) and `y` (`6`) is greater. In this case, that’s `y`, so the function returns `y` (which is still bound to `b`) back to the caller. The caller then assigns the value `7` to this returned reference.

Therefore, the expression `max(a, b) = 7` effectively resolves to `b = 7`.

This prints:

57

---
### Return by address

**Return by address** works almost identically to return by reference, except a pointer to an object is returned instead of a reference to an object. Return by address has the same primary caveat as return by reference -- the object being returned by address must outlive the scope of the function returning the address, otherwise the caller will receive a dangling pointer.

The major advantage of return by address over return by reference is that we can have the function return `nullptr` if there is no valid object to return. For example, let’s say we have a list of students that we want to search. If we find the student we are looking for in the list, we can return a pointer to the object representing the matching student. If we don’t find any students matching, we can return `nullptr` to indicate a matching student object was not found.

The major disadvantage of return by address is that the caller has to remember to do a `nullptr` check before dereferencing the return value, otherwise a null pointer dereference may occur and undefined behavior will result. Because of this danger, return by reference should be preferred over return by address unless the ability to return “no object” is needed.

>[!Best practice]
Prefer return by reference over return by address unless the ability to return “no object” (using `nullptr`) is important.

---
### In parameters

>In most cases, a function parameter is used only to receive an input from the caller. Parameters that are used only for receiving input from the caller are sometimes called **in parameters**.

```cpp
#include <iostream>

void print(int x) // x is an in parameter
{
    std::cout << x << '\n';
}

void print(const std::string& s) // s is an in parameter
{
    std::cout << s << '\n';
}

int main()
{
    print(5);
    std::string s { "Hello, world!" };
    print(s);

    return 0;
}
```

In-parameters are typically passed by value or by const reference.

---
### Out parameters

A function argument passed by non-const reference (or by pointer-to-non-const) allows the function to modify the value of an object passed as an argument. This provides a way for a function to return data back to the caller in cases where using a return value is not sufficient for some reason.

>A function parameter that is used only for the purpose of returning information back to the caller is called an **out parameter**.

For example:

```cpp
#include <cmath>    // for std::sin() and std::cos()
#include <iostream>

// sinOut and cosOut are out parameters
void getSinCos(double degrees, double& sinOut, double& cosOut)
{
    // sin() and cos() take radians, not degrees, so we need to convert
    constexpr double pi { 3.14159265358979323846 }; // the value of pi
    double radians = degrees * pi / 180.0;
    sinOut = std::sin(radians);
    cosOut = std::cos(radians);
}

int main()
{
    double sin { 0.0 };
    double cos { 0.0 };

    double degrees{};
    std::cout << "Enter the number of degrees: ";
    std::cin >> degrees;

    // getSinCos will return the sin and cos in variables sin and cos
    getSinCos(degrees, sin, cos);

    std::cout << "The sin is " << sin << '\n';
    std::cout << "The cos is " << cos << '\n';

    return 0;
}
```

---
### Out parameters have an unnatural usage syntax

```cpp
void getByReference(int& x) { x = 5; }
```

Here, `x` is an out-parameter: the function puts a value in it for the caller.

#### **Why it’s “unnatural” compared to return-by-value**

The author’s point is that **using out-parameters requires extra ceremony from the caller**, unlike return-by-value.

##### **1. Extra variable setup**

If you return by value:

```cpp
int x{ getByValue() };   // directly initialize
std::cout << getByValue();
```

You can:

- Initialize variables in one step
    
- Or use the return value directly in an expression
    

If you use an out-parameter:

```cpp
int y{};           // must declare a mutable variable first
getByReference(y); // call function to fill it
std::cout << y;    // now you can use it
```

You **can’t**:

- Pass a temporary
    
- Skip creating a variable ahead of time
    

##### **2. No temporaries allowed**

Out-parameters are usually **non-const references**, so:

```cpp
getByReference(10); // ❌ error — 10 is an rvalue, not an lvalue
```

You _must_ give it a named, modifiable object — you can’t just say “write it into this temporary value in place”.

##### **3. Less expression-friendly**

Because the out-parameter gets filled during the call, you can’t use it directly inline:

```cpp
std::cout << getByValue();   // ✅ nice and compact
std::cout << getByReference(y); // ❌ doesn’t even compile (void return)
```

You have to break it into:

```cpp
int y{};
getByReference(y);
std::cout << y;
```

This makes the call feel more “manual” and verbose.

##### **4. No `const` safety**

Since the whole point of an out-parameter is mutation, the caller **can’t** pass a `const` object:

```cpp
const int z{};
getByReference(z); // ❌ error — can't write to const
```

So you lose the ability to enforce immutability.

####  **Why return-by-value feels more natural**

- Lets you write compact, single-line expressions
    
- Works with temporaries and constants
    
- Cleaner and more composable
    
- Allows compiler optimizations like RVO (return value optimization), so there’s usually no performance penalty

---
### Out-parameters by reference don’t make it obvious the arguments will be modified

When we assign a function’s return value to an object, it is clear that the value of the object is being modified:

```cpp
x = getByValue(); // obvious that x is being modified
```

This is good, as it makes it clear that we should expect the value of `x` to change.

However, let’s take a look at the function call to `getSinCos()` in the example above again:

```cpp
getSinCos(degrees, sin, cos);
```

It is not clear from this function call that `degrees` is an in parameter, but `sin` and `cos` are out-parameters. If the caller does not realize that `sin` and `cos` will be modified, a semantic error will likely result.

Using pass by address instead of pass by reference can in some case help make out-parameters more obvious by requiring the caller to pass in the address of objects as arguments.

Consider the following example:

```cpp
void foo1(int x);  // pass by value
void foo2(int& x); // pass by reference
void foo3(int* x); // pass by address

int main()
{
    int i{};

    foo1(i);  // can't modify i
    foo2(i);  // can modify i (not obvious)
    foo3(&i); // can modify i

    int *ptr { &i };
    foo3(ptr); // can modify i (not obvious)

    return 0;
}
```

Notice that in the call to `foo3(&i)`, we have to pass in `&i` rather than `i`, which helps make it clearer that we should expect `i` to be modified.

However, this is not fool-proof, as `foo3(ptr)` allows `foo3()` to modify `i` and does not require the caller to take the address-of `ptr`.

The caller may also think they can pass in `nullptr` or a null pointer as a valid argument when this is disallowed. And the function is now required to do null pointer checking and handling, which adds more complexity. This need for added null pointer handling often causes more issues than just sticking with pass by reference.

For all of these reasons, out-parameters should be avoided unless no other good options exist.

>[!Best practice]
Avoid out-parameters (except in the rare case where no better options exist).
Prefer pass by reference for non-optional out-parameters.

---
### In/out parameters

In rare cases, a function will actually use the value of an out-parameter before overwriting its value. Such a parameter is called an **in-out parameter**. In-out-parameters work identically to out-parameters and have all the same challenges.

Example:

- **Out-parameter**:  
    The function **doesn’t care about the initial value** passed in — it just **writes a new value** into it for the caller.
    
```cpp
void getByReference(int& x) { x = 5; } // ignores original value
```
    
- **In-out parameter**:  
    The function **both reads the current value** _and_ **writes a new value** back into it.
    
```cpp
void doubleAndIncrement(int& x) {
    x = (x * 2) + 1; // uses old value, then updates
}
```

---
### Difference between in, out and in-out parameters

####  **In Parameters**

- **Purpose**: Pass information **into** a function.
    
- **Behavior**: The function _reads_ the parameter but does **not modify** it (or at least shouldn’t).
    
- **Typical Implementation**:
    
    - Passed **by value** (makes a copy) if the type is small.
        
    - Passed **by const reference** (`const T&`) if the type is large or expensive to copy.
        
- **Example**:
    


```cpp
void printValue(const std::string& name) {
    std::cout << name << '\n';
}

```

Here, `name` is only used for reading, not changing.

#### 2. **Out Parameters**

- **Purpose**: Return additional data **from** a function to the caller.
    
- **Behavior**: The function ignores the current value of the argument and **assigns** a new value to it.
    
- **Typical Implementation**:
    
    - Passed **by non-const reference** (`T&`) or pointer (`T*`).
        
    - Caller must supply a variable to hold the output.
        
- **Example**:
    

```cpp
void getCoordinates(int& x, int& y) { 
    x = 10;
    y = 20;
}

int main() {
    int a, b;
    getCoordinates(a, b); // after call: a=10, b=20
}

```

Here, the function doesn’t care about the old values of `a` and `b`.

#### 3. **In-Out Parameters**

- **Purpose**: Pass a value into the function **and** get a possibly updated value back.
    
- **Behavior**: Function may **read** the parameter first, then **modify** it.
    
- **Typical Implementation**:
    
    - Passed **by non-const reference** (`T&`) or pointer (`T*`).
        
- **Example**:
    

```cpp
void doubleIfPositive(int& num) {
    if (num > 0) {   // using the input
        num *= 2;    // modifying the input
    }
}

int main() {
    int x = 5;
    doubleIfPositive(x); // after call: x=10
}

```

Here, `num` is both read and written to.

## 🔍 Key Differences Table

|Parameter Type|Reads Input?|Writes Output?|`const` Allowed?|
|---|---|---|---|
|**In**|✅ Yes|❌ No|✅ Often `const`|
|**Out**|❌ No|✅ Yes|❌ No|
|**In-Out**|✅ Yes|✅ Yes|❌ No|

---
### When to pass by non-const reference

>If you’re going to pass by reference in order to avoid making a copy of the argument, you should almost always pass by const reference.

However, there are two primary cases where pass by non-const reference may be the better choice.

First, use pass by non-const reference when a parameter is an in-out-parameter. Since we’re already passing in the object we need back out, it’s often more straightforward and performant to just modify that object.

```cpp
void someFcn(Foo& inout)
{
    // modify inout
}

int main()
{
    Foo foo{};
    someFcn(foo); // foo modified after this call, may not be obvious

    return 0;
}
```

Giving the function a good name can help:

```cpp
void modifyFoo(Foo& inout)
{
    // modify inout
}

int main()
{
    Foo foo{};
    modifyFoo(foo); // foo modified after this call, slightly more obvious

    return 0;
}
```

The alternative is to pass the object by value or const reference instead (as per usual) and return a new object by value, which the caller can then assign back to the original object:

```cpp
Foo someFcn(const Foo& in)
{
    Foo foo { in }; // copy here
    // modify foo
    return foo;
}

int main()
{
    Foo foo{};
    foo = someFcn(foo); // makes it obvious foo is modified, but another copy made here

    return 0;
}
```

This has the benefit of using a more conventional return syntax, but requires making 2 extra copies (sometimes the compiler can optimize one of these copies away).

Second, use pass by non-const reference when a function would otherwise return an object by value to the caller, but making a copy of that object is _extremely_ expensive. Especially if the function is called many times in a performance-critical section of code.

```cpp
void generateExpensiveFoo(Foo& out)
{
    // modify out
}

int main()
{
    Foo foo{};
    generateExpensiveFoo(foo); // foo modified after this call

    return 0;
}
```

>That said, objects are rarely so expensive to copy that resorting to non-conventional methods of returning those objects is worthwhile.

---
### Type deduction with pointers, references, and const

>As we noted in type deduction chapter that auto keyword is used to determine type of object based on initializer and deduce it from that which compiler do, and that auto keywords drop the const and constexpr keyword so we have to add  them overself.

#### Type deduction drops references

==In addition to dropping const, type deduction will also drop references:==

```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref { getRef() }; // type deduced as std::string (not std::string&)

    return 0;
}
```

>In the above example, variable `ref` is using type deduction. Although function `getRef()` returns a `std::string&`, the reference qualifier is dropped, so the type of `ref` is deduced as `std::string`.

Just like with dropped `const`, if you want the deduced type to be a reference, you can reapply the reference at the point of definition:

```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref1 { getRef() };  // std::string (reference dropped)
    auto& ref2 { getRef() }; // std::string& (reference dropped, reference reapplied)

    return 0;
}
```

---
### Top-level const and low-level const

A **top-level const** is a const qualifier that applies to an object itself. For example:

```cpp
const int x;    // this const applies to x, so it is top-level
int* const ptr; // this const applies to ptr, so it is top-level
// references don't have a top-level const syntax, as they are implicitly top-level const
```

In contrast, a **low-level const** is a const qualifier that applies to the object being referenced or pointed to:

```cpp
const int& ref; // this const applies to the object being referenced, so it is low-level
const int* ptr; // this const applies to the object being pointed to, so it is low-level
```

A reference to a const value is always a low-level const. A pointer can have a top-level, low-level, or both kinds of const:

```cpp
const int* const ptr; // the left const is low-level, the right const is top-level
```

====When we say that type deduction drops const qualifiers, it only drops top-level consts. Low-level consts are not dropped. We’ll see examples of this in just a moment.====

---
### Type deduction and const references

If the initializer is a reference to const, the reference is dropped first (and then reapplied if applicable), and then any top-level const is dropped from the result.

```cpp
#include <string>

const std::string& getConstRef(); // some function that returns a reference to const

int main()
{
    auto ref1{ getConstRef() }; // std::string (reference dropped, then top-level const dropped from result)

    return 0;
}
```

In the above example, since `getConstRef()` returns a `const std::string&`, the reference is dropped first, leaving us with a `const std::string`. This const is now a top-level const, so it is also dropped, leaving the deduced type as `std::string`.

>[!Important]
>Dropping a reference may change a low-level const to a top-level const: `const std::string&` is a low-level const, but dropping the reference yields `const std::string`, which is a top-level const.

--> Example:

#### Step 1 — Quick recap of the function

```cpp
`const std::string& getConstRef();`
```

- Returns a **const reference** to a `std::string`.
    
- That **const** is **low-level const** because it applies to what the reference points to (the string), not to the reference itself.
    

#### Step 2 — The four cases

#####  **Case 1:**

```cpp
`auto ref1{ getConstRef() }; // std::string`
```

- `auto` **drops references** during deduction.
    
- After dropping the `&`, the `const` becomes **top-level const** (because the reference is gone).
    
- Top-level const is **also dropped** during `auto` deduction.
    
- **Result:** `auto` deduces `std::string` (a copy of the string).
    

##### **Case 2:**

```cpp
`const auto ref2{ getConstRef() }; // const std::string`
```

- Works just like **ref1**: reference dropped, const becomes top-level, and is dropped.
    
- But **you** reapply `const` yourself.
    
- **Result:** `const std::string` (a const copy).
    

##### **Case 3:**

```cpp
`auto& ref3{ getConstRef() }; // const std::string&`
```

- If you put `&` after `auto`, deduction keeps the reference type.
    
- This means the `const` is still **low-level const** (because it applies to the string being referred to, not the reference).
    
- Low-level const is **not dropped**.
    
- **Result:** `const std::string&`.


##### **Case 4:**

```cpp
`const auto& ref4{ getConstRef() }; // const std::string&`
```

- Very similar to **ref3** — reference kept, low-level const preserved.
    
- Adding the `const` here is **redundant** because the type is already `const std::string&`.
    
- But writing it makes your intent **explicit** (best practice for clarity).
    

#### Step 3 — Top-level vs Low-level const

This is the key to understanding why `const` sometimes “vanishes” and sometimes stays.

|Const Level|Applies To…|Dropped in `auto`?|
|---|---|---|
|**Top-level const**|The object itself (when not a reference)|✅ Dropped|
|**Low-level const**|The object being pointed/ref'd to|❌ Kept|

>[!Best Practice]
>If you want a const reference, reapply the `const` qualifier even when it’s not strictly necessary, as it makes your intent clear and helps prevent mistakes.

---
### What about constexpr references?

Constexpr is not part of an expression’s type, so it is not deduced by `auto`.

==When defining a const reference (e.g. `const int&`), the const applies to the object being referenced, not the reference itself.
When defining a constexpr reference to a const variable (e.g. `constexpr const int&`), we need to apply both `constexpr` (which applies to the reference) and `const` (which applies to the type being referenced).

```cpp
#include <string_view>
#include <iostream>

constexpr std::string_view hello { "Hello" };   // implicitly const

constexpr const std::string_view& getConstRef() // function is constexpr, returns a const std::string_view&
{
    return hello;
} // note return type is `const std::string_view&` and constexpr is not!

int main()
{
    auto ref1{ getConstRef() };                  // std::string_view (reference dropped and top-level const dropped)
    constexpr auto ref2{ getConstRef() };        // constexpr const std::string_view (reference dropped and top-level const dropped, constexpr applied, implicitly const)

    auto& ref3{ getConstRef() };                 // const std::string_view& (reference reapplied, low-level const not dropped)
    constexpr const auto& ref4{ getConstRef() }; // constexpr const std::string_view& (reference reapplied, low-level const not dropped, constexpr applied)

    return 0;
}
```

#### **Case 1**

```cpp
auto ref1{ getConstRef() };
```

- **Reference dropped** → becomes `const std::string_view` (top-level const now).
    
- **Top-level const dropped** in `auto` deduction → result: `std::string_view` (copy, not const).
    
- `ref1` is a runtime variable with no constexpr-ness.
    

✅ **Final type:** `std::string_view`

>[!Rule]
>> A variable declared `constexpr` is **const**.

####  **Case 2**

```cpp
constexpr auto ref2{ getConstRef() };
```

- Same deduction as **ref1**: drops reference, drops top-level const → `std::string_view`.
    
- `constexpr` variable = `const` automatically, so we get:
    

✅ **Final type:** `constexpr const std::string_view` (compile-time constant, implicitly const).

#### **Case 3**

```cpp
auto& ref3{ getConstRef() };
```

- You explicitly add `&` → keeps the reference.
    
- Low-level const is **not** dropped in `auto` deduction.
    
- **Result:** `const std::string_view&` (runtime reference to `hello`, can’t modify it).
    

✅ **Final type:** `const std::string_view&`

#### **Case 4**

```cpp
constexpr const auto& ref4{ getConstRef() };
```

- Keeps the reference (because of `&`).
    
- Keeps the low-level const (because references keep it).
    
- `constexpr` applies → this reference can be used in compile-time expressions.
    
- The extra `const` is **redundant** because the type was already `const std::string_view&`, but it makes intent explicit.
    

✅ **Final type:** `constexpr const std::string_view&`

---
### Type deduction and pointers

Unlike references, type deduction does not drop pointers:

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() }; // std::string*

    return 0;
}
```

We can also use an asterisk in conjunction with pointer type deduction (`auto*`) to make it clearer that the deduced type is a pointer:

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() };  // std::string*
    auto* ptr2{ getPtr() }; // std::string*

    return 0;
}
```

The reason that references are dropped during type deduction but pointers are not dropped is because references and pointers have different semantics.

When we evaluate a reference, we’re really evaluating the object being referenced. Therefore, when deducing a type, it makes sense that we should deduce the type of the thing being referenced, not the reference itself. Also, since we deduce a non-reference, it’s really easy to make it a reference by using `auto&`. If type deduction were to deduce a reference instead, the syntax for removing a reference if we didn’t want it is much more complicated.

On the other hand, pointers hold the address of an object. When we evaluate a pointer, we are evaluating the pointer, not the object being pointed to (if we want that, we can dereference the pointer). Therefore, it makes sense that we should deduce the type of the pointer, not the thing being pointed to.

---
---> 

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr3{ *getPtr() };      // std::string (because we dereferenced getPtr())
    auto* ptr4{ *getPtr() };     // does not compile (initializer not a pointer)

    return 0;
}
```

---
### Type deduction and const pointers

```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    const auto ptr1{ getPtr() };  // std::string* const
    auto const ptr2 { getPtr() }; // std::string* const

    const auto* ptr3{ getPtr() }; // const std::string*
    auto* const ptr4{ getPtr() }; // std::string* const

    return 0;
}
```

>When we use either `auto const` or `const auto`, we’re saying, “make the deduced pointer a const pointer”. So in the case of `ptr1` and `ptr2`, the deduced type is `std::string*`, and then const is applied, making the final type `std::string* const`. This is similar to how `const int` and `int const` mean the same thing.

However, when we use `auto*`, the order of the const qualifier matters. A `const` on the left means “make the deduced pointer a pointer to const”, whereas a `const` on the right means “make the deduced pointer type a const pointer”. Thus `ptr3` ends up as a pointer to const, and `ptr4` ends up as a const pointer.

>Now let’s look at an example where the initializer is a const pointer to const.

```cpp
#include <string>

int main()
{
    std::string s{};
    const std::string* const ptr { &s };

    auto ptr1{ ptr };  // const std::string*
    auto* ptr2{ ptr }; // const std::string*

    auto const ptr3{ ptr };  // const std::string* const
    const auto ptr4{ ptr };  // const std::string* const

    auto* const ptr5{ ptr }; // const std::string* const
    const auto* ptr6{ ptr }; // const std::string*

    const auto const ptr7{ ptr };  // error: const qualifer can not be applied twice
    const auto* const ptr8{ ptr }; // const std::string* const

    return 0;
}
```

>The `ptr5` and `ptr6` cases are analogous to the cases we showed in the prior example. In both cases, the top-level const is dropped. For `ptr5`, the `auto* const` reapplies the top-level const, so the final type is `const std::string* const`. For `ptr6`, the `const auto*` applies const to the type being pointed to (which in this case was already const), so the final type is `const std::string*`.

>In the `ptr7` case, we’re applying the const qualifier twice, which is disallowed, and will cause a compile error.

>And finally, in the `ptr8` case, we’re applying const on both sides of the pointer (which is allowed since `auto*` must be a pointer type), so the resulting types is `const std::string* const`.

>[!Best Practice]
>If you want a const pointer, pointer to const, or const pointer to const, reapply the `const` qualifier(s) even when it’s not strictly necessary, as it makes your intent clear and helps prevent mistakes.

>[!Tip]
>Consider using `auto*` when deducing a pointer type. Using `auto*` in this case makes it clearer that we are deducing a pointer type, enlists the compiler’s help to ensure we don’t deduce a non-pointer type, and gives you more control over const.

---
### Summary

Top-level vs low-level const:

- A top-level const applies to the object itself (e.g. `const int x` or `int* const ptr`).
- A low-level const applies to the object accessed through a reference or pointer (e.g. `const int& ref`, `const int* ptr`).

What type deduction deduces:

- Type deduction first drops any references (unless the deduced type is defined as a reference). For a const reference, dropping the reference will cause the (low-level) const to become a top-level const.
- Type deduction then drops any top-level const (unless the deduced type is defined as `const` or `constexpr`).
- Constexpr is not part of the type system, so is never deduced. It must always be explicitly applied to the deduced type.
- Type deduction does not drop pointers.
- Always explicitly define the deduced type as a reference, `const`, or `constexpr` (as applicable), and even if these qualifiers are redundant because they would be deduced. This helps prevent errors and makes it clear what your intent is.

Type deduction and pointers:

- When using `auto`, the deduced type will be a pointer only if the initializer is a pointer. When using `auto*`, the deduced type is always a pointer, even if the initializer is not a pointer.
- `auto const` and `const auto` both make the deduced pointer a const pointer. There is no way to explicitly specify a low-level const (pointer-to-const) using `auto`.
- `auto* const` also makes the deduced pointer a const pointer. `const auto*` makes the deduced pointer a pointer-to-const. If these are hard to remember, `int* const` is a const pointer (to int), so `auto* const` must be a const pointer. `const int*` is a pointer-to-const (int), so `const auto*` must be a pointer-to-const)
- Consider using `auto*` over `auto` when deducing a pointer type, as it allows you to explicitly reapply both the top-level and low-level const, and will error if a pointer type is not deduced.

---
