
# The hidden “this” pointer and member function chaining

### 🔑 The `this` Pointer in C++

### Problem

When we call a member function on an object, e.g.:

```cpp
Simple simple{1};
simple.setID(2);
```

How does C++ know that `m_id` inside `setID()` belongs to `simple` and not some other object?

#### Solution: The Hidden `this` Pointer

- Every **non-static member function** in C++ has access to a hidden pointer named **`this`**.
    
- `this` is a pointer to the object that invoked the function.
    
- So:
    
    - If `a.setID(5)` is called → inside the function, `this == &a`.
        
    - If `b.setID(5)` is called → inside the function, `this == &b`.

#### Implicit vs Explicit Use

These two are equivalent:

```cpp
void print() const { std::cout << m_id; }        // implicit
void print() const { std::cout << this->m_id; }  // explicit
```

- `m_id` is shorthand for `this->m_id`.
    
- Compiler automatically prefixes member accesses with `this->`.

#### How the Compiler Rewrites Calls

When we write:

```cpp
simple.setID(2);
```

The compiler translates it into:

```cpp
Simple::setID(&simple, 2);
```

And the function definition:

```cpp
void setID(int id) { m_id = id; }
```

is rewritten internally as:

```cpp
static void setID(Simple* const this, int id) {
    this->m_id = id;  // same as (*this).m_id
}
```

#### Step-by-Step

1. `simple.setID(2);`
    
2. Compiler rewrites → `Simple::setID(&simple, 2);`
    
3. Inside the function: `this == &simple`
    
4. Member access → `this->m_id = id;` → becomes `simple.m_id = id;`

#### Special Case: Static Functions

- **Static member functions** do **not** have a `this` pointer.
    
- They are not tied to any particular object; they behave like normal functions inside the class.

#### ✅ Key Insights

- All **non-static member functions** have a hidden `this` pointer.
    
- `this` holds the address of the object that invoked the function.
    
- `m_id` is shorthand for `this->m_id`.
    
- `obj.func(args)` is internally rewritten as `Class::func(&obj, args)`.

### `this` always points to the object being operated on

>New programmers are sometimes confused about how many `this` pointers exist. Each member function has a single `this` pointer parameter that points to the implicit object. Consider:

```cpp
int main()
{
    Simple a{1}; // this = &a inside the Simple constructor
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()
    b.setID(4); // this = &b inside member function setID()

    return 0;
}
```

Note that the `this` pointer alternately holds the address of object `a` or `b` depending on whether we’ve called a member function on object `a` or `b`.

Because `this` is just a function parameter (and not a member), it does not make instances of your class larger memory-wise.

### Explicitly referencing `this`

>Most of the time, you won’t need to explicitly reference the `this` pointer. However, there are a few occasions where doing so can be useful:

First, if you have a member function that has a parameter with the same name as a data member, you can disambiguate them by using `this`:

```cpp
struct Something
{
    int data{}; // not using m_ prefix because this is a struct

    void setData(int data)
    {
        this->data = data; // this->data is the member, data is the local parameter
    }
};
```

This `Something` class has a member named `data`. The function parameter of `setData()` is also named `data`. Within the `setData()` function, `data` refers to the function parameter (because the function parameter shadows the data member), so if we want to reference the `data` member, we use `this->data`.

Some developers prefer to explicitly add `this->` to all class members to make it clear that they are referencing a member. We recommend that you avoid doing so, as it tends to make your code less readable for little benefit. Using the “m_” prefix is a more concise way to differentiate private member variables from non-member (local) variables.

### Returning `*this`

#### 🔑 Returning `*this` (Method Chaining in C++)

### Problem

Sometimes we want to call multiple member functions on the **same object** in a single expression, instead of writing separate lines. This technique is called **method chaining**.

Example with `std::cout`:

```cpp
std::cout << "Hello, " << userName;
```

Actually works like:

```cpp
(std::cout << "Hello, ") << userName;
```

- Each `operator<<` prints something **and returns `std::cout`**, allowing the next `<<` to continue chaining.
    
- If `operator<<` returned `void`, chaining would not be possible.

#### Normal Class Example (without chaining)

```cpp
class Calc {
private:
    int m_value{};
public:
    void add(int v) { m_value += v; }
    void sub(int v) { m_value -= v; }
    void mult(int v) { m_value *= v; }
    int getValue() const { return m_value; }
};
```

Usage:

```cpp
Calc c{};
c.add(5);   // void
c.sub(3);   // void
c.mult(4);  // void

std::cout << c.getValue() << '\n';
```

Here, each function returns `void`, so we must call them on separate lines.

#### Solution: Return `*this` by Reference

We can return the **implicit object (`*this`)** instead of `void`:

