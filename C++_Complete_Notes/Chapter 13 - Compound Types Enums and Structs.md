### Introduction to program-defined (user-defined) types

>Because fundamental types are defined as part of the core C++ language, they are available for immediate use. For example, if we want to define a variable with a type of `int` or `double`, we can just do so:

```cpp
int x; // define variable of fundamental type 'int'
double d; // define variable of fundamental type 'double'
```

This is also true for the compound types that are simple extensions of fundamental types (including functions, pointers, references, and arrays):

```cpp
void fcn(int) {}; // define a function of type void(int)
int* ptr; // define variable of compound type 'pointer to int'
int& ref { x }; // define variable of compound type 'reference to int' (initialized with x)
int arr[5]; // define an array of 5 integers of type int[5] (we'll cover this in a future chapter)
```

This works because the C++ language already knows what the type names (and symbols) for these types mean -- we do not need to provide or import any definitions.

However, consider the case of a type alias (introduced in lesson [10.7 -- Typedefs and type aliases](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)), which allows us to define a new name for an existing type. Because a type alias introduces a new identifier into the program, a type alias must be defined before it can be used:

```cpp
#include <iostream>

using Length = int; // define a type alias with identifier 'Length'

int main()
{
    Length x { 5 }; // we can use 'length' here since we defined it above
    std::cout << x << '\n';

    return 0;
}
```

If we were to omit the definition of `Length`, the compiler wouldn’t know what a `Length` is, and would complain when we try to define a variable using that type. The definition for `Length` doesn’t create an object -- it just tells the compiler what a `Length` is so it can be used later.

>[!Note]
>The definition for `Length` doesn’t create an object -- it just tells the compiler what a `Length` is so it can be used later.

---
### What are user-defined / program-defined types?

