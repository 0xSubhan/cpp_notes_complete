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
# Aggregation

To qualify as an **aggregation**, a whole object and its parts must have the following relationship:

- The part (member) is part of the object (class)
- The part (member) can (if desired) belong to more than one object (class) at a time
- The part (member) does _not_ have its existence managed by the object (class)
- The part (member) does not know about the existence of the object (class)

>Like a composition, an aggregation is still a part-whole relationship, where the parts are contained within the whole, and it is a unidirectional relationship. However, unlike a composition, parts can belong to more than one object at a time, and the whole object is not responsible for the existence and lifespan of the parts. When an aggregation is created, the aggregation is not responsible for creating the parts. When an aggregation is destroyed, the aggregation is not responsible for destroying the parts.

For example, consider the relationship between a person and their home address. In this example, for simplicity, we’ll say every person has an address. However, that address can belong to more than one person at a time: for example, to both you and your roommate or significant other. However, that address isn’t managed by the person -- the address probably existed before the person got there, and will exist after the person is gone. Additionally, a person knows what address they live at, but the addresses don’t know what people live there. Therefore, this is an aggregate relationship.

>Alternatively, consider a car and an engine. A car engine is part of the car. And although the engine belongs to the car, it can belong to other things as well, like the person who owns the car. The car is not responsible for the creation or destruction of the engine. And while the car knows it has an engine (it has to in order to get anywhere) the engine doesn’t know it’s part of the car.

When it comes to modeling physical objects, the use of the term “destroyed” can be a little dicey. One might argue, “If a meteor fell out of the sky and crushed the car, wouldn’t the car parts all be destroyed too?” Yes, of course. But that’s the fault of the meteor. The important point is that the car is not responsible for destruction of its parts (but an external force might be).

We can say that aggregation models “has-a” relationships (a department has teachers, the car has an engine).

Similar to a composition, the parts of an aggregation can be singular or multiplicative.

### Implementing aggregations

Aggregation is a **weaker form of the “part-of” relationship** compared to composition.

Both composition and aggregation are part-whole relationships, but the **key difference** is:

> **In aggregation, the whole does NOT own the part.  
> The part can outlive the whole.**

This is why aggregation is also called a **“shared ownership” or “has-a (but doesn’t own)”** relationship.

#### How Aggregation is Implemented

Aggregation is implemented similarly to composition, but with one crucial difference:

##### ✔ Composition uses _actual_ member objects

##### ✔ Aggregation uses _references or pointers_ to objects created elsewhere

Meaning:

##### 🔹 The parts are **NOT** created inside the class

##### 🔹 The class only **points** to objects created outside

##### 🔹 When the class is destroyed, it does **NOT** destroy those objects

### ✔ **How Aggregation Works Internally**

#### 1. **Parts come from outside the class**

The aggregating object (the “whole”) does not create the parts.  
They are passed in or added later.

#### 2. **Member variable is a pointer or reference**

Instead of:

```cpp
Teacher m_teacher; // would be composition
```

We Use:

```cpp
const Teacher& m_teacher; // aggregation
```

This means “I refer to a Teacher, but I don’t own it.”

#### 3. **When the aggregator dies, the part stays alive**

Only the pointer/reference member is destroyed, not the object it pointed to.

### ⭐ **Example: Teacher & Department**

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Teacher
{
private:
  std::string m_name{};

public:
  Teacher(std::string_view name)
      : m_name{ name }
  {
  }

  const std::string& getName() const { return m_name; }
};

class Department
{
private:
  const Teacher& m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers

public:
  Department(const Teacher& teacher)
      : m_teacher{ teacher }
  {
  }
};

