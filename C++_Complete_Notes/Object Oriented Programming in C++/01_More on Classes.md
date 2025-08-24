
# The hidden “this” pointer and member function chaining

### 🔑 The `this` Pointer in C++

### Problem

When we call a member function on an object, e.g.:

```cpp
Simple simple{1};
simple.setID(2);
```

How does C++ know that `m_id` inside `setID()` belongs to `simple` and not some other object?

#### Solution: The Hidden `this` Pointer

- Every **non-static member function** in C++ has access to a hidden pointer named **`this`**.
    
- `this` is a pointer to the object that invoked the function.
    
- So:
    
    - If `a.setID(5)` is called → inside the function, `this == &a`.
        
    - If `b.setID(5)` is called → inside the function, `this == &b`.

#### Implicit vs Explicit Use

These two are equivalent:

```cpp
void print() const { std::cout << m_id; }        // implicit
void print() const { std::cout << this->m_id; }  // explicit
```

- `m_id` is shorthand for `this->m_id`.
    
- Compiler automatically prefixes member accesses with `this->`.

#### How the Compiler Rewrites Calls

When we write:

```cpp
simple.setID(2);
```

The compiler translates it into:

```cpp
Simple::setID(&simple, 2);
```

And the function definition:

```cpp
void setID(int id) { m_id = id; }
```

is rewritten internally as:

```cpp
static void setID(Simple* const this, int id) {
    this->m_id = id;  // same as (*this).m_id
}
```

#### Step-by-Step

1. `simple.setID(2);`
    
2. Compiler rewrites → `Simple::setID(&simple, 2);`
    
3. Inside the function: `this == &simple`
    
4. Member access → `this->m_id = id;` → becomes `simple.m_id = id;`

#### Special Case: Static Functions

- **Static member functions** do **not** have a `this` pointer.
    
- They are not tied to any particular object; they behave like normal functions inside the class.

#### ✅ Key Insights

- All **non-static member functions** have a hidden `this` pointer.
    
- `this` holds the address of the object that invoked the function.
    
- `m_id` is shorthand for `this->m_id`.
    
- `obj.func(args)` is internally rewritten as `Class::func(&obj, args)`.

### `this` always points to the object being operated on

>New programmers are sometimes confused about how many `this` pointers exist. Each member function has a single `this` pointer parameter that points to the implicit object. Consider:

```cpp
int main()
{
    Simple a{1}; // this = &a inside the Simple constructor
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()
    b.setID(4); // this = &b inside member function setID()

    return 0;
}
```

Note that the `this` pointer alternately holds the address of object `a` or `b` depending on whether we’ve called a member function on object `a` or `b`.

Because `this` is just a function parameter (and not a member), it does not make instances of your class larger memory-wise.

### Explicitly referencing `this`

>Most of the time, you won’t need to explicitly reference the `this` pointer. However, there are a few occasions where doing so can be useful:

First, if you have a member function that has a parameter with the same name as a data member, you can disambiguate them by using `this`:

```cpp
struct Something
{
    int data{}; // not using m_ prefix because this is a struct

    void setData(int data)
    {
        this->data = data; // this->data is the member, data is the local parameter
    }
};
```

This `Something` class has a member named `data`. The function parameter of `setData()` is also named `data`. Within the `setData()` function, `data` refers to the function parameter (because the function parameter shadows the data member), so if we want to reference the `data` member, we use `this->data`.

Some developers prefer to explicitly add `this->` to all class members to make it clear that they are referencing a member. We recommend that you avoid doing so, as it tends to make your code less readable for little benefit. Using the “m_” prefix is a more concise way to differentiate private member variables from non-member (local) variables.

### Returning `*this`

#### 🔑 Returning `*this` (Method Chaining in C++)

### Problem

Sometimes we want to call multiple member functions on the **same object** in a single expression, instead of writing separate lines. This technique is called **method chaining**.

Example with `std::cout`:

```cpp
std::cout << "Hello, " << userName;
```

Actually works like:

```cpp
(std::cout << "Hello, ") << userName;
```

- Each `operator<<` prints something **and returns `std::cout`**, allowing the next `<<` to continue chaining.
    
- If `operator<<` returned `void`, chaining would not be possible.

#### Normal Class Example (without chaining)

```cpp
class Calc {
private:
    int m_value{};
public:
    void add(int v) { m_value += v; }
    void sub(int v) { m_value -= v; }
    void mult(int v) { m_value *= v; }
    int getValue() const { return m_value; }
};
```

Usage:

```cpp
Calc c{};
c.add(5);   // void
c.sub(3);   // void
c.mult(4);  // void

std::cout << c.getValue() << '\n';
```

Here, each function returns `void`, so we must call them on separate lines.

#### Solution: Return `*this` by Reference

We can return the **implicit object (`*this`)** instead of `void`:

```cpp
class Calc {
private:
    int m_value{};
public:
    Calc& add(int v)  { m_value += v; return *this; }
    Calc& sub(int v)  { m_value -= v; return *this; }
    Calc& mult(int v) { m_value *= v; return *this; }
    int getValue() const { return m_value; }
};
```

Now usage becomes:

```cpp
Calc c{};
c.add(5).sub(3).mult(4); // method chaining

std::cout << c.getValue() << '\n'; // prints 8
```

#### Step-by-Step of Chaining

1. `c.add(5)` runs → modifies `m_value` → returns reference to `c`.
    
2. Returned object is `c`, so `.sub(3)` runs on the same object.
    
3. `.mult(4)` then runs on the same object again.
    
4. Final result = `(((0 + 5) - 3) * 4) = 8`.

#### Key Notes

- **Return type must be a reference (`ClassName&`)**, not a copy, otherwise chaining may operate on temporary objects instead of the original.
    
- Returning `*this` allows **compact, readable, fluent syntax**.
    
- This is the most common **explicit use of `this`** in real programs.
    
- `this` always points to a valid object when inside a member function, so dereferencing it is safe (no null check needed).
    

#### ✅ Key Insight

Returning `*this` by reference enables **method chaining**, letting us call multiple functions on the same object in a single expression.

### Resetting a class back to default state

If your class has a default constructor, you may be interested in providing a way to return an existing object back to its default state.

As noted in previous lessons ([14.12 -- Delegating constructors](https://www.learncpp.com/cpp-tutorial/delegating-constructors/)), constructors are only for initialization of new objects, and should not be called directly. Doing so will result in unexpected behavior.

The best way to reset a class back to a default state is to create a `reset()` member function, have that function create a new object (using the default constructor), and then assign that new object to the current implicit object, like this:

```cpp
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}
```

Here’s a full program demonstrating this `reset()` function in action:

```cpp
#include <iostream>

class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }

    void reset() { *this = {}; }
};


int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4);

    std::cout << calc.getValue() << '\n'; // prints 8

    calc.reset();

    std::cout << calc.getValue() << '\n'; // prints 0

    return 0;
}
```

### `this` and const objects

>For non-const member functions, `this` is a const pointer to a non-const value (meaning `this` cannot be pointed at something else, but the object pointing to may be modified). With const member functions, `this` is a const pointer to a const value (meaning the pointer cannot be pointed at something else, nor may the object being pointed to be modified).

#### Type of `this`

1. In a **non-const member function**:

```cpp
void func();
```

The type of `this` is:

```cpp
ClassName* const this;
```

- `this` is a **const pointer** (can’t point somewhere else)
    
- but it points to a **non-const object** (so members can be modified).

2. In a **const member function**:

```cpp
void func() const;
```

	The type of `this` is:

```cpp
const ClassName* const this;
```

- `this` is still a const pointer,
    
- but now it points to a **const object** (so members cannot be modified).

#### The Problem

Suppose we have:

```cpp
class Example {
public:
    void nonConstFunc() { /* modifies object */ }
    void constFunc() const { /* read-only */ }
};
```

And we call:

```cpp
const Example e{};
e.nonConstFunc();  // ❌ error
```

- Here, `e` is a **const object**.
    
- The implicit argument passed is of type:

```cpp
const Example* const
```

But `nonConstFunc` expects `this` to be:

```cpp
Example* const
```

- This would require converting a **pointer-to-const** (`const Example*`) into a **pointer-to-non-const** (`Example*`), which **discards const**.
    
- C++ does **not allow this conversion implicitly**, because it would break const-correctness (a `const` object could be modified).

#### The Compiler Error

Different compilers phrase it differently, but essentially the error says:

> “You are trying to call a non-const function on a const object. This requires discarding the const qualifier on the object.”

#### ✅ The Fix

Mark the function as `const` if it does not modify the object:

```cpp
class Example {
public:
    void nonConstFunc() { /* modifies object */ }
    void constFunc() const { /* read-only */ }
};
```

Now:

```cpp
const Example e{};
e.constFunc();   // ✅ works
e.nonConstFunc(); // ❌ still illegal
```

#### 🔑 Key Insight

- The `this` pointer type depends on the function:
    
    - Non-const function → `ClassName* const this`
        
    - Const function → `const ClassName* const this`
        
- You **cannot call a non-const function on a const object**, because that would require discarding `const`.
    
- To make a function callable on const objects, mark it as `const`.

### Why `this` a pointer and not a reference

>Since the `this` pointer always points to the implicit object (and can never be a null pointer unless we’ve done something to cause undefined behavior), you may be wondering why `this` is a pointer instead of a reference. The answer is simple: when `this` was added to C++, references didn’t exist yet.

If `this` were added to the C++ language today, it would undoubtedly be a reference instead of a pointer. In other more modern C++-like languages, such as Java and C#, `this` is implemented as a reference.

---
