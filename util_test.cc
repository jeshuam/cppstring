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

TEST(TestIn, TestReturnsFalseForEmptySourceString) {
  ASSERT_FALSE(string::In("", "search"));
}

TEST(TestIn, TestReturnsFalseForEmptySearchString) {
  ASSERT_FALSE(string::In("search", ""));
}

TEST(TestIn, TestReturnsSingleMatch) {
  ASSERT_TRUE(string::In("search", "ea"));
}

TEST(TestIn, TestReturnsMultipleMatches) {
  ASSERT_TRUE(string::In("searchea", "ea"));
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

TEST(TestStartsWith, TestReturnsFalseForSuffix) {
  ASSERT_FALSE(string::StartsWith("main.cc", ".cc"));
}

TEST(TestStartsWith, TestReturnsTrueForPrefix) {
  ASSERT_TRUE(string::StartsWith("main.cc", "main"));
}

TEST(TestStartsWith, TestReturnsFalseWhenPrefixEmpty) {
  ASSERT_FALSE(string::StartsWith("main.cc", ""));
}

TEST(TestStartsWith, TestReturnsFalseWhenStrEmpty) {
  ASSERT_FALSE(string::StartsWith("", "prefix"));
}

TEST(TestStartsWith, TestReturnsTrueWhenWholeStringMatches) {
  ASSERT_TRUE(string::StartsWith("prefix", "prefix"));
}

TEST(TestStartsWith, TestReturnsFalseWhenPrefixLongerThanString) {
  ASSERT_FALSE(string::StartsWith("prefix", "prefixprefix"));
}
