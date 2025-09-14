
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
# std::array and enumerations

### Using static assert to ensure the proper number of array initializers

When initializing a `constexpr std::array` using CTAD, the compiler will deduce how long the array should be from the number of initializers. If less initializers are provided than there should be, the array will be shorter than expected, and indexing it can lead to undefined behavior.

For example:

```cpp
#include <array>
#include <iostream>

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    constexpr std::array testScores { 78, 94, 66, 77 }; // oops, only 4 values

    std::cout << "Cartman got a score of " << testScores[StudentNames::cartman] << '\n'; // undefined behavior due to invalid index

    return 0;
}
```

Whenever the number of initializers in a `constexpr std::array` can be reasonably sanity checked, you can do so using a static assert:

```cpp
#include <array>
#include <iostream>

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    constexpr std::array testScores { 78, 94, 66, 77 };

    // Ensure the number of test scores is the same as the number of students
    static_assert(std::size(testScores) == max_students); // compile error: static_assert condition failed

    std::cout << "Cartman got a score of " << testScores[StudentNames::cartman] << '\n';

    return 0;
}
```

That way, if you add a new enumerator later but forget to add a corresponding initializer to `testScores`, the program will fail to compile.

You can also use a static assert to ensure two different `constexpr std::array` have the same length.

### Using constexpr arrays for better enumeration input and output

In lesson [13.5 -- Introduction to overloading the I/O operators](https://www.learncpp.com/cpp-tutorial/introduction-to-overloading-the-i-o-operators/), we covered a few ways to input and output the names of enumerators. To assist in this task, we had helper functions that converted an enumerator to a string and vice-versa. These functions each had their own (duplicate) set of string literals, and we had to specifically code logic to check each:

```cpp
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
```

This means that if we were to add a new enumerator, we’d have to remember to update these functions.

Let’s improve these functions a bit. In cases where the value of our enumerators start at 0 and proceed sequentially (which is true for most enumerations), we can use an array to hold the name of each enumerator.

This allows us to do two things:

1. Index the array using the enumerator’s value to get the name of that enumerator.
2. Use a loop to iterate through all of the names, and be able to correlate a name back to the enumerator based on index.

```cpp
#include <array>
#include <iostream>
#include <string>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    // We can index the array using the enumerator to get the name of the enumerator
    return Color::colorName[static_cast<std::size_t>(color)];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

// Teach operator>> how to input a Color by name
// We pass color by non-const reference so we can have the function modify its value
std::istream& operator>> (std::istream& in, Color::Type& color)
{
    std::string input {};
    std::getline(in >> std::ws, input);

    // Iterate through the list of names to see if we can find a matching name
    for (std::size_t index=0; index < Color::colorName.size(); ++index)
    {
        if (input == Color::colorName[index])
        {
            // If we found a matching name, we can get the enumerator value based on its index
            color = static_cast<Color::Type>(index);
            return in;
        }
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // color = {};
    return in;
}

int main()
{
    auto shirt{ Color::blue };
    std::cout << "Your shirt is " << shirt << '\n';

    std::cout << "Enter a new color: ";
    std::cin >> shirt;
    if (!std::cin)
        std::cout << "Invalid\n";
    else
        std::cout << "Your shirt is now " << shirt << '\n';

    return 0;
}
```

This prints:

Your shirt is blue
Enter a new color: red
Your shirt is now red

### Range-based for-loops and enumerations 

Occasionally we run across situations where it would be useful to iterate through the enumerators of an enumeration. While we can do this using a for-loop with an integer index, this is likely to require a lot of static casting of the integer index to our enumeration type.

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    // Use a for loop to iterate through all our colors
    for (int i=0; i < Color::max_colors; ++i )
        std::cout << static_cast<Color::Type>(i) << '\n';

    return 0;
}
```

Unfortunately, range-based for-loops won’t allow you to iterate over the enumerators of an enumeration:

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    for (auto c: Color::Type) // compile error: can't traverse enumeration
        std::cout << c < '\n';

    return 0;
}
```

There are many creative solutions for this. Since we can use a range-based for-loop on an array, one of the most straightforward solutions is to create a `constexpr std::array` containing each of our enumerators, and then iterate over that. This method only works if the enumerators have unique values.

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,     // 0
        red,       // 1
        blue,      // 2
        max_colors // 3
    };

    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };
    static_assert(std::size(colorName) == max_colors);

    constexpr std::array types { black, red, blue }; // A std::array containing all our enumerators
    static_assert(std::size(types) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    for (auto c: Color::types) // ok: we can do a range-based for on a std::array
        std::cout << c << '\n';

    return 0;
}
```

In the above example, since the element type of `Color::types` is `Color::Type`, variable `c` will be deduced as a `Color::Type`, which is exactly what we want!

This prints:

black
red
blue

---
# Introduction to C-style arrays

C-style arrays were inherited from the C language, and are built-in to the core language of C++ (unlike the rest of the array types, which are standard library container classes). This means we don’t need to `#include` a header file to use them.

### Declaring a C-style array

Because they are part of the core language, C-style arrays have their own special declaration syntax. In an C-style array declaration, we use square brackets (`[]`) to tell the compiler that a declared object is a C-style array. Inside the square brackets, we can optionally provide the length of the array, which is an integral value of type `std::size_t` that tells the compiler how many elements are in the array.

The following definition creates a C-style array variable named `testScore` which contains 30 elements of type `int`:

