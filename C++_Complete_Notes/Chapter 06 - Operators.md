> In simple maths we can evaluate expression by simple maths precedence rules but compiler doesnt know that.

> So at compile time compiler must do 2 things.
>- parse expression and determine how operands are grouped with operators and this is done by precedence and associativity rules.
>-  At compile time or runtime, the operands are evaluated and operations executed to produce a result.

### Operator precedence

> all operators are assigned a level of precedence.
> operators with high precedence level will group with operands first.
> eg: multiplication and division have higher precedence (level 5) than addition (level 6) so operator multiplication or division will grouped first and then addition.
> 4 + 2 * 3 will be 4 + (2 * 3).

### Operator associativity

There is some case where compiler cannot determine whom to group like: 

> Consider a compound expression like `7 - 4 - 1`. Should this be grouped as `(7 - 4) - 1` which evaluates to `2`, or `7 - (4 - 1)`, which evaluates to `4`? Since both subtraction operators have the same precedence level, the compiler can not use precedence alone to determine how this should be grouped.

> If two operator with the same precedence level are adjacent to each other in expression then operator associativity tells the compiler wheather to evaluate the operator from left to right or right to left, so the subtraction operator has precendence level 6 so it will do left to right.
> eg: 7 - 4 - 1 to (7 - 4) - 1.

### Table of operator precedence and associativity

- Precedence level 1 is the highest precedence level, and level 17 is the lowest. Operators with a higher precedence level have their operands grouped first.
- L->R means left to right associativity.
- R->L means right to left associativity.

				#### [Table](https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/#:~:text=Prec/Ass,expression%2C%20expression)

### Parenthesization

>[!tip]
>if we want to explicitly want to group operands we can use paranthesis because it has the highest precedence.

### Use parenthesis to make compound expressions easier to understand

>[!Best practice]
>Use parentheses to make it clear how a non-trivial compound expression should evaluate (even if they are technically unnecessary).
>Non-trival compound expression: `x && y || z`.

>A good rule of thumb is: Parenthesize everything, except addition, subtraction, multiplication, and division.

```cpp
x = (y + z + w);   // instead of this
x = y + z + w;     // it's okay to do this

x = ((y || z) && w); // instead of this
x = (y || z) && w;   // it's okay to do this

x = (y *= z); // expressions with multiple assignments still benefit from parenthesis
```

>[!Best practice]
>Expressions with a single assignment operator do not need to have the right operand of the assignment wrapped in parenthesis.
>> **Assignment operators** (like `=`, `+=`, `-=`, etc.) have **very low precedence** — almost the lowest.
>> The **only operator with lower precedence** than assignment is the **comma operator** `,`, which is rarely used.
>>Because of this low precedence, **the entire right-hand side is fully evaluated before** the assignment happens.

### Value computation of operations

>The C++ standard uses the term **value computation** to mean the execution of operators in an expression to produce a value. The precedence and association rules determine the order in which value computation happens.
>For example, given the expression `4 + 2 * 3`, due to the precedence rules this groups as `4 + (2 * 3)`. The value computation for `(2 * 3)` must happen first, so that the value computation for `4 + 6` can be completed.

### Evaluation of operands

>The C++ standard (mostly) uses the term **evaluation** to refer to the evaluation of operands (not the evaluation of operators or expressions!).
>eg: `a+b` evaluation of operands will be like a will become 1 etc. you got the point.

### The order of evaluation of operands (including function arguments) is mostly unspecified [](https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/#unspecified)

>We know the order of operator and how their value computation happends but evaluation of operands and function arguments are unspecified and compiler do it himself.

> eg: The compiler is free to calculate `a * b` or `c * d` first.

Lets take an example:

```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z)
{
    std::cout << x + (y * z);
}

int main()
{
    printCalculation(getValue(), getValue(), getValue()); // this line is ambiguous

    return 0;
}
```

>If you run this program and enter the inputs `1`, `2`, and `3`, you might assume that this program would calculate `1 + (2 * 3)` and print `7`. But that is making the assumption that the arguments to `printCalculation()` will evaluate in left-to-right order (so parameter `x` gets value `1`, `y` gets value `2`, and `z` gets value `3`). If instead, the arguments evaluate in right-to-left order (so parameter `z` gets value `1`, `y` gets value `2`, and `x` gets value `3`), then the program will print `5` instead.

```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z)
{
    std::cout << x + (y * z);
}

int main()
{
    int a{ getValue() }; // will execute first
    int b{ getValue() }; // will execute second
    int c{ getValue() }; // will execute third

    printCalculation(a, b, c); // this line is now unambiguous

    return 0;
}
```

>[!Warning]
>Operands, function arguments, and subexpressions may be evaluated in any order.
>>It is a common mistake to believe that operator precedence and associativity affects order of evaluation. Precedence and associativity is used only to determine how operands are grouped with operators, and the order of value computation.

