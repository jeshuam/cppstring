#include "util.h"

#include <gtest/gtest.h>

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

TEST(TestTrim, TestTrimWorksWithSingleToken) {
  ASSERT_STREQ("abc", string::Trim("|abc|", "|").c_str());
}

TEST(TestTrim, TestTrimWorksWithMultipleTokens) {
  ASSERT_STREQ("abc", string::Trim("|abc,", "|,").c_str());
}

TEST(TestTrim, TestTrimWorksWithManyJoinedTokensOnEachSide) {
  ASSERT_STREQ("abc", string::Trim(",|abc,|", "|,").c_str());
}

TEST(TestTrim, TestTrimWithOnlyTokensReturnsEmptyString) {
  ASSERT_STREQ("", string::Trim(",|,|", "|,").c_str());
}

TEST(TestTrimRight, TestTrimRightWorksWithSingleToken) {
  ASSERT_STREQ("|abc", string::TrimRight("|abc|", "|").c_str());
}

TEST(TestTrimRight, TestTrimRightWorksWithMultipleTokens) {
  ASSERT_STREQ("|abc", string::TrimRight("|abc,", "|,").c_str());
}

TEST(TestTrimRight, TestTrimRightWorksWithManyJoinedTokensOnEachSide) {
  ASSERT_STREQ(",|abc", string::TrimRight(",|abc,|", "|,").c_str());
}

TEST(TestTrimRight, TestTrimRightWithOnlyTokensReturnsEmptyString) {
  ASSERT_STREQ("", string::TrimRight(",|,|", "|,").c_str());
}

TEST(TestTrimLeft, TestTrimLeftWorksWithSingleToken) {
  ASSERT_STREQ("abc|", string::TrimLeft("|abc|", "|").c_str());
}

TEST(TestTrimLeft, TestTrimLeftWorksWithMultipleTokens) {
  ASSERT_STREQ("abc,", string::TrimLeft("|abc,", "|,").c_str());
}

TEST(TestTrimLeft, TestTrimLeftWorksWithManyJoinedTokensOnEachSide) {
  ASSERT_STREQ("abc,|", string::TrimLeft(",|abc,|", "|,").c_str());
}

TEST(TestTrimLeft, TestTrimLeftWithOnlyTokensReturnsEmptyString) {
  ASSERT_STREQ("", string::TrimLeft(",|,|", "|,").c_str());
}

TEST(TestSimple, TestCapitalize) {
  ASSERT_STREQ("Abc", string::Capitalize("Abc").c_str());
  ASSERT_STREQ("Abc", string::Capitalize("abc").c_str());
  ASSERT_STREQ(";bc", string::Capitalize(";bc").c_str());
  ASSERT_STREQ("", string::Capitalize("").c_str());
}

TEST(TestSimple, TestToLower) {
  ASSERT_STREQ("abc", string::ToLower("aBC").c_str());
  ASSERT_STREQ("abc", string::ToLower("ABC").c_str());
  ASSERT_STREQ(";bc", string::ToLower(";BC").c_str());
  ASSERT_STREQ("", string::ToLower("").c_str());
}

TEST(TestSimple, TestToUpper) {
  ASSERT_STREQ("ABC", string::ToUpper("Abc").c_str());
  ASSERT_STREQ("ABC", string::ToUpper("abc").c_str());
  ASSERT_STREQ(";BC", string::ToUpper(";bc").c_str());
  ASSERT_STREQ("", string::ToUpper("").c_str());
}

TEST(TestReplace, TestReplaceSingleReplacementOfWholeString) {
  ASSERT_STREQ("def", string::Replace("abc", "abc", "def").c_str());
}

TEST(TestReplace, TestReplaceMultipleReplacementOfWholeString) {
  ASSERT_STREQ("defdef", string::Replace("abcabc", "abc", "def").c_str());
}

TEST(TestReplace, TestReplaceLimitNumberOfReplacements) {
  ASSERT_STREQ("defabc", string::Replace("abcabc", "abc", "def", 1).c_str());
}

TEST(TestReplace, TestReplaceDoesNoReplacementsWhenCountIs0) {
  ASSERT_STREQ("abcabc", string::Replace("abcabc", "abc", "def", 0).c_str());
}

TEST(TestReplace, TestReplaceDoesNotReplaceOveralappingReplacements) {
  ASSERT_STREQ("defba", string::Replace("ababa", "aba", "def").c_str());
}
