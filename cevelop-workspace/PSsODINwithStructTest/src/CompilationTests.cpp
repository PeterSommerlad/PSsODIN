#include "odins.h"

using namespace odins;
using namespace odins::literals;

namespace _testing {


template<typename FROM, typename=void>
constexpr bool
from_int_compiles=false;

template<typename FROM>
constexpr bool
from_int_compiles<FROM,std::void_t<decltype(odins::from_int(FROM{}))>> = true;

static_assert(from_int_compiles<unsigned char>);
static_assert(from_int_compiles<signed char>);
static_assert(from_int_compiles<short>);
static_assert(from_int_compiles<unsigned short>);
static_assert(from_int_compiles<int>);
static_assert(from_int_compiles<unsigned>);
static_assert(from_int_compiles<long>);
static_assert(from_int_compiles<unsigned long>);
static_assert(from_int_compiles<long long>);
static_assert(from_int_compiles<unsigned long long>);
static_assert(from_int_compiles<std::uint8_t>);
static_assert(from_int_compiles<std::uint16_t>);
static_assert(from_int_compiles<std::uint32_t>);
static_assert(from_int_compiles<std::uint64_t>);
static_assert(from_int_compiles<std::int8_t>);
static_assert(from_int_compiles<std::int16_t>);
static_assert(from_int_compiles<std::int32_t>);
static_assert(from_int_compiles<std::int64_t>);


static_assert(! from_int_compiles<bool>);
static_assert(! from_int_compiles<char>);
#ifdef __cpp_char8_t
static_assert(! from_int_compiles<char8_t>);
#endif
static_assert(! from_int_compiles<wchar_t>);
static_assert(! from_int_compiles<char16_t>);
static_assert(! from_int_compiles<char32_t>);

using namespace odins;
using odins::detail_::promote_keep_signedness;

static_assert(sizeof(long) == sizeof(long long)); // on my mac...
static_assert(42_csi64 == from_int(42L));
static_assert(42_csi64 == from_int(42LL));
static_assert(42_csi32 == from_int(42));
static_assert(42_cui64 == from_int(42uL));
static_assert(42_cui64 == from_int(42uLL));
static_assert(42_cui32 == from_int(42u));



static_assert(detail_::is_overflowdetectingint_v<cui8>);
static_assert(detail_::is_overflowdetectingint_v<cui16>);
static_assert(detail_::is_overflowdetectingint_v<cui32>);
static_assert(detail_::is_overflowdetectingint_v<cui64>);
static_assert(detail_::is_overflowdetectingint_v<csi8>);
static_assert(detail_::is_overflowdetectingint_v<csi16>);
static_assert(detail_::is_overflowdetectingint_v<csi32>);
static_assert(detail_::is_overflowdetectingint_v<csi64>);
enum class enum4test{};
static_assert(!detail_::is_overflowdetectingint_v<enum4test>);
static_assert(!detail_::is_overflowdetectingint_v<std::byte>);
static_assert(!detail_::is_overflowdetectingint_v<int>);
static_assert(std::is_same_v<unsigned,decltype(promote_keep_signedness(1_cui8)+1)>);
static_assert(std::is_same_v<unsigned,decltype(promote_keep_signedness(2_cui16)+1)>);
static_assert(std::is_same_v<int,decltype(promote_keep_signedness(1_csi8))>);
static_assert(std::is_same_v<int,decltype(promote_keep_signedness(2_csi16))>);
static_assert(std::is_same_v<uint8_t,ULT<cui8>>);
static_assert(std::is_same_v<uint16_t,ULT<cui16>>);


//static_assert(promote_keep_signedness(0xffff_cui16 * 0xffff_cui16) == 0x1u); // wraps
//static_assert(0xff_cui8 * 0xff_cui8 == 1_cui8);

// the following does not compile due to signed integer overflow on 32bit int
//static_assert(static_cast<uint16_t>(0xffffu)* static_cast<uint16_t>(0xffffu));

//static_assert(0x7fff'ffff_csi32+2_csi32 == -0x7fff'ffff_csi32);
//static_assert(0x7fff'ffff + 2); // doesn't compile, integer overflow
//static_assert(-0x7fff'ffff_csi32 - 2_csi32 == 0x7fff'ffff_csi32);
//static_assert(-0x7fff'ffff - 2); // doesn't compile, integer overflow

//static_assert(std::is_same_v<int,decltype(+to_underlying(42_cui8))>);
//static_assert(std::is_same_v<uint8_t,decltype(to_underlying(42_cui8))>);

static_assert(1_cui8 == from_int(uint8_t(1)));
static_assert(42_csi8 == from_int_to<csi8>(42));
//static_assert(32_cui8 == from_int(' ')); // does not compile
//static_assert(32_cui8 == from_int(u' ')); // does not compile
//static_assert(32_cui8 == from_int(U' ')); // does not compile
//static_assert(32_cui8 == from_int(L' ')); // does not compile
//static_assert(1_cui8 == from_int_to<ui8>(true)); // does not compile

// Test case from Frank Buergel (extended):
// missing sign extension from 32 to 64bit
// discovered further bugs wrt signed division
namespace {
constexpr auto v1_64 {  1_csi64 };
constexpr auto v1_32 {  1_csi32 };
constexpr auto v1_16 {  1_csi16 };
constexpr auto v1_8  {  1_csi8 };
constexpr auto v2_64 {  2_csi64 };
constexpr auto v2_32 {  2_csi32 };
constexpr auto v2_16 {  2_csi16 };
constexpr auto v2_8  {  2_csi8 };
constexpr auto vminus1_64 { -1_csi64 };
constexpr auto vminus1_32 { -1_csi32 };
constexpr auto vminus1_16 { -1_csi16 };
constexpr auto vminus1_8  { -1_csi8 };

constexpr auto min_8  { std::numeric_limits<csi8 >::min() };
constexpr auto min_16 { std::numeric_limits<csi16>::min() };
constexpr auto min_32 { std::numeric_limits<csi32>::min() };
constexpr auto min_64 { std::numeric_limits<csi64>::min() };
constexpr auto max_8  { std::numeric_limits<csi8 >::max() };
constexpr auto max_16 { std::numeric_limits<csi16>::max() };
constexpr auto max_32 { std::numeric_limits<csi32>::max() };
constexpr auto max_64 { std::numeric_limits<csi64>::max() };


constexpr auto maxu_8  { std::numeric_limits<cui8 >::max() };
constexpr auto maxu_16 { std::numeric_limits<cui16>::max() };
constexpr auto maxu_32 { std::numeric_limits<cui32>::max() };
constexpr auto maxu_64 { std::numeric_limits<cui64>::max() };
constexpr auto v1u_64 {  1_cui64 };
constexpr auto v1u_32 {  1_cui32 };
constexpr auto v1u_16 {  1_cui16 };
constexpr auto v1u_8  {  1_cui8 };
constexpr auto v2u_64 {  2_cui64 };
constexpr auto v2u_32 {  2_cui32 };
constexpr auto v2u_16 {  2_cui16 };
constexpr auto v2u_8  {  2_cui8 };

}

static_assert(v1_64 + vminus1_64 == 0_csi64 );
static_assert(v1_64 + vminus1_32 == 0_csi64 );
static_assert(v1_64 + vminus1_16 == 0_csi64 );
static_assert(v1_64 + vminus1_8  == 0_csi64 );
static_assert(v1_32 + vminus1_64 == 0_csi64 );
static_assert(v1_32 + vminus1_32 == 0_csi32 );
static_assert(v1_32 + vminus1_16 == 0_csi32 );
static_assert(v1_32 + vminus1_8  == 0_csi32 );
static_assert(v1_16 + vminus1_64 == 0_csi64 );
static_assert(v1_16 + vminus1_32 == 0_csi32 );
static_assert(v1_16 + vminus1_16 == 0_csi16 );
static_assert(v1_16 + vminus1_8  == 0_csi16 );
static_assert(v1_8  + vminus1_64 == 0_csi64 );
static_assert(v1_8  + vminus1_32 == 0_csi32 );
static_assert(v1_8  + vminus1_16 == 0_csi16 );
static_assert(v1_8  + vminus1_8  == 0_csi8 );

static_assert(vminus1_64 +  v1_64== 0_csi64 );
static_assert(vminus1_32 +  v1_64== 0_csi64 );
static_assert(vminus1_16 +  v1_64== 0_csi64 );
static_assert(vminus1_8  +  v1_64== 0_csi64 );
static_assert(vminus1_64 +  v1_32== 0_csi64 );
static_assert(vminus1_32 +  v1_32== 0_csi32 );
static_assert(vminus1_16 +  v1_32== 0_csi32 );
static_assert(vminus1_8  +  v1_32== 0_csi32 );
static_assert(vminus1_64 +  v1_16== 0_csi64 );
static_assert(vminus1_32 +  v1_16== 0_csi32 );
static_assert(vminus1_16 +  v1_16== 0_csi16 );
static_assert(vminus1_8  +  v1_16== 0_csi16 );
static_assert(vminus1_64 +  v1_8 == 0_csi64 );
static_assert(vminus1_32 +  v1_8 == 0_csi32 );
static_assert(vminus1_16 +  v1_8 == 0_csi16 );
static_assert(vminus1_8  +  v1_8 == 0_csi8 );


// demonstrate wrapping:
//static_assert(max_64 + v1_64 == min_64 );
//static_assert(max_64 + v1_32 == min_64 );
//static_assert(max_64 + v1_16 == min_64 );
//static_assert(max_64 + v1_8  == min_64 );
static_assert(max_32 + v1_64 == 0x8000'0000_csi64 );
//static_assert(max_32 + v1_32 == min_32 );
//static_assert(max_32 + v1_16 == min_32 );
//static_assert(max_32 + v1_8  == min_32 );
static_assert(max_16 + v1_64 == 0x8000_csi64 );
static_assert(max_16 + v1_32 == 0x8000_csi32 );
//static_assert(max_16 + v1_16 == min_16 );
//static_assert(max_16 + v1_8  == min_16 );
static_assert(max_8  + v1_64 == 128_csi64 );
static_assert(max_8  + v1_32 == 128_csi32 );
static_assert(max_8  + v1_16 == 128_csi16 );
//static_assert(max_8  + v1_8  == min_8 );


static_assert(v1_64 - vminus1_64 == 2_csi64 );
static_assert(v1_64 - vminus1_32 == 2_csi64 );
static_assert(v1_64 - vminus1_16 == 2_csi64 );
static_assert(v1_64 - vminus1_8  == 2_csi64 );
static_assert(v1_32 - vminus1_64 == 2_csi64 );
static_assert(v1_32 - vminus1_32 == 2_csi32 );
static_assert(v1_32 - vminus1_16 == 2_csi32 );
static_assert(v1_32 - vminus1_8  == 2_csi32 );
static_assert(v1_16 - vminus1_64 == 2_csi64 );
static_assert(v1_16 - vminus1_32 == 2_csi32 );
static_assert(v1_16 - vminus1_16 == 2_csi16 );
static_assert(v1_16 - vminus1_8  == 2_csi16 );
static_assert(v1_8  - vminus1_64 == 2_csi64 );
static_assert(v1_8  - vminus1_32 == 2_csi32 );
static_assert(v1_8  - vminus1_16 == 2_csi16 );
static_assert(v1_8  - vminus1_8  == 2_csi8 );


static_assert(vminus1_64 - v1_64  == -2_csi64 );
static_assert(vminus1_32 - v1_64  == -2_csi64 );
static_assert(vminus1_16 - v1_64  == -2_csi64 );
static_assert(vminus1_8  - v1_64  == -2_csi64 );
static_assert(vminus1_64 - v1_32  == -2_csi64 );
static_assert(vminus1_32 - v1_32  == -2_csi32 );
static_assert(vminus1_16 - v1_32  == -2_csi32 );
static_assert(vminus1_8  - v1_32  == -2_csi32 );
static_assert(vminus1_64 - v1_16  == -2_csi64 );
static_assert(vminus1_32 - v1_16  == -2_csi32 );
static_assert(vminus1_16 - v1_16  == -2_csi16 );
static_assert(vminus1_8  - v1_16  == -2_csi16 );
static_assert(vminus1_64 - v1_8   == -2_csi64 );
static_assert(vminus1_32 - v1_8   == -2_csi32 );
static_assert(vminus1_16 - v1_8   == -2_csi16 );
static_assert(vminus1_8  - v1_8   == -2_csi8 );

static_assert(v1_64 * vminus1_64 == -1_csi64 );
static_assert(v1_64 * vminus1_32 == -1_csi64 );
static_assert(v1_64 * vminus1_16 == -1_csi64 );
static_assert(v1_64 * vminus1_8  == -1_csi64 );
static_assert(v1_32 * vminus1_64 == -1_csi64 );
static_assert(v1_32 * vminus1_32 == -1_csi32 );
static_assert(v1_32 * vminus1_16 == -1_csi32 );
static_assert(v1_32 * vminus1_8  == -1_csi32 );
static_assert(v1_16 * vminus1_64 == -1_csi64 );
static_assert(v1_16 * vminus1_32 == -1_csi32 );
static_assert(v1_16 * vminus1_16 == -1_csi16 );
static_assert(v1_16 * vminus1_8  == -1_csi16 );
static_assert(v1_8  * vminus1_64 == -1_csi64 );
static_assert(v1_8  * vminus1_32 == -1_csi32 );
static_assert(v1_8  * vminus1_16 == -1_csi16 );
static_assert(v1_8  * vminus1_8  == -1_csi8 );

static_assert(vminus1_64 *  v1_64== -1_csi64 );
static_assert(vminus1_32 *  v1_64== -1_csi64 );
static_assert(vminus1_16 *  v1_64== -1_csi64 );
static_assert(vminus1_8  *  v1_64== -1_csi64 );
static_assert(vminus1_64 *  v1_32== -1_csi64 );
static_assert(vminus1_32 *  v1_32== -1_csi32 );
static_assert(vminus1_16 *  v1_32== -1_csi32 );
static_assert(vminus1_8  *  v1_32== -1_csi32 );
static_assert(vminus1_64 *  v1_16== -1_csi64 );
static_assert(vminus1_32 *  v1_16== -1_csi32 );
static_assert(vminus1_16 *  v1_16== -1_csi16 );
static_assert(vminus1_8  *  v1_16== -1_csi16 );
static_assert(vminus1_64 *  v1_8 == -1_csi64 );
static_assert(vminus1_32 *  v1_8 == -1_csi32 );
static_assert(vminus1_16 *  v1_8 == -1_csi16 );
static_assert(vminus1_8  *  v1_8 == -1_csi8 );

static_assert(vminus1_64 *  v2_64== -2_csi64 );
static_assert(vminus1_32 *  v2_64== -2_csi64 );
static_assert(vminus1_16 *  v2_64== -2_csi64 );
static_assert(vminus1_8  *  v2_64== -2_csi64 );
static_assert(vminus1_64 *  v2_32== -2_csi64 );
static_assert(vminus1_32 *  v2_32== -2_csi32 );
static_assert(vminus1_16 *  v2_32== -2_csi32 );
static_assert(vminus1_8  *  v2_32== -2_csi32 );
static_assert(vminus1_64 *  v2_16== -2_csi64 );
static_assert(vminus1_32 *  v2_16== -2_csi32 );
static_assert(vminus1_16 *  v2_16== -2_csi16 );
static_assert(vminus1_8  *  v2_16== -2_csi16 );
static_assert(vminus1_64 *  v2_8 == -2_csi64 );
static_assert(vminus1_32 *  v2_8 == -2_csi32 );
static_assert(vminus1_16 *  v2_8 == -2_csi16 );
static_assert(vminus1_8  *  v2_8 == -2_csi8 );

static_assert(vminus1_64 * -v2_64==  2_csi64 );
static_assert(vminus1_32 * -v2_64==  2_csi64 );
static_assert(vminus1_16 * -v2_64==  2_csi64 );
static_assert(vminus1_8  * -v2_64==  2_csi64 );
static_assert(vminus1_64 * -v2_32==  2_csi64 );
static_assert(vminus1_32 * -v2_32==  2_csi32 );
static_assert(vminus1_16 * -v2_32==  2_csi32 );
static_assert(vminus1_8  * -v2_32==  2_csi32 );
static_assert(vminus1_64 * -v2_16==  2_csi64 );
static_assert(vminus1_32 * -v2_16==  2_csi32 );
static_assert(vminus1_16 * -v2_16==  2_csi16 );
static_assert(vminus1_8  * -v2_16==  2_csi16 );
static_assert(vminus1_64 * -v2_8 ==  2_csi64 );
static_assert(vminus1_32 * -v2_8 ==  2_csi32 );
static_assert(vminus1_16 * -v2_8 ==  2_csi16 );
static_assert(vminus1_8  * -v2_8 ==  2_csi8 );

static_assert(v2_64 * -v2_64== -4_csi64 );
static_assert(v2_32 * -v2_64== -4_csi64 );
static_assert(v2_16 * -v2_64== -4_csi64 );
static_assert(v2_8  * -v2_64== -4_csi64 );
static_assert(v2_64 * -v2_32== -4_csi64 );
static_assert(v2_32 * -v2_32== -4_csi32 );
static_assert(v2_16 * -v2_32== -4_csi32 );
static_assert(v2_8  * -v2_32== -4_csi32 );
static_assert(v2_64 * -v2_16== -4_csi64 );
static_assert(v2_32 * -v2_16== -4_csi32 );
static_assert(v2_16 * -v2_16== -4_csi16 );
static_assert(v2_8  * -v2_16== -4_csi16 );
static_assert(v2_64 * -v2_8 == -4_csi64 );
static_assert(v2_32 * -v2_8 == -4_csi32 );
static_assert(v2_16 * -v2_8 == -4_csi16 );
static_assert(v2_8  * -v2_8 == -4_csi8 );

static_assert(-v2_64 * -v2_64== 4_csi64 );
static_assert(-v2_32 * -v2_64== 4_csi64 );
static_assert(-v2_16 * -v2_64== 4_csi64 );
static_assert(-v2_8  * -v2_64== 4_csi64 );
static_assert(-v2_64 * -v2_32== 4_csi64 );
static_assert(-v2_32 * -v2_32== 4_csi32 );
static_assert(-v2_16 * -v2_32== 4_csi32 );
static_assert(-v2_8  * -v2_32== 4_csi32 );
static_assert(-v2_64 * -v2_16== 4_csi64 );
static_assert(-v2_32 * -v2_16== 4_csi32 );
static_assert(-v2_16 * -v2_16== 4_csi16 );
static_assert(-v2_8  * -v2_16== 4_csi16 );
static_assert(-v2_64 * -v2_8 == 4_csi64 );
static_assert(-v2_32 * -v2_8 == 4_csi32 );
static_assert(-v2_16 * -v2_8 == 4_csi16 );
static_assert(-v2_8  * -v2_8 == 4_csi8 );

// demonstrate no wrapping: (see below)
//static_assert(min_64 * v2_64 == 0_csi64 );
//static_assert(min_64 * v2_32 == 0_csi64  );
//static_assert(min_64 * v2_16 == 0_csi64  );
//static_assert(min_64 * v2_8  == 0_csi64 );
static_assert(min_32 * v2_64 == -0x1'0000'0000_csi64 );
//static_assert(min_32 * v2_32 == 0_csi32 );
//static_assert(min_32 * v2_16 == 0_csi32 );
//static_assert(min_32 * v2_8  == 0_csi32 );
static_assert(min_16 * v2_64 == -0x1'0000_csi64  );
static_assert(min_16 * v2_32 == -0x1'0000_csi32 );
//static_assert(min_16 * v2_16 == 0_csi16 );
//static_assert(min_16 * v2_8  == 0_csi16 );
static_assert(min_8  * v2_64 == -256_csi64 );
static_assert(min_8  * v2_32 == -256_csi32 );
static_assert(min_8  * v2_16 == -256_csi16 );
//static_assert(min_8  * v2_8  == 0_csi8 );


static_assert(v1_64 / vminus1_64 == -1_csi64 );
static_assert(v1_64 / vminus1_32 == -1_csi64 );
static_assert(v1_64 / vminus1_16 == -1_csi64 );
static_assert(v1_64 / vminus1_8  == -1_csi64 );
static_assert(v1_32 / vminus1_64 == -1_csi64 );
static_assert(v1_32 / vminus1_32 == -1_csi32 );
static_assert(v1_32 / vminus1_16 == -1_csi32 );
static_assert(v1_32 / vminus1_8  == -1_csi32 );
static_assert(v1_16 / vminus1_64 == -1_csi64 );
static_assert(v1_16 / vminus1_32 == -1_csi32 );
static_assert(v1_16 / vminus1_16 == -1_csi16 );
static_assert(v1_16 / vminus1_8  == -1_csi16 );
static_assert(v1_8  / vminus1_64 == -1_csi64 );
static_assert(v1_8  / vminus1_32 == -1_csi32 );
static_assert(v1_8  / vminus1_16 == -1_csi16 );
static_assert(v1_8  / vminus1_8  == -1_csi8 );

static_assert(vminus1_64 /  v1_64== -1_csi64 );
static_assert(vminus1_32 /  v1_64== -1_csi64 );
static_assert(vminus1_16 /  v1_64== -1_csi64 );
static_assert(vminus1_8  /  v1_64== -1_csi64 );
static_assert(vminus1_64 /  v1_32== -1_csi64 );
static_assert(vminus1_32 /  v1_32== -1_csi32 );
static_assert(vminus1_16 /  v1_32== -1_csi32 );
static_assert(vminus1_8  /  v1_32== -1_csi32 );
static_assert(vminus1_64 /  v1_16== -1_csi64 );
static_assert(vminus1_32 /  v1_16== -1_csi32 );
static_assert(vminus1_16 /  v1_16== -1_csi16 );
static_assert(vminus1_8  /  v1_16== -1_csi16 );
static_assert(vminus1_64 /  v1_8 == -1_csi64 );
static_assert(vminus1_32 /  v1_8 == -1_csi32 );
static_assert(vminus1_16 /  v1_8 == -1_csi16 );
static_assert(vminus1_8  /  v1_8 == -1_csi8 );


static_assert(v2_64 / vminus1_64 == -2_csi64 );
static_assert(v2_64 / vminus1_32 == -2_csi64 );
static_assert(v2_64 / vminus1_16 == -2_csi64 );
static_assert(v2_64 / vminus1_8  == -2_csi64 );
static_assert(v2_32 / vminus1_64 == -2_csi64 );
static_assert(v2_32 / vminus1_32 == -2_csi32 );
static_assert(v2_32 / vminus1_16 == -2_csi32 );
static_assert(v2_32 / vminus1_8  == -2_csi32 );
static_assert(v2_16 / vminus1_64 == -2_csi64 );
static_assert(v2_16 / vminus1_32 == -2_csi32 );
static_assert(v2_16 / vminus1_16 == -2_csi16 );
static_assert(v2_16 / vminus1_8  == -2_csi16 );
static_assert(v2_8  / vminus1_64 == -2_csi64 );
static_assert(v2_8  / vminus1_32 == -2_csi32 );
static_assert(v2_8  / vminus1_16 == -2_csi16 );
static_assert(v2_8  / vminus1_8  == -2_csi8 );

static_assert(vminus1_64 /  v2_64== 0_csi64 );
static_assert(vminus1_32 /  v2_64== 0_csi64 );
static_assert(vminus1_16 /  v2_64== 0_csi64 );
static_assert(vminus1_8  /  v2_64== 0_csi64 );
static_assert(vminus1_64 /  v2_32== 0_csi64 );
static_assert(vminus1_32 /  v2_32== 0_csi32 );
static_assert(vminus1_16 /  v2_32== 0_csi32 );
static_assert(vminus1_8  /  v2_32== 0_csi32 );
static_assert(vminus1_64 /  v2_16== 0_csi64 );
static_assert(vminus1_32 /  v2_16== 0_csi32 );
static_assert(vminus1_16 /  v2_16== 0_csi16 );
static_assert(vminus1_8  /  v2_16== 0_csi16 );
static_assert(vminus1_64 /  v2_8 == 0_csi64 );
static_assert(vminus1_32 /  v2_8 == 0_csi32 );
static_assert(vminus1_16 /  v2_8 == 0_csi16 );
static_assert(vminus1_8  /  v2_8 == 0_csi8 );

static_assert(min_64 /  min_64 ==  1_csi64 );
static_assert(min_32 /  min_64 ==  0_csi64 );
static_assert(min_16 /  min_64 ==  0_csi64 );
static_assert(min_8  /  min_64 ==  0_csi64 );
static_assert(min_64 /  min_32 ==  0x1'0000'0000_csi64 );
static_assert(min_32 /  min_32 ==  1_csi32 );
static_assert(min_16 /  min_32 ==  0_csi32 );
static_assert(min_8  /  min_32 ==  0_csi32 );
static_assert(min_64 /  min_16 ==  0x1'0000'0000'0000_csi64 );
static_assert(min_32 /  min_16 ==  0x1'0000_csi32 );
static_assert(min_16 /  min_16 ==  1_csi16 );
static_assert(min_8  /  min_16 ==  0_csi16 );
static_assert(min_64 /  min_8  ==  0x100'0000'0000'0000_csi64 );
static_assert(min_32 /  min_8  ==  0x100'0000_csi32 );
static_assert(min_16 /  min_8  ==  256_csi16 );
static_assert(min_8  /  min_8  ==  1_csi8 );

// demonstrate wrapping: (see below with overflow detection)
//static_assert(min_64 / vminus1_64 == min_64 );
//static_assert(min_64 / vminus1_32 == min_64 );
//static_assert(min_64 / vminus1_16 == min_64 );
//static_assert(min_64 / vminus1_8  == min_64 );
//static_assert(min_32 / vminus1_64 == 0x8000'0000_csi64 );
//static_assert(min_32 / vminus1_32 == min_32 );
//static_assert(min_32 / vminus1_16 == min_32 );
//static_assert(min_32 / vminus1_8  == min_32 );
//static_assert(min_16 / vminus1_64 == -static_cast<si64>(min_16)  );
//static_assert(min_16 / vminus1_32 == 0x8000_csi32 );
//static_assert(min_16 / vminus1_16 == min_16 );
//static_assert(min_16 / vminus1_8  == min_16 );
//static_assert(min_8  / vminus1_64 == 128_csi64 );
//static_assert(min_8  / vminus1_32 == 128_csi32 );
//static_assert(min_8  / vminus1_16 == 128_csi16 );
//static_assert(min_8  / vminus1_8  == min_8 );

static_assert(min_64 / v1_64 == min_64 );
static_assert(min_64 / v1_32 == min_64 );
static_assert(min_64 / v1_16 == min_64 );
static_assert(min_64 / v1_8  == min_64 );
static_assert(min_32 / v1_64 == -0x8000'0000_csi64 );
static_assert(min_32 / v1_32 == min_32 );
static_assert(min_32 / v1_16 == min_32 );
static_assert(min_32 / v1_8  == min_32 );
static_assert(min_16 / v1_64 == -0x8000_csi64  );
static_assert(min_16 / v1_32 == -0x8000_csi32 );
static_assert(min_16 / v1_16 == min_16 );
static_assert(min_16 / v1_8  == min_16 );
static_assert(min_8  / v1_64 == -128_csi64 );
static_assert(min_8  / v1_32 == -128_csi32 );
static_assert(min_8  / v1_16 == -128_csi16 );
static_assert(min_8  / v1_8  == min_8 );

static_assert(min_64 / v2_64 == -0x4000'0000'0000'0000_csi64 );
static_assert(min_64 / v2_32 == -0x4000'0000'0000'0000_csi64  );
static_assert(min_64 / v2_16 == -0x4000'0000'0000'0000_csi64  );
static_assert(min_64 / v2_8  == -0x4000'0000'0000'0000_csi64 );
static_assert(min_32 / v2_64 == -0x4000'0000_csi64 );
static_assert(min_32 / v2_32 == -0x4000'0000_csi32 );
static_assert(min_32 / v2_16 == -0x4000'0000_csi32 );
static_assert(min_32 / v2_8  == -0x4000'0000_csi32 );
static_assert(min_16 / v2_64 == -0x4000_csi64  );
static_assert(min_16 / v2_32 == -0x4000_csi32 );
static_assert(min_16 / v2_16 == -0x4000_csi16 );
static_assert(min_16 / v2_8  == -0x4000_csi16 );
static_assert(min_8  / v2_64 == -64_csi64 );
static_assert(min_8  / v2_32 == -64_csi32 );
static_assert(min_8  / v2_16 == -64_csi16 );
static_assert(min_8  / v2_8  == -64_csi8 );


static_assert(-100_csi32 / -9_csi64 == 11_csi64);
static_assert(100_csi32 / 9_csi64 == 11_csi64);
static_assert(-100_csi32 / 9_csi64 == -11_csi64);
static_assert(100_csi32 / -9_csi64 == -11_csi64);

//static_assert(std::numeric_limits<si32>::min() / 1_csi32 == std::numeric_limits<si32>::min()); // wraps
//static_assert(std::numeric_limits<si32>::min() / -1_csi32 == std::numeric_limits<si32>::min()); // wraps


namespace compile_checks {
using namespace odins;
template<auto ...value>
using consume_value = void;



#define concat_line_impl(A, B) A##_##B
#define concat_line(A, B) concat_line_impl(A,B)

#define check_does_compile(NOT, FROM, oper) \
namespace concat_line(NOT##_test, __LINE__) { \
        template<typename T, typename=void>\
        constexpr bool\
        expression_compiles{false};\
template<typename T> \
constexpr bool \
expression_compiles<T, consume_value<(T{} oper T{})> > {true};\
static_assert(NOT expression_compiles<FROM>, "should " #NOT " compile: " #FROM "{}" #oper #FROM "{}");\
} // namespace tag


// need to be on separate lines for disambiguation
check_does_compile(not,  csi8 , <<  )
check_does_compile(   ,  cui8 , << )
check_does_compile(not,  csi8 , >>  )
check_does_compile(   ,  cui8 , >> )
check_does_compile(not,  cui8 , + (1_cui8 << 010_cui8) + ) // too wide shift
check_does_compile(   ,  cui8 , + (1_cui8 << 7_cui8) + ) // not too wide shift
check_does_compile(not,  cui8 , + (0x80_cui8 >> 010_cui8) + ) // too wide shift
check_does_compile(   ,  cui8 , + (0x80_cui8 >> 7_cui8) + ) // not too wide shift
check_does_compile(not,  cui8 ,  % ) // modulo 0
check_does_compile(not,  csi8 ,  / ) // div 0
check_does_compile(not,  csi8 ,  % ) // modulo not working
check_does_compile(not,  cui8 ,  / ) // div 0
check_does_compile(   ,  cui8 , +( 1_cui8  / 1_cui8)+ ) // div
check_does_compile(   ,  cui8 , +( 11_cui8  % 3_cui8)+ ) // mod
check_does_compile(not,  cui8 , + 1_csi8 + ) // mixed
check_does_compile(not,  cui8 , + 255_cui8 + 1_cui8 + ) // overflow detect
check_does_compile(not,  cui8 , + 128_cui8 * 128_cui8 +) // overflow detect
check_does_compile(not,  csi8 , + 64_csi8 * 2_csi8 +) // overflow detect
check_does_compile(not,  csi8 , + (-127_csi8 - 1_csi8) * -1_csi8 +) // overflow detect
check_does_compile(   ,  csi8 , + (-127_csi8 - 1_csi8) * 1_csi8 +) // no overflow
check_does_compile(not,  csi8 , + (-127_csi8 - 1_csi8) / -1_csi8 +) // overflow detect
check_does_compile(   ,  csi8 , + (-127_csi8 - 1_csi8) / 1_csi8 +) // no overflow

// demonstrate overflow detection:
check_does_compile(not,  csi64 , + max_64 + v1_64 +) //  overflow detect
check_does_compile(not,  csi64 , + max_64 + v1_32 +) //  overflow detect
check_does_compile(not,  csi64 , + max_64 + v1_16 +) //  overflow detect
check_does_compile(not,  csi64 , + max_64 + v1_8 +) //  overflow detect
static_assert(max_32 + v1_64 == 0x8000'0000_csi64 );
check_does_compile(not,  csi32 , + max_32 + v1_32 +) //  overflow detect
check_does_compile(not,  csi32 , + max_32 + v1_16 +) //  overflow detect
check_does_compile(not,  csi32 , + max_32 + v1_8 +) //  overflow detect
static_assert(max_16 + v1_64 == 0x8000_csi64 );
static_assert(max_16 + v1_32 == 0x8000_csi32 );
check_does_compile(not,  csi16 , + max_16 + v1_16 +) //  overflow detect
check_does_compile(not,  csi16 , + max_16 + v1_8 +) //  overflow detect
static_assert(max_8  + v1_64 == 128_csi64 );
static_assert(max_8  + v1_32 == 128_csi32 );
static_assert(max_8  + v1_16 == 128_csi16 );
check_does_compile(not,  csi8 , + max_8 + v1_8 +) //  overflow detect

// unsigned addition overflow detection:
check_does_compile(not,  cui64 , + maxu_64 + v1u_64 +) //  overflow detect
check_does_compile(not,  cui64 , + maxu_64 + v1u_32 +) //  overflow detect
check_does_compile(not,  cui64 , + maxu_64 + v1u_16 +) //  overflow detect
check_does_compile(not,  cui64 , + maxu_64 + v1u_8 +) //  overflow detect
static_assert(maxu_32 + v1u_64 == 0x1'0000'0000_cui64 );
check_does_compile(not,  cui32 , + maxu_32 + v1u_32 +) //  overflow detect
check_does_compile(not,  cui32 , + maxu_32 + v1u_16 +) //  overflow detect
check_does_compile(not,  cui32 , + maxu_32 + v1u_8 +) //  overflow detect
static_assert(maxu_16 + v1u_64 == 0x1'0000_cui64 );
static_assert(maxu_16 + v1u_32 == 0x1'0000_cui32 );
check_does_compile(not,  cui16 , + maxu_16 + v1u_16 +) //  overflow detect
check_does_compile(not,  cui16 , + maxu_16 + v1u_8 +) //  overflow detect
static_assert(maxu_8  + v1u_64 == 256_cui64 );
static_assert(maxu_8  + v1u_32 == 256_cui32 );
static_assert(maxu_8  + v1u_16 == 256_cui16 );
check_does_compile(not,  cui8 , + maxu_8 + v1u_8 +) //  overflow detect

// unsigned subtraction underflow detection:
check_does_compile(not,  cui64 , + 0_cui64 - v1u_64 +) //  overflow detect
check_does_compile(not,  cui64 , + 0_cui64  - v1u_32 +) //  overflow detect
check_does_compile(not,  cui64 , + 0_cui64  - v1u_16 +) //  overflow detect
check_does_compile(not,  cui64 , + 0_cui64  - v1u_8 +) //  overflow detect
check_does_compile(not,  cui32 , + 0_cui32 - v1u_64 +) //  overflow detect
check_does_compile(not,  cui32 , + 0_cui32 - v1u_32 +) //  overflow detect
check_does_compile(not,  cui32 , + 0_cui32 - v1u_16 +) //  overflow detect
check_does_compile(not,  cui32 , + 0_cui32 - v1u_8 +) //  overflow detect
check_does_compile(not,  cui16 , + 0_cui16 - v1u_16 +) //  overflow detect
check_does_compile(not,  cui16 , + 0_cui16 - v1u_16 +) //  overflow detect
check_does_compile(not,  cui16 , + 0_cui16 - v1u_16 +) //  overflow detect
check_does_compile(not,  cui16 , + 0_cui16 - v1u_8 +) //  overflow detect
check_does_compile(not,  cui8 , + 0_cui8 - v1u_64 +) //  overflow detect
check_does_compile(not,  cui8 , + 0_cui8 - v1u_32 +) //  overflow detect
check_does_compile(not,  cui8 , + 0_cui8 - v1u_16 +) //  overflow detect
check_does_compile(not,  cui8 , + 0_cui8 - v1u_8  +) //  overflow detect


// demonstrate overflow detection:
check_does_compile(not,  csi64 , + min_64 / vminus1_64 +) // overflow detect
check_does_compile(not,  csi64 , + min_64 / vminus1_32 +) // overflow detect
check_does_compile(not,  csi64 , + min_64 / vminus1_16 +) // overflow detect
check_does_compile(not,  csi64 , + min_64 / vminus1_8 +) // overflow detect
check_does_compile(   ,  csi64 , + min_32 / vminus1_64 +) // overflow detect
static_assert(min_32 / vminus1_64 == 0x8000'0000_csi64 );
check_does_compile(not,  csi32 , + min_32 / vminus1_32 +) // overflow detect
check_does_compile(not,  csi32 , + min_32 / vminus1_16 +) // overflow detect
check_does_compile(not,  csi32 , + min_32 / vminus1_8 +) // overflow detect
static_assert(min_16 / vminus1_64 == -static_cast<csi64>(static_cast<ULT<decltype(min_16)>>(min_16))  );
static_assert(min_16 / vminus1_32 == 0x8000_csi32 );
check_does_compile(not,  csi16 , + min_16 / vminus1_16 +) // overflow detect
check_does_compile(not,  csi16 , + min_16 / vminus1_8 +) // overflow detect
static_assert(min_8  / vminus1_64 == 128_csi64 );
static_assert(min_8  / vminus1_32 == 128_csi32 );
static_assert(min_8  / vminus1_16 == 128_csi16 );
check_does_compile(not,  csi8 , + min_8 / vminus1_8 +) // overflow detect

// demonstrate modulo overflow detection:%
// not needed, only supported for unsigned operands


// demonstrate multiplication overflow detection:
check_does_compile(not,  csi64 , + min_64 * v2_64 +) // overflow detect
check_does_compile(not,  csi64 , + min_64 * v2_32 +) // overflow detect
check_does_compile(not,  csi64 , + min_64 * v2_16 +) // overflow detect
check_does_compile(not,  csi64 , + min_64 * v2_8 +) // overflow detect
static_assert(min_32 * v2_64 == -0x1'0000'0000_csi64 );
check_does_compile(not,  csi32 , + min_32 * v2_32 +) // overflow detect
check_does_compile(not,  csi32 , + min_32 * v2_16 +) // overflow detect
check_does_compile(not,  csi32 , + min_32 * v2_8 +) // overflow detect
static_assert(min_16 * v2_64 == -0x1'0000_csi64  );
static_assert(min_16 * v2_32 == -0x1'0000_csi32 );
check_does_compile(not,  csi16 , + min_16 * v2_16 +) // overflow detect
check_does_compile(not,  csi16 , + min_16 * v2_8 +) // overflow detect
static_assert(min_8  * v2_64 == -256_csi64 );
static_assert(min_8  * v2_32 == -256_csi32 );
static_assert(min_8  * v2_16 == -256_csi16 );
check_does_compile(not,  csi8 , + min_8 * v2_8 +) // overflow detect

// demonstrate unsigned multiplication overflow detection:
check_does_compile(not,  cui64 , + maxu_64 * v2u_64 +) // overflow detect
check_does_compile(not,  cui64 , + maxu_64 * v2u_32 +) // overflow detect
check_does_compile(not,  cui64 , + maxu_64 * v2u_16 +) // overflow detect
check_does_compile(not,  cui64 , + maxu_64 * v2u_8 +) // overflow detect
static_assert(maxu_32 * v2u_64 + 2_cui64 == 0x2'0000'0000_cui64 );
check_does_compile(not,  cui32 , + maxu_32 * v2u_32 +) // overflow detect
check_does_compile(not,  cui32 , + maxu_32 * v2u_16 +) // overflow detect
check_does_compile(not,  cui32 , + maxu_32 * v2u_8 +) // overflow detect
static_assert(maxu_16 * v2u_64 == 0x1'fffe_cui64  );
static_assert(maxu_16 * v2u_32 == 0x1'fffe_cui32 );
check_does_compile(not,  cui16 , + maxu_16 * v2u_16 +) // overflow detect
check_does_compile(not,  cui16 , + maxu_16 * v2u_8 +) // overflow detect
static_assert(maxu_8  * v2u_64 == 510_cui64 );
static_assert(maxu_8  * v2u_32 == 510_cui32 );
static_assert(maxu_8  * v2u_16 == 510_cui16 );
check_does_compile(not,  cui8 , + maxu_8 * v2u_8 +) // overflow detect

check_does_compile(not,  cui16 , + 0xffff_cui16 * 0xffff_cui16 +) // overflow detect
//static_assert(promote_keep_signedness(0xffff_cui16 * 0xffff_cui16) == 0x1u); // wraps
check_does_compile(not,  cui8 , + 0xff_cui8 * 0xff_cui8 +) // overflow detect
//static_assert(0xff_cui8 * 0xff_cui8 == 1_cui8);


// LShift operations (on unsigned)

static_assert(2_cui8  == (v1u_8  << v1u_8));
static_assert(2_cui16 == (v1u_16 << v1u_8));
static_assert(2_cui32 == (v1u_32 << v1u_8));
static_assert(2_cui64 == (v1u_64 << v1u_8));
check_does_compile(not,  cui8 , + v1u_8 << 8_cui8 +) // overflow detect
check_does_compile(not,  cui16 , + v1u_16 << 16_cui8 +) // overflow detect
check_does_compile(not,  cui32 , + v1u_32 << 32_cui8 +) // overflow detect
check_does_compile(not,  cui64 , + v1u_64 << 64_cui8 +) // overflow detect

// RShift operations (on unsigned)

static_assert(0_cui8  == (v1u_8  >> v1u_8));
static_assert(0_cui16 == (v1u_16 >> v1u_8));
static_assert(0_cui32 == (v1u_32 >> v1u_8));
static_assert(0_cui64 == (v1u_64 >> v1u_8));
check_does_compile(not,  cui8 , + (maxu_8 >> 8_cui8) +) // overflow detect
check_does_compile(not,  cui16 , + (maxu_16 >> 16_cui8) +) // overflow detect
check_does_compile(not,  cui32 , + (maxu_32 >> 32_cui8) +) // overflow detect
check_does_compile(not,  cui64 , + (maxu_64 >> 64_cui8) +) // overflow detect
check_does_compile(not,  cui64 , + (maxu_64 >> maxu_64) +) // overflow detect

// the following does not compile due to signed integer overflow on 32bit int
//static_assert(static_cast<uint16_t>(0xffffu)* static_cast<uint16_t>(0xffffu));

check_does_compile(not,  csi32 , + 0x7fff'ffff_csi32+2_csi32 +) // overflow detect
//static_assert(0x7fff'ffff_csi32+2_csi32 == -0x7fff'ffff_csi32);
//static_assert(0x7fff'ffff + 2); // doesn't compile, integer overflow
check_does_compile(not,  csi32 , + (-0x7fff'ffff_csi32 - 2_csi32) +) // overflow detect
//static_assert(-0x7fff'ffff_csi32 - 2_csi32 == 0x7fff'ffff_csi32);
//static_assert(-0x7fff'ffff - 2); // doesn't compile, integer overflow


check_does_compile(   ,  csi32, + std::numeric_limits<csi32>::min() / 1_csi32  +) // no overflow
check_does_compile(not,  csi32, + std::numeric_limits<csi32>::min() / -1_csi32  +) // overflow detected
//static_assert(std::numeric_limits<si32>::min() / 1_csi32 == std::numeric_limits<si32>::min()); // wraps
//static_assert(std::numeric_limits<si32>::min() / -1_csi32 == std::numeric_limits<si32>::min()); // wraps

#ifdef __clang__
// doesn't seem to work with gcc, but with Apple clang, not sure which is more correct.
int from_int(...); // cause non-matching code below to SFINAE


check_does_compile(not ,  csi8, + from_int(' ')  +) // invalid conversion
check_does_compile(not ,  cui8, + from_int(u' ')  +) // invalid conversion
check_does_compile(not ,  cui32, + from_int(U' ')  +) // invalid conversion
check_does_compile(not ,  cui16, + from_int(L' ')  +) // invalid conversion
check_does_compile(not ,  cui8, + from_int(true)  +) // invalid conversion
//static_assert(32_cui8 == from_int(' ')); // does not compile
//static_assert(32_cui8 == from_int(u' ')); // does not compile
//static_assert(32_cui8 == from_int(U' ')); // does not compile
//static_assert(32_cui8 == from_int(L' ')); // does not compile
//static_assert(1_cui8 == from_int_to<ui8>(true)); // does not compile
#endif

// to signed from signed

check_does_compile( ,  csi8, + from_int_to<csi8>(42)  +) // ok conversion
check_does_compile( ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::min()+0)  +) // ok conversion
check_does_compile( ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::max()+0)  +) // ok conversion
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::min()-1)  +) // overflow conversion
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::max()+1)  +) // overflow conversion

check_does_compile(    ,  csi16, + from_int_to<csi16>(42)  +) // ok conversion
check_does_compile(    ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::max()+0)  +) // ok conversion
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::min()-1)  +) // overflow conversion
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::max()+1)  +) // overflow conversion

check_does_compile(    ,  csi32, + from_int_to<csi32>(42)  +) // ok conversion
check_does_compile(    ,  csi32, + from_int_to<csi32>((int64_t)std::numeric_limits<int32_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  csi32, + from_int_to<csi32>((int64_t)std::numeric_limits<int32_t>::max()+0)  +) // ok conversion
check_does_compile(not ,  csi32, + from_int_to<csi32>((int64_t)std::numeric_limits<int32_t>::min()-1)  +) // overflow conversion
check_does_compile(not ,  csi32, + from_int_to<csi32>((int64_t)std::numeric_limits<int32_t>::max()+1)  +) // overflow conversion

check_does_compile(    ,  csi64, + from_int_to<csi64>(42)  +) // ok conversion
check_does_compile(    ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::max()+0)  +) // ok conversion
check_does_compile(not ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::min()-1)  +) // check would cause UB
check_does_compile(not ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::max()+1)  +) // check fails due to UB


// to signed from unsigned
check_does_compile(    ,  csi8, + from_int_to<csi8>(42ull)  +) // ok conversion
check_does_compile(    ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::min()+0)  +) // from unsigned too large
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::min()+0u)  +) // from unsigned too large
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::min()-1u)  +) //
check_does_compile(    ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::max()+0u)  +) // ok conversion
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<int8_t>::max()+1u)  +) // overflow from unsigned conversion
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<uint8_t>::max())  +) // too big
check_does_compile(not ,  csi8, + from_int_to<csi8>(std::numeric_limits<uint8_t>::min()-1u)  +) // promotion to int no overflow
check_does_compile(    ,  csi8, + from_int_to<csi8>(std::numeric_limits<uint8_t>::max() + std::numeric_limits<int8_t>::min())  +) // OK

check_does_compile(    ,  csi16, + from_int_to<csi16>(42ull)  +) // ok conversion
check_does_compile(    ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::min()+0ll)  +) // from unsigned too large
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::min()+0u)  +) // from unsigned too large
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::min()-1u)  +) // ok from unsigned too large
check_does_compile(    ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::max()+0ull)  +) // ok conversion
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<int16_t>::max()+1ull)  +) // overflow from unsigned conversion
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<uint16_t>::max())  +) // too big
check_does_compile(not ,  csi16, + from_int_to<csi16>(std::numeric_limits<uint16_t>::min()-1u)  +) // unsigned overflow leads to too big value
check_does_compile(    ,  csi16, + from_int_to<csi16>(std::numeric_limits<uint16_t>::max() + std::numeric_limits<int16_t>::min())  +) // OKdue to integral promotion

