
- The process of converting data from one type to another type is called “type conversion”.
- Implicit type conversion is performed automatically by the compiler when one data type is required, but a different data type is supplied.
- Explicit type conversion is requested by using a cast operator, such as `static_cast`.
- Conversions do not change the data being converted. Instead, the conversion process uses that data as input, and produces the converted result.
- When converting a value to another type of value, the conversion process produces a temporary object of the target type that holds the result of the conversion.
---
### Why conversions are needed

>The value of an object is stored as a sequence of bits, and the data type of the object tells the compiler how to interpret those bits into meaningful values. Different data types may represent the “same” value differently. For example, the integer value `3` might be stored as binary `0000 0000 0000 0000 0000 0000 0000 0011`, whereas floating point value `3.0` might be stored as binary `0100 0000 0100 0000 0000 0000 0000 0000`.

So what happens when we do something like this?

```cpp
float f{ 3 }; // initialize floating point variable with int 3
```

In such a case, the compiler can’t just copy the bits used to represent `int` value `3` into the memory allocated for `float` variable `f`. If it were to do so, then when `f` (which has type `float`) was evaluated, those bits would be interpreted as a `float` rather than an `int`, and who knows what `float` value we’d end up with!

---
### When implicit type conversion happens

**Implicit type conversion** (also called **automatic type conversion** or **coercion**) is performed automatically by the compiler when an expression of some type is supplied in a context where some other type is expected. The vast majority of type conversions in C++ are implicit type conversions. For example, implicit type conversion happens in all of the following cases:

When initializing (or assigning a value to) a variable with a value of a different data type:

```cpp
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double
```

When the type of a return value is different from the function’s declared return type:

```cpp
float doSomething()
{
    return 3.0; // double value 3.0 implicitly converted to type float
}
```

When using certain binary operators with operands of different types:

```cpp
double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double
```

When using a non-Boolean value in an if-statement:

```cpp
if (5) // int value 5 implicitly converted to type bool
{
}
```

When an argument passed to a function is a different type than the function parameter:

```cpp
void doSomething(long l)
{
}

doSomething(3); // int value 3 implicitly converted to type long
```

So how does the compiler know how to convert a value to a different type anyway?

---
### The standard conversions

As part of the core language, the C++ standard defines a collection of conversion rules known as the “standard conversions”. The **standard conversions** specify how various fundamental types (and certain compound types, including arrays, references, pointers, and enumerations) convert to other types within that same group.

As of C++23, there are 14 different standard conversions. These can be roughly grouped into 5 general categories:

|Category|Meaning|Link|
|---|---|---|
|Numeric promotions|Conversions of small integral types to `int` or `unsigned int`, and of `float` to `double`.|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric conversions|Other integral and floating point conversions that aren’t promotions.|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Qualification conversions|Conversions that add or remove `const` or `volatile`.||
|Value transformations|Conversions that change the value category of an expression|[12.2 -- Value categories (lvalues and rvalues)](https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/)|
|Pointer conversions|Conversions from `std::nullptr` to pointer types, or pointer types to other pointer types||

For example, converting an `int` value to a `float` value falls under the numeric conversions category, so the compiler to perform such a conversion, the compiler simply need apply the `int` to `float` numeric conversion rules.

---
### Type conversion can fail

When a type conversion is invoked (whether implicitly or explicitly), the compiler will determine whether it can convert the value from the current type to the desired type. If a valid conversion can be found, then the compiler will produce a new value of the desired type.

If the compiler can’t find an acceptable conversion, then the compilation will fail with a compile error. Type conversions can fail for any number of reasons. For example, the compiler might not know how to convert a value between the original type and the desired type.

For example:

```cpp
int main()
{
    int x { "14" };

    return 0;
}
```

The because there isn’t a standard conversion from the string literal “14” to `int`, the compiler will produce an error. For example, GCC produces the error: `prog.cc:3:13: error: invalid conversion from 'const char*' to 'int' [-fpermissive]`.

In other cases, specific features may disallow some categories of conversions. For example:

```cpp
int x { 3.5 }; // brace-initialization disallows conversions that result in data loss
```

Even though the compiler knows how to convert a `double` value to an `int` value, narrowing conversions are disallowed when using brace-initialization.

There are also cases where the compiler may not be able to figure out which of several possible type conversions is the best one to use.

>[!Tip]
>The full set of rules describing how type conversions work is both lengthy and complicated, and for the most part, type conversion “just works”.

---
### Floating-point and integral promotion

#### ✅ 1. **Why C++ Allows Type Size Variability**

> “This variability was allowed so that the `int` and `double` data types could be set to the size that maximizes performance on a given architecture.”

- C++ does **not guarantee** that `int` will always be 4 bytes or that `double` will always be 8 bytes.
    
- Instead, the compiler chooses the size that best **matches the CPU's natural data size**.
    
- This is done for **performance reasons**: the idea is to make programs **run faster** on the hardware.
    

#### ✅ 2. **What is the CPU’s Natural Data Size?**

> “For example, a 32-bit computer will typically be able to process 32-bits of data at a time.”

- A **32-bit CPU** is designed to work most efficiently with **32-bit values**.
    
- This is called the CPU’s **natural word size**.
    

So:

- On a 32-bit CPU, `int` will usually be 32 bits.
    
- On a 64-bit CPU, `int` might still be 32 bits, but `long` or `size_t` might be 64 bits.
    

#### ✅ 3. **What is Width?**

> “The number of bits a data type uses is called its width. A wider data type is one that uses more bits, and a narrower data type is one that uses less bits.”

- `char` → usually 8 bits = narrow
    
- `short` → 16 bits = medium
    
- `int` → 32 bits = wider
    
- `long long` → 64 bits = widest (among integers)
    

This is just terminology: "narrow" means "fewer bits", and "wide" means "more bits".

#### ✅ 4. **Why Using Narrow Types Can Be Slower**

> “Some 32-bit processors (such as 32-bit x86 CPUs) can manipulate 8-bit or 16-bit values directly. However, doing so is often slower…”

- CPUs are **optimized for their natural size**.
    
- Even if they _can_ work with 8-bit or 16-bit values, it might require **more steps**, or it might not use the CPU’s full data path.
    

#### 📌 Example:

- A 32-bit CPU wants to add two `char` values (8-bit).
    
- It **may promote** both `char`s to `int`s (32-bit) before doing the addition.
    
