# Introduction to containers and arrays

### Containers

>[!Analogy]
>When you go to the grocery store to buy a dozen eggs, you (probably) aren’t selecting 12 eggs individually and putting them in your cart (you aren’t, right?). Instead, you’re likely to select a single carton of eggs. The carton is a type of container, holding some predefined number of eggs (likely 6, 12, or 24). Now consider breakfast cereal, containing many little pieces of cereal. You definitely wouldn’t want to store all these pieces in your pantry individually! Cereal often comes in a box, which is another container. We use containers all the time in real life because they make it easy to manage a collection of items.

>Containers also exist in programming, to make it easier to create and manage (potentially large) collections of objects. In general programming, a **container** is a data type that provides storage for a collection of unnamed objects (called **elements**).

>[!Key insight]
>We typically use containers when we need to work with a set of related values.

As it turns out, you’ve already been using one container type: strings! A string container provides storage for a collection of characters, which can then be output as text:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" }; // strings are a container for characters
    std::cout << name; // output our string as a sequence of characters

    return 0;
}
```

### The elements of a container are unnamed

>While the container object itself typically has a name (otherwise how would we use it?), the elements of a container are unnamed. This is so that we can put as many elements in our container as we desire, without having to give each element a unique name! This lack of named elements is important, and is what distinguishes containers from other types of data structures. It is why plain structs (those that are just a collection of data members, like our `testScores` struct above) typically aren’t considered containers -- their data members require unique names.

In the example above, our string container has a name (`name`), but the characters inside the container (`'A'`, `'l'`, `'e'`, `'x'`) do not.

But if the elements themselves are unnamed, how do we access them? Each container provides one or more methods to access its elements -- but exactly how depends on the type of container.

>[!Summary]
>The elements of a container do not have their own names, so that the container can have as many elements as we want without having to give each element a unique name.
>
Each container provides some method to access these elements, but how depends on the specific type of container.

### The length of a container

>In programming, the number of elements in a container is often called it’s **length** (or sometimes **count**).

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Subhan" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```

This prints:

```cpp
Subhan has 6 characters
```

>[!Key insight]
>In C++, the term **size** is also commonly used for the number of elements in a container. This is an unfortunate choice of nomenclature, as the term “size” can also refer to the number of bytes of memory used by an object (as returned by the `sizeof` operator).
>
We’ll prefer the term “length” when referring to the number of elements in a container, and use the term “size” to refer to amount of storage required by an object.

### Container operations

containers typically implement a significant subset of the following operations:

- Create a container (e.g. empty, with storage for some initial number of elements, from a list of values).
- Access to elements (e.g. get first element, get last element, get any element).
- Insert and remove elements.
- Get the number of elements in the container.

>[!Key insight]
>Modern programming languages typically provide a variety of different container types. These container types differ in terms of which operations they actually support, and how performant those operations are. For example, one container type might provide fast access to any element in the container, but not support insertion or removal of elements. Another container type might provide fast insertion and removal of elements, but only allow access to elements in sequential order.
>
>Every container has a set of strengths and limitations. Picking the right container type for the task you are trying to solve can have a huge impact on both code maintainability and overall performance.

### Element types

>In most programming languages (including C++), containers are **homogenous**, meaning the elements of a container are required to have the same type.

Some containers use a preset element type (e.g. a string typically has `char` elements), but more often the element type can be set by the user of the container. In C++, containers are typically implemented as class templates, so that the user can provide the desired element type as a template type argument.

>This makes containers flexible, as we do not need to create a new container type for each different element type. Instead, we just instantiate the class template with the desired element type, and we’re ready to go.

>[!As an aside]
>The opposite of a homogenous container is a **heterogenous** container, which allows elements to be different types. Heterogeneous containers are typically supported by scripting languages (such as Python).

### Containers in C++

>The **Containers library** is a part of the C++ standard library that contains various class types that implement some common types of containers. A class type that implements a container is sometimes called a **container class**.

In C++, the definition of “container” is narrower than the general programming definition. Only the class types in the Containers library are considered to be containers in C++. We will use the term “container” when talking about containers in general, and “container class” when talking specifically about the container class types that are part of the Containers library.

>[!Note]
>Of the provided container classes, `std::vector` and `std::array` see by far the most use, and will be where we focus the bulk of our attention. The other containers classes are typically only used in more specialized situations.

### Introduction to arrays

>An **array** is a container data type that stores a sequence of values **contiguously** (meaning each element is placed in an adjacent memory location, with no gaps). Arrays allow fast, direct access to any element. They are conceptually simple and easy to use, making them the first choice when we need to create and work with a set of related values.

C++ contains three primary array types: (C-style) arrays, the `std::vector` container class, and the `std::array` container class.

(C-style) arrays were inherited from the C language. For backwards compatibility, these arrays are defined as part of the core C++ language (much like the fundamental data types). The C++ standard calls these “arrays”, but in modern C++ these are often called **C arrays** or **C-style arrays** in order to differentiate them from the similarly named `std::array`. C-style arrays are also sometimes called “naked arrays”, “fixed-sized arrays”, “fixed arrays”, or “built-in arrays”. We’ll prefer the term “C-style array”, and use “array” when discussing array types in general. By modern standards, C-style arrays behave strangely and they are dangerous. We will explore why in a future chapter.

To help make arrays safer and easier to use in C++, the `std::vector` container class was introduced in C++03. `std::vector` is the most flexible of the three array types, and has a bunch of useful capabilities that the other array types don’t.

Finally, the `std::array` container class was introduced in C++11 as a direct replacement for C-style arrays. It is more limited than `std::vector`, but can also be more efficient, especially for smaller arrays.

---
# Introduction to std::vector and list constructors

### Introduction to `std::vector`

>`std::vector` is one of the container classes in the C++ standard containers library that implements an array. `std::vector` is defined in the `<vector>` header as a class template, with a template type parameter that defines the type of the elements. Thus, `std::vector<int>` declares a `std::vector` whose elements are of type `int`.

Instantiating a `std::vector` object is straightforward:

```cpp
#include <vector>

int main()
{
	// Value initialization (uses default constructor)
	std::vector<int> empty{}; // vector containing 0 int elements

	return 0;
}
```

>Variable `empty` is defined as a `std::vector` whose elements have type `int`. Because we’ve used value initialization here, our vector will start empty (that is, with no elements).

### Initializing a `std::vector` with a list of values

Since the goal of a container is to manage a set of related values, most often we will want to initialize our container with those values. We can do this by using list initialization with the specific initialization values we want. For example:

```cpp
#include <vector>

int main()
{
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

	return 0;
}
```

With `primes`, we’re explicitly specifying that we want a `std::vector` whose elements have type `int`. Because we’ve supplied 4 initialization values, `primes` will contain 4 elements whose values are `2`, `3`, `5`, and `7`.

With `vowels`, we haven’t explicitly specified an element type. Instead, we’re using C++17’s CTAD (class template argument deduction) to have the compiler deduce the element type from the initializers. Because we’ve supplied 5 initialization values, `vowels` will contain 5 elements whose values are `'a'`, `'e'`, `'i'`, `'o'`, and `'u'`.

### List constructors and initializer lists

