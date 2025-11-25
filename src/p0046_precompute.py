import itertools
import math

n = 6


def get_permutations_for_size(n):
    for permutation in itertools.permutations(range(n)):
        yield ",".join(str(i) for i in permutation)


def build_lookup_array(n):
    return f"""constexpr std::array<std::size_t, {n * math.factorial(n)}> permutations_{n} = {{
    {",".join(permutation for permutation in get_permutations_for_size(n))}
    }};"""


lookup_arrays = "\n".join(build_lookup_array(n) for n in range(1, 7))
cases = "\n".join(
    f"case {n}:\n    return std::make_tuple(permutations_{n}.data(), permutations_{n}.size());"
    for n in range(1, 7)
)
lookup_function = f"""
[[nodiscard]] constexpr std::tuple<const std::size_t*, const std::size_t> get_permutations_for_size(std::size_t n) noexcept {{
    switch (n) {{
        {cases}
        default:
            return std::make_tuple(nullptr, 0);
            }}
}}
"""


code = f"""
#ifndef P0046_PRECOMPUTED_HPP
#define P0046_PRECOMPUTED_HPP

#include <array>
#include <tuple>

namespace p0046 {{

{lookup_arrays}

{lookup_function}

}}

#endif
"""
print(code)

# def get_all_permutations_up_to_size(n):
#     for _ in range(1, n + 1):
#         yield "{" + ",".join(str(i) for i in get_permutations_for_size(n)) + "}"


# all_permutations = "{{}," + ",".join(get_all_permutations_up_to_size(n)) + "}"

# code = f"""
# #ifndef P0046_PRECOMPUTED_HPP
# #define P0046_PRECOMPUTED_HPP

# #include <array>
# #include <vector>

# std::array<std::size_t, 3> permutations_3


# #endif
# """
# print(code)
