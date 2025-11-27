# Introduction to inheritance

### **1. Two ways to build complex classes in C++**

The text first reminds you that there are **two main ways** to build complex classes in C++:

1. **Object composition** → _“has-a” relationship_
    
    - Example: A car **has a** engine, wheels, seats.
        
2. **Inheritance** → _“is-a” relationship_
    
    - Example: A car **is a** vehicle.
        

The chapter you read earlier covered composition. Now we’re talking about inheritance.

## **2. Composition vs Inheritance**

### **Object composition**

- You build something by combining smaller parts.
    
- A computer **has** a CPU and RAM.
    

### **Inheritance**

- You build something by **starting from an existing type** and extending it.
    
- A laptop **is a** computer (but with extra features, like portability).
    

Inheritance = take all the existing attributes/behaviors of something, then add or specialize.

## **3. Real-life analogies**

- **You inherit traits from your parents**  
    → You get their features, but develop your own personality.
    
- **Technology evolves by inheriting features**  
    → Pentium inherited features from 486, 486 inherited from earlier CPUs.
    
- **Programming languages inherit features**  
    → C++ inherits from C.  
    → C inherits from older languages.
    

These analogies show the idea of _acquiring traits from something before you_.

## **4. The apples and bananas example**

Both apples and bananas are **fruit**.  
This means:

- All fruits have **name**, **color**, **size** → apples and bananas inherit those.
    
- All fruits **ripen** → apples and bananas inherit that behavior.
    

This is exactly how inheritance works in code:

```cpp
Fruit
 ├─ Apple
 └─ Banana
```

Anything defined in **Fruit** is automatically shared by **Apple** and **Banana**.

That structure is called a **hierarchy**.

## **5. What is a hierarchy?**

A **hierarchy** shows how things are related, usually from general → specific.

Examples:

### **Biology hierarchy**

Domain → Kingdom → … → Species  
General at the top, specific at bottom.

### **Shapes hierarchy**

Shape → Quadrilateral → Rectangle → Square  
Shape → Triangle → RightTriangle

In code, this would mean:

- A square **inherits from** rectangle → inherits from quadrilateral → inherits from shape.
    

Each level passes down traits to lower levels.

## **6. The important point**

**Inheritance builds a tree-like structure** where each level becomes more specific, but carries everything from above it.

This lets you:

- Avoid duplicating code.
    
- Organize related types.
    
- Express real-world relationships naturally.
    

## **Quick summary**

- **Composition** = object has another object.
    
- **Inheritance** = object is a more specialized version of another object.
    
- A **hierarchy** visually shows inheritance relationships (general → specific).
    
- Everything lower in the hierarchy automatically inherits everything above.

---
# Basic inheritance in C++

Now that we’ve talked about what inheritance is in an abstract sense, let’s talk about how it’s used within C++.

Inheritance in C++ takes place between classes. In an inheritance (is-a) relationship, the class being inherited from is called the **parent class**, **base class**, or **superclass**, and the class doing the inheriting is called the **child class**, **derived class**, or **subclass**.