check_does_compile(    ,  csi32, + from_int_to<csi32>(42ull)  +) // ok conversion
check_does_compile(    ,  csi32, + from_int_to<csi32>(std::numeric_limits<int32_t>::min()+0)  +) // from unsigned too large
check_does_compile(not ,  csi32, + from_int_to<csi32>(std::numeric_limits<int32_t>::min()+0u)  +) // from unsigned too large
check_does_compile(    ,  csi32, + from_int_to<csi32>(std::numeric_limits<int32_t>::min()-1u)  +) // ok from unsigned too large
check_does_compile(    ,  csi32, + from_int_to<csi32>(std::numeric_limits<int32_t>::max()+0u)  +) // ok conversion
check_does_compile(not ,  csi32, + from_int_to<csi32>(std::numeric_limits<int32_t>::max()+1u)  +) // overflow from unsigned conversion
check_does_compile(not ,  csi32, + from_int_to<csi32>(std::numeric_limits<uint32_t>::max())  +) // too big
check_does_compile(not ,  csi32, + from_int_to<csi32>(std::numeric_limits<uint32_t>::min()-1)  +) // unsigned overflow leads to too big value
check_does_compile(    ,  csi32, + from_int_to<csi32>(std::numeric_limits<uint32_t>::max()-std::numeric_limits<int32_t>::min())  +) // OK