#### What is a **list constructor**?

A **list constructor** is a special constructor that allows containers (like `std::vector`, `std::array`, etc.) to be directly initialized from an initializer list.

For example:

```cpp
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v { 1, 2, 3, 4, 5 };  // uses list constructor
    for (int x : v) 
        std::cout << x << " ";
}
```

Here, `std::vector<int>` calls its **list constructor**, which does 3 things:

1. **Ensures enough storage** for all the elements (`5` in this case).
    
2. **Sets the length** of the vector to match the initializer list (`size = 5`).
    
3. **Copies/initializes** each element in order (`1, 2, 3, 4, 5`).

### Accessing array elements using the subscript operator (operator[])

So now that we’ve created an array of elements… how do we access them?

>[!Analogy]
>Consider a set of identical mailboxes, side by side. To make it easier to identify the mailboxes, each mailbox has a number painted on the front. The first mailbox has number 0, the second has number 1, etc… So if you were told to put something in mailbox number 0, you’d know that meant the first mailbox.

>In C++, the most common way to access array elements is by using the name of the array along with the subscript operator (`operator[]`). To select a specific element, inside the square brackets of the subscript operator, we provide an integral value that identifies which element we want to select. This integral value is called a **subscript** (or informally, an **index**). Much like our mailboxes, the first element is accessed using index 0, the second is accessed using index 1, etc…

For example, `primes[0]` will return the element with index `0` (the first element) from the `prime` array. The subscript operator returns a reference to the actual element, not a copy. Once we’ve accessed an array element, we can use it just like a normal object (e.g. assign a value to it, output it, etc…)

Because the indexing starts with 0 rather than 1, we say arrays in C++ are **zero-based**. This can be confusing because we’re used to counting objects starting from 1.

>Generally, we’ll talk about array elements in terms of position rather than index (so the “first element” is the one with index 0).

### Subscript out of bounds

>[!Tip]
>In an array with N elements, the first element has index 0, the second has index 1, and the last element has index N-1. There is no element with index N!
>
>Using N as a subscript will cause undefined behavior (as this is actually attempting to access the N+1th element, which isn’t part of the array).
>
>Some compilers (like Visual Studio) provide a runtime assert that the index is valid. In such cases, if an invalid index is provided in debug mode, the program will assert out. In release mode, the assert is compiled out so there is no performance penalty.

### Arrays are contiguous in memory

>One of the defining characteristics of arrays is that the elements are always allocated contiguously in memory, meaning the elements are all adjacent in memory (with no gaps between them).

As an illustration of this:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
```

On the author’s machine, one run of the above program produced the following result:

```output
An int is 4 bytes
00DBF720
00DBF724
00DBF728
```

>You’ll note that the memory addresses for these int elements are 4 bytes apart, the same as the size of an `int` on the author’s machine.

Arrays are one of the few container types that allow for **random access**.

#### 🔹 1. What does **random access** mean?

- **Random access** = you can directly access any element by its index, in constant time **O(1)**.
    
- Example:

```cpp
int arr[5] {10, 20, 30, 40, 50};

int x = arr[4];   // directly jump to index 4 → 50
```

The computer can do this because arrays are **contiguous in memory**:

- The address of element `i` = `base_address + i * sizeof(element)`.
    
- That’s just one multiplication and addition → super fast.

#### 🔹 2. What is **sequential access**?

- With **sequential access**, you must go through elements one by one in order to reach the one you want.
    
- Example:  
    A **linked list**:

```cpp
head -> [10] -> [20] -> [30] -> [40]
```

If you want the element at index `3`, you must walk through 0 → 1 → 2 → 3. That’s **O(n)** time.

### Constructing a `std::vector` of a specific length

Consider the case where we want the user to input 10 values that we’ll store in a `std::vector`. In this case, we need a `std::vector` of length 10 before we have any values to put in the `std::vector`. How do we address this?

We could create a `std::vector` and initialize it with an initializer list with 10 placeholder values:

```cpp
std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
```

But that’s bad for a lot of reasons. It requires a lot of typing. It’s not easy to see how many initializers there are. And it’s not easy to update if we decide we want a different number of values later.

Fortunately, `std::vector` has an explicit constructor (`explicit std::vector<T>(std::size_t)`) that takes a single `std::size_t` value defining the length of the `std::vector` to construct:

```cpp
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```

Each of the created elements are value-initialized, which for `int` does zero-initialization (and for class types calls the default constructor).

However, there is one non-obvious thing about using this constructor: it must be called using direct initialization.

### Non-empty initializer lists prefer list constructors

#### 🔹 1. The code in question

```cpp
std::vector<int> data{ 10 };
```

At first glance, you might think:  
👉 does this create a vector **with one element = 10**?  
or  
👉 does this create a vector **of size 10, filled with zeros**?

Both interpretations seem possible — and that’s the problem.

#### 🔹 2. Why is it ambiguous?

`std::vector` has (among others) two relevant constructors:

1. **List constructor**

```cpp
std::vector(std::initializer_list<T> list);
```

- `{ 10 }` looks like an initializer list.
    
- This would create a vector of length 1, with the element `10`.
    
- Result: `data = { 10 }`

2. **Size constructor**

```cpp
explicit std::vector(size_t n);
```

 - `{ 10 }` could also be seen as a single argument of type `size_t`.
        
    - This would create a vector of length 10, with all elements initialized to `0`.
        
    - Result: `data = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }`
        

So `{ 10 }` matches **both constructors**.

#### 🔹 3. How does C++ resolve this?

Normally, when two constructors match, it’s an **ambiguity error**.  
But C++ has a **special rule**:

👉 _If there’s a non-empty initializer list and a matching list constructor exists, the list constructor always wins._

So in this case:

```cpp
std::vector<int> data{ 10 };
```

will always call the **initializer list constructor**, meaning:  
✅ You get a vector with **one element = 10**.

#### 🔹 4. How to call the other constructor?

If you actually want a vector of size 10 (all zeros), you must use **direct initialization with parentheses**:

```cpp
std::vector<int> data(10);   // 10 elements, all 0
```

#### 🔹 5. Why the rule exists

Without this rule, every use of `{}` with one argument would be ambiguous between:

- A list constructor, and
    
- Any single-argument constructor.
    

That would make initializer lists practically unusable.  
So the rule was added: _list constructor wins in `{}` form_.

To help clarify what happens in various initialization cases further, let’s look at similar cases using copy, direct, and list initialization:

```cpp
// Copy init
std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error

// Direct init
std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor

// List init
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor

// Copy list init
std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor

        // Default init
        std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
        std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor
```

>To summarize, list initializers are generally designed to allow us to initialize a container with a list of element values, and should be used for that purpose. That is what we want the majority of the time anyway. Therefore, `{ 10 }` is appropriate if `10` is meant to be an element value. If `10` is meant to be an argument to a non-list constructor of a container, use direct initialization.

>[!Best Practice]
>When constructing a container (or any type that has a list constructor) with initializers that are not element values, use direct initialization.

>Tip

When a `std::vector` is a member of a class type, it is not obvious how to provide a default initializer that sets the length of a `std::vector` to some initial value:

```cpp
#include <vector>