- This is called **promotion** (a kind of standard conversion).
    
- Then it might **truncate** the result back to `char`.
    

That whole promotion + operation + truncation takes more time than just doing a 32-bit operation.

#### ✅ 5. **Some CPUs _Require_ Wide Data**

> “Other 32-bit CPUs (like 32-bit PowerPC CPUs), can only operate on 32-bit values, and additional tricks must be employed…”

- Some CPUs **cannot work** directly on narrow types at all.
    
- The compiler must use **bit masking or shifting tricks** to emulate working with smaller values.
    
- This makes narrow types **even slower** to use.
    
#### ✅ Conclusion

C++ lets type widths vary to allow compilers to choose the most **efficient size** for each platform:

- This helps make code **portable** and **fast**.
    
- It’s why `int` is usually 32-bit on modern systems — because it matches what CPUs handle best.

>[!A reminder]
>The number of bits a data type uses is called its width. A wider data type is one that uses more bits, and a narrower data type is one that uses less bits.

---
### 🔹 What is Numeric Promotion?

**Numeric promotion** is:

> The automatic conversion of a **narrower** numeric type (like `char`, `short`, or `float`) to a **wider** type (usually `int` or `double`) to ensure better performance and accuracy.
> 
### 🔹 Why Does C++ Do This?

> “C++ is designed to be portable and performant…”

- Different CPUs have different "natural" sizes they work best with (like 32-bit or 64-bit).
    
- Some CPUs **can’t work efficiently** (or at all) with small values like `char` or `short`.
    
- So, to make sure your code works **correctly and efficiently** on all hardware, the compiler **automatically promotes** narrow types to wider ones.
    
### 🔸 Example

```cpp
char ch = 65; int x = ch + 5;
```

Here:

- `ch` is a `char` (8 bits),
    
- When you do `ch + 5`, the `char` is **automatically promoted to an `int`** (usually 32 bits),
    
- Then `int + int` happens.
    

This makes the operation **safe and fast**.

### 🔹 Promotions Are Always Safe

> “All numeric promotions are value-preserving…”

That means:

- No data is lost in the conversion.
    
- Every possible value of the source type **fits safely** in the destination type.
    

🟢 Example of value-preserving (safe):

```cpp
char c = 100; int i = c; // Always safe: char [-128 to 127] fits inside int [-2 billion to 2 billion]
```

🔴 Example of NOT value-preserving (unsafe conversion, called narrowing):

```cpp
`int i = 1000; char c = i; // NOT safe: might lose data because char can’t hold 1000`
```

### 🔹 The Compiler Applies Promotions Silently

> “Because promotions are safe, the compiler will freely use numeric promotion… and will not issue a warning.”

- Since there's **no risk of data loss**, the compiler doesn’t bother warning you.
    
- These conversions are **automatic**, so you don’t need to write a cast.
---
### Numeric promotion reduces redundancy

Numeric promotion solves another problem as well. Consider the case where you wanted to write a function to print a value of type `int`:

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

While this is straightforward, what happens if we want to also be able to print a value of type `short`, or type `char`? If type conversions did not exist, we’d have to write a different print function for `short` and another one for `char`. And don’t forget another version for `unsigned char`, `signed char`, `unsigned short`, `wchar_t`, `char8_t`, `char16_t`, and `char32_t`! You can see how this quickly becomes unmanageable.

Numeric promotion comes to the rescue here: we can write functions that have `int` and/or `double` parameters (such as the `printInt()` function above). That same code can then be called with arguments of types that can be numerically promoted to match the types of the function parameters.

---
### Numeric promotion categories

>The numeric promotion rules are divided into two subcategories: `integral promotions` and `floating point promotions`. Only the conversions listed in these categories are considered to be numeric promotions.

---
### Floating point promotions

We’ll start with the easier one.

Using the **floating point promotion** rules, a value of type `float` can be converted to a value of type `double`.

This means we can write a function that takes a `double` and then call it with either a `double` or a `float` value:

```cpp
#include <iostream>

void printDouble(double d)
{
    std::cout << d << '\n';
}

int main()
{
    printDouble(5.0); // no conversion necessary
    printDouble(4.0f); // numeric promotion of float to double

    return 0;
}
```

In the second call to `printDouble()`, the `float` literal `4.0f` is promoted into a `double`, so that the type of argument matches the type of the function parameter.

---
### Integral promotions

The integral promotion rules are more complicated.

Using the **integral promotion** rules, the following conversions can be made:

- signed char or signed short can be converted to int.
- unsigned char, char8_t, and unsigned short can be converted to int if int can hold the entire range of the type, or unsigned int otherwise.
- If char is signed by default, it follows the signed char conversion rules above. If it is unsigned by default, it follows the unsigned char conversion rules above.
- bool can be converted to int, with false becoming 0 and true becoming 1.

Assuming an 8 bit byte and an `int` size of 4 bytes or larger (which is typical these days), the above basically means that `bool`, `char`, `signed char`, `unsigned char`, `signed short`, and `unsigned short` all get promoted to `int`.

There are a few other integral promotion rules that are used less often. These can be found at [https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion](https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion).

In most cases, this lets us write a function taking an `int` parameter, and then use it with a wide variety of other integral types. For example:

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(2);

    short s{ 3 }; // there is no short literal suffix, so we'll use a variable for this one
    printInt(s); // numeric promotion of short to int

    printInt('a'); // numeric promotion of char to int
    printInt(true); // numeric promotion of bool to int

    return 0;
}
```

#### 🔷 The Context: **Integral Promotion** in C++

When you use smaller integer types (like `char`, `short`, `unsigned char`, etc.), **C++ automatically promotes them to `int` or `unsigned int`** so they can be used efficiently in arithmetic or function calls.

This is part of **numeric promotion**, specifically called **integral promotion**.

#### 🔶 Now, the Explanation:

##### ✅ 1. **Unsigned promotion to `unsigned int` instead of `int`**

> "On some architectures (e.g., with 2-byte ints), it is possible for some of the unsigned integral types to be promoted to `unsigned int` rather than `int`."

🔸 What this means:

- Normally, `char`, `short`, or `unsigned char` get promoted to `int`.
    
- BUT, **if `int` is not wide enough** to represent _all values_ of the **unsigned type**, then:  
    👉 It gets promoted to **`unsigned int`** instead!
    

##### 🔸 Example:

On a platform where:

- `unsigned short` can store up to `65535`
    
- But `int` can only go up to `32767` (2 bytes)
    

Then:

```cpp
`unsigned short x = 60000; int y = x;  // This could cause overflow on 2-byte int!`
```

So, instead of promoting `x` to `int`, C++ **may promote it to `unsigned int`** to **preserve the value safely**.

##### ✅ 2. **Unsigned types can be promoted to signed types**

> "Some narrower unsigned types (such as `unsigned char`) may be promoted to larger signed types (such as `int`)."

🔸 What this means:

- `unsigned char` (0 to 255) may be promoted to `int` (e.g., -32,768 to 32,767)
    
- Even though it's _unsigned_, the promotion target might still be _signed_ (`int`)
    

This happens **only if the signed type can hold all possible values of the unsigned type**.

So:

```cpp
`unsigned char uc = 200; int x = uc;  // safe: 200 fits in int, even though signedness changes`
```

✔️ This is **allowed** because **the value is preserved**, even if the **signedness is not**.

---
### Not all widening conversions are numeric promotions

Some widening type conversions (such as `char` to `short`, or `int` to `long`) are not considered to be numeric promotions in C++ (they are `numeric conversions`, which we’ll cover shortly in lesson [10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)). This is because such conversions do not assist in the goal of converting smaller types to larger types that can be processed more efficiently.

The distinction is mostly academic. However, in certain cases, the compiler will favor numeric promotions over numeric conversions. We’ll see examples where this makes a difference when we cover function overload resolution (in upcoming lesson [11.3 -- Function overload resolution and ambiguous matches](https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/)).

---
### Numeric conversions

>C++ supports another category of numeric type conversions, called **numeric conversions**. These numeric conversions cover additional type conversions between fundamental types.

>[!Key Insight]
>Any type conversion covered by the numeric promotion rules ([10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)) is called a numeric promotion, not a numeric conversion.

There are five basic types of numeric conversions.

1. Converting an integral type to any other integral type (excluding integral promotions):

```cpp
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int
```

2. Converting a floating point type to any other floating point type (excluding floating point promotions):

```cpp
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double
```

3. Converting a floating point type to any integral type:

```cpp
int i = 3.5; // convert double to int
```

4. Converting an integral type to any floating point type:

```cpp
double d = 3; // convert int to double
```

5. Converting an integral type or a floating point type to a bool:

```cpp
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```

>[!As an aside…]
Because brace initialization strictly disallows some types of numeric conversions (more on this next lesson), we use copy initialization in this lesson (which does not have any such limitations) in order to keep the examples simple.

---
### Safe and unsafe conversions

Unlike numeric promotions (which are always value-preserving and thus “safe”), many numeric conversions are unsafe. An **unsafe conversion** is one where at least one value of the source type cannot be converted into an equal value of the destination type.

Numeric conversions fall into three general safety categories:

1. _Value-preserving conversions_ are safe numeric conversions where the destination type can exactly represent all possible values in the source type.

For example, `int` to `long` and `short` to `double` are safe conversions, as the source value can always be converted to an equal value of the destination type.

```cpp
int main()
{
    int n { 5 };
    long l = n; // okay, produces long value 5

    short s { 5 };
    double d = s; // okay, produces double value 5.0

    return 0;
}
```

Compilers will typically not issue warnings for implicit value-preserving conversions.

A value converted using a value-preserving conversion can always be converted back to the source type, resulting in a value that is equivalent to the original value:

```cpp
#include <iostream>

int main()
{
    int n = static_cast<int>(static_cast<long>(3)); // convert int 3 to long and back
    std::cout << n << '\n';                         // prints 3

    char c = static_cast<char>(static_cast<double>('c')); // convert 'c' to double and back
    std::cout << c << '\n';                               // prints 'c'

    return 0;
}
```

2. _Reinterpretive conversions_ are unsafe numeric conversions where the converted value may be different than the source value, but no data is lost. Signed/unsigned conversions fall into this category.

For example, when converting a `signed int` to an `unsigned int`:

```cpp
int main()
{
    int n1 { 5 };
    unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

    int n2 { -5 };
    unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

    return 0;
}
```

In the case of `u1`, the signed int value `5` is converted to unsigned int value `5`. Thus, the value is preserved in this case.

In the case of `u2`, the signed int value `-5` is converted to an unsigned int. Since an unsigned int can’t represent negative numbers, the result will be modulo wrapped to a large integral value that is outside the range of a signed int. The value is not preserved in this case.

Such value changes are typically undesirable, and will often cause the program to exhibit unexpected or implementation-defined behavior.

>[!Warning]
Even though reinterpretive conversions are unsafe, most compilers leave implicit signed/unsigned conversion warnings disabled by default.
This is because in some areas of modern C++ (such as when working with standard library arrays), signed/unsigned conversions can be hard to avoid. And practically speaking, the majority of such conversions do not actually result in a value change. Therefore, enabling such warnings can lead to many spurious warnings for signed/unsigned conversions that are actually okay (drowning out legitimate warnings).
If you choose to leave such warnings disabled, be extra careful of inadvertent conversions between these types (particularly when passing an argument to a function taking a parameter of the opposite sign).

Values converted using a reinterpretive conversion can be converted back to the source type, resulting in a value equivalent to the original value (even if the initial conversion produced a value out of range of the source type). As such, reinterpretive conversions do not lose data during the conversion process.

```cpp
#include <iostream>

int main()
{
    int u = static_cast<int>(static_cast<unsigned int>(-5)); // convert '-5' to unsigned and back
    std::cout << u << '\n'; // prints -5

    return 0;
}
```

>[!For advanced readers]
Prior to C++20, converting an unsigned value that is out-of-range of the signed value is technically implementation-defined behavior (due to the allowance that signed integers could use a different binary representation than unsigned integers). In practice, this was a non-issue on modern system.
C++20 now requires that signed integers use 2s complement. As a result, the conversion rules were changed so that the above is now well-defined as a reinterpretive conversion (an out-of-range conversion will produce modulo wrapping).
Note that while such conversions are well defined, signed arithmetic overflow (which occurs when an arithmetic operation produces a value outside the range that can be stored) is still undefined behavior.

3. _Lossy conversions_ are unsafe numeric conversions where data may be lost during the conversion.

For example, `double` to `int` is a conversion that may result in data loss:

```cpp
int i = 3.0; // okay: will be converted to int value 3 (value preserved)
int j = 3.5; // data lost: will be converted to int value 3 (fractional value 0.5 lost)
```

Conversion from `double` to `float` can also result in data loss:

```cpp
float f = 1.2;        // okay: will be converted to float value 1.2 (value preserved)
float g = 1.23456789; // data lost: will be converted to float 1.23457 (precision lost)
```

Converting a value that has lost data back to the source type will result in a value that is different than the original value:

```cpp
#include <iostream>

