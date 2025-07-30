
### Compound statement / Block Statement

> is a group of zero or more statement treated as one statement by the compiler. 
> e.g: `{}` function...

> Blocks can also be nestest inside another block..
> When blocks are nested, the enclosing block is typically called the **outer block** and the enclosed block is called the **inner block** or **nested block**.

### Using blocks to execute multiple statements conditionally

> By default `if` statement just executes one statement but by adding block, we can execute multiple statements if condition evaluates to true.

### Block nesting levels

```cpp
#include <iostream>

int main()
{ // block 1, nesting level 1
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value >  0)
    { // block 2, nesting level 2
        if ((value % 2) == 0)
        { // block 3, nesting level 3
            std::cout << value << " is positive and even\n";
        }
        else
        { // block 4, also nesting level 3
            std::cout << value << " is positive and odd\n";
        }
    }

    return 0;
}
```

>The **nesting level** (also called the **nesting depth**) of a function is the maximum number of nested blocks you can be inside at any point in the function (including the outer block).

> In above example there are 4 blocks, but the nesting level is 3 since if and else can have one execution at a time.

> C++ standard says you can have nested level of 256 however not all compiler do that...

>[!tip]
>Keep the nesting level of your functions to 3 or less. If your function has a need for more nested levels, consider refactoring your function into sub-functions.

---

>[!warning]
>a linear increase in identifiers will result in an exponential increase in potential collisions! This is one of the key reasons for defining identifiers in the smallest scope possible.

>Let’s revisit an example of a naming collision, and then show how we can improve things using namespaces. In the following example, `foo.cpp` and `goo.cpp` are the source files that contain functions that do different things but have the same name and parameters.

foo.cpp

```cpp
// This doSomething() adds the value of its parameters
int doSomething(int x, int y)
{
    return x + y;
}
```

goo.cpp

```cpp
// This doSomething() subtracts the value of its parameters
int doSomething(int x, int y)
{
    return x - y;
}
```

main.cpp

```cpp
#include <iostream>

int doSomething(int x, int y); // forward declaration for doSomething

int main()
{
    std::cout << doSomething(4, 3) << '\n'; // which doSomething will we get?
    return 0;
}
```

> If we added both foo and goo files then it will give us error because there is two defination of the function doSomething which is not valid...
> One way to resolve this error would be to rename the function but then we have to change it everywhere and other files which is not efficient so to solve this, we use user defined namespace...

>[!Real Example]
>A better way to avoid collisions is to put your functions into your own namespaces. For this reason the standard library was moved into the `std` namespace.

### Defining your own namespaces

>C++ allows us to define our own namespaces via the `namespace` keyword. Namespaces that you create in your own programs are casually called **user-defined namespaces** (though it would be more accurate to call them **program-defined namespaces**).

The syntax for a namespace is as follows:

```cpp
namespace NamespaceIdentifier
{
    // content of namespace here
}
```

>[!tip]
>- It is convention to name program-defined types starting with a capital letter. Using the same convention for program-defined namespaces is consistent (especially when using a qualified name such as `Foo::x`, where `Foo` could be a namespace or a class type).
>- It helps prevent naming collisions with other system-provided or library-provided lower-cased names.

> Fixing our previous problem with namespace:

foo.cpp

```cpp
namespace Foo // define a namespace named Foo
{
    // This doSomething() belongs to namespace Foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}
```

goo.cpp

```cpp
namespace Goo // define a namespace named Goo
{
    // This doSomething() belongs to namespace Goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}
```

>Now `doSomething()` inside of `foo.cpp` is inside the `Foo` namespace, and the `doSomething()` inside of `goo.cpp` is inside the `Goo` namespace.

> Can arise the problem, how to tell the compiler which version of doSomething to use, there are two ways `scope resolution operator` and `using statement`.

---
### Accessing a namespace with the scope resolution operator (::)

>The best way to tell the compiler to look in a particular namespace for an identifier is to use the **scope resolution operator** (::). The scope resolution operator tells the compiler that the identifier specified by the right-hand operand should be looked for in the scope of the left-hand operand.

```cpp
#include <iostream>

namespace Foo // define a namespace named Foo
{
    // This doSomething() belongs to namespace Foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}

namespace Goo // define a namespace named Goo
{
    // This doSomething() belongs to namespace Goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}

int main()
{
    std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo
    return 0;
}
```

> If we want the doSomething version of goo.cpp then just use:
> `Goo::doSomething()`

---
### Using the scope resolution operator with no name prefix

```cpp
#include <iostream>

void print() // this print() lives in the global namespace
{
	std::cout << " there\n";
}

namespace Foo
{
	void print() // this print() lives in the Foo namespace
	{
		std::cout << "Hello";
	}
}

int main()
{
	Foo::print(); // call print() in Foo namespace
	::print();    // call print() in global namespace (same as just calling print() in this case)

	return 0;
}
```

> `::print just looks for the function defination in global scope so its same as `print()`

Exception:

>If an identifier inside a namespace is used and no scope resolution is provided, the compiler will first try to find a matching declaration in that same namespace. If no matching identifier is found, the compiler will then check each containing namespace in sequence to see if a match is found, with the global namespace being checked last.

```cpp
#include <iostream>

void print() // this print() lives in the global namespace
{
	std::cout << " there\n";
}

namespace Foo
{
	void print() // this print() lives in the Foo namespace
	{
		std::cout << "Hello";
	}

	void printHelloThere()
	{
		print();   // calls print() in Foo namespace
		::print(); // calls print() in global namespace
	}
}

int main()
{
	Foo::printHelloThere();

	return 0;
}
```

>In the above example, `print()` is called with no scope resolution provided. Because this use of `print()` is inside the `Foo` namespace, the compiler will first see if a declaration for `Foo::print()` can be found. Since one exists, `Foo::print()` is called.

>If `Foo::print()` had not been found, the compiler would have checked the containing namespace (in this case, the global namespace) to see if it could match a `print()` there.

>[!note]
>Note that we also make use of the scope resolution operator with no namespace (`::print()`) to explicitly call the global version of `print()`.

---
### Forward declaration of content in namespaces

>we discussed how we can use header files to propagate forward declarations. For identifiers inside a namespace, those forward declarations also need to be inside the same namespace:

add.h

```cpp
#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
}

#endif
```

add.cpp

```cpp
#include "add.h"

namespace BasicMath
{
    // define the function add() inside namespace BasicMath
    int add(int x, int y)
    {
        return x + y;
    }
}
```

main.cpp

```cpp
#include "add.h" // for BasicMath::add()

#include <iostream>

int main()
{
    std::cout << BasicMath::add(4, 3) << '\n';

    return 0;
}
```

>If forward declaration of add function wasnt placed inside the namespace then the linker will complain that it couldnt find matching defination for the call to BaicMath::add(4, 3) because BasicMath::add() and add() forward declaration is different and its not the forward declaration for BasicMath::add() becasue its inside a namespace so its different so if Function defination is in some namespace then its forward declaration should also be in the same namespace...

>[!note]
>Compiler - Translates **each source code file (`.cpp`)** into an **object file (`.o` or `.obj`)**.
>**🔴 Compiler Complains When:**
>> - You made a **syntax error**.
>> - You used an **undeclared variable or function**.
>> - You **mismatched types** in assignments or calls.
>
>Linker  Takes all the compiled object files (`.o`) and **links them together** to form the **final executable**.
>**🔴 Linker Complains When:**
>>- A **function or variable is declared** but **not defined** anywhere.
>>-  There's a **missing library**.
>>-  **Duplicate definitions** exist.

---
### Multiple namespace blocks are allowed

>It’s legal to declare namespace blocks in multiple locations (either across multiple files, or multiple places within the same file). All declarations within the namespace are considered part of the namespace.

>[!tip]
>> **You can define the same namespace in multiple places — even across multiple files — and they will all be part of the same namespace.**


circle.h

```cpp
#ifndef CIRCLE_H
#define CIRCLE_H

namespace BasicMath
{
    constexpr double pi{ 3.14 };
}

#endif
```

growth.h

```cpp
#ifndef GROWTH_H
#define GROWTH_H

namespace BasicMath
{
    // the constant e is also part of namespace BasicMath
    constexpr double e{ 2.7 };
}

#endif
```

main.cpp

```cpp
#include "circle.h" // for BasicMath::pi
#include "growth.h" // for BasicMath::e

#include <iostream>

int main()
{
    std::cout << BasicMath::pi << '\n';
    std::cout << BasicMath::e << '\n';

    return 0;
}
```

3.14
2.7

#### 🔷 Why is this important?

Without this feature, you would need to:

- Put **all definitions** related to `BasicMath` in **one single place/file**, which is:
    
    - Impractical
        
    - Not modular or maintainable
        

By allowing multiple namespace blocks, C++ lets you:

- Organize your code cleanly across files
    
- Group related things under the same name (`BasicMath`, `std`, etc.)

#### 🔷 Relation to the Standard Library

The **Standard Library** uses this feature heavily.

Example:

- `<iostream>` defines things like `std::cout`, `std::cin`
    
- `<vector>` defines `std::vector`
    
- `<string>` defines `std::string`
    

They all define different things in separate files — **but all inside `namespace std`**.

>[!warning]
>Do not add custom functionality to the std namespace.

---
### Nested namespaces

>Namespaces can be nested inside other namespaces. For example:

```cpp
#include <iostream>

