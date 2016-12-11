#include <gtest/gtest.h>

#include "format.h"

///
/// Happy Cases.
///
TEST(TestFormatMap, TestFormatMapWithSimpleMap) {
  auto result =
      string::FormatMap("{abc} {def}", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("abc def", result.c_str());
}

TEST(TestFormatMap, TestFormatMapWithNoTags) {
  auto result = string::FormatMap("xxx xxx", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("xxx xxx", result.c_str());
}

TEST(TestFormatMap, TestFormatMapWithExtraCharsAtStartAndEnd) {
  auto result = string::FormatMap("xxx {abc} {def} xxx",
                                  {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("xxx abc def xxx", result.c_str());
}

TEST(TestFormatMap, TestFormatMapWithExtraCharsAtEnd) {
  auto result =
      string::FormatMap("{abc} {def} xxx", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("abc def xxx", result.c_str());
}

TEST(TestFormatMap, TestFormatMapWithExtraCharsAtStart) {
  auto result =
      string::FormatMap("xxx {abc} {def}", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("xxx abc def", result.c_str());
}

TEST(TestFormatMap, TestFormatMapWithExtraCharsInMiddle) {
  auto result =
      string::FormatMap("{abc} xxx {def}", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("abc xxx def", result.c_str());
}

TEST(TestFormatMap, TestFormatMapSpecifyTypeDirectly) {
  auto result =
      string::FormatMap("{abc} xxx {def:s}", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("abc xxx def", result.c_str());
}

TEST(TestFormatMap, TestFormatMapInt) {
  auto result =
      string::FormatMap("{abc} xxx {def:d}", {{"abc", "abc"}, {"def", 10}});
  ASSERT_STREQ("abc xxx 10", result.c_str());
}

TEST(TestFormatMap, TestFormatMapIntComplex) {
  auto result =
      string::FormatMap("{abc} xxx {def:010d}", {{"abc", "abc"}, {"def", 10}});
  ASSERT_STREQ("abc xxx 0000000010", result.c_str());
}

TEST(TestFormatMap, TestFormatMapFloat) {
  auto result = string::FormatMap("{abc} xxx {def:f}",
                                  {{"abc", "abc"}, {"def", 10.2222f}});
  ASSERT_STREQ("abc xxx 10.222200", result.c_str());
}

TEST(TestFormatMap, TestFormatMapFloatComplex) {
  auto result = string::FormatMap("{abc} xxx {def:.3f}",
                                  {{"abc", "abc"}, {"def", 10.2564f}});
  ASSERT_STREQ("abc xxx 10.256", result.c_str());
}

struct ComplexObject {
  int x, y;
};

std::ostream& operator<<(std::ostream& os, const ComplexObject& o) {
  return os << "(" << o.x << ", " << o.y << ")";
}

TEST(TestFormatMap, TestFormatMapComplexObject) {
  auto result = string::FormatMap("{abc}", {{"abc", ComplexObject{1, 2}}});
  ASSERT_STREQ("(1, 2)", result.c_str());
}

TEST(TestFormatMap, TestFormatMapShowLeftBrackets) {
  ASSERT_STREQ("{{abc", string::FormatMap("{{abc", {}).c_str());
}

TEST(TestFormatMap, TestFormatMapShowRightBrackets) {
  ASSERT_STREQ("abc}}", string::FormatMap("abc}}", {}).c_str());
}

TEST(TestFormatMap, TestFormatMapShowBothBrackets) {
  ASSERT_STREQ("{{abc}}", string::FormatMap("{{abc}}", {}).c_str());
}

TEST(TestFormatMap, TestFormatMapShowMixedBrackets) {
  ASSERT_STREQ("{{abc}}",
               string::FormatMap("{{{abc}}}", {{"abc", "abc"}}).c_str());
}

TEST(TestFormatMap, TestFormatMapWithAllTypes) {
  auto obj = ComplexObject{1, 2};
  auto result = string::FormatMap(
      "{obj};"
      "{s:s};"
      "{c:c};"
      "{p:p};"
      "{d:d};{d:o};{d:x};{d:X};{d:i};{l:ld};{ll:lld};"
      "{u:u};{lu:lu};{llu:llu};"
      "{f:g};{f:G};{f:a};{f:A};{f:e};{f:E};{f:f};{f:F};"
      "{D:f};{DD:Lf};",
      {
          {"obj", obj},
          {"s", "s"},
          {"c", 'c'},
          {"p", (void*)nullptr},
          {"d", 10},
          {"l", 100L},
          {"ll", 1000LL},
          {"u", 20U},
          {"lu", 20LU},
          {"llu", 20LLU},
          {"f", 1.34f},
          {"D", 1.34},
          {"DD", 1.34L},
      });

#ifdef OS_WINDOWS
  ASSERT_STREQ(
      "(1, 2);"
      "s;"
      "c;"
      "0000000000000000;"
      "10;12;a;A;10;100;1000;"
      "20;20;20;"
      "1.34;1.34;0x1.570a3e0000000p+0;0X1.570A3E0000000P+0;1.340000e+00;1."
      "340000E+00;1.340000;1.340000;"
      "1.340000;1.340000;",
      result.c_str());
#else
  ASSERT_STREQ(
      "(1, 2);"
      "s;"
      "c;"
      "(nil);"
      "10;12;a;A;10;100;1000;"
      "20;20;20;"
      "1.34;1.34;0x1.570a3ep+0;0X1.570A3EP+0;1.340000e+00;1.340000E+00;1."
      "340000;1.340000;"
      "1.340000;1.340000;",
      result.c_str());
#endif
}

///
/// Error Cases
///
TEST(TestFormatMap, TestFormatMapWithMismatchedLeftBrackets) {
  ASSERT_THROW(string::FormatMap("{", {}), std::invalid_argument);
}

TEST(TestFormatMap, TestFormatMapWithMismatchedRightBrackets) {
  ASSERT_THROW(string::FormatMap("{abc}}", {{"abc", "abc"}}),
               std::invalid_argument);
}

TEST(TestFormatMap, TestFormatMapWithInvalidTagContent) {
  ASSERT_THROW(string::FormatMap("{ {}", {}), std::invalid_argument);
}
