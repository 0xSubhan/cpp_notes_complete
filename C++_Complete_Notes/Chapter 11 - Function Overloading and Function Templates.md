
### Function overloading

>**Function overloading** allows us to create multiple functions with the same name, so long as each identically named function has different parameter types (or the functions can be otherwise differentiated). Each function sharing a name (in the same scope) is called an **overloaded function** (sometimes called an **overload** for short).

To overload our `add()` function, we can simply declare another `add()` function that takes double parameters:

```cpp
double add(double x, double y)
{
    return x + y;
}
```

We now have two versions of `add()` in the same scope:

```cpp
int add(int x, int y) // integer version
{
    return x + y;
}

double add(double x, double y) // floating point version
{
    return x + y;
}

int main()
{
    return 0;
}
```

The above program will compile. Although you might expect these functions to result in a naming conflict, that is not the case here. Because the parameter types of these functions differ, the compiler is able to differentiate these functions, and will treat them as separate functions that just happen to share a name.

>[!Key Insight]
>Functions can be overloaded so long as each overloaded function can be differentiated by the compiler. If an overloaded function can not be differentiated, a compile error will result.

---
### Introduction to overload resolution

>Additionally, when a function call is made to a function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function call. This is called **overload resolution**.

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

double add(double x, double y)
{
    return x + y;
}

int main()
{
    std::cout << add(1, 2); // calls add(int, int)
    std::cout << '\n';
    std::cout << add(1.2, 3.4); // calls add(double, double)

    return 0;
}
```

---
### Making it compile

In order for a program using overloaded functions to compile, two things have to be true:

1. Each overloaded function has to be differentiated from the others. (We will talk about it in a bit).
2. When you call a function that has multiple overloaded versions, the compiler **must be able to choose exactly one matching function** based on the arguments **without ambiguity or confusion**.

>[!warning]
>If an overloaded function is not differentiated, or if a function call to an overloaded function can not be resolved to an overloaded function, then a compile error will result.

>[!Best Practice]
>Use function overloading to make your program simpler.

---
### How overloaded functions are differentiated

|Function property|Used for differentiation|Notes|
|---|---|---|
|Number of parameters|Yes||
|Type of parameters|Yes|Excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses.|
|Return type|No|
For member functions, additional function level qualifiers are also considered:

1. const 
2. Reference

---
### Overloading based on number of parameters

>An overloaded function is differentiated so long as each overloaded function has a different number of parameters

---
### Overloading based on type of parameters

>A function can also be differentiated so long as each overloaded function’s list of parameter types is distinct. For example, all of the following overloads are differentiated:

```cpp
int add(int x, int y); // integer version
double add(double x, double y); // floating point version
double add(int x, double y); // mixed version
double add(double x, int y); // mixed version
```

Because type aliases (or typedefs) are not distinct types, overloaded functions using type aliases are not distinct from overloads using the aliased type. For example, all of the following overloads are not differentiated (and will result in a compile error):

```cpp
typedef int Height; // typedef
using Age = int; // type alias

void print(int value);
void print(Age value); // not differentiated from print(int)
void print(Height value); // not differentiated from print(int)
```

>For parameters passed by value, the const qualifier is also not considered. Therefore, the following functions are not considered to be differentiated:

```cpp
void print(int);
void print(const int); // not differentiated from print(int)
```

---
### The return type of a function is not considered for differentiation

A function’s return type is not considered when differentiating overloaded functions.

Consider the case where you want to write a function that returns a random number, but you need a version that will return an int, and another version that will return a double. You might be tempted to do this:

```cpp
int getRandomValue();
double getRandomValue();
```

Error: error C2556: 'double getRandomValue(void)': overloaded function differs only by return type from 'int getRandomValue(void)'

>This makes sense. If you were the compiler, and you saw this statement:

```cpp
getRandomValue();
```

Which of the two overloaded functions would you call? It’s not clear.

---
### Type signature

>[!Important]
>The following question was asked in an interview as a basic question.
>

>A function’s **type signature** (generally called a **signature**) is defined as the parts of the function header that are used for differentiation of the function. In C++, this includes the function name, number of parameters, parameter type, and function-level qualifiers. It notably does _not_ include the return type.

>[!As an aside]
>When the compiler compiles a function, it performs **name mangling**, which means the compiled name of the function is altered (“mangled”) based on various criteria, such as the number and type of parameters, so that the linker has unique names to work with.
For example, a function with prototype `int fcn()` might compile to mangled name `__fcn_v`, whereas `int fcn(int)` might compile to mangled name `__fcn_i`. So while in the source code, the two overloaded functions share the name `fcn()`, in compiled code, the mangled names are unique (`__fcn_v` vs `__fcn_i`).
There is no standardization on how names should be mangled, so different compilers will produce different mangled names.

---
>[!Warning]
>If an overloaded function is not properly differentiated from the other overloads of the same name, then the compiler will issue a compile error.

When any function call is made, the compiler must also ensure that a matching function declaration can be found.

### Overloaded resolution

>With non-overloaded functions (functions with unique names), there is only one function that can potentially match a function call. That function either matches (or can be made to match after type conversions are applied), or it doesn’t (and a compile error results). With overloaded functions, there can be many functions that can potentially match a function call. Since a function call can only resolve to one of them, the compiler has to determine which overloaded function is the best match. The process of matching function calls to a specific overloaded function is called **overload resolution**.

In simple cases where the type of the function arguments and type of the function parameters match exactly, this is (usually) straightforward:

```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print(5); // 5 is an int, so this matches print(int)
     print(6.7); // 6.7 is a double, so this matches print(double)

     return 0;
}
```

But what happens in cases where the argument types in the function call don’t exactly match the parameter types in any of the overloaded functions? For example:

```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print('a'); // char does not match int or double, so what happens?
     print(5L); // long does not match int or double, so what happens?

     return 0;
}
```

Just because there is no exact match here doesn’t mean a match can’t be found -- after all, a `char` or `long` can be implicitly type converted to an `int` or a `double`. But which is the best conversion to make in each case?

---
### Resolving overloaded function calls

#### 🧠 **What’s going on when you call an overloaded function?**

When you write something like:

```cpp
func(10);  // Which version of func should be called?
```

And suppose you have multiple overloads:

```cpp
void func(int); void func(double); void func(char);
```

The **compiler’s job** is to figure out which `func` matches best with the argument `10`.

#### 🛠 How does the compiler do that?

The compiler goes through a **multi-step matching process**, where it tries **different kinds of type conversions** in a specific order. At each step:

1. It **applies a type conversion** (e.g., exact match, promotion, standard conversion, user-defined conversion, etc.).
    
2. It checks **if any of the overloaded functions match** using the converted arguments.
    
3. Then one of these three things can happen:
    

#### ✅ Possible outcomes at any step:

1. **No matching functions** →  
    It goes to the **next step** to try another set of conversions.
    
2. **One matching function** →  
    The compiler says: _“Great! I found the best match.”_  
    It **stops** here and uses this function.
    
3. **More than one matching function** →  
    Now it’s **ambiguous**. The compiler doesn’t know which one to pick.  
    So it gives a **compile error: ambiguous function call**.
    

#### 🛑 Final case:

If the compiler reaches the **end of all conversion steps** and **still hasn’t found any match**, it gives a **compile error** saying:

> "No matching overloaded function could be found."

#### 🧩 Summary (in plain English):

- The compiler doesn’t just pick a function randomly.
    
- It **tries different levels of type conversion** to match your arguments to the function parameters.
    
- At each level, it checks if there’s **a clear best match**.
    
- If it **finds one**, it uses it. If there are **none**, it keeps trying. (different conversions)
    
- If it **finds more than one equally good**, it complains (ambiguous call).
    
- If **none work at all**, it says: _“I don’t know what to call.”_

>[!Note]
>**Ambiguous** : means not clear.

---
### The argument matching sequence

#### Step 1

>Step 1) The compiler tries to find an exact match. This happens in two phases. First, the compiler will see if there is an overloaded function where the type of the arguments in the function call exactly matches the type of the parameters in the overloaded functions. For example:

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(0);   // exact match with foo(int)
    foo(3.4); // exact match with foo(double)

    return 0;
}
```