int main()
{
    double d { static_cast<double>(static_cast<int>(3.5)) }; // convert double 3.5 to int and back
    std::cout << d << '\n'; // prints 3

    double d2 { static_cast<double>(static_cast<float>(1.23456789)) }; // convert double 1.23456789 to float and back
    std::cout << d2 << '\n'; // prints 1.23457

    return 0;
}
```

For example, if `double` value `3.5` is converted to `int` value `3`, the fractional component `0.5` is lost. When `3` is converted back to a `double,` the result is `3.0`, not `3.5`.

Compilers will generally issue a warning (or in some cases, an error) when an implicit lossy conversion would be performed at runtime.

>[!Warning]
Some conversions may fall into different categories depending on the platform.
For example, `int` to `double` is typically a safe conversion, because `int` is usually 4 bytes and `double` is usually 8 bytes, and on such systems, all possible `int` values can be represented as a `double`. However, there are architectures where both `int` and `double` are 8 bytes. On such architectures, `int` to `double` is a lossy conversion!
We can demonstrate this by casting a long long value (which must be at least 64 bits) to double and back:
```cpp
#include <iostream>

int main()
{
    std::cout << static_cast<long long>(static_cast<double>(10000000000000001LL));

    return 0;
}
```

This prints:

10000000000000000

Note that our last digit has been lost!

Unsafe conversions should be avoided as much as possible. However, this is not always possible. When unsafe conversions are used, it is most often when:

- We can constrain the values to be converted to just those that can be converted to equal values. For example, an `int` can be safely converted to an `unsigned int` when we can guarantee that the `int` is non-negative.
- We don’t mind that some data is lost because it is not relevant. For example, converting an `int` to a `bool` results in the loss of data, but we’re typically okay with this because we’re just checking if the `int` has value `0` or not.
---
### More on numeric conversions

The specific rules for numeric conversions are complicated and numerous, so here are the most important things to remember.

- In _all_ cases, converting a value into a type whose range doesn’t support that value will lead to results that are probably unexpected. For example:

```cpp
int main()
{
    int i{ 30000 };
    char c = i; // chars have range -128 to 127

    std::cout << static_cast<int>(c) << '\n';

    return 0;
}
```

In this example, we’ve assigned a large integer to a variable with type `char` (that has range -128 to 127). This causes the char to overflow, and produces an unexpected result:

48

- Remember that overflow is well-defined for unsigned values and produces undefined behavior for signed values.
- Converting from a larger integral or floating point type to a smaller type from the same family will generally work so long as the value fits in the range of the smaller type. For example:

```cpp
int i{ 2 };
short s = i; // convert from int to short
std::cout << s << '\n';

double d{ 0.1234 };
float f = d;
std::cout << f << '\n';
```

This produces the expected result:

2
0.1234

- In the case of floating point values, some rounding may occur due to a loss of precision in the smaller type. For example:

```cpp
float f = 0.123456789; // double value 0.123456789 has 9 significant digits, but float can only support about 7
std::cout << std::setprecision(9) << f << '\n'; // std::setprecision defined in iomanip header
```

In this case, we see a loss of precision because the `float` can’t hold as much precision as a `double`:

0.123456791

- Converting from an integer to a floating point number generally works as long as the value fits within the range of the floating point type. For example:

```cpp
int i{ 10 };
float f = i;
std::cout << f << '\n';
```

This produces the expected result:

10

- Converting from a floating point to an integer works as long as the value fits within the range of the integer, but any fractional values are lost. For example:

```cpp
int i = 3.5;
std::cout << i << '\n';
```

In this example, the fractional value (.5) is lost, leaving the following result:

3

While the numeric conversion rules might seem scary, in reality the compiler will generally warn you if you try to do something dangerous (excluding some signed/unsigned conversions).

---
#### 🔹 **Source Type**:

The **original type** of the value you're converting **from**.

#### 🔹 **Destination Type**:

The **new type** you're converting the value **to**.

### Narrowing conversions

>In C++, a **narrowing conversion** is a potentially unsafe numeric conversion where the destination type may not be able to hold all the values of the source type.

The following conversions are defined to be narrowing:

- From a floating point type to an integral type.
- From a floating point type to a narrower or lesser ranked floating point type, unless the value being converted is constexpr and is in range of the destination type (even if the destination type doesn’t have the precision to store all the significant digits of the number).
- From an integral to a floating point type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.
- From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type. This covers both wider to narrower integral conversions, as well as integral sign conversions (signed to unsigned, or vice-versa).

##### 🔸 “Unless the value being converted is `constexpr` and whose value can be stored exactly in the destination type.”

There is **an exception** to narrowing conversions:  
If the value is known **at compile-time** (`constexpr`), and it's **within the valid range** of the destination type, it's **not considered narrowing**.

**Example:**

```cpp
`constexpr int x = 42; char y = x; // OK: 42 fits in char, and x is constexpr`
```

But:

```cpp
`int x = 42; char y = x; // narrowing, because x is not constexpr`
```

>In most cases, implicit narrowing conversions will result in compiler warnings, with the exception of signed/unsigned conversions (which may or may not produce warnings, depending on how your compiler is configured).

Narrowing conversions should be avoided as much as possible, because they are potentially unsafe, and thus a source of potential errors.

>[!Best Practice]
>Because they can be unsafe and are a source of errors, avoid narrowing conversions whenever possible.

---
### Make intentional narrowing conversions explicit

>Narrowing conversions are not always avoidable -- this is particularly true for function calls, where the function parameter and argument may have mismatched types and require a narrowing conversion.

In such cases, it is a good idea to convert an implicit narrowing conversion into an explicit narrowing conversion using `static_cast`. Doing so helps document that the narrowing conversion is intentional, and will suppress any compiler warnings or errors that would otherwise result.

For Example:

```cpp
void someFcn(int i)
{
}

