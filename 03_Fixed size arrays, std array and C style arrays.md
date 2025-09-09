
# Introduction to std::array

>we mentioned that arrays fall into two categories:

- Fixed-size arrays (also called fixed-length arrays) require that the length of the array be known at the point of instantiation, and that length cannot be changed afterward. C-style arrays and `std::array` are both fixed-size arrays.
- Dynamic arrays can be resized at runtime. `std::vector` is a dynamic array.

In the previous chapter, we focused on `std::vector`, as it is fast, comparatively easy to use, and versatile. This makes it our go-to type when we need an array container.

### So why not use dynamic arrays for everything?

Dynamic arrays are powerful and convenient, but like everything in life, they make some tradeoffs for the benefits they offer.

- `std::vector` is slightly less performant than the fixed-size arrays. In most cases you probably won’t notice the difference (unless you’re writing sloppy code that causes lots of inadvertent reallocations).
- `std::vector` only supports `constexpr` in very limited contexts.

In modern C++, it is really this latter point that’s significant. Constexpr arrays offer the ability to write code that is more robust, and can also be optimized more highly by the compiler. Whenever we can use a constexpr array, we should -- and if we need a constexpr array, `std::array` is the container class we should be using.

>[!Best practice]
Use `std::array` for constexpr arrays, and `std::vector` for non-constexpr arrays.

### Defining a `std::array`

>`std::array` is defined in the `<array>` header. It is designed to work similarly to `std::vector`, and as you’ll see, there are more similarities than differences between the two.

One difference is in how we declare a `std::array`:

```cpp
#include <array>  // for std::array
#include <vector> // for std::vector

int main()
{
    std::array<int, 5> a {};  // a std::array of 5 ints

    std::vector<int> b(5);    // a std::vector of 5 ints (for comparison)

    return 0;
}
```

Our `std::array` declaration has two template arguments. The first (`int`) is a type template argument defining the type of the array element. The second (`5`) is an integral non-type template argument defining the array length.

### The length of a `std::array` must be a constant expression

Unlike a `std::vector`, which can be resized at runtime, the length of a `std::array` must be a constant expression. Most often, the value provided for the length will be an integer literal, constexpr variable, or an unscoped enumerator.(which is constexpr by default)

```cpp
#include <array>

int main()
{
    std::array<int, 7> a {}; // Using a literal constant

    constexpr int len { 8 };
    std::array<int, len> b {}; // Using a constexpr variable

    enum Colors
    {
         red,
         green,
         blue,
         max_colors
    };

    std::array<int, max_colors> c {}; // Using an enumerator

#define DAYS_PER_WEEK 7
    std::array<int, DAYS_PER_WEEK> d {}; // Using a macro (don't do this, use a constexpr variable instead)

    return 0;
}
```

Note that non-const variables and runtime constants cannot be used for the length:

```cpp
#include <array>
#include <iostream>

void foo(const int length) // length is a runtime constant
{
    std::array<int, length> e {}; // error: length is not a constant expression
}

int main()
{
    // using a non-const variable
    int numStudents{};
    std::cin >> numStudents; // numStudents is non-constant

    std::array<int, numStudents> {}; // error: numStudents is not a constant expression

    foo(7);

    return 0;
}
```

>Runtime constant (like `const int`)

```cpp
void foo(const int length) {
    std::array<int, length> e {}; // ❌ error
}
```

- Even though `length` is declared `const`, its value is passed at runtime when calling `foo(7)`.
    
- `const` here just means it **can’t change inside the function**, but it is not a **compile-time constant**.
    
- Therefore, the compiler still doesn’t know the value when generating code → error.

>[!Warning]
>Perhaps surprisingly, a `std::array` can be defined with a length of 0:
```cpp
#include <array>
#include <iostream>

int main()
{
    std::array<int, 0> arr {}; // creates a zero-length std::array
    std::cout << arr.empty();  // true if arr is zero-length

    return 0;
}
```
>[!Warning]
>A zero-length `std::array` is a special-case class that has no data. As such, calling any member function that accesses the data of a zero-length `std::array` (including `operator[]`) will produce undefined behavior.
>You can test whether a `std::array` is zero-length using the `empty()` member function, which returns `true` if the array is zero-length and `false` otherwise.

### Aggregate initialization of a `std::array`

Perhaps surprisingly, `std::array` is an aggregate. This means it has no constructors, and instead is initialized using aggregate initialization. As a quick recap, aggregate initialization allows us to directly initialize the members of aggregates. To do this, we provide an initializer list, which is a brace-enclosed list of comma-separated initialization values.

```cpp
#include <array>

int main()
{
    std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    std::array<int, 5> prime { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    return 0;
}
```

Each of these initialization forms initializes the array members in sequence, starting with element 0.

If a `std::array` is defined without an initializer, the elements will be default initialized. In most cases, this will result in elements being left uninitialized.

Because we generally want our elements to be initialized, `std::array` should be value initialized (using empty braces) when defined with no initializers.

