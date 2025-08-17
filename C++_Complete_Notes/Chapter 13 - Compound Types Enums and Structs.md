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
### Forgotten lesson - Introduction to overloading the I/O operators

==I forget to do this lesson so here:

>Ideally, it would be nice if we could somehow teach `operator<<` to output an enumeration, so we could do something like this: `std::cout << shirt` and have it do what we expect.

#### Introduction to operator overloading

>we introduced function overloading, which allows us to create multiple functions with the same name so long as each function has a unique function prototype. Using function overloading, we can create variations of a function that work with different data types, without having to think up a unique name for each variant.

Similarly, C++ also supports **operator overloading**, which lets us define overloads of existing operators, so that we can make those operators work with our program-defined data types.

Basic operator overloading is fairly straightforward:

- Define a function using the name of the operator as the function’s name.
- Add a parameter of the appropriate type for each operand (in left-to-right order). One of these parameters must be a user-defined type (a class type or an enumerated type), otherwise the compiler will error.
- Set the return type to whatever type makes sense.
- Use a return statement to return the result of the operation.

--> **"Add a parameter of the appropriate type for each operand (in left-to-right order)"?**

Operators act on **operands**.

For example:

```cpp
x + y
```

- **Left operand** = `x`
    
- **Right operand** = `y`
    

When you overload an operator as a **non-member function**, the operands become parameters in **that same left-to-right order**:

```cpp
Vector operator+(const Vector& left, const Vector& right);
```

Here:

- `left` → corresponds to `x` in `x + y`
    
- `right` → corresponds to `y` in `x + y`

>When the compiler encounters the use of an operator in an expression and one or more of the operands is a user-defined type, the compiler will check to see if there is an overloaded operator function that it can use to resolve that call. For example, given some expression `x + y`, the compiler will use function overload resolution to see if there is an `operator+(x, y)` function call that it can use to evaluate the operation. If a non-ambiguous `operator+` function can be found, it will be called, and the result of the operation returned as the return value.

#### Overloading `operator<<` to print an enumerator

##### 1. **How `operator<<` works normally**

When you write:

```cpp
std::cout << 5;
```

- `std::cout` is a `std::ostream` object (a user-defined type in the standard library).
    
- The compiler looks for an `operator<<` that takes:
    
    - Left operand: `std::ostream&`
        
    - Right operand: `int`
        
- The standard library provides exactly that, so it calls it.
    
- Inside that function, `5` gets printed into the stream.
    
- The function **returns the left operand** (`std::cout`) so you can chain:

```cpp
std::cout << 5 << 10 << '\n';
```

##### 2. **Our goal**

We have an enum:

```cpp
enum Color { black, red, blue };
```

By default, `std::cout << blue;` would print `2` (the underlying integer value), not `"blue"`.  
We want:

```cpp
std::cout << blue; // prints "blue"
```

##### 3. **Overloading `operator<<` for our enum**

We define:

```cpp
std::ostream& operator<<(std::ostream& out, Color color)
```

- **Name**: `operator<<`
    
- **Left operand** → `std::ostream& out`
    
    - Passed by non-const reference because we **don’t** want to copy `std::ostream` and we **do** want to modify it (insert data into it).
        
- **Right operand** → `Color color`
    
- **Return type** → `std::ostream&`
    
    - This lets us return the same output stream so chaining works.


##### 4. **Implementation details**

We already have a helper:

```cpp
constexpr std::string_view getColorName(Color color)
```

It turns `black` → `"black"`, etc.

Inside `operator<<`:

```cpp
out << getColorName(color);
return out;
```

- We call `getColorName(color)` to get the string `"blue"`.
    
- `out << ...` works because `std::ostream` already knows how to print a `std::string_view`.
    
- We return `out` so you can write:

```cpp
std::cout << "Shirt: " << blue << '\n';
```

##### 5. **Why we don’t hardcode `std::cout`**

We use the `out` parameter instead of `std::cout` directly because the left operand might be something else, like:

```cpp
std::cerr << blue; // prints to std::cerr
```

This way, the same function works for **any** `std::ostream`.

##### 6. **What happens when you run it**

For:

```cpp
std::cout << "Your shirt is " << shirt << '\n';
```

Steps:

1. `"Your shirt is "` → printed by the `std::ostream& operator<<(std::ostream&, const char*)` overload.
    
2. `shirt` → triggers our custom `operator<<(std::ostream&, Color)`.
    
3. Inside our function:
    
    - `out` is a reference to `std::cout`
        
    - `color` is `blue`
        
    - `getColorName(color)` returns `"blue"`
        
    - That string is sent into the same `std::ostream` (`std::cout`).
        
4. `out` is returned so the final `'\n'` gets printed in the next chained call.

Result:

```cpp
Your shirt is blue
```


##### Why return _must_ be a reference, not a copy

- If you **returned by value** (`std::ostream operator<<(...)`), the compiler would need to **copy** `std::cout` to make the return value.
    
- But `std::ostream` **cannot** be copied — so it would fail to compile.
    
- Even if it could be copied, each `<<` would operate on a **different stream object**, so output wouldn’t all go to the same place.

#### Overloading `operator>>` to input an enumerator

```cpp
#include <iostream>
#include <limits>
#include <optional>
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
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

// pet is an in/out parameter
std::istream& operator>>(std::istream& in, Pet& pet)
{
    std::string s{};
    in >> s; // get input string from user

    std::optional<Pet> match { getPetFromString(s) };
    if (match) // if we found a match
    {
        pet = *match; // dereference std::optional to get matching enumerator
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // pet = {};

    return in;
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet{};
    std::cin >> pet;

    if (std::cin) // if we found a match
        std::cout << "You chose: " << getPetName(pet) << '\n';
    else
    {
        std::cin.clear(); // reset the input stream to good
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Your pet was not valid\n";
    }

    return 0;
}
```

##### Why `operator>>` returns a reference

Same reason as with `operator<<`:

- Streams are non-copyable, so we must return by reference.
    
- Allows chaining:

```cpp
std::cin >> pet1 >> pet2;
```

works because the same stream reference is returned.

>If the user did not enter a valid pet, then we handle that case by putting `std::cin` into “failure mode”. This is the state that `std::cin` typically goes into when an extraction fails. The caller can then check `std::cin` to see if the extraction succeeded or failed.

---
### Struct aggregate initialization

#### Data members are not initialized by default

Much like normal variables, data members are not initialized by default. Consider the following struct:

```cpp
#include <iostream>

struct Employee
{
    int id; // note: no initializer here
    int age;
    double wage;
};

int main()
{
    Employee joe; // note: no initializer here either
    std::cout << joe.id << '\n';

    return 0;
}
```

Because we have not provided any initializers, when `joe` is instantiated, `joe.id`, `joe.age`, and `joe.wage` will all be uninitialized. We will then get undefined behavior when we try to print the value of `joe.id`.

However, before we show you how to initialize a struct, let’s take a short detour.

#### What is an aggregate? [](https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/#aggregate)

In general programming, an **aggregate data type** (also called an **aggregate**) is any type that can contain multiple data members. Some types of aggregates allow members to have different types (e.g. structs), while others require that all members must be of a single type (e.g. arrays).

In C++, the definition of an aggregate is narrower and quite a bit more complicated.

>[!Reminder]
>The key thing to understand at this point is that structs with only data members are aggregates.

---
### Aggregate initialization of a struct

Because a normal variable can only hold a single value, we only need to provide a single initializer:

```cpp
int x { 5 };
```

However, a struct can have multiple members:

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```

When we define an object with a struct type, we need some way to initialize multiple members at initialization time:

```cpp
Employee joe; // how do we initialize joe.id, joe.age, and joe.wage?
```

>Aggregates use a form of initialization called **aggregate initialization**, which allows us to directly initialize the members of aggregates. To do this, we provide an **initializer list** as an initializer, which is just a braced list of comma-separated values.

There are 2 primary forms of aggregate initialization:

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)

    return 0;
}
```

Each of these initialization forms does a **memberwise initialization**, which means each member in the struct is initialized in the order of declaration. Thus, `Employee joe { 2, 28, 45000.0 };` first initializes `joe.id` with value `2`, then `joe.age` with value `28`, and `joe.wage` with value `45000.0` last.

>[!Best practice]
Prefer the (non-copy) braced list form when initializing aggregates.

---
### Missing initializers in an initializer list

If an aggregate is initialized but the number of initialization values is fewer than the number of members, then each member without an explicit initializer is initialized as follows:

- If the member has a default member initializer, that is used.
- Otherwise, the member is copy-initialized from an empty initializer list. In most cases, this will perform value-initialization on those members (on class types, this will invoke the default constructor even if a list constructor exist).

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage { 76000.0 };
    double whatever;
};

int main()
{
    Employee joe { 2, 28 }; // joe.whatever will be value-initialized to 0.0

    return 0;
}
```

In the above example, `joe.id` will be initialized with value `2` and `joe.age` will be initialized with value `28`. Because `joe.wage` wasn’t given an explicit initializer but has a default member initializer, `joe.wage` will be initialized to `76000.0`. And finally, because `joe.whatever` wasn’t given an explicit initializer, `joe.whatever` is value-initialized to `0.0`.

>[!Tip]
This means we can generally use an empty initialization list to value-initialize all members of the struct:
```cpp
Employee joe {}; // value-initialize all members
```

---
### Overloading `operator<<` to print a struct

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out, const Employee& e)
{
    out << "id: " << e.id << " age: " << e.age << " wage: " << e.wage;
    return out;
}

int main()
{
    Employee joe { 2, 28 }; // joe.wage will be value-initialized to 0.0
    std::cout << joe << '\n';

    return 0;
}
```
id: 2 age: 28 wage: 0

---
### Designated initializers C++20

>When initializing a struct from a list of values, the initializers are applied to the members in order of declaration.

```cpp
struct Foo
{
    int a {};
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // f.a = 1, f.c = 3

    return 0;
}
```

Now consider what would happen if you were to update this struct definition to add a new member that is not the last member:

```cpp
struct Foo
{
    int a {};
    int b {}; // just added
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // now, f.a = 1, f.b = 3, f.c = 0

    return 0;
}
```

Now all your initialization values have shifted, and worse, the compiler may not detect this as an error (after all, the syntax is still valid).

>To help avoid this, C++20 adds a new way to initialize struct members called **designated initializers**. Designated initializers allow you to explicitly define which initialization values map to which members. The members can be initialized using list or copy initialization, and must be initialized in the same order in which they are declared in the struct, otherwise a warning or error will result. Members not designated an initializer will be value initialized.

```cpp
struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    return 0;
}
```

Designated initializers are nice because they provide some level of self-documentation and help ensure you don’t inadvertently mix up the order of your initialization values. However, designated initializers also clutter up the initializer list significantly, so we won’t recommend their use as a best practice at this time.

Also, because there’s no enforcement that designated initializers are being used consistently everywhere an aggregate is initialized, it’s a good idea to avoid adding new members to the middle of an existing aggregate definition, to avoid the risk of initializer shifting.

>[!Best Practice]
>When adding a new member to an aggregate, it’s safest to add it to the bottom of the definition list so the initializers for other members don’t shift.

---
### Assignment with an initializer list

As shown in the prior lesson, we can assign values to members of structs individually:

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };

    joe.age  = 33;      // Joe had a birthday
    joe.wage = 66000.0; // and got a raise

    return 0;
}
```

This is fine for single members, but not great when we want to update many members. Similar to initializing a struct with an initializer list, you can also assign values to structs using an initializer list (which does memberwise assignment):

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { joe.id, 33, 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```

Note that because we didn’t want to change `joe.id`, we needed to provide the current value for `joe.id` in our list as a placeholder, so that memberwise assignment could assign `joe.id` to `joe.id`. This is a bit ugly.

---
### Assignment with designated initializers C++20

Designated initializers can also be used in a list assignment:

```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```

Any members that aren’t designated in such an assignment will be assigned the value that would be used for value initialization. If we hadn’t have specified a designated initializer for `joe.id`, `joe.id` would have been assigned the value 0.

---
### Initializing a struct with another struct of the same type

A struct may also be initialized using another struct of the same type:

```cpp
#include <iostream>

struct Foo
{
    int a{};
    int b{};
    int c{};
};

std::ostream& operator<<(std::ostream& out, const Foo& f)
{
    out << f.a << ' ' << f.b << ' ' << f.c;
    return out;
}

int main()
{
    Foo foo { 1, 2, 3 };

    Foo x = foo; // copy-initialization
    Foo y(foo);  // direct-initialization
    Foo z {foo}; // direct-list-initialization

    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << z << '\n';

    return 0;
}
```

The above prints:

1 2 3
1 2 3
1 2 3

---
### Default member initialization

