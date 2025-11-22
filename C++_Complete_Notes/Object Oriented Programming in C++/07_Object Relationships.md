The paragraph explains how humans naturally understand **patterns, hierarchies, and relationships** between objects in the real world. When you recognize a plant—even one you've never seen before—you can still understand a lot about it because you know the **general abstraction** called “plant” and the relationships its parts have (leaf → part of plant, flower → depends on plant, etc.).

Object-oriented programming (OOP) uses **the same idea**:  
we create objects, give them properties, and connect them using different types of **relationships** just like real-world objects.

Now let’s connect each of the relationship types mentioned in the paragraph with examples from real life and then show how they relate to **C++ programming**.

### Real-life example:

A square **is-a** shape.  
A rose **is-a** flower.

### Programming analogy:

This is **inheritance** in C++.

Not covered yet—but will be explored later in your learning.

## **HOW THIS ALL CONNECTS TO THE PARAGRAPH**

The paragraph explains that we understand new objects because we recognize **abstract relationships** among things.

Similarly, in C++:

- We understand how objects work by defining relationships between them.
    
- These relationships help make code more organized, reusable, and more like real-life logical structures.
    

You already used simple patterns like:

✔ loops  
✔ functions  
✔ arrays  
✔ recursion  
✔ classes

Now you're moving to more advanced concepts:

➡ **how objects relate to each other**  
➡ **how to design systems (like real-life)**  
➡ **how to make re-usable, extensible code**

Just like understanding plants helps you understand a new plant,  
understanding object relationships helps you understand new code.

---
# Composition

### Object composition

>Object composition is building complex object by using simpler object.
>

Broadly speaking, object composition models a “has-a” relationship between two objects. A car “has-a” transmission. Your computer “has-a” CPU. You “have-a” heart. The complex object is sometimes called the whole, or the parent. The simpler object is often called the part, child, or component.

In C++, you’ve already seen that structs and classes can have data members of various types (such as fundamental types or other classes). When we build classes with data members, we’re essentially constructing a complex object from simpler parts, which is object composition. For this reason, structs and classes are sometimes referred to as **composite types**.

>Object Composition is useful in a C++ context because it allows us to create complex classes by combining simpler

### Types of object composition

- Composition
- Aggregation

>[!Note]
>A note on terminology: the term “composition” is often used to refer to both composition and aggregation, not just to the composition subtype. In this tutorial, we’ll use the term “object composition” when we’re referring to both, and “composition” when we’re referring specifically to the composition subtype.

### Composition

> Composition is "has-a" relationship but it can also be "Part-of" relationship.
> 

Composition is a **strong “part-of” relationship** between two things (in C++: between a class and its data members).

It means:

- One object is made up of other objects(Member)
    
- Those parts **cannot exist independently** from the main object
    
- Their lifetime is controlled (managed) by the main object
    
- The part does _not_ know it belongs to the whole
    

Let’s break down each condition one by one.

### **1. The part is _part of_ the object**

This is the basic requirement.

Example:  
A **heart** is _part of_ a **person’s body**.  
A **denominator** is _part of_ a **Fraction object**.

In C++:

```cpp
class Fraction {
private:
    int m_numerator;     // part of
    int m_denominator;   // part of
};
```

The numerator and denominator **exist inside** the Fraction object.  
They are literally “contained” in it.

#### **2. The part can only belong to one object at a time**

A heart cannot belong to two people simultaneously.  
It is part of only _one_ body at any given moment.

In C++:  
`m_numerator` and `m_denominator` belong to **one** specific Fraction object.  
They cannot be shared between multiple Fraction objects.

If you create two Fractions:

```cpp
Fraction f1;
Fraction f2;
```

Each Fraction has **its own separate** numerator and denominator.

#### **3. The object's lifetime controls the part’s lifetime**

This is the strongest characteristic of composition.

- When the whole is created → the parts are created.
    
- When the whole is destroyed → the parts are destroyed.
    

