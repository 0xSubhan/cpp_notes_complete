# Function Pointers

you learned that a pointer is a variable that holds the address of another variable. Function pointers are similar, except that instead of pointing to variables, they point to functions!

Consider the following function:

```cpp
int foo()
{
    return 5;
}
```

Identifier `foo()` is the function’s name. But what type is the function? Functions have their own function type -- in this case, a function type that returns an integer and takes no parameters. Much like variables, functions live at an assigned address in memory (making them lvalues).

When a function is called (via `operator()`), execution jumps to the address of the function being called:

```cpp
int foo() // code for foo starts at memory address 0x002717f0
{
    return 5;
}

int main()
{
    foo(); // jump to address 0x002717f0

    return 0;
}
```

At some point in your programming career (if you haven’t already), you’ll probably make a simple mistake:

```cpp
#include <iostream>

int foo() // code starts at memory address 0x002717f0
{
    return 5;
}

int main()
{
    std::cout << foo << '\n'; // we meant to call foo(), but instead we're printing foo itself!

    return 0;
}
```

Instead of calling function `foo()` and printing the return value, we’ve unintentionally sent function `foo` directly to `std::cout`. What happens in this case?

>When a function is referred to by name (without parenthesis), C++ converts the function into a function pointer (holding the address of the function). Then `operator<<` tries to print the function pointer, which it fails at because `operator<<` does not know how to print function pointers. The standard says that in this case, `foo` should be converted to a `bool` (which `operator<<` does know how to print). And since the function pointer for `foo` is a non-null pointer, it should always evaluate to Boolean `true`. Thus, this should print:

`1`

Just like it is possible to declare a non-constant pointer to a normal variable, it’s also possible to declare a non-constant pointer to a function. In the rest of this lesson, we’ll examine these function pointers and their uses. Function pointers are a fairly advanced topic, and the rest of this lesson can be safely skipped or skimmed by those only looking for C++ basics.

### Pointers to functions

The syntax for creating a non-const function pointer is one of the ugliest things you will ever see in C++:

```cpp
// fcnPtr is a pointer to a function that takes no arguments and returns an integer
int (*fcnPtr)();
```

In the above snippet, fcnPtr is a pointer to a function that has no parameters and returns an integer. fcnPtr can point to any function that matches this type.

The parentheses around *fcnPtr are necessary for precedence reasons, as `int* fcnPtr()` would be interpreted as a forward declaration for a function named fcnPtr that takes no parameters and returns a pointer to an integer.

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

To make a const function pointer, the const goes after the asterisk:

```cpp
int (*const fcnPtr)();
```

If you put the const before the int, then that would indicate the function being pointed to would return a const int.

### Assigning a function to a function pointer

Function pointers can be initialized with a function (and non-const function pointers can be assigned a function). Like with pointers to variables, we can also use &foo to get a function pointer to foo.

```cpp
int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

int main()
{
    int (*fcnPtr)(){ &foo }; // fcnPtr points to function foo
    fcnPtr = &goo; // fcnPtr now points to function goo

    return 0;
}
```

One common mistake is to do this:

```cpp
fcnPtr = goo();
```

This tries to assign the return value from a call to function goo() (which has type `int`) to fcnPtr (which is expecting a value of type `int(*)()`), which isn’t what we want. We want fcnPtr to be assigned the address of function goo, not the return value from function goo(). So no parentheses are needed.

Note that the type (parameters and return type) of the function pointer must match the type of the function. Here are some examples of this:

```cpp
// function prototypes
int foo();
double goo();
int hoo(int x);

// function pointer initializers
int (*fcnPtr1)(){ &foo };    // okay
int (*fcnPtr2)(){ &goo };    // wrong -- return types don't match!
double (*fcnPtr4)(){ &goo }; // okay
fcnPtr1 = &hoo;              // wrong -- fcnPtr1 has no parameters, but hoo() does
int (*fcnPtr3)(int){ &hoo }; // okay
```

Unlike fundamental types, C++ _will_ implicitly convert a function into a function pointer if needed (so you don’t need to use the address-of operator (&) to get the function’s address). However, function pointers will not convert to void pointers, or vice-versa (though some compilers like Visual Studio may allow this anyway).

```cpp
// function prototypes
int foo();

// function initializations
int (*fcnPtr5)() { foo }; // okay, foo implicitly converts to function pointer to foo
void* vPtr { foo };       // not okay, though some compilers may allow
```

Function pointers can also be initialized or assigned the value nullptr:

```cpp
int (*fcnptr)() { nullptr }; // okay
```

### Calling a function using a function pointer

The other primary thing you can do with a function pointer is use it to actually call the function. There are two ways to do this. The first is via explicit dereference:

```cpp
int foo(int x)
{
    return x;
}

int main()
{
    int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo
    (*fcnPtr)(5); // call function foo(5) through fcnPtr.

    return 0;
}
```

The second way is via implicit dereference:

```cpp
int foo(int x)
{
    return x;
}

int main()
{
    int (*fcnPtr)(int){ &foo }; // Initialize fcnPtr with function foo
    fcnPtr(5); // call function foo(5) through fcnPtr.

    return 0;
}
```

As you can see, the implicit dereference method looks just like a normal function call -- which is what you’d expect, since normal function names are pointers to functions anyway! However, some older compilers do not support the implicit dereference method, but all modern compilers should.

Also note that because function pointers can be set to nullptr, it’s a good idea to assert or conditionally test whether your function pointer is a null pointer before calling it. Just like with normal pointers, dereferencing a null function pointer leads to undefined behavior.

### Default arguments don’t work for functions called through function pointers Advanced

When the compiler encounters a normal function call to a function with one or more default arguments, it rewrites the function call to include the default arguments. This process happens at compile-time, and thus can only be applied to functions that can be resolved at compile time.

However, when a function is called through a function pointer, it is resolved at runtime. In this case, there is no rewriting of the function call to include default arguments.

#### Key insight

>Because the resolution happens at runtime, default arguments are not resolved when a function is called through a function pointer.

This means that we can use a function pointer to disambiguate a function call that would otherwise be ambiguous due to default arguments. In the following example, we show two ways to do this:

```cpp
#include <iostream>

void print(int x)
{
    std::cout << "print(int)\n";
}

void print(int x, int y = 10)
{
    std::cout << "print(int, int)\n";
}

int main()
{
//    print(1); // ambiguous function call

    // Deconstructed method
    using vnptr = void(*)(int); // define a type alias for a function pointer to a void(int) function
    vnptr pi { print }; // initialize our function pointer with function print
    pi(1); // call the print(int) function through the function pointer

    // Concise method
    static_cast<void(*)(int)>(print)(1); // call void(int) version of print with argument 1

    return 0;
}
```

### Passing functions as arguments to other functions

Passing functions as arguments to other functions

One of the most useful things to do with function pointers is pass a function as an argument to another function. Functions used as arguments to another function are sometimes called **callback functions**.

Consider a case where you are writing a function to perform a task (such as sorting an array), but you want the user to be able to define how a particular part of that task will be performed (such as whether the array is sorted in ascending or descending order). Let’s take a closer look at this problem as applied specifically to sorting, as an example that can be generalized to other similar problems.

Many comparison-based sorting algorithms work on a similar concept: the sorting algorithm iterates through a list of numbers, does comparisons on pairs of numbers, and reorders the numbers based on the results of those comparisons. Consequently, by varying the comparison, we can change the way the algorithm sorts without affecting the rest of the sorting code.

Here is our selection sort routine from a previous lesson:

```cpp
#include <utility> // for std::swap

void SelectionSort(int* array, int size)
{
    if (!array)
        return;

    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // smallestIndex is the index of the smallest element we've encountered so far.
        int smallestIndex{ startIndex };

        // Look for smallest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller than our previously found smallest
            if (array[smallestIndex] > array[currentIndex]) // COMPARISON DONE HERE
            {
                // This is the new smallest number for this iteration
                smallestIndex = currentIndex;
            }
        }

        // Swap our start element with our smallest element
        std::swap(array[startIndex], array[smallestIndex]);
    }
}
```

Let’s replace that comparison with a function to do the comparison. Because our comparison function is going to compare two integers and return a boolean value to indicate whether the elements should be swapped, it will look something like this:

```cpp
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}
```

And here’s our selection sort routine using the ascending() function to do the comparison:

```cpp
#include <utility> // for std::swap

void SelectionSort(int* array, int size)
{
    if (!array)
        return;

    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // smallestIndex is the index of the smallest element we've encountered so far.
        int smallestIndex{ startIndex };

        // Look for smallest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller than our previously found smallest
            if (ascending(array[smallestIndex], array[currentIndex])) // COMPARISON DONE HERE
            {
                // This is the new smallest number for this iteration
                smallestIndex = currentIndex;
            }
        }

        // Swap our start element with our smallest element
        std::swap(array[startIndex], array[smallestIndex]);
    }
}
```

Now, in order to let the caller decide how the sorting will be done, instead of using our own hard-coded comparison function, we’ll allow the caller to provide their own sorting function! This is done via a function pointer.

Because the caller’s comparison function is going to compare two integers and return a boolean value, a pointer to such a function would look something like this:

```cpp
bool (*comparisonFcn)(int, int);
```

So, we’ll allow the caller to pass our sort routine a pointer to their desired comparison function as the third parameter, and then we’ll use the caller’s function to do the comparison.

Here’s a full example of a selection sort that uses a function pointer parameter to do a user-defined comparison, along with an example of how to call it:

```cpp
#include <utility> // for std::swap
#include <iostream>

// Note our user-defined comparison is the third parameter
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
{
    if (!array || !comparisonFcn)
        return;

    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest/largest element we've encountered so far.
        int bestIndex{ startIndex };

        // Look for smallest/largest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller/larger than our previously found smallest
            if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
            {
                // This is the new smallest/largest number for this iteration
                bestIndex = currentIndex;
            }
        }

        // Swap our start element with our smallest/largest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}

// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
    return x < y; // swap if the second element is greater than the first
}

// This function prints out the values in the array
void printArray(int* array, int size)
{
    if (!array)
        return;

    for (int index{ 0 }; index < size; ++index)
    {
        std::cout << array[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    printArray(array, 9);

    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    printArray(array, 9);

    return 0;
}
```

This program produces the result:

9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9

Is that cool or what? We’ve given the caller the ability to control how our selection sort does its job.

The caller can even define their own “strange” comparison functions:

```cpp
bool evensFirst(int x, int y)
{
	// if x is even and y is odd, x goes first (no swap needed)
	if ((x % 2 == 0) && !(y % 2 == 0))
		return false;

	// if x is odd and y is even, y goes first (swap needed)
	if (!(x % 2 == 0) && (y % 2 == 0))
		return true;

        // otherwise sort in ascending order
	return ascending(x, y);
}

int main()
{
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

    selectionSort(array, 9, evensFirst);
    printArray(array, 9);

    return 0;
}
```

The above snippet produces the following result:

2 4 6 8 1 3 5 7 9

As you can see, using a function pointer in this context provides a nice way to allow a caller to “hook” their own functionality into something you’ve previously written and tested, which helps facilitate code reuse! Previously, if you wanted to sort one array in descending order and another in ascending order, you’d need multiple versions of the sort routine. Now you can have one version that can sort any way the caller desires!

Note: If a function parameter is of a function type, it will be converted to a pointer to the function type. This means:

```cpp
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
```

can be equivalently written as:

```cpp
void selectionSort(int* array, int size, bool comparisonFcn(int, int))
```