check_does_compile(    ,  csi64, + from_int_to<csi64>(42ull)  +) // ok conversion
check_does_compile(    ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::min()+0ll)  +) // from unsigned too large
check_does_compile(not ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::min()+0ull)  +) // from unsigned too large
check_does_compile(    ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::min()-1ull)  +) // ok from unsigned too large
check_does_compile(    ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::max()+0ull)  +) // ok conversion
check_does_compile(not ,  csi64, + from_int_to<csi64>(std::numeric_limits<int64_t>::max()+1ull)  +) // overflow from unsigned conversion
check_does_compile(not ,  csi64, + from_int_to<csi64>(std::numeric_limits<uint64_t>::max())  +) // too big
check_does_compile(not ,  csi64, + from_int_to<csi64>(std::numeric_limits<uint64_t>::min()-1)  +) // unsigned overflow leads to too big value
check_does_compile(    ,  csi64, + from_int_to<csi64>(std::numeric_limits<uint64_t>::max()-std::numeric_limits<int64_t>::min())  +) // OK

// to unsigned from (mostly) unsigned

check_does_compile(not ,  cui8, + from_int_to<cui8>(-1)  +) // not ok conversion
check_does_compile(    ,  cui8, + from_int_to<cui8>(42)  +) // ok conversion
check_does_compile(    ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::max()+0)  +) // ok conversion
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::min()-1)  +) // overflow conversion
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::max()+1)  +) // overflow conversion

