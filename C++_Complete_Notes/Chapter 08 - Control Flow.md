
>Control Flow statements are the statements that allow the programmer to change the normal path of execution.
>eg: If-statements...

>[!Key Insight]
>When a control flow statement causes point of execution to change to a non-sequential statement, this is called **branching**.

### Categories of flow control statements

|Category|Meaning|Implemented in C++ by|
|---|---|---|
|Conditional statements|Causes a sequence of code to execute only if some condition is met.|if, else, switch|
|Jumps|Tells the CPU to start executing the statements at some other location.|goto, break, continue|
|Function calls|Jump to some other location and back.|function calls, return|
|Loops|Repeatedly execute some sequence of code zero or more times, until some condition is met.|while, do-while, for, ranged-for|
|Halts|Terminate the program.|std::exit(), std::abort()|
|Exceptions|A special kind of flow control structure designed for error handling.|try, throw, catch|

---

### If statements and blocks

>C++ supports two conditional statements:
>1. if statements 
>2. switch Statements

```cpp
if (age >= minDrinkingAge)
//    addBeerToCart();

checkout(); // conditionally executes now
```

>Now we’ve made `checkout()` conditional, which we certainly didn’t intend.

>[!best practice]
>Put Blocks even if it is one statement!

### Common If statement problem

>The Dangling problem of else can be fixed by using blocks, which will be our practice...

>[!tip]
>Code that is less nested is less error prone...

>Nested if-statements can often be flattened by either restructuring the logic or by using logical operators
>Flattened means made shorter.

>Null statements is an expression that consists of just a semicolon.

```cpp
if (x > 10)
    ; // this is a null statement
```
Null statements do nothing. They are typically used when the language requires a statement to exist but the programmer doesn’t need one

>[!warning]
>Be careful not to “terminate” your if-statement with a semicolon, otherwise the statement(s) you wanted to execute conditionally will execute unconditionally instead (even if they are inside a block).
>>```cpp
>>if(true);{
>>	statement-1 // will execute even if the condition is false
>>}
>>```

>[!tip]
>In Python instead of semicolon we use PASS word, we can mimic this by using preprocessor:
```cpp
#define PASS

void foo(int x, int y)
{
    if (x > y)
        PASS; // pass will be stripped by the preprocessor and only semicolon will remain
    else
        PASS;
}

int main()
{
    foo(4, 7);

    return 0;
}
```

---
### Constexpr If statements

>Normally, the conditional of an if-statement is evaluated at runtime.
>However, consider the case where the conditional is a constant expression, such as in the following example:

```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	// reminder: low-precision floating point literals of the same type can be tested for equality
	if (gravity == 9.8) // constant expression, always true
		std::cout << "Gravity is normal.\n";   // will always be executed
	else
		std::cout << "We are not on Earth.\n"; // will never be executed

	return 0;
}
```

>Because `gravity` is constexpr and initialized with value `9.8`, the conditional `gravity == 9.8` must evaluate to `true`. As a result, the else-statement will never be executed.
>Evaluating a constexpr conditional at runtime is wasteful (since the result will never vary). It is also wasteful to compile code into the executable that can never be executed.

>**constexpr if statement:** requires the conditional to be a constant expression.
>The conditional of a constexpr-if-statement will be evaluated at compile-time.

>**Important Read**: If the constexpr conditional evaluates to `true`, the entire if-else will be replaced by the true-statement. If the constexpr conditional evaluates to `false`, the entire if-else will be replaced by the false-statement (if it exists) or nothing (if there is no else).

To use a constexpr-if-statement, we add the `constexpr` keyword after the `if`:
```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	if constexpr (gravity == 9.8) // now using constexpr if
		std::cout << "Gravity is normal.\n";
	else
		std::cout << "We are not on Earth.\n";

	return 0;
}
```

>[!Key Insight]
>What it will do is replace the body of if with statement that are inside if at compile time and also it doesnt matter if insdie of IF statement have non-constant expression statements because only the conditional will evaluate at compile time!

In other words, it will compile this:
```cpp
int main()
{
	constexpr double gravity{ 9.8 };

	std::cout << "Gravity is normal.\n";

	return 0;
}
```

>[!best practice]
>Favor constexpr if statements over non-constexpr if statements when the conditional is a constant expression.

For optimization purposes, modern compilers will generally treat non-constexpr if-statements that have constexpr conditionals as if they were constexpr-if-statements. However, they are not required to do so.

A compiler that encounters a non-constexpr if-statement with a constexpr conditional may issue a warning advising you to use `if constexpr` instead. This will ensure that compile-time evaluation will occur (even if optimizations are disabled).

---
### Switch Statement

>Although it is possible to chain many if-else-statements together, this is both difficult to read and inefficient. Consider the following program:

