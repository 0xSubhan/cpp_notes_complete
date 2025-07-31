
### Testing Your Code

>Just because your program worked for one set of inputs doesn’t mean it’s going to work correctly in all cases.

>[!tip]
>**Software testing** (also called **software validation**) is the process of determining whether or not the software actually works as expected.

### Test your programs in small pieces

>Our Approch should be:
>Build (or buy) and test each car component individually before installing it. Once the component has been proven to work, integrate it into the car and retest it to make sure the integration worked. At the end, test the whole car, as a final validation that everything seems good.

>Testing a small part of your code in isolation to ensure that “unit” of code is correct is called **unit testing**. Each **unit test** is designed to ensure that a particular behavior of the unit is correct.

>[!Best Practice]
>Write your program in small, well defined units (functions or classes), compile often, and test your code as you go.

---
### Informal testing

>One way you can test code is to do informal testing as you write the program. After writing a unit of code (a function, a class, or some other discrete “package” of code), you can write some code to test the unit that was just added, and then erase the test once the test passes. As an example, for the following isLowerVowel() function, you might write the following code:

```cpp
#include <iostream>

// We want to test the following function
// For simplicity, we'll ignore that 'y' is sometimes counted as a vowel
bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

int main()
{
    // So here's our temporary tests to validate it works
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0

    return 0;
}
```

---
### Preserving your tests

>[!tip]
>Instead of removing our test code, we can move it into test-function so if in future we add some new capabilities then we can re-test it.

```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Not called from anywhere right now
// But here if you want to retest things later
void testVowel()
{
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0
}

int main()
{
    return 0;
}
```

---
### Automating your test functions

>We can do better by writing a test function that contains both the tests AND the expected answers and compares them so we don’t have to.

```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// returns the number of the test that failed, or 0 if all tests passed
int testVowel()
{
    if (!isLowerVowel('a')) return 1;
    if (isLowerVowel('q')) return 2;

    return 0;
}

int main()
{
    int result { testVowel() };
    if (result != 0)
        std::cout << "testVowel() test " << result << " failed.\n";
    else
        std::cout << "testVowel() tests passed.\n";

    return 0;
}
```

if **both tests fail**, the function will return **as soon as the first failure occurs**, and **the second one will never be reached**.

That **doesn't break the logic**, but it **does limit the diagnostic value**.

You **won’t know** if multiple test cases failed — only the first failure gets reported.

>A better method is to use `assert`, which will cause the program to abort with an error message if any test fails. We don’t have to create and handle test case numbers this way.
```cpp
#include <cassert> // for assert
#include <cstdlib> // for std::abort
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Program will halt on any failed test case
int testVowel()
{
#ifdef NDEBUG
    // If NDEBUG is defined, asserts are compiled out.
    // Since this function requires asserts to not be compiled out, we'll terminate the program if this function is called when NDEBUG is defined.
    std::cerr << "Tests run with NDEBUG defined (asserts compiled out)";
    std::abort();
#endif

    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(isLowerVowel('i'));
    assert(isLowerVowel('o'));
    assert(isLowerVowel('u'));
    assert(!isLowerVowel('b'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('y'));
    assert(!isLowerVowel('z'));

    return 0;
}

int main()
{
    testVowel();

    // If we reached here, all tests must have passed
    std::cout << "All tests succeeded\n";

    return 0;
}
```

### Unit testing frameworks

>Because writing functions to exercise other functions is so common and useful, there are entire frameworks (called **unit testing frameworks**) that are designed to help simplify the process of writing, maintaining, and executing unit tests. Since these involve third party software, we won’t cover them here, but you should be aware they exist.

### Integration testing

>Once each of your units has been tested in isolation, they can be integrated into your program and retested to make sure they were integrated properly. This is called an **integration test**. Integration testing tends to be more complicated -- for now, running your program a few times and spot checking the behavior of the integrated unit will suffice.

---
### Code Coverage

>The term **code coverage** is used to describe how much of the source code of a program is executed while testing.

---
### Statement coverage

>The term **statement coverage** refers to the percentage of statements in your code that have been exercised by your testing routines.

```cpp
int foo(int x, int y)
{
    int z{ y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```

Calling this function as `foo(1, 0)` will give you complete statement coverage for this function, as every statement in the function will execute.

