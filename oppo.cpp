#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

const static double PI = 3.14;

class Planet {
public:
    std::string name;
    std::string date;
    double radius;

    Planet(std::string Name, std::string Date, double Radius)
        : name(Name), date(Date), radius(Radius) {}

    double GetArea() const {
        return 4 * PI * radius * radius;
    }

    void Print(std::ostream& output) const {
        output << std::fixed << std::setprecision(2)
            << "Name: " << name
            << "\tDate of the research: " << date
            << "\tRadius: " << radius
            << "\tArea: " << GetArea() << std::endl;
    }
};

enum SortOptions {
    _datesort_,
    _areasort_,
    _printrange_
};

// Функция для получения имени планеты из строки
static std::string GetName(std::string& in_string) {
    std::regex name_regex("([a-zA-Z])+", std::regex_constants::extended);
    std::smatch match;
    if (std::regex_search(in_string, match, name_regex)) {
        return match[0];
    }
    return "";  // Возвращаем пустую строку, если имя не найдено
}

// Функция для получения даты исследования из строки
static std::string GetDate(std::string& in_string) {
    std::regex date_regex(R"((\d{4}\.\d{2}\.\d{2}))");
    std::smatch match;
    if (std::regex_search(in_string, match, date_regex)) {
        std::string date = match[1];    // Получаем дату
        in_string.replace(in_string.find(date), date.length(), "");
        return date;
    }
    return "";  // Возвращаем пустую строку, если дата не найдена
}

// Функция для получения радиуса планеты из строки
static double GetRadius(std::string in_string) {
    std::regex radius_regex(R"(\d+(\.\d+)?)");
    std::smatch match;
    if (std::regex_search(in_string, match, radius_regex)) {
        return std::stod(match[0]); // Возвращаем радиус
    }
    return 0.0;  // Возвращаем 0.0, если радиус не найден
}

//Функция дял вывода планет с определенной площадью
static void AreaRange(int min_area, int max_area, std::vector<Planet>& planet_arr) {
    for (auto it = planet_arr.begin(); it != planet_arr.end(); ) {
        if (!(min_area <= it->GetArea() && max_area >= it->GetArea())) {
            it = planet_arr.erase(it); // Удаление текущего элемента и перенос итератора на следующий
        }
        else {
            ++it; // Переход к следующему элементу
        }
    }
}

auto sortPlanets = [](std::vector<Planet>& vec, int choice) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (choice == _datesort_) {
                if (vec[j].date > vec[j + 1].date) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
            else if (choice == _areasort_) {
                if (vec[j].radius > vec[j + 1].radius) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }
    };

int main() {
    std::vector<Planet> planet_arr;

    std::ifstream input("in.txt");
    if (!input.is_open()) {
        std::cerr << "File did not openned" << std::endl;
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

    std::cout << "Sort by date = 0\nSort by area = 1\nPrint area in range = 2\n";
    int choice; std::cin >> choice;
    switch (choice) {
    case _datesort_:
        sortPlanets(planet_arr, _datesort_);
        break;
    case _areasort_:
        sortPlanets(planet_arr, _areasort_);
        break;
    case _printrange_:
        float area_min, area_max;
        std::cout << "Bottom area: "; std::cin >> area_min;
        std::cout << "Top area: "; std::cin >> area_max;
        AreaRange(area_min, area_max, planet_arr);
    default:
        break;
    }
    for (int i = 0; i < planet_arr.size(); i++) {
        planet_arr[i].Print(std::cout);
    }
}