>[!Note]
>If exact match of overloaded function is found by compiler then no conversion will take place.

>Second, the compiler will apply a number of trivial conversions to the arguments in the function call. The **trivial conversions** are a set of specific conversion rules that will modify types (without modifying the value) for purposes of finding a match. These include:

- lvalue to rvalue conversions
- qualification conversions (e.g. non-const to const)
- non-reference to reference conversions

**lvalue-to-rvalue conversion**:  An **lvalue-to-rvalue conversion** is the process of obtaining the value stored in an object (lvalue) so it can be used in a context that requires a value (rvalue).

```cpp
int x = 5;
int y = x; // ← this uses an lvalue-to-rvalue conversion
```
- `x` is an **lvalue** (it has a memory address and a name).
    
- But to **assign its value to `y`**, you need the **value inside `x`**.
    
- So the compiler applies an **lvalue-to-rvalue conversion** to get the `5` from `x`.

--> This is how it is used in function overloading:

```cpp
#include <iostream>

void foo(int) {
    std::cout << "foo(int)\n";
}

void foo(const int&) {
    std::cout << "foo(const int&)\n";
}

int main() {
    int x { 1 };
    foo(x); // Should call foo(int)
}

```

##### Why It's Ambiguous

The issue is that both function overloads are equally good matches for the arguments:

1. foo(int) - Takes by value

2. foo(const int&) - Takes by const reference

When you call foo(x) with an int x, the compiler can't decide between:

- Converting x to int (by-value parameter)

- Converting x to const int& (const reference parameter)

Both conversions have the same "cost" in C++ overload resolution, making it ambiguous.

```cpp
void foo(const int)
{
}

void foo(const double&) // double& is a reference to a double
{
}

int main()
{
    int x { 1 };
    foo(x); // x trivially converted from int to const int

    double d { 2.3 };
    foo(d); // d trivially converted from double to const double& (non-ref to ref conversion)

    return 0;
}
```

>In the above example, we’ve called `foo(x)`, where `x` is an `int`. The compiler will trivially convert `x` from an `int` into a `const int`, which then matches `foo(const int)`. We’ve also called `foo(d)`, where `d` is a `double`. The compiler will trivially convert `d` from a `double` to a `const double&`, which then matches `foo(const double&)`.

#### Step 2

>Step 2) If no exact match is found, the compiler tries to find a match by applying numeric promotion to the argument(s). In lesson ([10.1 -- Implicit type conversion](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/)), we covered how certain narrow integral and floating point types can be automatically promoted to wider types, such as `int` or `double`. If, after numeric promotion, a match is found, the function call is resolved.

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo('a');  // promoted to match foo(int)
    foo(true); // promoted to match foo(int)
    foo(4.5f); // promoted to match foo(double)

    return 0;
}
```

For `foo('a')`, because an exact match for `foo(char)` could not be found in the prior step, the compiler promotes the char `'a'` to an `int`, and looks for a match. This matches `foo(int)`, so the function call resolves to `foo(int)`.

#### Step 3

>If no match is found via numeric promotion, the compiler tries to find a match by applying numeric conversions ([10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)) to the arguments.

```cpp
#include <string> // for std::string

void foo(double)
{
}

void foo(std::string)
{
}

int main()
{
    foo('a'); // 'a' converted to match foo(double)

    return 0;
}
```

In this case, because there is no `foo(char)` (exact match), and no `foo(int)` (promotion match), the `'a'` is numerically converted to a double and matched with `foo(double)`.

>[!key Insight]
>Matches made by applying numeric promotions take precedence over any matches made by applying numeric conversions.

#### Step 4

>If no match is found via numeric conversion, the compiler tries to find a match through any user-defined conversions. Although we haven’t covered user-defined conversions yet, certain types (e.g. classes) can define conversions to other types that can be implicitly invoked. Here’s an example, just to illustrate the point:

```cpp
// We haven't covered classes yet, so don't worry if this doesn't make sense
class X // this defines a new type called X
{
public:
    operator int() { return 0; } // Here's a user-defined conversion from X to int
};

void foo(int)
{
}

void foo(double)
{
}

int main()
{
    X x; // Here, we're creating an object of type X (named x)
    foo(x); // x is converted to type int using the user-defined conversion from X to int

    return 0;
}
```

In this example, the compiler will first check whether an exact match to `foo(X)` exists. We haven’t defined one. Next the compiler will check whether `x` can be numerically promoted, which it can’t. The compiler will then check if `x` can be numerically converted, which it also can’t. Finally, the compiler will then look for any user-defined conversions. Because we’ve defined a user-defined conversion from `X` to `int`, the compiler will convert `X` to an `int` to match `foo(int)`.

After applying a user-defined conversion, the compiler may apply additional implicit promotions or conversions to find a match. So if our user-defined conversion had been to type `char` instead of `int`, the compiler would have used the user-defined conversion to `char` and then promoted the result into an `int` to match.

#### Step 5

>If no match is found via user-defined conversion, the compiler will look for a matching function that uses ellipsis. (its too early to learn these so skip it for now)

#### Step 6

> If no matches have been found by this point, the compiler gives up and will issue a compile error about not being able to find a matching function.

---

With overloaded functions, there is a third possible outcome: an `ambiguous match` may be found. An **ambiguous match** occurs when the compiler finds two or more functions that can be made to match in the same step. When this occurs, the compiler will stop matching and issue a compile error stating that it has found an ambiguous function call.

Since every overloaded function must be differentiated in order to compile, you might be wondering how it is possible that a function call could result in more than one match. Let’s take a look at an example that illustrates this:

```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(5L); // 5L is type long

    return 0;
}
```

Since literal `5L` is of type `long`, the compiler will first look to see if it can find an exact match for `foo(long)`, but it will not find one. Next, the compiler will try numeric promotion, but values of type `long` can’t be promoted, so there is no match here either.

Following that, the compiler will try to find a match by applying numeric conversions to the `long` argument. In the process of checking all the numeric conversion rules, the compiler will find two potential matches. If the `long` argument is numerically converted into an `int`, then the function call will match `foo(int)`. If the `long` argument is instead converted into a `double`, then it will match `foo(double)` instead. Since two possible matches via numeric conversion have been found, the function call is considered ambiguous.

Another Example:

```cpp
void foo(unsigned int)
{
}

void foo(float)
{
}

int main()
{
    foo(0);       // int can be numerically converted to unsigned int or to float
    foo(3.14159); // double can be numerically converted to unsigned int or to float

    return 0;
}
```

Although you might expect `0` to resolve to `foo(unsigned int)` and `3.14159` to resolve to `foo(float)`, both of these calls result in an ambiguous match. The `int` value `0` can be numerically converted to either an `unsigned int` or a `float`, so either overload matches equally well, and the result is an ambiguous function call.

The same applies for the conversion of a `double` to either a `float` or `unsigned int`. Both are numeric conversions, so either overload matches equally well, and the result is again ambiguous.

---
### Resolving ambiguous matches

Because ambiguous matches are a compile-time error, an ambiguous match needs to be disambiguated before your program will compile. There are a few ways to resolve ambiguous matches:

1. Often, the best way is simply to define a new overloaded function that takes parameters of exactly the type you are trying to call the function with. Then C++ will be able to find an exact match for the function call.
2. Alternatively, explicitly cast the ambiguous argument(s) to match the type of the function you want to call. For example, to have `foo(0)` match `foo(unsigned int)` in the above example, you would do this:

```cpp
int x{ 0 };
foo(static_cast<unsigned int>(x)); // will call foo(unsigned int)
```

3. If your argument is a literal, you can use the literal suffix to ensure your literal is interpreted as the correct type:

```cpp
foo(0u); // will call foo(unsigned int) since 'u' suffix is unsigned int, so this is now an exact match
```

---
### Matching for functions with multiple arguments

If there are multiple arguments, the compiler applies the matching rules to each argument in turn. The function chosen is the one for which each argument matches at least as well as all the other functions, with at least one argument matching better than all the other functions. In other words, the function chosen must provide a better match than all the other candidate functions for at least one parameter, and no worse for all of the other parameters.

In the case that such a function is found, it is clearly and unambiguously the best choice. If no such function can be found, the call will be considered ambiguous (or a non-match).

For example:

```cpp
#include <iostream>

