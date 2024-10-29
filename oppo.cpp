#include <cassert>
#include <iomanip>
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

enum class SortOptions : int {
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
    return "";  // Возвращаем пустую строку, если имя не найдено
}

// Функция для получения даты исследования из строки
static std::string GetDate(std::string& in_string) {
    std::regex date_regex(R"((\d{4}\.\d{2}\.\d{2}))");
    std::smatch match;
    if (std::regex_search(in_string, match, date_regex)) {
        std::string date = match[1];    // Получаем дату
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));
        if ((1 <= month && month <= 12) && (1 <= day && day <= 31)) {
            return date;
        }
    }
    return "";  // Возвращаем пустую строку, если дата не найдена
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
    return -1;  // Возвращаем -1, если радиус не найден
}

//Функция дял вывода планет с определенной площадью
static void AreaRange(float min_area, float max_area, std::vector<Planet>& planet_arr) {
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
    if (choice == SortOptions::datesort)
    {
        std::sort(vec.begin(), vec.end(), [](const Planet& planet_1, const Planet& planet_2)
            { return planet_1.date > planet_2.date; });
    }
    else if (choice == SortOptions::areasort) {
        std::sort(vec.begin(), vec.end(), [](const Planet& planet_1, const Planet& planet_2)
            { return planet_1.radius > planet_2.radius; });
    }
    };