```cpp
#include <array>
#include <vector>

int main()
{
    std::array<int, 5> a;   // Members default initialized (int elements are left uninitialized)
    std::array<int, 5> b{}; // Members value initialized (int elements are zero initialized) (preferred)

    std::vector<int> v(5);  // Members value initialized (int elements are zero initialized) (for comparison)

    return 0;
}
```

>If more initializers are provided in an initializer list than the defined array length, the compiler will error. If fewer initializers are provided in an initializer list than the defined array length, the remaining elements without initializers are value initialized:

```cpp
#include <array>

int main()
{
    std::array<int, 4> a { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    std::array<int, 4> b { 1, 2 };          // b[2] and b[3] are value initialized

    return 0;
}
```

### Const and constexpr `std::array`

A `std::array` can be const:

```cpp
#include <array>

int main()
{
    const std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```

Even though the elements of a `const std::array` are not explicitly marked as const, they are still treated as const (because the whole array is const).

`std::array` also has full support for constexpr:

```cpp
#include <array>

int main()
{
    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```

This support for constexpr is the key reason to use `std::array`.

>[!Best practice]
Define your `std::array` as constexpr whenever possible. If your `std::array` is not constexpr, consider using a `std::vector` instead.

`constexpr` means:

1. The object/function can be **evaluated at compile time**.
    
2. Its value is a **constant expression** and can be used where a compile-time constant is required.
    

So if you make an `std::array` `constexpr`, it means:

- The array itself will be created **at compile time**, not at runtime.
    
- Its elements must all be **known at compile time** too.

### Class template argument deduction (CTAD) for `std::array` C++17

>Using CTAD (class template argument deduction) in C++17, we can have the compiler deduce both the element type and the array length of a `std::array` from a list of initializers:

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5>
    constexpr std::array a2 { 9.7, 7.31 };     // The type is deduced to std::array<double, 2>

    return 0;
}
```

We favor this syntax whenever practical. If your compiler is not C++17 capable, you’ll need to explicitly provide the type and length template arguments.

>[!Best Practice]
>Use class template argument deduction (CTAD) to have the compiler deduce the type and length of a `std::array` from its initializers.

CTAD does not support partial omission of template arguments (as of C++23), so there is no way to use a core language feature to omit just the length or just the type of a `std::array`:

```cpp
#include <iostream>

int main()
{
    constexpr std::array<int> a2 { 9, 7, 5, 3, 1 };     // error: too few template arguments (length missing)
    constexpr std::array<5> a2 { 9, 7, 5, 3, 1 };       // error: too few template arguments (type missing)

    return 0;
}
```

### Omitting just the array length using `std::to_array` C++20

#### 🔑 The Problem Before C++20

When using `std::array`, you normally need to specify **both the type and the size** explicitly:

```cpp
std::array<int, 5> arr{ 9, 7, 5, 3, 1 };
```

This is fine, but sometimes redundant because the compiler _already knows_ the size and type from the initializer list.  
Unfortunately, template argument deduction (TAD) in C++17 and earlier could not deduce the `N` (size) part.

#### ✅ The C++20 Solution → `std::to_array`

C++20 introduced a helper function `std::to_array` that **deduces** template arguments automatically.

##### 1. Specify both type and size

```cpp
constexpr auto myArray1 { std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) };
```

- Here, you explicitly give both the element type (`int`) and length (`5`).
    
- Equivalent to:

```cpp
constexpr std::array<int, 5> myArray1{ 9, 7, 5, 3, 1 };
```

##### 2. Specify type only (size deduced)

```cpp
constexpr auto myArray2 { std::to_array<int>({ 9, 7, 5, 3, 1 }) };
```

- Compiler deduces that the size is **5** from the initializer list.
    
- Type is explicitly given (`int`).

##### 3. Deduce both type and size

```cpp
constexpr auto myArray3 { std::to_array({ 9, 7, 5, 3, 1 }) };
```

- Compiler deduces:
    
    - type = `int`
        
    - size = `5`
        
- Simplest form! Equivalent to writing:

```cpp
constexpr std::array<int, 5> myArray3{ 9, 7, 5, 3, 1 };
```

#### ⚡ Why is `std::to_array` sometimes needed?

Normally, C++ literals default to `int`. But what if you want an `std::array<short>`?

```cpp
std::array<short, 5> arr{ 9, 7, 5, 3, 1 };  // works, but you must specify size
```

With `std::to_array`:

```cpp
constexpr auto shortArray { std::to_array<short>({ 9, 7, 5, 3, 1 }) };
```

- Type = `short` (explicit)
    
- Size = deduced (5)
    

This avoids repetition and makes code cleaner.


#### ⚠️ Performance Caveat

`std::to_array` creates a **temporary `std::array`** and then copies it into your variable.

- For single global constants (`constexpr`), this cost is negligible.
    
- But if used inside a **loop** where arrays are created repeatedly, it may be inefficient compared to writing `std::array<int, 5>` directly.

#### 🚀 When to use `std::to_array`

- When you want **type or size deduction** to avoid redundancy.
    
- When working with **non-`int` literals** (like `short`, `char`, etc.).
    
- For **readability** in `constexpr` contexts.
    

Avoid it in **tight loops** or performance-critical sections.

### Accessing array elements using `operator[]`

>Just like a `std::vector`, the most common way to access elements of a `std::array` is by using the subscript operator (`operator[]`):

```cpp
#include <array> // for std::array
#include <iostream>

