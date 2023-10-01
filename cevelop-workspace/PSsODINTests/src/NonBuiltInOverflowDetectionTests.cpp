#include "NonBuiltInOverflowDetectionTests.h"
#include "cute.h"

#include "psssafecheckedint.h"

using namespace pssodin::non_builtin;

template<typename INT>
struct testSignedAddOverflow{
void AddSiNoOverflowPP() {
    INT result{};
    INT const l{1},r{1};
	ASSERT(not non_builtin_add_overflow(l, r, &result));
}
void AddSiOverflowPP() {
    INT result{};
    INT const l{std::numeric_limits<INT>::max()},r{1};
    ASSERT(non_builtin_add_overflow(l, r, &result));
}
void AddSiOverflowNN() {
    INT result{};
    INT const l{-std::numeric_limits<INT>::max()},r{-2};
    ASSERT(non_builtin_add_overflow(l, r, &result));
}
void AddSiNoOverflowNN() {
    INT result{};
    INT const l{-std::numeric_limits<INT>::max()},r{-1};
    ASSERT(not non_builtin_add_overflow(l, r, &result));
}
void AddSiNoOverflowPN() {
    INT result{};
    INT const l{std::numeric_limits<INT>::max()},r{std::numeric_limits<INT>::min()};
    ASSERT(not non_builtin_add_overflow(l, r, &result));
}
void AddSiNoOverflowNP() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{std::numeric_limits<INT>::max()};
    ASSERT(not non_builtin_add_overflow(l, r, &result));
}
};
template<typename INT>
struct testUnSignedAddOverflow{
void AddUnNoOverflowPP() {
    INT result{};
    INT const l{1},r{1};
    ASSERT(not non_builtin_add_overflow(l, r, &result));
}
void AddUnOverflowPP() {
    INT result{};
    INT const l{std::numeric_limits<INT>::max()},r{1};
    ASSERT(non_builtin_add_overflow(l, r, &result));
}
};
template<typename INT>
struct testSignedSubOverflow{
void SubSiNoOverflowPP() {
    INT result{};
    INT const l{1},r{1};
    ASSERT(not non_builtin_sub_overflow(l, r, &result));
}
void SubSiOverflowNP() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{1};
    ASSERT(non_builtin_sub_overflow(l, r, &result));
}
void SubSiOverflowPmaxN() {
    INT result{};
    INT const l{std::numeric_limits<INT>::max()},r{-1};
    ASSERT(non_builtin_sub_overflow(l, r, &result));
}
void SubSiNoOverflowNN() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{-1};
    ASSERT(not non_builtin_sub_overflow(l, r, &result));
}
void SubSiNoOverflowNP() {
    INT result{};
    INT const l{-std::numeric_limits<INT>::max()},r{std::numeric_limits<INT>::min()};
    ASSERT(not non_builtin_sub_overflow(l, r, &result));
}
void SubSiNoOverflowNPmax() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{-std::numeric_limits<INT>::max()};
    ASSERT(not non_builtin_sub_overflow(l, r, &result));
}
};
template<typename INT>
struct testUnSignedSubOverflow{
void SubUnNoOverflowPP() {
    INT result{};
    INT const l{1},r{1};
    ASSERT(not non_builtin_sub_overflow(l, r, &result));
}
void SubUnOverflowPP() {
    INT result{};
    INT const l{0},r{1};
    ASSERT(non_builtin_sub_overflow(l, r, &result));
}
};

