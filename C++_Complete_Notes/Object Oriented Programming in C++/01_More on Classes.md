
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
# Nested types (member types)

### Nested Types (Member Types) in C++

So far, we’ve seen two kinds of members inside a class:

- **Data members** → variables inside a class
    
- **Member functions** → functions inside a class
    

C++ also allows another kind of member: **nested types (member types)**.  
A **nested type** is a type (like `enum`, `struct`, `class`, or `using` alias) that is defined **inside a class**.

```cpp
#include <iostream>

class Fruit
{
public:
    // Nested enum type inside the class
    enum Type
    {
        apple,
        banana,
        cherry
    };

private:
    Type m_type {};
    int m_percentageEaten { 0 };

public:
    Fruit(Type type) : m_type { type } {}

    Type getType() { return m_type; }
    int getPercentageEaten() { return m_percentageEaten; }

    bool isCherry() { return m_type == cherry; } // No need for Fruit:: here
};

int main()
{
    Fruit apple { Fruit::apple }; // outside the class, we must use Fruit::

    if (apple.getType() == Fruit::apple)
        std::cout << "I am an apple";
    else
        std::cout << "I am not an apple";

    return 0;
}
```

#### Key Points

1. **Definition position**
    
    - Nested types must be fully defined before they are used.
        
    - That’s why they are usually placed **at the top of the class**.
        
    
    ✅ Best practice → Put nested types at the top of the class.

2. **Access control**

- Nested types follow the normal access rules:
    
    - If declared under `public:`, they are accessible outside the class.
        
    - If under `private:`, they can only be used inside the class.

3. **Scope rules**

- A class creates its own **scope region**, just like a namespace.
    
- So the **fully qualified name** of the nested type is `Fruit::Type`.
    
- The **fully qualified name** of an enumerator is `Fruit::apple`.

4. **Access inside vs outside the class**

- Inside the class → No need for the `Fruit::` prefix. Example: `m_type == cherry`.
    
- Outside the class → Must use the `Fruit::` prefix. Example: `Fruit::apple`.

5. **Why we renamed FruitType → Type**

- Writing `Fruit::Type` looks cleaner than `Fruit::FruitType`.
    
- It avoids redundancy.

6. **Scoped vs Unscoped enums**

- If we used a **scoped enum class**, we’d have to write `Fruit::Type::apple`.
    
- But since the class already provides a scope, an **unscoped enum** is simpler: `Fruit::apple`.

#### ✅ **Summary:**

- Nested types are types defined inside a class.
    
- They act like members and follow access control rules.
    
- The class scope makes their names qualified (`Fruit::Type`, `Fruit::apple`).
    
- Place them at the top of the class for clarity.
    
- Use unscoped enums if the class already provides a scope.

### Nested typedefs and type aliases

Class types can also contain nested typedefs or type aliases:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};

int main()
{
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() }; // must use fully qualified name outside class

    std::cout << john.getName() << " has id: " << id << '\n';

    return 0;
}
```

This prints:

John has id: 1

Note that inside the class we can just use `IDType`, but outside the class we must use the fully qualified name `Employee::IDType`.

### Nested Classes and Access to Outer Class Members

- **Definition**:  
    In C++, a class can contain another class inside it. The inner one is called a _nested class_.
    
- **Important Rule**:  
    A nested class **does not automatically get access** to the outer class’s `this` pointer.
    
    - This means it **cannot directly access** members of the outer class.
        
    - Reason: A nested class can exist independently of the outer class, so it may not have an outer object to reference.
        
- **But**:  
    Since the nested class is itself a _member_ of the outer class, it is allowed to access the **private members** of the outer class (if given an instance of the outer class).

```cpp
class Employee
{
public:
    using IDType = int;

    class Printer // nested class
    {
    public:
        void print(const Employee& e) const
        {
            // Can’t use outer `this`, but can access outer private members via object
            std::cout << e.m_name << " has id: " << e.m_id << '\n';
        }
    };

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name{ name }, m_id{ id }, m_wage{ wage }
    {
    }
};
```

Usage:

```cpp
const Employee john{ "John", 1, 45000 };
const Employee::Printer p{};
p.print(john); // Output: John has id: 1
```

#### Key Takeaways

1. **Nested classes do not have access** to the outer class’s `this`.
    
2. **But they can access outer private members** if they are given an object of the outer class.
    
3. **Common use case**: Iterators (e.g., `std::string::iterator`).

### Nested types and forward declarations

- **Nested types** are types (e.g., classes, structs, enums) declared inside another class.
    
- A **nested type can be forward declared** inside the enclosing class, and then defined:
    
    - Either **inside the enclosing class** later, or
        
    - **Outside of the enclosing class**.
        

✅ Example:

```cpp
class outer
{
public:
    class inner1;   // forward declaration (inside)
    class inner1 {}; // definition inside
    class inner2;   // forward declaration (inside)
};