>When we define a struct (or class) type, we can provide a default initialization value for each member as part of the type definition. For members not marked as `static`, this process is sometimes called **non-static member initialization**. The initialization value is called a **default member initializer**.

Here’s an example:

```cpp
struct Something
{
    int x;       // no initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1; // s1.x is uninitialized, s1.y is 0, and s1.z is 2

    return 0;
}
```

In the above definition of `Something`, `x` has no default value, `y` is value-initialized by default, and `z` has the default value `2`. These default member initialization values will be used if the user doesn’t provide an explicit initialization value when instantiating an object of type `Something`.

Our `s1` object doesn’t have an initializer, so the members of `s1` are initialized to their default values. `s1.x` has no default initializer, so it remains uninitialized. `s1.y` is value initialized by default, so it gets value `0`. And `s1.z` is initialized with the value `2`.

Note that even though we haven’t provided an explicit initializer for `s1.z`, it is initialized to a non-zero value because of the default member initializer provided.

>[!Key Insight]
>Using default member initializers (or other mechanisms that we’ll cover later), structs and classes can self-initialize even when no explicit initializers are provided!

---
### Explicit initialization values take precedence over default values

>Explicit values in a list initializer always take precedence over default member initialization values.

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s2 { 5, 6, 7 }; // use explicit initializers for s2.x, s2.y, and s2.z (no default values are used)

    return 0;
}
```

In the above case, `s2` has explicit initialization values for every member, so the default member initialization values are not used at all. This means `s2.x`, `s2.y` and `s2.z` are initialized to the values `5`, `6`, and `7` respectively.

---
### Missing initializers in an initializer list when default values exist

>we noted that if an aggregate is initialized but the number of initialization values is fewer than the number of members, then all remaining members will be value-initialized. However, if a default member initializer is provided for a given member, that default member initializer will be used instead.

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s3 {}; // value initialize s3.x, use default values for s3.y and s3.z

    return 0;
}
```

In the above case, `s3` is list initialized with an empty list, so all initializers are missing. This means that a default member initializer will be used if it exists, and value initialization will occur otherwise. Thus, `s3.x` (which has no default member initializer) is value initialized to `0`, `s3.y` is value initialized by default to `0`, and `s3.z` is defaulted to value `2`.

---
### Recapping the initialization possibilities

If an aggregate is defined with an initialization list:

- If an explicit initialization value exists, that explicit value is used.
- If an initializer is missing and a default member initializer exists, the default is used.
- If an initializer is missing and no default member initializer exists, value initialization occurs.

If an aggregate is defined with no initialization list:

- If a default member initializer exists, the default is used.
- If no default member initializer exists, the member remains uninitialized.

Members are always initialized in the order of declaration.

The following example recaps all possibilities:

```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1;             // No initializer list: s1.x is uninitialized, s1.y and s1.z use defaults
    Something s2 { 5, 6, 7 }; // Explicit initializers: s2.x, s2.y, and s2.z use explicit values (no default values are used)
    Something s3 {};          // Missing initializers: s3.x is value initialized, s3.y and s3.z use defaults

    return 0;
}
```

The case we want to watch out for is `s1.x`. Because `s1` has no initializer list and `x` has no default member initializer, `s1.x` remains uninitialized (which is bad, since we should always initialize our variables).

---
### Always provide default values for your members

>To avoid the possibility of uninitialized members, simply ensure that each member has a default value (either an explicit default value, or an empty pair of braces). That way, our members will be initialized with some value regardless of whether we provide an initializer list or not.

Consider the following struct, which has all members defaulted:

```cpp
struct Fraction
{
	int numerator { }; // we should use { 0 } here, but for the sake of example we'll use value initialization instead
	int denominator { 1 };
};

int main()
{
	Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
	Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
	Fraction f3 { 6 };    // f3.numerator initialized to 6, f3.denominator defaulted to 1
	Fraction f4 { 5, 8 }; // f4.numerator initialized to 5, f4.denominator initialized to 8

	return 0;
}
```

In all cases, our members are initialized with values.

>[!Best practice]
Provide a default value for all members. This ensures that your members will be initialized even if the variable definition doesn’t include an initializer list.

---
### Default initialization vs value initialization for aggregates

>Revisiting two lines from the above example:

```cpp
Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
```

You’ll note that `f1` is default initialized and `f2` is value initialized, yet the results are the same (`numerator` is initialized to `0` and `denominator` is initialized to `1`). So which should we prefer?

The value initialization case (`f2`) is safer, because it will ensure any members with no default values are value initialized (and although we should always provide default values for members, this protects against the case where one is missed).

Preferring value initialization has one more benefit -- it’s consistent with how we initialize objects of other types. Consistency helps prevent errors.

>[!Best Practice]
>For aggregates, prefer value initialization (with an empty braces initializer) to default initialization (with no braces).

---
### Passing and returning structs

#### Passing structs (by reference)

>A big advantage of using structs over individual variables is that we can pass the entire struct to a function that needs to work with the members. Structs are generally passed by reference (typically by const reference) to avoid making copies.

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    Employee joe { 14, 32, 24.15 };
    Employee frank { 15, 28, 18.27 };

    // Print Joe's information
    printEmployee(joe);

    std::cout << '\n';

    // Print Frank's information
    printEmployee(frank);

    return 0;
}
```

In the above example, we pass an entire `Employee` to `printEmployee()` (twice, once for `joe` and once for `frank`).

The above program outputs:

ID:   14
Age:  32
Wage: 24.15

ID:   15
Age:  28
Wage: 18.27

Because we are passing the entire struct object (rather than individual members), we only need one parameter no matter how many members the struct object has. And, in the future, if we ever decide to add new members to our `Employee` struct, we will not have to change the function declaration or function call! The new member will automatically be included.

---
### Passing temporary structs

>In the prior example, we created Employee variable `joe` prior to passing it to the `printEmployee()` function. This allows us to give the Employee variable a name, which can be useful for documentation purposes. But it also requires two statements (one to create `joe`, one to use `joe`).

In cases where we only use a variable once, having to give the variable a name and separate the creation and use of that variable can increase complexity. In such cases, it may be preferable to use a temporary object instead. A temporary object is not a variable, so it does not have an identifier.

Here’s the same example as above, but we’ve replaced variables `joe` and `frank` with temporary objects:

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    // Print Joe's information
    printEmployee(Employee { 14, 32, 24.15 }); // construct a temporary Employee to pass to function (type explicitly specified) (preferred)

    std::cout << '\n';

    // Print Frank's information
    printEmployee({ 15, 28, 18.27 }); // construct a temporary Employee to pass to function (type deduced from parameter)

    return 0;
}
```

