
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
# The override and final specifiers, and covariant return types

>To address some common challenges with inheritance, C++ has two inheritance-related identifiers: `override` and `final`. Note that these identifiers are not keywords -- they are normal words that have special meaning only when used in certain contexts. The C++ standard calls them “identifiers with special meaning”, but they are often referred to as “specifiers”.

Although final isn’t used very much, override is a fantastic addition that you should use regularly. In this lesson, we’ll take a look at both, as well as one exception to the rule that virtual function override return types must match.

## The override specifier

As we mentioned in the previous lesson, a derived class virtual function is only considered an override if its signature and return types match exactly. That can lead to inadvertent issues, where a function that was intended to be an override actually isn’t.

Consider the following example:

```cpp
#include <iostream>
#include <string_view>

class A
{
public:
	virtual std::string_view getName1(int x) { return "A"; }
	virtual std::string_view getName2(int x) { return "A"; }
};

class B : public A
{
public:
	virtual std::string_view getName1(short x) { return "B"; } // note: parameter is a short
	virtual std::string_view getName2(int x) const { return "B"; } // note: function is const
};

int main()
{
	B b{};
	A& rBase{ b };
	std::cout << rBase.getName1(1) << '\n';
	std::cout << rBase.getName2(2) << '\n';

	return 0;
}
```

Because rBase is an A reference to a B object, the intention here is to use virtual functions to access B::getName1() and B::getName2(). However, because B::getName1() takes a different parameter (a short instead of an int), it’s not considered an override of A::getName1(). More insidiously, because B::getName2() is const and A::getName2() isn’t, B::getName2() isn’t considered an override of A::getName2().

Consequently, this program prints:

`A
`A`
`
In this particular case, because A and B just print their names, it’s fairly easy to see that we messed up our overrides, and that the wrong virtual function is being called. However, in a more complicated program, where the functions have behaviors or return values that aren’t printed, such issues can be very difficult to debug.

To help address the issue of functions that are meant to be overrides but aren’t, the `override` specifier can be applied to any virtual function to tell the compiler to enforce that the function is an override. The `override` specifier is placed at the end of a member function declaration (in the same place where a function-level `const` goes). If a member function is `const` and an ovBest practice

Use the virtual keyword on virtual functions in a base class.

Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes virtual destructors.erride, the `const` must come before `override`.

If a function marked as `override` does not override a base class function (or is applied to a non-virtual function), the compiler will flag the function as an error.

```cpp
#include <string_view>

class A
{
public:
	virtual std::string_view getName1(int x) { return "A"; }
	virtual std::string_view getName2(int x) { return "A"; }
	virtual std::string_view getName3(int x) { return "A"; }
};

class B : public A
{
public:
	std::string_view getName1(short int x) override { return "B"; } // compile error, function is not an override
	std::string_view getName2(int x) const override { return "B"; } // compile error, function is not an override
	std::string_view getName3(int x) override { return "B"; } // okay, function is an override of A::getName3(int)

};

int main()
{
	return 0;
}
```

The above program produces two compile errors: one for B::getName1(), and one for B::getName2(), because neither override a prior function. B::getName3() does override A::getName3(), so no error is produced for that line.

Because there is no performance penalty for using the override specifier and it helps ensure you’ve actually overridden the function you think you have, all virtual override functions should be tagged using the override specifier. Additionally, because the override specifier implies virtual, there’s no need to tag functions using the override specifier with the virtual keyword.

>Best practice
	Use the virtual keyword on virtual functions in a base class.
	Use the override specifier (but not the virtual keyword) on override functions in derived classes. This includes virtual destructors.

>Rule
	If a member function is both `const` and an `override`, the `const` must be listed first. `const override` is correct, `override const` is not.

## The final specifier

### The `final` Specifier in C++

#### Definition

The **`final` specifier** in C++ is used to **restrict inheritance and overriding**.  
It tells the compiler that:

- A **virtual function** cannot be overridden further, **or**
    
- A **class** cannot be inherited from
    

If either rule is violated, the **compiler generates a compile-time error**.

### Why `final` is Needed

In object-oriented design, we sometimes want to:

- Preserve a specific behavior
    
- Prevent misuse of inheritance
    
- Protect critical logic from being changed
    
- Enforce strict class hierarchies
    