check_does_compile(not ,  cui16, + from_int_to<cui16>(-1)  +) // not ok conversion
check_does_compile(    ,  cui16, + from_int_to<cui16>(42)  +) // ok conversion
check_does_compile(    ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::max()+0)  +) // ok conversion
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::min()-1)  +) // overflow conversion
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::max()+1)  +) // overflow conversion

check_does_compile(not ,  cui32, + from_int_to<cui32>(-1)  +) // not ok conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(42)  +) // ok conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::max()+0)  +) // ok conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::min()-1)  +) // expression wraps, OK conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::max()+1)  +) // expression wraps, OK conversion

check_does_compile(not ,  cui64, + from_int_to<cui64>(-1)  +) // not ok conversion
check_does_compile(    ,  cui64, + from_int_to<cui64>(42)  +) // ok conversion
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::min()+0)  +) // ok conversion
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::max()+0)  +) // ok conversion
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::min()-1)  +) // expression wraps, OK conversion
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::max()+1)  +) // expression wraps, OK conversion

// to unsigned from signed

check_does_compile(    ,  cui8, + from_int_to<cui8>(42ll)  +) // ok conversion
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<int8_t>::min()+0)  +) // from unsigned too large
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<int8_t>::min()+0u)  +) // from unsigned too large
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<int8_t>::min()-1u)  +) //
check_does_compile(    ,  cui8, + from_int_to<cui8>(std::numeric_limits<int8_t>::max()+0u)  +) // ok conversion
check_does_compile(    ,  cui8, + from_int_to<cui8>(std::numeric_limits<int8_t>::max()+1u)  +) // overflow from unsigned conversion
check_does_compile(    ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::max())  +) // ok
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::max()+1u)  +) // not ok
check_does_compile(not ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::min()-1u)  +) // unsigned overflow leads to too big value
check_does_compile(    ,  cui8, + from_int_to<cui8>(std::numeric_limits<uint8_t>::max() + std::numeric_limits<int8_t>::min())  +) // OKdue to integral promotion