struct Foo
{
    std::vector<int> v1(8); // compile error: direct initialization not allowed for member default initializers
};
```

This doesn’t work because direct (parenthesis) initialization is disallowed for member default initializers.

When providing a default initializer for a member of a class type:

- We must use either copy initialization or list initialization (direct or copy).
- CTAD is not allowed (so we must explicitly specify the element type).

The answer is as follows:

```cpp
struct Foo
{
    std::vector<int> v{ std::vector<int>(8) }; // ok
};
```

This creates a `std::vector` with a capacity of 8, and then uses that as the initializer for `v`.

### Const and constexpr `std::vector`

Objects of type `std::vector` can be made `const`:

```cpp
#include <vector>

int main()
{
    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified

    return 0;
}
```

A `const std::vector` must be initialized, and then cannot be modified. The elements of such a vector are treated as if they were const.

The element type of a `std::vector` must not be defined as const (e.g. `std::vector<const int>` is disallowed).

>One of the biggest downsides of `std::vector` is that it cannot be made `constexpr`. If you need a `constexpr` array, use `std::array`.

### Why is it called a vector?

When people use the term “vector” in conversation, they typically mean a geometric vector, which is an object with a magnitude and direction. So how did `std::vector` get its name when it’s not a geometric vector?

In the book “From Mathematics to Generic Programming”, Alexander Stepanov wrote, “The name vector in STL was taken from the earlier programming languages Scheme and Common Lisp. Unfortunately, this was inconsistent with the much older meaning of the term in mathematics… this data structure should have been called array. Sadly, if you make a mistake and violate these principles, the result might stay around for a long time.”

So, basically, `std::vector` is misnamed, but it’s too late to change it now.

---
# std::vector and the unsigned length and subscript problem

### The container length sign problem

#### 1. The Ideal

In theory, the **type of an index** (the thing you use with `[]`) should **match the type used to store the container’s length**.

- If a container can have length `N`, you should be able to index `0 … N-1`.
    
- The type should ensure every valid index is representable, and invalid ones are easy to catch.
    

So if length is `int`, subscripting should be `int`. If length is `size_t`, subscripting should be `size_t`.

#### 2. What the Standard Library Did

When C++’s standard containers (like `std::vector`, `std::string`, etc.) were being designed in the 1990s, the committee chose **unsigned types** (`size_t`) for:

- Container length (`.size()`, `.capacity()` return `size_t`)
    
- Subscript indices (`operator[]` takes a `size_t`)
    

The reasoning at the time:

- Indices can’t be negative, so unsigned felt “logical.”
    
- On 16-bit systems, unsigned gave you one extra bit of range (so `65535` instead of `32767`).
    
- Range checking was simpler: you only had to check `i < size(std::size_t)`, not `i >= 0 && i < size(std::size_t)`.
    
- Performance was critical, and unsigned was thought to help.

#### 3. Why This Was a Mistake

With hindsight, most experts (including Stroustrup himself) think this was **the wrong choice**:

- **Signed vs unsigned mixing causes bugs**  
    If you loop with a signed `int i` and compare to an unsigned `size_t`, you can easily get:

```cpp
for (std::size_t i = vec.size() - 1; i >= 0; --i) // ❌ infinite loop
```
	
	because `vec.size()` returns `size_t`, so `vec.size() - 1` is unsigned, and comparing `i >= 0` gets messed up by implicit conversions.

- **Unsigned doesn’t actually prevent negatives**
	If you write:

```cpp
std::vector<int> v(10);
v[-1];  // ❌ compiles, but converted to a huge unsigned number
```

- `-1` silently becomes something like `18446744073709551615` (on 64-bit). No safety at all.
    
- **The “extra bit” doesn’t matter anymore**  
    On modern systems, `size_t` is 32-bit or 64-bit.
    
    - 32-bit → max 4 billion elements.
        
    - 64-bit → max 18 quintillion elements.  
        You’ll run out of RAM way before you hit those numbers, so the extra bit is meaningless.
        
- **No range checking in `operator[]` anyway**  
    They justified unsigned by saying it makes range checks simpler, but `[]` doesn’t do checks at all. (You need `.at()` for that.)

#### 4. The Real Consequence

We’re stuck with `size_t` because it’s standardized. This means:

- You **cannot avoid unsigned** when working with STL containers.
    
- You have to be careful when mixing signed loop variables (`int i`) with `size_t`.
    
- Many subtle bugs come from signed/unsigned comparisons.

### A review: sign conversions are narrowing conversions, except when constexpr

>Sign conversions are considered to be narrowing conversions because a signed or unsigned type cannot hold all the values contained in the range of the opposing type. When such a conversion would be performed at runtime, the compiler will issue an error in contexts where narrowing conversions are disallowed (such as in list initialization), and may or may not issue a warning in other contexts where such a conversion is performed.

```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    int s { 5 };

    [[maybe_unused]] unsigned int u { s }; // compile error: list initialization disallows narrowing conversion
    foo(s);                                // possible warning: copy initialization allows narrowing conversion

    return 0;
}
```

####  **Enter `constexpr`**

Now comes the key part:

> If the value being converted is `constexpr` (known at compile time), and the compiler can prove the conversion is **safe** (fits exactly in the target type), then it is **not considered narrowing**.

Example:

```cpp
constexpr int s{ 5 };
unsigned int u{ s }; // ✅ allowed, not narrowing
```

Why? Because `5` is a constant expression, and the compiler can check at compile time:

- Does `5` fit in `unsigned int`? ✅ Yes → safe, so no narrowing.
    

But if it doesn’t fit:

```cpp
constexpr int s{ -5 };
unsigned int u{ s }; // ❌ compile-time error, value not representable
```

The compiler refuses because it knows `-5` cannot be safely converted.

>Example:

```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    constexpr int s { 5 };                 // now constexpr
    [[maybe_unused]] unsigned int u { s }; // ok: s is constexpr and can be converted safely, not a narrowing conversion
    foo(s);                                // ok: s is constexpr and can be converted safely, not a narrowing conversion

    return 0;
}
```

In this case, since `s` is constexpr and the value to be converted (`5`) can be represented as an unsigned value, the conversion is not considered to be narrowing and can be performed implicitly without issue.

### The length and indices of `std::vector` have type `size_type`

#### 1. What is `size_type`?

Every **standard library container** (like `std::vector`, `std::list`, `std::map`, etc.) defines a special **nested type** called `size_type`.

👉 `size_type` is the type that the container uses to represent:

- The **length** (number of elements in the container).
    
- The **indices** (if the container supports indexing, like `std::vector` or `std::string`).
    

So, when you call something like:

```cpp
std::vector<int> vec{1,2,3};
auto n = vec.size();  // n has type vector<int>::size_type
```

the type of `n` is not `int`, but `std::vector<int>::size_type`.

#### 2. What is it actually?

In practice, `size_type` is **almost always** just an alias for `std::size_t`.

- `std::size_t` is an **unsigned integer type** chosen by the implementation (commonly `unsigned long` or `unsigned long long`) that’s big enough to represent the size of objects in memory.
    
- Since containers use allocators (`std::allocator` by default), and `std::allocator::size_type` is defined as `std::size_t`, that’s what you usually get.
    

So you can think of:

```cpp
std::vector<int>::size_type  ≈  std::size_t
```

#### 3. Why not just say `std::size_t` directly?

Because **flexibility**.  
If someone uses a **custom allocator** with a different `size_type`, then the container’s `size_type` will also change. This is rare, but the C++ standard allows it.

So the safe way is:

```cpp
std::vector<int>::size_type len = vec.size();
```

instead of:

```cpp
std::size_t len = vec.size(); // works 99.9% of the time
```

#### 4. Key Takeaways

- `size_type` is a **nested typedef** inside containers.
    
- It tells you the type used for sizes and indices of that container.
    
- For almost all practical cases:  
    `std::vector<T>::size_type == std::size_t`
    
- You should use `size_type` when writing generic code, since it adapts to whatever the container/allocator decides.

### Getting the length of a `std::vector` using the `size()` member function or `std::size()`

>We can ask a container class object for its length using the `size()` member function (which returns the length as unsigned `size_type`):

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    return 0;
}
```