The `final` keyword allows us to **enforce these design rules at compile time**.

#### 1️⃣ Using `final` to Prevent Function Overriding

#### Concept

When `final` is applied to a **virtual function**, it means:

> This function can be overridden here, but **cannot be overridden again** in any derived class.

#### Example

```cpp
#include <string_view>

class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};

class B : public A
{
public:
    // This function overrides A::getName and is marked final
    std::string_view getName() const override final { return "B"; }
};

class C : public B
{
public:
    std::string_view getName() const override { return "C"; } 
    // ❌ Compile-time error
};
```

#### Explanation

- `A::getName()` is virtual and can be overridden
    
- `B::getName()` **overrides** `A::getName()` ✔️
    
- `B::getName()` is marked `final`
    
- `C::getName()` tries to override a **final function** ❌
    

📌 Result: **Compiler error**

> The `override` keyword in class `C` is not the cause of the error;  
> the error occurs because the base function is `final`.

### Key Point

```cpp
std::string_view getName() const override final;
```

- `override` → ensures correct overriding
    
- `final` → prevents further overriding

### 2️⃣ Using `final` to Prevent Class Inheritance

#### Concept

When `final` is applied to a **class**, it means:

> No other class is allowed to inherit from it.

#### Example

```cpp
#include <string_view>

class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};

class B final : public A
{
public:
    std::string_view getName() const override { return "B"; }
};

class C : public B
{
    // ❌ Compile-time error
};
```

#### Explanation

- `B` inherits from `A` ✔️
    
- `B` is declared as `final`
    
- `C` attempts to inherit from `B` ❌
    

📌 Result: **Compiler error: cannot inherit from final class**

### 3️⃣ Summary Table

|Usage|Purpose|
|---|---|
|`virtual func() final`|Prevents further overriding|
|`class X final`|Prevents inheritance|
|Error type|Compile-time|
|Runtime cost|None|

### ✅ Use `final` when:

- A class represents a **complete, closed design**
    
- A function’s behavior **must not change**
    
- You want **strong compile-time safety**
    
- You want better **compiler optimizations**
    

### ❌ Avoid `final` when:

- You expect future extension
    
- You are designing a base framework/library

### 5️⃣ Important Notes

- `final` works **only with virtual functions**
    
- `final` is checked **at compile time**
    
- `final` improves **code safety and clarity**
    
- `final` does **not affect runtime polymorphism** unless overriding is blocked

## Covariant return types

### 1. What is a covariant return type?

Normally, when a **derived class overrides a virtual function**, the **return type must be exactly the same** as in the base class.

👉 **Exception (Special Case):**  
If the return type is a **pointer or reference to a class**, then the derived class is allowed to return a **pointer or reference to a derived class**.

This feature is called **covariant return types**.

### 2. Basic Rule

If:

- Base class function returns:

```
Base*   or   Base&
```

Derived class may return:

```cpp
Derived*   or   Derived&
```

✅ Allowed because `Derived` **is-a** `Base`

❌ Not allowed for:

- Value returns (objects by value)
    
- Unrelated types
    
- Built-in types (`int`, `double`, etc.)

### 3. Your Example Explained

#### Base class

```cpp
class Base
{
public:
    virtual Base* getThis()
    {
        std::cout << "called Base::getThis()\n";
        return this;
    }

    void printType()
    {
        std::cout << "returned a Base\n";
    }
};
```

- `getThis()` returns `Base*`
    
- `printType()` is **non-virtual**

#### Derived class

```cpp
class Derived : public Base
{
public:
    Derived* getThis() override
    {
        std::cout << "called Derived::getThis()\n";
        return this;
    }

    void printType()
    {
        std::cout << "returned a Derived\n";
    }
};
```

- `Derived::getThis()` returns `Derived*`
    
- This is **legal** due to **covariant return type**
    
- `printType()` is also **non-virtual**

### 4. Case 1: Calling through a `Derived` object

```cpp
Derived d{};
d.getThis()->printType();
```

#### What happens?

1. `d` is a **Derived object**
    
2. `Derived::getThis()` is called
    
3. Return type is `Derived*`
    
4. `printType()` is resolved **at compile time**
    
5. Calls `Derived::printType()`
    

#### Output:

```cpp
called Derived::getThis()
returned a Derived
```