```cpp
int main()
{
    int testScore[30] {};      // Defines a C-style array named testScore that contains 30 value-initialized int elements (no include required)

//  std::array<int, 30> arr{}; // For comparison, here's a std::array of 30 value-initialized int elements (requires #including <array>)

    return 0;
}
```

>The length of a C-style array must be at least 1. The compiler will error if the array length is zero, negative, or a non-integral value.

### The array length of a c-style array must be a constant expression

Just like `std::array`, when declaring a C-style array, the length of the array must be a constant expression (of type `std::size_t`, though this typically doesn’t matter).

### Subscripting a C-style array

Just like with a `std::array`, C-style arrays can be indexed using the subscript operator (`operator[]`):

```cpp
#include <iostream>

int main()
{
    int arr[5]; // define an array of 5 int values

    arr[1] = 7; // use subscript operator to index array element 1
    std::cout << arr[1]; // prints 7

    return 0;
}
```

>Unlike the standard library container classes (which use unsigned indices of type `std::size_t` only), the index of a C-style array can be a value of any integral type (signed or unsigned) or an unscoped enumeration. This means that C-style arrays are not subject to all of the sign conversion indexing issues that the standard library container classes have!

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    int s { 2 };
    std::cout << arr[s] << '\n'; // okay to use signed index

    unsigned int u { 2 };
    std::cout << arr[u] << '\n'; // okay to use unsigned index

    return 0;
}
```

>[!Tip]
>C-style arrays will accept signed or unsigned indexes (or unscoped enumerations).

>[!As an aside]
>When declaring an array (e.g. `int arr[5]`), the use of `[]` is part of the declaration syntax, not an invocation of the subscript operator `operator[]`.

### Aggregate initialization of C-style arrays

#### **1. What is aggregate initialization?**

- An _aggregate_ in C++ is basically a class or type (like arrays, structs, or `std::array`) that can be initialized by directly listing its members in **braces `{}`**.
    
- For C-style arrays, aggregate initialization just means we can give the elements directly in braces, in order.
    

Example:

```cpp
int fib[6] = {0, 1, 1, 2, 3, 5}; // initializes fib[0]..fib[5]
int primes[5]{2, 3, 5, 7, 11};   // same thing (preferred modern style)
```

#### **2. Default initialization vs value initialization**

If you don’t provide initializers, the behavior depends on how you define the array:

```cpp
int arr1[5];    // default initialization -> uninitialized garbage values
int arr2[5] {}; // value initialization -> all elements set to 0
```

👉 Always prefer `{}` so you don’t get random garbage.

#### **3. Too many or too few initializers**

- If you give **more elements than the size**, you get a compile error:

```cpp
int a[4]{1, 2, 3, 4, 5}; // ❌ error (too many)
```

If you give **fewer elements**, the rest are value-initialized (zero for ints):

```cpp
int b[4]{1, 2}; // becomes {1, 2, 0, 0}
```

#### **4. Downsides of C-style arrays**

- You must explicitly write the type:

```cpp
int numbers[3]{1, 2, 3}; // must specify `int`
```

You **can’t use `auto` with them**:

```cpp
auto squares[5]{1, 4, 9, 16, 25}; // ❌ compile error
```

because `auto` doesn’t work with raw arrays.

👉 But with `std::array` or `std::vector`, you can use `auto` (thanks to CTAD in C++17+).

#### ✅ **Summary**:  
C-style arrays can be aggregate-initialized with braces. Uninitialized arrays give garbage, `{}` gives zeros. Too many values = error, fewer = zeros fill. But C-style arrays are limited (no type deduction, unsafe), which is why modern C++ prefers `std::array` or `std::vector`.

### Omitted length

There’s a subtle redundancy in the following array definition. See it?

```cpp
int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // prime has length 5

    return 0;
}
```

We’re explicitly telling the compiler the array has length 5, and then we’re also initializing it with 5 elements. When we initialize a C-style array with an initializer list, we can omit the length (in the array definition) and let the compiler deduce the length of the array from the number of initializers.

The following array definitions behave identically:

```cpp
int main()
{
    const int prime1[5] { 2, 3, 5, 7, 11 }; // prime1 explicitly defined to have length 5
    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 deduced by compiler to have length 5

    return 0;
}
```

This only works when initializers are explicitly provided for all array members.

```cpp
int main()
{
    int bad[] {}; // error: the compiler will deduce this to be a zero-length array, which is disallowed!

    return 0;
}
```

When using an initializer list to initialize all elements of a C-style array, it’s preferable to omit the length and let the compiler calculate the length of the array. That way, if initializers are added or removed, the length of the array will automatically adjust, and we are not at risk for a mismatch between the defined array length and number of initializers provided.

>[!Best Practice]
>Prefer omitting the length of a C-style array when explicitly initializing every array element with a value.

### Const and constexpr C-style arrays

>Just like `std::array`, C-style arrays can be `const` or `constexpr`. Just like other const variables, const arrays must be initialized, and the value of the elements cannot be changed afterward.

```cpp
#include <iostream>

namespace ProgramData
{
    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // an array of constexpr int
}

