#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <iostream>

#include <boost/any.hpp>

namespace string {

// Internal; don't use directly.
namespace internal {

// Wrapper around boost::any which allows it to be printed.
struct PrintableAny : boost::any {
  template <typename T>
  PrintableAny(T t) : boost::any(t) {
    printer_ = [](std::ostream& os, const boost::any& a) {
      os << boost::any_cast<const T&>(a);
    };
  }

  std::function<void(std::ostream&, const boost::any&)> printer_;
};

#ifdef OS_LINUX

// Add a custom overwrite for char arrays, to allow users to pass raw strings as
// arguments.
template <>
PrintableAny::PrintableAny(const char t[]);

#endif  // OS_LINUX

}  // namespace internal

/**
 * @brief      Create a formatted string from the given format and mapping.
 *
 * @details    The formatting language is very heavily based off Python, so get
 *             familiar with that. Basically, your format will look like this:
 *
 *                 "Hello, {name}!"
 *
 *             ... and you would call the function as follows:
 *
 *                 FormatMap("Hello, {name}!", {{"name", "Sarah"}});
 *
 *             The second argument is the C++11 initializer list syntax for
 *             making a mapping structure, basically saying that you should
 *             replace all tags called "{name}" with "Sarah". If "{name}" occurs
 *             more than once in the format, it will be substituted more than
 *             once.
 *
 *             By default, objects will be formatted using the C++ << notation.
 *             i.e. this would be the equivalent of doing:
 *
 *                 sstream << "Hello, " << "Sarah";
 *
 *             This allows custom objects to be passed as well!
 *
 *                 FormatMap("Hello, {name}!", {{"name", Person("Sarah")}});
 *
 *             The types in the map are _not_ homogeneous, so you can pass
 *             things of different types!
 *
 *                 FormatMap("{greet}, {name}!",
 *                           {{"greet","Hello"}, {"name", 24601}});
 *                           -> "Hello, 24601"
 *
 *             If you want more control over your formatting, you can specify
 *             the format to use after a : character. So:
 *
 *                 FormatMap("{n:.3f}", {{"n", 6.1423}}) -> "6.142"
 *
 *             ... will format format the number as a float with 3 decimal
 *             places. The possible options for formats are the same as the
 *             standard `printf()`.
 *
 *             If you want the format to include { or }, just write it twice.
 *
 *                 FormatMap("{{{n}}}", {{"n", 3}}) -> "{{3}}"
 *
 * @param[in]  fmt   The format string.
 * @param[in]  args  The mapping to be applied to the format string.
 *
 * @throws     std::invalid_argument Thrown if the format string is invalid.
 * @throws     std::out_of_range Key in the format is not in the map provided.
 *
 * @return     A string with all formatted tags substituted.
 */
std::string FormatMap(
    const std::string& fmt,
    const std::unordered_map<std::string, internal::PrintableAny>& args);

/**
 * @brief      Create a formatted string from the given format and args.
 *
 * @details    Very similar to FormatMap, but tags are indexed by numbers rather
 *             than keys. You can also omit the numbers and just use {}, in
 *             which case each tag will contain subsequent arguments.
 *
 *             Tag formatting is identical to FormatMap. Indexed and non-indexed
 *             tags can be mixed, but are processed separately. So:
 *
 *                 Format("{}{2}{}", {1, "x", 2}) -> "12x"
 *
 *             Indexing starts from 0 (so {0} is the first tag). You can skip
 *             numbers if you wish, although the arguments list should be large
 *             enough to accommodate.
 *
 * @param[in]  fmt   The format string.
 * @param[in]  args  The arguments to substitute.
 *
 * @throws     std::invalid_argument Thrown if the format string is invalid.
 * @throws     std::out_of_range Key in the format is not in the list provided.
 *
 * @return     A string with all formatted tags substituted.
 *
 * @see        FormatMap
 */
std::string Format(const std::string& fmt,
                   const std::vector<internal::PrintableAny>& args);

/**
 * @brief      Trim any formatting tags from the given string.
 *
 * @param[in]  fmt   The format string to trim.
 *
 * @return     A trimmed version of the given format string.
 */
std::string FormatTrimTags(const std::string& fmt);

/**
 * @brief      Check whether the given format has any tags in it.
 *
 * @param[in]  fmt   The format to check.
 *
 * @return     `true` iff `fmt` has at least one tag in it.
 */
bool FormatHasTag(const std::string& fmt, const std::string& tag);

}  // namespace string