int main()
{
  // Create a teacher outside the scope of the Department
  Teacher bob{ "Bob" }; // create a teacher

  {
    // Create a department and use the constructor parameter to pass
    // the teacher to it.
    Department department{ bob };

  } // department goes out of scope here and is destroyed

  // bob still exists here, but the department doesn't

  std::cout << bob.getName() << " still exists!\n";

  return 0;
}
```

#### 🔸 **Teacher bob is created first**

He exists independently.

```cpp
Teacher bob{ "Bob" };
```

#### 🔸 Then Department is created, and it receives a reference to bob

```cpp
Department department{ bob };
```

- Department _does not_ own bob
    
- It only **refers** to bob
    
- bob lives outside Department
    

#### 🔸 When Department goes out of scope, it is destroyed

```cpp
} // department is destroyed here
```

But bob **still exists**, because Department did NOT create bob and does NOT manage bob's lifetime.

### 🔍 **Why this is Aggregation (not Composition)?**

Let’s check the rules:

#### **1. Part is part of the whole?**

Yes.  
A Department _has-a_ Teacher.

#### **2. Part can belong to many wholes?**

Yes.  
A Teacher can be associated with multiple Departments (in a bigger example).

In composition, this would NOT be allowed.

#### **3. Whole does NOT manage the part’s lifetime**

✔ Correct — this is the BIG difference.

- Department does NOT create Teacher
    
- Department does NOT destroy Teacher
    

bob continues existing after Department is gone.

#### **4. The part may or may not know about the whole**

In this example:

- Teacher does NOT know about Department
    
- The relationship is **unidirectional**
    

(This can also happen in composition, but it's more common in aggregation.)

### 🎯 **Key Points in the Code**

### ✔ `Teacher bob{ "Bob" };`

Teacher bob is created in main().  
He exists independently.

### ✔ `Department department{ bob };`

Department receives a **reference** to bob.

### ✔ `m_teacher` is a reference

So Department does NOT own or manage bob.

### ✔ Department is destroyed when the inner scope ends

But bob is NOT destroyed.

### 🔵 **Aggregation vs Composition Summary**

|Feature|Composition|Aggregation|
|---|---|---|
|Ownership|Whole _owns_ the part|Whole _uses_ the part but doesn't own it|
|Lifetime|Part dies with whole|Part lives independently|
|Implementation|Member object|Pointer or reference|
|Example|Person → Heart|Department → Teacher|
|Strong or weak?|Strong relationship|Weak relationship|

### Pick the right relationship for what you’re modeling

Although it might seem a little silly in the above example that the Teachers don’t know what Department they’re working for, that may be totally fine in the context of a given program. When you’re determining what kind of relationship to implement, implement the simplest relationship that meets your needs, not the one that seems like it would fit best in a real-life context.

>For example, if you’re writing a body shop simulator, you may want to implement a car and engine as an aggregation, so the engine can be removed and put on a shelf somewhere for later. However, if you’re writing a racing simulation, you may want to implement a car and an engine as a composition, since the engine will never exist outside of the car in that context.

>[!Tip]
>Implement the simplest relationship type that meets the needs of your program, not what seems right in real-life.

### Summarizing composition and aggregation

Compositions:

- Typically use normal member variables
- Can use pointer members if the class handles object allocation/deallocation itself
- Responsible for creation/destruction of parts

Aggregations:

- Typically use pointer or reference members that point to or reference objects that live outside the scope of the aggregate class
- Not responsible for creating/destroying parts

It is worth noting that the concepts of composition and aggregation can be mixed freely within the same class. It is entirely possible to write a class that is responsible for the creation/destruction of some parts but not others. For example, our Department class could have a name and a Teacher. The name would probably be added to the Department by composition, and would be created and destroyed with the Department. On the other hand, the Teacher would be added to the department by aggregation, and created/destroyed independently.

While aggregations can be extremely useful, they are also potentially more dangerous, because aggregations do not handle deallocation of their parts. Deallocations are left to an external party to do. If the external party no longer has a pointer or reference to the abandoned parts, or if it simply forgets to do the cleanup (assuming the class will handle that), then memory will be leaked.

For this reason, compositions should be favored over aggregations.

### std::reference_wrapper

In the `Department`/`Teacher` example above, we used a reference in the `Department` to store the `Teacher`. This works fine if there is only one `Teacher`, but what if a Department has multiple Teachers? We’d like to store those Teachers in a list of some kind (e.g. a `std::vector`) but fixed arrays and the various standard library lists can’t hold references (because list elements must be assignable, and references can’t be reassigned).

```cpp
std::vector<const Teacher&> m_teachers{}; // Illegal
```

Instead of references, we could use pointers, but that would open the possibility to store or pass null pointers. In the `Department`/`Teacher` example, we don’t want to allow null pointers. To solve this, there’s `std::reference_wrapper`.

Essentially, `std::reference_wrapper` is a class that acts like a reference, but also allows assignment and copying, so it’s compatible with lists like `std::vector`.

The good news is that you don’t really need to understand how it works to use it. All you need to know are three things:

1. `std::reference_wrapper` lives in the `<functional>` header.
2. When you create your `std::reference_wrapper` wrapped object, the object can’t be an anonymous object (since anonymous objects have expression scope, and this would leave the reference dangling).
3. When you want to get your object back out of `std::reference_wrapper`, you use the `get()` member function.

Here’s an example using `std::reference_wrapper` in a `std::vector`:

```cpp
#include <functional> // std::reference_wrapper
#include <iostream>
#include <vector>
#include <string>

