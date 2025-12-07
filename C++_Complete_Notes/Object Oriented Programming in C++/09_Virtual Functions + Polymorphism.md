
# Pointers and references to the base class of derived objects

>In the previous chapter, you learned all about how to use inheritance to derive new classes from existing classes. In this chapter, we are going to focus on one of the most important and powerful aspects of inheritance -- virtual functions.

But before we discuss what virtual functions are, let’s first set the table for why we need them.

```cpp
#include <string_view>

class Base
{
protected:
    int m_value {};

public:
    Base(int value)
        : m_value{ value }
    {
    }

    std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }

    std::string_view getName() const { return "Derived"; }
    int getValueDoubled() const { return m_value * 2; }
};
```
## **Pointers, references, and derived classes**

It should be fairly intuitive that we can set Derived pointers and references to Derived objects:

### ✅ **Why a Base pointer/reference can point to a Derived object**

A `Derived` object contains all of the following:

- everything inside `Base`
    
- plus anything extra that `Derived` adds
    

So the object in memory looks like:

```cpp
[ Base part ] + [ Derived extra stuff ]
```

Because the Base part is always there, C++ allows:

```cpp
Base& rBase = derived;
Base* pBase = &derived;
```

This is safe, because the Base pointer/reference will only use the Base portion of the object.

### ✅ **Why Base references only call Base’s version of functions**

When you write:

```cpp
rBase.getName();
```

Even though the actual object is Derived, **the reference type is Base**.

So C++ says:

> “I only know that this is a Base.  
> So I will use Base’s functions and Base’s members.”

This is called **early/static binding** (you’ll learn the full meaning later — you don’t need it yet).

So:

- `derived.getName()` → Derived version
    
- `rBase.getName()` → Base version
    
- `pBase->getName()` → Base version
    

Because Base can’t see anything in Derived.

### ✅ **Why Derived functions disappear when viewed through Base**

Look at this function:

```cpp
int getValueDoubled() const { return m_value * 2; }
```

This function **belongs only to Derived**.

Base does **not** have it.

So a Base pointer/reference **cannot** call it:

```cpp
rBase.getValueDoubled(); // ❌ not allowed
```

Even though the _object_ is Derived, the _identity_ (the type of the pointer/reference) is Base.

This is exactly what the chapter is trying to teach:

> **When you view a Derived object through a Base pointer/reference,  
> you only see the Base part. Everything specific to Derived is hidden.**

### ✅ **Why the output shows “Base” instead of “Derived”**

Because the function `getName()` in Derived **hides** the one in Base.

But when using a Base pointer/reference:

- C++ does not look for the hidden version
    
- C++ does not search Derived
    
- C++ simply says:  
    **“I am a Base, so I will use Base’s getName().”**
    

That’s why the program prints:

```cpp
rBase is a Base
pBase is a Base
```

Even though the actual object is Derived.

### 🔑 **Key takeaways (build-up for polymorphism)**

This entire topic is preparing you for polymorphism later.  
You only need to understand these ideas for now:

#### ✔ A Derived contains a Base → so it can be treated as a Base

#### ✔ When treated as a Base, only Base parts are visible

#### ✔ Derived-specific members vanish when using Base pointers/references

#### ✔ Function hiding means Base’s version is used when accessed as Base

Later, you will learn how to make C++ say:

```cpp
You are actually a Derived, so use the Derived version...
```

## Here’s another slightly more complex example that we’ll build on in the next lesson:

```cpp
#include <iostream>
#include <string_view>
#include <string>

class Animal
{
protected:
    std::string m_name;

    // We're making this constructor protected because
    // we don't want people creating Animal objects directly,
    // but we still want derived classes to be able to use it.
    Animal(std::string_view name)
        : m_name{ name }
    {
    }

    // To prevent slicing (covered later)
    Animal(const Animal&) = delete;
    Animal& operator=(const Animal&) = delete;

public:
    std::string_view getName() const { return m_name; }
    std::string_view speak() const { return "???"; }
};

class Cat: public Animal
{
public:
    Cat(std::string_view name)
        : Animal{ name }
    {
    }

    std::string_view speak() const { return "Meow"; }
};

class Dog: public Animal
{
public:
    Dog(std::string_view name)
        : Animal{ name }
    {
    }

    std::string_view speak() const { return "Woof"; }
};

int main()
{
    const Cat cat{ "Fred" };
    std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

    const Dog dog{ "Garbo" };
    std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

    const Animal* pAnimal{ &cat };
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    pAnimal = &dog;
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    return 0;
}
```

This produces the result:

cat is named Fred, and it says Meow
dog is named Garbo, and it says Woof
pAnimal is named Fred, and it says ???
pAnimal is named Garbo, and it says ???

We see the same issue here. Because pAnimal is an Animal pointer, it can only see the Animal portion of the class. Consequently, `pAnimal->speak()` calls Animal::speak() rather than the Dog::Speak() or Cat::speak() function.

### Confusion

