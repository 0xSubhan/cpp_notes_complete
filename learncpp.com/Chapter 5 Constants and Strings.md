> **Constant** is a value that cannot be changed during program execution means runtime.

> Const variable can be initialized by taking another variable value even if its non-const variable.

> Function parameters can also be constant so it ensures that argument value doesnt change inside the function, but **it is not prefered to use const in function parameters because** its doesnt matter if its value changes since its a copy and will be destroyed at the end of function.

>Don’t use `const` when returning by value.

### Why use const?

- reduce bugs, because value cannot be changed accidentally.
- make programs optimize.
- reduces overall complexity of our program and easy to debug.

>Object like macros with substitution text are also named constants.

```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';

    return 0;
}
```
In which MY_NAME is name(identifyer) and Alex is constant value.

### Prefer constant variables to preprocessor macros

- macros dont follow c++ scoping rules because its not the part of compilation but it is processed by preprocessor. And if we use name of macro identifyer in any where in program where it shouldnt be then it will be replaced by its macro value because it doesnt follow c++ scope ruling.
- It is harder to debug code using macros because debugger and compiler never see the macro value because it has already been replaced before they run.
- macro subsititution behaves differently than everything in c++.
```cpp
#include <iostream>

void someFcn()
{
// Even though gravity is defined inside this function
// the preprocessor will replace all subsequent occurrences of gravity in the rest of the file
#define gravity 9.8
}

void printGravity(double gravity) // including this one, causing a compilation error
{
    std::cout << "gravity: " << gravity << '\n';
}

int main()
{
    printGravity(3.71);

    return 0;
}
```
>Prefer constant variables over object-like macros with substitution text.

>A **type qualifier** (sometimes called a **qualifier** for short) is a keyword that is applied to a type that modifies how that type behaves. The `const` used to declare a constant variable is called a **const type qualifier** (or **const qualifier** for short).

>As of C++23, C++ only has two type qualifiers: `const` and `volatile`.



>literals are value which are inserted directly into the code and these are sometimes called **literal constants** because their meaning cannot be redefined.

>If the default type of a literal is not as desired, you can change the type of a literal by adding a suffix.

