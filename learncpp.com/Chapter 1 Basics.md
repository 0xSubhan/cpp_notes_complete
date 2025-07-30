> *What is the C++ Standard Library?* 
> 
> A library file is a collection of precompiled code that has been “packaged up” for reuse in other programs. The C++ Standard Library is a library that ships with C++. It contains additional functionality to use in your programs.

> Comment your code liberally, and write your comments as if speaking to someone who has no idea what the code does. Don’t assume you’ll remember why you made specific choices.

>  At the library, program, or function level, use comments to describe _what.
>  Inside the library, program, or function, use comments to describe _how_.
> At the statement level, use comments to describe _why_.

> Programs are collections of instructions that manipulate data to produce a desired result.
	Computer programs (both in source code format and compiled) are technically data too, since they can be moved, processed, and stored. However, in the context of a computer program, we typically use the term “code” to mean the program itself, and “data” to mean the information that the program works with to produce a result.

> When we run the program, the operating system loads the program into Ram. Any Data that is hardcoded into the program itself like `std::cout<<Hello World;` is loaded at this point.
> The OS also reserves some additional Ram for the program to use while it is running. Common use of this memory are to store values entered by the user, to store data read in from a file or network, or to store values calculated while program is running so they can be used again.
> You can think of Ram as a series of numbered boxes that can be used to store data while the program is running.
> In some older programming languages (like Applesoft BASIC), you could directly access these boxes (e.g. you could write a statement to “go get the value stored in membox number 7532”).
> ![[memviz1.webp]]

> In C++, direct memory access is discouraged. Instead, we access memory indirectly through an object. An object represents a region of storage(typically ram or a cpu register) that can hold a value. 

```cpp
int x = 42;
```
> **`x` is an object** in C++. It's an abstraction provided by the language to represent a specific region of memory (a RAM address) where the value `42` is stored.
> Its like `x` is a nickname and its real name is its ram address.
> How the compiler and operating system work to assign memory to objects is beyond the scope of this lesson. But the key point here is that rather than say “go get the value stored in mailbox number 7532”, we can say, “go get the value stored by this object” and let the compiler figure out where and how to retrieve the value. This means we can focus on using objects to store and retrieve values, and not have to worry about where in memory those objects are actually being placed.

### Objects in context of C++

> An **object** is a region of memory that is defined by a **data type** (class, struct, int, float, etc.) and is capable of holding a **value**.
> The definition **excludes functions** because functions do not occupy memory to hold a value like variables or objects do. Instead, functions are blocks of executable code.

> In other programing languages like python or javascript, functions can be treated as first-class objects. Which means they can store data.

### Why Functions Are Excluded in C++

> *Functions Do Not Hold Valies* : An object is defined as a region of memory that stores a value while functions don't store values, they are executable intructions.
> *Functions Are Code, Not Data*: Functions exist in the program's **code segment** in memory, not in the **data segment** where objects reside.

### About Segments

 > When a program is loaded into memory, it is divided into several segments, each with a specific purpose. The key segments are:
1. **Code Segment**:
    
    - Also known as the **text segment**.
    - This segment contains the machine code (compiled instructions) of the program.
    - **Functions reside here**, as they are compiled into executable instructions.
    - The code segment is **read-only** to prevent accidental modifications of instructions during execution.
2. **Data Segment**:
    
    - This is where **global variables**, **static variables**, and **constant data** (e.g., string literals) are stored.
    - It is further divided into:
        - **Initialized Data Segment**: Stores global and static variables that are explicitly initialized.
        - **Uninitialized Data Segment (BSS)**: Stores global and static variables that are not explicitly initialized.
    - **Objects (variables)** reside here if they have global or static scope.
3. **Stack Segment**:
    
    - This is where **local variables** (declared inside functions) and **function call information** (like return addresses) are stored.
    - The stack grows and shrinks as functions are called and return.
4. **Heap Segment**:
    
    - This is where **dynamically allocated memory** (e.g., memory allocated using `new` or `malloc`) is stored.
    - Objects created at runtime via dynamic allocation reside here.
#### lets take Example to understand where function Reside:

> Functions are **blocks of executable instructions** that the CPU reads and executes.

```cpp
int add(int a, int b) {
    return a + b;
}

```

- The function `add` is compiled into machine code intructions.
- These instructions are stored in the code segment of memory.
	**Why the Code Segment?**
	- The code segment is dedicated to **storing instructions** because:
	    - It is **read-only**, which ensures that the program logic isn’t accidentally modified during execution.
	    - It allows for efficient execution of instructions.