>Back in the introduction to the previous chapter ([12.1 -- Introduction to compound data types](https://www.learncpp.com/cpp-tutorial/introduction-to-compound-data-types/)), we introduced the challenge of wanting to store a fraction, which has a numerator and denominator that are conceptually linked together. In that lesson, we discussed some of the challenges with using two separate integers to store a fraction’s numerator and denominator independently.

Example:

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

But in this both variables are different and are dependent on each other so many mistakes can happen.

>If C++ had a built-in fraction type, that would have been perfect -- but it doesn’t. And there are hundreds of other potentially useful types that C++ doesn’t include because it’s just not possible to anticipate everything that someone might need (let alone implement and test those things).

Instead, C++ solves such problems in a different way: by allowing the creation of entirely new, custom types that we can use in our programs! Such types are called **user-defined types**. However, as we will discuss later in this lesson, we’ll prefer the term **program-defined types** for any such types that we create for use in our own programs.

>C++ has two different categories of compound types that can be used to create program-defined types:

- Enumerated types (including unscoped and scoped enumerations)
- Class types (including structs, classes, and unions).

>[!Note]
>They’re called **compound types** because they are made by **combining multiple pieces of data into one unit** — instead of holding a single, simple value like an `int` or `char`.

---
### Defining program-defined types

>Just like type aliases, program-defined types must also be defined and given a name before they can be used. The definition for a program-defined type is called a **type definition**.

>[!Key Insight]
>A program-defined type must have a name and a definition before it can be used. The other compound types require neither.
Functions aren’t considered user-defined types (even though they require a name and a definition before they can be used) because it is the function itself being given a name and a definition, not the function’s type. Functions that we define ourselves are called user-defined functions instead.

Although we haven’t covered what a struct is yet, here’s an example showing the definition of custom Fraction type and an instantiation of an object using that type:

```cpp
// Define a program-defined type named Fraction so the compiler understands what a Fraction is
// (we'll explain what a struct is and how to use them later in this chapter)
// This only defines what a Fraction type looks like, it doesn't create one
struct Fraction
{
	int numerator {};
	int denominator {};
};

// Now we can make use of our Fraction type
int main()
{
	Fraction f { 3, 4 }; // this actually instantiates a Fraction object named f

	return 0;
}
```

>In this example, we’re using the `struct` keyword to define a new program-defined type named `Fraction` (in the global scope, so it can be used anywhere in the rest of the file). This doesn’t allocate any memory -- it just tells the compiler what a `Fraction` looks like, so we can allocate objects of a `Fraction` type later. Then, inside `main()`, we instantiate (and initialize) a variable of type `Fraction` named `f`.

>[!Warning]
>Don’t forget to end your type definitions with a semicolon.

>[!Best Practice]
>Name your program-defined types starting with a capital letter and do not use a suffix.

---
### Using program-defined types throughout a multi-file program

>[!Best Practice]
>A program-defined type used in only one code file should be defined in that code file as close to the first point of use as possible.
>A program-defined type used in multiple code files should be defined in a header file with the same name as the program-defined type and then #included into each code file as needed.

Fraction.h

```cpp
#ifndef FRACTION_H
#define FRACTION_H

// Define a new type named Fraction
// This only defines what a Fraction looks like, it doesn't create one
// Note that this is a full definition, not a forward declaration
struct Fraction
{
	int numerator {};
	int denominator {};
};

#endif 
```

---
### Type definitions are partially exempt(free) from the one-definition rule (ODR)

In lesson [2.7 -- Forward declarations and definitions](https://www.learncpp.com/cpp-tutorial/forward-declarations/#ODR), we discussed how the one-definition rule requires that each function and global variable only have one definition per program. To use a given function or global variable in a file that does not contain the definition, we need a forward declaration (which we typically propagate via a header file). This works because declarations are enough to satisfy the compiler when it comes to functions and non-constexpr variables, and the linker can then connect everything up.

However, using forward declarations in a similar manner doesn’t work for types, because the compiler typically needs to see the full definition to use a given type. We must be able to propagate the full type definition to each code file that needs it.

To allow for this, types are partially exempt(free) from the one-definition rule: a given type is allowed to be defined in multiple code files.

You’ve already exercised this capability (likely without realizing it): if your program has two code files that both `#include <iostream>`, you’re importing all of the input/output type definitions into both files.

There are two caveats that are worth knowing about. First, you can still only have one type definition per code file (this usually isn’t a problem since header guards will prevent this). Second, all of the type definitions for a given type must be identical , otherwise undefined behavior will result.

>[!Rule]
>(program-defined types allows to have multiple defination across different translational units but that defination had to be identical in every unit...)

---
### user-defined types vs program-defined types

>The C++ language standard uses the term “user-defined type” in a non-conventional manner. In the language standard, a “user-defined type” is any class type or enumerated type that is defined by you, the standard library, or the implementation (e.g. types defined by the compiler to support language extensions). Perhaps counter-intuitively, this means `std::string` (a class type defined in the standard library) is considered to be a user-defined type!

To provide additional differentiation, the C++20 language standard helpfully defines the term “program-defined type” to mean class types and enumerated types that are not defined as part of the standard library, implementation, or core language. In other words, “program-defined types” only include class types and enum types that are defined by us (or a third-party library).

Consequently, when talking only about class types and enum types that we’re defining for use in our own programs, we’ll prefer the term “program-defined”, as it has a more precise definition.

| Type            | Meaning                                                                                                                                                                    | Examples                                          |
| --------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------- |
| Fundamental     | A basic type built into the core C++ language                                                                                                                              | int, std::nullptr_t                               |
| Compound        | A type defined in terms of other types                                                                                                                                     | int&, double*, std::string, Fraction(is a struct) |
| User-defined    | A class type or enumerated type  <br>(Includes those defined in the standard library or implementation)  <br>(In casual use, typically used to mean program-defined types) | std::string, Fraction                             |
| Program-defined | A class type or enumerated type  <br>(Excludes those defined in standard library or implementation)                                                                        | Fraction                                          |

---
### Unscoped enumerations

#### **1. The Problem**

We sometimes want a variable to hold **one value from a fixed set of options**.  
Example:

- Apple color can only be red, green, or yellow
    
- Shirt color can only be from a fixed color list

#### **2. The Naive Way: Using integers**

```cpp
int appleColor{ 0 }; // 0 = red
int shirtColor{ 1 }; // 1 = green
```

- You use integers to represent colors.
    
- You need an **implicit mapping** (0 = red, 1 = green, etc.).
    
- This is hard to read and easy to mess up — these integers are called **magic numbers**.

#### **3. Slightly Better: Symbolic constants**

```cpp
constexpr int red{ 0 };
constexpr int green{ 1 };
constexpr int blue{ 2 };

int appleColor{ red };
int shirtColor{ green };
```

- This replaces magic numbers with **named constants**.
    
- More readable, but the compiler still treats these as plain `int`s.
    
- Nothing stops you from writing `appleColor = 42;` (which makes no sense for a color).

#### **4. Another Improvement: Type alias**

```cpp
using Color = int;

constexpr Color red{ 0 };
constexpr Color green{ 1 };
constexpr Color blue{ 2 };

Color appleColor{ red };
Color shirtColor{ green };
```

- Now there’s a **named type** `Color` instead of plain `int`.
    
- Slightly clearer, but still just an alias for `int`.
    
- The compiler won’t prevent you from doing:
```cpp
Color eyeColor{ 8 }; // still valid but meaningless
```
- Debuggers will still only show the number (e.g., `0`) instead of the name (`red`).

#### **5. The Ideal: Like `bool`**

The `bool` type is a **well-designed type** because:

1. **Restricted valid values** — you can only store `true` or `false` in it.
    
2. **Compiler enforcement** — the compiler stops you from assigning invalid values.
    
3. **Readable debugging** — debuggers show `true`/`false` instead of raw numbers.
    
4. **Special handling in functions** — functions can treat it differently from other numeric types.
    

The lesson here is: when you create your own types (using `enum`, `struct`, or later `class`), you should **try to design them like `bool`** — with clear meaning, limited valid values, and compiler checks that prevent invalid usage.

It’s basically saying: _If your type is as safe and clear as `bool`, you’ve done it right._ ✅

--> Example:

```cpp
#include <iostream>

// Our bool-like type
enum LightSwitch {
    Off = 0,
    On = 1
};

void toggle(LightSwitch state) {
    if (state == On) {
        std::cout << "Light is now OFF\n";
    } else {
        std::cout << "Light is now ON\n";
    }
}

int main() {
    LightSwitch lamp = Off;  // Only valid values: Off or On

    // Works fine
    toggle(lamp);

    // Uncomment this and the compiler will complain:
    // lamp = 2; // ❌ invalid, not On or Off

    lamp = On;  // ✅ valid
    toggle(lamp);

    return 0;
}

```

#### **6. The Need for a Better Solution**

What we really want is:

- A **custom type** for colors
    
- A fixed set of **named values** it can hold
    
- Compiler enforcement so invalid values can’t be assigned
    
- Better readability in debugging and code
    

That’s exactly where **enumerated types (`enum`)** come in — they let you define a type with a fixed set of named values that the compiler can check.

---
### Enumerations

#### **1. What an Enumeration Is**

- An **enumeration** (or **enum**) is a **program-defined compound type**.
    
- Its values are restricted to a **specific set of named symbolic constants** (called **enumerators**).
    
- Example: If you make a `Color` enum with `{ red, green, blue }`, then **only** those three values are valid for a `Color` variable.
    

#### **2. Why They Exist**

- Without enums, we’d use integers or constants to represent a fixed set of values (like colors), but that’s unsafe — the compiler can’t stop you from assigning meaningless numbers.
    
- Enums make the compiler enforce that variables of that type only hold valid, named values.
    

#### **3. Unscoped Enums**

- Declared with the `enum` keyword.
    
- Syntax

```cpp
enum Color
{
    red,
    green,
    blue, // trailing comma optional
};
```

- **`Color`** is the enumeration type (the custom type you just made).
    
- **`red`, `green`, `blue`** are **enumerators** (the allowed named values for that type).

#### **4. Key Rules**

- You **must** define the enum **before** you use it (no forward declaration like you can with functions).
    
- Inside the curly braces `{}`, list the **enumerators**, separated by commas (not semicolons).
    
- End the whole enum definition with a semicolon `;`.
    

#### **5. How It Works in Code**

```cpp
Color apple{ red };   // ✅ valid — red is in Color
Color shirt{ green }; // ✅ valid — green is in Color
Color cup{ blue };    // ✅ valid — blue is in Color

Color socks{ white }; // ❌ error — white is not in Color
Color hat{ 2 };       // ❌ error — integers aren't valid here
```

- The compiler will **reject** assignments with values not in the enum.

#### **6. Other Notes**

- Enumerators are **implicitly `constexpr`**, meaning they’re constant expressions that can be used at compile time.
    
- By convention:
    
    - **Enumeration** = the type (e.g., `Color`)
        
    - **Enumerator** = the individual value (e.g., `red`, `green`)

---
### Naming enumerations and enumerators

>[!Best Practice]
>Name your enumerated types starting with a capital letter. Name your enumerators starting with a lower case letter.

---
### Enumerated types are distinct types

Each enumerated type you create is considered to be a **distinct type**, meaning the compiler can distinguish it from other types (unlike typedefs or type aliases, which are considered non-distinct from the types they are aliasing).

Because enumerated types are distinct, enumerators defined as part of one enumerated type can’t be used with objects of another enumerated type:

```cpp
enum Pet
{
    cat,
    dog,
    pig,
    whale,
};

enum Color
{
    black,
    red,
    blue,
};

int main()
{
    Pet myPet { black }; // compile error: black is not an enumerator of Pet
    Color shirt { pig }; // compile error: pig is not an enumerator of Color

    return 0;
}
```

You probably didn’t want a pig shirt anyway.

---
### Putting enumerations to use

Because enumerators are descriptive, they are useful for enhancing code documentation and readability. Enumerated types are best used when you have a smallish set of related constants, and objects only need to hold one of those values at a time.

Commonly defined enumerations include days of the week, the cardinal directions, and the suits in a deck of cards:

```cpp
enum DaysOfWeek
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

enum CardinalDirections
{
    north,
    east,
    south,
    west,
};

enum CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,
};
```

Sometimes functions will return a status code to the caller to indicate whether the function executed successfully or encountered an error. Traditionally, small negative numbers were used to represent different possible error codes. For example:

```cpp
int readFileContents()
{
    if (!openFile())
        return -1;
    if (!readFile())
        return -2;
    if (!parseFile())
        return -3;

    return 0; // success
}
```

However, using magic numbers like this isn’t very descriptive. A better method would be to use an enumerated type:

```cpp
enum FileReadResult
{
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents()
{
    if (!openFile())
        return readResultErrorFileOpen;
    if (!readFile())
        return readResultErrorFileRead;
    if (!parseFile())
        return readResultErrorFileParse;

    return readResultSuccess;
}
```

Then the caller can test the function’s return value against the appropriate enumerator, which is easier to understand than testing the return result for a specific integer value.

```cpp
if (readFileContents() == readResultSuccess)
{
    // do something
}
else
{
    // print error message
}
```

Enumerated types can also be put to good use in games, to identify different types of items, or monsters, or terrain. Basically, anything that is a small set of related objects.

For example:

```cpp
enum ItemType
{
	sword,
	torch,
	potion,
};

int main()
{
	ItemType holding{ torch };

	return 0;
}
```

Enumerated types can also make for useful function parameters when the user needs to make a choice between two or more options:

```cpp
enum SortOrder
{
    alphabetical,
    alphabeticalReverse,
    numerical,
};

void sortData(SortOrder order)
{
    switch (order)
    {
        case alphabetical:
            // sort data in forwards alphabetical order
            break;
        case alphabeticalReverse:
            // sort data in backwards alphabetical order
            break;
        case numerical:
            // sort data numerically
            break;
    }
}
```

Many languages use enumerations to define Booleans -- after all, a Boolean is essentially just an enumeration with 2 enumerators: `false` and `true`! However, in C++, `true` and `false` are defined as keywords instead of enumerators.

Because enumerations are small and inexpensive to copy, it is fine to pass (and return) them by value.

>In lesson [O.1 -- Bit flags and bit manipulation via std::bitset](https://www.learncpp.com/cpp-tutorial/bit-flags-and-bit-manipulation-via-stdbitset/), we discussed bit flags. Enums can also be used to define a collection of related bit flag positions for use with `std::bitset`:

```cpp
#include <bitset>
#include <iostream>

namespace Flags
{
    enum State
    {
        isHungry,
        isSad,
        isMad,
        isHappy,
        isLaughing,
        isAsleep,
        isDead,
        isCrying,
    };
}

int main()
{
    std::bitset<8> me{};
    me.set(Flags::isHappy);
    me.set(Flags::isLaughing);

    std::cout << std::boolalpha; // print bool as true/false

    // Query a few states (we use the any() function to see if any bits remain set)
    std::cout << "I am happy? " << me.test(Flags::isHappy) << '\n';
    std::cout << "I am laughing? " << me.test(Flags::isLaughing) << '\n';

    return 0;
}
```

By default, the compiler assigns them integer values starting from `0`:

```cpp
isHungry   = 0
isSad      = 1
isMad      = 2
isHappy    = 3
isLaughing = 4
isAsleep   = 5
isDead     = 6
isCrying   = 7
```

These values are used as **bit positions** in the `bitset` later.

```cpp
std::bitset<8> me{};
```

- This creates a fixed-size collection of **8 bits**, all initialized to `0` (false).
    
- Each bit can be turned **on** (1) or **off** (0), just like a set of light switches.
    
- Perfect for tracking **on/off states** (e.g., "happy" yes/no).

```cpp
me.set(Flags::isHappy);
me.set(Flags::isLaughing);
```

- `.set(position)` turns on the bit at the given index.
    
- Here:
    
    - `Flags::isHappy` is `3` → turns on the 4th bit (index 3).
        
    - `Flags::isLaughing` is `4` → turns on the 5th bit (index 4).
        
- Now the `bitset` looks like:
```cpp
00011000
↑↑
|└ index 3 = Happy
└ index 4 = Laughing
```

---
### The scope of unscoped enumerations

Unscoped enumerations are named such because they put their enumerator names into the same scope as the enumeration definition itself (as opposed to creating a new scope region like a namespace does).

For example, given this program:

```cpp
enum Color // this enum is defined in the global namespace
{
    red, // so red is put into the global namespace
    green,
    blue,
};

int main()
{
    Color apple { red }; // my apple is red

    return 0;
}
```

The `Color` enumeration is defined in the global scope. Therefore, all the enumeration names (`red`, `green`, and `blue`) also go into the global scope. This pollutes the global scope and significantly raises the chance of naming collisions.

One consequence of this is that an enumerator name can’t be used in multiple enumerations within the same scope:

```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

enum Feeling
{
    happy,
    tired,
    blue, // error: naming collision with the above blue
};

int main()
{
    Color apple { red }; // my apple is red
    Feeling me { happy }; // I'm happy right now (even though my program doesn't compile)

    return 0;
}
```

In the above example, both unscoped enumerations (`Color` and `Feeling`) put enumerators with the same name `blue` into the global scope. This leads to a naming collision and subsequent compile error.

Unscoped enumerations also provide a named scope region for their enumerators (much like a namespace acts as a named scope region for the names declared within). This means we can access the enumerators of an unscoped enumeration as follows:

```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

int main()
{
    Color apple { red }; // okay, accessing enumerator from global namespace
    Color raspberry { Color::red }; // also okay, accessing enumerator from scope of Color

    return 0;
}
```

Most often, unscoped enumerators are accessed without using the scope resolution operator.

---
### Avoiding enumerator naming collisions

There are quite a few common ways to prevent unscoped enumerator naming collisions.

One option is to prefix each enumerator with the name of the enumeration itself:

```cpp
enum Color
{
    color_red,
    color_blue,
    color_green,
};

enum Feeling
{
    feeling_happy,
    feeling_tired,
    feeling_blue, // no longer has a naming collision with color_blue
};

int main()
{
    Color paint { color_blue };
    Feeling me { feeling_blue };

    return 0;
}
```

This still pollutes the namespace but reduces the chance for naming collisions by making the names longer and more unique.

A better option is to put the enumerated type inside something that provides a separate scope region, such as a namespace:

```cpp
namespace Color
{
    // The names Color, red, blue, and green are defined inside namespace Color
    enum Color
    {
        red,
        green,
        blue,
    };
}

namespace Feeling
{
    enum Feeling
    {
        happy,
        tired,
        blue, // Feeling::blue doesn't collide with Color::blue
    };
}

int main()
{
    Color::Color paint{ Color::blue };
    Feeling::Feeling me{ Feeling::blue };

    return 0;
}
```

This means we now have to prefix our enumeration and enumerator names with the name of the scoped region.

>A related option is to use a scoped enumeration (which defines its own scope region). We’ll discuss scoped enumerations shortly

>[!Best Practice]
>Prefer putting your enumerations inside a named scope region (such as a namespace or class) so the enumerators don’t pollute the global namespace.

>Alternatively, if an enumeration is only used within the body of a single function, the enumeration should be defined inside the function. This limits the scope of the enumeration and its enumerators to just that function. The enumerators of such an enumeration will shadow identically named enumerators defined in the global scope.

---
### Comparing against enumerators

We can use the equality operators (`operator==` and `operator!=`) to test whether an enumeration has the value of a particular enumerator or not.

```cpp
#include <iostream>

enum Color
{
    red,
    green,
    blue,
};

int main()
{
    Color shirt{ blue };

    if (shirt == blue) // if the shirt is blue
        std::cout << "Your shirt is blue!";
    else
        std::cout << "Your shirt is not blue!";

    return 0;
}
```

In the above example, we use an if-statement to test whether `shirt` is equal to the enumerator `blue`. This gives us a way to conditionalize our program’s behavior based on what enumerator our enumeration is holding.

---
