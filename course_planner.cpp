#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

struct Course {
    std::string number;
    std::string title;
    std::vector<std::string> prerequisites;
};

class CourseCatalog {
private:
    std::map<std::string, Course> courses;

    static std::string trim(const std::string& s) {
        const char* ws = " \t\n\r\f\v";
        std::size_t start = s.find_first_not_of(ws);
        std::size_t end   = s.find_last_not_of(ws);
        return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
    }

public:
    bool empty() const { return courses.empty(); }

    bool loadFromCsv(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            std::cerr << "Error: Could not open file '" << filename << "'\n";
            return false;
        }
        courses.clear();
        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(ss, token, ',')) {
                tokens.push_back(trim(token));
            }
            if (tokens.size() < 2) {
                std::cerr << "Warning: skipping malformed row: " << line << '\n';
                continue;
            }
            Course c;
            c.number = tokens[0];
            c.title  = tokens[1];
            for (std::size_t i = 2; i < tokens.size(); ++i) {
                if (!tokens[i].empty()) c.prerequisites.push_back(tokens[i]);
            }
            courses[c.number] = std::move(c);
        }
        return true;
    }

    void printAll() const {
        if (courses.empty()) {
            std::cout << "Please load data first (option 1)." << '\n';
            return;
        }
        std::cout << "Here is a sample schedule:" << '\n';
        for (const auto& [num, course] : courses) {
            std::cout << course.number << ", " << course.title << '\n';
        }
    }

    void printCourse(const std::string& courseNum) const {
        auto it = courses.find(courseNum);
        if (it == courses.end()) {
            std::cout << courseNum << " not found." << '\n';
            return;
        }
        const Course& c = it->second;
        std::cout << c.number << ", " << c.title << '\n';
        std::cout << "Prerequisites: ";
        if (c.prerequisites.empty()) {
            std::cout << "None" << '\n';
        } else {
            for (std::size_t i = 0; i < c.prerequisites.size(); ++i) {
                std::cout << c.prerequisites[i];
                if (i + 1 < c.prerequisites.size()) std::cout << ", ";
            }
            std::cout << '\n';
        }
    }

    static std::string normalize(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
        return trim(s);
    }
};

static void printMenu() {
    std::cout << "1. Load Data Structure." << '\n'
              << "2. Print Course List." << '\n'
              << "3. Print Course." << '\n'
              << "9. Exit" << '\n';
}

int main() {
    CourseCatalog catalog;
    std::cout << "Welcome to the course planner." << '\n';

    while (true) {
        printMenu();
        std::cout << "What would you like to do? ";
        std::string rawChoice;
        std::getline(std::cin, rawChoice);
        int choice = 0;
        try { choice = std::stoi(rawChoice); }
        catch (...) { choice = -1; }

        switch (choice) {
            case 1: {
                std::cout << "Enter file name: ";
                std::string fname; std::getline(std::cin, fname);
                if (catalog.loadFromCsv(fname)) {
                    std::cout << "Data loaded successfully." << '\n';
                }
                break;
            }
            case 2:
                catalog.printAll();
                break;
            case 3: {
                if (catalog.empty()) {
                    std::cout << "Please load data first (option 1)." << '\n';
                    break;
                }
                std::cout << "What course do you want to know about? ";
                std::string courseNum; std::getline(std::cin, courseNum);
                catalog.printCourse(CourseCatalog::normalize(courseNum));
                break;
            }
            case 9:
                std::cout << "Thank you for using the course planner!" << '\n';
                return 0;
            default:
                std::cout << rawChoice << " is not a valid option." << '\n';
        }
    }
}
