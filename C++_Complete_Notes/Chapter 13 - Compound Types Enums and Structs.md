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
>[!Note]
>Enumerators are symbolic constants which have value that is of integral type.

>[!Important]
>A char is really just a 1-byte integral value, and the character `'A'` gets converted to an integral value (in this case, `65`) and stored.

### Unscoped enumerator integral conversions

>When we define an enumeration, each enumerator is automatically associated with an integer value based on its position in the enumerator list. By default, the first enumerator is given the integral value `0`, and each subsequent enumerator has a value one greater than the previous enumerator:

```cpp
enum Color
{
    black,   // 0
    red,     // 1
    blue,    // 2
    green,   // 3
    white,   // 4
    cyan,    // 5
    yellow,  // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue }; // shirt actually stores integral value 2

    return 0;
}
```

It is possible to explicitly define the value of enumerators. These integral values can be positive or negative, and can share the same value as other enumerators. Any non-defined enumerators are given a value one greater than the previous enumerator.

```cpp
enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};
```

>Note in this case, `horse` and `giraffe` have been given the same value. When this happens, the enumerators become non-distinct -- essentially, `horse` and `giraffe` are interchangeable. Although C++ allows it, assigning the same value to two enumerators in the same enumeration should generally be avoided.

Most of the time, the default values for enumerators will be exactly what you want, so do not provide your own values unless you have a specific reason to do so.

>[!Best Practice]
>Avoid assigning explicit values to your enumerators unless you have a compelling reason to do so.

---
### Value-initializing an enumeration

#### **What’s happening here?**

When you create an enum variable in C++ like this:

```cpp
Animal a {};
```

You’re **value-initializing** it.  
For **enums**, value-initialization **zero-initializes** the variable — meaning it just stores `0` in that underlying integer slot, **regardless of whether you have an enumerator with value 0 or not**.

#### Example:

```cpp
enum Animal
{
    cat = -3,  // -3
    dog,       // -2
    pig,       // -1
    // no enumerator with value 0
    horse = 5, // 5
    giraffe = 5, // 5
    chicken,   // 6
};

Animal a {}; // value-initialization -> stores 0
```

Here:

- `a` is an `Animal`.
    
- You didn’t specify any value → `a` is **zero-initialized**.
    
- The underlying integer representation is `0`.
    
- BUT there’s **no enumerator** named for value `0` in `Animal`.  
    So `0` is a **semantically invalid state** for `Animal`.
    

When you print:

```cpp
std::cout << a;
```

It just prints `0` (the underlying integer value).

#### **Two important semantic consequences**

##### **1. If there IS an enumerator with value `0`**

Example:

```cpp
enum Color
{
    black, // 0
    red,
    green,
    blue
};

Color c {}; // zero-initialized -> black
```

Here:

- `c` is zero-initialized.
    
- Since `black` is `0`, `c` automatically means **black**.
    
- This is nice, because you can choose `0` to mean the **default or safe** value.
    

✅ **Best practice:** If your enum has a “default” meaning, give it value `0`.

##### **2. If there is NO enumerator with value `0`**

Then value-initialization will still store `0`, but it won’t correspond to any named enumerator.

Example:

```cpp
enum UniverseResult
{
    destroyUniverse, // 0
    saveUniverse     // 1
};
```

This is okay because `0` means `destroyUniverse`, but…

If you had:

```cpp
enum Animal
{
    cat = -3,
    dog,
    pig,
    horse = 5
};
Animal a {}; // stores 0, but 0 means "nothing" in this enum
```

Now you have an enum in an **invalid state** — code might not know how to handle it.

#### **How to avoid invalid zero states**

Introduce an explicit "unknown" or "invalid" enumerator with value `0`:

```cpp
enum Winner
{
    winnerUnknown, // 0 — safe default
    player1,       // 1
    player2        // 2
};

Winner w {}; // defaults to winnerUnknown
if (w == winnerUnknown) {
    // handle unknown case
}
```