class inner2 {}; // definition outside
```

**But**: You **cannot forward declare a nested type before the enclosing class is defined**.

```cpp
class outer;         // okay
class outer::inner1; // error! outer not defined yet
```
Same code as above:
```cpp
#include <iostream>

class outer;         // okay: can forward declare non-nested type
class outer::inner1; // error: can't forward declare nested type prior to outer class definition

class outer
{
public:
    class inner1{}; // note: nested type declared here
};

class outer::inner1; // okay (but redundant) since nested type has already been declared as part of outer class definition

int main()
{
    return 0;
}```

✅ Correct:

```cpp
class outer
{
public:
    class inner1 {};  // nested type declared here
};

class outer::inner1; // okay, but redundant
```

#### ⚡ **Key takeaway:**

- You can forward declare **nested types inside their enclosing class**.
    
- You **cannot** forward declare a nested type outside the enclosing class before the enclosing class is defined.
    
- Forward declarations **after** the enclosing class is defined are allowed but redundant.

---
# Introduction to destructors

```cpp
// This example won't compile because it is (intentionally) incomplete
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    n.sendData();

    return 0;
}```

### 1. The problem

The class `NetworkData` stores some data, and at some point you need to **send that data** before the object goes away.

- If the programmer **forgets to call** `sendData()`, the data will be lost when the object is destroyed.
    
- Even worse, sometimes the code **returns early** (like in the `someFunction` example), and `sendData()` is **skipped accidentally**.
    

So the responsibility of remembering to "clean up" (send, close, save, flush, etc.) is **on the user of the class** → which is risky and error-prone.

```cpp
bool someFunction()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    if (someCondition)
        return false;

    n.sendData();
    return true;
}
```

#### 2. The general pattern

This problem isn’t unique to networking:

- Files → must be closed.
    
- Database connections → must be released.
    
- Memory → must be freed.
    
- Locks → must be unlocked.
    

Anytime a class acquires some resource, it usually also has **cleanup requirements**.

#### 3. The key question

> “But why are we even requiring the user to ensure this? If the object is being destroyed, then we know that cleanup needs to be performed at that point. Should that cleanup happen automatically?”

The answer is **Yes** → this is where **destructors** come in.

C++ provides destructors, which are functions automatically called when an object goes out of scope (or is deleted). This is the perfect place to put cleanup logic.

That way:

- Even if the function returns early.
    
- Even if an exception is thrown.
    
- Even if the programmer forgets.
    

…the cleanup code **still runs automatically**.

```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
    NetworkData(std::string_view serverName)
        : m_serverName{ serverName }
    {
    }

    void addData(std::string_view data)
    {
        m_dataQueue.add(data);
    }

    void sendData()
    {
        // connect to server
        // send all data
        // clear data
    }

    ~NetworkData() // destructor
    {
        if (!m_dataQueue.empty())
            sendData();  // cleanup automatically
    }
};
```

Now cleanup **always happens**, because the destructor will call `sendData()` when the object is destroyed, no matter what path the function takes.

### Destructor naming

Like constructors, destructors have specific naming rules:

1. The destructor must have the same name as the class, preceded by a tilde (~).
2. The destructor can not take arguments.
3. The destructor has no return type.

A class can only have a single destructor.

>Destructors may safely call other member functions since the object isn’t destroyed until after the destructor executes.

### A destructor example

```cpp
#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```

This program produces the following result:

Constructing Simple 1
Constructing Simple 2
Destructing Simple 2
Destructing Simple 1

Note that when each `Simple` object is destroyed, the destructor is called, which prints a message. “Destructing Simple 1” is printed after “Destructing Simple 2” because `simple2` was destroyed before the end of the function, whereas `simple1` was not destroyed until the end of `main()`.

Remember that static variables (including global variables and static local variables) are constructed at program startup and destroyed at program shutdown.

### Improving the NetworkData program

Back to our example at the top of the lesson, we can remove the need for the user to explicitly call `sendData()` by having a destructor call that function:

```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	~NetworkData()
	{
		sendData(); // make sure all data is sent before object is destroyed
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    return 0;
}
```

With such a destructor, our `NetworkData` object will always send whatever data it has before the object is destroyed! The cleanup happens automatically, which means less chance for errors, and less things to think about.

### An implicit destructor

If a non-aggregate class type object has no user-declared destructor, the compiler will generate a destructor with an empty body. This destructor is called an implicit destructor, and it is effectively just a placeholder.

