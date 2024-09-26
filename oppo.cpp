#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const static double PI = 3.14159265;

class Planet {
public: 
	string name;
	string date;
	double radius;

	Planet(string Name, string Date, double Radius) {
		name = Name;
		date = Date;
		radius = Radius;
	}

	double get_area() const {
		return 4 * PI * radius * radius;
	};
	void print() const{
		cout << fixed << setprecision(2) << 
			"Name: " << name << "\t Date of the research: " 
			<< date << "\t Radius: " << radius << endl;
	}
};

static string get_name(string a) {
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

static string get_date(string a) {
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '.' && a[i + 3] == '.') {
			int year = stoi(a.substr(i - 4, 4)), month = stoi(a.substr(i + 1, 2)), day = stoi(a.substr(i + 4, 2));
			if ((1 <= month && month <= 12) && (1 <= day && day <= 31)) {
				return a.substr(i - 4, 10);
			}
			else {
				cout << "incorrect date in " << a.substr(i - 4, 10);
				exit(-1);
			}
		}
	}
}

static float get_radius(string a) {
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

int main() {
	string s;
	ifstream in("in.txt");
	if (!in.is_open()) {
		cerr << "File did not openned";
	}
	else {
		string s; int count = 0;
		while (getline(in, s)) {
			Planet planet(get_name(s), get_date(s), get_radius(s));
			planet.print();
			cout  << "Area: " << planet.get_area() << endl;
		}
	}
	in.close();
}
