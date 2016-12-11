#pragma once

#include <string>

namespace string {

/**
 * The lower-case, ASCII letters.
 */
extern const std::string kAsciiLowercase;

/**
 * The upper-case, ASCII letters.
 */
extern const std::string kAsciiUppercase;

/**
 * All digits 0-9.
 */
extern const std::string kDigits;

/**
 * All digits that can be in hex numbers.
 */
extern const std::string kHexDigits;

/**
 * All digits that can be in octal numbers.
 */
extern const std::string kOctDigits;

/**
 * All punctuation characters.
 */
extern const std::string kPunctuation;

/**
 * All whitespace characters.
 */
extern const std::string kWhitespace;

// Generated based on the above.
/**
 * `kAsciiLowercase` + `kAsciiUppercase`
 */
extern const std::string kAsciiLetters;

/**
 * `kDigits` + `kAsciiLetters` + `kPunctuation` + `kWhitespace`
 */
extern const std::string kPrintable;

}  // namespace string