int main()
{
    constexpr std::array<int, 5> prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3]; // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```

As a reminder, `operator[]` does not do bounds checking. If an invalid index is provided, undefined behavior will result.

---
# std::array length and indexing

>std::array faces the same issue of unsigned value as the std::vector because they are part of the same standard library container class.

now would be a good time to refresh your memory on “sign conversions are narrowing conversions, except when constexpr”
Becasue if it is constexpr it can determine at compile time that if it is narrowing conversion or not.

### The length of a `std::array` has type `std::size_t`

`std::array` is implemented as a template struct whose declaration looks like this:

```cpp
template<typename T, std::size_t N> // N is a non-type template parameter
struct array;
```

As you can see, the non-type template parameter representing the array length (`N`) has type `std::size_t`. And as you’re probably aware by now, `std::size_t` is a large unsigned integral type.

>[!Important]
>The length of the std::array must be constant expression (constexpr).

>Thus, when we define a `std::array`, the length non-type template argument must either have type `std::size_t`, or be convertible to a value of type `std::size_t`. Because this value must be constexpr, we don’t run into sign conversion issues when we use a signed integral value, as the compiler will happily convert a signed integral value to a `std::size_t` at compile-time without it being considered a narrowing conversion.

### The length and indices of `std::array` have type `size_type`, which is always `std::size_t`

Just like a `std::vector`, `std::array` defines a nested typedef member named `size_type`, which is an alias for the type used for the length (and indices, if supported) of the container. In the case of `std::array`, `size_type` is _always_ an alias for `std::size_t`.

Note that the non-type template parameter defining the length of the `std::array` is explicitly defined as `std::size_t` rather than `size_type`. This is because `size_type` is a member of `std::array`, and isn’t defined at that point. This is the only place that uses `std::size_t` explicitly -- everywhere else uses `size_type`.

```cpp
template <typename Container>
void printIndices(const Container& c) {
    for (typename Container::size_type i = 0; i < c.size(); ++i) {
        std::cout << i << " ";
    }
}
```

- Works for `std::array`, `std::vector`, `std::deque`, etc.
    
- If instead you wrote `std::size_t`, it would still work in practice (since most containers use `std::size_t`), but using `size_type` makes it **more correct and future-proof**.

### Getting the length of a `std::array`

There are three common ways to get the length of a `std::array` object.

First, we can ask a `std::array` object for its length using the `size()` member function (which returns the length as unsigned `size_type`):

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array arr { 9.0, 7.2, 5.4, 3.6, 1.8 };
    std::cout << "length: " << arr.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    return 0;
}
```

This prints:

length: 5

Second, in C++17, we can use the `std::size()` non-member function (which for `std::array` just calls the `size()` member function, thus returning the length as unsigned `size_type`).

Finally, in C++20, we can use the `std::ssize()` non-member function, which returns the length as a large _signed_ integral type (usually`std::ptrdiff_t`):

### Getting the length of a `std::array` as a constexpr value

>Because the length of a `std::array` is constexpr, each of the above functions will return the length of a `std::array` as a constexpr value (even when called on a non-constexpr `std::array` object)! This means we can use any of these functions in constant expressions, and the length returned can be implicitly converted to an `int` without it being a narrowing conversion:

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array arr { 9, 7, 5, 3, 1 }; // note: not constexpr for this example
    constexpr int length{ std::size(arr) }; // ok: return value is constexpr std::size_t and can be converted to int, not a narrowing conversion

    std::cout << "length: " << length << '\n';

    return 0;
}
```

>[!Warning]

#### 🔹 The situation

You want to get the length of a `std::array` at compile time using `std::size`.

#### Works fine in `main`:

```cpp
std::array arr{ 9, 7, 5, 3, 1 };
constexpr int length{ std::size(arr) }; // ✅ okay
```

- Here, the compiler **knows the type**: `std::array<int, 5>`.
    
- `std::size(arr)` returns `5`.
    
- `length` is `constexpr`.

#### Fails in a function:

```cpp
void printLength(const std::array<int, 5> &arr) {
    constexpr int length{ std::size(arr) }; // ❌ compile error
}
```

Why? 🤔

- When you pass `arr` as a **function parameter**, it is treated like a **normal runtime reference**.
    
- Due to a language defect (before C++23), the compiler **doesn’t propagate the fact that `arr.size()` is known at compile time** when the array is passed by reference.
    