![](http://learncpp.com/images/CppTutorial/Section11/FruitInheritance.gif)

In the above diagram, Fruit is the parent, and both Apple and Banana are children.

![](http://learncpp.com/images/CppTutorial/Section11/ShapesInheritance.gif)

In this diagram, Triangle is both a child (to Shape) and a parent (to Right Triangle).

A child class inherits both behaviors (member functions) and properties (member variables) from the parent (subject to some access restrictions that we’ll cover in a future lesson).  
These variables and functions become members of the derived class.

Because child classes are full-fledged classes, they can (of course) have their own members that are specific to that class. We’ll see an example of this in a moment.

**A Person class**

Here’s a simple class to represent a generic person:

```cpp
#include <string>
#include <string_view>

class Person
{
// In this example, we're making our members public for simplicity
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0)
        : m_name{ name }, m_age{ age }
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }

};
```

Because this Person class is designed to represent a generic person, we’ve only defined members that would be common to any type of person. Every person (regardless of gender, profession, etc…) has a name and age, so those are represented here.

Note that in this example, we’ve made all of our variables and functions public. This is purely for the sake of keeping these examples simple right now. Normally we would make the variables private. We will talk about access controls and how those interact with inheritance later in this chapter.

**A BaseballPlayer class**

Let’s say we wanted to write a program that keeps track of information about some baseball players. Baseball players need to contain information that is specific to baseball players -- for example, we might want to store a player’s batting average, and the number of home runs they’ve hit.

Here’s our incomplete Baseball player class:

```cpp
class BaseballPlayer
{
// In this example, we're making our members public for simplicity
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};
```

Now, we also want to keep track of a baseball player’s name and age, and we already have that information as part of our Person class.

We have three choices for how to add name and age to BaseballPlayer:

1. Add name and age to the BaseballPlayer class directly as members. This is probably the worst choice, as we’re duplicating code that already exists in our Person class. Any updates to Person will have to be made in BaseballPlayer too.
2. Add Person as a member of BaseballPlayer using composition. But we have to ask ourselves, “does a BaseballPlayer have a Person”? No, it doesn’t. So this isn’t the right paradigm.
3. Have BaseballPlayer inherit those attributes from Person. Remember that inheritance represents an is-a relationship. Is a BaseballPlayer a Person? Yes, it is. So inheritance is a good choice here.

**Making BaseballPlayer a derived class**

To have BaseballPlayer inherit from our Person class, the syntax is fairly simple. After the `class BaseballPlayer` declaration, we use a colon, the word “public”, and the name of the class we wish to inherit. This is called _public inheritance_. We’ll talk more about what public inheritance means in a future lesson.

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

```cpp
// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};
```

Using a derivation diagram, our inheritance looks like this:

![](https://www.learncpp.com/images/CppTutorial/Section11/BaseballPlayerInheritance.gif)

When BaseballPlayer inherits from Person, BaseballPlayer acquires the member functions and variables from Person. Additionally, BaseballPlayer defines two members of its own: m_battingAverage and m_homeRuns. This makes sense, since these properties are specific to a BaseballPlayer, not to any Person.

Thus, BaseballPlayer objects will have 4 member variables: m_battingAverage and m_homeRuns from BaseballPlayer, and m_name and m_age from Person.

This is easy to prove:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Person
{
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0)
        : m_name{name}, m_age{age}
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }

};

// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage{};
    int m_homeRuns{};

    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage{battingAverage}, m_homeRuns{homeRuns}
    {
    }
};

int main()
{
    // Create a new BaseballPlayer object
    BaseballPlayer joe{};
    // Assign it a name (we can do this directly because m_name is public)
    joe.m_name = "Joe";
    // Print out the name
    std::cout << joe.getName() << '\n'; // use the getName() function we've acquired from the Person base class

    return 0;
}
```

Which prints the value:

Joe

This compiles and runs because joe is a BaseballPlayer, and all BaseballPlayer objects have a m_name member variable and a getName() member function inherited from the Person class.

**An Employee derived class**

Now let’s write another class that also inherits from Person. This time, we’ll write an Employee class. An employee “is a” person, so using inheritance is appropriate:

```cpp
// Employee publicly inherits from Person
class Employee: public Person
{
public:
    double m_hourlySalary{};
    long m_employeeID{};

    Employee(double hourlySalary = 0.0, long employeeID = 0)
        : m_hourlySalary{hourlySalary}, m_employeeID{employeeID}
    {
    }

