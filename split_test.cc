#include "split.h"

#include <gtest/gtest.h>

TEST(TestSplit, TestSplitWithBasicString) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split("a,b,c", ","));
}

TEST(TestSplit, TestSplitWithMultipleSeps) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split("a,b|c", ",|"));
}

TEST(TestSplit, TestSplitWithSepsAtEndIncludesEmptySpaces) {
  std::vector<std::string> out{"", "a", "b", "c", ""};
  ASSERT_EQ(out, string::Split(",a,b,c,", ","));
}

TEST(TestSplit, TestSplitWithSepsAtEndAndCollapseEmptyGroupsIgnoresSepsAtEnd) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split(",a,b,c,", ",", true));
}

TEST(TestSplit, TestSplitWithCollapseEmptyGroupsIgnoresRepeatedGroups) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split("a,|,b,c", ",|", true));
}

TEST(TestSplit, TestSplitWithNothingButSepsAndCollapseEmptyGroupsReturnsEmpty) {
  std::vector<std::string> out;
  ASSERT_EQ(out, string::Split(",|,,|", ",|", true));
}

TEST(TestSplit, TestSplitWithNothingButSepsReturnsListOfEmptyStrings) {
  std::vector<std::string> out{"", "", "", "", "", ""};
  ASSERT_EQ(out, string::Split(",|,,|", ",|"));
}

TEST(TestSplit, TestSplitWithMultipleIdenticalSeps) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split("a,b|c", ",|,"));
}

TEST(TestSplit, TestSplitWithCollapseGroupsAndMultipleSepsAndEnd) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split("||a,b,c||", ",|", true));
}

TEST(TestSplit, TestSplitWithCollapseGroupsAndOnlySepsAtEnd) {
  std::vector<std::string> out{"abc"};
  ASSERT_EQ(out, string::Split("abc,||", ",|", true));
}

TEST(TestSplit, TestSplitMaxsplitSimple) {
  std::vector<std::string> out{"a", "b", "c,d"};
  ASSERT_EQ(out, string::Split("a,b,c,d", ",", true, 2));
}

TEST(TestSplit, TestSplitMaxsplitIgnoredForLargeValues) {
  std::vector<std::string> out{"a", "b", "c", "d"};
  ASSERT_EQ(out, string::Split("a,b,c,d", ",", true, 10));
}

TEST(TestSplit, TestSplitRespectsMaxsplitWhenCollapsingGroups) {
  std::vector<std::string> out{"a", "b,c||"};
  ASSERT_EQ(out, string::Split("||a,b,c||", ",|", true, 1));
}

TEST(TestSplit, TestSplitRespectsMaxsplitWhenNotCollapsingGroups) {
  std::vector<std::string> out{"", "|a,b,c||"};
  ASSERT_EQ(out, string::Split("||a,b,c||", ",|", false, 1));
}

TEST(TestSplitRight, TestSplitRightWithBasicString) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::Split("a,b,c", ","));
}

TEST(TestSplitRight, TestSplitRightWithMultipleSeps) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::SplitRight("a,b|c", ",|"));
}

TEST(TestSplitRight, TestSplitRightWithSepsAtEndIncludesEmptySpaces) {
  std::vector<std::string> out{"", "a", "b", "c", ""};
  ASSERT_EQ(out, string::SplitRight(",a,b,c,", ","));
}

TEST(TestSplitRight,
     TestSplitRightWithSepsAtEndAndCollapseEmptyGroupsIgnoresSepsAtEnd) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::SplitRight(",a,b,c,", ",", true));
}

TEST(TestSplitRight,
     TestSplitRightWithCollapseEmptyGroupsIgnoresRepeatedGroups) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::SplitRight("a,|,b,c", ",|", true));
}

TEST(TestSplitRight,
     TestSplitRightWithNothingButSepsAndCollapseEmptyGroupsReturnsEmpty) {
  std::vector<std::string> out;
  ASSERT_EQ(out, string::SplitRight(",|,,|", ",|", true));
}

TEST(TestSplitRight,
     TestSplitRightWithNothingButSepsReturnsListOfEmptyStrings) {
  std::vector<std::string> out{"", "", "", "", "", ""};
  ASSERT_EQ(out, string::SplitRight(",|,,|", ",|"));
}

TEST(TestSplitRight, TestSplitRightWithMultipleIdenticalSeps) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::SplitRight("a,b|c", ",|,"));
}

TEST(TestSplitRight, TestSplitRightWithCollapseGroupsAndMultipleSepsAndEnd) {
  std::vector<std::string> out{"a", "b", "c"};
  ASSERT_EQ(out, string::SplitRight("||a,b,c||", ",|", true));
}

TEST(TestSplitRight, TestSplitRightWithCollapseGroupsAndOnlySepsAtEnd) {
  std::vector<std::string> out{"abc"};
  ASSERT_EQ(out, string::SplitRight("abc,||", ",|", true));
}

TEST(TestSplitRight, TestSplitRightMaxsplitSimple) {
  std::vector<std::string> out{"a,b", "c", "d"};
  ASSERT_EQ(out, string::SplitRight("a,b,c,d", ",", true, 2));
}

TEST(TestSplitRight, TestSplitRightMaxsplitIgnoredForLargeValues) {
  std::vector<std::string> out{"a", "b", "c", "d"};
  ASSERT_EQ(out, string::SplitRight("a,b,c,d", ",", true, 10));
}

TEST(TestSplitRight, TestSplitRightRespectsMaxsplitWhenCollapsingGroups) {
  std::vector<std::string> out{"||a,b", "c"};
  ASSERT_EQ(out, string::SplitRight("||a,b,c||", ",|", true, 1));
}

TEST(TestSplitRight, TestSplitRightRespectsMaxsplitWhenNotCollapsingGroups) {
  std::vector<std::string> out{"||a,b,c|", ""};
  ASSERT_EQ(out, string::SplitRight("||a,b,c||", ",|", false, 1));
}

TEST(TestJoin, TestJoinWithNormalList) {
  ASSERT_STREQ("a,b,c", string::Join({"a", "b", "c"}, ",").c_str());
}

TEST(TestJoin, TestJoinWithSingleEntryListHasNoSep) {
  ASSERT_STREQ("a", string::Join({"a"}, ",").c_str());
}

TEST(TestJoin, TestJoinWithMultiCharSeparatorUsesFullSep) {
  ASSERT_STREQ("a,,b,,c", string::Join({"a", "b", "c"}, ",,").c_str());
}

TEST(TestJoin, TestJoinWithEmptyListReturnsEmptyString) {
  ASSERT_STREQ("", string::Join({}, ",").c_str());
}

TEST(TestJoin, TestJoinWithEmptySepJustJoinsCharacters) {
  ASSERT_STREQ("abc", string::Join({"a", "b", "c"}, "").c_str());
}

TEST(TestJoin, TestJoinWithEmptySepAndEmptyListReturnsEmptyString) {
  ASSERT_STREQ("", string::Join({}, "").c_str());
}
