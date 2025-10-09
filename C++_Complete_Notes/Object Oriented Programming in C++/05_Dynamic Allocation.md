# Dynamic memory allocation with new and delete

### The need for dynamic memory allocation

The need for dynamic memory allocation

C++ supports three basic types of memory allocation, of which you’ve already seen two.

- **Static memory allocation** happens for static and global variables. Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.
- **Automatic memory allocation** happens for function parameters and local variables. Memory for these types of variables is allocated when the relevant block is entered, and freed when the block is exited, as many times as necessary.
- **Dynamic memory allocation** is the topic of this article.

Both static and automatic allocation have two things in common:

- The size of the variable / array must be known at compile time.
- Memory allocation and deallocation happens automatically (when the variable is instantiated / destroyed).

>Most of the time, this is just fine. However, you will come across situations where one or both of these constraints cause problems, usually when dealing with external (user or file) input.

### ⚠️ Why This Becomes a Problem

There are many real-world situations where we **don’t know** the size we need until the program runs.

Examples:

- You don’t know how long a user’s name is until they enter it.
    
- You don’t know how many records are in a file until you open it.
    
- You don’t know how many enemies (monsters) exist in a game at a given moment.
    

If you must decide the size at compile time, your only choice is to **guess** a maximum value:

```cpp
char name[25];      // hope no one has a longer name
Record record[500]; // hope no more than 500 records
Monster monster[40];
```

### 💣 4. The Four Big Problems With This Approach

#### **(1) Wasted Memory**

You must allocate enough for the “worst case,” so most of it stays unused.  
Example:

```cpp
char name[25];  // but most names are < 12 characters
```

→ Half the space is wasted for every name.  
In large programs, this adds up to **huge memory waste**.

#### **(2) Managing Which Memory Is Actually Used**

You must track which slots are used or free manually.

Example:

```cpp
Monster monster[40];
```

- Is `monster[24]` active?
    
- Has it been initialized yet?  
    You might need an extra flag for each entry, making code messy and inefficient.

#### **(3) Limited Stack Size**

- **Automatic variables** (local variables, fixed arrays) are stored on the **stack**.
    
- Stack memory is **small** (around 1 MB on most systems).
    
- Large arrays can easily cause a **stack overflow**, crashing your program.
    

Example:

```cpp
int main() {
    int array[1000000]; // ~4MB -> too large for stack -> crash
}
```

→ The stack isn’t meant for large or flexible data storage.

#### **(4) Artificial Limits and Overflow Risks**

If the user needs **more space than you reserved**, you hit a hard limit:

```cpp
Record record[500];  // what if there are 600 records?
```

Options:

- Stop and show an error (annoying for users)
    
- Read only part of the data (incomplete)
    
- Or worse: write beyond array bounds → **undefined behavior** (crashes, corrupted data)

### 🧠 5. The Solution — Dynamic Memory Allocation

**Dynamic allocation** lets your program **request memory at runtime**, when it knows how much it needs.

- Memory comes from the **heap**, not the limited stack.
    
- Heap space is **much larger** (often several gigabytes).
    
- You can allocate exactly the amount needed — no more guessing.

### Dynamically allocating single variables

To allocate a _single_ variable dynamically, we use the scalar (non-array) form of the **new** operator:

```cpp
new int; // dynamically allocate an integer (and discard the result)
```

In the above case, we’re requesting an integer’s worth of memory from the operating system. The new operator creates the object using that memory, and then returns a pointer containing the _address_ of the memory that has been allocated.

Most often, we’ll assign the return value to our own pointer variable so we can access the allocated memory later.

```cpp
int* ptr{ new int }; // dynamically allocate an integer and assign the address to ptr so we can access it later
```

We can then dereference the pointer to access the memory:

```cpp
*ptr = 7; // assign value of 7 to allocated memory
```

If it wasn’t before, it should now be clear at least one case in which pointers are useful. Without a pointer to hold the address of the memory that was just allocated, we’d have no way to access the memory that was just allocated for us!

Note that accessing heap-allocated objects is generally slower than accessing stack-allocated objects. Because the compiler knows the address of stack-allocated objects, it can go directly to that address to get a value. Heap allocated objects are typically accessed via pointer. This requires two steps: one to get the address of the object (from the pointer), and another to get the value.

### How does dynamic memory allocation work?

#### 🧠 1. What’s Happening in Your Computer’s Memory