This prints:

length: 5

Unlike `std::string` and `std::string_view`, which have both a `length()` and a `size()` member function (that do the same thing), `std::vector` (and most other container types in C++) only has `size()`. And now you understand why the length of a container is sometimes ambiguously called its size.

>In C++17, we can also use the `std::size()` non-member function (which for container classes just calls the `size()` member function).

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)

    return 0;
}
```

If we want to use either of the above methods to store the length in a variable with a signed type, this will likely result in a signed/unsigned conversion warning or error. The simplest thing to do here is static_cast the result to the desired type:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    int length { static_cast<int>(prime.size()) }; // static_cast return value to int
    std::cout << "length: " << length ;

    return 0;
}
```

### Getting the length of a `std::vector` using `std::ssize()` C++20

>C++20 introduces the `std::ssize()` non-member function, which returns the length as a large _signed_ integral type (usually `std::ptrdiff_t`, which is the type normally used as the signed counterpart to `std::size_t`):

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::ssize(prime); // C++20, returns length as a large signed integral type

    return 0;
}
```

This is the only function of the three which returns the length as a signed type.

If you want to use this method to store the length in a variable with a signed type, you have a couple of options.

First, because the `int` type may be smaller than the signed type returned by `std::ssize()`, if you are going to assign the length to an `int` variable, you should static_cast the result to `int` to make any such conversion explicit (otherwise you might get a narrowing conversion warning or error):

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    int length { static_cast<int>(std::ssize(prime)) }; // static_cast return value to int
    std::cout << "length: " << length;

    return 0;
}
```

Alternatively, you can use `auto` to have the compiler deduce the correct signed type to use for the variable:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    auto length { std::ssize(prime) }; // use auto to deduce signed type, as returned by std::ssize()
    std::cout << "length: " << length;

    return 0;
}
```

### Accessing array elements using `operator[]` does no bounds checking

==`operator[]` does not do bounds checking. The index for operator[] can be non-const. We’ll discuss this further in a later section.

### Accessing array elements using the `at()` member function does runtime bounds checking

>The array container classes support another method for accessing an array. The `at()` member function can be used to do array access with runtime bounds checking:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime.at(3); // print the value of element with index 3
    std::cout << prime.at(9); // invalid index (throws exception)

    return 0;
}
```

In the above example, the call to `prime.at(3)` checks to ensure the index 3 is valid, and because it is, it returns a reference to array element 3. We can then print this value. However, the call to `prime.at(9)` fails (at runtime) because 9 is not a valid index for this array. Instead of returning a reference, the `at()` function generates an error that terminates the program.

>When the `at()` member function encounters an out-of-bounds index, it actually throws an exception of type `std::out_of_range`. If the exception is not handled, the program will be terminated.

Just like `operator[]`, the index passed to `at()` can be non-const.

Because it does runtime bounds checking on every call, `at()` is slower (but safer) than `operator[]`. Despite being less safe, `operator[]` is typically used over `at()`, primarily because it’s better to do bounds checking prior to indexing, so we don’t try to use an invalid index in the first place.

### Indexing `std::vector` with a constexpr signed int

When indexing a `std::vector` with a constexpr (signed) int, we can let the compiler implicitly convert this to a `std::size_t` without it being a narrowing conversion:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3] << '\n';     // okay: 3 converted from int to std::size_t, not a narrowing conversion

    constexpr int index { 3 };         // constexpr
    std::cout << prime[index] << '\n'; // okay: constexpr index implicitly converted to std::size_t, not a narrowing conversion

    return 0;
}
```

### Indexing `std::vector` with a non-constexpr value

#### **Case 1: Using `std::size_t` directly (no issue)**

```cpp
std::size_t index { 3 };    // unsigned type
std::cout << prime[index];  // ✅ fine, no conversion
```

Here, `index` is already the correct type → **no conversion**, no warning, no problem.

#### Case 2: Using `int` (signed type)

```cpp
int index { 3 };            // signed type
std::cout << prime[index];  // ⚠️ warning possible
```

Here’s what happens:

- `index` is of type `int` (signed, can be negative).
    
- `operator[]` expects `std::size_t` (unsigned).
    
- The compiler **implicitly converts** the `int` into a `std::size_t`.
    

This works fine **if the value is non-negative**, but:

- If `index = -1`, it gets converted to a huge unsigned value (wrap-around), leading to **out-of-bounds access**.
    
- Because of this, compilers treat the conversion as **potentially unsafe narrowing** and warn you.

#### **Why is this an issue?**

- Array indexing is **super common**, so if you always use `int`, you’ll constantly trigger warnings.
    
- If you treat warnings as errors (`-Werror`), your build will fail.
    
- You could cast every time:

```cpp
std::cout << prime[static_cast<std::size_t>(index)];
```

…but that clutters your code.

#### **Best practice**

Instead of fighting with conversions, just use the right type for indexing:

```cpp
std::size_t index { 3 };
std::cout << prime[index];
```

And if you need a loop, write:

```cpp
for (std::size_t i = 0; i < prime.size(); ++i) {
    std::cout << prime[i] << ' ';
}
```

⚠️ Key rule: **Only use that `std::size_t` variable for indexing.** Don’t mix it with arithmetic where negatives could appear.

#### ✅ **Summary**:

- `std::vector::operator[]` expects an **unsigned index** (`std::size_t`).
    
- If you pass a signed `int`, it gets converted → possibly unsafe → compiler warns.
    
- Best fix: use `std::size_t` for indexing variables.

---
# Passing std::vector

An object of type `std::vector` can be passed to a function just like any other object. That means if we pass a `std::vector` by value, an expensive copy will be made. Therefore, we typically pass `std::vector` by (const) reference to avoid such copies.

With a `std::vector`, the element type is part of the type information of the object. Therefore, when we use a `std::vector` as a function parameter, we have to explicitly specify the element type:

```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);

    return 0;
}
```

### Passing `std::vector` of different element types

#### 🔹 The problem: Passing `std::vector` of different element types

In C++, a `std::vector<int>` and a `std::vector<double>` are **completely different types**.  
That’s why this code:

```cpp
void passByRef(const std::vector<int>& arr);

