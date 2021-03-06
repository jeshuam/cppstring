#include "format.h"

#include <gflags/gflags.h>
#include <gtest/gtest.h>

DECLARE_uint32(cppstring_format_buffer_bytes);

///
/// Happy Cases.
///
TEST(TestFormatMap, TestFormatMapWithSimpleMap) {
  auto result =
      string::FormatMap("{abc} {def}", {{"abc", "abc"}, {"def", "def"}});
  ASSERT_STREQ("abc def", result.c_str());
}

TEST(TestFormatMap, TestFormatMapWithCharArray) {
  char abc[] = "abc";
  char def[] = "def";
  auto result = string::FormatMap("{abc} {def}", {{"abc", abc}, {"def", def}});
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
  ASSERT_STREQ("{{abc", string::FormatMap("{{abc", {{"abc", 0}}).c_str());
}

TEST(TestFormatMap, TestFormatMapShowRightBrackets) {
  ASSERT_STREQ("abc}}", string::FormatMap("abc}}", {{"abc", 0}}).c_str());
}

TEST(TestFormatMap, TestFormatMapShowBothBrackets) {
  ASSERT_STREQ("{{abc}}", string::FormatMap("{{abc}}", {{"abc", 0}}).c_str());
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

TEST(TestFormat, TestFormatWorksWithTagsSet) {
  ASSERT_STREQ("1x1", string::Format("{0}{1}{0}", {1, "x"}).c_str());
}

TEST(TestFormat, TestFormatWorksWithTagsNotSet) {
  ASSERT_STREQ("1x2", string::Format("{}{}{}", {1, "x", 2}).c_str());
}

TEST(TestFormat, TestFormatWorksWithInconsistentTagging) {
  ASSERT_STREQ("12x", string::Format("{}{2}{}", {1, "x", 2}).c_str());
}

TEST(TestFormat, TestFormatWorksWhenSkippingTags) {
  ASSERT_STREQ("12", string::Format("{0}{2}", {1, "x", 2}).c_str());
}

TEST(TestFormatTrimTags, TestFormatTrimTagsWithNoTags) {
  ASSERT_STREQ("blah", string::FormatTrimTags("blah").c_str());
}

TEST(TestFormatTrimTags, TestFormatTrimTagsWithSomeTags) {
  ASSERT_STREQ("blah  blah ",
               string::FormatTrimTags("blah {abc} blah {def}").c_str());
}

TEST(TestFormatTrimTags, TestFormatTrimTagsWithNoTagsButCurlyBrackets) {
  ASSERT_STREQ("{{blah}}", string::FormatTrimTags("{{blah}}").c_str());
}

TEST(TestFormatTrimTags, TestFormatTrimTagsWithTagsAndEscapedBrackets) {
  ASSERT_STREQ("{{}}", string::FormatTrimTags("{{{blah}}}").c_str());
}

TEST(TestFormatHasTag, TestFormatHasTagWithNoTags) {
  ASSERT_FALSE(string::FormatHasTag("blah", "tag"));
}

TEST(TestFormatHasTag, TestFormatHasTagWithManyTagsButNoneMatch) {
  ASSERT_FALSE(string::FormatHasTag("blah {abc} blah {def}", "aaa"));
}

TEST(TestFormatHasTag, TestFormatHasTagWithManyTagsWhichMatch) {
  ASSERT_TRUE(string::FormatHasTag("blah {abc} blah {def}", "abc"));
}

TEST(TestFormatHasTag, TestFormatHasTagWithEscapedTagsButNoTags) {
  ASSERT_FALSE(string::FormatHasTag("{{blah}}", "blah"));
}

TEST(TestFormatHasTag, TestFormatHasTagWithEscapedTagsAndTagsButNoneMatch) {
  ASSERT_FALSE(string::FormatHasTag("{{{blah}}}", "abc"));
}

TEST(TestFormatHasTag, TestFormatHasTagWithEscapedTagsAndTagsWhichMatch) {
  ASSERT_TRUE(string::FormatHasTag("{{{blah}}}", "blah"));
}

///
/// Error Cases
///
TEST(TestFormatMap, TestFormatMapWithMismatchedLeftBrackets) {
  ASSERT_THROW(string::FormatMap("{", {{"abc", "abc"}}), std::invalid_argument);
}

TEST(TestFormatMap, TestFormatMapWithMismatchedRightBrackets) {
  ASSERT_THROW(string::FormatMap("{abc}}", {{"abc", "abc"}}),
               std::invalid_argument);
}

TEST(TestFormatMap, TestFormatMapWithInvalidTagContent) {
  ASSERT_THROW(string::FormatMap("{ {}", {{"abc", "abc"}}),
               std::invalid_argument);
}

TEST(TestFormatMap, TestFormatMapWithInvalidType) {
  ASSERT_THROW(string::FormatMap("{abc:W}", {{"abc", "ABC"}}),
               std::invalid_argument);
}

TEST(TestFormatMap, TestFormatMapWithVeryLongFormat) {
  auto old_val = FLAGS_cppstring_format_buffer_bytes;
  FLAGS_cppstring_format_buffer_bytes = 1;

  ASSERT_THROW(string::FormatMap("{abc:d}", {{"abc", 1000000}}),
               std::invalid_argument);

  FLAGS_cppstring_format_buffer_bytes = old_val;
}

TEST(TestFormatMap, TestFormatMapFailsWithUnrecognizedTag) {
  ASSERT_THROW(string::FormatMap("{abc} {def}", {{"abc", "ABC"}}),
               std::out_of_range);
}

TEST(TestFormatMap, TestFormatMapDoesNotFailsWithUnrecognizedTagIfFlagSet) {
  ASSERT_STREQ(
      "ABC {def}",
      string::FormatMap("{abc} {def}", {{"abc", "ABC"}}, true).c_str());
}