namespace Foo
{
    namespace Goo // Goo is a namespace inside the Foo namespace
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

>Note that because namespace `Goo` is inside of namespace `Foo`, we access `add` as `Foo::Goo::add`.

>Since C++17, nested namespaces can also be declared this way:

```cpp
#include <iostream>

namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

This is equivalent to the prior example.

>If you later need to add declarations to the `Foo` namespace (only), you can define a separate `Foo` namespace to do so:

```cpp
#include <iostream>

namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Foo
{
     void someFcn() {} // This function is in Foo only
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
    return 0;
}
```

---
### Namespace aliases

Because typing the qualified name of a variable or function inside a nested namespace can be painful, C++ allows you to create **namespace aliases**, which allow us to temporarily shorten a long sequence of namespaces into something shorter:

```cpp
#include <iostream>

namespace Foo::Goo
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace Active = Foo::Goo; // active now refers to Foo::Goo

    std::cout << Active::add(1, 2) << '\n'; // This is really Foo::Goo::add()

    return 0;
} // The Active alias ends here
```

One nice advantage of namespace aliases: If you ever want to move the functionality within `Foo::Goo` to a different place, you can just update the `Active` alias to reflect the new destination, rather than having to find/replace every instance of `Foo::Goo`.

```cpp
#include <iostream>

namespace Foo::Goo
{
}

namespace V2
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace Active = V2; // active now refers to V2

    std::cout << Active::add(1, 2) << '\n'; // We don't have to change this

    return 0;
}
```

### [How to use namespaces](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/#:~:text=It%E2%80%99s%20worth%20noting,inline%20namespaces.)

---
## 🧠 Scenario: You’re making a software system for a company

Let’s say you’re building a software system for a **tech company**. The company has two departments:

- **Finance**
    
- **HR**
    

Each department has its own utility functions, and you want to **organize your code cleanly** and avoid name collisions.

### ✅ Example using namespaces and nested namespaces

#### 🔹 `finance.h`

```cpp
#ifndef FINANCE_H
#define FINANCE_H

namespace Company {
    namespace Finance {
        double calculateTax(double income) {
            return income * 0.15;  // 15% tax
        }
    }
}

#endif

```

#### 🔹 `hr.h`

```cpp
#ifndef HR_H
#define HR_H

namespace Company {
    namespace HR {
        void sendOfferLetter(const std::string& name) {
            std::cout << "Sending offer letter to " << name << '\n';
        }
    }
}

#endif

```

#### 🔹 `main.cpp`

```cpp
#include <iostream>
#include <string>
#include "finance.h"
#include "hr.h"

int main() {
    double salary = 50000;
    double tax = Company::Finance::calculateTax(salary);
    std::cout << "Tax on $" << salary << " is $" << tax << '\n';

    Company::HR::sendOfferLetter("Alice");

    return 0;
}

```

#### ⛳ Output

```pgsql
Tax on $50000 is $7500
Sending offer letter to Alice

```

#### 🔐 Why use this?

1. **Avoids name clashes**:
    
    - Both Finance and HR could have functions like `calculateSalary()`.
        
    - Namespaces isolate them.
        
2. **Logical grouping**:
    
    - `Company::Finance::calculateTax` is **clear and self-documenting**.
        
3. **Scalability**:

---

### Local Variables

> Scope is a compile-time property, and trying to use an identifier when it is out of scope will result in a compile error.

> Local variables have block scope which means they are in scope from their point of defination to the end of block they are defined in.

```cpp
int main()
{
    int i { 5 }; // i enters scope here
    double d { 4.0 }; // d enters scope here

    return 0;
} // d and i go out of scope here
```

>Function parameters are also local variables which are considered in scope of function block although they are not inside the block...

>All variable names within a scope must be unique

```cpp
void someFunction(int x)
{
    int x{}; // compilation failure due to name collision with function parameter
}

int main()
{
    return 0;
}
```

### Local variables have automatic storage duration

>a variable’s storage duration directly determines its `lifetime`.

>local variables have **automatic storage duration**, which means they are created at the point of definition and destroyed at the end of the block they are defined in. For example:

```cpp
int main()
{
    int i { 5 }; // i created and initialized here
    double d { 4.0 }; // d created and initialized here

    return 0;
} // d and i are destroyed here
```

---

### Local variables in nested blocks

```cpp
int main() // outer block
{
    int x { 5 }; // x enters scope and is created here

    { // nested block
        int y { 7 }; // y enters scope and is created here
    } // y goes out of scope and is destroyed here

    // y can not be used here because it is out of scope in this block

    return 0;
} // x goes out of scope and is destroyed here
```

>Because the scope of variable `y` is limited to the inner block in which it is defined, it’s not accessible anywhere in the outer block.

> But we can access variables of outerblock inside innerblock.

---
### Local variables have no linkage

>Identifiers have another property named _linkage_. An identifier’s **linkage** determines whether a declaration of that same identifier in a different scope refers to the same object (or function).

```cpp
int main()
{
    int x { 2 }; // local variable, no linkage

    {
        int x { 3 }; // this declaration of x refers to a different object than the previous x
    }

    return 0;
}
```

>Scope and linkage may seem somewhat similar. However, scope determines where declaration of a single identifier can be seen and used in the code. Linkage determines whether multiple declarations of the same identifier refer to the same object or not.

---
### Variables should be defined in the most limited scope

>If a variable is only used within a nested block, it should be defined inside that nested block:

```cpp
#include <iostream>

int main()
{
    // do not define y here

    {
        // y is only used inside this block, so define it here
        int y { 5 };
        std::cout << y << '\n';
    }

    // otherwise y could still be used here, where it's not needed

    return 0;
}
```

>By limiting the scope of a variable, you reduce the complexity of the program because the number of active variables is reduced. Further, it makes it easier to see where variables are used (or aren’t used). A variable defined inside a block can only be used within that block (or nested blocks). This can make the program easier to understand.

If a variable is needed in an outer block, it needs to be declared in the outer block:

```cpp
#include <iostream>

int main()
{
    int y { 5 }; // we're declaring y here because we need it in this outer block later

    {
        int x{};
        std::cin >> x;

        // if we declared y here, immediately before its actual first use...
        if (x == 4)
            y = 4;
    } // ... it would be destroyed here

    std::cout << y; // and we need y to exist here

    return 0;
}
```

>[!tip]
>Define variables in the most limited existing scope. Avoid creating new blocks whose only purpose is to limit the scope of variables.

---
### Global Variables

> Variables that are declared outside the function are called global variable.

### Declaring global variables

>By convention, global variables are declared at the top of a file, below the includes, in the global namespace. Here’s an example of a global variable being defined:

```cpp
#include <iostream>

// Variables declared outside of a function are global variables
int g_x {}; // global variable g_x

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    g_x = 3;
    std::cout << g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << g_x << '\n';

    // global variables can be seen and used everywhere in the file
    g_x = 5;
    std::cout << g_x << '\n';

    return 0;
}
// g_x goes out of scope here
```

### The scope of global variables

>Identifiers declared in the global namespace have **global namespace scope** (commonly called **global scope**, and sometimes informally called **file scope**)

>which means they are visible from the point of declaration until the end of the _file_ in which they are declared.

>Once declared, a global variable can be used anywhere in the file from that point onward! In the above example, global variable `g_x` is used in both functions `doSomething()` and `main()`.

>Global variables can also be defined inside a user-defined namespace.

```cpp
#include <iostream>

