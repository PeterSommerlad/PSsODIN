#include "OverflowCheckedTests.h"
#include "cute.h"
#include "psssafecheckedint.h"

#include <string>

using namespace pssscint;

using exception_t = char const *;


void si16minnegateOverflows() {
    const auto minimum { std::numeric_limits<si16>::min() };
    try {
        std::ignore = -minimum;
    } catch (char const * const exc){
        std::string const msg{exc};
        std::string const expectedend{"\"negating std::numeric_limits<E>::min()\""};
        ASSERT_EQUALM(msg,expectedend, msg.substr(msg.size()-expectedend.size()));
    }
}

void si16mindividedbyminus1Overflows(){
    const auto minimum { std::numeric_limits<si16>::min() };
    try {
        std::ignore = minimum / -1_si16;
    } catch (exception_t const exc) {
        std::string const msg{exc};
        std::string const expectedend{"\"pssscint: signed division overflow\""};
        ASSERT_EQUALM(msg,expectedend, msg.substr(msg.size()-expectedend.size()));
    }
}



void s16minimumdividedbyoneIsminimum(){
    auto const minimum { std::numeric_limits<si16>::min()  };
    ASSERT_EQUAL(minimum, minimum / 1_si16);

}

void s16MultiplicationOverflowDetected(){
    auto const operand { 0x7fff_si16 };
    ASSERT_THROWS(std::ignore = operand * operand, exception_t);
}

void s16AdditionOverflowDetected(){
    auto const operand { 0x7fff_si16 };
    ASSERT_THROWS(std::ignore = operand + 1_si16, exception_t);

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
    ASSERT_THROWS(std::ignore = operand * operand, exception_t);
}

void u16AdditionOverflowDetected(){
    auto const operand { 0xffff_ui16 };
    ASSERT_THROWS(std::ignore = operand + 1_ui16, exception_t);

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
    ASSERT_THROWS(std::ignore = val << 16_ui8, exception_t);
}

void u16RShiftOverflowDetected(){
    auto const val{ 1_ui16 };
    ASSERT_THROWS(std::ignore = val >> 16_ui8, exception_t);
}

void si8incrementOverflow(){
    si8 x{std::numeric_limits<si8>::max()};
    ASSERT_THROWS(++x,char const *);
}
void si16incrementOverflow(){
    si16 x{std::numeric_limits<si16>::max()};
    ASSERT_THROWS(++x,char const *);
}
void si32incrementOverflow(){
    si32 x{std::numeric_limits<si32>::max()};
    ASSERT_THROWS(++x,char const *);
}
void si64incrementOverflow(){
    si64 x{std::numeric_limits<si64>::max()};
    ASSERT_THROWS(++x,char const *);
}
void si8decrementOverflow(){
    si8 x{std::numeric_limits<si8>::min()};
    ASSERT_THROWS(--x,char const *);
}
void si16decrementOverflow(){
    si16 x{std::numeric_limits<si16>::min()};
    ASSERT_THROWS(--x,char const *);
}
void si32decrementOverflow(){
    si32 x{std::numeric_limits<si32>::min()};
    ASSERT_THROWS(--x,char const *);
}
void si64decrementOverflow(){
    si64 x{std::numeric_limits<si64>::min()};
    ASSERT_THROWS(--x,char const *);
}
void si8postincrementOverflow(){
    si8 x{std::numeric_limits<si8>::max()};
    ASSERT_THROWS(std::ignore = x++,char const *);
}
void si16postincrementOverflow(){
    si16 x{std::numeric_limits<si16>::max()};
    ASSERT_THROWS(std::ignore = x++,char const *);
}
void si32postincrementOverflow(){
    si32 x{std::numeric_limits<si32>::max()};
    ASSERT_THROWS(std::ignore = x++,char const *);
}
void si64postincrementOverflow(){
    si64 x{std::numeric_limits<si64>::max()};
    ASSERT_THROWS(std::ignore = x++,char const *);
}
void si8postdecrementOverflow(){
    si8 x{std::numeric_limits<si8>::min()};
    ASSERT_THROWS(std::ignore = x--,char const *);
}
void si16postdecrementOverflow(){
    si16 x{std::numeric_limits<si16>::min()};
    ASSERT_THROWS(std::ignore = x--,char const *);
}
void si32postdecrementOverflow(){
    si32 x{std::numeric_limits<si32>::min()};
    ASSERT_THROWS(std::ignore = x--,char const *);
}
void si64postdecrementOverflow(){
    si64 x{std::numeric_limits<si64>::min()};
    ASSERT_THROWS(std::ignore = x--,char const *);
}

