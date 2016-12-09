#include "format.h"

#include <sstream>
#include <iostream>

#include <string.h>

#include <gflags/gflags.h>

#include "util.h"

DEFINE_uint32(cppstring_format_buffer_bytes, 256,
              "Length of the format string buffer to use in bytes.");

namespace string {

std::string Format(const std::string& fmt,
                   const std::unordered_map<std::string, boost::any>& map) {
	// We have to be fast, so just scan through the string until we find a set of
	// matching {}.
	std::stringstream result;

	size_t start = fmt.find("{"), last_end = -1;
	while (start != std::string::npos) {
		size_t end = fmt.find("}", start + 1);

		// Everything between [start, end] is a tag. So, first add everything from
		// the end of the last tag until now to the string.
		if (last_end + 1 < start) {
			result << fmt.substr(last_end + 1, start - last_end - 1);
		}

		// Parse the tag.
		auto tagRaw = fmt.substr(start + 1, end - start - 1);
		std::string tag = tagRaw, type = "%s";
		if (In(tagRaw, ":")) {
			type = "%" + tagRaw.substr(tagRaw.find(":") + 1);
			tag = tagRaw.substr(0, tagRaw.length() - type.length());
		}

		// Try to substitute this tag in. If it isn't found, throw an exception.
		char buffer[FLAGS_cppstring_format_buffer_bytes];

		// Strings.
		if (EndsWith(type, "s")) {
			snprintf(buffer,
			         FLAGS_cppstring_format_buffer_bytes,
			         type.c_str(), boost::any_cast<const char*>(map.at(tag)));
		}

		// Integers.
		else if (EndsWith(type, "d")) {
			snprintf(buffer,
			         FLAGS_cppstring_format_buffer_bytes,
			         type.c_str(), boost::any_cast<int>(map.at(tag)));
		}

		else if (EndsWith(type, "f")) {
			snprintf(buffer,
			         FLAGS_cppstring_format_buffer_bytes,
			         type.c_str(), boost::any_cast<float>(map.at(tag)));
		}

		// Unknown type!
		else {
			throw std::invalid_argument("unknown type format");
		}

		result << buffer;

		// Move to the next tag.
		last_end = end;
		start = fmt.find("{", last_end + 1);
	}

	// Add the rest of the string.
	if (last_end + 1 < fmt.size()) {
		result << fmt.substr(last_end + 1);
	}

	return result.str();
}

}