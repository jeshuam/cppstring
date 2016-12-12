#include "format.h"

#include <memory>
#include <sstream>

#include <string.h>

#include <gflags/gflags.h>

#include "util.h"

DEFINE_uint32(cppstring_format_buffer_bytes, 1024,
              "Length of the format string buffer to use in bytes.");

namespace string {

#ifdef OS_LINUX

namespace internal {

template <>
PrintableAny::PrintableAny(const char t[])
    : boost::any(t), printer_([](std::ostream& os, const boost::any& a) {
        os << boost::any_cast<const char*>(a);
      }) {}

}  // namespace internal

#endif  // OS_LINUX

namespace {

// Write all non-tag characters to the given SS.
void _WriteIntermediateCharacters(const std::string& str,
                                  std::stringstream& ss) {
  // If there is a single } somewhere in the string, then we have a problem.
  int n_right = Count(str, "}");
  int n_double_right = Count(str, "}}");
  if (n_right > (2 * n_double_right)) {
    throw std::invalid_argument("Mismatch { and } in format string.");
  }

  ss << str;
}

// Write the given format string to the given format buffer, using `val` of type
// `T` as the input.
template <typename T>
char* _WriteToFormatBuffer(char* buffer, const std::string& fmt,
                           const boost::any& val) {
  int n = snprintf(buffer, FLAGS_cppstring_format_buffer_bytes, fmt.c_str(),
                   boost::any_cast<T>(val));

  if (n < 0 || n >= FLAGS_cppstring_format_buffer_bytes) {
    std::cerr << "Failed to write format to buffer: " << fmt << ", "
              << boost::any_cast<T>(val);
    throw std::invalid_argument("Format too long for buffer.");
  }

  return buffer;
}

typedef std::function<const internal::PrintableAny(const std::string&)> TagFn;

std::string _Format(const std::string& fmt, const TagFn& get_tag) {
  // We have to be fast, so just scan through the string until we find a set of
  // matching {}.
  std::stringstream result;

// Allocate space for the buffer. On Windows, this has to be an actually
// allocated array, so use a unique_ptr to make sure it is destroyed. On other
// OSes, you can just use a variable sized char array.
#ifdef OS_WINDOWS
  std::unique_ptr<char[]> buffer_store(
      new char[FLAGS_cppstring_format_buffer_bytes]);
  char* buffer = buffer_store.get();
#else
  char buffer[FLAGS_cppstring_format_buffer_bytes];
#endif

  size_t start = fmt.find("{"), last_end = -1;
  size_t next_tag_index = 0;  // used for Format(), not FormatMap()
  while (start != std::string::npos) {
    // If the immediate next character is a {, then this bracket has been
    // escaped and we can ignore it; just move on.
    if (fmt.substr(start + 1, 1) == "{") {
      result << "{{";
      last_end = start + 1;
      start = fmt.find("{", last_end + 1);
      continue;
    }

    size_t end = fmt.find("}", start + 1);

    // If we didn't find end, it is an invalid format.
    if (end == std::string::npos) {
      throw std::invalid_argument("Mismatch { and } in format string.");
    }

    // Everything between [start, end] is a tag. So, first add everything from
    // the end of the last tag until now to the string.
    if (last_end + 1 < start) {
      _WriteIntermediateCharacters(
          fmt.substr(last_end + 1, start - last_end - 1), result);
    }

    // Parse the tag.
    auto tag_raw = fmt.substr(start + 1, end - start - 1);
    std::string tag = tag_raw, type = " ";
    if (In(tag_raw, ":")) {
      type = "%" + tag_raw.substr(tag_raw.find(":") + 1);
      tag = tag_raw.substr(0, tag_raw.length() - type.length());
    }

    // If the tag is empty, the use the next index.
    if (tag.empty()) {
      tag = std::to_string(next_tag_index);
      next_tag_index++;
    }

    // If the tag contains a { character, that is bad.
    if (tag_raw.find("{") != std::string::npos) {
      throw std::invalid_argument("Invalid tag contents.");
    }

    // Write the typed content to the buffer.
    char last_char = type.back();
    const internal::PrintableAny& val = get_tag(tag);
    switch (last_char) {
      // String type.
      case 's':
        result << _WriteToFormatBuffer<const char*>(buffer, type, val);
        break;

      // Character type.
      case 'c':
        result << _WriteToFormatBuffer<char>(buffer, type, val);
        break;

      // Pointer type.
      case 'p':
        result << _WriteToFormatBuffer<void*>(buffer, type, val);
        break;

      // Integer types.
      case 'd':
      case 'o':
      case 'x':
      case 'X':
      case 'i':
        try {
          result << _WriteToFormatBuffer<int>(buffer, type, val);
        } catch (boost::bad_any_cast) {
          try {
            result << _WriteToFormatBuffer<long>(buffer, type, val);
          } catch (boost::bad_any_cast) {
            result << _WriteToFormatBuffer<long long>(buffer, type, val);
          }
        }

        break;

      // Unsigned integer.
      case 'u':
        try {
          result << _WriteToFormatBuffer<unsigned int>(buffer, type, val);
        } catch (boost::bad_any_cast) {
          try {
            result << _WriteToFormatBuffer<unsigned long>(buffer, type, val);
          } catch (boost::bad_any_cast) {
            result << _WriteToFormatBuffer<unsigned long long>(buffer, type,
                                                               val);
          }
        }
        break;

      // Floating point notations.
      case 'g':
      case 'G':
      case 'a':
      case 'A':
      case 'E':
      case 'e':
      case 'F':
      case 'f':
        try {
          result << _WriteToFormatBuffer<float>(buffer, type, val);
        } catch (boost::bad_any_cast) {
          try {
            result << _WriteToFormatBuffer<double>(buffer, type, val);
          } catch (boost::bad_any_cast) {
            result << _WriteToFormatBuffer<long double>(buffer, type, val);
          }
        }

        break;

      // Arbitrary objects. Assume the object supports << notation.
      case ' ':
        val.printer_(result, val);
        break;

      // Unknown types.
      default:
        throw std::invalid_argument("unknown type format");
    }

    // Move to the next tag.
    last_end = end;
    start = fmt.find("{", last_end + 1);
  }

  // Add the rest of the string.
  if (last_end + 1 < fmt.size()) {
    _WriteIntermediateCharacters(fmt.substr(last_end + 1), result);
  }

  return result.str();
}

}  // namespace

std::string FormatMap(const std::string& fmt, const FormatMapType& map) {
  return _Format(fmt, [&map](const std::string& s) { return map.at(s); });
}

std::string Format(const std::string& fmt, const FormatListType& args) {
  return _Format(
      fmt, [&args](const std::string& s) { return args.at(std::stoi(s)); });
}

std::string FormatTrimTags(const std::string& fmt) {
  return _Format(fmt, [](const std::string&) { return ""; });
}

bool FormatHasTag(const std::string& fmt, const std::string& tag) {
  bool has_tag = false;
  _Format(fmt, [&has_tag, &tag](const std::string& t) {
    has_tag = has_tag || (t == tag);
    return "";
  });

  return has_tag;
}

}  // namespace string
