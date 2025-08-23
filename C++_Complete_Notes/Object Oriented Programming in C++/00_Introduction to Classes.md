---

---

---
# Introduction to Object Oriented Programming

### Procedural Programming

>Up to now, we’ve been doing a type of programming called procedural programming. In **procedural programming**, the focus is on creating “procedures” (which in C++ are called functions) that implement our program logic. We pass data objects to these functions, those functions perform operations on the data, and then potentially return a result to be used by the caller.

In procedural programming, the functions and the data those functions operate on are separate entities. The programmer is responsible for combining the functions and the data together to produce the desired result. This leads to code that looks like this:

```cpp
eat(you, apple);
```

Now, take a look around you -- everywhere you look are objects: books and buildings and food and even you. Such objects have two major components to them: 1) Some number of associated properties (e.g. weight, color, size, solidity, shape, etc…), and 2) Some number of behaviors that they can exhibit (e.g. being opened, making something else hot, etc…). These properties and behaviors are inseparable.

In programming, properties are represented by objects, and behaviors are represented by functions. And thus, procedural programming represents reality fairly poorly, as it separates properties (objects) and behaviors (functions).

### What is object-oriented programming?

>OOP is a **programming paradigm** (a style of writing programs) where the main focus is on **objects**.

An **object** is basically:

- **Data (properties / attributes)** → things the object _has_
    
- **Behaviors (methods / functions)** → things the object _can do_
    

Instead of just writing functions and variables separately, we **group them together** into objects that represent real-world entities.

>Example:

In procedural programming (non-OOP), you might do this:

```cpp
eat(you, apple);  // function takes parameters
```

But in OOP, you attach the behavior to the object:

```cpp
you.eat(apple);   // object 'you' performs the action
```

Here:

- `you` → the object (subject)
    
- `eat()` → the behavior (method of the object `you`)
    
- `apple` → another object being interacted with
    

This way, the code is more natural and intuitive, like describing a real-world action.

>**Why is OOP useful?**

- **Modularity** → Each object is a self-contained unit (data + functions).
    
- **Reusability** → You can reuse objects in different programs or projects.
    
- **Maintainability** → Easier to update or fix code since related things are grouped together.
    
- **Abstraction** → You can hide unnecessary details and expose only what matters.
    
- **Intuitive** → Mirrors how humans think about real-world entities.

>[!Summary]
>👉 So in summary:  
**OOP = bundling data + behavior into objects**.

### A procedural vs OOP-like example

>Procedural Example:

```cpp
#include <iostream>
#include <string_view>

enum AnimalType
{
    cat,
    dog,
    chicken,
};

constexpr std::string_view animalName(AnimalType type)
{
    switch (type)
    {
    case cat: return "cat";
    case dog: return "dog";
    case chicken: return "chicken";
    default:  return "";
    }
}

constexpr int numLegs(AnimalType type)
{
    switch (type)
    {
    case cat: return 4;
    case dog: return 4;
    case chicken: return 2;
    default:  return 0;
    }
}


int main()
{
    constexpr AnimalType animal{ cat };
    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

    return 0;
}
```

 ✅ How it works:

- You represent animals using an **enum `AnimalType`**.
    
- Then you write **separate functions** (`animalName`, `numLegs`) to get information about that enum.
    
- Adding a new animal (e.g., `snake`) means:
    
    1. Add it to the enum
        
    2. Update **every function** that switches on `AnimalType`
        
    3. Possibly update any other logic that depends on `AnimalType`.
        

👉 This becomes harder to maintain as the program grows, because changing _one thing_ (new animal) requires updating _many places_.

>OOP Example:

```cpp
struct Cat {
    std::string_view name{ "cat" };
    int numLegs{ 4 };
};

struct Dog {
    std::string_view name{ "dog" };
    int numLegs{ 4 };
};

struct Chicken {
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
};

int main() {
    constexpr Cat animal;
    std::cout << "a " << animal.name 
              << " has " << animal.numLegs << " legs\n";
}
```

 ✅ How this works:

- Each animal is its own **type** (struct).
    
- Each type contains its **own data members** (`name`, `numLegs`).
    
- No big `switch` statements, no central `enum`—just **encapsulation**: each type manages its own info.
    
- Adding a new animal (say `Snake`) is simple:

```cpp
struct Snake {
    std::string_view name{ "snake" };
    int numLegs{ 0 };
};
```

And then in `main`:

```cpp
constexpr Snake animal;
```

That’s it. No need to touch `Cat`, `Dog`, `Chicken`, or other code.

> 🔹 Key Advantages of OOP Approach

1. **Encapsulation**
    
    - Each animal “knows” its own properties.
        
    - No need for external functions (`animalName()`, `numLegs()`) to look them up.
        
2. **Extensibility**
    
    - Adding new animals doesn’t break existing code.
        
    - You just add a new type.
        
3. **Flexibility**
    
    - You can customize individual animals.
        
    - Example:

```cpp
struct Chicken {
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
    int wormsPerDay{ 10 }; // unique to chickens
};
```

>[!Warning]
>In the procedural model, _every animal_ would be forced to have `wormsPerDay`, even if it doesn’t make sense.

### OOP brings other benefits to the table

- In **school assignments**, your code is often “one-and-done”:
    
    - You write it, test it, submit it.
        
    - Nobody cares about maintaining or extending it later.
        
- In the **real world** (working in a company or on open-source projects):
    
    - Your code **lives on**.
        
    - Other developers will read it, extend it, fix it.
        
    - Users will find bugs.
        
    - New features will be requested.
        
    - Operating system or library updates might break it.
        

👉 Therefore, code needs to be **evolvable, modular, and easy to maintain**.

>**Why OOP Helps:**

It emphasizes **modularity** (breaking things into self-contained objects) and **reusability** (using existing objects without rewriting).

To achieve this, OOP introduces four powerful principles:

- Inheritance
- encapsulation
- abstraction
- polymorphism

>🔹 Important Takeaway

- **OOP doesn’t replace procedural programming**.
    
- Think of it as **extra tools in your toolbox**.
    
- For small scripts: procedural may be simpler.
    
- For larger systems: OOP’s encapsulation, abstraction, inheritance, and polymorphism help keep code **manageable and future-proof**.

>[!Summary]
>OOP isn’t just about “objects” — it’s about **designing code that can survive in the real world**: easy to extend, easy to fix, and safe from breaking when things change.

### The term "object"

>Note that the term “object” is overloaded a bit, and this causes some amount of confusion. In traditional programming, an object is a piece of memory to store values. And that’s it. In object-oriented programming, an “object” implies that it is both an object in the traditional programming sense, and that it combines both properties and behaviors. We will favor the traditional meaning of the term object in these tutorials, and prefer the term “class object” when specifically referring to OOP objects.

---
# Introduction to classes

>As useful as structs are, structs have a number of deficiencies that can present challenges when trying to build large, complex programs (especially those worked on by multiple developers).

### The class invariant problem

>In the context of class types (which include structs, classes, and unions), a **class invariant** is a condition that must be true throughout the lifetime of an object in order for the object to remain in a valid state. An object that has a violated class invariant is said to be in an **invalid state**, and unexpected or undefined behavior may result from further use of that object.

 >🔹 What is a Class Invariant?

- **Invariant** = a condition that must **always** hold true for an object to be valid.
    
- If the invariant is broken → the object is in an **invalid state**, and using it may cause **bugs or undefined behavior**.

>[!Rule]
>Using an object whose class invariant has been violated may result in unexpected or undefined behavior.

>First, consider the following struct:

```cpp
struct Pair
{
    int first {};
    int second {};
};
```

The `first` and `second` members can be independently set to any value, so `Pair` struct has no invariant.

>Now consider the following almost-identical struct:

```cpp
struct Fraction
{
    int numerator { 0 };
    int denominator { 1 };
};
```

We know from mathematics that a fraction with a denominator of `0` is mathematically undefined. Therefore, we want to ensure the `denominator` member of a Fraction object is never set to `0`. If it is, then that Fraction object is in an invalid state, and undefined behavior may result from further use of that object.

>For Example:

```cpp
#include <iostream>

struct Fraction
{
    int numerator { 0 };
    int denominator { 1 }; // class invariant: should never be 0
};

void printFractionValue(const Fraction& f)
{
     std::cout << f.numerator / f.denominator << '\n';
}

int main()
{
    Fraction f { 5, 0 };   // create a Fraction with a zero denominator
    printFractionValue(f); // cause divide by zero error

    return 0;
}
```

In the above example, we used comment to document that using 0 in denominator will make set the object to invalid state and also we have given default value 1 so that if user doesn't provide initialization value then it will be set to 1 not 0 which will set it to invalid state.
But it doesnt protect the object to be explicitly set to 0.

And that is exactly what we see later, when we call `printFractionValue(f)`: the program terminates due to a divide-by-zero error.

>We can put assertion in print function but it doesnt solve the problem because before printing the object it was already in invalid state and it doesnt fix the problem.

Given the relative simplicitly of the Fraction example, it shouldn’t be too difficult to simply avoid creating invalid Fraction objects. However, in a more complex code base that uses many structs, structs with many members, or structs whose members have complex relationships, understanding what combination of values might violate some class invariant may not be so obvious.

### A more complex class invariant

- A **class invariant** is a rule that must always hold true for an object to be valid.
    
- For `Fraction`, it was simple: `denominator != 0`.
    
- For `Employee`, the invariant is more complex because **two members are related**.

>🔹 The Employee Problem:

```cpp
struct Employee
{
    std::string name { };
    char firstInitial { }; // should always be first char of name
};
```

Expected Invariant:

- `firstInitial == name[0]` (or `0` if the name is empty).
    

❌ Problem:

- With this `struct`, **the user is responsible** for keeping `firstInitial` in sync.
    

Example:

```cpp
Employee e { "Alice", 'A' };   // okay
e.name = "Bob";                // 🚨 forgot to update firstInitial
std::cout << e.firstInitial;   // still 'A', invalid object!
```

Now the object is in an **invalid state** because its invariant (`firstInitial == name[0]`) was broken.

>🔹 Why Is This Harder?

- The `Fraction` invariant only involved **one member** (`denominator != 0`).
    
- Here, the invariant involves **two correlated members** (`name` and `firstInitial`).
    
- That means whenever **one changes, the other must change too**.
    
- If the user forgets → object becomes invalid.
    

👉 **Key insight:** _If maintaining an invariant requires the user to “remember” something, it will eventually break._

>🔹 Why Structs Are Bad for This

- Structs (used as plain aggregates) have:
    
    - Public members, directly modifiable.
        
    - No built-in mechanism to **enforce relationships** between members.
        

Even if you add helper functions (like `setName(Employee&, std::string)`), the user can still bypass them and directly modify `e.name`.

So invariants that require **coordinated updates** across multiple members are **unsafe in plain structs**.

==Structs (as aggregates) just don’t have the mechanics required to solve this problem in an elegant way.

### classes

>Just like structs, a **class** is a program-defined compound type that can have many member variables with different types.

>[!Key Insight]
>From a technical standpoint, structs and classes are almost identical -- therefore, any example that is implemented using a struct could be implemented using a class, or vice-versa. However, from a practical standpoint, we use structs and classes differently.

>Because a class is a program-defined data type, it must be defined before it can be used. Classes are defined similarly to structs, except we use the `class` keyword instead of `struct`. For example, here is a definition for a simple employee class:

```cpp
class Employee
{
    int m_id {};
    int m_age {};
    double m_wage {};
};
```

To demonstrate how similar classes and structs can be, the following program is equivalent to the one we presented at the top of the lesson, but `Date` is now a class instead of a struct:

```cpp
#include <iostream>

class Date       // we changed struct to class
{
public:          // and added this line, which is called an access specifier
    int m_day{}; // and added "m_" prefixes to each of the member names
    int m_month{};
    int m_year{};
};

void printDate(const Date& date)
{
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year;
}

int main()
{
    Date date{ 4, 10, 21 };
    printDate(date);

    return 0;
}
```
class is by default private, which we will cover soon.

>[!Key Insight]
>You have already been using class objects, perhaps without knowing it. Both `std::string` and `std::string_view` are defined as classes. In fact, most of the non-aliased types in the standard library are defined as classes!
Classes are really the heart and soul of C++ -- they are so foundational that C++ was originally named “C with classes”! Once you are familiar with classes, much of your time in C++ will be spent writing, testing, and using them.

---
# Member Functions

### The separation of properties and actions

>Take a look around you -- everywhere you look are objects: books and buildings and food and even you. Real-life objects have two major components to them: 1) Some number of observable properties (e.g. weight, color, size, solidity, shape, etc…), and 2) Some number of actions that they can perform or have performed on them (e.g. being opened, damaging something else, etc…) based on those properties. These properties and actions are inseparable.

In programming, we represent properties with variables, and actions with functions.

>In the `Date` example above, note that we have defined our properties (the member variables of `Date`) and the actions we perform using those properties (the function `print()`) separately. We are left to infer a connection between `Date` and `print()` based solely on the `const Date&` parameter of `print()`.

