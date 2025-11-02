# PSsODIN

![tests](https://github.com/PeterSommerlad/PSsODIN/actions/workflows/runtests.yml/badge.svg?branch=main)

<br/>

<!-- ![conan check](https://github.com/PeterSommerlad/PSsODIN/actions/workflows/runconantest.yml/badge.svg?branch=main) -->


## Introduction

A C++20 implementation of safe overflow detecting integers following MISRA C++ rules.

<!-- An `#ifdef`ed C++17 implementation is available in branch C++17. -->

I provide two implementations of saturating integer arithmetic for signed and unsigned integers of sizes 8, 16, 32, 64 bits. 

* [pssodin.h](include/pssodin.h) is using `enum class` types and corresponding operator overloading etc.
* [odins.h](include/odins.h) is using a class template for the integers with fixed sizes. 

Note that according to MISRA C++ guidelines arithmetic on character types (i.e., `char16_t`) is not supported.

All operations are supported at compile time and this is checked by the tests.

Invalid operations (according to MISRA-C++ integer rules), such as combining too large types in arithmetic with smaller types or mixing signed and unsigned values in operations are prevented to compile.

Any operation that overflows, also for unsigned types, will generate a run-time error and don't have undefined behavior, this includes:

* Shifting by too many bits.
* Negating the minimal signed value.
* Division by zero.

You can play with it and observe code generation on [Compiler Explorer enum](https://godbolt.org/z/33ac3Khar) 

It provides the following types in `namspace pssodin` and corresponding UDL operators in `namespace pssodin::literals`:

```C++
// unsigned
enum class cui8;   auto a = 1_cui8;
enum class cui16;  auto b = 2_cui16;
enum class cui32;  auto c = 3_cui32;
enum class cui64;  auto d = 4_cui64;
// signed
enum class csi8;   auto e = 5_csi8;
enum class csi16;  auto f = 6_csi16;
enum class csi32;  auto g = 7_csi32;
enum class csi64;  auto h = 8_csi64;
```

The class-based implementation `odins.h` benefits from having checking constructors for explicit conversion from all sized integer types and uses the same class names and suffixes in `namespace odins` and `namespace odins::literals`.

You can play with it and observe code generation on [Compiler Explorer class-based](https://godbolt.org/z/djcxTbr9e)


Some extra features:
* an output operator is defined and will output also `cui8` and `csi8` as integer values.
* The UDL operators check for range as well.
* not recommended features for the enum case:
   * `to_int(val)` promotes the safe integer val to built-in integer keeping its signedness
   * `to_underlying(val)` allows access to the underlying-type's value, use with care in operations because of promotion. This is useful for existing function overloads.
   * `from_int(val)` converts one of the allowed integer type's value to corresponding safe integer type. This is useful for integration with not-yet adapted code. Prevents conversion from `char` (+other character types) and `bool`.
      Note, that depending on the definition of the types in `<cstdint>` not all built-in integer types will convert, for example, if `std::int32_t` is defined as `int` and `std::int64_t` is defined as `long long`, you cannot convert a `42L`, because its conversion rank differs from both. 
   * `from_int_to<safeinttype>(val)` converts integer to safe integer type with range check (throws or aborts if mismatch).
* the class-based solution provides explicit constructors from all integral types (value checked) and an explicit conversion operator to the underlying type.


The following MISRA C++ recommendations for integer usage are implemented:

* No mixing of signed and unsigned types or with any standard-defined arithmetic types
* Integral promotion (only when mixing types in operations) will keep signedness
* Operations using the same operand type result in said type (no implicit promotion)
* Operations using mixed types of the same signedness promote to the bigger type first
* All operations detect overflow, even for unsigned types
* Bitwise operations are only defined for unsigned types
* Negation is only defined for signed types
* Comparison is only available through operands of the same type, using built-in comparison (`<=>` in 20)

What else do you want?


## Licensing

see [MIT open source license](LICENSE)

**For industrial use, commercial licensing and support is available on request**
