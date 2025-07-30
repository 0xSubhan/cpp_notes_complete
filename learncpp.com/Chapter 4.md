>surprisingly, in modern computer architectures, each bit does not get its own unique memory address. This is because the number of memory addresses is limited, and the need to access data bit-by-bit is rare. Instead, each memory address holds 1 byte of data. A **byte** is a group of bits that are operated on as a unit. The modern standard is that a byte is comprised of 8 sequential bits.

>In C++, we typically work with “byte-sized” chunks of data.

![[Pasted image 20250519184156.png]]
>The following picture shows some sequential memory addresses, along with the corresponding byte of data:

>Void is our first example of an incomplete type. An **incomplete type** is a type that has been declared but not yet defined. The compiler knows about the existence of such types, but does not have enough information to determine how much memory to allocate for objects of that type. `void` is intentionally incomplete since it represents the lack of a type, and thus cannot be defined.

>Up to this point, it has been useful to think of memory as a bunch of cubbyholes or mailboxes where we can put and retrieve information, and variables as names for accessing those cubbyholes or mailboxes.
However, this analogy is not quite correct in one regard -- most objects actually take up more than 1 byte of memory. A single object may use 1, 2, 4, 8, or even more consecutive memory addresses. The amount of memory that an object
uses is based on its data type.

>**the more bits you have, the more different values you can store**.
>2^n `n`, it will tell how many different combination of values can it store.

### **Why does this matter?**

- The **size of an object (in bytes)** decides how much data it can represent.
    
    - A 1-byte object has 256 possible values.
        
    - A 2-byte object can represent 65,536 different values.
        
- This becomes important especially when dealing with **integers** (whole numbers), because larger integers require more bytes.

### Bit Architecture
>When someone says **"We are on a 32-bit or 64-bit architecture,"** they are talking about the type of **CPU (Central Processing Unit)** and the **operating system** your computer uses. Here's what it means:

### ✅ **What is "bit architecture"?**

It refers to the **number of bits** the processor can handle **at once** or **in a single operation**.

---

### 🧠 **32-bit architecture**

- The CPU processes **32 bits of data at a time**.
    
- It can use **up to 4 GB of RAM** (2³² = ~4.29 billion memory addresses).
    
- Common in older systems.
    
- Uses 32-bit instructions and 32-bit registers.
    

---

### ⚡ **64-bit architecture**

- The CPU processes **64 bits of data at a time**.
    
- It can theoretically use **16 exabytes of RAM** (2⁶⁴ = a _huge_ number).
    
    - In practice, modern systems support hundreds of GBs or TBs of RAM.
        
- Faster and more powerful.
    
- Used in modern PCs, laptops, and phones.

>You might assume that types that use less memory would be faster than types that use more memory. This is not always true. CPUs are often optimized to process data of a certain size (e.g. 32 bits), and types that match that size may be processed quicker. On such a machine, a 32-bit int could be faster than a 16-bit short or an 8-bit char.

### Signed integers
>An **integer** is an integral type that can represent positive and negative whole numbers, including 0 (e.g. -2, -1, 0, 1, 2). C++ has _4_ primary fundamental integer types available for use:

|Type|Minimum Size|Note|
|---|---|---|
|short int|16 bits||
|int|16 bits|Typically 32 bits on modern architectures|
|long int|32 bits||
|long long int|64 bits||
>The key difference between the various integer types is that they have varying sizes -- the larger integers can hold bigger numbers.

>C++ only guarantees that integers will have a certain minimum size, not that they will have a specific size

>Technically, the `bool` and `char` types are considered to be integral types (because these types store their values as integer values).

>This attribute of being positive, negative, or zero is called the number’s **sign**.

> Integers in c++ are by default signed.
> which means the number’s sign is stored as part of the value. Therefore, a signed integer can hold both positive and negative numbers (and 0).

>a variable with _n_ bits can hold 2n possible values

#### What Specific Values?
>We call the set of specific values that a data type can hold its **range**.
>The range of an integer variable is determined by two factors: its size (in bits), and whether it is signed or not.

>For example, an 8-bit signed integer has a range of -128 to 127. This means an 8-bit signed integer can store any integer value between -128 and 127 (inclusive) safely.

### 🧠 How many values can 8 bits represent?

- 8 bits can represent 2^8=256 different values.
    

---

