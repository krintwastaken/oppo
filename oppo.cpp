#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const static double PI = 3.14159265;

class Planet {
public:
    std::string name;
    std::string date;
    double radius;

    Planet(std::string Name, std::string Date, double Radius) {
        name = Name;
        date = Date;
        radius = Radius;
    }

    double get_area() const { return 4 * PI * radius * radius; }

    void print() const {
        std::cout << std::fixed << std::setprecision(2) << "Name: " << name
            << "\t Date of the research: " << date << "\t Radius: " << radius
            << std::endl;
    }

    Planet() = default;
};

// Функция для получения имени планеты из строки
static std::string GetName(std::string &a) {
    int count = 0, pos1, pos2;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '"') {
            if (count == 0) {
                pos1 = i;
            }else {
                pos2 = i - pos1 + 1;
                std::string name = a.substr(pos1, pos2);
                a.erase(pos1, pos2 + 1);
                return name;
            }
            count += 1;
        }
    }
    return "";  // Возвращаем пустую строку, если имя не найдено
}

// Функция для получения даты исследования из строки
static std::string GetDate(std::string &a) {
    for (int i = 0; i < a.length(); i++) {
        if (a[i] == '.' && a[i + 3] == '.') {
            int year = stoi(a.substr(i - 4, 4)),
                month = stoi(a.substr(i + 1, 2)),
                day = stoi(a.substr(i + 4, 2));
            if ((1 <= month && month <= 12) && (1 <= day && day <= 31)) {
                std::string date = a.substr(i - 4, 10);
                a.erase(i - 4, 10);
                return date;
            }
            else {
                std::cout << "incorrect date in " << a.substr(i - 4, 10)
                    << std::endl;
                return "";
            }
        }
    }
    return "";  // Возвращаем пустую строку, если дата не найдена
}

// Функция для получения радиуса планеты из строки
static float GetRadius(std::string a) {
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != ' ') {
            return stof(a.substr(i, a.length()));
        }
    }
    return 0.0;  // Возвращаем 0.0, если радиус не найден
}

//Функция дял вывода планет с определенной площадью
static bool AreaRange(int a1, int a2, int area) {
    if (a1 <= area && area <= a2) {
        return true;
    }
    else {
        return false;
    }
}

// Функция для сортировки вектора Planet по дате
static void DateSort(std::vector<Planet>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j].date > vec[j + 1].date) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// Функция для сортировки вектора Planet по площади
static void AreaSort(std::vector<Planet>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j].radius > vec[j + 1].radius) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

int main() {
    std::ifstream in("in.txt");
    std::vector<Planet> planet_arr;
    if (!in.is_open()) {
        std::cerr << "File did not openned" << std::endl;
        exit(-1);
    }
    else {
        std::string s;
        while (getline(in, s)) {
            std::string name = GetName(s), date = GetDate(s); float radius = GetRadius(s);
            Planet planet = { name, date, radius };
            planet_arr.push_back(planet);
        }
    }
    in.close();

    int choice;
    std::cout << "DateSort = 1\nAreaSort = 2\nAreaRangePrint = 3\n";
    std::cin >> choice;
    switch (choice) {
    case 1:
        DateSort(planet_arr);
        for (int i = 0; i < planet_arr.size(); i++) {
            planet_arr[i].print();
        }
        break;
    case 2:
        AreaSort(planet_arr);
        for (int i = 0; i < planet_arr.size(); i++) {
            planet_arr[i].print();
            std::cout << "Area: " << planet_arr[i].get_area() << std::endl;
        }
        break;
    case 3:
        float Area1, Area2;
        std::cout << "Area_1: "; std::cin >> Area1;
        std::cout << "Area_2: "; std::cin >> Area2;
        for (int i = 0; i < planet_arr.size(); i++) {
            if (AreaRange(Area1, Area2, planet_arr[i].get_area())) {
                planet_arr[i].print();
                std::cout << "Area: " << planet_arr[i].get_area() << std::endl;
            }
        }
    }
    return 0;
}
