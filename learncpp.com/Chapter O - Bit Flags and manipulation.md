> On modern architecture, the smallest addressable unit of memory is a byte, this is fine for most types but not for bool since it only has two states 0 or 1 so it takes only 1 bit to store information and since variable is atleast 1 byte that means 7 bits are unused.

> In some storage-intensive cases, it can be useful to pack 8 individual boolean values each of 1 bit into a single byte for storage efficiency purposes.
> `std::bitset` is not designed for that — it’s a **tool for code clarity**, not bit-level compression.

>[!tip]
>Doing these things requires that we can manipulate objects at the bit level. Fortunately, C++ gives us tools to do precisely this. Modifying individual bits within an object is called **bit manipulation**.

> 0b before literal identifies the literal as binary and `'` is used to seperate binary digits.

---

### Bit flags

>**Bit flags** are a compact way of storing multiple Boolean options or settings using a single integer. Each bit in an integer represents a true/false (1/0) value.

>[!tip]
>In computing, a **flag** is a value that signals when some condition exists in a program. With a bit flag, a value of `true` means the condition exists.

>To define a set of bit flags, we’ll typically use an unsigned integer of the appropriate size (8 bits, 16 bits, 32 bits, etc… depending on how many flags we have), or `std::bitset`.

```cpp
#include <bitset> // for std::bitset

std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags
```

>[!tip]
>Bit manipulation is one of the few times when you should unambiguously use unsigned integers (or `std::bitset`).

>The positioning of bits start from right to left.
>
>>Given the bit sequence 0000 0101, the bits that are in position 0 and 2 have value 1, and the other bits have value 0.
>

---

### Manipulating bits via `std::bitset`

> Bitset can be used tp print values in binary. However, this isn't the only useful thing they can do.

`std::bitset` provides 4 key member functions that are useful for doing bit manipulation:

- test() allows us to query whether a bit is a 0 or 1.
- set() allows us to turn a bit on (this will do nothing if the bit is already on).
- reset() allows us to turn a bit off (this will do nothing if the bit is already off).
- flip() allows us to flip a bit value from a 0 to a 1 or vice versa.

Each of these functions takes the position of the bit we want to operate on as their only argument.

```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    bits.set(3);   // set bit position 3 to 1 (now we have 0000 1101)
    bits.flip(4);  // flip bit 4 (now we have 0001 1101)
    bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << bits<< '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
    std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

    return 0;
}
```

This prints:

All the bits: 00001101
Bit 3 has value: 1
Bit 4 has value: 0

>Giving our bits names can help make our code more readable:

```cpp
#include <bitset>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr int  isHungry   { 0 };
    [[maybe_unused]] constexpr int  isSad      { 1 };
    [[maybe_unused]] constexpr int  isMad      { 2 };
    [[maybe_unused]] constexpr int  isHappy    { 3 };
    [[maybe_unused]] constexpr int  isLaughing { 4 };
    [[maybe_unused]] constexpr int  isAsleep   { 5 };
    [[maybe_unused]] constexpr int  isDead     { 6 };
    [[maybe_unused]] constexpr int  isCrying   { 7 };

    std::bitset<8> me{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    me.set(isHappy);      // set bit position 3 to 1 (now we have 0000 1101)
    me.flip(isLaughing);  // flip bit 4 (now we have 0001 1101)
    me.reset(isLaughing); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << me << '\n';
    std::cout << "I am happy: " << me.test(isHappy) << '\n';
    std::cout << "I am laughing: " << me.test(isLaughing) << '\n';

    return 0;
}
```

### The size of `std::bitset`

>One potential surprise is that `std::bitset` is optimized for speed, not memory savings. The size of a `std::bitset` is typically the number of bytes needed to hold the bits, rounded _up_ to the nearest `sizeof(size_t)`, which is 4 bytes on 32-bit machines, and 8-bytes on 64-bit machines.
>Thus, a `std::bitset<8>` will typically use either 4 or 8 bytes of memory, even though it technically only needs 1 byte to store 8 bits. Thus, `std::bitset` is most useful when we desire convenience, not memory savings.

### Querying `std::bitset`

>There are a few other member functions that are often useful:

- size() returns the number of bits in the bitset.
- count() returns the number of bits in the bitset that are set to `true`.
- all() returns a Boolean indicating whether all bits are set to `true`.
- any() returns a Boolean indicating whether any bits are set to `true`.
- none() returns a Boolean indicating whether no bits are set to `true`.

```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'1101 };
    std::cout << bits.size() << " bits are in the bitset\n";
    std::cout << bits.count() << " bits are set to true\n";

    std::cout << std::boolalpha;
    std::cout << "All bits are true: " << bits.all() << '\n';
    std::cout << "Some bits are true: " << bits.any() << '\n';
    std::cout << "No bits are true: " << bits.none() << '\n';

    return 0;
}
```

This prints:

8 bits are in the bitset
3 bits are set to true
All bits are true: false
Some bits are true: true
No bits are true: false

---

### O.2 — Bitwise operators

>C++ provides 6 bit manipulation operators, often called **bitwise** operators:

|Operator|Symbol|Form|The operation returns a value where:|
|---|---|---|---|
|left shift|<<|x << n|the bits from `x` are shifted left by `n` positions, new bits are `0`.|
|right shift|>>|x >> n|the bits from `x` are shifted right by `n` positions, new bits are `0`.|
|bitwise NOT|~|~x|each bit from `x` is flipped.|
|bitwise AND|&|x & y|each bit is set when both corresponding bits in `x` and `y` are `1`.|
|bitwise OR|\||x \| y|each bit is set when either corresponding bit in `x` and `y` is `1`.|
|bitwise XOR|^|x ^ y|each bit is set when the corresponding bits in `x` and `y` are different.|

>[!tip]
>These are non-modifying operators (they do not modify their operands).

>[!tip]
>To avoid surprises, use the bitwise operators with unsigned integral operands or `std::bitset`.

#### Difference Between unsigned integral operand and bitset 

```cpp
#include <iostream>
#include <bitset>
using namespace std;

int main() {
    unsigned int a = 12;
    bitset<8> b(12);

    cout << "a = " << a << endl;       // 12
    cout << "b = " << b << endl;       // 00001100

    cout << "b[2] = " << b[2] << endl; // access individual bit (from right)

    return 0;
}

```

---

Here’s an example demonstrating the use of **bitwise operators** with **unsigned integral operands** in C++:

>[!tip]
>This example is just to show the alternative to `std::bitset`:

```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int a = 12;   // binary: 00001100
    unsigned int b = 5;    // binary: 00000101

    cout << "a & b = " << (a & b) << endl;  // Bitwise AND:      00000100 (4)
    cout << "a | b = " << (a | b) << endl;  // Bitwise OR:       00001101 (13)
    cout << "a ^ b = " << (a ^ b) << endl;  // Bitwise XOR:      00001001 (9)
    cout << "~a = " << (~a) << endl;        // Bitwise NOT:      11110011 (depends on number of bits)
    cout << "a << 1 = " << (a << 1) << endl; // Left shift:       00011000 (24)
    cout << "a >> 2 = " << (a >> 2) << endl; // Right shift:      00000011 (3)

    return 0;
}

```

### Explanation:

- `&` (AND): Sets bit to 1 if **both bits** are 1.
    
- `|` (OR): Sets bit to 1 if **at least one** bit is 1.
    
- `^` (XOR): Sets bit to 1 if **only one** of the bits is 1.
    
- `~` (NOT): Flips all bits (note: result depends on the size of `unsigned int`).
    
- `<<` (Left shift): Shifts bits to the left and fills with 0.
    
- `>>` (Right shift): Shifts bits to the right.

--- 
### Bitwise left shift (<<) and bitwise right shift (>>) operators

> The bitwise left shift `<<` operator shifts bits to the right, the left operand is an expression that have initial bit sequence and the right operand is an integer number that specifies the number of bit-positions to move the bits over by.

Example:

0011 \<\< 1 is 0110
0011 \<\< 2 is 1100
0011 \<\< 3 is 1000   

>Note that in the third case, we shifted a `1` bit off the end of the number! Bits that are shifted off the end of the bit sequence are lost forever.

>[!tip]
>The left operand is not modified

>The **bitwise right shift** (>>) operator works similarly but shifts bits to the right.

Here are some examples of right shifting the bit sequence `1100`:

1100 />/> 1 is 0110
1100 />/> 2 is 0011
1100 />/> 3 is 0001

```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> x { 0b1100 };

    std::cout << x << '\n';
    std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
    std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1000

    return 0;
}
```
This prints:
1100
0110
1000

---
### What!? Aren’t operator<< and operator>> used for input and output?

> Simple Answer `Operator Overloading`.

>Note that if you’re using `operator<<` for both output and left shift, parenthesization is required to use for left-shifting:
```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::bitset<4> x{ 0b0110 };

	std::cout << x << 1 << '\n'; // print value of x (0110), then 1
	std::cout << (x << 1) << '\n'; // print x left shifted by 1 (1100)

	return 0;
}
```

---

### Bitwise NOT

>The **bitwise NOT** operator (~) is conceptually straightforward: It simply flips each bit from a `0` to a `1`, or vice versa.

~0011 is 1100
~0000 0100 is 1111 1011