### ➕➖ Signed Representation

In signed integers (usually using **two's complement** representation):

- Half of the values are used for **negative numbers** (including zero).
    
- The other half are for **positive numbers**.
    

So:

- **Negative range**: -128 to -1 → 128 values
    
- **Zero**: 1 value
    
- **Positive range**: 1 to 127 → 127 values
    

Total = 128 (negative) + 1 (zero) + 127 (positive) = **256 values**

---

### ✅ Final Range

So an **8-bit signed integer** can safely store **any integer from -128 to 127**, **inclusive**.

We use **two’s complement** because it:

- Makes arithmetic easy and efficient
    
- Eliminates the need for separate subtraction circuits
    
- Avoids having two zeros
    
- Uses the full range of values available in n bits
    

It’s the **standard** way to represent signed integers in almost all modern computer systems.

Here’s a table containing the range of signed integers of different sizes:

|Size / Type|Range|
|---|---|
|8-bit signed|-128 to 127|
|16-bit signed|-32,768 to 32,767|
|32-bit signed|-2,147,483,648 to 2,147,483,647|
|64-bit signed|-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807|

### OverFlow
[Read](https://www.learncpp.com/cpp-tutorial/signed-integers/#:~:text=Overflow,a%20bigger%20range!)

### Division OverFlow
[Read](https://www.learncpp.com/cpp-tutorial/signed-integers/#:~:text=Integer%20division,results%20are%20predictable.)

### Unsigned Integer
>**Unsigned integers** are integers that can only hold non-negative whole numbers.

>unsigned integer should generally be avoided unless you’re doing bit-level manipulation.

To define an unsigned integer, we use the _unsigned_ keyword. By convention, this is placed before the type:
```cpp
unsigned short us;
```
### Unsigned integer range
>A 1-byte unsigned integer has a range of 0 to 255. Compare this to the 1-byte signed integer range of -128 to 127. Both can store 256 different values, but signed integers use half of their range for negative numbers, whereas unsigned integers can store positive numbers that are twice as large.

| Size/Type       | Range                           |
| --------------- | ------------------------------- |
| 8 bit unsigned  | 0 to 255                        |
| 16 bit unsigned | 0 to 65,535                     |
| 32 bit unsigned | 0 to 4,294,967,295              |
| 64 bit unsigned | 0 to 18,446,744,073,709,551,615 |
|                 |                                 |

>What happens if we try to store the number `280` (which requires 9 bits to represent) in a 1-byte (8-bit) unsigned integer? The answer is overflow.

>If an unsigned value is out of range, it is divided by one greater than the largest number of the type, and only the remainder kept.

>The number `280` is too big to fit in our 1-byte range of 0 to 255. 1 greater than the largest number of the type is 256. Therefore, we divide 280 by 256, getting 1 remainder 24. The remainder of 24 is what is stored.

>Here’s another way to think about the same thing. Any number bigger than the largest number representable by the type simply “wraps around” (sometimes called “modulo wrapping”). `255` is in range of a 1-byte integer, so `255` is fine. `256`, however, is outside the range, so it wraps around to the value `0`. `257` wraps around to the value `1`. `280` wraps around to the value `24`.

```cpp
#include <iostream>

int main()
{
    unsigned short x{ 65535 }; // largest 16-bit unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = 65536; // 65536 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = 65537; // 65537 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    return 0;
}
```
x was: 65535
x is now: 0
x is now: 1

>It’s possible to wrap around the other direction as well. 0 is representable in a 2-byte unsigned integer, so that’s fine. -1 is not representable, so it wraps around to the top of the range, producing the value 65535. -2 wraps around to 65534. And so forth.

```cpp
#include <iostream>

int main()
{
    unsigned short x{ 0 }; // smallest 2-byte unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = -1; // -1 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = -2; // -2 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    return 0;
}
```
x was: 0
x is now: 65535
x is now: 65534

>Many notable bugs in video game history happened due to wrap around behavior with unsigned integers. In the arcade game Donkey Kong, it’s not possible to go past level 22 due to an overflow bug that leaves the user with not enough bonus time to complete the level.
In the PC game Civilization, Gandhi was known for often being the first one to use nuclear weapons, which seems contrary to his expected passive nature. Players had a theory that Gandhi’s aggression setting was initially set at 1, but if he chose a democratic government, he’d get a -2 aggression modifier (lowering his current aggression value by 2). This would cause his aggression to overflow to 255, making him maximally aggressive! However, more recently Sid Meier (the game’s author) clarified that this wasn’t actually the case.

### The controversy over unsigned numbers
[Read](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/#:~:text=The%20controversy%20over,the%20libtorrent%20blog)

### So when should you use unsigned numbers?
There are still a few cases in C++ where it’s okay / necessary to use unsigned numbers.

First, unsigned numbers are preferred when dealing with bit manipulation (covered in chapter O -- that’s a capital ‘o’, not a ‘0’). They are also useful when well-defined wrap-around behavior is required (useful in some algorithms like encryption and random number generation).

Second, use of unsigned numbers is still unavoidable in some cases, mainly those having to do with array indexing. We’ll talk more about this in the lessons on arrays and array indexing.

Also note that if you’re developing for an embedded system (e.g. an Arduino) or some other processor/memory limited context, use of unsigned numbers is more common and accepted (and in some cases, unavoidable) for performance reasons.

>we know that integer variables have a minimum size but they can be larger depending on the target system.

For example, an `int` has a minimum size of 16-bits, but it’s typically 32-bits on modern architectures.

```cpp
#include <iostream>

int main()
{
    int x { 32767 };        // x may be 16-bits or 32-bits
    x = x + 1;              // 32768 overflows if int is 16-bits, okay if int is 32-bits
    std::cout << x << '\n'; // what will this print?

    return 0;
}
```
[Logic](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=On%20a%20machine,overall%20memory%20usage.)

### Key insight

In most cases, we only instantiate a small number of `int` variables at a time, and these are typically destroyed at the end of the function in which they are created. In such cases, wasting 2 bytes of memory per variable isn’t a concern (the limited range is a bigger issue). However, in cases where our program allocates millions of `int` variables, wasting 2 bytes of memory per variable can have a significant impact on the program’s overall memory usage.

### Why isn’t the size of the integer types fixed?
[Read](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=The%20short%20answer,to%20be%20portable).)

### Fixed-width integers
>To address the above issues, C++11 provides an alternate set of integer types that are guaranteed to be the same size on any architecture. Because the size of these integers is fixed, they are called **fixed-width integers**.

The fixed-width integers are defined (in the < cstdint >\ header) as follows:
[Table](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=Name,0%20to%2018%2C446%2C744%2C073%2C709%2C551%2C615)

```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int32_t x { 32767 }; // x is always a 32-bit integer
    x = x + 1;                // so 32768 will always fit
    std::cout << x << '\n';

    return 0;
}
```

### Warning: `std::int8_t` and `std::uint8_t` typically behave like chars
>Due to an oversight in the C++ specification, modern compilers typically treat `std::int8_t` and `std::uint8_t` (and the corresponding fast and least fixed-width types, which we’ll introduce in a moment) the same as `signed char` and `unsigned char` respectively. Thus on most modern systems, the 8-bit fixed-width integral types will behave like char types.

### 🧠 What about `std::int8_t`?

This is where it gets a little more subtle.

#### Normally:

- The only 8-bit signed integral type available in most C++ systems is `signed char`.
    
- So, `std::int8_t` is typically just an alias for `signed char`.
    

But here's the catch:

#### Why not just `char` or `bool`?

- `char` can be signed or unsigned depending on the compiler settings.
    
- `bool` is not considered an integral type suitable for arithmetic.
    
- So `signed char` is the only safe 8-bit signed integral type.
### Other fixed-width downsides
[Read](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=The%20fixed%2Dwidth%20integers%20have,are%20just%20minor%20quibbles%20though.)

### Fast and least integral types
>The fast types (std::int_fast#_t and std::uint_fast#_t) provide the fastest signed/unsigned integer type with a width of at least # bits (where # = 8, 16, 32, or 64). For example, `std::int_fast32_t` will give you the fastest signed integer type that’s at least 32-bits. By fastest, we mean the integral type that can be processed most quickly by the CPU.

>The least types (std::int_least#_t and std::uint_least#_t) provide the smallest signed/unsigned integer type with a width of at least # bits (where # = 8, 16, 32, or 64). For example, `std::uint_least32_t` will give you the smallest unsigned integer type that’s at least 32-bits.

```cpp
#include <cstdint> // for fast and least types
#include <iostream>

int main()
{
	std::cout << "least 8:  " << sizeof(std::int_least8_t)  * 8 << " bits\n";
	std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
	std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
	std::cout << '\n';
	std::cout << "fast 8:  "  << sizeof(std::int_fast8_t)   * 8 << " bits\n";
	std::cout << "fast 16: "  << sizeof(std::int_fast16_t)  * 8 << " bits\n";
	std::cout << "fast 32: "  << sizeof(std::int_fast32_t)  * 8 << " bits\n";

		return 0;
}
```
#### Why is `fast` 64 bits?

Because on many 64-bit CPUs:

- 64-bit types can be accessed faster due to the CPU's word size.
    
- So the compiler picks `int_fast8_t` = `int64_t`, even if that's overkill in size.

- Operations on `int8_t` or `int16_t` might be **slower**, because:
    
    - The CPU may have to convert them to 32/64 bits anyway during arithmetic.
        
    - It may require extra steps to ensure correct overflow/underflow behavior.
        

So the compiler says:

> "Even though you only need 8 bits, I’ll give you a 64-bit type, because that’s **faster** on this machine."

>You can see that `std::int_least16_t` is 16-bits, whereas `std::int_fast16_t` is actually 32-bits. This is because on the author’s machine, 32-bit integers are faster to process than 16-bit integers.

### ⚙️ Imagine a system with only:

- **16-bit** integers (small)
    
- **64-bit** integers (large)
    

And **no** 32-bit type available at all.

---

### 🧱 What happens with `std::int32_t`?

`std::int32_t` is a **fixed-width type** that must be:

> Exactly **32 bits**

If the system **doesn't have any type that is exactly 32 bits**, then:

> ❌ `std::int32_t` **does not exist** on that system.

So you can't use it, because there's no way to satisfy that exact size requirement.

---

### ✅ But what about `std::int_least32_t`?

This type means:

> "Give me the **smallest** available signed integer type that is **at least** 32 bits."

In our example, we have:

- 16-bit type ❌ (too small)
    
- 64-bit type ✅ (big enough)
    

So:

cpp

CopyEdit

`std::int_least32_t === 64-bit type`

Even though it's more than 32 bits, it's the **least** type available that's ≥32.

---

### ✅ What about `std::int_fast32_t`?

This means:

> "Give me the **fastest** integer type that is **at least** 32 bits."

In our system:

- Only the 64-bit type qualifies.
    
- And it's the fastest too (because there’s no 32-bit type).
    

So:

cpp

CopyEdit

`std::int_fast32_t === 64-bit type`

---

### 📌 Summary

| Type                 | Requirement                     | Result in this case |
| -------------------- | ------------------------------- | ------------------- |
| `std::int32_t`       | Exactly 32 bits                 | ❌ Not available     |
| `std::int_least32_t` | At least 32 bits, smallest type | ✅ 64-bit type       |
| `std::int_fast32_t`  | At least 32 bits, fastest type  | ✅ 64-bit type       |

### [Why We Should Avoid Using Fasy and leasy?](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=be%2064%20bits.-,However%2C%20these%20fast%20and%20least%20integers%20have%20their%20own%20downsides.%20First,exhibit%20different%20behaviors%20on%20architectures%20where%20they%20resolve%20to%20different%20sizes.,-Best%20practices%20for)

### Best practice for integral types
[Read](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/#:~:text=Given%20the%20various,__int8%2C%20__int16%2C%20etc%E2%80%A6)

>`std::size_t` is an alias for an implementation-defined unsigned integral type. It is used within the standard library to represent the byte-size or length of objects.


### Scientific Notaion
**Scientific notation** is a useful shorthand for writing lengthy numbers in a concise manner. And although scientific notation may seem foreign at first, understanding scientific notation will help you understand how floating point numbers work, and more importantly, what their limitations are.

Numbers in scientific notation take the following form: _significand_ x 10_exponent_. For example, in the scientific notation `1.2 x 10⁴`, `1.2` is the significand and `4` is the exponent. Since 10⁴ evaluates to 10,000, 1.2 x 10⁴ evaluates to 12,000.

By convention, numbers in scientific notation are written with one digit before the decimal point, and the rest of the digits afterward.

Consider the mass of the Earth. In decimal notation, we’d write this as `5972200000000000000000000 kg`. That’s a really large number (too big to fit even in an 8 byte integer). It’s also hard to read (is that 19 or 20 zeros?). Even with separators (5,972,200,000,000,000,000,000,000) the number is still hard to read.

>Remember, keep trailing zeros after a decimal point, drop trailing zeros if there is no decimal point.

#### [Quiz Questions for scientific notation](https://www.learncpp.com/cpp-tutorial/introduction-to-scientific-notation/#:~:text=floating%20point%20numbers.-,Quiz%20time,Show%20Solution,-Next%20lesson)

### Floating Point Numbers
C++ has three fundamental floating point data types: a single-precision `float`, a double-precision `double`, and an extended-precision `long double`. As with integers, C++ does not define the actual size of these types.

|Category|C++ Type|Typical Size|
|---|---|---|
|floating point|float|4 bytes|
||double|8 bytes|
||long double|8, 12, or 16 bytes|

>`float` is almost always 4 bytes, and `double` is almost always 8 bytes.

>Avoid using long double becuase it can vary between 8,12 or 16 bytes and doesnt follow IEEE 754 Compliment format.

>The **IEEE 754** format is the **standard for representing floating-point numbers** in computers, widely used across hardware and programming languages. It defines how real numbers (including fractions and very large/small numbers) are stored and processed.

```cpp
int a { 5 };      // 5 means integer
double b { 5.0 }; // 5.0 is a floating point literal (no suffix means double type by default)
float c { 5.0f }; // 5.0 is a floating point literal, f suffix means float type

int d { 0 };      // 0 is an integer
double e { 0.0 }; // 0.0 is a double
```

>Note that by default, floating point literals default to type double. An `f` suffix is used to denote a literal of type float.

### Floating point precision
>Consider the fraction 1/3. The decimal representation of this number is 0.33333333333333… with 3’s going out to infinity. If you were writing this number on a piece of paper, your arm would get tired at some point, and you’d eventually stop writing. And the number you were left with would be close to 0.3333333333…. (with 3’s going out to infinity) but not exactly.

>On a computer, an infinite precision number would require infinite memory to store, and we typically only have 4 or 8 bytes per value. This limited memory means floating point numbers can only store a certain number of significant digits -- any additional significant digits are either lost or represented imprecisely. The number that is actually stored may be close to the desired number, but not exact. We’ll show an example of this in the next section.

#### [More On Precision](https://www.learncpp.com/cpp-tutorial/floating-point-numbers/#:~:text=The%20precision%20of,being%20stored%20inexactly.)

```cpp
#include <iomanip> // for std::setprecision()
#include <iostream>

int main()
{
    float f { 123456789.0f }; // f has 10 significant digits
    std::cout << std::setprecision(9); // to show 9 digits in f
    std::cout << f << '\n';

    return 0;
}
```
outpuT:123456792

>123456792 is greater than 123456789. The value 123456789.0 has 10 significant digits, but float values typically have 7 digits of precision (and the result of 123456792 is precise only to 7 significant digits). We lost some precision! When precision is lost because a number can’t be stored precisely, this is called a **rounding error**.

>Favor double over float unless space is at a premium, as the lack of precision in a float will often lead to inaccuracies.

### [Rounding errors make floating point comparisons tricky](https://www.learncpp.com/cpp-tutorial/floating-point-numbers/#:~:text=Rounding%20errors%20make,or%20currency%20data.)

### NaN and Inf
>- **Inf**, which represents infinity. Inf is signed, and can be positive (+Inf) or negative (-Inf).

>- **NaN**, which stands for “Not a Number”. There are several different kinds of NaN (which we won’t discuss here).

>- Signed zero, meaning there are separate representations for “positive zero” (+0.0) and “negative zero” (-0.0).

```cpp
#include <iostream>

int main()
{
    double zero { 0.0 };

    double posinf { 5.0 / zero }; // positive infinity
    std::cout << posinf << '\n';

    double neginf { -5.0 / zero }; // negative infinity
    std::cout << neginf << '\n';

    double z1 { 0.0 / posinf }; // positive zero
    std::cout << z1 << '\n';

    double z2 { -0.0 / posinf }; // negative zero
    std::cout << z2 << '\n';

    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << nan << '\n';

    return 0;
}
```

And the results using Clang:

inf
-inf
0
-0
nan

>Avoid division by `0.0`, even if your compiler supports it.

### Conclusion

To summarize, the two things you should remember about floating point numbers:

1. Floating point numbers are useful for storing very large or very small numbers, including those with fractional components.
2. Floating point numbers often have small rounding errors, even when the number has fewer significant digits than the precision. Many times these go unnoticed because they are so small, and because the numbers are truncated for output. However, comparisons of floating point numbers may not give the expected results. Performing mathematical operations on these values will cause the rounding errors to grow larger.

### Boolean Values
>Boolean values are not actually stored in Boolean variables as the words “true” or “false”. Instead, they are stored as integral values: `true` is stored as integer `1`, and `false` is stored as integer `0`. Similarly, when Boolean values are evaluated, they don’t actually evaluate to “true” or “false”. They evaluate to the integers `0` (false) or `1` (true). Because Booleans store integral values, they are considered to be an integral type.

### std::boolalpha and std::noboolalpha
>If you want `std::cout` to print `true` or `false` instead of `0` or `1`, you can output `std::boolalpha`. This doesn’t output anything, but manipulates the way `std::cout` outputs `bool` values.

```cpp
#include <iostream>

int main()
{
    std::cout << true << '\n';
    std::cout << false << '\n';

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << true << '\n';
    std::cout << false << '\n';
    return 0;
}
```

>You can use `std::noboolalpha` to turn it back off.

>Enabling `std::boolalpha` for input will only allow lower-cased `false` or `true` to be accepted. Variations with capital letters will not be accepted. `0` and `1` will also no longer be accepted.

#### Taking false and true value using cin
>Note that we use `std::cin >> std::boolalpha;` to input bool values as `true` or `false`, and `std::cout << std::boolalpha;` to output bool values as `true` or `false`. These are independent controls that can be turned on (using `std::boolalpha`) or off (using `std::noboolalpha`) separately.

```cpp
#include <iostream>

int main()
{
	bool b{};
	std::cout << "Enter a boolean value: ";

	// Allow the user to input 'true' or 'false' for boolean values
	// This is case-sensitive, so True or TRUE will not work
	std::cin >> std::boolalpha;
	std::cin >> b;

	// Let's also output bool values as `true` or `false`
	std::cout << std::boolalpha;
	std::cout << "You entered: " << b << '\n';

	return 0;
}
```

### Boolean return values

>Boolean values are often used as the return values for functions that check whether something is true or not. Such functions are typically named starting with the word _is_ (e.g. isEqual) or _has_ (e.g. hasCommonDivisor).

Consider the following example, which is quite similar to the above:
```cpp
#include <iostream>

// returns true if x and y are equal, false otherwise
bool isEqual(int x, int y)
{
    return x == y; // operator== returns true if x equals y, and false otherwise
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << x << " and " << y << " are equal? ";
    std::cout << isEqual(x, y) << '\n'; // will return true or false

    return 0;
}
```

### IF statement

```cpp
#include <iostream>

int main()
{
    int x { 4 };
    if (x) // nonsensical, but for the sake of example...
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}
```
>In such a case, the result of the conditional expression is converted to a Boolean value: non-zero values get converted to Boolean `true`, and zero-values get converted to Boolean `false`

>`if (x)` means “if x is non-zero/non-empty”.

### If-statements and early returns 
>A return-statement that is not the last statement in a function is called an **early return**. Such a statement will cause the function to return to the caller when the return statement is executed (before the function would otherwise return to the caller, hence, “early”).

```cpp
#include <iostream>

// returns the absolute value of x
int abs(int x)
{
    if (x < 0)
        return -x; // early return (only when x < 0)

    return x;
}

int main()
{
    std::cout << abs(4) << '\n'; // prints 4
    std::cout << abs(-3) << '\n'; // prints 3

    return 0;
}
```

>Historically, early returns were frowned upon. However, in modern programming they are more accepted, particularly when they can be used to make a function simpler, or are used to abort a function early due to some error condition.

### Chars
>The **char** data type was designed to hold a single `character`. A **character** can be a single letter, number, symbol, or whitespace.

>The char data type is an integral type, meaning the underlying value is stored as an integer. Similar to how a Boolean value `0` is interpreted as `false` and non-zero is interpreted as `true`, the integer stored by a `char` variable are intepreted as an `ASCII character`.

[About unprintable chars and printable chars](https://www.learncpp.com/cpp-tutorial/chars/#:~:text=Codes%200%2D31,upon%20your%20OS.)

>Be careful not to mix up character numbers with integer numbers. The following two initializations are not the same:

```cpp
char ch{5}; // initialize with integer 5 (stored as integer 5)
char ch{'5'}; // initialize with code point for '5' (stored as integer 53)
```

### Char and buffer behavious
```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "abcd" (without quotes)

    char ch{};
    std::cin >> ch; // ch = 'a', "bcd" is left queued.
    std::cout << "You entered: " << ch << '\n';

    // Note: The following cin doesn't ask the user for input, it grabs queued input!
    std::cin >> ch; // ch = 'b', "cd" is left queued.
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```
>Note that std::cin will let you enter multiple characters. However, variable _ch_ can only hold 1 character. Consequently, only the first input character is extracted into variable _ch_. The rest of the user input is left in the input buffer that std::cin uses, and can be extracted with subsequent calls to std::cin.

### Extracting whitespace characters
>Because extracting input ignores leading whitespace, this can lead to unexpected results when trying to extract whitespace characters to a char variable:

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```
>In the above example, we may have expected to extract the space, but because leading whitespace is skipped, we extracted the `b` character instead.

#### Simple Solution
>One simple way to address this is to use the `std::cin.get()` function to perform the extraction instead, as this function does not ignore leading whitespace:

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin.get(ch); // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin.get(ch); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

### Char size, range, and default sign
>Char is defined by C++ to always be 1 byte in size. By default, a char may be signed or unsigned (though it’s usually signed). If you’re using chars to hold ASCII characters, you don’t need to specify a sign (since both signed and unsigned chars can hold values between 0 and 127). Since ASCII table also have code from 0 to 127 so we dont need to specify sign.

### [Escape Sequence](https://www.learncpp.com/cpp-tutorial/chars/#:~:text=Escape%20sequences,the%20desired%20result.)

### [Multicharacter literals and why should avoid them](https://www.learncpp.com/cpp-tutorial/chars/#:~:text=Avoid%20multicharacter%20literals,avoids%20them%20entirely.)

### Unicode Usage in C++
>ASCII maps integers 0-127 to english characters and symbols but its limited to 128 so it only supports basic english.

### 💡 What is Unicode?

- A **universal encoding system** that maps over **144,000 characters** (as of 2025) to unique numbers called **code points**.
    
- Supports **almost every language**, math symbols, emojis, etc.

## 🔢 3. **Unicode Encodings: UTF-8, UTF-16, UTF-32**

Unicode can be stored in **different formats**, depending on how much memory you want to use:

|Encoding|Bits per character|Description|
|---|---|---|
|UTF-8|8 bits (1 byte) to 4 bytes|Variable-length (uses 1 to 4 bytes). Saves memory for texts mostly in English.|
|UTF-16|16 bits (2 bytes) or 4 bytes|Variable-length (1 or 2 code units). Good middle ground.|
|UTF-32|Always 32 bits (4 bytes)|Fixed length. Easy but uses more memory.|

## 🧱 4. **New C++ Character Types (for Unicode)**

To support Unicode in C++, the language introduced new character types:

|Type|From|Represents|Equivalent size/type|
|---|---|---|---|
|`char8_t`|C++20|UTF-8 code unit (1 byte)|Same size as `unsigned char`|
|`char16_t`|C++11|UTF-16 code unit (2 bytes)|Same as `std::uint_least16_t`|
|`char32_t`|C++11|UTF-32 code unit (4 bytes)|Same as `std::uint_least32_t`|

> 🔸 _Note:_ These types are **distinct**, meaning you cannot mix them freely with `char`, `int`, etc., without casting.

### Implicit Type conversion
```cpp
#include <iostream>

void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5); // what happens when we pass an int value?

	return 0;
}
```
>In most cases, C++ will allow us to convert values of one fundamental type to another fundamental type. The process of converting data from one type to another type is called **type conversion**. Thus, the int argument `5` will be converted to double value `5.0` and then copied into parameter `x`. The `print()` function will print this value, resulting in the following output:

>When the compiler does type conversion on our behalf without us explicitly asking, we call this **implicit type conversion**. The above example illustrates this -- nowhere do we explicitly tell the compiler to convert integer value `5` to double value `5.0`. Rather, the function is expecting a double value, and we pass in an integer argument. The compiler will notice the mismatch and implicitly convert the integer to a double.

### Type conversion of a value produces a new value

```cpp
#include <iostream>

void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	int y { 5 };
	print(y); // y is of type int

	return 0;
}
```
>In the above example, the conversion does not change variable `y` from type `int` to `double` or the value of `y` from `5` to `5.0`. Instead, the conversion uses the value of `y` (`5`) as input, and returns a temporary object of type `double` with value `5.0`. This temporary object is then passed to function `print`.

### Treat Warning as error for vs code studio
>in tasks.json file, paste this:

```
"-Wall",
"-Weffc++",
"-Wextra",
"-Wconversion",
"-Wsign-conversion",
```

[Implicit type conversion warnings](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/#:~:text=Although%20implicit%20type,type%20conversion.)

>Some type conversions (such as a `char` to an `int`) always preserve the value being converted, whereas others (such as `double` to `int`) may result in the value being changed during conversion. Unsafe implicit conversions will typically either generate a compiler warning, or (in the case of brace initialization) an error.
This is one of the primary reasons brace initialization is the preferred initialization form. Brace initialization will ensure we don’t try to initialize a variable with an initializer that will lose value when it is implicitly type converted:

```cpp
int main()
{
    double d { 5 }; // okay: int to double is safe
    int x { 5.5 }; // error: double to int not safe

    return 0;
}
```

### An introduction to explicit type conversion via the static_cast operator

>To perform an explicit type conversion, in most cases we’ll use the `static_cast` operator. The syntax for the `static cast` looks a little funny:

```cpp
static_cast<new_type>(expression)
```
>static_cast takes the value from an expression as input, and returns that value converted into the type specified by _new_type_ (e.g. int, bool, char, double).

>Whenever you see C++ syntax (excluding the preprocessor) that makes use of angled brackets (<>), the thing between the angled brackets will most likely be a type. This is typically how C++ deals with code that need a parameterized type.

Let’s update our prior program using `static_cast`:

```cpp
#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	print( static_cast<int>(5.5) ); // explicitly convert double value 5.5 to an int

	return 0;
}
```

> We can do the same for converting char to int.

```cpp
#include <iostream>

int main()
{
    char ch{ 97 }; // 97 is ASCII code for 'a'
    // print value of variable ch as an int
    std::cout << ch << " has value " << static_cast<int>(ch) << '\n';

    return 0;
}
```

### [Sign conversions using static_cast](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/#:~:text=Signed%20integral%20values,the%20signed%20type.)

### std::int8_t and std::uint8_t likely behave like chars instead of integers

>As noted in lesson [4.6 -- Fixed-width integers and size_t](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/), most compilers define and treat `std::int8_t` and `std::uint8_t` (and the corresponding fast and least fixed-width types) identically to types `signed char` and `unsigned char` respectively. Now that we’ve covered what chars are, we can demonstrate where this can be problematic:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int8_t myInt{65};      // initialize myInt with value 65
    std::cout << myInt << '\n'; // you're probably expecting this to print 65

    return 0;
}
```
>Because `std::int8_t` describes itself as an int, you might be tricked into believing that the above program will print the integral value `65`. However, on most systems, this program will print `A` instead (treating `myInt` as a `signed char`). However, this is not guaranteed (on some systems, it may actually print `65`).

>If you want to ensure that a `std::int8_t` or `std::uint8_t` object is treated as an integer, you can convert the value to an integer using `static_cast`:

In cases where `std::int8_t` is treated as a char, input from the console can also cause problems:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::cout << "Enter a number between 0 and 127: ";
    std::int8_t myInt{};
    std::cin >> myInt;

    std::cout << "You entered: " << static_cast<int>(myInt) << '\n';

    return 0;
}
```

>Here’s what’s happening. When `std::int8_t` is treated as a char, the input routines interpret our input as a sequence of characters, not as an integer. So when we enter `35`, we’re actually entering two chars, `'3'` and `'5'`. Because a char object can only hold one character, the `'3'` is extracted (the `'5'` is left in the input stream for possible extraction later). Because the char `'3'` has ASCII code point 51, the value `51` is stored in `myInt`, which we then print later as an int.