- So inside the function, `std::size(arr)` is seen as a **runtime call**, not a constexpr expression.

#### 🔹 Fix in C++23 (P2280)

C++23 fixed this "language defect" (via **P2280**).  
Now, even if the array is passed by reference, the compiler can recognize that its size is **constexpr**.

So this will compile in C++23:

```cpp
void printLength(const std::array<int, 5> &arr) {
    constexpr int length{ std::size(arr) }; // ✅ works in C++23
}
```

### Subscripting `std::array` using `operator[]` or the `at()` member function

we covered that the most common way to index a `std::array` is to use the subscript operator (`operator[]`). No bounds checking is done in this case, and passing in an invalid index will result in undefined behavior.

Just like `std::vector`, `std::array` also has an `at()` member function that does subscripting with runtime bounds checking. We recommend avoiding this function since we typically want to do bounds checking before indexing, or we want compile-time bounds checking.

Both of these functions expect the index to be of type `size_type` (`std::size_t`).

If either of these functions are called with a constexpr value, the compiler will do a constexpr conversion to `std::size_t`. This isn’t considered to be a narrowing conversion, so you won’t run into sign problems here.

However, if either of these functions are called with a non-constexpr signed integral value, the conversion to `std::size_t` is considered narrowing and your compiler may emit a warning.

### `std::get()` does compile-time bounds checking for constexpr indices

#### 1. Background: `std::array` has a fixed size at compile time

A `std::array<T, N>` has two things we care about:

- The **length** (`N`) is known at compile time (a `constexpr`).
    
- We often want to index into it using **indices** that might also be known at compile time.
    

Normally, when indexing:

- `operator[]` → **no bounds checking** (dangerous if wrong).
    
- `at()` → **runtime bounds checking** (slower, but safe at runtime).
    

Neither of these provides **compile-time bounds checking**.

#### 2. Why `constexpr` index matters

If both:

- the array length (`N`) is a `constexpr`, and
    
- the index is also a `constexpr`,
    

then in theory the compiler could verify the index is valid at compile time.  
But:

- function parameters can’t be `constexpr` (so you can’t do `arr[index]` if `index` is passed in).
    
- `operator[]` and `.at()` don’t do compile-time checking.
    

So we need another tool.

#### 3. `std::get` to the rescue

C++ provides a function template:

```cpp
template <std::size_t I, class T, std::size_t N>
constexpr T& get(std::array<T, N>& arr) noexcept;
```

- The **index `I`** is a **non-type template parameter**, so it **must be a `constexpr`**.
    
- This means the compiler **knows the index at compile time**.
    

Inside the implementation of `std::get`, there is a `static_assert(I < N)` which:

- passes if the index is valid,
    
- fails (compilation error) if the index is out of range.

#### 4. Example

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array prime{ 2, 3, 5, 7, 11 };

    std::cout << std::get<3>(prime);  // ✅ prints 7
    std::cout << std::get<9>(prime);  // ❌ compile error, index 9 out of bounds
}
```

- `std::get<3>(prime)` works fine, because `3 < 5`.
    
- `std::get<9>(prime)` fails at **compile time**, not runtime.
    

That’s the key difference: unlike `at()` which throws at runtime, `std::get` stops compilation if you use an invalid index.

#### 5. Why this is powerful

- **Zero runtime overhead** → it’s checked before the program even runs.
    
- **Safety** → impossible to accidentally use an invalid `constexpr` index.
    
- **Performance** → the compiler often inlines it, so it’s just as fast as `operator[]`.

#### ✅ **Summary:**

- `std::get<I>(arr)` requires `I` to be `constexpr`.
    
- It performs **compile-time bounds checking** using `static_assert`.
    
- If `I >= arr.size()`, your program won’t compile.

---
# Passing and returning std::array

An object of type `std::array` can be passed to a function just like any other object. That means if we pass a `std::array` by value, an expensive copy will be made. Therefore, we typically pass `std::array` by (const) reference to avoid such copies.

With a `std::array`, both the element type and array length are part of the type information of the object. Therefore, when we use a `std::array` as a function parameter, we have to explicitly specify both the element type and array length:

```cpp
#include <array>
#include <iostream>