int main()
{
    double d{ 5.0 };

    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning

    // good: we're explicitly telling the compiler this narrowing conversion is intentional
    someFcn(static_cast<int>(d)); // no warning generated

    return 0;
}
```

>[!best practice]
>If you need to perform a narrowing conversion, use `static_cast` to convert it into an explicit conversion.

---

>[!Key Insight]
>Numeric conversion is allowed by list-initializiation but narrowing conversion produces error in list-initialization because it is disallowed.

### Brace initialization disallows narrowing conversions

>Narrowing conversions are disallowed when using brace initialization (which is one of the primary reasons this initialization form is preferred), and attempting to do so will produce a compile error.

For Example:

```cpp
int main()
{
    int i { 3.5 }; // won't compile

    return 0;
}
```

`error C2397: conversion from 'double' to 'int' requires a narrowing conversion`

>If you actually want to do a narrowing conversion inside a brace initialization, use `static_cast` to convert the narrowing conversion into an explicit conversion:

>[!tip]
>Explicit narrowing conversion is allowed also in list-initialization.

---

>[!Key Insight]
>Double is not a integral type instead it is a floating-point data type.

### Some constexpr conversions aren’t considered narrowing

When the source value of a narrowing conversion isn’t known until runtime, the result of the conversion also can’t be determined until runtime. In such cases, whether the narrowing conversion preserves the value or not also can’t be determined until runtime. For example:

```cpp
#include <iostream>

void print(unsigned int u) // note: unsigned
{
    std::cout << u << '\n';
}

int main()
{
    std::cout << "Enter an integral value: ";
    int n{};
    std::cin >> n; // enter 5 or -5
    print(n);      // conversion to unsigned may or may not preserve value

    return 0;
}
```

In the above program, the compiler has no idea what value will be entered for `n`. When `print(n)` is called, the conversion from `int` to `unsigned int` will be performed at that time, and the results may be value-preserving or not depending on what value for `n` was entered. Thus, a compiler that has signed/unsigned warnings enabled will issue a warning for this case.

However, you may have noticed that most of the narrowing conversions definitions have an exception clause that begins with “unless the value being converted is constexpr and …”. For example, a conversion is narrowing when it is “From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.”

When the source value of a narrowing conversion is constexpr, the specific value to be converted must be known to the compiler. In such cases, the compiler can perform the conversion itself, and then check whether the value was preserved. If the value was not preserved, the compiler can halt compilation with an error. If the value is preserved, the conversion is not considered to be narrowing (and the compiler can replace the entire conversion with the converted result, knowing that doing so is safe).

For example:

```cpp
#include <iostream>

int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```

Let’s apply the rule “From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type” to both of the conversions above.

In the case of `n1` and `u1`, `n1` is an `int` and `u1` is an `unsigned int`, so this is a conversion from an integral type to another integral type that cannot represent all values of the original type. However, `n1` is constexpr, and its value `5` can be represented exactly in the destination type (as unsigned value `5`). Therefore, this is not considered to be a narrowing conversion, and we are allowed to list initialize `u1` using `n1`.

In the case of `n2` and `u2`, things are similar. Although `n2` is constexpr, its value `-5` cannot be represented exactly in the destination type, so this is considered to be a narrowing conversion, and because we are doing list initialization, the compiler will error and halt the compilation.

Strangely, conversions from a floating point type to an integral type do not have a constexpr exclusion clause, so these are always considered narrowing conversions even when the value to be converted is constexpr and fits in the range of the destination type:

```cpp
int n { 5.0 }; // compile error: narrowing conversion
```

Even more strangely, conversions from a constexpr floating point type to a narrower floating point type are not considered narrowing even when there is a loss of precision!

```cpp
constexpr double d { 0.1 };
float f { d }; // not narrowing, even though loss of precision results
```

>[!Warning]
Conversion from a constexpr floating point type to a narrower floating point type is not considered narrowing even when a loss of precision results.

---

>[!Key Insight]
>literal is a kind of implicit constexpr.

#### ✅ **Key Concept: List Initialization with `constexpr` Initializers**

In C++ (especially C++11 and beyond), when you use **list initialization** with `{}`, it **normally disallows narrowing conversions** at compile time to make your code safer.

However, there's a **special rule**:

> If the initializer is a `constexpr` **and the value fits** in the destination type **exactly or within range**, then the compiler will **allow** the initialization — even if it looks like a narrowing conversion.

#### 🔍 What does this mean practically?

#### 🧪 Without suffixes or casts:

```cpp
`unsigned int u { 5 };   // ✅ OK — no need to write 5u float f { 1.5 };        // ✅ OK — no need to write 1.5f`
```

These look like narrowing conversions, but:

- `5` is a literal of type `int`, but it fits into `unsigned int` safely.
    
- `1.5` is a `double`, but it's small and fits into `float`.
    

Since the value is a literal (a kind of implicit `constexpr`), **the compiler allows it**.

#### 🧪 No need for `static_cast`

```cpp
`constexpr int n{ 5 }; double d { n };   // ✅ OK — int to double is widening short s { 5 };    // ✅ OK — 5 fits in short, no cast needed`
```

No cast like `static_cast<short>(5)` is needed because the value is a constant that fits.

#### ⚠️ Special Caveat for Floating-Point Types

Floating-point types are **ranked**:

```cpp
`long double > double > float`
```

This means:

```cpp
`float f { 1.23456789 }; // ✅ OK (no compile error), even though some precision is lost`
```

- `1.23456789` is a `double` literal.
    
- `float` **can** store the value, but with **reduced precision**.
    
- Since the value fits within the **range** of `float`, the compiler accepts it.
    
- But: You **will** lose precision (i.e., it might store 1.2345678 instead).
    

#### 🛑 Why isn't this a narrowing conversion error?

Because:

- The initializer is a `constexpr` value (like a literal),
    
- The value fits **within the range** of the destination type,
    
- Even if **some precision is lost**, it's still allowed.
    

#### 🚨 But be aware:

Some compilers like GCC/Clang will warn you about this **if** you compile with:

---
### Arithmetic Conversions

```cpp
int x { 2 + 3 };
```

Binary `operator+` is given two operands, both of type `int`. Because both operands are of the same type, that type will be used to perform the calculation, and the value returned will also be of this same type. Thus, `2 + 3` will evaluate to `int` value `5`.

But what happens when the operands of a binary operator are of different types?

```cpp
??? y { 2 + 3.5 };
```

In this case, `operator+` is being given one operand of type `int` and another of type `double`. Should the result of the operator be returned as an `int`, a `double`, or possibly something else altogether?

In C++, certain operators require that their operands be of the same type. If one of these operators is invoked with operands of different types, one or both of the operands will be implicitly converted to matching types using a set of rules called the **usual arithmetic conversions**. The matching type produced as a result of the usual arithmetic conversion rules is called the **common type** of the operands.

---
### The operators that require operands of the same type

The following operators require their operands to be of the same type:

- The binary arithmetic operators: +, -, *, /, %
- The binary relational operators: <, >, <=, >=, ==, !=
- The binary bitwise arithmetic operators: &, ^, |
- The conditional operator ?: (excluding the condition, which is expected to be of type `bool`)

>[!For advanced readers]
Overloaded operators are not subject to the usual arithmetic conversion rules.

---
### The usual arithmetic conversion rules

>The usual arithmetic conversion rules are somewhat complex, so we’ll simplify a bit. The compiler has a ranked list of types that looks something like this:

- long double (highest rank)
- double
- float
- long long
- long
- int (lowest rank)

The following rules are applied to find a matching type:

>Step 1:

- If one operand is an integral type and the other a floating point type, the integral operand is converted to the type of the floating point operand (no integral promotion takes place).
- If both operands are **integral**, then smaller types like `char`, `short`, or `bool` are **promoted to `int`** (this is **integral promotion**) **before the operation.**

>Step 2:

- After promotion, if one operand is signed and the other unsigned, special rules apply (see below)
- Otherwise, the operand with lower rank is converted to the type of the operand with higher rank.

>[!For advanced readers]
The special matching rules for integral operands with different signs:
- If the rank of the unsigned operand is greater than or equal to the rank of the signed operand, the signed operand is converted to the type of the unsigned operand.
- If the type of the signed operand can represent all the values of the type of the unsigned operand, the type of the unsigned operand is converted to the type of the signed operand.
- Otherwise both operands are converted to the corresponding unsigned type of the signed operand.

---

>In the following examples, we’ll use the `typeid` operator (included in the `<typeinfo>` header), to show the resulting type of an expression.

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b

    return 0;
}
```

