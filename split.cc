#include "split.h"

#include <algorithm>
#include <functional>
#include <list>
#include <sstream>
#include <unordered_set>

namespace string {

namespace {

typedef std::function<void(std::list<std::string>& list,
                           const std::string& item)>
    InsertFn;

std::vector<std::string> _DoSplit(const std::string& str,
                                  const std::string& sep,
                                  bool collapse_empty_groups, int maxsplit,
                                  int i_start, int i_delta) {
  std::list<std::string> result;

  // Count the number of splits.
  int n_splits = 0;

  // Make a set of seps, to make lookups fast.
  std::unordered_set<char> sep_set;
  for (char c : sep) {
    sep_set.insert(c);
  }

  // Function to insert into the result.
  auto insert = [&i_delta, &result](const std::string& piece) {
    if (i_delta > 0) {
      result.push_back(piece);
    } else {
      result.push_front(piece);
    }
  };

  int last_sep = i_start - i_delta;
  for (int i = i_start; i < str.size() && i >= 0; i += i_delta) {
    char c = str[i];

    // If this character is a delimiter...
    if (sep_set.find(c) != sep_set.end()) {
      // Add everything from the last separator until now to the list.
      auto last_chars =
          str.substr(std::min(last_sep, i) + 1,
                     std::max(last_sep, i) - std::min(last_sep, i) - 1);

      // If last_chars is empty and collapse_empty_groups is false, then add.
      if (last_chars.empty()) {
        if (!collapse_empty_groups) {
          insert("");
          n_splits++;
        }
      } else {
        insert(last_chars);
        n_splits++;
      }

      last_sep = i;

      // If we have split too many, then stop.
      if (maxsplit >= 0 && n_splits >= maxsplit) {
        break;
      }
    }
  }

  // Add any remaining data.
  std::string data = "";
  if (i_delta > 0) {
    data = str.substr(last_sep + 1);
  } else if (i_delta < 0) {
    data = str.substr(0, last_sep);
  }

  if (!data.empty() || !collapse_empty_groups) {
    insert(data);
  }

  // Copy the list to a vector.
  std::vector<std::string> result_vec(result.size());
  std::copy(result.begin(), result.end(), result_vec.begin());
  return result_vec;
}

}  // namespace

std::vector<std::string> Split(const std::string& str, const std::string& sep,
                               bool collapse_empty_groups, int maxsplit) {
  return _DoSplit(str, sep, collapse_empty_groups, maxsplit, 0, 1);
}

std::vector<std::string> SplitRight(const std::string& str,
                                    const std::string& sep,
                                    bool collapse_empty_groups, int maxsplit) {
  return _DoSplit(str, sep, collapse_empty_groups, maxsplit, str.size() - 1,
                  -1);
}

std::string Join(const std::vector<std::string>& list, const std::string& sep) {
  std::stringstream output;
  for (int i = 0; i < list.size(); i++) {
    output << list[i];
    if (i < list.size() - 1) {
      output << sep;
    }
  }

  return output.str();
}

}  // namespace string
