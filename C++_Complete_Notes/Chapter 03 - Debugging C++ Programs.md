### std::cerr 
>When printing information for debugging purposes, use `std::cerr` instead of `std::cout`. One reason for this is that `std::cout` may be buffered, which means a bit of time may pass between when you ask `std::cout` to output text and when it actually does. If you output using `std::cout` and then your program crashes immediately afterward, `std::cout` may or may not have actually output yet. This can mislead you about where the issue is. On the other hand, `std::cerr` is unbuffered, which means anything you send to it will output immediately. This helps ensure all debug output appears as soon as possible (at the cost of some performance, which we usually don’t care about when debugging).
Using `std::cerr` also helps make clear that the information being output is for an error case rather than a normal case.

## Tip

When adding temporary debug statements, it can be helpful to not indent them. This makes them easier to find for removal later.

If you are using clang-format to format your code, it will try to auto-indent these lines. You can suppress the automatic formatting like this:

```cpp
// clang-format off
std::cerr << "main() called\n";
// clang-format on
```

### Why using printing statements to debug isn’t great

While adding debug statements to programs for diagnostic purposes is a common rudimentary technique, and a functional one (especially when a debugger is not available for some reason), it’s not that great for a number of reasons:

1. Debug statements clutter your code.
2. Debug statements clutter the output of your program.
3. Debug statements require modification of your code to both add and to remove, which can introduce new bugs.
4. Debug statements must be removed after you’re done with them, which makes them non-reusable.
### Logger