>While aiming for 100% statement coverage is good, it’s often not enough to ensure correctness.

---
### Branch coverage

>**Branch coverage** refers to the percentage of branches that have been executed, each possible branch counted separately. An `if statement` has two branches -- a branch that executes when the condition is `true`, and a branch that executes when the condition is `false` (even if there is no corresponding `else statement` to execute). A switch statement can have many branches.

```cpp
int foo(int x, int y)
{
    int z{ y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```

>[!best practice]
>Aim for 100% branch coverage of your code.

---
### Loop Coverage

>**Loop coverage** (informally called **the 0, 1, 2 test**) says that if you have a loop in your code, you should ensure it works properly when it iterates 0 times, 1 time, and 2 times. If it works correctly for the 2-iteration case, it should work correctly for all iterations greater than 2. These three tests therefore cover all possibilities (since a loop can’t execute a negative number of times).

>To test the loop within this function properly, you should call it three times: `spam(0)` to test the zero-iteration case, `spam(1)` to test the one-iteration case, and `spam(2)` to test the two-iteration case. If `spam(2)` works, then `spam(n)` should work, where `n > 2`.

>[!Best Practice]
>Use the `0, 1, 2 test` to ensure your loops work correctly with different number of iterations.

---
### Testing different categories of input

>Test different categories of input values to make sure your unit handles them properly.

---
### Common Semantic errors in c++

>Semantic errors can cause most of the same symptoms of `undefined behavior`, such as causing the program to produce the wrong results, causing erratic behavior, corrupting program data, causing the program to crash -- or they may not have any impact at all.

>When writing programs, it is almost inevitable that you will make semantic errors. You will probably notice some of these just by using the program: for example, if you were writing a maze game, and your character was able to walk through walls.

---
### Conditional logic errors

>One of the most common types of semantic errors is a conditional logic error. A **conditional logic error** occurs when the programmer incorrectly codes the logic of a conditional statement or loop condition.

---
>unintentional Infinite loop is also a semantic error.

---
### Off-by-one errors

>An **off-by-one** error is an error that occurs when a loop executes one too many or one too few times.

---
### Incorrect operator precedence

```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 7 };

    if (!x > y) // oops: operator precedence issue
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    return 0;
}
```

>Because `logical NOT` has higher precedence than `operator>`, the conditional evaluates as if it was written `(!x) > y`, which isn’t what the programmer intended.

---
### Precision issues with floating point types

>The following floating point variable doesn’t have enough precision to store the entire number:

```cpp
#include <iostream>

int main()
{
    float f{ 0.123456789f };
    std::cout << f << '\n';

    return 0;
}
```
Because of this lack of precision, the number is rounded slightly:

0.123457

In lesson [6.7 -- Relational operators and floating point comparisons](https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/), we talked about how using `operator==` and `operator!=` can be problematic with floating point numbers due to small rounding errors (as well as what to do about it). Here’s an example:

```cpp
#include <iostream>

int main()
{
    double d{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should sum to 1.0

    if (d == 1.0)
        std::cout << "equal\n";
    else
        std::cout << "not equal\n";

    return 0;
}
```
not equal

>The more arithmetic you do with a floating point number, the more it will accumulate small rounding errors.

---
### Accidental null statements

```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y');     // accidental null statement here
        blowUpWorld(); // so this will always execute since it's not part of the if-statement

    return 0;
}
```
---
### Not using a compound statement when one is required

---
### Using assignment instead of equality inside a conditional

---
### Forgetting to use the function call operator when calling a function

```cpp
#include <iostream>

int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue << '\n';

    return 0;
}
```

Instead of using `getValue()` (which would call the function and produce an `int` return value), we’ve used `getValue` without the function call operator. In many cases, this will result in a value that gets converted to `bool` value `true`).

>[!important]
>Using a function’s name without calling it generally yields a function pointer holding the address of the function. Such a function pointer will implicitly convert to a `bool` value. And since this pointer should never have address `0`, that `bool` value will always be `true`.

### Detecting and handling errors

>we’ll talk about error handling strategies (what to do when things go wrong) inside a function. In the subsequent lessons, we’ll talk about validating user input, and then introduce a useful tool to help document and validate assumptions.

---
### Handling errors in functions