When interpreted as an integer, the number of bits in the result of a bitwise NOT affects the value produced.
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> b4{ 0b100 }; // b4 is 0100
    std::bitset<8> b8{ 0b100 }; // b8 is 0000 0100

    std::cout << "Initial values:\n";
    std::cout << "Bits: " << b4 << ' ' << b8 << '\n';
    std::cout << "Values: " << b4.to_ulong() << ' ' << b8.to_ulong() << "\n\n";

    b4 = ~b4; // flip b4 to 1011
    b8 = ~b8; // flip b8 to 1111 1011

    std::cout << "After bitwise NOT:\n";
    std::cout << "Bits: " << b4 << ' ' << b8 << '\n';
    std::cout << "Values: " << b4.to_ulong() << ' ' << b8.to_ulong() << '\n';

    return 0;
}
```

This prints:

Initial values:
Bits: 0100 00000100
Values: 4 4

After bitwise NOT:
Bits: 1011 11111011
Values: 11 251

>Initially, `b4` and `b8` are both set to `0b100`. When padded with leading zeros, `b4` ends up as `0100` and `b8` as `00000100`, which is printed on the next line.
>We then use the `to_ulong()` member function to interpret the value of the bits, interpreted as a `long` integer. You can see that both `b4` and `b8` print the value `4`. Despite the different number of bits, they both represent the same value. This is because leading zero bits contribute no value to the interpreted integer.
>Then we use bitwise NOT to flip the bits of each, so `b4` now has bits `1011` and `b8` now has bits `1111 1011`. When printed as an integer, this prints the values `11` and `251`. As you can see, these values are no longer identical. This is because leading ones do contribute value to the interpreted integer, and `b8` has more leading ones than `b4`.

>[!tip]
>Leading zeros doesnt contribute to intrepreted value but leading one's do!

---
### Bitwise OR

> Its same as OR operator. However, whereas logical OR is applied to the entire operand (to produce a single true or false result), bitwise OR is applied to each pair of bits in the operands (to produce a single true or false result for each bit).

Consider the expression `0b0101 | 0b0110`

>[!tip]
>To do any binary bitwise operation by hand, it is easiest to line the two operands up like this:
>> 0 1 0 1 OR (or whatever bitwise operation you are doing)
>> 0 1 1 0
>
>Then, apply the operation to each _column_ of bits, and write the result underneath.

In the first column, `0` OR `0` is `0`, so we put a 0 underneath the line.

0 1 0 1 OR
0 1 1 0
-------
0

Second column, `1` OR `1` is `1`. Third column `0` or `1` is `1`. And fourth column, `1` or `0` is `1`.

0 1 0 1 OR
0 1 1 0
-------
0 1 1 1

Our result is `0111` binary.

```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::cout << (std::bitset<4>{ 0b0101 } | std::bitset<4>{ 0b0110 }) << '\n';

	return 0;
}
```
0111

>We can do the same thing to compound bitwise OR expressions, such as `0b0111 | 0b0011 | 0b0001`. If any of the bits in a column are `1`, the result of that column is `1`:

0 1 1 1 OR
0 0 1 1 OR
0 0 0 1

0 1 1 1

```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::cout << (std::bitset<4>{ 0b0111 } | std::bitset<4>{ 0b0011 } | std::bitset<4>{ 0b0001 }) << '\n';

	return 0;
}
```
0111

---

### Bitwise AND

> **Bitwise AND** (&) works similarly to the above, except it uses AND logic instead of OR logic. That is, for each pair of bits in the operands, Bitwise AND sets the resulting bit to `true` (`1`) if both paired bits are `1`, and `false` (`0`) otherwise.

Same column Technique for AND!

```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::cout << (std::bitset<4>{ 0b0101 } & std::bitset<4>{ 0b0110 }) << '\n';

	return 0;
}
```
0100

> We can also do Compound bitwise AND expression!

---
### Bitwise XOR

>**bitwise XOR** (^), also known as **exclusive or**.
>For each pair of bits in the operands, Bitwise XOR sets the resulting bit to `true` (`1`) when exactly one of the paired bits is `1`, and `false` (`0`) otherwise. Put another way, Bitwise XOR sets the resulting bit to `true` when the paired bits are different (one is a `0` and the other a `1`).

Consider the expression `0b0110 ^ 0b0011`:

0 1 1 0 XOR
0 0 1 1
-
0 1 0 1

>It is also possible to evaluate compound XOR expression column style, such as `0b0001 ^ 0b0011 ^ 0b0111`. If there are an even number of `1` bits in a column, the result is `0`. If there are an odd number of `1` bits in a column, the result is `1`.

0 0 0 1 XOR
0 0 1 1 XOR
0 1 1 1
-
0 1 0 1

---
### Bitwise assignment operators

>Similar to the arithmetic assignment operators, C++ provides bitwise assignment operators. These do modify the left operand.

| Operator    | Symbol | Form    | The operation modifies the left operand where:                            |
| ----------- | ------ | ------- | ------------------------------------------------------------------------- |
| left shift  | <<     | x <<= n | the bits in `x` are shifted left by `n` positions, new bits are `0`.      |
| right shift | >>     | x >>= n | the bits in `x` are shifted right by `n` positions, new bits are `0`.     |
| bitwise AND | &      | x &= y  | each bit is set when both corresponding bits in `x` and `y` are `1`.      |
| bitwise OR  | \|     | x \|= y | each bit is set when either corresponding bit in `x` and `y` is `1`.      |
| bitwise XOR | ^      | x ^= y  | each bit is set when the corresponding bits in `x` and `y` are different. |
For example, instead of writing `x = x >> 1;`, you can write `x >>= 1;`.

```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> bits { 0b0100 };
    bits >>= 1;
    std::cout << bits << '\n';

    return 0;
}
```
0010

>There is no bitwise NOT assignment operator. This is because the other bitwise operators are binary, but bitwise NOT is unary (so what would go on the right-hand side of a `~=` operator?). If you want to flip all of the bits of an object, you can use normal assignment: `x = ~x;`

---
### Bitwise operators perform integral promotion on smaller integral types Advanced

```cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    std::uint8_t c { 0b00001111 };

    std::cout << std::bitset<32>(~c) << '\n';     // incorrect: prints 11111111111111111111111111110000
    std::cout << std::bitset<32>(c << 6) << '\n'; // incorrect: prints 0000000000000000001111000000
    std::uint8_t cneg { ~c };                     // error: narrowing conversion from unsigned int to std::uint8_t
    c = ~c;                                       // possible warning: narrowing conversion from unsigned int to std::uint8_t

    return 0;
}
```

> In case 3 (cneg), you can see that cneg object is unsigned integer of 8 bits and its initializer is of the same type so why is narrowing conversion occuring? It is because of the use of bitwise operator NOT which performs integral promotion of uint8_t to int.

>[!tip]
>If the operand(s) of a bitwise operator are an integral type smaller than an `int`, those operands will be promoted (converted) to `int` or `unsigned int`

These issues can be addressed by using `static_cast` to convert the result of your bitwise operation back to the narrower integral type. The following program produces the correct results:

```cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    std::uint8_t c { 0b00001111 };

    std::cout << std::bitset<32>(static_cast<std::uint8_t>(~c)) << '\n';     // correct: prints 00000000000000000000000011110000
    std::cout << std::bitset<32>(static_cast<std::uint8_t>(c << 6)) << '\n'; // correct: prints 0000000000000000000011000000
    std::uint8_t cneg { static_cast<std::uint8_t>(~c) };                     // compiles
    c = static_cast<std::uint8_t>(~c);                                       // no warning

    return 0;
}
```

>[!tip]
>list initialization rejects narrow conversion

>[!warning]
>Bitwise operators will promote operands with narrower integral types to `int` or `unsigned int`.
>`operator~` and `operator<<` are width-sensitive and may produce different results depending on the width of the operand. `static_cast` the result of such bitwise operations back to the narrower integral type before using to ensure correct results.

>[!tip]
>Avoid bit shifting on integral types smaller than `int` whenever possible.

A bitwise rotation is like a bitwise shift, except that any bits shifted off one end are added back to the other end. For example `0b1001 << 1` would be `0b0010`, but a left rotate by 1 would result in `0b0011` instead. Implement a function that does a left rotate on a `std::bitset<4>`. For this one, it’s okay to use test() and set().

---

### Bit masks

> In order to manipulate individual bits (e.g. turn them on or off), we need some way to identify the specific bits we want to manipulate. Unfortunately, the bitwise operators don’t know how to work with bit positions. Instead they work with bit masks.

### ⚙️ What You Might Expect:

You might _want_ to say:

> "I want to flip bit #3."

But the bitwise operators can't take a position like `3` and do the job automatically. Instead, you must **manually create a value (mask)** where **only bit #3 is set**, and then apply the operator.

### 🛠️ What Is a Bit Mask?

A **bit mask** is just a binary number where:

- Some bits are set (`1`)
    
- Others are cleared (`0`)
    
- You use this pattern to tell the computer **which bits to touch**, and **which to leave alone**

>[!Analogy]
>Consider a real-life case where you want to paint a window frame. If you’re not careful, you risk painting not only the window frame, but also the glass itself. You might buy some masking tape and apply it to the glass and any other parts you don’t want painted. Then when you paint, the masking tape blocks the paint from reaching anything you don’t want painted. In the end, only the non-masked parts (the parts you want painted) get painted.
>A bit mask essentially performs the same function for bits -- the bit mask blocks the bitwise operators from touching bits we don’t want modified, and allows access to the ones we do want modified.

---

### Defining bit masks in C++14

>The simplest set of bit masks is to define one bit mask for each bit position. We use 0s to mask out the bits we don’t care about, and 1s to denote the bits we want modified.

```cpp
#include <cstdint>

constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7
```

>Now we have a set of symbolic constants that represents each bit position. We can use these to manipulate the bits

### [Defining bit masks in C++11 or earlier](https://www.learncpp.com/cpp-tutorial/bit-manipulation-with-bitwise-operators-and-bit-masks/#:~:text=Because%20C%2B%2B11,//%201000%200000)

---

### Testing a bit (to see if it is on or off)

>To determine if a bit is on or off, we use _bitwise AND_ in conjunction with the bit mask for the appropriate bit:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
	[[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	[[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	[[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	[[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	[[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	[[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	[[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	[[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

	std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

	std::cout << "bit 0 is " << (static_cast<bool>(flags & mask0) ? "on\n" : "off\n");
	std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

	return 0;
}
```

This prints:

bit 0 is on
bit 1 is off

Let’s examine how this works.

In the case of `flags & mask0`, we have `0000'0101` & `0000'0001`. Let’s line these up:

0000'0101 &
0000'0001
-
0000'0001

We are then casting `0000'0001` to a `bool`. Since any non-zero number converts to `true` and this value has a non-zero digit, this evaluates to `true`.

In the case of `flags & mask1`, we have `0000'0101` & `0000'0010`. Let’s line these up:

0000'0101 &
0000'0010
-
0000'0000

Since a zero value converts to `false` and this value has only zero digits, this evaluates to `false`.