This way:

- You document that `0` is not a real winner.
    
- Your code has a meaningful name for the default state.
    
- You can check and handle it explicitly.

>[!Best Practice]
>Make the enumerator representing 0 the one that is the best default meaning for your enumeration. If no good default meaning exists, consider adding an “invalid” or “unknown” enumerator that has value 0, so that state is explicitly documented and can be explicitly handled where appropriate.

---
### Unscoped enumerations will implicitly convert to integral values

#### **Key idea**

- **Unscoped enumerations** (`enum Something { ... };`) store **integral values** internally (like `int`, `unsigned int`, etc.).
    
- They are **not** technically integral types (like `int` or `long`) — they are their own distinct type.
    
- **But** C++ allows them to **implicitly** convert to their underlying integral type **whenever needed** (usually `int` unless otherwise specified).
    
- That conversion is **constexpr** — meaning it happens at compile time.

--> Even though `Color` is stored as an integer under the hood, the compiler says:

> “This is not an `int`, it’s a `Color` — a different type entirely.”

So:

- **`Color` is not part of the "integral type" family** in the C++ type taxonomy.
    
- It’s part of the **"enumeration type" family**.
    
- But **unscoped enums** have a special rule: they can implicitly convert _to_ their underlying integral type when needed.

#### Example:

```cpp
enum Color
{
    black,   // 0
    red,     // 1
    blue,    // 2
    green,   // 3
    white,   // 4
    cyan,    // 5
    yellow,  // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue }; // shirt is of type Color, with value 2

    std::cout << "Your shirt is " << shirt << '\n';
}
```

Here’s what happens when the compiler sees:

```cpp
std::cout << shirt;
```

1. **Step 1** — The compiler checks if `operator<<` for `std::ostream` can take a `Color` directly.
    
    - There’s **no built-in operator<<** for `Color`.
        
2. **Step 2** — The compiler says: “Okay, can I convert `Color` to something `operator<<` understands?”
    
    - Since `Color` is an **unscoped enum**, it can implicitly convert to its underlying integral type (`int` here).
        
    - This conversion is **constexpr** because `blue` is a compile-time constant.
        
3. **Step 3** — Now `operator<<` sees an `int` value `2`, and prints it.
    

**Result:**

```csharp
Your shirt is 2
```

---
### Enumeration size and underlying type (base)

#### **1. Enums store numbers — but what _kind_ of number?**

When you write:

```cpp
enum Color
{
    black,
    red,
    blue
};
```

- Internally, each enumerator (`black`, `red`, `blue`) is stored as an **integral value**.
    
- But C++ doesn’t _mandate_ exactly which integral type is used — that’s called the **underlying type** (or **base type**) of the enum.

#### **2. The “underlying type”**

- The **underlying type** is just the actual integer type the compiler chooses to store the enumerator values.
    
- Commonly, it’s `int` for unscoped enums.
    
- But if your enumerator values are too big to fit in `int`, the compiler will use a bigger type (like `long` or `long long`).
    

Example:

```cpp
enum BigEnum
{
    smallValue = 1,
    hugeValue = 2147483648 // bigger than int
};
// Compiler will probably use a 64-bit type internally
```

⚠ **Platform-dependent:** Different compilers or architectures can choose different underlying types — so don’t assume it’s always `int`.

#### **3. Explicitly setting the base type**

You can tell the compiler exactly what type to use:

```cpp
#include <cstdint>

enum Color : std::int8_t  // 8-bit signed integer
{
    black,
    red,
    blue
};
```

Now:

- `sizeof(Color)` will be `1` byte.
    
- Useful when sending data over a network or saving space in large arrays.

>[!Best Practice]
>Specify the base type of an enumeration only when necessary.

>[!Warning]
>Because `std::int8_t` and `std::uint8_t` are usually type aliases for char types, using either of these types as the enum base will most likely cause the enumerators to print as char values rather than int values.