Functions may fail for any number of reasons -- the caller may have passed in an argument with an invalid value, or something may fail within the body of the function. For example, a function that opens a file for reading might fail if the file cannot be found.

When this happens, you have quite a few options at your disposal. There is no best way to handle an error -- it really depends on the nature of the problem and whether the problem can be fixed or not.

There are 4 general strategies that can be used:

- Handle the error within the function
- Pass the error back to the caller to deal with
- Halt the program
- Throw an exception

#### Handling the error within the function

If possible, the best strategy is to recover from the error in the same function in which the error occurred, so that the error can be contained and corrected without impacting any code outside the function. There are two options here: retry until successful, or cancel the operation being executed.

If the error has occurred due to something outside of the program’s control, the program can retry until success is achieved. For example, if the program requires an internet connection, and the user has lost their connection, the program may be able to display a warning and then use a loop to periodically recheck for internet connectivity. Alternatively, if the user has entered invalid input, the program can ask the user to try again, and loop until the user is successful at entering valid input.

### Passing errors back to the caller

>We can do something like if we encounter an error we can show error message and return false to the caller from which we can handle the error.

>But what if function has return type other than bool then we can use **sentinel value**.

```cpp
// The reciprocal of x is 1/x
double reciprocal(double x)
{
    return 1.0 / x;
}
```

The reciprocal of some number `x` is defined as `1/x`, and a number multiplied by its reciprocal equals 1.

However, what happens if the user calls this function as `reciprocal(0.0)`? We get a `divide by zero` error and a program crash, so clearly we should protect against this case. But this function must return a double value, so what value should we return? It turns out that this function will never produce `0.0` as a legitimate result, so we can return `0.0` to indicate an error case.

```cpp
// The reciprocal of x is 1/x, returns 0.0 if x=0
constexpr double error_no_reciprocal { 0.0 }; // could also be placed in namespace

double reciprocal(double x)
{
    if (x == 0.0)
       return error_no_reciprocal;

    return 1.0 / x;
}
```

>A **sentinel value** is a value that has some special meaning in the context of a function or algorithm. In our `reciprocal()` function above, `0.0` is a sentinel value indicating that the function failed. The caller can test the return value to see if it matches the sentinel value -- if so, then the caller knows the function failed. While functions often return the sentinel value directly, returning a constant that describes the sentinel value can add additional readability.

### Fatal errors

>If the error is so bad that the program can not continue to operate properly, this is called a **non-recoverable** error (also called a **fatal error**). In such cases, the best thing to do is terminate the program. If your code is in `main()` or a function called directly from `main()`, the best thing to do is let `main()` return a non-zero status code. However, if you’re deep in some nested subfunction, it may not be convenient or possible to propagate the error all the way back to `main()`. In such a case, a `halt statement` (such as `std::exit()`) can be used.

```cpp
double doIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: Could not divide by zero\n";
        std::exit(1);
    }
    return x / y;
}
```

### Exceptions

Because returning an error from a function back to the caller is complicated (and the many different ways to do so leads to inconsistency, and inconsistency leads to mistakes), C++ offers an entirely separate way to pass errors back to the caller: `exceptions`.

The basic idea is that when an error occurs, an exception is “thrown”. If the current function does not “catch” the error, the caller of the function has a chance to catch the error. If the caller does not catch the error, the caller’s caller has a chance to catch the error. The error progressively moves up the call stack until it is either caught and handled (at which point execution continues normally), or until main() fails to handle the error (at which point the program is terminated with an exception error).

### [When to use `std::cout` vs `std::cerr` vs logging](https://www.learncpp.com/cpp-tutorial/detecting-and-handling-errors/#:~:text=In%20lesson%203.4,error%20messages%2C%20etc%E2%80%A6)

---
### std::cin and handling invalid input

>A program that handles error cases well is said to be **robust**.

### Error case 1: Extraction succeeds but input is meaningless

```cpp
char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    } // and try again
}
```

>As you can see, we’re using a while loop to continuously loop until the user provides valid input. If they don’t, we ask them to try again until they either give us valid input, shutdown the program, or destroy their computer.

---
### Error case 2: Extraction succeeds but with extraneous input