---
### Setting a bit

>To set (turn on) a bit (to value 1), we use bitwise OR equals (operator |=) in conjunction with the bit mask for the appropriate bit:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    flags |= mask1; // turn on bit 1

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    return 0;
}
```

This prints:

bit 1 is off
bit 1 is on

We can also turn on multiple bits at the same time using _Bitwise OR_:

```cpp
flags |= (mask4 | mask5); // turn bits 4 and 5 on at the same time
```

---
### Resetting a bit

>To reset (clear) a bit (to value 0), we use _Bitwise AND_ and _Bitwise NOT_ together:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    flags &= ~mask2; // turn off bit 2

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    return 0;
}
```

This prints:

bit 2 is on
bit 2 is off

>We can turn off multiple bits at the same time:

```cpp
flags &= ~(mask4 | mask5); // turn bits 4 and 5 off at the same time
```

---

### Flipping a bit

>To toggle (flip) a bit state (from 0 to 1 or from 1 to 0), we use _Bitwise XOR_:

```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // flip bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // flip bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    return 0;
}
```

This prints:

bit 2 is on
bit 2 is off
bit 2 is on

We can flip multiple bits simultaneously:

```cpp
flags ^= (mask4 | mask5); // flip bits 4 and 5 at the same time
```

---
### 🧠 Why Use Masks if We Have Built-in Bitwise Functions like `set`, `test`, etc.?

#### ✅ Short Answer

Because:

1. **`std::bitset` is a high-level abstraction** for compile-time known sizes.
    
2. **Bit masks and raw operators work on any integral type**, are **faster**, and more **low-level and flexible**.
    
3. **Some systems (e.g. embedded, hardware-level programming)** don’t support `std::bitset`, or you need to pack bits in specific formats.

>std::bitset supports the full set of bitwise operators. So even though it’s easier to use the functions (test, set, reset, and flip) to modify individual bits, you can use bitwise operators and bit masks if you want.
	Why would you want to? The functions only allow you to modify individual bits. The bitwise operators allow you to modify multiple bits at once.

```cpp
#include <bitset>
#include <iostream>

int main()
{
	[[maybe_unused]] constexpr std::bitset<8> mask0{ 0b0000'0001 }; // represents bit 0
	[[maybe_unused]] constexpr std::bitset<8> mask1{ 0b0000'0010 }; // represents bit 1
	[[maybe_unused]] constexpr std::bitset<8> mask2{ 0b0000'0100 }; // represents bit 2
	[[maybe_unused]] constexpr std::bitset<8> mask3{ 0b0000'1000 }; // represents bit 3
	[[maybe_unused]] constexpr std::bitset<8> mask4{ 0b0001'0000 }; // represents bit 4
	[[maybe_unused]] constexpr std::bitset<8> mask5{ 0b0010'0000 }; // represents bit 5
	[[maybe_unused]] constexpr std::bitset<8> mask6{ 0b0100'0000 }; // represents bit 6
	[[maybe_unused]] constexpr std::bitset<8> mask7{ 0b1000'0000 }; // represents bit 7

	std::bitset<8> flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	flags ^= (mask1 | mask2); // flip bits 1 and 2
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	flags |= (mask1 | mask2); // turn bits 1 and 2 on
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	flags &= ~(mask1 | mask2); // turn bits 1 and 2 off
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	return 0;
}
```
This prints:

bit 1 is off
bit 2 is on
bit 1 is on
bit 2 is off
bit 1 is on
bit 2 is on
bit 1 is off
bit 2 is off

---
### Making bit masks meaningful

>Naming our bit masks “mask1” or “mask2” tells us what bit is being manipulated, but doesn’t give us any indication of what that bit flag is actually being used for.

