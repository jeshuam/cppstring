#include <gtest/gtest.h>

#include "format.h"

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