```cpp
#include <iostream>

void printDigitName(int x)
{
    if (x == 1)
        std::cout << "One";
    else if (x == 2)
        std::cout << "Two";
    else if (x == 3)
        std::cout << "Three";
    else
        std::cout << "Unknown";
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

>Variable `x` in `printDigitName()` will be evaluated up to three times depending on the value passed in (which is inefficient), and the reader has to be sure that it is `x` being evaluated each time (not some other variable).

>Because testing a variable or expression for equality against a set of different values is common, C++ provides an alternative conditional statement called a switch-statement that is specialized for this purpose. Here is the same program as above using a switch:

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x)
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

>The idea behind a **switch statement** is simple: an expression (sometimes called the condition) is evaluated to produce a value.
>Then one of the following occurs:
>
>>1. If the expression’s value is equal to the value after any of the case-labels, the statements after the matching case-label are executed.
>>2. If no matching value can be found and a default label exists, the statements after the default label are executed.
>>3. If no matching value can be found and there is no default label, the switch is skipped.

>We start a switch-statement by using the `switch` keyword, followed by parentheses with the conditional expression that we would like to evaluate inside. Often the expression is just a single variable, but it can be any valid expression.

>[!tip]
>Condition in switch must evaluate to integral type or be convertable to one...
>Expressions that evaluate to floating point types, strings, and most other non-integral types may not be used here.

#### [Why do switch statements allow only integral evaluation!](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/#:~:text=For%20advanced%20readers,of%20C%2B%2B23)

>Following the conditional expression, we declare a block. Inside the block, we use labels to define all of the values we want to test for equality. There are two kinds of labels used with switch statements, which we’ll discuss subsequently.

### Case Labels

>The first kind of label is the **case label**, which is declared using the `case` keyword and followed by a constant expression. The constant expression must either match the type of the condition or must be convertible to that type.

>If the value of the conditional expression equals the expression after a `case label`, execution begins at the first statement after that `case label` and then continues sequentially.

```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 2
    {
    case 1:
        std::cout << "One";
        return;
    case 2: // which matches the case statement here
        std::cout << "Two"; // so execution starts here
        return; // and then we return to the caller
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```

>[!warning]
>all the case labels in a switch statement must be unique:
```cpp
switch (x)
{
case 54:
case 54:  // error: already used value 54!
case '6': // error: '6' converts to integer value 54, which is already used
}
```

### The default label

>The second kind of label is the **default label** (often called the **default case**), which is declared using the `default` keyword. If the conditional expression does not match any case label and a default label exists, execution begins at the first statement after the default label.

Can be only One default label and its optional!!!!!!!

### Taking a break

> we used return statements to stop the execution of the statements after the labels. However, this also exits the entire function!

>A break statement `break;` tells the compiler that we are done executing statements within the switch.
>--> Exit the switch statement

>[!best practice]
>Each set of statements underneath a label should end in a break-statement or a return-statement. This includes the statements underneath the last label in the switch.


```cpp
// Acceptable but not preferred version
void printDigitName(int x)
{
    switch (x)
    {
        case 1: // indented from switch block
            std::cout << "One"; // indented from label (misleading)
            return;
        case 2:
            std::cout << "Two";
            return;
        case 3:
            std::cout << "Three";
            return;
        default:
            std::cout << "Unknown";
            return;
    }
}
```
>it implies that the statements beneath each label are in a nested scope, which is not the case (we’ll see examples of this in the next lesson, where a variable we define in one case can be used in another case). This formatting is considered acceptable (as it is readable), but it is not preferred.

>[!Best Practice]
>Prefer not to indent labels. This allows them to stand out from the surrounding code without implying that they are defining a nested scope region.
```cpp
// Preferred version
void printDigitName(int x)
{
    switch (x)
    {
    case 1: // not indented from switch statement
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}
```

#### [Switch vs if-else](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/#:~:text=Switch%20statements%20are%20best,small%20set%20of%20values.)

>[!Best Practice]
>Prefer a switch-statement over if-else statements when testing a single expression (with a non-boolean integral type or an enumerated type) for equality against a small set of values.

---

>[!Note]
>Presence of another case label is not one of the terminating conditions thus, without break or return, execution will overflow into subsequent cases...which is called **Fallthrough**
```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }

    return 0;
}
```

---
### The [[fallthrough]] attribute

>Commenting intentional fallthrough is a common convention to tell other developers that fallthrough is intended. While this works for other developers, the compiler and code analysis tools don’t know how to interpret comments, so it won’t get rid of the warnings.

To help address this, C++17 adds a new attribute called `[[fallthrough]]`.

>[!note]
>Attribute are a modern C++ feature that allows the programmer to provide the compiler with some additional data about the code.
>To specify an attribute, the attribute name is placed between double brackets.
>Attributes are not statements.

>The `[[fallthrough]]` attribute modifies a `null statement` to indicate that fallthrough is intentional (and no warnings should be triggered):

```cpp
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }
```

>[!Best Practice]
>Use the `[[fallthrough]]` attribute (along with a null statement) to indicate intentional fallthrough.

---
### Sequential case labels

```cpp
bool isVowel(char c)
{
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
        c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
}
```

>This suffers from the same challenges that we presented in the introduction to switch statements: `c` gets evaluated multiple times and the reader has to make sure it is `c` that is being evaluated each time.

You can do something similar using switch statements by placing multiple case labels in sequence:
```cpp
bool isVowel(char c)
{
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        return true;
    default:
        return false;
    }
}
```
>Remember, execution begins at the first statement after a matching case label. Case labels aren’t statements (they’re labels), so they don’t count.
>The first statement after _all_ of the case statements in the above program is `return true`, so if any case labels match, the function will return `true`.

---
### Labels do not define a new scope

With `if statements`, you can only have a single statement after the if-condition, and that statement is considered to be implicitly inside a block:

```cpp
if (x > 10)
    std::cout << x << " is greater than 10\n"; // this line implicitly considered to be inside a block
```

>However, with switch statements, the statements after labels are all scoped to the switch block. No implicit blocks are created.

```cpp
switch (1)
{
case 1: // does not create an implicit block
    foo(); // this is part of the switch scope, not an implicit block to case 1
    break; // this is part of the switch scope, not an implicit block to case 1
default:
    std::cout << "default case\n";
    break;
}
```
In the above example, the 2 statements between the `case 1` and the default label are scoped as part of the switch block, not a block implicit to `case 1`.

---
### Variable declaration and initialization inside case statements

>You can declare or define (but not initialize) variables inside the switch, both before and after the case labels:

```cpp
switch (1)
{
    int a; // okay: definition is allowed before the case labels
    int b{ 5 }; // illegal: initialization is not allowed before the case labels

case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;

case 2:
    int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;

case 3:
    break;
}
```

>[!tip]
>We can declare or define the variable inside the switch both before and after the case labels but we cannot initialize the variable...

>Although variable `y` was defined in `case 1`, it was used in `case 2` as well. All statements inside the switch are considered to be part of the same scope. Thus, a variable declared or defined in one case can be used in a later case, even if the case in which the variable is defined is never executed (because the switch jumped over it)!

>However, initialization of variables _does_ require the definition to execute. Initialization of variables is disallowed in any case that is not the last case (because the switch could jump over the initializer if there is a subsequent case defined, in which case the variable would be undefined, and accessing it would result in undefined behavior). Initialization is also disallowed before the first case, as those statements will never be executed, as there is no way for the switch to reach them.
```cpp
switch (value)
    int x = 5;  // ❌ This code is unreachable
