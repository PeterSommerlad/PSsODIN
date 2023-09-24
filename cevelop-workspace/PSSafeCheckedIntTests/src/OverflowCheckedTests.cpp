#include "OverflowCheckedTests.h"
#include "cute.h"
#include "psssafecheckedint.h"

#include <string>

using namespace pssscint;

void si16minnegateOverflows() {
    const auto minimum { std::numeric_limits<si16>::min() };
    ASSERT_THROWS(-minimum, char const *);
    try {
        auto const x = -minimum;
    } catch (char const * const exc){
        std::string const msg{exc};
        std::string const expectedend{"\"negating std::numeric_limits<E>::min()\""};
        ASSERT_EQUALM(msg,expectedend, msg.substr(msg.size()-expectedend.size()));
    }
}

void s16mindividedbyminus1Overflows(){
    const auto minimum { std::numeric_limits<si16>::min() };
    ASSERT_THROWS((minimum) / (-1_si16), char const *);
    try {
        auto const x = minimum / -1_si16;
    } catch (char const *const exc) {
        std::string const msg{exc};
        std::string const expectedend{"\"signed division overflow\""};
        ASSERT_EQUALM(msg,expectedend, msg.substr(msg.size()-expectedend.size()));
    }
}

void s16minimumdividedbyoneIsminimum(){
    auto const minimum { std::numeric_limits<si16>::min()  };
    ASSERT_EQUAL(minimum, minimum / 1_si16);

}

void s16MultiplicationOverflowDetected(){
    auto const operand { 0x7fff_si16 };
    ASSERT_THROWS(operand * operand, char const *);
}

void s16AdditionOverflowDetected(){
    auto const operand { 0x7fff_si16 };
    ASSERT_THROWS(operand + 1_si16, char const *);

}



cute::suite make_suite_OverflowCheckedTests() {
	cute::suite s { };
	s.push_back(CUTE(si16minnegateOverflows));
	s.push_back(CUTE(s16mindividedbyminus1Overflows));
	s.push_back(CUTE(s16minimumdividedbyoneIsminimum));
	s.push_back(CUTE(s16MultiplicationOverflowDetected));
	s.push_back(CUTE(s16AdditionOverflowDetected));
	return s;
}
