---

---

---
## Introduction to Object Oriented Programming

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