std::vector<double> dbl{1.1, 2.2, 3.3};
passByRef(dbl); // ❌ compile error
```

fails:

- `std::vector<int>` ≠ `std::vector<double>`.
    
- C++ does not allow implicit conversion between different `std::vector<T>` types.

#### 🔹 Why not CTAD?

CTAD (Class Template Argument Deduction) lets the compiler **deduce template arguments** when creating an object:

```cpp
std::vector primes{2, 3, 5}; // deduced as std::vector<int>
std::vector dbl{1.1, 2.2};   // deduced as std::vector<double>
```

But **CTAD doesn’t work for function parameters**:

```cpp
void passByRef(const std::vector& arr); // ❌ not allowed
```

Because when calling a function, the compiler must already know the exact type of the parameter. CTAD only applies at **construction time**, not at **function call time**.

#### 🔹 Solution: Function template

We need something that can adapt to different vector element types.  
That’s exactly what **function templates** are for.

```cpp
template <typename T>
void passByRef(const std::vector<T>& arr)
{
    std::cout << arr[0] << '\n';
}
```

Here’s what happens:

- When you call `passByRef(primes)`, where `primes` is a `std::vector<int>`, the compiler **instantiates**:

```cpp
void passByRef(const std::vector<int>& arr) { ... }
```

When you call `passByRef(dbl)`, where `dbl` is a `std::vector<double>`, the compiler **instantiates**:

```cpp
void passByRef(const std::vector<double>& arr) { ... }
```

#### 🔹 Why this works?

Because templates allow the **element type** (`T`) of the vector to be a parameter.  
The compiler generates the correct version of the function for each type of vector you pass in.

#### ✅ **Final Example**

```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const std::vector<T>& arr)
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{2, 3, 5, 7, 11};   // std::vector<int>
    passByRef(primes); // works → calls vector<int> version

    std::vector dbl{1.1, 2.2, 3.3};       // std::vector<double>
    passByRef(dbl);    // works → calls vector<double> version
}
```

Output:

```Ouput
2
1.1
```

👉 So in short:

- `std::vector<int>` and `std::vector<double>` are different types.
    
- CTAD can’t deduce function parameters.
    
- **Function templates** let us generalize over different vector element types.

### Passing a `std::vector` using a generic template or abbreviated function template

We can also create a function template that will accept any type of object:

```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const T& arr) // will accept any type of object that has an overloaded operator[]
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```

In C++20, we can use an abbreviated function template (via an `auto` parameter) to do the same thing:

```cpp
#include <iostream>
#include <vector>

void passByRef(const auto& arr) // abbreviated function template
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```

Both of these will accept an argument of _any_ type that will compile. This can be desirable when writing functions that we might want to operate on more than just a `std::vector`. For example, the above functions will also work on a `std::array`, a `std::string`, or some other type we may not have even considered.

The potential downside of this method is that it may lead to bugs if the function is passed an object of a type that compiles but doesn’t make sense semantically.

### Asserting on array length

#### 🔹 The function

```cpp
template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}
```

This function **always tries to access `arr[3]`** (the 4th element).

#### 🔹 Problem

The compiler does **not check at compile time** whether the vector you pass in actually has at least 4 elements.

So:

```cpp
std::vector arr{9, 7, 5, 3, 1}; // ✅ has index 3 (0..4)
printElement3(arr); // works fine
```

But:

```cpp
std::vector arr{9, 7}; // ❌ only indices 0 and 1 exist
printElement3(arr);    // arr[3] is out of bounds → undefined behavior
```

Undefined behavior = your program might crash, print garbage, or even appear to "work" sometimes but not always. Very dangerous.

#### 🔹 Solution 1: **Runtime assert**

We can **assert that the vector is long enough** before accessing it:

```cpp
#include <cassert>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    assert(arr.size() > 3 && "Vector must have at least 4 elements");
    std::cout << arr[3] << '\n';
}
```

- If `arr.size() <= 3`, the program will stop with an error in **debug builds** (asserts are disabled in release builds by default).
    
- This prevents silent undefined behavior during development.
    

But notice:  
`std::vector::size()` is a **runtime function** (not constexpr), so you cannot check this at compile time — only at runtime.

#### 🔹 Solution 2: **Use `std::array`**

If instead of a `std::vector`, you used `std::array`:

```cpp
template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    static_assert(N > 3, "Array must have at least 4 elements");
    std::cout << arr[3] << '\n';
}
```

Here, `N` is known at **compile time**, so you can `static_assert` and catch the problem **before the program even runs**.

#### 🔹 Best option

The **best design** is to **avoid writing functions that assume a minimum size at all**.  
Instead, pass the index you want, or design the function so it works with any length safely.

For example:

```cpp
template <typename T>
void printElement(const std::vector<T>& arr, std::size_t index)
{
    if (index < arr.size())
        std::cout << arr[index] << '\n';
    else
        std::cerr << "Index out of bounds!\n";
}
```

#### ✅ **Summary**

- `printElement3` is unsafe because it assumes at least 4 elements exist.
    
- With `std::vector`, you can only **runtime assert** (`assert`).
    
- With `std::array`, you can use **compile-time check** (`static_assert`).
    
- Best practice: **don’t design functions that assume minimum vector size** in the first place.

---
# Returning std::vector, and an introduction to move semantics

When we need to pass a `std::vector` to a function, we pass it by (const) reference so that we do not make an expensive copy of the array data.

Therefore, you will probably be surprised to find that it is okay to return a `std::vector` by value.

### Copy semantics

Consider the following program:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    std::vector arr2 { arr1 };          // copies arr1 into arr2

    arr1[0] = 6; // We can continue to use arr1
    arr2[0] = 7; // and we can continue to use arr2

    std::cout << arr1[0] << arr2[0] << '\n';

    return 0;
}
```

When `arr2` is initialized with `arr1`, the copy constructor of `std::vector` is called, which copies `arr1` into `arr2`.

Making a copy is the only reasonable thing to do in this case, as we need both `arr1` and `arr2` to live on independently. This example ends up making two copies, one for each initialization.

The term **copy semantics** refers to the rules that determine how copies of objects are made. When we say a type supports copy semantics, we mean that objects of that type are copyable, because the rules for making such copies have been defined. When we say copy semantics are being invoked, that means we’ve done something that will make a copy of an object.

For class types, copy semantics are typically implemented via the copy constructor (and copy assignment operator), which defines how objects of that type are copied. Typically this results in each data member of the class type being copied. In the prior example, the statement `std::vector arr2 { arr1 };` invokes copy semantics, resulting in a call to the copy constructor of `std::vector`, which then makes a copy of each data member of `arr1` into `arr2`. The end result is that `arr1` is equivalent to (but independent from) `arr2`.

### When copy semantics is not optimal

#### Step 1: The function returns by value

```cpp
std::vector<int> generate()
{
    std::vector arr1 { 1, 2, 3, 4, 5 };
    return arr1; // arr1 is a named local variable
}
```

- `arr1` is created on the stack.
    
- At `return arr1;`, since `arr1` is a **named variable** (an lvalue), the compiler normally interprets this as “make a copy of `arr1` and return it”.
    