While we could put both `Date` and `print()` into a namespace (to make it clearer that the two are meant to be packaged together), that adds yet more names into our program and more namespace prefixes, cluttering our code.

It sure would be nice if there were some way to define our properties and actions together, as a single package.

### Member functions

>In addition to having member variables, class types (which includes structs, classes, and unions) can also have their own functions! Functions that belong to a class type are called **member functions**.

>[!Aside]
>In other object-oriented languages (such as Java and C#), these are called **methods**.

Functions that are not member functions are called non-member functions.

>[!Important]
>Member functions must be declared inside the class type definition, and can be defined inside or outside of the class type definition. As a reminder, a definition is also a declaration, so if we define a member function inside the class, that counts as a declaration.

> --> Example of member function:

Let’s rewrite the `Date` example from the top of the lesson, converting `print()` from a non-member function into a member function:

```cpp
// Member function version
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // defines a member function named print
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    return 0;
}
```
2020/10/16

### Member functions are declared inside the class type defination

>In the non-member example, the `print()` non-member function is defined outside of the `Date` struct, in the global namespace. By default, it has external linkage, so it could be called from other source files (with the appropriate forward declaration).

In the member example, the `print()` member function is declared (and in this case, defined) inside the `Date` struct definition. Because `print()` is declared as part of the `Date`, this tells the compiler that `print()` is a member function.

Member functions defined inside the class type definition are implicitly inline, so they will not cause violations of the one-definition rule if the class type definition is included into multiple code files.

>**Member**: It’s “built into” the `Date` type. Since all code that sees `Date` must see the same definition, C++ allows `inline` to make this safe.

### Calling member functions (and the implicit object)

>In the non-member example, we call `print(today)`, where `today` is (explicitly) passed as an argument.

In the member example, we call `today.print()`. This syntax, which uses the member selection operator (.) to select the member function to call, is consistent with how we access member variables (e.g. `today.day = 16;`).

All (non-static) member functions must be called using an object of that class type. In this case, `today` is the object that `print()` is being called on.

Note that in the member function case, we don’t need to pass `today` as an argument. The object that a member function is called on is _implicitly_ passed to the member function. For this reason, the object that a member function is called on is often called **the implicit object**.

In other words, when we call `today.print()`, `today` is the implicit object, and it is implicitly passed to the `print()` member function.

### Accessing members inside a member function uses the implicit object

>With non-member functions, we have to explicitly pass an object to the function to work with, and members are explicitly accessed through that object.

```cpp
// non-member version of print
void print(const Date& date)
{
    // member variables accessed using member selection operator (.)
    std::cout << date.year << '/' << date.month << '/' << date.day;
}
```

>With member functions, we implicitly pass an object to the function to work with, and members are implicitly accessed through that object.

```cpp
void print() // defines a member function named print()
{
    std::cout << year << '/' << month << '/' << day;
}
```

In other words, when `today.print()` is called, `today` is our implicit object, and `year`, `month`, and `day` (which are not prefixed) evaluate to the values of `today.year`, `today.month`, and `today.day` respectively.

### Another member function example

>Here’s an example with a slightly more complex member function:

```cpp
#include <iostream>
#include <string>

struct Person
{
    std::string name{};
    int age{};

    void kisses(const Person& person)
    {
        std::cout << name << " kisses " << person.name << '\n';
    }
};

int main()
{
    Person joe{ "Joe", 29 };
    Person kate{ "Kate", 27 };

    joe.kisses(kate);

    return 0;
}
```
Joe kisses Kate

When the `kisses()` member function executes, the identifier `name` doesn’t use the member selection operator (.), so it refers to the implicit object, which is `joe`. So this resolves to `joe.name`. `person.name` uses the member selection operator, so it does not refer to the implicit object. Since `person` is a reference for `kate`, this resolves to `kate.name`.

>[!Key Insight]
>Without a member function, we would have written `kisses(joe, kate)`. With a member function, we write `joe.kisses(kate)`. Note how much better the latter reads, and how it makes clear exactly which object is initiating the action and which is in support.

### Member variables and functions can be defined in any order

>In **normal C++ code** (outside a class), the compiler reads top to bottom.

If you try to call a function before it has been **declared**, you get an error:

```cpp
int x() {
    return y();  // ❌ Error: y not declared yet
}

int y() {
    return 5;
}
```

To fix this, we either:

- reorder functions, or
    
- use a **forward declaration**.

>🔹 Inside a class (OOP world):

**Different rule applies.**  
When you are inside a class/struct definition, the compiler treats **all member names as if they are already declared**, even if you define them later.

So this works:

```cpp
struct Foo
{
    int z() { return m_data; }   // ✅ can use member variable before it's declared
    int x() { return y(); }      // ✅ can use member function before it's declared

    int m_data { y() };          // ✅ even works in default initializer (but careful!)
    int y() { return 5; }
};
```

Why?  
Because the **class definition is parsed as a whole**, and the compiler already knows that `m_data` and `y()` are members of `Foo` before it checks the body of each member.

>[!Warning]
>Members are **initialized in the order of declaration**, not in the order you write them in initializers.
>
>Example of **bad usage**:
```cpp
struct Bad
{
    int m_bad1 { m_data }; // ❌ UB: m_bad1 initialized before m_data exists
    int m_bad2 { fcn() };  // ❌ UB: calls fcn() before m_data initialized

    int m_data { 5 };
    int fcn() { return m_data; }
};
```
>[!Warning]
>Even though it looks like `m_bad1` is using `m_data`, at runtime `m_bad1` is initialized **first** (because it appears first in the declaration list). Since `m_data` doesn’t have a value yet, this is **undefined behavior**.

--> Compile time process:

>when the compiler encounters this:

```cpp
struct Foo
{
    int z() { return m_data; } // m_data not declared yet
    int x() { return y(); }    // y not declared yet
    int y() { return 5; }

    int m_data{};
};
```

>It will compile the equivalent of this:

```cpp
struct Foo
{
    int z(); // forward declaration of Foo::z()
    int x(); // forward declaration of Foo::x()
    int y(); // forward declaration of Foo::y()

    int m_data{};
};

int Foo::z() { return m_data; } // m_data already declared above
int Foo::x() { return y(); }    // y already declared above
int Foo::y() { return 5; }
```

### Member functions can be overloaded

>Just like non-member functions, member functions can be overloaded, so long as each member function can be differentiated.

>[!Best Practice]
>Member functions can be used with both structs and classes.
>However, structs should avoid defining constructor member functions, as doing so makes them a non-aggregate.

>[!Tip]
>If your class type has no data members, prefer using a namespace.

---
# Const class objects and const member functions

>class type objects (struct, classes, and unions) can also be made const by using the `const` keyword. Such objects must also be initialized at the time of creation.

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};
};

int main()
{
    const Date today { 2020, 10, 14 }; // const class type object

    return 0;
}
```

Just like with normal variables, you’ll generally want to make your class type objects const (or constexpr) when you need to ensure they aren’t modified after creation.

### Modifying the data members of const objects is disallowed

>Once a const class has been initialized then we cannot modify the values of its member even if its member function is changing its own member value, it is disallowed.

Example:

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay()
    {
        ++day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.day += 1;        // compile error: can't modify member of const object
    today.incrementDay();  // compile error: can't call member function that modifies member of const object

    return 0;
}
```

### Const objects may not call non-const member functions

>You may be surprised to find that this code also causes a compilation error:

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // compile error: can't call non-const member function

    return 0;
}
```

Even though `print()` does not try to modify a member variable, our call to `today.print()` is still a const violation. This happens because the `print()` member function itself is not declared as const. The compiler won’t let us call a non-const member function on a const object.

### Const member functions

>To address the above issue, we need to make `print()` a const member function. A **const member function** is a member function that guarantees it will not modify the object or call any non-const member functions (as they may modify the object).

Making `print()` a const member function is easy -- we simply append the `const` keyword to the function prototype, after the parameter list, but before the function body:

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now a const member function
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // ok: const object can call const member function

    return 0;
}
```

In the above example, `print()` has been made a const member function, which means we can call it on const objects (such as `today`).

==A const member function that attempts to change a data member or call a non-const member function will cause a compiler error to occur. For example:

```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay() const // made const
    {
        ++day; // compile error: const function can't modify member
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.incrementDay();

    return 0;
}
```

In this example, `incrementDay()` has been marked as a const member function, but it attempts to change `day`. This will cause a compiler error.

>[!Key Insight]
>A const member function may not: modify the implicit object, call non-const member functions.  
A const member function may: modify objects that aren’t the implicit object, call const member functions, call non-member functions.

==In C++, when you mark a **member function** as `const`, you’re not saying the _function itself_ is constant — you’re saying the function promises **not to modify the object it’s called on**.
That’s why the `const` qualifier goes **after** the parameter list

### Const member functions may be called on non-const objects

Const member functions may also be called on non-const objects.

```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // non-const

    today.print();  // ok: can call const member function on non-const object

    return 0;
}
```

>[!Best Practice]
>A member function that does not (and will not ever) modify the state of the object should be made const, so that it can be called on both const and non-const objects.

### Const objects via pass by const reference

>When you pass an object to a function by **const reference** (`const Date& date`), that function promises **not to modify the passed object**.

That means:

- Inside `doSomething`, `date` is effectively a **const Date object**.
    
- And on **const objects**, you are only allowed to call **const member functions** (those that promise not to modify the object).
    

So if `print()` is not declared `const`, the compiler says:

> "I can’t guarantee that `print()` won’t change the object. Since `date` is const, I can’t allow this call."

>[!Error]
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // non-const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```

>[!Fix]
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```

>[!Analogy]
>Think of it like lending your friend your diary:
>>- If you lend it with `const` → you’re saying: _“You can read it, but don’t write in it.”_
>>- If you don’t use `const` → they might change it.

### Member function const and non-const overloading

>Finally, although it is not done very often, it is possible to overload a member function to have a const and non-const version of the same function. This works because the const qualifier is considered part of the function’s signature, so two functions which differ only in their const-ness are considered distinct.

```cpp
#include <iostream>

struct Something
{
    void print()
    {
        std::cout << "non-const\n";
    }

    void print() const
    {
        std::cout << "const\n";
    }
};

int main()
{
    Something s1{};
    s1.print(); // calls print()

    const Something s2{};
    s2.print(); // calls print() const

    return 0;
}
```

This prints:

non-const
const

---
# Public and private members and access specifiers

>[!Important Analogy]
>Let’s say you’re walking down the street on a brisk autumn day, eating a burrito. You want somewhere to sit, so you look around. To your left is a park, with mowed grass and shade trees, a few uncomfortable benches, and screaming kids on the nearby playground. To your right is a stranger’s residence. Through the window, you see a comfy reclining chair and a crackling fireplace.
With a heavy sigh, you choose the park.
The key determinant for your choice is that the park is a public space, whereas the residence is private. You (and anyone else) are allowed to freely access public spaces. But only the members of the residence (or those given explicit permission to enter) are permitted to access the private residence.

### Member access

>A similar concept applies to the members of a class type. Each member of a class type has a property called an **access level** that determines who can access that member.

C++ has three different access levels: _public_, _private_, and _protected_.

>Whenever a member is accessed, the compiler checks whether the access level of the member permits that member to be accessed. If the access is not permitted, the compiler will generate a compilation error. This access level system is sometimes informally called **access controls**.

### The member of a struct are public  by default

>Members that have the _public_ access level are called _public members_. **Public members** are members of a class type that do not have any restrictions on how they can be accessed. Much like the park in our opening analogy, public members can be accessed by anyone (as long as they are in scope).

>🔹 Access Specifiers in C++

In C++, **struct** and **class** differ mainly in **default access control**:

- **struct** → members are **public** by default.
    
- **class** → members are **private** by default.
    

That means if you don’t explicitly write `public:` or `private:`, the compiler assumes the default based on whether you’re using `struct` or `class`.

>🔹 Public Members

When something is **public**, it can be accessed:

1. By **member functions** of the same struct/class.
    
2. By **non-member functions** (code outside the class).
    
3. By **other class types**.


>🔹 “The Public”

The phrase **“the public”** in this context means **any code that is not inside the struct/class itself**.

- This includes non-member functions like `main()`
    
- Or functions in other classes.
    

So when `main()` accesses `today.day` or calls `today.print()`, it’s the **public** accessing **public members**.

-->Example:

```cpp
#include <iostream>

struct Date
{
    // struct members are public by default, can be accessed by anyone
    int year {};       // public by default
    int month {};      // public by default
    int day {};        // public by default

    void print() const // public by default
    {
        // public members can be accessed in member functions of the class type
        std::cout << year << '/' << month << '/' << day;
    }
};