case 1:
    // execution starts here

```

>If a case needs to define and/or initialize a new variable, the best practice is to do so inside an explicit block underneath the case statement:

```cpp
switch (1)
{
case 1:
{ // note addition of explicit block here
    int x{ 4 }; // okay, variables can be initialized inside a block inside a case
    std::cout << x;
    break;
}

default:
    std::cout << "default case\n";
    break;
}
```

>[!tip]
>If defining variables used in a case statement, do so in a block inside the case.

---
### GOTO statements

>An unconditional jump causes execution to jump to another spot in the code. The term “unconditional” means the jump always happens (unlike an if-statement or switch-statement, where the jump only happens conditionally based on the result of an expression).

>In C++, unconditional jumps are implemented via a **goto statement**, and the spot to jump to is identified through use of a **statement label**.

The following is an example of a goto statement and statement label:

```cpp
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
    return 0;
}
```
>In this program, the user is asked to enter a non-negative number. However, if a negative number is entered, the program utilizes a goto statement to jump back to the `tryAgain` label. The user is then asked again to enter a new number. In this way, we can continually ask the user for input until he or she enters something valid.

---
### Statement labels have function scope

>In the chapter on object scope ([chapter 7](https://www.learncpp.com/#Chapter7)), we covered two kinds of scope: local (block) scope, and file (global) scope. Statement labels utilize a third kind of scope: **function scope**, which means the label is visible throughout the function even before its point of declaration. The goto statement and its corresponding `statement label` must appear in the same function.

>[!warning]
>The goto statement and statement label must appear int he same function otherwise out of scope!!!

>While the above example shows a goto statement that jumps backwards (to a preceding point in the function), goto statements can also jump forward:

```cpp
#include <iostream>

void printCats(bool skip)
{
    if (skip)
        goto end; // jump forward; statement label 'end' is visible here due to it having function scope

    std::cout << "cats\n";
end:
    ; // statement labels must be associated with a statement
}

int main()
{
    printCats(true);  // jumps over the print statement and doesn't print anything
    printCats(false); // prints "cats"

    return 0;
}
```
cats

>First, note that statement labels must be associated with a statement (hence their name: they label a statement). Because the end of the function had no statement, we had to use a null statement so we had a statement to label. Second, we were able to jump to the statement labeled by `end` even though we hadn’t declared `end` yet due to statement labels having function scope. No forward declaration of statement labels is necessary. Third, it’s worth explicitly mentioning that the above program is poor form -- it would have been better to use an if-statement to skip the print statement than a goto statement to jump over it.

>There are two primary limitations to jumping: You can jump only within the bounds of a single function (you can’t jump out of one function and into another), and if you jump forward, you can’t jump forward over the initialization of any variable that is still in scope at the location being jumped to. For example:

```cpp
int main()
{
    goto skip;   // error: this jump is illegal because...
    int x { 5 }; // this initialized variable is still in scope at statement label 'skip'
skip:
    x += 3;      // what would this even evaluate to if x wasn't initialized?
    return 0;
}
```

---
### [Avoid GOTO STATEMENTS](https://www.learncpp.com/cpp-tutorial/goto-statements/#:~:text=Avoid%20using%20goto,at%20xkcd%3A)

>[!Best Practice]
>Avoid goto statements (unless the alternatives are significantly worse for code readability).

>[!tip]
>One notable exception is when you need to exit a nested loop but not the entire function -- in such a case, a goto to just beyond the loops is probably the cleanest solution.

---
### While Statements

>The **while statement** (also called a **while loop**) is the simplest of the three loop types that C++ provides, and it has a definition very similar to that of an if-statement:

```cpp
while (condition)
    statement;
```

```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10)
    {
        std::cout << count << ' ';
        ++count;
    }

    std::cout << "done!\n";

    return 0;
}
```

>[!tip]
>It will return control back to the while until the condition becomes false

### Intentional infinite loops

```cpp
#include <iostream>

int main()
{

    while (true) // infinite loop
    {
        std::cout << "Loop again (y/n)? ";
        char c{};
        std::cin >> c;

        if (c == 'n')
            return 0;
    }

    return 0;
}
```

>The only way to exit an infinite loop is through a return-statement, a break-statement, an exit-statement, a goto-statement, an exception being thrown, or the user killing the program.

>This program will continuously loop until the user enters `n` as input, at which point the if-statement will evaluate to `true` and the associated `return 0;` will cause function `main()` to exit, terminating the program.

>[!Example]
>It is common to see this kind of loop in web server applications that run continuously and service web requests.

>[!Best Practice]
>Favor `while(true)` for intentional infinite loops.

### Unintentional infinite loops

>Unintentionally placing a semicolon after the condition of a while-loop is a good way to hang your program.

```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10); // note the semicolon here
    {
        std::cout << count << ' ';
        ++count;
    }

    std::cout << "done!\n";

    return 0;
}
```

>[!Warning]
>Be careful about placing a semicolon after the condition of a while-statement, as it will result in an infinite loop unless the condition some way to evaluate to `false`.

>[!Best Practice]
>Integral loop variables should generally be a signed integral type.
>**Why?:** Because after 0 is decremented it overflows and wraps around 4294967295 which is greater than 0 so it will be an unintentional loop!
```cpp
#include <iostream>

int main()
{
    unsigned int count{ 10 }; // note: unsigned

    // count from 10 down to 0
    while (count >= 0)
    {
        if (count == 0)
        {
            std::cout << "blastoff!";
        }
        else
        {
            std::cout << count << ' ';
        }
        --count;
    }

    std::cout << '\n';

    return 0;
}
```

>[!tip]
>Each time a loop executes, it is called an iteration.

---
### Doing something every N iterations

```cpp
#include <iostream>