[Table](https://www.learncpp.com/cpp-tutorial/literals/#:~:text=more%20common%20suffixes%3A-,Data%20type,std%3A%3Astring_view,-We%E2%80%99ll%20discuss%20the)
> In most cases we only need suffix f for float.

>**Integral literals** eg: 5 for default int, 5L for long and 5u for unsigned int.
>the compiler will convert the int literal to the appropriate type.

```cpp 
int main()
{
    int a { 5 };          // ok: types match
    unsigned int b { 6 }; // ok: compiler will convert int value 6 to unsigned int value 6
    long c { 7 };         // ok: compiler will convert int value 7 to long value 7

    return 0;
}
```

> by default floating point literal has type of double so to make it float we have to add f or F suffix at the end.
> eg: 5.0 to 5.0f.

```cpp
float f { 4.1 }; // warning: 4.1 is a double literal, not a float literal
```
**Why this issue warning?**
>because 4.1 literal is a double and variable type is float so it converts double to float which can cause losing of precision so the compiler issue warning **so to fix this** we use float suffix f.

### String Literals
>in programming, a string is a sequence of characters (char).

> like other modern languages strings are not fundamental data type in c or c++ but rather in c or c++ they are complicated type called `C string` or `C-style strings`.

### C-style strings

two things worth knowing about c-style strings:

>All c-style strings have an implicit null terminator at the end.
>eg: assume string `"Subhan"` it looks like there are 6 characters in this string but actually there are 7 in which 7 character is a null terminator `\0` (a character with ASCII code 0) and it indicates end of string.

>	C-style string literals are const objects that are created at the start of the program and are guaranteed to exist for the entirety of the program.

Example:
```cpp
#include <iostream>
#include <cstring>

int main() {
    char greeting[20] = "Hello";
    strcat(greeting, " World"); // manual string operation
    std::cout << greeting << '\n';
}

```

### Magic Numbers
>Magic number is a literal that has unclear meaning or may need to be changed later.

```cpp
const int maxStudentsPerSchool{ numClassrooms * 30 };
setMax(30);
```
> In a program it is very difficult to tell what a literal mean so instead of writting literal directly, we store that literal in a variable (const) and also if we want to later change that literal, we just have to make changes in one variable and it will apply on every literal.

> Magic numbers are not always numbers, they can also be other types like string.
> Like App name, we might later change the app name so using magic number is easy and error prone.


>[!Best Practice]
>Avoid magic numbers in your code instead use constexpr

### Confusion of binary and decimal
> In decimal we call non-one digit number like eg: 10 as ten as it is 9+1.
> But in binary it is different because in binary 1+1 is equal to 10 which is confusing so we call this 10 as 1-0 and other with same pattern.


### How to use octal literal

>[!Avoid]
>Octal is hardly ever used, and we recommend you avoid it.

> Just use 0 prefix before the number

```cpp
#include <iostream>

int main()
{
    int x{ 012 }; // 0 before the number means this is octal
    std::cout << x << '\n';
    return 0;
}
```

### How to use hexadecimal literal

>To use a hexadecimal literal, prefix your literal with `0x`:

```cpp
#include <iostream>

int main()
{
    int x{ 0xF }; // 0x before the number means this is hexadecimal
    std::cout << x << '\n';
    return 0;
}
```

>In any base, counting follows a **place-value system**. When a digit reaches the max (`base - 1`), it rolls over to 0 and **carries** to the next digit on the left — just like odometers or digital clocks.

Example: (Same for other number system)
```cpp
...   97
...   98
...   99   ← rightmost digit is at max (9), so:
...  100   ← reset rightmost digit to 0, carry 1 to the left

```
- 9 → reset to 0
    
- Add 1 to the left digit
    
- If that’s also 9, reset it too and keep carrying left

### Using hexadecimal to represent binary
>Because there are 16 different values for a hexadecimal digit, we can say that a single hexadecimal digit encompasses 4 bits.
### 🧮 Why 1 Hex Digit = 4 Bits?
Because **4 bits** in binary can represent exactly **16** different values.

|Binary (4 bits)|Hex|
|---|---|
|0000|0|
|0001|1|
|0010|2|
|0011|3|
|0100|4|
|0101|5|
|0110|6|
|0111|7|
|1000|8|
|1001|9|
|1010|A|
|1011|B|
|1100|C|
|1101|D|
|1110|E|
|1111|F|

So, **1 hex digit** = **4 binary bits**

>Consequently, a pair of hexadecimal digits can be used to exactly represent a full byte.

### 💡 Then Why 2 Hex Digits = 1 Byte?

- 2 hex digits = 4 bits + 4 bits = **8 bits** = **1 byte**
    

**Example:**

- Hex: `AF`
    
- Binary:
    
    - `A` = `1010`
        
    - `F` = `1111`
        
- Together: `10101111` → 8 bits → 1 byte

### 🧠 Why Not 1 Hex Digit per Byte?

Because **1 hex digit = only 4 bits**.  
You'd only be able to represent numbers from `0000` to `1111` (0 to 15), which is **not enough** for a full byte (which goes from `00000000` to `11111111`, or 0 to 255).

>Consider a 32-bit integer with binary value 0011 1010 0111 1111 1001 1000 0010 0110. Because of the length and repetition of digits, that’s not easy to read. In hexadecimal, this same value would be: 3A7F 9826, which is much more concise. For this reason, hexadecimal values are often used to represent memory addresses or raw data in memory (whose type isn’t known).

### Binary Literals
>To use binary literal use `0b` prefix before binary digit.

```cpp
#include <iostream>

int main()
{
    int bin{};        // assume 16-bit ints
    bin = 0b1;        // assign binary 0000 0000 0000 0001 to the variable
    bin = 0b11;       // assign binary 0000 0000 0000 0011 to the variable
    bin = 0b1010;     // assign binary 0000 0000 0000 1010 to the variable
    bin = 0b11110000; // assign binary 0000 0000 1111 0000 to the variable

    return 0;
}
```
>[!Tip]
>Because binary literals are long so we can seperate them by using digit seperator (') single quote.
> ````cpp
int bin { 0b1011'0010 };

> By default C++ outputs values in decimal

> We can change the format via `std::dec`, `std::hex` etc Which are I/O manipulators.

```cpp
#include <iostream>

int main()
{
    int x { 12 };
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    std::cout << x << '\n'; // now hexadecimal
    std::cout << std::oct << x << '\n'; // octal
    std::cout << std::dec << x << '\n'; // return to decimal
    std::cout << x << '\n'; // decimal

    return 0;
}
```

### Outputting values in binary
>std::cout doesnt have the capability built-in to output binary values, for this we will use C++ standard library type called std::bitset, for this we have to include header file `#include <bitset>`

>To use `std::bitset`, we can define a `std::bitset` variable and tell `std::bitset` how many bits we want to store. The number of bits must be a compile-time constant. `std::bitset` can be initialized with an integral value (in any format, including decimal, octal, hex, or binary).

```cpp
#include <bitset> // for std::bitset
#include <iostream>

int main()
{
	// std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
	std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

	std::cout << bin1 << '\n' << bin2 << '\n';
	std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

	return 0;
}
```

```cpp
std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it
```
>creates a temporary (unnamed) `std::bitset` object with 4 bits, initializes it with binary literal `0b1010`, prints the value in binary, and then discards the temporary object.

### [Outputting values in binary using the Format / Print Library Advanced](https://www.learncpp.com/cpp-tutorial/numeral-systems-decimal-binary-hexadecimal-and-octal/#:~:text=In%20C%2B%2B20,0b1010%0A1010%200b1010)

> Modern C++ compilers are optimizing compilers, meaning they are capable of automatically optimizing your programs.
> And these optimization dont not modify your source file.

> For IDE: the IDE will likely automatically configure release builds to enable optimization and debug builds to disable optimization.

### The as-if rule
>The **as-if rule** says that the compiler can modify a program however it likes in order to produce more optimized code, so long as those modifications do not affect a program’s “observable behavior”.

>[!An optimization opportunity]
>[An optimization opportunity](https://www.learncpp.com/cpp-tutorial/the-as-if-rule-and-compile-time-optimization/#:~:text=Consider%20the%20following,run%20is%20wasteful.)

### Compile-time evaluation

>Modern C++ compilers are capable of fully or partially evaluating certain expressions at compile-time (rather than at runtime). When the compiler fully or partially evaluates an expression at compile-time, this is called **compile-time evaluation**.

> The resulting executable `.exe` are faster and smaller but at the cost of slightly slower compilation times.

#### Constant folding
>Constant folding is an optimization technique where compiler replaces expressions that have literal operands with the result of the expression.

```cpp
#include <iostream>

int main()
{
	// int x {3+4};
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```
This program produces the same output (`7`) as the prior version, but the resulting executable no longer needs to spend CPU cycles calculating `3 + 4` at runtime!

```cpp
#include <iostream>

int main()
{
	std::cout << 3 + 4 << '\n';

	return 0;
}
```
>In the above example, `3 + 4` is a subexpression of the full expression `std::cout << 3 + 4 << '\n';`. The compiler can optimize this to `std::cout << 7 << '\n';`.

### Constant Propagation

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```

> When x is initialized, the value 7 will be stored in the memory allocated for `x` then on next line it will go to fetch the memory allocated for `x` so it can print, so this require two memory access operations.
> **Constant Propagtion** is optimization technique where compiler replaces variable with their constant value so that variable exchanges with the constant value stored in it. So it will look like this in compilation:

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << 7 << '\n';

	return 0;
}
```
No need to fetch value from memory.

> It can further do constant folding optimization by Following:

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	int y { 3 };
	std::cout << x + y << '\n';

	return 0;
}
```
In this example, constant propagation would transform `x + y` into `7 + 3`, which can then be constant folded into the value `10`.

### Dead Code Elimination
**Dead code elimination** is an optimization technique where the compiler removes code that may be executed but has no effect on the program’s behavior.

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << 7 << '\n';

	return 0;
}
```

```cpp
#include <iostream>

int main()
{
	std::cout << 7 << '\n';

	return 0;
}
```
>When a variable is removed from a program because it is no longer needed, we say the variable has been **optimized out** (or **optimized away**).

### Const variables are easier to optimize

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```

>Since x is defined non-constant, in order to apply this optimization, the compiler must realize that the value of x must not changed, it comes down to complexity of program and how sophisticated the compiler’s optimization routines are.

>[!Tip]
>We can help the compiler optimize more effectively by using constant variables wherever possible. For example:

```cpp
#include <iostream>

int main()
{
	const int x { 7 }; // x is now const
	std::cout << x << '\n';

	return 0;
}
```
> Now compiler have a must case that value of x will not change so optimization will take place.

>[!Warning]
>[Optimization can make programs harder to debug](https://www.learncpp.com/cpp-tutorial/the-as-if-rule-and-compile-time-optimization/#:~:text=If%20optimization%20makes,that%20will%20help.)
>Compile-time debugging is an underdeveloped area


### # Constant expressions


>[!tip]
>By default, expressions evaluate at runtime.

```cpp
const double x { 1.2 };
const double y { 3.4 };
const double z { x + y }; // x + y may evaluate at runtime or compile-time
```
> The expression `x+y` would normally evaluate at runtime but since values of x and y are known(constant) they can be optimize to evaluate at compile time according to as-if rule.

### Compile-time programming

> Compile time programming is programming in which we explicitly tell the compiler through C++ feature for CTP to execute code at compile time, this feature is called compile time programming.

This feature can help improve software in a number of areas:

- Performance: makes our program smaller and faster.
- Versatility: We can always use such code in places that require a compile-time value. Code that relies on the as-if rule to evaluate at compile-time can’t be used in such places (even if the compiler opts to evaluate that code at compile-time) -- this decision was made so that code that compiles today won’t stop compiling tomorrow, when the compiler decides to optimize differently. [you **cannot** rely on compiler optimizations alone to make something behave like a constant. You **must** use proper `constexpr` or similar mechanisms to guarantee compile-time evaluation.]
- Predictability: We can have the compiler terminate the compilation process if explicit code cannot be executed at compile time rather than silently opting to have the code evaluate at runtime instead. This ensures the code execute at compile time as we want.
- Error Handling
- Undefined Behavious handling: Perhaps most importantly, undefined behavior is not allowed at compile-time. If we do something that causes undefined behavior at compile-time, the compiler should halt the build and ask us to fix it. Note that this is a hard problem for compilers, and they may not catch all cases.

>[!Conclusion]
>To summarize, compile-time evaluation allows us to write programs that are both more performant and of higher quality (more secure and less buggy)! So while compile-time evaluation does add some additional complexity to the language, the benefits can be substantial.

The following C++ features are the most foundational to compile-time programming:
- Constexpr variables
- Constexpr functions
- Templates
- static_assert
All of these features have one thing in common: they make use of constant expressions.

>[!Tip]
>Compile-time programming is a better alternative to as-if rule especially when you need **guaranteed compile-time evaluation**.

### Constant expressions

> In a constant expression, each part of the expression must be evaluatable at compile-time.

>Perhaps surprisingly, the C++ standard barely mentions “compile-time” at all. Instead, the standard defines a “constant expression”.

>An expression that is not a constant expression is often called a non-constant expression, and may informally be called a **runtime expression** (as such expressions typically evaluate at runtime).

>[!tip]
>constexpr are used for constant expression values. (Also other)

```cpp
int x = 5;
int y = x + 10;
int arr[y]; // ❌ Error: y is not a constant expression
```
constexpr is not used.

```cpp
constexpr int x = 5;
constexpr int y = x + 10;
int arr[y]; // OK: y is a constant expression

```
- `x` and `y` are `constexpr`, so they must be evaluated at compile-time.

#### What can be in Constant expression?
you dont need to remember this because compiler will point it to you.

- Literals
- most operators
- constexpr
- constexpr function calls with constant expression arguments

>[!tip]
>the following cannot be used in a constant expression:
>[Open](https://www.learncpp.com/cpp-tutorial/constant-expressions/#:~:text=Non%2Dconst%20variables,a%20runtime%20expression.)

>[!tip]
>**“Literals are constant expressions (because they are actually values).”**
>> Any expression that **only consists of a literal** (like `5`, `'x'`, or `true`) is automatically a **constant expression**, because its value is **known at compile time** — it never changes, it’s just a fixed value.

>[!as an aside]
>When constant expressions were defined, `const` integral types were grandfathered in because they were already being treated as constant expressions within the language.
>The committee discussed whether `const` non-integral types with a constant expression initializer should also be treated as constant expressions (for consistency with the `const` integral types case). Ultimately, they decided not to, in order to promote more consistent usage of `constexpr`.



```cpp
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}
```

```cpp
// Const integral variables with a constant expression initializer can be used in constant expressions:
const int a { 5 };           // a is usable in constant expressions
const int b { a };           // b is usable in constant expressions (a is a constant expression per the prior statement)
const long c { a + 2 };      // c is usable in constant expressions (operator+ has constant expression operands)

// Other variables cannot be used in constant expressions (even when they have a constant expression initializer):
int d { 5 };                 // d is not usable in constant expressions (d is non-const)
const int e { d };           // e is not usable in constant expressions (initializer is not a constant expression)
const double f { 1.2 };      // f is not usable in constant expressions (not a const integral variable)
```

>[!tip]
>The compiler is only _required_ to evaluate constant expressions at compile-time in contexts that _require_ a constant expression. It may or may not do so in other cases.

```cpp
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```

### So why doesn’t C++ require all constant expressions to be evaluated at compile-time? There are at least two good reasons:

- Makes debugging harder.
- To provide the compiler with the flexibility to optimize as it sees fit

>[!tip]
>In as-if rule optimizing depends on wheather the initializer is a constant expression.


```cpp
const int d { a * 2 }; // a defined as char a { 'q' };
```
`a` is not a constant expression, so `a * 2` is a non-constant expression.  
`d` is a non-constant expression since the initializer is not a constant expression.

### Constexpr variables

>A **constexpr** variable is always a compile-time constant. As a result, a constexpr variable must be initialized with a constant expression, otherwise a compilation error will result.

```cpp
#include <iostream>

// The return value of a non-constexpr function is not constexpr
int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not constexpr

    return 0;
}
```

>Additionally, `constexpr` works for variables with non-integral types:

### The meaning of const vs constexpr for variables

>**Const** : value cannot be changed after initializing. Value may be known at compile time or runtime. the const object can be evaluated at runtime.

> **constexpr** : The value of initializer must be known at compile time otherwise error, the constexpr object can be evaluated at runtime or compile time but runtime in a sense where it depends on other calculation which must be done in runtime like: 

```cpp
int runtime_input;
std::cin >> runtime_input;
constexpr int fixed = 10;
int sum = fixed + runtime_input; // ✅ fixed is constexpr, but this is runtime

```

>[!tip]
>Constexpr variables are implicitly const. Const variables are not implicitly constexpr (except for const integral variables with a constant expression initializer).


>Constexpr variables are implicitly const. Const variables are not implicitly constexpr (except for const integral variables with a constant expression initializer).

Example for constexpr are impicitly const:
```cpp
constexpr int x = 10;

// Equivalent To:
const int x = 10;

```
- You **do not** need to write `const` explicitly.
    
- The compiler **treats `x` as a `const int`**, even though you only wrote `constexpr`.
    
- So you **cannot modify** a `constexpr` variable after initialization — it's **implicitly `const`**.

Example for const variable are not implicitly constexpr:
```cpp
const int x = getValue(); // getValue() runs at runtime

```
- This is perfectly valid. The value is **set at runtime**, not compile-time.
    
- So `x` is **not a constant expression**, and **cannot be used** where a compile-time constant is required (e.g. array size or template arguments).

>[!Best Practice]
>Any constant variable whose initializer is a constant expression should be declared as `constexpr`.
>Any constant variable whose initializer is not a constant expression (making it a runtime constant) should be declared as `const`.

> Since Array length should be given at compile time so giving it as const variable with non-constant-expression will be invalid because it will evaluate at runtime so to solve this we can use const with constant-expression or we can simply use constexpr.


### Const and constexpr function parameters

>1. `const` function parameters are treated as runtime constants (even when the supplied argument is a compile-time constant).

```cpp
void printValue(const int x) {
    std::cout << x << '\n';
}

int main() {
    constexpr int value = 10;
    printValue(value); // Even though `value` is constexpr, `x` is a runtime parameter
}

```

>2. Function parameters cannot be declared as `constexpr`, since their initialization value isn’t determined until runtime.

```cpp
void func(constexpr int x) { } // ❌ Invalid — syntax error

```

### A brief introduction to constexpr functions

>A **constexpr function** is a function that can be called in a constant expression. A constexpr function must evaluate at compile-time when the constant expression it is part of must evaluate at compile time (e.g. in the initializer of a constexpr variable). Otherwise, a constexpr function may be evaluated at either compile-time (if eligible) or runtime. To be eligible for compile-time execution, all arguments must be constant expressions.

>To make a constexpr function, the `constexpr` keyword is placed in the function declaration before the return type:

```cpp
#include <iostream>

int max(int x, int y) // this is a non-constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

constexpr int cmax(int x, int y) // this is a constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    int m1 { max(5, 6) };            // ok
    const int m2 { max(5, 6) };      // ok
    constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

    int m4 { cmax(5, 6) };           // ok: may evaluate at compile-time or runtime
    const int m5 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
    constexpr int m6 { cmax(5, 6) }; // okay: must evaluate at compile-time

    return 0;
}
```

### Introduction to std::string

>C-style string literals are fine to use but C-style string variables behave odly and are hard to work with e.g: copy a larger C-style string into the space allocated for shorter c-style string.

Solution:

> For this we use std::string and std::string_view.

> These are not fundamental types, they are a class.

```cpp
#include <string>
```


```cpp
std::string myID{ "45" }; // "45" is not the same as integer 45!
```

>[!tip]
>`string` **is a data type** — just not a primitive one like `int` or `double`. It’s a **class type** from the standard library, which means it behaves like a type, **but with methods and features**.

>One of the neatest things that `std::string` can do is store strings of different lengths.

```cpp
std::string name { "Alex" }; // initialize name with string literal "Alex"