namespace Foo // Foo is defined in the global scope
{
    int g_x {}; // g_x is now inside the Foo namespace, but is still a global variable
}

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    Foo::g_x = 3;
    std::cout << Foo::g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << Foo::g_x << '\n';

    // global variables can be seen and used everywhere in the file
    Foo::g_x = 5;
    std::cout << Foo::g_x << '\n';

    return 0;
}
```

Although the identifier `g_x` is now limited to the scope of `namespace Foo`, that name is still globally accessible (via `Foo::g_x`), and `g_x` is still a global variable.

>[!tip]
>Variables declared **at namespace scope** (outside of any function or class) are **global in scope**

>[!Best Practice]
>Prefer defining global variables inside a namespace rather than in the global namespace.

### Global variables have static duration

>Global variables are created when the program starts (before `main()` begins execution), and destroyed when it ends. This is called **static duration**. Variables with _static duration_ are sometimes called **static variables**.

And local variable have automatic duration...

### Naming global variables

>By convention, some developers prefix global variable identifiers with “g” or “g_” to indicate that they are global. This prefix serves several purposes:

- avoid naming collisions in global namespace
- prevent inadvertent name shadowing
- it helps indicate that the prefix variables persist beyond the scope of function and any changes made in function will also presist

>**Global variable inside namespace:** if we define a global variable inside a user-defined namespace then the need for prefix `g or g_` is not needed but its good practice if we do to identify the global variable.

>[!Best Practice]
>Use `g or g_` prefix for naming global variable.

---
### Global variable initialization

>Unlike local variables, which are uninitialized by default ( with the exception of using list initializer  ), variables with static duration are zero-initialized by default.

```cpp
int g_x;       // no explicit initializer (zero-initialized by default)
int g_y {};    // value initialized (resulting in zero-initialization)
int g_z { 1 }; // list initialized with specific value
```

---
### Constant global variables

>Just like local variables, global variables can be constant. As with all constants, constant global variables must be initialized.

```cpp

const int g_x;     // error: constant variables must be initialized
constexpr int g_w; // error: constexpr variables must be initialized

const int g_y { 1 };     // const global variable g_y, initialized with a value
constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value

```

---
### Variable shadowing (name hiding)

>Each block defines its own scope region. So what happens when we have a variable inside a nested block that has the same name as a variable in an outer block? When this happens, the nested variable “hides” the outer variable in areas where they are both in scope. This is called **name hiding** or **shadowing**.

### Shadowing of local variables

```cpp
#include <iostream>

int main()
{ // outer block
    int apples { 5 }; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        int apples{ 0 }; // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10; // this assigns value 10 to nested block apples, not outer block apples

        std::cout << apples << '\n'; // print value of nested block apples
    } // nested block apples destroyed


    std::cout << apples << '\n'; // prints value of outer block apples

    return 0;
} // outer block apples destroyed
```

>There are two apples variables one in outer scope and one in nested scope but we can access the outer scope variable inside nested scope but when we make a new variable with same name as outer scope in nested scope then the outer variable with same name is shadowed or hidden.

>[!tip]
>If we didnt define the apple variable insdie the nested scope then it would refer to the outer scope apple variable...

### Shadowing of global variables

>Similar to how variables in a nested block can shadow variables in an outer block, local variables with the same name as a global variable will shadow the global variable wherever the local variable is in scope:

```cpp
#include <iostream>
int value { 5 }; // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}

int main()
{
    int value { 7 }; // hides the global variable value (wherever local variable value is in scope)

    ++value; // increments local value, not global value

    std::cout << "local variable value: " << value << '\n';

    foo();

    return 0;
} // local value is destroyed
```
local variable value: 8
global variable value: 5

>However, because global variables are part of the global namespace, we can use the scope operator (::) with no prefix to tell the compiler we mean the global variable instead of the local variable.

```cpp
#include <iostream>
int value { 5 }; // global variable

int main()
{
    int value { 7 }; // hides the global variable value
    ++value; // increments local value, not global value

    --(::value); // decrements global value, not local value (parenthesis added for readability)

    std::cout << "local variable value: " << value << '\n';
    std::cout << "global variable value: " << ::value << '\n';

    return 0;
} // local value is destroyed
```
local variable value: 8
global variable value: 4

>[!warning]
>Shadowing of local variables should generally be avoided, as it can lead to inadvertent errors where the wrong variable is used or modified. Some compilers will issue a warning when a variable is shadowed.
>For the same reason that we recommend avoiding shadowing local variables, we recommend avoiding shadowing global variables as well. This is trivially avoidable if all of your global names use a “g_” prefix.

>[!tip]
>Avoid variable shadowing.

---

### Internal Linkage

>[!Reminder]
>Local Variables have no linkage:
>**Linkage** determines whether multiple **declarations** of an entity (variable/function) across **different translation units or scopes** refer to the **same entity** or not.
>**local variables have no linkage** because **they exist only within the scope (block/function) in which they are defined**.

>Global Variables and function can have either internal linkage or external linkage.

#### What is translation unit?
##### 📁 **Example:**

Suppose you have the following files:

**main.cpp**

```cpp
#include "math_utils.h"

int main() {
    return square(5);
}

```

**math_utils.h**

```cpp
int square(int x);

```

**math_utils.cpp**

```cpp
int square(int x) {
    return x * x;
}

```

##### ✅ What are the translation units?

- `main.cpp` + `math_utils.h` → one translation unit.
    
- `math_utils.cpp` + any headers it includes → another translation unit.
    

Each `.cpp` file is **compiled separately** into an object file. These are later **linked** together.

---

>**Internal linkage:** An identifier with **internal linkage** can be seen and used within a single translation unit, but it is not accessible from other translation units. This means that if two source files have identically named identifiers with internal linkage, those identifiers will be treated as independent (and do not result in an ODR violation for having duplicate definitions).

### Global variables with internal linkage

>To make a non-constant global variable internal, we use the `static` keyword.

```cpp
#include <iostream>

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}
```

>[!tip]
>Const and constexpr global variables have internal linkage by default (and thus don’t need the `static` keyword -- if it is used, it will be ignored).

Here’s an example of multiple files using internal variables:

a.cpp

```cpp
[[maybe_unused]] constexpr int g_x { 2 }; // this internal g_x is only accessible within a.cpp
```

main.cpp

```cpp
#include <iostream>

static int g_x { 3 }; // this separate internal g_x is only accessible within main.cpp

int main()
{
    std::cout << g_x << '\n'; // uses main.cpp's g_x, prints 3

    return 0;
}
```
This program prints:

3

---


>There are two reasons for having internal linkage for const object.
>> - Const objects should be usable in constant expressions.
>> - Const objects should be able to be propagated via header files


>With internal linkage:

- Each `.cpp` file gets **its own separate definition** of the `const` object.
    
- These are considered **different variables** by the linker.
    
- No conflict, **no ODR violation**.

#### ✅ Why This Is Important for Constant Expressions


```cpp
// header.h
const int size = 5;
char arr[size];  // requires a compile-time constant

```

This only works if the compiler sees the **definition of `size`** — not just:

```cpp
extern const int size;  // <- not enough for constant expression

```

So by giving it **internal linkage by default**, C++ allows you to:

- Place a `const` in a header,
    
- Use it as a constant expression,
    
- Include it in multiple `.cpp` files,
    
- Without linker errors.

>**Allow `const` objects to be defined in headers** and included in multiple `.cpp` files — without violating the **ODR** (One Definition Rule).

This is **very important in large projects**, where you want constants to be shared:

```cpp
// config.h
const int max_users = 100;

```

Then used in: 

```cpp
// main.cpp
#include "config.h"

```

```cpp
// server.cpp
#include "config.h"

```
You can include this `config.h` in many files **safely** — because `max_users` has **internal linkage**, a **separate copy is generated in each translation unit** — and that's **allowed by the ODR**.

#### ❗ What If `const` Had External Linkage by Default?

Let’s say `const` had external linkage by default (like `extern` variables). Then this code:

```cpp
// config.h
const int max_users = 100;

```
would cause an **ODR violation** if included in multiple `.cpp` files. Why?

Because:

- You’d be **defining** `max_users` in each `.cpp` file that includes `config.h`.
    
- With external linkage, **only one definition is allowed** across the whole program.
    

🔴 So you’d get a linker error: _multiple definitions of `max_users`_.


---
### Functions with internal linkage

>Function identifiers also have linkage and by default it has external linkage but can be changed into internal linkage by making it static...

add.cpp

```cpp
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
[[maybe_unused]] static int add(int x, int y)
{
    return x + y;
}
```

> ❗ This function should only be visible **within this translation unit** (i.e., this `.cpp` file).


main.cpp

```cpp
#include <iostream>

int add(int x, int y); // forward declaration for function add