int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // an array of const int
    prime[0] = 17; // compile error: can't change const int

    return 0;
}
```

### The sizeof a C-style array

In previous lessons, we used the `sizeof()` operator to get the size of an object or type in bytes. Applied to a C-style array, `sizeof()` returns the number of bytes used by the entire array:

```cpp
#include <iostream>

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 }; // the compiler will deduce prime to have length 5

    std::cout << sizeof(prime); // prints 20 (assuming 4 byte ints)

    return 0;
}
```

Assuming 4 byte ints, the above program prints `20`. The `prime` array contains 5 `int` elements that are 4 bytes each, so 5 * 4 = 20 bytes.

Note that there is no overhead here. An C-style array object contains its elements and nothing more.

### Getting the length of a C-style array

In C++17, we can use `std::size()` (defined in the `<iterator>` header), which returns the array length as an unsigned integral value (of type `std::size_t`). In C++20, we can also use `std::ssize()`, which returns the array length as a signed integral value (of a large signed integral type, probably `std::ptrdiff_t`).

```cpp
#include <iostream>
#include <iterator> // for std::size and std::ssize

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };   // the compiler will deduce prime to have length 5

    std::cout << std::size(prime) << '\n';  // C++17, returns unsigned integral value 5
    std::cout << std::ssize(prime) << '\n'; // C++20, returns signed integral value 5

    return 0;
}
```

>[!Tip]
>The canonical header for the definition of `std::size()` and `std::ssize()` is `<iterator>`. However, because these functions are so useful, many other headers also make them available, including `<array>` and `<vector>`. When using `std::size()` or `std::ssize()` on a C-style array, we may not have already included one of the other headers. In such a case, the `<iterator>` header is the one that’s conventionally included.

### C-style arrays don’t support assignment

Perhaps surprisingly, C++ arrays don’t support assignment:

```cpp
int main()
{
    int arr[] { 1, 2, 3 }; // okay: initialization is fine
    arr[0] = 4;            // assignment to individual elements is fine
    arr = { 5, 6, 7 };     // compile error: array assignment not valid

    return 0;
}
```

Technically, this doesn’t work because assignment requires the left-operand to be a modifiable lvalue, and C-style arrays are not considered to be modifiable lvalues.

---
# C-style array decay

### Problem in C

#### 📌 The challenge

```cpp
#include <iostream>

void printElementZero(int arr[1000])
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[1000] { 5 };   // define an array with 1000 elements, x[0] is initialized to 5
    printElementZero(x);

    return 0;
}
```

C had **two big problems** when it came to passing arrays (C-style array) to functions:

1. **Performance**:  
    Copying a whole array (like `int arr[1000]`) into a function parameter every time would be _very expensive_ in both time and memory.  
    Unlike a single `int`, an array might contain thousands of elements.
    
2. **Flexibility**:  
    We want one function to handle arrays of _any length_.  
    Writing:

```cpp
void printElementZero(int arr[7]);
void printElementZero(int arr[1000]);
```

	 for every possible size is not practical.
    

But **C didn’t have references or templates** to solve this elegantly (those came later in C++).

```cpp
#include <iostream>

void printElementZero(int arr[1000]) // doesn't make a copy
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[7] { 5 };      // define an array with 7 elements
    printElementZero(x); // somehow works!

    return 0;
}
```

Somehow, the above example passes a 7 element array to a function expecting a 1000 element array, without any copies being made. In this lesson, we’ll explore how this works.

We’ll also take a look at why the solution the C designers picked is dangerous, and not well suited for use in modern C++.

But first, we need to cover two subtopics.

### Array to pointer conversions (array decay)

>In most cases, when a C-style array is used in an expression, the array will be implicitly converted into a pointer to the element type, initialized with the address of the first element (with index 0). Colloquially, this is called **array decay** (or just **decay** for short).

```cpp
#include <iomanip> // for std::boolalpha
#include <iostream>