This only works for function parameters, and so is of somewhat limited use. On a non-function parameter, the latter is interpreted as a forward declaration:

```cpp
bool (*ptr)(int, int); // definition of function pointer ptr
bool fcn(int, int);    // forward declaration of function fcn
```

### Providing default functions

If you’re going to allow the caller to pass in a function as a parameter, it can often be useful to provide some standard functions for the caller to use for their convenience. For example, in the selection sort example above, providing the ascending() and descending() function along with the selectionSort() function would make the caller’s life easier, as they wouldn’t have to rewrite ascending() or descending() every time they want to use them.

You can even set one of these as a default parameter:

```cpp
// Default the sort to ascending sort
void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int) = ascending);
```

In this case, as long as the user calls selectionSort normally (not through a function pointer), the comparisonFcn parameter will default to ascending. You will need to make sure that the `ascending` function is declared prior to this point, otherwise the compiler will complain it doesn’t know what `ascending` is.

### Making function pointers prettier with type aliases

Let’s face it -- the syntax for pointers to functions is ugly. However, type aliases can be used to make pointers to functions look more like regular variables:

```cpp
using ValidateFunction = bool(*)(int, int);
```

This defines a type alias called “ValidateFunction” that is a pointer to a function that takes two ints and returns a bool.

Now instead of doing this:

```cpp
bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly
```

You can do this:

```cpp
bool validate(int x, int y, ValidateFunction pfcn) // clean
```

### Using std::function

An alternate method of defining and storing function pointers is to use std::function, which is part of the standard library `<functional>` header. To define a function pointer using this method, declare a std::function object like so:

```cpp
#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and takes two int parameters
```

As you see, both the return type and parameters go inside angled brackets, with the parameters inside parentheses. If there are no parameters, the parentheses can be left empty.

Updating our earlier example with std::function:

```cpp
#include <functional>
#include <iostream>

int foo()
{
    return 5;
}

int goo()
{
    return 6;
}

int main()
{
    std::function<int()> fcnPtr{ &foo }; // declare function pointer that returns an int and takes no parameters
    fcnPtr = &goo; // fcnPtr now points to function goo
    std::cout << fcnPtr() << '\n'; // call the function just like normal

    std::function fcnPtr2{ &foo }; // can also use CTAD to infer template arguments

    return 0;
}
```

Type aliasing std::function can be helpful for readability:

```cpp
using ValidateFunctionRaw = bool(*)(int, int); // type alias to raw function pointer
using ValidateFunction = std::function<bool(int, int)>; // type alias to std::function
```

Also note that std::function only allows calling the function via implicit dereference (e.g. `fcnPtr()`), not explicit dereference (e.g. `(*fcnPtr)()`).

When defining a type alias, we must explicitly specify any template arguments. We can’t use CTAD in this case since there is no initializer to deduce the template arguments from.

### Type inference for function pointers

Much like the _auto_ keyword can be used to infer the type of normal variables, the _auto_ keyword can also infer the type of a function pointer.

```cpp
#include <iostream>

int foo(int x)
{
	return x;
}

int main()
{
	auto fcnPtr{ &foo };
	std::cout << fcnPtr(5) << '\n';

	return 0;
}
```

This works exactly like you’d expect, and the syntax is very clean. The downside is, of course, that all of the details about the function’s parameters types and return type are hidden, so it’s easier to make a mistake when making a call with the function, or using its return value.

### Conclusion

Function pointers are useful primarily when you want to store functions in an array (or other structure), or when you need to pass a function to another function. Because the native syntax to declare function pointers is ugly and error prone, we recommend using std::function. In places where a function pointer type is only used once (e.g. a single parameter or return value), std::function can be used directly. In places where a function pointer type is used multiple times, a type alias to a std::function is a better choice (to prevent repeating yourself).

### Question

```cpp
// Online C++ compiler to run C++ program online
#include <functional> 
#include <iostream>

using namespace std;

using ArithmeticFunction = function<int(int,int)>;

char getOperator()
{
    char op;
    do
    {
        cout << "Enter Operator: ";
        cin >> op;    
        
    }while(op != '+' && op != '-' && op != '*' && op != '/' );
    return op;
}
int getInteger()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    return x;
}
int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    return x / y;
}
ArithmeticFunction getArithmeticFunction(char ch)
{
    switch(ch)
    {
        case '+':
        return &add;
        break;    
        case '-':
        return &subtract;
        break;    
        case '*':
        return &multiply;
        break;    
        case '/':
        return &divide;
        break;            
    }
    return nullptr;
}
int main() {
    char op {getOperator()};
    int x {getInteger()};
    int y{ getInteger() };

    ArithmeticFunction ptr_call {getArithmeticFunction(op)};
    
    if(ptr_call)
        cout << x << " " << op << " " <<  y << " = " << ptr_call(x,y) << endl;

    return 0;
}
```

```cpp
ArithmeticFunction ptr_call { getArithmeticFunction(op) };
```

`ArithmeticFunction` is a **type alias** for `std::function<int(int, int)>`

```cpp
using ArithmeticFunction = function<int(int,int)>;
```

- `getArithmeticFunction(op)` returns the correct function (like `add`, `subtract`, etc.) **based on the operator** `op`.
    

So this line means:

> **“Store the function chosen by the user (like add or subtract) inside `ptr_call`.”**

Example:

- If `op` = `'+'`, then `ptr_call` will hold the `add` function.

```cpp
if(ptr_call)
```

- This checks if `ptr_call` is **valid (not null)**.

```cpp
cout << x << " " << op << " " <<  y << " = " << ptr_call(x, y) << endl;
```

- `ptr_call(x, y)` **calls the stored function** with arguments `x` and `y`.
    
- If `ptr_call` holds `add`, it does `add(x, y)`.
    
- If `ptr_call` holds `multiply`, it does `multiply(x, y)`, etc.

---
# The stack and the heap

The memory that a program uses is typically divided into a few different areas, called segments:

- The code segment (also called a text segment), where the compiled program sits in memory. The code segment is typically read-only.
- The bss segment (also called the uninitialized data segment), where zero-initialized global and static variables are stored.
- The data segment (also called the initialized data segment), where initialized global and static variables are stored.
- The heap, where dynamically allocated variables are allocated from.
- The call stack, where function parameters, local variables, and other function-related information are stored.

For this lesson, we’ll focus primarily on the heap and the stack, as that is where most of the interesting stuff takes place.

### **The heap segment**

The heap segment (also known as the “free store”) keeps track of memory used for dynamic memory allocation. We talked about the heap a bit already in this lesson.

In C++, when you use the new operator to allocate memory, this memory is allocated in the application’s heap segment.

Assuming an int is 4 bytes:

```cpp
int* ptr { new int }; // new int allocates 4 bytes in the heap
int* array { new int[10] }; // new int[10] allocates 40 bytes in the heap
```

The address of this memory is passed back by operator new, and can then be stored in a pointer. You do not have to worry about the mechanics behind the process of how free memory is located and allocated to the user. However, it is worth knowing that sequential memory requests may not result in sequential memory addresses being allocated!

```cpp
int* ptr1 { new int };
int* ptr2 { new int };
// ptr1 and ptr2 may not have sequential addresses
```

When a dynamically allocated variable is deleted, the memory is “returned” to the heap and can then be reassigned as future allocation requests are received. Remember that deleting a pointer does not delete the variable, it just returns the memory at the associated address back to the operating system.

The heap has advantages and disadvantages:

- Allocating memory on the heap is comparatively slow.
- Allocated memory stays allocated until it is specifically deallocated (beware memory leaks) or the application ends (at which point the OS should clean it up).
- Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a variable directly.
- Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.

### **The call stack**

The **call stack** (usually referred to as “the stack”) has a much more interesting role to play. The call stack keeps track of all the active functions (those that have been called but have not yet terminated) from the start of the program to the current point of execution, and handles allocation of all function parameters and local variables.

The call stack is implemented as a stack data structure. So before we can talk about how the call stack works, we need to understand what a stack data structure is.

### **The stack data structure**

A **data structure** is a programming mechanism for organizing data so that it can be used efficiently. You’ve already seen several types of data structures, such as arrays and structs. Both of these data structures provide mechanisms for storing data and accessing that data in an efficient way. There are many additional data structures that are commonly used in programming, quite a few of which are implemented in the standard library, and a stack is one of those.

Consider a stack of plates in a cafeteria. Because each plate is heavy and they are stacked, you can really only do one of three things:

1. Look at the surface of the top plate
2. Take the top plate off the stack (exposing the one underneath, if it exists)
3. Put a new plate on top of the stack (hiding the one underneath, if it exists)

In computer programming, a stack is a container data structure that holds multiple variables (much like an array). However, whereas an array lets you access and modify elements in any order you wish (called **random access**), a stack is more limited. The operations that can be performed on a stack correspond to the three things mentioned above:

1. Look at the top item on the stack (usually done via a function called top(), but sometimes called peek())
2. Take the top item off of the stack (done via a function called pop())
3. Put a new item on top of the stack (done via a function called push())

A stack is a last-in, first-out (LIFO) structure. The last item pushed onto the stack will be the first item popped off. If you put a new plate on top of the stack, the first plate removed from the stack will be the plate you just pushed on last. Last on, first off. As items are pushed onto a stack, the stack grows larger -- as items are popped off, the stack grows smaller.

For example, here’s a short sequence showing how pushing and popping on a stack works:

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

Stack: empty
Push 1
Stack: 1
Push 2
Stack: 1 2
Push 3
Stack: 1 2 3
Pop
Stack: 1 2
Pop
Stack: 1

The plate analogy is a pretty good analogy as to how the call stack works, but we can make a better analogy. Consider a bunch of mailboxes, all stacked on top of each other. Each mailbox can only hold one item, and all mailboxes start out empty. Furthermore, each mailbox is nailed to the mailbox below it, so the number of mailboxes can not be changed. If we can’t change the number of mailboxes, how do we get a stack-like behavior?

First, we use a marker (like a post-it note) to keep track of where the bottom-most empty mailbox is. In the beginning, this will be the lowest mailbox (on the bottom of the stack). When we push an item onto our mailbox stack, we put it in the mailbox that is marked (which is the first empty mailbox), and move the marker up one mailbox. When we pop an item off the stack, we move the marker down one mailbox (so it’s pointed at the top non-empty mailbox) and remove the item from that mailbox. Anything below the marker is considered “on the stack”. Anything at the marker or above the marker is not on the stack.

--> Explanation

#### 1. **The stack and the marker**

- Imagine a stack of mailboxes or boxes arranged vertically.
    
- A **marker** (like a post-it note) tells you **where the next empty spot is** in the stack.
    
- Initially, the stack is empty, so the marker points at the **bottom-most mailbox** (the first empty spot).

#### 2. **Pushing an item (adding to the stack)**

- To **push** an item:
    
    1. Put the item in the mailbox where the marker is pointing (the first empty mailbox).
        
    2. Move the marker **up one mailbox**.
        
- After this, the marker always points to the **next empty spot**, and everything below it is considered **on the stack**.
    

**Example:**

Initial stack (empty):

```cpp
[ ] ← marker (points at first empty mailbox)
```

Push 5:

```cpp
[5] ← item
[ ] ← marker (moves up to next empty mailbox)
```

Push 10:

```cpp
[5]
[10] ← item
[ ] ← marker (next empty)
```

#### 3. **Popping an item (removing from the stack)**