template<typename INT>
struct testSignedMulOverflow{
void MulSiNoOverflowPP() {
    INT result{};
    INT const l{1},r{1};
    ASSERT(not non_builtin_mul_overflow(l, r, &result));
}
void MulSiNoOverflowNP() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{1};
    ASSERT(not non_builtin_mul_overflow(l, r, &result));
}
void MulSiNOOverflowPN() {
    INT result{};
    INT const l{-std::numeric_limits<INT>::max()},r{-1};
    ASSERT(not non_builtin_mul_overflow(l, r, &result));
}
void MulSiOverflowNN() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{-1};
    ASSERT(non_builtin_mul_overflow(l, r, &result));
}
void MulSiOverflowPmaxNmin() {
    INT result{};
    INT const l{-std::numeric_limits<INT>::max()},r{std::numeric_limits<INT>::min()};
    ASSERT(non_builtin_mul_overflow(l, r, &result));
}
void MulSiNoOverflowNminP1() {
    INT result{};
    INT const l{std::numeric_limits<INT>::min()},r{1};
    ASSERT(not non_builtin_mul_overflow(l, r, &result));
}
void MulSiOverflowSqrtMaxplus1() {
    INT result{};
    INT const l{static_cast<INT>(ceil(sqrt(static_cast<long double>(std::numeric_limits<INT>::max())))+1)};
    ASSERT(non_builtin_mul_overflow(l, l, &result));
}
void MulSiOverflowSqrtMaxminus1() {
    INT result{};
    INT const l{static_cast<INT>(sqrt(static_cast<long double>(std::numeric_limits<INT>::max()))-1)};
    ASSERT(not non_builtin_mul_overflow(l, l, &result));
}
};

cute::suite make_suite_NonBuiltInOverflowDetectionTests() {
	cute::suite s { };
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int64_t>, AddSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int64_t>, AddSiOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int64_t>, AddSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int64_t>, AddSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int64_t>, AddSiNoOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int64_t>, AddSiNoOverflowNP));

    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int32_t>, AddSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int32_t>, AddSiOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int32_t>, AddSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int32_t>, AddSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int32_t>, AddSiNoOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int32_t>, AddSiNoOverflowNP));

    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int16_t>, AddSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int16_t>, AddSiOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int16_t>, AddSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int16_t>, AddSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int16_t>, AddSiNoOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int16_t>, AddSiNoOverflowNP));

    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int8_t>, AddSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int8_t>, AddSiOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int8_t>, AddSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int8_t>, AddSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int8_t>, AddSiNoOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedAddOverflow<int8_t>, AddSiNoOverflowNP));

	s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint64_t>, AddUnNoOverflowPP));
	s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint64_t>, AddUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint32_t>, AddUnNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint32_t>, AddUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint16_t>, AddUnNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint16_t>, AddUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint8_t>, AddUnNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testUnSignedAddOverflow<uint8_t>, AddUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int64_t>, SubSiNoOverflowPP));
	s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int64_t>, SubSiOverflowNP));
	s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int64_t>, SubSiOverflowPmaxN));
	s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int64_t>, SubSiNoOverflowNN));
	s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int64_t>, SubSiNoOverflowNPmax));

    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int32_t>, SubSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int32_t>, SubSiOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int32_t>, SubSiOverflowPmaxN));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int32_t>, SubSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int32_t>, SubSiNoOverflowNPmax));

    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int16_t>, SubSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int16_t>, SubSiOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int16_t>, SubSiOverflowPmaxN));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int16_t>, SubSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int16_t>, SubSiNoOverflowNPmax));

    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int8_t>, SubSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int8_t>, SubSiOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int8_t>, SubSiOverflowPmaxN));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int8_t>, SubSiNoOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedSubOverflow<int8_t>, SubSiNoOverflowNPmax));

	s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint64_t>, SubUnNoOverflowPP));
	s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint64_t>, SubUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint32_t>, SubUnNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint32_t>, SubUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint16_t>, SubUnNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint16_t>, SubUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint8_t>, SubUnNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testUnSignedSubOverflow<uint8_t>, SubUnOverflowPP));

    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiNoOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiNOOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiOverflowPmaxNmin));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiNoOverflowNminP1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiOverflowSqrtMaxplus1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int64_t>, MulSiOverflowSqrtMaxminus1));

    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiNoOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiNOOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiOverflowPmaxNmin));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiNoOverflowNminP1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiOverflowSqrtMaxplus1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int32_t>, MulSiOverflowSqrtMaxminus1));

    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiNoOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiNOOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiOverflowPmaxNmin));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiNoOverflowNminP1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiOverflowSqrtMaxplus1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int16_t>, MulSiOverflowSqrtMaxminus1));

    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiNoOverflowPP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiNoOverflowNP));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiNOOverflowPN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiOverflowNN));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiOverflowPmaxNmin));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiNoOverflowNminP1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiOverflowSqrtMaxplus1));
    s.push_back(CUTE_SMEMFUN(testSignedMulOverflow<int8_t>, MulSiOverflowSqrtMaxminus1));
	return s;
}
