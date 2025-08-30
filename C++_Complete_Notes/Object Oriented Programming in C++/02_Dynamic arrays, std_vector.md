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