[Read](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/#:~:text=with%20extraneous%20input-,Consider%20the%20following%20execution%20of%20the%20above%20program%3A,haven%E2%80%99t%20extracted%20all%20the%20input%2C%20meaning%20there%20is%20still%20unextracted%20input.,-Error%20case%203)

we use following to clear the buffer:

```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

>To ignore all characters up to the next ‘\n’, we can pass `std::numeric_limits<std::streamsize>::max()` to `>std::cin.ignore()`. `std::numeric_limits<std::streamsize>::max()` returns the largest value that can be stored in a variable of type `std::streamsize`. Passing this value to `std::cin.ignore()` causes it to disable the count check.

This will ignore everything up to and including the next \n character...
#### **--> Tip**

In certain cases, it may be better to treat extraneous input as a failure case (rather than just ignoring it). We can then ask the user to re-enter their input.

Here’s a variation of `getDouble()` that asks the user to re-enter their input if there is any extraneous input entered:

```cpp
// returns true if std::cin has unextracted input on the current line, false otherwise
bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        // NOTE: YOU SHOULD CHECK FOR A FAILED EXTRACTION HERE (see section below)

        // If there is extraneous input, treat as failure case
        if (hasUnextractedInput())
        {
            ignoreLine(); // remove extraneous input
            continue;
        }

        return x;
    }
}
```

The above snippet makes use of two functions we haven’t seen before:

- The `std::cin.eof()` function returns `true` if the last input operation (in this case the extraction to `x`) reached the end of the input stream.
- The `std::cin.peek()` function allows us to peek at the next character in the input stream without extracting it.

Here’s how this function works. After the user’s input has been extracted to `x`, there may or may not be additional (unextracted) characters left in `std::cin`.

First, we call `std::cin.eof()` to see if the extraction to `x` reached the end of the input stream. If so, then we know all characters were extracted, which is a success case.

Otherwise, there must be additional characters still inside `std::cin` waiting to be extracted. In that case, we call `std::cin.peek()` to peek at the next character waiting to be extracted without actually extracting it. If that next character is a `'\n'`, that means we’ve already extracted all of the characters on this line of input to `x`. This is also a success case.

However, if the next character is something other than `'\n'`, then the user must have entered extraneous input that wasn’t extracted to `x`. That’s our failure case. We clear out all of that extraneous input, and `continue` back to the top of the loop to try again.

If you’re having trouble deciphering how the boolean expression in `hasUnextractedInput()` evaluates, that’s not surprising -- boolean expressions with negations can be difficult to understand. In such cases, using de Morgan’s law can help. An equivalent statement is `return !(std::cin.eof() || std::cin.peek() == '\n');`. This makes it clearer that we are testing for EOF or a newline. If either are true, then we’ve extracted all the input. We then apply `operator!` to tell us whether we haven’t extracted all the input, meaning there is still unextracted input.

---
### Error case 3: Extraction fails

[Read](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/#:~:text=3%3A%20Extraction%20fails-,Extraction%20fails%20when%20no%20input%20can%20be%20extracted%20to%20the%20specified,COPY,-Checking%20for%20EOF)

```cpp
if (std::cin.fail()) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```

Because `std::cin` has a Boolean conversion indicating whether the last input succeeded, it’s more idiomatic to write the above as following:

```cpp
if (!std::cin) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```

>[!Key Insight]
>Once an extraction has failed, future requests for input extraction (including calls to `ignore()`) will silently fail until the `clear()` function is called. Thus, after detecting a failed extraction, calling `clear()` is usually the first thing you should do.

```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        // Our extraction succeeded
        ignoreLine(); // Ignore any additional input on this line
        return x;     // Return the value we extracted
    }
}
```

It is fine to call `clear()` even when extraction hasn’t failed -- it won’t do anything. In cases where we are going to call `ignoreLine()` regardless of whether we succeeded or failed, we can essentially combine the two cases:

```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        bool success { std::cin }; // Remember whether we had a successful extraction
        std::cin.clear();          // Put us back in 'normal' operation mode (in case we failed)
        ignoreLine();              // Ignore any additional input on this line (regardless)

        if (success)               // If we actually extracted a value
            return x;              // Return it (otherwise, we go back to top of loop)
    }
}
```

---
### 🔍 **What is EOF?**

- **EOF stands for "End Of File"**.
    
- It’s a **special error state**, not a character.
    
- EOF means **“No more data is available for input”**.
    
- It's commonly encountered when reading from files, but it can also happen with `std::cin`.
    

### 📂 **EOF in File Input**

- When reading a file:
    
    - You keep reading line by line.
        
    - When the file ends, an **EOF error is generated**.
        
    - You can detect it and move on (like closing the file).
        

### ⌨️ **EOF in `std::cin` (User Input)**

- Normally, `std::cin` **waits** for the user to input something.
    
- But if the user types a **keyboard EOF command**:
    
    - **Linux/macOS:** Press `Ctrl + D`
        
    - **Windows:** Press `Ctrl + Z`, then `Enter`
        
- Then `std::cin` enters the **EOF error state**.
    

### 🧠 **Key Insight**

- EOF isn’t a literal character—it’s a **state**.
    
- The OS **interprets a special key combo** as "user wants to end input".
    

### 🧪 **Typical Behavior**

1. **If EOF comes _after_ other characters:**
    
    - The characters _before_ EOF are processed normally.
        
    - EOF character is ignored.
        
2. **If EOF is the _first_ thing entered:**
    
    - `std::cin` enters the **EOF error state**.
        
    - Input stream may even get **disconnected** (especially in terminal environments).
        
    - **Calling `.clear()` won't help**, because trying to get input again just causes another EOF error.
        

### 🔁 **Issue in Loops**

- In `while(true)` or `do-while` loops for input:
    
    - If EOF happens, the loop keeps asking for input.
        
    - But since stream is disconnected, it **keeps failing**, causing an **infinite loop**.
        

### ✅ **Best Practice: Detect and Exit**

When EOF is detected from user input:

```cpp
`if (std::cin.eof()) {     std::exit(0); // Gracefully terminate the program }`
```

### 🔧 **Reusable Utility Functions**

#### 1. **ignoreLine()**

```cpp
`std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');`
```

- **Discards everything** left in the input buffer until a newline.
    
- Useful to clean up bad input (like extra characters).
    

#### 2. **clearFailedExtraction()**

```cpp
`bool clearFailedExtraction() {     if (!std::cin)     {         if (std::cin.eof())         {             std::exit(0);         }          std::cin.clear();     // Clear fail state         ignoreLine();         // Clean input buffer         return true;     }      return false; }`
```

- Checks whether input failed.
    
- If it’s an EOF: exits.
    
- Otherwise: clears the error and flushes the input buffer.
    
- Useful to **reuse wherever input extraction is done**, like this:
    

```cpp
`int x; std::cin >> x; if (clearFailedExtraction()) {     // retry input or handle error }`
```

>[!tip]
>- `std::cin.eof()` returns `true` if the **EOF has been reached**.
>-  This means: there is **no more input**, and the stream is at the end.

```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the user entered an EOF
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```
---
### Error case 4: Extraction succeeds but the user overflows a numeric value

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int16_t x{}; // x is 16 bits, holds from -32768 to 32767
    std::cout << "Enter a number between -32768 and 32767: ";
    std::cin >> x;

    std::int16_t y{}; // y is 16 bits, holds from -32768 to 32767
    std::cout << "Enter another number between -32768 and 32767: ";
    std::cin >> y;

    std::cout << "The sum is: " << x + y << '\n';
    return 0;
}
```