    void printNameAndSalary() const
    {
        std::cout << m_name << ": " << m_hourlySalary << '\n';
    }
};
```

Employee inherits m_name and m_age from Person (as well as the two access functions), and adds two more member variables and a member function of its own. Note that printNameAndSalary() uses variables both from the class it belongs to (Employee::m_hourlySalary) and the parent class (Person::m_name).

This gives us a derivation chart that looks like this:

![](https://www.learncpp.com/images/CppTutorial/Section11/EmployeeInheritance.gif)

Note that Employee and BaseballPlayer don’t have any direct relationship, even though they both inherit from Person.

Here’s a full example using Employee:

```cpp
#include <iostream>
#include <string>
#include <string_view>

class Person
{
public:
    std::string m_name{};
    int m_age{};

    Person(std::string_view name = "", int age = 0)
        : m_name{name}, m_age{age}
    {
    }

    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }

};

// Employee publicly inherits from Person
class Employee: public Person
{
public:
    double m_hourlySalary{};
    long m_employeeID{};

    Employee(double hourlySalary = 0.0, long employeeID = 0)
        : m_hourlySalary{hourlySalary}, m_employeeID{employeeID}
    {
    }

    void printNameAndSalary() const
    {
        std::cout << m_name << ": " << m_hourlySalary << '\n';
    }
};

int main()
{
    Employee frank{20.25, 12345};
    frank.m_name = "Frank"; // we can do this because m_name is public

    frank.printNameAndSalary();

    return 0;
}
```

This prints:

Frank: 20.25

### **Inheritance chains**

It’s possible to inherit from a class that is itself derived from another class. There is nothing noteworthy or special when doing so -- everything proceeds as in the examples above.

For example, let’s write a Supervisor class. A Supervisor is an Employee, which is a Person. We’ve already written an Employee class, so let’s use that as the base class from which to derive Supervisor:

```cpp
class Supervisor: public Employee
{
public:
    // This Supervisor can oversee a max of 5 employees
    long m_overseesIDs[5]{};
};
```

Now our derivation chart looks like this:

![](https://www.learncpp.com/images/CppTutorial/Section11/SupervisorInheritance.gif)

All Supervisor objects inherit the functions and variables from both Employee and Person, and add their own m_overseesIDs member variable.

By constructing such inheritance chains, we can create a set of reusable classes that are very general (at the top) and become progressively more specific at each level of inheritance.

>supervisor will have attributes of both employee and person!

### **Why is this kind of inheritance useful?**

Inheriting from a base class means we don’t have to redefine the information from the base class in our derived classes. We automatically receive the member functions and member variables of the base class through inheritance, and then simply add the additional functions or member variables we want. This not only saves work, but also means that if we ever update or modify the base class (e.g. add new functions, or fix a bug), all of our derived classes will automatically inherit the changes!

For example, if we ever added a new function to Person, then Employee, Supervisor, and BaseballPlayer would automatically gain access to it. If we added a new variable to Employee, then Supervisor would also gain access to it. This allows us to construct new classes in an easy, intuitive, and low-maintenance way!

---
# Order of construction of derived classes

First, let’s introduce some new classes that will help us illustrate some important points.

```cpp
class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id { id }
    {
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0)
        : m_cost { cost }
    {
    }

    double getCost() const { return m_cost; }
};
```

In this example, class Derived is derived from class Base.

![](https://www.learncpp.com/images/CppTutorial/Section11/DerivedBase.gif)

Because Derived inherits functions and variables from Base, you may assume that the members of Base are copied into Derived. However, this is not true. Instead, we can consider Derived as a two part class: one part Derived, and one part Base.

![](https://www.learncpp.com/images/CppTutorial/Section11/DerivedBaseCombined.gif)

You’ve already seen plenty examples of what happens when we instantiate a normal (non-derived) class:

```cpp
int main()
{
    Base base;

    return 0;
}
```

Base is a non-derived class because it does not inherit from any other classes. C++ allocates memory for Base, then calls Base’s default constructor to do the initialization.

Now let’s take a look at what happens when we instantiate a derived class:

```cpp
int main()
{
    Derived derived;

    return 0;
}
```

If you were to try this yourself, you wouldn’t notice any difference from the previous example where we instantiate non-derived class Base. But behind the scenes, things happen slightly differently. As mentioned above, Derived is really two parts: a Base part, and a Derived part. When C++ constructs derived objects, it does so in phases. First, the most-base class (at the top of the inheritance tree) is constructed. Then each child class is constructed in order, until the most-child class (at the bottom of the inheritance tree) is constructed last.

So when we instantiate an instance of Derived, first the Base portion of Derived is constructed (using the Base default constructor). Once the Base portion is finished, the Derived portion is constructed (using the Derived default constructor). At this point, there are no more derived classes, so we are done.

This process is actually easy to illustrate.

```cpp
#include <iostream>