// Iterate through every number between 1 and 50
int main()
{
    int count{ 1 };
    while (count <= 50)
    {
        // print the number (pad numbers under 10 with a leading 0 for formatting purposes)
        if (count < 10)
        {
            std::cout << '0';
        }

        std::cout << count << ' ';

        // if the loop variable is divisible by 10, print a newline
        if (count % 10 == 0)
        {
            std::cout << '\n';
        }

        // increment the loop counter
        ++count;
    }

    return 0;
}
```

### 🧠 What does `count % 10` mean?

It means: **divide `count` by 10 and give me the remainder**.

- For example:
    
    - `9 % 10 = 9` (because 10 goes into 9 zero times, with remainder 9)
        
    - `10 % 10 = 0` (because 10 goes into 10 exactly once, with no remainder)
        
    - `11 % 10 = 1` // 10 **goes into** 11 exactly **1 time** with remainder 1
        
    - `20 % 10 = 0`
        
    - `21 % 10 = 1`
        

So, `count % 10 == 0` becomes true when `count` is a **multiple of 10** — i.e., 10, 20, 30, 40, 50, etc.

### 🔍 Why is it used here?

You're printing numbers from 1 to 50. This condition:

cpp

CopyEdit

`if (count % 10 == 0)`

is used to **insert a newline every 10 numbers**, so the output is organized in rows like:

```cpp
01 02 03 04 05 06 07 08 09 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
```

Without this condition, all 50 numbers would be printed in one long horizontal line.

---
### Nested Loop

```cpp
#include <iostream>

void printUpto(int outer)
{
    // loop between 1 and outer
    // note: inner will be created and destroyed at the end of the block
    int inner{ 1 };
    while (inner <= outer)
    {
        std::cout << inner << ' ';
        ++inner;
    }
} // inner destroyed here

int main()
{
    // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // This function prints numbers between 1 and outer
        printUpto(outer);

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    }

    return 0;
}
```
Therefore, this program prints:

1
1 2
1 2 3
1 2 3 4
1 2 3 4 5

```cpp
#include <iostream>

int main()
{
    // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // inner loops between 1 and outer
        // note: inner will be created and destroyed at the end of the block
        int inner{ 1 };
        while (inner <= outer)
        {
            std::cout << inner << ' ';
            ++inner;
        }

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    } // inner destroyed here

    return 0;
}
```

---
### Do While Statements

```cpp
do
    statement; // can be a single statement or a compound statement
while (condition);
```

A **do while statement** is a looping construct that works just like a while loop, except the statement always executes at least once. After the statement has been executed, the do-while loop checks the condition. If the condition evaluates to `true`, the path of execution jumps back to the top of the do-while loop and executes it again.

```cpp
#include <iostream>

int main()
{
    // selection must be declared outside of the do-while-loop, so we can use it later
    int selection {};

    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection < 1 || selection > 4);

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```
In this way, we’ve avoided both magic numbers and additional variables.

In practice, do-while loops aren’t commonly used. Having the condition at the bottom of the loop obscures the loop condition, which can lead to errors. Many developers recommend avoiding do-while loops altogether as a result. We’ll take a softer stance and advocate for preferring while loops over do-while when given an equal choice.

>[!Best Practice]
>Favor while loops over do-while when given an equal choice.

---
### For Statements

>The initialization happens only once in for loop.

> with each loop iteration, the condition is evaluated, if it evaluates to true then the statemets are executed.

--> Order:
- Init-statement
- Condition (if this is false, the loop terminates here).
- Loop body
- End-expression (then jumps back to condition)

>[!tip]
>Note that the end-expression executes _after_ the loop statement, and then the condition is re-evaluated.

>[!tip]
>we can change the value of our loop variable by more than 1 with each iteration:
>```cpp
>for (int i{ 0 }; i <= 10; i += 2) // increment by 2 each iteration
>```

>[!Best Practice]
>Avoid `operator!=` when doing numeric comparisons in the for-loop condition. Prefer `operator<` or `operator<=` where possible.
```cpp
#include <iostream>

int main()
{
    for (int i { 0 }; i < 10; ++i) // uses <, still terminates
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

    for (int i { 0 }; i != 10; ++i) // uses !=, infinite loop
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

     return 0;
}
```

>Off-by-one error occurs when we use wrong relational operator like instead of `<=` we use `<` which can be wrong depending on logic.

### Omitted Expression

>It is possible to write _for loops_ that omit any or all of the statements or expressions. For example, in the following example, we’ll omit the init-statement and end-expression, leaving only the condition:

```cpp
#include <iostream>

int main()
{
    int i{ 0 };
    for ( ; i < 10; ) // no init-statement or end-expression
    {
        std::cout << i << ' ';
        ++i;
    }

    std::cout << '\n';

    return 0;
}
```
0 1 2 3 4 5 6 7 8 9

>Rather than having the _for loop_ do the initialization and incrementing, we’ve done it manually. We have done so purely for academic purposes in this example, but there are cases where not defining a loop variable (because you already have one) or not incrementing it in the end-expression (because you’re incrementing it some other way) is desired.

```cpp
for (;;)
    statement;
    // this is infinite loop
```

### For-loops with multiple counters

>Although for-loops typically iterate over only one variable, sometimes for-loops need to work with multiple variables. To assist with this, the programmer can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end-expression:

```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```

>[!Best Practice]
>Defining multiple variables (in the init-statement) and using the comma operator (in the end-expression) is acceptable inside a for-statement.

```cpp
#include <iostream>

int main()
{
    int i {}; // i defined outside loop
    for (i = 0; i < 10; ++i) // i assigned value
    {
        std::cout << i << ' ';
    }

    // i can still be accessed here

    std::cout << '\n';
    std::cout << i;
    return 0;
}
```
>[!Example]
>In the above example, as you can see we can still access i because we initialized it outside the for loop so i is still in scope...

>[!Best Practice]
>Variables used only inside a loop should be defined inside the scope of the loop.

- **Declaring a variable** (e.g., `int i;`) has no runtime cost—it's just a name for a memory location.
    
- **Initializing or assigning** a value to it (e.g., `i = 0;`) is what actually causes computation or memory writes.

>[!Best Practice]
>Prefer for-loops over while-loops when there is an obvious loop variable.  
Prefer while-loops over for-loops when there is no obvious loop variable.

---
### Break And Continue

>The **break statement** causes a while loop, do-while loop, for loop, or switch statement to end, with execution continuing with the next statement after the loop or switch being broken out of.

>A break is also a common way to get out of an intentional infinite loop:

```cpp
#include <iostream>