int main()
{
    int arr[5]{ 9, 7, 5, 3, 1 }; // our array has elements of type int

    // First, let's prove that arr decays into an int* pointer

    auto ptr{ arr }; // evaluation causes arr to decay, type deduction should deduce type int*
    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // Prints true if the type of ptr is int*

    // Now let's prove that the pointer holds the address of the first element of the array

    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

    return 0;
}
```

#### 📌 What is happening?

```cpp
int arr[5]{ 9, 7, 5, 3, 1 };
```

- `arr` here is a **C-style array object**.
    
- Its type is `int[5]` → “array of 5 ints”.
    
- At this point, it actually knows its length (`5`) at compile time.

Now:

```cpp
auto ptr{ arr };
```

- When you use `arr` in most expressions, the compiler **automatically converts it (decays) into a pointer** to its first element.
    
- So `arr` becomes `&arr[0]`.
    
- That means `auto ptr` deduces to `int*`.
    

The program then checks this with `typeid` and prints `true`. ✅

#### 📌 Important distinction: Array ≠ Pointer

- **Array (`int[5]`)**:  
    A real object in memory that contains _5 ints back-to-back_.  
    The type `int[5]` includes its length.
    
- **Pointer (`int*`)**:  
    A variable that stores a _memory address_.  
    The type `int*` knows nothing about how many elements exist beyond that address.
    

👉 That’s why the text says:

> The term “decay” indicates this loss of length type information.

When `arr` decays to a pointer, you lose the fact that it had length `5`.

#### 📌 Verifying the pointer value

```cpp
std::cout << (&arr[0] == ptr);
```

- `&arr[0]` is the address of the first element.
    
- `ptr` is the decayed pointer (which is also `&arr[0]`).
    
- They are equal, so the program prints `true`.

## 📌 Special cases where decay does NOT happen

Normally arrays decay into pointers, **but not always**.  
Some exceptions:

1. **`sizeof(arr)`**
    
    - Here `arr` is treated as an array type, not a pointer.
        
    - `sizeof(arr)` gives the total size: `5 * sizeof(int)`.
        
2. **`typeid(arr)`**
    
    - Will show type `int[5]`, not `int*`.
        
3. **`&arr`**
    
    - Gives you the address of the _whole array_, not just the first element.
        
    - Type: `int (*)[5]` (pointer to an array of 5 ints), different from `int*`.
        
4. **Pass by reference**

```cpp
void func(int (&arr)[5]); // takes reference to array of exactly 5 ints
```

	Here decay is prevented, and the function still knows the size.

#### 📌 Why this matters

- Because arrays decay silently, many C programmers mistakenly think _arrays are pointers_.  
    They are not — they just convert easily into one.
    
- After decay, you can index `ptr[2]` like an array, but the pointer itself doesn’t know how many elements are valid. If you go past 5, you hit undefined behavior.
    
- This is why modern C++ prefers `std::array` or `std::vector`, since they **keep size information** and provide bounds-safe operations.
    

#### ✅ Key takeaway

- `int arr[5]` has type `int[5]`.
    
- In most expressions, it _decays_ into `int*` → pointer to first element. (initialized to first element)
    
- **Decay loses size information** (only the starting address remains).
    
- Arrays ≠ Pointers, but arrays decay into pointers most of the time.

### Subscripting a C-style array actually applies `operator[]` to the decayed pointer

#### 1. Arrays decay into pointers

When you use a C-style array in an expression, the compiler automatically converts it into a pointer to its first element.

Example:

```cpp
const int arr[] { 9, 7, 5, 3, 1 };
const int* ptr { arr }; // arr decays into &arr[0]
```

Here:

- `arr` has type `const int[5]` (an array of 5 ints).
    
- But in most expressions, it _decays_ to `const int*` (pointer to the first element).
    
- So `ptr` now holds the same address as `&arr[0]`.

#### 2. Subscript operator on arrays is really on the pointer

When you write:

```cpp
std::cout << arr[2];
```

What actually happens is:

1. `arr` decays to a pointer → type `const int*` pointing at `arr[0]`.
    
2. Then `arr[2]` is interpreted as:

```cpp
*(arr + 2)
```

 - Move 2 elements forward from `arr[0]`
      
- Dereference → gives you `arr[2]` (value 5).
      

So **subscripting an array is just pointer arithmetic under the hood**.

#### 3. Subscript works on pointers directly

Since `arr` decays to a pointer anyway, you can also use subscripting on a pointer:

```cpp
const int* ptr { arr }; // arr decays into &arr[0]
std::cout << ptr[2];    // same as *(ptr + 2), prints 5
```

This works because `operator[]` is defined for pointers as well.

#### 4. Key insight

- `arr[2]` and `ptr[2]` do the exact same thing (if `ptr` points to `arr[0]`).
    
- That’s why C treats arrays and pointers as being “interchangeable” in many cases.
    
- But ⚠️ an **array is not the same thing as a pointer**:
    
    - Array has size info (`int[5]` knows it has 5 elements).
        
    - Pointer loses that info (`int*` only knows where it points).

### Array decay solves our C-style array passing issue

#### 1. Arrays normally don’t copy

If arrays worked like other objects, this would happen:

```cpp
void printArray(int arr[5]) { ... } // looks like pass by value
```

- You’d expect a full copy of the array.
    
- That would be expensive (especially for big arrays).
    

But **C++ doesn’t do that**. Instead, the array _decays_ to a pointer.

#### 2. Array decay when passing to functions

When you pass an array to a function:

```cpp
void func(const int* arr);

const int nums[5] { 1,2,3,4,5 };
func(nums);
```

- `nums` is of type `const int[5]`.
    
- At the function call, it **decays** into a `const int*` → pointer to the first element.
    
- That pointer is passed to the function.
    

So inside `func`, `arr` just points to the same memory as `nums`.  
➡️ No copy is made, memory-efficient.

#### 3. Why different lengths still work

Arrays of different lengths are technically **different types**:

- `const int[5]`
    
- `const int[8]`
    

You normally can’t assign one to the other. But when they decay:

- `const int[5] → const int*`
    
- `const int[8] → const int*`
    

Now both are the _same type_ → `const int*`.  
That’s why this works:

```cpp
void printElementZero(const int* arr) {
    std::cout << arr[0];
}

const int prime[]   { 2,3,5,7,11 };           // const int[5]
const int squares[] { 1,4,9,25,36,49,64,81 }; // const int[8]

printElementZero(prime);   // passes const int*
printElementZero(squares); // also passes const int*
```

Output:

```cpp
2
1
```

#### 4. Key insights

- ✅ **Arrays always decay** into pointers when passed to functions (unless passed by reference).
    
- ✅ That’s why no copy happens — we’re effectively passing by address.
    
- ✅ Different-sized arrays become interchangeable, since both decay into the same pointer type.
    
- ⚠️ **Danger**: the size info is lost. Inside `printElementZero`, you only know you have a `const int*`, but not how many elements exist. That’s why you need to separately pass the array size if you want to loop:

>Because a C-style array is passed by address, the function has direct access to the array passed in (not a copy) and can modify its elements. For this reason, it’s a good idea to make sure your function parameter is const if your function does not intend to modify the array elements.

### C-style array function parameter syntax

#### 1. The root problem

When you write a function like this:

```cpp
void printElementZero(const int* arr);
```

- Technically correct ✅
    
- But to someone reading the function declaration, `arr` just looks like _a pointer to a single int_.
    
- It’s not obvious that the function is really meant to take a **whole array (decayed to a pointer)**.

#### 2. The array parameter syntax

C++ lets you write the same function like this:

```cpp
void printElementZero(const int arr[]);
```

- The compiler **treats this exactly the same as** `const int* arr`.
    
- But for a human reader, `arr[]` gives a _hint_:  
    → “this parameter is supposed to represent an array (decayed to a pointer), not just any pointer.”
    

So it’s more expressive / self-documenting.

#### 3. No size information

You might think:

```cpp
void func(const int arr[5]);
```

means “an array of 5 ints.”  
❌ Wrong — the `[5]` is ignored by the compiler. It’s still just a `const int*`.

So these three are **all equivalent**:

```cpp
void func(const int* arr);
void func(const int arr[]);
void func(const int arr[123456]); // size ignored
```

#### 4. Example

```cpp
#include <iostream>