// non-member function main is part of "the public"
int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    // public members can be accessed by the public
    today.day = 16; // okay: the day member is public
    today.print();  // okay: the print() member function is public

    return 0;
}
```

In this example, members are accessed in three places:

- Within member function `print()`, we access the `year`, `month`, and `day` members of the implicit object.
- In `main()`, we directly access `today.day` to set its value.
- In `main()`, we call member function `today.print()`.

### The member of a class are private by default

>Members that have the _private_ access level are called _private members_. **Private members** are members of a class type that can only be accessed by other members of the same class.

Consider the following example, which is almost identical to the one above:

```cpp
#include <iostream>

class Date // now a class instead of a struct
{
    // class members are private by default, can only be accessed by other members
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can be accessed in member functions
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

    // private members can not be accessed by the public
    today.m_day = 16; // compile error: the m_day member is private
    today.print();    // compile error: the print() member function is private

    return 0;
}
```

In this example, members are accessed in the same three places:

- Within member function `print()`, we access the `m_year`, `m_month`, and `m_day` members of the implicit object.
- In `main()`, we directly access `today.m_day` to set its value.
- In `main()`, we call member function `today.print()`.

>However, if you compile this program, you will note that three compilation errors are generated.

Within `main()`, the statements `today.m_day = 16` and `today.print()` now both generate compilation errors. This is because `main()` is part of the public, and the public is not allowed to directly access private members.

Within `print()`, access to members `m_year`, `m_month`, and `m_day` is allowed. This is because `print()` is a member of the class, and members of the class are allowed to access private members.

>[!Key Insight]
>The members of a class are private by default. Private members can be accessed by other members of the class, but can not be accessed by the public.
A class with private members is no longer an aggregate, and therefore can no longer use aggregate initialization.

### Naming your private member variables

>[!Best Practice]
>Consider naming your private data members starting with an “m_” prefix to help distinguish them from the names of local variables, function parameters, and member functions.
Public members of classes may also follow this convention if desired. However, the public members of structs typically do not use this prefix since structs generally do not have many member functions (if any).

### Setting access levels via access specifiers

>By default, the members of structs (and unions) are public, and the members of classes are private.

However, we can explicitly set the access level of our members by using an **access specifier**. An access specifier sets the access level of _all members_ that follow the specifier. C++ provides three access specifiers: `public:`, `private:`, and `protected:`.

In the following example, we use both the `public:` access specifier to make sure the `print()` member function can be used by the public, and the `private:` access specifier to make our data members private.

```cpp
class Date
{
// Any members defined here would default to private

public: // here's our public access specifier

    void print() const // public due to above public: specifier
    {
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }

private: // here's our private access specifier

    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main()
{
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
```

This example compiles. Because `print()` is a public member due to the `public:` access specifier, `main()` (which is part of the public) is allowed to access it.

>Because we have private members, we can not aggregate initialize `d`. For this example, we’re using default member initialization instead (as a temporary workaround).

| Access level | Access specifier | Member access | Derived class access | Public access |
| ------------ | ---------------- | ------------- | -------------------- | ------------- |
| Public       | public:          | yes           | yes                  | yes           |
| Protected    | protected:       | yes           | yes                  | no            |
| Private      | private:         | yes           | no                   | no            |

### Access level best practice for structs and classes

>[!Best Practice]
>Classes should generally make member variables private (or protected), and member functions public.
Structs should generally avoid using access specifiers (all members will default to public).

### Access levels work on a per-class basis

>One nuance of C++ access levels that is often missed or misunderstood is that access to members is defined on a per-class basis, not on a per-object basis.

You already know that a member function can directly access private members (of the implicit object). However, because access levels are per-class, not per-object, a member function can also directly access the private members of ANY other object of the same class type that is in scope.

Let’s illustrate this with an example:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name{};

public:
    void kisses(const Person& p) const
    {
        std::cout << m_name << " kisses " << p.m_name << '\n';
    }

    void setName(std::string_view name)
    {
        m_name = name;
    }
};

int main()
{
    Person joe;
    joe.setName("Joe");

    Person kate;
    kate.setName("Kate");

    joe.kisses(kate);

    return 0;
}
```

This prints:

Joe kisses Kate

There are a few things to note here.

First, `m_name` has been made private, so it can only be accessed by members of the `Person` class (not the public).

Second, because our class has private members, it is not an aggregate, and we can’t use aggregate initialization to initialize our Person objects. As a workaround (until we cover a proper solution to this issue), we’ve created a public member function named `setName()` that allows us to assign a name to our Person objects.

==Third, because `kisses()` is a member function, it has direct access to private member `m_name`. However, you might be surprised to see that it also has direct access to `p.m_name`! This works because `p` is a `Person` object, and `kisses()` can access the private members of any `Person` object in scope!

### The technical and practical difference between structs and classes

>A class defaults its members to private, whereas a struct defaults its members to public.

In practice, we use structs and classes differently.

As a rule of thumb, use a struct when all of the following are true:

- You have a simple collection of data that doesn’t benefit from restricting access.
- Aggregate initialization is sufficient.
- You have no class invariants, setup needs, or cleanup needs.

A few examples of where structs might be used: constexpr global program data, a point struct (a simple collection of int members that don’t benefit from being made private), structs used to return a set of data from a function.

Use a class otherwise.

We want our structs to be aggregates. So if you use any capabilities that makes your struct a non-aggregate, you should probably be using a class instead (and following all of the best practices for classes).

---
# Access functions

>An **access function** is a trivial public member function whose job is to retrieve or change the value of a private member variable for that object.

--> Getters returns the private member variable and setters set the private member variable value.

==Getters are usually made const, so they can be called on both const and non-const objects. Setters should be non-const, so they can modify the data members.

>Example:

```cpp
#include <iostream>

class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter for year
    void setYear(int year) { m_year = year; }     // setter for year

    int getMonth() const  { return m_month; }     // getter for month
    void setMonth(int month) { m_month = month; } // setter for month

    int getDay() const { return m_day; }          // getter for day
    void setDay(int day) { m_day = day; }         // setter for day
};

int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}
```
The year is: 2021

>[!Tip]
Use a “set” prefix on your setters to make it more obvious that they are changing the state of the object.

### Getters should return by value or by const lvalue reference

>[!Best Practice]
>Getters should provide “read-only” access to data. Therefore, the best practice is that they should return by either value (if making a copy of the member is inexpensive) or by const lvalue reference (if making a copy of the member is expensive).

### Access functions concerns

>🔹 The concern with access functions

The idea of OOP is that a class should represent **behavior**, not just a bag of data.  
If you start writing getters and setters for every private member, your class becomes like a `struct` in disguise — you’re just exposing data indirectly, which goes against _encapsulation_. (We will conver it soon!)

That’s why many developers argue:  
👉 “If you need tons of getters/setters, maybe your design is wrong.”

#### 🔹 The pragmatic approach (from the text)

1. **If your class has no invariants** (no rules about what values its members must follow)  
    → and you find yourself writing accessors for everything → maybe just use a `struct` with public members.  
    Example:

```cpp
struct Point {
    int x{};
    int y{};
};
```

Here, getters/setters would add no real value.

2. **Prefer behaviors over accessors**  
    Instead of raw `get`/`set`, think about _actions_.  
    Example:  
    ❌ `setAlive(false)`  
    ✅ `kill()`  
    ❌ `setAlive(true)`  
    ✅ `revive()`
    
    Why? Because `kill()` and `revive()` are meaningful operations in the context of a game. They also leave room for logic (e.g., when killed, drop inventory, play animation, etc.), while `setAlive(false)` is just a dumb data assignment.

3. **Only provide accessors when they make sense**
	Sometimes, you _do_ need them. For example:

```cpp
class BankAccount {
private:
    double balance{};
public:
    double getBalance() const { return balance; }  // makes sense, public needs it
    void deposit(double amount) { balance += amount; }  
};
```
Here, `getBalance()` is natural — clients of `BankAccount` will reasonably need to know the balance.

#### 🔑 Key insight

- **Accessors are not evil** → but overusing them can turn your class into a glorified `struct`.
    
- **Good design** favors meaningful actions (methods) over exposing raw data.
    
- Use accessors only when _outside code actually needs to know or modify a value_.


>[!Note]
>Access functions refers to getters and setters member functions!

---
# Member functions returning references to data members

>Member functions can also return by reference, and they follow the same rules for when it is safe to return by reference as non-member functions. However, member functions have one additional case we need to discuss: member functions that return data members by reference.

This is most commonly seen with getter access functions, so we’ll illustrate this topic using getter member functions. But note that this topic applies to any member function returning a reference to a data member.

### Returning data members by value can be expensive

```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	std::string getName() const { return m_name; } //  getter returns by value
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}
```

In this example, the `getName()` access function returns `std::string m_name` by value.

While this is the safest thing to do, it also means that an expensive copy of `m_name` will be made every time `getName()` is called. Since access functions tend to be called a lot, this is generally not the best choice.

### Returning data members by lvalue reference

>Member functions can also return data members by (const) lvalue reference.

```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
```

Now when `joe.getName()` is invoked, `joe.m_name` is returned by reference to the caller, avoiding having to make a copy. The caller then uses this reference to print `joe.m_name` to the console.

Because `joe` exists in the scope of the caller until the end of the `main()` function, the reference to `joe.m_name` is also valid for the same duration.

>[!Key Insight]
>It is okay to return a (const) lvalue reference to a data member. The implicit object (containing the data member) still exists in the scope of the caller after the function returns, so any returned references will be valid.

### The return type of a member function returning a reference to a data member should match the data member’s type

#### 1. The main idea

When you write a **getter** that returns a **reference to a member variable**, the **return type should match the actual member variable’s type**.

Why?  
Because otherwise, C++ might need to create **temporary objects** or **do implicit conversions**, which are unnecessary and inefficient.

#### 2. Example: matching return type

```cpp
class Employee
{
    std::string m_name{}; // actual member type

public:
    const std::string& getName() const { return m_name; } // ✅ matches member type
};
```

- `m_name` is a `std::string`.
    
- Getter returns `const std::string&`.
    
- Caller gets a reference to the actual `m_name`, no copy, no extra work.

#### 3. Example: mismatch return type

```cpp
class Employee
{
    std::string m_name{};

public:
    std::string_view getName() const { return m_name; } // ⚠️ mismatch
};
```

- `m_name` is a `std::string`.
    
- `std::string_view` is a different type.
    
- Each call to `getName()` has to construct a temporary `std::string_view` from `m_name`.
    
- This is extra overhead. Worse, if the member wasn’t a `std::string` (say, a temporary), the `string_view` could dangle (point to invalid memory).

#### 4. Using `auto` return type

```cpp
class Employee
{
    std::string m_name{};

public:
    const auto& getName() const { return m_name; } // type deduced as std::string
};
```

- This guarantees the return type always matches `m_name`.
    
- No mismatch possible, no extra conversions.
    

But… from a **documentation/readability** perspective:

- A programmer reading just `const auto& getName()` doesn’t know whether `m_name` is `std::string`, `std::vector<int>`, or anything else.
    

So, while **`auto` helps avoid mistakes**, it makes the code slightly harder to understand at first glance.

#### 5. Best practice

- If the member type is **obvious and stable** (like `std::string m_name`), prefer **explicit return type** for clarity:

```cpp
const std::string& getName() const { return m_name; }
```

- If the member type might **change in the future**, or you want **absolute type-safety** without conversions, `auto&` is useful:

```cpp
const auto& getName() const { return m_name; }
```

### Rvalue implicit objects and return by reference

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e;
	e.setName(name);
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member

	return 0;
}
```

#### 🔑 First, the setup

- **Rvalue** = temporary object (like the return value of a function that returns by value).
    
- **Lvalue** = named object that persists beyond the current expression (like a variable you declared).
    
- **Full expression** = everything between two `;` or similar sequence points. When the full expression ends, all temporaries created in it are destroyed.
    

So if a function returns by **value**, the object it returns is a temporary **rvalue** that lives only until the end of that full expression.

#### 🚩 The danger

If you call a method on an rvalue object and that method returns a **reference to one of its members**, that reference points **into the rvalue’s guts**. Once the rvalue is destroyed, the reference dangles (becomes invalid). Using it afterward is undefined behavior.

#### The 3 cases in your code

##### **Case 1: Immediate use (Safe)**

```cpp
std::cout << createEmployee("Frank").getName();
```

- `createEmployee("Frank")` returns a temporary `Employee`.
    
- `.getName()` returns a `const std::string&` to its `m_name`.
    
- We immediately pass that reference to `std::cout`.
    
- After the statement finishes (end of full expression), the rvalue `Employee` is destroyed.  
    ✅ Safe, because the reference was only used _before_ destruction.

##### **Case 2: Save reference for later (Dangling, UB)**

```cpp
const std::string& ref { createEmployee("Garbo").getName() };
std::cout << ref; // ❌ Undefined behavior
```

- `createEmployee("Garbo")` gives an rvalue `Employee`.
    
- `.getName()` returns a reference to its `m_name`.
    
- That reference (`ref`) points inside the temporary `Employee`.
    
- As soon as the full expression (the initialization of `ref`) ends, the temporary `Employee` is destroyed, leaving `ref` dangling.
    
- Later, when we use `ref`, we’re accessing freed memory.  
    🚨 Undefined behavior.

##### **Case 3: Copy value instead of storing reference (Safe)**

```cpp
std::string val { createEmployee("Hans").getName() };
std::cout << val; // ✅ Safe
```

- Same as Case 2, except `val` is a **copy** of the string, not a reference.
    
- The `std::string` inside the temporary rvalue is copied into `val`.
    
- After the temporary `Employee` is destroyed, `val` remains valid.  
    ✅ Safe, because `val` owns its own data.

👉 A good rule of thumb:  
If a function returns by reference, be careful when calling it on an rvalue. Unless you use the result immediately, **copy it**.

>[!Warning]
>An rvalue object is destroyed at the end of the full expression in which it is created. Any references to members of the rvalue object are left dangling at that point.
A reference to a member of an rvalue object can only be safely used within the full expression where the rvalue object is created.

#### Two const difference

- The **first const** protects the **returned value** (caller can’t modify `m_name` through the returned reference).
    
- The **second const** protects the **object itself** (the function promises not to modify the object when called).

### Using member functions that return by reference safely

>[!Best Practice]
>Prefer to use the return value of a member function that returns by reference immediately, to avoid issues with dangling references when the implicit object is an rvalue.

### Do not return non-const references to private data members

Because a reference acts just like the object being referenced, a member function that returns a non-const reference provides direct access to that member (even if the member is private).

For example:

```cpp
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() { return m_value; } // returns a non-const reference (don't do this)
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value(); // prints 5

