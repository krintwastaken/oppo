#include <iostream>
#include <fstream>

#include "SourceOppo.cpp"
#include "gtest/gtest.h"
#pragma once

TEST(PlanetDataTests, GetNameTest) {
    ASSERT_EQ(GetName(std::string("\"Mars\" 2023.01.01")), "Mars");
    ASSERT_EQ(GetName(std::string("\"Jupiter\" 1999.12.31")), "Jupiter");
    ASSERT_EQ(GetName(std::string("\"Venus\" 2000.01.01")), "Venus");
    ASSERT_EQ(GetName(std::string("2023.01.01")), "");
    ASSERT_EQ(GetName(std::string("")), "");
}

TEST(PlanetDataTests, GetDateTest) {
    ASSERT_EQ(GetDate(std::string("\"Mars\" 2023.01.01")), "2023.01.01");
    ASSERT_EQ(GetDate(std::string("\"Jupiter\" 1999.12.31")), "1999.12.31");
    ASSERT_EQ(GetDate(std::string("\"Venus\" 2000.01.01")), "2000.01.01");
    ASSERT_EQ(GetDate(std::string("\"Mars\" 2023.13.01")), "");
    ASSERT_EQ(GetDate(std::string("\"Jupiter\" 1999.12.32")), "");
    ASSERT_EQ(GetDate(std::string("2023.01.01")), "2023.01.01");
    ASSERT_EQ(GetDate(std::string("")), "");
}

TEST(PlanetDataTests, GetRadiusTest) {
    ASSERT_EQ(GetRadius("\"Mars\" 2023.01.01 3389.5"), 3389.5);
    ASSERT_EQ(GetRadius("\"Jupiter\" 1999.12.31 71492"), 71492.0);
    ASSERT_EQ(GetRadius("\"Venus\" 2000.01.01 6051.8"), 6051.8);
    ASSERT_EQ(GetRadius("\"Mars\" 2023.01.01 -1"), -1);
    ASSERT_EQ(GetRadius("\"Mars\" 2023.01.01"), -1);
    ASSERT_EQ(GetRadius("2023.01.01 3389.5"), 3389.5);
    ASSERT_EQ(GetRadius(""), -1);
}


int main() {
    std::vector<Planet> planet_arr;

    std::ifstream input("in.txt");
    if (!input.is_open()) {
        std::cerr << "File did not openned" << std::endl;
        return -1;
    }
    else {
        std::string input_string;
        while (getline(input, input_string)) {
            std::string name = GetName(input_string),
                date = GetDate(input_string); float radius = GetRadius(input_string);
            Planet planet = { name, date, radius };
            planet_arr.push_back(planet);
        }
    }
    input.close();

    std::cout << "Sort by date = 0\nSort by area = 1\nPrint area in range = 2\nTests = 3\n";
    int choice; std::cin >> choice;
    switch (choice) {
    case static_cast<int>(SortOptions::datesort):
    {
        sortPlanets(planet_arr, SortOptions::datesort);
        break;
    }
    case static_cast<int>(SortOptions::areasort):
    {
        sortPlanets(planet_arr, SortOptions::areasort);
        break;
    }
    case static_cast<int>(SortOptions::printrange):
    {
        float area_min, area_max;
        std::cout << "Bottom area: "; std::cin >> area_min;
        std::cout << "Top area: "; std::cin >> area_max;
        AreaRange(area_min, area_max, planet_arr);
        break;
    }
    case static_cast<int>(SortOptions::tests):
    {
        planet_arr.clear();
        return RUN_ALL_TESTS();
    }
    default:
        break;
    }
    for (int i = 0; i < planet_arr.size(); i++) {
        planet_arr[i].Print(std::cout);
    }
}