void printElementZero(const int arr[]) {
    std::cout << arr[0]; // works fine, arr is just a const int*
}

int main() {
    const int prime[]   { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);   // prime decays → const int*
    printElementZero(squares); // squares decays → const int*
}
```

Output:

```Output
2
1
```

#### 5. Best practice

- ✅ If your function **expects a decayed array**, write the parameter as `int arr[]` (or `const int arr[]`).  
    → This communicates intent better than `int* arr`.
    
- ⚠️ But remember: it’s still just a pointer! The array size information is lost.
    

If you really need the size:

- Pass it separately (`void func(int arr[], int size)`), or
    
- Use **references to arrays** (`template<size_t N> void func(int (&arr)[N])`), or
    
- Prefer modern containers (`std::array`, `std::vector`) which carry size with them.

#### 👉 In short:  
`int* arr` and `int arr[]` are **100% identical to the compiler**, but `arr[]` makes it clearer to humans that “this is meant to represent an array.”

### The problems with array decay

#### ⚡ 1. Loss of size information

When an array decays into a pointer, it **forgets how big it was**.

Example:

```cpp
int arr[]{ 3, 2, 1 };

std::cout << sizeof(arr) << '\n'; // 12 (3 ints, each 4 bytes)

printArraySize(arr); // passes pointer
```

Inside the function:

```cpp
void printArraySize(int arr[]) {
    std::cout << sizeof(arr) << '\n'; // 4 (size of a pointer, not array!)
}
```

So:

- At the call site, `arr` is a real array → `sizeof(arr)` is 12.
    
- Inside the function, `arr` has decayed to `int*` → `sizeof(arr)` is 4 or 8 depending on system.
    

👉 This makes `sizeof(arr) / sizeof(*arr)` dangerous if you accidentally call it on a decayed array.

#### ⚡ 2. Refactoring hazards

Suppose you have working code:

```cpp
int arr[]{ 1, 2, 3 };
std::cout << sizeof(arr) / sizeof(*arr); // works → prints 3
```
Now you refactor:

```cpp
void foo(int arr[]) {
    std::cout << sizeof(arr) / sizeof(*arr); // prints pointer size / int size → wrong
}
```

Same code, different meaning, silent bug.  
👉 This makes splitting code into functions risky with C-style arrays.

#### ⚡ 3. Undefined behavior from unknown length

The biggest danger: **the function has no clue how many elements exist**.

Example:

```cpp
void printElement2(int arr[]) {
    std::cout << arr[2] << '\n'; // assumes at least 3 elements
}

int a[]{ 3, 2, 1 };
printElement2(a);  // ✅ okay

int b[]{ 7, 6 };
printElement2(b);  // ❌ UB (index out of bounds)

int c{ 9 };
printElement2(&c); // ❌ compiles, but UB (not even an array!)
```

Because there’s no size info, the function can’t enforce preconditions.  
This can lead to subtle and dangerous runtime errors.

Fortunately, C++17’s better replacement `std::size()` (and C++20’s `std::ssize()`) will fail to compile if passed a pointer value:

#### ⚡ 4. Traversal is hard

How do you know when to stop iterating?

```cpp
void printAll(int arr[]) {
    // No way to know where the array ends!
    for (int i = 0; ???; ++i)
        std::cout << arr[i];
}
```

Without the size passed separately, you’re stuck. Historically, C used _sentinel values_ (like `'\0'` in C-strings) to mark the end, but that doesn’t generalize to all arrays.

Fortunately, C++17’s better replacement `std::size()` (and C++20’s `std::ssize()`) will fail to compile if passed a pointer value:

#### ✅ Modern fixes

To avoid all these pitfalls:

- Use **`std::array`** when the size is fixed at compile time.
    
- Use **`std::vector`** when the size is dynamic.
    
- Use **`std::span` (C++20)** to pass views of arrays/vectors with both pointer and length.
    
- Or, pass the array by reference with templates:

```cpp
template <std::size_t N>
void printElement2(const int (&arr)[N]) {
    if constexpr (N > 2)
        std::cout << arr[2] << '\n';
}
```

👉 **Key takeaway**:  
Array decay solved C’s performance and flexibility problems, but at the cost of **safety and correctness**. That’s why in modern C++, you should avoid raw arrays for most work and use standard containers or spans instead.

### Working around array length issues

==optional read

Historically, programmers have worked around the lack of array length information via one of two methods.

First, we can pass in both the array and the array length as separate arguments:

```cpp
#include <cassert>
#include <iostream>

void printElement2(const int arr[], int length)
{
    assert(length > 2 && "printElement2: Array too short"); // can't static_assert on length

    std::cout << arr[2] << '\n';
}