check_does_compile(    ,  cui16, + from_int_to<cui16>(42ll)  +) // ok conversion
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<int16_t>::min()+0ll)  +) // from unsigned too large
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<int16_t>::min()+0u)  +) // from unsigned too large
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<int16_t>::min()-1u)  +) // ok from unsigned too large
check_does_compile(    ,  cui16, + from_int_to<cui16>(std::numeric_limits<int16_t>::max()+0ull)  +) // ok conversion
check_does_compile(    ,  cui16, + from_int_to<cui16>(std::numeric_limits<int16_t>::max()+1ull)  +) // overflow from unsigned conversion
check_does_compile(    ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::max())  +) // too big
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::max() +1u)  +) // too big
check_does_compile(not ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::min()-1u)  +) // unsigned overflow leads to too big value
check_does_compile(    ,  cui16, + from_int_to<cui16>(std::numeric_limits<uint16_t>::max() + std::numeric_limits<int16_t>::min())  +) // OKdue to integral promotion

check_does_compile(    ,  cui32, + from_int_to<cui32>(42ll)  +) // ok conversion
check_does_compile(not ,  cui32, + from_int_to<cui32>(std::numeric_limits<int32_t>::min())  +) // from signed too large
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<int32_t>::min()+0u)  +) // from unsigned too large
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<int32_t>::min()-1u)  +) // ok from unsigned too large
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<int32_t>::max()+0u)  +) // ok conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<int32_t>::max()+1u)  +) // overflow from unsigned conversion
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::max())  +) // too big
check_does_compile(not ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::min()-1ll)  +) // unsigned overflow leads to too big value
check_does_compile(    ,  cui32, + from_int_to<cui32>(std::numeric_limits<uint32_t>::max()-std::numeric_limits<int32_t>::min())  +) // OK

