#include <algorithm>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int64_t r(int64_t min, int64_t max) {
    int64_t n1 = rand();
    int64_t n2 = rand();
    int64_t n3 = rand();
    n1 = n1 ^ (n2 << 16) ^ (n3 << 16);
    n1 = n1 % (max - min);
    n1 = n1 + min;
    return n1;
}

int64_t sdiv(int64_t a, int64_t b) {
    return (a - ((a % b) + b) % b) / b;
}

int64_t srzdiv(int64_t a, int64_t b) {
    return a / b;
}

bool u_method_0(int den, int sh_post, int bits) {
    uint64_t max = (1L << bits) - 1;
    // for (int64_t num = 0; num <= max; num++) {
    for (unsigned iter = 0; iter < 1000000UL; iter++) {
        uint64_t num = r(0, max);
        // Make sure we hit the extremes
        if (iter == 0) num = 0;
        if (iter == 1) num = max;
        uint64_t result = num;
        result >>= sh_post;
        if (num / den != result) return false;
    }
    return true;
}

bool u_method_1(int den, int64_t mul, int sh_post, int bits) {
    uint64_t max = (1L << bits) - 1;
    if (mul > max) return false;
    // for (uint64_t num = 0; num <= max; num++) {
    for (unsigned iter = 0; iter < 1000000UL; iter++) {
        uint64_t num = r(0, max);
        // Make sure we hit the extremes
        if (iter == 0) num = 0;
        if (iter == 1) num = max;
        uint64_t result = num;
        result *= mul;
        result >>= bits;
        if (result > max) return false;
        result >>= sh_post;
        if (num / den != result) return false;
    }
    return true;
}

bool u_method_2(int den, int64_t mul, int sh_post, int bits) {
    uint64_t max = (1UL << bits) - 1;
    if (mul > max) return false;
    // for (uint64_t num = 0; num <= max; num++) {
    for (unsigned iter = 0; iter < 1000000UL; iter++) {
        uint64_t num = r(0, max);
        // Make sure we hit the extremes
        if (iter == 0) num = 0;
        if (iter == 1) num = max;
        uint64_t result = num;
        result *= mul;
        result >>= bits;
        if (result > max) return false;
        result = (result + num) >> 1;
        if (result > max) return false;
        result >>= sh_post;
        if (num / den != result) return false;
    }
    return true;
}

bool u_method_3(int den, int64_t mul, int sh_post, int bits) {
    uint64_t max = (1UL << bits) - 1;
    if (mul > max) return false;
    // for (uint64_t num = 0; num <= max; num++) {
    for (unsigned iter = 0; iter < 1000000UL; iter++) {
        uint64_t num = r(0, max);
        // Make sure we hit the extremes
        if (iter == 0) num = 0;
        if (iter == 1) num = max;
        uint64_t result = num;
        result *= mul;
        result >>= bits;
        if (result > max) return false;
        result = (result + num + 1) >> 1;
        if (result > max) return false;
        result >>= sh_post;
        if (num / den != result) return false;
    }
    return true;
}

bool s_method_0(int den, int sh_post, int bits) {
    int64_t min = -(1L << (bits - 1)), max = (1L << (bits - 1)) - 1;
    // for (int64_t num = min; num <= max; num++) {
    for (int iter = 0; iter < 1000000L; iter++) {
        int64_t num = r(min, max);
        // Make sure we hit the extremes
        if (iter == 0) num = min;
        if (iter == 1) num = max;
        int64_t result = num;
        result >>= sh_post;
        if (sdiv(num, den) != result) return false;
    }
    return true;
}

bool s_method_1(int den, int64_t mul, int sh_post, int bits) {
    int64_t min = -(1 << (bits - 1)), max = (1 << (bits - 1)) - 1;

    // for (int64_t num = min; num <= max; num++) {
    for (int iter = 0; iter < 1000000L; iter++) {
        int64_t num = r(min, max);
        // Make sure we hit the extremes
        if (iter == 0) num = min;
        if (iter == 1) num = max;
        int64_t result = num;
        uint64_t xsign = result >> (bits - 1);
        uint64_t q0 = (mul * (xsign ^ result)) >> bits;
        result = xsign ^ (q0 >> sh_post);
        if (sdiv(num, den) != result) return false;
    }
    return true;
}

