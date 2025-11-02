#ifndef SRC_ODINS_H_
#define SRC_ODINS_H_

#include <cstdint>
#include <type_traits>
#include <iosfwd>
#include <limits>
#include <climits>
#include <compare>
#include <concepts>

// define to non-zero for self-kill with core dump, testing requires 0 for throw
#ifndef PSSODIN_SHOULD_RAISE
#define PSSODIN_SHOULD_RAISE 0
#endif

#if PSSODIN_SHOULD_RAISE
#include <csignal>
// SIGFPE (arithmetic error) dumps core (unless prohibited by OS, i.e., ulimit -c 0, macos cores are more tricky to get
#define PSSODIN_RAISE_SIGFPE() ::raise(SIGFPE)
#else
#define PSSODIN_RAISE_SIGFPE()
#endif

#define ps_assert( cond, msg) \
   if (not (cond)) { PSSODIN_RAISE_SIGFPE() ; throw(msg); } ;

// no NDEBUG-like support, because we want safety!


namespace odins { // SATuration Integral Numbers with struct
namespace detail_ {
template<typename T>
using plain = std::remove_cvref_t<T>;

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

// only support the following sizes:
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
template<typename TESTED>
concept sized_integer = detail_::is_known_integer_v<TESTED>;
// deliberately not std::integral, because of bool and characters!
namespace detail_ {

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
template<sized_integer T>
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
template<sized_integer T>
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
template<sized_integer T>
[[nodiscard]]
constexpr bool non_builtin_mul_overflow(T l, T r, T* result) noexcept {
    if constexpr (std::numeric_limits<T>::is_signed){
        if constexpr(sizeof(T) == sizeof(std::int64_t)){
            bool resultnegative { (l < 0) != (r < 0) };
            uint64_t res{};
            auto abs64 { [](int64_t value) -> uint64_t { return value < 0? 1ULL + ~static_cast<uint64_t>(value):static_cast<uint64_t>(value);} };
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
template<sized_integer T>
[[nodiscard]]
constexpr bool add_overflow(T l, T r, T* result) noexcept {
    return __builtin_add_overflow(l,r,result);
}
template<sized_integer T>
[[nodiscard]]
constexpr bool sub_overflow(T l, T r, T* result) noexcept {
    return __builtin_sub_overflow(l,r,result);
}
template<sized_integer T>
[[nodiscard]]
constexpr bool mul_overflow(T l, T r, T* result) noexcept {
    return __builtin_mul_overflow(l,r,result);
}

#else // DIY
template<sized_integer T>
[[nodiscard]]
constexpr bool add_overflow(T l, T r, T* result) noexcept {
    return non_builtin::non_builtin_add_overflow(l,r,result);
}
template<sized_integer T>
[[nodiscard]]
constexpr bool sub_overflow(T l, T r, T* result) noexcept {
    return non_builtin::non_builtin_sub_overflow(l,r,result);
}
template<sized_integer T>
[[nodiscard]]
constexpr bool mul_overflow(T l, T r, T* result) noexcept {
    return non_builtin::non_builtin_mul_overflow(l,r,result);
}

#endif




} // NS detail_


template<sized_integer INT>
struct Odin;

namespace detail_{
template<typename T>
constexpr bool is_overflowdetectingint_v = false;
template<sized_integer I>
constexpr bool is_overflowdetectingint_v<Odin<I>> = true;

template<typename C>
struct ULT_impl;
template<typename I>
struct ULT_impl<Odin<I>>{
    using type=I;
};
} // NS detail_
template<typename E>
concept an_overflowdetectingint = detail_::is_overflowdetectingint_v<E>;

template<typename C>
using ULT=detail_::ULT_impl<detail_::plain<C>>::type;

namespace detail_ {

template<typename E>
using promoted_t = // will promote the underlying type keeping signedness
        std::conditional_t<(sizeof(ULT<E>) < sizeof(int))
            , std::conditional_t<std::is_unsigned_v<ULT<E>>
                , unsigned
                , int >
            , ULT<E>>;

template<an_overflowdetectingint E>
[[nodiscard]]
constexpr auto
promote_keep_signedness(E value) noexcept
{ // promote keeping signedness
    return static_cast<promoted_t<E>>((value.value_which_should_not_be_referred_to_from_user_code));// promote with sign extension
}


template<an_overflowdetectingint E>
[[nodiscard]]
constexpr auto
promote_to_unsigned(E value) noexcept
{ // promote to unsigned for wrap around arithmetic
    using u_result_t = std::make_unsigned_t<promoted_t<E>>;
    return static_cast<u_result_t>(promote_keep_signedness(value));
}
template<sized_integer TARGET, an_overflowdetectingint E>
[[nodiscard]]
constexpr auto
promote_and_extend_to_unsigned(E value) noexcept
{ // promote to unsigned for wrap around arithmetic, with sign extension if needed
       using u_result_t = std::conditional_t< (sizeof(TARGET) > sizeof(promoted_t<E>)),
                std::make_unsigned_t<TARGET>, std::make_unsigned_t<promoted_t<E> > >;
       using s_result_t = std::make_signed_t<u_result_t>;
       return static_cast<u_result_t>(static_cast<s_result_t>(promote_keep_signedness(value)));// promote with sign extension
}


} // NS detail_

template<typename LEFT, typename RIGHT>
constexpr bool
same_signedness_v = std::numeric_limits<LEFT>::is_signed == std::numeric_limits<RIGHT>::is_signed;

template<typename LEFT, typename RIGHT>
concept same_signedness = same_signedness_v<LEFT,RIGHT>;



template<sized_integer INT>
struct Odin{
    constexpr Odin() noexcept:value_which_should_not_be_referred_to_from_user_code{}{}
    explicit constexpr Odin(std::same_as<INT> auto v) noexcept:value_which_should_not_be_referred_to_from_user_code(v){
    }
    friend constexpr auto operator<=>(Odin, Odin) noexcept = default;
    explicit constexpr operator INT() const noexcept { return value_which_should_not_be_referred_to_from_user_code;}
    template<std::integral FROM>
    explicit constexpr Odin(FROM v)
    requires (not std::same_as<INT,detail_::plain<FROM>>)
    :value_which_should_not_be_referred_to_from_user_code(v){
        if constexpr(std::is_unsigned_v<INT>){
            ps_assert(  (v >= FROM{} && // in case FROM is signed
                         static_cast<std::make_unsigned_t<FROM>>(v) <= std::numeric_limits<INT>::max()), "odins: integer value out of range") ;
        } else {
            if constexpr (std::is_unsigned_v<FROM>){
                ps_assert(  v <= static_cast<std::make_unsigned_t<INT>>(std::numeric_limits<INT>::max()), "odins: integer value out of range");

            } else { // both are signed
                ps_assert(  (v <= std::numeric_limits<INT>::max() &&
                                    v >= std::numeric_limits<INT>::min()), "odins: integer value out of range");
            }
        }
    }

    // member/friend operators

    // negation for signed types only, two's complement
    constexpr auto
    operator-() const
    requires std::numeric_limits<INT>::is_signed
    {
        ps_assert(  value_which_should_not_be_referred_to_from_user_code != std::numeric_limits<INT>::min() , "odins: negating std::numeric_limits<>::min()" );

        return static_cast<Odin>(static_cast<INT>(1u + ~detail_::promote_to_unsigned(*this)));
    }

    // increment/decrement

    constexpr Odin& operator++() &
    {
        return *this =  *this + static_cast<Odin>(1) ;
    }

    constexpr Odin operator++(int) &
    {
        auto result=*this;
        ++*this;
        return result;
    }
    constexpr Odin& operator--() &
    {
        return *this = *this - static_cast<Odin>(1);
    }

    constexpr Odin operator--(int) &
    {
        auto result=*this;
        --*this;
        return result;
    }

    // arithmetic

    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator+(Odin l, RIGHT r)
    requires same_signedness<Odin,RIGHT>
    {
        // handle sign extension
        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        using ult = ULT<result_t>;
        ult result{};
        ult const left{static_cast<ult>(static_cast<ULT<Odin>>(l))};
        ult const right{static_cast<ult>(static_cast<ULT<RIGHT>>(r))};
        if (detail_::add_overflow(left,right,&result)){
            ps_assert( false , "odins: integer addition overflow");
        }
        return static_cast<result_t>(result);
    }


    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator+=(RIGHT r)  &
    requires same_signedness<Odin,RIGHT>
    {
        static_assert(sizeof(Odin) >= sizeof(RIGHT),"odins: adding too large integer type");
        *this = static_cast<Odin>(*this+r);
        return *this;
    }

    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator-(Odin l, RIGHT r)
    requires same_signedness<Odin,RIGHT>
    {
        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        using ult = ULT<result_t>;

        ult result{};
        ult const left{static_cast<ult>(static_cast<ULT<Odin>>(l))};
        ult const right{static_cast<ult>(static_cast<ULT<RIGHT>>(r))};
        if (detail_::sub_overflow(left,right,&result)){
            ps_assert( false , "odins: subtraction overflow");
        }
        return static_cast<result_t>(result);
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator-=(RIGHT r) &
    requires same_signedness<Odin,RIGHT>
    {
        static_assert(sizeof(Odin) >= sizeof(RIGHT),"subtracting too large integer type");
        *this = static_cast<Odin>(*this-r);
        return *this;
    }


    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator*(Odin l, RIGHT r)
    requires same_signedness<Odin,RIGHT>
    {
        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        using ult = ULT<result_t>;
        ult result{};
        ult const left{static_cast<ult>(static_cast<ULT<Odin>>(l))};
        ult const right{static_cast<ult>(static_cast<ULT<RIGHT>>(r))};
        if (detail_::mul_overflow(left,right,&result)){
            ps_assert( false , "odins: multiplication overflow");
        }
        return static_cast<result_t>(result);
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator*=(RIGHT r) &
    requires same_signedness<Odin,RIGHT>
    {
        static_assert(sizeof(Odin) >= sizeof(RIGHT),"multiplying too large integer type");
        *this = static_cast<Odin>(*this*r);
        return *this;
    }
    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator/(Odin const l, RIGHT const r)
    requires same_signedness<Odin,RIGHT>
    {
        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        using ult = ULT<result_t>;
        ult const numerator{static_cast<ult>(static_cast<ULT<Odin>>(l))};
        ult const denominator{static_cast<ult>(static_cast<ULT<RIGHT>>(r))};
        ps_assert(  r != RIGHT{} , "odins: division by zero");
        if constexpr (std::numeric_limits<result_t>::is_signed){
            // detect -min / -1 which is overflow
            ps_assert(  numerator != std::numeric_limits<ult>::min() || r != -RIGHT{1} , "odins: signed division overflow");
        }
        return static_cast<result_t>(numerator/denominator);
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator/=(RIGHT r) &
    requires same_signedness<Odin,RIGHT>
    {
        static_assert(sizeof(Odin) >= sizeof(RIGHT),"dividing by too large integer type");
        *this = static_cast<Odin>(*this/r);
        return *this;
    }
    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator%(Odin l, RIGHT r)
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        using ult = ULT<result_t>;
        ps_assert(  r != RIGHT{}, "odins: modulo division by zero");
        return static_cast<result_t>(
                static_cast<ult>(
                        detail_::promote_and_extend_to_unsigned<ult>(l)
                        % // unsigned modulo cannot overflow
                        detail_::promote_and_extend_to_unsigned<ult>(r)
                )
        );
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator%=(RIGHT r) &
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        static_assert(sizeof(Odin) >= sizeof(RIGHT),"dividing by too large integer type");
        *this = static_cast<Odin>(*this % r);
        return *this;
    }
    // bitwise operators

    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator&(Odin l, RIGHT r) noexcept
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        using detail_::promote_keep_signedness;

        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        return static_cast<result_t>(promote_keep_signedness(l)&promote_keep_signedness(r));
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator&=(RIGHT r) & noexcept
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        static_assert(sizeof(Odin) == sizeof(RIGHT),"bitand by different sized integer type");
        *this = static_cast<Odin>(*this&r);
        return *this;
    }

    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator|(Odin l, RIGHT r) noexcept
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        using detail_::promote_keep_signedness;
        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        return static_cast<result_t>(promote_keep_signedness(l)|promote_keep_signedness(r));
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator|=(RIGHT r) & noexcept
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        static_assert(sizeof(Odin) == sizeof(RIGHT),"bitor by different sized integer type");
        *this = static_cast<Odin>(*this|r);
        return *this;
    }

    template<an_overflowdetectingint RIGHT>
    friend constexpr auto
    operator^(Odin l, RIGHT r) noexcept
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        using detail_::promote_keep_signedness;

        using result_t=std::conditional_t<sizeof(Odin)>=sizeof(RIGHT),Odin,RIGHT>;
        return static_cast<result_t>(promote_keep_signedness(l)^promote_keep_signedness(r));
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator^=(RIGHT r) & noexcept
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        static_assert(sizeof(Odin) == sizeof(RIGHT),"xor by different sized integer type");
        *this = static_cast<Odin>(*this^r);
        return *this;
    }


    constexpr Odin
    operator~() noexcept
    requires std::is_unsigned_v<ULT<Odin>>
    {
        return Odin(static_cast<INT>(~detail_::promote_keep_signedness(*this)));
    }


    template<an_overflowdetectingint RIGHT>
    friend constexpr Odin
    operator<<(Odin l, RIGHT r)
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        using detail_::promote_keep_signedness;
        ps_assert( static_cast<size_t>(promote_keep_signedness(r)) < sizeof(Odin)*CHAR_BIT , "odins: trying to left-shift by too many bits");
        return static_cast<Odin>(promote_keep_signedness(l)<<promote_keep_signedness(r));
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator<<=(RIGHT r) &
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        *this = (*this<<r);
        return *this;
    }
    template<an_overflowdetectingint RIGHT>
    friend constexpr Odin
    operator>>(Odin l, RIGHT r)
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {   using detail_::promote_keep_signedness;
        ps_assert( static_cast<size_t>(promote_keep_signedness(r)) < sizeof(Odin)*CHAR_BIT , "odins: trying to right-shift by too many bits");
        return static_cast<Odin>(promote_keep_signedness(l)>>promote_keep_signedness(r));
    }
    template<an_overflowdetectingint RIGHT>
    constexpr auto&
    operator>>=( RIGHT r) &
    requires std::is_unsigned_v<ULT<Odin>> && std::is_unsigned_v<ULT<RIGHT>>
    {
        *this = (*this >>r);
        return *this;
    }


    friend std::ostream& operator<<(std::ostream &out, Odin value){
        out << detail_::promote_keep_signedness(value);
        return out;
    }
    // no need for private, makes compilability checks possible
    // all possible values of INT are valid
    INT value_which_should_not_be_referred_to_from_user_code;
};
// unsigned

using cui8  = Odin<std::uint8_t >;
using cui16 = Odin<std::uint16_t>;
using cui32 = Odin<std::uint32_t>;
using cui64 = Odin<std::uint64_t>;

inline namespace literals {
consteval
cui8 operator""_cui8(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<std::uint8_t>::max()) {
        return cui8(static_cast<std::uint8_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
cui16 operator""_cui16(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<std::uint16_t>::max()) {
        return cui16(static_cast<std::uint16_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
cui32 operator""_cui32(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<uint32_t>::max()) {
        return cui32(static_cast<std::uint32_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
cui64 operator""_cui64(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if constexpr (sizeof(cui64) < sizeof(value_which_should_not_be_referred_to_from_user_code)){
        if (value_which_should_not_be_referred_to_from_user_code > 0xffff'ffff'fffffffful) {
            throw "integral constant too large"; // trigger compile-time error
        }
    }
    return cui64(static_cast<std::uint64_t>(value_which_should_not_be_referred_to_from_user_code));
}

}

// signed
using csi8  = Odin<std::int8_t >;
using csi16 = Odin<std::int16_t>;
using csi32 = Odin<std::int32_t>;
using csi64 = Odin<std::int64_t>;


inline namespace literals {
consteval
csi8 operator""_csi8(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<std::int8_t>::max()) {
        return csi8(static_cast<int8_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
csi16 operator""_csi16(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<int16_t>::max()) {
        return csi16(static_cast<int16_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
csi32 operator""_csi32(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<int32_t>::max()) {
        return csi32(static_cast<int32_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
csi64 operator""_csi64(unsigned long long value_which_should_not_be_referred_to_from_user_code) {
    if (value_which_should_not_be_referred_to_from_user_code <= std::numeric_limits<int64_t>::max()) {
        return csi64(static_cast<int64_t>(value_which_should_not_be_referred_to_from_user_code));
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}
} // NS literals

// the following are not really needed for class types,
// because of the availability of constructors, kept for symmetry

template<sized_integer T>
[[nodiscard]]
constexpr auto
from_int(T value_which_should_not_be_referred_to_from_user_code) noexcept {
    using detail_::is_compatible_integer_v;
    using std::conditional_t;
    struct cannot_convert_integer{};
    using result_t =
            conditional_t<is_compatible_integer_v<std::uint8_t,T>, cui8,
             conditional_t<is_compatible_integer_v<std::uint16_t,T>, cui16,
              conditional_t<is_compatible_integer_v<std::uint32_t,T>, cui32,
               conditional_t<is_compatible_integer_v<std::uint64_t,T>, cui64,
                conditional_t<is_compatible_integer_v<std::int8_t,T>, csi8,
                 conditional_t<is_compatible_integer_v<std::int16_t,T>, csi16,
                  conditional_t<is_compatible_integer_v<std::int32_t,T>, csi32,
                   conditional_t<is_compatible_integer_v<std::int64_t,T>, csi64, cannot_convert_integer>>>>>>>>;
    return static_cast<result_t>(value_which_should_not_be_referred_to_from_user_code); // no need to check, result_t corresponds to input T's range
}
// path tests are compile-time checked:
template<an_overflowdetectingint TO, sized_integer FROM>
[[nodiscard]]
constexpr auto
from_int_to(FROM val)
{
    using result_t = TO;
    using ultr = ULT<result_t>;
    if constexpr(std::is_unsigned_v<ultr>){
        ps_assert(  (val >= FROM{} && // in case FROM is signed
                     static_cast<std::make_unsigned_t<FROM>>(val) <= std::numeric_limits<ultr>::max()), "from_int_to: integer value out of range") ;
    } else {
        if constexpr (std::is_unsigned_v<FROM>){
            ps_assert(  val <= static_cast<std::make_unsigned_t<ultr>>(std::numeric_limits<ultr>::max()), "from_int_to: integer value out of range");

        } else { // both are signed
            ps_assert(  (val <= std::numeric_limits<ultr>::max() &&
                                val >= std::numeric_limits<ultr>::min()),  "from_int_to:  integer value out of range");
        }
    }
    return static_cast<result_t>(val); // cast is checked above
}

} // NS odins


// provide std::numeric_limits
namespace std {

template<odins::an_overflowdetectingint type>
  struct numeric_limits<type>
  {
    using ult = odins::ULT<type>;
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
    static constexpr bool is_modulo =  false; // saturation arithmetic never modulo

    static constexpr bool traps = false; // saturation arithmetic never traps
    static constexpr bool tinyness_before =  numeric_limits<ult>::tinyness_before;
    static constexpr float_round_style round_style =  numeric_limits<ult>::round_style;
  };

}





#endif /* SRC_ODINS_H_ */