- To **pop** an item:
    
    1. Move the marker **down one mailbox** (so it points to the top item).
        
    2. Remove the item from that mailbox.
        
- After this, everything **below the marker** is still on the stack.
    

**Example:**

Stack before pop:

```cpp
[5]
[10]
[ ] ← marker (empty)
```

Pop:

```cpp
[5]
[ ] ← marker moves down, 10 removed
```

#### 4. **Key idea**

- **Below the marker** → items on the stack.
    
- **At or above the marker** → empty or not part of the stack.
    
- Marker always tracks **where the next push will go**.

#### 💡 **Analogy:** Think of stacking plates:

- Your finger (marker) points at **where the next plate goes**.
    
- Add a plate → finger moves up.
    
- Remove a plate → finger moves down.

#### Imagine the stack like a vertical column of mailboxes

```cpp
Top of stack
   [ ] ← mailbox 4
   [ ] ← mailbox 3
   [ ] ← mailbox 2
   [ ] ← mailbox 1 (bottom)
Bottom of stack
```

- The **bottom** is where the stack starts empty.
    
- The **marker** points to the **first empty mailbox**.
    
- Everything **below the marker** contains stack items.
    
- Everything **at or above the marker** is empty.

#### Step 1: Stack is empty

```cpp
Marker →
   [ ]  ← mailbox 1 (bottom-most empty)
   [ ]  ← mailbox 2
   [ ]  ← mailbox 3
   [ ]  ← mailbox 4
```

- Nothing is on the stack yet.
    
- Marker points to mailbox 1 (first empty slot).

#### Step 2: Push 5

```cpp
   [5]  ← mailbox 1 (now filled)
Marker →
   [ ]  ← mailbox 2 (next empty)
   [ ]  ← mailbox 3
   [ ]  ← mailbox 4
```

- Marker moved **up** to the next empty mailbox.
    
- **Stack items:** mailbox 1 = 5

#### Step 3: Push 10

```cpp
   [5]  ← mailbox 1
   [10] ← mailbox 2
Marker →
   [ ]  ← mailbox 3
   [ ]  ← mailbox 4
```

- Marker is **always at the first empty slot**.
    
- Stack items = mailboxes **below the marker** (mailbox 1 & 2).

#### Step 4: Pop (remove top item)

- Move **marker down** one mailbox → points to mailbox 2.
    
- Remove item from mailbox 2.

```cpp
   [5]  ← mailbox 1
Marker →
   [ ]  ← mailbox 2 (now empty)
   [ ]  ← mailbox 3
   [ ]  ← mailbox 4
```

- Stack items = mailbox 1 (5)

✅ **Key positioning rule:**

- Bottom of the stack = first mailbox.
    
- Marker = **next empty spot**.
    
- Anything **below marker** = on stack.
    
- Anything **at/above marker** = empty.

### **The call stack segment**

#### 🧠 What Is the _Call Stack Segment_?

The **call stack segment** is a special part of memory where your program keeps track of function calls.  
It manages:

- Which function is currently running,
    
- Who called it,
    
- Local variables of those functions.

#### 🚀 What Happens When the Program Starts?

- When your program starts running, the **operating system** automatically pushes the `main()` function onto the call stack.
    
- Then execution begins inside `main()`.

#### 🔁 Function Calls = Push / Pop

Every time a function is called:

- A **new block of memory** is added to the stack → this is called a **stack frame**.
    
- When the function finishes, that block (stack frame) is removed from the stack → **popped** off.
    

This process of removing function frames is called **unwinding the stack**.

#### 📬 Connecting to the Mailbox Analogy

>Our mailbox analogy above is fairly analogous to how the call stack works. The stack itself is a fixed-size chunk of memory addresses. The mailboxes are memory addresses, and the “items” we’re pushing and popping on the stack are called **stack frames**. A stack frame keeps track of all of the data associated with one function call. We’ll talk more about stack frames in a bit. The “marker” is a register (a small piece of memory in the CPU) known as the stack pointer (sometimes abbreviated “SP”). The stack pointer keeps track of where the top of the call stack currently is.

|Mailbox Analogy|Real Memory Concept|
|---|---|
|Stack of mailboxes|Call stack memory segment|
|Item placed in mailbox|Stack frame (function data)|
|Marker / Post-it note|**Stack Pointer (SP)** (CPU register)|
|Pushing item|Calling a function|
|Popping item|Finishing a function|
#### 🧱 What Is a **Stack Frame**?

A **stack frame** is like a package placed in a mailbox — it contains:

- Function parameters (arguments)
    
- Local variables
    
- Return address (where to go back after function ends)
    

Each function call creates **one stack frame**.

#### 🪫 Stack Pointer (SP) – The Marker

The **stack pointer (SP)** is a very small memory register inside the CPU.  
It tells us **where the top of the stack is** — just like our **marker** in the mailbox analogy.

- When we **push** (call function) → SP moves **up**
    
- When we **pop** (return from function) → SP moves **down**

#### ⚡ Optimization: No Need to Erase Memory on Pop

When a function finishes:

- We do **not erase or clean** the memory it used.
    
- We only move the stack pointer down.
    
- That old memory is now considered **unused**, and will be overwritten later.
    

**Why?** It’s faster — clearing memory takes time, so we skip it.

#### 🗂 Visual Summary

```cpp
Call stack (Top = latest function)

| funcB() frame |  ← Top (SP)
| funcA() frame |
| main() frame  |
-----------------  ← Bottom (start of program)
```

- `funcB()` was called by `funcA()`
    
- `funcA()` was called by `main()`
    
- When `funcB()` finishes → its frame is popped, SP moves down

#### 📝 Final Key Points to Remember

✅ The **call stack** stores function calls.  
✅ Each function = **stack frame** with its variables.  
✅ **Stack pointer (SP)** = marker showing top of stack.  
✅ On pop, memory is **not cleared**, only pointer moved.

### Stack in Action (Important to know for recursion)

#### 🔍 What Happens When a Function is Called (Call Stack in Action)

Think of your program like a **to-do list**.  
Every time you call a function, you add a **note card** to a stack saying:

- “I am going to do this task.”
    
- “When I finish, I must return here.”
    

That stack of note cards is the **call stack**.

#### 🧱 Step-by-Step: Calling a Function

##### 🟢 Step 1: A Function is Called

Example:

```cpp
result = add(5, 3);
```

Program sees `add(5, 3)` and says:

> “Pause `main()`. I need to go to `add()` function.”


##### 🟠 Step 2: Create a **Stack Frame** (new note card)

This stack frame has:

|Inside the Frame|Why It’s Needed|
|---|---|
|📍 Return Address|Where to return after function completes|
|🎒 Arguments|Values passed to function (5 and 3)|
|🗂 Local Variables|Variables created inside the function|
|💾 Saved Registers|To restore CPU state later|

📝 **This stack frame is pushed onto the stack.**

##### 🔵 Step 3: CPU Jumps to the Function

Now it starts running code inside `add()`.

#### 🔁 When the Function Ends (Returning Back)

##### 🔴 Step 4: Function is Done → Time to Return

This happens:

|Step|What CPU Does|
|---|---|
|1️⃣|Restore saved registers|
|2️⃣|Pop (remove) the stack frame — local variables are gone|
|3️⃣|Save return value (like 8)|
|4️⃣|Jump back to **Return Address** (back to `main()`)|

#### 🧠 KEY IDEA

❗ **Every function call adds a stack frame.**  
❗ **Every function return removes that frame.**  
This is why it's called a **stack** — just like stacking and unstacking plates.

#### 👀 Why This Matters

|Concept|Needs Stack Understanding|
|---|---|
|🔁 Recursion|Function calling itself repeatedly|
|💥 Stack Overflow|Too many function calls (frames)|
|🐞 Debugging|Seeing call trace in errors|
#### 🧭 Final Point: Memory Direction

- Some computers grow the stack upward in memory.
    
- Others grow it downward.  
    👉 This doesn’t affect how we write programs — it's just a system detail.

#### 🧠 What Is “CPU State”?

The **CPU state** means whatever the CPU was doing **before the function call**:

- What **registers** (temporary CPU memory) were holding
    
- What **instruction** it was about to execute
    
- What **variable values** the CPU was working with

#### 🎯 Why Do We Need to Save and Restore CPU State?

When you call a function, the CPU must:

1. **Pause the current work**
    
2. **Do the work of the new function**
    
3. **Come back and continue exactly where it left off**
    

For that to work, the CPU must **remember everything** about where it paused.  
That’s what “restore CPU state later” means.

### **Stack overflow**

The stack has a limited size, and consequently can only hold a limited amount of information. On Visual Studio for Windows, the default stack size is 1MB. With g++/Clang for Unix variants, it can be as large as 8MB. If the program tries to put too much information on the stack, stack overflow will result. **Stack overflow** happens when all the memory in the stack has been allocated -- in that case, further allocations begin overflowing into other sections of memory.

Stack overflow is generally the result of allocating too many variables on the stack, and/or making too many nested function calls (where function A calls function B calls function C calls function D etc…) On modern operating systems, overflowing the stack will generally cause your OS to issue an access violation and terminate the program.

Here is an example program that will likely cause a stack overflow. You can run it on your system and watch it crash:

```cpp
#include <iostream>

int main()
{
    int stack[10000000];
    std::cout << "hi" << stack[0]; // we'll use stack[0] here so the compiler won't optimize the array away

    return 0;
}
```

This program tries to allocate a huge (likely 40MB) array on the stack. Because the stack is not large enough to handle this array, the array allocation overflows into portions of memory the program is not allowed to use.

Here’s another program that will cause a stack overflow for a different reason:

```cpp
// h/t to reader yellowEmu for the idea of adding a counter
#include <iostream>

int g_counter{ 0 };

void eatStack()
{
    std::cout << ++g_counter << ' ';

    // We use a conditional here to avoid compiler warnings about infinite recursion
    if (g_counter > 0)
        eatStack(); // note that eatStack() calls itself

    // Needed to prevent compiler from doing tail-call optimization
    std::cout << "hi";
}

int main()
{
    eatStack();

    return 0;
}
```

In the above program, a stack frame is pushed on the stack every time function eatStack() is called. Since eatStack() calls itself (and never returns to the caller), eventually the stack will run out of memory and cause an overflow.

>When run on the author’s Windows 10 machine (from within the Visual Studio Community IDE), eatStack() crashed after 4848 calls in debug mode, and 128,679 calls in release mode.

### The stack has advantages and disadvantages:

- Allocating memory on the stack is comparatively fast.
- Memory allocated on the stack stays in scope as long as it is on the stack. It is destroyed when it is popped off the stack.
- All memory allocated on the stack is known at compile time. Consequently, this memory can be accessed directly through a variable.
- Because the stack is relatively small, it is generally not a good idea to do anything that eats up lots of stack space. This includes allocating or copying large arrays or other memory-intensive structures.

---
# Recursion

>A **recursive function** in C++ is a function that calls itself. Here is an example of a poorly-written recursive function:

```cpp
#include <iostream>

void countDown(int count)
{
    std::cout << "push " << count << '\n';
    countDown(count-1); // countDown() calls itself recursively
}

int main()
{
    countDown(5);

    return 0;
}
```

When countDown(5) is called, “push 5” is printed, and countDown(4) is called. countDown(4) prints “push 4” and calls countDown(3). countDown(3) prints “push 3” and calls countDown(2). The sequence of countDown(n) calling countDown(n-1) is repeated indefinitely, effectively forming the recursive equivalent of an infinite loop.