void ui8incrementOverflow(){
    ui8 x{std::numeric_limits<ui8>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui16incrementOverflow(){
    ui16 x{std::numeric_limits<ui16>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui32incrementOverflow(){
    ui32 x{std::numeric_limits<ui32>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui64incrementOverflow(){
    ui64 x{std::numeric_limits<ui64>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui8decrementOverflow(){
    ui8 x{std::numeric_limits<ui8>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui16decrementOverflow(){
    ui16 x{std::numeric_limits<ui16>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui32decrementOverflow(){
    ui32 x{std::numeric_limits<ui32>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui64decrementOverflow(){
    ui64 x{std::numeric_limits<ui64>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui8postincrementOverflow(){
    ui8 x{std::numeric_limits<ui8>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui16postincrementOverflow(){
    ui16 x{std::numeric_limits<ui16>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui32postincrementOverflow(){
    ui32 x{std::numeric_limits<ui32>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui64postincrementOverflow(){
    ui64 x{std::numeric_limits<ui64>::max()};
    ASSERT_THROWS(++x,char const *);
}
void ui8postdecrementOverflow(){
    ui8 x{std::numeric_limits<ui8>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui16postdecrementOverflow(){
    ui16 x{std::numeric_limits<ui16>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui32postdecrementOverflow(){
    ui32 x{std::numeric_limits<ui32>::min()};
    ASSERT_THROWS(--x,char const *);
}
void ui64postdecrementOverflow(){
    ui64 x{std::numeric_limits<ui64>::min()};
    ASSERT_THROWS(--x,char const *);
}

void si8addtoMaxOverflow(){
    auto const max = std::numeric_limits<si8>::max();
    ASSERT_THROWS(std::ignore = 1_si8+max,char const *);
}
void si8addtoMinOverflow(){
    auto const min = std::numeric_limits<si8>::min();
    ASSERT_THROWS(std::ignore = -1_si8+min,char const *);
}
void si16addtoMaxOverflow(){
    auto const max = std::numeric_limits<si16>::max();
    ASSERT_THROWS(std::ignore = 1_si16+max,char const *);
}
void si16addtoMinOverflow(){
    auto const min = std::numeric_limits<si16>::min();
    ASSERT_THROWS(std::ignore = -1_si16+min,char const *);
}
void si32addtoMaxOverflow(){
    auto const max = std::numeric_limits<si32>::max();
    ASSERT_THROWS(std::ignore = 1_si32+max,char const *);
}
void si32addtoMinOverflow(){
    auto const min = std::numeric_limits<si32>::min();
    ASSERT_THROWS(std::ignore = -1_si32+min,char const *);
}
void si64addtoMaxOverflow(){
    auto const max = std::numeric_limits<si64>::max();
    ASSERT_THROWS(std::ignore = 1_si64+max,char const *);
}
void si64addtoMinOverflow(){
    auto const min = std::numeric_limits<si64>::min();
    ASSERT_THROWS(std::ignore = -1_si64+min,char const *);
}
void ui8addtoMaxOverflow(){
    auto const max = std::numeric_limits<ui8>::max();
    ASSERT_THROWS(std::ignore = 1_ui8+max,char const *);
}
void ui16addtoMaxOverflow(){
    auto const max = std::numeric_limits<ui16>::max();
    ASSERT_THROWS(std::ignore = 1_ui16+max,char const *);
}
void ui32addtoMaxOverflow(){
    auto const max = std::numeric_limits<ui32>::max();
    ASSERT_THROWS(std::ignore = 1_ui32+max,char const *);
}
void ui64addtoMaxOverflow(){
    auto const max = std::numeric_limits<ui64>::max();
    ASSERT_THROWS(std::ignore = 1_ui64+max,char const *);
}

void si8subfromMaxOverflow(){
    auto const max = std::numeric_limits<si8>::max();
    ASSERT_THROWS(std::ignore = max - -1_si8,char const *);
}
void si8subfromMinOverflow(){
    auto const min = std::numeric_limits<si8>::min();
    ASSERT_THROWS(std::ignore = min - 1_si8,char const *);
}
void ui8subfromZeroOverflow(){
    auto const min = std::numeric_limits<ui8>::min();
    ASSERT_THROWS(std::ignore = min - 1_ui8,char const *);
}
void si16subfromMaxOverflow(){
    auto const max = std::numeric_limits<si16>::max();
    ASSERT_THROWS(std::ignore = max - -1_si16,char const *);
}
void si16subfromMinOverflow(){
    auto const min = std::numeric_limits<si16>::min();
    ASSERT_THROWS(std::ignore = min - 1_si16,char const *);
}
void ui16subfromZeroOverflow(){
    auto const min = std::numeric_limits<ui16>::min();
    ASSERT_THROWS(std::ignore = min - 1_ui16,char const *);
}
void si32subfromMaxOverflow(){
    auto const max = std::numeric_limits<si32>::max();
    ASSERT_THROWS(std::ignore = max - -1_si32,char const *);
}
void si32subfromMinOverflow(){
    auto const min = std::numeric_limits<si32>::min();
    ASSERT_THROWS(std::ignore = min - 1_si32,char const *);
}
void ui32subfromZeroOverflow(){
    auto const min = std::numeric_limits<ui32>::min();
    ASSERT_THROWS(std::ignore = min - 1_ui32,char const *);
}
void si64subfromMaxOverflow(){
    auto const max = std::numeric_limits<si64>::max();
    ASSERT_THROWS(std::ignore = max - -1_si64,char const *);
}
void si64subfromMinOverflow(){
    auto const min = std::numeric_limits<si64>::min();
    ASSERT_THROWS(std::ignore = min - 1_si64,char const *);
}
void ui64subfromZeroOverflow(){
    auto const min = std::numeric_limits<ui64>::min();
    ASSERT_THROWS(std::ignore = min - 1_ui64,char const *);
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
    s.push_back(CUTE(si8incrementOverflow));
    s.push_back(CUTE(si16incrementOverflow));
    s.push_back(CUTE(si32incrementOverflow));
    s.push_back(CUTE(si64incrementOverflow));
    s.push_back(CUTE(si8decrementOverflow));
    s.push_back(CUTE(si16decrementOverflow));
    s.push_back(CUTE(si32decrementOverflow));
    s.push_back(CUTE(si64decrementOverflow));
    s.push_back(CUTE(ui8incrementOverflow));
    s.push_back(CUTE(ui16incrementOverflow));
    s.push_back(CUTE(ui32incrementOverflow));
    s.push_back(CUTE(ui64incrementOverflow));
    s.push_back(CUTE(ui8decrementOverflow));
    s.push_back(CUTE(ui16decrementOverflow));
    s.push_back(CUTE(ui32decrementOverflow));
    s.push_back(CUTE(ui64decrementOverflow));
    s.push_back(CUTE(si8postincrementOverflow));
    s.push_back(CUTE(si16postincrementOverflow));
    s.push_back(CUTE(si32postincrementOverflow));
    s.push_back(CUTE(si64postincrementOverflow));
    s.push_back(CUTE(si8postdecrementOverflow));
    s.push_back(CUTE(si16postdecrementOverflow));
    s.push_back(CUTE(si32postdecrementOverflow));
    s.push_back(CUTE(si64postdecrementOverflow));
    s.push_back(CUTE(ui8postincrementOverflow));
    s.push_back(CUTE(ui16postincrementOverflow));
    s.push_back(CUTE(ui32postincrementOverflow));
    s.push_back(CUTE(ui64postincrementOverflow));
    s.push_back(CUTE(ui8postdecrementOverflow));
    s.push_back(CUTE(ui16postdecrementOverflow));
    s.push_back(CUTE(ui32postdecrementOverflow));
    s.push_back(CUTE(ui64postdecrementOverflow));
	s.push_back(CUTE(si8addtoMaxOverflow));
	s.push_back(CUTE(si8addtoMinOverflow));
	s.push_back(CUTE(si16addtoMaxOverflow));
	s.push_back(CUTE(si16addtoMinOverflow));
	s.push_back(CUTE(si32addtoMaxOverflow));
	s.push_back(CUTE(si32addtoMinOverflow));
	s.push_back(CUTE(si64addtoMaxOverflow));
	s.push_back(CUTE(si64addtoMaxOverflow));
	s.push_back(CUTE(si64addtoMinOverflow));
	s.push_back(CUTE(ui8addtoMaxOverflow));
	s.push_back(CUTE(ui16addtoMaxOverflow));
	s.push_back(CUTE(ui32addtoMaxOverflow));
	s.push_back(CUTE(ui64addtoMaxOverflow));
	s.push_back(CUTE(si8subfromMaxOverflow));
	s.push_back(CUTE(si8subfromMinOverflow));
	s.push_back(CUTE(ui8subfromZeroOverflow));
	s.push_back(CUTE(si16subfromMaxOverflow));
	s.push_back(CUTE(si16subfromMinOverflow));
	s.push_back(CUTE(ui16subfromZeroOverflow));
	s.push_back(CUTE(si32subfromMaxOverflow));
	s.push_back(CUTE(si32subfromMinOverflow));
	s.push_back(CUTE(ui32subfromZeroOverflow));
	s.push_back(CUTE(si64subfromMaxOverflow));
	s.push_back(CUTE(si64subfromMinOverflow));
	s.push_back(CUTE(ui64subfromZeroOverflow));
	return s;
}