#### **How enum storage works**

An `enum` is just a **type**, like `int` or `bool`.  
A single variable of that enum type holds **exactly one enumerator’s value at a time** — not all of them.

Think of it like this:

```cpp
enum Color { black, red, blue };
```

- `Color` is a type.
    
- `Color shirt = red;` means: "shirt’s storage is one integer slot, currently storing the value `1` (for `red`)."
    

So:

- You can have many **possible** values (`black`, `red`, `blue`).
    
- But the variable **only stores one at a time**.
    
- That one value fits into a single integer of the enum’s **underlying type**.
- ==Enum itself doesnt take storage since its a defination but it will take memory when we assign this with objects then it will allocate memory.==

---
### Integer to unscoped enumerator conversion

>While the compiler will implicitly convert an unscoped enumeration to an integer, it will _not_ implicitly convert an integer to an unscoped enumeration. The following will produce a compiler error:

```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
    pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

    return 0;
}
```

There are two ways to work around this.

First, you can explicitly convert an integer to an unscoped enumerator using `static_cast`:

```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
    pet = static_cast<Pet>(3);       // our pig evolved into a whale!

    return 0;
}
```

It is safe to static_cast any integral value that is represented by an enumerator of the target enumeration. Since our `Pet` enumeration has enumerators with values `0`, `1`, `2`, and `3`, static_casting integral values `0`, `1`, `2`, and `3` to a `Pet` is valid.

>It is also safe to static_cast any integral value that is in range of the target enumeration’s underlying type, even if there are no enumerators representing that value. Static casting a value outside the range of the underlying type will result in undefined behavior. eg: the range of signed char which will be base of enum will be 127 to -127 so if we go outside the range then undefined behaviour.

Second, as of C++17, if an unscoped enumeration has an explicitly specified base, then the compiler will allow you to list initialize an unscoped enumeration using an integral value:

```cpp
enum Pet: int // we've specified a base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet1 { 2 }; // ok: can brace initialize unscoped enumeration with specified base with integer (C++17)
    Pet pet2 (2);   // compile error: cannot direct initialize with integer
    Pet pet3 = 2;   // compile error: cannot copy initialize with integer

    pet1 = 3;       // compile error: cannot assign with integer

    return 0;
}
```

---
### Converting an enumeration to and from a string

>Most of the time, printing an enumeration as an integral value (such as `2`) isn’t what we want. Instead, we typically want to print the name of whatever the enumerator represents (e.g. `blue`). C++ doesn’t come with an out-of-the-box way to do this, so we’ll have to find a solution ourselves. Fortunately, that’s not very difficult.

### Getting the name of an enumerator

>The typical way to get the name of an enumerator is to write a function that allows us to pass in an enumerator and returns the enumerator’s name as a string. But that requires some way to determine which string should be returned for a given enumerator.

There are two common ways to do this.

>In lesson [8.5 -- Switch statement basics](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/), we noted that a switch statement can switch on either an integral value or an enumerated value. In the following example, we use a switch statement to select an enumerator and return the appropriate color string literal for that enumerator:

```cpp
#include <iostream>
#include <string_view>

enum Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    constexpr Color shirt{ blue };

    std::cout << "Your shirt is " << getColorName(shirt) << '\n';

    return 0;
}
```
Your shirt is blue

>In the above example, we switch on `color`, which holds the enumerator we passed in. Inside the switch, we have a case-label for each enumerator of `Color`. Each case returns the name of the appropriate color as a C-style string literal. This C-style string literal gets implicitly converted into a `std::string_view`, which is returned to the caller. We also have a default case which returns `"???"`, in case the user passes in something we didn’t expect.

>[!Reminder]
>Because C-style string literals exist for the entire program, it’s okay to return a `std::string_view` that is viewing a C-style string literal. When the `std::string_view` is copied back to the caller, the C-style string literal being viewed will still exist.

>The function is constexpr so that we can use the color’s name in a constant expression.

