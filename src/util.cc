#include "util.h"

#include <algorithm>

namespace string {

int Count(const std::string& str, const std::string& sub) {
  if (str.length() == 0 || sub.length() == 0) {
    return 0;
  }

  // Keep std::find'ing sub in str until we reach the end of the string.
  int count = 0;
  auto pos = str.find(sub);
  while (pos != std::string::npos) {
    count++;
    pos = str.find(sub, pos + sub.length() + 1);
  }

  return count;
}

bool In(const std::string& str, const std::string& needle) {
  if (needle.length() == 0) {
    return false;
  }

  return str.find(needle) != std::string::npos;
}

bool EndsWith(const std::string& str, const std::string& suffix) {
  if (suffix.length() == 0) {
    return false;
  }

  return str.rfind(suffix) == (str.length() - suffix.length());
}

bool StartsWith(const std::string& str, const std::string& prefix) {
  if (prefix.length() == 0) {
    return false;
  }

  return str.find(prefix) == 0;
}

std::string Trim(const std::string& str, const std::string& tokens) {
  return TrimRight(TrimLeft(str, tokens), tokens);
}

std::string TrimRight(const std::string& str, const std::string& tokens) {
  auto last_non_token = str.find_last_not_of(tokens);
  if (last_non_token == std::string::npos) {
    return "";
  }

  return str.substr(0, str.size() - (str.size() - last_non_token) + 1);
}

std::string TrimLeft(const std::string& str, const std::string& tokens) {
  auto first_non_token = str.find_first_not_of(tokens);
  if (first_non_token == std::string::npos) {
    return "";
  }

  return str.substr(first_non_token);
}

std::string Capitalize(const std::string& str) {
  if (str.empty()) {
    return "";
  }

  std::string result(str);
  result[0] = ::toupper(result[0]);
  return result;
}

std::string ToLower(const std::string& str) {
  std::string result(str);
  std::transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

std::string ToUpper(const std::string& str) {
  std::string result(str);
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

std::string Replace(const std::string& str, const std::string& old,
                    const std::string& replacement, int count) {
  // Keep finding copies until we reach the end.
  std::string str_replace(str);
  size_t start = str_replace.find(old), replacements = 0;
  while (start != std::string::npos) {
    // Make sure we aren't over our limit.
    if (count >= 0 && replacements >= count) {
      break;
    }

    // Do the replacement.
    str_replace.replace(start, old.size(), replacement);
    start = str_replace.find(old, start + 1);
    replacements++;
  }

  return str_replace;
}

}  // namespace string