What happens if the user enters a number that is too large (e.g. 40000)?

Enter a number between -32768 and 32767: 40000
Enter another number between -32768 and 32767: The sum is: 32767

In the above case, `std::cin` goes immediately into “failure mode”, but also assigns the closest in-range value to the variable. When the entered value is larger than the largest possible value for the type, the closest in-range value is the largest possible value for the type. Consequently, `x` is left with the assigned value of `32767`. Additional inputs are skipped, leaving `y` with the initialized value of `0`. We can handle this kind of error in the same way as a failed extraction.

---
### Integration of concepts

```cpp
#include <cstdlib> // for std::exit
#include <iostream>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        if (y == 0.0)
            break;

        std::cout << x / y << '\n';
        return;
    }

    std::cout << "???";  // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    // Handle division by 0
    while (operation == '/' && y == 0.0)
    {
        std::cout << "The denominator cannot be zero.  Try again.\n";
        y = getDouble();
    }

    printResult(x, operation, y);

    return 0;
}
```

--> Why if(!clearFailedExtraction())

1. `std::cin >> something` **fails** (invalid input).
    
2. `clearFailedExtraction()` is called.
    
3. Inside `clearFailedExtraction()`:
    
    - `!std::cin` is **true** (input failed).
        
    - If `std::cin.eof()` → program exits.
        
    - Else:
        
        - `std::cin.clear()` is called — fixes the stream.
            
        - `ignoreLine()` is called — flushes the leftover junk.
            
        - Then it returns `true`.
            