The second way to solve the program of mapping enumerators to strings is to use an array. (We havent covered it yet!)

---
### Unscoped enumerator input

Now let’s take a look at an input case. In the following example, we define a `Pet` enumeration. Because `Pet` is a program-defined type, the language doesn’t know how to input a `Pet` using `std::cin`:

```cpp
#include <iostream>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

int main()
{
    Pet pet { pig };
    std::cin >> pet; // compile error: std::cin doesn't know how to input a Pet

    return 0;
}
```

One simple way to work around this is to read in an integer, and use `static_cast` to convert the integer to an enumerator of the appropriate enumerated type:

```cpp
#include <iostream>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

int main()
{
    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input{};
    std::cin >> input; // input an integer

    if (input < 0 || input > 3)
        std::cout << "You entered an invalid pet\n";
    else
    {
        Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet
        std::cout << "You entered: " << getPetName(pet) << '\n';
    }

    return 0;
}
```

While this works, it’s a bit awkward. Also note that we should only `static_cast<Pet>(input)` once we know `input` is in range of the enumerator.

---
### Getting an enumeration from a string

Instead of inputting a number, it would be nicer if the user could type in a string representing an enumerator (e.g. “pig”), and we could convert that string into the appropriate `Pet` enumerator. However, doing this requires us to solve a couple of challenges.

First, we can’t switch on a string, so we need to use something else to match the string the user passed in. The simplest approach here is to use a series of if-statements.

Second, what `Pet` enumerator should we return if the user passes in an invalid string? One option would be to add an enumerator to represent “none/invalid”, and return that. However, a better option is to use `std::optional` here.

```cpp
#include <iostream>
#include <optional> // for std::optional
#include <string>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    // We can only switch on an integral value (or enum), not a string
    // so we have to use if-statements here
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    std::string s{};
    std::cin >> s;

    std::optional<Pet> pet { getPetFromString(s) };

    if (!pet)
        std::cout << "You entered an invalid pet\n";
    else
        std::cout << "You entered: " << getPetName(*pet) << '\n';

    return 0;
}
```

>In the above solution, we use a series of if-else statements to do string comparisons. If the user’s input string matches an enumerator string, we return the appropriate enumerator. If none of the strings match, we return `{}`, which means “no value”.

---
### Scoped enumerations (enum classes)

>Although unscoped enumerations are distinct types in C++, they are not type safe, and in some cases will allow you to do things that don’t make sense. Consider the following case:

```cpp
#include <iostream>

int main()
{
    enum Color
    {
        red,
        blue,
    };

    enum Fruit
    {
        banana,
        apple,
    };

    Color color { red };
    Fruit fruit { banana };

    if (color == fruit) // The compiler will compare color and fruit as integers
        std::cout << "color and fruit are equal\n"; // and find they are equal!
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```

This prints:

color and fruit are equal

When `color` and `fruit` are compared, the compiler will look to see if it knows how to compare a `Color` and a `Fruit`. It doesn’t. Next, it will try converting `Color` and/or `Fruit` to integers to see if it can find a match. Eventually the compiler will determine that if it converts both to integers, it can do the comparison. Since `color` and `fruit` are both set to enumerators that convert to integer value `0`, `color` will equal `fruit`.

This doesn’t make sense semantically since `color` and `fruit` are from different enumerations and are not intended to be comparable. With standard enumerators, there’s no easy way to prevent this.

Because of such challenges, as well as the namespace pollution problem (unscoped enumerations defined in the global scope put their enumerators in the global namespace), the C++ designers determined that a cleaner solution for enumerations would be of use.

---
### Scoped Enumerations

#### 1️⃣ What a **Scoped Enumeration** Is

A **scoped enumeration** (`enum class`) is basically an _enumeration with boundaries_.  
Compared to old-style (**unscoped**) `enum`, it has two major changes:

1. **No implicit conversion to integers**
    
    - In old `enum`, you could treat the values like `int` without asking — which sometimes led to mistakes.
        
    - In `enum class`, you must _explicitly_ convert to `int` if you want the numeric value.
        
2. **Enumerator names are scoped inside the enum**
    
    - In old `enum`, the names (`red`, `blue`) are dumped into the surrounding scope — possibly clashing with other enums.
        
    - In `enum class`, the names stay inside the enum’s scope, so you write `Color::red` instead of just `red`.

--> Example:

```cpp
enum class Color
{
    red,
    blue
};

enum class Fruit
{
    banana,
    apple
};

Color color { Color::red };
Fruit fruit { Fruit::banana };
```

Here:

- `Color::red` and `Fruit::banana` are **completely separate identifiers**.
    
- There’s no accidental conflict — you _must_ qualify them with their enum name.

#### 3️⃣ Why the comparison fails

```cpp
if (color == fruit) // ❌ compile error
```

This fails because:

- `color` is type `Color`.
    
- `fruit` is type `Fruit`.
    
- **They are not interchangeable** — `enum class` values don’t implicitly convert to integers or other enums.
    

If you _really_ wanted to compare them numerically, you’d have to cast:

```cpp
if (static_cast<int>(color) == static_cast<int>(fruit)) { ... }
```

…but that defeats the type-safety benefit.

#### 4️⃣ Why `enum class` exists

It was introduced in **C++11** to fix problems with old enums:

- Old enums could silently convert to `int` and be mixed with unrelated enums, leading to bugs.
    
- Old enums polluted the surrounding namespace with their names, making conflicts easy.

>[!As an aside…]
The `class` keyword (along with the `static` keyword), is one of the most overloaded keywords in the C++ language, and can have different meanings depending on context. Although scoped enumerations use the `class` keyword, they aren’t considered to be a “class type” (which is reserved for structs, classes, and unions).
`enum struct` also works in this context, and behaves identically to `enum class`. However, use of `enum struct` is non-idiomatic, so avoid its use.

---
### Scoped enumerations define their own scope regions

>Unlike unscoped enumerations, which place their enumerators in the same scope as the enumeration itself, scoped enumerations place their enumerators _only_ in the scope region of the enumeration. In other words, scoped enumerations act like a namespace for their enumerators. This built-in namespacing helps reduce global namespace pollution and the potential for name conflicts when scoped enumerations are used in the global scope.

To access a scoped enumerator, we do so just as if it was in a namespace having the same name as the scoped enumeration:

```cpp
#include <iostream>

int main()
{
    enum class Color // "enum class" defines this as a scoped enum rather than an unscoped enum
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    std::cout << red << '\n';        // compile error: red not defined in this scope region
    std::cout << Color::red << '\n'; // compile error: std::cout doesn't know how to print this (will not implicitly convert to int)

    Color color { Color::blue }; // okay

    return 0;
}
```

---
### Scoped enumerations don’t implicitly convert to integers

#### 1️⃣ Old behavior: unscoped enums

In an **unscoped** enum:

```cpp
enum Color { red, blue };
Color c = red;
int x = c; // ✅ works automatically (implicit conversion)
```

Here, `red` and `blue` are basically just named integers. They _automatically_ convert to `int` — which is convenient but risky, because:

- You can accidentally mix enums from different categories.
    
- You can do nonsensical math like `red + 5`.
    
- Name clashes are easier.

#### 2️⃣ Scoped enums block implicit conversion

With a **scoped** enum (`enum class`):

```cpp
enum class Color { red, blue };
Color c = Color::red;
int x = c; // ❌ compile error
```

- You _must_ explicitly convert if you want the integer value.
    
- This **forces you to be intentional** when treating enum values as numbers.
    
- You _can still_ compare values from the **same** scoped enum (e.g., `Color::red == Color::blue`), because they’re the same type.

#### 3️⃣ Explicit conversion methods

If you _really_ want the numeric value, you can do it in two main ways:

##### **C++11+** — `static_cast`

```cpp
std::cout << static_cast<int>(Color::blue); // prints 1
```

**C++23** — `std::to_underlying()` (cleaner)

```cpp
#include <utility>
std::cout << std::to_underlying(Color::blue); // prints 1
```

`std::to_underlying()` is nicer because:

- It’s self-documenting.
    
- It avoids surprises if the underlying type isn’t `int` (could be `unsigned char`, etc.).

#### 4️⃣ Converting integers back to enums

Sometimes you’ll get an `int` from somewhere (like user input) and want to turn it into a scoped enum value:

```cpp
int input{};
std::cin >> input;
Pet pet = static_cast<Pet>(input);
```

This works, but **be careful** — there’s no automatic range checking.  
If the user enters `99`, you’ll still get a `Pet` value — it’ll just be invalid.

#### 5️⃣ C++17 shortcut

As of **C++17**, you can directly list-initialize a scoped enum from an integer without `static_cast`:

```cpp
Pet pet { 1 }; // same as static_cast<Pet>(1)
```

This is a bit more concise, but explicit `static_cast` can still be clearer in intent

#### 6️⃣ Why use scoped enums

**Benefits:**

- No accidental mixing of unrelated enums.
    
- Prevents weird math operations on enums.
    
- No name pollution in outer scope.
    
- Safer, more readable code.
    

**Downside:**

- You have to explicitly convert when you _do_ want integer behavior — which can feel tedious in some scenarios (especially for bitmask flags, where unscoped enums are still common).

>[!Best Practice]
>Use `enum class` by default. Only use unscoped enums when implicit integer conversion is truly needed (like heavy bitmasking or legacy code interop).

---
### `using enum` statements C++20

>Introduced in C++20, a `using enum` statement imports all of the enumerators from an enum into the current scope. When used with an enum class type, this allows us to access the enum class enumerators without having to prefix each with the name of the enum class.

This can be useful in cases where we would otherwise have many identical, repeated prefixes, such as within a switch statement:

```cpp
#include <iostream>
#include <string_view>

enum class Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColor(Color color)
{
    using enum Color; // bring all Color enumerators into current scope (C++20)
    // We can now access the enumerators of Color without using a Color:: prefix

    switch (color)
    {
    case black: return "black"; // note: black instead of Color::black
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    Color shirt{ Color::blue };

    std::cout << "Your shirt is " << getColor(shirt) << '\n';

    return 0;
}
```

In the above example, `Color` is an enum class, so we normally would access the enumerators using a fully qualified name (e.g. `Color::blue`). However, within function `getColor()`, we’ve added the statement `using enum Color;`, which allows us to access those enumerators without the `Color::` prefix.

This saves us from having multiple, redundant, obvious prefixes inside the switch statement.

---
### Introduction to structs, members, and member selection

