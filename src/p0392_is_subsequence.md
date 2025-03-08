# Complexity of the Two Pointer Approach

We visit each character in `t` at most once, thus the complexity is $\mathcal{O}(N_t)$. If we want to check $k$ `s` strings, the total complexity is $\mathcal{O}(k N_t)$.

# Complexity of the Lookup Table

## Building the Table

When pre-computing the lookup table for a given `t` with $N_t$ characters, we have to iterate through each one of them and check if an index `std::set` is already present in the `std::unordered_map`. Since there can only be one set per character, this check is $\mathcal{O}(1)$ as we just have to find the correct bucket in the hashmap. Inserting the index in the corrsponding `std::set` only requires $\mathcal{O}(1)$ time as it has to be the largest index and we can provide the end iterator as a hint.

In total, building the lookup table is of linear complexity $\mathcal{O}(N_t)$.

## Looking up a Single `s`

We have to go through each of the $N_s$ characters in `s`, retrieving the corresponding index `std::set` in $\mathcal{O}(1)$ due to the unique keys. Due to the ordered nature of the set, we can find the smallest index in logarithmic time. In the worst case, all characters in `t` could be identical. The complexity is thus given by $\mathcal{O}(\log N_t)$.

The total complexity of checking a single `s` is thus $\mathcal{O}(N_s\log N_t)$.

## Checking a lot of `s`

If we want to check $k$ `s` strings against `k`, the total complexity with the lookup table is $\mathcal{O}(N_t + k N_s\log N_t)$ when including the complexity of constructing it in the first place.

# Comparison

Comparing the two approaches, the lookup table makes sense for $N_t \gg N_s$.
