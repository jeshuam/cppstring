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

/**
 * @brief      Trim all characters in `tokens` from either side of `str`.
 *
 * @param[in]  str     The string to trim.
 * @param[in]  tokens  The tokens to trim.
 *
 * @return     A copy of `str` with all characters in `tokens` removed.
 * @see        TrimRight
 * @see        TrimLeft
 */
std::string Trim(const std::string& str, const std::string& tokens);

/**
 * @brief      Trim all characters in `tokens` from the right side of `str`.
 *
 * @param[in]  str     The string to trim.
 * @param[in]  tokens  The tokens to trim.
 *
 * @return     A copy of `str` with all characters in `tokens` removed from the
 *             right.
 * @see        Trim
 * @see        TrimLeft
 */
std::string TrimRight(const std::string& str, const std::string& tokens);

/**
 * @brief      Trim all characters in `tokens` from the left side of `str`.
 *
 * @param[in]  str     The string to trim.
 * @param[in]  tokens  The tokens to trim.
 *
 * @return     A copy of `str` with all characters in `tokens` removed from the
 *             left.
 * @see        Trim
 * @see        TrimRight
 */
std::string TrimLeft(const std::string& str, const std::string& tokens);

/**
 * @brief      Capitalize the given string.
 *
 * @param[in]  str   The string to capitalize.
 *
 * @return     A version of the string with the first letter capitalized.
 */
std::string Capitalize(const std::string& str);

/**
 * @brief      Convert the given string to lowercase.
 *
 * @param[in]  str   The string to convert.
 *
 * @return     A version of the string with all letters in their lowercase form.
 * @see        ToUpper
 */
std::string ToLower(const std::string& str);

/**
 * @brief      Convert the given string to uppercase.
 *
 * @param[in]  str   The string to convert.
 *
 * @return     A version of the string with all letters in their uppercase form.
 * @see        ToLower
 */
std::string ToUpper(const std::string& str);

/**
 * @brief      Replace all occurrences of `old` with `replacement` in `str`.
 *
 * @details    At most `count` occurrences of `old` will be replaced by
 *             `replacement` in `str`. This replacement will occur from left
 *             to right.
 *
 * @param[in]  str           The string to replace the contents of.
 * @param[in]  old           The string to replace.
 * @param[in]  replacement   The string to replace it with.
 * @param[in]  count         The number of replacements to make.
 *
 * @return     A new string with the replacement performed.
 */
std::string Replace(const std::string& str, const std::string& old,
                    const std::string& replacement, int count = -1);

}  // namespace string
