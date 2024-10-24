#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

const double PI = 3.14159265358979323846;

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

enum class SortOptions  : int {
    datesort = 0,
    areasort,
    printrange,
    tests
};

// Функция для получения имени планеты из строки
static std::string GetName(std::string& in_string) {
    std::regex name_regex("([a-zA-Z])+", std::regex_constants::extended);
    std::smatch match;
    if (std::regex_search(in_string, match, name_regex)) {
        return match[0];
    }
    return "N/A";  // Возвращаем пустую строку, если имя не найдено
}

// Функция для получения даты исследования из строки
static std::string GetDate(std::string& in_string) {
    std::regex date_regex(R"((\d{4}\.\d{2}\.\d{2}))");
    std::smatch match;
    if (std::regex_search(in_string, match, date_regex)) {
        std::string date = match[1];    // Получаем дату
        int month = std::stoi(date.substr(5, 2)); 
        int day = std::stoi(date.substr(8, 2));
        if ((1 <= month && month <= 12) && (1 <= day && day <= 31))
        return date;
    }
    return "0000.00.00";  // Возвращаем пустую строку, если дата не найдена
}

// Функция для получения радиуса планеты из строки
static double GetRadius(std::string in_string) {
    std::regex pattern(R"((\d{4}\.\d{2}\.\d{2})|([-+]?\d+([,\.]\d+)?))");
    std::smatch matches;
    std::string fractionalNumber, date;
    {
        while (std::regex_search(in_string, matches, pattern)) {
            if (matches[1].matched) {
                date = matches[1].str(); // извлекаем дату
            }
            else {
                fractionalNumber = matches[2].str(); // извлекаем дробное число
            }
            in_string = matches.suffix().str(); // обновляем строку для следующего поиска
        }
        if (fractionalNumber != "" && std::stod(fractionalNumber) >= 0) {
            return std::stod(fractionalNumber);
        }
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

auto sortPlanets = [](std::vector<Planet>& vec, SortOptions choice) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (choice == SortOptions::datesort) {
                if (vec[j].date > vec[j + 1].date) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
            else if (choice == SortOptions::areasort) {
                if (vec[j].radius > vec[j + 1].radius) {
                    std::swap(vec[j], vec[j + 1]);
                }
            }
        }
    }
 };

void testGetName() {
    std::string input1 = "Earth 2023.05.20 6371.0";
    assert(GetName(input1) == "Earth");

    std::string input2 = "2023.05.20 6371.0";
    assert(GetName(input2) == "N/A");

    std::cout << "GetName test passed." << std::endl;
}

void testGetDate() {
    std::string input1 = "Earth 2023.05.20 6371.0";
    assert(GetDate(input1) == "2023.05.20");

    std::string input2 = "Earth 6371.0";
    assert(GetDate(input2) == "0000.00.00");

    std::string input3 = "Earth 2023.15.20 6371.0";
    assert(GetDate(input3) == "0000.00.00");

    std::cout << "GetDate test passed." << std::endl;
}

void testGetRadius() {
    std::string input1 = "Earth 2023.05.20 6371.0";
    assert(GetRadius(input1) == 6371.0);

    std::string input2 = "Earth 2023.05.20";
    assert(GetRadius(input2) == 0.0);

    std::string input3 = "Earth 2023.05.20 -6371.0";
    assert(GetRadius(input3) == 0.0);

    std::cout << "GetRadius test passed." << std::endl;
}

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
        testGetName();
        testGetDate();
        testGetRadius();
        break;
    }
    default:
        break;
    }
    for (int i = 0; i < planet_arr.size(); i++) {
        planet_arr[i].Print(std::cout);
    }
}