void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD deduces type std::array<int, 5>
    passByRef(arr);

    return 0;
}
```

CTAD doesn’t (currently) work with function parameters, so we cannot just specify `std::array` here and let the compiler deduce the template arguments.

### Using function templates to pass `std::array` of different element types or lengths

#### 1. How `std::array` itself is defined

At its core, `std::array` is just a templated struct:

```cpp
template <typename T, std::size_t N>
struct array;
```

- `T` = element type (e.g., `int`, `double`, `char`…)
    
- `N` = non-type template parameter (array length, must be `std::size_t`)
    

So `std::array<int, 5>` is "an array of 5 `int`s".

#### 2. Function templates for flexibility

If you want a function to accept **any `std::array` of any type and any length**, you make your function a template with the same parameters:

```cpp
template <typename T, std::size_t N>
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // disallow empty arrays
    std::cout << arr[0] << '\n';
}
```

- `T` → element type
    
- `N` → array length
    

When you call `passByRef()` with a `std::array`, the compiler deduces `T` and `N` from the argument.

Example:

```cpp
std::array arr{ 9, 7, 5, 3, 1 };   // CTAD → std::array<int, 5>
passByRef(arr); // compiler generates: passByRef(const std::array<int, 5>&)
```

Another call with a different type or length:

```cpp
std::array arr2{ 1.2, 2.3, 3.4 };  // CTAD → std::array<double, 3>
passByRef(arr2); // compiler generates: passByRef(const std::array<double, 3>&)
```

So **one function template** can cover infinite variations of `std::array`.

#### 3. Why `N` must be `std::size_t`, not `int`

`std::array` is declared with `std::size_t` for its length.

If you mistakenly write:

```cpp
template <typename T, int N> // ❌ wrong
void func(const std::array<T, N>& arr) { ... }
```

then the compiler sees a mismatch:

- `std::array<int, 5>` is really `std::array<int, std::size_t{5}>`
    
- But your template wants `std::array<int, int{5}>`
    

Templates don’t do implicit conversions, so they won’t match.

#### 4. Templating only part of it

You don’t always need both parameters. For example, if you only care about the length and want to force the type to `int`:

```cpp
template <std::size_t N>
void passByRef(const std::array<int, N>& arr)
{
    std::cout << arr[0] << '\n';
}
```

Now:

```cpp
std::array arr{ 9, 7, 5 };  // int, size 3
passByRef(arr); // works

std::array arr2{ 1.2, 3.4 }; // double, size 2
passByRef(arr2); // ❌ error (not std::array<int, N>)
```

This restricts the function to only `int` arrays, but any size.

#### ✅ **Key takeaway**:  
Function templates with `<typename T, std::size_t N>` let you write a single function that automatically adapts to **any element type and array length** of `std::array`.

### Auto non-type template parameters C++20

Having to remember (or look up) the type of a non-type template parameter so that you can use it in a template parameter declaration for your own function templates is a pain.

In C++20, we can use `auto` in a template parameter declaration to have a non-type template parameter deduce its type from the argument:

```cpp
template <typename T, auto N> // now using auto to deduce type of N
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}
```

If your compiler is C++20 capable, this is fine to use.

### Static asserting on array length

#### 🔹 The Problem

You wrote a function template:

```cpp
template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << arr[3] << '\n';
}
```

This assumes **every array passed in has at least 4 elements** (index `3` must exist).  
But templates don’t enforce that — so if someone calls:

```cpp
std::array arr{ 9, 7 }; // size = 2
printElement3(arr);     // index 3 doesn’t exist!
```

👉 This compiles fine, but causes **undefined behavior** at runtime.  
The compiler won’t warn you, because `arr[3]` doesn’t do any bounds checking.

#### 🔹 Two Solutions

##### ✅ 1. Use `std::get<Index>()`

```cpp
std::cout << std::get<3>(arr) << '\n';
```

- `std::get<Index>` takes the index as a **template parameter**, which is a `constexpr`.
    
- The compiler checks at **compile-time** whether `Index` is valid for the array size `N`.
    
- If it’s out of range, compilation **fails immediately** instead of producing undefined behavior.
    

Example:

```cpp
std::array arr{ 9, 7 }; 
printElement3(arr); // ❌ compile error
```

##### ✅ 2. Use `static_assert`

```cpp
template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    static_assert(N > 3, "Array must have at least 4 elements");
    std::cout << arr[3] << '\n';
}
```

- Here we enforce a **precondition**: “this function only works if `N > 3`”.
    
- If someone tries to call it with a smaller array, the compiler **rejects the code**.
    

Example:

```cpp
std::array arr2{ 9, 7 };
printElement3(arr2); // ❌ compile error: static assertion failed
```

#### 🔹 Key Insight

Why not use `static_assert(std::size(arr) > 3)`?

Because:

- `std::size(arr)` is only `constexpr` when `arr` is a local variable, not when it’s a function parameter (prior to **C++23**).
    
- So before C++23, the only thing you can reliably use is the **template parameter `N`**, which is always a compile-time constant.

#### 🚀 Summary

- `operator[]` → **no bounds checking** → can cause runtime UB.
    
- `at()` → **runtime bounds checking**, throws exception if invalid.
    
- `std::get<Index>()` → **compile-time bounds checking**, safe if `Index` is constexpr.
    
- `static_assert(N > k)` → enforce **preconditions at compile time**.
    

👉 Both `std::get()` and `static_assert` are ways to **catch errors early, at compile-time**, instead of letting UB sneak in.

### Returning a `std::array`

Returning a `std::array`

Syntax aside, passing a `std::array` to a function is conceptually simple -- pass it by (const) reference. But what if we have a function that needs to return a `std::array`? Things are a little more complicated. Unlike `std::vector`, `std::array` is not move-capable, so returning a `std::array` by value will make a copy of the array. The elements inside the array will be moved if they are move-capable, and copied otherwise.

There are two conventional options here, and which you should pick depends on circumstances.

### Returning a `std::array` by value

It is okay to return a `std:array` by value when all of the following are true:

- The array isn’t huge.
- The element type is cheap to copy (or move).
- The code isn’t being used in a performance-sensitive context.

In such cases, a copy of the `std::array` will be made, but if all of the above are true, the performance hit will be minor, and sticking with the most conventional way to return data to the caller may be the best choice.

```cpp
#include <array>
#include <iostream>
#include <limits>