int main()
{
    std::cout << add(3, 4) << '\n';

    return 0;
}
```

- This is trying to use `add()` from another file.
    
- The compiler allows the call (because of the declaration),
    
- But the **linker fails** because there is **no definition of `add()` with external linkage** to link to.

This program won’t link, because function `add` is not accessible outside of `add.cpp`.

### The one-definition rule and internal linkage

>the one-definition rule says that an object or function can’t have more than one definition, either within a file or a program.

>[!tip]
>However, it’s worth noting that internal objects (and functions) that are defined in different files are considered to be independent entities (even if their names and types are identical), so there is no violation of the one-definition rule. Each internal object only has one definition.

> Modern C++ make use of unnamed namespaces instead of static.

---
### Why bother giving identifiers internal linkage?

>There are typically two reasons to give identifiers internal linkage:
>
>> - Suppose there is an identifier we want to make sure isnt accessible to other `.cpp` files. This could be a global variable we dont want messed with.
>> - To avoid naming collisions, because identifiers with internal linkage arent exposed to the linker, they can only collide with nams in the same TU not across the entire program.

>[!best practice]
>Give identifiers internal linkage when you have an explicit reason to disallow access from other files.
>Consider giving all identifiers you don’t want accessible to other files internal linkage (use an unnamed namespace for this).

---
### External linkage and variable forward declarations

>An identifier with **external linkage** can be seen and used both from the file in which it is defined, and from other code files (via a forward declaration). In this sense, identifiers with external linkage are truly “global” in that they can be used anywhere in your program!

Identifiers with external linkage are visible to the linker. This allows the linker to do two things:

- Connect an identifier used in one translation unit with the appropriate definition in another translation unit.
- Deduplicate inline identifiers so one canonical definition remains.

### Functions have external linkage by default

>As we know we can call function from another translational unit `.cpp` file in current file by just having forward declaration in current file in which where we are calling that function and by just having decalaration in current file the linker will connect that defination from another translational unit to current TU and functional will be called.

>[!tip]
>In order to call a function defined in another file, you must place a `forward declaration` for the function in any other files wishing to use the function. The forward declaration tells the compiler about the existence of the function, and the linker connects the function calls to the actual function definition.

Example:

a.cpp

```cpp
#include <iostream>

void sayHi() // this function has external linkage, and can be seen by other files
{
    std::cout << "Hi!\n";
}
```

main.cpp

```cpp
void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file

int main()
{
    sayHi(); // call to function defined in another file, linker will connect this call to the function definition

    return 0;
}
```
Hi!

>[!tip]
>The forward declaration satisfies the compiler, and the linker is able to link the function call to the function definition.

>If function `sayHi()` had internal linkage instead, the linker would not be able to connect the function call to the function definition, and a linker error would result.

---
### Global variables with external linkage

>Global variables with external linkage are sometimes called **external variables**. To make a global variable external (and thus accessible by other files), we can use the `extern` keyword to do so:

```cpp
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

>[!tip]
>Non-const global variables are external by default, so we don’t need to mark them as `extern`.

### Variable forward declarations via the extern keyword

>[!tip]
>If we want to use the external global variable in other translational unit then there should be an external forward declaration in that translational unit `.cpp` .

Here is an example of using variable forward declarations:

a.cpp

```cpp
// global variable definitions
int g_x { 2 };              // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```

main.cpp

```cpp
#include <iostream>

extern int g_x;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << ' ' << g_y << '\n'; // prints 2 3

    return 0;
}
```

In the above example, `a.cpp` and `main.cpp` both reference the same global variable named `g_x`. So even though `g_x` is defined and initialized in `a.cpp`, we are able to use its value in `main.cpp` via the forward declaration of `g_x`.

>[!note]
>Note that the `extern` keyword has different meanings in different contexts. In some contexts, `extern` means “give this variable external linkage”. In other contexts, `extern` means “this is a forward declaration for an external variable that is defined somewhere else”.

>[!warning]
>If you want to define an uninitialized non-const global variable, do not use the extern keyword, otherwise C++ will think you’re trying to make a forward declaration for the variable.

>[!warning]
>Although constexpr variables can be given external linkage via the `extern` keyword, they can not be forward declared as constexpr. This is because the compiler needs to know the value of the constexpr variable (at compile time). If that value is defined in some other file, the compiler has no visibility on what value was defined in that other file.
>However, you can forward declare a constexpr variable as const, which the compiler will treat as a runtime const. This isn’t particularly useful.

>[!note]
>Note that function forward declarations don’t need the `extern` keyword -- the compiler is able to tell whether you’re defining a new function or making a forward declaration based on whether you supply a function body or not. Variables forward declarations _do_ need the `extern` keyword to help differentiate uninitialized variables definitions from variable forward declarations (they look otherwise identical):

```cpp
// non-constant
int g_x;        // variable definition (no initializer)
int g_x { 1 };  // variable definition (w/ initializer)
extern int g_x; // forward declaration (no initializer)

// constant
extern const int g_y { 1 }; // variable definition (const requires initializers)
extern const int g_y;       // forward declaration (no initializer)
```

>[!tip]
>Avoid using `extern` on a non-const global variable with an initializer

The following two lines are semantically equivalent:

```cpp
int g_x { 1 };        // extern by default
extern int g_x { 1 }; // explicitly extern (may cause compiler warning)
```

Remember when we said compilers have the leeway to issue a diagnostic for things they find suspicious? This is one of those cases. Conventionally, `extern` is applied to a non-const variable when we want a forward declaration. However, adding an initializer makes the statement a definition instead. The compiler is telling you that something seems amiss. To correct it, either remove the initializer (if you intended a forward declaration) or remove the `extern` (if you intended a definition).

>[!best practice]
>Only use `extern` for global variable forward declarations or const global variable definitions.  
Do not use `extern` for non-const global variable definitions (they are implicitly `extern`).

```cpp
// Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
```

>[!Remember]
>Scope determines where a variable is accessible. Duration determines when a variable is created and destroyed. Linkage determines whether the variable can be exported to another file or not.

---
### Why (non-const) global variables are evil

>[!tip]
>When developers tell you that global variables are evil, they’re usually not talking about _all_ global variables. They’re mostly talking about non-const global variables.

>By far the biggest reason non-const global variables are dangerous is because their values can be changed by _any_ function that is called, and there is no easy way for the programmer to know that this will happen. Consider the following program:

```cpp
#include <iostream>

int g_mode; // declare global variable (will be zero-initialized by default)

void doSomething()
{
    g_mode = 2; // set the global g_mode variable to 2
}

int main()
{
    g_mode = 1; // note: this sets the global g_mode variable to 1.  It does not declare a local g_mode variable!

    doSomething();

    // Programmer still expects g_mode to be 1
    // But doSomething changed it to 2!

    if (g_mode == 1)
    {
        std::cout << "No threat detected.\n";
    }
    else
    {
        std::cout << "Launching nuclear missiles...\n";
    }

    return 0;
}
```

>In short, global variables make the program’s state unpredictable. Every function call becomes potentially dangerous, and the programmer has no easy way of knowing which ones are dangerous and which ones aren’t! Local variables are much safer because other functions can not affect them directly.

>[!tip]
>One of the key reasons to declare local variables as close to where they are used as possible is because doing so minimizes the amount of code you need to look through to understand what the variable does.

>Global variables are at the opposite end of the spectrum -- because they can be accessed anywhere, you might have to look through the entire program to understand their usage. In small programs, this might not be an issue. In large ones, it will be.

>[!best practice]
>Use local variables instead of global variables whenever possible.

---
### The initialization order problem of global variables

>Initialization of static variables (which includes global variables) happens as part of program startup, before execution of the `main` function. This proceeds in two phases.

The first phase is called **static initialization**. Static initialization proceeds in two phases:

- Global variables with constexpr initializers (including literals) are initialized to those values. This is called **constant initialization**.
- Global variables without initializers are zero-initialized. Zero-initialization is considered to be a form of static-initialization since `0` is a constexpr value.

The second phase is called **dynamic initialization**. This phase is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized.

Here’s an example of a non-constexpr initializer:
```cpp
int init()
{
    return 5;
}

int g_something{ init() }; // non-constexpr initialization
```

>Within a single file, for each phase, global variables are generally initialized in order of definition (there are a few exceptions to this rule for the dynamic initialization phase). Given this, you need to be careful not to have variables dependent on the initialization value of other variables that won’t be initialized until later. For example:

```cpp
#include <iostream>

int initX();  // forward declaration
int initY();  // forward declaration

int g_x{ initX() }; // g_x is initialized first
int g_y{ initY() };

int initX()
{
    return g_y; // g_y isn't initialized when this is called
}

int initY()
{
    return 5;
}

int main()
{
    std::cout << g_x << ' ' << g_y << '\n';
}
```
This prints:

0 5

### static initialization order fiasco Problem?

In C++, **static duration objects** (like global variables or variables marked `static` at namespace or file scope) are initialized **before `main()` starts**.

a.cpp

```cpp
// a.cpp
#include <iostream>

int a = 10;

```

b.cpp

```cpp
// b.cpp
#include <iostream>

int b = 20;

```

Both `a` and `b` have **static storage duration** and are initialized **before `main()`**.

#### 🔹 What’s the Problem?

When you have **multiple translation units** (i.e., multiple `.cpp` files), **the C++ standard does not define the order** in which these static objects are initialized **across files**.

- Within the same file: the order of initialization is **well-defined, top to bottom**.
    
- Across different files: the order is **unspecified**, **undefined**, and **non-deterministic**.
    

That means: **either file could initialize its static variables first.**

#### 🔹 Why Is That Dangerous?

Imagine this:

```cpp
// a.cpp
#include <iostream>

extern int getValueFromB(); // declared in b.cpp

int a = getValueFromB();  // uses b during initialization

int getValueFromA() { return a; }

```

```cpp
// b.cpp
#include <iostream>

extern int getValueFromA(); // declared in a.cpp

int b = getValueFromA();  // uses a during initialization

int getValueFromB() { return b; }

```

