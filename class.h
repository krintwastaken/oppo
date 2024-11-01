
#pragma once

#include <cassert>
#include <iomanip>
#include <regex>
#include <string>
#include <vector>

const double PI = 3.14159265358979323846;

enum class SortOptions : int {
    datesort = 0,
    areasort,
    printrange,
    tests
};

class Planet {
public:
    std::string name;
    std::string date;
    double radius;

    Planet(std::string Name, std::string Date, double Radius)
        : name(Name), date(Date), radius(Radius) {}

    double GetArea() const { return 4 * PI * radius * radius; }
    void Print(std::ostream& output) const;
    static std::string GetName( std::string in_string);
    static std::string GetDate( std::string in_string);
    static double GetRadius( std::string in_string);
    static void AreaRange( float min_area,  float max_area,
         std::vector<Planet> planet_arr);
    static void sortPlanets(std::vector<Planet>& vec, SortOptions choice);
};