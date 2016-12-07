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