Because neither operand appears on the priority list, both operands undergo integral promotion to type `int`. The result of adding two `ints` is an `int`, as you would expect:

--> Output: int 9

---
### Signed and unsigned issues

This prioritization hierarchy and conversion rules can cause some problematic issues when mixing signed and unsigned values. For example, take a look at the following code:

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer

    return 0;
}
```

You might expect the expression `5u - 10` to evaluate to `-5` since `5 - 10` = `-5`. But here’s what actually results:

unsigned int 4294967291

Due to the conversion rules, the `int` operand is converted to an `unsigned int`. And since the value `-5` is out of range of an `unsigned int`, we get a result we don’t expect.

Here’s another example showing a counterintuitive result:

```cpp
#include <iostream>

int main()
{
    std::cout << std::boolalpha << (-3 < 5u) << '\n';

    return 0;
}
```

While it’s clear to us that `5` is greater than `-3`, when this expression evaluates, `-3` is converted to a large `unsigned int` that is larger than `5`. Thus, the above prints `false` rather than the expected result of `true`.

This is one of the primary reasons to avoid unsigned integers -- when you mix them with signed integers in arithmetic expressions, you’re at risk for unexpected results. And the compiler probably won’t even issue a warning.

---
### `std::common_type` and `std::common_type_t`

In future lessons, we’ll encounter cases where it is useful to know what the common type of two type is. `std::common_type` and the useful type alias `std::common_type_t` (both defined in the <type_traits> header) can be used for just this purpose.

For example, `std::common_type_t<int, double>` returns the common type of `int` and `double`, and `std::common_type_t<unsigned int, long>` returns the common type of `unsigned int` and `long`.

>[!Key Insight]
>std::common_type_t<int,double>; is a datatype like `int;` and it returns the common type:
>

---

```cpp
double d = 10 / 4; // does integer division, initializes d with value 2.0
```

Because `10` and `4` are both of type `int`, integer division is performed, and the expression evaluates to `int` value `2`. This value then undergoes numeric conversion to `double` value `2.0` before being used to initialize variable `d`. Most likely, this isn’t what was intended.

In the case where you are using literal operands, replacing one or both of the integer literals with double literals will cause floating point division to happen instead:

```cpp
double d = 10.0 / 4.0; // does floating point division, initializes d with value 2.5
```

But what if you are using variables instead of literals? Consider this case:

```cpp
int x { 10 };
int y { 4 };
double d = x / y; // does integer division, initializes d with value 2.0
```

Because integer division is used here, variable `d` will end up with the value of `2.0`. How do we tell the compiler that we want to use floating point division instead of integer division in this case? Literal suffixes can’t be used with variables. We need some way to convert one (or both) of the variable operands to a floating point type, so that floating point division will be used instead.

Fortunately, C++ comes with a number of different **type casting operators** (more commonly called **casts**) that can be used by the programmer to have the compiler perform type conversion. Because casts are explicit requests by the programmer, this form of type conversion is often called an **explicit type conversion** (as opposed to implicit type conversion, where the compiler performs a type conversion automatically).

---

>[!Key Insight]
>`static_cast` : Performs compile-time type conversions.

### Type casting

C++ supports 5 different types of casts: `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`, and C-style casts. The first four are sometimes referred to as **named casts**.

For advanced readers

| Cast             | Description                                                                                           | Safe?                 |
| ---------------- | ----------------------------------------------------------------------------------------------------- | --------------------- |
| static_cast      | Performs compile-time type conversions between related types.                                         | Yes                   |
| dynamic_cast     | Performs runtime type conversions on pointers or references in an polymorphic (inheritance) hierarchy | Yes                   |
| const_cast       | Adds or removes const.                                                                                | Only for adding const |
| reinterpret_cast | Reinterprets the bit-level representation of one type as if it were another type                      | No                    |
| C-style casts    | Performs some combination of `static_cast`, `const_cast`, or `reinterpret_cast`.                      | No                    |

Each cast works the same way. As input, the cast takes an expression (that evaluates to a value or an object), and a target type. As output, the cast returns the result of the conversion.

>[!Warning]
>Avoid `const_cast` and `reinterpret_cast` unless you have a very good reason to use them.

---
### C-style cast

In standard C programming, casting is done via `operator()`, with the name of the type to convert to placed inside the parentheses, and the value to convert to placed immediately to the right of the closing parenthesis. In C++, this type of cast is called a **C-style cast**. You may still see these used in code that has been converted from C.

For example:

```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    std::cout << (double)x / y << '\n'; // C-style cast of x to double

    return 0;
}
```

C++ also provides an alternative form of C-style cast known as a **function-style cast**, which resembles a function call:

```cpp
std::cout << double(x) / y << '\n'; //  // function-style cast of x to double
```

>[!Best Practice]
>Avoid using C-style casts.

>There is one thing you can do with a C-style cast that you can’t do with C++ casts: C-style casts can convert a derived object to a base class that is inaccessible (e.g. because it was privately inherited).

---
### `static_cast` should be used to cast most values

By far the most used cast in C++ is the **static cast** operator, which is accessed via the `static_cast` keyword. `static_cast` is used when we want to explicitly convert a value of one type into a value of another type.

You’ve previously seen `static_cast` used to convert a `char` into an `int` so that `std::cout` prints it as an integer instead of a character:

```cpp
#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << static_cast<int>(c) << '\n'; // prints 97 rather than a

    return 0;
}
```

To perform a static cast, we start with the `static_cast` keyword, and then place the type to convert to inside angled brackets. Then inside parenthesis, we place the expression whose value will be converted. Note how much the syntax looks like a function call to a function named `static_cast<type>()` with the expression whose value will be converted provided as an argument! Static casting a value to another type of value returns a temporary object that has been direct-initialized with the converted value.

Here’s how we’d use `static_cast` to solve the problem we introduced in the introduction of this lesson:

```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    // static cast x to a double so we get floating point division
    std::cout << static_cast<double>(x) / y << '\n'; // prints 2.5

    return 0;
}
```

`static_cast<double>(x)` returns a temporary `double` object containing the converted value `10.0`. This temporary is then used as the left-operand of the floating point division.

>There are two important properties of `static_cast`.

- First, `static_cast` provides compile-time type checking. If we try to convert a value to a type and the compiler doesn’t know how to perform that conversion, we will get a compilation error. [Confusion] : So my confusion was that if we have test() function who is returning a char and we do a static type casting so if static_cast performs casting at compile time but we dont know the value of test() function at compile time so how come it runs, so the answer is simple, static_cast performs compile time type checking only so it doesnt need to know the value of that type just the type and it can determine if the type conversion is possible!

	```cpp
	// a C-style string literal can't be converted to an int, so the following is an invalid conversion
