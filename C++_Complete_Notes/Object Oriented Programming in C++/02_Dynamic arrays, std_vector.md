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