    return 0;
}
```

Because `value()` returns a non-const reference to `m_value`, the caller is able to use that reference to directly access (and change the value of) `m_value`.

==This allows the caller to subvert the access control system.

### Const member functions can’t return non-const references to data members

#### 📌 Rule in C++

A **`const` member function** promises:

1. It will not modify any non-`mutable` data members.
    
2. It will not call any non-`const` member functions (since they might modify the object).
    

Now imagine if such a function returned a **non-const reference** to a data member.

```cpp
#include <string>
#include <iostream>

class Employee {
    std::string m_name{"Joe"};

public:
    const std::string& getNameConst() const { return m_name; } // ✅ okay
    std::string& getNameBad() const { return m_name; }         // ❌ not allowed
};

int main() {
    const Employee e{};

    // Fine, because getNameConst returns const reference
    std::cout << e.getNameConst() << '\n';

    // If this were allowed:
    // e.getNameBad() = "Changed";  // 🚨 modifies e.m_name even though e is const!
}
```

If `getNameBad()` were allowed, we’d be able to mutate `m_name` **through a const object** — completely breaking the guarantee that `const` means "this object cannot change".

#### Strange case

```cpp
#include <string>
#include <iostream>

class Employee {
    std::string m_name{"Joe"};

public:
    auto& getName() const { return m_name; } // <-- looks like it should work?
};
```

>At first glance, it seems this should **return a non-const reference** to `m_name`.  
But in reality, the compiler **adds const** automatically during type deduction because the function itself is `const`.

- The function body is considered as operating on a **const Employee**.
    
- Therefore, inside the function, `m_name` is seen as a **const std::string**.
    
- So `auto&` deduces to `const std::string&`, not `std::string&`.

In other words:

```cpp
auto& getName() const { return m_name; }
```

is **equivalent to**:

```cpp
const std::string& getName() const { return m_name; }
```

---
# The benefits of data hiding (Encapsulation)

>we mentioned that the member variables of a class are typically made private. Programmers who are learning about classes for the first time often have a hard time understanding why you’d want to do this. After all, making your variables private means they can’t be accessed by the public. At best, this makes for more work when writing your classes. At worst, it may seem completely pointless (especially if we’re providing public access functions to the private member data).

The answer to this question is so foundational that we’re going to spend an entire lesson on the topic!

>[!Analogy]
>In modern life, we have access to many mechanical or electronic devices. You turn your TV on/off with a remote control. You make your car move forward by pressing the gas pedal. You turn on your lights by flipping a switch. All of these devices have something in common: They provide a simple user interface (a set of buttons, a pedal, a switch, etc…) that allows you to perform key actions.
How these devices actually operate is hidden away from you. When you press the button on your remote control, you don’t need to know how the remote is communicating with your TV. When you press the gas pedal on your car, you don’t need to know how the combustion engine makes the wheels turn. When you take a picture, you don’t need to know how the sensors gather light and turn that light into a pixelated image.
This separation of interface and implementation is extremely useful because it allows us to use objects without having to understand how they work -- instead, we only have to understand how to interact with them. This vastly reduces the complexity of using these objects, and increases the number of objects we’re capable of interacting with.

### Implementation and interfaces in class types

#### 🔹 1. What is the **interface** of a class?

- The **interface** is _how the outside world interacts_ with the class.
    
- In C++, that means the **public members**:
    
    - public functions (getters, setters, behaviors, actions)
        
    - sometimes public constants or types
        

👉 Think of it like the **remote control** for a TV:

- Buttons (public functions) = what you’re allowed to press.
    
- You don’t care how the TV processes signals internally.
    

Example:

```cpp
class TV {
public:
    void turnOn();
    void turnOff();
    void changeChannel(int channel);
};
```

Here:

- `turnOn`, `turnOff`, `changeChannel` = **interface**
    
- A user of `TV` doesn’t need to know _how_ they’re implemented.

#### 🔹 2. What is the implementation of a class?

The implementation is how things actually work under the hood.

This includes:

private data members (e.g. bool m_powerOn, int m_channel)

the code inside the member function bodies

Example:

```cpp
class TV {
private:
    bool m_powerOn{false};
    int m_channel{1};

public:
    void turnOn() { m_powerOn = true; }
    void turnOff() { m_powerOn = false; }
    void changeChannel(int channel) { m_channel = channel; }
};
```

Here:

- `m_powerOn`, `m_channel` and the logic inside functions = **implementation**
    
- A user of `TV` doesn’t need to know these exist.

### Data hiding

#### **1. What is Data Hiding?**

- **Definition:**  
    Data hiding means making the _implementation details_ (like how data is stored and manipulated internally) **inaccessible to users** of a class.
    
- **How:**
    
    - Mark **data members** as `private` → users can’t touch them directly.
        
    - Provide **public member functions** to interact with those data members → users must go through the class interface.
        

So instead of:

```cpp
person.name = "Ali";   // directly changing internals
```

You do:

```cpp
person.setName("Ali");  // via public interface
```

#### **2. Why do we do this?**

- Prevents misuse: Users can’t directly corrupt the internal state.
    
- Flexibility: You can change how the data is stored internally (implementation) without breaking outside code that only relies on the interface.
    
- Encapsulation: Bundles data + behaviors into one logical unit.

#### **3. Classes vs Structs**

- **Classes:**  
    Should use data hiding → by default, members are `private`. They’re meant for more structured, safe, reusable code.
    
- **Structs:**  
    By convention, structs in C++ **don’t** use data hiding (their members are usually `public` by default). Structs are good for _plain old data (POD)_, like:

```cpp
struct Point {
    int x{};
    int y{};
};
```

- No hidden logic, just data storage.

#### **Encapsulation**

🔹 **Concept:**  
Encapsulation is about **wrapping/bundling data and the functions that operate on that data into a single unit (class)**.

- Example:

```cpp
class Player {
    int health {};              // data
public:
    void takeDamage(int d) {    // function operating on data
        health -= d;
    }
};
```

Here, `health` + `takeDamage` live together in **one class** → that’s encapsulation.

✅ Key idea: Encapsulation is about **packaging** (data + behavior together).  
It does **not necessarily mean hiding anything**.

#### **Data Hiding**

🔹 **Concept:**  
Data hiding is about **restricting access** to internal details so they can’t be misused. It’s achieved using **access specifiers** (`private`, `protected`) in C++.

- Example (data hidden):

```cpp
class Player {
private:
    int health {};  // hidden

public:
    void takeDamage(int d) {   // controlled access
        health -= d;
    }
};
```

Now, outsiders **cannot directly access** `health`.

✅ Key idea: Data hiding is about **protection** (controlling what can and cannot be accessed).

#### **Relationship**

- Encapsulation = **putting things in a box** (class with data + methods).
    
- Data hiding = **locking the box** (restricting direct access to internal stuff).
    

👉 Encapsulation is possible **without** data hiding:

```cpp
struct Player {      // struct members are public by default
    int health {};   // not hidden
    void takeDamage(int d) {
        health -= d;
    }
};
```

This is still encapsulation (data + method bundled), but no data hiding (user can do `player.health = -1000;`).

==👉 Data hiding **requires encapsulation** (you need a class/struct to hide data inside).

>In this tutorial series, we’ll assume all encapsulated classes implement data hiding.

#### 🔑 Final Truth

- **Encapsulation** can exist **without data hiding**.
    
- **Data hiding cannot exist without encapsulation** (since you need a class to hide things inside).

### Data hiding make classes easier to use, and reduces complexity

**Data hiding (achieved via encapsulation) shields the internal details of a class so the user only sees the interface, not the messy implementation behind it.**

This makes the class:

1. **Easier to use** – because you don’t need to know “how it works,” just “how to use it.”
    
2. **Less error-prone** – because users can’t accidentally mess with internal details.
    
3. **Less complex** – because you only need to learn a small, clean set of public functions.

>Example:

```cpp
#include <iostream>
#include <string_view>

int main()
{
    std::string_view sv{ "Hello, world!" };
    std::cout << sv.length(); // prints 13
}
```

- **What you see (Interface)**:
    
    - You can create a `std::string_view`.
        
    - You can call `sv.length()` to get the length.
        
- **What you don’t see (Implementation)**:
    
    - How `std::string_view` stores the pointer and size of the string.
        
    - How `length()` is calculated internally.
        
    - What private members exist, their names, or their types.
        

👉 As a user, you **don’t need to care**. You just rely on the **public interface**.

#### 🔹 Why this matters

Imagine if you had to understand all the internals of `std::string`, `std::vector`, or `std::cout` before you could use them… 🤯

- Your programs would be insanely complicated.
    
- You’d spend hours reading internal implementation details instead of focusing on solving your problem.
    

Instead, **encapsulation + data hiding** give you a clean, safe interface — you only need to know:

- Which functions exist,
    
- What parameters they take,
    
- What values they return.
    

That’s it.

✅ **Bottom line:**  
**Data hiding reduces complexity** because it allows you to work with classes as _black boxes_. You don’t care about _how they work inside_, only _what they can do for you_.

### Data hiding allows us to maintain invariants

```cpp
#include <iostream>
#include <string>

struct Employee // members are public by default
{
    std::string name{ "John" };
    char firstInitial{ 'J' }; // should match first initial of name

    void print() const
    {
        std::cout << "Employee " << name << " has first initial " << firstInitial << '\n';
    }
};

int main()
{
    Employee e{}; // defaults to "John" and 'J'
    e.print();

    e.name = "Mark"; // change employee's name to "Mark"
    e.print(); // prints wrong initial

    return 0;
}
```

>Explanation:

#### 🔹 What’s an **invariant**?

- An **invariant** is a condition that must **always hold true** for an object to remain in a valid state.
    
- For example, in your `Employee` class:

```cpp
std::string name;
char firstInitial;  // invariant: should always match first letter of name
```

- 👉 The invariant is: `firstInitial == name[0]`.  
    If this condition breaks, the object is in an **invalid or inconsistent state**.

#### 🔹 Problem with public members (no data hiding)

In the **struct version**:

```cpp
Employee e{};
e.name = "Mark";  // name changes, but firstInitial is still 'J'
```

- Because `name` is public, users of the class can directly modify it.
    
- But when they do so, **they forget to update** `firstInitial`.
    
- Result: The invariant (`firstInitial == name[0]`) is broken.
    
- Now, `print()` produces a **wrong output**.
    

⚠️ This means that the correctness of your program depends on the **user remembering internal rules** — which is error-prone.

#### 🔹 Solution with data hiding

In the **class version**:

```cpp
class Employee {
    std::string m_name{};
    char m_firstInitial{};

public:
    void setName(std::string_view name) {
        m_name = name;
        m_firstInitial = name.front();
    }
};
```

- The data members are now **private**.
    
- The user can’t touch them directly.
    
- The only way to set a name is via `setName()`.
    
- And `setName()` **enforces the invariant** by updating both `m_name` and `m_firstInitial`.
    

✅ Result:

- Invariants are **automatically maintained**.
    
- The user can’t mess it up even accidentally.
    
- Complexity is reduced, and reliability is increased.

#### 🔹 Why data hiding helps maintain invariants

1. **Prevents direct access** → Users can’t bypass your logic.
    
2. **Centralizes updates** → All changes go through your controlled functions.
    
3. **Automatic enforcement** → Invariants stay true without user effort.

### Data hiding allows us to do better error detection (and handling)

>In the above program, the invariant that `m_firstInitial` must match the first character of `m_name` exists because `m_firstInitial` exists independently of `m_name`. We can remove this particular invariant by replacing data member `m_firstInitial` with a member function that returns the first initial:

```cpp
#include <iostream>
#include <string>

