#include "util.h"

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

bool EndsWith(const std::string& str, const std::string& suffix) {
  if (suffix.length() == 0) {
    return false;
  }

  auto pos = str.rfind(suffix);
  return pos == (str.length() - suffix.length());
}

}