int x { static_cast<int>("Hello") }; // invalid: will produce compilation error
```

>[!Best Practice]
>Favor `static_cast` when you need to convert a value from one type to another type.

---
### Using `static_cast` to make narrowing conversions explicit

Compilers will often issue warnings when a potentially unsafe (narrowing) implicit type conversion is performed. For example, consider the following snippet:

```cpp
int i { 48 };
char ch = i; // implicit narrowing conversion
```

Casting an `int` (2 or 4 bytes) to a `char` (1 byte) is potentially unsafe (as the compiler can’t tell whether the integer value will overflow the range of the `char` or not), and so the compiler will typically print a warning. If we used list initialization, the compiler would yield an error.

To get around this, we can use a static cast to explicitly convert our integer to a `char`:

```cpp
int i { 48 };

// explicit conversion from int to char, so that a char is assigned to variable ch
char ch { static_cast<char>(i) };
```

When we do this, we’re explicitly telling the compiler that this conversion is intended, and we accept responsibility for the consequences (e.g. overflowing the range of a `char` if that happens). Since the output of this static cast is of type `char`, the initialization of variable `ch` doesn’t generate any type mismatches, and hence no warnings or errors.

Here’s another example where the compiler will typically complain that converting a `double` to an `int` may result in loss of data:

```cpp
int i { 100 };
i = i / 2.5;
```

To tell the compiler that we explicitly mean to do this:

```cpp
int i { 100 };
i = static_cast<int>(i / 2.5);
```

---
### Casting vs initializing a temporary object

Let’s say we have some variable `x` that we need to convert to an `int`. There are two conventional ways we can do this:

1. `static_cast<int>(x)`, which returns a temporary `int` object _direct-initialized_ with `x`.
2. `int { x }`, which creates a temporary `int` object _direct-list-initialized_ with `x`.

We should avoid `int ( x )`, which is a C-style cast. This will return a temporary `int` direct-initialized with the value of `x` (like we’d expect from the syntax), but it also has the other downsides mentioned in the C-style cast section (like allowing the possibility of performing a dangerous conversion).

There are (at least) three notable differences between the `static_cast` and the direct-list-initialized temporary:

1. `int { x }` uses list initialization, which disallows narrowing conversions. This is great when initializing a variable, because we rarely intend to lose data in such cases. But when using a cast, it is presumed we know what we’re doing, and if we want to do a cast that might lose some data, we should be able to do that. The narrowing conversion restriction can be an impediment in this case.

Let’s show an example of this, including how it can lead to platform-specific issues:

```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    // We want to do floating point division, so one of the operands needs to be a floating point type
    std::cout << double{x} / y << '\n'; // okay if int is 32-bit, narrowing if x is 64-bit
}
```

In this example, we have decided to convert `x` to a `double` so we can do floating-point division rather than integer division. On a 32-bit architecture, this will work fine (because a `double` can represent all the values that can be stored in a 32-bit `int`, so it isn’t a narrowing conversion). But on a 64-bit architecture, this is not the case, so converting a 64-bit `int` to a `double` is a narrowing conversion. And since list initialization disallows narrowing conversions, this won’t compile on architectures where `int` is 64-bits.

2. `static_cast` makes it clearer that we are intending to perform a conversion. Although the `static_cast` is more verbose than the direct-list-initialized alternative, in this case, that’s a good thing, as it makes the conversion easier to spot and search for. That ultimately makes your code safer and easier to understand.
3. Direct-list-initializion of a temporary only allows single-word type names. Due to a weird syntax quirk, there are several places within C++ where only single-word type names are allowed (the C++ standard calls these names “simple type specifiers”). So while `int { x }` is a valid conversion syntax, `unsigned int { x }` is not.

You can see this for yourself in the following example, which produces a compile error:

```cpp
#include <iostream>

int main()
{
    unsigned char c { 'a' };
    std::cout << unsigned int { c } << '\n';

    return 0;
}
```

There are simple ways to work around this, the easiest of which is to use a single-word type alias:

```cpp
#include <iostream>