We can create a temporary `Employee` in two ways. In the first call, we use the syntax `Employee { 14, 32, 24.15 }`. This tells the compiler to create an `Employee` object and initialize it with the provided initializers. This is the preferred syntax because it makes clear what kind of temporary object we are creating, and there is no way for the compiler to misinterpret our intentions.

In the second call, we use the syntax `{ 15, 28, 18.27 }`. The compiler is smart enough to understand that the provided arguments must be converted to an `Employee` so that the function call will succeed. Note that this form is considered an implicit conversion, so it will not work in cases where only explicit conversions are acceptable.

---
### Returning structs

>Consider the case where we have a function that needs to return a point in 3-dimensional Cartesian space. Such a point has 3 attributes: an x-coordinate, a y-coordinate, and a z-coordinate. But functions can only return one value. So how do we return all 3 coordinates back the user?

One common way is to return a struct:

```cpp
#include <iostream>

struct Point3d
{
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
};

Point3d getZeroPoint()
{
    // We can create a variable and return the variable (we'll improve this below)
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}

int main()
{
    Point3d zero{ getZeroPoint() };

    if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
        std::cout << "The point is zero\n";
    else
        std::cout << "The point is not zero\n";

    return 0;
}
```

This prints:

The point is zero

Structs defined inside functions are usually returned by value, so as not to return a dangling reference.

In the `getZeroPoint()` function above, we create a new named object (`temp`) just so we could return it:

```cpp
Point3d getZeroPoint()
{
    // We can create a variable and return the variable (we'll improve this below)
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}
```

The name of the object (`temp`) doesn’t really provide any documentation value here.

We can make our function slightly better by returning a temporary (unnamed/anonymous) object instead:

```cpp
Point3d getZeroPoint()
{
    return Point3d { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```

In this case, a temporary `Point3d` is constructed, copied back to the caller, and then destroyed at the end of the expression. Note how much cleaner this is (one line vs two, and no need to understand whether `temp` is used more than once).

---
### Deducing the return type

In the case where the function has an explicit return type (e.g. `Point3d`), we can even omit the type in the return statement:

```cpp
Point3d getZeroPoint()
{
    // We already specified the type at the function declaration
    // so we don't need to do so here again
    return { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```

This is considered to be an implicit conversion.

Also note that since in this case we’re returning all zero values, we can use empty braces to return a value-initialized Point3d:

```cpp
Point3d getZeroPoint()
{
    // We can use empty curly braces to value-initialize all members
    return {};
}
```

---
### Structs are an important building block

While structs are useful in and of themselves, classes (which are the heart of C++ and object oriented programming) build directly on top of the concepts we’ve introduced here. Having a good understanding of structs (especially data members, member selection, and default member initialization) will make your transition to classes that much easier.

---
### Structs with program-defined members

>In C++, structs (and classes) can have members that are other program-defined types. There are two ways to do this.

First, we can define one program-defined type (in the global scope) and then use it as a member of another program-defined type:

```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

struct Company
{
    int numberOfEmployees {};
    Employee CEO {}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```

In the above case, we’ve defined an `Employee` struct, and then used that as a member in a `Company` struct. When we initialize our `Company`, we can also initialize our `Employee` by using a nested initialization list. And if we want to know what the CEO’s salary was, we simply use the member selection operator twice: `myCompany.CEO.wage;`

Second, types can also be nested inside other types, so if an Employee only existed as part of a Company, the Employee type could be nested inside the Company struct:

```cpp
#include <iostream>

struct Company
{
    struct Employee // accessed via Company::Employee
    {
        int id{};
        int age{};
        double wage{};
    };

    int numberOfEmployees{};
    Employee CEO{}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```

---
### Structs that are owners should have data members that are owners

>In most cases, we want our structs (and classes) to be owners of the data they contain. This provides a few useful benefits:

- The data members will be valid for as long as the struct (or class) is.
- The value of those data members won’t change unexpectedly.

>If a struct (or class) has a data member that is a viewer, it is possible that the object being viewed by that member will be destroyed before the data member that is viewing it. If this happens, the struct will be left with a dangling member, and accessing that member will lead to undefined behavior.

>[!Best Practice]
>In most cases, we want our structs (and classes) to be owners. The easiest way to enable this is to ensure each data member has an owning type (e.g. not a viewer, pointer, or reference).

This is why string data members are almost always of type `std::string` (which is an owner), and not of type `std::string_view` (which is a viewer). The following example illustrates a case where this matters:

```cpp
#include <iostream>
#include <string>
#include <string_view>

struct Owner
{
    std::string name{}; // std::string is an owner
};

struct Viewer
{
    std::string_view name {}; // std::string_view is a viewer
};

// getName() returns the user-entered string as a temporary std::string
// This temporary std::string will be destroyed at the end of the full expression
// containing the function call.
std::string getName()
{
    std::cout << "Enter a name: ";
    std::string name{};
    std::cin >> name;
    return name;
}

int main()
{
    Owner o { getName() };  // The return value of getName() is destroyed just after initialization
    std::cout << "The owners name is " << o.name << '\n';  // ok

    Viewer v { getName() }; // The return value of getName() is destroyed just after initialization
    std::cout << "The viewers name is " << v.name << '\n'; // undefined behavior

    return 0;
}
```

The `getName()` function returns the name the user entered as a temporary `std::string`. This temporary return value is destroyed at the end of the full expression in which the function is called.

In the case of `o`, this temporary `std::string` is used to initialize `o.name`. Since `o.name` is a `std::string`, `o.name` makes a copy of the temporary `std::string`. The temporary `std::string` then dies, but `o.name` is not affected since it’s a copy. When we print `o.name` in the subsequent statement, it works as we expect.

In the case of `v`, this temporary `std::string` is used to initialize `v.name`. Since `v.name` is a `std::string_view`, `v.name` is just a view of the temporary `std::string`, not a copy. The temporary `std::string` then dies, leaving `v.name` dangling. When we print `v.name` in the subsequent statement, we get undefined behavior.

---
### Struct size and data structure alignment

>Typically, the size of a struct is the sum of the size of all its members, but not always!

Consider the following program:

```cpp
#include <iostream>

struct Foo
{
    short a {};
    int b {};
    double c {};
};

int main()
{
    std::cout << "The size of short is " << sizeof(short) << " bytes\n";
    std::cout << "The size of int is " << sizeof(int) << " bytes\n";
    std::cout << "The size of double is " << sizeof(double) << " bytes\n";

    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n";

    return 0;
}
```

On the author’s machine, this printed:

```cpp
The size of short is 2 bytes
The size of int is 4 bytes
The size of double is 8 bytes
The size of Foo is 16 bytes
```

>Note that the size of `short` + `int` + `double` is 14 bytes, but the size of `Foo` is 16 bytes!

It turns out, we can only say that the size of a struct will be _at least_ as large as the size of all the variables it contains. But it could be larger! For performance reasons, the compiler will sometimes add gaps into structures (this is called **padding**).

In the `Foo` struct above, the compiler is invisibly adding 2 bytes of padding after member `a`, making the size of the structure 16 bytes instead of 14.

>This can actually have a pretty significant impact on the size of the struct, as the following program demonstrates:

```cpp
#include <iostream>

struct Foo1
{
    short a{}; // will have 2 bytes of padding after a
    int b{};
    short c{}; // will have 2 bytes of padding after c
};

struct Foo2
{
    int b{};
    short a{};
    short c{};
};

int main()
{
    std::cout << sizeof(Foo1) << '\n'; // prints 12
    std::cout << sizeof(Foo2) << '\n'; // prints 8

    return 0;
}
```

This program prints:

12
8

Note that `Foo1` and `Foo2` have the same members, the only difference being the declaration order. Yet `Foo1` is 50% larger due to the added padding.

>[!Important]
>You can minimize padding by defining your members in decreasing order of size.
>The C++ compiler is not allowed to reorder members, so this has to be done manually.

---
### Member selection with pointers and references

>Since references to an object act just like the object itself, we can also use the member selection operator (.) to select a member from a reference to a struct:

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

void printEmployee(const Employee& e)
{
    // Use member selection operator (.) to select member from reference to struct
    std::cout << "Id: " << e.id << '\n';
    std::cout << "Age: " << e.age << '\n';
    std::cout << "Wage: " << e.wage << '\n';
}

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    printEmployee(joe);

    return 0;
}
```

---
### Member selection for pointers to structs

>However, the member selection operator (.) can’t be used directly on a pointer to a struct:

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers

    return 0;
}
```

>With normal variables or references, we can access objects directly. However, because pointers hold addresses, we first need to dereference the pointer to get the object before we can do anything with it. So one way to access a member from a pointer to a struct is as follows:

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << (*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection

    return 0;
}
```

==To make for a cleaner syntax, C++ offers a **member selection from pointer operator (->)** (also sometimes called the **arrow operator**) that can be used to select members from a pointer to an object:

```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr->id << '\n'; // Better: use -> to select member from pointer to object

    return 0;
}
```

This member selection from pointer operator (->) works identically to the member selection operator (.) but does an implicit dereference of the pointer object before selecting the member. Thus `ptr->id` is equivalent to `(*ptr).id`.

>[!Best Practice]
>When using a pointer to access a member, use the member selection from pointer operator (->) instead of the member selection operator (.).

---
### Chaining `operator->`

If the member accessed via `operator->` is a pointer to a class type, `operator->` can be applied again in the same expression to access the member of that class type.

The following example illustrates this (courtesy of reader Luna):

```cpp
#include <iostream>

struct Point
{
    double x {};
    double y {};
};

struct Triangle
{
    Point* a {};
    Point* b {};
    Point* c {};
};

int main()
{
    Point a {1,2};
    Point b {3,7};
    Point c {10,2};

    Triangle tr { &a, &b, &c };
    Triangle* ptr {&tr};

    // ptr is a pointer to a Triangle, which contains members that are pointers to a Point
    // To access member y of Point c of the Triangle pointed to by ptr, the following are equivalent:

    // access via operator.
    std::cout << (*(*ptr).c).y << '\n'; // ugly!

    // access via operator->
    std::cout << ptr -> c -> y << '\n'; // much nicer
}
```

When using more than one `operator->` in sequence (e.g `ptr->c->y`), the expression can be hard to read. Adding whitespace between the members and `operator->` (e.g. `ptr -> c -> y`) can make it a bit easier to distinguish the members being accessed from the operator.

---
### Mixing pointers and non-pointers to members

The member selection operator is always applied to the currently selected variable. If you have a mix of pointers and normal member variables, you can see member selections where . and -> are both used in sequence:

```cpp
#include <iostream>
#include <string>

struct Paw
{
    int claws{};
};

struct Animal
{
    std::string name{};
    Paw paw{};
};

int main()
{
    Animal puma{ "Puma", { 5 } };

    Animal* ptr{ &puma };

    // ptr is a pointer, use ->
    // paw is not a pointer, use .

    std::cout << (ptr->paw).claws << '\n';

    return 0;
}
```

Note that in the case of `(ptr->paw).claws`, parentheses aren’t necessary since both `operator->` and `operator.` evaluate in left to right order, but it does help readability slightly.

---
### Class templates

>For example, let’s say we’re writing a program where we need to work with pairs of `int` values, and need to determine which of the two numbers is larger. We might write a program like this:

```cpp
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

constexpr int max(Pair p) // pass by value because Pair is small
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    return 0;
}
```

Later, we discover that we also need pairs of `double` values. So we update our program to the following:

```cpp
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

struct Pair // compile error: erroneous redefinition of Pair
{
    double first{};
    double second{};
};

