#ifndef UTILITY_GENERAL_CONSOLE_HPP
#define UTILITY_GENERAL_CONSOLE_HPP

#define CONSOLE_RED "\033[1;31m"
#define CONSOLE_RESET "\033[0m"

#include <string>
#include <span>

namespace utility
{
#ifdef __cpp_lib_span
    void read_commands(int argc, char **argv)
    {
        auto sp_arg = std::span(argv, argc);
        for (const auto &arg : sp_arg)
            std::cout << arg << '\n';
    }
#else
    void read_commands(int argc, char **argv)
    {
        while (argc--)
            std::cout << *(argv++) << '\n';
    }
#endif /* __cpp_lib_span */
    constexpr void maybe_unused_commands(int argc, char **argv)
    {
        static_cast<void>(argc);
        static_cast<void>(argv);
    }

    namespace console
    {
        std::string space = " ";
        std::string endline = "\n";

        template <typename... T>
        void println(T... args)
        {
            ((std::cout << args << space), ..., (std::cout << endline));
        };

        template <typename... T>
        void read(T &...args)
        {
            ((std::cin >> args), ...);
        }
    } /* console */
} /* utility */

#endif /* UTILITY_GENERAL_CONSOLE_HPP */