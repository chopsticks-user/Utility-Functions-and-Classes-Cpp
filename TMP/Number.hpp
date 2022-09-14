#ifndef UTILITY_TMP_NUMBER_HPP
#define UTILITY_TMP_NUMBER_HPP

#include <cstdlib>
#include <numeric>
#include <ratio>

namespace utility
{
    namespace tmp
    {
        template <const auto &str>
        constexpr auto cmpl_string() { return str; }

        template <bool cond, const auto &fail_msg>
        constexpr void cmpl_expect() noexcept
        {
            if constexpr (cond == false)
            {
                std::cout << "Compile-time expectation failed with message: " << fail_msg << '\n';
                std::exit(EXIT_FAILURE);
            }
        }

        template <int base, int p = 1, long result = base>
        constexpr double cmpl_exp()
        {
            if constexpr (p <= 1)
            {
                if constexpr (p == 0)
                    return 1;
                else
                    return result;
            }
            else
                return cmpl_exp<base, p - 1, base * result>();
        }

        template <long numer = 0, long denom = 1, long exp10 = 0>
        struct zz_Number
        {
            template <typename sym_ratio = std::ratio<numer, denom>>
            using type = zz_Number<sym_ratio::num, sym_ratio::den, exp10>;

            static constexpr double coefficient = numer * 1.0 / denom;
            static constexpr long exponent = exp10;
            static constexpr double value = coefficient * cmpl_exp<10, exponent>();

            template <long n = 0, long d = 1, long e10 = 0>
            constexpr auto operator+(zz_Number<n, d, e10>)
            {
                using ratio_sum = std::ratio_add<std::ratio<numer, denom>,
                                                 std::ratio<n, d>>;
                return zz_Number<ratio_sum::num, ratio_sum::den, exp10>{};
            }

            template <long n = 0, long d = 1, long e10 = 0>
            constexpr auto operator-(zz_Number<n, d, e10>)
            {
                using ratio_diff = std::ratio_subtract<std::ratio<numer, denom>,
                                                       std::ratio<n, d>>;
                return zz_Number<ratio_diff::num, ratio_diff::den, exp10>{};
            }

            template <long n = 0, long d = 1, long e10 = 0>
            constexpr auto operator*(zz_Number<n, d, e10>)
            {
                using ratio_product = std::ratio_multiply<std::ratio<numer, denom>,
                                                          std::ratio<n, d>>;
                return zz_Number<ratio_product::num, ratio_product::den, exp10>{};
            }

            template <long n = 0, long d = 1, long e10 = 0>
            constexpr auto operator/(zz_Number<n, d, e10>)
            {
                using ratio_quotient = std::ratio_divide<std::ratio<numer, denom>,
                                                         std::ratio<n, d>>;
                return zz_Number<ratio_quotient::num, ratio_quotient::den, exp10>{};
            }

            // template <long n = 0, long d = 1, long e10 = 0>
            // constexpr bool operator==(zz_Number<n, d, e10>)
            // {
            //     return std::ratio_equal_v<>
            // }

            static constexpr auto symplify()
            {
                constexpr auto cd = std::gcd(numer, denom);
                return zz_Number<numer / cd, denom / cd>();
            }
        };

        template <long numer = 0, long denom = 1, long exp10 = 0>
        constexpr zz_Number<numer, denom, exp10> Number{};

        // template <long exp10 = 0>
        // constexpr auto make_number(double val)
        // {
        //     constexpr auto decimal = val - static_cast<long>(val);
        //     return zz_Number<>
        // }

        template <typename N1, typename N2>
        constexpr auto operator+(N1, N2)
        {
            return N1{} + N2{};
        }

        template <typename N1, typename N2>
        constexpr auto operator-(N1, N2)
        {
            return N1{} - N2{};
        }

        template <typename N1, typename N2>
        constexpr auto operator*(N1, N2)
        {
            return N1{} * N2{};
        }

        template <typename N1, typename N2>
        constexpr auto operator/(N1, N2)
        {
            return N1{} / N2{};
        }
    } /* tmp */
} /* utility */

#endif /* UTILITY_TMP_NUMBER_HPP */