```cpp
class Calc {
private:
    int m_value{};
public:
    Calc& add(int v)  { m_value += v; return *this; }
    Calc& sub(int v)  { m_value -= v; return *this; }
    Calc& mult(int v) { m_value *= v; return *this; }
    int getValue() const { return m_value; }
};
```

Now usage becomes:

```cpp
Calc c{};
c.add(5).sub(3).mult(4); // method chaining

std::cout << c.getValue() << '\n'; // prints 8
```

#### Step-by-Step of Chaining

1. `c.add(5)` runs → modifies `m_value` → returns reference to `c`.
    
2. Returned object is `c`, so `.sub(3)` runs on the same object.
    
3. `.mult(4)` then runs on the same object again.
    
4. Final result = `(((0 + 5) - 3) * 4) = 8`.

#### Key Notes

- **Return type must be a reference (`ClassName&`)**, not a copy, otherwise chaining may operate on temporary objects instead of the original.
    
- Returning `*this` allows **compact, readable, fluent syntax**.
    
- This is the most common **explicit use of `this`** in real programs.
    
- `this` always points to a valid object when inside a member function, so dereferencing it is safe (no null check needed).
    

#### ✅ Key Insight

Returning `*this` by reference enables **method chaining**, letting us call multiple functions on the same object in a single expression.

### Resetting a class back to default state

If your class has a default constructor, you may be interested in providing a way to return an existing object back to its default state.

