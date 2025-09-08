
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