bool srz_method_0(int den, int sh_post, int bits) {
    int64_t min = -(1L << (bits - 1)), max = (1L << (bits - 1)) - 1;
    for (int64_t num = min; num <= max; num++) {
        // for (int iter = 0; iter < 1000000L; iter++) {
        // int64_t num = r(min, max);
        // Make sure we hit the extremes
        // if (iter == 0) num = min;
        // if (iter == 1) num = max;
        int64_t result = num;
        result += (result >> (bits - 1)) & (den - 1);
        result >>= sh_post;
        if (srzdiv(num, den) != result) return false;
    }
    return true;
}

bool srz_method_1(int den, int64_t mul, int sh_post, int bits) {
    int64_t min = -(1 << (bits - 1)), max = (1 << (bits - 1)) - 1;

    for (int64_t num = min; num <= max; num++) {
        // for (int iter = 0; iter < 1000000L; iter++) {
        // int64_t num = r(min, max);
        // Make sure we hit the extremes
        // if (iter == 0) num = min;
        // if (iter == 1) num = max;
        int64_t result = num;
        uint64_t xsign = result >> (bits - 1);
        uint64_t q0 = (mul * result) >> bits;
        result = (q0 >> sh_post);
        uint64_t mask = (1ULL << bits) - 1;
        // printf("%lld %lld\n", (long long int)result, (long long int)mask);
        result -= (xsign & mask);
        // Fix-up the sign bits
        result <<= (64 - bits);
        result >>= (64 - bits);
        // printf("%d %d %lld %lld\n", (int)num, (int)den, (long long int)srzdiv(num, den), (long long int)result);
        if (srzdiv(num, den) != result) {
            printf("Fail\n");
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    /* This program computes a table to help us do cheap integer
        division by a constant. It is based on the paper "Division by
        Invariant Integers using Multiplication" by Granlund and
        Montgomery.
    */

    FILE *c_out = fopen("IntegerDivisionTable.cpp", "w");
    FILE *h_out = fopen("IntegerDivisionTable.h", "w");

    fprintf(h_out, "%s",
            "#ifndef HALIDE_INTEGER_DIVISION_TABLE_H\n"
            "#define HALIDE_INTEGER_DIVISION_TABLE_H\n"
            "\n"
            "#include <cstdint>\n"
            "\n"
            "/** \\file\n"
            " * Tables telling us how to do integer division via fixed-point\n"
            " * multiplication for various small constants. This file is \n"
            " * automatically generated by find_inverse.cpp.\n"
            " */\n"
            "namespace Halide {\n"
            "namespace Internal {\n"
            "namespace IntegerDivision {\n");

    fprintf(c_out, "%s",
            "/** \\file\n"
            " * Tables telling us how to do integer division\n"
            " * via fixed-point multiplication for various small\n"
            " * constants. This file is automatically generated\n"
            " * by find_inverse.cpp. There are two sets of tables.\n"
            " * The first set is for compile-time-constant divisors\n"
            " * from 2 to 256. The second is for runtime divisors\n"
            " * from 1 to 255. The second set always uses the most\n"
            " * expensive method, while the compile-time set uses\n"
            " * the cheapest method for the given divisor.\n"
            " */\n"
            "\n"
            "#include \"IntegerDivisionTable.h\"\n"
            "\n"
            "namespace Halide {\n"
            "namespace Internal {\n"
            "namespace IntegerDivision {\n\n");

    for (int runtime = 0; runtime < 2; runtime++) {
        for (int bits = 8; bits <= 32; bits *= 2) {
            printf("Generating table%s_u%d...\n", runtime ? "_runtime" : "", bits);
            if (runtime) {
                fprintf(h_out, "extern const int64_t table_runtime_u%d[256][4];\n", bits);
                fprintf(c_out, "const int64_t table_runtime_u%d[256][4] = {\n", bits);
            } else {
                fprintf(h_out, "extern const int64_t table_u%d[256][4];\n", bits);
                fprintf(c_out, "const int64_t table_u%d[256][4] = {\n", bits);
            }
            for (int d = 0; d < 256; d++) {
                if (runtime && d < 2) {
                    fprintf(c_out, "    {0, 0, 0, 0}, // unused\n");
                    continue;
                }

                int den = d;
                if (den == 0) den = 256;
                if (!runtime) {
                    for (int shift = 0; shift < 16; shift++) {
                        if (u_method_0(den, shift, bits)) {
                            fprintf(c_out, "    {%d, 0, 0, %d},\n", den, shift);
                            goto next_unsigned;
                        }
                    }

                    for (int shift = 0; shift < 8; shift++) {
                        int64_t mul = (1L << (bits + shift)) / den + 1;
                        if (u_method_1(den, mul, shift, bits)) {
                            fprintf(c_out, "    {%d, 1, %lldULL, %d},\n", den, (long long)mul, shift);
                            goto next_unsigned;
                        }
                    }

                    for (int shift = 0; shift < 8; shift++) {
                        int64_t mul = (1L << (bits + shift + 1)) / den - (1L << bits);
                        mul &= (1L << bits) - 1;
                        if (u_method_3(den, mul, shift, bits)) {
                            fprintf(c_out, "    {%d, 3, %lldULL, %d},\n", den, (long long)mul, shift);
                            goto next_unsigned;
                        }
                    }
                } else if (d == 1) {
                    // Runtime division by one is handled by a select
                    fprintf(c_out, "    {1, 0, 0ULL, 0},\n");
                    goto next_unsigned;
                }

                {
                    int shift = 31 - __builtin_clz(den - 1);
                    int64_t mul = (1L << (bits + shift + 1)) / den - (1L << bits) + 1;
                    mul &= (1L << bits) - 1;
                    if (u_method_2(den, mul, shift, bits)) {
                        fprintf(c_out, "    {%d, 2, %lldULL, %d},\n", den, (long long)mul, shift);
                        goto next_unsigned;
                    }
                }

                fprintf(c_out, "ERROR! No solution found for unsigned %d\n", den);
            next_unsigned:;
            }
            fprintf(c_out, "};\n");
            printf("Generating table%s_s%d...\n", runtime ? "_runtime" : "", bits);
            if (runtime) {
                fprintf(h_out, "extern const int64_t table_runtime_s%d[256][4];\n", bits);
                fprintf(c_out, "const int64_t table_runtime_s%d[256][4] = {\n", bits);
            } else {
                fprintf(h_out, "extern const int64_t table_s%d[256][4];\n", bits);
                fprintf(c_out, "const int64_t table_s%d[256][4] = {\n", bits);
            }
            for (int d = 0; d < 256; d++) {
                if (runtime && d < 2) {
                    fprintf(c_out, "    {0, 0, 0, 0}, // unused\n");
                    continue;
                }
                int den = d;
                if (den == 0) den = 256;
                if (!runtime) {
                    for (int shift = 0; shift < 8; shift++) {
                        if (s_method_0(den, shift, bits)) {
                            fprintf(c_out, "    {%d, 0, 0, %d},\n", den, shift);
                            goto next_signed;
                        }
                    }
                }

                {
                    int shift = 31 - __builtin_clz(den - 1);
                    int64_t mul = (1L << (shift + bits)) / den + 1;
                    if (s_method_1(den, mul, shift, bits)) {
                        fprintf(c_out, "    {%d, 1, %lldLL, %d},\n", den, (long long)mul, shift);
                        goto next_signed;
                    }
                }
                fprintf(c_out, "ERROR! No solution found for signed %d\n", den);
            next_signed:;
            }
            fprintf(c_out, "};\n");
            printf("Generating table%s_srz%d...\n", runtime ? "_runtime" : "", bits);
            if (runtime) {
                fprintf(h_out, "extern const int64_t table_runtime_srz%d[256][4];\n", bits);
                fprintf(c_out, "const int64_t table_runtime_srz%d[256][4] = {\n", bits);
            } else {
                fprintf(h_out, "extern const int64_t table_srz%d[256][4];\n", bits);
                fprintf(c_out, "const int64_t table_srz%d[256][4] = {\n", bits);
            }
            for (int d = 0; d < 256; d++) {
                if (runtime && d < 2) {
                    fprintf(c_out, "    {0, 0, 0, 0}, // unused\n");
                    continue;
                }
                int den = d;
                if (den == 0) den = 256;
                if (!runtime) {
                    for (int shift = 0; shift < 8; shift++) {
                        if (srz_method_0(den, shift, bits)) {
                            fprintf(c_out, "    {%d, 0, 0, %d},\n", den, shift);
                            goto next_signedrz;
                        }
                    }
                }

                {
                    int shift = 31 - __builtin_clz(den - 1);
                    int64_t mul = (1L << (shift + bits)) / den + 1;
                    if (srz_method_1(den, mul, shift, bits)) {
                        fprintf(c_out, "    {%d, 1, %lldLL, %d},\n", den, (long long)mul, shift);
                        goto next_signedrz;
                    }
                }
                fprintf(c_out, "ERROR! No solution found for signed %d\n", den);
            next_signedrz:;
            }
            fprintf(c_out, "};\n");
        }
    }

    fprintf(h_out, "}\n}\n}\n\n#endif\n");
    fprintf(c_out, "}\n}\n}\n");

    fclose(h_out);
    fclose(c_out);

    return 0;
}
