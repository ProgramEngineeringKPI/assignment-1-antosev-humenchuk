#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

enum Status
{
	Contract,
	Budget
};

class Student
{
	string name;
	double score;
	Status status;

public:
	string GetName()
	{
		return name;
	}

	double GetScore()
	{
		return score;
	}

	Status GetStatus()
	{
		return status;
	}

	Student(string name,double score,Status status)
	{
		this->name = name;
		this->score = score;
		this->status = status;
	}

	Student()
	{

	}
};

FILE *LoadData(char *filename);
void PrintArray(Student *arr, int size);
void InsertionSort(Student *arr, int p, int r);
void SaveData(char *filename, Student *table, int numOfTeams);
void FillArrayByDataFromFile(Student *table, int numberOfStudents, FILE *file, int &numberOfBudgetStudents);
void FillArrayOfBudgetStudents(Student *table, Student *budgetStudentsTable, int numberOfStudents);

int main()
{
	FILE* file = LoadData("students.csv");
	int numberOfStudents;		
	int numberOfBudgetStudents;
	fscanf(file, "%d/n", &numberOfStudents);
	numberOfBudgetStudents = numberOfStudents;
	Student *table = new Student[numberOfStudents];
	FillArrayByDataFromFile(table, numberOfStudents, file, numberOfBudgetStudents);
	Student *budgetStudentsTable = new Student[numberOfBudgetStudents];
	FillArrayOfBudgetStudents(table, budgetStudentsTable, numberOfStudents);
	InsertionSort(budgetStudentsTable, 0, numberOfBudgetStudents);
	SaveData("res.csv", budgetStudentsTable, numberOfBudgetStudents);	
	delete[] budgetStudentsTable;
	delete[] table;
    return 0;
	
}

void FillArrayByDataFromFile(Student *table, int numberOfStudents, FILE *file, int &numberOfBudgetStudents)
{
	for (int i = 0; i < numberOfStudents; i++)
	{
		string name;
		int score = 0;
		double resultScore = 0;
		char symbol;
		Status status = Status::Budget;
		fscanf(file, "%c", &symbol);
		while (symbol != ',')
		{
			name += symbol;
			fscanf(file, "%c", &symbol);
		}
		for (int j = 0; j < 5; j++)
		{
			fscanf(file, "%d,", &score);
			resultScore += score;
		}
		resultScore /= 5;
		fscanf(file, "%c", &symbol);
		if (symbol == '+')
		{
			status = Status::Contract;
			numberOfBudgetStudents--;
		}
		else status = Status::Budget;
		Student student(name, resultScore, status);
		table[i] = student;
	}
}

void FillArrayOfBudgetStudents(Student *table, Student *budgetStudentsTable, int numberOfStudents)
{
	int j = 0;
	for (int i = 0; i < numberOfStudents; i++)
	{		
		if (table[i].GetStatus() == Status::Budget)
		{
			budgetStudentsTable[j] = table[i];
			j++;
		}
	}
}

FILE *LoadData(char *filename)
{
	FILE *file;
	fopen_s(&file, filename, "r");
	if (file == NULL)
	{
		printf("Error opening file");
	}
	return file;
}

void SaveData(char *filename, Student *table, int numOfTeams)
{
	FILE *file;
	fopen_s(&file, filename, "w");
	if (file == NULL)
	{
		printf("Error opening file");
	}
	int count = numOfTeams * 0.4;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < table[i].GetName().length(); j++)
		{
			fprintf(file, "%c", table[i].GetName()[j]);
		}
		int sc = (int)table[i].GetScore();
		fprintf(file, "  -  %d\n", sc);
	}
	fclose(file);
}

void InsertionSort(Student *arr, int p, int r)
{
	for (int i = p + 1; i < r; i++)
	{
		Student temp = arr[i];
		int j = i - 1;
		while (temp.GetScore() > arr[j].GetScore() && j >= 0)
		{
			arr[j + 1] = arr[j];
			arr[j] = temp;
			j--;
		}
	}
}

void PrintArray(Student *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i].GetName() << "  --  " << arr[i].GetScore() << "  --  " << endl;
	}
}