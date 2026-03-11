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
};

struct StudentID {
	string id;
};

struct TestScore {
	double score1;
	double score2;
	double score3;
	double score4;
};

struct Grade {
	double grade;
};

int main() {
	ifstream file("C:/Users/elija/Downloads/student_data.txt");
	if (!file.is_open()) {
		cerr << "Error opening file!" << endl;
		return 1;
	}
	vector<Student> students;
	vector<StudentID> studentIDs;
	vector<TestScore> testScores;
	vector<Grade> grades;
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string name, id;
		double t1, t2, t3, t4;
		double grade;
		// layout
		if (!(iss >> name >> id >> t1 >> t2 >> t3 >> t4 >> grade)) {
			cerr << "Error parsing line: " << line << endl;
			continue; 
		}
		students.push_back({name});
		studentIDs.push_back({id});
		testScores.push_back({ t1, t2, t3, t4 });
		grades.push_back({grade});
	}
	file.close();

	// Column widths
	const int nameW = 20;
	const int idW = 15;
	const int testW = 7;
	const int overallW = 10;
	const int totalWidth = nameW + idW + 4 * testW + overallW;

	cout << left << setw(nameW) << "Name" << setw(idW) << "Student ID";
	cout << right << setw(testW) << "T1" << setw(testW) << "T2" << setw(testW) << "T3" << setw(testW) << "T4";
	cout << setw(overallW) << "Grade" << endl;
	cout << string(totalWidth, '-') << endl;

	for (size_t i = 0; i < students.size(); ++i) {
		cout << left << setw(nameW) << students[i].name 
			 << setw(idW) << studentIDs[i].id;

		
		cout << right << fixed << setprecision(1)
			 << setw(testW) << testScores[i].score1
			 << setw(testW) << testScores[i].score2
			 << setw(testW) << testScores[i].score3
			 << setw(testW) << testScores[i].score4;

		
		cout << setw(overallW) << setprecision(2) << grades[i].grade 
			 << endl;
	}
	return 0;
}