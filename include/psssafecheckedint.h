#ifndef SRC_PSSODIN_
#define SRC_PSSODIN_

#include <cstdint>
#include <type_traits>
#include <iosfwd>
#include <limits>
#include <climits>
// define to non-zero for self-kill with core dump, testing requires 0 for throw
#ifndef PSSODIN_SHOULD_RAISE
#define PSSODIN_SHOULD_RAISE 0
#endif

#if PSSODIN_SHOULD_RAISE
#include <csignal>
// SIGFPE dumps core (unless prohibited by OS, i.e., ulimit -c 0, macos cores are more tricky to get
#define PSSODIN_RAISE_SIGFPE() ::raise(SIGFPE)
#else
#define PSSODIN_RAISE_SIGFPE()
#endif

#define ps_assert( cond, msg) \
   if (not (cond)) { PSSODIN_RAISE_SIGFPE() ; throw(#msg); } ;

// NDEBUG causes std::terminate on errors, unless SIGFPE is raised
#ifdef NDEBUG
#define NOEXCEPT_WITH_THROWING_ASSERTS noexcept(true)
#else
#define NOEXCEPT_WITH_THROWING_ASSERTS noexcept(false)
#endif




namespace pssodin { // Peter Sommerlad's simple Overflow Detecting Integral Numbers PSsODIN


// unsigned 
enum class [[nodiscard]] ui8: std::uint8_t { pssodin_tag_to_prevent_mixing_other_enums };
enum class [[nodiscard]]ui16: std::uint16_t{ pssodin_tag_to_prevent_mixing_other_enums };
enum class [[nodiscard]]ui32: std::uint32_t{ pssodin_tag_to_prevent_mixing_other_enums };
enum class [[nodiscard]]ui64: std::uint64_t{ pssodin_tag_to_prevent_mixing_other_enums };

inline namespace literals {
consteval
ui8 operator""_cui8(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<ui8>>::max()) {
        return ui8(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
ui16 operator""_cui16(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<ui16>>::max()) {
        return ui16(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
ui32 operator""_cui32(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<ui32>>::max()) {
        return ui32(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
ui64 operator""_cui64(unsigned long long val) {
    if constexpr (sizeof(ui64) < sizeof(val)){
        if (val > 0xffff'ffff'fffffffful) {
            throw "integral constant too large"; // trigger compile-time error
        }
    }
    return ui64(val);
}

}
// signed
enum class [[nodiscard]]si8 : std::int8_t { pssodin_tag_to_prevent_mixing_other_enums };
enum class [[nodiscard]]si16: std::int16_t{ pssodin_tag_to_prevent_mixing_other_enums };
enum class [[nodiscard]]si32: std::int32_t{ pssodin_tag_to_prevent_mixing_other_enums };
enum class [[nodiscard]]si64: std::int64_t{ pssodin_tag_to_prevent_mixing_other_enums };

inline namespace literals {
consteval
si8 operator""_csi8(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si8>>::max()) {
        return si8(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
si16 operator""_csi16(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si16>>::max()) {
        return si16(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
si32 operator""_csi32(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si32>>::max()) {
        return si32(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
si64 operator""_csi64(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si64>>::max()) {
        return si64(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}
}




template<typename T>
using plain = std::remove_cvref_t<T>;

template<typename T>
concept an_enum = std::is_enum_v<plain<T>>;


namespace detail_ {
// from C++23
template<an_enum T>
constexpr bool
is_scoped_enum_v = not std::is_convertible_v<T, std::underlying_type_t<T>>;

template<typename T>
concept a_scoped_enum = is_scoped_enum_v<T>;


// detection concept

template<typename T>
constexpr bool
is_safeint_v = false;

template<a_scoped_enum E>
constexpr bool
is_safeint_v<E> = requires { E{} == E::pssodin_tag_to_prevent_mixing_other_enums; } ;

template<typename E>
using ULT=std::conditional_t<std::is_enum_v<plain<E>>,std::underlying_type_t<plain<E>>,plain<E>>;

template<typename E>
using promoted_t = // will promote keeping signedness
        std::conditional_t<(sizeof(ULT<E>) < sizeof(int))
            , std::conditional_t<std::is_unsigned_v<ULT<E>>
                , unsigned
                , int >
            , ULT<E>>;




}


template<typename E>
concept a_safeint = detail_::is_safeint_v<E>;

} // psssint


// provide std::numeric_limits
namespace std {



template<pssodin::a_safeint type>
  struct numeric_limits<type>
  {
    using ult = pssodin::detail_::ULT<type>;
    static constexpr bool is_specialized = true;

    static constexpr type
    min() noexcept { return type{numeric_limits<ult>::min()}; }

    static constexpr type
    max() noexcept { return type{numeric_limits<ult>::max()}; }

    static constexpr type
    lowest() noexcept { return type{numeric_limits<ult>::lowest()}; }

    static constexpr int digits = numeric_limits<ult>::digits;
    static constexpr int digits10 = numeric_limits<ult>::digits10;
    static constexpr int max_digits10 = numeric_limits<ult>::max_digits10;
    static constexpr bool is_signed = numeric_limits<ult>::is_signed;
    static constexpr bool is_integer = numeric_limits<ult>::is_integer;
    static constexpr bool is_exact = numeric_limits<ult>::is_exact;
    static constexpr int radix = numeric_limits<ult>::radix;

    static constexpr type
    epsilon() noexcept {  return type{numeric_limits<ult>::epsilon()}; }

    static constexpr type
    round_error() noexcept {  return type{numeric_limits<ult>::round_error()}; }

    static constexpr int min_exponent = numeric_limits<ult>::min_exponent;
    static constexpr int min_exponent10 = numeric_limits<ult>::min_exponent10;
    static constexpr int max_exponent = numeric_limits<ult>::max_exponent;
    static constexpr int max_exponent10 = numeric_limits<ult>::max_exponent10;

    static constexpr bool has_infinity = numeric_limits<ult>::has_infinity;
    static constexpr bool has_quiet_NaN = numeric_limits<ult>::has_quiet_NaN;
    static constexpr bool has_signaling_NaN = numeric_limits<ult>::has_signaling_NaN;
    static constexpr float_denorm_style has_denorm
     = numeric_limits<ult>::has_denorm;
    static constexpr bool has_denorm_loss = numeric_limits<ult>::has_denorm_loss;

    static constexpr type
    infinity() noexcept { return type{numeric_limits<ult>::infinity()}; }

    static constexpr type
    quiet_NaN() noexcept { return type{numeric_limits<ult>::quiet_NaN()}; }

    static constexpr type
    signaling_NaN() noexcept
    { return type{numeric_limits<ult>::signaling_NaN()}; }

    static constexpr type
    denorm_min() noexcept
    { return type{numeric_limits<ult>::denorm_min()}; }

    static constexpr bool is_iec559 =  numeric_limits<ult>::is_iec559;
    static constexpr bool is_bounded =  numeric_limits<ult>::is_bounded;
    static constexpr bool is_modulo =  true;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before =  numeric_limits<ult>::tinyness_before;
    static constexpr float_round_style round_style =  numeric_limits<ult>::round_style;
  };

}

namespace pssodin{

namespace detail_{

template<a_safeint LEFT, a_safeint RIGHT>
constexpr bool
same_signedness_v = detail_::is_safeint_v<LEFT> && detail_::is_safeint_v<RIGHT> && std::numeric_limits<LEFT>::is_signed == std::numeric_limits<RIGHT>::is_signed;

template<typename CHAR>
constexpr bool
is_chartype_v =    std::is_same_v<char,CHAR>
                || std::is_same_v<wchar_t,CHAR>
#ifdef __cpp_char8_t
                || std::is_same_v<char8_t,CHAR>
#endif
                || std::is_same_v<char16_t,CHAR>
                || std::is_same_v<char32_t,CHAR> ;



template<typename INT, typename TESTED>
constexpr bool
is_compatible_integer_v = std::is_same_v<TESTED,INT> ||
   (   std::is_integral_v<TESTED>
   && not std::is_same_v<bool,TESTED>
   && not is_chartype_v<TESTED>
   && (std::is_unsigned_v<INT> == std::is_unsigned_v<TESTED>)
   && std::numeric_limits<TESTED>::max() == std::numeric_limits<INT>::max() );


template<typename TESTED>
constexpr bool
is_known_integer_v =    is_compatible_integer_v<std::uint8_t,  TESTED>
                     || is_compatible_integer_v<std::uint16_t, TESTED>
                     || is_compatible_integer_v<std::uint32_t, TESTED>
                     || is_compatible_integer_v<std::uint64_t, TESTED>
                     || is_compatible_integer_v<std::int8_t,  TESTED>
                     || is_compatible_integer_v<std::int16_t, TESTED>
                     || is_compatible_integer_v<std::int32_t, TESTED>
                     || is_compatible_integer_v<std::int64_t, TESTED>;

}

template<typename LEFT, typename RIGHT>
concept same_signedness = detail_::same_signedness_v<LEFT,RIGHT>;

template<a_safeint E>
[[nodiscard]]
constexpr auto
promote_keep_signedness(E val) noexcept
{ // promote keeping signedness
    return static_cast<detail_::promoted_t<E>>(val);// promote with sign extension
}

// not used in framework:
template<a_safeint E>
[[nodiscard]]
constexpr auto
to_underlying(E val) noexcept 
{ // plain value with all bad properties
    return static_cast<std::underlying_type_t<E>>(val);
}

template<a_safeint E>
[[nodiscard]]
constexpr auto
promote_to_unsigned(E val) noexcept
{ // promote to unsigned for wrap around arithmetic
    using u_result_t = std::make_unsigned_t<detail_::promoted_t<E>>;
    return static_cast<u_result_t>(promote_keep_signedness(val));
}

// deliberately not std::integral, because of bool and characters!
template<typename T>
concept an_integer = detail_::is_known_integer_v<T>;

#ifdef __has_builtin
#if __has_builtin(__builtin_add_overflow)
# define HAVE_GCC_OVERFLOW_CHECKING
#endif
#endif
#if defined(__clang__)
# define HAVE_GCC_OVERFLOW_CHECKING
#endif

namespace non_builtin {
// like built-ins __builtin_add_overflow return true on overflow
template<an_integer T>
[[nodiscard]]
constexpr bool non_builtin_add_overflow(T l, T r, T* result) noexcept {
    if constexpr (std::numeric_limits<T>::is_signed){
        if constexpr(sizeof(T) == sizeof(std::int64_t)){
            *result = static_cast<T>(static_cast<uint64_t>(l) + static_cast<uint64_t>(r));
            if (l < 0){
                return (r<0) && (*result > l);
            } else {
                return (r >= 0) && (*result < l);
            }
        } else {
            std::int64_t res {l};
            res += r;
            *result = static_cast<T>(res);
            return res != *result;
        }
    } else { // unsigned
        if constexpr(sizeof(T) == sizeof(std::uint64_t)){
            *result = l + r;
            return *result < l; // wrapped when true
        } else {
            std::uint64_t res {l};
            res += r;
            *result = static_cast<T>(res);
            return res != *result;
        }
    }
    return true;
}
template<an_integer T>
[[nodiscard]]
constexpr bool non_builtin_sub_overflow(T l, T r, T* result) noexcept {
    if constexpr (std::numeric_limits<T>::is_signed){
        if constexpr(sizeof(T) == sizeof(std::int64_t)){
            *result = static_cast<T>(static_cast<uint64_t>(l) - static_cast<uint64_t>(r));
            if (l >= 0){
                return (r<0) && (*result < l);
            } else {
                return (r >= 0) && (*result > l);
            }
        } else {
            std::int64_t res {l};
            res -= r;
            *result = static_cast<T>(res);
            return res != *result;
        }
    } else { // unsigned
        if constexpr(sizeof(T) == sizeof(std::uint64_t)){
            *result = l - r;
            return *result > l; // wrapped when true
        } else {
            std::uint64_t res {l};
            res -= r;
            *result = static_cast<T>(res);
            return res != *result;
        }
    }
    return true;
}
template<an_integer T>
[[nodiscard]]
constexpr bool non_builtin_mul_overflow(T l, T r, T* result) noexcept {
    if constexpr (std::numeric_limits<T>::is_signed){
        if constexpr(sizeof(T) == sizeof(std::int64_t)){
            bool resultnegative { (l < 0) != (r < 0) };
            uint64_t res{};
            auto abs64 { [](int64_t val) -> uint64_t { return val < 0? 1ULL + ~static_cast<uint64_t>(val):static_cast<uint64_t>(val);} };
            if (not non_builtin_mul_overflow(abs64(l), abs64(r), &res) ){
                if (resultnegative) {
                    if (res <= static_cast<uint64_t>(std::numeric_limits<int64_t>::max())+1ull){
                        *result = static_cast<T>(1ULL + ~res); // two's complement
                        return false;
                    }
                } else {
                    if (res <= static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
                        *result = static_cast<T>(res);
                        return false;
                    }
                }
            }
            return true; // overflow
        } else {
            std::int64_t res {l};
            res *= r;
            *result = static_cast<T>(res);
            return res != *result; // detect overflow bits
        }
    } else { // unsigned
        if constexpr(sizeof(T) == sizeof(std::uint64_t)){
            // compute high-parts and low-parts
            uint64_t lhigh { l >> 32 };
            uint64_t llow { l & 0xffff'ffffULL} ;
            uint64_t rhigh { r >> 32 };
            uint64_t rlow { r & 0xffff'ffffULL} ;
            if (lhigh > 0 && rhigh > 0) return true;
            uint64_t high_low{ lhigh>0? lhigh*rlow : rhigh*llow };
            if (high_low >> 32) return true; // overflow
            uint64_t low_low { llow * rlow } ;
            *result = (high_low << 32) + low_low;

            return *result < low_low; // detect overflow
        } else {
            std::uint64_t res {l};
            res *= r;
            *result = static_cast<T>(res);
            return res != *result;
        }
    }
    return true;
}
} // namespace non_builtin

#ifdef HAVE_GCC_OVERFLOW_CHECKING
template<an_integer T>
[[nodiscard]]
constexpr bool add_overflow(T l, T r, T* result) noexcept {
    return __builtin_add_overflow(l,r,result);
}
template<an_integer T>
[[nodiscard]]
constexpr bool sub_overflow(T l, T r, T* result) noexcept {
    return __builtin_sub_overflow(l,r,result);
}
template<an_integer T>
[[nodiscard]]
constexpr bool mul_overflow(T l, T r, T* result) noexcept {
    return __builtin_mul_overflow(l,r,result);
}

#else // DIY
template<an_integer T>
[[nodiscard]]
constexpr bool add_overflow(T l, T r, T* result) noexcept {
    return non_builtin::non_builtin_add_overflow(l,r,result);
}
template<an_integer T>
[[nodiscard]]
constexpr bool sub_overflow(T l, T r, T* result) noexcept {
    return non_builtin::non_builtin_sub_overflow(l,r,result);
}
template<an_integer T>
[[nodiscard]]
constexpr bool mul_overflow(T l, T r, T* result) noexcept {
    return non_builtin::non_builtin_mul_overflow(l,r,result);
}

#endif



template<an_integer TARGET, a_safeint E>
[[nodiscard]]
constexpr auto
promote_and_extend_to_unsigned(E val) noexcept
{ // promote to unsigned for wrap around arithmetic, with sign extension if needed
       using u_result_t = std::conditional_t< (sizeof(TARGET) > sizeof(detail_::promoted_t<E>)),
                std::make_unsigned_t<TARGET>, std::make_unsigned_t<detail_::promoted_t<E> > >;
       using s_result_t = std::make_signed_t<u_result_t>;
       return static_cast<u_result_t>(static_cast<s_result_t>(promote_keep_signedness(val)));// promote with sign extension
}
template<an_integer TARGET, a_safeint E>
[[nodiscard]]
constexpr auto
abs_promoted_and_extended_as_unsigned(E val) noexcept
 requires (std::numeric_limits<TARGET>::is_signed)
{ // promote to unsigned for wrap around arithmetic removing sign if negative
  // return just the bits for std::numeric_limits<TARGET>::min()
       using promoted_t = detail_::promoted_t<E>;
       using u_result_t = std::conditional_t< (sizeof(TARGET) > sizeof(promoted_t)),
                std::make_unsigned_t<TARGET>, std::make_unsigned_t<promoted_t > >;
       static_assert(std::is_unsigned_v<u_result_t>);
       using s_result_t = std::make_signed_t<u_result_t>;
       s_result_t value = promote_keep_signedness(val);
       if (val < E{} && value > std::numeric_limits<s_result_t>::min()){
           return static_cast<u_result_t>(-static_cast<s_result_t>(value)); // cannot overflow
       } else {
           return static_cast<u_result_t>(value);
       }
}






template<an_integer T>
[[nodiscard]]
constexpr auto
from_int(T val) noexcept {
    using detail_::is_compatible_integer_v;
    using std::conditional_t;
    struct cannot_convert_integer{};
    using result_t =
            conditional_t<is_compatible_integer_v<std::uint8_t,T>, ui8,
             conditional_t<is_compatible_integer_v<std::uint16_t,T>, ui16,
              conditional_t<is_compatible_integer_v<std::uint32_t,T>, ui32,
               conditional_t<is_compatible_integer_v<std::uint64_t,T>, ui64,
                conditional_t<is_compatible_integer_v<std::int8_t,T>, si8,
                 conditional_t<is_compatible_integer_v<std::int16_t,T>, si16,
                  conditional_t<is_compatible_integer_v<std::int32_t,T>, si32,
                   conditional_t<is_compatible_integer_v<std::int64_t,T>, si64, cannot_convert_integer>>>>>>>>;
    return static_cast<result_t>(val); // no need to check, result_t corresponds to input T's range
}
// path tests are compile-time checked:
template<a_safeint TO, an_integer FROM>
[[nodiscard]]
constexpr auto
from_int_to(FROM val) NOEXCEPT_WITH_THROWING_ASSERTS
{
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
    using result_t = TO;
    using ultr = std::underlying_type_t<result_t>;
    if constexpr(std::is_unsigned_v<ultr>){
        ps_assert(  (val >= FROM{} && // in case FROM is signed
                     static_cast<std::make_unsigned_t<FROM>>(val) <= std::numeric_limits<ultr>::max()), #__FUNCTION__ "integer value out of range") ;
    } else {
        if constexpr (std::is_unsigned_v<FROM>){
            ps_assert(  val <= static_cast<std::make_unsigned_t<ultr>>(std::numeric_limits<ultr>::max()), #__FUNCTION__ "integer value out of range");

        } else { // both are signed
            ps_assert(  (val <= std::numeric_limits<ultr>::max() &&
                                val >= std::numeric_limits<ultr>::min()), #__FUNCTION__ "integer value out of range");
        }
    }
#pragma GCC diagnostic pop
    return static_cast<result_t>(val); // cast is checked above
}


// comparison
// not needed, we won't mix types in comparison.
// enum class types compare three way implicitly with themselves


// negation for signed types only, two's complement
template<a_safeint E>
[[nodiscard]]
constexpr E
operator-(E l) NOEXCEPT_WITH_THROWING_ASSERTS
requires std::numeric_limits<E>::is_signed
{
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
    ps_assert(  l != std::numeric_limits<E>::min() , "negating std::numeric_limits<E>::min()" );
#pragma GCC diagnostic pop
    return static_cast<E>(1u + ~promote_to_unsigned(l));
}


// increment/decrement

template<a_safeint E>
constexpr E&
operator++(E& l) NOEXCEPT_WITH_THROWING_ASSERTS
{
    return l = static_cast<E>(1) + l;
}

template<a_safeint E>
constexpr E
operator++(E& l, int) NOEXCEPT_WITH_THROWING_ASSERTS
{
    auto result=l;
    ++l;
    return result;
}
template<a_safeint E>
constexpr E&
operator--(E& l) NOEXCEPT_WITH_THROWING_ASSERTS
{
    return l = l - static_cast<E>(1);
}

template<a_safeint E>
constexpr E
operator--(E& l, int) NOEXCEPT_WITH_THROWING_ASSERTS
{
    auto result=l;
    --l;
    return result;
}



// arithmetic

//// TODO: continue compile time tests for operators below


template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator+(LEFT l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    // need to handle sign extension
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    using ult = detail_::ULT<result_t>;
    ult result{};
    if (add_overflow(static_cast<ult>(l),static_cast<ult>(r),&result)){
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
        ps_assert( false , "pssodin: integer addition overflow");
#pragma GCC diagnostic pop
    }
    return static_cast<result_t>(result);
}


template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator+=(LEFT &l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    static_assert(sizeof(LEFT) >= sizeof(RIGHT),"pssodin: adding too large integer type");
    l = static_cast<LEFT>(l+r);
    return l;
}

template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator-(LEFT l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    using ult = detail_::ULT<result_t>;

    ult result{};
    if (sub_overflow(static_cast<ult>(l),static_cast<ult>(r),&result)){
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
        ps_assert( false , "pssodin: subtraction overflow");
#pragma GCC diagnostic pop
    }
    return static_cast<result_t>(result);
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator-=(LEFT &l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    static_assert(sizeof(LEFT) >= sizeof(RIGHT),"subtracting too large integer type");
    l = static_cast<LEFT>(l-r);
    return l;
}


template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator*(LEFT l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    using ult = detail_::ULT<result_t>;
    ult result{};
    if (mul_overflow(static_cast<ult>(l),static_cast<ult>(r),&result)){
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
        ps_assert( false , "pssodin: multiplication overflow");
#pragma GCC diagnostic pop
     }
    return static_cast<result_t>(result);
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator*=(LEFT &l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    static_assert(sizeof(LEFT) >= sizeof(RIGHT),"multiplying too large integer type");
    l = static_cast<LEFT>(l*r);
    return l;
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator/(LEFT const l, RIGHT const r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    using ult = detail_::ULT<result_t>;

#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
    ps_assert(  r != RIGHT{} , "pssodin: division by zero");
    if constexpr (std::numeric_limits<result_t>::is_signed){
        // detect -min / -1 which is overflow
        ps_assert(  static_cast<result_t>(l) != std::numeric_limits<result_t>::min() || r != -RIGHT{1} , "pssodin: signed division overflow");
#pragma GCC diagnostic pop
       bool result_is_negative = (l < LEFT{}) != (r < RIGHT{});
        auto const absresult =  static_cast<result_t>(
                             static_cast<ult>(
                                abs_promoted_and_extended_as_unsigned<ult>(l)
                                / // use unsigned op to prevent signed overflow, but wrap.
                                abs_promoted_and_extended_as_unsigned<ult>(r)));
        auto minint_div_one = [&]{return absresult == std::numeric_limits<result_t>::min() && r == RIGHT{1} ;};
        if (result_is_negative && not minint_div_one() ) {
            return -absresult; // compute two's complement, not built-in
        } else {
            return absresult;
        }
    } else {
    return static_cast<result_t>(
            static_cast<ult>(
                    promote_and_extend_to_unsigned<ult>(l)
                    / // use unsigned op no overflow possible on division after initial checks
                    promote_and_extend_to_unsigned<ult>(r)
            )
    );
    }

}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator/=(LEFT &l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT>
{
    static_assert(sizeof(LEFT) >= sizeof(RIGHT),"dividing by too large integer type");
    l = static_cast<LEFT>(l/r);
    return l;
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator%(LEFT l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires same_signedness<LEFT,RIGHT> && std::is_unsigned_v<detail_::ULT<LEFT>>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    using ult = detail_::ULT<result_t>;
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
    ps_assert(  r != RIGHT{}, "pssodin: modulo division by zero");
#pragma GCC diagnostic pop
    return static_cast<result_t>(
            static_cast<ult>(
                    promote_and_extend_to_unsigned<ult>(l)
                    % // unsigned modulo cannot overflow
                    promote_and_extend_to_unsigned<ult>(r)
            )
    );
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator%=(LEFT &l, RIGHT r) noexcept
requires same_signedness<LEFT,RIGHT> && std::is_unsigned_v<detail_::ULT<LEFT>>
{
    static_assert(sizeof(LEFT) >= sizeof(RIGHT),"dividing by too large integer type");
    l = static_cast<LEFT>(l%r);
    return l;
}

// bitwise operators

template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator&(LEFT l, RIGHT r) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    return static_cast<result_t>(promote_keep_signedness(l)&promote_keep_signedness(r));
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator&=(LEFT &l, RIGHT r) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    static_assert(sizeof(LEFT) == sizeof(RIGHT),"bitand by different sized integer type");
    l = static_cast<LEFT>(l&r);
    return l;
}

template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator|(LEFT l, RIGHT r) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    return static_cast<result_t>(promote_keep_signedness(l)|promote_keep_signedness(r));
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator|=(LEFT &l, RIGHT r) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    static_assert(sizeof(LEFT) == sizeof(RIGHT),"bitor by different sized integer type");
    l = static_cast<LEFT>(l|r);
    return l;
}

template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto
operator^(LEFT l, RIGHT r) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    using result_t=std::conditional_t<sizeof(LEFT)>=sizeof(RIGHT),LEFT,RIGHT>;
    return static_cast<result_t>(promote_keep_signedness(l)^promote_keep_signedness(r));
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator^=(LEFT &l, RIGHT r) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    static_assert(sizeof(LEFT) == sizeof(RIGHT),"xor by different sized integer type");
    l = static_cast<LEFT>(l^r);
    return l;
}

template<a_safeint LEFT>
constexpr LEFT
operator~(LEFT l) noexcept
requires std::is_unsigned_v<detail_::ULT<LEFT>>
{
    return static_cast<LEFT>(~promote_keep_signedness(l));
}


template<a_safeint LEFT, a_safeint RIGHT>
constexpr LEFT
operator<<(LEFT l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
    ps_assert( static_cast<size_t>(promote_keep_signedness(r)) < sizeof(LEFT)*CHAR_BIT , "pssodin: trying to left-shift by too many bits");
#pragma GCC diagnostic pop
    return static_cast<LEFT>(promote_keep_signedness(l)<<promote_keep_signedness(r));
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator<<=(LEFT &l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    l = (l<<r);
    return l;
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr LEFT
operator>>(LEFT l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wexceptions"

#else
#pragma GCC diagnostic ignored "-Wterminate"
#endif
#endif
    ps_assert( static_cast<size_t>(promote_keep_signedness(r)) < sizeof(LEFT)*CHAR_BIT , "pssodin: trying to right-shift by too many bits");
#pragma GCC diagnostic pop
    return static_cast<LEFT>(promote_keep_signedness(l)>>promote_keep_signedness(r));
}
template<a_safeint LEFT, a_safeint RIGHT>
constexpr auto&
operator>>=(LEFT &l, RIGHT r) NOEXCEPT_WITH_THROWING_ASSERTS
requires std::is_unsigned_v<detail_::ULT<LEFT>> && std::is_unsigned_v<detail_::ULT<RIGHT>>
{
    l = (l>>r);
    return l;
}


std::ostream& operator<<(std::ostream &out, a_safeint auto value){
    out << promote_keep_signedness(value);
    return out;
}

}

#undef ps_assert

#endif /* SRC_PSSODIN_ */
