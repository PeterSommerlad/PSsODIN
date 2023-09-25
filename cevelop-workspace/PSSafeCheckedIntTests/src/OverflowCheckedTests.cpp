#include "OverflowCheckedTests.h"
#include "cute.h"
#include "psssafecheckedint.h"

#include <string>

using namespace pssscint;

#pragma GCC diagnostic push
#if defined(__GNUG__)
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"

#else
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif
#endif

using exception_t = char const *;


void si16minnegateOverflows() {
    const auto minimum { std::numeric_limits<si16>::min() };
    ASSERT_THROWS(-minimum, exception_t);
    try {
        auto const x = -minimum;
    } catch (char const * const exc){
        std::string const msg{exc};
        std::string const expectedend{"\"negating std::numeric_limits<E>::min()\""};
        ASSERT_EQUALM(msg,expectedend, msg.substr(msg.size()-expectedend.size()));
    }
}

void si16mindividedbyminus1Overflows(){
    const auto minimum { std::numeric_limits<si16>::min() };
    ASSERT_THROWS((minimum) / (-1_si16), exception_t);
    try {
        auto const x = minimum / -1_si16;
    } catch (exception_t const exc) {
        std::string const msg{exc};
        std::string const expectedend{"\"pssscint: signed division overflow\""};
        ASSERT_EQUALM(msg,expectedend, msg.substr(msg.size()-expectedend.size()));
    }
}

#pragma GCC diagnostic pop


void s16minimumdividedbyoneIsminimum(){
    auto const minimum { std::numeric_limits<si16>::min()  };
    ASSERT_EQUAL(minimum, minimum / 1_si16);

}

void s16MultiplicationOverflowDetected(){
    auto const operand { 0x7fff_si16 };
    ASSERT_THROWS(operand * operand, exception_t);
}

void s16AdditionOverflowDetected(){
    auto const operand { 0x7fff_si16 };
    ASSERT_THROWS(operand + 1_si16, exception_t);

}
void s16IncrementOverflowDetected(){
	auto max{ std::numeric_limits<si16>::max() };
	ASSERT_THROWS(++max, exception_t);
}

void s16DecrementOverflowDetected(){
    auto min{ std::numeric_limits<si16>::min() };
    ASSERT_THROWS(--min, exception_t);
}

void u16minimumdividedbyoneIsminimum(){
    auto const minimum { std::numeric_limits<ui16>::min()  };
    ASSERT_EQUAL(minimum, minimum / 1_ui16);

}

void u16MultiplicationOverflowDetected(){
    auto const operand { 0x7fff_ui16 };
    ASSERT_THROWS(operand * operand, exception_t);
}

void u16AdditionOverflowDetected(){
    auto const operand { 0xffff_ui16 };
    ASSERT_THROWS(operand + 1_ui16, exception_t);

}
void u16IncrementOverflowDetected(){
    auto max{ std::numeric_limits<ui16>::max() };
    ASSERT_THROWS(++max, exception_t);
}

void u16DecrementOverflowDetected(){
    auto min{ 0_ui16 };
    ASSERT_THROWS(--min, exception_t);
}

void u16LShiftOverflowDetected(){
    auto const val{ 1_ui16 };
    ASSERT_THROWS(val << 16_ui8, exception_t);
}

void u16RShiftOverflowDetected(){
    auto const val{ 1_ui16 };
    ASSERT_THROWS(val >> 16_ui8, exception_t);
}



cute::suite make_suite_OverflowCheckedTests() {
	cute::suite s { };
	s.push_back(CUTE(si16minnegateOverflows));
	s.push_back(CUTE(si16mindividedbyminus1Overflows));
	s.push_back(CUTE(s16minimumdividedbyoneIsminimum));
	s.push_back(CUTE(s16MultiplicationOverflowDetected));
	s.push_back(CUTE(s16AdditionOverflowDetected));
	s.push_back(CUTE(s16IncrementOverflowDetected));
	s.push_back(CUTE(s16DecrementOverflowDetected));
	s.push_back(CUTE(u16minimumdividedbyoneIsminimum));
	s.push_back(CUTE(u16MultiplicationOverflowDetected));
	s.push_back(CUTE(u16AdditionOverflowDetected));
	s.push_back(CUTE(u16IncrementOverflowDetected));
	s.push_back(CUTE(u16DecrementOverflowDetected));
	s.push_back(CUTE(u16LShiftOverflowDetected));
	s.push_back(CUTE(u16RShiftOverflowDetected));
	return s;
}