int main()
{
    constexpr int a[]{ 3, 2, 1 };
    printElement2(a, static_cast<int>(std::size(a)));  // ok

    constexpr int b[]{ 7, 6 };
    printElement2(b, static_cast<int>(std::size(b)));  // will trigger assert

    return 0;
}
```

However, this still has a number of issues:

- The caller needs to make sure that the array and the array length are paired -- if the wrong value for length is passed in, the function will still malfunction.
- There are potential sign conversion issues if you’re using `std::size()` or a function that returns a length as `std::size_t`.
- Runtime asserts only trigger when encountered at runtime. If our testing path doesn’t cover all calls to the function, there’s a risk of shipping a program to the customer that will assert when they do something we didn’t explicitly test for. In modern C++, we’d want to use `static_assert` for compile-time validation of the array length of constexpr arrays, but there’s no easy way to do this (as function parameters can’t be constexpr, even in constexpr or consteval functions!).
- This method only works if we’re making an explicit function call. If the function call is implicit (e.g. we’re calling an operator with the array as an operand), then there’s no opportunity to pass in the length.

Second, if there is an element value that is not semantically valid (e.g. a test score of `-1`), we can instead mark the end of the array using an element of that value. That way, the length of the array can be calculated by counting how many elements exist between the start of the array and this terminating element. The array can also be traversed by iterating from the start until we hit the terminating element. The nice thing about this method is that it works even with implicit function calls.

Key insight

C-style strings (which are C-style arrays) use a null-terminator to mark the end of the string, so that they can be traversed even if they have decayed.

But this method also has a number of issues:

- If the terminating element does not exist, traversal will walk right off the end of the array, causing undefined behavior.
- Functions that traverse the array need special handling for the terminating element (e.g. a C-style string print function needs to know not to print the terminating element).
- There is a mismatch between the actual array length and the number of semantically valid elements. If the wrong length is used, the semantically invalid terminating element may be “processed”.
- This approach only works if a semantically invalid value exists, which is often not the case.

### C-style arrays should be avoided in most cases

>Because of the non-standard passing semantics (pass by address is used instead of pass by value) and risks associated with decayed arrays losing their length information, C-style arrays have generally fallen out of favor. We recommend avoiding them as much as possible.

>[!Best Practice]
>Avoid C-style arrays whenever practical.
>
>>- Prefer `std::string_view` for read-only strings (string literal symbolic constants and string parameters).
>>- Prefer `std::string` for modifiable strings.
>>- Prefer `std::array` for non-global constexpr arrays.
>>- Prefer `std::vector` for non-constexpr arrays.
>
>It is okay to use C-style arrays for global constexpr arrays. We’ll discuss this in a moment.

### C-style arrays can be passed by reference

#### 🔹 Normal behavior (decay)

Normally, when you pass a C-style array to a function:

```cpp
void foo(int arr[]) { }  // really int* arr

int main() {
    int arr[5]{ 1, 2, 3, 4, 5 };
    foo(arr);  // arr decays → int* 
}
```

👉 The array _decays_ into a pointer → the function doesn’t know the array length anymore.

#### 🔹 Passing by reference (no decay at the call site)

You can **prevent decay** by making the function parameter a reference to an array:

```cpp
void foo(int (&arr)[5]) {   // reference to array of 5 ints
    std::cout << sizeof(arr) / sizeof(*arr) << '\n';
}

int main() {
    int arr[5]{ 1, 2, 3, 4, 5 };
    foo(arr); // ✅ No decay here
}
```

Here:

- `int (&arr)[5]` means _“arr is a reference to an array of exactly 5 ints”_.
    
- No decay happens at the call site → inside the function, `sizeof(arr)` is 20 (if ints are 4 bytes).
    
- This fixes the size-loss problem.

#### 🔹 The catch: fixed size

The downside?  
That function only works for arrays of **exactly 5 ints**. If you try:

```cpp
int arr2[7]{};
foo(arr2);  // ❌ compile error, wrong size
```

it won’t compile.  
So this isn’t very flexible unless you add templates.

#### 🔹 Using templates to handle different sizes

You can generalize with a template:

```cpp
template <std::size_t N>
void foo(int (&arr)[N]) {   // reference to array of N ints
    std::cout << N << '\n'; // we know the size at compile time!
}
```

### So when are C-style arrays used in modern C++?

In modern C++, C-style arrays are typically used in two cases:

1. To store constexpr global (or constexpr static local) program data. Because such arrays can be accessed directly from anywhere in the program, we do not need to pass the array, which avoids decay-related issues. The syntax for defining C-style arrays can be a little less wonky than `std::array`. More importantly, indexing such arrays does not have sign conversion issues like the standard library container classes do.
2. As parameters to functions or classes that want to handle non-constexpr C-style string arguments directly (rather than requiring a conversion to `std::string_view`). There are two possible reasons for this: First, converting a non-constexpr C-style string to a `std::string_view` requires traversing the C-style string to determine its length. If the function is in a performance critical section of code and the length isn’t needed (e.g. because the function is going to traverse the string anyway) then avoiding the conversion may be useful. Second, if the function (or class) calls other functions that expect C-style strings, converting to a `std::string_view` just to convert back may be suboptimal (unless you have other reasons for wanting a `std::string_view`).

>Explanation of 2:

Sometimes functions/classes accept raw C-style strings (`const char*`) instead of `std::string_view` for efficiency.

- **Reason 1**: Converting to `std::string_view` requires scanning the C-string to find its length, which may be wasted work if the length isn’t needed.
    
- **Reason 2**: If the function just forwards the string to another API that already expects a C-style string, converting back and forth is unnecessary overhead.

---
# Pointer arithmetic and subscripting

we mentioned that arrays are stored sequentially in memory. In this lesson, we’ll take a deeper look at how arrays indexing math works.

Although we won’t use the indexing math in future lessons, the topics covered in this lesson will give you insight into how range-based for loops actually work, and will come in handy again later when we cover iterators.

### What is pointer arithmetic?

**Pointer arithmetic** is a feature that allows us to apply certain integer arithmetic operators (addition, subtraction, increment, or decrement) to a pointer to produce a new memory address.

Given some pointer `ptr`, `ptr + 1` returns the address of the _next object_ in memory (based on the type being pointed to). So if `ptr` is an `int*`, and an `int` is 4 bytes, `ptr + 1` will return the memory address that is 4 bytes after `ptr`, and `ptr + 2` will return the memory address that is 8 bytes after `ptr`.

#### Example with `int*` (assume `int` = 4 bytes):

```cpp
int x {};
const int* ptr{ &x };