int main()
{
  std::string tom{ "Tom" };
  std::string berta{ "Berta" };

  std::vector<std::reference_wrapper<std::string>> names{ tom, berta }; // these strings are stored by reference, not value

  std::string jim{ "Jim" };

  names.emplace_back(jim);

  for (auto name : names)
  {
    // Use the get() member function to get the referenced string.
    name.get() += " Beam";
  }

  std::cout << jim << '\n'; // prints Jim Beam

  return 0;
}
```

To create a vector of const references, we’d have to add const before the `std::string` like so

```cpp
// Vector of const references to std::string
std::vector<std::reference_wrapper<const std::string>> names{ tom, berta };
```

---
# Association

In the previous two lessons, we’ve looked at two types of object composition, composition and aggregation. Object composition is used to model relationships where a complex object is built from one or more simpler objects (parts).

In this lesson, we’ll take a look at a weaker type of relationship between two otherwise unrelated objects, called an association. Unlike object composition relationships, in an association, there is no implied whole/part relationship.

### ✅ **Association (Explained Simply + Clearly)**

Association is the **weakest** and most flexible relationship between two objects in OOP.

It means:

> **Two objects are connected or interact with each other,  
> but neither object owns the other,  
> neither object manages the other's lifetime,  
> and they are not part of each other.**

It is basically a **“uses-a”** relationship.

### 🔍 **To qualify as an Association, four things must be true**

Let’s break down each one.

#### **1. They are otherwise unrelated**

This means the two objects do NOT form a:

- part-of relationship (composition)
    
- has-a ownership relationship (aggregation)
    

They are just **connected**, not “contained.”

Example:  
A **doctor** and a **patient** are not physically part of each other.  
They interact, but one is not contained inside the other.

#### **2. The associated object can belong to many objects at the same time**

In association:

- A doctor can have **many** patients.
    
- A patient can have **many** doctors.
    

There is **no exclusivity** and **no ownership**.

This is different from composition (where a part belongs only to one whole).

#### **3. The associated object’s lifetime is NOT managed by the other object**

This is extremely important.

- Destroying the doctor object does **not** destroy the patient object.
    
- Destroying the patient object does **not** destroy the doctor object.
    

They live independently.

This is also true for aggregation — but in association, the objects are **not** in a part-whole structure at all.

#### **4. The associated object may or may not know about the existence of the other**

This is what makes association unique.

There are two possible types:

### ✔ **Unidirectional Association**

Only one object knows about the other.  
Example:  
A **patient** may keep a reference to their **doctor**,  
but the doctor does NOT store any reference to the patient.

### ✔ **Bidirectional Association**

Both know about each other.  
Example:  
A doctor has a list of patients,  
and each patient has a reference to their doctor.

In aggregation and composition, the relationship is typically **unidirectional**.

### ⭐ **Real-life Example: Doctors and Patients**

This is the perfect analogy for association because:

#### ✔ Not a part-whole relationship

Patients are not “part of” a doctor.  
Doctors are not “part of” a patient.

#### ✔ Many-to-many

One doctor can treat many patients.  
One patient can see many doctors.

#### ✔ Independent lifetimes

A doctor doesn’t cease to exist if a patient disappears  
(and vice versa).

#### ✔ They “use” each other

- A doctor _uses_ patients to earn money.
    
- A patient _uses_ a doctor for healthcare.
    

>This is why association is also called a **uses-a** relationship.

## Implementing associations

Because associations are a broad type of relationship, they can be implemented in many different ways. However, most often, associations are implemented using pointers, where the object points at the associated object.

In this example, we’ll implement a bi-directional Doctor/Patient relationship, since it makes sense for the Doctors to know who their Patients are, and vice-versa.

```cpp
#include <functional> // reference_wrapper
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// Since Doctor and Patient have a circular dependency, we're going to forward declare Patient
class Patient;