// return by value
template <typename T, std::size_t N>
std::array<T, N> inputArray() // return by value
{
	std::array<T, N> arr{};
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

	return arr;
}

int main()
{
	std::array<int, 5> arr { inputArray<int, 5>() };

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

There are a few nice things about this method:

- It uses the most conventional way to return data to the caller.
- It’s obvious that the function is returning a value.
- We can define an array and use the function to initialize it in a single statement.

There are also a few downsides:

- The function returns a copy of the array and all its elements, which isn’t cheap.
- When we call the function, we must explicitly supply the template arguments since there is no parameter to deduce them from.

### Returning a `std::array` via an out parameter

In cases where return by value is too expensive, we can use an out-parameter instead. In this case, the caller is responsible for passing in the `std::array` by non-const reference (or by address), and the function can then modify this array.

```cpp
#include <array>
#include <limits>
#include <iostream>

template <typename T, std::size_t N>
void inputArray(std::array<T, N>& arr) // pass by non-const reference
{
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

}

int main()
{
	std::array<int, 5> arr {};
	inputArray(arr);

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

The primary advantage of this method is that no copy of the array is ever made, so this is efficient.

There are also a few downsides:

- This method of returning data is non-conventional, and it is not easy to tell that the function is modifying the argument.
- We can only use this method to assign values to the array, not initialize it.
- Such a function cannot be used to produce temporary objects.

### Returning a `std::vector` instead

`std::vector` is move-capable and can be returned by value without making expensive copies. If you’re returning a `std::array` by value, your `std::array` probably isn’t constexpr, and you should consider using (and returning) `std::vector` instead.

---
# std::array of class types, and brace elision

>A `std::array` isn’t limited to elements of fundamental types. Rather, the elements of a `std::array` can be any object type, including compound types. This means you can create a `std::array` of pointers, or a `std::array` of structs (or classes)

### Defining and assigning to a `std::array` of structs

Let’s start with a simple struct:

```cpp
struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};
```

Defining a `std::array` of `House` and assigning elements works just like you’d expect:

```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    std::array<House, 3> houses{};

    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
