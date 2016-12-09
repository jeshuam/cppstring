#pragma once

#include <string>

namespace string {

/**
 * @brief Count the number of occurences of `sub` in `str`.
 *
 * @param str The string to search.
 * @param sub The string to search for.
 *
 * @return The number of times `sub` occurs in `str`.
 */
int Count(const std::string& str, const std::string& sub);

/**
 * @brief Check whether a needle is within a haystack.
 *
 * @param str The string to search.
 * @param needle The needle to search for.
 *
 * @return `true` iff `needle` is within `str`.
 */
bool In(const std::string& str, const std::string& needle);

/**
 * @brief Check if `str` ends in `suffix`.
 *
 * @param str The string to search.
 * @param suffix The suffix to look for.
 *
 * @return `true` iff `str` ends with the characters in `suffix`.
 */
bool EndsWith(const std::string& str, const std::string& suffix);

/**
 * @brief Check if `str` starts in `prefix`.
 *
 * @param str The string to search.
 * @param suffix The prefix to look for.
 *
 * @return `true` iff `str` starts with the characters in `prefix`.
 */
bool StartsWith(const std::string& str, const std::string& prefix);

}