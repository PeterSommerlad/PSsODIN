#include "odins.h"

// this file content is generated
// it tests all numeric limits members of all integer replacement types against their corresponding underlying types

/* File: ../generatenumericlmitstests.sh
#!/bin/sh

for safeint in csi8 csi16 csi32 csi64 cui8 cui16 cui32 cui64
do

for func in min max lowest epsilon round_error infinity quiet_NaN signaling_NaN denorm_min
do
  echo "static_assert(std::numeric_limits<$safeint>::$func() == from_int(std::numeric_limits<ULT<$safeint>>::$func()) );"


done

for variable in is_specialized digits digits10 max_digits10 is_signed is_integer is_exact radix min_exponent min_exponent10 max_exponent max_exponent10 \
                has_infinity has_quiet_NaN has_signaling_NaN has_denorm has_denorm_loss is_iec559 is_bounded tinyness_before round_style
do
  echo "static_assert(std::numeric_limits<$safeint>::$variable == std::numeric_limits<ULT<$safeint>>::$variable);"

done

  echo "static_assert(not std::numeric_limits<$safeint>::traps);"
  echo "static_assert(not std::numeric_limits<$safeint>::is_modulo);"

done

*/
using namespace odins;

static_assert(std::numeric_limits<csi8>::min() == from_int(std::numeric_limits<ULT<csi8>>::min()) );
static_assert(std::numeric_limits<csi8>::max() == from_int(std::numeric_limits<ULT<csi8>>::max()) );
static_assert(std::numeric_limits<csi8>::lowest() == from_int(std::numeric_limits<ULT<csi8>>::lowest()) );
static_assert(std::numeric_limits<csi8>::epsilon() == from_int(std::numeric_limits<ULT<csi8>>::epsilon()) );
static_assert(std::numeric_limits<csi8>::round_error() == from_int(std::numeric_limits<ULT<csi8>>::round_error()) );
static_assert(std::numeric_limits<csi8>::infinity() == from_int(std::numeric_limits<ULT<csi8>>::infinity()) );
static_assert(std::numeric_limits<csi8>::quiet_NaN() == from_int(std::numeric_limits<ULT<csi8>>::quiet_NaN()) );
static_assert(std::numeric_limits<csi8>::signaling_NaN() == from_int(std::numeric_limits<ULT<csi8>>::signaling_NaN()) );
static_assert(std::numeric_limits<csi8>::denorm_min() == from_int(std::numeric_limits<ULT<csi8>>::denorm_min()) );
static_assert(std::numeric_limits<csi8>::is_specialized == std::numeric_limits<ULT<csi8>>::is_specialized);
static_assert(std::numeric_limits<csi8>::digits == std::numeric_limits<ULT<csi8>>::digits);
static_assert(std::numeric_limits<csi8>::digits10 == std::numeric_limits<ULT<csi8>>::digits10);
static_assert(std::numeric_limits<csi8>::max_digits10 == std::numeric_limits<ULT<csi8>>::max_digits10);
static_assert(std::numeric_limits<csi8>::is_signed == std::numeric_limits<ULT<csi8>>::is_signed);
static_assert(std::numeric_limits<csi8>::is_integer == std::numeric_limits<ULT<csi8>>::is_integer);
static_assert(std::numeric_limits<csi8>::is_exact == std::numeric_limits<ULT<csi8>>::is_exact);
static_assert(std::numeric_limits<csi8>::radix == std::numeric_limits<ULT<csi8>>::radix);
static_assert(std::numeric_limits<csi8>::min_exponent == std::numeric_limits<ULT<csi8>>::min_exponent);
static_assert(std::numeric_limits<csi8>::min_exponent10 == std::numeric_limits<ULT<csi8>>::min_exponent10);
static_assert(std::numeric_limits<csi8>::max_exponent == std::numeric_limits<ULT<csi8>>::max_exponent);
static_assert(std::numeric_limits<csi8>::max_exponent10 == std::numeric_limits<ULT<csi8>>::max_exponent10);
static_assert(std::numeric_limits<csi8>::has_infinity == std::numeric_limits<ULT<csi8>>::has_infinity);
static_assert(std::numeric_limits<csi8>::has_quiet_NaN == std::numeric_limits<ULT<csi8>>::has_quiet_NaN);
static_assert(std::numeric_limits<csi8>::has_signaling_NaN == std::numeric_limits<ULT<csi8>>::has_signaling_NaN);
static_assert(std::numeric_limits<csi8>::has_denorm == std::numeric_limits<ULT<csi8>>::has_denorm);
static_assert(std::numeric_limits<csi8>::has_denorm_loss == std::numeric_limits<ULT<csi8>>::has_denorm_loss);
static_assert(std::numeric_limits<csi8>::is_iec559 == std::numeric_limits<ULT<csi8>>::is_iec559);
static_assert(std::numeric_limits<csi8>::is_bounded == std::numeric_limits<ULT<csi8>>::is_bounded);
static_assert(std::numeric_limits<csi8>::tinyness_before == std::numeric_limits<ULT<csi8>>::tinyness_before);
static_assert(std::numeric_limits<csi8>::round_style == std::numeric_limits<ULT<csi8>>::round_style);
static_assert(not std::numeric_limits<csi8>::traps);
static_assert(not std::numeric_limits<csi8>::is_modulo);
static_assert(std::numeric_limits<csi16>::min() == from_int(std::numeric_limits<ULT<csi16>>::min()) );
static_assert(std::numeric_limits<csi16>::max() == from_int(std::numeric_limits<ULT<csi16>>::max()) );
static_assert(std::numeric_limits<csi16>::lowest() == from_int(std::numeric_limits<ULT<csi16>>::lowest()) );
static_assert(std::numeric_limits<csi16>::epsilon() == from_int(std::numeric_limits<ULT<csi16>>::epsilon()) );
static_assert(std::numeric_limits<csi16>::round_error() == from_int(std::numeric_limits<ULT<csi16>>::round_error()) );
static_assert(std::numeric_limits<csi16>::infinity() == from_int(std::numeric_limits<ULT<csi16>>::infinity()) );
static_assert(std::numeric_limits<csi16>::quiet_NaN() == from_int(std::numeric_limits<ULT<csi16>>::quiet_NaN()) );
static_assert(std::numeric_limits<csi16>::signaling_NaN() == from_int(std::numeric_limits<ULT<csi16>>::signaling_NaN()) );
static_assert(std::numeric_limits<csi16>::denorm_min() == from_int(std::numeric_limits<ULT<csi16>>::denorm_min()) );
static_assert(std::numeric_limits<csi16>::is_specialized == std::numeric_limits<ULT<csi16>>::is_specialized);
static_assert(std::numeric_limits<csi16>::digits == std::numeric_limits<ULT<csi16>>::digits);
static_assert(std::numeric_limits<csi16>::digits10 == std::numeric_limits<ULT<csi16>>::digits10);
static_assert(std::numeric_limits<csi16>::max_digits10 == std::numeric_limits<ULT<csi16>>::max_digits10);
static_assert(std::numeric_limits<csi16>::is_signed == std::numeric_limits<ULT<csi16>>::is_signed);
static_assert(std::numeric_limits<csi16>::is_integer == std::numeric_limits<ULT<csi16>>::is_integer);
static_assert(std::numeric_limits<csi16>::is_exact == std::numeric_limits<ULT<csi16>>::is_exact);
static_assert(std::numeric_limits<csi16>::radix == std::numeric_limits<ULT<csi16>>::radix);
static_assert(std::numeric_limits<csi16>::min_exponent == std::numeric_limits<ULT<csi16>>::min_exponent);
static_assert(std::numeric_limits<csi16>::min_exponent10 == std::numeric_limits<ULT<csi16>>::min_exponent10);
static_assert(std::numeric_limits<csi16>::max_exponent == std::numeric_limits<ULT<csi16>>::max_exponent);
static_assert(std::numeric_limits<csi16>::max_exponent10 == std::numeric_limits<ULT<csi16>>::max_exponent10);
static_assert(std::numeric_limits<csi16>::has_infinity == std::numeric_limits<ULT<csi16>>::has_infinity);
static_assert(std::numeric_limits<csi16>::has_quiet_NaN == std::numeric_limits<ULT<csi16>>::has_quiet_NaN);
static_assert(std::numeric_limits<csi16>::has_signaling_NaN == std::numeric_limits<ULT<csi16>>::has_signaling_NaN);
static_assert(std::numeric_limits<csi16>::has_denorm == std::numeric_limits<ULT<csi16>>::has_denorm);
static_assert(std::numeric_limits<csi16>::has_denorm_loss == std::numeric_limits<ULT<csi16>>::has_denorm_loss);
static_assert(std::numeric_limits<csi16>::is_iec559 == std::numeric_limits<ULT<csi16>>::is_iec559);
static_assert(std::numeric_limits<csi16>::is_bounded == std::numeric_limits<ULT<csi16>>::is_bounded);
static_assert(std::numeric_limits<csi16>::tinyness_before == std::numeric_limits<ULT<csi16>>::tinyness_before);
static_assert(std::numeric_limits<csi16>::round_style == std::numeric_limits<ULT<csi16>>::round_style);
static_assert(not std::numeric_limits<csi16>::traps);
static_assert(not std::numeric_limits<csi16>::is_modulo);
static_assert(std::numeric_limits<csi32>::min() == from_int(std::numeric_limits<ULT<csi32>>::min()) );
static_assert(std::numeric_limits<csi32>::max() == from_int(std::numeric_limits<ULT<csi32>>::max()) );
static_assert(std::numeric_limits<csi32>::lowest() == from_int(std::numeric_limits<ULT<csi32>>::lowest()) );
static_assert(std::numeric_limits<csi32>::epsilon() == from_int(std::numeric_limits<ULT<csi32>>::epsilon()) );
static_assert(std::numeric_limits<csi32>::round_error() == from_int(std::numeric_limits<ULT<csi32>>::round_error()) );
static_assert(std::numeric_limits<csi32>::infinity() == from_int(std::numeric_limits<ULT<csi32>>::infinity()) );
static_assert(std::numeric_limits<csi32>::quiet_NaN() == from_int(std::numeric_limits<ULT<csi32>>::quiet_NaN()) );
static_assert(std::numeric_limits<csi32>::signaling_NaN() == from_int(std::numeric_limits<ULT<csi32>>::signaling_NaN()) );
static_assert(std::numeric_limits<csi32>::denorm_min() == from_int(std::numeric_limits<ULT<csi32>>::denorm_min()) );
static_assert(std::numeric_limits<csi32>::is_specialized == std::numeric_limits<ULT<csi32>>::is_specialized);
static_assert(std::numeric_limits<csi32>::digits == std::numeric_limits<ULT<csi32>>::digits);
static_assert(std::numeric_limits<csi32>::digits10 == std::numeric_limits<ULT<csi32>>::digits10);
static_assert(std::numeric_limits<csi32>::max_digits10 == std::numeric_limits<ULT<csi32>>::max_digits10);
static_assert(std::numeric_limits<csi32>::is_signed == std::numeric_limits<ULT<csi32>>::is_signed);
static_assert(std::numeric_limits<csi32>::is_integer == std::numeric_limits<ULT<csi32>>::is_integer);
static_assert(std::numeric_limits<csi32>::is_exact == std::numeric_limits<ULT<csi32>>::is_exact);
static_assert(std::numeric_limits<csi32>::radix == std::numeric_limits<ULT<csi32>>::radix);
static_assert(std::numeric_limits<csi32>::min_exponent == std::numeric_limits<ULT<csi32>>::min_exponent);
static_assert(std::numeric_limits<csi32>::min_exponent10 == std::numeric_limits<ULT<csi32>>::min_exponent10);
static_assert(std::numeric_limits<csi32>::max_exponent == std::numeric_limits<ULT<csi32>>::max_exponent);
static_assert(std::numeric_limits<csi32>::max_exponent10 == std::numeric_limits<ULT<csi32>>::max_exponent10);
static_assert(std::numeric_limits<csi32>::has_infinity == std::numeric_limits<ULT<csi32>>::has_infinity);
static_assert(std::numeric_limits<csi32>::has_quiet_NaN == std::numeric_limits<ULT<csi32>>::has_quiet_NaN);
static_assert(std::numeric_limits<csi32>::has_signaling_NaN == std::numeric_limits<ULT<csi32>>::has_signaling_NaN);
static_assert(std::numeric_limits<csi32>::has_denorm == std::numeric_limits<ULT<csi32>>::has_denorm);
static_assert(std::numeric_limits<csi32>::has_denorm_loss == std::numeric_limits<ULT<csi32>>::has_denorm_loss);
static_assert(std::numeric_limits<csi32>::is_iec559 == std::numeric_limits<ULT<csi32>>::is_iec559);
static_assert(std::numeric_limits<csi32>::is_bounded == std::numeric_limits<ULT<csi32>>::is_bounded);
static_assert(std::numeric_limits<csi32>::tinyness_before == std::numeric_limits<ULT<csi32>>::tinyness_before);
static_assert(std::numeric_limits<csi32>::round_style == std::numeric_limits<ULT<csi32>>::round_style);
static_assert(not std::numeric_limits<csi32>::traps);
static_assert(not std::numeric_limits<csi32>::is_modulo);
static_assert(std::numeric_limits<csi64>::min() == from_int(std::numeric_limits<ULT<csi64>>::min()) );
static_assert(std::numeric_limits<csi64>::max() == from_int(std::numeric_limits<ULT<csi64>>::max()) );
static_assert(std::numeric_limits<csi64>::lowest() == from_int(std::numeric_limits<ULT<csi64>>::lowest()) );
static_assert(std::numeric_limits<csi64>::epsilon() == from_int(std::numeric_limits<ULT<csi64>>::epsilon()) );
static_assert(std::numeric_limits<csi64>::round_error() == from_int(std::numeric_limits<ULT<csi64>>::round_error()) );
static_assert(std::numeric_limits<csi64>::infinity() == from_int(std::numeric_limits<ULT<csi64>>::infinity()) );
static_assert(std::numeric_limits<csi64>::quiet_NaN() == from_int(std::numeric_limits<ULT<csi64>>::quiet_NaN()) );
static_assert(std::numeric_limits<csi64>::signaling_NaN() == from_int(std::numeric_limits<ULT<csi64>>::signaling_NaN()) );
static_assert(std::numeric_limits<csi64>::denorm_min() == from_int(std::numeric_limits<ULT<csi64>>::denorm_min()) );
static_assert(std::numeric_limits<csi64>::is_specialized == std::numeric_limits<ULT<csi64>>::is_specialized);
static_assert(std::numeric_limits<csi64>::digits == std::numeric_limits<ULT<csi64>>::digits);
static_assert(std::numeric_limits<csi64>::digits10 == std::numeric_limits<ULT<csi64>>::digits10);
static_assert(std::numeric_limits<csi64>::max_digits10 == std::numeric_limits<ULT<csi64>>::max_digits10);
static_assert(std::numeric_limits<csi64>::is_signed == std::numeric_limits<ULT<csi64>>::is_signed);
static_assert(std::numeric_limits<csi64>::is_integer == std::numeric_limits<ULT<csi64>>::is_integer);
static_assert(std::numeric_limits<csi64>::is_exact == std::numeric_limits<ULT<csi64>>::is_exact);
static_assert(std::numeric_limits<csi64>::radix == std::numeric_limits<ULT<csi64>>::radix);
static_assert(std::numeric_limits<csi64>::min_exponent == std::numeric_limits<ULT<csi64>>::min_exponent);
static_assert(std::numeric_limits<csi64>::min_exponent10 == std::numeric_limits<ULT<csi64>>::min_exponent10);
static_assert(std::numeric_limits<csi64>::max_exponent == std::numeric_limits<ULT<csi64>>::max_exponent);
static_assert(std::numeric_limits<csi64>::max_exponent10 == std::numeric_limits<ULT<csi64>>::max_exponent10);
static_assert(std::numeric_limits<csi64>::has_infinity == std::numeric_limits<ULT<csi64>>::has_infinity);
static_assert(std::numeric_limits<csi64>::has_quiet_NaN == std::numeric_limits<ULT<csi64>>::has_quiet_NaN);
static_assert(std::numeric_limits<csi64>::has_signaling_NaN == std::numeric_limits<ULT<csi64>>::has_signaling_NaN);
static_assert(std::numeric_limits<csi64>::has_denorm == std::numeric_limits<ULT<csi64>>::has_denorm);
static_assert(std::numeric_limits<csi64>::has_denorm_loss == std::numeric_limits<ULT<csi64>>::has_denorm_loss);
static_assert(std::numeric_limits<csi64>::is_iec559 == std::numeric_limits<ULT<csi64>>::is_iec559);
static_assert(std::numeric_limits<csi64>::is_bounded == std::numeric_limits<ULT<csi64>>::is_bounded);
static_assert(std::numeric_limits<csi64>::tinyness_before == std::numeric_limits<ULT<csi64>>::tinyness_before);
static_assert(std::numeric_limits<csi64>::round_style == std::numeric_limits<ULT<csi64>>::round_style);
static_assert(not std::numeric_limits<csi64>::traps);
static_assert(not std::numeric_limits<csi64>::is_modulo);
static_assert(std::numeric_limits<cui8>::min() == from_int(std::numeric_limits<ULT<cui8>>::min()) );
static_assert(std::numeric_limits<cui8>::max() == from_int(std::numeric_limits<ULT<cui8>>::max()) );
static_assert(std::numeric_limits<cui8>::lowest() == from_int(std::numeric_limits<ULT<cui8>>::lowest()) );
static_assert(std::numeric_limits<cui8>::epsilon() == from_int(std::numeric_limits<ULT<cui8>>::epsilon()) );
static_assert(std::numeric_limits<cui8>::round_error() == from_int(std::numeric_limits<ULT<cui8>>::round_error()) );
static_assert(std::numeric_limits<cui8>::infinity() == from_int(std::numeric_limits<ULT<cui8>>::infinity()) );
static_assert(std::numeric_limits<cui8>::quiet_NaN() == from_int(std::numeric_limits<ULT<cui8>>::quiet_NaN()) );
static_assert(std::numeric_limits<cui8>::signaling_NaN() == from_int(std::numeric_limits<ULT<cui8>>::signaling_NaN()) );
static_assert(std::numeric_limits<cui8>::denorm_min() == from_int(std::numeric_limits<ULT<cui8>>::denorm_min()) );
static_assert(std::numeric_limits<cui8>::is_specialized == std::numeric_limits<ULT<cui8>>::is_specialized);
static_assert(std::numeric_limits<cui8>::digits == std::numeric_limits<ULT<cui8>>::digits);
static_assert(std::numeric_limits<cui8>::digits10 == std::numeric_limits<ULT<cui8>>::digits10);
static_assert(std::numeric_limits<cui8>::max_digits10 == std::numeric_limits<ULT<cui8>>::max_digits10);
static_assert(std::numeric_limits<cui8>::is_signed == std::numeric_limits<ULT<cui8>>::is_signed);
static_assert(std::numeric_limits<cui8>::is_integer == std::numeric_limits<ULT<cui8>>::is_integer);
static_assert(std::numeric_limits<cui8>::is_exact == std::numeric_limits<ULT<cui8>>::is_exact);
static_assert(std::numeric_limits<cui8>::radix == std::numeric_limits<ULT<cui8>>::radix);
static_assert(std::numeric_limits<cui8>::min_exponent == std::numeric_limits<ULT<cui8>>::min_exponent);
static_assert(std::numeric_limits<cui8>::min_exponent10 == std::numeric_limits<ULT<cui8>>::min_exponent10);
static_assert(std::numeric_limits<cui8>::max_exponent == std::numeric_limits<ULT<cui8>>::max_exponent);
static_assert(std::numeric_limits<cui8>::max_exponent10 == std::numeric_limits<ULT<cui8>>::max_exponent10);
static_assert(std::numeric_limits<cui8>::has_infinity == std::numeric_limits<ULT<cui8>>::has_infinity);
static_assert(std::numeric_limits<cui8>::has_quiet_NaN == std::numeric_limits<ULT<cui8>>::has_quiet_NaN);
static_assert(std::numeric_limits<cui8>::has_signaling_NaN == std::numeric_limits<ULT<cui8>>::has_signaling_NaN);
static_assert(std::numeric_limits<cui8>::has_denorm == std::numeric_limits<ULT<cui8>>::has_denorm);
static_assert(std::numeric_limits<cui8>::has_denorm_loss == std::numeric_limits<ULT<cui8>>::has_denorm_loss);
static_assert(std::numeric_limits<cui8>::is_iec559 == std::numeric_limits<ULT<cui8>>::is_iec559);
static_assert(std::numeric_limits<cui8>::is_bounded == std::numeric_limits<ULT<cui8>>::is_bounded);
static_assert(std::numeric_limits<cui8>::tinyness_before == std::numeric_limits<ULT<cui8>>::tinyness_before);
static_assert(std::numeric_limits<cui8>::round_style == std::numeric_limits<ULT<cui8>>::round_style);
static_assert(not std::numeric_limits<cui8>::traps);
static_assert(not std::numeric_limits<cui8>::is_modulo);
static_assert(std::numeric_limits<cui16>::min() == from_int(std::numeric_limits<ULT<cui16>>::min()) );
static_assert(std::numeric_limits<cui16>::max() == from_int(std::numeric_limits<ULT<cui16>>::max()) );
static_assert(std::numeric_limits<cui16>::lowest() == from_int(std::numeric_limits<ULT<cui16>>::lowest()) );
static_assert(std::numeric_limits<cui16>::epsilon() == from_int(std::numeric_limits<ULT<cui16>>::epsilon()) );
static_assert(std::numeric_limits<cui16>::round_error() == from_int(std::numeric_limits<ULT<cui16>>::round_error()) );
static_assert(std::numeric_limits<cui16>::infinity() == from_int(std::numeric_limits<ULT<cui16>>::infinity()) );
static_assert(std::numeric_limits<cui16>::quiet_NaN() == from_int(std::numeric_limits<ULT<cui16>>::quiet_NaN()) );
static_assert(std::numeric_limits<cui16>::signaling_NaN() == from_int(std::numeric_limits<ULT<cui16>>::signaling_NaN()) );
static_assert(std::numeric_limits<cui16>::denorm_min() == from_int(std::numeric_limits<ULT<cui16>>::denorm_min()) );
static_assert(std::numeric_limits<cui16>::is_specialized == std::numeric_limits<ULT<cui16>>::is_specialized);
static_assert(std::numeric_limits<cui16>::digits == std::numeric_limits<ULT<cui16>>::digits);
static_assert(std::numeric_limits<cui16>::digits10 == std::numeric_limits<ULT<cui16>>::digits10);
static_assert(std::numeric_limits<cui16>::max_digits10 == std::numeric_limits<ULT<cui16>>::max_digits10);
static_assert(std::numeric_limits<cui16>::is_signed == std::numeric_limits<ULT<cui16>>::is_signed);
static_assert(std::numeric_limits<cui16>::is_integer == std::numeric_limits<ULT<cui16>>::is_integer);
static_assert(std::numeric_limits<cui16>::is_exact == std::numeric_limits<ULT<cui16>>::is_exact);
static_assert(std::numeric_limits<cui16>::radix == std::numeric_limits<ULT<cui16>>::radix);
static_assert(std::numeric_limits<cui16>::min_exponent == std::numeric_limits<ULT<cui16>>::min_exponent);
static_assert(std::numeric_limits<cui16>::min_exponent10 == std::numeric_limits<ULT<cui16>>::min_exponent10);
static_assert(std::numeric_limits<cui16>::max_exponent == std::numeric_limits<ULT<cui16>>::max_exponent);
static_assert(std::numeric_limits<cui16>::max_exponent10 == std::numeric_limits<ULT<cui16>>::max_exponent10);
static_assert(std::numeric_limits<cui16>::has_infinity == std::numeric_limits<ULT<cui16>>::has_infinity);
static_assert(std::numeric_limits<cui16>::has_quiet_NaN == std::numeric_limits<ULT<cui16>>::has_quiet_NaN);
static_assert(std::numeric_limits<cui16>::has_signaling_NaN == std::numeric_limits<ULT<cui16>>::has_signaling_NaN);
static_assert(std::numeric_limits<cui16>::has_denorm == std::numeric_limits<ULT<cui16>>::has_denorm);
static_assert(std::numeric_limits<cui16>::has_denorm_loss == std::numeric_limits<ULT<cui16>>::has_denorm_loss);
static_assert(std::numeric_limits<cui16>::is_iec559 == std::numeric_limits<ULT<cui16>>::is_iec559);
static_assert(std::numeric_limits<cui16>::is_bounded == std::numeric_limits<ULT<cui16>>::is_bounded);
static_assert(std::numeric_limits<cui16>::tinyness_before == std::numeric_limits<ULT<cui16>>::tinyness_before);
static_assert(std::numeric_limits<cui16>::round_style == std::numeric_limits<ULT<cui16>>::round_style);
static_assert(not std::numeric_limits<cui16>::traps);
static_assert(not std::numeric_limits<cui16>::is_modulo);
static_assert(std::numeric_limits<cui32>::min() == from_int(std::numeric_limits<ULT<cui32>>::min()) );
static_assert(std::numeric_limits<cui32>::max() == from_int(std::numeric_limits<ULT<cui32>>::max()) );
static_assert(std::numeric_limits<cui32>::lowest() == from_int(std::numeric_limits<ULT<cui32>>::lowest()) );
static_assert(std::numeric_limits<cui32>::epsilon() == from_int(std::numeric_limits<ULT<cui32>>::epsilon()) );
static_assert(std::numeric_limits<cui32>::round_error() == from_int(std::numeric_limits<ULT<cui32>>::round_error()) );
static_assert(std::numeric_limits<cui32>::infinity() == from_int(std::numeric_limits<ULT<cui32>>::infinity()) );
static_assert(std::numeric_limits<cui32>::quiet_NaN() == from_int(std::numeric_limits<ULT<cui32>>::quiet_NaN()) );
static_assert(std::numeric_limits<cui32>::signaling_NaN() == from_int(std::numeric_limits<ULT<cui32>>::signaling_NaN()) );
static_assert(std::numeric_limits<cui32>::denorm_min() == from_int(std::numeric_limits<ULT<cui32>>::denorm_min()) );
static_assert(std::numeric_limits<cui32>::is_specialized == std::numeric_limits<ULT<cui32>>::is_specialized);
static_assert(std::numeric_limits<cui32>::digits == std::numeric_limits<ULT<cui32>>::digits);
static_assert(std::numeric_limits<cui32>::digits10 == std::numeric_limits<ULT<cui32>>::digits10);
static_assert(std::numeric_limits<cui32>::max_digits10 == std::numeric_limits<ULT<cui32>>::max_digits10);
static_assert(std::numeric_limits<cui32>::is_signed == std::numeric_limits<ULT<cui32>>::is_signed);
static_assert(std::numeric_limits<cui32>::is_integer == std::numeric_limits<ULT<cui32>>::is_integer);
static_assert(std::numeric_limits<cui32>::is_exact == std::numeric_limits<ULT<cui32>>::is_exact);
static_assert(std::numeric_limits<cui32>::radix == std::numeric_limits<ULT<cui32>>::radix);
static_assert(std::numeric_limits<cui32>::min_exponent == std::numeric_limits<ULT<cui32>>::min_exponent);
static_assert(std::numeric_limits<cui32>::min_exponent10 == std::numeric_limits<ULT<cui32>>::min_exponent10);
static_assert(std::numeric_limits<cui32>::max_exponent == std::numeric_limits<ULT<cui32>>::max_exponent);
static_assert(std::numeric_limits<cui32>::max_exponent10 == std::numeric_limits<ULT<cui32>>::max_exponent10);
static_assert(std::numeric_limits<cui32>::has_infinity == std::numeric_limits<ULT<cui32>>::has_infinity);
static_assert(std::numeric_limits<cui32>::has_quiet_NaN == std::numeric_limits<ULT<cui32>>::has_quiet_NaN);
static_assert(std::numeric_limits<cui32>::has_signaling_NaN == std::numeric_limits<ULT<cui32>>::has_signaling_NaN);
static_assert(std::numeric_limits<cui32>::has_denorm == std::numeric_limits<ULT<cui32>>::has_denorm);
static_assert(std::numeric_limits<cui32>::has_denorm_loss == std::numeric_limits<ULT<cui32>>::has_denorm_loss);
static_assert(std::numeric_limits<cui32>::is_iec559 == std::numeric_limits<ULT<cui32>>::is_iec559);
static_assert(std::numeric_limits<cui32>::is_bounded == std::numeric_limits<ULT<cui32>>::is_bounded);
static_assert(std::numeric_limits<cui32>::tinyness_before == std::numeric_limits<ULT<cui32>>::tinyness_before);
static_assert(std::numeric_limits<cui32>::round_style == std::numeric_limits<ULT<cui32>>::round_style);
static_assert(not std::numeric_limits<cui32>::traps);
static_assert(not std::numeric_limits<cui32>::is_modulo);
static_assert(std::numeric_limits<cui64>::min() == from_int(std::numeric_limits<ULT<cui64>>::min()) );
static_assert(std::numeric_limits<cui64>::max() == from_int(std::numeric_limits<ULT<cui64>>::max()) );
static_assert(std::numeric_limits<cui64>::lowest() == from_int(std::numeric_limits<ULT<cui64>>::lowest()) );
static_assert(std::numeric_limits<cui64>::epsilon() == from_int(std::numeric_limits<ULT<cui64>>::epsilon()) );
static_assert(std::numeric_limits<cui64>::round_error() == from_int(std::numeric_limits<ULT<cui64>>::round_error()) );
static_assert(std::numeric_limits<cui64>::infinity() == from_int(std::numeric_limits<ULT<cui64>>::infinity()) );
static_assert(std::numeric_limits<cui64>::quiet_NaN() == from_int(std::numeric_limits<ULT<cui64>>::quiet_NaN()) );
static_assert(std::numeric_limits<cui64>::signaling_NaN() == from_int(std::numeric_limits<ULT<cui64>>::signaling_NaN()) );
static_assert(std::numeric_limits<cui64>::denorm_min() == from_int(std::numeric_limits<ULT<cui64>>::denorm_min()) );
static_assert(std::numeric_limits<cui64>::is_specialized == std::numeric_limits<ULT<cui64>>::is_specialized);
static_assert(std::numeric_limits<cui64>::digits == std::numeric_limits<ULT<cui64>>::digits);
static_assert(std::numeric_limits<cui64>::digits10 == std::numeric_limits<ULT<cui64>>::digits10);
static_assert(std::numeric_limits<cui64>::max_digits10 == std::numeric_limits<ULT<cui64>>::max_digits10);
static_assert(std::numeric_limits<cui64>::is_signed == std::numeric_limits<ULT<cui64>>::is_signed);
static_assert(std::numeric_limits<cui64>::is_integer == std::numeric_limits<ULT<cui64>>::is_integer);
static_assert(std::numeric_limits<cui64>::is_exact == std::numeric_limits<ULT<cui64>>::is_exact);
static_assert(std::numeric_limits<cui64>::radix == std::numeric_limits<ULT<cui64>>::radix);
static_assert(std::numeric_limits<cui64>::min_exponent == std::numeric_limits<ULT<cui64>>::min_exponent);
static_assert(std::numeric_limits<cui64>::min_exponent10 == std::numeric_limits<ULT<cui64>>::min_exponent10);
static_assert(std::numeric_limits<cui64>::max_exponent == std::numeric_limits<ULT<cui64>>::max_exponent);
static_assert(std::numeric_limits<cui64>::max_exponent10 == std::numeric_limits<ULT<cui64>>::max_exponent10);
static_assert(std::numeric_limits<cui64>::has_infinity == std::numeric_limits<ULT<cui64>>::has_infinity);
static_assert(std::numeric_limits<cui64>::has_quiet_NaN == std::numeric_limits<ULT<cui64>>::has_quiet_NaN);
static_assert(std::numeric_limits<cui64>::has_signaling_NaN == std::numeric_limits<ULT<cui64>>::has_signaling_NaN);
static_assert(std::numeric_limits<cui64>::has_denorm == std::numeric_limits<ULT<cui64>>::has_denorm);
static_assert(std::numeric_limits<cui64>::has_denorm_loss == std::numeric_limits<ULT<cui64>>::has_denorm_loss);
static_assert(std::numeric_limits<cui64>::is_iec559 == std::numeric_limits<ULT<cui64>>::is_iec559);
static_assert(std::numeric_limits<cui64>::is_bounded == std::numeric_limits<ULT<cui64>>::is_bounded);
static_assert(std::numeric_limits<cui64>::tinyness_before == std::numeric_limits<ULT<cui64>>::tinyness_before);
static_assert(std::numeric_limits<cui64>::round_style == std::numeric_limits<ULT<cui64>>::round_style);
static_assert(not std::numeric_limits<cui64>::traps);
static_assert(not std::numeric_limits<cui64>::is_modulo);
