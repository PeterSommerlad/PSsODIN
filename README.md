# PSsODIN

![tests](https://github.com/PeterSommerlad/PSsODIN/actions/workflows/runtests.yml/badge.svg?branch=main)

<br/>

![conan check](https://github.com/PeterSommerlad/PSsODIN/actions/workflows/runconantest.yml/badge.svg?branch=main)


## Introduction

A C++20 implementation of safe overflow detecting integers following MISRA C++ rules is on the main branch.

An `#ifdef`ed C++17 implementation is available in branch C++17.


It provides the following types in `namspace pssodin` and corresponding UDL operators in `namespace pssodin::literals`:

```C++
// unsigned
enum class ui8;   auto a = 1_cui8;
enum class ui16;  auto b = 2_cui16;
enum class ui32;  auto c = 3_cui32;
enum class ui64;  auto d = 4_cui64;
// signed
enum class si8;   auto e = 5_csi8;
enum class si16;  auto f = 6_csi16;
enum class si32;  auto g = 7_csi32;
enum class si64;  auto h = 8_csi64;
```

You can play around with it on compiler explorer starting soon... <!-- [here](https://godbolt.org/z/TvnrrEzEK)-->


Some extra features:
* an output operator is defined and will output also `ui8` and `si8` as integer values.
* The UDL operators check for range as well.
* not recommended features:
   * `to_int(val)` promotes the safe integer val to built-in integer keeping its signedness
   * `to_underlying(val)` allows access to the underlying-type's value, use with care in operations because of promotion. This is useful for existing function overloads.
   * `from_int(val)` converts one of the allowed integer type's value to corresponding safe integer type. This is useful for integration with not-yet adapted code. Prevents conversion from `char` (+other character types) and `bool`.
      Note, that depending on the definition of the types in `<cstdint>` not all built-in integer types will convert, for example, if `std::int32_t` is defined as `int` and `std::int64_t` is defined as `long long`, you cannot convert a `42L`, because its conversion rank differs from both. 
   * `from_int_to<safeinttype>(val)` converts integer to safe integer type with range check (throws or aborts if mismatch).

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