Now, in practice, **return value optimization (RVO)** and **mandatory copy elision (C++17)** often eliminate this copy — but here the lesson _intentionally_ disables that optimization by using a named variable. So logically, a **copy constructor** would be called.

#### Step 2: Where the returned object goes

```cpp
std::vector arr2 { generate() };
```

- `generate()` returns a temporary object (an **rvalue**) holding `{1,2,3,4,5}`.
    
- This temporary lives only until the end of the full statement.
    
- At the end of the line, that temporary object is destroyed.
    

So if we simply **copied** it into `arr2`, the sequence is:

1. Temporary vector created inside `generate`.
    
2. Temporary returned, then copied into `arr2`.
    
3. Temporary destroyed.
    

That means we did a full **deep copy** of the data (allocating memory for arr2, copying 5 integers) … only to immediately throw away the temporary. Wasteful.

#### Step 3: Why copy semantics is not optimal here

The key idea:

- In the first example (`arr2 { arr1 };`), **both `arr1` and `arr2` need to live** → we truly need two copies of the data. Copy semantics is correct.
    
- In this example (`arr2 { generate() };`), the temporary will **die anyway**, so keeping two independent copies is unnecessary.
    
    - We only need **one set of data**, owned by `arr2`.
        
    - So instead of copying, we’d like to **transfer ownership of the temporary’s data** directly to `arr2`.
        

That’s exactly what **move semantics** does.

### Introduction to move semantics

#### 🔹 Problem with Copy Semantics

- Copy semantics = make a duplicate of data when assigning/initializing.
    
- Works fine when both objects must live independently.
    
- But inefficient when working with **temporaries** (rvalues):
    
    - Example: returning a vector from a function.
        
    - Temporary will be destroyed anyway → making a copy is wasteful.

#### 🔹 Solution: Move Semantics

- **Idea**: Instead of copying, let one object **“steal”** the resources (ownership) from another.
    
- Called **moving**: ownership of data is transferred.
    
- **Cost**: trivial (just pointer swaps / a few assignments). Much cheaper than copying large arrays.
    
- When temporary is destroyed → it has nothing to free → no destruction overhead.

#### 🔹 Definition

- **Move semantics** = rules that determine how data is transferred from one object to another.
    
- When move semantics is invoked:
    
    - Movable members → moved.
        
    - Non-movable members → copied.
        
- Benefit: avoids expensive deep copies.
    

**Key insight**:

- Move semantics = optimization that cheaply transfers ownership of data.
    
- Works best with large, expensive-to-copy objects (e.g., `std::vector`, `std::string`).

#### 🔹 When is Move Semantics Invoked?

Move semantics happens **only if all conditions are met**:

1. The type supports move semantics (e.g., `std::vector`, `std::string`).
    
2. The source object is an **rvalue** (temporary).
    
3. Copy elision is **not** applied (otherwise no move/copy happens at all).
    

⚠️ Not many standard types support move semantics — but the important ones (`std::vector`, `std::string`) do.

#### 🔹 Return by Value and Move Semantics

- Returning by value produces an **rvalue**.
    
- If the type supports moves → the return value can be **moved instead of copied**.
    
- This makes return-by-value **inexpensive** for move-capable types.
    

**Rule of thumb:**

- Pass large/move-capable objects by `const&`.
    
- Return them by value → moves/elision will optimize it.

#### 🔹 Common Function Call Flow (with class types)

Passing a value to a function and getting one back typically has 4 steps:

1. Construct value to be passed.
    
2. Pass value to function.
    
3. Construct value to be returned.
    
4. Pass return value back to caller.

#### 🔹 Example: Without Move Semantics

```cpp
std::vector<int> doSomething(std::vector<int> v2)
{
    std::vector v3 { v2[0] + v2[0] };
    return v3;
}

int main()
{
    std::vector v1 { 5 };
    std::cout << doSomething(v1)[0] << '\n';
}
```

If `std::vector` is **not move-capable**, then:

1. Copy initializer list → `v1`.
    
2. Copy `v1` → `v2` (function parameter).
    
3. Copy initializer → `v3`.
    
4. Copy `v3` → return value.
    

➡️ **4 copies** total → expensive.

#### 🔹 Optimizations in Steps

- **Copy 1 & 3**: unavoidable → we must construct `v1` and `v3`.
    
- **Copy 2 (argument passing)**:
    
    - ❌ Cannot elide.
        
    - ❌ Cannot move (argument is lvalue, moving would empty `v1`).
        
    - ✅ Best option: pass by `const&` to avoid copy.
        
- **Copy 4 (return value)**:
    
    - ❌ Cannot return reference (local would dangle).
        
    - ✅ Copy elision (if compiler applies).
        
    - ✅ Move semantics (safe, since `v3` will be destroyed anyway).
        
    - ✅ Out parameter (possible, but awkward).

#### 🔹 Final Best Practices

- **Pass** large/move-capable objects by **const reference** → avoids unnecessary copies.
    
- **Return** large/move-capable objects by **value** → moves (or elision) make it efficient.

#### ✅ **Summary Insight**:

- Move semantics lets us **transfer ownership** of resources cheaply.
    
- Copy = duplicate data. Move = steal data.
    
- Use `const&` for parameters, return by value for results.
    
- For move-capable types (e.g., `std::vector`, `std::string`), this gives both safety and efficiency.

>[!Key insight]
>Move semantics is an optimization that allows us, under certain circumstances, to inexpensively transfer ownership of some data members from one object to another object (rather than making a more expensive copy).
>
Data members that can’t be moved are copied instead.

>[!Key insight]
>We can return move-capable types (like `std::vector` and `std::string`) by value. Such types will inexpensively move their values instead of making an expensive copy.
>
Such types should still be passed by const reference.

---
# Arrays and loops

### The variable scalability challenge, revisited

Consider the case where we want to find the average test score for a class of students. To keep these examples concise, we’ll assume the class has only 5 students.

Here’s how we might solve this using individual variables:

```cpp
#include <iostream>

int main()
{
    // allocate 5 integer variables (each with a different name)
    int testScore1{ 84 };
    int testScore2{ 92 };
    int testScore3{ 76 };
    int testScore4{ 81 };
    int testScore5{ 56 };

    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

That’s a lot of variables and a lot of typing. Imagine how much work we’d have to do for 30 students, or 600. Furthermore, if a new test score is added, a new variable has to be declared, initialized, and added to the average calculation. And did you remember to update the divisor? If you forgot, you now have a semantic error. Any time you have to modify existing code, you run the risk of introducing errors.

By now, you know that we should be using an array when we have a bunch of related variables. So let’s replace our individual variables with a `std::vector`:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
        / static_cast<int>(length) };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

This is better -- we’ve cut down on the number of variables defined significantly, and the divisor for the average calculation is now determined directly from the length of the array.

But the average calculation is still a problem, as we’re having to manually list each element individually. And because we have to list each element explicitly, our average calculation only works for arrays with exactly as many elements as we list. If we also want to be able to average arrays of other lengths, we’ll need to write a new average calculation for each different array length.

What we really need is some way to access each array element without having to explicitly list each one.

### Arrays and loops

Normally when you write something like:

```cpp
testScore[2]; // fixed, constant index
```

You’re using a literal constant. But C++ also allows:

```cpp
testScore[i]; // where i is a variable (runtime value)
```

So instead of hardcoding every index, you can **loop** through the indices dynamically.

>Also note that the array indices used in the average calculation of the previous example are an ascending sequence: 0, 1, 2, 3, 4. Therefore, if we had some way to set a variable to values 0, 1, 2, 3, and 4 in sequence, then we could just use that variable as our array index instead of literals. And we already know how to do that -- with a for-loop.

Let’s rewrite the above example using a for-loop, where the loop variable is used as the array index:

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { 0 };
    for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
        average += testScore[index];                      // add the value of element with index `index`
    average /= static_cast<int>(length);                  // calculate the average

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

This solution is ideal in terms of maintainability. The number of times the loop iterates is determined from the length of the array, and the loop variable is used to do all of the array indexing. We no longer have to manually list each array element.

If we want to add or remove a test score, we can just modify the number of array initializers, and the rest of the code will still work without further changes!

==Accessing each element of a container in some order is called **traversal**, or **traversing** the container. Traversal is often called **iteration**, or **iterating over** or **iterating through** the container.

### Templates, arrays, and loops unlock scalability

Arrays provide a way to store multiple objects without having to name each element.

Loops provide a way to traverse an array without having to explicitly list each element.

Templates provide a way to parameterize the element type.

Together, templates, arrays, and loops allow us to write code that can operate on a container of elements, regardless of the element type or number of elements in the container!

To illustrate this further, let’s rewrite the above example, refactoring the average calculation into a function template:

```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average of the values in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    std::size_t length { arr.size() };

    T average { 0 };                                      // if our array has elements of type T, our average should have type T too
    for (std::size_t index{ 0 }; index < length; ++index) // iterate through all the elements
        average += arr[index];                            // sum up all the elements
    average /= static_cast<int>(length);                  // divide by count of items (integral in nature)

    return average;
}

int main()
{
    std::vector class1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // calc average of 5 ints

    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
    std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // calc average of 4 doubles

    return 0;
}
```

This prints:

The class 1 average is: 77
The class 2 average is: 81.75

In the above example, we’ve created function template `calculateAverage()`, which takes a `std::vector` of any element type and any length, and returns the average. In `main()`, we demonstrate that this function works equally well when called with an array of 5 `int` elements or an array of 4 `double` elements!

`calculateAverage()` will work for any type `T` that supports the operators used inside the function (`operator+=(T)`, `operator/=(int)`). If you try to use a `T` that does not support these operators, the compiler will error when trying to compile the instantiated function template.

You might be wondering why we cast `length` to an `int` rather than a `T`. When we calculate the average, we divide the sum by the count of items. The count of items is an integral value. Therefore, semantically, it makes more sense to divide by an `int`.

### What we can do with arrays and loops

>Now that we know how to traverse a container of elements using a loop, let’s look at the most common things that we can use container traversal for. We typically traverse a container in order to do one of four things:

1. Calculate a new value based on the value of existing elements (e.g. average value, sum of values).
2. Search for an existing element (e.g. has exact match, count number of matches, find highest value).
3. Operate on each element (e.g. output each element, multiply all elements by 2).
4. Reorder the elements (e.g. sort the elements in ascending order).

>The first three of these are fairly straightforward. We can use a single loop to traverse the array, inspecting or modifying each element as appropriate.

### Arrays and off-by-one errors

>When traversing a container using an index, you must take care to ensure the loop executes the proper number of times. Off-by-one errors (where the loop body executes one too many or one too few times) are easy to make.

Typically, when traversing a container using an index, we will start the index at `0` and loop until `index < length`.

---
# Arrays, loops, and sign challenge solutions

we discussed how `std::vector` (and other container classes) uses unsigned integral type `std::size_t` for length and indices.

This can lead to problems such as this one:

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
    {
        std::cout << arr[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
```

This code begins by printing the array in reverse:

9 1 2 8 3 7 6 4

And then exhibits undefined behavior. It might print garbage values, or crash the application.

There are two problems here. First, our loop executes as long as `index >= 0` (or in other words, as long as `index` is positive), which is always true when `index` is unsigned. Therefore, the loop never terminates.

Second, when we decrement `index` when it has value `0`, it will wrap around to a large positive value.