>- Functions live in the **code segment** because they are executable instructions.
> - Objects (variables) live in the **data, stack, or heap segments**, depending on their type and scope.
> - This separation ensures both safety and efficiency in program execution.


### Variable Defination

> A definition statement can be used to tell the compiler that we want to use a variable in our program.

> [About Variable Defination](https://www.learncpp.com/cpp-tutorial/introduction-to-objects-and-variables/#:~:text=In%20order%20to,0%3B%0A%7D)

```cpp
int main()
{
    int x; // definition of variable x

    return 0;
}
```

> At **runtime** (when the program is loaded into memory and run), each object is given an actual storage location (such as RAM, or a CPU register) that it can use to store values. The process of reserving storage for an object’s use is called **allocation**. Once allocation has occurred, the object has been created and can be used.
> For the sake of example, let’s say that variable `x` is instantiated at memory location 140. Whenever the program uses variable `x`, it will access the value in memory location 140.

> One more key point, when we define the variable x at let say location address 140 in ram so when we give its instance to function as an argument then it will use the same address at 140 and not create new variable.

### Difference Between Variables and Objects

> A variable of a primitive type (e.g., `int`, `float`, `char`) is often called a variable, but technically it is also an object because it occupies memory and holds a value.

```cpp
int x = 10;  // 'x' is a variable and also an object.

```

> When you use a class, struct, or another user-defined type, the term **object** is more commonly used.

```cpp
MyClass obj;  // 'obj' is an object of type MyClass.

```

> **All Variables Are Objects, But Not All Objects Are Variables**:
- Any variable in C++ can technically be considered an object because it represents a memory region that stores a value.
- However, not all objects are variables. For instance:
    - A **temporary object** created during expression evaluation is an object, but it doesn't have a variable name.
    - Example:
	```cpp
	MyClass();  // Creates a temporary unnamed object of type MyClass.

```

### Summary for difference between objects and variables
- A **variable** is a named region of memory used to store values.
- An **object** is any instance of a type that occupies memory and holds data.
- In C++, all variables are technically objects, but the term **object** is more commonly used to refer to instances of user-defined types like classes and structs.

### Data Types

> The data type of an object must be known at compile-time (so the compiler knows how much memory that object requires).

> So i was having a litle confusion here about memory address, here is the problem: I was confused that when after printing the memory address of a variable it was giving me different address for same variable so the reason for that was following: 
>  Modern operating systems (like Linux, Windows, and macOS) use a security feature called **Address Space Layout Randomization (ASLR)**.
>  ASLR randomizes the memory layout of a program's process each time it is executed.
>  This includes the addresses of variables, functions, and the stack.
>  So after every time my program run it changes the address.

> *Default Initialization* : When no initializer is provided (such as for variable `a` above), this is called **default-initialization**. In many cases, default-initialization performs no initialization, and leaves the variable with an indeterminate value (a value that is not predictable, sometimes called a “garbage value”).


### List-initialization disallows narrowing conversions

> One of the primary benefits of list-initialization for new C++ programmers is that “narrowing conversions” are disallowed. This means that if you try to list-initialize a variable using a value that the variable can not safely hold, the compiler is required to produce a diagnostic (compilation error or warning) to notify you. For example:


```cpp
int main()
{
    // An integer can only hold non-fractional values.
    // Initializing an int with fractional value 4.5 requires the compiler to convert 4.5 to a value an int can hold.
    // Such a conversion is a narrowing conversion, since the fractional part of the value will be lost.

    int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion

    int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
    int w3 (4.5);   // compiles: w3 direct-initialized to value 4

    return 0;
}
```

> List-initialization (including value-initialization) is generally preferred over the other initialization forms because it works in most cases (and is therefore most consistent), it disallows narrowing conversions (which we normally don’t want), and it supports initialization with a list of values (something we’ll cover in a future lesson).

> Bjarne Stroustrup (creator of C++) and Herb Sutter (C++ expert) also recommend [using list-initialization](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-list) to initialize your variables.

> Use `int x{2};` unless you have a specific reason to use `int x = {2};` (e.g., aligning with an older coding style). It's more concise, aligns with modern C++ best practices, and avoids any unnecessary verbosity.

> So there is another topic, using of variable, if we initialize a variable and don't use it in our code then it will produce warning and if i have turned on compiler option: treat warning as error then compiler will produce error so what we can do is just comment out the unused variable but what if there are 50+ unused variable then we use `[[maybe_unused]]` attribute: 

```cpp
#include <iostream>

int main()
{
    [[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused
    [[maybe_unused]] double gravity { 9.8 }; // Don't complain if gravity is unused
    [[maybe_unused]] double phi { 1.61803 }; // Don't complain if phi is unused

    std::cout << pi << '\n';
    std::cout << phi << '\n';

    // The compiler will no longer warn about gravity not being used

    return 0;
}
```
> To address such cases, C++17 introduced the `[[maybe_unused]]` attribute, which allows us to tell the compiler that we’re okay with a variable being unused. The compiler will not generate unused variable warnings for such variables.
> Additionally, the compiler will likely optimize these variables out of the program, so they have no performance impact.
> 

#### What are default-initialization and value-initialization? What is the behavior of each? Which should you prefer?

> Default-initialization is when a variable initialization has no initializer (e.g. `int x;`). In most cases, the variable is left with an indeterminate value.
> 
> Value-initialization is when a variable initialization has an empty brace initializer (e.g. `int x{};`). In most cases this will perform zero-initialization.
> 
> You should prefer value-initialization, as it initializes the variable to a consistent value.

### `std::cout` Buffered!!!

> *`std::cout` is buffered*: Statements in our program request that output be sent to the console. However, that output is typically not sent to the console immediately. Instead, the requested output “gets in line”, and is stored in a region of memory set aside to collect such requests (called a **buffer**). Periodically, the buffer is **flushed**, meaning all of the data collected in the buffer is transferred to its destination (in this case, the console).
> 
> Analogy for this:
>- Output (data) is collected in the buffer (toilet bowl).
>- Flushing transfers the collected output to its final destination.
>- If flushing doesn’t occur (due to a crash or pause), the collected output remains "unprocessed."
>
>This also means that if your program crashes, aborts, or is paused (e.g. for debugging purposes) before the buffer is flushed, any output still waiting in the buffer will not be displayed. 

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world"; // Stored in the buffer
    // Program crashes or pauses here — "Hello, world" may not be displayed
    return 0;
}