name = "Jason";              // change name to a longer string

```

>[!tip]
>If `std::string` doesn’t have enough memory to store a string, it will request additional memory (at runtime) using a form of memory allocation known as dynamic memory allocation. This ability to acquire additional memory is part of what makes `std::string` so flexible, but also comparatively slow.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color;

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

#### Output:
Enter your full name: John Doe

Enter your favorite color: Your name is John and your favorite color is Doe

> This is because of buffer.

#### Solution:

> To fix this we will use `std::getline`.

```cpp
#include <iostream>
#include <string> // For std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

#### Output:

Enter your full name: John Doe

Enter your favorite color: blue
Your name is John Doe and your favorite color is blue

#### What is std::ws

> We previously used output manipulators like `std::setprecision()` to change the precision outputted.

> C++ also supports input manipulators which alter the way how input is accepted.

> `std::ws` input manipulator tells std::cin to ignore any whitespace before extraction, Leading whitespace is any whitespace character (spaces, tabs, newlines) that occur at the start of the string.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin, name); // note: no std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

#### Output:

Pick 1 or 2: 2

Now enter your name: Hello, , you picked 2

>it won’t actually wait for you to enter your name! Instead, it prints the “Hello” string, and then exits.
>When you enter a value using `operator>>`, `std::cin` not only captures the value, it also captures the newline character (`'\n'`) that occurs when you hit the enter key. So when we type `2` and then hit enter, `std::cin` captures the string `"2\n"` as input. It then extracts the value `2` to variable `choice`, leaving the newline character behind for later. Then, when `std::getline()` goes to extract text to `name`, it sees `"\n"` is already waiting in `std::cin`, and figures we must have previously entered an empty string! Definitely not what was intended.

