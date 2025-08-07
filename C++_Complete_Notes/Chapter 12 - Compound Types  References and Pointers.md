
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