```cpp
#include <cstdint>
#include <iostream>

int main()
{
        // Define a bunch of physical/emotional states
	[[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
	[[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
	[[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
	[[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
	[[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
	[[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
	[[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
	[[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000

	std::uint8_t me{}; // all flags/options turned off to start
	me |= (isHappy | isLaughing); // I am happy and laughing
	me &= ~isLaughing; // I am no longer laughing

	// Query a few states
	// (we'll use static_cast<bool> to interpret the results as a boolean value)
	std::cout << std::boolalpha; // print true or false instead of 1 or 0
	std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n';
	std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';

	return 0;
}
```

Two notes here: First, std::bitset doesn’t have a nice function that allows you to query bits using a bit mask. So if you want to use bit masks rather than positional indexes, you’ll have to use _Bitwise AND_ to query bits. Second, we make use of the any() function, which returns true if any bits are set, and false otherwise to see if the bit we queried remains on or off.

---
### When are bit flags most useful?

>Astute readers may note that the above examples don’t actually save any memory. 8 separate booleans values would normally take 8 bytes. But the examples above (using std::uint8_t) use 9 bytes -- 8 bytes to define the bit masks, and 1 byte for the flag variable!

#### 🧠 What the Statement Means:

#### 🔹 Problem:

If you have **many objects** (e.g., 100 people), and each object needs to store **several boolean states** (like hungry, tired, happy, etc.), you might be tempted to do this:

```cpp
struct PersonStates {
    bool hungry;
    bool tired;
    bool happy;
    bool sad;
    bool busy;
    bool sleeping;
    bool angry;
    bool bored;
};

```

Each `bool` usually takes **1 byte** (even though it stores just 1 bit), due to alignment and compiler behavior.

So:

- 8 `bool`s × 1 byte each = **8 bytes per person**
    
- 100 people → **800 bytes total**

#### 🔹 Bit Flags Optimization

Instead of 8 separate `bool`s, you can use **1 `uint8_t`** (8 bits) to store **all 8 flags** per person using **bitwise operations**.

```cpp
struct Person {
    std::uint8_t flags; // each bit represents one state
};

```

Then you use **bit masks** and bitwise operators to read/set/clear each flag.

So:

- 1 byte per person → **100 bytes total**
    
- Plus 8 bytes (or less) for global bit masks → **~108 bytes total**
    

🧠 That’s **~8x less memory usage**!

#### ✅ Example

##### 👎 Without Bit Flags

```cpp
struct PersonStates {
    bool hungry;
    bool tired;
    bool happy;
    bool sad;
    bool busy;
    bool sleeping;
    bool angry;
    bool bored;
};

PersonStates people[100]; // uses 800 bytes

```

#### ✅ With Bit Flags

```cpp
constexpr std::uint8_t hungry   = 0b0000'0001;
constexpr std::uint8_t tired    = 0b0000'0010;
// ... up to 0b1000'0000

struct Person {
    std::uint8_t flags;
};

Person people[100]; // only 100 bytes

```
#### ✅ Conclusion

Using **bit flags** is a **compact, fast, and scalable** way to store multiple boolean states — especially when you're managing **large arrays** or **tight memory environments** (e.g., embedded systems, games, etc.).

Let me know if you'd like help creating a reusable class or struct to handle this cleanly!

>For most programs, the amount of memory saved using bit flags is not worth the added complexity. But in programs where there are tens of thousands or even millions of similar objects, using bit flags can reduce memory use substantially. It’s a useful optimization to have in your toolkit if you need it.

>There’s another case where bit flags and bit masks can make sense. Imagine you had a function that could take any combination of 32 different options. One way to write that function would be to use 32 individual Boolean parameters:

```cpp
void someFunction(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6, bool option7, bool option8, bool option9, bool option10, bool option11, bool option12, bool option13, bool option14, bool option15, bool option16, bool option17, bool option18, bool option19, bool option20, bool option21, bool option22, bool option23, bool option24, bool option25, bool option26, bool option27, bool option28, bool option29, bool option30, bool option31, bool option32);
```

Hopefully you’d give your parameters more descriptive names, but the point here is to show you how obnoxiously long the parameter list is.

Then when you wanted to call the function with options 10 and 32 set to true, you’d have to do so like this:

```cpp
someFunction(false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true);
```

This is ridiculously difficult to read (is that option 9, 10, or 11 that’s set to true?), and also means you have to remember which argument corresponds to which option (is setting the “edit flag” the 9th, 10th, or 11th parameter?).

Instead, if you defined the function using bit flags like this:

```cpp
void someFunction(std::bitset<32> options);
```

Then you could use bit flags to pass in only the options you wanted:

```cpp
someFunction(option10 | option32);
// combines the result of 10 and 32
```

#### REAL world example

This is much more readable.

This is one of the reasons OpenGL, a well regarded 3d graphic library, opted to use bit flag parameters instead of many consecutive Boolean parameters.

Here’s a sample function call from OpenGL:

```cpp
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color and the depth buffer
```