#### Fix:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: added std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

#### Output:
Pick 1 or 2: 2

Now enter your name: Alex
Hello, Alex, you picked 2

>[!tip]
>If using `std::getline()` to read strings, use `std::cin >> std::ws` input manipulator to ignore leading whitespace. This needs to be done for each `std::getline()` call, as `std::ws` is not preserved across calls.


>[!Conclusion Very Important] 
If we use simple getline() without ws input manipulator then it will also take leading whitespace captured in buffer so to not do this we use `std::ws` which tells to skip the leading whitespace which in our case can be `\n` from simple `>>` operator left in buffer so thats why.


### The length of a `std::string`

> To get the length of string we use member function of class std::string which  is length `length()`

> And to call the member function of class we use dot `.` operator instead of simple function which is different.

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```
Alex has 4 characters

>[!tip]
>the returned length of a `std::string` does not include the implicit null-terminator character.

> Length() returns an unsigned integral value, if you want to assign it as int variable you should use static_cast to avoid compiler warning about signed/unsigned conversion warning.

```cpp
int length { static_cast<int>(name.length()) };
```

### Initializing a `std::string` is expensive

>Whenever a std::string is initialized, a copy of the string used to initialize it is made. Making copies of strings is expensive, so care should be taken to minimize the number of copies made.

```cpp
std::string name = "Alex";

