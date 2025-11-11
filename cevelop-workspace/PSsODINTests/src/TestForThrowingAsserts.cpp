#include "TestForThrowingAsserts.h"

#include "pssodin.h"
#include "cute.h"
    using namespace pssodin;

void DivisionByZeroThrows() {
    constexpr auto divisor = 0_csi8;
    auto divident = 1_csi8;

    ASSERT_THROWS((void)(divident/divisor), char const *);
    //constexpr auto should_not_compile = 1_csi8 / divisor; in CompilationTests.cpp
}

void ModuloByZeroThrows() {
    constexpr auto divisor = 0_cui8;
    auto divident = 1_cui8;

    ASSERT_THROWS((void)(divident % divisor), char const *);

    //constexpr auto should_not_compile = 1_cui8 % divisor; in CompilationTests.cpp
}

void ShiftLeftByTooManyBitsThrows() {
    constexpr auto shiftby = 8_cui8;
    auto toshift = 0xff_cui8;

    ASSERT_THROWS((void)(toshift << shiftby), char const *);
     //constexpr auto should_not_compile = 1_cui8 << shiftby; in CompilationTests.cpp
}
void ShiftRightByTooManyBitsThrows() {
    constexpr auto shiftby = 8_cui8;
    auto toshift = 0xff_cui8;

    ASSERT_THROWS((void)(toshift >> shiftby), char const *);
     //constexpr auto should_not_compile = 1_cui8 >> shiftby; in CompilationTests.cpp
}


cute::suite make_suite_TestForThrowingAsserts() {
	cute::suite s { };
	s.push_back(CUTE(DivisionByZeroThrows));
	s.push_back(CUTE(ModuloByZeroThrows));
	s.push_back(CUTE(ShiftLeftByTooManyBitsThrows));
	s.push_back(CUTE(ShiftRightByTooManyBitsThrows));
	return s;
}