4. Now you have: `if (!clearFailedExtraction())`
    
    - Which becomes: `if (!true)` → `if (false)`
        
5. So the `ignoreLine()` **outside** the function does **not run**.
---
### Conclusion

As you write your programs, consider how users will misuse your program, especially around text input. For each point of text input, consider:

- Could extraction fail?
- Could the user enter more input than expected?
- Could the user enter meaningless input?
- Could the user overflow an input?

You can use if statements and boolean logic to test whether input is expected and meaningful.

The following code will clear any extraneous input:

```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

The following code will test for and fix failed extractions or overflow (and remove extraneous input):

```cpp
// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```

We can test to see if there is an unextracted input (other than a newline) as follows:

```cpp
// returns true if std::cin has unextracted input on the current line, false otherwise
bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}
```

Finally, use loops to ask the user to re-enter input if the original input was invalid.

---

```cpp
void printDivision(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    else
        std::cerr << "Error: Could not divide by zero\n";
}
```

This function does an explicit check to see if `y` is `0`, since dividing by zero is a semantic error and will cause the program to crash if executed.

In the prior lesson, we discussed a couple of ways to deal with such problems, including halting the program, or skipping the offending statements.

>Both of those options are problematic though. If a program skips statements due to an error, then it is essentially failing silently. Especially while we are writing and debugging programs, silent failures are bad, because they obscure real problems. Even if we print an error message, that error message may be lost among the other program output, and it may be non-obvious where the error message is being generated or how the conditions that triggered the error message occurred. Some functions may be called tens or hundreds of times, and if only one of those cases is generating a problem, it can be hard to know which one.

If the program terminates (via `std::exit`) then we will have lost our call stack and any debugging information that might help us isolate the problem. `std::abort` is a better option for such cases, as typically the developer will be given the option to start debugging at the point where the program aborted.

### Preconditions, invariants, and postconditions

>In programming, a **precondition** is any condition that must be true prior to the execution of some section of code (typically the body of a function). In the prior example, our check that `y != 0` is a precondition that ensures `y` has a non-zero value before dividing by `y`.

>[!tip]
>Preconditions for a function are best placed at the top of a function, using an early return to return back to the caller if the precondition isn’t met. For example:
```cpp
void printDivision(int x, int y)
{
    if (y == 0) // handle
    {
        std::cerr << "Error: Could not divide by zero\n";
        return; // bounce the user back to the caller
    }

    // We now know that y != 0
    std::cout << static_cast<double>(x) / y;
}
```

#### 🧠 **Loop Invariant (Short Note)**

- A **loop invariant** is a condition or rule that **remains true**:
    
    - **Before** the loop starts
        
    - **Before and after** **each iteration** of the loop
        
- It is used to **reason about** the correctness of loops in a program.
    
- It is **not** the condition that controls the loop.  
    The loop runs based on the **loop condition** (e.g., `i < 10`), **not** the invariant.

```cpp
int sum = 0;
for (int i = 0; i <= 5; ++i)
{
    sum += i;
}
// Sum is the invariant
```

#### 🧠 **Postcondition (Short Note)**

- A **postcondition** is a condition that **must be true after** a section of code finishes executing (e.g., after a function or loop).
    
- It helps you verify that the code **achieved what it was supposed to**.

```cpp
int square(int x)
{
    return x * x;
}
// The return value is always equal to `x²`.
```

---
### Assertions

>Using a conditional statement to detect an invalid parameter (or to validate some other kind of assumption), along with printing an error message and terminating the program, is such a common method of detecting problems that C++ provides a shortcut method for doing this.