void print(char, int)
{
	std::cout << 'a' << '\n';
}

void print(char, double)
{
	std::cout << 'b' << '\n';
}

void print(char, float)
{
	std::cout << 'c' << '\n';
}

int main()
{
	print('x', 'a');

	return 0;
}
```

In the above program, all functions match the first argument exactly. However, the top function matches the second parameter via promotion, whereas the other functions require a conversion. Therefore, `print(char, int)` is unambiguously the best match.

>[!note]
>So Numeric promotion takes precedence here!

---
### Deleting functions

>In some cases, it is possible to write functions that don’t behave as desired when called with values of certain types.

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(5);    // okay: prints 5
    printInt('a');  // prints 97 -- does this make sense?
    printInt(true); // print 1 -- does this make sense?

    return 0;
}
```

Let’s assume we don’t think it makes sense to call `printInt()` with a value of type `char` or `bool`. What can we do?

---
### Deleting a function using the `=delete` specifier

>In cases where we have a function that we explicitly do not want to be callable, we can define that function as deleted by using the **= delete** specifier. If the compiler matches a function call to a deleted function, compilation will be halted with a compile error.

```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // calls to this function will halt compilation
void printInt(bool) = delete; // calls to this function will halt compilation

int main()
{
    printInt(97);   // okay

    printInt('a');  // compile error: function deleted
    printInt(true); // compile error: function deleted

    printInt(5.0);  // compile error: ambiguous match

    return 0;
}
```

Let’s take a quick look at some of these. First, `printInt('a')` is a direct match for `printInt(char)`, which is deleted. The compiler thus produces a compilation error. `printInt(true)` is a direct match for `printInt(bool)`, which is deleted, and thus also produces a compilation error.

#### 👇 Given:

```cpp
void printInt(int x);          // ✅ valid function
void printInt(char) = delete; // ❌ explicitly disabled
void printInt(bool) = delete; // ❌ explicitly disabled
```

And you call:

```cpp
 printInt(5.0); // 5.0 is a `double`
```

#### 🧠 What happens?

#### 🧭 Step 1: Exact Match?

Is there a function `printInt(double)`?

- ❌ **No exact match**
    

So, the compiler tries to find the **best match** using **standard conversions**.

#### 🔎 Step 2: What can `double` convert to?

|Function|Conversion type from `double`|Deleted?|
|---|---|---|
|`printInt(int)`|double → int (standard conversion)|❌ No|
|`printInt(char)`|double → char (standard conversion)|✅ Yes|
|`printInt(bool)`|double → bool (standard conversion)|✅ Yes|

All three are **viable** candidates from the compiler's perspective in overload resolution.

BUT:

- Even though some functions are **deleted**, they are **still considered** during overload resolution.
    
- If a deleted function is considered a **better match**, even though it can’t be called, it still **blocks** the other candidates.

#### 💥 Step 3: Why is this **ambiguous**?

- `double → int`, `double → char`, and `double → bool` are **all standard conversions**.
    
- **No conversion is clearly better** than the others. (Important insight)
    
- So the compiler **can't decide** which function is the best match.
    

Now, even though `char` and `bool` overloads are deleted, they **still participate** in overload resolution.

So the compiler ends up with:

> Multiple viable candidates — some deleted — but no unambiguously better one.

➡️ Result: **Ambiguous match** → **Compile-time error**.

#### 🧠 Important Rule:

> 🔴 **Deleted functions participate in overload resolution**, but if the compiler ends up choosing a deleted function, or if one blocks another due to being a better match, it results in an error.

This makes `= delete` a powerful tool for **disabling certain implicit conversions** while still allowing specific overloads.

Let’s walk through a **clear, minimal example** of:

> 🔴 **A deleted function that participates in overload resolution and blocks a valid one**, resulting in a **compile-time error**.

#### 🧪 **Example Code**

```cpp
#include <iostream>

void print(int) {
    std::cout << "int version\n";
}

void print(double) = delete; // prevent accidental usage of double

```

#### 🤔 What happens here?

Now call:

```cpp
int main() {
    print(3.5); // double literal
}

```

#### 🔎 Breakdown:

- `3.5` is a `double`.
    
- There is **no exact match** for `print(double)` — but we do have one, it's **deleted**.
    
- The other candidate is:
    
    - `print(int)` — which requires **narrowing conversion**: `double → int`.
        

#### 🚨 So now what?

- Both `print(double)` and `print(int)` are **viable** overloads.
    
- But:
    
    - The deleted function `print(double)` is **a better match** (no conversion).
        
- However, it’s **deleted**, so the compiler **cannot choose it**.
    
- And it **does not fall back to `print(int)`** — because `print(double)` is still considered a better match in overload resolution.
    

#### 💥 Result:


```cpp
error: use of deleted function ‘void print(double)’
```

Even though `print(int)` exists and could technically be used, the compiler says:

> "Sorry, the better match is deleted, and I'm not allowed to ignore that."

#### ✅ Moral of the story:

> A deleted function can **block overloads** that would otherwise work, simply by being a better match.

This makes `= delete` useful for **explicitly disabling certain types**, but you must be careful — because it can cause **surprising errors** if not designed thoughtfully.

>[!Key insight]
>`= delete` means “I forbid this”, not “this doesn’t exist”.
>Deleted function participate in all stages of function overload resolution (not just in the exact match stage). If a deleted function is selected, then a compilation error results.

---
### Advance Technique

#### 🧠 **What is this technique?**

> A way to **delete all overloads** except for **one specific type**, using a **deleted function template**.

It ensures that **only an exact type match** (like `int`) can be passed to a function — **all other types will cause a compile-time error**, even if they are convertible to `int`.

## ✅ **How it works**

### 🔹 The exact match:

```cpp
void printInt(int x)
{
    std::cout << x << '\n';
}

```

This regular function handles the exact case where the argument is `int`.

#### 🔹 The deleted catch-all template:

```cpp
template <typename T>
void printInt(T x) = delete;
```

This is a **function template**, and it will match **any type that doesn't match an exact overload** — like `char`, `bool`, `float`, etc.

But since this template is **`= delete`**, if the compiler tries to use it, it will **immediately produce a compile-time error**.

#### 🧪 **Example in Action**

```cpp
printInt(97);    // ✅ int — matches the non-template version → compiles
printInt('a');   // ❌ char — no exact match, matches deleted template → error
printInt(true);  // ❌ bool — no exact match, matches deleted template → error
```

#### 🛠️ **Why use this technique?**

This gives you **precise control** over what argument types are allowed:

- Prevents accidental implicit conversions (e.g., `char → int`, `bool → int`)
    
- Avoids needing to manually `= delete` many overloads
    
- Makes errors **explicit and intentional** for unsupported types
    

#### ⚠️ **Without this technique:**

You might write many individual deletions:

```cpp
void printInt(char) = delete;
void printInt(bool) = delete;
void printInt(float) = delete;
void printInt(double) = delete;
// ... tedious and error-prone
```

Instead, with one line:

```cpp
template <typename T>
void printInt(T) = delete;
```

You delete **everything else** not exactly matched.

---
### Default arguments

>A **default argument** is a default value provided for a function parameter. For example:

```cpp
#include <iostream>

void print(int x, int y=4) // 4 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(1, 2); // y will use user-supplied argument 2
    print(3); // y will use default argument 4, as if we had called print(3, 4)

    return 0;
}
```

x: 1
y: 2
x: 3
y: 4

In the first function call, the caller supplied explicit arguments for both parameters, so those argument values are used. In the second function call, the caller omitted the second argument, so the default value of `4` was used.

>[!Note]
>Note that you must use the equals sign to specify a default argument. Using parenthesis or brace initialization won’t work:

>Perhaps surprisingly, default arguments are handled by the compiler at the call site. In the above example, when the compiler sees `print(3)`, it will rewrite this function call as `print(3, 4)`, so that the number of arguments matches the number of parameters. The rewritten function call then works as per usual.

>[!Key Insight]
>Default arguments are inserted by the compiler at site of the function call.

Default arguments are frequently used in C++, and you’ll see them a lot in code you encounter (and in future lessons).

---
### When to use default arguments