Now, imagine that **a.cpp's static object `a` is initialized first**, so it calls `getValueFromB()` while `b` has **not been initialized yet**!

Or vice versa.

This causes:

- **Undefined behavior**
    
- Possibly accessing uninitialized variables
    
- Bugs that appear _randomly_ or _only in some builds/platforms_
    

>[!tip]
> **You should avoid using non-const static objects at global or namespace scope because their initialization order across translation units is undefined, which can lead to subtle and hard-to-debug issues.**

#### 🔹 What Are Static Duration Objects?

Static duration objects are:

- **Global variables**
    
- **Namespace-scope static variables**
    
- **Function-local static variables**
    
- **Static class members**
    

These are created before `main()` starts and destroyed after it ends.

>[!warning]
>> **Never initialize static-duration objects with values from other static-duration objects defined in a different translation unit.**

---

### So what are very good reasons to use non-const global variables?

#### [Read](https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/#:~:text=There%20aren%E2%80%99t%20many,versus%20or%20hotseat)

>[!tip]
> In short there arent many cases where it is a good idea to use non-const global variables..
> But there are some cases where it can be used:
> Example: A good example is a log file, where you can dump error or debug information. It probably makes sense to define this as a global, because you’re likely to only have one such log in a program and it will likely be used everywhere in your program.

---

### As a rule of thumb, any use of a global variable should meet at least the following two criteria:

#### ✅ Condition 1: "There should only ever be one of the thing the variable represents"

This means:

- The object or value **naturally exists as a single instance** in your program.
    
- You wouldn’t ever want multiple copies of it.
    

#### Examples where this is true:

| Variable       | Why it's okay?                             |
| -------------- | ------------------------------------------ |
| `globalLogger` | You only need **one logging system**       |
| `appSettings`  | There's only **one app configuration**     |
| `std::cin`     | There’s only **one standard input** stream |

🔻 If you need more than one, **a global is probably the wrong tool**.

#### 🚫 Bad example:

```cpp
int currentUserScore;  // global variable
```
❌ If you later add multiplayer support, this design **breaks** — you need a score per player.

#### ✅ Condition 2: "Its use should be ubiquitous throughout your program"

This means:

- The variable is **used everywhere** across your program.
    
- Almost **every part of the program needs access** to it.
    

#### Examples:

- `globalLogger.log("something")` used in dozens of modules
    
- `appConfig.get("theme")` accessed in UI, back-end, logging, etc.
    

If only **one small part** of your program uses it, **you shouldn't make it global** — just pass it as a function parameter or member variable instead.

---
### Protecting yourself from global destruction

>If you do find a reason to use non-const global variables or global variables, follow these advices:

**Advice:**
- prefix all non-namespaced global variable with g or g_
- better way is to keep them in namespace then no need for prefix

instead of:

```cpp
#include <iostream>

constexpr double gravity { 9.8 }; // risk of collision with some other global variable named gravity

int main()
{
    std::cout << gravity << '\n'; // unclear if this is a local or global variable from the name

    return 0;
}
```

Do this:

```cpp
#include <iostream>

namespace constants
{
    constexpr double gravity { 9.8 }; // will not collide with other global variables named gravity
}

int main()
{
    std::cout << constants::gravity << '\n'; // clear this is a global variable (since namespaces are global)

    return 0;
}
```

