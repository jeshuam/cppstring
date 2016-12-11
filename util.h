#pragma once

#include <string>

namespace string {

/**
 * @brief      Count the number of occurrences of `sub` in `str`.
 *
 * @details    This will only count non-overlapping occurrences of `str`. For
 *             example:
 *
 *                 Count("ababa", "aba") -> 1
 *
 *             This functional will return 0 if `sub` is an empty string.
 *
 * @param[in]  str   The string to search.
 * @param[in]  sub   The substring to search for.
 *
 * @return     The number of times `sub` occurs in `str`.
 */
int Count(const std::string& str, const std::string& sub);

/**
 * @brief      Determine whether `needle` is within `str.
 *
 * @param[in]  str     The string to search.
 * @param[in]  needle  The needle to search for.
 *
 * @return     `true` iff `needle` is within `str`.
 */
bool In(const std::string& str, const std::string& needle);

/**
 * @brief      Determines if `str` ends with suffix `suffix`.
 *
 * @param[in]  str     The string to search.
 * @param[in]  suffix  The suffix to search for.
 *
 * @return     `true` iff `str` ends with `suffix`.
 */
bool EndsWith(const std::string& str, const std::string& suffix);

/**
 * @brief      Determines if `str` starts with prefix `prefix`.
 *
 * @param[in]  str     The string to search.
 * @param[in]  prefix  The prefix to search for.
 *
 * @return     `true` iff `str` starts with `prefix`.
 */
bool StartsWith(const std::string& str, const std::string& prefix);

}  // namespace string