class Doctor
{
private:
	std::string m_name{};
	std::vector<std::reference_wrapper<const Patient>> m_patient{};

public:
	Doctor(std::string_view name) :
		m_name{ name }
	{
	}

	void addPatient(Patient& patient);

	// We'll implement this function below Patient since we need Patient to be defined at that point
	friend std::ostream& operator<<(std::ostream& out, const Doctor& doctor);

	const std::string& getName() const { return m_name; }
};

class Patient
{
private:
	std::string m_name{};
	std::vector<std::reference_wrapper<const Doctor>> m_doctor{}; // so that we can use it here

	// We're going to make addDoctor private because we don't want the public to use it.
	// They should use Doctor::addPatient() instead, which is publicly exposed
	void addDoctor(const Doctor& doctor)
	{
		m_doctor.push_back(doctor);
	}

public:
	Patient(std::string_view name)
		: m_name{ name }
	{
	}

	// We'll implement this function below to parallel operator<<(std::ostream&, const Doctor&)
	friend std::ostream& operator<<(std::ostream& out, const Patient& patient);

	const std::string& getName() const { return m_name; }

	// We'll friend Doctor::addPatient() so it can access the private function Patient::addDoctor()
	friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
	// Our doctor will add this patient
	m_patient.push_back(patient);

	// and the patient will also add this doctor
	patient.addDoctor(*this);
}

std::ostream& operator<<(std::ostream& out, const Doctor& doctor)
{
	if (doctor.m_patient.empty())
	{
		out << doctor.m_name << " has no patients right now";
		return out;
	}

	out << doctor.m_name << " is seeing patients: ";
	for (const auto& patient : doctor.m_patient)
		out << patient.get().getName() << ' ';

	return out;
}

std::ostream& operator<<(std::ostream& out, const Patient& patient)
{
	if (patient.m_doctor.empty())
	{
		out << patient.getName() << " has no doctors right now";
		return out;
	}

	out << patient.m_name << " is seeing doctors: ";
	for (const auto& doctor : patient.m_doctor)
		out << doctor.get().getName() << ' ';

	return out;
}

int main()
{
	// Create a Patient outside the scope of the Doctor
	Patient dave{ "Dave" };
	Patient frank{ "Frank" };
	Patient betsy{ "Betsy" };

	Doctor james{ "James" };
	Doctor scott{ "Scott" };

	james.addPatient(dave);

	scott.addPatient(dave);
	scott.addPatient(betsy);

	std::cout << james << '\n';
	std::cout << scott << '\n';
	std::cout << dave << '\n';
	std::cout << frank << '\n';
	std::cout << betsy << '\n';

	return 0;
}
```

#### 🧠 **In this example: Doctor ↔ Patient**

We choose to model a **bidirectional association**, meaning:

- A **Doctor** knows which **Patients** they treat.
    
- A **Patient** knows which **Doctors** they see.
    

This makes the relationship symmetrical just like in real life.

But it also makes the code more complicated, which is why the chapter warns:

> **Avoid bidirectional associations unless absolutely necessary.**

###  🔹 1. Circular dependency → Forward declaration

```cpp
class Patient;
```

Doctor needs to reference Patient,  
but Patient also needs to reference Doctor.

This is a classic circular dependency,  
so we forward declare Patient first.

#### 🔹 2. Doctor stores a list of Patients

```cpp
std::vector<std::reference_wrapper<const Patient>> m_patient{};
```

Why reference_wrapper?

- Because C++ cannot store plain references in containers.
    
- reference_wrapper behaves like a reference but is container-friendly.
    

Doctor stores **references**, not actual Patients →  
meaning Doctor does **not own** the Patients.

**This is exactly what an association requires.**

#### 🔹 3. Patient stores a list of Doctors

```cpp
std::vector<std::reference_wrapper<const Doctor>> m_doctor{};
```

Same idea:

- Patient does NOT own Doctors
    
- It's just storing references for the relationship

#### 🔹 4. Keeping the relationship consistent (bidirectional)

When we call:

```cpp
james.addPatient(dave);
```

We want:

- James to add Dave
    
- AND Dave to add James
    

To enforce that, we make this chain:

```cpp
void Doctor::addPatient(Patient& patient)
{
    m_patient.push_back(patient); // doctor adds patient
    patient.addDoctor(*this);     // patient adds doctor
}
```

This ensures both sides stay in sync.

#### 🔹 5. Patient::addDoctor is **private**

```cpp
void addDoctor(const Doctor& doctor)
{
    m_doctor.push_back(doctor);
}
```

Why private?

Because we don’t want external code doing:

```cpp
dave.addDoctor(james);   // ❌ WRONG use
```

We want all associations to be managed through Doctor::addPatient()  
to prevent mismatches like:

- Doctor thinks he has the patient
    
- Patient thinks he has no doctor
    

Thus, to give Doctor permission to call this private function:

```cpp
friend void Doctor::addPatient(Patient& patient);
```

#### 🔹 6. Printing operators (<<) show the associations

For doctor:

- If no patients → print a line
    
- Else print all patient names
    

For patient:

- Same thing reversed
    

These operators basically **read the association lists**.

#### 🔹 7. Lifetime Behavior

This is the key part of association:

```cpp
Patient dave{"Dave"};
Doctor james{"James"};