```

What happens behind the scenes:

1. `"Alex"` is a **string literal** stored in static memory (a `const char[5]`).
    
2. `std::string` creates a new object.
    
3. It **copies** the characters `'A'`, `'l'`, `'e'`, `'x'`, and the null terminator into **its own internal buffer**.
    

So `"Alex"` stays in memory, and a **second copy** is made inside the `std::string` object.

> This takes **CPU time and memory**, especially for large strings or in tight loops.


### Do not pass `std::string` by value


```cpp
void greet(std::string name) {
    std::cout << "Hello, " << name << "!\n";
}
```

>You're **making a full copy** of the `name` string every time the function is called.
>So if the original string is large or the function is called many times, it becomes:
- Slow
- Memory wasteful

#### 💥 Why is this bad?

```cpp
std::string longName = "AlexanderTheGreatTheConqueror";
greet(longName); // full copy happens here!

```

This causes:

1. A new memory allocation for `name`.
    
2. Copying of all characters.
    
3. Deallocation after the function ends.
    

This overhead is unnecessary if the function just **reads** the string.

#### ✅ Better Way: Pass by `const reference`

```cpp
void greet(const std::string& name) {
    std::cout << "Hello, " << name << "!\n";
}

```

- ✅ **No copy** is made.
    
- ✅ Fast and efficient.
    
- ✅ The `const` prevents accidental modification.

#### 🔁 When is passing by value okay?
#### 1. You **want** to modify or own the copy

#### 2. You are going to **move** it inside the function

### Returning a `std::string`

>When a function returns by value to the caller, the return value is normally copied from the function back to the caller.

You might think:

> “Returning a `std::string` by value must be inefficient — it causes a copy!”

But **in modern C++**, this is **not always true** — thanks to **Return Value Optimization (RVO)** and **move semantics**.

#### When is it okay to return std::string by value?

- A local variable of type `std::string`.
- A `std::string` that has been returned by value from another function call or operator.
- A `std::string` temporary that is created as part of the return statement.

>In most other cases, prefer to avoid returning a `std::string` by value, as doing so will make an expensive copy.

### Literals for `std::string`

>Double-quoted string literals (like “Hello, world!”) are C-style strings by default (and thus, have a strange type).

>We can create string literals with type `std::string` by using a `s` suffix after the double-quoted string literal. The `s` must be lower case.

```cpp
#include <iostream>
#include <string> // for std::string

