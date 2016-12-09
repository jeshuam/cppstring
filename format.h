#pragma once

#include <string>
#include <unordered_map>

#include <boost/any.hpp>

namespace string {

// Errors if:
//   fmt has nested tags.
//   fmt has incomplete tags.
//   fmt has char not found in map.
//   fmt has char with type error.
std::string Format(const std::string& fmt,
                   const std::unordered_map<std::string, boost::any>& args);

}