When you run a program, your **operating system (OS)** loads it into memory (RAM).  
This memory is divided into **different regions**, each serving a special purpose:

|Memory Area|Purpose|
|---|---|
|**Code segment (text segment)**|Stores your program’s compiled instructions (the actual code).|
|**Data segment (global/static)**|Stores global and static variables.|
|**Stack**|Stores local variables and function call information (automatic storage).|
|**Heap**|Large area of free memory used for **dynamic allocation** (requested at runtime).|

So when your program runs, it only occupies part of your RAM — the rest remains **available** to be handed out to programs that **ask for it**.

#### 🧩 2. What Happens During Dynamic Allocation

When your program **dynamically allocates memory**, it’s doing something like this:

> “Hey OS, I need some memory that I didn’t know I’d need earlier.  
> Please give me a chunk of memory big enough to hold X.”

If the OS can fulfill that request, it:

1. Finds an unused region of the **heap** large enough.
    
2. Reserves (marks) that region as “in use”.
    
3. Returns the **address** of the starting byte of that region to your program.
    

That address is stored in a **pointer** — because a pointer holds memory addresses.

### Example in C++

```cpp
int* ptr = new int;  // asks OS for space to hold one integer
```

- The OS allocates space for an `int` (say 4 bytes).
    
- Returns the **memory address**, e.g. `0x6ffe20`.
    
- The pointer `ptr` now holds that address:

```cpp
ptr → 0x6ffe20
*ptr = 0  // (uninitialized)
```

You can now use `*ptr` just like a normal variable:

```cpp
*ptr = 42;
std::cout << *ptr;  // prints 42
```

>When your program no longer needs that memory, it should give it back to the OS so that it can be reused. (delete)
>If you forget to `delete`, that memory stays “in use” even though you can’t reach it anymore → this is called a **memory leak**.

#### 📌 3. Why We Use Pointers for Heap Memory

The OS gives you the **memory address** of the allocated block.  
To store and access that memory, you need something that can hold an address — that’s what **pointers** are for.

Example:

```cpp
int* number = new int(7);  // allocate and initialize to 7
std::cout << *number;      // prints 7

delete number;             // free it
number = nullptr;          // avoid dangling pointer
```

##### Key Idea:

You don’t access heap objects directly — you access them **through their addresses**, which you keep in pointers.

#### ⚡ 4. Visualizing It

Let’s imagine this simple code:

```cpp
int x = 5;          // stored on stack
int* p = new int(10);  // stored on heap
```

**Memory layout:**

```cpp
Stack:                         Heap:
+--------------------+          +----------------+
| x = 5             |          | 10             |
| p -> 0x600100     | -------> | (heap address) |
+--------------------+          +----------------+
```

- The variable `x` lives on the **stack**.
    
- The pointer `p` lives on the **stack**, but points to an integer on the **heap**.
    

#### 🧠 4. Key Insight (from your passage)

> The allocation and deallocation for **stack objects** is automatic.  
> The allocation and deallocation for **heap objects** is **manual**.

This means:

- Stack: You don’t touch memory addresses or delete anything. The compiler does it.
    
- Heap: You must keep track of addresses and release them yourself.
    

So in dynamic memory allocation:

- You **request** memory → using `new`
    
- You **use** it → via pointer
    
- You **release** it → using `delete`

#### ✅ 5. Summary

| Concept                       | Description                                                        |
| ----------------------------- | ------------------------------------------------------------------ |
| **Dynamic memory allocation** | Requesting memory from the OS at runtime                           |
| **Where it comes from**       | The heap (large pool of unused memory)                             |
| **How to allocate**           | `new` keyword (C++)                                                |
| **How to free**               | `delete` keyword                                                   |
| **Access via**                | Pointers (which store the address)                                 |
| **Responsibility**            | Programmer must manage it (or use smart pointers / STL containers) |

### Initializing a dynamically allocated variable

When you dynamically allocate a variable, you can also initialize it via direct initialization or uniform initialization:

```cpp
int* ptr1{ new int (5) }; // use direct initialization
int* ptr2{ new int { 6 } }; // use uniform initialization
```

### Deleting a single variable

When we are done with a dynamically allocated variable, we need to explicitly tell C++ to free the memory for reuse. For single variables, this is done via the scalar (non-array) form of the **delete** operator:

```cpp
// assume ptr has previously been allocated with operator new
delete ptr; // return the memory pointed to by ptr to the operating system
ptr = nullptr; // set ptr to be a null pointer
```

