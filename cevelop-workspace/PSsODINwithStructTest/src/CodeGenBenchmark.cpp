#include "odins.h"
#include "CodeGenBenchmark.h"
#include "cute.h"
#include <initializer_list>

#include <vector>
#include <numeric>


using namespace odins;


template<typename INT>
struct operations {
    operations(std::initializer_list<INT> seedvalues):values{seedvalues}{};
    std::vector<INT> values;

    auto sum() const {
        auto const initialvalue = INT{0}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue);
    }
    auto product() const {
        auto const initialvalue = INT{1}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue,[](auto l, auto r){return l*r;});
    }
    auto sumthirds() const {
        auto const initialvalue = INT{0}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue,[](auto l, auto r){return l+(r/INT{3});});
    }
    auto sumnegative() const {
        auto const initialvalue = INT{}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue,[](auto l, auto r){return l-r;});
    }
};

std::initializer_list<int8_t> i8_seed{1,1,2,3,5,8/*,13,21,34,55,89*/};
std::initializer_list<csi8> si8_seed{1_csi8,1_csi8,2_csi8,3_csi8,5_csi8,8_csi8/*,13_csi8,21_csi8,34_csi8,55_csi8,89_csi8*/};

auto sum(operations<int8_t> const &ops){
    return ops.sum();
}
auto product(operations<int8_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int8_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int8_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<csi8> const &ops){
    return ops.sum();
}
auto product(operations<csi8> const &ops){
    return ops.product();
}
auto sumthirds(operations<csi8> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<csi8> const &ops){
    return ops.sumnegative();
}




void codegenAdditionTest() {
    auto resi8 = sum(operations<int8_t>{i8_seed});
    auto ressi8 =sum( operations<csi8>{si8_seed});
    ASSERT_EQUAL(resi8,promote_keep_signedness(ressi8));
}

void codegenMultiplicationTest(){
    auto resi8 = product(operations<int8_t>{i8_seed});
//    auto ressi8 = product( operations<si8>{si8_seed});
//    ASSERT_EQUAL(resi8,promote_keep_signedness(ressi8));
//    ASSERT_EQUAL(from_int(resi8),ressi8);
    ASSERTM("expect signed integer overflow not detected by ubsan",resi8 < 0);
//    ASSERTM("expect signed integer overflow not detected by ubsan",ressi8 < 0_csi8);
}
void codegenSumThirdsTest(){
    auto resi8 = sumthirds(operations<int8_t>{i8_seed});
    auto ressi8 = sumthirds( operations<csi8>{si8_seed});
    ASSERT_EQUAL(resi8,promote_keep_signedness(ressi8));
}
void codegenSubtractionTest(){
    auto resi8 = sumnegative(operations<int8_t>{i8_seed});
    auto ressi8 = sumnegative( operations<csi8>{si8_seed});
    ASSERT_EQUAL(resi8,promote_keep_signedness(ressi8));
}