This is why composition is sometimes called the **“death relationship”**.

Example:

- When a person is born → their heart is created.
    
- When the person dies → the heart stops existing (in terms of belonging to that body).
    

In C++:

```cpp
Fraction f{3, 4};  // numerator and denominator are created here

// when f goes out of scope:
} // numerator and denominator are destroyed automatically
```

You never manage the lifetime of numerator/denominator separately.

#### **4. The part does _not_ know the whole**

This is very important.

- A heart **does not know** it belongs to a person.
    
- It just beats.
    
- It has no idea it’s part of something larger.
    

In C++:

`m_numerator` and `m_denominator` are just `int`s.  
They do not know they are part of a Fraction.

```cpp
int m_numerator;  
// It doesn’t know it's inside Fraction
```

This is called a **unidirectional relationship**:

- The whole knows the part
    
- The part does NOT know the whole

### **Real-world analogy recap**

You → know you have a heart  
Your heart → has no idea you exist

Fraction → knows it has a numerator  
Numerator → no idea it belongs to a Fraction

>A heart can be transplanted.  
>
  But still, after transfer:

- It belongs to exactly one person
    
- That person manages its existence
    
- It still doesn’t know who owns it
    

So it still qualifies as composition.

Same for C++:  
An object can transfer ownership of its part to another object, but the relationship still counts as composition.

### **Composition usually models physical containment**

Examples:

- A body is made of organs
    
- A house is made of rooms
    
- A car is made of an engine, tires, etc.
    
- A Fraction is made of two integers
    

Composition is the best way to model things that are:

- **physically part-of** something
    
- **exclusively owned**
    
- **lifetime-dependent**

### **Parts can be single or multiple**

- A body has **1 heart** → singular
    
- A body has **10 fingers** → multiple (usually represented in arrays or vectors)
    

In C++:

```cpp
class Body {
    Heart heart;               // singular part
    std::array<Finger, 10> fingers; // multiple parts
};
```

### **In Summary (Short Version)**

**Composition = Strong part-of relationship**

✔ the part is inside the whole  
✔ belongs to only one whole  
✔ lifetime is controlled by the whole  
✔ part doesn’t know the whole  
✔ often used to model physical containment  
✔ can be one part or many parts

### Implementing compositions

Compositions are one of the easiest relationship types to implement in C++. They are typically created as structs or classes with normal data members. Because these data members exist directly as part of the struct/class, their lifetimes are bound to that of the class instance itself.

Compositions that need to do dynamic allocation or deallocation may be implemented using pointer data members. In this case, the composition class should be responsible for doing all necessary memory management itself (not the user of the class).

In general, if you _can_ design a class using composition, you _should_ design a class using composition. Classes designed using composition are straightforward, flexible, and robust (in that they clean up after themselves nicely).

### More examples

Many games and simulations have creatures or objects that move around a board, map, or screen. One thing that all of these creatures/objects have in common is that they all have a location. In this example, we are going to create a creature class that uses a point class to hold the creature’s location.

First, let’s design the point class. Our creature is going to live in a 2d world, so our point class will have 2 dimensions, X and Y. We will assume the world is made up of discrete squares, so these dimensions will always be integers.

Point2D.h:

```cpp
#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>

class Point2D
{
private:
    int m_x;
    int m_y;

public:
    // A default constructor
    Point2D()
        : m_x{ 0 }, m_y{ 0 }
    {
    }

    // A specific constructor
    Point2D(int x, int y)
        : m_x{ x }, m_y{ y }
    {
    }

    // An overloaded output operator
    friend std::ostream& operator<<(std::ostream& out, const Point2D& point)
    {
        out << '(' << point.m_x << ", " << point.m_y << ')';
        return out;
    }

    // Access functions
    void setPoint(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

};

#endif
```

Note that because we’ve implemented all of our functions in the header file (for the sake of keeping the example concise), there is no Point2D.cpp.