```

The above outputs the following:

House number 13 has 7 rooms.
House number 14 has 10 rooms.
House number 15 has 8 rooms.

### Initializing a `std::array` of structs

Initializing an array of structs also works just like you’d expect, so long as you are explicit about the element type:

```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    constexpr std::array houses { // use CTAD to deduce template arguments <House, 3>
            House{ 13, 1, 7 },
            House{ 14, 2, 5 },
            House{ 15, 2, 4 }
        };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
            << " has " << (house.stories * house.roomsPerStory)
            << " rooms.\n";
    }

    return 0;
}
```

In the above example, we’re using CTAD to deduce the type of the `std::array` as `std::array<House, 3>`. We then provide 3 `House` objects as initializers, which works just fine.

### Initialization without explicitly specifying the element type for each initializer

#### 1. Why explicit `House{...}` works

When you write:

```cpp
constexpr std::array houses {
    House{ 13, 1, 7 },
    House{ 14, 2, 5 },
    House{ 15, 2, 4 }
};
```

You’re explicitly saying: _“Each element of this `std::array` is a `House`, so please construct a `House` here.”_  
The compiler has no ambiguity: each initializer corresponds to one element.

#### 2. Why `{ 13, 1, 7 }` alone doesn’t work

When you try this:

```cpp
constexpr std::array<House, 3> houses {
    { 13, 1, 7 },
    { 14, 2, 5 },
    { 15, 2, 4 }
};
```

It **looks** like you’re giving three `House` initializers.  
But here’s the trick: `std::array` itself is just a **struct with one data member**, which is a raw C-style array inside:

```cpp
template<typename T, std::size_t N>
struct array {
    T elems[N]; // raw array member
};
```

So the compiler interprets your code as:

- First `{ 13, 1, 7 }` → initializing the **only data member** (`elems`).
    
- Then it sees two more `{...}` blocks and says: _“Wait, there’s only one member in `std::array`, why are you trying to initialize more?”_  
    → Compilation error.
    

That’s why it fails.

#### 3. Why double braces fix it

When you add double braces:

```cpp
constexpr std::array<House, 3> houses {{
    { 13, 1, 7 },
    { 14, 2, 5 },
    { 15, 2, 4 }
}};
```

Now it’s clear:

- **Outer braces** → initialize the `std::array` itself (the struct).
    
- **Inner braces** → initialize its only member (`elems`, the C-style array).
    
- Inside that, each `{ ... }` is used to initialize each `House`.
    

So the compiler is happy.

#### 4. Why assignment works differently

With assignment:

```cpp
houses[0] = { 13, 1, 7 };
```

The compiler already knows `houses[0]` is a `House`, so `{ 13, 1, 7 }` is automatically treated as a `House` initializer. No confusion, no double braces.

#### 5. Key takeaway

- `std::array` is technically a wrapper around a C-style array → that’s why the compiler sometimes needs “extra help” (double braces) when doing aggregate initialization.
    
- Other containers like `std::vector` don’t need this, because they use constructors instead of aggregate initialization.

### Brace elision for aggregates

#### 1. Why single braces work sometimes

Recall:  
`std::array` is essentially:

```cpp
template <typename T, std::size_t N>
struct array {
    T elems[N]; // the only member
};
```

So strictly speaking, initializing it should require **two levels of braces**:

- One for the `std::array` itself (struct).
    
- One for its data member (`elems`, the raw C-style array).
    

Example (the "fully correct" way):

```cpp
constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }};
```

But C++ allows **brace elision**:  
If it’s clear what you mean, the compiler lets you **omit some inner braces**.

So this also works:

```cpp
constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 };
```

The compiler implicitly interprets it as if you had written double braces.

#### 2. When brace elision applies

Brace elision rules are a bit messy, but for practical purposes:

✅ You can use **single braces** when:

- Initializing with **scalar types** (e.g., `int`, `double`), because the compiler can unambiguously forward the values into the inner array.
    
- Initializing with **class/struct types where the type is explicitly named** in each element (`House{...}`).
    

❌ You need **double braces** when:

- The element type is a struct/class/array, but you don’t explicitly name the type for each element.  
    Example:

```cpp
constexpr std::array<House, 3> houses {{ // ✅ works
    { 13, 1, 7 },
    { 14, 2, 5 },
    { 15, 2, 4 }
}};
```

If you try single braces here, the compiler gets confused:  
Is `{ 13, 1, 7 }` meant for the `std::array` itself or for the first `House`?

#### 3. No harm in always using double braces

You could _always_ write:

```cpp
constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }};
```

This always works, because you’re being explicit:

- Outer braces = struct (`std::array`)
    
- Inner braces = raw C-style array inside.
    

But for simple types (`int`, `double`), brace elision makes single braces fine — and people usually prefer it for readability.

#### 4. Rule of thumb

- If **single braces compile**, you can safely use them (brace elision kicked in).
    
- If they don’t, just add another pair of braces — that’s the compiler telling you brace elision isn’t allowed here.

👉 In short:  
Brace elision = “the compiler forgivingly lets you drop extra `{}` in obvious cases.”  
It works for scalars and explicit struct initializers, but not for more ambiguous cases like `std::array<House, N>` without explicitly writing `House{...}`.

### Another example

Here’s one more example where we initialize a `std::array` with `Student` structs.

```cpp
#include <array>
#include <iostream>
#include <string_view>

// Each student has an id and a name
struct Student
{
	int id{};
	std::string_view name{};
};

// Our array of 3 students (single braced since we mention Student with each initializer)
constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };

const Student* findStudentById(int id)
{
	// Look through all the students
	for (auto& s : students)
	{
		// Return student with matching id
		if (s.id == id) return &s;
	}

	// No matching id found
	return nullptr;
}