class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id { id }
    {
        std::cout << "Base\n";
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0)
        : m_cost { cost }
    {
        std::cout << "Derived\n";
    }

    double getCost() const { return m_cost; }
};

int main()
{
    std::cout << "Instantiating Base\n";
    Base base;

    std::cout << "Instantiating Derived\n";
    Derived derived;

    return 0;
}
```

This program produces the following result:

Instantiating Base
Base
Instantiating Derived
Base
Derived

As you can see, when we constructed Derived, the Base portion of Derived got constructed first. This makes sense: logically, a child can not exist without a parent. It’s also the safe way to do things: the child class often uses variables and functions from the parent, but the parent class knows nothing about the child. Instantiating the parent class first ensures those variables are already initialized by the time the derived class is created and ready to use them.

### **Order of construction for inheritance chains**

It is sometimes the case that classes are derived from other classes, which are themselves derived from other classes. For example:

```cpp
#include <iostream>

class A
{
public:
    A()
    {
        std::cout << "A\n";
    }
};

class B: public A
{
public:
    B()
    {
        std::cout << "B\n";
    }
};

class C: public B
{
public:
    C()
    {
        std::cout << "C\n";
    }
};

class D: public C
{
public:
    D()
    {
        std::cout << "D\n";
    }
};
```

Remember that C++ always constructs the “first” or “most base” class first. It then walks through the inheritance tree in order and constructs each successive derived class.

![Ezoic](https://go.ezodn.com/utilcave_com/ezoicbwa.png "ezoic")

Here’s a short program that illustrates the order of creation all along the inheritance chain.

```cpp
int main()
{
    std::cout << "Constructing A: \n";
    A a;

    std::cout << "Constructing B: \n";
    B b;

    std::cout << "Constructing C: \n";
    C c;

    std::cout << "Constructing D: \n";
    D d;
}
```

This code prints the following:

Constructing A:
A
Constructing B:
A
B
Constructing C:
A
B
C
Constructing D:
A
B
C
D

### **Conclusion**

C++ constructs derived classes in phases, starting with the most-base class (at the top of the inheritance tree) and finishing with the most-child class (at the bottom of the inheritance tree). As each class is constructed, the appropriate constructor from that class is called to initialize that part of the class.

You will note that our example classes in this section have all used base class default constructors (for simplicity). In the next lesson, we will take a closer look at the role of constructors in the process of constructing derived classes (including how to explicitly choose which base class constructor you want your derived class to use).

---
# Constructors and initialization of derived classes

In the past two lessons, we’ve explored some basics around inheritance in C++ and the order that derived classes are initialized. In this lesson, we’ll take a closer look at the role of constructors in the initialization of derived classes. To do so, we will continue to use the simple Base and Derived classes we developed in the previous lesson:

```cpp
class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id{ id }
    {
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0)
        : m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};