int main()
{
    using namespace std::string_literals; // easy access to the s suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    return 0;
}
```

>[!tip]
>We recommend `using namespace std::string_literals`, which imports only the literals for `std::string`.

### Constexpr strings 

>If you try to define a `constexpr std::string`, your compiler will probably generate an error:

```cpp
#include <iostream>
#include <string>

int main()
{
    using namespace std::string_literals;

    constexpr std::string name{ "Alex"s }; // compile error

    std::cout << "My name is: " << name;

    return 0;
}
```

>This happens because `constexpr std::string` isn’t supported at all in C++17 or earlier, and only works in very limited cases in C++20/23. If you need constexpr strings, use `std::string_view` instead.

### `std::string_view`

> For fundamental types, initializing and copying a variable is fast but for std::string it is slow.

```cpp
#include <iostream>
#include <string>

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    printString(s);

    return 0;
}
```

>In this example program makes two copies of C-style string, one for initializing s in main and one as a parameter for function.

>**`std::string_view`** : provides read-only access to an existing string (a C-style string, a `std::string`, or another `std::string_view`) without making copy.

```cpp
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```

> `std::string_view` is same as `const std::string &str` which also points to some string variable by reference and doesnt make copy which is efficient when you are passing a `std::string` object but there are some limitations with this like:
>> You cannot pass C-style strings `const char*`, string literals or other string types directly.
>> `std::string` needs to be constructed beforehand.
>
>So Due to these limitations we use `std::string_view`, - Accepts **any string-like input** without copying (read-only view of the string). Works With: 
>> `std::string`
>> string literals
>> const char*
>> std::string_view
>
>No Heap allocation. faster and more flexible. 

```cpp
print("Subhan");               // ✅ string literal
print(std::string{"Subhan"}); // ✅ std::string
print(std::string_view{"Sub"}); // ✅ string_view

```

## 🧪 Performance Comparison

|Feature|`const std::string&`|`std::string_view`|
|---|---|---|
|Copies string?|❌ No|❌ No|
|Works with string literals?|❌ No|✅ Yes|
|Works with `std::string`?|✅ Yes|✅ Yes|
|Requires constructing a `std::string`?|✅ Yes if not already a string|❌ No|
|Preferred in modern C++?|🔸 Sometimes|✅ Often (since C++17)|
## ✅ Final Rule of Thumb:

- When **creating or storing** a string in your code:  
    ➤ Use `std::string`
    
- When you only need a **read-only window/view**, especially in function arguments:  
    ➤ Use `std::string_view`


---

## 🔑 Quick Answer:

Use `std::string` when:

- You **own** the string.
    
- You want to **store**, **modify**, or **extend** it.
    
- You want a **safe copy** that won’t depend on external memory.
    

Use `std::string_view` when:

- You only need a **read-only, non-owning view** of a string.
    
- You don’t need to store or change it.
    
- You’re pointing to string **data managed elsewhere** (e.g., a literal or another `std::string`).

```cpp
int main() {
    std::string s1{"Subhan"};           // Owns the string
    std::string_view s2{"Subhan"};      // Just points to the literal

    s1[0] = 'Z';        // ✅ OK
    // s2[0] = 'Z';     // ❌ Error — read-only view

    s1 += " Ahmed";     // ✅ OK
    // s2 += " Ahmed";  // ❌ Error — cannot append
}

```

### `std::string_view` parameters will accept many different types of string arguments

>Both a C-style string and a `std::string` will implicitly convert to a `std::string_view`. Therefore, a `std::string_view` parameter will accept arguments of type C-style string, a `std::string`, or `std::string_view`:

### `std::string_view` will not implicitly convert to `std::string`

```cpp
void print(std::string s) { /* ... */ }