int main()
{
    while (true) // infinite loop
    {
        std::cout << "Enter 0 to exit or any other integer to continue: ";
        int num{};
        std::cin >> num;

        // exit loop if user enters 0
        if (num == 0)
            break;
    }

    std::cout << "We're out!\n";

    return 0;
}
```

### Break vs return

>New programmers sometimes have trouble understanding the difference between `break` and `return`. A `break` statement terminates the switch or loop, and execution continues at the first statement beyond the switch or loop. A `return` statement terminates the entire function that the loop is within, and execution continues at point where the function was called.

### Continue

>The **continue statement** provides a convenient way to end the current iteration of a loop without terminating the entire loop.

```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is divisible by 4, skip this iteration
        if ((count % 4) == 0)
            continue; // go to next iteration

        // If the number is not divisible by 4, keep going
        std::cout << count << '\n';

        // The continue statement jumps to here
    }

    return 0;
}
```
12356789

>A `continue` statement works by causing the current point of execution to jump to the bottom of the current loop.

>Be careful when using a `continue` statement with while or do-while loops. These loops typically change the value of variables used in the condition inside the loop body. If use of a `continue` statement causes these lines to be skipped, then the loop can become infinite!

```cpp
#include <iostream>

int main()
{
    int count{ 0 };
    while (count < 10)
    {
        if (count == 5)
            continue; // jump to end of loop body

        std::cout << count << '\n';

        ++count; // this statement is never executed after count reaches 5

        // The continue statement jumps to here
    }

    return 0;
}
```

### The debate over use of break and continue

>Many textbooks caution readers not to use `break` and `continue` in loops, both because it causes the execution flow to jump around, and because it can make the flow of logic harder to follow. For example, a `break` in the middle of a complicated piece of logic could either be missed, or it may not be obvious under what conditions it should be triggered.

>[!tip]
>However, used judiciously, `break` and `continue` can help make loops more readable by keeping the number of nested blocks down and reducing the need for complicated looping logic.

```cpp
#include <iostream>

int main()
{
    int count{ 0 }; // count how many times the loop iterates
    bool keepLooping { true }; // controls whether the loop ends or not
    while (keepLooping)
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'e')
            keepLooping = false;
        else
        {
            ++count;
            std::cout << "We've iterated " << count << " times\n";
        }
    }

    return 0;
}
```

Here’s a version that’s easier to understand, using a `break` statement:

```cpp
#include <iostream>

int main()
{
    int count{ 0 }; // count how many times the loop iterates
    while (true) // loop until user terminates
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'e')
            break;

        ++count;
        std::cout << "We've iterated " << count << " times\n";
    }

    return 0;
}
```

>The `continue` statement is most effectively used at the top of a for-loop to skip loop iterations when some condition is met. This can allow us to avoid a nested block.

```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is not divisible by 4...
        if ((count % 4) != 0) // nested block
        {
                // Print the number
                std::cout << count << '\n';
        }
    }

    return 0;
}
```
instead we can do: 

```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is divisible by 4, skip this iteration
        if ((count % 4) == 0)
            continue;

        // no nested block needed

        std::cout << count << '\n';
    }

    return 0;
}
```

>Minimizing the number of variables used and keeping the number of nested blocks down both improve code comprehensibility more than a `break` or `continue` harms it. For that reason, we believe judicious use of `break` or `continue` is acceptable.

>[!Best Practice]
>Use break and continue when they simplify your loop logic.

>[!best practice]
>Use early returns when they simplify your function’s logic.

>Some developers take a middle ground, and only use early returns at the top of a function to do parameter validation (catch bad arguments passed in), and then a single return thereafter.

---
### The std::exit() function

>`std::exit()` is a function that causes the program to terminate normally. **Normal termination** means the program has exited in an expected way. Note that the term `normal termination` does not imply anything about whether the program was successful (that’s what the `status code` is for). For example, let’s say you were writing a program where you expected the user to type in a filename to process. If the user typed in an invalid filename, your program would probably return a non-zero `status code` to indicate the failure state, but it would still have a `normal termination`.

>`std::exit()` performs a number of cleanup functions. First, objects with static storage duration are destroyed. Then some other miscellaneous file cleanup is done if any files were used. Finally, control is returned back to the OS, with the argument passed to `std::exit()` used as the `status code`.

### Calling std::exit() explicitly

>Although `std::exit()` is called implicitly after function `main()` returns, `std::exit()` can also be called explicitly to halt the program before it would normally terminate. When `std::exit()` is called this way, you will need to include the `cstdlib` header.

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    std::cout << 1 << '\n';
    cleanup();

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

>[!note]
>Note that the statements after the call to `std::exit()` never execute because the program has already terminated.

>[!note]
>explicitly `std::exit()` does not clean up local variables

>[!warning]
>The `std::exit()` function does not clean up local variables in the current function or up the call stack.
>And due to this it will have security risk...

### std::atexit

>Because `std::exit()` terminates the program immediately, you may want to manually do some cleanup before terminating. In this context, cleanup means things like closing database or network connections, deallocating any memory you have allocated, writing information to a log file, etc…

>In the above example, we called function `cleanup()` to handle our cleanup tasks. However, remembering to manually call a cleanup function before calling every call to exit() adds burden to the programmer and is a recipe for errors.

>To assist with this, C++ offers the `std::atexit()` function, which allows you to specify a function that will automatically be called on program termination via `std::exit()`.

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

>[!Note] 
>that when we pass `cleanup()` function as an argument, we use `cleanup` (the function’s name), not `cleanup()` (which would actually call the function).

>The benefit of `std::atexit()` is that we only have to call it once (probably from within function `main()`). Since `std::atexit()` will be automatically called on exit, we don’t have to remember to call anything before calling `std::exit()`.

>[!Important]
>A few notes here about `std::atexit()` and the cleanup function: First, because `std::exit()` is called implicitly when `main()` terminates, this will invoke any functions registered by `std::atexit()` if the program exits that way. Second, the function being registered must take no parameters and have no return value. Finally, you can register multiple cleanup functions using `std::atexit()` if you want, and they will be called in reverse order of registration (the last one registered will be called first).

>[!As an aside]
>Memory management in C++ refers to the process of controlling how a program uses and releases computer memory. Unlike some higher-level languages that employ automatic garbage collection, C++ provides developers with direct control over memory allocation and deallocation. This control offers performance advantages but also introduces the responsibility of managing memory correctly to prevent issues like memory leaks and dangling pointers.

>[!best practice]
>Only use a halt if there is no safe or reasonable way to return normally from the main function. If you haven’t disabled exceptions, prefer using exceptions for handling errors safely.

>[!tip]
>Although explicit use of halts should be minimized, there are many other ways that a program can shut down unexpectedly. For example:
>- The application could crash due to a bug (in which case the OS will shut it down).
>- The user might kill the application in various ways.
>- The user might turn off (or lose) power to their computer.
>- The sun could go supernova and consume the earth in a giant ball of fire.
>
>A well-designed program should be able to handle being shut down at any point with minimal repercussions.
>
>As a common example of this, modern games often autosave game state and user settings periodically, so that if the game is unexpectedly shut down without saving, the user can continue later (using the prior autosave) without much lost progress.

---
### Random Numbers

>modern programs typically _simulate_ randomness using an algorithm.

>algorithms are typically implemented as reusable functions.

>An **algorithm** is a finite sequence of instructions that can be followed to solve some problem or produce some useful result.

simple algorithm:
```cpp
#include <iostream>