std::cout << ptr << '\n';     // prints address of x
std::cout << ptr + 1 << '\n'; // address + 4 bytes
std::cout << ptr + 2 << '\n'; // address + 8 bytes
```

If `ptr = 00AFFD80`, then:

- `ptr + 1 = 00AFFD84`
    
- `ptr + 2 = 00AFFD88`
    

So the pointer **jumps by 4 bytes** each time (because `sizeof(int) == 4`).

#### 🔹 Increment & Decrement (`++` and `--`)

They are just shorthand:

- `++ptr` → `ptr = ptr + 1`
    
- `--ptr` → `ptr = ptr - 1`

They also assigns the new address to the pointer!
#### 🔹 Key insight

Pointer arithmetic moves to the **next/previous object of that type**, not just the next memory byte.

For example:

- `double*` would move by 8 bytes per step (if `sizeof(double) == 8`).
    
- `char*` would move by 1 byte per step (since `sizeof(char) == 1`).

#### ⚠️ Warning

Pointer arithmetic is only **well-defined inside arrays**.  
Outside arrays (like just taking `&x` and then doing `ptr + 1`) → it’s **undefined behavior** (though compilers usually let it slide).

### Subscripting is implemented via pointer arithmetic

#### 1. **What “subscripting is implemented via pointer arithmetic” means**

When you write something like:

```cpp
ptr[n]
```

the compiler **doesn’t** treat it as a special operator only for arrays. Instead, it literally translates it into:

```cpp
*(ptr + n)
```

That is:

1. Move `n` elements forward from the memory location `ptr` points to.
    
2. Dereference that new location to access the value.
    

So **subscript `[]` is just shorthand for pointer arithmetic**.

#### 2. **Step-by-step with your first example**

```cpp
const int arr[] { 9, 7, 5, 3, 1 };
const int* ptr{ arr }; // arr decays to &arr[0]
std::cout << ptr[2];   // prints 5
```

- `arr` → decays to a pointer to the first element (`&arr[0]`).
    
- `ptr` → now holds the address of element `0` (which stores `9`).
    
- `ptr[2]` → compiler rewrites as `*(ptr + 2)`.
    
    - `ptr + 2` → pointer arithmetic: move forward `2 × sizeof(int)` bytes.
        
    - If `ptr` was pointing to `arr[0]`, then `ptr + 2` points to `arr[2]`.
        
    - Dereferencing → gives the value `5`.

#### 3. **Why does pointer arithmetic work like this?**

Because array elements are stored **contiguously** in memory:

```cpp
arr[0]   arr[1]   arr[2]   arr[3]   arr[4]
  9        7        5        3        1
 ↑
 ptr
```

- `arr` points to the beginning.
    
- `(arr + 1)` points to the next element.
    
- `(arr + 2)` points to the second element past the start.
    

This works because the compiler knows the **size of each element** (e.g., `int` is 4 bytes on your machine).  
So `(arr + 1)` really means: _add `1 × sizeof(int)` bytes to the address_.

That’s why you saw addresses like:

```cpp
00AFFD80   00AFFD84   00AFFD88
```

Each one is `+4` from the previous.

### 4.  Why arrays start at index 0

If arrays were 1-based, the compiler would need to do `*(ptr + (n-1))` for every lookup.  
With **0-based indexing**, the math is cleaner:

- `arr[0]` → `*(arr + 0)` → first element directly.
    
- `arr[1]` → `*(arr + 1)` → second element.  
    Efficient and no extra subtraction.

#### 5. **Weird trivia: `n[ptr]` works**

Since:

```cpp
ptr[n] == *(ptr + n)
```

and addition is commutative (`a + b == b + a`):

```cpp
ptr[n] == *(n + ptr) == n[ptr]
```

So yes, this works:

```cpp
std::cout << 2[ptr]; // also prints 5
```

But it’s **bad style**—very confusing to readers.

#### ✅ **In short:**

- `[]` is just sugar for `*(pointer + offset)`.
    
- Arrays are 0-based so the math works cleanly.
    
- You can even do `n[ptr]`, but don’t.

### Pointer arithmetic and subscripting are relative addresses

When first learning about array subscripting, it’s natural to assume that the index represents a fixed element within the array: Index 0 is always the first element, index 1 is always the second element, etc…

This is a illusion. Array indices are actually relative positions. The indices just appear fixed because we almost always index from the start (element 0) of the array!

Remember, given some pointer `ptr`, both `*(ptr + 1)` and `ptr[1]` return the _next object_ in memory (based on the type being pointed to). Next is a relative term, not an absolute one. Thus, if `ptr` is pointing to element 0, then both `*(ptr + 1)` and `ptr[1]` will return element 1. But if `ptr` is pointing to element 3 instead, then both `*(ptr + 1)` and `ptr[1]` will return element 4!

The following example demonstrates this:

```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };
    const int *ptr { arr }; // arr decays into a pointer to element 0

    // Prove that we're pointing at element 0
    std::cout << *ptr << ptr[0] << '\n'; // prints 99
    // Prove that ptr[1] is element 1
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 88

    // Now set ptr to point at element 3
    ptr = &arr[3];

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[1] is element 4!
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 55

    return 0;
}
```

However, you’ll also note that our program is a lot more confusing if we can’t assume that `ptr[1]` is always the element with index 1. For this reason, we recommend using subscripting only when indexing from the start of the array (element 0). Use pointer arithmetic only when doing relative positioning.

>[!Best Practice]
>Favor subscripting when indexing from the start of the array (element 0), so the array indices line up with the element.
Favor pointer arithmetic when doing relative positioning from a given element.

### Negative indices

At the top of this lesson, we noted that `*(ptr-1)` returns the _previous object_ in memory. Want to guess what the subscript equivalent is? Yup, `ptr[-1]`.

```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    // Set ptr to point at element 3
    const int* ptr { &arr[3] };

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[-1] is element 2!
    std::cout << *(ptr-1) << ptr[-1] << '\n'; // prints 77

    return 0;
}
```

### Pointer arithmetic can be used to traverse an array

One of the most common uses of pointer arithmetic is to iterate through a C-style array without explicit indexing. The following example illustrates how this is done:

```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	for (; begin != end; ++begin)           // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' ';     // dereference our loop variable to get the current element
	}

	return 0;
}
```

#### 1. **What does “pointer arithmetic can be used to traverse an array” mean?**

Normally, when we loop through an array, we write:

```cpp
for (int i = 0; i < size; ++i)
    std::cout << arr[i];