std::string_view sv = "Hello";

// ❌ ERROR: No implicit conversion allowed!
print(sv);

// ✅ OK: Explicit conversion required
print(std::string(sv));
print(static_cast<std::string>(sv));
```

> Because `std::string` makes a copy of its initializer (which is expensive), C++ won’t allow implicit conversion of a `std::string_view` to a `std::string`. This is to prevent accidentally passing a `std::string_view` argument to a `std::string` parameter, and inadvertently making an expensive copy where such a copy may not be required.

### Assignment changes what the `std::string_view` is viewing

> Assigning a new string to a `std::string_view` causes the `std::string_view` to view the new string. It does not modify the prior string being viewed in any way.

> [!tip]
> We dont have to use std::string_view literals with `sv` suffix because actually they are C-style literals in disguise no need to use std::string_view literals with `sv` suffix.


### constexpr `std::string_view`

>Unlike `std::string`, `std::string_view` has full support for constexpr:

```cpp
#include <iostream>
#include <string_view>

int main()
{
    constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
    std::cout << s << '\n'; // s will be replaced with "Hello, world!" at compile-time

    return 0;
}
```

### Owners and Viewers

#### Analogy
>Say you’ve decided that you’re going to paint a picture of a bicycle. But you don’t have a bicycle! What are you to do?
>Well, you could go to the local cycle shop and buy one. You would own that bike. This has some benefits: you now have a bike that you can ride. You can guarantee the bike will always be available when you want it. You can decorate it, or move it. There are also some downsides to this choice. Bicycles are expensive. And if you buy one, you are now responsible for it. You have to periodically maintain it. And when you eventually decide you don’t want it any more, you have to properly dispose of it.Ownership can be expensive. As an owner, it is your responsibility to acquire, manage, and properly dispose of the objects you own.On your way out of the house, you glance out your window front. You notice that your neighbor has parked their bike across from your window. You could just paint a picture of your neighbor’s bike (as seen from your window) instead. There are lots of benefits to this choice. You save the expense of having to go acquire your own bike. You don’t have to maintain it. Nor are you responsible for disposing of it. When you are done viewing, you can just shut your curtains and move on with your life. This ends your view of the object, but the object itself is not affected by this. There are also some potential downsides to this choice. You can’t paint or customize your neighbors bike. And while you are viewing the bike, your neighbor may decide to change the way the bike looks, or move it out of your view altogether. You may end up with a view of something unexpected instead.Viewing is inexpensive. As a viewer, you have no responsibility for the objects you are viewing, but you also have no control over those objects.

### why `std::string` makes an expensive copy of its initializer.

> When an object is created like `std::string` , it needs to store its own copy of data so it can access and modify it safely.

```cpp
std::string s = "hello";
```

- `"hello"` is a **temporary string literal** (or temporary `std::string` in some cases).
    
- When `s` is constructed, it **copies** `"hello"` into its own internal memory.
    
- After this, `s` doesn’t rely on the original `"hello"` anymore.

### 🔁 Example with a Temporary

```cpp
std::string s = std::string("hello");
```

- `std::string("hello")` is a **temporary object**.
    
- If `s` didn’t copy the content, it would point to a temporary that disappears immediately.
    
- That would cause undefined behavior when you try to use `s`.
### 🔁 Example with a Variable

```cpp
std::string original = "hello";
std::string copy = original;
original = "world"; // Doesn't affect 'copy'
```

- `copy` needs its **own copy** of `"hello"` because `original` might change later.
    
- If `copy` shared memory with `original`, changes to `original` would affect `copy`, which is not the desired behavior.

>[!Key Insight]
>An initialized object has no control over what happens to the initialization value after initialization is finished.

```cpp
std::string name = std::string("Alice"); // temporary std::string
```

> since `std::string` makes its own copy of the initializer so we dont have to worry about what happens to initializer after initialization, it can destroy but we dont have to worry since we have already made copy of that.


>[!tip]
>In the context of our analogy, `std::string` is an owner -- it is responsible for acquiring its string data from the initializer, managing access to the string data, and properly disposing of the string data when the `std::string` object is destroyed.

>[!Conclusion on Difference Between std::string and std::string_view]
>When we initailize string using std::string it copyies the initialization string into the object (In memory) while std::string_view doesnt copy the initialization string, it just make a pointer of that initialization string and points to it, it doesnt own that string.

```cpp
std::string_view sv = "Hello";
sv = "Hello2";
```
> In this example: You're **not changing the characters of the string** `"Hello"` or `"Hello2"`.

What you're actually doing is:

- First: `sv` is set to view the string literal `"Hello"`.
    
- Then: `sv` is reassigned to view a **different string literal** `"Hello2"`.

>[!Warning]
>A view is dependent on the object being viewed. If the object being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result.

#### Example:

```cpp
std::string_view sv;

{
    std::string temp = "Hello";
    sv = temp; // sv points to temp's internal buffer
} // temp is destroyed here

std::cout << sv << "\n"; // ❌ Undefined behavior: sv is dangling

