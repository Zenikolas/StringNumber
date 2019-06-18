#include <stringnumber.h>

#include <gtest/gtest.h>

TEST(StringNumberTest, sumSmoke)
{
    scientific::StringNumber lhs("100");
    scientific::StringNumber rhs("100");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("200"));
}

TEST(StringNumberTest, sumZero)
{
    scientific::StringNumber lhs("100");
    scientific::StringNumber rhs("-100");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("0"));
}

TEST(StringNumberTest, sumExtendOrder)
{
    scientific::StringNumber lhs("999");
    scientific::StringNumber rhs("1");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("1000"));
}

TEST(StringNumberTest, sumNegative)
{
    scientific::StringNumber lhs("-99999");
    scientific::StringNumber rhs("-11111");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("-111110"));
}

TEST(StringNumberTest, subNegativeGreat)
{
    scientific::StringNumber lhs("11111");
    scientific::StringNumber rhs("-99999");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("-88888"));
}

TEST(StringNumberTest, subNegativeLess)
{
    scientific::StringNumber lhs("-11111");
    scientific::StringNumber rhs("99999");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("88888"));
}

TEST(StringNumberTest, subDiffSizes)
{
    scientific::StringNumber lhs("-9099");
    scientific::StringNumber rhs("19");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("-9080"));
}

TEST(StringNumberTest, subDiffSizesSwapped)
{
    scientific::StringNumber lhs("19");
    scientific::StringNumber rhs("-9099");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("-9080"));
}

TEST(StringNumberTest, subDiffSizesOpposite)
{
    scientific::StringNumber lhs("-19");
    scientific::StringNumber rhs("9099");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("9080"));
}

TEST(StringNumberTest, subLong)
{
    scientific::StringNumber lhs("-909999999999999999999999999");
    scientific::StringNumber rhs("199999999999999999999999999");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("-710000000000000000000000000"));
}

TEST(StringNumberTest, sumLong)
{
    scientific::StringNumber lhs("909999999999999999999999999");
    scientific::StringNumber rhs("199999999999999999999999999");
    scientific::StringNumber res = lhs + rhs;
    ASSERT_EQ(res, scientific::StringNumber("1109999999999999999999999998"));
}