This Point2d class is a composition of its parts: location values x and y are part-of Point2D, and their lifespan is tied to that of a given Point2D instance.

Now let’s design our Creature. Our Creature is going to have a few properties: a name, which will be a string, and a location, which will be our Point2D class.

Creature.h:

```cpp
#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <string_view>
#include "Point2D.h"

class Creature
{
private:
    std::string m_name;
    Point2D m_location;

public:
    Creature(std::string_view name, const Point2D& location)
        : m_name{ name }, m_location{ location }
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Creature& creature)
    {
        out << creature.m_name << " is at " << creature.m_location;
        return out;
    }

    void moveTo(int x, int y)
    {
        m_location.setPoint(x, y);
    }
};
#endif
```

This Creature is also a composition of its parts. The creature’s name and location have one parent, and their lifetime is tied to that of the Creature they are part of.

And finally, main.cpp:

```cpp
#include <string>
#include <iostream>
#include "Creature.h"
#include "Point2D.h"

int main()
{
    std::cout << "Enter a name for your creature: ";
    std::string name;
    std::cin >> name;
    Creature creature{ name, { 4, 7 } };

    while (true)
    {
        // print the creature's name and location
        std::cout << creature << '\n';

        std::cout << "Enter new X location for creature (-1 to quit): ";
        int x{ 0 };
        std::cin >> x;
        if (x == -1)
            break;

        std::cout << "Enter new Y location for creature (-1 to quit): ";
        int y{ 0 };
        std::cin >> y;
        if (y == -1)
            break;

        creature.moveTo(x, y);
    }

    return 0;
}
```

Here’s a transcript of this code being run:

`Enter a name for your creature: Marvin
Marvin is at (4, 7)
Enter new X location for creature (-1 to quit): 6
Enter new Y location for creature (-1 to quit): 12
Marvin is at (6, 12)
Enter new X location for creature (-1 to quit): 3
Enter new Y location for creature (-1 to quit): 2
Marvin is at (3, 2)
Enter new X location for creature (-1 to quit): -1`

### Variants on the composition theme

Although most compositions directly create their parts when the composition is created and directly destroy their parts when the composition is destroyed, there are some variations of composition that bend these rules a bit.

>[!Key]
>The key point here is that the composition should manage its parts without the user of the composition needing to manage anything.

### Composition and class members

One question that new programmers often ask when it comes to object composition is, “When should I use a class member instead of direct implementation of a feature?”. For example, instead of using the Point2D class to implement the Creature’s location, we could have instead just added 2 integers to the Creature class and written code in the Creature class to handle the positioning. However, making Point2D its own class (and a member of Creature) has a number of benefits:

1. Each individual class can be kept relatively simple and straightforward, focused on performing one task well. This makes those classes easier to write and much easier to understand, as they are more focused. For example, Point2D only worries about point-related stuff, which helps keep it simple.
2. Each class can be self-contained, which makes them reusable. For example, we could reuse our Point2D class in a completely different application. Or if our creature ever needed another point (for example, a destination it was trying to get to), we can simply add another Point2D member variable.
3. The outer class can have the class members do most of the hard work, and instead focus on coordinating the data flow between the members . This helps lower the overall complexity of the outer class, because it can delegate tasks to its members, who already know how to do those tasks. For example, when we move our Creature, it delegates that task to the Point class, which already understands how to set a point. Thus, the Creature class does not have to worry about how such things would be implemented.

>[!Tip]
>A good rule of thumb is that each class should be built to accomplish a single task. That task should either be the storage and manipulation of some kind of data (e.g. Point2D, std::string), OR the coordination of its members (e.g. Creature). Ideally not both.

In this case of our example, it makes sense that Creature shouldn’t have to worry about how Points are implemented, or how the name is being stored. Creature’s job isn’t to know those intimate details. Creature’s job is to worry about how to coordinate the data flow and ensure that each of the class members knows _what_ it is supposed to do. It’s up to the individual classes to worry about _how_ they will do it.

---