>Default arguments are an excellent option when a function needs a value that has a reasonable default value, but for which you want to let the caller override if they wish.

```cpp
int rollDie(int sides=6);
void openLogFile(std::string filename="default.log");
```

> **Default arguments** allow you to add new parameters to a function **without breaking old code** that uses that function.

#### 📌 The Problem Without Default Arguments

Imagine you have this function:

```cpp
void greet(std::string name) {
    std::cout << "Hello, " << name << '\n';
}
```

And it's been used in many places:

```cpp
greet("Alice");
greet("Bob");
```

Now, you decide to **add a new parameter**:

```cpp
void greet(std::string name, std::string title);
```

Now all existing calls like `greet("Alice")` break with a compile error:

```vbnet
error: too few arguments to function 'greet'
```

👉 That means you'd have to go back and update **every existing call** to include a second argument — which could be **dozens or hundreds of places**.

#### ✅ The Solution: Use a Default Argument

Instead, write it like this:

```cpp
void greet(std::string name, std::string title = "Friend") {
    std::cout << "Hello, " << title << " " << name << '\n';
}
```

Now you get the best of both worlds:

- Existing calls like `greet("Alice")` still work — they use `"Friend"` as the default title.
    
- New calls like `greet("Alice", "Dr.")` can provide the new argument explicitly.

---
### Multiple default arguments

A function can have multiple parameters with default arguments:

```cpp
#include <iostream>

void print(int x=10, int y=20, int z=30)
{
    std::cout << "Values: " << x << " " << y << " " << z << '\n';
}

int main()
{
    print(1, 2, 3); // all explicit arguments
    print(1, 2); // rightmost argument defaulted
    print(1); // two rightmost arguments defaulted
    print(); // all arguments defaulted

    return 0;
}
```

Values: 1 2 3
Values: 1 2 30
Values: 1 20 30
Values: 10 20 30

