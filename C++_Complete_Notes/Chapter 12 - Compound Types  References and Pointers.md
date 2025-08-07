
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
