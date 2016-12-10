#include <gtest/gtest.h>

#include "format.h"

///
/// Happy Cases.
///
TEST(TestFormat, TestFormatWithSimpleMap) {
	auto result = string::Format("{abc} {def}", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("abc def", result.c_str());
}

TEST(TestFormat, TestFormatWithNoTags) {
	auto result = string::Format("xxx xxx", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("xxx xxx", result.c_str());
}

TEST(TestFormat, TestFormatWithExtraCharsAtStartAndEnd) {
	auto result = string::Format("xxx {abc} {def} xxx", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("xxx abc def xxx", result.c_str());
}

TEST(TestFormat, TestFormatWithExtraCharsAtEnd) {
	auto result = string::Format("{abc} {def} xxx", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("abc def xxx", result.c_str());
}

TEST(TestFormat, TestFormatWithExtraCharsAtStart) {
	auto result = string::Format("xxx {abc} {def}", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("xxx abc def", result.c_str());
}

TEST(TestFormat, TestFormatWithExtraCharsInMiddle) {
	auto result = string::Format("{abc} xxx {def}", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("abc xxx def", result.c_str());
}

TEST(TestFormat, TestFormatSpecifyTypeDirectly) {
	auto result = string::Format("{abc} xxx {def:s}", {{"abc", "abc"}, {"def", "def"}});
	ASSERT_STREQ("abc xxx def", result.c_str());
}

TEST(TestFormat, TestFormatInt) {
	auto result = string::Format("{abc} xxx {def:d}", {{"abc", "abc"}, {"def", 10}});
	ASSERT_STREQ("abc xxx 10", result.c_str());
}

TEST(TestFormat, TestFormatIntComplex) {
	auto result = string::Format("{abc} xxx {def:010d}", {{"abc", "abc"}, {"def", 10}});
	ASSERT_STREQ("abc xxx 0000000010", result.c_str());
}

TEST(TestFormat, TestFormatFloat) {
	auto result = string::Format("{abc} xxx {def:f}", {{"abc", "abc"}, {"def", 10.2222f}});
	ASSERT_STREQ("abc xxx 10.222200", result.c_str());
}

TEST(TestFormat, TestFormatFloatComplex) {
	auto result = string::Format("{abc} xxx {def:.3f}", {{"abc", "abc"}, {"def", 10.2564f}});
	ASSERT_STREQ("abc xxx 10.256", result.c_str());
}

struct ComplexObject {
	int x, y;
};

std::ostream& operator<<(std::ostream& os, const ComplexObject& o) {
	return os << "(" << o.x << ", " << o.y << ")";
}

TEST(TestFormat, TestFormatComplexObject) {
	auto result = string::Format("{abc}", {{"abc", ComplexObject{1, 2}}});
	ASSERT_STREQ("(1, 2)", result.c_str());
}

TEST(TestFormat, TestFormatShowLeftBrackets) {
	ASSERT_STREQ("{{abc", string::Format("{{abc", {}).c_str());
}

TEST(TestFormat, TestFormatShowRightBrackets) {
	ASSERT_STREQ("abc}}", string::Format("abc}}", {}).c_str());
}

TEST(TestFormat, TestFormatShowBothBrackets) {
	ASSERT_STREQ("{{abc}}", string::Format("{{abc}}", {}).c_str());
}

TEST(TestFormat, TestFormatShowMixedBrackets) {
	ASSERT_STREQ("{{abc}}", string::Format("{{{abc}}}", {{"abc", "abc"}}).c_str());
}

TEST(TestFormat, TestFormatWithAllTypes) {
	auto obj = ComplexObject{1, 2};
	auto result = string::Format(
	                "{obj};"
	                "{s:s};"
	                "{c:c};"
	                "{p:p};"
	                "{d:d};{d:o};{d:x};{d:X};{d:i};{l:ld};{ll:lld};"
	                "{u:u};{lu:lu};{llu:llu};"
	                "{f:g};{f:G};{f:a};{f:A};{f:e};{f:E};{f:f};{f:F};"
	"{D:f};{DD:Lf};", {
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

	ASSERT_STREQ(
	  "(1, 2);"
	  "s;"
	  "c;"
	  "(nil)"
	  ";10;12;a;A;10;100;1000;"
	  "20;20;20;"
	  "1.34;1.34;0x1.570a3ep+0;0X1.570A3EP+0;1.340000e+00;1.340000E+00;1.340000;1.340000;"
	  "1.340000;1.340000;",
	  result.c_str());
}

///
/// Error Cases
///
TEST(TestFormat, TestFormatWithMismatchedLeftBrackets) {
	ASSERT_THROW(string::Format("{", {}), std::invalid_argument);
}

TEST(TestFormat, TestFormatWithMismatchedRightBrackets) {
	ASSERT_THROW(string::Format("{abc}}", {{"abc", "abc"}}), std::invalid_argument);
}

TEST(TestFormat, TestFormatWithInvalidTagContent) {
	ASSERT_THROW(string::Format("{ {}", {}), std::invalid_argument);
}