constexpr int max(Pair p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair p) // compile error: overloaded function differs only by return type
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    Pair p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n";

    return 0;
}
```

Unfortunately, this program won’t compile, and has a number of problems that need to be addressed.

>First, unlike functions, type definitions can’t be overloaded. The compiler will treat double second definition of `Pair` as an erroneous redeclaration of the first definition of `Pair`. Second, although functions can be overloaded, our `max(Pair)` functions only differ by return type, and overloaded functions can’t be differentiated solely by return type. Third, there is a lot of redundancy here. Each `Pair` struct is identical (except for the data type) and same with our `max(Pair)` functions (except for the return type).

We could solve the first two issues by giving our `Pair` structs different names (e.g. `PairInt` and `PairDouble`). But then we both have to remember our naming scheme, and essentially clone a bunch of code for each additional pair type we want, which doesn’t solve the redundancy problem.

Fortunately, we can do better.

---
### Class templates

>Much like a function template is a template definition for instantiating functions, a **class template** is a template definition for instantiating class types.

>[!Reminder]
>A “class type” is a struct, class, or union type. Although we’ll be demonstrating “class templates” on structs for simplicity, everything here applies equally well to classes.

#### 🔹 Function templates vs. Class templates

- **Function template** → blueprint for generating functions.
    
- **Class template** → blueprint for generating class/struct types.
    

Just like you don’t really “call” a function template directly, you don’t “use” a class template directly. Instead, you **instantiate** it with a real type, and the compiler generates an actual type definition for you.

#### 🔹 Normal (non-templated) class/struct

Example:

```cpp
struct Pair
{
    int first{};
    int second{};
};
```

This is **hard-coded** for `int`. If you want `Pair<double>` or `Pair<std::string>`, you’d have to write separate versions manually.

#### 🔹 Turning it into a class template

```cpp
template <typename T>
struct Pair
{
    T first{};
    T second{};
};
```

- `template <typename T>` says:  
    _“This is a template. Wherever I see `T` in this struct, I’ll substitute whatever type the user requests later.”_
    
- `T` is a placeholder type (like a variable, but for types).
    
- Now, instead of being locked to `int`, the struct can be reused with any type.

#### 🔹 Instantiating the template

In `main`:

```cpp
Pair<int> p1{5, 6};        // compiler generates Pair<int>
Pair<double> p2{1.2, 3.4}; // compiler generates Pair<double>
Pair<double> p3{7.8, 9.0}; // uses already-generated Pair<double>
```

When the compiler sees `Pair<int>`, it says:

> “Hmm, I don’t have a definition for `Pair<int>` yet. Let’s substitute `T = int` in the blueprint.”

It produces (behind the scenes):

```cpp
struct Pair<int>
{
    int first{};
    int second{};
};
```

Same for `Pair<double>`.

For `p3`, since `Pair<double>` was already generated earlier, the compiler just reuses that definition. It doesn’t generate it again.

#### 🔹 What the compiler _actually sees_ after instantiation

The second version in your example is showing the **expanded code** (like unrolling a macro, but type-safe):

```cpp
// Generated from template
struct Pair<int>
{
    int first{};
    int second{};
};

struct Pair<double>
{
    double first{};
    double second{};
};
```

Now your `main` just works with these concrete types like normal structs.

#### 🔹 Important points about class templates

1. **Blueprint, not a real class**  
    `Pair` by itself is _not_ a type. Only `Pair<int>` or `Pair<double>` are real types.
```cpp
Pair x; // ❌ error, compiler doesn’t know what type T is
```
- **On-demand instantiation**  
    The compiler only generates a version of the class when you use it with a specific type.
    
- **Reusability**  
    You don’t need to write separate classes for `int`, `double`, etc. One template covers all.
    
- **Specialization** (the `template <> struct Pair<int> { ... };` you saw)
    
    - This lets you say: _“Hey compiler, when someone asks for `Pair<int>`, don’t use the generic version, use this custom one.”_
        
    - Useful when some types need special handling.

==Here’s the same example as above, showing what the compiler actually compiles after all template instantiations are done:

```cpp
#include <iostream>

// A declaration for our Pair class template
// (we don't need the definition any more since it's not used)
template <typename T>
struct Pair;

// Explicitly define what Pair<int> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<int>
{
    int first{};
    int second{};
};

// Explicitly define what Pair<double> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<double>
{
    double first{};
    double second{};
};

int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```

---
### Using our class template in a function

#### 🔹 The Problem

You have a **class template**:

```cpp
template <typename T>
struct Pair {
    T first{};
    T second{};
};
```

Now you want a function `max()` that works with _any_ `Pair<T>`.

If you try to write one overload per type:

```cpp
constexpr int max(Pair<int> p) { /* ... */ }
constexpr double max(Pair<double> p) { /* ... */ }
```

✔️ Works,  
❌ But it’s **repetitive**. For every new type (`char`, `std::string`, etc.), you’d have to write another overload.

That defeats the purpose of templates.

#### 🔹 The Solution → Function Template

Instead of hardcoding each type, you write:

```cpp
template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}
```

Now:

- `T` is a **template parameter for the function** (separate from the class template).
    
- The parameter type is `Pair<T>`.
    
- The return type is also `T`.
    

This means the function works for **any `Pair<T>`**.

#### 🔹 What Happens When You Call It

##### Example 1: Explicit instantiation

```cpp
Pair<int> p1{5, 6};
std::cout << max<int>(p1);
```

- Compiler sees `max<int>(p1)`
    
- Substitutes `T = int`
    
- Instantiates this:

```cpp
constexpr int max(Pair<int> p)
{
    return (p.first < p.second ? p.second : p.first);
}
```

##### Example 2: Template Argument Deduction

```cpp
Pair<double> p2{1.2, 3.4};
std::cout << max(p2);
```

- Compiler sees parameter type `Pair<double>`
    
- Figures out `T = double` automatically
    
- Instantiates this:

```cpp
constexpr double max(Pair<double> p)
{
    return (p.first < p.second ? p.second : p.first);
}
```

No need to write `<double>` explicitly.

#### 🔹 Why This Is Powerful

1. **No redundancy** — one function template replaces many overloads.
    
2. **Scales automatically** — works for any `Pair<T>`, even user-defined types (as long as `<` works).
    
3. **Compiler-generated** — you don’t need to write versions for each type, the compiler does it for you.

#### ✅ **Summary**:  
`max(Pair<T>)` is a **function template** that works with your `Pair<T>` **class template**.

- When called, the compiler **deduces T** from the argument type.
    
- It instantiates a version of the function specialized for that type.
    
- You don’t need multiple overloads anymore — one template handles all cases.

---
### Class templates with template type and non-template type members

Class templates can have some members using a template type and other members using a normal (non-template) type. For example:

```cpp
template <typename T>
struct Foo
{
    T first{};    // first will have whatever type T is replaced with
    int second{}; // second will always have type int, regardless of what type T is
};
```

This works exactly like you’d expect: `first` will be whatever the template type `T` is, and `second` will always be an `int`.

---
### Class templates with multiple template types

Class templates can also have multiple template types. For example, if we wanted the two members of our `Pair` class to be able to have different types, we can define our `Pair` class template with two template types:

```cpp
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
void print(Pair<T, U> p)
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
    Pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
    Pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
    Pair<int, int> p3{ 7, 8 };      // a pair holding two ints

    print(p2);

    return 0;
}
```

To define multiple template types, in our template parameter declaration, we separate each of our desired template types with a comma. In the above example we define two different template types, one named `T`, and one named `U`. The actual template type arguments for `T` and `U` can be different (as in the case of `p1` and `p2` above) or the same (as in the case of `p3`).

---
### Making a function template work with more than one class type

Consider the `print()` function template from the above example:

```cpp
template <typename T, typename U>
void print(Pair<T, U> p)
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
```

Because we’ve explicitly defined the function parameter as a `Pair<T, U>`, only arguments of type `Pair<T, U>` (or those that can be converted to a `Pair<T, U>`) will match. This is ideal if we only want to be able to call our function with a `Pair<T, U>` argument.

In some cases, we may write function templates that we want to use with any type that will successfully compile. To do that, we simply use a type template parameter as the function parameter instead.

For example:

```cpp
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