james.addPatient(dave);
```

Who owns whom?

- Dave exists independently
    
- James exists independently
    
- Destroying James does NOT destroy Dave
    
- Destroying Dave does NOT destroy James
    

Each object simply _references_ the other.

This matches the association rules perfectly.

#### Output (meaning)

```cpp
James is seeing patients: Dave
Scott is seeing patients: Dave Betsy
Dave is seeing doctors: James Scott
Frank has no doctors right now
Betsy is seeing doctors: Scott
```

Everything matches the relationships we built.

### 🚩 Why avoid bidirectional associations?

Because they introduce:

- extra complexity
    
- risk of inconsistent state
    
- harder debugging
    
- more interdependencies
    

A **unidirectional** association is often enough:

- Doctor → Patient  
    OR
    
- Patient → Doctor
    

But not both.

### ✨ Summary (In Simple Words)

**Association** is when:

- Objects are related, but not owned.
    
- They can both exist independently.
    
- They may know about each other (bidirectional) or only one way (unidirectional).
    
- Lifetimes are totally independent.
    

In implementation:

- You usually store **pointers** or **references** to other objects.
    
- You do **not** allocate or delete those objects.
    
- You simply keep a link to them.

## Reflexive association

Sometimes objects may have a relationship with other objects of the same type. This is called a **reflexive association**. A good example of a reflexive association is the relationship between a university course and its prerequisites (which are also university courses).

Consider the simplified case where a Course can only have one prerequisite. We can do something like this:

```cpp
#include <string>
#include <string_view>

class Course
{
private:
    std::string m_name{};
    const Course* m_prerequisite{};

public:
    Course(std::string_view name, const Course* prerequisite = nullptr):
        m_name{ name }, m_prerequisite{ prerequisite }
    {
    }

};
```

This can lead to a chain of associations (a course has a prerequisite, which has a prerequisite, etc…)

## Associations can be indirect

>In all of the previous cases, we’ve used either pointers or references to directly link objects together. However, in an association, this is not strictly required. Any kind of data that allows you to link two objects together suffices. In the following example, we show how a Driver class can have a unidirectional association with a Car without actually including a Car pointer or reference member:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Car
{
private:
	std::string m_name{};
	int m_id{};

public:
	Car(std::string_view name, int id)
		: m_name{ name }, m_id{ id }
	{
	}

	const std::string& getName() const { return m_name; }
	int getId() const { return m_id; }
};

// Our CarLot is essentially just a static array of Cars and a lookup function to retrieve them.
// Because it's static, we don't need to allocate an object of type CarLot to use it
namespace CarLot
{
    Car carLot[4] { { "Prius", 4 }, { "Corolla", 17 }, { "Accord", 84 }, { "Matrix", 62 } };

	Car* getCar(int id)
	{
		for (auto& car : carLot)
        {
			if (car.getId() == id)
			{
				return &car;
			}
		}

		return nullptr;
	}
};

class Driver
{
private:
	std::string m_name{};
	int m_carId{}; // we're associated with the Car by ID rather than pointer

public:
	Driver(std::string_view name, int carId)
		: m_name{ name }, m_carId{ carId }
	{
	}

	const std::string& getName() const { return m_name; }
	int getCarId() const { return m_carId; }
};

int main()
{
	Driver d{ "Franz", 17 }; // Franz is driving the car with ID 17

	Car* car{ CarLot::getCar(d.getCarId()) }; // Get that car from the car lot

	if (car)
		std::cout << d.getName() << " is driving a " << car->getName() << '\n';
	else
		std::cout << d.getName() << " couldn't find his car\n";

	return 0;
}
```

