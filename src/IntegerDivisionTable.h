#ifndef HALIDE_INTEGER_DIVISION_TABLE_H
#define HALIDE_INTEGER_DIVISION_TABLE_H

#include <cstdint>

/** \file
 * Tables telling us how to do integer division via fixed-point
 * multiplication for various small constants. This file is 
 * automatically generated by find_inverse.cpp.
 */
namespace Halide {
namespace Internal {
namespace IntegerDivision {
extern const int64_t table_u8[256][4];
extern const int64_t table_s8[256][4];
extern const int64_t table_srz8[256][4];
extern const int64_t table_u16[256][4];
extern const int64_t table_s16[256][4];
extern const int64_t table_srz16[256][4];
extern const int64_t table_u32[256][4];
extern const int64_t table_s32[256][4];
extern const int64_t table_srz32[256][4];
extern const int64_t table_runtime_u8[256][4];
extern const int64_t table_runtime_s8[256][4];
extern const int64_t table_runtime_srz8[256][4];
extern const int64_t table_runtime_u16[256][4];
extern const int64_t table_runtime_s16[256][4];
extern const int64_t table_runtime_srz16[256][4];
extern const int64_t table_runtime_u32[256][4];
extern const int64_t table_runtime_s32[256][4];
extern const int64_t table_runtime_srz32[256][4];
}
}
}

#endif