struct Point
{
    int first{};
    int second{};
};

template <typename T>
void print(T p) // type template parameter will match anything
{
    std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
}

int main()
{
    Pair<double, int> p1{ 4.5, 6 };
    print(p1); // matches print(Pair<double, int>)

    std::cout << '\n';

    Point p2 { 7, 8 };
    print(p2); // matches print(Point)

    std::cout << '\n';

    return 0;
}
```

In the above example, we’ve rewritten `print()` so that it has only a single type template parameter (`T`), which will match any type. The body of the function will compile successfully for any class type that has a `first` and `second` member. We demonstrate this by calling `print()` with an object of type `Pair<double, int>`, and then again with an object of type `Point`.

There is one case that can be misleading. Consider the following version of `print()`:

```cpp
template <typename T, typename U>
struct Pair // defines a class type named Pair
{
    T first{};
    U second{};
};

template <typename Pair> // defines a type template parameter named Pair (shadows Pair class type)
void print(Pair p)       // this refers to template parameter Pair, not class type Pair
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
```

You might expect that this function will only match when called with a `Pair` class type argument. But this version of `print()` is functionally identically to the prior version where the template parameter was named `T`, and will match with _any_ type. The issue here is that when we define `Pair` as a type template parameter, it shadows other uses of the name `Pair` within the global scope. So within the function template, `Pair` refers to the template parameter `Pair`, not the class type `Pair`. And since a type template parameter will match to any type, this `Pair` matches to any argument type, not just those of class type `Pair`!

This is a good reason to stick to simple template parameter names, such a `T`, `U`, `N`, as they are less likely to shadow a class type name.

---
### std::pair

Because working with pairs of data is common, the C++ standard library contains a class template named `std::pair` (in the `<utility>` header) that is defined identically to the `Pair` class template with multiple template types in the preceding section. In fact, we can swap out the `pair` struct we developed for `std::pair`:

```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    // the members of std::pair have predefined names `first` and `second`
    std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
    std::pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
    std::pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
    std::pair<int, int> p3{ 7, 8 };      // a pair holding two ints

    print(p2);

    return 0;
}
```

We developed our own `Pair` class in this lesson to show how things work, but in real code, you should favor `std::pair` over writing your own.

---
### Using class templates in multiple files

Just like function templates, class templates are typically defined in header files so they can be included into any code file that needs them. Both template definitions and type definitions are exempt from the one-definition rule, so this won’t cause problems:

pair.h:

```cpp
#ifndef PAIR_H
#define PAIR_H

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

#endif
```

foo.cpp:

```cpp
#include "pair.h"
#include <iostream>

void foo()
{
    Pair<int> p1{ 1, 2 };
    std::cout << max(p1) << " is larger\n";
}
```

main.cpp:

```cpp
#include "pair.h"
#include <iostream>

void foo(); // forward declaration for function foo()

int main()
{
    Pair<double> p2 { 3.4, 5.6 };
    std::cout << max(p2) << " is larger\n";

    foo();

    return 0;
}
```

---
### Class template argument deduction (CTAD) C++17 [](https://www.learncpp.com/cpp-tutorial/class-template-argument-deduction-ctad-and-deduction-guides/#CTAD)

Starting in C++17, when instantiating an object from a class template, the compiler can deduce the template types from the types of the object’s initializer (this is called **class template argument deduction** or **CTAD** for short). For example:

```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<int, int> p1{ 1, 2 }; // explicitly specify class template std::pair<int, int> (C++11 onward)
    std::pair p2{ 1, 2 };           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)

    return 0;
}
```

CTAD is only performed if no template argument list is present. Therefore, both of the following are errors:

```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<> p1 { 1, 2 };    // error: too few template arguments, both arguments not deduced
    std::pair<int> p2 { 3, 4 }; // error: too few template arguments, second argument not deduced

    return 0;
}
```

>Since CTAD is a form of type deduction, we can use literal suffixes to change the deduced type:

```cpp
#include <utility> // for std::pair

int main()
{
    std::pair p1 { 3.4f, 5.6f }; // deduced to pair<float, float>
    std::pair p2 { 1u, 2u };     // deduced to pair<unsigned int, unsigned int>

    return 0;
}
```

---
### **Why doesn’t CTAD work with aggregates in C++17?**

Your custom `Pair` is an **aggregate** (a simple struct without constructors).  
In **C++17**, CTAD **only works with constructors**, not with aggregate initialization.

So:

```cpp
Pair p2{1, 2}; // ❌ error in C++17
```

Because there’s no constructor, the compiler has no rule to deduce `<int, int>` from `{1, 2}`.

### **Deduction Guides**

To fix this in C++17, you add a **deduction guide**.  
A deduction guide explicitly tells the compiler **how to map constructor arguments to template parameters**.

Example:

```cpp
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;
```

This means:

- If you see `Pair(x, y)` where `x` has type `T` and `y` has type `U`,
    
- Deduce the type as `Pair<T, U>`.
    

Now this works:

```cpp
Pair p2{1, 2};   // ✅ deduced as Pair<int, int>
```

>[!Tip]
>C++20 added the ability for the compiler to automatically generate deduction guides for aggregates, so deduction guides should only need to be provided for C++17 compatibility.

---
### Type template parameters with default values

>Just like function parameters can have default arguments, template parameters can be given default values. These will be used when the template parameter isn’t explicitly specified and can’t be deduced.

Here’s a modification of our `Pair<T, U>` class template program above, with type template parameters `T` and `U` defaulted to type `int`:

```cpp
template <typename T=int, typename U=int> // default T and U to type int
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    Pair p3;                   // uses default Pair<int, int>

    return 0;
}
```

Our definition for `p3` does not explicitly specify types for the type template parameters, nor is there an initializer for these types to be deduced from. Therefore, the compiler will use the types specified in the defaults, which means `p3` will be of type `Pair<int, int>`.

---
### CTAD doesn’t work with non-static member initialization

CTAD doesn’t work with non-static member initialization

When initializing the member of a class type using non-static member initialization, CTAD will not work in this context. All template arguments must be explicitly specified:

```cpp
#include <utility> // for std::pair