>**Advice:** Instead of allowing direct access to global variable what we can do is use the concept of encapsulation by making the global variable inside namespace static or const then it will have internal linkage and can be accessed in current translational unit only and to access these global variables in other translational unit what we can do is make functions which are external by default and return global variables value from that function and thats how we can access the global variable in other translational unit... NEAT [Example of this](https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/#:~:text=by%20making%20the,be%20static.)

>**Advice:** when writing an otherwise standalone function that uses the global variable, don’t use the variable directly in your function body. Pass it in as an argument instead. That way, if your function ever needs to use a different value for some circumstance, you can simply vary the argument. This helps maintain modularity.

instead of:

```cpp
#include <iostream>

namespace constants
{
    constexpr double gravity { 9.8 };
}

// This function is only useful for calculating your instant velocity based on the global gravity
double instantVelocity(int time)
{
    return constants::gravity * time;
}

int main()
{
    std::cout << instantVelocity(5) << '\n';

    return 0;

}
```
Do this:
```cpp
#include <iostream>

namespace constants
{
    constexpr double gravity { 9.8 };
}

// This function can calculate the instant velocity for any gravity value (more useful)
double instantVelocity(int time, double gravity)
{
    return gravity * time;
}

int main()
{
    std::cout << instantVelocity(5, constants::gravity) << '\n'; // pass our constant to the function as a parameter

    return 0;
}
```

---
### Inline functions and variables

>When we want to do some discrete task like reading from user or outputting something to some file there are two option to do so:
>>- Write the code as part of exsisting function which is called writting code "in-place" or "inline".
>>- Create a new function which has many benefits

#### Downside of creating new function

>one downside of using a new function is that every time a function is called, there is a certain amount of performance overhead that occurs. Consider the following example:

```cpp
#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0;
}
```

When a call to `min()` is encountered,

- CPU must store address of the current instruction so it knows where to return to.
- Values of various CPU registers
- parameters values `x and y` must be instantiated and then initialized.
- Then it execution path has to jump to the code in the `min()` fucntion.
- when function ends the program has to jump back to the location of function call.
- return value has to be copied so it can be output
- These has to happen for each function call.

>All of the extra work that must happen to setup, facilitate, and/or cleanup after some task (in this case, making a function call) is called **overhead**.

>For functions that are large and/or perform complex tasks, the overhead of the function call is typically insignificant compared to the amount of time the function takes to run. However, for small functions (such as `min()` above), the overhead costs can be larger than the time needed to actually execute the function’s code! In cases where a small function is called often, using a function can result in a significant performance penalty over writing the same code in-place.

---
### Inline expansion

>Fortunately, the C++ compiler has a trick that it can use to avoid such overhead cost: **Inline expansion** is a process where a function call is replaced by the code from the called function’s definition.

For example, if the compiler expanded the `min()` calls in the above example, the resulting code would look like this:

```cpp
#include <iostream>

int main()
{
    std::cout << ((5 < 6) ? 5 : 6) << '\n';
    std::cout << ((3 < 2) ? 3 : 2) << '\n';
    return 0;
}
```

Note that the two calls to function `min()` have been replaced by the code in the body of the `min()` function (with the value of the arguments substituted for the parameters). This allows us to avoid the overhead of those calls, while preserving the results of the code.

---
### The performance of inline code

>Beyond removing the cost of function call, inline expansion can also allow the compiler to optimize the resulting code more efficiently -- for example, because the expression `((5 < 6) ? 5 : 6)` is now a constant expression, the compiler could further optimize the first statement in `main()` to `std::cout << 5 << '\n';`.

>However, inline expansion has its own potential cost: if the body of the function being expanded takes more instructions than the function call being replaced, then each inline expansion will cause the executable to grow larger. Larger executables tend to be slower (due to not fitting as well in memory caches).

>The decision about whether a function would benefit from being made inline (because removal of the function call overhead outweighs the cost of a larger executable) is not straightforward. Inline expansion could result in performance improvements, performance reductions, or no change to performance at all, depending on the relative cost of a function call, the size of the function, and what other optimizations can be performed.

>[!tip]
>Inline expansion is best suited to simple, short functions (e.g. no more than a few statements), especially cases where a single function call can be executed more than once (e.g. function calls inside a loop).

---
### When inline expansion occurs

>Every function falls into one of two categories, where calls to the function:

- May be expanded (most functions are in this category).
- Can’t be expanded.

>Most functions fall into the “may” category: their function calls can be expanded if and when it is beneficial to do so. For functions in this category, a modern compiler will assess each function and each function call to make a determination about whether that particular function call would benefit from inline expansion. A compiler might decide to expand none, some, or all of the function calls to a given function.

>[!tip]
>Modern optimizing compilers make the decision about when functions should be expanded inline.

The most common kind of function that can’t be expanded inline is a function whose definition is in another translation unit. Since the compiler can’t see the definition for such a function, it doesn’t know what to replace the function call with!

---
### The inline keyword, historically

>Historically, compilers didnt have the capability to determine which function call should be beneficial for making inline expansion so keyword of `inline` was used but i didnt make the function inline expansion but provided a hint and making that function inline expansion was in the hand of compiler and compiler can reject that request...

However, in modern C++, the `inline` keyword is no longer used to request that a function be expanded inline. There are quite a few reasons for this:

- Using `inline` to request inline expansion is a form of premature optimization, and misuse could actually harm performance.
- The `inline` keyword is just a hint to help the compiler determine where to perform inline expansion. The compiler is completely free to ignore the request, and it may very well do so. The compiler is also free to perform inline expansion of functions that do not use the `inline` keyword as part of its normal set of optimizations.
- The `inline` keyword is defined at the wrong level of granularity. We use the `inline` keyword on a function definition, but inline expansion is actually determined per function call. It may be beneficial to expand some function calls and detrimental to expand others, and there is no syntax to influence this.

Modern optimizing compilers are typically good at determining which function calls should be made inline -- better than humans in most cases. As a result, the compiler will likely ignore or devalue any use of `inline` to request inline expansion for your functions.

>[!best practice]
>Do not use the `inline` keyword to request inline expansion for your functions.

---
### The inline keyword, modernly

>In previous chapters, we mentioned that you should not implement functions (with external linkage) in header files, because when those headers are included into multiple .cpp files, the function definition will be copied into multiple .cpp files. These files will then be compiled, and the linker will throw an error because it will note that you’ve defined the same function more than once, which is a violation of the one-definition rule.

In modern C++, the term `inline` has evolved to mean “multiple definitions are allowed”. Thus, an inline function is one that is allowed to be defined in multiple translation units (without violating the ODR).

>Inline functions have two primary requirements:

>[!tip]
>The compiler needs to be able to see the full definition of an inline function wherever it is used(current translational unit), and all definitions for an inline function (with external linkage) must be identical (or undefined behavior will result).
>[Rules](https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/#:~:text=Inline%20functions%20have,behavior%20will%20result.)

The linker will consolidate all inline function definitions for an identifier into a single definition (thus still meeting the requirements of the one definition rule).

Example:

main.cpp

```cpp
#include <iostream>

double circumference(double radius); // forward declaration

inline double pi() { return 3.14159; }

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

math.cpp

```cpp
inline double pi() { return 3.14159; }

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

Notice that both files have a definition for function `pi()` -- however, because this function has been marked as `inline`, this is acceptable, and the linker will de-duplicate them. If you remove the `inline` keyword from both definitions of `pi()`, you’ll get an ODR violation (as duplicate definitions for non-inline functions are disallowed).

>Inline functions are typically defined in header files, where they can be #included into the top of any code file that needs to see the full definition of the identifier. This ensures that all inline definitions for an identifier are identical.

pi.h

```cpp
#ifndef PI_H
#define PI_H

inline double pi() { return 3.14159; }

#endif 

```

main.cpp

```cpp
#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

math.cpp

```cpp
#include "pi.h" // will include a copy of pi() here

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

>This is particularly useful for **header-only libraries**, which are one or more header files that implement some capability (no .cpp files are included). Header-only libraries are popular because there are no source files that need to be added to a project to use them and nothing that needs to be linked. You simply #include the header-only library and then can use it.

>[!best practice]
>Avoid the use of the `inline` keyword unless you have a specific, compelling reason to do so (e.g. you’re defining those functions or variables in a header file).

## ✅ Reasons We Need Function Definitions in Header Files

### 1. **Templates Require It**

💡 **Function templates must be defined in the header**, because:

- The compiler needs to **see the full definition** when it generates code for a specific type.

```cpp
// math.h
template <typename T>
T square(T x) {
    return x * x;
}

```

If you only put the **declaration** in the header and the **definition** in the `.cpp`, you’ll get linker errors.

### 2. **Inline Functions**

If you want to define **small utility functions** that are:

- Used in many files
    
- Possibly inlined by the compiler
    

Then you define them in the header using the `inline` keyword.

```cpp
// math.h
inline int square(int x) {
    return x * x;
}

```

This avoids:

- Repeating the same code in multiple `.cpp` files
    
- Linker errors from ODR violations

---
### Why not make all functions inline and defined in a header file?

Mainly because doing so can increase your compile times significantly.

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

When a header containing an inline function is #included into a source file, that function definition will be compiled as part of that translation unit. An inline function #included into 6 translation units will have its definition compiled 6 times (before the linker deduplicates the definitions). Conversely, a function defined in a source file will have its definition compiled only once, no matter how many translation units its forward declaration is included into.

Second, if a function defined in a source file changes, only that single source file needs to be recompiled. When an inline function in a header file changes, every code file that includes that header (either directly or via another header) needs to recompiled. On large projects, this can cause a cascade of recompilation and have a drastic impact.

---
### Sharing global constants across multiple files (using inline variables)

>Somtimes we need to use some constant not only in one place but throughout the program so we dont have to change the value of that constant in every place instead we can only change the value in one place and the value will be changed everywhere.

### Global constants as internal variables

>Prior to C++ 17, the following was the easiest and most common solution:

```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define your own namespace to hold constants
namespace constants
{
    // Global constants have internal linkage by default
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```
Then use the scope resolution operator to access the global variable from the namespace.

```cpp
#include "constants.h" // include a copy of each constant in this file

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

>Because const globals have internal linkage, each .cpp file gets an independent version of the global variable that the linker can’t see. In most cases, because these are constexpr, the compiler will simply optimize the variables away.

>While this is simple (and fine for smaller programs), every time _constants.h_ gets #included into a different code file, each of these variables is copied into the including code file. Therefore, if constants.h gets included into 20 different code files, each of these variables is duplicated 20 times. Header guards won’t stop this from happening, as they only prevent a header from being included more than once into a single including file, not from being included one time into multiple different code files. This introduces two challenges:
>>-  Changing a single constant value would require recompiling every file that includes the constants header, which can lead to lengthy rebuild times for larger projects.
>>-  If the constants are large in size and can’t be optimized away, this can use a lot of memory.

--> Downsides:

- Changing anything in the header file requires recompiling files including the header.
- Each translation unit including the header gets its own copy of the variable.

---
### Global constants as external variables

> If you’re actively changing values or adding new constants, the prior solution might be problematic, at least until things settle.
> One way to avoid these problems is by turning these constants into external variables, since we can then have a single variable (initialized once) that is shared across all files. In this method, we’ll define the constants in a .cpp file (to ensure the definitions only exist in one place), and put forward declarations in the header (which will be included by other files).

constants.cpp

```cpp
#include "constants.h"

namespace constants
{
    // We use extern to ensure these have external linkage
    extern constexpr double pi { 3.14159 };
    extern constexpr double avogadro { 6.0221413e23 };
    extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
}
```

constants.h

```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    // Since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
    // We can't forward declare variables as constexpr, but we can forward declare them as (runtime) const
    extern const double pi;
    extern const double avogadro;
    extern const double myGravity;
}

#endif
```

main.cpp:

```cpp
#include "constants.h" // include all the forward declarations

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

>Now the symbolic constants will get instantiated only once (in _constants.cpp_) instead of in each code file where _constants.h_ is #included, and all uses of these constants will be linked to the version instantiated in _constants.cpp_. Any changes made to _constants.cpp_ will require recompiling only _constants.cpp_.

>However, there are a couple of downsides to this method. First, because only the variable definitions are constexpr (the forward declarations aren’t, and can’t be), these constants are constant expressions only within the file they are actually defined in (_constants.cpp_). In other files, the compiler will only see the forward declaration, which doesn’t define a constexpr value (and must be resolved by the linker). This means outside of the file where they are defined, these variables can’t be used in a constant expression. Second, because constant expressions can typically be optimized more than runtime expressions, the compiler may not be able to optimize these as much.

>[!tip]
>In order for variables to be usable in compile-time contexts, such as array sizes, the compiler has to see the variable’s definition (not just a forward declaration).

>[!warning]
> You **can** define a global variable as `extern constexpr` in a `.cpp` file and use it across the program. In the header file, you can forward declare it using `extern const` instead of `constexpr`, because:
> 
> 🔸 A file using the variable must **see the full `constexpr` definition** to allow compile-time evaluation.
> 
> 🔸 Without seeing the definition, the compiler **treats it as a runtime constant**, not a `constexpr`.
> 
> So, in practice, the variable behaves as just another runtime `const`, **not a `constexpr`**, in any translation unit that doesn’t see the definition.

>[!tip]
>> The **main downside** of using `extern` for `constexpr` global variables is that **other translation units can't use them in `constexpr` contexts**, **unless the full definition is visible**.
>

Example of that: 

main.cpp

```cpp
#include <string>

#include <string_view>

#include <iostream>

// #include <./constant.h>

extern const double pi;
// here you can see i didnt use constexpr becuase it would have given me error.
  

using namespace std;

  

int main() {

  

double rad {2.2};

double cal = rad * pi;

cout << cal << endl;

return 0;

}
```

constant.cpp

```cpp
constexpr double pi;
```

>[!tip]
>variable definitions in _constants.cpp_ are not visible when the compiler compiles _main.cpp_. For this reason, constexpr variables cannot be separated into header and source file, they have to be defined in the header file.

>[!tip]
> Only requires recompilation of one file if the value of a constant changes.

>[!warning]
>- Forward declarations and variable definitions are in separate files, and must be kept in sync.
Variables not usable in constant expressions outside of the file in which they are defined.


---

### Global constants as inline variables C++17

>inline variables that can have more than one definition, so long as those definitions are identical.

>By making our constexpr variables inline, we can define them in a header file and then #include them into any .cpp file that requires them. This avoids both ODR violations and the downside of duplicated variables.

>[!tip]
>We dont need to forward declare the variable because defination plays both rules (Defination + Declaration) at the same time.

>[!Reminder]
>Constexpr functions are implicitly inline, but constexpr variables are not implicitly inline. If you want an inline constexpr variable, you must explicitly mark it as `inline`.

####  ✅ When You **Can** Put Function Definitions in a Header

You **can safely put a function definition in a header file** if:

1. The function is declared `inline`, or
    
2. The function is a `constexpr` function, or
    
3. The function is a **template function**

>Inline variables have external linkage by default, so that they are visible to the linker. This is necessary so the linker can de-duplicate the definitions.
>Non-inline constexpr variables have internal linkage. If included into multiple translation units, each translation unit will get its own copy of the variable. This is not an ODR violation because they are not exposed to the linker.

>Why do we need to make them inline then:
>To make them have external linkage so it doesnt make copy everytime it is added...

> 🧠 **Changing a header file causes all `.cpp` files that include it to be recompiled — regardless of the linkage of the variables inside it.**
> But the difference between inline constexpr which has external linkage and constexpr which has internal linkage is that inline will produce one copy which is shared throuhout the program while constexpr will produce each copy for .cpp it is in included.


constant.h

```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr double pi { 3.14159 }; // note: now inline constexpr
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

main.cpp

```cpp
#include "constants.h"

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

We can include `constants.h` into as many code files as we want, but these variables will only be instantiated once and shared across all code files

>This method does retain the downside of requiring every file that includes the constants header be recompiled if any constant value is changed.

Advantages:

- Can be used in constant expressions in any translation unit that includes them.
- Only one copy of each variable is required.

Downsides:

- Only works in C++17 onward.
- Changing anything in the header file requires recompiling files including the header.

>[!best practice]
>If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file.

>[!tip]
>Use `std::string_view` for `constexpr` strings.
>
>>`std::string` :  It’s **not usable in a `constexpr` context** because it involves runtime memory management.
>> You cannot make a `constexpr std::string` because it’s not a literal type.
>
>>`std::string_view`: - ✅ This **does compile** and is **fully `constexpr`-friendly**.
>> `std::string_view` is a **non-owning, lightweight view** into a string.
>>It can point to string literals (like `"Alice"`) that exist at compile time.

---

### Static local variables

> The term static has different meaning and it depends on context like for example we studied earlier that global variables have static duration which means they are created when program starts and ends when program ends and later we studied that static keyword is used to give internal linkage to non-const variable which have external linkage by default.

-->  We will be discussing about static keyword onward:

### Static local variables

>local variable by default have automatic duration which means they are created at the declaration and destroyed at the end of block but by making them static they will have internal linkage This means the variable is now created at the start of the program, and destroyed at the end of the program (just like a global variable). As a result, the static variable will retain its value even after it goes out of scope!

Example:

```cpp
#include <iostream>

void incrementAndPrint()
{
    int value{ 1 }; // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```

Each time `incrementAndPrint()` is called, a variable named value is created and assigned the value of `1`. `incrementAndPrint()` increments value to `2`, and then prints the value of `2`. When `incrementAndPrint()` is finished running, the variable goes out of scope and is destroyed. Consequently, this program outputs:

2
2
2

Now consider a version of this program that uses a static local variable. The only difference between this and the above program is that we’ve changed the local variable from automatic duration to static duration by using the `static` keyword.

```cpp
#include <iostream>

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```

In this program, because `s_value` has been declared as `static`, it is created at the program start.

>A **`static` local variable** is declared inside a function but retains its value **between function calls** and is **initialized only once**.

Because `s_value` has constexpr initializer `1`, `s_value` will be initialized at program start.

When `s_value` goes out of scope at the end of the function, it is not destroyed. Each time the function `incrementAndPrint()` is called, the value of `s_value` remains at whatever we left it at previously. Consequently, this program outputs:

>[!key insight]
>Static local variables are used when you need a local variable to remember its value across function calls.

>[!best practice]
>Initialize your static local variables. Static local variables are only initialized the first time the code is executed, not on subsequent calls.

>[!tip]
>Just like we use “g_” to prefix global variables, it’s common to use “s_” to prefix static (static duration) local variables.

---
### when and how static local variables are initialized

#### ✅ CASE 1: **Constexpr or Zero Initializer → Initialized at Program Start**

**Static local variables with:**

- a **`constexpr` initializer**
    
- or a **zero initializer** (`= 0`, `= {}` or no initializer at all)
    

➡️ **Are initialized at program start** (before `main()` runs).

This is known as **constant initialization** and happens at **compile time or static initialization phase**.

##### ✅ Example 1: constexpr initializer

```cpp
void f() {
    static int s_value = 1;  // constexpr initializer
}

```
Here, `1` is a `constexpr`. So `s_value` will be initialized **at program start**.

##### ✅ Example 2: zero initializer

```cpp
void f() {
    static int s_value;  // no initializer = zero-initialized
}

```
Here, `s_value` will be **zero-initialized at program start**.


#### ❗ CASE 2: **Non-constexpr Initializer → Initialized on First Use**

If the initializer is **not a `constexpr`**, the static local variable:

- is **zero-initialized** at program start (for safety)
    
- then **re-initialized** (i.e., constructed) **only once**, the **first time the definition is encountered**
    

This is called **dynamic initialization**.

##### ❗ Example 3: Non-constexpr initializer

```cpp
int getValue() {
    return 42;
}

void f() {
    static int s_value = getValue();  // not constexpr
}

```

Here:

- `s_value` is **zero-initialized at program start** (i.e., set to 0)
    
- Then the first time `f()` is called, `getValue()` is called and assigns 42 to `s_value`
    
- Any further calls **skip the initialization**

>[!tip]
>Once a **`static` local variable** has been **initialized**, that initialization **will not happen again** — even if the function is called multiple times.

---
### ID generation

#### [Read but easy](https://www.learncpp.com/cpp-tutorial/static-local-variables/#:~:text=One%20of%20the%20most%20common,understand%20and%20safer%20to%20use.)

>[!tip]
>A static local variable has block scope like a local variable, but its lifetime is until the end of the program like a global variable.

---

### Static local constants

> You can make a `static` local variable also `const` or `constexpr`.

This is useful when:

- You want to **reuse a value** across function calls
    
- The value is **expensive to create** (e.g., reading from a file or database, allocating memory, doing a big computation)

```cpp
void expensiveFunction() {
    const int value = readFromDatabase();  // Hypothetical function
    std::cout << value << "\n";
}

```
>If you call `expensiveFunction()` 100 times, it will **read from the database 100 times**, which is inefficient.

#### ✅ Static const local variable: Initialized once

```cpp
void optimizedFunction() {
    static const int value = readFromDatabase();  // initialized once
    std::cout << value << "\n";
}

```

Now:

- `value` is created only **once**
    
- On all future calls, the function will **reuse** the already-initialized value
    
- This improves **performance**


>[!tip]
>Static local variables are best used to avoid expensive local object initialization each time a function is called.

---
### Don’t use static local variables to alter flow

```cpp
#include <iostream>

int getInteger()
{
	static bool s_isFirstCall{ true };

	if (s_isFirstCall)
	{
		std::cout << "Enter an integer: ";
		s_isFirstCall = false;
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}

int main()
{
	int a{ getInteger() };
	int b{ getInteger() };

	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	return 0;
}
```

#### [Read](https://www.learncpp.com/cpp-tutorial/static-local-variables/#:~:text=Sample%20output,%3B%0A%0A%09return%200%3B%0A%7D)

>Non-const static local variables should only be used if in your entire program and in the foreseeable future of your program, the variable is unique and it wouldn’t make sense to reset the variable.

>[!tip]
>Const static local variables are generally okay to use.
>Non-const static local variables should generally be avoided. If you do use them, ensure the variable never needs to be reset, and isn’t used to alter program flow.

---
### Scope, duration, and linkage summary
#### [Summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/#:~:text=LEARN%20C%2B%2B,%E2%9A%99)

---
### Using declarations and using directives

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!\n";

    return 0;
}
```

>If you see this, run. Your textbook or tutorial are probably out of date. In this lesson, we’ll explore why.

#### [A short history lesson](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/#:~:text=Back%20before%20C,define%20two%20terms.)

### Qualified and unqualified names

>A **qualified name** is a name that includes an associated scope. Most often, names are qualified with a namespace using the scope resolution operator (::). For example:

```cpp
std::cout // identifier cout is qualified by namespace std
::foo // identifier foo is qualified by the global namespace
```

>An **unqualified name** is a name that does not include a scoping qualifier. For example, `cout` and `x` are unqualified names, as they do not include an associated scope.

---
### Using-declarations

>One way to reduce the repetition of typing `std::` over and over is to utilize a using-declaration statement. A **using declaration** allows us to use an unqualified name (with no scope) as an alias for a qualified name.

```cpp
#include <iostream>

