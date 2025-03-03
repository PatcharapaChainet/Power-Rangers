#ifndef COST_H
#define COST_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

using namespace std;

class cost {
public:
    string day;
    string month;
    string year;
    string date;
    double revennue;
    string name;

    cost(string n, double m);
    cost(string n, string d, string m, string y, double r);

    string getday();
    string getmonth();
    string getyear();

    bool operator==(const cost& other) const {
        return date == other.date && revennue == other.revennue && name == other.name;
    }
};

cost::cost(string n, double m) {
    day = getday();
    month = getmonth();
    year = getyear();
    name = n;
    revennue = m;
}

cost::cost(string n, string d, string m, string y, double r) {
    name = n;
    day = d;
    month = m;
    year = y;
    revennue = r;
}

string cost::getday() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_mday);
}

string cost::getmonth() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_mon + 1);
}

string cost::getyear() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return to_string(ltm->tm_year + 1900);
}

extern vector<cost> costlist;

inline void saveCostToFile() {
    ofstream outFile("Cost.txt");
    if (outFile.is_open()) {
        for (auto& c : costlist) {
            outFile << c.name << "," << c.day << ","
                << c.month << "," << c.year << ","
                << c.revennue << "\n";
        }
        outFile.close();
    }
    else {
        cerr << "Error: Could not open Cost.txt for writing" << endl;
    }
}

inline void loadcostFromFile() {
    costlist.clear();
    ifstream inFile("Cost.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, day, month, year;
            double revenue;

            getline(ss, name, ',');
            getline(ss, day, ',');
            getline(ss, month, ',');
            getline(ss, year, ',');
            ss >> revenue;

            if (!ss.fail()) {
                costlist.push_back(cost(name, day, month, year, revenue));
            }
            else {
                cerr << "Invalid data format in line: " << line << endl;
            }
        }
        inFile.close();
    }
    else {
        cerr << "Error: Could not open Cost.txt for reading" << endl;
    }
}

inline void initializecostList() {
    loadcostFromFile();
}

inline void addcost(string name, double rev) {
    costlist.push_back(cost(name, rev));
    saveCostToFile();
}

inline void delcost(string name) {
    costlist.erase(remove_if(costlist.begin(), costlist.end(), [&name](const cost& c) { return c.name == name; }), costlist.end());
    saveCostToFile();
}

vector<cost> scost;

inline void searchday(string keyd, string keym, string keyy) {
    scost.clear();
    for (auto& c : costlist) {
        if (keyd == c.day && keym == c.month && keyy == c.year) {
            c.date = keyd + "/" + keym + "/" + keyy;
            scost.push_back(c);
        }
    }
}

inline void searchmon(string keym, string keyy) {
    scost.clear();
    for (auto& c : costlist) {
        if (keym == c.month && keyy == c.year) {
            c.date = keym + "/" + keyy;
            scost.push_back(c);
        }
    }
}

inline void searchyear(string keyy) {
    scost.clear();
    for (auto& c : costlist) {
        if (keyy == c.year) {
            c.date = keyy;
            scost.push_back(c);
        }
    }
}

vector<double> reve;
vector<string> Date;
vector<string> Name;

inline void costinspector() {
    double totalRevenue = 0.0;
    for (auto& c : scost) {
        totalRevenue += c.revennue;
    }
    Date.push_back(scost[0].date);
    Name.push_back(scost[0].name);
    reve.push_back(totalRevenue);
}

double totalreve(vector<double>& x) {
    double total = 0.0;
    for (const auto& val : x) {
        total += val;
    }
    return total;
}

#endif
