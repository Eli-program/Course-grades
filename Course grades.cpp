#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Student {
    std::string name;
    std::string id;
    std::vector<int> tests;

    double overall() const {
        if (tests.empty()) return 0.0;
        double sum = 0;
        for (int t : tests) sum += t;
        return sum / tests.size();
    }
};

static std::string toLower(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return out;
}

int main() {
    std::ifstream studentFile("C:/Users/elija/Downloads/student_data.txt");
    if (!studentFile) {
        std::cerr << "Error: could not open student_data.txt\n";
        return 1;
    }

    std::string line;
    std::vector<Student> students;

    // Expected line format (common case):
    // FirstName LastName ID test1 test2 ... testN
    // If your file uses a different format (CSV, "Last, First", etc.), provide a sample.
    while (std::getline(studentFile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Student s;

        std::string first, second;
        if (!(iss >> first)) continue;            // no tokens
        if (!(iss >> second)) {                  // only one token -> treat as name, no id/tests
            s.name = first;
            students.push_back(std::move(s));
            continue;
        }

        // Try to parse as First Last ID ...
        std::string third;
        if (!(iss >> third)) {
            // Two tokens only -> treat as "First Last" with no id/tests
            s.name = first + " " + second;
            students.push_back(std::move(s));
            continue;
        }

        // We have at least three tokens: assume first+second = name, third = id
        s.name = first + " " + second;
        s.id = third;

        int score;
        while (iss >> score) {
            s.tests.push_back(score);
        }

        students.push_back(std::move(s));
    }

    // Sort by student name (case-insensitive)
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return toLower(a.name) < toLower(b.name);
        });

    for (const auto& st : students) {
        std::cout << st.name;
        if (!st.id.empty()) std::cout << ' ' << st.id;
        for (int t : st.tests) std::cout << ' ' << t;
        std::cout << ' ' << std::fixed << std::setprecision(1) << st.overall() << '\n';
    }

    return 0;
}