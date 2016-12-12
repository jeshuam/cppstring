#pragma once

#include <string>
#include <vector>

#include "constants.h"

namespace string {

/**
 * @brief      Split a string into components based on a list of separators.
 *
 * @details    The string will be split into a list by any character within
 *             `sep`. This means that multiple characters can be selected, and
 *             each individual character will act as a split character. For
 *             example:
 *
 *                 Split("a,b|c^d;e", ",|^") -> {"a", "b", "c", "d;e"}
 *
 *             If `collapse_empty_groups` is set, then adjacent separators will
 *             be collapsed into a single separator. For example:
 *
 *                 Split("a,|,b,c", ",|", true) -> {"a", "b", "c"}
 *
 *             Without this, empty strings will be inserted in lieu of elements.
 *
 *             By default, `sep` is set to all whitespace characters.
 *
 *             When `maxsplit` is specified, the maximum length of the output
 *             container is `maxsplit + 1`.
 *
 * @param[in]  str                     The string to split.
 * @param[in]  sep                     The separators to split by.
 * @param[in]  collapse_empty_groups   When true, collapse adjacent delimiters
 *                                     into a single delimiter.
 * @param[in]  maxsplit                The maximum number of splits to perform.
 *                                     Set to -1 for unlimited.
 *
 * @return     A vector of strings, which are the parts of `str`.
 * @see        SplitRight
 */
std::vector<std::string> Split(const std::string& str,
                               const std::string& sep = kWhitespace,
                               bool collapse_empty_groups = false,
                               int maxsplit = -1);

/**
 * @brief      Same as Split, but starts scanning from the RHS of the string.
 *
 * @param[in]  str                     The string to split.
 * @param[in]  sep                     The separators to split by.
 * @param[in]  collapse_empty_groups   When true, collapse adjacent delimiters
 *                                     into a single delimiter.
 * @param[in]  maxsplit                The maximum number of splits to perform.
 *                                     Set to -1 for unlimited.
 *
 * @return     A vector of strings, which are the parts of `str`.
 * @see        Split
 */
std::vector<std::string> SplitRight(const std::string& str,
                                    const std::string& sep = kWhitespace,
                                    bool collapse_empty_groups = false,
                                    int maxsplit = -1);

/**
 * @brief      Join a list of strings by a separator.
 *
 * @param[in]  list  The list of strings to join.
 * @param[in]  sep   The separator used to join them.
 *
 * @return     A string containing all elements in `list`, separated by `sep`.
 */
std::string Join(const std::vector<std::string>& list, const std::string& sep);

}  // namespace string