int plusOne()
{
    static int s_state { 3 }; // only initialized the first time this function is called

    // Generate the next number

    ++s_state;      // first we modify the state
    return s_state; // then we use the new state to generate the next number in the sequence
}

int main()
{
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';

    return 0;
}
```

>An algorithm is considered to be **stateful** if it retains some information across calls. Conversely, a **stateless** algorithm does not store any information (and must be given all the information it needs to work with whenever it is called). Our `plusOne()` function is stateful, in that it uses the static variable `s_state` to store the last number that was generated. When applied to algorithms, the term **state** refers to the current values held in stateful variables (those retained across calls).

>Our algorithm is considered **deterministic**, meaning that for a given input (the value provided for `start`), it will always produce the same output sequence.

#### [Pseudo-random number generators (PRNGs) Algorithm](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/#:~:text=Pseudo%2Drandom%20number,better%20quality%20results.)

### Seeding a PRNG

>The sequence of “random numbers” generated by a PRNG is not random at all. Just like our `plusOne()` function, `LCG16()` is also deterministic. Given some initial state value (such as `0`), a PRNG will generate the same sequence of numbers each time. If you run the above program 3 times, you’ll see it generates the same sequence of values each time.

>In order to generate different output sequences, the initial state of a PRNG needs to be varied. The value (or set of values) used to set the initial state of a PRNG is called a **random seed** (or **seed** for short). When the initial state of a PRNG has been set using a seed, we say it has been **seeded**.

>[!Key]
>Because the initial state of the PRNG is set from the seed value(s), all of the values that a PRNG will produce are deterministically calculated from the seed value(s).

The seed value is typically provided by the program using the PRNG. Here’s a sample program that requests a seed value from the user and then generates 10 random numbers using that seed value (using our `LCG16()` function).

```cpp
#include <iostream>

unsigned int g_state{ 0 };

void seedPRNG(unsigned int seed)
{
    g_state = seed;
}

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    g_state = 8253729 * g_state + 2396403; // first we modify the state
    return g_state % 32768; // then we use the new state to generate the next number in the sequence
}

void print10()
{
    // Print 10 random numbers
    for (int count{ 1 }; count <= 10; ++count)
    {
        std::cout << LCG16() << '\t';
    }

    std::cout << '\n';
}

int main()
{
    unsigned int x {};
    std::cout << "Enter a seed value: ";
    std::cin >> x;

    seedPRNG(x); // seed our PRNG
    print10();   // generate 10 random values

    return 0;
}
```

Here are 3 sample runs from this:

Enter a seed value: 7
10458	3853	16032	17299	10726	32153	19116	7455	242	549	

Enter a seed value: 7
10458	3853	16032	17299	10726	32153	19116	7455	242	549	

Enter a seed value: 9876
24071	18138	27917	23712	8595	18406	23449	26796	31519	7922	

Notice that when we provide the same seed value, we get the same output sequence. If we provide a different seed value, we get a different output sequence.

### Seed quality and underseeding

[Important Read Very!](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/#:~:text=If%20we%20want,simulations%20or%20cryptography)

#### [What makes a good PRNG?](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/#:~:text=What%20makes%20a,lots%20of%20randomness.)

---
### Generating random numbers in C++ using Mersenne Twister

- `mt19937` is a Mersenne Twister that generates 32-bit unsigned integers
- `mt19937_64` is a Mersenne Twister that generates 64-bit unsigned integers

```cpp
#include <iostream>
#include <random> // for std::mt19937

