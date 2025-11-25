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