you learned that every function call causes data to be placed on the call stack. Because the countDown() function never returns (it just calls countDown() again), this information is never being popped off the stack! Consequently, at some point, the computer will run out of stack memory, stack overflow will result, and the program will crash or terminate. On the author’s machine, this program counted down to -11732 before terminating!

### **Recursive termination conditions**

Recursive function calls generally work just like normal function calls. However, the program above illustrates the most important difference with recursive functions: you must include a recursive termination condition, or they will run “forever” (actually, until the call stack runs out of memory). A **recursive termination** is a condition that, when met, will cause the recursive function to stop calling itself.

>Recursive termination generally involves using an if statement. Here is our function redesigned with a termination condition (and some extra output):

```cpp
#include <iostream>

void countDown(int count)
{
    std::cout << "push " << count << '\n';

    if (count > 1) // termination condition
        countDown(count-1);

    std::cout << "pop " << count << '\n';
}

int main()
{
    countDown(5);
    return 0;
}
```

Now when we run our program, countDown() will start by outputting the following:

push 5
push 4
push 3
push 2
push 1

>Because of the termination condition, countDown(1) does not call countDown(0) -- instead, the “if statement” does not execute, so it prints “pop 1” and then terminates. At this point, countDown(1) is popped off the stack, and control returns to countDown(2). countDown(2) resumes execution at the point after countDown(1) was called, so it prints “pop 2” and then terminates. The recursive function calls get subsequently popped off the stack until all instances of countDown have been removed.

Thus, this program in total outputs:

push 5
push 4
push 3
push 2
push 1
pop 1
pop 2
pop 3
pop 4
pop 5

>It’s worth noting that the “push” outputs happen in forward order since they occur before the recursive function call. The “pop” outputs occur in reverse order because they occur after the recursive function call, as the functions are being popped off the stack (which happens in the reverse order that they were put on).

### **A more useful example**

Now that we’ve discussed the basic mechanics of recursive function calls, let’s take a look at another recursive function that is slightly more typical:

```cpp
// return the sum of all the integers between 1 (inclusive) and sumto (inclusive)
// returns 0 for negative numbers
int sumTo(int sumto)
{
    if (sumto <= 0)
        return 0; // base case (termination condition) when user passed in an unexpected argument (0 or negative)
    if (sumto == 1)
        return 1; // normal base case (termination condition)

    return sumTo(sumto - 1) + sumto; // recursive function call
}
```

>Recursive programs are often hard to figure out just by looking at them. It’s often instructive to see what happens when we call a recursive function with a particular value. So let’s see what happens when we call this function with parameter sumto = 5.

#### 🧮 Goal: `sumTo(5)`

We want to calculate:  
**1 + 2 + 3 + 4 + 5 = 15**

But the function does it using **recursion** (calling itself).

#### 🛑 First: Base Rules in the Function

- If number is **1** → return **1** (Stop here)
    
- For any number **greater than 1** → ask for `sumTo(number - 1)` and then **add that number**

#### 🔁 Let's Start with `sumTo(5)` (Going Down)

| Function Call | What it asks            | Doesn't know yet |
| ------------- | ----------------------- | ---------------- |
| sumTo(5)      | "What is sumTo(4)?" + 5 | Waiting          |
| sumTo(4)      | "What is sumTo(3)?" + 4 | Waiting          |
| sumTo(3)      | "What is sumTo(2)?" + 3 | Waiting          |
| sumTo(2)      | "What is sumTo(1)?" + 2 | Waiting          |
| sumTo(1)      | I know: **1**           | ✅ Answer found!  |

#### 🧵 Now We Return Back (Coming Up and Adding)

|Call|Calculation|Result|
|---|---|---|
|sumTo(1)|1|1|
|sumTo(2)|1 + 2|3|
|sumTo(3)|3 + 3|6|
|sumTo(4)|6 + 4|10|
|sumTo(5)|10 + 5|15|
#### 🎉 Final Answer

**sumTo(5) = 15**

#### 📝 Short Visual Story

```cpp
sumTo(5) → sumTo(4) + 5
sumTo(4) → sumTo(3) + 4
sumTo(3) → sumTo(2) + 3
sumTo(2) → sumTo(1) + 2
sumTo(1) → 1   (stop here!)
```

Now add everything while returning back:

```cpp
1
1 + 2 = 3
3 + 3 = 6
6 + 4 = 10
10 + 5 = 15  ✅
```

Because recursive functions can be hard to understand by looking at them, good comments are particularly important.

>Note that in the above code, we recurse with value `sumto - 1` rather than `--sumto`. We do this because `operator--` has a side effect, and using a variable that has a side effect applied more than once in a given expression will result in undefined behavior. Using `sumto - 1` avoids side effects, making sumto safe to use more than once in the expression.

### **Recursive algorithms**

#### 🧠 What Are Recursive Algorithms?

A **recursive algorithm** is a way to solve a problem by:

1. **Breaking the problem into a smaller version of itself.**
    
2. **Solving that smaller version (repeat, repeat…)**
    
3. **Then using that smaller solution to get the final answer.**

#### 🔍 Using `sumTo(value)` as an Example

```cpp
sumTo(value)
   = 1 + 2 + 3 + ... + value
```

How recursion solves it:

- It **does not** add everything at once.
    
- It first solves a **smaller problem** → `sumTo(value - 1)`
    
- Then it just **adds the missing part (`value`)** at the end.
    

👉 Example for value = 5

```cpp
sumTo(5) = sumTo(4) + 5
sumTo(4) = sumTo(3) + 4
sumTo(3) = sumTo(2) + 3
sumTo(2) = sumTo(1) + 2
```

#### 🛑 What Is a Base Case?

Some inputs are **so simple** that we already know the answer without any recursion.  
These simple answers are called **base cases**.