>C++ does not (as of C++23) support a function call syntax such as `print(,,3)` (as a way to provide an explicit value for `z` while using the default arguments for `x` and `y`. This has three major consequences:

1. In a function call, any explicitly provided arguments must be the leftmost arguments (arguments with defaults cannot be skipped).

```cpp
void print(std::string_view sv="Hello", double d=10.0);

int main()
{
    print();           // okay: both arguments defaulted
    print("Macaroni"); // okay: d defaults to 10.0
    print(20.0);       // error: does not match above function (cannot skip argument for sv)

    return 0;
}
```

2. If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default arguments.

```cpp
void print(int x=10, int y); // not allowed
```

3. If more than one parameter has a default argument, the leftmost parameter should be the one most likely to be explicitly set by the user.

>[!Rule]
>If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default arguments.

---
### Default arguments can not be redeclared, and must be declared before use

>Once declared, a default argument can not be redeclared in the same translation unit. That means for a function with a forward declaration and a function definition, the default argument can be declared in either the forward declaration or the function definition, but not both.

```cpp
#include <iostream>

void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // compile error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

The default argument must also be declared in the translation unit before it can be used:

#### 🧠 What does this rule mean?

> The compiler must **see** the default argument **before** any call to the function that relies on it.

In other words:

- You **must declare the default value** before using the function **without that argument**.

```cpp
#include <iostream>

void print(int x, int y); // forward declaration, no default argument

int main()
{
    print(3); // compile error: default argument for y hasn't been defined yet

    return 0;
}

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

The best practice is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by other files and included before use (particularly if it’s in a header file).

in foo.h:

```cpp
#ifndef FOO_H
#define FOO_H
void print(int x, int y=4);
#endif
```

in main.cpp:

```cpp
#include "foo.h"
#include <iostream>

void print(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(5);

    return 0;
}
```

Note that in the above example, we’re able to use the default argument for function `print()` because _main.cpp_ `#includes` _foo.h_, which has the forward declaration that defines the default argument.

>[!Best Practice]
>If the function has a forward declaration (especially one in a header file), put the default argument there. Otherwise, put the default argument in the function definition.

---
### Default arguments and function overloading

Functions with default arguments may be overloaded. For example, the following is allowed:

```cpp
#include <iostream>
#include <string_view>

void print(std::string_view s)
{
    std::cout << s << '\n';
}

void print(char c = ' ')
{
    std::cout << c << '\n';
}

int main()
{
    print("Hello, world"); // resolves to print(std::string_view)
    print('a');            // resolves to print(char)
    print();               // resolves to print(char)

    return 0;
}
```

The function call to `print()` actually calls `print(char)`, which acts as if the user had explicitly called `print(' ')`.

Now consider this case:

```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)
```

Default values are not part of a function’s signature, so these function declarations are differentiated overloads.

#### ✅ This means:

Two functions **can’t differ only by default arguments**.

Let’s look at an example to make this concrete:

#### ❌ **Invalid — ambiguous overloads**

```cpp
void greet(int x);
void greet(int x = 5); // ❌ Error: redefinition — same signature
```

Even though the second one has a default value, the **signature** of both is:

```cpp
greet(int)
```

Default values are **not considered part of the signature**, so this is a **duplicate** declaration — and causes a **compiler error**.

---
### Default arguments can lead to ambiguous matches

Default arguments can easily lead to ambiguous function calls:

```cpp
void foo(int x = 0)
{
}

void foo(double d = 0.0)
{
}

int main()
{
    foo(); // ambiguous function call

    return 0;
}
```

In this example, the compiler can’t tell whether `foo()` should resolve to `foo(0)` or `foo(0.0)`.

Here’s a slightly more complex example:

```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)

int main()
{
    print(1, 2);   // will resolve to print(int, int)
    print(1, 2.5); // will resolve to print(int, double)
    print(1);      // ambiguous function call

    return 0;
}
```

For the call `print(1)`, the compiler is unable to tell whether this resolve to `print(int)`, `print(int, int)`, or `print(int, double)`.

In the case where we mean to call `print(int, int)` or `print(int, double)` we can always explicitly specify the second parameter. But what if we want to call `print(int)`? It’s not obvious how we can do so.

>[!Note]
>Default arguments don’t work for functions called through function pointers

---
### Function Templates

Let’s say you wanted to write a function to calculate the maximum of two numbers. You might do so like this:

```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
```

While the caller can pass different values into the function, the type of the parameters is fixed, so the caller can only pass in `int` values. That means this function really only works well for integers (and types that can be promoted to `int`).

So what happens later when you want to find the max of two `double` values? Because C++ requires us to specify the type of all function parameters, the solution is to create a new overloaded version of `max` with parameters of type `double`:

```cpp
double max(double x, double y)
{
    return (x < y) ? y: x;
}
```

Note that the code for the implementation of the double version of `max` is exactly the same as for the int version of `max`! In fact, this implementation works for many different types: including `int`, `double`, `long`, `long double`, and even new types that you’ve created yourself (which we’ll cover how to do in future lessons).

Having to create overloaded functions with the same implementation for each set of parameter types we want to support is a maintenance headache, a recipe for errors, and a clear violation of the DRY (don’t repeat yourself) principle. There’s a less-obvious challenge here as well: a programmer who wishes to use the `max` function may wish to call it with an argument type that the author of the `max` did not anticipate (and thus did not write an overloaded function for).

What we are really missing is some way to write a single version of `max` that can work with arguments of any type (even types that may not have been anticipated when the code for `max` was written). Normal functions are simply not up to the task here. Fortunately, C++ supports another feature that was designed specifically to solve this kind of problem.

Welcome to the world of C++ templates.

--- 
### Introduction to c++ templates

In C++, the template system was designed to simplify the process of creating functions (or classes) that are able to work with different data types.

Instead of manually creating a bunch of mostly-identical functions or classes (one for each set of different types), we instead create a single _template_. Just like a normal definition, a **template** definition describes what a function or class looks like. Unlike a normal definition (where all types must be specified), in a template we can use one or more placeholder types. A placeholder type represents some type that is not known at the time the template is defined, but that will be provided later (when the template is used).

Once a template is defined, the compiler can use the template to generate as many overloaded functions (or classes) as needed, each using different actual types!

The end result is the same -- we end up with a bunch of mostly-identical functions or classes (one for each set of different types). But we only have to create and maintain a single template, and the compiler does all the hard work to create the rest for us.

>[!Key Insight]
>The compiler can use a single template to generate a family of related functions or classes, each using a different set of actual types.

>[!Analogy]
>Because the concept behind templates can be hard to describe in words, let’s try an analogy.
If you were to look up the word “template” in the dictionary, you’d find a definition that was similar to the following: “a template is a model that serves as a pattern for creating similar objects”. One type of template that is very easy to understand is that of a stencil. A stencil is a thin piece of material (such as a piece of cardboard or plastic) with a shape cut out of it (e.g. a happy face). By placing the stencil on top of another object, then spraying paint through the hole, you can very quickly replicate the cut-out shape. The stencil itself only needs to be created once, and then it can be reused as many times as desired, to create the cut out shape in as many different colors as you like. Even better, the color of a shape made with the stencil doesn’t have to be determined until the stencil is actually used.
A template is essentially a stencil for creating functions or classes. We create the template (our stencil) once, 
and then we can use it as many times as needed, to stencil out a function or class for a specific set of actual types. Those actual types don’t need to be determined until the template is actually used.

You don’t have to know **in advance** all the possible types someone might want to use with your code. That makes template code extremely flexible and reusable.

---
### Function Templates

>A **function template** is a function-like definition that is used to generate one or more overloaded functions, each with a different set of actual types. This is what will allow us to create functions that can work with many different types. The initial function template that is used to generate other functions is called the **primary template**, and the functions generated from the primary template are called **instantiated functions**.

When we create a primary function template, we use **placeholder types** (technically called **type template parameters**, informally called **template types**) for any parameter types, return types, or types used in the function body that we want to be specified later, by the user of the template.

---
### Creating a `max()` function template

Here’s the `int` version of `max()` again:

```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
}
```

Note that we use type `int` three times in this function: once for parameter `x`, once for parameter `y`, and once for the return type of the function.

To create a function template for `max()`, we’re going to do two things. First, we’re going to replace any actual types that we want to be specified later with type template parameters. In this case, because we have only one type that needs replacing (`int`), we only need one type template parameter (which we’ll call `T`):

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

Here’s our new function that uses a single template type, where all occurrences of actual type `int` have been replaced with type template parameter `T` :

```cpp
T max(T x, T y) // won't compile because we haven't defined T
{
    return (x < y) ? y : x;
}
```

This is a good start -- however, it won’t compile because the compiler doesn’t know what `T` is! And this is still a normal function, not a function template.

Second, we’re going to tell the compiler that this is a template, and that `T` is a type template parameter that is a placeholder for any type. Both of these are done using a **template parameter declaration**, which defines any template parameters that will be subsequently used. The scope of a template parameter declaration is strictly limited to the function template (or class template) that follows. Therefore, each function template or class template needs its own template parameter declaration.

```cpp
template <typename T> // this is the template parameter declaration defining T as a type template parameter
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}
```

In our template parameter declaration, we start with the keyword `template`, which tells the compiler that we’re creating a template. Next, we specify all of the template parameters that our template will use inside angled brackets (`<>`). For each type template parameter, we use the keyword `typename` (preferred) or `class`, followed by the name of the type template parameter (e.g. `T`).

>[!As an aside...]
>There is no difference between the `typename` and `class` keywords in this context. You will often see people use the `class` keyword since it was introduced into the language earlier. However, we prefer the newer `typename` keyword, because it makes it clearer that the type template parameter can be replaced by any type (such as a fundamental type), not just class types.

Believe it or not, we’re done! We have created a template version of our `max()` function that can accept arguments of different types.

In the next lesson, we’ll look at how we use our `max` function template to generate one or more `max()` functions with parameters of different types and actually call those functions.

>[!Best Practice]
>Use a single capital letter starting with `T` (e.g. `T`, `U`, `V`, etc…) to name type template parameters that are used in trivial or obvious ways and represent “any reasonable type”.
If the type template parameter has a non-obvious usage or specific requirements that must be met, then a more descriptive name is warranted (e.g. `Allocator` or `TAllocator`).

>[!Analogy]
>The construction blueprint itself is just a piece of paper that describes how to construct a building. Using the blueprint, construction crews can quickly erect many buildings with an identical structure. However, the specific material types used for each building can vary (e.g. what type of material is used for the siding of the building), and don’t need to be determined until the buildings are actually built.

---
### Using a function template

#### 🧩 **Function templates are like blueprints — not actual functions.**

When you write a function template in C++, you’re not creating a function **yet**. You’re just creating a **pattern** (or "template") that the compiler will use **later** to generate actual functions when needed.

#### 🔧 What happens behind the scenes:

Let’s say you write this template:

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```

At this point, the compiler doesn’t create any real function code. This code is **just a pattern**, not something that can be compiled or run yet.

#### 🔁 When does a real function get created?

When you call `add` with a specific type:

```cpp
int x = add(2, 3);       // T is int → compiler creates: int add(int, int)
double y = add(2.5, 3.7); // T is double → compiler creates: double add(double, double)
```

Only **when you call** the template with specific types, the compiler **instantiates** the template, meaning it **generates a real function** from the template using those types.

>To use our `max<T>` function template, we can make a function call with the following syntax:

```cpp
max<actual_type>(arg1, arg2); // actual_type is some actual type, like int or double
```

This looks a lot like a normal function call -- the primary difference is the addition of the type in angled brackets (called a **template argument**), which specifies the actual type that will be used in place of template type `T`.

Lets see an example:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

>When the compiler encounters the function call `max<int>(1, 2)`, it will determine that a function definition for `max<int>(int, int)` does not already exist. Consequently, the compiler will implicitly use our `max<T>` function template to create one.

The process of creating functions (with specific types) from function templates (with template types) is called **function template instantiation** (or **instantiation** for short). When a function is instantiated due to a function call, it’s called **implicit instantiation**. A function that is instantiated from a template is technically called a **specialization**, but in common language is often called a **function instance**. The template from which a specialization is produced is called a **primary template**. Function instances are normal functions in all regards.

>[!Tip]
>A function that is instantiated from a template is technically called a **specialization**

>The process for instantiating a function is simple: the compiler essentially clones the primary template and replaces the template type (`T`) with the actual type we’ve specified (`int`).

So when we call `max<int>(1, 2)`, the function specialization that gets instantiated looks something like this:

```cpp
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

####  **"Function template is only instantiated the first time..."**

- When you call a function template (like `add<int>(2, 3)`), the compiler **generates (instantiates)** a real version of that function — but **only once** for each translation unit (i.e., each `.cpp` file and everything it includes).
    
- On the **first call**, the compiler **creates** the actual function.
    
- On **further calls**, it **reuses** the already-created function.

Conversely, if no function call is made to a function template, the function template won’t be instantiated in that translation unit.

```cpp
#include <iostream>

template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```

--> The following code demonstrate explicit template specialization of a function template:

```cpp
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

template<>
double max<double>(double x, double y) // the generated function max<double>(double, double)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```

```cpp
template <typename T>
T max(T x, T y);
```

This line declares a **function template** `max`. It tells the compiler:

> "There is a function `max` that works with **any type `T`** and takes two arguments of type `T`, returning the maximum of the two."

Note:

- This is **only a declaration**, not the definition.
    
- You’re promising the compiler that you’ll provide special versions (specializations) of this template for certain types.

```cpp
template<>
int max<int>(int x, int y)
{
    return (x < y) ? y : x;
}
```

This is an **explicit specialization** of the `max` function template **for `int`**:

- You’re saying: _“If someone uses `max` with `int`, use this version.”_
    
- It compares `x` and `y`, and returns the larger of the two.


```cpp
template<>
double max<double>(double x, double y)
{
    return (x < y) ? y : x;
}
```

Same thing, but this version is **specialized for `double`** types.

🔧 Main Function

```cpp
int main()
{
    std::cout << max<int>(1, 2) << '\n';
}
```
- You explicitly say: “Use the `int` specialization of `max`”.
    
- It prints `2`.

```cpp
    std::cout << max<int>(4, 3) << '\n';
```

- Again uses the already instantiated `int` specialization.
    
- Prints `4`.

```cpp
    std::cout << max<double>(1, 2) << '\n';
```

- Uses the `double` specialization.
    
- Prints `2`.

Why there is a declaration at the top? : C++ still needs to know:

> “There’s a general template function named `max` that can be specialized for different types.”

That’s why this **forward declaration** of the template is required.

One additional thing to note here: when we instantiate `max<double>`, the instantiated function has parameters of type `double`. Because we’ve provided `int` arguments, those arguments will be implicitly converted to `double`.

---
### Template argument deduction

In most cases, the actual types we want to use for instantiation will match the type of our function parameters. For example:

```cpp
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
```

>In cases where the type of the arguments match the actual type we want, we do not need to specify the actual type -- instead, we can use **template argument deduction** to have the compiler deduce the actual type that should be used from the argument types in the function call.

For example, instead of making a function call like this:

```cpp
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
```

We can do one of these instead:

```cpp
std::cout << max<>(1, 2) << '\n';
std::cout << max(1, 2) << '\n';
```

In either case, the compiler will see that we haven’t provided an actual type, so it will attempt to deduce an actual type from the function arguments that will allow it to generate a `max()` function where all template parameters match the type of the provided arguments. In this example, the compiler will deduce that using function template `max<T>` with actual type `int` allows it to instantiate function `max<int>(int, int)`, so that the type of both function parameters (`int`) matches the type of the provided arguments (`int`).

The difference between the two cases has to do with how the compiler resolves the function call from a set of overloaded functions. In the top case (with the empty angled brackets), the compiler will only consider `max<int>` template function overloads when determining which overloaded function to call. In the bottom case (with no angled brackets), the compiler will consider both `max<int>` template function overloads and `max` non-template function overloads. When the bottom case results in both a template function and a non-template function that are equally viable, the non-template function will be preferred.

>[!Key Insight]
>The normal function call syntax will prefer a non-template function over an equally viable function instantiated from a template.

For Example:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
    std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    return 0;
}
```

Note how the syntax in the bottom case looks identical to a normal function call! In most cases, this normal function call syntax will be the one we use to call functions instantiated from a function template.

There are a few reasons for this:

- The syntax is more concise.
- It’s rare that we’ll have both a matching non-template function and a function template.
- If we do have a matching non-template function and a matching function template, we will usually prefer the non-template function to be called.

>That last point may be non-obvious. A function template has an implementation that works for multiple types -- but as a result, it must be generic. A non-template function only handles a specific combination of types. It can have an implementation that is more optimized or more specialized for those specific types than the function template version. For example:

```cpp
#include <iostream>

