#include "test.h"
#include "class.h"

#include <iostream>
#include <fstream>

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
            std::string name = Planet::GetName(input_string),
                date = Planet::GetDate(input_string); 
            double radius = Planet::GetRadius(input_string);
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
        Planet::sortPlanets(planet_arr, SortOptions::datesort);
        break;
    }
    case static_cast<int>(SortOptions::areasort):
    {
        Planet::sortPlanets(planet_arr, SortOptions::areasort);
        break;
    }
    case static_cast<int>(SortOptions::printrange):
    {
        float area_min, area_max;
        std::cout << "Bottom area: "; std::cin >> area_min;
        std::cout << "Top area: "; std::cin >> area_max;
        Planet::AreaRange(area_min, area_max, planet_arr);
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