check_does_compile(    ,  cui64, + from_int_to<cui64>(42ll)  +) // ok conversion
check_does_compile(not ,  cui64, + from_int_to<cui64>(std::numeric_limits<int64_t>::min())  +) // from unsigned too large
check_does_compile(not ,  cui64, + from_int_to<cui64>(-1)  +) // negative to unsigned fails
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<int64_t>::min()+0ull)  +) // from unsigned too large
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<int64_t>::min()-1ull)  +) // ok from unsigned too large
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<int64_t>::max())  +) // ok conversion
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<int64_t>::max()+1ull)  +) // unsigned overflow always OK
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::max())  +) // OK
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::min()-1ll)  +) // unsigned overflow always OK
check_does_compile(    ,  cui64, + from_int_to<cui64>(std::numeric_limits<uint64_t>::max()-std::numeric_limits<int64_t>::min())  +) // OK

// check negation detection
check_does_compile(    ,  csi8, +  (- max_8)  +) // ok conversion
check_does_compile(not ,  csi8, +  (- min_8)  +) // ok conversion
check_does_compile(    ,  csi16, +  (- max_16)  +) // ok conversion
check_does_compile(not ,  csi16, +  (- min_16)  +) // ok conversion
check_does_compile(    ,  csi32, +  (- max_32)  +) // ok conversion
check_does_compile(not ,  csi32, +  (- min_32)  +) // ok conversion
check_does_compile(    ,  csi64, +  (- max_64)  +) // ok conversion
check_does_compile(not ,  csi64, +  (- min_64)  +) // ok conversion
// negation of unsigned types is not available due to concept