int main()
{
	constexpr std::string_view nobody { "nobody" };

	const Student* s1 { findStudentById(1) };
	std::cout << "You found: " << (s1 ? s1->name : nobody) << '\n';

	const Student* s2 { findStudentById(3) };
	std::cout << "You found: " << (s2 ? s2->name : nobody) << '\n';

	return 0;
}
```

This prints:

You found: Joe
You found: nobody

Note that because `std::array students` is constexpr, our `findStudentById()` function must return a const pointer, which means our `Student` pointers in `main()` must also be const.

--> Explanation of the following above:

#### 1. The setup

We have:

```cpp
constexpr std::array students{
    Student{0, "Alex"},
    Student{1, "Joe"},
    Student{2, "Bob"}
};
```

Because we wrote `constexpr std::array`, this array lives in **read-only memory** at compile time — it’s immutable data.

That means:

- You can read from it in a `constexpr` context.
    
- But you **cannot modify it** at runtime.
    

So, the elements inside `students` are treated as `const Student`.

#### 2. Inside `findStudentById`

Your function is:

```cpp
const Student* findStudentById(int id)
{
    for (auto& s : students) {
        if (s.id == id) return &s;
    }
    return nullptr;
}
```

Why does the return type need to be `const Student*`?

Because `students` is `constexpr`, the compiler treats its elements as **`const Student` objects**.  
You can’t legally return a **non-const `Student*`** pointing into a `const` object, because that would allow the caller to modify a `const` thing.

So the function must promise:

> "I will give you a pointer to a `const Student`. You can look at it, but you may not modify it."

#### 3. In `main`

When you do:

```cpp
const Student* s1 { findStudentById(1) };
```

Notice `s1` is declared as a `const Student*`.  
That’s necessary because `findStudentById()` returns `const Student*`.

If you wrote just `Student* s1`, the compiler would reject it, since it would be unsafe (you’d be pretending to be able to modify an immutable student).

#### 4. What if `students` wasn’t `constexpr`?

If instead we wrote:

```cpp
std::array students{
    Student{0, "Alex"},
    Student{1, "Joe"},
    Student{2, "Bob"}
};
```

Now `students` is a normal runtime array (not `constexpr`).  
In this case, the elements are **mutable `Student` objects**, so `findStudentById()` could return a plain `Student*` (non-const pointer).

Then in `main` you’d be allowed to write:

```cpp
Student* s1 = findStudentById(1);
s1->name = "Changed"; // ✅ legal now
```

But since your array is `constexpr`, that’s forbidden.

✅ **Key point:**  
Because `constexpr std::array` makes its elements `const`, any function returning pointers to its elements must return `const Student*`. And any variable receiving that pointer must also be declared `const Student*`.

---
# Arrays of references via std::reference_wrapper

### std::reference_wrapper

#### 1. Arrays can hold **objects only**

C++ arrays (and `std::array`) can hold **objects**. That includes:

- fundamental types (`int`, `double`, `char`)
    
- compound object types (`int*`, `std::string`, `std::vector<int>`, …)
    

But **references are not objects** — they are just **aliases** for other objects.

So this is **illegal**:

```cpp
std::array<int&, 2> refarr { x, y }; // ❌ compile error
```

because you can’t have an array of references.

#### 2. Why `std::array valarr { ref1, ref2 };` works

If you write:

```cpp
int& ref1 { x };
int& ref2 { y };
std::array valarr { ref1, ref2 };
```

you might think it’s an array of references, but it’s actually an array of **values**.

Reason: when `ref1` and `ref2` are passed into the array, they are **implicitly converted to `int` values** (copied), so `valarr` is really a `std::array<int, 2>`.

That’s why `valarr` does **not** stay tied to `x` and `y`.

#### 3. How to actually make an “array of references”

Since C++ doesn’t allow reference members in arrays, the workaround is to use **`std::reference_wrapper`** (from `<functional>`).

A `std::reference_wrapper<T>` is an **object** that internally holds a reference to a `T`. Since it’s an object, it can go inside arrays and containers.

Example:

```cpp
int x { 1 };
int y { 2 };
int z { 3 };

std::array<std::reference_wrapper<int>, 3> arr { x, y, z };
```

Now `arr` really holds references to `x`, `y`, and `z`.

#### 4. Behavior of `std::reference_wrapper`

- ✅ You can modify the referenced value:

```cpp
arr[1].get() = 5;  // changes y (and arr[1])
```

- The `get()` member function can be used to get a `T&`. This is useful when we want to update the value of the object being referenced.

✅ You can print it:

```cpp
std::cout << arr[1]; // implicitly converts to int& for printing
```

⚠️ If you write:

```cpp
arr[1] = 5;
```

this is ambiguous:

- Do you mean "re-seat the reference wrapper to refer to 5"? (not valid — can’t reference a literal)
    
- Or "assign 5 to the referenced object"?
    

That’s why `get()` is needed when assigning.

#### 5. Why is this useful?

Imagine you want a collection of objects that always “track” some variables rather than copies. With `std::reference_wrapper`, if the original variables change, the array reflects that:

```cpp
x = 42;
std::cout << arr[0]; // prints 42, because arr[0] still references x
```

#### ✅ **In summary:**

- Arrays can’t hold references directly (`int&` is not allowed).
    
- If you try to use references in `std::array`, they decay into values.
    
- To store “references,” use `std::reference_wrapper`, which is an object that behaves like a reference and works in arrays/containers.

### `std::ref` and `std::cref`

- `std::ref(x)` → creates `std::reference_wrapper<T>`
    
- `std::cref(x)` → creates `std::reference_wrapper<const T>`
    
- Before C++17, this avoided writing long template arguments.
    
- After C++17, CTAD makes things easier, but `std::ref`/`std::cref` are still shorter and more readable, so people keep using them.

```cpp
int x { 5 };
auto ref { std::ref(x) };   // C++11, deduces to std::reference_wrapper<int>
auto cref { std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>
```

Of course, now that we have CTAD in C++17, we can also do this:

```cpp
std::reference_wrapper ref1 { x };        // C++17
auto ref2 { std::reference_wrapper{ x }}; // C++17
```

But since `std::ref()` and `std::cref()` are shorter to type, they are still widely used to create `std::reference_wrapper` objects.

---