>Using a signed type for a loop variable more easily avoids such problems, but has its own challenges. Here’s a version of the above problem that uses a signed index:

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (int index{ static_cast<int>(arr.size()) - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
```

While this version functions as intended, the code is also a cluttered due to the addition two static casts. `arr[static_cast<std::size_t>(index)]` is particularly hard to read. In this case, we’ve improved safety at a significant cost to readability.

>Here’s another example of using a signed index:

```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average value in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    int length{ static_cast<int>(arr.size()) };

    T average{ 0 };
    for (int index{ 0 }; index < length; ++index)
        average += arr[static_cast<std::size_t>(index)];
    average /= length;

    return average;
}

int main()
{
    std::vector testScore1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(testScore1) << '\n';

    return 0;
}
```

The cluttering of our code with static casts is pretty terrible.

So what should we do? This is an area where there is no ideal solution.

### Leave signed/unsigned conversion warnings off

If you were wondering why signed/unsigned conversion warnings are often disabled by default, this topic is one of the key reasons. Every time we subscript a standard library container using a signed index, a sign conversion warning will be generated. This will quickly fill up your compilation log with spurious warnings, drowning out warnings that may actually be legitimate.

So one way to avoid having to deal with lots of signed/unsigned conversion warnings is to simply leave those warnings turned off.

==This is the simplest solution, but not one we recommend, as this will also suppress generation of legitimate sign conversion warnings that may cause bugs if not addressed.

### Using an unsigned loop variable

>[!Best Practice]
>So i,ve read a long ass article on this and to be honest its very tricky so my suggestion is just use :
>`std::size_t` for indices and length.
>One exception would be if we were using custom allocator then there are other approches like
>using the nested typedef `std::vector<T>::size_type`.

### Using a signed loop variable

Although it makes working with the standard library container types a bit more difficult, using a signed loop variable is consistent with the best practices employed in the rest of our code (to favor signed values for quantities). And the more we can consistently apply our best practices, the fewer errors we will have overall.

If we are going to use signed loop variables, there are three issues we need to address:

- What signed type should we use?
- Getting the length of the array as a signed value
- Converting the signed loop variable to an unsigned index

### What signed type should we use?

#### ✅ Options for signed index type

1. **`int` (default choice)**
    
    - Works fine for **most arrays** (since arrays aren’t usually larger than `2^31-1` elements on 32-bit int systems).
        
    - Familiar, simple, easy to read.
        
    - Safe unless dealing with _huge_ data structures.

2. **`std::ptrdiff_t` (defensive choice)**
    
    - Typedef defined in `<cstddef>`.
        
    - Designed to hold the difference between two pointers → large enough to represent all possible array index differences.
        
    - Essentially the **signed counterpart to `std::size_t`**.
        
    - Downsides:
        
        - Name is awkward (`ptrdiff_t` looks weird to newcomers).
            

3. **Type alias for readability**

```cpp
using Index = std::ptrdiff_t;
```

- Makes code more expressive (`Index` clearly means "an array index").
    
- Future-proof: if C++ later adds a dedicated signed index type, you can easily swap your alias to use it.

4. **`auto` deduction**

- If your index is derived from `.size()` anyway, you can let the compiler deduce the type:

```cpp
for (auto index{ static_cast<std::ptrdiff_t>(arr.size()) - 1 }; index >= 0; --index)
```

	Compiler ensures correct signed type, but readability suffers a bit because of the `static_cast`.

5. **C++23 `Z` suffix**

- Adds a literal suffix `Z` that produces a literal of the **signed counterpart of `std::size_t`**.
    
- Example:

```cpp
for (auto index{ 0Z }; index < static_cast<std::ptrdiff_t>(arr.size()); ++index)
```

	Cleaner than writing `static_cast`.

#### 🔑 Summary

- Use `int` unless you’re dealing with very large arrays.
    
- Use `std::ptrdiff_t` (or an alias like `Index`) for safer, general-purpose indexing.
    
- Use `auto` or C++23 `Z` suffix when you want type safety with less manual casting.

### Getting the length of an array as a signed value

#### Problem:

- `std::vector::size()` (and `std::size()`) return an **unsigned type** (`std::size_t`).
    
- When iterating backwards (like from `n-1` to `0`), unsigned integers can cause **wrap-around problems**:
    
    - Example: `0 - 1` with unsigned → becomes a huge positive number instead of negative.
        
- To avoid this, we want the **array length in a signed type**.

#### ✅ Pre-C++20 Solution (Manual cast):

- Convert (`static_cast`) the unsigned `.size()` result to a signed type (e.g., `std::ptrdiff_t`).

```cpp
using Index = std::ptrdiff_t;  // signed type for indices

std::vector arr{ 9, 7, 5, 3, 1 };

for (auto index{ static_cast<Index>(arr.size()) - 1 }; index >= 0; --index)
    std::cout << arr[static_cast<std::size_t>(index)] << ' ';
```

Now:

- `index` is **signed** → can correctly go negative to terminate loop.
    
- Prevents unsigned wrap-around issue.

#### ✅ Cleaner version (store length first):

Instead of repeating the cast inside the loop:

```cpp
auto length{ static_cast<Index>(arr.size()) };
for (auto index{ length - 1 }; index >= 0; --index)
    std::cout << arr[static_cast<std::size_t>(index)] << ' ';
```
	Easier to read and avoids clutter.

#### ✅ C++20 Solution: `std::ssize()`

- `std::ssize()` was introduced to directly return the **signed size** of a container/array. probably std::ptrdiff_t.
    
- Eliminates the need for casting.

```cpp
for (auto index{ std::ssize(arr) - 1 }; index >= 0; --index)
    std::cout << arr[static_cast<std::size_t>(index)] << ' ';
```

#### 🔑 Key Points:

- `arr.size()` → returns unsigned (`std::size_t`).
    
- When counting backwards → use **signed type** to avoid wrap-around.
    
- Pre-C++20 → `static_cast<std::ptrdiff_t>(arr.size())`.
    
- C++20+ → use `std::ssize()` for signed length.
    
- Accessing array still requires unsigned index, so cast back when indexing.

### Converting the signed loop variable to an unsigned index

Once we have a signed loop variable, we’re going to run into implicit sign conversion warnings whenever we try to use that signed loop variable as an index. So we need some way to convert our signed loop variable to an unsigned value wherever we intend to use it as an index.

1. The obvious option is to static cast our signed loop variable into an unsigned index. We show this in the prior example. Unfortunately, we need to do this everywhere we subscript the array, and it makes our array indices hard to read.
2. Use a conversion function with a short name:

```cpp
#include <iostream>
#include <type_traits> // for std::is_integral and std::is_enum
#include <vector>

using Index = std::ptrdiff_t;

// Helper function to convert `value` into an object of type std::size_t
// UZ is the suffix for literals of type std::size_t.
template <typename T>
constexpr std::size_t toUZ(T value)
{
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());

    return static_cast<std::size_t>(value);
}

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length-1 }; index >= 0; --index)
        std::cout << arr[toUZ(index)] << ' '; // use toUZ() to avoid sign conversion warning

    return 0;
}
```

In the above example, we’ve created a function named `toUZ()` that is designed to convert integral values to values of type `std::size_t`. This allows us to index our array as `arr[toUZ(index)]`, which is pretty readable.

#### 3. Use a Custom view

Just like `std::string_view` gives a _view_ into a string without owning it,  
`SignedArrayView` gives a **view into a container** (e.g., `std::vector`) but with a **signed indexing interface**.

While we can’t modify the standard library containers to accept a signed integral index, we can create our own custom view class to “view” a standard library container class. And in doing so, we can define our own interface to work however we want.

In the following example, we define a custom view class that can view any standard library container that supports indexing. Our interface will do two things:

- Allow us to access elements using `operator[]` with a signed integral type.
- Get the length of the container as a signed integral type (since `std::ssize()` is only available on C++20).

```cpp
#ifndef SIGNED_ARRAY_VIEW_H
#define SIGNED_ARRAY_VIEW_H

#include <cstddef> // for std::size_t and std::ptrdiff_t

// SignedArrayView provides a view into a container that supports indexing
// allowing us to work with these types using signed indices
template <typename T>
class SignedArrayView // requires C++17
{
private:
    T& m_array;

public:
    using Index = std::ptrdiff_t;

    SignedArrayView(T& array)
        : m_array{ array } {}

    // Overload operator[] to take a signed index
    constexpr auto& operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr const auto& operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }
};

#endif
```

main.cpp:

```cpp
#include <iostream>
#include <vector>
#include "SignedArrayView.h"

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };
    SignedArrayView sarr{ arr }; // Create a signed view of our std::vector

    for (auto index{ sarr.ssize() - 1 }; index >= 0; --index)
        std::cout << sarr[index] << ' '; // index using a signed type

    return 0;
}
```

### Index the underlying C-style array instead

>we noted that instead of indexing the standard library container, we can instead call the `data()` member function and index that instead. Since `data()` returns the array data as a C-style array, and C-style arrays allow indexing with both signed and unsigned values, this avoids sign conversion issues.

```cpp
int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length - 1 }; index >= 0; --index)
        std::cout << arr.data()[index] << ' ';       // use data() to avoid sign conversion warning

    return 0;
}
```

We believe that this method is the best of the indexing options:

- We can use signed loop variables and indices.
- We don’t have to define any custom types or type aliases.
- The hit to readability from using `data()` isn’t very big.
- There should be no performance hit in optimized code.

### The only sane choice: avoid indexing altogether!

All of the options presented above have their own downsides, so it’s hard to recommend one approach over the other. However, there is a choice that is far more sane than the others: avoid indexing with integral values altogether.

C++ provides several other methods for traversing through arrays that do not use indices at all. And if we don’t have indices, then we don’t run into all of these signed/unsigned conversion issues.

Two common methods for array traversal without indices include range-based for loops, and iterators.

- Range based for loops (for-each)
- iterators

>[!Best Practice]
>Avoid array indexing with integral values whenever possible.

---
