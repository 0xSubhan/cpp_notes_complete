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
