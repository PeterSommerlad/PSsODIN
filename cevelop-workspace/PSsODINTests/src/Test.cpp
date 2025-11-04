#include "pssodin.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "CodeGenBenchmark.h"
#include "OverflowCheckedTests.h"
#include "NonBuiltInOverflowDetectionTests.h"
#include "TestForThrowingAsserts.h"
#include <type_traits>

using namespace pssodin::literals;
using namespace pssodin;

void signedIntegerBoundaryTestResultRecovery(){
    // temporary testcase for getting static_asserts above right
    ASSERT_EQUAL(0x8000'0000_csi64, std::numeric_limits<csi32>::max() + 1_csi64  );
}


void si8preincrement(){
    auto one = 1_csi8;
    ASSERT_EQUAL(2_csi8,++one);
}
void si8postincrement(){
    auto one = 1_csi8;
    ASSERT_EQUAL(1_csi8,one++);
    ASSERT_EQUAL(2_csi8,one);
}
void si8predecrement(){
    auto one = 1_csi8;
    ASSERT_EQUAL(0_csi8,--one);
}
void si8postdecrement(){
    auto one = 1_csi8;
    ASSERT_EQUAL(1_csi8,one--);
    ASSERT_EQUAL(0_csi8,one);
}
void si16preincrement(){
    auto one = 1_csi16;
    ASSERT_EQUAL(2_csi16,++one);
}
void si16postincrement(){
    auto one = 1_csi16;
    ASSERT_EQUAL(1_csi16,one++);
    ASSERT_EQUAL(2_csi16,one);
}
void si16predecrement(){
    auto one = 1_csi16;
    ASSERT_EQUAL(0_csi16,--one);
}
void si16postdecrement(){
    auto one = 1_csi16;
    ASSERT_EQUAL(1_csi16,one--);
    ASSERT_EQUAL(0_csi16,one);
}
void si32preincrement(){
    auto one = 1_csi32;
    ASSERT_EQUAL(2_csi32,++one);
}
void si32postincrement(){
    auto one = 1_csi32;
    ASSERT_EQUAL(1_csi32,one++);
    ASSERT_EQUAL(2_csi32,one);
}
void si32predecrement(){
    auto one = 1_csi32;
    ASSERT_EQUAL(0_csi32,--one);
}
void si32postdecrement(){
    auto one = 1_csi32;
    ASSERT_EQUAL(1_csi32,one--);
    ASSERT_EQUAL(0_csi32,one);
}
void si64preincrement(){
    auto one = 1_csi64;
    ASSERT_EQUAL(2_csi64,++one);
}
void si64postincrement(){
    auto one = 1_csi64;
    ASSERT_EQUAL(1_csi64,one++);
    ASSERT_EQUAL(2_csi64,one);
}
void si64predecrement(){
    auto one = 1_csi64;
    ASSERT_EQUAL(0_csi64,--one);
}
void si64postdecrement(){
    auto one = 1_csi64;
    ASSERT_EQUAL(1_csi64,one--);
    ASSERT_EQUAL(0_csi64,one);
}


void ui8preincrement(){
    auto one = 1_cui8;
    ASSERT_EQUAL(2_cui8,++one);
}
void ui8postincrement(){
    auto one = 1_cui8;
    ASSERT_EQUAL(1_cui8,one++);
    ASSERT_EQUAL(2_cui8,one);
}
void ui8predecrement(){
    auto one = 1_cui8;
    ASSERT_EQUAL(0_cui8,--one);
}
void ui8postdecrement(){
    auto one = 1_cui8;
    ASSERT_EQUAL(1_cui8,one--);
    ASSERT_EQUAL(0_cui8,one);
}
void ui16preincrement(){
    auto one = 1_cui16;
    ASSERT_EQUAL(2_cui16,++one);
}
void ui16postincrement(){
    auto one = 1_cui16;
    ASSERT_EQUAL(1_cui16,one++);
    ASSERT_EQUAL(2_cui16,one);
}
void ui16predecrement(){
    auto one = 1_cui16;
    ASSERT_EQUAL(0_cui16,--one);
}
void ui16postdecrement(){
    auto one = 1_cui16;
    ASSERT_EQUAL(1_cui16,one--);
    ASSERT_EQUAL(0_cui16,one);
}
void ui32preincrement(){
    auto one = 1_cui32;
    ASSERT_EQUAL(2_cui32,++one);
}
void ui32postincrement(){
    auto one = 1_cui32;
    ASSERT_EQUAL(1_cui32,one++);
    ASSERT_EQUAL(2_cui32,one);
}
void ui32predecrement(){
    auto one = 1_cui32;
    ASSERT_EQUAL(0_cui32,--one);
}
void ui32postdecrement(){
    auto one = 1_cui32;
    ASSERT_EQUAL(1_cui32,one--);
    ASSERT_EQUAL(0_cui32,one);
}
void ui64preincrement(){
    auto one = 1_cui64;
    ASSERT_EQUAL(2_cui64,++one);
}
void ui64postincrement(){
    auto one = 1_cui64;
    ASSERT_EQUAL(1_cui64,one++);
    ASSERT_EQUAL(2_cui64,one);
}
void ui64predecrement(){
    auto one = 1_cui64;
    ASSERT_EQUAL(0_cui64,--one);
}
void ui64postdecrement(){
    auto one = 1_cui64;
    ASSERT_EQUAL(1_cui64,one--);
    ASSERT_EQUAL(0_cui64,one);
}
void ui16intExists() {
    using pssodin::cui16;
    auto large=0xff00_cui16;
    //0x10000_cui16; // compile error
    //ui16{0xfffff}; // narrowing detection
    ASSERT_EQUAL(cui16{0xff00u},large);
}

void ui16NotEqualAutomaticInCpp20(){
    ASSERT(0xf_cui16 != 0_cui16);
}

void ui16canbeadded(){
    ASSERT_EQUAL(100_cui16,75_cui16+25_cui16);
}

void ui16canbeaddedto(){
    auto l = 42_cui16;
    l += 8_cui8;
    //l += 1_cui32; // compile error
    ASSERT_EQUAL(50_cui16,l);
}

void ui16canbesubtracted(){
    ASSERT_EQUAL(50_cui16,75_cui16-25_cui16);
}

void ui16canbesubtractedfrom(){
    auto l = 42_cui16;
    l -= 8_cui8;
    //l -= 1_cui32; // compile error
    ASSERT_EQUAL(34_cui16,l);
}

void ui16canbemultiplied(){
    ASSERT_EQUAL(1875_cui16,75_cui16*25_cui16);
}

void ui16canbemultipliedwith(){
    auto l = 42_cui16;
    l *= 8_cui8;
    //l -= 1_cui32; // compile error
    ASSERT_EQUAL(336_cui16,l);
}


void ui16canbedivided(){
    ASSERT_EQUAL(3_cui16,75_cui16/25_cui16);
}

void ui16canbedividedby(){
    auto l = 42_cui16;
    l /= 7_cui8;
    //l /= 1_cui32; // compile error
    ASSERT_EQUAL(6_cui16,l);
}

void ui16canbemoduloed(){
    ASSERT_EQUAL(10_cui16,75_cui16%13_cui16);
}

void ui16canbemoduloedby(){
    auto l = 42_cui16;
    l %= 13_cui8;
    //l %= 1_cui32; // compile error
    ASSERT_EQUAL(3_cui16,l);
}


void ui16canbeanded(){
    ASSERT_EQUAL(0X0AA0_cui16,0x0ff0_cui16 & 0xAAAA_cui16);
}

void ui16canbeandedwith(){
    auto l = 0xff00_cui16;
    l &= 0xABCD_cui16;
    //l &= 1_cui8; // compile error
    ASSERT_EQUAL(0xAB00_cui16,l);
}

void ui16canbeored(){
    ASSERT_EQUAL(0XAFFA_cui16,0x0ff0_cui16 | 0xAAAA_cui16);
}

void ui16canbeoredwith(){
    auto l = 0xff00_cui16;
    l |= 0xABCD_cui16;
    //l |= 1_cui8; // compile error
    ASSERT_EQUAL(0xFFCD_cui16,l);
}

void ui16canbexored(){
    ASSERT_EQUAL(0XA55A_cui16,0x0ff0_cui16 ^ 0xAAAA_cui16);
}

void ui16canbexoredwith(){
    auto l = 0xff00_cui16;
    l ^= 0xABCD_cui16;
    //l ^= 1_cui8; // compile error
    ASSERT_EQUAL(0x54CD_cui16,l);
}

void ui16canbenegated(){
    ASSERT_EQUAL(0XA55A_cui16, ~0x5AA5_cui16 );
}

void ui16canbeleftshifted(){
    //constexpr auto l = 0x1_cui16 << 16_cui8; // compile error
    ASSERT_EQUAL(0XFF00_cui16,0x0ff0_cui16 << 0x4_cui8);
}

void ui16canbeleftshiftedby(){
    auto l = 0x00ff_cui16;
    l <<= 4_cui16;
    ASSERT_EQUAL(0x0FF0_cui16,l);
}
void ui16canberightshifted(){
    //constexpr auto l = 0x1_cui16 << 16_cui8; // compile error
    ASSERT_EQUAL(0X00FF_cui16,0x0ff0_cui16 >> 0x4_cui8);
}

void ui16canberightshiftedby(){
    auto l = 0x00ff_cui16;
    l >>= 4_cui16;
    ASSERT_EQUAL(0x0F_cui16,l);
}
void ui16canbepreincremented(){
    auto l = 0x00ff_cui16;
    ASSERT_EQUAL(0x100_cui16,++l);
    ASSERT_EQUAL(0x100_cui16,l);
}
void ui16canbepostincremented(){
    auto l = 0x00ff_cui16;
    ASSERT_EQUAL(0x00ff_cui16,l++);
    ASSERT_EQUAL(0x100_cui16,l);
}
void ui16canbepredecremented(){
    auto l = 0x00ff_cui16;
    ASSERT_EQUAL(0x100_cui16,++l);
    ASSERT_EQUAL(0x100_cui16,l);
}
void ui16canbepostdecremented(){
    auto l = 0x00ff_cui16;
    ASSERT_EQUAL(0x00ff_cui16,l++);
    ASSERT_EQUAL(0x100_cui16,l);
}

void ui16canbecompared(){
    auto l = 0x00ff_cui16;
    auto s = 0x000f_cui16;

	ASSERTM("check comparison", l != s && s < l && l >= s && !(l < s) && ! (l <= s));
}

void ui16canNotbecomparedwithui8() {
    auto l = 0x00ff_cui16;
    auto s = 0x000f_cui8;


//    ASSERTM("check comparison", l != s && s < l && l >= s && !(l < s) && ! (l <= s));

    auto ss = s + 0_cui16;
    ASSERTM("check comparison", l != ss && ss < l && l >= ss && !(l < ss) && ! (l <= ss));
}

void ui32CanNotbeComparedwithlong(){
    auto l = 0x00ff_cui32;
    auto s = std::uint32_t{0x000fU};


//    ASSERTM("check comparison", l != s && s < l && l >= s && !(l < s) && ! (l <= s));

    auto ss = pssodin::from_int(s);
    ASSERTM("check comparison", l != ss && ss < l && l >= ss && !(l < ss) && ! (l <= ss));

}


// signed test to check if result is correct (overflow wraps)

void si8canbeaddednormal(){
    ASSERT_EQUAL(42_csi8, 21_csi8 + 21_csi8);
}

void si8Negation(){
    ASSERT_EQUAL(-1,promote_keep_signedness(-1_csi8));
}

void si8negationminintthrows(){
    ASSERT_THROWS(std::ignore = -(std::numeric_limits<pssodin::csi8>::min()), char const *);
}

void si8overflowIsDetected(){
    ASSERT_THROWS(std::ignore = 127_csi8+2_csi8, char const *);
}

void si8subtraction(){
    ASSERT_EQUAL(-1_csi8,2_csi8-3_csi8);
}

void si8subtractionoverflowdetected(){
    try {
    ASSERT_THROWS(std::ignore = ((-2_csi8)-127_csi8) , char const *);
    } catch(...){}
}
void si8multiplication(){
    ASSERT_EQUAL(120_csi8 , 3_csi8 * 40_csi8);
}
void si8division(){
    ASSERT_EQUAL(3_csi8 , 120_csi8 / 40_csi8);
}

void si8OutputAsInteger(){
    std::ostringstream out{};
    out << 42_csi8;
    ASSERT_EQUAL("42",out.str());
}

void ui8OutputAsInteger(){
    std::ostringstream out{};
    out << 42_cui8;
    ASSERT_EQUAL("42",out.str());
}

void checkedFromInt(){
    using namespace pssodin;
    ASSERT_THROWS(std::ignore = from_int_to<cui8>(2400u), char const *);

}




namespace cppnowtalk{

void testUBforint() {
    std::ostringstream out{};
    out << 65535 * 32768 << '\n';
    // prints: 2147450880
#pragma GCC diagnostic push
#ifdef __clang__
    #pragma clang diagnostic ignored "-Winteger-overflow"
#else
    #pragma GCC diagnostic ignored "-Woverflow"
#endif
    out << 65536 * 32768 << '\n';
    //../src/Test.cpp:421:18: error: integer overflow in expression of type 'int' results in '-2147483648' [-Werror=overflow]
#pragma GCC diagnostic pop
    // prints: ?
    out << std::boolalpha << std::numeric_limits<int>::is_modulo << '\n';
    ASSERT_EQUAL("2147450880\n-2147483648\nfalse\n",out.str());
}
void testNoUBforunsigned() {
    std::ostringstream out{};
    out << 65535u * 32768u << '\n';
    // prints: 2147450880
    out << 65536u * 32768u << '\n';
    // prints: 2147483648

    out << 65536u * 32768u * 2u << '\n';
    // prints: ?
    out << std::boolalpha << std::numeric_limits<unsigned>::is_modulo << '\n';
    ASSERT_EQUAL("2147450880\n2147483648\n0\ntrue\n",out.str());
}
}

bool runAllTests(int argc, char const *argv[]) {
    cute::suite TestForThrowingAsserts = make_suite_TestForThrowingAsserts();
    TestForThrowingAsserts.push_back(CUTE(cppnowtalk::testUBforint));
    TestForThrowingAsserts.push_back(CUTE(cppnowtalk::testNoUBforunsigned));

    cute::suite s { };

    s.push_back(CUTE(ui16intExists));
    s.push_back(CUTE(ui16NotEqualAutomaticInCpp20));
    s.push_back(CUTE(ui16canbeadded));
    s.push_back(CUTE(ui16canbeaddedto));
    s.push_back(CUTE(ui16canbesubtracted));
    s.push_back(CUTE(ui16canbesubtractedfrom));
    s.push_back(CUTE(ui16canbemultiplied));
    s.push_back(CUTE(ui16canbemultipliedwith));
    s.push_back(CUTE(ui16canbedivided));
    s.push_back(CUTE(ui16canbedividedby));
    s.push_back(CUTE(ui16canbemoduloed));
    s.push_back(CUTE(ui16canbemoduloedby));
    s.push_back(CUTE(ui16canbeandedwith));
    s.push_back(CUTE(ui16canbeanded));
    s.push_back(CUTE(ui16canbeored));
    s.push_back(CUTE(ui16canbeoredwith));
    s.push_back(CUTE(ui16canbexoredwith));
    s.push_back(CUTE(ui16canbexored));
    s.push_back(CUTE(ui16canbenegated));
    s.push_back(CUTE(ui16canbeleftshifted));
    s.push_back(CUTE(ui16canbeleftshiftedby));
    s.push_back(CUTE(ui16canberightshifted));
    s.push_back(CUTE(ui16canberightshiftedby));
    s.push_back(CUTE(si8canbeaddednormal));
    s.push_back(CUTE(si8Negation));
    s.push_back(CUTE(si8negationminintthrows));
    s.push_back(CUTE(si8overflowIsDetected));
    s.push_back(CUTE(si8subtraction));
    s.push_back(CUTE(si8subtractionoverflowdetected));
    s.push_back(CUTE(si8multiplication));
    s.push_back(CUTE(si8division));
    s.push_back(CUTE(ui16canbepreincremented));
    s.push_back(CUTE(ui16canbepostincremented));
    s.push_back(CUTE(ui16canbepredecremented));
    s.push_back(CUTE(ui16canbepostdecremented));
	s.push_back(CUTE(checkedFromInt));
	s.push_back(CUTE(si8OutputAsInteger));
	s.push_back(CUTE(ui8OutputAsInteger));
	s.push_back(CUTE(ui16canbecompared));
	s.push_back(CUTE(ui16canNotbecomparedwithui8));
	s.push_back(CUTE(ui32CanNotbeComparedwithlong));
	s.push_back(CUTE(signedIntegerBoundaryTestResultRecovery));
    s.push_back(CUTE(si8preincrement));
    s.push_back(CUTE(si8postincrement));
    s.push_back(CUTE(si8predecrement));
    s.push_back(CUTE(si8postdecrement));
    s.push_back(CUTE(si16preincrement));
    s.push_back(CUTE(si16postincrement));
    s.push_back(CUTE(si16predecrement));
    s.push_back(CUTE(si16postdecrement));
    s.push_back(CUTE(si32preincrement));
    s.push_back(CUTE(si32postincrement));
    s.push_back(CUTE(si32predecrement));
    s.push_back(CUTE(si32postdecrement));
    s.push_back(CUTE(si64preincrement));
    s.push_back(CUTE(si64postincrement));
    s.push_back(CUTE(si64predecrement));
    s.push_back(CUTE(si64postdecrement));
    s.push_back(CUTE(ui8preincrement));
    s.push_back(CUTE(ui8postincrement));
    s.push_back(CUTE(ui8predecrement));
    s.push_back(CUTE(ui8postdecrement));
    s.push_back(CUTE(ui16preincrement));
    s.push_back(CUTE(ui16postincrement));
    s.push_back(CUTE(ui16predecrement));
    s.push_back(CUTE(ui16postdecrement));
    s.push_back(CUTE(ui32preincrement));
    s.push_back(CUTE(ui32postincrement));
    s.push_back(CUTE(ui32predecrement));
    s.push_back(CUTE(ui32postdecrement));
    s.push_back(CUTE(ui64preincrement));
    s.push_back(CUTE(ui64postincrement));
    s.push_back(CUTE(ui64predecrement));
    s.push_back(CUTE(ui64postdecrement));
	cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    auto runner = cute::makeRunner(lis, argc, argv);
    bool success = runner(s, "AllTests");
    success = runner(make_suite_CodeGenBenchmark(),"CodeGenBenchmark") && success;
    success &= runner(TestForThrowingAsserts, "TestForThrowingAsserts");
    cute::suite OverflowCheckedTests = make_suite_OverflowCheckedTests();
    success &= runner(OverflowCheckedTests, "OverflowCheckedTests");
    return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