// This function template can handle many types, so its implementation is generic
template <typename T>
void print(T x)
{
    std::cout << x; // print T however it normally prints
}

// This function only needs to consider how to print a bool, so it can specialize how it handles
// printing of a bool
void print(bool x)
{
    std::cout << std::boolalpha << x; // print bool as true or false, not 1 or 0
}

int main()
{
    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    std::cout << '\n';

    return 0;
}
```

>[!Best Practice]
>Favor the normal function call syntax when making calls to a function instantiated from a function template (unless you need the function template version to be preferred over a matching non-template function).

---
### Function templates with non-template parameters

It’s possible to create function templates that have both template parameters and non-template parameters. The type template parameters can be matched to any type, and the non-template parameters work like the parameters of normal functions.

For example:

```cpp
// T is a type template parameter
// double is a non-template parameter
// We don't need to provide names for these parameters since they aren't used
template <typename T>
int someFcn(T, double)
{
    return 5;
}

int main()
{
    someFcn(1, 3.4); // matches someFcn(int, double)
    someFcn(1, 3.4f); // matches someFcn(int, double) -- the float is promoted to a double
    someFcn(1.2, 3.4); // matches someFcn(double, double)
    someFcn(1.2f, 3.4); // matches someFcn(float, double)
    someFcn(1.2f, 3.4f); // matches someFcn(float, double) -- the float is promoted to a double

    return 0;
}
```

This function template has a templated first parameter, but the second parameter is fixed with type `double`. Note that the return type can also be any type. In this case, our function will always return an `int` value.

---
### Instantiated functions may not always compile

```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::string hello { "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```

When the compiler tries to resolve `addOne(hello)` it won’t find a non-template function match for `addOne(std::string)`, but it will find our function template for `addOne(T)`, and determine that it can generate an `addOne(std::string)` function from it. Thus, the compiler will generate and compile this:

```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x);

template<>
std::string addOne<std::string>(std::string x)
{
    return x + 1;
}

int main()
{
    std::string hello{ "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```

However, this will generate a compile error, because `x + 1` doesn’t make sense when `x` is a `std::string`. The obvious solution here is simply not to call `addOne()` with an argument of type `std::string`.

---
### Instantiated functions may not always make sense semantically

The compiler will successfully compile an instantiated function template as long as it makes sense syntactically. However, the compiler does not have any way to check that such a function actually makes sense semantically.

For example:

```cpp
#include <iostream>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne("Hello, world!") << '\n';

    return 0;
}
```

In this example, we’re calling `addOne()` on a C-style string literal. What does that actually mean semantically? Who knows!

Perhaps surprisingly, because C++ syntactically allows addition of an integer value to a string literal (we cover this in future lesson [17.9 -- Pointer arithmetic and subscripting](https://www.learncpp.com/cpp-tutorial/pointer-arithmetic-and-subscripting/)), the above example compiles, and produces the following result:

ello, world!

>[!Warning]
>The compiler will instantiate and compile function templates that do not make sense semantically as long as they are syntactically valid. It is your responsibility to make sure you are calling such function templates with arguments that make sense.

---
We can tell the compiler that instantiation of function templates with certain arguments should be disallowed. This is done by using function template specialization, which allow us to overload a function template for a specific set of template arguments, along with `= delete`, which tells the compiler that any use of the function should emit a compilation error.

```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char* addOne(const char* x) = delete;

int main()
{
    std::cout << addOne("Hello, world!") << '\n'; // compile error

    return 0;
}
```

### Confusion: so my confusion was that, why not `const char* addOne<const char*>(const char* x) = delete;` :

#### You **can** write:

```cpp
template<>
int max(int x, int y) { ... }           // ✅ OK
template<>
int max<int>(int x, int y) { ... }      // ✅ Also OK (redundant but legal)
```

Both are valid specializations — but the one **with angle brackets** is **more explicit** (you’re stating the template argument). The compiler **already knows** the template parameter (`int`) from the function parameter types and return type, so the `<int>` part is **optional** here.

```cpp
template<> int max<int>(int x, int y) // more explicit
template<> int max(int x, int y)      // cleaner, preferred
```

Both are valid and do the same thing.

#### ❌ But you **cannot** do this with `addOne<const char*>`:

#### 🧠 Why the difference?

##### 🔹 Function template **specialization syntax** has two styles:

**Option 1 — Preferred style (clean):**

```cpp
template<> ReturnType functionName(Args) { ... }
```

**Option 2 — More verbose but legal:**

```cpp
template<>
ReturnType functionName<SpecializedType>(Args) { ... }
```

✅ They both work — **as long as you begin with `template<>`**.

But **for deletion**, the C++ syntax rules **do not allow** the verbose form:

```cpp
template <>
const char* addOne<const char*>(const char* x) = delete; // ❌ invalid!
```

Only this form is valid:

```cpp
template <>
const char* addOne(const char* x) = delete; // ✅ correct
```

---
### Function templates and default arguments for non-template parameters

Just like normal functions, function templates can have default arguments for non-template parameters. Each function instantiated from the template will use the same default argument.

For example:

```cpp
#include <iostream>

template <typename T>
void print(T val, int times=1)
{
    while (times--)
    {
        std::cout << val;
    }
}

int main()
{
    print(5);      // print 5 1 time
    print('a', 3); // print 'a' 3 times

    return 0;
}
```

This prints:

5aaa

---
### Beware function templates with modifiable static local variables

In lesson [7.11 -- Static local variables](https://www.learncpp.com/cpp-tutorial/static-local-variables/), we discussed static local variables, which are local variables with static duration (they persist for the lifetime of the program).

When a static local variable is used in a function template, each function instantiated from that template will have a separate version of the static local variable. This is rarely a problem if the static local variable is const. But if the static local variable is one that is modified, the results may not be as expected.

For example:

```cpp
#include <iostream>

// Here's a function template with a static local variable that is modified
template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);
    printIDAndValue(13);

    printIDAndValue(14.5);

    return 0;
}
```

This produces the result:

1) 12
2) 13
3) 14.5

You may have been expecting the last line to print `3) 14.5`. However, this is what the compiler actually compiles and executes:

```cpp
#include <iostream>

template <typename T>
void printIDAndValue(T value);

template <>
void printIDAndValue<int>(int value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

template <>
void printIDAndValue<double>(double value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);   // calls printIDAndValue<int>()
    printIDAndValue(13);   // calls printIDAndValue<int>()

    printIDAndValue(14.5); // calls printIDAndValue<double>()

    return 0;
}
```

Note that `printIDAndValue<int>` and `printIDAndValue<double>` each have their own independent static local variable named `id`, not one that is shared between them.

---
### Generic programming

Because template types can be replaced with any actual type, template types are sometimes called **generic types**. And because templates can be written agnostically of specific types, programming with templates is sometimes called **generic programming**. Whereas C++ typically has a strong focus on types and type checking, in contrast, generic programming lets us focus on the logic of algorithms and design of data structures without having to worry so much about type information.

#### ✅ Real-World Analogy

##### 🧰 Imagine: A Warehouse Sorting System

You work at a warehouse that sorts **boxes of all kinds**: small boxes, large boxes, heavy boxes, etc.

Instead of writing **different sorting machines** for each type of box (`SmallBox`, `LargeBox`, `HeavyBox`, etc.), you design a **generic sorting machine** that works with **any kind of box** — as long as it knows how to **compare sizes**.

---
### Conclusion

Once you get used to writing function templates, you’ll find they actually don’t take much longer to write than functions with actual types. Function templates can significantly reduce code maintenance and errors by minimizing the amount of code that needs to be written and maintained.

Function templates do have a few drawbacks, and we would be remiss not to mention them. First, the compiler will create (and compile) a function for each function call with a unique set of argument types. So while function templates are compact to write, they can expand into a crazy amount of code, which can lead to code bloat and slow compile times. The bigger downside of function templates is that they tend to produce crazy-looking, borderline unreadable error messages that are much harder to decipher than those of regular functions. These error messages can be quite intimidating, but once you understand what they are trying to tell you, the problems they are pinpointing are often quite straightforward to resolve.

These drawbacks are fairly minor compared with the power and safety that templates bring to your programming toolkit, so use templates liberally anywhere you need type flexibility! A good rule of thumb is to create normal functions at first, and then convert them into function templates if you find you need an overload for different parameter types.

>[!Best Practice]
>Use function templates to write generic code that can work with a wide variety of types whenever you have the need.

---
### Functions templates with multiple template types

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';  // compile error

    return 0;
}
```

You may be surprised to find that this program won’t compile. Instead, the compiler will issue a bunch of (probably crazy looking) error messages. On Visual Studio, the author got the following:

Project3.cpp(11,18): error C2672: 'max': no matching overloaded function found
Project3.cpp(11,28): error C2782: 'T max(T,T)': template parameter 'T' is ambiguous
Project3.cpp(4): message : see declaration of 'max'
Project3.cpp(11,28): message : could be 'double'
Project3.cpp(11,28): message : or       'int'
Project3.cpp(11,28): error C2784: 'T max(T,T)': could not deduce template argument for 'T' from 'double'
Project3.cpp(4): message : see declaration of 'max'

In our function call `max(2, 3.5)`, we’re passing arguments of two different types: one `int` and one `double`. Because we’re making a function call without using angled brackets to specify an actual type, the compiler will first look to see if there is a non-template match for `max(int, double)`. It won’t find one.

Next, the compiler will see if it can find a function template match (using template argument deduction, which we covered in lesson [11.7 -- Function template instantiation](https://www.learncpp.com/cpp-tutorial/function-template-instantiation/)). However, this will also fail, for a simple reason: `T` can only represent a single type. There is no type for `T` that would allow the compiler to instantiate function template `max<T>(T, T)` into a function with two different parameter types. Put another way, because both parameters in the function template are of type `T`, they must resolve to the same actual type.

Since both a non-template match and a template match couldn’t be found, the function call fails to resolve, and we get a compile error.

>You might wonder why the compiler didn’t generate function `max<double>(double, double)` and then use numeric conversion to type convert the `int` argument to a `double`. The answer is simple: type conversion is done only when resolving function overloads, not when performing template argument deduction.

This lack of type conversion is intentional for at least two reasons. First, it helps keep things simple: we either find an exact match between the function call arguments and template type parameters, or we don’t. Second, it allows us to create function templates for cases where we want to ensure that two or more parameters have the same type (as in the example above).

---
### Use static_cast to convert the arguments to matching types

The first solution is to put the burden on the caller to convert the arguments into matching types. For example:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)

    return 0;
}
```

