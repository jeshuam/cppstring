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

}  // namespace string