```

After the block ends, `temp` is destroyed, but `sv` is still pointing to its now-invalid memory.

>[!tip]
>A `std::string_view` that is viewing a string that has been destroyed is sometimes called a **dangling** view.

> The best use for `std::string_view` is as a read-only function parameter.

[Improperly using `std::string_view`](https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/#:~:text=Let%E2%80%99s%20take%20a,use%20name.)

>[!Warning]
>Do not initialize a `std::string_view` with a `std::string` literal, as this will leave the `std::string_view` dangling.

>We can also get undefined behavior when the underlying string is modified:

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, a!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    return 0;
}
```

>[!tip]
>Modifying a `std::string` is likely to invalidate all views into that `std::string`.

### Revalidating an invalid `std::string_view`

>Invalidated objects can often be revalidated (made valid again) by setting them back to a known good state. For an invalidated `std::string_view`, we can do this by assigning the invalidated `std::string_view` object a valid string to view.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    sv = s;                    // revalidate sv: sv is now viewing s again
    std::cout << sv << '\n';   // prints "Hello, universe!"

    return 0;
}
```

### Be careful returning a `std::string_view`

> Using `std::string_view` as a return value is dangerous.

>Because local variables are destroyed at the end of the function, returning a `std::string_view` that is viewing a local variable will result in the returned `std::string_view` being invalid, and further use of that `std::string_view` will result in undefined behavior. For example:

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view getBoolName(bool b)
{
    std::string t { "true" };  // local variable
    std::string f { "false" }; // local variable

    if (b)
        return t;  // return a std::string_view viewing t

    return f; // return a std::string_view viewing f
} // t and f are destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // undefined behavior

    return 0;
}
```

#### [Two cases where returning std::string_view is safe](https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/#:~:text=There%20are%20two%20main%20cases,after%20the%20temporary%20is%20destroyed)

>[!warning]
>> ❗ Never return a `std::string_view` from a function that creates a temporary string inside it.

### Some View modification functions

- `remove_prefix()` - remove character from left side of view.
- `remove_suffix()` - remove character from right side of view.
> To reset the view - just reassign the source string to view again and its the only way.


> We can also view substring of string using `std::string_view`.

#### `std::string_view` may or may not be null-terminated

> The ability of viewing just a substring comes with consequences which is that we may or may not be null-terminated.

Example:
>Consider the string “snowball”, which is null-terminated (because it is a C-style string literal, which are always null-terminated). If a `std::string_view` views the whole string, then it is viewing a null-terminated string. However, if `std::string_view` is only viewing the substring “now”, then that substring is not null-terminated (the next character is a ‘b’).

>[!tip]
>A C-style string literal and a `std::string` are always null-terminated.
>A `std::string_view` may or may not be null-terminated.

>[!tip]
>the null terminator **is part of the string in memory**, but **not part of the string length** returned by functions like `strlen()`.

### A quick guide on when to use `std::string` vs `std::string_view`

#### Variables

> Use `std::string` when: 
> 
>>1: when we need string which we can modify.
>>2: when we want to store user inputted text.
>>3: when we want to store return value of a function which returns `std::string`.
>
>Use `std::string_view` when:
>
>>1:  You need read-only access to part or all of a string that already exists elsewhere and will not be modified or destroyed before use of the `std::string_view` is complete.
>>2: You need a symbolic constant for a C-style string.
>>3: You need to continue viewing the return value of a function that returns a C-style string or a non-dangling `std::string_view`.

#### Function parameters

>Use `std::string` function parameters when:
>
>>1: The function needs to modify the string passed in as an argument without affecting the caller string. This is rare.
>>2: You are using language standard C++14 or older and aren’t comfortable using references yet.
>
>Use a `std::string_view` function parameter when:
>
>>1:  The function needs a read-only string.
>>2:  The function needs to work with non-null-terminated strings.

>[!tip]
>`std::string_view` doesnt need null terminated because it Knows where the string **starts and ends** using a length.

#### **Return types**

Use a `std::string` return type when:

- The return value is a `std::string` local variable or function parameter.
- The return value is a function call or operator that returns a `std::string` by value.

Use a `std::string_view` return type when:

- The function returns a C-style string literal or local `std::string_view` that has been initialized with a C-style string literal.
- The function returns a `std::string_view` parameter.


### **Insights**

Things to remember about `std::string`:

- Initializing and copying `std::string` is expensive, so avoid this as much as possible.
- Avoid passing `std::string` by value, as this makes a copy.
- If possible, avoid creating short-lived `std::string` objects.
- Modifying a `std::string` will invalidate any views to that string.
- It is okay to return a local `std::string` by value.

Things to remember about `std::string_view`:

- `std::string_view` is typically used for passing string function parameters and returning string literals.
- Because C-style string literals exist for the entire program, it is always okay to set a `std::string_view` to a C-style string literal.
- When a string is destroyed, all views to that string are invalidated.
- Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
- A `std::string_view` may or may not be null-terminated.


>[!tip]
>- Because C-style string literals exist for the entire program, it is always okay to set a `std::string_view` to a C-style string literal.

>[!tip]
>**in many cases, using `std::string_view` to reference a string literal is better than initializing a `std::string`**, especially when **you don’t need to modify or own the string**.

>[!tip]
>A `std::string_view` that is viewing a string that has been destroyed is sometimes called a **dangling** view.

All done just little confusion on why std::string_view may or may not be null termianted?