Now that both arguments are of type `double`, the compiler will be able to instantiate `max(double, double)` that will satisfy this function call.

However, this solution is awkward and hard to read.

---
### Provide an explicit type template argument

If we had written a non-template `max(double, double)` function, then we would be able to call `max(int, double)` and let the implicit type conversion rules convert our `int` argument into a `double` so the function call could be resolved:

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

```cpp
#include <iostream>

double max(double x, double y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // the int argument will be converted to a double

    return 0;
}
```

However, when the compiler is doing template argument deduction, it won’t do any type conversions. Fortunately, we don’t have to use template argument deduction if we specify an explicit type template argument to be used instead:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    // we've explicitly specified type double, so the compiler won't use template argument deduction
    std::cout << max<double>(2, 3.5) << '\n';

    return 0;
}
```

In the above example, we call `max<double>(2, 3.5)`. Because we’ve explicitly specified that `T` should be replaced with `double`, the compiler won’t use template argument deduction. Instead, it will just instantiate the function `max<double>(double, double)`, and then type convert any mismatched arguments. Our `int` parameter will be implicitly converted to a `double`.

While this is more readable than using `static_cast`, it would be even nicer if we didn’t even have to think about the types when making a function call to `max` at all

---
### Function templates with multiple template type parameters

#### ✅ THE ROOT OF THE PROBLEM

##### Original function:

```cpp
template <typename T>
T max(T x, T y)
```

- Both parameters **must be the same type** (`T`)
    
- Works fine for `max(3, 7)` or `max(2.5, 3.5)`
    
- ❌ But fails or gives **unexpected results** when you do:

```cpp
max(2, 3.5); // int + double
```

Because both `x` and `y` are of the **same template type**, this forces both to become `T`, and you may **lose precision** (e.g., `3.5 → 3`).

#### 🛠 THE FIRST FIX: Use two template parameters

```cpp
template <typename T, typename U>
T max(T x, U y)
```

Now, `x` and `y` can have different types — for example:

```cpp
max(2, 3.5); // T = int, U = double
```

**So far, so good.** But…

#### ⚠️ THE NEW PROBLEM: Return type is **still T**

```cpp
return (x < y) ? y : x;
```

Even though the ternary operator produces a **double**, it’s being returned as **T (int)**.

So:

```cpp
return 3.5; // narrowing conversion to int ⇒ becomes 3
```

This is why:

```cpp
std::cout << max(2, 3.5) << '\n'; // prints 3 instead of 3.5
```

#### ✅ THE RIGHT FIX: Use `auto` for return type

```cpp
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}
```

Now the compiler does **return type deduction**:

- If `x = int`, `y = double` → ternary produces **double** → compiler deduces return type is **double**
    
- If `x = std::string`, `y = std::string` → return type is **std::string**
    

This eliminates the **loss of precision** problem and makes your function **type-safe** and **generic**.

---
### Abbreviated function templates C++20

>C++20 introduces a new use of the `auto` keyword: When the `auto` keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template with each auto parameter becoming an independent template type parameter. This method for creating a function template is called an **abbreviated function template**.

For example:

```cpp
auto max(auto x, auto y)
{
    return (x < y) ? y : x;
}
```

is shorthand in C++20 for the following:

```cpp
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}
```

which is the same as the `max` function template we wrote above.

In cases where you want each template type parameter to be an independent type, this form is preferred as the removal of the template parameter declaration line makes your code more concise and readable.

>There isn’t a concise way to use abbreviated function templates when you want more than one auto parameter to be the same type. That is, there isn’t an easy abbreviated function template for something like this:

```cpp
template <typename T>
T max(T x, T y) // two parameters of the same type
{
    return (x < y) ? y : x;
}
```

>[!Best practice]
Feel free to use abbreviated function templates with a single auto parameter, or where each auto parameter should be an independent type (and your language standard is set to C++20 or newer).

---
### Function templates may be overloaded

Just like functions may be overloaded, function templates may also be overloaded. Such overloads can have a different number of template types and/or a different number or type of function parameters:

```cpp
#include <iostream>