Example:  
`sumTo(1)` → The answer is **1** (you don't need recursion to know that).

✅ Base Case = A simple input with a direct answer.

#### 🔐 Why Base Case Is Important?

- It **stops the recursion**.
    
- Without a base case, the function would call itself **forever** and crash.

#### 🧪 Common Base Cases in Recursion

|Type|Base Case Example|
|---|---|
|Numbers|0 or 1|
|Strings|"" (empty string)|
|Pointers|null|

These are values where the answer is obvious and no recursion is needed.

#### 🧵 Summary (In One Line)

> A recursive algorithm solves a big problem by solving a smaller problem first…  
> and stops when input becomes so simple that the answer is obvious (base case).

### **Fibonacci numbers**

**Fibonacci numbers**

One of the most famous mathematical recursive algorithms is the Fibonacci sequence. Fibonacci sequences appear in many places in nature, such as branching of trees, the spiral of shells, the fruitlets of a pineapple, an uncurling fern frond, and the arrangement of a pine cone.

Here is a picture of a Fibonacci spiral:  
![](https://www.learncpp.com/images/CppTutorial/Section7/Fibonacci.png)

```cpp
#include <iostream>

int fibonacci(int count)
{
    if (count == 0)
        return 0; // base case (termination condition)
    if (count == 1)
        return 1; // base case (termination condition)
    return fibonacci(count-1) + fibonacci(count-2);
}

// And a main program to display the first 13 Fibonacci numbers
int main()
{
    for (int count { 0 }; count < 13; ++count)
        std::cout << fibonacci(count) << ' ';

    return 0;
}
```

#### 🔢 Fibonacci Sequence (Basic Idea)

The numbers go like this:

**0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...**

How do we get these?

> Each number = **Sum of the previous two numbers**

#### 🧮 Mathematical Definition

```cpp
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2) , when n > 1
```

#### 🧠 How Recursion Works Here

When you call `fibonacci(n)`:

- If **n = 0 or 1** → Directly return 0 or 1 (Base Case)
    
- If **n > 1** → Return `fibonacci(n-1) + fibonacci(n-2)`  
    (Call function again for smaller values)

### Let’s explain **Fibonacci recursion for 5** in a very clear and simple way, step by step.

We want to find:

```cpp
fibonacci(5)
```

#### 🪜 Step-by-Step Recursive Breakdown

```cpp
fibonacci(5)
= fibonacci(4) + fibonacci(3)
```

Now calculate both parts:

##### 🔹 Part 1: fibonacci(4)

```cpp
fibonacci(4) = fibonacci(3) + fibonacci(2)
```

##### 🔸 Part 2: fibonacci(3)

```cpp
fibonacci(3) = fibonacci(2) + fibonacci(1)
```

Now let’s go deeper:

#### 📌 Break Down fibonacci(4)

```cpp
fibonacci(4)
= fibonacci(3) + fibonacci(2)
```

Break fibonacci(3):

```cpp
fibonacci(3) = fibonacci(2) + fibonacci(1)
```

Break fibonacci(2):

```cpp
fibonacci(2) = fibonacci(1) + fibonacci(0)
```

#### 🧠 Let’s Replace Base Cases

We know:

```cpp
fibonacci(1) = 1
fibonacci(0) = 0
```

Now build back up:

|Call|Result|
|---|---|
|fibonacci(2)|1 + 0 = **1**|
|fibonacci(3)|1 + 1 = **2**|
|fibonacci(4)|2 + 1 = **3**|
|fibonacci(5)|3 + 2 = **5**|
#### ✅ Final Answer:

```cpp
fibonacci(5) = 5
```

#### 🌳 Visual Tree of Calls

```markdown
            fibonacci(5)
           /            \
      fib(4)            fib(3)
      /    \            /    \
   fib(3)  fib(2)    fib(2)  fib(1)
   /  \     /   \     /  \
fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
 / \
fib(1) fib(0)
```

Now substitute base cases and add everything up!

### **Memoization algorithms**

**Memoization** means:  
🗂️ _“Remember the results of expensive function calls, so we don’t calculate them again.”_

#### 🧠 Problem with Normal Recursive Fibonacci

The basic recursive Fibonacci function:

```cpp
fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
```

This creates **many repeated calculations**.

Example:

- fibonacci(5) calls fibonacci(4) and fibonacci(3)
    
- fibonacci(4) again calls fibonacci(3) and fibonacci(2)
    
- fibonacci(3) gets calculated **many times again and again**
    

❗ **Too slow!**  
The normal recursive Fibonacci for `n=12` makes **1205 function calls** → very inefficient!

#### 💡 Solution: Memoization

**Memoization = Save answers you already calculated.**  
Next time, just reuse it — don’t recalculate!

#### 🧾 Memoized Fibonacci Code Explanation

```cpp
static std::vector results{ 0, 1 }; // store known Fibonacci values
```

This vector saves results like:

```cpp
Index:   0   1   2   3   4   5   6  ...
Value:   0   1   1   2   3   5   8  ...
```

#### 🔍 How the Function Works

```cpp
int fibonacci(std::size_t count)
{
    static std::vector results{ 0, 1 };

    // 1️⃣ If we already calculated fibonacci(count), return it from cache
    if (count < results.size())
        return results[count];

    // 2️⃣ Otherwise, compute it and store it in the vector
    results.push_back(fibonacci(count - 1) + fibonacci(count - 2));

    return results[count];
}
```

#### 🏁 Why This Is Faster?

|Version|Function Calls|
|---|---|
|Normal Recursion|1205 calls|
|With Memoization|**35 calls** ✅|

Memoization avoids recalculating the same values again.

#### 🧩 Simple Analogy

Imagine solving math problems:

- Without memoization: You solve **2 + 2** every time from scratch.
    
- With memoization: You remember **2 + 2 = 4** and reuse it. 🧠


let’s walk **exactly** what the memoized `fibonacci` does for `count = 5`, step-by-step. I’ll show the function calls, the `results` cache contents at each point, and what each call returns.

**Initial state**

- `results = [0, 1]` (static cache)
    
- Call we make: `fibonacci(5)`

#### Trace (in order of actual function calls)

1. `fibonacci(5)` — _call #1_
    
    - `count = 5` → not in cache (`5 >= results.size()`), so we must compute `fibonacci(4) + fibonacci(3)`.
        
2. `fibonacci(4)` — _call #2_ (called from `fibonacci(5)`)
    
    - `count = 4` → not in cache, compute `fibonacci(3) + fibonacci(2)`.
        
3. `fibonacci(3)` — _call #3_ (called from `fibonacci(4)`)
    
    - `count = 3` → not in cache, compute `fibonacci(2) + fibonacci(1)`.
        
4. `fibonacci(2)` — _call #4_ (called from `fibonacci(3)`)
    
    - `count = 2` → not in cache, compute `fibonacci(1) + fibonacci(0)`.
        
5. `fibonacci(1)` — _call #5_ (called from `fibonacci(2)`)
    
    - Base case: returns `1`.
        
    - **No change** to `results` (still `[0,1]`).
        
6. `fibonacci(0)` — _call #6_ (called from `fibonacci(2)`)
    
    - Base case: returns `0`.
        
    - **No change** to `results`.
        
7. Back in `fibonacci(2)` — now we have `fibonacci(1)=1` and `fibonacci(0)=0`.
    
    - Compute `1 + 0 = 1`.
        
    - **Store** it: `results.push_back(1)` → `results = [0, 1, 1]`.
        
    - `fibonacci(2)` returns `1`.
        
8. Back in `fibonacci(3)` — it needed `fibonacci(2)` and `fibonacci(1)`.
    
    - `fibonacci(2)` is now **cached** (index 2), so we use `results[2] = 1` (no new call).
        
    - `fibonacci(1)` is base case (we could return it directly or use cache index 1 = 1).
        
    - Compute `1 + 1 = 2`.
        
    - **Store** it: `results.push_back(2)` → `results = [0, 1, 1, 2]`.
        
    - `fibonacci(3)` returns `2`.
        
9. Back in `fibonacci(4)` — it needed `fibonacci(3)` and `fibonacci(2)`.
    
    - Both are now cached: `results[3] = 2`, `results[2] = 1`.
        
    - Compute `2 + 1 = 3`.
        
    - **Store** it: `results.push_back(3)` → `results = [0, 1, 1, 2, 3]`.
        
    - `fibonacci(4)` returns `3`.
        
10. Back in `fibonacci(5)` — it needed `fibonacci(4)` and `fibonacci(3)`.
    
    - Both cached: `results[4] = 3`, `results[3] = 2`.
        
    - Compute `3 + 2 = 5`.
        
    - **Store** it: `results.push_back(5)` → `results = [0, 1, 1, 2, 3, 5]`.
        
    - `fibonacci(5)` returns `5`.
        

#### Summary

- **Final result:** `fibonacci(5) = 5`
    
- **Final cache (`results`):** `[0, 1, 1, 2, 3, 5]`
    
- **Total actual function calls made:** **6**
    
    - (Calls were for counts 5,4,3,2,1,0 — after those, remaining uses read from the cache)

#### Why memoization helped here

Instead of re-computing the same `fibonacci(k)` multiple times, each newly computed Fibonacci number is stored once in `results`. After being stored, later requests reuse it with **no extra recursive calls**, so the number of calls is linear in `n` (roughly `n+1` calls in this small example) rather than exponential.

#### 🧾 The Cache Vector (results)

```cpp
static std::vector results{ 0, 1 };
```

This vector stores **calculated Fibonacci values** using **index positions**:

| Index | Value stored in vector |
| ----- | ---------------------- |
| 0     | 0 (Fibonacci of 0)     |
| 1     | 1 (Fibonacci of 1)     |
| 2     | 1 (Fibonacci of 2)     |
| 3     | 2 (Fibonacci of 3)     |
| 4     | 3 (Fibonacci of 4)     |
| 5     | 5 (Fibonacci of 5)     |
#### 📌 How Indexing Works

When we write:

```cpp
return results[count];
```

It simply means:

👉 **Return the Fibonacci number already stored at position `count`** in the vector.

#### 🧠 Example: fibonacci(5)

##### Step-by-step:

1️⃣ **Start:**  
`results = {0, 1}`  
Indexes → `0 : 0`, `1 : 1`

2️⃣ Need `fibonacci(2)`  
Not in vector → calculate → store at `results[2] = 1`

3️⃣ Need `fibonacci(3)`  
Calculated → `results[3] = 2`

4️⃣ Need `fibonacci(4)`  
Calculated → `results[4] = 3`

5️⃣ Need `fibonacci(5)`  
Calculated → `results[5] = 5`

### **Recursive vs iterative**

One question that is often asked about recursive functions is, “Why use a recursive function if you can do many of the same tasks iteratively (using a _for loop_ or _while loop_)?”. It turns out that you can always solve a recursive problem iteratively -- however, for non-trivial problems, the recursive version is often much simpler to write (and read). For example, while it’s possible to write the Fibonacci function iteratively, it’s a little more difficult! (Try it!)

Iterative functions (those using a for-loop or while-loop) are almost always more efficient than their recursive counterparts. This is because every time you call a function there is some amount of overhead that takes place in pushing and popping stack frames. Iterative functions avoid this overhead.

That’s not to say iterative functions are always a better choice. Sometimes the recursive implementation of a function is so much cleaner and easier to follow that incurring a little extra overhead is more than worth it for the benefit in maintainability, particularly if the algorithm doesn’t need to recurse too many times to find a solution.

In general, recursion is a good choice when most of the following are true:

- The recursive code is much simpler to implement.
- The recursion depth can be limited (e.g. there’s no way to provide an input that will cause it to recurse down 100,000 levels).
- The iterative version of the algorithm requires managing a stack of data.
- This isn’t a performance-critical section of code.

However, if the recursive algorithm is simpler to implement, it may make sense to start recursively and then optimize to an iterative algorithm later.

>Best practice
>Generally favor iteration over recursion, except when recursion really makes sense.

---
# Command line arguments

### 🔍 **1. Why Do We Need Command Line Arguments?**

Normally, when a program starts, it begins at `main()` and waits for the user to **enter input** using `std::cin`.

Example:

```cpp
std::cout << "Enter image filename: ";
std::string filename;
std::cin >> filename;
```

❗ Problem:  
This approach **forces the user to input manually** every time the program runs. This is fine for small tasks, but becomes inefficient when:

- You want to process **hundreds of files automatically**
    
- Another **program or script** wants to call your program
    
- Your program needs to run on a **server or website** (no user typing!)

### 🏁 Solution → Command Line Arguments

Command line arguments allow us to give input **at the moment of launching the program**, like this:

```bash
WordCount MyFile.txt
```

📌 Here:

- `WordCount` → Program name
    
- `MyFile.txt` → Input provided directly via command line
    

💡 This means no asking the user with `cin`. The program **starts and directly has the input** it needs.

### 🧠 2. How Do We Use Command Line Arguments?

We use a different version of `main()`:

```cpp
int main(int argc, char* argv[])
```

#### 🔍 What are `argc` and `argv`?

|Parameter|Meaning|
|---|---|
|`argc`|Argument Count → Number of arguments|
|`argv`|Argument Vector → Array of arguments (C-style strings)|
#### ✅ Key Concept: C-String = Pointer to First Character

In C/C++, a **string** is not a built-in type. A string is just an **array of characters** that ends with a special null character: `'\0'`.

📌 And in C++, the **name of an array** decays to a **pointer to its first element**.

So, when you write:

```cpp
char* str = "Hello";
```

- `"Hello"` is stored as: `H e l l o \0`
    
- `str` is a **pointer to the first character ('H')**
    
- But since we know strings continue until `'\0'`, we treat it as the **entire string**

#### 🪢 Now What About `char* arr[]`?

```cpp
char* names[] = {"Ali", "Ahmed", "Sara"};
```

This is:

- An **array (`[]`)**
    
- Each element is a `char*` → pointer to the first character of a separate string

```cpp
names[0] → "Ali"   → points to 'A'
names[1] → "Ahmed" → points to 'A'
names[2] → "Sara"  → points to 'S'
```

📦 Memory Picture

```cpp
names array:
+----------+----------+----------+
| names[0] | names[1] | names[2] |
+----------+----------+----------+
     ↓          ↓          ↓
   "Ali"     "Ahmed"     "Sara"
```

### 🗂 Example Command

```bash
MyArgs Myfile.txt 100
```

|Index|Argument Value|
|---|---|
|`argv[0]`|Program name (e.g., MyArgs.exe or ./MyArgs)|
|`argv[1]`|`"Myfile.txt"`|
|`argv[2]`|`"100"`|
|`argc`|`3` (total arguments)|

### 🔬 3. Inside the Program

Example code:

```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments:\n";

    for (int i = 0; i < argc; ++i)
        std::cout << i << " " << argv[i] << '\n';

    return 0;
}
```

#### Output when run:

```bash
MyArgs Myfile.txt 100
```

```sql
There are 3 arguments:
0 C:\MyArgs
1 Myfile.txt
2 100
```

### 🔢 4. Numeric Arguments (Conversion Required)

All command-line arguments are **strings**, even if they look like numbers.

To convert argument `"567"` to integer:

```cpp
#include <sstream>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    std::stringstream convert{ argv[1] };  // argv[1] = "567"
    int num{};
    convert >> num;
    std::cout << "Got integer: " << num << '\n';
}
```

#### 💡 3️⃣ Using `std::stringstream` to Convert String → Integer

```cpp
std::stringstream convert{ argv[1] };
```

- This creates a **stringstream object**.
    
- It stores the string `"567"` inside it.

#### 🔁 4️⃣ Extract Integer from Stream

```cpp
int num{};
convert >> num;
```

- Works just like reading from `std::cin`
    
- It tries to read an **int** from the stored string
    
- `"567"` → 567 (as integer)

#### 🖨 5️⃣ Output

```cpp
std::cout << "Got integer: " << num << '\n';
```

✨ Example output:

```cpp
Got integer: 567
```

### 🧵 5. How OS Processes Arguments

Examples:

```bash
MyArgs Hello world!
```

Output:

```bash
1 Hello
2 world!
```

But with quotes:

```bash
MyArgs "Hello world!"
```

Output:

```bash
1 Hello world!
```

### 🎯 Final Summary

|Feature|Purpose|
|---|---|
|Command Line Arguments|Pass input at startup (no need for `cin`)|
|`argc`|Number of arguments|
|`argv`|Array of string arguments|
|Use Case|Automation, scripting, server programs, batch operations|
### 🧾 Practical Tip

Make input required → Use command-line argument  
If missing → Ask user with `cin`  
This gives flexibility to run both manually or automatically.

### 🛠 Passing Command Line Arguments in **VS Code**

In VS Code, command line arguments are set in a file called **`launch.json`** inside the `.vscode` folder.

### 📍 Step-by-Step Guide

#### ✅ Step 1: Run Your Program Once

- Press **`Run > Run Without Debugging`** or **`Ctrl + F5`**
    
- VS Code will ask you to create a **debug configuration**
    
- Choose **"C++ (GDB/LLDB)"** or your compiler option

#### ✅ Step 2: Open `launch.json`

If it didn't open automatically:

- Go to **Run → Open Configurations**
    
- Or press `Ctrl + Shift + P` → _type_ `"Open launch.json"`

#### ✅ Step 3: Add Your Arguments Here

Inside `launch.json`, find or add:

```cpp
"args": ["Myfile.txt", "100"]
```

#### 📌 Example `launch.json`

```cpp
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C++ Run",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}",
            "args": ["Myfile.txt", "100"],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb"
        }
    ]
}
```

#### 🧪 Now In Your Program (`main()`)

```cpp
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    cout << "Argument Count: " << argc << endl;
    for (int i = 0; i < argc; ++i)
        cout << "Arg " << i << ": " << argv[i] << endl;
}
```

💻 When you **Run with Debugger (`F5`)**, Output:

```cpp
Argument Count: 3
Arg 0: C:\path\program
Arg 1: Myfile.txt
Arg 2: 100
```

---
# Ellipsis (and why to avoid them)

### 🔍 What Are Ellipsis (`...`) in C++?

Ellipsis (`...`) allow a function to accept a **variable number of arguments** (like `printf` in C).  
Normally, C++ functions must know **exactly how many arguments** they will receive, but ellipsis breaks that rule.

```cpp
return_type function_name(fixed_arguments, ...);
```

### ⚠ Why Learn This?

Ellipsis are **rarely used and unsafe**. You’ll mostly see them in C-style code or libraries like `printf()`.  
Modern C++ prefers **variadic templates** instead (Safer, type-checked).

In all of the functions we’ve seen so far, the number of parameters a function will take must be known in advance (even if they have default values). However, there are certain cases where it can be useful to be able to pass a variable number of parameters to a function. C++ provides a special specifier known as ellipsis (aka “…”) that allow us to do precisely this.

Because ellipsis are rarely used, potentially dangerous, and we recommend avoiding their use, this section can be considered optional reading.

```
return_type function_name(argument_list, ...)
```

The _argument_list_ is one or more normal function parameters. Note that functions that use ellipsis must have at least one non-ellipsis parameter. Any arguments passed to the function must match the argument_list parameters first.

The ellipsis (which are represented as three periods in a row) must always be the last parameter in the function. The ellipsis capture any additional arguments (if there are any). Though it is not quite accurate, it is conceptually useful to think of the ellipsis as an array that holds any additional parameters beyond those in the argument_list.

### **An ellipsis example**

The best way to learn about ellipsis is by example. So let’s write a simple program that uses ellipsis. Let’s say we want to write a function that calculates the average of a bunch of integers. We’d do it like this:

```cpp
#include <iostream>
#include <cstdarg> // needed to use ellipsis

// The ellipsis must be the last parameter
// count is how many additional arguments we're passing
double findAverage(int count, ...)
{
    int sum{ 0 };

    // We access the ellipsis through a va_list, so let's declare one
    std::va_list list;

    // We initialize the va_list using va_start.  The first argument is
    // the list to initialize.  The second argument is the last non-ellipsis
    // parameter.
    va_start(list, count);

    // Loop through all the ellipsis values
    for (int arg{ 0 }; arg < count; ++arg)
    {
         // We use va_arg to get values out of our ellipsis
         // The first argument is the va_list we're using
         // The second argument is the type of the value
         sum += va_arg(list, int);
    }

    // Cleanup the va_list when we're done.
    va_end(list);

    return static_cast<double>(sum) / count;
}

int main()
{
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';

    return 0;
}
```

This code prints:

3
3.5

As you can see, this function takes a variable number of parameters! Now, let’s take a look at the components that make up this example.

First, we have to include the cstdarg header. This header defines va_list, va_arg, va_start, and va_end, which are macros that we need to use to access the parameters that are part of the ellipsis.

We then declare our function that uses the ellipsis. Remember that the argument list must be one or more fixed parameters. In this case, we’re passing in a single integer that tells us how many numbers to average. The ellipsis always comes last.

Note that the ellipsis parameter has no name! Instead, we access the values in the ellipsis through a special type known as va_list. It is conceptually useful to think of va_list as a pointer that points to the ellipsis array. First, we declare a va_list, which we’ve called “list” for simplicity.

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

The next thing we need to do is make list point to our ellipsis parameters. We do this by calling va_start(). va_start() takes two parameters: the va_list itself, and the name of the _last_ non-ellipsis parameter in the function. Once va_start() has been called, va_list points to the first parameter in the ellipsis.

To get the value of the parameter that va_list currently points to, we use va_arg(). va_arg() also takes two parameters: the va_list itself, and the type of the parameter we’re trying to access. Note that va_arg() also moves the va_list to the next parameter in the ellipsis!

Finally, to clean up when we are done, we call va_end(), with va_list as the parameter.

Note that va_start() can be called again any time we want to reset the va_list to point to the first parameter in the ellipses again.

#### 📌 How It Works Internally

|Step|Function/Macro|Purpose|
|---|---|---|
|`va_list list;`|Declare handler to access extra arguments||
|`va_start(list, count);`|Start at the first variable argument after `count`||
|`va_arg(list, int);`|Read next variable (`int`)||
|`va_end(list);`|Cleanup||
### 📦 Key Concept: No Type Safety!

Ellipsis **do not know** the types of extra values. You must manually tell it using `va_arg(list, TYPE)`.

🚨 Example Problem:

```cpp
findAverage(3, 1.0, 2, 3);   // OOPS! 1.0 is double, but expected int
```

Output? **Garbage!** Because it's reading double bytes as if it's an int.

### 💣 2 Major Dangers of Ellipsis

|Danger|Explanation|
|---|---|
|❌ No Type Checking|Compiler doesn’t stop wrong types|
|❌ No Argument Count|Function doesn’t know how many were passed|

### 🛑 Common Mistakes (Hard Bugs!)

#### ❗ Wrong Count

```cpp
findAverage(5, 1, 2, 3, 4);   // Says 5 values, gave 4 → reads garbage
```

#### ❗ Extra Values

```cpp
findAverage(5, 1, 2, 3, 4, 5, 6);  // Extra ignored or causes wrong value
```

### 🏁 Final Recommendation

❌ Avoid ellipsis in C++  
✅ Use **containers**, **std::vector**, or **variadic templates** (C++11+)

Example Modern Alternative:

```cpp
template<typename... Args>
double findAverage(Args... args) {
    std::vector<int> nums{args...};
    double sum = 0;
    for (int n : nums) sum += n;
    return sum / nums.size();
}
```

==typename... Args means many types which will store as a Args and that many types will be appointed to ... args which mean many variables or parameters so all set think of it like we made ... elipse for first types and then for parameters from which that types will be appointed.  

### 🧱 1. `template<typename... Args>`

This tells C++:

> "I am writing a function that can accept **any number of arguments of any type**."

- `Args...` is called a **parameter pack** (means many types).

### 📥 2. `double findAverage(Args... args)`

This is the function itself.

- `Args... args` = all the values you pass (like 1, 2, 3, 4, 5).
    
- If you write:

```cpp
findAverage(2, 4, 6);
```

- Then `args...` will contain `{2, 4, 6}`.

### 📦 3. `std::vector<int> nums{args...};`

This line **collects all the arguments** and puts them into a vector of integers.

Example:

```cpp
findAverage(1, 2, 3, 4);
```

→ `nums = {1, 2, 3, 4}`

### ➕ 4. Sum All Numbers

```cpp
double sum = 0;
for (int n : nums) sum += n;
```

- Goes through each number in `nums`
    
- Adds them into `sum`

### 🧮 5. Calculate and Return Average

```cpp
return sum / nums.size();
```

- `sum` = total of all numbers
    
- `nums.size()` = how many numbers
    
- Final result = sum / count

```cpp
std::cout << findAverage(1, 2, 3, 4, 5); // → 3
std::cout << findAverage(10, 20);       // → 15
```

### 🛑 Important Point!

This example assumes **all inputs are integers** (because vector is `std::vector<int>`). It will not correctly work for `double` like `findAverage(1.5, 2.5)`. We can improve that later.

---
# Introduction to lambdas (anonymous functions)

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

// Our function will return true if the element matches
bool containsNut(std::string_view str)
{
    // std::string_view::find returns std::string_view::npos if it doesn't find
    // the substring. Otherwise it returns the index where the substring occurs
    // in str.
    return str.find("nut") != std::string_view::npos;
}

int main()
{
    constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

    // Scan our array to see if any elements contain the "nut" substring
    auto found{ std::find_if(arr.begin(), arr.end(), containsNut) };

    if (found == arr.end())
    {
        std::cout << "No nuts\n";
    }
    else
    {
        std::cout << "Found " << *found << '\n';
    }

    return 0;
}
```

This code searches through an array of strings looking for the first element that contains the substring “nut”. Thus, it produces the result:

Found walnut

And while it works, it could be improved.

The root of the issue here is that `std::find_if` requires that we pass it a function pointer. Because of that, we are forced to define a function that’s only going to be used once, that must be given a name, and that must be put in the global scope (because functions can’t be nested!). The function is also so short, it’s almost easier to discern what it does from the one line of code than from the name and comments.

### Lambdas are anonymous functions

>A **lambda expression** (also called a **lambda** or **closure**) allows us to define an anonymous function inside another function. The nesting is important, as it allows us both to avoid namespace naming pollution, and to define the function as close to where it is used as possible (providing additional context).

The syntax for lambdas is one of the weirder things in C++, and takes a bit of getting used to. Lambdas take the form:

```
[ captureClause ] ( parameters ) -> returnType
{
    statements;
}
```

- The capture clause can be empty if no captures are needed.
- The parameter list can be empty if no parameters are required. It can also be omitted entirely unless a return type is specified.
- The return type is optional, and if omitted, `auto` will be assumed (thus using type deduction used to determine the return type). While we previously noted that type deduction for function return types should be avoided, in this context, it’s fine to use (because these functions are typically so trivial).

Also note that lambdas (being anonymous) have no name, so we don’t need to provide one.

This means a trivial lambda definition looks like this:

```cpp
#include <iostream>

int main()
{
  [] {}; // a lambda with an omitted return type, no captures, and omitted parameters.

  return 0;
}
```

Let’s rewrite the above example using a lambda:

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main()
{
  constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  // Define the function right where we use it.
  auto found{ std::find_if(arr.begin(), arr.end(),
                           [](std::string_view str) // here's our lambda, no capture clause
                           {
                             return str.find("nut") != std::string_view::npos;
                           }) };

  if (found == arr.end())
  {
    std::cout << "No nuts\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }

  return 0;
}
```

This works just like the function pointer case, and produces an identical result:

`Found walnut`

Note how similar our lambda is to our `containsNut` function. They both have identical parameters and function bodies. The lambda has no capture clause (we’ll explain what a capture clause is in the next lesson) because it doesn’t need one. And we’ve omitted the trailing return type in the lambda (for conciseness), but since `operator!=` returns a `bool`, our lambda will return a `bool` too.

>Best Practice:
>
	Following the best practice of defining things in the smallest scope and closest to first use, lambdas are preferred over normal functions when we need a trivial, one-off function to pass as an argument to some other function.

### Type of a lambda

#### 🧩 What is a Lambda?

A **lambda expression** is basically an **anonymous function** — a small, unnamed function that you can define right where you need it.

Example:

```cpp
[](int i){ return i % 2 == 0; }
```

This function takes an integer `i`, and returns whether it’s even.

You can pass this directly to algorithms like `std::find_if`, `std::all_of`, etc.

#### 💡 Function Literal

If you write a lambda **directly where it’s used**, like this:

```cpp
return std::all_of(array.begin(), array.end(), [](int i){ return (i % 2) == 0; });
```

It’s called a **function literal** — because just like you can write a literal `42` for an integer or `"Hello"` for a string, you are literally writing the function where you use it.

The downside?  
It can make the line **hard to read**, especially if the lambda body is big.

#### 🧾 Naming a Lambda

You can instead **store the lambda in a variable**, give it a name, and use it later:

```cpp
auto isEven{
  [](int i)
  {
    return (i % 2) == 0;
  }
};

return std::all_of(array.begin(), array.end(), isEven);
```

This improves readability.  
Now, when you read the last line, you can think:

> “Return whether all elements in the array are even.”

Much cleaner, right?

#### 🧠 Key Insights

1. Storing a lambda in a variable lets you **give it a meaningful name**.  
    → `isEven`, `isPositive`, `printValue`, etc.
    
2. You can **reuse** it multiple times in the code.
    

Example:

```cpp
auto isEven = [](int x){ return x % 2 == 0; };

std::all_of(arr.begin(), arr.end(), isEven);
std::any_of(arr.begin(), arr.end(), isEven);
```

#### ❓ But what is the **type** of a lambda?

Here’s the interesting part:

> Every lambda expression has a **unique compiler-generated type**.

That means:

- You can’t write it manually.
    
- You can’t do `LambdaType isEven = ...;` — because that type doesn’t have a name.
    
- The compiler secretly creates a **struct**-like type for each lambda.
    

For example, this:

```cpp
[](int i){ return i % 2 == 0; }
```

might be turned into something like this (behind the scenes):

```cpp
struct CompilerGeneratedType {
    bool operator()(int i) const { return i % 2 == 0; }
};
```

So lambdas are actually **objects** with a function-call operator `operator()` — these are called **functors**.

#### ⚙️ 3 Ways to Store a Lambda

Since we don’t know the type, we have three main options for storing a lambda:

##### 1️⃣ Function pointer (only for empty capture lambdas)

```cpp
double (*addNumbers1)(double, double){
  [](double a, double b) {
    return a + b;
  }
};
```

- Works only if the lambda has **no captures** (the part in `[]` is empty).
    
- No extra overhead.
    
- Limited use.

##### 2️⃣ `std::function`

```cpp
std::function addNumbers2{
  [](double a, double b) {
    return a + b;
  }
};
```

or (pre-C++17 syntax):

```cpp
std::function<double(double, double)> addNumbers2{
  [](double a, double b) {
    return a + b;
  }
};
```

- Works even if the lambda **captures variables**.
    
- Has **some overhead** (because it uses type erasure and dynamic allocation).
    
- Explicitly shows the parameter and return types.

##### 3️⃣ `auto` (best way)

```cpp
auto addNumbers3{
  [](double a, double b) {
    return a + b;
  }
};
```

- The compiler automatically deduces the **true lambda type**.
    
- No overhead.
    
- Works with all lambdas.
    

✅ **Best practice:**

> Use `auto` whenever you store a lambda.

#### 🏃 Passing a Lambda to a Function

There are **4 ways** to pass a lambda to another function.

Let’s look at each one:

##### **Case 1: Using `std::function` parameter**

```cpp
void repeat1(int repetitions, const std::function<void(int)>& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}
```

- The parameter `fn` can hold **any callable** that matches the signature `void(int)`.
    
- Easy to read and flexible.
    
- But converting the lambda to `std::function` adds a **small performance overhead**.
    

Usage:

```cpp
repeat1(3, lambda);
```

##### **Case 2: Function Template with Type Parameter**

```cpp
template <typename T>
void repeat2(int repetitions, const T& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}
```

- The compiler generates a specialized version of the function where `T` is the actual lambda type.
    
- Very efficient (no overhead).
    
- But the function signature doesn’t clearly tell what the callable’s parameters are.

##### **Case 3: C++20 Abbreviated Template Syntax**

```cpp
void repeat3(int repetitions, const auto& fn)
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}
```

- Same as case 2, but shorter and cleaner.
    
- Requires C++20 or later.

##### **Case 4: Function Pointer Parameter**

```cpp
void repeat4(int repetitions, void (*fn)(int))
{
    for (int i{ 0 }; i < repetitions; ++i)
        fn(i);
}
```

- Only works with lambdas **without captures**.
    
- The compiler can convert such lambdas into a function pointer automatically.

##### 🧩 Example Using All 4

```cpp
int main()
{
    auto lambda = [](int i)
    {
        std::cout << i << '\n';
    };

    repeat1(3, lambda);
    repeat2(3, lambda);
    repeat3(3, lambda);
    repeat4(3, lambda);

    return 0;
}
```

All four calls print:

```cpp
0
1
2
```

#### ✅ Best Practices Summary

|Situation|Best Approach|
|---|---|
|Store a lambda in a variable|Use `auto`|
|Pass a lambda to a function (C++20)|Use `auto` parameter|
|Pass a lambda to a function (pre-C++20)|Use template `<typename T>` parameter|
|Lambda has no captures|Function pointer also works|
|Want explicit parameter/return types|Use `std::function`|
#### 💭 Quick Recap

- Each **lambda** has a **unique, compiler-generated type** → not directly usable.
    
- Lambdas are **functor objects** (they overload `operator()`).
    
- Use `auto` to store them.
    
- Use template or `auto` parameter to pass them efficiently.
    
- Use `std::function` when you need flexibility or explicit types.

### Generic lambdas

#### ⚙️ What are _generic lambdas_?

Normally, lambdas need you to **specify the parameter types**, like `int`, `double`, etc.

But since **C++14**, you can write:

```cpp
auto print = [](auto value) {
    std::cout << value << '\n';
};
```

Now `print` can take **any type**:

```cpp
print(42);        // int
print(3.14);      // double
print("Hello");   // const char*
```

The compiler automatically **infers the type** for `auto`, just like it does for variables.

That’s why this is called a **generic lambda** — it can work with _many different types_, similar to **templates**.

#### 🧩 How it actually works

Inside, the compiler secretly treats it like a **template function**.

So:

```cpp
[](auto x, auto y) { return x + y; }
```

is roughly equivalent to:

```cpp
template <typename T1, typename T2>
auto operator()(T1 x, T2 y) const {
    return x + y;
}
```

That’s why the explanation says:

> “When used in the context of a lambda, `auto` is just a shorthand for a template parameter.”

==We cant use auto in normal function defination!

#### 📘 Example from the lesson

##### Code:

```cpp
const auto sameLetter{
    std::adjacent_find(months.begin(), months.end(),
        [](const auto& a, const auto& b) {
            return a[0] == b[0];
        })
};
```

Here’s what’s happening:

1. The lambda takes **two values** `a` and `b` (consecutive elements from the array `months`).
    
2. It checks if their **first letters** match.
    
3. Because we wrote `const auto&`, it will automatically work for:
    
    - `const char*`
        
    - `std::string`
        
    - `std::string_view`
        
    - or any other string-like type.
        

That’s the power of **generic lambdas** — the same code works for different data types.

✅ Output:

```cpp
June and July start with the same letter
```

#### ⚠️ Why not always use `auto`?

Sometimes `auto` gives you a **less convenient type**.

For example:

```cpp
[](auto str) { return str.length(); }
```

If you pass a **C-style string** (like `"June"`), `auto` will deduce `const char*`, and pointers **don’t have `.length()`** → ❌ error.

So in that case, you should explicitly say:

```cpp
[](std::string_view str) { return str.length(); }
```

Now it will work whether you pass:

```cpp
"June"                     // const char*
std::string("June")        // std::string
std::string_view("June")   // std::string_view
```

✅ Output:

```cpp
There are 2 months with 5 letters
```

#### 🪄 Summary

|Concept|Explanation|
|---|---|
|**Generic Lambda**|A lambda that uses `auto` in its parameters.|
|**Why “generic”?**|Because it can accept different data types, like a template.|
|**When introduced**|C++14|
|**Works like**|Template function (`auto` = template parameter)|
|**When to use**|When your lambda should work for any type.|
|**When _not_ to use**|When you need specific operations that only certain types support (e.g., `.length()`)|

### Constexpr lambdas

As of C++17, lambdas are implicitly constexpr if the result satisfies the requirements of a constant expression. This generally requires two things:

- The lambda must either have no captures, or all captures must be constexpr.
- The functions called by the lambda must be constexpr. Note that many standard library algorithms and math functions weren’t made constexpr until C++20 or C++23.

In the above example, our lambda would not be implicitly constexpr in C++17 but it would be in C++20 (as `std::count_if` was made constexpr in C++20). This means in C++20 we can make `fiveLetterMonths` constexpr:

```cpp
constexpr auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
                                     [](std::string_view str) {
                                       return str.length() == 5;
                                     }) };
```

### Generic lambdas and static variables

we discussed that when a function template contains a static local variable, each function instantiated from that template will receive its own independent static local variable. This may cause issues if that is not expected.

Generic lambdas work the same way: a unique lambda will be generated for each different type that `auto` resolves to.

The following example shows how one generic lambda turns into two distinct lambdas:

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

int main()
{
  // Print a value and count how many times @print has been called.
  auto print{
    [](auto value) {
      static int callCount{ 0 };
      std::cout << callCount++ << ": " << value << '\n';
    }
  };

  print("hello"); // 0: hello
  print("world"); // 1: world

  print(1); // 0: 1
  print(2); // 1: 2

  print("ding dong"); // 2: ding dong

  return 0;
}
```

Output

```
0: hello
1: world
0: 1
1: 2
2: ding dong
```

In the above example, we define a lambda and then call it with two different parameters (a string literal parameter, and an integer parameter). This generates two different versions of the lambda (one with a string literal parameter, and one with an integer parameter).

Most of the time, this is inconsequential. However, note that if the generic lambda uses static duration variables, those variables are not shared between the generated lambdas.

We can see this in the example above, where each type (string literals and integers) has its own unique count! Although we only wrote the lambda once, two lambdas were generated -- and each has its own version of `callCount`. To have a shared counter between the two generated lambdas, we’d have to define a global variable or a `static` local variable outside of the lambda. As you know from previous lessons, both global- and static local variables can cause problems and make it more difficult to understand code. We’ll be able to avoid those variables after talking about lambda captures in the next lesson.

### Return type deduction and trailing return types

If return type deduction is used, a lambda’s return type is deduced from the `return`-statements inside the lambda, and all return statements in the lambda must return the same type (otherwise the compiler won’t know which one to prefer).

For example:

```cpp
#include <iostream>

int main()
{
  auto divide{ [](int x, int y, bool intDivision) { // note: no specified return type
    if (intDivision)
      return x / y; // return type is int
    else
      return static_cast<double>(x) / y; // ERROR: return type doesn't match previous return type
  } };

  std::cout << divide(3, 2, true) << '\n';
  std::cout << divide(3, 2, false) << '\n';

  return 0;
}
```

This produces a compile error because the return type of the first return statement (int) doesn’t match the return type of the second return statement (double).

In the case where we’re returning different types, we have two options:

1. Do explicit casts to make all the return types match, or
2. explicitly specify a return type for the lambda, and let the compiler do implicit conversions.

The second case is usually the better choice:

```cpp
#include <iostream>

int main()
{
  // note: explicitly specifying this returns a double
  auto divide{ [](int x, int y, bool intDivision) -> double {
    if (intDivision)
      return x / y; // will do an implicit conversion of result to double
    else
      return static_cast<double>(x) / y;
  } };

  std::cout << divide(3, 2, true) << '\n';
  std::cout << divide(3, 2, false) << '\n';

  return 0;
}
```

That way, if you ever decide to change the return type, you (usually) only need to change the lambda’s return type, and not touch the lambda body.

### Standard library function objects

For common operations (e.g. addition, negation, or comparison) you don’t need to write your own lambdas, because the standard library comes with many basic callable objects that can be used instead. These are defined in the `[<functional>]`header.

In the following example:

```cpp
#include <algorithm>
#include <array>
#include <iostream>

bool greater(int a, int b)
{
  // Order @a before @b if @a is greater than @b.
  return a > b;
}

int main()
{
  std::array arr{ 13, 90, 99, 5, 40, 80 };

  // Pass greater to std::sort
  std::sort(arr.begin(), arr.end(), greater);

  for (int i : arr)
  {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  return 0;
}
```

Output

99 90 80 40 13 5

Instead of converting our `greater` function to a lambda (which would obscure its meaning a bit), we can instead use `std::greater`:

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <functional> // for std::greater

int main()
{
  std::array arr{ 13, 90, 99, 5, 40, 80 };

  // Pass std::greater to std::sort
  std::sort(arr.begin(), arr.end(), std::greater{}); // note: need curly braces to instantiate object

  for (int i : arr)
  {
    std::cout << i << ' ';
  }

  std::cout << '\n';

  return 0;
}
```

Output

99 90 80 40 13 5

### Conclusion

Lambdas and the algorithm library may seem unnecessarily complicated when compared to a solution that uses a loop. However, this combination can allow some very powerful operations in just a few lines of code, and can be more readable than writing your own loops. On top of that, the algorithm library features powerful and easy-to-use parallelism, which you won’t get with loops. Upgrading source code that uses library functions is easier than upgrading code that uses loops.

Lambdas are great, but they don’t replace regular functions for all cases. Prefer regular functions for non-trivial and reusable cases.

==Quiz Remaining Click Below:

[Quiz](https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/#:~:text=and%20reusable%20cases.-,Quiz%20time,-Question%20%231)

---
# Lambda Captures

Now, let’s modify the nut example and let the user pick a substring to search for. This isn’t as intuitive as you might expect.

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
  std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  // Ask the user what to search for.
  std::cout << "search for: ";

  std::string search{};
  std::cin >> search;

  auto found{ std::find_if(arr.begin(), arr.end(), [](std::string_view str) {
    // Search for @search rather than "nut".
    return str.find(search) != std::string_view::npos; // Error: search not accessible in this scope
  }) };

  if (found == arr.end())
  {
    std::cout << "Not found\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }

  return 0;
}
```

This code won’t compile. Unlike nested blocks, where any identifier accessible in the outer block is accessible in the nested block, lambdas can only access certain kinds of objects that have been defined outside the lambda. This includes:

- Objects with static (or thread local) storage duration (this includes global variables and static locals)
- Objects that are constexpr (explicitly or implicitly)

Since `search` fulfills none of these requirements, the lambda can’t see it.

>[!Tip]
>Lambdas can only access certain kinds of objects that have been defined outside the lambda, including those with static storage duration (e.g. global variables and static locals) and constexpr objects.

To access `search` from within the lambda, we’ll need to use a capture clause.

### The capture clause

The **capture clause** is used to (indirectly) give a lambda access to variables available in the surrounding scope that it normally would not have access to. All we need to do is list the entities we want to access from within the lambda as part of the capture clause. In this case, we want to give our lambda access to the value of variable `search`, so we add it to the capture clause:

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>

int main()
{
  std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

  std::cout << "search for: ";

  std::string search{};
  std::cin >> search;

  // Capture @search                                vvvvvv
  auto found{ std::find_if(arr.begin(), arr.end(), [search](std::string_view str) {
    return str.find(search) != std::string_view::npos;
  }) };

  if (found == arr.end())
  {
    std::cout << "Not found\n";
  }
  else
  {
    std::cout << "Found " << *found << '\n';
  }

  return 0;
}
```

The user can now search for an element of our array.

Output

search for: nana
Found banana

### 🧩 1. What _actually happens_ when a lambda “captures” something

When you write a lambda like this:

```cpp
int search{42};

auto find = [search]() {
    std::cout << search << '\n';
};
```

It might look like the lambda is directly accessing `search` from `main()`, but **it’s not**.

👉 What’s really happening:

- When the lambda is _defined_, the compiler **creates an object** behind the scenes.
    
- That object has **member variables** for every captured variable.
    
- So `search` in the capture becomes a _data member_ of the lambda object.
    
- That data member is **initialized (copied)** from the current value of `search` at that moment.
    

So:

- The lambda now has its **own copy** of `search`.
    
- Changing `search` in main() won’t affect the lambda’s `search`, and vice versa.
    

🧠 **Key idea:**

> Captured variables are _copies_ (clones) stored inside the lambda object — not direct references to the originals (unless you use reference capture).

### ⚙️ 2. Lambdas are actually **objects** (functors)

Even though lambdas _look_ like functions, they’re **actually objects** that behave like functions — i.e., they are **functors** (objects with an overloaded `operator()`).

Example:

```cpp
auto f = []() { std::cout << "Hello"; };
```

is basically like writing:

```cpp
struct LambdaGenerated {
    void operator()() const {
        std::cout << "Hello";
    }
};

LambdaGenerated f;
```

So when you “call the lambda” using `f();`, you’re really calling `f.operator()();`.

And any variable captured is a **member** of this object.

### 🧱 3. Captures are **const** by default

Example:

```cpp
int ammo{10};

auto shoot = [ammo]() {
    --ammo; // ❌ ERROR
};
```

This fails because:

- Captured variables are copied as _const members_ inside the lambda object.
    
- The lambda’s `operator()` is `const` by default.
    
- So you can’t modify captured values unless you mark the lambda as `mutable`.

### ✏️ 4. Making captures **mutable**

You can allow modification like this:

```cpp
int ammo{10};

auto shoot = [ammo]() mutable {
    --ammo;
    std::cout << "Pew! " << ammo << '\n';
};
```

Now it compiles and runs.

Output:

```cpp
Pew! 9
Pew! 8
10 shot(s) left
```

👉 Explanation:

- `mutable` allows modifying the _lambda’s copy_ of `ammo`.
    
- But it does **not** modify the original `ammo` in `main()`.
    
- The lambda keeps its internal copy, which persists across calls.
    

🧠 So when you call it twice, it decrements its own copy from 10 → 9 → 8.

### 🔗 5. Capture by **reference (&)**

If you want the lambda to modify the original variable, capture by **reference**:

```cpp
int ammo{10};

auto shoot = [&ammo]() {
    --ammo;
    std::cout << "Pew! " << ammo << '\n';
};

shoot();
std::cout << ammo;  // prints 9
```

Now it modifies the original `ammo` in `main()`.

💡 When capturing by reference:

- The lambda doesn’t copy the variable.
    
- It stores a _reference_ to the original variable.
    
- If that variable changes (or goes out of scope), the lambda “sees” that.

### ⚔️ 6. Capturing **multiple variables**

You can capture multiple variables by mixing values and references:

```cpp
[health, armor, &enemies]() { /* ... */ };
```

- `health` and `armor` are captured by value (copies)
    
- `enemies` is captured by reference
    

### 🧮 7. Default captures (= and &)

Typing every variable name can be annoying, so you can tell the compiler how to _automatically_ capture variables.

|Default capture|Meaning|
|---|---|
|`[=]`|Capture _all used variables_ by value|
|`[&]`|Capture _all used variables_ by reference|

Example:

```cpp
auto found = std::find_if(areas.begin(), areas.end(),
                          [=](int knownArea) {
                              return width * height == knownArea;
                          });
```

Here, `width` and `height` are captured by **value** automatically.

You can mix defaults with explicit captures:

```cpp
[=, &enemies]() {};  // all by value, except enemies by reference
[&, armor]() {};     // all by reference, except armor by value
```

⚠️ Rules:

- Default capture must appear first.
    
- You can’t capture the same variable twice.
    
- `[&, &armor]` or `[=, armor]` are illegal.

### 🧠 8. Defining **new variables** in capture

You can define new variables inside the capture list:

```cpp
[userArea{width * height}](int knownArea) {
    return userArea == knownArea;
}
```

Here:

- `userArea` is calculated _once_ when the lambda is created.
    
- It’s stored inside the lambda object.
    
- It’s not re-evaluated every time the lambda runs.
    

### ⚠️ 9. **Dangling captures** (a common mistake)

If you capture a variable **by reference**, but that variable dies, the lambda is left holding a _dangling reference_ → **undefined behavior**.

Example:

```cpp
auto makeWalrus(const std::string& name)
{
  return [&]() {
    std::cout << name << '\n'; // ❌ undefined behavior
  };
}

int main() {
  auto sayName = makeWalrus("Roofus"); // "Roofus" is temporary
  sayName(); // dangling reference used
}
```

When `makeWalrus` returns, the parameter `name` is destroyed.  
The lambda still points to it — bad!

✅ Fix: capture by **value**

```cpp
return [=]() {
  std::cout << name << '\n'; // safe
};
```

### 🧍‍♂️ 10. Unintended **copies** of mutable lambdas

Because lambdas are objects, **they can be copied.**

Example:

```cpp
auto count = [i = 0]() mutable {
  std::cout << ++i << '\n';
};

count();       // prints 1
auto other = count;  // copy lambda object (copies i = 1)
count();       // prints 2
other();       // prints 2
```

Each lambda object keeps its own copy of captured variables.

### 💡 11. Copies in `std::function` parameters

If you pass a lambda into a function expecting a `std::function`, the lambda gets **copied**.

```cpp
void myInvoke(const std::function<void()>& fn) {
    fn();
}

auto count = [i = 0]() mutable { std::cout << ++i << '\n'; };

myInvoke(count);
myInvoke(count);
myInvoke(count);
```

Output:

```cpp
1
1
1
```

Why? Because `myInvoke(count)` creates a **temporary `std::function`**, which copies the lambda each time.

### ✅ Fixes for this issue

#### Option 1 — Store it in a `std::function` first:

```cpp
std::function<void()> count = [i = 0]() mutable {
  std::cout << ++i << '\n';
};

myInvoke(count); // No extra copies
myInvoke(count);
```

Output:

```cpp
1
2
3
```

#### Option 2 — Use `std::ref()` (reference wrapper)

```cpp
myInvoke(std::ref(count));
```

This makes sure the lambda is **not copied**, only _referenced_.

### 🧭 12. Best Practices Summary

✅ **Capture by value**  
– When you only need to read variables, not modify them.  
– Safer, no dangling references.

✅ **Capture by reference**  
– When you want to modify external variables.  
– Make sure captured variables _outlive_ the lambda.

✅ **Avoid mutable lambdas**  
– They can be confusing and cause bugs when copied or used in multithreaded contexts.

✅ **If using mutable lambdas in std::function**  
– Use `std::ref()` or wrap in `std::function` yourself to avoid unintentional copies.

✅ **Define new variables in capture** only when short and clear.

==Quiz Remaining 
https://www.learncpp.com/cpp-tutorial/lambda-captures/#:~:text=add%20parallel%20execution.-,Quiz%20time,-Question%20%231

---

# ==[Summary And Quiz Of Whole Chapter](https://www.learncpp.com/cpp-tutorial/chapter-20-summary-and-quiz/)

---