int main()
{
	std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << mt() << '\t'; // generate a random number

		// If we've printed 5 numbers, start a new row
		if (count % 5 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

3499211612      581869302       3890346734      3586334585      545404204
4161255391      3922919429      949333985       2715962298      1323567403
418932835       2350294565      1196140740      809094426       2348838239
4264392720      4112460519      4279768804      4144164697      4156218106
676943009       3117454609      4168664243      4213834039      4111000746
471852626       2084672536      3427838553      3437178460      1275731771
609397212       20544909        1811450929      483031418       3933054126
2747762695      3402504553      3772830893      4120988587      2163214728

>First, we include the `<random>` header, since that’s where all the random number capabilities live. Next, we instantiate a 32-bit Mersenne Twister engine via the statement `std::mt19937 mt`. Then, each time we want to generate a random 32-bit unsigned integer, we call `mt()`.

>**Why mt()?** : since mt is a variable so how come we are using `()` operator which is used to call functions, `mt()` is a concise syntax for calling the function `mt.operator()`.
>The advantage of using `operator()` instead of a named function is that we don’t need to remember the function’s name, and the concise syntax is less typing.

>[!tip]
>A **random number distribution** is just a **probability distribution** designed to take values from a **PRNG** and shape them into values that match a desired statistical pattern.

### Rolling a dice using Mersenne Twister

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::uniform_int_distribution

int main()
{
	std::mt19937 mt{};

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```
3       1       3       6       5       2       6       6       1       2
2       6       1       1       6       1       4       5       2       5
6       2       6       2       1       3       5       4       5       6
1       4       2       3       1       2       2       6       2       1

>There are only two noteworthy differences in this example compared to the previous one. First, we’ve created a uniform distribution variable (named `die6`) to generate numbers between 1 and 6. Second, instead of calling `mt()` to generate 32-bit unsigned integer random numbers, we’re now calling `die6(mt)` to generate a value between 1 and 6.

### The above program isn’t as random as it seems

>If you run the program multiple times, you will note that it prints the same numbers every time! While each number in the sequence is random with regards to the previous one, the entire sequence is not random at all! Each run of our program produces the exact same result.

>it is being initialized with the same seed every time the program is run. And because the seed is the same, the random numbers being generated are also the same.

>In order to make our entire sequence randomized differently each time the program is run, we need to pick a seed that’s not a fixed number. The first answer that probably comes to mind is that we need a random number for our seed! That’s a good thought, but if we need a random number to generate random numbers, then we’re in a catch-22. It turns out, we really don’t need our seed to be a random number -- we just need to pick something that changes each time the program is run. Then we can use our PRNG to generate a unique sequence of pseudo-random numbers from that seed.

There are two methods that are commonly used to do this:

- Use the system clock
- Use the system’s random device
---
### Seeding with the system clock

What’s one thing that’s different every time you run your program? Unless you manage to run your program twice at exactly the same moment in time, the answer is that the current time is different. Therefore, if we use the current time as our seed value, then our program will produce a different set of random numbers each time it is run. C and C++ have a long history of PRNGs being seeded using the current time (using the `std::time()` function), so you will probably see this in a lot of existing code.

Fortunately, C++ has a chrono library containing various clocks that we can use to generate a seed value. To minimize the chance of two time values being identical if the program is run quickly in succession, we want to use some time measure that changes as quickly as possible. For this, we’ll ask the clock how much time has passed since the earliest time it can measure. This time is measured in “ticks”, which is a very small unit of time (usually nanoseconds, but could be milliseconds).

```cpp
#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{
	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

#### 🧩 `std::mt19937 mt{ ... };`

- `std::mt19937` is a Mersenne Twister 32-bit pseudo-random number generator engine.
    
- We're creating an instance of it named `mt`.
    
- The value inside `{ ... }` is the **seed** being passed to initialize the PRNG.
    

#### 🕒 `std::chrono::steady_clock::now()`

- This gives you the **current time point** according to the `steady_clock`.
    
- `steady_clock` is **monotonic** and **not affected by system time changes** (unlike `system_clock`).
    
- Good choice when you want consistent timing not dependent on wall-clock time.
    

#### 📆 `.time_since_epoch()`

- This returns a `duration` representing the time passed since the "epoch" (starting point of the clock).
    
- In `steady_clock`, this doesn't mean any particular date — it's just how much time has passed since the program started (or system boot, depending on the OS).
    

#### 🔢 `.count()`

- This extracts the raw **integer value** from the duration — typically measured in **nanoseconds** or **milliseconds** depending on your platform.
    

#### 🔁 `static_cast<std::mt19937::result_type>(...)`

- `std::mt19937::result_type` is the type of values that `mt19937` produces (usually `uint32_t`).
    
- You're **casting** the integer you got from the clock into this type to make sure it matches what the PRNG expects as a seed.
    

#### ✅ Why Use This Form?

- It ensures that the PRNG is seeded with **a dynamic value** based on time (so the sequence changes every time you run).
    
- `static_cast` guarantees **type safety** and ensures you're passing the correct type (`uint32_t`) to the PRNG constructor.

The downside of this approach is that if the program is run several times in quick succession, the seeds generated for each run won’t be that different, which can impact the quality of the random results from a statistical standpoint. For normal programs, this doesn’t matter, but for programs that require high quality, independent results, this method of seeding may be insufficient.

>[!tip]
>`std::chrono::high_resolution_clock` is a popular choice instead of `std::chrono::steady_clock`. `std::chrono::high_resolution_clock` is the clock that uses the most granular unit of time, but it may use the system clock for the current time, which can be changed or rolled back by users. `std::chrono::steady_clock` may have a less granular tick time, but is the only clock with a guarantee that users cannot adjust it.

---
### Seeding with the random device

>The random library contains a type called `std::random_device` that is an implementation-defined PRNG. Normally we avoid implementation-defined capabilities because they have no guarantees about quality or portability, but this is one of the exception cases. Typically `std::random_device` will ask the OS for a pseudo-random number (how it does this depends on the OS).

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
	std::mt19937 mt{ std::random_device{}() };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

In the above program, we’re seeding our Mersenne Twister with one random number generated from a temporary instance of `std::random_device`. If you run this program multiple times, it should also produce different results each time.

One potential problem with `std::random_device`: it isn’t required to be non-deterministic, meaning it _could_, on some systems, produce the same sequence every time the program is run, which is exactly what we’re trying to avoid. There was a [bug in MinGW](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85494) (fixed in GCC 9.2) that would do exactly this, making `std::random_device` useless.

However, the latest versions of the most popular compilers (GCC/MinGW, Clang, Visual Studio) support proper implementations of `std::random_device`.

>[!Best Practice]
>Use `std::random_device` to seed your PRNGs (unless it’s not implemented properly for your target compiler/architecture).

#### Q: What does `std::random_device{}()` mean?

`std::random_device{}` creates a value-initialized temporary object of type `std::random_device`. The `()` then calls `operator()` on that temporary object, which returns a randomized value (which we use as an initializer for our Mersenne Twister)

It’s the equivalent of the calling the following function, which uses a syntax you should be more familiar with:

```cpp
unsigned int getRandomDeviceValue()
{
   std::random_device rd{}; // create a value initialized std::random_device object
   return rd(); // return the result of operator() to the caller
}
```

Using `std::random_device{}()` allows us to get the same result without creating a named function or named variable, so it’s much more concise.

#### Q: If std::random_device is random itself, why don’t we just use that instead of Mersenne Twister?

Because std::random_device is implementation defined, we can’t assume much about it. It may be expensive to access or it may cause our program to pause while waiting for more random numbers to become available. The pool of numbers that it draws from may also be depleted quickly, which would impact the random results for other applications requesting random numbers via the same method. For this reason, std::random_device is better used to seed other PRNGs rather than as a PRNG itself.

---
>[!Best Practice]
>Only seed a given pseudo-random number generator once, and do not reseed it.
```cpp
#include <iostream>
#include <random>

int getCard()
{
    std::mt19937 mt{ std::random_device{}() }; // this gets created and seeded every time the function is called
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}

int main()
{
    std::cout << getCard() << '\n';

    return 0;
}
```

In the `getCard()` function, the random number generator is being created and seeded every time the function is called. This is inefficient at best, and will likely cause poor random results.

---
### Mersenne Twister and underseeding issues

The internal state of a Mersenne Twister requires 19937 bits (2493 bytes), which is 624 32-bit values or 312 64-bit values. As a result, `std::mt19937` allocates 624 integers, whereas `std::mt19937_64` allocates 312 integers.

As an aside…

The integers allocated by `std::mt19937` are defined to be of type `std::uint_fast32_t`, which could be 32-bit or 64-bit integers depending on the architecture. If `std::uint_fast32_t` resolves to a 64-bit integer, `std::mt19937` will use 624 64-bit integers, making it double the size it needs to be.

In the examples above, where we seed our `std::mt19937` from the clock or std::random_device, our seed is only a single integer. This means we’re essentially initializing 624 integers using a single integer, which is significantly underseeding the Mersenne Twister PRNG. The Random library does the best it can to fill in the remaining 623 values with “random” data… but it can’t work magic. Underseeded PRNG can generate results that are suboptimal for applications that need the highest quality results. For example, seeding `std::mt19937` with a single 32-bit value will never generate the number `42` as its first output.

So how do we fix this? As of C++20, there’s no easy way. But we do have some suggestions.

First, let’s talk about `std::seed_seq` (which stands for “seed sequence”). In the prior lesson, we mentioned that ideally we want our seed data to be as many bits as the state of our PRNG, or our PRNG will be underseeded. But in many cases (especially when our PRNG has a large state), we won’t have that many bits of randomized seed data.

`std::seed_seq` is a type that was designed to help with this. We can pass it as many randomized values as we have, and then it will generate as many additional unbiased seed values as needed to initialize a PRNG’s state. If you initialize `std::seed_seq` with a single value (e.g. from `std::random_device`) and then initialize a Mersenne Twister with the `std::seed_seq` object, `std::seed_seq` will generate 623 values of additional seed data. This won’t add randomness, but it will give us a better mix of 0 and 1 bits. However, the more random data we can provide `std::seed_seq`, the better job it will do for us. So the easiest idea is to simply use `std::random_device` to give `std::seed_seq` more data to work with. If we initialize `std::seed_seq` with 8 values from `std::random_device` instead of 1, then the remaining values generated by `std::seed_seq` should be much better:

>[!tip]
>the more random data we can provide `std::seed_seq`, the better job it will do for us. So the easiest idea is to simply use `std::random_device` to give `std::seed_seq` more data to work with. If we initialize `std::seed_seq` with 8 values from `std::random_device` instead of 1, then the remaining values generated by `std::seed_seq` should be much better

```cpp
#include <iostream>
#include <random>

int main()
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

#### Q: Why not give std::seed_seq 624 values from `std::random_device`?

You can, but this is likely to be slow, and risks depleting the pool of random numbers that `std::random_device` uses.

### Warming up a PRNG

>When a PRNG is given a poor quality seed (or underseeded), the initial results of the PRNG may not be high quality. For this reason, some PRNGs benefit from being “warmed up”, which is a technique where the first N results generated from the PRNG are discarded. This allows the internal state of the PRNG to be mixed up such that the subsequent results should be of higher quality. Typically a few hundred to a few thousand initial results are discarded. The longer the period of the PRNG, the more initial results should be discarded.

>[!tip]
>The `seed_seq` initialization used by `std::mt19937` performs a warm up, so we don’t need to explicitly warm up `std::mt19937` objects.

---
### Global Random Numbers

What happens if we want to use a random number generator in multiple functions or files? One way is to create (and seed) our PRNG in our `main()` function, and then pass it everywhere we need it. But that’s a lot of passing for something we may only use sporadically, and in many different places. It would add a lot of clutter to our code to pass such an object around.

Alternately, you could create a static local `std::mt19937` variable in each function that needs it (static so that it only gets seeded once). However, it’s overkill to have every function that uses a random number generator define and seed its own local generator, and the low volume of calls to each generator may lead to lower quality results.

What we really want is a single PRNG object that we can share and access anywhere, across all of our functions and files. The best option here is to create a global random number generator object (inside a namespace!). Remember how we told you to avoid non-const global variables? This is an exception.

Here’s a simple, header-only solution that you can #include in any code file that needs access to a randomized, self-seeded `std::mt19937`:

Random.h:

```cpp
#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
```

>[!Important]
>An **algorithm** is a finite sequence of instructions that can be followed to solve some problem or produce some useful result. An algorithm is considered to be **stateful** if it retains some information across calls. Conversely, a **stateless** algorithm does not store any information (and must be given all the information it needs to work with when it is called). When applied to algorithms, the term **state** refers to the current values held in stateful variables.

>[!important]
>An algorithm is considered **deterministic** if for a given input (the value provided for `start`) it will always produce the same output sequence.

>[!important]
>A **pseudo-random number generator (PRNG)** is an algorithm that generates a sequence of numbers whose properties simulate a sequence of random numbers. When a PRNG is instantiated, an initial value (or set of values) called a **random seed** (or **seed** for short) can be provided to initialize the state of the PRNG. When a PRNG has been initialized with a seed, we say it has been **seeded**. The size of the seed value can be smaller than the size of the state of the PRNG. When this happens, we say the PRNG has been **underseeded**. The length of the sequence before a PRNG begins to repeat itself is known as the **period**.