class Employee
{
    std::string m_name{ "John" };

public:
    void setName(std::string_view name)
    {
        m_name = name;
    }

    // use std::string::front() to get first letter of `m_name`
    char firstInitial() const { return m_name.front(); }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << firstInitial() << '\n';
    }
};

int main()
{
    Employee e{}; // defaults to "John"
    e.setName("Mark");
    e.print();

    return 0;
}
```

However, this program has another class invariant. Take a moment and see if you can determine what it is. We’ll wait here and watch this dry paint…

The answer is that `m_name` shouldn’t be an empty string (because every `Employee` should have a name). If `m_name` is set to an empty string, nothing bad will happen immediately. But if `firstInitial()` is then called, the `front()` member of `std::string` will try to get the first letter of the empty string, and that leads to undefined behavior.

Ideally, we’d like to prevent `m_name` from ever being empty.

If the user had public access to the `m_name` member, they could just set `m_name = ""`, and there’s nothing we can do to prevent that from happening.

However, because we’re forcing the user to set `m_name` through the public interface function `setName()`, we can have `setName()` validate that the user has passed in a valid name. If the name is non-empty, then we can assign it to `m_name`. If the name is an empty string, we can do any number of things in response:

- Ignore the request to set the name to “” and return to the caller.
- Assert out.
- Throw an exception.

The point here is that we can detect the misuse, and then handle it however we think is most appropriate. How we best handle such cases effectively is a topic for another day.

### Data hiding makes it possible to change implementation details without breaking existing programs

Consider this simple example:

```cpp
#include <iostream>

struct Something
{
    int value1 {};
    int value2 {};
    int value3 {};
};

int main()
{
    Something something;
    something.value1 = 5;
    std::cout << something.value1 << '\n';
}
```

While this program works fine, what would happen if we decided to change the implementation details of the class, like this?

```cpp
#include <iostream>

struct Something
{
    int value[3] {}; // uses an array of 3 values
};

int main()
{
    Something something;
    something.value1 = 5;
    std::cout << something.value1 << '\n';
}
```

We haven’t covered arrays yet, but don’t worry about that. The point here is that this program no longer compiles because the member named `value1` no longer exists, and a statement in `main()` is still using that identifier.

Data hiding gives us the ability to change how classes are implemented without breaking the programs that use them.

Here is the encapsulated version of the original version of this class that uses functions to access `m_value1`:

```cpp
#include <iostream>

class Something
{
private:
    int m_value1 {};
    int m_value2 {};
    int m_value3 {};

public:
    void setValue1(int value) { m_value1 = value; }
    int getValue1() const { return m_value1; }
};

int main()
{
    Something something;
    something.setValue1(5);
    std::cout << something.getValue1() << '\n';
}
```

Now, let’s change the class’s implementation back to an array:

```cpp
#include <iostream>

class Something
{
private:
    int m_value[3]; // note: we changed the implementation of this class!

public:
    // We have to update any member functions to reflect the new implementation
    void setValue1(int value) { m_value[0] = value; }
    int getValue1() const { return m_value[0]; }
};

int main()
{
    // But our programs that use the class do not need to be updated!
    Something something;
    something.setValue1(5);
    std::cout << something.getValue1() << '\n';
}
```

Because we did not change the public interface of the class, our program that uses that interface did not need to change at all, and still functions identically.

Analogously, if gnomes snuck into your house at night and replaced the internals of your TV remote with a different (but compatible) technology, you probably wouldn’t even notice!

### Classes with interfaces are easier to debug

And finally, encapsulation can help you debug a program when something goes wrong. Often when a program does not work correctly, it is because one of our member variables has been given an incorrect value. If everyone is able to set the member variable directly, tracking down which piece of code actually modified the member variable to the wrong value can be difficult. This can involve breakpointing every statement that modifies the member variable -- and there can be lots of them.

However, if a member can only be changed through a single member function, then you can simply breakpoint that single function and watch as each caller changes the value. This can make it much easier to determine who the culprit is.

### Prefer non-member functions to member functions 

#### 🔹 Key Idea

>In C++, **not every function that uses a class needs to be a member of that class**.  
If a function can be written **without direct access** to private data, it’s usually better to make it a **non-member function**.

#### 🔹 Why prefer non-member functions?

Here are the main reasons (with explanations):

1. **Smaller class interface**
    
    - Member functions become part of the **public interface**.
        
    - The bigger the interface, the more complex the class is to understand and maintain.
        
    - By keeping functions outside when possible, your class stays lean.
        
2. **Better encapsulation while hiding the implementaion detail**
    
    - Non-member functions can only use the class’s **public interface** (like getters/setters).
        
    - They can’t "cheat" by directly touching private data, so they enforce good encapsulation.
    
	- If `m_flavor` later changes to `m_tasteProfile` or `enum class Flavor`, `print()` breaks.
    
	- The class is now **less flexible**, because external logic (printing) is coupled to internal data.
        
3. **Less coupling**
    
    - If you later change the internal implementation of the class, non-member functions don’t need to be revisited (as long as the public interface stays the same).
        
    - Member functions might need changes because they are tied to the internals.
        
4. **Flexibility & reusability**
    
    - Non-member functions can be **customized per application** without modifying the class itself.
        
    - Example: different programs might want to print `Yogurt` differently — this is easy if `print()` is non-member.
        
5. **Easier to debug**
    
    - Non-member functions are just free functions. They are easier to isolate and test compared to member functions that are entangled with class internals.

>[!Best Practice]
>Prefer implementing functions as non-members when possible (especially functions that contain application specific data or logic).

>Let’s illustrate this with three similar examples, in order from worst to best:

```cpp
#include <iostream>
#include <string>