### Unary arithmetic operators

There are two Unary arithmetic operstors:
- + : +x, using this is redundant since it is by default.
- - :  -x, miltiplyies the x with -1.

>[!tip]
>Don't confuse unary minus operator with binary subtraction operator which use the same symbol.

>`x = 5 - -3` : the first minus is the _binary subtraction_ operator, and the second is the _unary minus_ operator.

### Integer and floating point division

> If either or both of the operands are floating point number then the division operator performs floating point division and fraction value is kept and this is called **floating point division**.
> If both of the operands are integers then the division performed will be **integer division** which will exclude fraction if there is!

### Using static_cast<> to do floating point division with integers

```cpp
#include <iostream>

int main()
{
    constexpr int x{ 7 };
    constexpr int y{ 4 };

    std::cout << "int / int = " << x / y << '\n';
    std::cout << "double / int = " << static_cast<double>(x) / y << '\n';
    std::cout << "int / double = " << x / static_cast<double>(y) << '\n';
    std::cout << "double / double = " << static_cast<double>(x) / static_cast<double>(y) << '\n';

    return 0;
}
```

### Dividing by 0 and 0.0

Integer division with a divisor of `0` will cause undefined behavior, as the results are mathematically undefined!

```cpp
#include <iostream>

int main()
{
	constexpr int apples { 12 };
	std::cout << "You have " << apples << " apples. Enter how many people to divide them between: ";
	int x {};
	std::cin >> x;

	std::cout << "Each person gets " << apples / x << " whole apples.\n"; // apples and x are int, so this is integer division

	return 0;
}
```

> If i give divisor a value of 0 then our program will crash!

```cpp
#include <iostream>

int main()
{
	constexpr int apples { 12 };
	std::cout << "You have " << apples << " apples. Enter how many servings of apples you want: ";

	double d {};
	std::cin >> d;

	std::cout << "Each serving is " << apples / d << " apples.\n"; // d is double, so this is floating point division

	return 0;
}
```

> The result of dividing by floating point value `0.0` is implementation-defined meaning the behavious is determined by the compiler/architecture.
> Like on architecture that support IEEE754 floating point format the resilt will be NaN or Infinity.

### Arithmetic assignment operators

|Operator|Symbol|Form|Operation|
|---|---|---|---|
|Addition assignment|+=|x += y|Add y to x|
|Subtraction assignment|-=|x -= y|Subtract y from x|
|Multiplication assignment|*=|x *= y|Multiply x by y|
|Division assignment|/=|x /= y|Divide x by y|
|Remainder assignment|%=|x %= y|Put the remainder of x / y in x|
### Modifying and non-modifying operators

> An operator that can modify the value of one of its operands is informally called a **modifying operator**

- The assignment operators, including the standard assignment operator (`=`), the arithmetic assignment operators (`+=`, `-=`, `*=`, `/=`, and `%=`), and the bitwise assignment operators (`<<=`, `>>=`, `&=`, `|=` and `^=`).
- The increment and decrement operators (`++` and `--` respectively). 


### The remainder operator (Modulus operator)

>The **remainder operator** (also commonly called the **modulo operator** or **modulus operator**) is an operator that returns the remainder after doing an integer division.

>The remainder operator only works with integer operands.

>This is most useful for testing whether a number is evenly divisible by another number (meaning that after division, there is no remainder): if _x % y_ evaluates to 0, then we know that _x_ is evenly divisible by _y_.

### General Rule:

Whenever you divide a **smaller number by a larger one**, the result of integer division will always be:

- **Quotient = 0**
    
- **Remainder = the smaller number itself**

### Remainder with negative numbers

>The remainder operator can also work with negative operands. `x % y` always returns results with the sign of _x_.
>remainder takes the sign of the first operand.

```cpp
#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;

	std::cout << "Enter another integer: ";
	int y{};
	std::cin >> y;

	std::cout << "The remainder is: " << x % y << '\n';

	if ((x % y) == 0)
		std::cout << x << " is evenly divisible by " << y << '\n';
	else
		std::cout << x << " is not evenly divisible by " << y << '\n';

	return 0;
}
```

>In cases where the first operand can be negative, one must take care to note that the remainder can also be negative. For example, you might think to write a function that returns whether a number is odd like this:

```cpp
bool isOdd(int x)
{
    return (x % 2) == 1; // fails when x is -5
}
```

>However, this will fail when x is a negative odd number, such as `-5`, because `-5 % 2` is -1, and -1 != 1.

>[!tip]
>if you’re going to compare the result of a remainder operation, it’s better to compare against 0.

```cpp
bool isOdd(int x)
{
    return (x % 2) != 0; // could also write return (x % 2)
}
```

### Where’s the exponent operator?

> In C++ `^` operator which is used for exponent in maths is used for Bitwise operator `XOR`.

>To do exponents in C++, `#include` the `<cmath>` header, and use the pow() function:

```cpp
#include <cmath>

double x{ std::pow(3.0, 4.0) }; // 3 to the 4th power
```

> The parameters and return value of function pow() are of type double due to rounding errors in floating point numbers.

>the results of pow() may not be precise (even if you pass it integers or whole numbers).

>[!tip]
>If you want to do integer exponentiation, you’re best off using your own function to do so. 


The following function implements integer exponentiation (using the non-intuitive “exponentiation by squaring” algorithm for efficiency):

```cpp
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>

// note: exp must be non-negative
// note: does not perform range/overflow checking, use with caution
constexpr std::int64_t powint(std::int64_t base, int exp)
{
	assert(exp >= 0 && "powint: exp parameter has negative value");

	// Handle 0 case
	if (base == 0)
		return (exp == 0) ? 1 : 0;

	std::int64_t result{ 1 };
	while (exp > 0)
	{
		if (exp & 1)  // if exp is odd
			result *= base;
		exp /= 2;
		base *= base;
	}

	return result;
}

int main()
{
	std::cout << powint(7, 12) << '\n'; // 7 to the 12th power

	return 0;
}
```

### Difference Between Prefix and Postfix Increment and Decrement

#### Prefix :

- The **operation happens first**, then the result is used in the expression.
    
- The variable is incremented/decremented **before** it is used.
```cpp
int x = 5;
int y = ++x;  // x becomes 6, then y is assigned 6

```
Result:
- `x = 6`
    
- `y = 6`

#### Postfix

- The **value is used first**, then the operation happens.
    
- The variable is incremented/decremented **after** it is used.
    

**Example:**
```cpp
int x = 5;
int y = x++;  // y is assigned 5, then x becomes 6

```

**Result:**

- `x = 6`
    
- `y = 5`

>[!tip]
>When the result is **not** used in an expression, both forms behave the same:
>> ```
>> x++;  // same as ++x; if not used in a larger expression

But in expressions like:

```cpp
arr[i++] = val;  // uses i, then increments it
arr[++i] = val;  // increments i, then uses it
```

```cpp
int arr[5] = {0};   // an array of size 5
int i = 1;
int val = 10;

```

- `i++` is **postfix**: Use `i` first, then increment.
    
- `arr[i] = val;` → Since `i = 1`, this means `arr[1] = 10;`
    
- After this, `i` becomes `2`.


### When to use prefix vs postfix

>In cases where code can be written to use either prefix or postfix, prefer the prefix versions, as they are generally more performant, and less likely to cause surprises.

>[!tip]
>Favor the prefix versions, as they are more performant and less likely to cause surprises.

### Side effects

>A function or expression is said to have a **side effect** if it has some observable effect beyond producing a return value.

>Common examples of side effects include changing the value of objects, doing input or output, or updating a graphical user interface (e.g. enabling or disabling a button).

```cpp
x = 5; // the assignment operator has side effect of changing value of x
++x; // operator++ has side effect of incrementing x
std::cout << x; // operator<< has side effect of modifying the state of the console
```

>[!tip]
>The assignment operators, prefix operator, and postfix operator have side effects that permanently change the value of an object.  
Other operators (such as the arithmetic operators) return a value, and do not modify their operands.

### Side effects can cause order of evaluation issues

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int x { 5 };
    int value{ add(x, ++x) }; // undefined behavior: is this 5 + 6, or 6 + 6?
    // It depends on what order your compiler evaluates the function arguments in

    std::cout << value << '\n'; // value could be 11 or 12, depending on how the above line evaluates!

    return 0;
}
```

>The C++ standard does not define the order in which function arguments are evaluated. If the left argument is evaluated first, this becomes a call to add(5, 6), which equals 11. If the right argument is evaluated first, this becomes a call to add(6, 6), which equals 12! Note that this is only a problem because one of the arguments to function add() has a side effect.

>[!As an aside!]
>The C++ standard intentionally does not define these things so that compilers can do whatever is most natural (and thus most performant) for a given architecture.

### The sequencing of side effects

#### ✅ **1. What Are Side Effects?**

A **side effect** in C++ is any change in state caused by evaluating an expression.

Examples of side effects:
```cpp
++x;     // increments x x = 5;   // modifies x func();  // if func() modifies any variable or I/O
```

`++x;     // increments x x = 5;   // modifies x func();  // if func() modifies any variable or I/O`

---

#### ⚠️ **2. Why Does `x + ++x` Cause Problems?**

```cpp
int x = 1; int y = x + ++x;
```

This line seems simple but leads to **unspecified or undefined behavior**.

#### Here’s Why:

- You’re modifying `x` with `++x` (**side effect**), and
    
- You’re also **reading** `x` (the left operand of `+`) **in the same statement**,
    
- Without a **sequence point** or guaranteed evaluation order.
    

Different compilers may do:

- `x + ++x` → `1 + 2` (Clang-style)
    
