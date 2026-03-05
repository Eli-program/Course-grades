#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    string id;
    vector<int> tests;

    double overall() const {
        if (tests.empty()) return 0.0;
        double sum = 0;
        for (int t : tests) sum += t;
        return sum / tests.size();
    }
};

static string toLower(const string& s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c) { return tolower(c); });
    return out;
}

int main() {
    ifstream studentFile("C:/Users/elija/Downloads/student_data.txt");
    if (!studentFile) {
        cerr << "Error: could not open student_data.txt\n";
        return 1;
    }

    string line;
    vector<Student> students;

    
    while (getline(studentFile, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Student s;

        string first, second;
        if (!(iss >> first)) continue;            
        if (!(iss >> second)) {                 
            s.name = first;
            students.push_back(move(s));
            continue;
        }

       
        string third;
        if (!(iss >> third)) {
           
            s.name = first + " " + second;
            students.push_back(move(s));
            continue;
        }

        
        s.name = first + " " + second;
        s.id = third;

        int score;
        while (iss >> score) {
            s.tests.push_back(score);
        }

        students.push_back(move(s));
    }

    // Sort by student name
    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return toLower(a.name) < toLower(b.name);
        });

    for (const auto& st : students) {
        cout << st.name;
        if (!st.id.empty()) cout << ' ' << st.id;
        for (int t : st.tests) cout << ' ' << t;
        cout << ' ' << fixed << setprecision(1) << st.overall() << '\n';
    }

    return 0;
}