✅ You get a **Derived*** and **Derived behavior**

### 5. Case 2: Calling through a `Base*` pointer

```cpp
Base* b{ &d };
b->getThis()->printType();
```

#### Step-by-step:

1. `b` is a **Base pointer** pointing to a `Derived` object
    
2. `getThis()` is **virtual**
    
    - Calls `Derived::getThis()`
        
3. `Derived::getThis()` returns a `Derived*`
    
4. But the **expected return type is `Base*`**
    
    - So the compiler **upcasts** `Derived* → Base*`
        
5. `printType()` is **non-virtual**
    
    - So it is resolved using the **static type (`Base*`)**
        

#### Output:

```cpp
called Derived::getThis()
returned a Base
```

⚠️ Even though `Derived::getThis()` ran, the returned pointer is treated as `Base*`.

### 6. Key Concept: Static vs Dynamic Type

|Aspect|Used Type|
|---|---|
|Virtual function call|**Dynamic type**|
|Return type|**Static type**|
|Non-virtual function|**Static type**|

👉 **C++ cannot dynamically change the return type** based on runtime object.

### 7. What if `printType()` were virtual?

If `printType()` were declared `virtual`:

```cpp
virtual void printType();
```

Then this call:

```cpp
b->getThis()->printType();
```

Would result in:

```cpp
called Derived::getThis()
returned a Derived
```

Because:

- `printType()` would be resolved **dynamically**
    
- Runtime object is `Derived`

### 8. Important Notes

✔ Covariant return types:

- Work **only with pointers and references**
    
- Require inheritance relationship
    
- Only apply to **virtual functions**
    

❌ Not allowed:

```cpp
Base getThis();      // ❌
Derived getThis();   // ❌ (object return)
```

### 9. Why Are Covariant Return Types Useful?

They are commonly used when:

- A function returns `this`
    
- Factory methods
    
- Fluent interfaces
    
- Clone patterns
    

Example:

```cpp
virtual Base* clone();
Derived* clone() override;
```

This allows:

- Base users to work with `Base*`
    
- Derived users to get `Derived*` without casting

### 10. One-Line Exam Definition ⭐

> **Covariant return types allow an overriding virtual function in a derived class to return a pointer or reference to a derived type instead of the base type.**

---
# Virtual destructors, virtual assignment, and overriding virtualization

# Virtual Destructors

### ❓ The problem

When you use **inheritance** and delete an object through a **base class pointer**, C++ must know which destructor to call.

If the **base class destructor is NOT virtual**, then:

```cpp
Base* base = new Derived();
delete base;
```

C++ sees the pointer type (`Base*`) and **only calls `~Base()`**, skipping `~Derived()`.

Result:

- `Derived` resources (like `m_array`) **are not freed**
    
- Causes **memory leaks**
    
- Dangerous if Derived allocated memory or opened files, etc.

### ✔ The fix

Make the **Base destructor virtual**:

```cpp
class Base {
public:
    virtual ~Base() {
        cout << "Calling ~Base()\n";
    }
};
```

Now C++ performs **dynamic dispatch** (runtime lookup) and calls:

1. `~Derived()` ← cleans Derived resources
    
2. `~Base()` ← cleans Base part
    

Output becomes:

```cpp
Calling ~Derived()
Calling ~Base()
```

This is what we _actually want_.

### 🧠 Why does it work?

Because `virtual` tells C++:

> "Decide at runtime which destructor belongs to the real object type, not the pointer type."

So even though the pointer is `Base*`, C++ checks the actual object (`Derived`) and runs its destructor first.

### 📌 Key Rule

**Always make destructors virtual in a base class if inheritance is involved and you plan to delete objects using a base pointer.**

### 🔎 Extra notes

