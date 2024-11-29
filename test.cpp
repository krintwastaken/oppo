#include "test.h"
#include "class.h"

TEST(PlanetDataTests, GetNameTest) {
    ASSERT_EQ(Planet::GetName(std::string("\"Mars\" 2023.01.01")), "Mars");
    ASSERT_EQ(Planet::GetName(std::string("\"Jupiter\" 1999.12.31")), "Jupiter");
    ASSERT_EQ(Planet::GetName(std::string("\"Venus\" 2000.01.01")), "Venus");
    ASSERT_EQ(Planet::GetName(std::string("2023.01.01")), "");
    ASSERT_EQ(Planet::GetName(std::string("")), "");
}

TEST(PlanetDataTests, GetDateTest) {
    ASSERT_EQ(Planet::GetDate(std::string("\"Mars\" 2023.01.01")), "2023.01.01");
    ASSERT_EQ(Planet::GetDate(std::string("\"Jupiter\" 1999.12.31")), "1999.12.31");
    ASSERT_EQ(Planet::GetDate(std::string("\"Venus\" 2000.01.01")), "2000.01.01");
    ASSERT_EQ(Planet::GetDate(std::string("\"Mars\" 2023.13.01")), "");
    ASSERT_EQ(Planet::GetDate(std::string("\"Jupiter\" 1999.12.32")), "");
    ASSERT_EQ(Planet::GetDate(std::string("2023.01.01")), "2023.01.01");
    ASSERT_EQ(Planet::GetDate(std::string("")), "");
}

TEST(PlanetDataTests, GetRadiusTest) {
    ASSERT_EQ(Planet::GetRadius("\"Mars\" 2023.01.01 3389.5"), 3389.5);
    ASSERT_EQ(Planet::GetRadius("\"Jupiter\" 1999.12.31 71492"), 71492.0);
    ASSERT_EQ(Planet::GetRadius("\"Venus\" 2000.01.01 6051.8"), 6051.8);
    ASSERT_EQ(Planet::GetRadius("\"Mars\" 2023.01.01 -1"), -1);
    ASSERT_EQ(Planet::GetRadius("\"Mars\" 2023.01.01"), -1);
    ASSERT_EQ(Planet::GetRadius("2023.01.01 3389.5"), 3389.5);
    ASSERT_EQ(Planet::GetRadius(""), -1);
}