int main()
{
   using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
   cout << "Hello world!\n"; // so no std:: prefix is needed here!

   return 0;
} // the using declaration expires at the end of the current scope
```

>The using-declaration `using std::cout;` tells the compiler that we’re going to be using the object `cout` from the `std` namespace. So whenever it sees `cout`, it will assume that we mean `std::cout`. If there’s a naming conflict between `std::cout` and some other use of `cout` that is visible from within `main()`, `std::cout` will be preferred. Therefore on line 6, we can type `cout` instead of `std::cout`.

>The using-declaration is active from the point of declaration to the end of the scope in which it is declared.

---
### Using-directives

>Another way to simplify things is to use a using-directive. A **using directive** allows _all_ identifiers in a given namespace to be referenced without qualification from the scope of the using-directive.
>eg: like we do mostly in our programs:
>`using namespace std;`

```cpp
#include <iostream>

int main()
{
   using namespace std; // all names from std namespace now accessible without qualification
   cout << "Hello world!\n"; // so no std:: prefix is needed here

   return 0;
} // the using-directive ends at the end of the current scope
```

>a single using-directive (`using namespace std;`) could be placed at the top of each file, and all of the names that had been moved to the `std` namespace could still be used unqualified.

---
### Problems with using-directives aka why you should avoid "using namespace std;"

>the possibility for naming collisions to occur increases significantly (especially if you import the `std` namespace).

>Using-directives allow unqualified access to _all_ of the names from a namespace (potentially including lots of names you’ll never use).

Foolib.h

```cpp
#ifndef FOOLIB_H
#define FOOLIB_H