>An **assertion** is an expression that will be true unless there is a bug in the program. If the expression evaluates to `true`, the assertion statement does nothing. If the conditional expression evaluates to `false`, an error message is displayed and the program is terminated (via `std::abort`). This error message typically contains the expression that failed as text, along with the name of the code file and the line number of the assertion. This makes it very easy to tell not only what the problem was, but where in the code the problem occurred. This can help with debugging efforts immensely.

In C++, runtime assertions are implemented via the **assert** preprocessor macro, which lives in the `<cassert>` header.

```cpp
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

  if (initialHeight <= 0.0)
  {
    // The object is already on the ground. Or buried.
    return 0.0;
  }

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

  return 0;
}
```
--> Extra: 

📐 **Formula Used**

This line is based on the physics equation:

h=12gt2h = \frac{1}{2} g t^2h=21​gt2

Where:

- hhh = height the object falls (initialHeight)
    
- ggg = gravitational acceleration (gravity, usually ~9.8 m/s²)
    
- ttt = time to fall
    

Rearranged to solve for ttt:

t=2hgt = \sqrt{\frac{2h}{g}}t=g2h​​

>When the program calls `calculateTimeUntilObjectHitsGround(100.0, -9.8)`, `assert(gravity > 0.0)` will evaluate to `false`, which will trigger the assert. That will print a message similar to this:

`dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double): Assertion 'gravity > 0.0' failed.`

---
### Making your assert statements more descriptive

Sometimes assert expressions aren’t very descriptive. Consider the following statement:

```cpp
assert(found);
```

If this assert is triggered, the assert will say:

`Assertion failed: found, file C:\\VCProjects\\Test.cpp, line 34
`
What does this even mean? Clearly `found` was `false` (since the assert triggered), but what wasn’t found? You’d have to go look at the code to determine that.

Fortunately, there’s a little trick you can use to make your assert statements more descriptive. Simply add a string literal joined by a logical AND:

```cpp
assert(found && "Car could not be found in database");
```

Here’s why this works: A string literal always evaluates to Boolean `true`. So if `found` is `false`, `false && true` is `false`. If `found` is `true`, `true && true` is `true`. Thus, logical AND-ing a string literal doesn’t impact the evaluation of the assert.

However, when the assert triggers, the string literal will be included in the assert message:

`Assertion failed: found && "Car could not be found in database", file C:\\VCProjects\\Test.cpp, line 34`

---
### Using assertions for unimplemented features

Assertions are also sometimes used to document cases that were not implemented because they were not needed at the time the programmer wrote the code:

```cpp
assert(moved && "Need to handle case where student was just moved to another classroom");
```

That way, if a developer encounters a situation where this case is needed, the code will fail with a useful error message, and the programmer can then determine how to implement that case.

>[!Important]
>Assertion only triggers when condition is false.

---
####  🛑 **Why `assert()` is NOT used in production code**

#### 🔧 1. **Assertions are for catching programmer mistakes during development**

- Assertions are designed to detect **logic errors**, **invalid assumptions**, or **impossible states**.
    
- These are **bugs** that shouldn't happen if the program is written correctly.
    
- In production, we assume (or _hope_) that these bugs have already been caught and fixed during testing.
---
### NDEBUG

>The `assert` macro comes with a small performance cost that is incurred each time the assert condition is checked. Furthermore, asserts should (ideally) never be encountered in production code (because your code should already be thoroughly tested). Consequently, most developers prefer that asserts are only active in debug builds. C++ comes with a built-in way to turn off asserts in production code: if the preprocessor macro `NDEBUG` is defined, the assert macro gets disabled.

>Most IDEs set `NDEBUG` by default as part of the project settings for release configurations. For example, in Visual Studio, the following preprocessor definitions are set at the project level: `WIN32;NDEBUG;_CONSOLE`. If you’re using Visual Studio and want your asserts to trigger in release builds, you’ll need to remove `NDEBUG` from this setting.

>[!tip]
>For testing purposes, you can enable or disable asserts within a given translation unit. To do so, place one of the following on its own line **before** any #includes: `#define NDEBUG` (to disable asserts) or `#undef NDEBUG` (to enable asserts). Make sure that you do not end the line in a semicolon.
```cpp
#define NDEBUG // disable asserts (must be placed before any #includes)
#include <cassert>
#include <iostream>

int main()
{
    assert(false); // won't trigger since asserts have been disabled in this translation unit
    std::cout << "Hello, world!\n";

    return 0;
}
```

