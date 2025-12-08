
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
# Virtual functions and polymorphism

In the previous lesson on [pointers and references to the base class of derived objects](https://www.learncpp.com/cpp-tutorial/121-pointers-and-references-to-the-base-class-of-derived-objects/), we took a look at a number of examples where using pointers or references to a base class had the potential to simplify code. However, in every case, we ran up against the problem that the base pointer or reference was only able to call the base version of a function, not a derived version.

Here’s a simple example of this behavior:

```cpp
#include <iostream>
#include <string_view>

class Base
{
public:
    std::string_view getName() const { return "Base"; }
};

class Derived: public Base
{
public:
    std::string_view getName() const { return "Derived"; }
};

int main()
{
    Derived derived {};
    Base& rBase{ derived };
    std::cout << "rBase is a " << rBase.getName() << '\n';

    return 0;
}
```

This example prints the result:

`rBase is a Base`

Because rBase is a Base reference, it calls Base::getName(), even though it’s actually referencing the Base portion of a Derived object.

In this lesson, we will show how to address this issue using virtual functions.

## Virtual functions

A **virtual function** is a special type of member function that, when called, resolves to the most-derived version of the function for the actual type of the object being referenced or pointed to.

A derived function is considered a match if it has the same signature (name, parameter types, and whether it is const) and return type as the base version of the function. Such functions are called **overrides**.

To make a function virtual, simply place the “virtual” keyword before the function declaration.

Here’s the above example with a virtual function:

```cpp
#include <iostream>
#include <string_view>

class Base
{
public:
    virtual std::string_view getName() const { return "Base"; } // note addition of virtual keyword
};

class Derived: public Base
{
public:
    virtual std::string_view getName() const { return "Derived"; }
};

int main()
{
    Derived derived {};
    Base& rBase{ derived };
    std::cout << "rBase is a " << rBase.getName() << '\n';

    return 0;
}
```

This example prints the result:

rBase is a Derived

>Because rBase is a reference to the Base portion of a Derived object, when _rBase.getName()_ is evaluated, it would normally resolve to Base::getName(). However, Base::getName() is virtual, which tells the program to go look and see if there are any more-derived versions of the function available for a Derived object. In this case, it will resolve to Derived::getName()!

Let’s take a look at a slightly more complex example:

```cpp
#include <iostream>
#include <string_view>

class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};

class B: public A
{
public:
    virtual std::string_view getName() const { return "B"; }
};

class C: public B
{
public:
    virtual std::string_view getName() const { return "C"; }
};

class D: public C
{
public:
    virtual std::string_view getName() const { return "D"; }
};

int main()
{
    C c {};
    A& rBase{ c };
    std::cout << "rBase is a " << rBase.getName() << '\n';

    return 0;
}
```

What do you think this program will output?

Let’s look at how this works. First, we instantiate a C class object. rBase is an A reference, which we set to reference the A portion of the C object. Finally, we call rBase.getName(). rBase.getName() evaluates to A::getName(). However, A::getName() is virtual, so the compiler will call the most-derived match between A and C. In this case, that is C::getName(). Note that it will not call D::getName(), because our original object was a C, not a D, so only functions between A and C are considered.

As a result, our program outputs:

`rBase is a C`

Note that virtual function resolution only works when a virtual member function is called through a pointer or reference to a class type object. This works because the compiler can differentiate the type of the pointer or reference from the type of the object being pointed to or referenced. We see this in example above.

Calling a virtual member function directly on an object (not through a pointer or reference) will always invoke the member function belonging to the same type of that object. For example:

```cpp
C c{};
std::cout << c.getName(); // will always call C::getName

A a { c }; // copies the A portion of c into a (don't do this)
std::cout << a.getName(); // will always call A::getName
```

>Virtual function resolution only works when a member function is called through a pointer or reference to a class type object.

## Polymorphism

In programming, **polymorphism** refers to the ability of an entity to have multiple forms (the term “polymorphism” literally means “many forms”). For example, consider the following two function declarations:

```cpp
int add(int, int);
double add(double, double);
```

The identifier `add` has two forms: `add(int, int)` and `add(double, double)`.

**Compile-time polymorphism** refers to forms of polymorphism that are resolved by the compiler. These include function overload resolution, as well as template resolution.

**Runtime polymorphism** refers to forms of polymorphism that are resolved at runtime. This includes virtual function resolution.

## A more complex example

A more complex example

Let’s take another look at the Animal example we were working with in the previous lesson. Here’s the original class, along with some test code:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Animal
{
protected:
    std::string m_name {};

    // We're making this constructor protected because
    // we don't want people creating Animal objects directly,
    // but we still want derived classes to be able to use it.
    Animal(std::string_view name)
        : m_name{ name }
    {
    }

public:
    const std::string& getName() const { return m_name; }
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

void report(const Animal& animal)
{
    std::cout << animal.getName() << " says " << animal.speak() << '\n';
}

int main()
{
    Cat cat{ "Fred" };
    Dog dog{ "Garbo" };

    report(cat);
    report(dog);

    return 0;
}
```

This prints:

Fred says ???
Garbo says ???

Here’s the equivalent class with the speak() function made virtual:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Animal
{
protected:
    std::string m_name {};

    // We're making this constructor protected because
    // we don't want people creating Animal objects directly,
    // but we still want derived classes to be able to use it.
    Animal(std::string_view name)
        : m_name{ name }
    {
    }

public:
    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const { return "???"; }
};

class Cat: public Animal
{
public:
    Cat(std::string_view name)
        : Animal{ name }
    {
    }

    virtual std::string_view speak() const { return "Meow"; }
};

class Dog: public Animal
{
public:
    Dog(std::string_view name)
        : Animal{ name }
    {
    }

    virtual std::string_view speak() const { return "Woof"; }
};

void report(const Animal& animal)
{
    std::cout << animal.getName() << " says " << animal.speak() << '\n';
}

int main()
{
    Cat cat{ "Fred" };
    Dog dog{ "Garbo" };

    report(cat);
    report(dog);

    return 0;
}
```

This program produces the result:

Fred says Meow
Garbo says Woof

It works!

When animal.speak() is evaluated, the program notes that Animal::speak() is a virtual function. In the case where animal is referencing the Animal portion of a Cat object, the program looks at all the classes between Animal and Cat to see if it can find a more derived function. In that case, it finds Cat::speak(). In the case where animal references the Animal portion of a Dog object, the program resolves the function call to Dog::speak().

Note that we didn’t make Animal::getName() virtual. This is because getName() is never overridden in any of the derived classes, therefore there is no need.

Similarly, the following array example now works as expected:

```cpp
Cat fred{ "Fred" };
Cat misty{ "Misty" };
Cat zeke{ "Zeke" };

Dog garbo{ "Garbo" };
Dog pooky{ "Pooky" };
Dog truffle{ "Truffle" };

// Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
Animal* animals[]{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

for (const auto* animal : animals)
    std::cout << animal->getName() << " says " << animal->speak() << '\n';
```

Which produces the result:

Fred says Meow
Garbo says Woof
Misty says Meow
Pooky says Woof
Truffle says Woof
Zeke says Meow

==Even though these two examples only use Cat and Dog, any other classes we derive from Animal would also work with our report() function and animal array without further modification! This is perhaps the biggest benefit of virtual functions -- the ability to structure your code in such a way that newly derived classes will automatically work with the old code without modification!

==A word of warning: the signature of the derived class function must _exactly_ match the signature of the base class virtual function in order for the derived class function to be used. If the derived class function has different parameter types, the program will likely still compile fine, but the virtual function will not resolve as intended. In the next lesson, we’ll discuss how to guard against this.

==Note that if a function is marked as virtual, all matching overrides in derived classes are also implicitly considered virtual, even if they are not explicitly marked as such.

>Rule
If a function is virtual, all matching overrides in derived classes are implicitly virtual.

This does not work the other way around -- a virtual override in a derived class does not implicitly make the base class function virtual.

## Return types of virtual functions

Under normal circumstances, the return type of a virtual function and its override must match. Consider the following example:

```cpp
class Base
{
public:
    virtual int getValue() const { return 5; }
};

class Derived: public Base
{
public:
    virtual double getValue() const { return 6.78; }
};
```

In this case, Derived::getValue() is not considered a matching override for Base::getValue() and compilation will fail.

And that is runtime polymorphism!

## Do not call virtual functions from constructors or destructors

Here’s another gotcha that often catches unsuspecting new programmers. You should not call virtual functions from constructors or destructors. Why?

Remember that when a Derived class is created, the Base portion is constructed first. If you were to call a virtual function from the Base constructor, and Derived portion of the class hadn’t even been created yet, it would be unable to call the Derived version of the function because there’s no Derived object for the Derived function to work on. In C++, it will call the Base version instead.

A similar issue exists for destructors. If you call a virtual function in a Base class destructor, it will always resolve to the Base class version of the function, because the Derived portion of the class will already have been destroyed.

>Best practice
Never call virtual functions from constructors or destructors.

## The downside of virtual functions

Since most of the time you’ll want your functions to be virtual, why not just make all functions virtual? The answer is because it’s inefficient -- resolving a virtual function call takes longer than resolving a regular one.

Furthermore, to make virtual functions work, the compiler has to allocate an extra pointer for each object of a class that has virtual functions. This adds a lot of overhead to objects that otherwise have a small size. We’ll talk about this more in future lessons in this chapter.

## Case

```cpp
#include <iostream>
#include <string_view>

class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};

class B: public A
{
public:
    // note: no virtual keyword in B, C, and D
    std::string_view getName() const { return "B"; }
};

class C: public B
{
public:
    std::string_view getName() const { return "C"; }
};

class D: public C
{
public:
    std::string_view getName() const { return "D"; }
};

int main()
{
    C c {};
    B& rBase{ c }; // note: rBase is a B this time
    std::cout << rBase.getName() << '\n';

    return 0;
}
```

C. Even though B and C aren’t marked as virtual functions, A::getName() is virtual and B::getName() and C::getName() are overrides. Therefore, B::getName() and C::getName() are considered implicitly virtual, and thus the call to rBase.getName() resolves to C::getName(), not B::getName().

```cpp
#include <iostream>
#include <string_view>

class A
{
public:
	A() { std::cout << getName(); } // note addition of constructor (getName() now called from here)

	virtual std::string_view getName() const { return "A"; }
};

class B : public A
{
public:
	virtual std::string_view getName() const { return "B"; }
};

class C : public B
{
public:
	virtual std::string_view getName() const { return "C"; }
};

class D : public C
{
public:
	virtual std::string_view getName() const { return "D"; }
};

int main()
{
	C c {};

	return 0;
}
```

A. Another tricky one. When we create a C object, the A part is constructed first. When the A constructor is called to do this, it calls virtual function getName(). Because the B and C parts of the class aren’t set up yet, this resolves to A::getName().

---
