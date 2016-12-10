#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include <iostream>

#include <boost/any.hpp>

namespace string {

namespace internal {

// Wrapper around boost::any which allows it to be printed.
struct PrintableAny : boost::any {
	template <typename T> PrintableAny(T t)
		: boost::any(t),
		  printer_(
		    [](std::ostream & os,
		       const boost::any & a) { os << boost::any_cast<const T&>(a); }) {}

	std::function<void(std::ostream&, const boost::any&)> printer_;
};

// Add a custom overwrite for char arrays, to allow users to pass raw strings as
// arguments.
template<>
PrintableAny::PrintableAny(const char t[]);

}

// Errors if:
//   fmt has nested tags.
//   fmt has incomplete tags.
//   fmt has char not found in map.
//   fmt has char with type error.
std::string Format(
  const std::string& fmt,
  const std::unordered_map<std::string, internal::PrintableAny>& args);

}