### What does it mean to delete memory?

The delete operator does not _actually_ delete anything. It simply returns the memory being pointed to back to the operating system. The operating system is then free to reassign that memory to another application (or to this application again later).

#### 💡  What Actually Happens

When you write `delete ptr;`, you are **not deleting the pointer** and **not deleting the variable itself**.

Here’s what really happens under the hood:

1. The pointer `ptr` holds an **address** of some memory block on the **heap** (allocated earlier using `new`).
    
2. The `delete` operator tells the **operating system (via the runtime system)**:
    
    > “I’m done using the memory block that starts at this address.  
    > Please mark it as free so it can be reused later.”
    
3. The OS marks that memory region as **available** for reuse.
    
4. The **pointer variable itself** is **not destroyed** — it still exists and still holds the same old address, but that address is now invalid (the memory is no longer yours).
    

That’s why we say:

> `delete` **returns** the memory to the OS — it doesn’t actually destroy it.

>Note that deleting a pointer that is not pointing to dynamically allocated memory may cause bad things to happen.

#### ⚠️  Dangling Pointer Example

```cpp
int* ptr = new int(5);
delete ptr;     // memory returned to OS
*ptr = 10;      // ❌ undefined behavior (memory no longer yours!)
```

The pointer `ptr` still exists, but the memory it points to has been freed.  
Accessing or writing to that address can crash the program or corrupt data.

✅ The safe practice:

```cpp
delete ptr;
ptr = nullptr;  // now it's clearly marked as "points to nothing"
```

### Dangling pointers

#### **What is a Dangling Pointer?**

A **dangling pointer** is a pointer that _points to memory which has already been freed (deallocated)_.

This is dangerous because the pointer still holds an _address_, but that memory is no longer valid or safe to use. Accessing it causes **undefined behavior** — meaning _anything can happen_ (crash, garbage output, etc.).

#### **Why Does This Happen?**

When you use `new`, memory is given to your program.  
When you use `delete`, that memory is returned to the operating system.

**IMPORTANT:**  
`delete` only frees the memory — **it does not erase or change the pointer itself**.  
The pointer still holds the old address → now pointing to _invalid memory_ → **dangling pointer**.

#### **Example 1: Simple Dangling Pointer**

```cpp
int* ptr{ new int };   // Memory allocated
*ptr = 7;              // Value assigned

delete ptr;            // Memory freed, ptr is now dangling!

std::cout << *ptr;     // ❌ Undefined behavior
delete ptr;            // ❌ Double delete -> Undefined behavior
```

### What Can Go Wrong?

- It may print `7` (old value still there)
    
- It may print garbage
    
- It may crash the program
    
- It may access memory now used by another program

#### **Example 2: Multiple Dangling Pointers**

```cpp
int* ptr{ new int{} };
int* otherPtr{ ptr };   // Both point to same memory

delete ptr;             // Memory freed

ptr = nullptr;          // ptr is safe now
// BUT otherPtr still points to freed memory -> dangling!
```

Even though `ptr` was set to `nullptr`, `otherPtr` is still dangerous!

#### **Why Dangling Pointers Are Dangerous**

- **Reading** → May access invalid data or crash
    
- **Writing** → May overwrite memory of another program
    
- **Deleting again** → Double free → Crash or security bugs
    

This is why they cause **undefined behavior**.

#### **Why Dangling Pointers Are Dangerous**

- **Reading** → May access invalid data or crash
    
- **Writing** → May overwrite memory of another program
    
- **Deleting again** → Double free → Crash or security bugs
    

This is why they cause **undefined behavior**.

#### **Best Practices to Avoid Dangling Pointers**

✅ **1. Set pointers to `nullptr` after deleting**

✅ **2. Avoid multiple raw pointers owning the same memory**  
Use only one pointer responsible for deleting.