### ⭐ **Associations Can Be Indirect — Explained**

So far, you learned that **associations** (like “uses-a” relationships) are usually implemented using **pointers or references** — one object literally points to the other.

But **this is NOT the only way** to create an association.

An association only means:

- Object A _needs to access_ Object B
    
- But Object B is _not owned_ by A
    
- And B exists _independently_ of A
    

How they connect does **not** have to be a pointer.

### 🔵 **What the Example Shows**

### Instead of:

`Driver` → pointer to → `Car`

We use:  
`Driver` → **car ID** → `Car`

The **ID** acts as an indirect link.

The driver says:

> “I use the car whose ID is **17**”,  
> instead of  
> “I use this exact Car object in memory.”

Later, we can use that ID to look up the real Car in a car storage system (`CarLot`).

### 🔵 **Why Is This Still an Association?**

Because:

- The **Driver uses a Car** → that’s an association
    
- But the **Driver does not own the Car**
    
- And their lifetimes are **independent**
    
- And the **Driver only stores an ID**, not an actual pointer
    

This is called an **indirect association**.

## 🔵 **Walkthrough of the Example**

### 1️⃣ The `Car` class

Each car has:

- A name (`Prius`, `Corolla`, etc.)
    
- A unique ID (4, 17, 84…)
    

### 2️⃣ The `CarLot` namespace

This is like a garage with all the cars:

```cpp
CarLot::carLot[4] = { Prius, Corolla, Accord, Matrix };
```

And a helper function:

```cpp
Car* getCar(int id);
```

This searches the lot and returns the matching car.

### 3️⃣ The `Driver` class

Instead of storing a pointer to a Car, the driver stores:

```cpp
int m_carId;
```

This is the key to which car they are associated with.

### 4️⃣ In `main()`

We make a driver:

```cpp
Driver d{ "subhan", 17 };
```

Meaning:

> subhan uses the car whose ID is 17.

Now we “translate” that ID into the actual Car:

```cpp
Car* car = CarLot::getCar(d.getCarId());
```

If found, we print:

```cpp
subhan is driving a Corolla
```

## 🔵 **Why Would Anyone Use an ID Instead of a Pointer?**

### ✔ Advantage 1: The object may not be in memory

Maybe the Car is stored in:

- a file
    
- a database
    
- over a network
    

Using an ID lets us load it **only when needed**.

Pointers only work when the object is already in memory.

### ✔ Advantage 2: IDs take less space

Pointers = 4 or 8 bytes  
ID = maybe 1 or 2 bytes

If you have 1 million objects, saving memory matters a lot.

### ✔ Advantage 3: IDs don’t break

Pointers can become:

- dangling
    
- invalid
    
- pointing to freed memory
    

IDs don’t have that issue.

## 🔵 **Summary (Simple Version)**

- An **association** does NOT require pointers.
    
- You can associate objects through:
    
    - IDs
        
    - names
        
    - indexes
        
    - handles
        
    - database keys
        
- This is still an association because one object **uses** the other.
    

The _Driver–Car_ example demonstrates a **unidirectional association** using IDs instead of pointers.

## 🔵 Want a visual explanation?

Think of your phone:

📱 **You have your friend's phone number**, not their phone.  
When you need to call them, you look them up in your contact list.

