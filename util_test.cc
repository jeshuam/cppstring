#include <gtest/gtest.h>

#include "util.h"

TEST(TestCount, TestReturns0ForEmptySourceString) {
  ASSERT_EQ(0, string::Count("", "search"));
}

TEST(TestCount, TestReturns0ForEmptySearchString) {
  ASSERT_EQ(0, string::Count("search", ""));
}

TEST(TestCount, TestReturnsSingleMatch) {
  ASSERT_EQ(1, string::Count("search", "ea"));
}

TEST(TestCount, TestReturnsMultipleMatches) {
  ASSERT_EQ(2, string::Count("searchea", "ea"));
}

TEST(TestCount, TestDoesNotReturnOverlappingMatches) {
  ASSERT_EQ(1, string::Count("sasas", "sas"));
}

TEST(TestCount, TestIsCaseSensitive) {
  ASSERT_EQ(0, string::Count("SAS", "sas"));
}

TEST(TestEndsWith, TestReturnsTrueForSuffix) {
  ASSERT_TRUE(string::EndsWith("main.cc", ".cc"));
}

TEST(TestEndsWith, TestReturnsFalseForPrefix) {
  ASSERT_FALSE(string::EndsWith("main.cc", "main"));
}

TEST(TestEndsWith, TestReturnsFalseWhenSuffixEmpty) {
  ASSERT_FALSE(string::EndsWith("main.cc", ""));
}

TEST(TestEndsWith, TestReturnsFalseWhenStrEmpty) {
  ASSERT_FALSE(string::EndsWith("", "suffix"));
}

TEST(TestEndsWith, TestReturnsTrueWhenWholeStringMatches) {
  ASSERT_TRUE(string::EndsWith("suffix", "suffix"));
}

TEST(TestEndsWith, TestReturnsFalseWhenSuffixLongerThanString) {
  ASSERT_FALSE(string::EndsWith("suffix", "suffixsuffix"));
}