>There are many instances in programming where we need more than one variable in order to represent something of interest. As we discussed in the introduction to the previous chapter ([12.1 -- Introduction to compound data types](https://www.learncpp.com/cpp-tutorial/introduction-to-compound-data-types/)), a fraction has a numerator and denominator that are linked together into a single mathematical object.

Alternatively, lets say we want to write a program where we need to store information about the employees in a company. We might be interested in keeping track of attributes such as the employee’s name, title, age, employee id, manager id, wage, birthday, hire date, etc…

If we were to use independent variables to track all of this information, that might look something like this:

```cpp
std::string name;
std::string title;
int age;
int id;
int managerId;
double wage;
int birthdayYear;
int birthdayMonth;
int birthdayDay;
int hireYear;
int hireMonth;
int hireDay;
```

However, there are a number of problems with this approach. First, it’s not immediately clear whether these variables are actually related or not (you’d have to read comments, or see how they are used in context). Second, there are now 12 variables to manage. If we wanted to pass this employee to a function, we’d have to pass 12 arguments (and in the correct order), which would make a mess of our function prototypes and function calls. And since a function can only return a single value, how would a function even return an employee?

And if we wanted more than one employee, we’d need to define 12 more variables for each additional employee (each of which would require a unique name)! This clearly doesn’t scale at all. What we really need is some way to organize all of these related pieces of data together, to make them easier to manage.

==Fortunately, C++ comes with two compound types designed to solve such challenges: structs (which we’ll introduce now) and classes (which we’ll explore soon). A **struct** (short for **structure**) is a program-defined data type ([13.1 -- Introduction to program-defined (user-defined) types](https://www.learncpp.com/cpp-tutorial/introduction-to-program-defined-user-defined-types/)) that allows us to bundle multiple variables together into a single type. As you’ll see shortly, this makes management of related sets of variables much simpler!


>[!A reminder]
A struct is a class type (as are classes and unions). As such, anything that applies to class types applies to structs.

---
### Defining structs

>Because structs are a program-defined type, we first have to tell the compiler what our struct type looks like before we can begin using it. Here is an example of a struct definition for a simplified employee:

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```

The `struct` keyword is used to tell the compiler that we’re defining a struct, which we’ve named `Employee` (since program-defined types are typically given names starting with a capital letter).

Then, inside a pair of curly braces, we define the variables that each Employee object will contain. In this example, each `Employee` we create will have 3 variables: an `int id`, an `int age`, and a `double wage`. The variables that are part of the struct are called **data members** (or **member variables**).

>[!Tip]
>In everyday language, a _member_ is a individual who belongs to a group. For example, you might be a member of the basketball team, and your sister might be a member of the choir.
In C++, a **member** is a variable, function, or type that belongs to a struct (or class). All members must be declared within the struct (or class) definition.

==As a reminder, `Employee` is just a type definition -- no objects are actually created at this point.

---
### Defining struct objects

In order to use the `Employee` type, we simply define a variable of type `Employee`:

```cpp
Employee joe {}; // Employee is the type, joe is the variable name
```

This defines a variable of type `Employee` named `joe`. When the code is executed, an Employee object is instantiated that contains the 3 data members. The empty braces ensures our object is value-initialized.

Just like any other type, it is possible to define multiple variables of the same struct type:

```cpp
Employee joe {}; // create an Employee struct for Joe
Employee frank {}; // create an Employee struct for Frank
```

---
### Accessing members

Consider the following example:

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    return 0;
}
```

In the above example, the name `joe` refers to the entire struct object (which contains the member variables). To access a specific member variable, we use the **member selection operator** (`operator.`) in between the struct variable name and the member name. For example, to access Joe’s age member, we’d use `joe.age`.

Struct member variables work just like normal variables, so it is possible to do normal operations on them, including assignment, arithmetic, comparison, etc…

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    joe.age = 32;  // use member selection operator (.) to select the age member of variable joe

    std::cout << joe.age << '\n'; // print joe's age

    return 0;
}
```

This prints:

32

One of the biggest advantages of structs is that we only need to create one new name per struct variable (the member names are fixed as part of the struct type definition). In the following example, we instantiate two `Employee` objects: `joe` and `frank`.

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};
    joe.id = 14;
    joe.age = 32;
    joe.wage = 60000.0;

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int totalAge { joe.age + frank.age };
    std::cout << "Joe and Frank have lived " << totalAge << " total years\n";

    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage < frank.wage)
        std::cout << "Joe makes less than Frank\n";
    else
        std::cout << "Joe and Frank make the same amount\n";

    // Frank got a promotion
    frank.wage += 5000.0;

    // Today is Joe's birthday
    ++joe.age; // use pre-increment to increment Joe's age by 1

    return 0;
}
```

In the above example, it is very easy to tell which member variables belong to Joe and which belong to Frank. This provides a much higher level of organization than individual variables would. Furthermore, because Joe’s and Frank’s members have the same names, this provides consistency when you have multiple variables of the same struct type.

---