- If Base has `virtual ~Base()`, you **don’t need** to write `virtual` again in Derived (it's already virtual implicitly).
    
- You **don’t need** an empty destructor in Derived just to make it virtual.
    
- If you want an empty virtual destructor in Base, write:

```cpp
virtual ~Base() = default;
```

This generates a normal destructor but still virtual.

### 🚩 Your first code was leaking memory

Because Base destructor was not virtual, this line:

```cpp
delete base;
```

Only ran `~Base()` → `~Derived()` never executed → `delete[] m_array` never happened.

## Ignoring virtualization

Very rarely you may want to ignore the virtualization of a function. For example, consider the following code:

```cpp
#include <string_view>
class Base
{
public:
    virtual ~Base() = default;
    virtual std::string_view getName() const { return "Base"; }
};

class Derived: public Base
{
public:
    virtual std::string_view getName() const { return "Derived"; }
};
```

There may be cases where you want a Base pointer to a Derived object to call Base::getName() instead of Derived::getName(). To do so, simply use the scope resolution operator:

```cpp
#include <iostream>
int main()
{
    Derived derived {};
    const Base& base { derived };

    // Calls Base::getName() instead of the virtualized Derived::getName()
    std::cout << base.Base::getName() << '\n';

    return 0;
}
```

You probably won’t use this very often, but it’s good to know it’s at least possible.

## Should we make all destructors virtual?

### ❓ Should we make **all destructors virtual**?

**No. Not always.**

### ⚖ Why not?

Because when you mark a destructor `virtual`, C++ adds a **vptr (virtual pointer)** to every object instance.

**Cost of vptr:**

- Extra memory per object (usually 8 bytes on 64-bit systems)
    
- Slight runtime overhead
    
- Not needed if the class will never be a base class
    

So doing it blindly = unnecessary performance/memory penalty.

### ✅ When you **should** make the destructor virtual

Make it `virtual` **only if** the class is meant to support inheritance **or already has virtual functions**.

Example:

```cpp
class Animal {  // Designed for inheritance
public:
    virtual ~Animal() = default;  // Must be virtual
    virtual void sound() = 0;
};
```

Reason: You might delete derived objects using `Animal*`, so you need proper destructor dispatch.

### ❌ When you **should not**

If the class is **not designed to be a base class**, keep it simple:

```cpp
class MathHelper { // Not intended for inheritance
public:
    ~MathHelper() = default; // Not virtual
};
```

You can still reuse this class using **composition (has-a)** instead of inheritance.

### 🛑 How to enforce "No one can inherit this class"?

Use `final`:

```cpp
class DatabaseConnection final {
public:
    ~DatabaseConnection() = default;
};
```

Now:

- No class can inherit from it
    
- No vptr is added (better performance)
    
- Class remains fully usable

### 📌 Best Practice Summary

|Intent of class|What to do|
|---|---|
|Class **will be inherited**|`public virtual ~Class()`|
|Class **has virtual functions**|Destructor must also be `virtual`|
|Class **should NOT be inherited**|Mark class `final` and keep destructor non-virtual|

### 🧠 What about the old advice?

> “Destructor should be **public + virtual** OR **protected + non-virtual**”

Protected non-virtual destructor prevents this unsafe delete:

```cpp
Base* b = new Derived();
delete b;  // ❌ not allowed if ~Base is protected
```

But it also creates big usability issues:

- You **can’t** do:

```cpp
Base b;  // ❌ destructor not accessible when going out of scope
```

You **can’t** safely delete base objects allocated with `new`

```cpp
Base* b = new Base();
delete b; // ❌ destructor not accessible
```

So the class becomes almost unusable by itself.  
That’s why this method is **not recommended anymore**.

### 🎯 Modern solution is better

Instead of making destructors virtual everywhere or hiding them:

```cpp
class MyClass final {  // Explicitly blocks inheritance
public:
    ~MyClass() = default;
};
```

This gives:

- Safety (no inheritance misuse)
    
- Performance (no vptr)
    
- Usability (object can be created and destroyed normally)

### Final takeaway

> **Only make destructors virtual when inheritance is intended. Otherwise mark the class final and avoid virtual overhead.**

---
# Early binding and late binding (Optional Read)

>In this lesson and the next, we are going to take a closer look at how virtual functions are implemented. While this information is not strictly necessary to effectively use virtual functions, it is interesting. Nevertheless, you can consider both sections optional reading.

==When a program is compiled, the compiler converts each statement in your C++ program into one or more lines of machine language. Each line of machine language is given its own unique sequential address. This is no different for functions -- when a function is encountered, it is converted into machine language and given the next available address. Thus, each function ends up with a unique address.

### **How function calls work at CPU level**

- A C++ program runs **line by line** starting from `main()`.
    
- When you call a function like `add()`, the CPU needs to **jump to that function’s code**.
    
- The CPU knows where to jump because:
    
    - During compilation, every line of code is converted into **machine instructions**.
        
    - Each instruction gets a **unique memory address**.
        
    - Each function also gets a **starting address** where its machine code lives.
        
    - So every function ends up having its own **fixed address** in the compiled program.

### **Binding vs Dispatching**

- **Binding** = Deciding _which function belongs to a function call_.
    
    - Example: when you write `int x`, name `x` gets bound to type `int`.
        
    - For functions, binding means: _matching the function call to the actual function definition_.
        
- **Dispatching** = _Actually calling/invoking the function at runtime_ (jumping to its address and executing it).

### **Early Binding (Static Binding)**

- Happens at **compile-time**.
    
- Used when calling:
    
    - Normal functions
        
    - Non-virtual class member functions
        
    - Overloaded functions
        
    - Templates


```cpp
#include <iostream>

struct Foo
{
    void printValue(int value)
    {
        std::cout << value;
    }
};

void printValue(int value)
{
    std::cout << value;
}

int main()
{
    printValue(5);   // direct function call to printValue(int)

    Foo f{};
    f.printValue(5); // direct function call to Foo::printValue(int)
    return 0;
}
```

```cpp
printValue(5);
f.printValue(5);
```

- The compiler already knows **exactly which function to call**, so it generates instructions like:
    
    > _Jump directly to address 0x1234 (example address)_
    
- **Important Note**:  
    Even if a `switch` decides between `add`, `subtract`, or `multiply` at runtime, the compiler still knows the address of each function beforehand — so binding is still early.
    

**Efficiency**:

- Fast, because CPU jumps **directly** to the function address.

Let’s take a look at a simple calculator program that uses early binding:

```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int main()
{
    int x{};
    std::cout << "Enter a number: ";
    std::cin >> x;

    int y{};
    std::cout << "Enter another number: ";
    std::cin >> y;

    int op{};
    std::cout << "Enter an operation (0=add, 1=subtract, 2=multiply): ";
    std::cin >> op;

    int result {};
    switch (op)
    {
        // call the target function directly using early binding
        case 0: result = add(x, y); break;
        case 1: result = subtract(x, y); break;
        case 2: result = multiply(x, y); break;
        default:
            std::cout << "Invalid operator\n";
            return 1;
    }

    std::cout << "The answer is: " << result << '\n';

    return 0;
}
```

Because `add()`, `subtract()`, and `multiply()` are all direct function calls to non-member functions, the compiler will match these function calls to their respective function definitions at compile-time.

Note that because of the switch statement, which function is actually called is not determined until runtime. However, that is a path of execution issue, not a binding issue.

### **Late Binding (Dynamic Dispatch)**

- Happens at **runtime**.
    
- Compiler **cannot know** which function will be called at compile time.
    
- One way this happens: **function pointers**

```cpp
#include <iostream>

void printValue(int value)
{
    std::cout << value << '\n';
}

int main()
{
    auto fcn { printValue }; // create a function pointer and make it point to function printValue
    fcn(5);                  // invoke printValue indirectly through the function pointer

    return 0;
}
```

- Here the compiler does _not_ know what `fcn()` will call — it only knows that `fcn` holds an address.
    
- At runtime, the program:
    
    1. Reads the address stored inside the pointer
        
    2. Then jumps to that address
        

So instead of:

> Jump to 0x5678

It becomes:

> Read pointer → get 0x5678 → Jump there

**Efficiency**:

- Slightly slower than early binding because of **one extra step (indirection)**.
    
- But **more flexible**, because the function can be chosen while the program is running.
    

### **Final Summary**

|Concept|When it happens|Used for|Speed|Flexibility|
|---|---|---|---|---|
|**Early Binding**|Compile-time|Normal + non-virtual + overloads + templates|Faster (direct jump)|Less flexible|
|**Late Binding**|Runtime|Function pointers, virtual functions (via vtable)|Slightly slower (indirect jump)|More flexible|

### **Key Takeaways**

- Function addresses are **fixed during compilation**.
    
- **Binding** = matching call to function, **Dispatching** = executing it.
    
- **Early binding is faster**, **late binding is more flexible**.
    
- Virtual functions use **late binding via vtable**, function pointers use **late binding via stored addresses**.

---