namespace int16 {
std::initializer_list<int16_t> i16_seed{1,1,2,3,5,8,13,21,34,55};
std::initializer_list<csi16> si16_seed{1_csi16,1_csi16,2_csi16,3_csi16,5_csi16,8_csi16,13_csi16,21_csi16,34_csi16,55_csi16};

auto sum(operations<int16_t> const &ops){
    return ops.sum();
}
auto product(operations<int16_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int16_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int16_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<csi16> const &ops){
    return ops.sum();
}
auto product(operations<csi16> const &ops){
    return ops.product();
}
auto sumthirds(operations<csi16> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<csi16> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto resi16 = sum(operations<int16_t>{i16_seed});
    auto ressi16 =sum( operations<csi16>{si16_seed});
    ASSERT_EQUAL(resi16,promote_keep_signedness(ressi16));
}

//#pragma GCC diagnostic push
//#if defined(__GNUG__)
//#if defined(__clang__)
//#pragma clang diagnostic ignored "-Wunused-variable"
//
//#else
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#endif
//#endif


void codegenMultiplicationTest(){
    auto resi16 = product(operations<int16_t>{i16_seed});
ASSERT_THROWS(   [[maybe_unused]] auto ressi16 = product( operations<csi16>{si16_seed}); , char const *);
//    ASSERT_EQUAL(resi16,promote_keep_signedness(ressi16));
//    ASSERT_EQUAL(from_int(resi16),ressi16);
    ASSERTM("expect signed integer overflow not detected by ubsan",resi16 < 0);
//    ASSERTM("expect signed integer overflow not detected by ubsan",ressi16 < 0_csi16);
    // no detection of overflow by UBSAN

}
void codegenSumThirdsTest(){
    auto resi16 = sumthirds(operations<int16_t>{i16_seed});
    auto ressi16 = sumthirds( operations<csi16>{si16_seed});
    ASSERT_EQUAL(resi16,promote_keep_signedness(ressi16));
}
void codegenSubtractionTest(){
    auto resi16 = sumnegative(operations<int16_t>{i16_seed});
    auto ressi16 = sumnegative( operations<csi16>{si16_seed});
    ASSERT_EQUAL(resi16,promote_keep_signedness(ressi16));
}

}
namespace int32 {
std::initializer_list<int32_t> i32_seed{1,1,2,3,5,8,13,21,34,55,89};
std::initializer_list<csi32> si32_seed{1_csi32,1_csi32,2_csi32,3_csi32,5_csi32,8_csi32,13_csi32,21_csi32,34_csi32,55_csi32,89_csi32};

auto sum(operations<int32_t> const &ops){
    return ops.sum();
}
auto product(operations<int32_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int32_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int32_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<csi32> const &ops){
    return ops.sum();
}
auto product(operations<csi32> const &ops){
    return ops.product();
}
auto sumthirds(operations<csi32> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<csi32> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto resi32 = sum(operations<int32_t>{i32_seed});
    auto ressi32 =sum( operations<csi32>{si32_seed});
    ASSERT_EQUAL(resi32,promote_keep_signedness(ressi32));
}

void codegenMultiplicationTest(){
    auto const resi32 = product(operations<int32_t> { i32_seed });
    ASSERT_THROWS([[maybe_unused]] auto ressi32 = product( operations<csi32>{si32_seed}); , char const *);
//    ASSERT_EQUAL(resi32,promote_keep_signedness(ressi32));
//    ASSERT_EQUAL(from_int(resi32),ressi32);
    ASSERTM("expect signed integer overflow detected by ubsan",resi32 < 0);
//    ASSERTM("expect signed integer overflow not detected by ubsan",ressi32 < 0_csi32);
    // ../src/CodeGenBenchmark.cpp:23:99: runtime error: signed integer overflow: 122522400 * 89 cannot be represented in type 'int'

}
void codegenSumThirdsTest(){
    auto resi32 = sumthirds(operations<int32_t>{i32_seed});
    auto ressi32 = sumthirds( operations<csi32>{si32_seed});
    ASSERT_EQUAL(resi32,promote_keep_signedness(ressi32));
}
void codegenSubtractionTest(){
    auto resi32 = sumnegative(operations<int32_t>{i32_seed});
    auto ressi32 = sumnegative( operations<csi32>{si32_seed});
    ASSERT_EQUAL(resi32,promote_keep_signedness(ressi32));
}

}
namespace int64 {
constexpr std::initializer_list<int64_t> i64_seed{1,1,2,3,5,8,13,21,34,55,89,
                                        144,233,377,610};
constexpr std::initializer_list<csi64> si64_seed{1_csi64,1_csi64,2_csi64,3_csi64,5_csi64,8_csi64,13_csi64,21_csi64,34_csi64,55_csi64,89_csi64,
    144_csi64,233_csi64,377_csi64,610_csi64};

auto sum(operations<int64_t> const &ops){
    return ops.sum();
}
auto product(operations<int64_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int64_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int64_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<csi64> const &ops){
    return ops.sum();
}
auto product(operations<csi64> const &ops){
    return ops.product();
}
auto sumthirds(operations<csi64> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<csi64> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto resi64 = sum(operations<int64_t>{i64_seed});
    auto ressi64 =sum( operations<csi64>{si64_seed});
    ASSERT_EQUAL(resi64,promote_keep_signedness(ressi64));
}

void codegenMultiplicationTest(){
    auto resi64 = product(operations<int64_t>{i64_seed});
    ASSERT_THROWS([[maybe_unused]] auto ressi64 = product( operations<csi64>{si64_seed}); , char const *);
//    ASSERT_EQUAL(resi64,promote_keep_signedness(ressi64));
//    ASSERT_EQUAL(from_int(resi64),ressi64);
    ASSERTM("expect signed integer overflow detected by ubsan",resi64 < 0);
//    ASSERTM("expect signed integer overflow not detected by ubsan",ressi64 < 0_csi64);
    // ../src/CodeGenBenchmark.cpp:23:99: runtime error: signed integer overflow: 137932073613734400 * 610 cannot be represented in type 'long long int'

}
void codegenSumThirdsTest(){
    auto resi64 = sumthirds(operations<int64_t>{i64_seed});
    auto ressi64 = sumthirds( operations<csi64>{si64_seed});
    ASSERT_EQUAL(resi64,promote_keep_signedness(ressi64));
}
void codegenSubtractionTest(){
    auto resi64 = sumnegative(operations<int64_t>{i64_seed});
    auto ressi64 = sumnegative( operations<csi64>{si64_seed});
    ASSERT_EQUAL(resi64,promote_keep_signedness(ressi64));
}

}
namespace uint32 {
std::initializer_list<uint32_t> ui32_seed{1,1,2,3,5,8,13,21,34,55,89};
std::initializer_list<cui32> uui32_seed{1_cui32,1_cui32,2_cui32,3_cui32,5_cui32,8_cui32,13_cui32,21_cui32,34_cui32,55_cui32,89_cui32};

auto sum(operations<uint32_t> const &ops){
    return ops.sum();
}
auto product(operations<uint32_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<uint32_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<uint32_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<cui32> const &ops){
    return ops.sum();
}
auto product(operations<cui32> const &ops){
    return ops.product();
}
auto sumthirds(operations<cui32> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<cui32> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto reui32 = sum(operations<uint32_t>{ui32_seed});
    auto resui32 =sum( operations<cui32>{uui32_seed});
    ASSERT_EQUAL(reui32,promote_keep_signedness(resui32));
}

void codegenMultiplicationTest(){
    [[maybe_unused]] auto reui32 = product(operations<uint32_t>{ui32_seed});
    ASSERT_THROWS([[maybe_unused]] auto resui32 = product( operations<cui32>{uui32_seed}); , char const *);
    //ASSERT_EQUAL(reui32,promote_keep_signedness(resui32));
}
void codegenSumThirdsTest(){
    auto reui32 = sumthirds(operations<uint32_t>{ui32_seed});
    auto resui32 = sumthirds( operations<cui32>{uui32_seed});
    ASSERT_EQUAL(reui32,promote_keep_signedness(resui32));
}
void codegenSubtractionTest(){
    [[maybe_unused]] auto reui32 = sumnegative(operations<uint32_t>{ui32_seed});
    ASSERT_THROWS([[maybe_unused]] auto resui32 = sumnegative( operations<cui32>{uui32_seed}); , char const *);
//    ASSERT_EQUAL(reui32,promote_keep_signedness(resui32));
}

}


