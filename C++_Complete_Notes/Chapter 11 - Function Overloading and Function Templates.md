
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