// check increment/decrement continue here.... (see below, cannot be at compile time)
// check add
check_does_compile(not ,  csi8,  +  max_8  + 1_csi8  +) // overflow
check_does_compile(not ,  csi16, +  max_16 + 1_csi8  +) // overflow
check_does_compile(not ,  csi32, +  max_32 + 1_csi8  +) // overflow
check_does_compile(not ,  csi64, +  max_64 + 1_csi8  +) // overflow
check_does_compile(not ,  csi8,  +  min_8  + -1_csi8  +) //overflow
check_does_compile(not ,  csi16, +  min_16 + -1_csi8  +) //overflow
check_does_compile(not ,  csi32, +  min_32 + -1_csi8  +) //overflow
check_does_compile(not ,  csi64, +  min_64 + -1_csi8  +) //overflow
check_does_compile(not ,  csi8,  +   1_cui8  +) // mixing signedness
check_does_compile(not ,  csi16, +   1_cui8  +) // mixing signedness
check_does_compile(not ,  csi32, +   1_cui8  +) // mixing signedness
check_does_compile(not ,  csi64, +   1_cui8  +) // mixing signedness
check_does_compile(not ,  cui8,  +  maxu_8  + 1_cui8  +) //overflow
check_does_compile(not ,  cui16, +  maxu_16 + 1_cui8  +) //overflow
check_does_compile(not ,  cui32, +  maxu_32 + 1_cui8  +) //overflow
check_does_compile(not ,  cui64, +  maxu_64 + 1_cui8  +) //overflow
check_does_compile(not ,  cui8,  +   1_csi8  +) // mixing signedness
check_does_compile(not ,  cui16, +   1_csi8  +) // mixing signedness
check_does_compile(not ,  cui32, +   1_csi8  +) // mixing signedness
check_does_compile(not ,  cui64, +   1_csi8  +) // mixing signedness
check_does_compile(    ,  cui8,  +  1_cui8  + 1_cui8  +) // same signedness
check_does_compile(    ,  cui16, +  1_cui16 + 1_cui8  +) // same signedness
check_does_compile(    ,  cui32, +  1_cui32 + 1_cui8  +) // same signedness
check_does_compile(    ,  cui64, +  1_cui64 + 1_cui8  +) // same signedness
// check substract:
check_does_compile(not ,  csi8,  +  max_8  - -1_csi8  +) // overflow
check_does_compile(not ,  csi16, +  max_16 - -1_csi8  +) // overflow
check_does_compile(not ,  csi32, +  max_32 - -1_csi8  +) // overflow
check_does_compile(not ,  csi64, +  max_64 - -1_csi8  +) // overflow
check_does_compile(    ,  csi8,  +  max_8  - 1_csi8  +) //
check_does_compile(    ,  csi16, +  max_16 - 1_csi8  +) //
check_does_compile(    ,  csi32, +  max_32 - 1_csi8  +) //
check_does_compile(    ,  csi64, +  max_64 - 1_csi8  +) //
check_does_compile(not ,  csi8,  +  min_8  - 1_csi8  +) //overflow
check_does_compile(not ,  csi16, +  min_16 - 1_csi8  +) //overflow
check_does_compile(not ,  csi32, +  min_32 - 1_csi8  +) //overflow
check_does_compile(not ,  csi64, +  min_64 - 1_csi8  +) //overflow
check_does_compile(not ,  csi8,   - 1_cui8  +) // mixing signedness
check_does_compile(not ,  csi16,  - 1_cui8  +) // mixing signedness
check_does_compile(not ,  csi32,  - 1_cui8  +) // mixing signedness
check_does_compile(not ,  csi64,  - 1_cui8  +) // mixing signedness
check_does_compile(not ,  cui8,  +  0_cui8  - 1_cui8  +) //overflow
check_does_compile(not ,  cui16, +  0_cui16 - 1_cui8  +) //overflow
check_does_compile(not ,  cui32, +  0_cui32 - 1_cui8  +) //overflow
check_does_compile(not ,  cui64, +  0_cui64 - 1_cui8  +) //overflow
check_does_compile(not ,  cui8,   - 1_csi8  +) // mixing signedness
check_does_compile(not ,  cui16,  - 1_csi8  +) // mixing signedness
check_does_compile(not ,  cui32,  - 1_csi8  +) // mixing signedness
check_does_compile(not ,  cui64,  - 1_csi8  +) // mixing signedness
check_does_compile(    ,  cui8,  +  1_cui8  - 1_cui8  -) // same signedness
check_does_compile(    ,  cui16, +  1_cui16 - 1_cui8  +) // same signedness
check_does_compile(    ,  cui32, +  1_cui32 - 1_cui8  +) // same signedness
check_does_compile(    ,  cui64, +  1_cui64 - 1_cui8  +) // same signedness
template<typename T, typename WHAT>
constexpr bool
isa = std::is_same_v<std::remove_cvref_t<T>,WHAT>;


template<typename T>
constexpr bool
is_unsigned = isa<T, unsigned char>
|| isa<T, unsigned short>
|| isa<T, unsigned >
|| isa<T, unsigned long>
|| isa<T, unsigned long long>;

template<typename T>
constexpr bool
is_signed = isa<T, signed char>
|| isa<T, short>
|| isa<T, int >
|| isa<T, long>
|| isa<T, long long>;


template<typename T>
constexpr bool
is_integer = is_unsigned<T>||is_signed<T>;

static_assert(is_integer<ULT<cui16>>);
static_assert(!is_integer<cui16>);
static_assert(is_integer<ULT<csi16>>);
static_assert(!is_integer<csi16>);



}
#undef check_does_compile
#undef concat_line_impl
#undef concat_line
}