class Yogurt
{
    std::string m_flavor{ "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }

    // Worst: member function print() uses direct access to m_flavor when getter exists
    void print() const
    {
        std::cout << "The yogurt has flavor " << m_flavor << '\n';
    }
};

int main()
{
    Yogurt y{};
    y.setFlavor("cherry");
    y.print();

    return 0;
}
```

The above is the worst version. The `print()` member function directly accesses `m_flavor` when a getter for the flavor already exists. If the class implementation is ever updated, `print()` will also probably need to be modified. The string printed by `print()` is application-specific (another application using this class may want to print something else, which will require cloning or modifying the class).

```cpp
#include <iostream>
#include <string>

class Yogurt
{
    std::string m_flavor{ "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }

    // Better: member function print() has no direct access to members
    void print(std::string_view prefix) const
    {
        std::cout << prefix << ' ' << getFlavor() << '\n';
    }
};

int main()
{
    Yogurt y{};
    y.setFlavor("cherry");
    y.print("The yogurt has flavor");

    return 0;
}
```

The above version is better, but still not great. `print()` is still a member function, but at least it now does not directly access any data members. If the class implementation is ever updated, `print()` will need to be evaluated to determine whether it needs an update (but it will not). The prefix for the `print()` function is now parameterized, which allows us to move the prefix into non-member function `main()`. But the function still imposes constraints on how things are printed (e.g. it always prints as prefix, space, flavor, newline). If that does not meet the needs of a given application, another function will need to be added.

```cpp
#include <iostream>
#include <string>

class Yogurt
{
    std::string m_flavor{ "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }
};

// Best: non-member function print() is not part of the class interface
void print(const Yogurt& y)
{
        std::cout << "The yogurt has flavor " << y.getFlavor() << '\n';
}

int main()
{
    Yogurt y{};
    y.setFlavor("cherry");
    print(y);

    return 0;
}
```

The above version is the best. `print()` is now a non-member function. It does not directly access any members. If the class implementation ever changes, `print()` will not need to be evaluated at all. Additionally, each application can provide it’s own `print()` function that prints exactly how that application wants to.

#### 🔹 When to use member vs non-member?

✅ **Use a member function when**:

- It must be (e.g. constructors, destructors, virtual functions, operators like `operator[]`).
    
- The function needs **direct access** to private/protected data.
    
- The function is essential to the "identity" of the class (e.g. `push_back()` in `std::vector`).
    

✅ **Use a non-member function when**:

- The function can be implemented entirely using the public interface.
    
- The function is more about **application logic** than core functionality of the class.
    
- You want to keep the class’s interface small and clean.

### The order of class member declaration

>When writing code outside of a class, we are required to declare variables and functions before we can use them. However, inside a class, this limitation does not exist. As noted in lesson [14.3 -- Member functions](https://www.learncpp.com/cpp-tutorial/member-functions/), we can order our members in any order we like.

So how should we order them?

>[!Best Practice]
>Declare public members first, protected members next, and private members last. This spotlights the public interface and de-emphasizes implementation details.

>[!Define Encapsulation]
>Encapsulation in C++ is a fundamental principle of Object-Oriented Programming (OOP) that involves bundling data (attributes) and the methods (functions) that operate on that data into a single unit, known as a class. This concept serves two primary purposes:
>
>>- **Data Hiding:** Encapsulation allows for the protection of sensitive data within a class by restricting direct external access. This is achieved by declaring data members as `private` or `protected`, making them inaccessible from outside the class. Access and modification of this hidden data are then controlled through public methods (often called "getter" and "setter" methods). This prevents unintended or unauthorized manipulation of the object's internal state. 
>>-  **Modularity and Organization:** By grouping related data and functions within a class, encapsulation promotes a more organized and modular code structure. Each class represents a self-contained unit, responsible for its own data and behavior. This improves code readability, maintainability, and reusability, as changes within one encapsulated unit are less likely to impact other parts of the program.

#### Where _abstraction_ fits in here

The lesson is essentially teaching **abstraction through data hiding.**

1. **Interface vs Implementation**
    
    - The **interface** = the _public functions_ of the class. This is what the _user of the class_ sees and uses.
        
    - The **implementation** = the _private members and function bodies_ that actually make the class work.
        
    
    Abstraction means: _you only care about the interface, not the implementation details_.
    
    Example from the lesson:

```cpp
std::string_view sv{ "Hello, world!" };
std::cout << sv.length();
```

2. **Data hiding (information hiding / data abstraction)**

	- By making data members `private`, the class **forces users to interact only through the interface.**
    
	- This _hides complexity_ (users don’t deal with invariants, validation, etc.).
    

	Example from the lesson with `Employee`:

	- **Without data hiding (struct):** the user can directly change `name` and break invariants (`firstInitial` doesn’t update).
    
	- **With data hiding (class):** user must call `setName()`, and the function ensures invariants are preserved.
    

→ Abstraction = the user doesn’t worry about how `setName` maintains invariants. They just know “I can set a name.”

3. **Why this is abstraction in OOP terms**

	- In OOP, abstraction = _present only the essential features, hide unnecessary details_.
    
	- This lesson shows exactly that:
    
	    - The **essential features** are the public functions (`setName`, `getValue1`, etc.).
        
	    - The **hidden details** are the private members and internal logic.
        

By separating **what the class does** (interface) from **how it does it** (implementation), you reduce complexity and let users focus only on the _behavior they need_.

#### 🔑 Encapsulation vs Abstraction in C++

##### **1. Encapsulation**

- **Meaning:** Wrapping _data members_ + _functions that operate on them_ into a single unit (class).
    
- **Focus:** _How things are grouped and protected._
    
- **Mechanism in C++:**
    
    - Access specifiers (`private`, `protected`, `public`)
        
    - Class boundaries
        

👉 Example:

```cpp
class Employee
{
private:
    std::string name;   // hidden
    char firstInitial;  // hidden

public:
    void setName(std::string n)  // exposed
    {
        name = n;
        firstInitial = n.empty() ? '?' : n[0];
    }
};
```

- Data + methods = encapsulated in one unit.
    
- Encapsulation also gives **data hiding** (via `private`).

##### **2. Abstraction**

- **Meaning:** Showing only _essential features_ to the user while hiding unnecessary details.
    
- **Focus:** _What the class does, not how it does it._
    
- **Mechanism in C++:**
    
    - Public interface (functions) vs hidden implementation (private members).
        
    - Also via abstract classes & virtual functions (later).
        

👉 Example with `Employee`:

```cpp
Employee e;
e.setName("John");  // user only cares about "setName"
```

- User doesn’t know (or need to know) how `firstInitial` is maintained.
    
- They only see the abstraction: “set the name”.

##### ✅ How they relate

- **Encapsulation is the tool.**  
    → You put things inside a class and restrict access.
    
- **Abstraction is the outcome.**  
    → The user sees a clean interface and doesn’t worry about the messy details inside.
    

Another way to phrase it:

- Encapsulation = _hiding implementation by restricting access._
    
- Abstraction = _focusing on essential behavior and ignoring implementation._

>[!Summary]
>🔹 Abstraction in OOP
>>**Hiding implementation** → The user doesn’t see the internal details (the “how”).
>>**Providing only an interface** → The user only sees what operations they can perform (the “what”).
>>**Explaining how to use that interface** → Documentation / function names / class design guide the user to interact correctly.
>>

>Example:

```cpp
class Database {
public:
    void connect(std::string_view connStr);
    void executeQuery(std::string_view query);
    void disconnect();
    
private:
    // internal details hidden
    int socketId;
    void authenticate();
    void parseResponse();
};
```

- User only knows **the interface**: `connect()`, `executeQuery()`, `disconnect()`.
    
- They don’t know (or care) about **implementation**: sockets, authentication, parsing.
    
- This is **abstraction**: showing **what can be done**, hiding **how it’s done**.

👉 Encapsulation made it possible (by putting everything inside the class + hiding private parts).  
👉 Abstraction is the _effect_: the user sees only a clean, simplified view.

>Conclusion:

- **Data hiding** → A _mechanism_.
    
    - Achieved by marking members `private` / `protected`.
        
    - Purpose: protect internal state from direct external access.
        
    - Example: `private int balance;`
        
- **Abstraction** → An _effect / design principle_.
    
    - Achieved by exposing only the **necessary interface** (public methods) and **hiding implementation details**.
        
    - Purpose: let users focus on _what_ an object does, not _how_ it does it.
        
    - Example: `deposit()` and `withdraw()` methods, without showing how money is stored internally.

---
# Introduction to constructors

>as soon as we make any member variables private (to hide our data), our class type is no longer an aggregate (because aggregates cannot have private members). And that means we’re no longer able to use aggregate initialization:

>[!Error]
```cpp
class Foo // Foo is not an aggregate (has private members)
{
    int m_x {};
    int m_y {};
};

int main()
{
    Foo foo { 6, 7 }; // compile error: can not use aggregate initialization

    return 0;
}
```

>Not allowing class types with private members to be initialized via aggregate initialization makes sense for a number of reasons:

- Aggregate initialization requires knowing about the implementation of the class (since you have to know what the members are, and what order they were defined in), which we’re intentionally trying to avoid when we hide our data members.
- If our class had some kind of invariant, we’d be relying on the user to initialize the class in a way that preserves the invariant.

### Constructors

>A **constructor** is a special member function that is automatically called after a non-aggregate class type object is created.

When a non-aggregate class type object is defined, the compiler looks to see if it can find an accessible constructor that is a match for the initialization values provided by the caller (if any).

- If an accessible matching constructor is found, memory for the object is allocated, and then the constructor function is called.
- If no accessible matching constructor can be found, a compilation error will be generated.

>[!Key Insight About memory allocation in constructor]
>Many beginners think:
> “When I call a constructor, it creates the object.”
But that’s not quite true.  
>
Actually:
>
>1. **The compiler** creates (allocates) the object.  
>2. **The constructor** just initializes that object’s data members.
>
So the **constructor does not create** the object — it just _prepares_ it.
>
>So the order is:
>
>- **Allocate memory → Call constructor**  
>    NOT:
  >  
>- **Constructor magically creates object**
>
>**so what happens to that allocated memory if constructor isnt found?**
>
>It’s easy to think: “First memory is allocated, then constructor is called, so what happens to the memory if the constructor is missing?”
But here’s the thing:  
That "allocation first" step is only the _conceptual model_.  
If the compiler determines at compile-time that it cannot call a constructor → it **won’t even generate code to allocate the memory**.
So the bad state “allocated but not initialized” never happens in this case — the compiler saves you.

>Beyond determining how an object may be created, constructors generally perform two functions:

- They typically perform initialization of any member variables (via a member initialization list)
- They may perform other setup functions (via statements in the body of the constructor). This might include things such as error checking the initialization values, opening a file or database, etc…

After the constructor finishes executing, we say that the object has been “constructed”, and the object should now be in a consistent, usable state.

Note that aggregates are not allowed to have constructors -- so if you add a constructor to an aggregate, it is no longer an aggregate.

### Naming constructors

Unlike normal member functions, constructors have specific rules for how they must be named:

- Constructors must have the same name as the class (with the same capitalization). For template classes, this name excludes the template parameters.
- Constructors have no return type (not even `void`).

Because constructors are typically part of the interface for your class, they are usually public.

### A basic constructor example

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) // here's our constructor function that takes two initializers
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();

    return 0;
}
```
Foo(6, 7) constructed
Foo(0, 0)

>At runtime, when `foo` is instantiated, memory for `foo` is allocated, and then the `Foo(int, int)` constructor is called with parameter `x` initialized to `6` and parameter `y` initialized to `7`. The body of the constructor function then executes and prints `Foo(6, 7) constructed`.

### Constructor implicit conversion of arguments

>In lesson "Implicit type conversion", we noted that the compiler will perform implicit conversion of arguments in a function call (if needed) in order to match a function definition where the parameters are a different type, its same for constructors:

```cpp
void foo(int, int)
{
}

int main()
{
    foo('a', true); // will match foo(int, int)

    return 0;
}
```

### Constructors should not be const

>A constructor needs to be able to initialize the object being constructed -- therefore, a constructor must not be const.

```cpp
#include <iostream>

class Something
{
private:
    int m_x{};

public:
    Something() // constructors must be non-const
    {
        m_x = 5; // okay to modify members in non-const constructor
    }

    int getX() const { return m_x; } // const
};

int main()
{
    const Something s{}; // const object, implicitly invokes (non-const) constructor

    std::cout << s.getX(); // prints 5

    return 0;
}
```

#### 🔹 Usual rule

Normally in C++:

- If you declare an object as `const`, you **cannot call non-const member functions** on it.  
    Why? → Because those functions might modify the object, and `const` promises immutability.

```cpp
struct Foo {
    void change() { } // non-const
};

int main() {
    const Foo f{};
    f.change(); // ❌ Error: cannot call non-const function on const object
}
```

#### 🔹 Special rule for constructors

But constructors are special.

The standard says:

> _An object is not considered `const` until its constructor has finished running._

That means:

- When a `const` object is **being constructed**, the `const` qualifier is not yet enforced.
    
- The object becomes `const` **only after** the constructor finishes.

#### 🔹 Why?

Because during construction, you **must** initialize and set up the object’s state.  
If `const` applied immediately, you wouldn’t even be able to assign values to its members inside the constructor!

```cpp
struct Foo {
    int x;
    Foo(int val) {
        x = val; // allowed, even if object is const
    }
};

int main() {
    const Foo f{42}; // okay
}
```

If `const` applied immediately, `x = val;` would be illegal.

### Constructors vs setters

Constructors are designed to initialize an entire object at the point of instantiation. Setters are designed to assign a value to a single member of an existing object.

---
# Constructor member initializer lists

### Member initialization via a member initialization list

#### 🔹 What is a _member initialization list_?

A **member initialization list** is a special syntax in constructors that lets you **directly initialize class members** at the moment the object is created.

It looks like this:

```cpp
ClassName(parameters)
    : member1{value1}, member2{value2}, member3{value3}
{
    // constructor body
}
```

Notice:

- Starts with a `:` after the constructor parameter list.
    
- Members are separated by commas `,`.
    
- Uses **direct initialization** (`{}` or `()`), **not** `=`.

#### 🔹 Why not just assign in the constructor body?

Because there is an **important difference** between:

1. **Initialization** (happens before the constructor body runs).
    
2. **Assignment** (happens inside the constructor body, after the member is already initialized with a default value).
    

Example:

```cpp
class Foo {
private:
    int m_x{};
    int m_y{};

public:
    // Constructor using assignment
    Foo(int x, int y) {
        m_x = x; // assignment (m_x was already default-initialized first!)
        m_y = y;
    }

    // Constructor using member initializer list
    Foo(int x, int y)
        : m_x{x}, m_y{y} // direct initialization
    {}
};
```

🔑 Key difference:

- In the first case, `m_x` and `m_y` are **default-initialized first** (to `0` here), and then assigned new values (`x`, `y`).
    
- In the second case, `m_x` and `m_y` are **directly initialized** with `x` and `y`.

>***data members are initialized before the constructor body runs***

Here’s the sequence when you create an object:

1. **Memory allocation** happens for the object.
    
2. **Member initialization list** (if provided) is executed: each member is initialized in the order they are declared in the class (not the order in the list).
    
3. After all members are initialized, **the constructor body runs**.

> Direct initialization avoids creating a “default” value first and then overwriting it.  
    → Faster, especially for expensive objects (like strings, vectors).

### Member initializer list formatting

>The following styles are all valid (and you’re likely to see all three in practice):

```cpp
Foo(int x, int y) : m_x { x }, m_y { y }
{
}
```

```cpp
Foo(int x, int y) :
    m_x { x },
    m_y { y }
{
}
```

```cpp
Foo(int x, int y)
    : m_x { x }
    , m_y { y }
{
}
```

>Our recommendation is to use the third style above.

### Member initialization order

```cpp
#include <algorithm> // for std::max
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // issue on this line
    {
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
```

#### 🔹 Rule in C++

- **Members are always initialized in the order they are defined in the class**, **not** the order you write them in the initializer list.
    
- This is mandated by the C++ standard.

```cpp
class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // LOOKS like m_y before m_x
    {
    }
};

```

- Class definition order:
    
    1. `m_x`
        
    2. `m_y`
        
- So actual initialization order is:
    
    1. `m_x` → initialized first
        
    2. `m_y` → initialized second

#### What goes wrong here

```cpp
: m_y { std::max(x, y) }, m_x { m_y }
```

- Looks like `m_y` is set first, then `m_x`.
    
- But actually, **`m_x` initializes first** → and it tries to copy `m_y`.
    
- But `m_y` isn’t initialized yet → so `m_x` gets garbage (uninitialized value).
    
- Then `m_y` gets the proper value.
    

That’s why you got:

```cpp
Foo(-858993460, 7) // garbage, 7
```

#### 🔹 Best Practices

1. **List initializers in class order**

```cpp
Foo(int x, int y)
    : m_x { std::max(x, y) }, m_y { m_x } // safe
{}
```

- - Now, since `m_x` is defined first in the class, and listed first in the initializer list, it matches.
        
    - `m_x` gets initialized with `std::max(x, y)` first.
        
    - Then `m_y` uses `m_x`.
        
    
    ✅ Safe and predictable.
    
- **Avoid member dependencies if possible**  
    If you don’t rely on one member’s value to initialize another, this problem can’t occur.
    