```

With non-derived classes, constructors only have to worry about their own members. For example, consider Base. We can create a Base object like this:

```cpp
int main()
{
    Base base{ 5 }; // use Base(int) constructor

    return 0;
}
```

Here’s what actually happens when base is instantiated:

1. Memory for base is set aside
2. The appropriate Base constructor is called
3. The member initializer list initializes variables
4. The body of the constructor executes
5. Control is returned to the caller

This is pretty straightforward. With derived classes, things are slightly more complex:

```cpp
int main()
{
    Derived derived{ 1.3 }; // use Derived(double) constructor

    return 0;
}
```

Here’s what actually happens when derived is instantiated:

1. Memory for derived is set aside (enough for both the Base and Derived portions)
2. The appropriate Derived constructor is called
3. **The Base object is constructed first using the appropriate Base constructor**. If no base constructor is specified, the default constructor will be used.
4. The member initializer list initializes variables
5. The body of the constructor executes
6. Control is returned to the caller

The only real difference between this case and the non-inherited case is that before the Derived constructor can do anything substantial, the Base constructor is called first. The Base constructor sets up the Base portion of the object, control is returned to the Derived constructor, and the Derived constructor is allowed to finish up its job.

## **Initializing base class members**

### **1. The problem**

You have two classes:

```cpp
class Base {
protected:
    int m_id {};
};
class Derived : public Base {
    double m_cost {};
};
```

When creating a **Derived** object, you want to set **both**:

- `m_cost` → belongs to `Derived`
    
- `m_id` → belongs to `Base`
    

You write this:

```cpp
Derived(double cost, int id)
    : m_cost{ cost }, m_id{ id } // ❌ error
{
}
```

But this **does not work**.

### **2. Why can’t Derived initialize m_id directly?**

#### **Rule:**

A class constructor may **only initialize its own member variables** in its initializer list.

Meaning:

- `Base` constructor can initialize `m_id`
    
- `Derived` constructor can initialize `m_cost`
    
- **Derived cannot initialize m_id** because it _doesn’t own it_

### **3. Why does C++ enforce this rule?**

Because of **const** and **reference** members.

Imagine `m_id` was:

```cpp
const int m_id;
```

Const values must be initialized **exactly once** at creation.

If C++ allowed Derived to initialize `m_id`, this could happen:

1. Base constructor initializes `m_id`
    
2. Derived constructor initializer also tries to initialize `m_id`
    

→ **Illegal: const initialized twice**  
→ **Very confusing behavior**

So C++ simply forbids it entirely.

### **4. Why not assign it inside the constructor body?**

Example:

```cpp
Derived(double cost, int id)
    : m_cost{ cost }
{
    m_id = id;   // works only sometimes
}
```

This works _only if_ `m_id` is **not const** and **not a reference**.

But it’s still wrong because:

#### **a) It assigns twice**

- Base constructor already set `m_id`
    
- Now Derived reassigns it again → wasteful and potentially incorrect
    

#### **b) Base can’t use the value**

During construction:

1. Base constructor runs **first**
    
2. Derived’s assignment runs **later**
    

So Base never sees the correct `id` while it’s constructing.

If Base needed to do something with `id` during construction → it can’t.

### **5. The correct solution**

You let the **Derived constructor call the correct Base constructor**, passing `id` to it.

```cpp
Derived(double cost, int id)
    : Base{ id }   // ✅ call Base(int) constructor
    , m_cost{ cost }
{
}
```

This tells C++:

> “When constructing Derived, initialize the Base part using Base(id).”

Now:

- `m_id` is initialized correctly in Base’s initializer list
    
- `m_cost` is initialized correctly in Derived’s initializer list
    
- Construction order is correct and efficient

### **6. What actually happens during construction**

Step-by-step:

1. Memory for `derived` is allocated.
    
2. `Derived(cost = 1.3, id = 5)` is called.
    
3. It sees `Base{id}`, so it calls `Base(5)`:
    
    - `m_id` is initialized to 5.
        
4. Base constructor finishes.
    
5. Now Derived’s initializer list sets:
    
    - `m_cost = 1.3`
        
6. Derived constructor finishes.
    

Output:

```cpp
Id: 5
Cost: 1.3
```

### **7. Important rule**

> **The Base constructor always runs before the Derived constructor**  
> Even if Base appears second in the initializer list, it still executes first.

Because the base “part” of the object must exist before the derived “part” is built on top of it.

### **Short summary**

- You **cannot** initialize inherited members (`m_id`) inside Derived’s initializer list.
    
- Only the **Base constructor** is allowed to initialize `m_id`.
    
- To pass values to Base, you must explicitly call a Base constructor in Derived’s initializer list.
    
- Assigning inherited members inside the constructor body is allowed but:
    
    - inefficient
        
    - breaks for const/reference members
        
    - makes Base unable to use the value during construction

## **Now we can make our members private**

Now that you know how to initialize base class members, there’s no need to keep our member variables public. We make our member variables private again, as they should be.

As a quick refresher, public members can be accessed by anybody. Private members can only be accessed by member functions of the same class. Note that this means derived classes can not access private members of the base class directly! Derived classes will need to use access functions to access private members of the base class.

Consider:

```cpp
#include <iostream>