>According to the following logic: "We see the same issue here. Because pAnimal is an Animal pointer, it can only see the Animal portion of the class. Consequently, pAnimal->speak() calls Animal::speak() rather than the Dog::Speak() or Cat::speak() function. " since it can only see animal portion and public cant access animal constructor since its protected so how come the name is set for cat which can only be set by animal constructor?

==My Answer: since cat is already created so it called the aniaml constructor earlier and set the name and that was it!

### 🔥 **Key idea:**

A derived object (Cat or Dog) _always contains_ a fully constructed base object (Animal).

That base part is created earlier — when the derived object was made.

### 🧠 Why “can only see the Animal portion” does NOT affect construction

You are mixing two different concepts:

#### 1️⃣ Access during **construction**

- Happens inside the Cat constructor.
    
- Cat is allowed to call Animal’s protected constructor.
    

#### 2️⃣ Access through a **pointer/reference**

- Happens _after_ the object is already fully built.
    
- A pointer only controls **what functions are visible**,  
    not **how the object was constructed**.
    

So:

- pAnimal can only call Animal methods (like speak() → "???")
    
- But pAnimal _still points to an Animal that has already been initialized_  
    by the Cat constructor earlier.

### 📌 Final Answer (Simple Form)

#### ✔ Yes, the name is already set earlier.

#### ✔ It was set when Cat (or Dog) called the Animal constructor during its own construction.

#### ✔ By the time you assign `pAnimal = &cat`, the Animal portion is fully initialized.

This is why the name shows correctly, even though `pAnimal` can only “see” the Animal portion.

## **Use for pointers and references to base classes**

### 1️⃣ **The Main Question**

> “Why would we ever use a pointer/reference to a base class when we can simply use the derived object?”

Because doing so gives **huge flexibility** and **saves a ton of duplicate code**, especially when you have **many derived classes**.

### 2️⃣ **Problem 1: Writing a function for each animal type**

### Without base-class references

You must write separate overloaded functions:

```cpp
void report(const Cat& cat);
void report(const Dog& dog);
```

#### Why this is bad

- If you have **30 animal types**, you need **30 report() functions**.
    
- If you add a new animal type later → you must write another function.
    
- Every function is almost identical — only the parameter type changes.
    

This is **wasteful**, repetitive, and error-prone.

### 3️⃣ **Observation: All animals _are_ animals**

Since `Cat` and `Dog` **inherit from** `Animal`:

- Every Cat **has an Animal part**.
    
- Every Dog **has an Animal part**.
    

So it makes sense that if we write:

```cpp
void report(const Animal& rAnimal);
```

Then:

- We can pass **any derived class** (Cat, Dog, etc.).
    
- Only **one function** is needed for all animals.

### 4️⃣ **Why using a base-class reference looks perfect**

```cpp
void report(const Animal& a)
{
    std::cout << a.getName() << " says " << a.speak() << '\n';
}
```

Advantages:

1. Only **one function** instead of 30.
    
2. Works for **all existing and future animal types**.
    
3. Prevents duplicated logic.

### 5️⃣ **The Problem (Before Virtual Functions)**

Because `rAnimal` is an **Animal reference**, it can only “see” the Animal version of functions.

So:

```cpp
rAnimal.speak();  // calls Animal::speak()
```

Even if the actual object is a Cat or Dog.  
This is the **core limitation** of non-virtual functions.

### 6️⃣ **Aside: Using templates instead**

```cpp
template <typename T>
void report(const T& a);
```

#### Pros:

- Only one function.
    
- Works for any type with `getName()` and `speak()`.
    

#### Cons:

- ❌ It does **not** restrict T to be an Animal.
    
- ❌ The meaning (“this should be an Animal”) is hidden.
    
- ❌ Accepts weird types accidentally (duck typing).
    

So templates don’t solve the real problem here.

### 7️⃣ **Problem 2: Storing many animals in a single array**

#### Without base-class pointers

Arrays require **all elements to be the same type**.  
So you must write:

```cpp
std::array<Cat, 3> cats;
std::array<Dog, 3> dogs;
```

If you had 30 different animal types → you need 30 arrays.

Terrible for managing large heterogeneous sets.

### 8️⃣ **Using pointers to the base class solves this (conceptually)**

Because every Cat and Dog _is an Animal_, you can do:

```cpp
const Animal* animals[] = { &fred, &garbo, &misty, ... };
```

This single array contains pointers to anything derived from Animal.

Perfect for:

- Games
    
- Simulators
    
- Real applications
    
- Managing mixed object collections

### 9️⃣ **But again, same problem appears**

Inside the loop:

```cpp
animal->speak();
```

Because `animal` is an `Animal*`:

- It only sees the **Animal** version of speak(),
    
- so _every animal says the same “???” sound_.
    

This destroys the usefulness of the technique.

### 🔟 **The Summary Before Virtual Functions**

Both techniques suffer from the **same limitation**:

### ❌ **A base-class pointer/reference calls baseclass functions — not derived ones.**

You end up with:

- A perfect design structure
    
- Fully valid code
    
- But **wrong behavior**
    

Because:

```cpp
Animal::speak() is always called
```

---