GL_COLOR_BUFFER_BIT and GL_DEPTH_BUFFER_BIT are bit masks defined as follows (in gl2.h):

```cpp
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000
```

#### 🔥 Why Combine Bit Flags with `|`?

Combining bit flags with the **bitwise OR (`|`)** operator allows you to:

> **Pass multiple options at once using a single variable.**

This is efficient, compact, and extremely flexible.

#### 🧠 Core Idea:

Each bit in an integer represents **a different flag (option/state)**.

When you **combine** bit flags using `|`, you're **turning on multiple bits** — each representing a different feature or behavior.

---
### Bit masks involving multiple bits

Although bit masks often are used to select a single bit, they can also be used to select multiple bits. Lets take a look at a slightly more complicated example where we do this.

Color display devices such as TVs and monitors are composed of millions of pixels, each of which can display a dot of color. Each dot of color is the result of combining three beams of light: one red, one green, and one blue (RGB). The intensity of these lights are varied to produce different colors.

Typically, the intensity of R, G, and B for a given pixel is represented by an 8-bit unsigned integer. For example, a red pixel would have R=255, G=0, B=0. A purple pixel would have R=255, G=0, B=255. A medium-grey pixel would have R=127, G=127, B=127.

When assigning color values to a pixel, in addition to R, G, and B, a 4th value called A is often used. “A” stands for “alpha”, and it controls how transparent the color is. If A=0, the color is fully transparent. If A=255, the color is opaque.

R, G, B, and A are normally stored as a single 32-bit integer, with 8 bits used for each component:

The following program asks the user to enter a 32-bit hexadecimal value, and then extracts the 8-bit color values for R, G, B, and A.

```cpp
#include <cstdint>
#include <iostream>

int main()
{
	constexpr std::uint32_t redBits{ 0xFF000000 };
	constexpr std::uint32_t greenBits{ 0x00FF0000 };
	constexpr std::uint32_t blueBits{ 0x0000FF00 };
	constexpr std::uint32_t alphaBits{ 0x000000FF };

	std::cout << "Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): ";
	std::uint32_t pixel{};
	std::cin >> std::hex >> pixel; // std::hex allows us to read in a hex value

	// use Bitwise AND to isolate the pixels for our given color,
	// then right shift the value into the lower 8 bits
	const std::uint8_t red{ static_cast<std::uint8_t>((pixel & redBits) >> 24) };
	const std::uint8_t green{ static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
	const std::uint8_t blue{ static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
	const std::uint8_t alpha{ static_cast<std::uint8_t>(pixel & alphaBits) };

	std::cout << "Your color contains:\n";
	std::cout << std::hex; // print the following values in hex

        // reminder: std::uint8_t will likely print as a char
        // we static_cast to int to ensure it prints as an integer
	std::cout << static_cast<int>(red)   << " red\n";
	std::cout << static_cast<int>(green) << " green\n";
	std::cout << static_cast<int>(blue)  << " blue\n";
	std::cout << static_cast<int>(alpha) << " alpha\n";

	return 0;
}
```

This produces the output:

Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): FF7F3300
Your color contains:
ff red
7f green
33 blue
0 alpha

In the above program, we use a _bitwise AND_ to query the set of 8 bits we’re interested in, and then we _right shift_ them into an 8-bit value so we can print them back as hex values.

---
### Method 3 for converting decimal to binary

This method is a variant of method 2 that uses integer division. Consider the decimal number 148 yet again. The largest power of 2 that’s smaller than 148 is 128, so we’ll start there.

148 / 128 = 1 with some remainder. Since 1 is odd, this bit is a 1.  
148 / 64 = 2 with some remainder. Since 2 is even, this bit is a 0.  
148 / 32 = 4 with some remainder. Since 4 is even, this bit is a 0.  
148 / 16 = 9 with some remainder. Since 9 is odd, this bit is a 1.  
148 / 8 = 18 with some remainder. Since 18 is even, this bit is a 0.  
148 / 4 = 37 with some remainder. Since 37 is odd, this bit is a 1.  
148 / 2 = 74 with some remainder. Since 74 is even, this bit is a 0.  
148 / 1 = 148 with some remainder. Since 148 is even, this bit is a 0.


148 = (1 * 128) + (0 * 64) + (0 * 32) + (1 * 16) + (0 * 8) + (1 * 4) + (0 * 2) + (0 * 1) = 1001 0100

This method isn’t great for humans, as it requires a lot of division. It’s also less efficient for machines since division is an inefficient operation. But it is easy to write in code since it requires no if-statements.

---
### [Addition in Binary](https://www.learncpp.com/cpp-tutorial/converting-integers-between-binary-and-decimal-representation/#:~:text=Adding%20in%20binary,binary)

---
### Signed numbers and two’s complement

In the above examples, we’ve dealt solely with unsigned integers. In this section, we’ll take a look at how signed numbers (which can be negative) are dealt with.

