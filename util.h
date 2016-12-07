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

}