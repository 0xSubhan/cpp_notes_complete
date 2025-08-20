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
