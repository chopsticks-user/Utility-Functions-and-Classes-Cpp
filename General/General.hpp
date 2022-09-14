#ifndef UTILITY_GENERAL_HPP
#define UTILITY_GENERAL_HPP

#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>
#include <chrono>
#include <random>

namespace utility
{
    using mic = std::chrono::microseconds;
    using mil = std::chrono::milliseconds;
    using sec = std::chrono::seconds;
    using min = std::chrono::minutes;
    using hr = std::chrono::hours;

    template <typename DurationType = mic>
    class Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::string time_unit;

    public:
        Timer()
        {
            if (std::is_same_v<DurationType, mic>)
                this->time_unit = "μs";
            else if (std::is_same_v<DurationType, mil>)
                this->time_unit = "ms";

            else if (std::is_same_v<DurationType, sec>)
                this->time_unit = "s";

            else if (std::is_same_v<DurationType, min>)
                this->time_unit = "mins";

            else if (std::is_same_v<DurationType, hr>)
                this->time_unit = "hrs";
            else
                static_assert("Unkown time unit.");

            this->start = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            auto stop = std::chrono::high_resolution_clock::now();
            std::cout << "Time elapsed: "
                      << std::chrono::duration_cast<
                             DurationType>(stop - start)
                             .count()
                      << ' ' << this->time_unit << "\n";
        }
    };

    double rand(double min, double max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    template <typename ItTp>
    void rand(double min, double max, ItTp it_begin, ItTp it_end)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        while (it_begin != it_end)
            *(it_begin++) = dis(gen);
    }

    template <typename T>
    constexpr bool is_lvalue(T &&)
    {
        return std::is_lvalue_reference<T>{};
    };

    template <typename T>
    constexpr bool is_rvalue(T &&)
    {
        return std::is_rvalue_reference<T &&>{};
    };

    template <typename T>
    std::string type_name()
    {
        int status;
        std::string name = typeid(T).name();
        auto demangled_name = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
        if (status == 0)
        {
            name = demangled_name;
            std::free(demangled_name);
        }
        return name;
    }

} /* utility */

#endif /* UTILITY_GENERAL_HPP */