Signed integers are typically stored using a method known as **two’s complement**. In two’s complement, the leftmost (most significant) bit is used as the sign bit. A 0 sign bit means the number is positive (or zero), and a 1 sign bit means the number is negative.

Positive signed numbers are represented in binary just like positive unsigned numbers (with the sign bit set to 0).

Negative signed numbers are represented in binary as the bitwise inverse of the positive number, plus 1.

---
### Converting decimal to binary (two’s complement)

For example, here’s how we represent -5 in binary two’s complement:

First we figure out the binary representation for 5: 0000 0101  
Then we invert all of the bits: 1111 1010  
Then we add 1: 1111 1011

Converting -76 to binary:

Positive 76 in binary: 0100 1100  
Invert all the bits: 1011 0011  
Add 1: 1011 0100

Why do we add 1? Consider the number 0. If a negative value was simply represented as the inverse of the positive number (called “one’s complement”), 0 would have two representations: 0000 0000 (positive zero) and 1111 1111 (negative zero). By adding 1, 1111 1111 intentionally overflows and becomes 0000 0000. This prevents 0 from having two representations, and simplifies some of the internal logic needed to do arithmetic with negative numbers.

####  🔢 **The Problem with One’s Complement**

In binary systems, to represent **negative numbers**, one early approach was called **one’s complement**:

- You **invert** all the bits of the positive number.
    
- For example:
    
    - `+5` in 8-bit binary: `0000 0101`
        
    - One’s complement of `+5` → `1111 1010` (which represents `-5` in one's complement)
        

But there’s a **problem with zero** in one’s complement:

- `+0` = `0000 0000`
    
- `-0` = `1111 1111`
    

Now you have **two ways to represent zero**, which can cause complications in comparisons, arithmetic, etc.

#### ✅ **The Solution: Two’s Complement**

To solve this, we use **two’s complement**, which works like this:

> To represent a negative number, invert all bits of the number and **add 1**.

Example:  
Represent `-5` using two’s complement in 8-bit:

- Start with `+5`: `0000 0101`
    
- Invert bits: `1111 1010`
    
- Add 1: `1111 1011` ← this is `-5`
    

Now let’s try the same for `0`:

- `+0`: `0000 0000`
    
- Invert: `1111 1111`
    
- Add 1: `0000 0000` ← we’re back to zero!
    

✅ So `-0` and `+0` are **the same**, and we avoid the duplicate representation.


#### 🔁 **Why “Adding 1” Fixes the Problem**

Without adding 1:

- `1111 1111` = `-0` (bad)
    

With adding 1:

- `1111 1111 + 1 = 0000 0000` (wraps around) = `+0` (good!)
    

This **overflow** behavior is intentional and useful:

- Ensures a **unique zero**
    
- Simplifies arithmetic logic in hardware
    
- Makes addition/subtraction work consistently across positive and negative numbers
    

#### 🔍 Summary

We **add 1** after bit inversion to create **two’s complement** form.  
This:

- Eliminates the need for two representations of zero
    
- Simplifies arithmetic logic in CPUs
    
- Makes operations like subtraction easier and faster in binary

---

### Converting binary (two’s complement) to decimal

To convert a two’s complement binary number back into decimal, first look at the sign bit.

If the sign bit is 0, just convert the number as shown for unsigned numbers above.

If the sign bit is 1, then we invert the bits, add 1, then convert to decimal, then make that decimal number negative (because the sign bit was originally negative).

For example, to convert 1001 1110 from two’s complement into a decimal number:  
Given: 1001 1110  
Invert the bits: 0110 0001  
Add 1: 0110 0010  
Convert to decimal: (0 * 128) + (1 * 64) + (1 * 32) + (0 * 16) + (0 * 8) + (0 * 4) + (1 * 2) + (0 * 1) = 64 + 32 + 2 = 98  
Since the original sign bit was negative, the final value is -98.

There is another method that is easier to calculate by hand. In this method, the sign bit represents a negative value, all the other bits represent positive values.

Given: 1001 1110  
Convert to decimal: (1 * -128) + (0 * 64) + (0 * 32) + (1 * 16) + (1 * 8) + (1 * 4) + (1 * 2) + (0 * 1) = -128 + 16 + 8 + 4 + 2 = -98

---
### Why types matter

Consider the binary value 1011 0100. What value does this represent? You’d probably say 180, and if this were an unsigned binary number, you’d be right.

However, if this value was stored using two’s complement, it would be -76.

And if the value were encoded some other way, it could be something else entirely.

So how does C++ know whether to print a variable containing binary 1011 0100 as 180 or -76?

In case the section title didn’t give it away, this is where types come into play. The type of the variable determines both how a variable’s value is encoded into binary, and decoded back into a value. So if the variable type was an unsigned integer, it would know that 1011 0100 was standard binary, and should be printed as 180. If the variable was a signed integer, it would know that 1011 0100 was encoded using two’s complement (now guaranteed as of C++20), and should be printed as -76.

---