---
### static_assert

>C++ also has another type of assert called `static_assert`. A **static_assert** is an assertion that is checked at compile-time rather than at runtime, with a failing `static_assert` causing a compile error. Unlike assert, which is declared in the `<cassert>` header, static_assert is a keyword, so no header needs to be included to use it.

A `static_assert` takes the following form:

`static_assert(condition, diagnostic_message)`

If the condition is not true, the diagnostic message is printed. Here’s an example of using static_assert to ensure types have a certain size:

```cpp
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}
```

`1>c:\consoleapplication1\main.cpp(19): error C2338: long must be 8 bytes`

>A few useful notes about `static_assert`:

- Because `static_assert` is evaluated by the compiler, the condition must be a constant expression.
- `static_assert` can be placed anywhere in the code file (even in the global namespace).
- `static_assert` is not deactivated in release builds (like normal `assert` is).
- Because the compiler does the evaluation, there is no runtime cost to a `static_assert`.

>[!Best Practice]
>Favor `static_assert` over `assert()` whenever possible. 

---
### Asserts vs error handling

Assertions and error handling are similar enough that their purposes can be confused, so let’s clarify.

Assertions are used to detect _programming errors_ during development by documenting assumptions about things that should never happen. And if they do happen, it’s the fault of the programmer. Assertions do not allow recovery from errors (after all, if something should never happen, there’s no need to recover from it). Because asserts are typically compiled-out in release builds, you can put a lot of them in without worrying about performance, so there’s little reason not to use them liberally.

Error handling is used when we need to gracefully handle cases that could happen (however rarely) in a release build. These may either be recoverable issues (where the program can keep running), or unrecoverable issues (where the program has to shut down, but we can at least show a nice error message and ensure everything is cleaned up properly). Error detection and handling has both a runtime performance cost and a development time cost.

In some cases, it’s less clear what we should do. Consider a function like this:

```cpp
double getInverse(double x)
{
    return 1.0 / x;
}
```

If `x` is `0.0`, this function will misbehave, and we need to guard against that. Should we use an assert or error handling? The best answer may be “both”.

During debugging, if this function is called when `x` is `0.0`, that indicates a bug in our code somewhere, and we want to know that immediately. So an assert is definitely appropriate.

However, this could also reasonably happen in a release build (e.g. along an obscure path we didn’t test). If the assert is compiled out and we don’t have error handling, then this function will return something unexpected and misbehave. In such a case, it’s probably better to detect that and handle the case.

Our resulting function might look like this:

```cpp
double getInverse(double x)
{
    assert(x != 0.0);
    if (x == 0.0)
       // handle error somehow (e.g. throw an exception)

    return 1.0 / x;
}
```
#### --> Tip

Given this, we suggest the following:

- Use assertions to detect programming errors, incorrect assumptions, or conditions that should never occur in correct code. It is the programmer’s responsibility to fix these, so we want to catch them early.
- Use error handling for issues that we expect will occur during the normal operation of your program.
- Use both in cases where something isn’t supposed to occur, but we want to fail gracefully if it does.
---
### Some assert limitations and warnings

There are a few pitfalls and limitations to asserts. First, the assert itself can be improperly written. If this happens, the assert will either report an error where none exists, or fail to report a bug where one does exist.

Second, your `assert()` expressions should have no side effects, as the assert expression won’t be evaluated when `NDEBUG` is defined (and thus the side effect won’t be applied). Otherwise, what you are testing in a debug configuration will not be the same as in a release configuration (assuming you ship with NDEBUG).

Also note that the `abort()` function terminates the program immediately, without a chance to do any further cleanup (e.g. close a file or database). Because of this, asserts should be used only in cases where corruption isn’t likely to occur if the program terminates unexpectedly.

---

>[!Note]
>The **happy path** is the path of execution that occurs when there are no errors encountered. A **sad path** is one where an error or failure state occurs. A **non-recoverable error** (also called a **fatal error**) is an error that is severe enough that the program can’t continue running. A program that handles error cases well is **robust**.

#### ✅ **Key Idea:**

> **Use `assert()` for things that should _never happen_**  
> **Use error handling for things that _might happen_** (even rarely)

---
Reminder:

Need To revise 4 errors again for the quiz question.