```

But since `arr[i]` is just shorthand for `*(arr + i)`, we can instead move a **pointer** along the array using pointer arithmetic (`++ptr`), and dereference it (`*ptr`) to get each element.  
This avoids using an index at all.

#### 2. **Step-by-step in the example**

```cpp
constexpr int arr[]{ 9, 7, 5, 3, 1 };

const int* begin{ arr };                // points to arr[0]
const int* end{ arr + std::size(arr) }; // points to "one past the last element"
```

- `begin` → points to the **first element** (`&arr[0]`).
    
- `end` → points to **one-past-the-last element** (`&arr[5]`).
    
    - This is valid in C++: you can point one past the end, but you must not dereference it.
        

Now the loop:

```cpp
for (; begin(address) != end(address); ++begin)
{
    std::cout << *begin << ' ';
}
```

- `*begin` → dereferences the current pointer → prints the element.
    
- `++begin` → moves the pointer to the **next element**.
    
- Loop stops when `begin == end`, i.e., after the last element.
    

Output:

```cpp
9 7 5 3 1
```

#### 3. **Why one-past-the-end is used**

This is a very common idiom in C++ (also used in STL containers).

- If you stopped at `arr + (size - 1)`, you’d need special handling for the last element.
    
- By using `end = arr + size`, you can just say `begin != end` and stop cleanly.
    

This is exactly how iterators work in the standard library.

#### 4. **Refactoring into a function**

Because the loop only needs two pointers (`begin` and `end`), we can put it into a function:

```cpp
void printArray(const int* begin, const int* end)
{
    for (; begin != end; ++begin)
        std::cout << *begin << ' ';
    std::cout << '\n';
}
```

Then call it like this:

```cpp
printArray(arr, arr + std::size(arr));
```

Notice that we **never pass the array directly**.  
Instead, we pass:

- a pointer to the first element,
    
- and a pointer to one-past-the-last element.
    

That’s all the function needs to traverse the array.

#### 5. **Important safety rule**

Pointer arithmetic is only defined if:

- The pointer stays **within the array**,
    
- Or points to **one past the last element**.
    

Anything beyond that = **undefined behavior** (even if you don’t dereference it).

#### ✅ **In short:**

- Traversing with pointers = `for (p = arr; p != arr+size; ++p)`.
    
- `end` points one-past-the-last.
    
- `*p` gives the element at the current position.
    
- This pattern is the foundation of C++ iterators.

### Range-based for loops over C-style arrays are implemented using pointer arithmetic

Consider the following range-based for loop:

```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	for (auto e : arr)         // iterate from `begin` up to (but excluding) `end`
	{
		std::cout << e << ' '; // dereference our loop variable to get the current element
	}

	return 0;
}
```

If you look at the [documentation](https://en.cppreference.com/w/cpp/language/range-for) for range-based for loops, you’ll see that they are typically implemented something like this:

{
    auto __begin = begin-expr;
    auto __end = end-expr;

    for ( ; __begin != __end; ++__begin)
    {
        range-declaration = *__begin;
        loop-statement;
    }
}

Let’s replace the range-based for loop in the prior example with this implementation:

```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	auto __begin = arr;                // arr is our begin-expr
	auto __end = arr + std::size(arr); // arr + std::size(arr) is our end-expr

	for ( ; __begin != __end; ++__begin)
	{
		auto e = *__begin;         // e is our range-declaration
		std::cout << e << ' ';     // here is our loop-statement
	}

	return 0;
}
```

Note how similar this is to the example we wrote in the prior section! The only difference is that we’re assigning `*__begin` to `e` and using `e` rather than just using `*__begin` directly!

---