// Add two values with matching types
template <typename T>
auto add(T x, T y)
{
    return x + y;
}

// Add two values with non-matching types
// As of C++20 we could also use auto add(auto x, auto y)
template <typename T, typename U>
auto add(T x, U y)
{
    return x + y;
}

// Add three values with any type
// As of C++20 we could also use auto add(auto x, auto y, auto z)
template <typename T, typename U, typename V>
auto add(T x, U y, V z)
{
    return x + y + z;
}

int main()
{
    std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
    std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
    std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()

    return 0;
}
```

One interesting note here is that for the call to `add(1.2, 3.4)`, the compiler will prefer `add<T>(T, T)` over `add<T, U>(T, U)` even though both could possibly match.

The rules for determining which of multiple matching function templates should be preferred are called “partial ordering of function templates”. In short, whichever function template is more restrictive/specialized will be preferred. `add<T>(T, T)` is the more restrictive function template in this case (since it only has one template parameter), so it is preferred.

If multiple function templates can match a call and the compiler can’t determine which is more restrictive, the compiler will error with an ambiguous match.

---
### Non-type template parameters

>A **non-type template parameter** is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.

A non-type template parameter can be any of the following types:

- An integral type
- An enumeration type
- `std::nullptr_t`
- A floating point type (since C++20)
- A pointer or reference to an object
- A pointer or reference to a function
- A pointer or reference to a member function
- A literal class type (since C++20)

We saw our first example of a non-type template parameter when we discussed `std::bitset`

```cpp
#include <bitset>

int main()
{
    std::bitset<8> bits{ 0b0000'0101 }; // The <8> is a non-type template parameter

    return 0;
}
```

In the case of `std::bitset`, the non-type template parameter is used to tell the `std::bitset` how many bits we want it to store.

---
### Defining our own non-type template parameters

Here’s a simple example of a function that uses an int non-type template parameter:

```cpp
#include <iostream>

template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}

int main()
{
    print<5>(); // 5 is our non-type template argument

    return 0;
}
```

This example prints:

5

On line 3, we have our template parameter declaration. Inside the angled brackets, we’re defining a non-type template parameter named `N` that will be a placeholder for a value of type `int`. Inside the `print()` function, we use the value of `N`.

On line 11, we have our call to function `print()`, which uses int value `5` as the non-type template argument. When the compiler sees this call, it will instantiate a function that looks something like this:

```cpp
template <>
void print<5>()
{
    std::cout << 5 << '\n';
}
```

At runtime, when this function is called from `main()`, it prints `5`.

Then the program ends. Pretty simple, right?

Much like `T` is typically used as the name for the first type template parameter, `N` is conventionally used as the name of an int non-type template parameter.

>[!Best practice]
Use `N` as the name of an int non-type template parameter.

---
### What are non-type template parameters useful for?

>As of C++20, function parameters cannot be constexpr. This is true for normal functions, constexpr functions (which makes sense, as they must be able to be run at runtime), and perhaps surprisingly, even consteval functions.

```cpp
#include <cassert>
#include <cmath> // for std::sqrt
#include <iostream>

double getSqrt(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");

    // The assert above will probably be compiled out in non-debug builds
    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

int main()
{
    std::cout << getSqrt(5.0) << '\n';
    std::cout << getSqrt(-5.0) << '\n';

    return 0;
}
```

>When run, the call to `getSqrt(-5.0)` will runtime assert out. While this is better than nothing, because `-5.0` is a literal (and implicitly constexpr), it would be better if we could static_assert so that errors such as this one would be caught at compile-time. However, static_assert requires a constant expression, and function parameters can’t be constexpr…

#### 🧠 The Key Concepts:

##### 🔹 `-5.0` is a **literal**

When you write:

```cpp
getSqrt(-5.0);
```

You're passing a **literal value**, which **is** a constant known at compile time — also known as a **constant expression** (a `constexpr`).

BUT...

##### 🔸 Function parameters can't be `constexpr`

Even if you pass a literal like `-5.0`, once it reaches the function like this:

```cpp
double getSqrt(double d)
```

The parameter `d` is **just a runtime variable** — even if its value came from a compile-time constant.

So inside the function:

```cpp
static_assert(d >= 0.0, "d must be non-negative"); // ❌ ERROR
```

this fails, because `static_assert` **needs a compile-time expression**, and `d` is **not** one — it's a runtime parameter.

##### 🤯 Why is this a problem?

You’re passing a constant, **but** your function can’t treat it as such:

- You lose the ability to check for errors **at compile time**.
    
- So even if the input is clearly invalid (`-5.0`), the compiler doesn’t stop you.
    
- You only find out when you run the program (runtime assert fails).


>However, if we change the function parameter to a non-type template parameter instead, then we can do exactly as we want:

```cpp
#include <cmath> // for std::sqrt
#include <iostream>

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (D >= 0) // ignore the constexpr here for this example
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

int main()
{
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    return 0;
}
```

This version fails to compile. When the compiler encounters `getSqrt<-5.0>()`, it will instantiate and call a function that looks something like this:

```cpp
template <>
double getSqrt<-5.0>()
{
    static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (-5.0 >= 0) // ignore the constexpr here for this example
        return std::sqrt(-5.0);

    return 0.0;
}
```

The static_assert condition is false, so the compiler asserts out.

>[!Key Insight]
>Non-type template parameters are used primarily when we need to pass constexpr values to functions (or class types) so they can be used in contexts that require a constant expression.
The class type `std::bitset` uses a non-type template parameter to define the number of bits to store because the number of bits must be a constexpr value.

>[!Note]
>Having to use non-type template parameters to circumvent the restriction that function parameters can’t be constexpr isn’t great. There are quite a few different proposals being evaluated to help address situations like this. I expect that we might see a better solution to this in a future C++ language standard.

---
### [Implicit conversions for non-type template arguments (Optional)](https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/#:~:text=Implicit%20conversions%20for,in%20ambiguous%20matches.)
---
### ype deduction for non-type template parameters using `auto` C++17

As of C++17, non-type template parameters may use `auto` to have the compiler deduce the non-type template parameter from the template argument:

```cpp
#include <iostream>

template <auto N> // deduce non-type template parameter from template argument
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // N deduced as int `5`
    print<'c'>(); // N deduced as char `c`

    return 0;
}
```

This compiles and produces the expected result:

5
c

---

>[!Note Important]
> **Templates must be defined in the same translation unit where they are instantiated**

>The most conventional way to address this issue is to put all your template code in a header (.h) file instead of a source (.cpp) file:

add.h

```cpp
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}

#endif 
```

main.cpp

```cpp
#include "add.h" // import the function template definition
#include <iostream>

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```

That way, any files that need access to the template can #include the relevant header, and the template definition will be copied by the preprocessor into the source file. The compiler will then be able to instantiate any functions that are needed.

>You may be wondering why this doesn’t cause a violation of the one-definition rule (ODR). The ODR says that types, templates, inline functions, and inline variables are allowed to have identical definitions in different files. So there is no problem if the template definition is copied into multiple files (as long as each definition is identical).

But what about the instantiated functions themselves? If a function is instantiated in multiple files, how does that not cause a violation of the ODR? The answer is that functions implicitly instantiated from templates are implicitly inline. And as you know, inline functions can be defined in multiple files, so long as the definition is identical in each.

>[!Best Practice]
>Templates that are needed in multiple files should be defined in a header file, and then #included wherever needed. This allows the compiler to see the full template definition and instantiate the template when needed.

---
### [Summary and Quiz](https://www.learncpp.com/cpp-tutorial/chapter-11-summary-and-quiz/)

---