✅ **3. Use smart pointers (`std::unique_ptr`, `std::shared_ptr`)**  
They automatically manage memory safely. (We haven't learned it yet!)

#### **Key Takeaway**

> **A dangling pointer is like having an old house key after the house is demolished –  
> if you try to use it, you’ll get into trouble.**

### Operator new can fail

When requesting memory from the operating system, in rare circumstances, the operating system may not have any memory to grant the request with.

By default, if new fails, a _bad_alloc_ exception is thrown. If this exception isn’t properly handled (and it won’t be, since we haven’t covered exceptions or exception handling yet), the program will simply terminate (crash) with an unhandled exception error.

In many cases, having new throw an exception (or having your program crash) is undesirable, so there’s an alternate form of new that can be used instead to tell new to return a null pointer if memory can’t be allocated. This is done by adding the constant std::nothrow between the new keyword and the allocation type:

```cpp
int* value { new (std::nothrow) int }; // value will be set to a null pointer if the integer allocation fails
```

In the above example, if new fails to allocate memory, it will return a null pointer instead of the address of the allocated memory.

Note that if you then attempt to dereference this pointer, undefined behavior will result (most likely, your program will crash). Consequently, the best practice is to check all memory requests to ensure they actually succeeded before using the allocated memory.

```cpp
int* value { new (std::nothrow) int{} }; // ask for an integer's worth of memory
if (!value) // handle case where new returned null
{
    // Do error handling here
    std::cerr << "Could not allocate memory\n";
}
```

Because asking new for memory only fails rarely (and almost never in a dev environment), it’s common to forget to do this check!

### Null pointers and dynamic memory allocation

Null pointers (pointers set to nullptr) are particularly useful when dealing with dynamic memory allocation. In the context of dynamic memory allocation, a null pointer basically says “no memory has been allocated to this pointer”. This allows us to do things like conditionally allocate memory:

```cpp
// If ptr isn't already allocated, allocate it
if (!ptr)
    ptr = new int;
```

Deleting a null pointer has no effect. Thus, there is no need for the following:

```cpp
if (ptr) // if ptr is not a null pointer
    delete ptr; // delete it
// otherwise do nothing
```

Instead, you can just write:

```cpp
delete ptr;
```

If ptr is non-null, the dynamically allocated memory will be deleted. If ptr is null, nothing will happen.

>[!Best Practice]
>Deleting a null pointer is okay, and does nothing. There is no need to conditionalize your delete statements.

### Memory leaks

Dynamically allocated memory stays allocated until it is explicitly deallocated or until the program ends (and the operating system cleans it up, assuming your operating system does that). However, the pointers used to hold dynamically allocated memory addresses follow the normal scoping rules for local variables. This mismatch can create interesting problems.

Consider the following function:

```cpp
void doSomething()
{
    int* ptr{ new int{} };
}
```

This function allocates an integer dynamically, but never frees it using delete. Because pointers variables are just normal variables, when the function ends, ptr will go out of scope. And because ptr is the only variable holding the address of the dynamically allocated integer, when ptr is destroyed there are no more references to the dynamically allocated memory. This means the program has now “lost” the address of the dynamically allocated memory. As a result, this dynamically allocated integer can not be deleted.

This is called a **memory leak**. Memory leaks happen when your program loses the address of some bit of dynamically allocated memory before giving it back to the operating system. When this happens, your program can’t delete the dynamically allocated memory, because it no longer knows where it is. The operating system also can’t use this memory, because that memory is considered to be still in use by your program.

Memory leaks eat up free memory while the program is running, making less memory available not only to this program, but to other programs as well. Programs with severe memory leak problems can eat all the available memory, causing the entire machine to run slowly or even crash. Only after your program terminates is the operating system able to clean up and “reclaim” all leaked memory.

Although memory leaks can result from a pointer going out of scope, there are other ways that memory leaks can result. For example, a memory leak can occur if a pointer holding the address of the dynamically allocated memory is assigned another value:

```cpp
int value = 5;
int* ptr{ new int{} }; // allocate memory
ptr = &value; // old address lost, memory leak results
```

This can be fixed by deleting the pointer before reassigning it:

```cpp
int value{ 5 };
int* ptr{ new int{} }; // allocate memory
delete ptr; // return memory back to operating system
ptr = &value; // reassign pointer to address of value
```

Relatedly, it is also possible to get a memory leak via double-allocation:

```cpp
int* ptr{ new int{} };
ptr = new int{}; // old address lost, memory leak results
```

The address returned from the second allocation overwrites the address of the first allocation. Consequently, the first allocation becomes a memory leak!

Similarly, this can be avoided by ensuring you delete the pointer before reassigning.

### Conclusion

Operators new and delete allow us to dynamically allocate single variables for our programs.

Dynamically allocated memory has dynamic duration and will stay allocated until you deallocate it or the program terminates.

Be careful not to perform dereference a dangling or null pointers.

---
