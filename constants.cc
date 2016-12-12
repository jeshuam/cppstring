#include "constants.h"

namespace string {

const std::string kAsciiLowercase = "abcdefghijklmnopqrstuvwxyz";
const std::string kAsciiUppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string kDigits = "0123456789";
const std::string kHexDigits = "0123456789abcdefABCDEF";
const std::string kOctDigits = "01234567";
const std::string kPunctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
const std::string kWhitespace = "\t\n\x0b\x0c\r ";

const std::string kAsciiLetters = kAsciiLowercase + kAsciiUppercase;
const std::string kPrintable =
    kDigits + kAsciiLetters + kPunctuation + kWhitespace;

namespace color {

// Magic color reset.
const std::string kReset = "\033[0m";

// Color formats.
const std::string kBold = "\033[1m";
const std::string kItalic = "\033[3m";

// Colors.
const std::string kBlack = "\033[30m";
const std::string kRed = "\033[31m";
const std::string kGreen = "\033[32m";
const std::string kYellow = "\033[33m";
const std::string kBlue = "\033[34m";
const std::string kMagenta = "\033[35m";
const std::string kCyan = "\033[36m";
const std::string kWhite = "\033[37m";
const std::string kGray = kBlack + kBold;

}  // namespace color

}  // namespace string