That’s **exactly what indirect associations are** in programming.

Composition vs aggregation vs association summary

Here’s a summary table to help you remember the difference between composition, aggregation, and association:

|Property|Composition|Aggregation|Association|
|---|---|---|---|
|Relationship type|Whole/part|Whole/part|Otherwise unrelated|
|Members can belong to multiple classes|No|Yes|Yes|
|Members’ existence managed by class|Yes|No|No|
|Directionality|Unidirectional|Unidirectional|Unidirectional or bidirectional|
|Relationship verb|Part-of|Has-a|Uses-a|

---
# Dependencies

## ⭐ **What Are Dependencies in C++?**

So far you’ve learned:

- **Composition** → “has-a” AND owns the lifetime
    
- **Aggregation** → “has-a” but _does NOT own_ the lifetime
    
- **Association** → “uses/knows-about” long-term (unidirectional or bidirectional)
    

Now comes the **simplest and weakest relationship**:

## 🔵 **Dependency ("uses temporarily")**

A **dependency** happens when:

> One object temporarily uses another object **to perform a task**, but does not store it, own it, or maintain a long-term link.

In simple words:

- You **use** something _momentarily_ to get something done.
    
- You **don’t keep it**, and you don’t “know it” permanently.
    

Example in real life:

- You use crutches only when your foot is broken (temporary).
    
- A plant _depends_ on bees only for pollination (not always).
    

In programming:

- A class “depends on” another class when it **calls its functions** to get some work done.

## 🔵 **Key characteristics of a dependency**

✔ It is **temporary**

✔ It does **not appear as a data member** inside the class

✔ It is almost always **unidirectional**

✔ If the depended-on class changes, the dependent code may break

## ⭐ Example: `Point` depending on `std::ostream`

```cpp
friend std::ostream& operator<< (std::ostream& out, const Point& point);
```

Here:

- The `Point` class **does not store** a `std::ostream` object
    
- It only **uses** it when printing
    
- The dependency happens **only during the operator<< call**
    

So:

- `Point` **does not have** an ostream
    
- It **uses** ostream _temporarily_ → that is a **dependency**

## 🔵 **Where is the dependency visible?**

### 1. Inside the class declaration

`Point` declares:

```cpp
friend std::ostream& operator<<(std::ostream&, const Point&);
```

This means `Point` must know that `std::ostream` exists → it depends on it.

### 2. In `main()`

```cpp
std::cout << point1;
```

The program depends on:

- `std::cout`
    
- The overloaded `operator<<`
    
- `std::ostream`
    

All to accomplish **printing**.

##  **Dependencies vs Associations — What’s the Difference?**

Many people confuse these two. Here’s the clean difference:

## 🔷 **Association ("knows long-term")**

✔ The depending object _stores_ some form of link:

- pointer
    
- reference
    
- ID
    
- vector of pointers
    
- etc.
    

✔ It keeps knowing about the other object for its **entire lifetime**

Example:

```cpp
class Doctor {
    std::vector<Patient*> patients;
};
```

Doctor **always knows** his patients → permanent link → association.

### 🔶 **Dependency ("uses temporarily")**

❌ No member variable storing the related object  
❌ No long-term relationship  
❌ Only uses the object during a function call

Example:

```cpp
void print() {
    std::cout << value;   // temporary use
}
```

## 🔵 **Quick Comparison Table**

|Relationship|Stores as Member?|Lifetime Tied?|Direction|Strength|
|---|---|---|---|---|
|**Composition**|Yes|Yes|Uni|Strongest|
|**Aggregation**|Yes|No|Uni|Strong|
|**Association**|Yes (direct/indirect)|No|Uni OR Bi|Medium|
|**Dependency**|**No**|No|Uni|Weakest|

## ⭐ **Easy Real-Life Analogy**

### **Association**

Like a friend in your contact list — their number stays saved.

### **Dependency**

Like borrowing scissors from someone to cut tape — you don’t keep them.

## 🔵 Summary (Very Simple Version)

- **Dependency** = “uses temporarily”
    
- It happens during a **function call**
    
- No pointer/reference/member inside the class
    
- Much weaker than association
    
- Always **unidirectional**
    
- Example: printing using `std::ostream`

---