namespace Foo
{
    int a { 20 };

    int get(int) { return 2; } // new function added
}
#endif
```

main.cpp

```cpp
#include <iostream>
#include <Foolib.h> // a third-party library we installed outside our project directory, thus angled brackets used

int get(long)
{
    return 1;
}

int main()
{
    using namespace Foo; // Because we're lazy and want to access Foo:: qualified names without typing the Foo:: prefix
    std::cout << a << '\n'; // uses Foo::a

    std::cout << get(0) << '\n'; // calls ::get(long)

    return 0;
}
```

>When the compiler encounters a function call, it has to determine what function definition it should match the function call with. In selecting a function from a set of potentially matching functions, it will prefer a function that requires no argument conversions over a function that requires argument conversions. Because the literal `0` is an integer, C++ will prefer to match `print(0)` with the newly introduced `print(int)` (no conversions) over `print(long)` (which requires a conversion from `int` to `long`). That causes an unexpected change to our program behavior.

#### [Read](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/#:~:text=Problems%20with%20using,not%20a%20guarantee)

---
### The scope of  `using-statements`

>If a using-declaration or using-directive is used within a block, the names are applicable to just that block (it follows normal block scoping rules). This is a good thing, as it reduces the chances for naming collisions to occur to just within that block.

>If a using-declaration or using-directive is used in a namespace (including the global namespace), the names are applicable to the entire rest of the file (they have file scope).

---
### Do not use using-statements in header files, or before an #include directive

>using-statements should not be used in header files, nor before an #include directive.

>For example, if you placed a using-statement in the global namespace of a header file, then every other file that #included that header would also get that using-statement. That’s clearly bad. This also applies to namespaces inside header files, for the same reason.

>[!tip]
>We should also avoid using using-statement inside function defination which is held in header files.

>It turns out that the behavior of using-statements is dependent on what identifiers have already been introduced. This makes them order-dependent, as their function may change if the identifiers that have been introduced before them change.

--> Example:

Foolnt.h

```cpp
namespace Foo
{
    void print(int)
    {
        std::cout << "print(int)\n" << std::endl;
    }
}
```

FooDouble.h

```cpp
namespace Foo
{
    void print(double)
    {
        std::cout << "print(double)\n" << std::endl;
    }
}
```

main.cpp (Okay)

```cpp
#include <iostream>

#include "FooDouble.h"
#include "FooInt.h"

using Foo::print; // print means Foo::print

int main()
{
    print(5);  // Calls Foo::print(int)
}
```

When run, this program calls `Foo::print(int)`, which prints `print(int)`.

Now let’s change main.cpp slightly.

main.cpp (BAD)

```cpp
#include <iostream>

#include "FooDouble.h"

using Foo::print; // we moved the using-statement here, before the #include directive
#include "FooInt.h"

int main()
{
    print(5);  // Calls Foo::print(double)
}
```

>All we’ve done is move `using Foo::print;` before `#include "FooInt.h"`. And our program now prints `print(double)`! Regardless of why this happens, you’ll likely agree that this is the kind of behavior we want to avoid!

>So then to loop back around, the reason we shouldn’t use using-statements in functions that are defined in header files is the same reason -- we can’t control which other headers might be #included before our header, and it’s possible those headers might do something that alters the way our using-statement behaves!

>The only place it is truly safe to use using-statements is in our source (.cpp) files, after all the #includes.

---
### Cancelling or replacing a using-statement

>Once a using-statement has been declared, there’s no way to cancel or replace it with a different using-statement within the scope in which it was declared.

```cpp
int main()
{
    using namespace Foo;

    // there's no way to cancel the "using namespace Foo" here!
    // there's also no way to replace "using namespace Foo" with a different using statement

    return 0;
} // using namespace Foo ends here
```

The best you can do is intentionally limit the scope of the using-statement from the outset using the block scoping rules.

```cpp
int main()
{
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // using namespace Foo expires

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // using namespace Goo expires

    return 0;
}
```

>[!tip]
>Of course, all of this headache can be avoided by explicitly using the scope resolution operator (::) in the first place.

>[!Best Practice]
>Prefer explicit namespace qualifiers over using-statements.
Avoid using-directives altogether (except `using namespace std::literals` to access the `s` and `sv` literal suffixes). Using-declarations are okay in .cpp files, after the #include directives. Do not use using-statements in header files (especially in the global namespace of header files).

---

### Unnamed and inline namespaces

>This lesson is optional, you just have to know about this...

>An **unnamed namespace** (also called an **anonymous namespace**) is a namespace that is defined without a name, like so:

```cpp
#include <iostream>

namespace // unnamed namespace
{
    void doSomething() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```
This prints:

v1

>All content declared in an unnamed namespace is treated as if it is part of the parent namespace. So even though function `doSomething()` is defined in the unnamed namespace, the function itself is accessible from the parent namespace (which in this case is the global namespace), which is why we can call `doSomething()` from `main()` without any qualifiers.

>This might make unnamed namespaces seem useless. But the other effect of unnamed namespaces is that all identifiers inside an unnamed namespace are treated as if they have internal linkage, which means that the content of an unnamed namespace can’t be seen outside of the file in which the unnamed namespace is defined.

>For functions, this is effectively the same as defining all functions in the unnamed namespace as static functions. The following program is effectively identical to the one above:

```cpp
#include <iostream>

static void doSomething() // can only be accessed in this file
{
    std::cout << "v1\n";
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```

---> Use:
>Unnamed namespaces are typically used when you have a lot of content that you want to ensure stays local to a given translation unit, as it’s easier to cluster such content in a single unnamed namespace than individually mark all declarations as `static`. Unnamed namespaces will also keep program-defined types (something we’ll discuss in a later lesson) local to the translation unit, something for which there is no alternative equivalent mechanism to do.

>[!tip]
>Prefer unnamed namespaces when you have content you want to keep local to a translation unit.
>Avoid unnamed namespaces in header files.

---

### Inline Namespace

```cpp
#include <iostream>

void doSomething()
{
    std::cout << "v1\n";
}

int main()
{
    doSomething();

    return 0;
}
```
v1

>But let’s say you’re not happy with `doSomething()`, and you want to improve it in some way that changes how it behaves. But if you do this, you risk breaking existing programs using the older version. How do you handle this?

>One way would be to create a new version of the function with a different name. But over the course of many changes, you could end up with a whole set of almost-identically named functions (`doSomething`, `doSomething_v2`, `doSomething_v3`, etc…).

>An alternative is to use an inline namespace. An **inline namespace** is a namespace that is typically used to version content. Much like an unnamed namespace, anything declared inside an inline namespace is considered part of the parent namespace. However, unlike unnamed namespaces, inline namespaces don’t affect linkage.

```cpp
#include <iostream>

inline namespace V1 // declare an inline namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V1)

    return 0;
}
```

This prints:

V1
V2
V1

>In the above example, callers to `doSomething()` will get the V1 (the inline version) of `doSomething()`. Callers who want to use the newer version can explicitly call `V2::doSomething()`. This preserves the function of existing programs while allowing newer programs to take advantage of newer/better variations.

---
