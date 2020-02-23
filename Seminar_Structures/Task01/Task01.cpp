#include <iostream>
using namespace std;

const int NAME_SIZE = 20;
const int EGN_SIZE = 10;
const int FACULTY_NUMBER_SIZE = 10;
const int GRADES_COUNT = 5;

struct Student {
	char name[NAME_SIZE];
	char egn[EGN_SIZE];
	char facultyNumber[FACULTY_NUMBER_SIZE];
	double grades[GRADES_COUNT];
};

void initialize(Student& student) {
	cout << "Please, enter the name of the student: ";
	cin.getline(student.name, NAME_SIZE);

	cout << "Please, enter the egn of the student: ";
	cin.getline(student.egn, EGN_SIZE);

	cout << "Please, enter the faculty number of the student: ";
	cin.getline(student.facultyNumber, FACULTY_NUMBER_SIZE);

	cout << "Please, enter five grades: ";
	for (int i = 0; i < GRADES_COUNT; i++)
	{
		cin >> student.grades[i];
	}
}

void print(const Student& student) {
	cout << "Student's name: " << student.name << endl;
	cout << "Student's EGN: " << student.egn << endl;
	cout << "Student's faculty number: " << student.facultyNumber << endl;
	cout << "Student's grades: ";
	
	for (int i = 0; i < GRADES_COUNT; i++)
	{
		cout << student.grades[i] << " ";
	}
	cout << endl;
}

double getAverageGrade(double* grades) {
	double gradesSum = 0.0;

	for (int i = 0; i < GRADES_COUNT; i++)
	{
		gradesSum += grades[i];
	}

	return gradesSum / GRADES_COUNT;
}

void printAverageGrades(Student* students, size_t count) {
	Student currentStudent;
	for (size_t i = 0; i < count; i++)
	{
		currentStudent = students[i];
		double studentAverageGrade = getAverageGrade(currentStudent.grades);

		cout << currentStudent.name << "'s average grade is: " << studentAverageGrade << endl;
	}
}

Student& getBestStudent(Student* students, size_t count) {
	int bestStudentIndex = 0;
	double highestStudentAverageGrade = 2.00;
	
	for (size_t i = 0; i < count; i++)
	{
		double studentAverageGrade = getAverageGrade(students[i].grades);

		if (studentAverageGrade > highestStudentAverageGrade)
		{
			highestStudentAverageGrade = studentAverageGrade;
			bestStudentIndex = i;
		}
	}

	return students[bestStudentIndex];
}

int main()
{
	const int numberOfStudents = 2;
	Student students[numberOfStudents];

	for (int i = 0; i < numberOfStudents; i++)
	{
		initialize(students[i]);
		cin.get();
	}

	print(students[0]);

	printAverageGrades(students, numberOfStudents);

	Student bestStudent = getBestStudent(students, numberOfStudents);

	cout << bestStudent.name << endl;
	cout << bestStudent.facultyNumber << endl;
}