[plog](https://www.learncpp.com/cpp-tutorial/more-debugging-tactics/#:~:text=Using%20a%20logger,as%20spdlog.)

#### 1. **Include the Headers**

```cpp
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

```
#### 2. **Initialize the Logger**

```cpp
plog::init(plog::debug, "Logfile.txt");

```
#### 3. **Log Your Messages**

```cpp
PLOGD << "main() called";

```

- `PLOGD` is a macro that logs a **debug** message.

### Setting Up **Plog** Logging Library in C++ (with VS Code)

### ✅ 1. Download and Extract Plog

- Go to the [Plog GitHub repo](https://github.com/SergiusTheBest/plog).
    
- Click the green **Code** button → **Download ZIP**.
    
- Unzip it somewhere on your system, for example:
    
    swift
    
    CopyEdit
    
    `/home/subhan/plog-master/`
    

---

### ✅ 2. Tell the Compiler Where to Find Plog Headers

- When compiling your C++ file, add this to your compile command:
    
    bash
    
    CopyEdit
    
    `-I/home/subhan/plog-master/include`
    
- Example `g++` command:
    
    bash
    
    CopyEdit
    
    `g++ -I/home/subhan/plog-master/include main.cpp -o main`
    

---

### ✅ 3. Fix IntelliSense in VS Code (for Auto-complete, Error Checking, etc.)

- Press `Ctrl + Shift + P` → Select **C/C++: Edit Configurations (UI)**.
    
- Under the **"Include path"** section, add:
    
    ruby
    
    CopyEdit
    
    `${workspaceFolder}/** /home/subhan/plog-master/include`
    
- 🔴 **Important**: Do **not** use double quotes (`"`) around paths in the UI. Just plain paths.
    

---

### 💡 Notes:

- `c_cpp_properties.json` is used by the C/C++ extension in VS Code for IntelliSense — it doesn’t affect compilation, only things like:
    
    - Red squiggles under `#include`
        
    - Auto-completion
        
    - Go to definition, etc.
        
- The compiler needs the `-I` flag separately.
    

### For VS Code users

When you first ran your program, a new file called _tasks.json_ was created under the _.vscode_ folder in the explorer pane. Open the _tasks.json_ file, find _“args”_, and then locate the line _“${file}”_ within that section.

Above the _“${file}”_ line, add a new line containing the following command (one per line) when debugging:  
`"-ggdb",`

Above the _“${file}”_ line, add new lines containing the following commands (one per line) for release builds:  
`"-O2",`  
`"-DNDEBUG",`

### Setup Debugger in Vs code studio
>To set up debugging, press _Ctrl+Shift+P_ and select “C/C++: Add Debug Configuration”, followed by “C/C++: g++ build and debug active file”. This should create and open the `launch.json` configuration file. Change the “stopAtEntry” to true:  
`"stopAtEntry": true,`

Then open _main.cpp_ and start debugging by pressing _F5_ or by pressing _Ctrl+Shift+P_ and selecting “Debug: Start Debugging and Stop on Entry”.

### Problem of buffered while debugging
std::cout is buffered, which means there may be a delay between when you ask std::cout to print a value, and when it actually does. Because of this, you may not see the value 5 appear at this point. To ensure that all output from std::cout is output immediately, you can temporarily add the following statement to the top of your main() function:

```cpp
std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
```


For performance reasons, this statement should be removed or commented out after debugging.

If you don’t want to continually add/remove/comment/uncomment the above, you can wrap the statement in a conditional compilation preprocessor directive.

```cpp
#ifdef DEBUG
std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
#endif
```

You’ll need to make sure the DEBUG preprocessor macro is defined, either somewhere above this statement, or as part of your compiler settings.

### How Call Stack is useful?
>The call stack is useful in conjunction with breakpoints, when your breakpoint is hit and you want to know what functions were called to get to that specific point in the code.

### [# 3.10 — Finding issues before they become problems](https://www.learncpp.com/cpp-tutorial/finding-issues-before-they-become-problems/)

### **static analysis tools**
>Programmers tend to make certain kinds of common mistakes, and some of those mistakes can be discovered by programs trained to look for them. These programs, generally known as **static analysis tools** (sometimes informally called _linters_) are programs that analyze your source code to identify specific semantic issues (in this context, _static_ means that these tools analyze the source code without executing it). The issues found by static analysis tools may or may not be the cause of any particular problem you are having, but may help point out fragile areas of code or issues that can be problematic in certain circumstances.

You already have one static analysis tool at your disposal -- your compiler! In addition to ensuring your program is syntactically correct, most modern C++ compilers will do some light static analysis to identify some common problems. For example, many compilers will warn you if you try to use a variable that has not been initialized. If you haven’t already, turning up your compiler warning and error levels (see lesson [0.11 -- Configuring your compiler: Warning and error levels](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-warning-and-error-levels/)) can help surface these.

[Many static analysis tools exist](https://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis#C,_C++), some of which can identify over 300 types of programming errors. On our small academic programs, use of a static analysis tool is optional, but using one may help you find areas where your code is non-compliant with best practices. On large programs, use of a static analysis tool is highly recommended, as it can surface tens or hundreds of potential issues.

Best practice

Use a static analysis tool on your programs to help find areas where your code is non-compliant with best practices.

### Chapter 3 Summary 

[Summary](https://www.learncpp.com/cpp-tutorial/chapter-3-summary-and-quiz/)

### Problem in Quiz chapter 3 Question 2

```cpp
#include <iostream>

using namespace std;

  

int readNumber()

{

std::cout << "Please enter a number: ";

int x {};

std::cin >> x;

return x;

}

  

void writeAnswer(int x)

{

std::cout << "The quotient is: " << x << '\n';

}

  

int main()

{

int x{ };

int y{ };

x = readNumber();

y = readNumber();

writeAnswer(x/y);

  

return 0;

}

```

## 📌 **Question:**

> In my C++ program, `x` is declared inside both `main()` and `readNumber()`. Since they are in different scopes, why does it seem like `main`’s `x` changes when I assign a value to `x` inside `readNumber()`?
> 
> Also, while debugging, the watch window shows that `main`’s `x` value changes **when `readNumber()` sets its own `x = 0`**, even before the return. Why is that?

---

## 📘 **Key Concepts:**

### ✅ **Variable Scope**

- Each function has its **own local variables**.
    
- `x` in `main()` and `x` in `readNumber()` are **completely separate variables**.
    
- They may have the **same name**, but exist in **different scopes** and **different stack frames**.
    

---

### ✅ **How Values Are Passed**

- When you do:
    
    cpp
    
    CopyEdit
    
    `x = readNumber();`
    
    - `readNumber()` returns a value.
        
    - That value is **copied into** `x` in `main()` after the function call ends.
        

---

### ✅ **Why It Looks Like `main()`'s `x` Changes Early**

- In debug mode, it **may appear** as though `main`'s `x` is changing when `readNumber()`'s `x` is set — but that’s likely due to:
    
    1. **The debugger reusing memory addresses** for local variables (optimization).
        
    2. Or **watch expressions being ambiguous**, especially if both variables are named `x`.
        

---

## 🔄 **Compiler Optimization and Stack Reuse**

- Local variables from different functions with **non-overlapping lifetimes** might use the **same memory address**.
    
- This is a **safe and efficient optimization** since the variables don't exist at the same time.
    
- That's why you may see both `x`s share the same address in the debugger.
    

---

### 🧪 **How to Check This Yourself**

Add this code to see addresses:

cpp

CopyEdit

`int readNumber() {     int x {};     std::cout << "Address of x in readNumber: " << &x << '\n';     std::cin >> x;     return x; }  int main() {     int x {};     std::cout << "Address of x in main: " << &x << '\n';     x = readNumber(); }`

If both addresses match, it confirms the **memory reuse**.

---

## 🛠️ **Best Practices to Avoid Confusion**

- Use **different variable names** in different scopes (e.g., `num`, `input`, etc.).
    
- Use **scoped watch variables** like `main::x` or `readNumber::x` (if supported in your IDE).
    
- Understand that the debugger might **show misleading behavior** due to optimization or reuse.