class Base
{
private: // our member is now private
    int m_id {};

public:
    Base(int id=0)
        : m_id{ id }
    {
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
private: // our member is now private
    double m_cost;

public:
    Derived(double cost=0.0, int id=0)
        : Base{ id } // Call Base(int) constructor with value id!
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};

int main()
{
    Derived derived{ 1.3, 5 }; // use Derived(double, int) constructor
    std::cout << "Id: " << derived.getId() << '\n';
    std::cout << "Cost: " << derived.getCost() << '\n';

    return 0;
}
```

In the above code, we made m_id and m_cost private. This is fine, since we use the relevant constructors to initialize them, and use a public accessor to get the values.

This prints, as expected:

Id: 5
Cost: 1.3

We’ll talk more about access specifiers in the next lesson.

## **Inheritance chains**

Classes in an inheritance chain work in exactly the same way.

```cpp
#include <iostream>

class A
{
public:
    A(int a)
    {
        std::cout << "A: " << a << '\n';
    }
};

class B: public A
{
public:
    B(int a, double b)
    : A{ a }
    {
        std::cout << "B: " << b << '\n';
    }
};

class C: public B
{
public:
    C(int a, double b, char c)
    : B{ a, b }
    {
        std::cout << "C: " << c << '\n';
    }
};

int main()
{
    C c{ 5, 4.3, 'R' };

    return 0;
}
```

In this example, class C is derived from class B, which is derived from class A. So what happens when we instantiate an object of class C?

First, main() calls C(int, double, char). The C constructor calls B(int, double). The B constructor calls A(int). Because A does not inherit from anybody, this is the first class we’ll construct. A is constructed, prints the value 5, and returns control to B. B is constructed, prints the value 4.3, and returns control to C. C is constructed, prints the value ‘R’, and returns control to main(). And we’re done!

Thus, this program prints:

A: 5
B: 4.3
C: R

It is worth mentioning that constructors can only call constructors from their immediate parent/base class. Consequently, the C constructor could not call or pass parameters to the A constructor directly. The C constructor can only call the B constructor (which has the responsibility of calling the A constructor).

## **Destructors**

When a derived class is destroyed, each destructor is called in the _reverse_ order of construction. In the above example, when c is destroyed, the C destructor is called first, then the B destructor, then the A destructor.

>Warning

If your base class has virtual functions, your destructor should also be virtual, otherwise undefined behavior will result in certain cases.

## **Summary**

When constructing a derived class, the derived class constructor is responsible for determining which base class constructor is called. If no base class constructor is specified, the default base class constructor will be used. In that case, if no default base class constructor can be found (or created by default), the compiler will display an error. The classes are then constructed in order from most base to most derived.

At this point, you now understand enough about C++ inheritance to create your own inherited classes!

---
# Inheritance and access specifiers