void testUBSanWithSignedOverflow(){
	unsigned short x=0xffffu;

	auto y = x * x; // UBSAN: ../src/CodeGenBenchmark.cpp:46:13: runtime error: signed integer overflow: 65535 * 65535 cannot be represented in type 'int'

	ASSERT_EQUAL(0xffffu*0xffffu,y);
}


void testUnSignedOverflowThrows(){
    auto x=0xffff_cui16;

    ASSERT_THROWS(std::ignore = x * x, char const *);

}


cute::suite make_suite_CodeGenBenchmark() {
	cute::suite s { };
	s.push_back(CUTE(codegenAdditionTest));
	s.push_back(CUTE(testUBSanWithSignedOverflow));
	s.push_back(CUTE(testUnSignedOverflowThrows));
	s.push_back(CUTE(codegenMultiplicationTest));
	s.push_back(CUTE(codegenSumThirdsTest));
	s.push_back(CUTE(codegenSubtractionTest));
	s.push_back(CUTE(int32::codegenAdditionTest));
	s.push_back(CUTE(int32::codegenMultiplicationTest));
	s.push_back(CUTE(int32::codegenSumThirdsTest));
	s.push_back(CUTE(int32::codegenSubtractionTest));
	s.push_back(CUTE(uint32::codegenAdditionTest));
	s.push_back(CUTE(uint32::codegenMultiplicationTest));
	s.push_back(CUTE(uint32::codegenSumThirdsTest));
	s.push_back(CUTE(uint32::codegenSubtractionTest));
	s.push_back(CUTE(int16::codegenAdditionTest));
	s.push_back(CUTE(int16::codegenMultiplicationTest));
	s.push_back(CUTE(int16::codegenSumThirdsTest));
	s.push_back(CUTE(int16::codegenSubtractionTest));
	s.push_back(CUTE(int64::codegenAdditionTest));
	s.push_back(CUTE(int64::codegenMultiplicationTest));
	s.push_back(CUTE(int64::codegenSumThirdsTest));
	s.push_back(CUTE(int64::codegenSubtractionTest));
	return s;
}