- or → `2 + 2` (GCC / MSVC style)
    

⚠️ The C++ standard **does not guarantee** the order in which operands of `+` are evaluated.

---

#### 🧠 **Why Is This Dangerous?**

It’s dangerous because:

- The same code can behave **differently** on different compilers.
    
- The behavior can change even within the same compiler with different optimization flags.
    
- It may result in **unpredictable bugs**.
    

---

#### ✅ **Safe Programming Practice:**

> Never **modify and use** the same variable **more than once in a single expression**.

❌ Risky:

```cpp
int y = x + ++x; int z = x++ + x;
```

✅ Safe:

```cpp
++x; int y = a + x;
```

Or:

```cpp
int temp = ++x; int y = x + temp;
```

---

#### 🧪 Visual Breakdown of the Problem:

Let’s take `x + ++x` when `x = 1`

#### Possible Compilers' Views:

| Compiler | `x` read  | `++x` applied | Final Expression |
| -------- | --------- | ------------- | ---------------- |
| Clang    | 1         | `++x` → 2     | `1 + 2 = 3`      |
| GCC/MSVC | `++x` → 2 | then used     | `2 + 2 = 4`      |

⚠️ Result: **Different answers from different compilers. Dangerous!**

---

#### 🔒 Rule of Thumb:

> Don’t write code that relies on the **order of evaluation** when you're **modifying and reading the same variable**.


### Comma Operator

>Comma operator has the lowest precedence and lower than assignment operator.

>The **comma operator (,)** allows you to evaluate multiple expressions wherever a single expression is allowed. The comma operator evaluates the left operand, then the right operand, and then returns the result of the right operand.

```cpp
#include <iostream>

int main()
{
    int x{ 1 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand

    return 0;
}
```

- `x` is initialized to 1.
    
- `y` is initialized to 2.
    
- `(++x, ++y)`:
    
    - First, `++x` is executed → `x = 2`
        
    - Then, `++y` is executed → `y = 3`
        
    - The **value of the entire expression** is the value of `++y`, which is `3`
        
- `std::cout << 3;` → prints `3`

```cpp
z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.

z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.
```

>[!tip]
>In almost every case, a statement written using the comma operator would be better written as separate statements.

>[!tip]
>Avoid using the comma operator, except within _for loops_.

### Comma as a separator

>In C++, the comma symbol is often used as a separator, and these uses do not invoke the comma operator. Some examples of separator commas:

```cpp
void foo(int x, int y) // Separator comma used to separate parameters in function definition
{
    add(x, y); // Separator comma used to separate arguments in function call
    constexpr int z{ 3 }, w{ 5 }; // Separator comma used to separate multiple variables being defined on the same line (don't do this)
}
```

### The conditional operator (ternary operartor)

> Conditional operator `?:` also called ternary operator (takes 3 operands).
> The `?:` operator provides a shorthand method for doing a particular type of if-else statement.

Syntax:
`condition ? expression1 : expression2;`

```cpp
max = ((x > y) ? x : y);
```

```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
    int x { getValue() };
    int y { getValue() };
    int max { (x > y) ? x : y };
    std::cout << "The max of " << x <<" and " << y << " is " << max << ".\n";

    return 0;
}
```

### The conditional operator evaluates as part of an expression

### 🧠 What is the Conditional Operator?

Also known as the **ternary operator**, the conditional operator looks like this:

```cpp
(condition) ? value_if_true : value_if_false;
```

It's **an expression**, not a statement.

### 🔍 What’s the Main Point?

> **The conditional operator can be used anywhere an expression is allowed — even in constant expressions — but `if-else` cannot.**

### ✅ Example That Works

```cpp
constexpr bool inBigClassroom { false };
constexpr int classSize { inBigClassroom ? 30 : 20 };
```

Here:

- `inBigClassroom` is `false`
    
- So `classSize` becomes `20`
    
