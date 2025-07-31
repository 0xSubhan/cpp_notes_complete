
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
