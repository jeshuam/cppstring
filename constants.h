#pragma once

#include <string>
#include <unordered_map>

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

// Colors.
namespace color {

// Magic color reset.
extern const std::string kReset;

// Color formats.
extern const std::string kBold;
extern const std::string kItalic;

// Colors.
extern const std::string kBlack;
extern const std::string kRed;
extern const std::string kGreen;
extern const std::string kYellow;
extern const std::string kBlue;
extern const std::string kMagenta;
extern const std::string kCyan;
extern const std::string kWhite;
extern const std::string kGray;

}  // namespace color

}  // namespace string