```
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world" << std::endl; // Flushed immediately
    return 0;
}

```
> `std::endl` ,this process is called unbuffered output and there is a downfall for this:
> The opposite of buffered output is unbuffered output. With unbuffered output, each individual output request is sent directly to the output device.
>Writing data to a buffer is typically fast, whereas transferring a batch of data to an output device is comparatively slow. Buffering can significantly increase performance by batching multiple output requests together to minimize the number of times output has to be sent to the output device.

> It is better to not use unbuffered output due to performance issues and speed issue unless it is necessary!!!

### **Key Insight: FIFO Principle**
> - The output buffer follows the **FIFO (First In, First Out)** principle:
    - **First In:** Data is added to the buffer in the order of `std::cout` calls.
    - **First Out:** Data is flushed from the buffer in the same order, ensuring consistent output order.

```cpp
std::cout << "Hello";   // Buffer: ["Hello"]
std::cout << " World";  // Buffer: ["Hello", " World"]
std::cout.flush();      // Console Output: "Hello World" (FIFO order)
```

### Replacement of `std::endl`

> To output a newline without flushing the output buffer, we use `\n` (inside either single or double quotes), which is a special symbol that the compiler interprets as a newline character. `\n` moves the cursor to the next line of the console without causing a flush, so it will typically perform better. `\n` is also more concise to type and can be embedded into existing double-quoted text.
> 
> Prefer `\n` over `std::endl` when outputting text to the console.

### `std::cin` Buffered!!!

>- The individual characters you enter as input are added to the end of an input buffer (inside `std::cin`). The enter key (pressed to submit the data) is also stored as a `'\n'` character.
>- The extraction operator ‘>>’ removes characters from the front of the input buffer and converts them into a value that is assigned (via copy-assignment) to the associated variable. This variable can then be used in subsequent statements.

```cpp
int x, y;
cin >> x;  // Reads first available integer
cin >> y;  // Reads next available integer
```

```cpp
#include <iostream>  // for std::cout and std::cin

int main()
{
    std::cout << "Enter two numbers: ";

    int x{};
    std::cin >> x;

    int y{};
    std::cin >> y;

    std::cout << "You entered " << x << " and " << y << '\n';

    return 0;
}
```

> **Run-1:**     When `std::cin >> x;` is encountered, the program will wait for input. Enter the value `4`. The input `4\n` goes into the input buffer, and the value `4` is extracted to variable `x`.
When `std::cin >> y;` is encountered, the program will again wait for input. Enter the value `5`. The input `5\n` goes into the input buffer, and the value `5` is extracted to variable `y`. Finally, the program will print `You entered 4 and 5`.