- The compiler evaluates it at **compile time** (because it's `constexpr`)
    
- And because this is all part of a single **expression**, it’s allowed.
    

✅ You can use this in **variable initialization**, especially with `constexpr`, which only accepts expressions known at compile time.

### ❌ Why If-Else Doesn’t Work Here

```cpp
if (inBigClassroom)
    constexpr int classSize { 30 };
else
    constexpr int classSize { 20 };

std::cout << classSize;
```

This fails because:

- `if-else` is a **statement**, not an expression.
    
- Variables defined **inside the `if` or `else` block** have **local scope** — they disappear outside those blocks.
    
- So when you try to use `classSize` later, it's **not visible**.

### 📘 Why This Matters

This is why the conditional operator is useful:

- It allows **conditional logic inside an expression**.
    
- You can use it where you **can't use statements**, like:
    
    - `constexpr` initializations
        
    - Function arguments
        
    - Initializer lists
        
    - Return values directly

### 🔁 Alternative: Using a Function

You _can_ use `if-else` inside a function:

```cpp
int getClassSize(bool inBigClassroom) {
    if (inBigClassroom)
        return 30;
    else
        return 20;
}
```

Then:

```cpp
const int classSize { getClassSize(false) };
```

>[!tip]
>Above example add extra code so prefer conditional operator is better here.

### Parenthesizing the conditional operator

>Because C++ prioritizes the evaluation of most operators above the evaluation of the conditional operator, it’s quite easy to write expressions using the conditional operator that don’t evaluate as expected.

```cpp
#include <iostream>

int main()
{
    int x { 2 };
    int y { 1 };
    int z { 10 - x > y ? x : y };
    std::cout << z;

    return 0;
}
```

You might expect this to evaluate as `10 - (x > y ? x : y)` (which would evaluate to `8`) but it actually evaluates as `(10 - x) > y ? x : y` (which evaluates to `2`).

>Here’s another example that exhibits a common mistake:

```cpp
#include <iostream>

int main()
{
    int x { 2 };
    std::cout << (x < 0) ? "negative" : "non-negative";

    return 0;
}
```
You might expect this to print `non-negative`, but it actually prints `0`.

#### Reason:
>Here’s what’s happening in the above example. First, `x < 0` evaluates to `false`. The partially evaluated expression is now `std::cout << false ? "negative" : "non-negative"`. Because `operator<<` has higher precedence than `operator?:`, this expression evaluates as if it were written as `(std::cout << false) ? "negative" : "non-negative"`. Thus `std::cout << false` is evaluated, which prints `0` (and returns `std::cout`).

To avoid such evaluation prioritization issues, the conditional operator should be parenthesized as follows:

> - Parenthesize the entire conditional operation (including operands) when used in a compound expression (an expression with other operators).
> - For readability, consider parenthesizing the condition if it contains any operators (other than the function call operator).

```cpp
return isStunned ? 0 : movesLeft;           // not used in compound expression, condition contains no operators
int z { (x > y) ? x : y };                  // not used in compound expression, condition contains operators
std::cout << (isAfternoon() ? "PM" : "AM"); // used in compound expression, condition contains no operators (function call operator excluded)
std::cout << ((x > y) ? x : y);             // used in compound expression, condition contains operators
```

### The type of the expressions must match or be convertible

To comply with C++’s type checking rules, one of the following must be true:

- The type of second and third operand must match.
- The compiler must be able to find a way to convert one or both of the second and third operands to matching types. The conversion rules the compiler uses are fairly complex and may yield surprising results in some cases.

```cpp
#include <iostream>

int main()
{
    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int

    std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double

    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range

    return 0;
}
```

Assuming 4 byte integers, the above prints:
1
2.2
4294967295

>In general, it’s okay to mix operands with fundamental types (excluding mixing signed and unsigned values). If either operand is not a fundamental type, it’s generally best to explicitly convert one or both operands to a matching type yourself so you know exactly what you’ll get.

If the compiler can’t find a way to convert the second and third operands to a matching type, a compile error will result:

```cpp
#include <iostream>

int main()
{
    constexpr int x{ 5 };
    std::cout << ((x != 5) ? x : "x is 5"); // compile error: compiler can't find common type for constexpr int and C-style string literal

    return 0;
}
```

In such cases, you can either do an explicit conversion, or use an if-else statement:

```cpp
#include <iostream>
#include <string>

int main()
{
    int x{ 5 }; // intentionally non-constexpr for this example

    // We can explicitly convert the types to match
    std::cout << ((x != 5) ? std::to_string(x) : std::string{"x is 5"}) << '\n';

    // Or use an if-else statement
    if (x != 5)
        std::cout << x << '\n';
    else
        std::cout << "x is 5" << '\n';

    return 0;
}
```

### So when should you use the conditional operator?

The conditional operator is most useful when doing one of the following:

- Initializing an object with one of two values.
- Assigning one of two values to an object.
- Passing one of two values to a function.
- Returning one of two values from a function.
- Printing one of two values.

Complicated expressions should generally avoid use of the conditional operator, as they tend to be error prone and hard to read.

>[!tip]
>Prefer to avoid the conditional operator in complicated expressions.

### Relational Operators

>**Relational operators** are operators that let you compare two values. There are 6 relational operators:

|Operator|Symbol|Form|Operation|
|---|---|---|---|
|Greater than|>|x > y|true if x is greater than y, false otherwise|
|Less than|<|x < y|true if x is less than y, false otherwise|
|Greater than or equals|>=|x >= y|true if x is greater than or equal to y, false otherwise|
|Less than or equals|<=|x <= y|true if x is less than or equal to y, false otherwise|
|Equality|==|x == y|true if x equals y, false otherwise|
|Inequality|!=|x != y|true if x does not equal y, false otherwise|
>Relational operators evaluate to boolean value.

>By default, conditions in an _if statement_ or _conditional operator_ (and a few other places) evaluate as Boolean values.

so instead of doing this:
```cpp
if (b1 == true) ...
```
Do this:
```cpp
if (b1) ...
```
Same For !=

>[!tip]
>Don’t add unnecessary == or != to conditions. It makes them harder to read without offering any additional value.

### Comparison of calculated floating point values can be problematic

```cpp
#include <iostream>

int main()
{
    constexpr double d1{ 100.0 - 99.99 }; // should equal 0.01 mathematically
    constexpr double d2{ 10.0 - 9.99 }; // should equal 0.01 mathematically

    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';

    return 0;
}
```
>You would expect `d1==d2` but it would print d1>d2.

>If you inspect the value of d1 and d2 in a debugger, you’d likely see that d1 = 0.010000000000005116 and d2 = 0.0099999999999997868. Both numbers are close to 0.01, but d1 is greater than, and d2 is less than.

>Comparing floating point values using any of relational operator is dangerous because floating point numbers are not precise. And rounding error may cause them to be slightly smaller or larger.

> When relational operators are used with floating point values they will produce reliable answer in most cases (when the value of operands is not similar.), otherwise in above example you can see the result could be any of them because they are similar.

#### 🧠 Core Idea

When you compare **floating-point values** that are **very close to each other**, the result may not be reliable due to **rounding errors** and the way floating-point arithmetic works in computers.

However:

> If your application doesn’t require perfect precision, and getting the comparison slightly wrong won’t break anything — **it's okay to use these comparisons**.

This is what the quote is saying: **"This is an application-specific decision."**

#### 🎮 Example: Space Invaders Game

Imagine a game like _Space Invaders_, and you're trying to detect if a **missile is below an alien**, like this:

```cpp
if (missile.y < alien.y) {
    // missile is below alien
}
```

This works fine when the missile and alien are far apart.

But when the two are **extremely close together**, due to floating-point imprecision (say, missile.y is `4.0000001` and alien.y is `4.0000000`), the comparison might give unexpected or inconsistent results:

- It may **falsely** report that the missile is not below
    
- Or that it is below when visually it looks like it’s the same height

If the objects are so close that the comparison might go either way, the result is still **visually acceptable**:

- The missile might look like a **near miss** or a **near hit**
    
- The player probably won’t even notice
    

So in that case:

> Using `<`, `>`, etc. directly on floating-point values **is acceptable**, even if it's not 100% precise.

>[!warning]
>Avoid using operator== and operator!= to compare floating point values if there is any chance those values have been calculated.

>There is one exception to above case, which is when we are comparing floating point literal. But so long as the number of significant digits in each literal doesnt not exceed the minimum precision for that type.
>Float has a minimum precision of 6 significant digits, and double has a minimum precision of 15 significant digits.

Example:

```cpp
if (someFcn() == 0.0) // okay if someFcn() returns 0.0 as a literal only
    // do something
```

>Instead of a literal, we can also compare a const or constexpr floating point variable that was initialized with a literal value:

```cpp
constexpr double gravity { 9.8 };
if (gravity == 9.8) // okay if gravity was initialized with a literal
    // we're on earth
```

>[!warning]
>It is mostly not safe to compare floating point literals of different types. For example, comparing `9.8f` to `9.8` will return false.

### How to compare floating point numbers?

>The most common method of doing floating point equality involves using a function that looks to see if two numbers are _almost_ the same. If they are “close enough”, then we call them equal. The value used to represent “close enough” is traditionally called **epsilon**. Epsilon is generally defined as a small positive number (e.g. 0.00000001, sometimes written 1e-8).

New developers often try to write their own “close enough” function like this:

```cpp
#include <cmath> // for std::abs()

// absEpsilon is an absolute value
bool approximatelyEqualAbs(double a, double b, double absEpsilon)
{
    // if the distance between a and b is less than or equal to absEpsilon, then a and b are "close enough"
    return std::abs(a - b) <= absEpsilon;
}
```

### Why this approach is **not ideal**:

Using a **fixed epsilon** (like `0.00001`) can lead to problems depending on the **scale of the numbers**:

#### 1. **Too strict for large values:**

```cpp
a = 10000.0, b = 10000.000001
std::abs(a - b) = 0.000001
```

This difference is tiny **relative** to 10,000, but `std::abs(a - b) > 0.00001` would return `false`, **incorrectly** saying they're not equal.

#### 2. **Too lenient for small values:**

```cpp
a = 0.0000001, b = 0.00000011
std::abs(a - b) = 0.00000001
```

This is a large difference **relative** to the small values. But if `absEpsilon = 0.00001`, the function would return `true`, saying they're equal — which is probably **not what you want**.

### The Core Problem:

A **fixed epsilon** (`0.00001`) doesn't adapt to the **magnitude** of the numbers being compared.

- It’s **too loose** for small numbers.
    
- It’s **too strict** for large numbers.

>This means every time we call this function, we have to pick an epsilon that’s appropriate for our inputs. If we know we’re going to have to scale epsilon in proportion to the magnitude of our inputs, we might as well modify the function to do that for us.

>[Donald Knuth](https://en.wikipedia.org/wiki/Donald_Knuth), a famous computer scientist, suggested the following method in his book “The Art of Computer Programming, Volume II: Seminumerical Algorithms (Addison-Wesley, 1969)”:

```cpp
#include <algorithm> // for std::max
#include <cmath>     // for std::abs

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
```

Explanation:

#### Step 1: Find the difference between the numbers

```cpp
std::abs(a - b)
```

#### Step 2: Find the **larger** of the two numbers (ignoring sign)

```cpp
std::max(std::abs(a), std::abs(b))
```

This helps us understand the **scale** of the numbers.

Example:

- `a = 1000`, `b = 1001` → max is 1001
    
- `a = 0.001`, `b = 0.0011` → max is 0.0011

#### Step 3: Multiply the larger number by a small value called `relEpsilon`

This gives us a small value that says:

> “This is how much error we’ll allow, depending on the size of the numbers.”

## 📌 So, why multiply by the max?

Because `relEpsilon` is a **percentage of the value** —  
and we want the allowed error to grow **with the size of the numbers**.

It's just like saying:

> "I'll allow up to 1% difference, no matter how big or small the numbers are."

>So its like I'll allow 1% of maxNumber error.

>[!Confusion]
>> Why are we multiplying the **max number** (of `a` and `b`) by `relEpsilon`?
>> 
>We do that because we want to allow a **percentage-based error**, and to be **safe**, we use the **bigger number** of the two.

>Note that while the approximatelyEqualRel() function will work for most cases, it is not perfect, especially as the numbers approach zero:

```cpp
#include <algorithm> // for std::max
#include <cmath>     // for std::abs
#include <iostream>

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}

int main()
{
    // a is really close to 1.0, but has rounding errors
    constexpr double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };

    constexpr double relEps { 1e-8 };
    constexpr double absEps { 1e-12 };

    std::cout << std::boolalpha; // print true or false instead of 1 or 0

    // First, let's compare a (almost 1.0) to 1.0.
    std::cout << approximatelyEqualRel(a, 1.0, relEps) << '\n';

    // Second, let's compare a-1.0 (almost 0.0) to 0.0
    std::cout << approximatelyEqualRel(a-1.0, 0.0, relEps) << '\n';

    return 0;
}
```

Perhaps surprisingly, this returns:

true
false

The second call didn’t perform as expected. The math simply breaks down close to zero.

>One way to avoid this is to use both an absolute epsilon (as we did in the first approach) and a relative epsilon (as we did in Knuth’s approach):

```cpp
// Return true if the difference between a and b is less than or equal to absEpsilon, or within relEpsilon percent of the larger of a and b
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if (std::abs(a - b) <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return approximatelyEqualRel(a, b, relEpsilon);
}
```

Here’s our previous code testing both algorithms:

```cpp
#include <algorithm> // for std::max
#include <cmath>     // for std::abs
#include <iostream>

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}

// Return true if the difference between a and b is less than or equal to absEpsilon, or within relEpsilon percent of the larger of a and b
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    if (std::abs(a - b) <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return approximatelyEqualRel(a, b, relEpsilon);
}

int main()
{
    // a is really close to 1.0, but has rounding errors
    constexpr double a{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 };

    constexpr double relEps { 1e-8 };
    constexpr double absEps { 1e-12 };

    std::cout << std::boolalpha; // print true or false instead of 1 or 0

    std::cout << approximatelyEqualRel(a, 1.0, relEps) << '\n';     // compare "almost 1.0" to 1.0
    std::cout << approximatelyEqualRel(a-1.0, 0.0, relEps) << '\n'; // compare "almost 0.0" to 0.0

    std::cout << approximatelyEqualAbsRel(a, 1.0, absEps, relEps) << '\n';     // compare "almost 1.0" to 1.0
    std::cout << approximatelyEqualAbsRel(a-1.0, 0.0, absEps, relEps) << '\n'; // compare "almost 0.0" to 0.0

    return 0;
}
```

>[!tip]
>We can also made aproximately function constexpr but it will run into error but its too early for that.
>[About That](https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/#:~:text=Making%20the%20approximatelyEqual%20functions%20constexpr%20Advanced)


### Logical Operators

>Logical operators provide us with the capability to test multiple conditions.

C++ has 3 logical operators:

|Operator|Symbol|Example Usage|Operation|
|---|---|---|---|
|Logical NOT|!|!x|true if x is false, or false if x is true|
|Logical AND|&&|x && y|true if x and y are both true, false otherwise|
|Logical OR|\||x \| y|true if either (or both) x or y are true, false otherwise|

>[!tip]
>One thing to be wary of is that _logical NOT_ has a very high level of precedence.

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 7 };

    if (!x > y)
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    return 0;
}
```

Output: 5 is greater than 7

But _x_ is not greater than _y_, so how is this possible? The answer is that because the _logical NOT_ operator has higher precedence than the _greater than_ operator, the expression `! x > y` actually evaluates as `(!x) > y`. Since _x_ is 5, !x evaluates to _0_, and `0 > y` is false, so the _else_ statement executes!

> Correct way would be to use paraenthesis to alter precedence.

>[!warning]
>`if (value == 0 || 1) // incorrect: if value is 0, or if 1`
>
>> When `1` is evaluated, it will implicitly convert to `bool` `true`. Thus this conditional will always evaluate to `true`.


### Short circuit evaluation

> And operator check multiple operands but if first condition evaluates to false then it will not check next condition and this is called short circuit evaluation and it is done primarily for optimization purposes.

> It is same for logical OR operator.

>[!warning]
>Short circuit evaluation may cause _Logical OR_ and _Logical AND_ to not evaluate the right operand. Avoid using expressions with side effects in conjunction with these operators.
>> ```cpp
>> if (x == 1 && ++y == 2)
   >  // do something

>[!tip]
>When mixing _logical AND_ and _logical OR_ in a single expression, explicitly parenthesize each operation to ensure they evaluate how you intend.
>
>> Because And operator has higher precedence than Logical OR operator so And operator will evaulate first so thats why.
>
>New programmers will often write expressions such as `value1 || value2 && value3`. Because _logical AND_ has higher precedence, this evaluates as `value1 || (value2 && value3)`, not `(value1 || value2) && value3`.

### De Morgan’s laws

>Many programmers also make the mistake of thinking that `!(x && y)` is the same thing as `!x && !y`. Unfortunately, you can not “distribute” the _logical NOT_ in that manner.

[De Morgan’s laws](https://en.wikipedia.org/wiki/De_Morgan%27s_laws) tell us how the _logical NOT_ should be distributed in these cases:

- `!(x && y)` is equivalent to `!x || !y`
- `!(x && y)` is equivalent to `!x || !y`

>In other words, when you distribute the _logical NOT_, you also need to flip _logical AND_ to _logical OR_, and vice-versa!

[This can sometimes be useful when trying to make complex expressions easier to read.](https://www.learncpp.com/cpp-tutorial/logical-operators/#:~:text=easier%20to%20read.-,For%20advanced%20readers,the%20value%20of%20!x%20%26%26%20!y.%20Thus%2C%20they%20are%20equivalent.,-Where%E2%80%99s%20the%20logical)

--- 
### Where’s the logical exclusive or (XOR) operator?

> C++ doesn’t provide an explicit _logical XOR_ operator (`operator^` is a bitwise XOR, not a logical XOR). Unlike _logical OR_ or _logical AND_, _logical XOR_ cannot be short circuit evaluated. Because of this, making a _logical XOR_ operator out of _logical OR_ and _logical AND_ operators is challenging.

>However, `operator!=` produces the same result as a logical XOR when given `bool` operands:


```cpp
if (a != b) ... // a XOR b, assuming a and b are bool
```

>If the operands are not of type `bool`, using `operator!=` to implement a logical XOR will not work as expected.

>If you need a form of _logical XOR_ that works with non-Boolean operands, you can static_cast your operands to bool:

```cpp
if (static_cast<bool>(a) != static_cast<bool>(b) != static_cast<bool>(c)) ... // a XOR b XOR c, for any type that can be converted to bool
```

However, this is a bit verbose. The following trick also works and is a bit more concise:

```cpp
if (!!a != !!b != !!c) // a XOR b XOR c, for any type that can be converted to bool
```

- The first time does the implicit conversion to `bool` and inverts the bool. The second time inverts the `bool` back to its original value.

>[!tip]
 `a != b` is true **only when one of them is true and the other is false**.
  That's **exactly the same** as logical XOR.

## 🔄 Extending XOR to 3 or more values

Now here’s the cool part:

```cpp
if (a != b != c)
```

Looks weird, right? But it works for `bool`.

### Why does it work?

Let’s say:

- `a = true`
    
- `b = false`
    
- `c = true`
    

#### Step-by-step:

```cpp
a != b   → true
true != c  → true != true → false
```

So `a != b != c` ends up checking if an **odd number of values are true**.

This works **only for bools**, because:

- Each `!=` returns a `bool`.
    
- The whole thing chains together like:
    
```cpp
((a != b) != c)
```

## ⚠️ Caution: Only for `bool`

If `a`, `b`, or `c` are **not bools**, this trick will **not behave as logical XOR**.

For example:

```cpp
int x = 3, y = 3, z = 4;
if (x != y != z)  // ❌ Not logical XOR here
```

This becomes:

```cpp
(x != y) → false (because 3 == 3)
false != 4 → true
```

Which is weird and **not meaningful** as XOR.

--- 
