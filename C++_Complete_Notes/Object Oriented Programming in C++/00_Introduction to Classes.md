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
