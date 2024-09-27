//Чумутин Е. КИ23-07Б

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
	};

	double get_area() const {
		return 4 * PI * radius * radius;
	};

	void print() const{
		std::cout << std::fixed << std::setprecision(2) <<
			"Name: " << name << "\t Date of the research: " 
			<< date << "\t Radius: " << radius << std::endl;
	}

	Planet() = default;
};

static std::string get_name(std::string a) {
	int count = 0;
	int pos1, pos2;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '"') {
			if (count == 0) {
				pos1 = i;
			}
			if (count == 1) {
				pos2 = i - pos1 + 1;
				return a.substr(pos1, pos2);
			}
			count += 1;
		}
	}
}

static std::string get_date(std::string a) {
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '.' && a[i + 3] == '.') {
			int year = stoi(a.substr(i - 4, 4)), month = stoi(a.substr(i + 1, 2)), day = stoi(a.substr(i + 4, 2));
			if ((1 <= month && month <= 12) && (1 <= day && day <= 31)) {
				return a.substr(i - 4, 10);
			}
			else {
				std::cout << "incorrect date in " << a.substr(i - 4, 10);
				exit(-1);
			}
		}
	}
}

static float get_radius(std::string a) {
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '.' && a[i + 3] == '.') {
			a.erase(i - 4, 11);
			break;
		}
	}
	int pos1, pos2, count1 = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '\"') {
			if (count1 == 0) {
				pos1 = i;
			}
			if (count1 == 1) {
				pos2 = i;
				a.erase(pos1, pos2 + 1);
				break;
			}
			count1 += 1;
		}
	}
	for (int i = 0; i < a.length(); i++) {
		if (a[i] != ' ') {
			return stof(a.substr(i, a.length()));
		}
	}
}

static void area_sort(std::vector<Planet>& vec) {
	int n = vec.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (vec[j].radius > vec[j + 1].radius) {
				std::swap(vec[j], vec[j + 1]);
			}
		}
	}
}

static void date_sort(std::vector<Planet>& vec) {
	int n = vec.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (vec[j].date > vec[j + 1].date) {
				std::swap(vec[j], vec[j + 1]);
			}
		}
	}
}

int main() {
	std::string s;
	std::ifstream in("in.txt");
	std::vector <Planet> planet_arr;
	if (!in.is_open()) {
		std::cerr << "File did not openned";
		exit(-1);
	}
	else {
		std::string s; int count = 0;
		while (getline(in, s)) {
			Planet planet = { get_name(s), get_date(s), get_radius(s) };
			planet_arr.push_back(planet);
			count += 1;
		}
	}
	in.close();

	int choice;
	std::cout << "date_sort = 1\narea_sort = 2\n";
	std::cin >> choice;
	switch (choice) {
	case 1:
		date_sort(planet_arr);
		for (int i = 0; i < planet_arr.size(); i++) {
			planet_arr[i].print();
		}
		break;
	case 2: 
		area_sort(planet_arr);
		for (int i = 0; i < planet_arr.size(); i++) {
			planet_arr[i].print();
			std::cout << "Area: " << planet_arr[i].get_area() << std::endl;
		}
		break;
	}
}
