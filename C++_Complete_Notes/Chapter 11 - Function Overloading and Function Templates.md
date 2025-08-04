
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