If your class does not need to do any cleanup on destruction, it’s fine to not define a destructor at all, and let the compiler generate an implicit destructor for your class.

### A warning about the `std::exit()` function

In lesson [8.12 -- Halts (exiting your program early)](https://www.learncpp.com/cpp-tutorial/halts-exiting-your-program-early/), we discussed the `std::exit()` function, can be used to terminate your program immediately. When the program is terminated immediately, the program just ends. Local variables are not destroyed first, and because of this, no destructors will be called. Be wary if you’re relying on your destructors to do necessary cleanup work in such a case.

### **Implicit Destructor in C++**

#### **1. What is an implicit destructor?**

- If you **don’t define a destructor**, the compiler will **automatically generate one** for you.
    
- This is called the **implicit destructor** (or compiler-generated destructor).

#### **2. Why are implicit destructors empty?**

- By default, most classes **don’t need any special cleanup**.
    
- If a class only contains **basic types** (like `int`, `double`, etc.), or objects of other classes that already know how to clean themselves up → no extra work is needed.
    
- The implicit destructor is essentially:

```cpp
~ClassName() { }
```

which means **“do nothing special”**.

#### **3. Why do we still use them?**

- Even though they look “empty”, implicit destructors still:  
    ✅ Destroy all member objects in the reverse order of their construction.  
    ✅ Call destructors of base classes automatically.
    
- This ensures **proper cleanup of members** without the programmer having to write anything.
    

Example:

```cpp
#include <iostream>
#include <string>

class A {
    std::string str{"Hello"}; // std::string has its own destructor
};

int main() {
    A obj;  // constructor called
}           // implicit destructor called → automatically destroys std::string
```

Here:

- `A` has no user-defined destructor.
    
- The compiler generates an implicit destructor.
    
- That destructor automatically calls the destructor of `std::string` to release its memory.

#### **4. When do we need to define our own destructor?**

- Only if the class manages **resources manually** (like raw `new`/`delete`, file handles, sockets, etc.).
    
- Otherwise, the implicit destructor is enough.

---
# Class templates with member functions

### Type template parameters in member functions

```cpp
#include <ios>       // for std::boolalpha
#include <iostream>

template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    // When we define a member function inside the class definition,
    // the template parameter declaration belonging to the class applies
    Pair(const T& first, const T& second)
        : m_first{ first }
        , m_second{ second }
    {
    }

    bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
    Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

    return 0;
}
```

#### 🔹 The Core Idea: _Type template parameters in member functions_

When you write a **class template** like:

```cpp
template <typename T>
class Pair
{
    T m_first{};
    T m_second{};
};
```

You are telling the compiler: _“This is not just one class, but a blueprint to generate multiple classes, each with `T` replaced by some actual type.”_

So:

- `Pair<int>` → a class with two `int`s
    
- `Pair<double>` → a class with two `double`s
    
- etc.
    

Since your **data members** (`m_first`, `m_second`) are of type `T`, any **member functions** you write must also know what `T` is.

That’s where **type template parameters in member functions** come in.

#### 🔹 Case 1: Defining functions _inside_ the class

```cpp
template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    Pair(const T& first, const T& second)
        : m_first{ first }, m_second{ second }
    {}

    bool isEqual(const Pair<T>& pair)   // ✅ no template redeclaration needed
    {
        return m_first == pair.m_first && m_second == pair.m_second;
    }
};
```

Here:

- The function is **inside** the template class.
    
- The function can directly use `T` because it already belongs to the class template.
    
- No need to redeclare `template <typename T>` again.

#### 🔹 Case 2: Defining functions _outside_ the class

```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
```

Why is `template <typename T>` needed again?

Because **outside of the class definition, the compiler has no context for what `T` is anymore**. You must “remind” it:

```cpp
template <typename T>  // redeclare template parameter list
bool Pair<T>::isEqual(const Pair<T>& pair) // fully qualify Pair<T>
```

If you wrote just `Pair::isEqual`, the compiler wouldn’t know which `Pair` (e.g., `Pair<int>`? `Pair<double>`?).

So:

- You resupply `template <typename T>`
    
- And you fully qualify it as `Pair<T>::function`

#### 🔹 CTAD (Class Template Argument Deduction)

```cpp
Pair p1{ 5, 6 };   // compiler infers this is Pair<int>
```

How does the compiler know `T = int`?

- It looks at the constructor: `Pair(const T&, const T&)`
    
- Since you provided `5` and `6` (both `int`s), it deduces `T = int`.
    
- That’s why you don’t need an explicit **deduction guide** for non-aggregate classes: the constructor itself is enough.

#### 🔹 Why pass `const T&` in constructor?

```cpp
Pair(const T& first, const T& second)
```

- If `T` is cheap (like `int`), passing by reference doesn’t hurt.
    
- If `T` is expensive (like a giant `std::string`), passing by value would copy unnecessarily.
    
- Using `const T&` avoids copies when possible.
    
- For modern C++, we might also add **move semantics**:

```cpp
Pair(T first, T second) : m_first{std::move(first)}, m_second{std::move(second)} {}
```

#### 🔹 Key Takeaways

1. **Inside class definition**:
    
    - You can use the template parameter (`T`) directly.
        
    - No need to redeclare `template <typename T>`.
        
2. **Outside class definition**:
    
    - You must redeclare the template (`template <typename T>`).
        
    - You must fully qualify the class with `Pair<T>::function`.
        
3. **CTAD** works automatically for non-aggregate class templates with constructors.

#### ✅ So the essence:

- **Templates are like blueprints.**
    
- When defining _outside_ the blueprint, the compiler needs to be reminded what template parameters apply.
    
- Inside the blueprint, they’re already in scope.

### Injected class names

#### 1. The basic problem

Normally, when you define a constructor, **its name must exactly match the class name**.

For a **non-template class**, that’s straightforward:

```cpp
class Foo {
public:
    Foo() { }  // constructor name == class name
};
```

But for a **class template**, things seem tricky:

```cpp
template <typename T>
class Pair {
public:
    Pair(const T& a, const T& b) { }  // constructor
};
```

Here, the constructor is named `Pair`, not `Pair<T>`.  
But shouldn’t the constructor’s name include `<T>` to match the template instantiation?

#### 2. Injected class names

The answer is **injected class names**.

Inside the scope of a class (or class template), the **unqualified name of the class itself** is automatically treated as a shorthand for the class with its template arguments.

👉 In other words:

- Inside `Pair<T>`, the name `Pair` is **injected** and automatically treated as if you wrote `Pair<T>`.
    

That’s why this works:

```cpp
template <typename T>
class Pair {
public:
    Pair(const T& a, const T& b) { }  // really Pair<T>(const T&, const T&)
};
```

The compiler interprets `Pair` here as `Pair<T>`.

#### 3. Example with a member function

Normally, when defining a member function outside a class template, we’d write:

```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair) {
    return m_first == pair.m_first && m_second == pair.m_second;
}
```

But because of **injected class names**, we can shorten this to:

```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair& pair) {   // Pair == Pair<T>
    return m_first == pair.m_first && m_second == pair.m_second;
}
```

Here, `Pair` is shorthand for `Pair<T>` because we’re still inside the scope of the class template `Pair<T>`.

#### 4. Important distinction from CTAD

- **Class Template Argument Deduction (CTAD)** works when _creating_ an object:

```cpp
Pair p{5, 6};   // compiler deduces T = int
```

But **function parameter deduction** does NOT work:

```cpp
void foo(Pair x);  // ❌ doesn’t deduce T
```

So why does `isEqual(const Pair& pair)` work?  
👉 Because this is not CTAD — it’s just shorthand! The `Pair` here is expanded by the compiler into `Pair<T>`.

#### 5. Key insights

1. Inside a class template, the **unqualified class name** automatically means “this class with its current template arguments.”
    
2. That’s why we can write constructors as `Pair(...)` instead of `Pair<T>(...)`.
    
3. And why member function parameters can use `Pair` instead of `Pair<T>`.
    
4. This shorthand is _not_ CTAD, it’s just compiler substitution.

### Where to define member functions for class templates outside the class

With member functions for class templates, the compiler needs to see both the class definition (to ensure that the member function template is declared as part of the class) and the template member function definition (to know how to instantiate the template). Therefore, we typically want to define both a class and its member function templates in the same location.

When a member function template is defined _inside_ the class definition, the template member function definition is part of the class definition, so anywhere the class definition can be seen, the template member function definition can also be seen. This makes things easy (at the cost of cluttering our class definition).

When a member function template is defined _outside_ the class definition, it should generally be defined immediately below the class definition. That way, anywhere the class definition can be seen, the member function template definitions immediately below the class definition will also be seen.

In the typical case where a class is defined in a header file, this means any member function templates defined outside the class should also be defined in the same header file, below the class definition.

>[!Key insight]
In lesson [11.7 -- Function template instantiation](https://www.learncpp.com/cpp-tutorial/function-template-instantiation/), we noted that functions implicitly instantiated from templates are implicitly inline. This includes both non-member and member function templates. Therefore, there is no issue including member function templates defined in header files into multiple code files, as the functions instantiated from those templates will be implicitly inline (and the linker will de-duplicate them).

>[!Best practice]
Any member function templates defined outside the class definition should be defined just below the class definition (in the same file).

---