    Example:

```cpp
Foo(int x, int y)
    : m_x { std::max(x, y) }, m_y { std::max(x, y) }
{}
```

- Both members independently initialized.
        
- No dependency → no surprises.

>[!Best Practice]
>Member variables in a member initializer list should be listed in order that they are defined in the class.

### Member initializer list vs default member initializers

Members can be initialized in a few different ways:

- If a member is listed in the member initializer list, that initialization value is used
- Otherwise, if the member has a default member initializer, that initialization value is used
- Otherwise, the member is default-initialized.

This means that if a member has both a default member initializer and is listed in the member initializer list for the constructor, the member initializer list value takes precedence.

Here’s an example showing all three initialization methods:

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};    // default member initializer (will be ignored)
    int m_y { 2 }; // default member initializer (will be used)
    int m_z;      // no initializer

public:
    Foo(int x)
        : m_x { x } // member initializer list
    {
        std::cout << "Foo constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};

int main()
{
    Foo foo { 6 };
    foo.print();

    return 0;
}
```
Foo constructed
Foo(6, 2, -858993460)

>Here’s what’s happening. When `foo` is constructed, only `m_x` appears in the member initializer list, so `m_x` is first initialized to `6`. `m_y` is not in the member initialization list, but it does have a default member initializer, so it is initialized to `2`. `m_z` is neither in the member initialization list, nor does it have a default member initializer, so it is default-initialized (which for fundamental types, means it is left uninitialized). Thus, when we print the value of `m_z`, we get undefined behavior.

### Constructor function bodies

>The bodies of constructors functions are most often left empty. This is because we primarily use constructor for initialization, which is done via the member initializer list. If that is all we need to do, then we don’t need any statements in the body of the constructor.

However, because the statements in the body of the constructor execute after the member initializer list has executed, we can add statements to do any other setup tasks required. In the above examples, we print something to the console to show that the constructor executed, but we could do other things like open a file or database, allocate memory, etc…

New programmers sometimes use the body of the constructor to assign values to members:

```cpp
#include <iostream>

class Foo
{
private:
    int m_x { 0 };
    int m_y { 1 };

public:
    Foo(int x, int y)
    {
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = y; // incorrect: this is an assignment, not an initialization
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
```

Although in this simple case this will produce the expected result, in case where members are required to be initialized (such as for data members that are const or references) assignment will not work.

>[!Key Insight]
>Once the member initializer list has finished executing, the object is considered initialized. Once the function body has finished executing, the object is considered constructed.

>[!Best Practice]
>Prefer using the member initializer list to initialize your members over assigning values in the body of the constructor.

### Detecting and handling invalid arguments to constructors

#### 1. The Problem

- A `Fraction` needs a **denominator ≠ 0** (otherwise invalid).
    
- If user does:

```cpp
Fraction f{1, 0}; 
```

- → object becomes semantically invalid (denominator = 0).
    

That violates the **class invariant**: `m_denominator != 0`.

#### 2. Why not fix it in the initializer list?

In the initializer list:

```cpp
Fraction(int numerator, int denominator) :
    m_numerator{numerator}, m_denominator{denominator != 0 ? denominator : ???}
{ }
```

- We can _detect_ `denominator == 0`, but we can’t really _handle_ it properly.
    
- If we silently replace `0` with something else (say `1`), the user gets an object **different from what they asked for**, without being told.
    
- That’s unsafe and misleading.
    

So → initializer list is not suitable for error handling.

### 3. Why constructor body is better

In the constructor body, we can use **statements**:

```cpp
Fraction(int numerator, int denominator) :
    m_numerator{numerator}, m_denominator{denominator}
{
    if (denominator == 0)
        // handle error here
}
```

Options here:

- `assert(denominator != 0);` → catches errors in debug builds, but useless in production.
    
- Runtime handling needed → leads us to "constructor failure".

#### 4. When constructors fail

If arguments are invalid, **constructor cannot make a valid object** → the constructor "fails".

How to handle such failure? Four general strategies (same as with normal functions):

1. **Resolve internally** → not possible, since we don’t know what a "fixed denominator" should be.
    
2. **Return error to caller** → constructors can’t return values, so not feasible.  
    (A hack is `isValid()` method, but caller might forget to check → unsafe).
    
3. **Halt program** → rarely acceptable in real applications.
    
4. **Throw exception** → aborts construction process entirely → prevents invalid objects from existing.
    
#### 5. Key insight

- The **best option** in most cases is:  
    **Throw an exception inside the constructor when invalid arguments are passed.**
    

That way:

- Construction stops immediately.
    
- Caller never gets a broken object.
    
- Error can be caught and handled at a higher level.
    

✅ **So the main takeaway:**  
If a constructor gets invalid arguments and cannot create a valid object, the best way to handle it is to **throw an exception**.

### [For Advanced Readers](https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/#:~:text=For%20advanced%20readers,COPY)

---
# Default constructors and default arguments

>A **default constructor** is a constructor that accepts no arguments. Typically, this is a constructor that has been defined with no parameters.

```cpp
#include <iostream>

class Foo
{
public:
    Foo() // default constructor
    {
        std::cout << "Foo default constructed\n";
    }
};

int main()
{
    Foo foo{}; // No initialization values, calls Foo's default constructor

    return 0;
}
```

When the above program runs, an object of type `Foo` is created. Since no initialization values have been provided, the default constructor `Foo()` is called

>[!Best Practice]
>Prefer value initialization over default initialization for all class types.

### Constructors with default arguments

>As with all functions, the rightmost parameters of constructors can have default arguments.

```cpp
#include <iostream>

class Foo
{
private:
    int m_x { };
    int m_y { };

public:
    Foo(int x=0, int y=0) // has default arguments
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // calls Foo(int, int) constructor using default arguments
    Foo foo2{6, 7}; // calls Foo(int, int) constructor

    return 0;
}
```

This prints:

Foo(0, 0) constructed
Foo(6, 7) constructed

==If all of the parameters in a constructor have default arguments, the constructor is a default constructor (because it can be called with no arguments).

### Overloaded constructors

>Because constructors are functions, they can be overloaded. That is, we can have multiple constructors so that we can construct objects in different ways:

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x, int y) // non-default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // Calls Foo() constructor
    Foo foo2{6, 7}; // Calls Foo(int, int) constructor

    return 0;
}
```

A corollary of the above is that a class should only have one default constructor. If more than one default constructor is provided, the compiler will be unable to disambiguate which should be used:

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x=1, int y=2) // default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // compile error: ambiguous constructor function call

    return 0;
}
```

In the above example, we instantiate `foo` with no arguments, so the compiler will look for a default constructor. It will find two, and be unable to disambiguate which constructor should be used. This will result in a compile error.

### An implicit default constructor

If a non-aggregate class type object has no user-declared constructors, the compiler will generate a public default constructor (so that the class can be value or default initialized). This constructor is called an **implicit default constructor**.

Consider the following example:

```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

    // Note: no constructors declared
};

int main()
{
    Foo foo{};

    return 0;
}
```

>The implicit default constructor is useful mostly when we have classes that have no data members. If a class has data members, we’ll probably want to make them initializable with values provided by the user, and the implicit default constructor isn’t sufficient for that.

### Using `= default` to generate an explicitly defaulted default constructor

>In cases where we would write a default constructor that is equivalent to the implicitly generated default constructor, we can instead tell the compiler to generate a default constructor for us. This constructor is called an **explicitly defaulted default constructor**, and it can be generated by using the `= default` syntax:

```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() = default; // generates an explicitly defaulted default constructor

    Foo(int x, int y)
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // calls Foo() default constructor

    return 0;
}
```

>[!Best Practice]
>Prefer an explicitly defaulted default constructor (`= default`) over a default constructor with an empty body.

### Explicitly defaulted default constructor vs empty user-defined constructor

#### 1. **Two ways to provide a default constructor**

- **User-defined default constructor**

```cpp
User() {}   // an empty user-defined constructor
```

- Even if it does nothing, _this counts as user code_.
    
- **Explicitly defaulted constructor**

```cpp
Default() = default;   // compiler-provided behavior
```

This is the same as letting the compiler generate it implicitly — except you’re explicitly saying "I want the compiler default".

#### 2. **Difference during value initialization (`T obj{}`)**

##### Case A: **User-defined constructor (even if empty)**

- Value initialization **does NOT zero-initialize** members first.
    
- It jumps straight to calling your constructor body.
    
- If you don’t manually initialize members, they remain **indeterminate** (garbage).
    

That’s why in your code:

```cpp
User user{}; 
// m_a = uninitialized garbage
// m_b = 0 (because of {} default member initializer)
```

Output example:

```cpp
782510864 0
```

##### Case B: **Explicitly defaulted (`= default`) or Implicit**

- Value initialization **does zero-initialize first**.
- Then apply **default member initializers** (or ctor init list).
    
- Then the compiler-generated constructor runs.
    
- So uninitialized members become **0**, not garbage.
    

That’s why:

```cpp
Default def{};
Implicit imp{};
// m_a = 0
// m_b = 0
```

Output:

```cpp
0 0
0 0
```

#### 3. **Why this distinction exists**

- **User-provided constructor** (even empty) → compiler assumes "the programmer knows what they’re doing" → skips zero-initialization for performance.
    
- **Compiler-provided constructor** (`= default` or implicit) → C++ standard says "be safe" → zero-initialize before default-init.

#### 4. **Practical Implication**

- If you write your own constructor (even empty), **you must initialize all members yourself**, or risk UB.
    
- If you use `= default`, you get safety (zero-init first).
    
- **Best practice:** Always give your data members default initializers:

```cpp
class Safe {
    int m_a{};   // guarantees zero-init
    int m_b{};  
};
```

→ Now no matter what kind of constructor you use, your members start from a known state.

✅ **Summary:**

- `User() {}` → **no zero-init**, members left uninitialized unless you do it yourself.
    
- `User() = default;` or implicit → **zero-init first**, then default-init.
    
- Best practice: always initialize members with `= {}` or constructor initializer list.

>[!Important]
>Always give your data members default initializers:

### Only create a default constructor when it makes sense

A default constructor allows us to create objects of a non-aggregate class type with no user-provided initialization values. Thus, a class should only provide a default constructor when it makes sense for objects of a class type to be created using all default values.

For example:

```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction() = default;
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f1 {3, 5};
    f1.print();

    Fraction f2 {}; // will get Fraction 0/1
    f2.print();

    return 0;
}
```

For a class representing a fraction, it makes sense to allow the user to create Fraction objects with no initializers (in which case, the user will get the fraction 0/1).

Now consider this class:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{ };
    int m_id{ };

public:
    Employee(std::string_view name, int id)
        : m_name{ name }
        , m_id{ id }
    {
    }

    void print() const
    {
        std::cout << "Employee(" << m_name << ", " << m_id << ")\n";
    }
};

int main()
{
    Employee e1 { "Joe", 1 };
    e1.print();

    Employee e2 {}; // compile error: no matching constructor
    e2.print();

    return 0;
}
```

For a class representing an employee, it doesn’t make sense to allow creation of employees with no name. Thus, such a class should not have a default constructor, so that a compilation error will result if the user of the class tries to do so.

>[!Tip]
>The implicit default constructor will only be created if there isn't any other constructor otherwise if we try to create object with empty list initializer then we will get an error.

---
# Delegating constructors

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };
    bool m_isManager { false };

public:
    Employee(std::string_view name, int id) // Employees must have a name and an id
        : m_name{ name }, m_id { id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }

    Employee(std::string_view name, int id, bool isManager) // They can optionally be a manager
        : m_name{ name }, m_id{ id }, m_isManager { isManager }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James", 7 };
    Employee e2{ "Dave", 42, true };
}
```

#### 🔹 Problem

In the original example, you had **two constructors**:

```cpp
Employee(std::string_view name, int id)
    : m_name{ name }, m_id { id }
{
    std::cout << "Employee " << m_name << " created\n";
}

Employee(std::string_view name, int id, bool isManager)
    : m_name{ name }, m_id{ id }, m_isManager { isManager }
{
    std::cout << "Employee " << m_name << " created\n";
}
```

- Both constructors **repeat the same `std::cout` line**.
    
- Both constructors also **initialize `m_name` and `m_id`** in the same way.
    

This duplication makes code harder to maintain. For example: if you later want to change how employees are printed, you must update **both constructors**. That’s against DRY.

#### 🔹 First Improvement (Helper Function)

Introduce a helper function:

```cpp
void printCreated() const
{
    std::cout << "Employee " << m_name << " created\n";
}
```

Now both constructors call it:

```cpp
Employee(std::string_view name, int id)
    : m_name{ name }, m_id { id }
{
    printCreated();
}

Employee(std::string_view name, int id, bool isManager)
    : m_name{ name }, m_id{ id }, m_isManager { isManager }
{
    printCreated();
}
```

✅ This reduces redundancy of the `std::cout` line.  
❌ But both constructors still duplicate initialization of `m_name` and `m_id`.

>It’s generally not a good idea to have a constructor print something (except for debugging purposes), as this means you can’t create an object using that constructor in cases where you do not want to print something. We’re doing it in this example to help illustrate what’s happening.

### Calling a constructor in the body of a function creates a temporary object

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };
    bool m_isManager { false };

public:
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // this constructor initializes name and id
    {
        std::cout << "Employee " << m_name << " created\n"; // our print statement is back here
    }

    Employee(std::string_view name, int id, bool isManager)
        : m_isManager { isManager } // this constructor initializes m_isManager
    {
        // Call Employee(std::string_view, int) to initialize m_name and m_id
        Employee(name, id); // this doesn't work as expected!
    }

    const std::string& getName() const { return m_name; }
};

int main()
{
    Employee e2{ "Dave", 42, true };
    std::cout << "e2 has name: " << e2.getName() << "\n"; // print e2.m_name
}
```

But this doesn’t work correctly, as the program outputs the following:

```cpp
Employee Dave created
e2 has name: ???
```

- **Problem:**  
    If you call a constructor like a normal function inside another constructor’s body (e.g., `Employee(name, id);`), it **creates a temporary object**, not initializes the current object (`this`).
    
- **Why?**
    
    - Initialization of an object’s members happens **only in the member initializer list**, before the constructor body runs.
        
    - By the time you’re in the body, the current object is already initialized (default values or whatever you specified).
        
    - Calling `Employee(name, id)` inside the body just constructs a **new temporary Employee object**, initializes _that_, prints its message, then destroys it immediately.
        
    - Your actual object (`e2`) remains unchanged → members stay at defaults (`"???"`, `0`, etc.).

```cpp
Employee(std::string_view name, int id, bool isManager)
    : m_isManager{isManager}  // only initializes m_isManager
{
    Employee(name, id); // creates & destroys a temporary, doesn’t touch *this
}
```

- Output shows `Employee Dave created` (temporary)
    
- But `e2.m_name` is still `"???"` (original object never got updated).

>[!Best Practice]
>Constructors should not be called directly from the body of another function. Doing so will either result in a compilation error, or will direct-initialize a temporary object.

### Delegating constructors

#### **Definition**

- A **delegating constructor** is a constructor that calls another constructor **from the same class** to handle initialization.
    
- This is also called **constructor chaining**.

#### **How it works**

- To delegate, you call another constructor in the **member initializer list**:

```cpp
Employee(std::string_view name)
    : Employee{name, 0} // delegates to another constructor
{
}
```

#### **Rules**

1. **Delegate or Initialize, not both**
    
    - A constructor can either:
        
        - Initialize members directly **OR**
            
        - Delegate to another constructor
            
    - But not both at the same time.
        
2. **Avoid Infinite Loops**
    
    - If constructor A delegates to B, and B delegates back to A → infinite recursion → program crash.
        
    - Ensure all chains eventually end at a **non-delegating constructor**.
        