struct Foo
{
    std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
    std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
};

int main()
{
    std::pair p3{ 1, 2 };           // ok, CTAD can be used here
    return 0;
}
```

--> Foo is a defination so we are not constructing it.

---
### CTAD doesn’t work with function parameters

CTAD stands for class template _argument_ deduction, not class template _parameter_ deduction, so it will only deduce the type of template arguments, not template parameters.

Therefore, CTAD can’t be used in function parameters.

```cpp
#include <iostream>
#include <utility>

void print(std::pair p) // compile error, CTAD can't be used here
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

In such cases, you should use a template instead:

```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

---
### Alias templates

>Creating a type alias for a class template where all template arguments are explicitly specified works just like a normal type alias:

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
void print(const Pair<T>& p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    using Point = Pair<int>; // create normal type alias
    Point p { 1, 2 };        // compiler replaces this with Pair<int>

    print(p);

    return 0;
}
```

Such aliases can be defined locally (e.g. inside a function) or globally.

>Now, what if you want an alias for a **template**, where the user still provides some template arguments? That’s what **alias templates** do.

```cpp
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Alias template
template <typename T>
using Coord = Pair<T>;
```

- `Coord<int>` is just another name for `Pair<int>`.
    
- It doesn’t make a new type, it’s purely shorthand.
    

So:

```cpp
Coord<int> p{1, 2};
```

is exactly same as:

```cpp
Pair<int> p{1, 2};
```

>Using with functions

The function template:

```cpp
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}
```

- Notice: `Coord<T>` just means `Pair<T>`.
    
- The compiler treats them as the same type.

>CTAD and C++20

Before C++20:

```cpp
Coord<int> p1{1, 2}; // must specify <int>
```

With C++20, **alias template deduction** lets you skip the `<int>`:

```cpp
Coord p2{1, 2}; // compiler deduces T = int
```

This works the same way CTAD (Class Template Argument Deduction) does for normal templates, but now also works for alias templates.

✅ **Key takeaway**:

- An **alias template** is just a shorthand for an existing template type.
    
- It doesn’t define a new type, just another name.
    
- With C++20, you can use CTAD with alias templates, making them even easier to use.

--> Complete Example:

```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's our alias template
// Alias templates must be defined in global scope
template <typename T>
using Coord = Pair<T>; // Coord is an alias for Pair<T>

// Our print function template needs to know that Coord's template parameter T is a type template parameter
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}

int main()
{
    Coord<int> p1 { 1, 2 }; // Pre C++-20: We must explicitly specify all type template argument
    Coord p2 { 1, 2 };      // In C++20, we can use alias template deduction to deduce the template arguments in cases where CTAD works

    std::cout << p1.first << ' ' << p1.second << '\n';
    print(p2);

    return 0;
}
```

>In this example, we’re defining an alias template named `Coord` as an alias for `Pair<T>`, where type template parameter `T` will be defined by the user of the Coord alias. `Coord` is the alias template, and `Coord<T>` is the instantiated type alias for `Pair<T>`. Once defined, we can use `Coord` where we would use `Pair`, and `Coord<T>` where we would use `Pair<T>`.

There are a couple of things worth noting about this example.

First, unlike normal type aliases (which can be defined inside a block), alias templates must be defined in the global scope (as all templates must).

Second, prior to C++20, we must explicitly specify the template arguments when we instantiate an object using an alias template. As of C++20, we can use **alias template deduction**, which will deduce the type of the template arguments from an initializer in cases where the aliased type would work with CTAD.

Third, because CTAD doesn’t work on function parameters, when we use an alias template as a function parameter, we must explicitly define the template arguments used by the alias template. In other words, we do this:

```cpp
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}
```

Not this:

```cpp
void print(const Coord& c) // won't work, missing template arguments
{
    std::cout << c.first << ' ' << c.second << '\n';
}
```

This is no different than if we’d used `Pair` or `Pair<T>` instead of `Coord` or `Coord<T>`.

---
### [Complete Summary and quiz](https://www.learncpp.com/cpp-tutorial/chapter-13-summary-and-quiz/****)

---
### Question: What is an enumeration and structs  in c++?

>> An **enumeration** (or **enum**) in C++ is a user-defined type that allows you to assign names to a set of integral constant values.  
> It improves readability and type safety by letting us use meaningful names instead of raw numbers.

> A **struct** in C++ is a user-defined type that groups together related variables (called data members) under a single name.  
> It’s similar to a class, but by default, its members are **public**, whereas in a class they are **private**.

---
>In general programming, an **aggregate data type** (also called an **aggregate**) is any type that can contain multiple data members. In C++, arrays and structs with only data members are **aggregates**.

---
>Enumerated types hold integral values (usually int). Since integral values are passed by value, enumerated types should be passed by value.

---
Darwin code example:

```cpp
struct Mob
{
    MonsterType type{MonsterType::slime};
    std::string name{"Regular Slime"};
    int health{ 10 };
};
```

- ✅ Default initialization is good → avoids uninitialized garbage.
    
- ✅ Default to `slime` makes testing easier (safe fallback).
    
- ✅ Readable and extendable.

#### 🔹 Your idea: Make it generic with templates

Instead of fixing `Mob` to only use `MonsterType`, you could template it:

```cpp
template <typename Type>
struct Mob
{
    Type type{};  // will use Type’s default initialization
    std::string name{"Unnamed"};
    int health{10};
};
```

Now you can do:

```cpp
enum class MonsterType { slime, goblin, orc };
enum class HumanType   { warrior, hunter };
enum class WaifuType   { princess, witch };

Mob<MonsterType> slimeMob;
Mob<HumanType>   hunterMob;
Mob<WaifuType>   waifuMob;
```

#### 🔹 Benefits

1. **Flexibility** → Works with different type categories (`MonsterType`, `HumanType`, etc.).
    
2. **Default safe init** → Each type will still fall back to its `enum`’s first/default value.
    
3. **Reusable** → One generic `Mob` definition instead of writing different ones.

---