>**Run-2:** When `std::cin >> x` is encountered, the program will wait for input. Enter `4 5`. The input `4 5\n` goes into the input buffer, but only the `4` is extracted to variable `x` (extraction stops at the space).
When `std::cin >> y` is encountered, the program will _not_ wait for input. Instead, the `5` that is still in the input buffer is extracted to variable `y`. The program then prints `You entered 4 and 5`.

### When Does The Buffer Flush in the case of Cin?

> Unlike `std::cout`, `std::cin` does not "flush" in the same way. Instead:
> 
>- The buffer **waits** until the user presses **Enter** (newline `\n` is added).
  >  
>- Extraction operations (`>>`) read data **sequentially** from the buffer.
  >  
> Unread data **stays in the buffer** until consumed.

```cpp
int num;
char ch;
cin >> num;   // Reads an integer (e.g., "42")
cin >> ch;    // Reads the next non-whitespace character
```
- If input is: `42 A`:
    
    - `num = 42` (first extraction).
        
    - `ch = 'A'` (next extraction).
        
- If input is: `42A`:
    
    - `num = 42` (reads until non-digit).
        
    - `ch = 'A'` (next character).


# Uninitialized variables and undefined behavior

### Uninitialized Variable
>An uninitialized variable is a variable that has not been given a value by the program (generally through initialization or assignment). Using the value stored in an uninitialized variable will result in undefined behavior.

### Undefined Behavior
>Undefined behavior is the result of executing code whose behavior is not well defined by the language. The result can be almost anything, including something that behaves correctly.

### Implementation-Defined Behavior
>A specific compiler and the associated standard library it comes with are called an **implementation** (as these are what actually implements the C++ language). In some cases, the C++ language standard allows the implementation to determine how some aspect of the language will behave, so that the compiler can choose a behavior that is efficient for a given platform. Behavior that is defined by the implementation is called **implementation-defined behavior**. Implementation-defined behavior must be documented and consistent for a given implementation.
>- Implementation-defined behaviour are documented behaviour that each compiler may adopt. the result are known but may vary from system to system

```cpp
#include <iostream>

int main()
{
	std::cout << sizeof(int) << '\n'; // print how many bytes of memory an int value takes

	return 0;
}
```
>On most platforms, this will produce `4`, but on others it may produce `2`.

### Literals
>What are ‘”Hello world!”‘ and ‘5’? They are literals. A **literal** (also known as a **literal constant**) is a fixed value that has been inserted directly into the source code.
>Literals and variables both have a value (and a type). Unlike a variable (whose value can be set and changed through initialization and assignment respectively), the value of a literal is fixed and cannot be changed. The literal `5` always has value `5`. This is why literals are called constants.

### Operator's arity
>The number of operands that an operator takes as input is called the operator’s **arity**. Few people know what this word means, so don’t drop it in a conversation and expect anybody to have any idea what you’re talking about. Operators in C++ come in four different arities:
>1: **Unary** operators act on one operand. An example of a unary operator is the `-` operator. For example, given `-5`, `operator-` takes literal operand `5` and flips its sign to produce new output value `-5`.
>2:**Binary** operators act on two operands (often called _left_ and _right_, as the left operand appears on the left side of the operator, and the right operand appears on the right side of the operator). An example of a binary operator is the `+` operator. For example, given `3 + 4`, `operator+` takes the left operand `3` and the right operand `4` and applies mathematical addition to produce new output value `7`. The insertion (`<<`) and extraction (`>>`) operators are binary operators, taking `std::cout` or `std::cin` on the left side, and the value to output or variable to input to on the right side.
>3:**Ternary** operators act on three operands.
>4:**Nullary** operators act on zero operands. There is also only one of these in C++ (the throw operator), which we’ll also cover later.

### Return Values and side effects
>Some operators have additional behaviors. An operator (or function) that has some observable effect beyond producing a return value is said to have a **side effect**. For example, `x = 5` has the side effect of assigning value `5` to variable `x`. The changed value of `x` is observable (e.g. by printing the value of `x`) even after the operator has finished executing. `std::cout << 5` has the side effect of printing `5` to the console. We can observe the fact that `5` has been printed to the console even after `std::cout << 5` has finished executing.
>In C++, the term “side effect” has a different meaning: it is an observable effect of an operator or function beyond producing a return value.

> ***Tip*** : New programmers often try to write an entire program all at once, and then get overwhelmed when it produces a lot of errors. A better strategy is to add one piece at a time, make sure it compiles, and test it. Then when you’re sure it’s working, move on to the next piece.