3. **Common Pattern**
    
    - Constructors with **fewer parameters** often delegate to constructors with **more parameters**, providing default values.


>Example:

```cpp
class Employee {
private:
    std::string m_name{"???"};
    int m_id{0};

public:
    Employee(std::string_view name)
        : Employee{name, 0}  // delegates to main constructor
    { }

    Employee(std::string_view name, int id)
        : m_name{name}, m_id{id}  // main constructor (non-delegating)
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};
```

#### **Execution Flow**

For:

```cpp
Employee e1{"James"};
```

- `Employee(std::string_view)` is called with `"James"`.
    
- It **delegates** to `Employee(std::string_view, int)` with `("James", 0)`.
    
- The second constructor initializes members.
    
- Control returns to the first constructor (its body executes).
    
- Object is ready.

#### **Downside**

- Sometimes requires **duplicate default values** (e.g., hardcoding `0` for `m_id`) because you **cannot reference default member initializers** in delegation.
    

>[!Best Practice]
>If you have multiple constructors, consider whether you can use delegating constructors to reduce duplicate code.

### Reducing constructors using default arguments

```cpp
class Employee
{
private:
    std::string m_name{};
    int m_id{ 0 }; // default member initializer

public:
    // only one constructor
    Employee(std::string_view name, int id = 0) 
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};
```

```cpp
Employee e1{ "James" };     // id defaults to 0
Employee e2{ "Dave", 42 };  // id explicitly set
```

### Key Idea

- Instead of writing two constructors:

```cpp
Employee(std::string_view name);
Employee(std::string_view name, int id);
```

- we **merge them into one** by giving `id` a **default argument**.
    

So if the caller doesn’t pass `id`, it defaults to `0`.

#### 🔹 Best Practice

- **Required parameters first** (leftmost).  
    e.g. `name` must always be given.
    
- **Optional parameters later** (rightmost).  
    e.g. `id` has a default value, so it goes last.
    

This order ensures the function call makes sense:

```cpp
Employee e1{"John"};        // required only
Employee e2{"John", 99};    // required + optional
```

⚠️ **Cons:**

- You **duplicate the default value** for `m_id`:
    
    - once as `int m_id{0};` (default member initializer),
        
    - again as `int id = 0` (default argument).
        
- If the default changes later (say from `0` → `-1`), you must update it in **two places** → possible inconsistency.

### A conundrum: Redundant constructors vs redundant default values

#### 1. Problem we are solving

When writing constructors, we want:

- ✅ Fewer constructors (less code, easier to maintain).
    
- ✅ No duplication of default values (so one change updates everywhere).
    

But in C++, you **cannot always have both** at the same time.

#### 2. Two main techniques

##### (A) **Delegating constructors**

One constructor calls another to avoid repeating logic.

```cpp
class Employee {
    std::string m_name{};
    int m_id{0};   // default member initializer

public:
    Employee(std::string_view name, int id)
        : m_name{name}, m_id{id} {}

    Employee(std::string_view name) 
        : Employee{name, 0} {}   // delegates
};
```

- **Good**: Only one constructor (`Employee(string,int)`) does real work.
    
- **Bad**: The default value `0` is written **twice**:
    
    - once in `int m_id{0};`
        
    - once in `Employee{name, 0}`
        

If the default changes later (say `0 → -1`), you must update it in 2 places.

##### (B) **Default arguments**

Let a single constructor handle both cases by giving a parameter a default.

```cpp
class Employee {
    std::string m_name{};
    int m_id{0};   // default member initializer

public:
    Employee(std::string_view name, int id = 0) 
        : m_name{name}, m_id{id} {}
};
```

- **Good**: Only **one constructor**. Very clean.
    
- **Bad**: Again, `0` is written **twice**:
    
    - once in `int m_id{0};`
        
    - once in `int id = 0`
        

Same problem: if default changes, must update 2 places.

#### 3. Why this happens

C++ currently has **no way** to tell a constructor:

> “If the caller doesn’t provide a value, just use the member initializer’s default.”

So if you want both:

- default member initializer (safety),
    
- and a delegating constructor / default argument (convenience),  
    you are **forced to duplicate the default values**.

#### 4. The tradeoff

- **Option A: More constructors**
    
    - Each constructor written separately.
        
    - No duplication of default values.
        
    - But more boilerplate code.
        
- **Option B: Fewer constructors** (delegation or default args)
    
    - Less boilerplate code.
        
    - But duplicate default values.
        

This is the **conundrum**:

- Do you want fewer constructors (cleaner code) but accept duplication?
    
- Or more constructors (no duplication) but more boilerplate?

#### 5. Common advice

Most experts (and LearnCpp) recommend:  
👉 Prefer **fewer constructors**, even if you have to duplicate default values.  
Why?

- Code is easier to read.
    
- Bugs from mismatched defaults are rare if you’re disciplined.
    
- Easier to maintain overall.
    

✅ **In one line for your notes:**  
C++ forces a tradeoff → Either duplicate default values (fewer constructors) or write more constructors (no duplication). Best practice = fewer constructors, even with duplication.

👉 Example that **requires delegation**:

```cpp
class Student {
private:
    std::string m_name{};
    int m_age{};
    double m_gpa{};

public:
    Student(std::string_view name, int age, double gpa)
        : m_name{name}, m_age{age}, m_gpa{gpa} {}

    // Default GPA depends on age → can't be done with member initializer
    Student(std::string_view name, int age)
        : Student(name, age, (age < 10 ? 5.0 : 0.0)) {}
};
```

Here, the GPA default depends on `age`, so **delegation wins**.

📝 Example: Using **Default Member Initializers**

```cpp
class Student {
private:
    std::string m_name{"Unknown"};
    int m_age{18};
    double m_gpa{0.0};
public:
    Student() = default;               // uses defaults
    Student(std::string_view name) : m_name{name} {}
};
```

✅ Best when defaults never change.  
❌ Can’t handle: “If age < 10, GPA = 5.0”.

## 📊 Default Member Initializers vs Delegating Constructors

|Feature|**Default Member Initializers**|**Delegating Constructors**|
|---|---|---|
|**Where defaults live**|Next to the data members|Inside one “master” constructor|
|**Simplicity**|Very simple for constants|Slightly more verbose|
|**Code duplication**|Each constructor must still set values if different|No duplication → one master constructor handles all|
|**Conditional defaults**|❌ Not possible (only static values)|✅ Possible (can compute based on arguments)|
|**Readability**|Easy to see defaults at a glance|Defaults hidden in delegating calls|
|**Flexibility**|Limited|Very flexible|
|**Best use case**|Simple constants (e.g., `int age{18};`)|Context-dependent defaults (e.g., GPA depends on age)

---
# Temporary class objects

### 🔹 1. Avoid unnecessary one-use variables

- Example:

```cpp
int add(int x, int y) {
    int sum { x + y };
    return sum;
}
```

is the same as:

```cpp
int add(int x, int y) {
    return x + y;
}
```

- If a variable is **only used once**, it adds clutter.
    
- Directly use the expression instead of storing it in a variable.

#### 🔹 2. Works for function arguments too

- Instead of:

```cpp
int sum { 5 + 3 };
printValue(sum);
```

→ Just write:

```cpp
printValue(5 + 3);
```

✅ Cleaner, no need to track an extra variable.

#### 🔹 3. Limitation: Need lvalues for non-const references

- If a function requires **non-const reference**, we **must** pass a variable (an lvalue).

```cpp
void addOne(int& value) { ++value; }

int sum { 5 + 3 };
addOne(sum);   // ✅ ok
addOne(5 + 3); // ❌ error, rvalue cannot bind to non-const reference
```

#### 🔹 4. Temporary objects (class types)

- Same rule applies to **user-defined types** (like `IntPair`).
    
- Three cases:

```cpp
IntPair p{3,4};  
print(p);                // Case 1: named object

print(IntPair{5,6});     // Case 2: explicit temporary

print({7,8});            // Case 3: implicit temporary (compiler deduces type)
```

Temporaries are **created, used, and destroyed** immediately after the expression.

To summarize:

```cpp
IntPair p { 1, 2 }; // create named object p initialized with { 1, 2 }
IntPair { 1, 2 };   // create temporary object initialized with { 1, 2 }
{ 1, 2 };           // compiler will try to convert { 1, 2 } to temporary object matching expected type (typically a parameter or return type)
```

- `std::string{"Hello"}` → temporary string `"Hello"`.
    
- `std::string{}` → temporary empty string.

### Creating temporary objects via direct initialization (Optional)

#### ✅ Key Insight

- `Foo(...)` without a variable name = creates a **temporary Foo**.
    
- `Foo var(...);` = depends: could be a variable definition or function declaration (most vexing parse).
    
- `Foo(bar);` = defines a variable named `bar`, not a temporary.
    
- Curly braces `{}` are unambiguous: always object initialization.
    

That’s why **modern C++ prefers `{}` initialization**:

```cpp
Foo a{1};   // variable
Foo{1};     // temporary
```

### Temporary objects and return by value

When a function returns by value, the object that is returned is a temporary object (initialized using the value or object identified in the return statement).

Here are some examples:

```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

// Case 1: Create named variable and return
IntPair ret1()
{
    IntPair p { 3, 4 };
    return p; // returns temporary object (initialized using p)
}

// Case 2: Create temporary IntPair and return
IntPair ret2()
{
    return IntPair { 5, 6 }; // returns temporary object (initialized using another temporary object)
}

// Case 3: implicitly convert { 7, 8 } to IntPair and return
IntPair ret3()
{
    return { 7, 8 }; // returns temporary object (initialized using another temporary object)
}

int main()
{
    print(ret1());
    print(ret2());
    print(ret3());

    return 0;
}
```

In case 1, when we `return p`, a temporary object is created and initialized using `p`.

### A few notes

First, just as in the case of an `int`, when used in an expression, a temporary class object is an rvalue. Thus, such objects can only be used where rvalue expressions are accepted.

Second, temporary objects are created at the point of definition, and destroyed at the end of the full expression in which they are defined . A full expression is an expression that is not a subexpression.

### `static_cast` vs explicit instantiation of a temporary object

#### 🔹 The core similarity

Both `static_cast<T>(expr)` and `T{expr}` (or `T(expr)`) create a **temporary object of type `T`** initialized with `expr`.  
In your first example:

```cpp
char c{'a'};

std::cout << static_cast<int>(c) << '\n'; // static_cast → temporary int
std::cout << int{c} << '\n';              // list-init temporary int
```

Both give you a temporary `int` constructed from `c`.

#### 🔹 The subtle difference: how initialization works

1. **`static_cast<T>(expr)` → direct-initialization**
    
    - This applies _direct-initialization rules_.
        
    - Example: `static_cast<int>(c)` directly initializes the temporary `int` from `c`.
        
    - Direct-initialization allows implicit conversions (but won’t use `explicit` constructors unless explicitly written).

2. **`T{expr}` (list-initialization) → safer**
    
    - This uses _list-initialization rules_.
        
    - Example: `int{c}` creates a temporary `int` initialized from `c`.
        
    - List-initialization:
        
        - **Forbids narrowing conversions** (trying to assign a `double` to an `int` would be an error).
            
        - Can call `explicit` constructors.
            
        - Can invoke initializer-list constructors.
            

So the key distinction is: **direct-init (`static_cast`) vs list-init (`T{expr}`)**.


#### 🔹 Why it matters n the `std::string_view` → `std::string` case

```cpp
std::string_view sv{"Hello"};

printString(static_cast<std::string>(sv)); // direct-init from sv
printString(std::string{sv});              // list-init from sv
```

Both work here, because `std::string` has constructors that accept `std::string_view`.  
The real difference comes down to **style and safety**:

- `static_cast<std::string>(sv)`
    
    - Looks like an explicit cast.
        
    - Obvious that a type conversion is happening.
        
    - Uses direct-init.
        
- `std::string{sv}`
    
    - Looks like normal construction.
        
    - Safer (prevents narrowing).
        
    - Preferred when converting between class types.

#### 🔹 Why avoid C-style cast?

```cpp
printString(std::string(sv)); // C-style cast
```

This works, but:

- It looks almost identical to list-init but actually isn’t.
    
- C-style casts can do **reinterpret_cast**, **const_cast**, and other dangerous things silently.
    
- That’s why modern C++ best practice says: don’t use it.

#### ==🔹 Best Practice 

✅ Use **`static_cast<T>(x)`** when:

- Converting between **fundamental types** (like `char` → `int`).
    
- You want it to be _very obvious_ you’re doing a cast.
    

✅ Use **`T{...}`** when:

- Converting to a **class type** (like `std::string` from `std::string_view`).
    
- You want narrowing protection.
    
- You might need to pass multiple args to a constructor.

#### 🔹 Quick Summary

- `static_cast<T>(x)` → direct-init, good for **fundamentals**.
    
- `T{x}` → list-init, good for **classes**.
    
- Both produce temporaries.
    
- Prefer explicit construction (`T{}`) over `static_cast` when calling constructors.

---