As noted in previous lessons ([14.12 -- Delegating constructors](https://www.learncpp.com/cpp-tutorial/delegating-constructors/)), constructors are only for initialization of new objects, and should not be called directly. Doing so will result in unexpected behavior.

The best way to reset a class back to a default state is to create a `reset()` member function, have that function create a new object (using the default constructor), and then assign that new object to the current implicit object, like this:

```cpp
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}
```

Here’s a full program demonstrating this `reset()` function in action:

```cpp
#include <iostream>

class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }

    void reset() { *this = {}; }
};


int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4);

    std::cout << calc.getValue() << '\n'; // prints 8

    calc.reset();

    std::cout << calc.getValue() << '\n'; // prints 0

    return 0;
}
```

### `this` and const objects

>For non-const member functions, `this` is a const pointer to a non-const value (meaning `this` cannot be pointed at something else, but the object pointing to may be modified). With const member functions, `this` is a const pointer to a const value (meaning the pointer cannot be pointed at something else, nor may the object being pointed to be modified).

#### Type of `this`

1. In a **non-const member function**:

```cpp
void func();
```

The type of `this` is:

```cpp
ClassName* const this;
```

- `this` is a **const pointer** (can’t point somewhere else)
    
- but it points to a **non-const object** (so members can be modified).

2. In a **const member function**:

```cpp
void func() const;
```

	The type of `this` is:

```cpp
const ClassName* const this;
```

- `this` is still a const pointer,
    
- but now it points to a **const object** (so members cannot be modified).

#### The Problem

Suppose we have:

```cpp
class Example {
public:
    void nonConstFunc() { /* modifies object */ }
    void constFunc() const { /* read-only */ }
};
```

And we call:

```cpp
const Example e{};
e.nonConstFunc();  // ❌ error
```

- Here, `e` is a **const object**.
    
- The implicit argument passed is of type:

```cpp
const Example* const
```

But `nonConstFunc` expects `this` to be:

```cpp
Example* const
```

- This would require converting a **pointer-to-const** (`const Example*`) into a **pointer-to-non-const** (`Example*`), which **discards const**.
    
- C++ does **not allow this conversion implicitly**, because it would break const-correctness (a `const` object could be modified).

#### The Compiler Error

Different compilers phrase it differently, but essentially the error says:

> “You are trying to call a non-const function on a const object. This requires discarding the const qualifier on the object.”

#### ✅ The Fix

Mark the function as `const` if it does not modify the object:

```cpp
class Example {
public:
    void nonConstFunc() { /* modifies object */ }
    void constFunc() const { /* read-only */ }
};
```

Now:

```cpp
const Example e{};
e.constFunc();   // ✅ works
e.nonConstFunc(); // ❌ still illegal
```

#### 🔑 Key Insight

- The `this` pointer type depends on the function:
    
    - Non-const function → `ClassName* const this`
        
    - Const function → `const ClassName* const this`
        
- You **cannot call a non-const function on a const object**, because that would require discarding `const`.
    
- To make a function callable on const objects, mark it as `const`.

### Why `this` a pointer and not a reference

>Since the `this` pointer always points to the implicit object (and can never be a null pointer unless we’ve done something to cause undefined behavior), you may be wondering why `this` is a pointer instead of a reference. The answer is simple: when `this` was added to C++, references didn’t exist yet.

If `this` were added to the C++ language today, it would undoubtedly be a reference instead of a pointer. In other more modern C++-like languages, such as Java and C#, `this` is implemented as a reference.

---
# Classes and header files

### 🔑 Defining Member Functions Inside vs Outside a Class

#### 1. Defining Functions Inside the Class

In simple cases, we can define all member functions **inside** the class body:

```cpp
class Date {
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day)     // constructor
        : m_year{ year }, m_month{ month }, m_day{ day }
    {
    }

    void print() const { 
        std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n"; 
    }

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};
```

Usage:

```cpp
Date d{2015, 10, 14};
d.print();   // prints Date(2015, 10, 14)
```

👉 This works fine for **small/simple classes**.  
But as classes grow larger, keeping all definitions inside can **clutter the interface** and make it harder to see what’s important for users of the class.

#### 2. Splitting Declaration and Definition

C++ allows separating:

- **Declaration** (inside the class → what the function looks like).
    
- **Definition** (outside the class → how the function works).
    

#### Example:

```cpp
class Date {
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day); // declaration only
    void print() const;                 // declaration only

    // short one-line functions often stay inside
    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};
```

Definitions outside:

```cpp
Date::Date(int year, int month, int day)   // definition
    : m_year{ year }, m_month{ month }, m_day{ day }
{
}

void Date::print() const                   // definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
}
```

Usage:

```cpp
Date d{2015, 10, 14};
d.print();
```

#### 3. Important Notes

- When defining functions **outside the class**, you must prefix the function name with the **class scope**:

```cpp
ReturnType ClassName::functionName(...) { ... }
```

- Example: `void Date::print() const { ... }`
    
- This tells the compiler that the function belongs to the class, not a free function.
    

#### 4. Which Functions Should Stay Inside?

- **Accessors (getters)** and other very short, one-line functions are usually kept **inside** the class definition → keeps code concise.
    
- Longer, more complex functions are usually moved **outside** to keep the class definition clean and easy to read.
    

#### ✅ Key Insight

- **Inside the class** = simple, quick to read, but can get messy for large classes.
    
- **Outside the class** = cleaner interface (users only see function names, not implementations).
    
- Prefix with `ClassName::` when defining functions outside the class.

### Putting class definitions in a header file

If you define a class inside a source (.cpp) file, that class is only usable within that particular source file. In larger programs, it’s common that we’ll want to use the classes we write in multiple source files.

In lesson [2.11 -- Header files](https://www.learncpp.com/cpp-tutorial/header-files/), you learned that you can put function declarations in a header files. Then you can #include those functions declarations into multiple code files (or even multiple projects). Classes are no different. A class definitions can be put in a header files, and then #included into any other files that want to use the class type.

Unlike functions, which only need a forward declaration to be used, the compiler typically needs to see the full definition of a class (or any program-defined type) in order for the type to be used. This is because the compiler needs to understand how members are declared in order to ensure they are used properly, and it needs to be able to calculate how large objects of that type are in order to instantiate them. So our header files usually contain the full definition of a class rather than just a forward declaration of the class.

### Naming your class header and code files

#### 1. Why split into `.h` and `.cpp`?

- As classes get larger, we don’t want **all definitions** cluttering the class interface.
    
- C++ best practice is to **separate class declarations and definitions** into two files:
    
    - **Header file (`.h`)** → contains the class declaration (blueprint).
        
    - **Source file (`.cpp`)** → contains function definitions (implementation).

#### 2. Example: Splitting the `Date` Class

**`Date.h`** (class declaration):

```cpp
#ifndef DATE_H   // include guard start
#define DATE_H

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day); // declaration only
    void print() const;                 // declaration only

    // trivial functions can stay inline
    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

#endif  // include guard end
```

**`Date.cpp`** (definitions/implementation):

```cpp
#include "Date.h"
#include <iostream>

Date::Date(int year, int month, int day)
    : m_year{ year }, m_month{ month }, m_day{ day }
{
}

void Date::print() const
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
}
```

#### 3. How It Works

- Any other file that wants to use `Date` just writes:

```cpp
#include "Date.h"
```

The compiler needs both:

- `Date.h` (so it knows the class layout + declarations).
    
- `Date.cpp` compiled and linked (so function calls have actual code to run).

#### 4. Best Practices

✔ **Header file (`.h`)**

- Use the **same name as the class** (`Date.h` for `Date`).
    
- Put the **class definition** (data members + function declarations).
    
- Define only **trivial one-liners** (e.g., getters, simple constructors).
    

✔ **Source file (`.cpp`)**

- Also use the **same name as the class** (`Date.cpp`).
    
- Put **non-trivial function definitions** here.
    
- Always `#include "Date.h"` at the top.

#### ✅ Key Insight

- **Header = What the class looks like** (interface).
    
- **Source = How the class works** (implementation).
    
- This makes projects organized, avoids clutter, and keeps code easier to read and maintain.

### 📘 Does Defining a Class in a Header File Violate the One-Definition Rule (ODR)?

#### 🔹 The One-Definition Rule (ODR)

- In C++, most things (like functions, variables) must have **exactly one definition** across the entire program.
    
- If you define the same function or variable in multiple translation units, the linker throws an error.

#### 🔹 What About Classes?

- **Types (like classes)** are **exempt** from the "only one definition per program" part of the ODR.
    
    - ✅ You can safely `#include` a class definition in multiple files.
        
    - ❌ But including the same class definition more than once in a _single file_ **is an ODR violation**.
        
    - Solution → Use **include guards** (`#ifndef … #define … #endif`) or `#pragma once`.

#### 🔹 Member Functions

- **Functions are NOT exempt from ODR** → each function definition must exist only once in the entire program.
    

1. **Functions defined inside the class**
    
    - They are **implicitly `inline`**.
        
    - Inline functions are allowed to appear in multiple translation units without violating ODR.
        
2. **Functions defined outside the class**
    
    - They are **NOT inline by default**.
        
    - To avoid ODR violations:
        
        - Either put them in a `.cpp` file (so there’s only one definition).
            
        - Or mark them `inline` in the header if you bdwant them inlined and usable across bdmultiple files.

#### 🔹 Example (`Date.h` with inline functions)

```cpp
#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day); // declaration
    void print() const;                 // declaration
};

inline Date::Date(int year, int month, int day) // definition made inline
    : m_year{ year }, m_month{ month }, m_day{ day }
{
}

inline void Date::print() const // definition made inline
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
}

#endif

```

Since the constructor and `print()` are marked `inline`, this header can be included in multiple `.cpp` files safely.

#### 🔹 Why Not Put _Everything_ in the Header?

- ✅ Compiles fine, but…
    

1. **Clutters the class definition** → harder to read.
    
2. **Recompilation cost** → if you edit a header, _every file that includes it_ must recompile.
    
    - Changing only a `.cpp` file triggers recompilation of _just that file_.
        
3. **Project organization** → keeping non-trivial code in `.cpp` files makes codebases cleaner.

#### 🔹 Exceptions (When You Might Put Everything in a Header)

1. Small, single-use classes (only used in one `.cpp`).
    
2. Classes with very few non-trivial functions.
    
3. **Header-only libraries** → everything goes in the header (all functions `inline`).
    
4. **Templates** → must be fully defined in headers (compiler needs full definition to generate code).

#### ✅ Key Takeaways

- **Classes in headers = okay** (types are ODR-exempt).
    
- **Functions in headers = must be inline** (unless trivial inside class).
    
- **Best practice** → class in header, non-trivial function definitions in `.cpp`.

### Inline expansion of member functions

>The compiler must be able to see a full definition of a function in order to perform inline expansion. Most often, such functions (e.g. access functions) are defined inside the class definition. However, if you want to define a member function outside the class definition, but still want it to be eligible for inline expansion, you can define it as an inline function just below the class definition (in the same header file). That way the definition of the function is accessible to anybody who #includes the header.

### Default arguments for member functions

>[!Best Practice]
>Put any default arguments for member functions inside the class definition.

### Libraries

Throughout your programs, you’ve used classes that are part of the standard library, such as `std::string`. To use these classes, you simply need to #include the relevant header (such as `#include <string>`). Note that you haven’t needed to add any code files (such as `string.cpp` or `iostream.cpp`) into your projects.

The header files provide the declarations that the compiler requires in order to validate that the programs you’re writing are syntactically correct. However, the implementations for the classes that belong to the C++ standard library are contained in a precompiled file that is linked in automatically at the link stage. You never see the code.

Many open source software packages provide both .h and .cpp files for you to compile into your program. However, most commercial libraries provide only .h files and a precompiled library file. There are several reasons for this: 1) It’s faster to link a precompiled library than to recompile it every time you need it, 2) A single copy of a precompiled library can be shared by many applications, whereas compiled code gets compiled into every executable that uses it (inflating file sizes), and 3) Intellectual property reasons (you don’t want people stealing your code).

We discuss how to include 3rd party precompiled libraries into your projects in the appendix.

While you probably won’t be creating and distributing your own libraries for a while, separating your classes into header files and source files is not only good form, it also makes creating your own custom libraries easier. Creating your own libraries is beyond the scope of these tutorials, but separating your declaration and implementation is a prerequisite to doing so if you want to distribute precompiled binaries.

---