int main()
{
    unsigned char c { 'a' };
    using uint = unsigned int;
    std::cout << uint { c } << '\n';

    return 0;
}
```

But why go to the trouble when you can just `static_cast`?

For all these reasons, we generally prefer `static_cast` over direct-list-initialization of a temporary.

>[!Best practice]
Prefer `static_cast` over initializing a temporary object when a conversion is desired.

---
### Type aliases

>n C++, **using** is a keyword that creates an alias for an existing data type. To create such a type alias, we use the `using` keyword, followed by a name for the type alias, followed by an equals sign and an existing data type.

```cpp
#include <iostream>

int main()
{
    using Distance = double; // define Distance as an alias for type double

    Distance milesToDestination{ 3.4 }; // defines a variable of type double

    std::cout << milesToDestination << '\n'; // prints a double value

    return 0;
}
```

>[!Best Practice]
>Name your type aliases starting with a capital letter and do not use a suffix (unless you have a specific reason to do otherwise).

---

>An alias does not actually define a new, distinct type (one that is considered separate from other types) -- it just introduces a new identifier for an existing type. A type alias is completely interchangeable with the aliased type.

>[!Warning]
>Care must be taken not to mix values of aliases that are intended to be semantically distinct.

>[!Tip]
>type alias identifiers follow the same scoping rules as variable identifiers

---

>[!Best Practice]
>Prefer type aliases over typedefs.

### Using type aliases for platform independent coding

One of the primary uses for type aliases is to hide platform specific details. On some platforms, an `int` is 2 bytes, and on others, it is 4 bytes. Thus, using `int` to store more than 2 bytes of information can be potentially dangerous when writing platform independent code.

Because `char`, `short`, `int`, and `long` give no indication of their size, it is fairly common for cross-platform programs to use type aliases to define aliases that include the type’s size in bits. For example, `int8_t` would be an 8-bit signed integer, `int16_t` a 16-bit signed integer, and `int32_t` a 32-bit signed integer. Using type aliases in this manner helps prevent mistakes and makes it more clear about what kind of assumptions have been made about the size of the variable.

In order to make sure each aliased type resolves to a type of the right size, type aliases of this kind are typically used in conjunction with preprocessor directives:

```cpp
#ifdef INT_2_BYTES
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif
```

On machines where integers are only 2 bytes, `INT_2_BYTES` can be #defined (as a compiler/preprocessor setting), and the program will be compiled with the top set of type aliases. On machines where integers are 4 bytes, leaving `INT_2_BYTES` undefined will cause the bottom set of type aliases to be used. In this way, as long as `INT_2_BYTES` is #defined correctly, `int8_t` will resolve to a 1 byte integer, `int16_t` will resolve to a 2 bytes integer, and `int32_t` will resolve to a 4 byte integer (using the combination of `char`, `short`, `int`, and `long` that is appropriate for the machine the program is being compiled on).

The fixed-width integer types (such as `std::int16_t` and `std::uint32_t`) and the `size_t` type (both covered in lesson [4.6 -- Fixed-width integers and size_t](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/)) are actually just type aliases to various fundamental types.

This is also why when you print an 8-bit fixed-width integer using `std::cout`, you’re likely to get a character value. For example:

```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int8_t x{ 97 }; // int8_t is usually a typedef for signed char
    std::cout << x << '\n';

    return 0;
}
```

This program prints:

a

Because `std::int8_t` is typically a typedef for `signed char`, variable `x` will likely be defined as a `signed char`. And char types print their values as ASCII characters rather than as integer values.

---
### Using type aliases to make complex types easier to read

Although we have only dealt with simple data types so far, in advanced C++, types can be complicated and lengthy to manually enter on your keyboard. For example, you might see a function and variable defined like this:

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
{
    // some code here
    return false;
}

int main()
{
     std::vector<std::pair<std::string, int>> pairlist;

     return 0;
}
```

By Using Type alias we can do something like this:

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

using VectPairSI = std::vector<std::pair<std::string, int>>; // make VectPairSI an alias for this crazy type

bool hasDuplicates(VectPairSI pairlist) // use VectPairSI in a function parameter
{
    // some code here
    return false;
}

int main()
{
     VectPairSI pairlist; // instantiate a VectPairSI variable

     return 0;
}
```
This is probably best use case of type alias... 

---
### Using type aliases to document the meaning of a value

With variables, we have the variable’s identifier to help document the purpose of the variable. But consider the case of a function’s return value. Data types such as `char`, `int`, `long`, `double`, and `bool` describe what _type_ of value a function returns, but more often we want to know what the _meaning_ of a return value is.

```cpp
using TestScore = int;
TestScore gradeTest();
```

---
### Using type aliases for easier code maintenance

Type aliases also allow you to change the underlying type of an object without having to update lots of hardcoded types. For example, if you were using a `short` to hold a student’s ID number, but then later decided you needed a `long` instead, you’d have to comb through lots of code and replace `short` with `long`. It would probably be difficult to figure out which objects of type `short` were being used to hold ID numbers and which were being used for other purposes.

However, if you use type aliases, then changing types becomes as simple as updating the type alias (e.g. from `using StudentId = short;` to `using StudentId = long;`).

While this seems like a nice benefit, caution is necessary whenever a type is changed, as the behavior of the program may also change. This is especially true when changing the type of a type alias to a type in a different type family (e.g. an integer to a floating point value, or a signed to unsigned value)! The new type may have comparison or integer/floating point division issues, or other issues that the old type did not. If you change an existing type to some other type, your code should be thoroughly retested.

---
### Downsides and conclusion

While type aliases offer some benefits, they also introduce yet another identifier into your code that needs to be understood. If this isn’t offset by some benefit to readability or comprehension, then the type alias is doing more harm than good.

A poorly utilized type alias can take a familiar type (such as `std::string`) and hide it behind a custom name that needs to be looked up. In some cases (such as with smart pointers, which we’ll cover in a future chapter), obscuring the type information can also be harmful to understanding how the type should be expected to work.

For this reason, type aliases should be used primarily in cases where there is a clear benefit to code readability or code maintenance. This is as much of an art as a science. Type aliases are most useful when they can be used in many places throughout your code, rather than in fewer places.

Best practice

Use type aliases judiciously, when they provide a clear benefit to code readability or code maintenance.

---
