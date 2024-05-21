/*
Program: Student Record Management System
Author: Akshat Dodhiya
Date: 04/14/2024
Description: This program is part of my lab project for 3rd Semester of Computer Engineering Technology program.

This program is a simple student record management system that allows the user to perform the following operations:
	1. List all students
	2. List students by program
	3. Add a new student
	4. Search a student using ID
	5. Modify data of a student
	6. Delete a student
	7. Exit

	The program uses a file to store the student data and the user data.
	The user data is stored in a file named "users.pwd" and the student data is stored in a file named "StudentsData.dat".
	The program also provides a login system where the user can create an account or login to an existing account.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include "Validators.h"

using namespace std;

string filename = "StudentsData.dat";
string usr_file = "users.pwd";


class Student
{
private:
	int ID;
	string Name;
	string Program;
	string Email;
	string PhoneNumber;
	int Attendance;
	float CGPA;

public:
	Student()
	{
		ID = 0;
		Name = "";
		Program = "";
		Email = "";
		PhoneNumber = "";
		Attendance = 0;
		CGPA = 0.0;
	}

	Student(int id, string name, string program, string email, string phone, int att, float cgpa)
	{
		ID = id;
		Name = name;
		Program = program;
		Email = email;
		PhoneNumber = phone;
		Attendance = att;
		CGPA = cgpa;
	}

	int getID()
	{
		return ID;
	}

	string getName()
	{
		return Name;
	}

	string getProgram()
	{
		return Program;
	}

	string getEmail()
	{
		return Email;
	}

	string getPhoneNumber()
	{
		return PhoneNumber;
	}

	int getAttendance()
	{
		return Attendance;
	}

	float getCGPA()
	{
		return CGPA;
	}

	void setProgram(string program)
	{
		Program = program;
	}

	void setEmail(string email)
	{
		Email = email;
	}

	void setPhoneNumber(string phone)
	{
		PhoneNumber = phone;
	}

	void setAttendance(int att)
	{
		Attendance = att;
	}

	void setCGPA(float cgpa)
	{
		CGPA = cgpa;
	}

	void display() const
	{
		cout << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Program" << setw(30) << "Email" << setw(15) << "Phone Number" << setw(10) << "Attendance" << setw(10) << "CGPA" << endl;
		cout << setw(5) << ID << setw(20) << Name << setw(20) << Program << setw(30) << Email << setw(15) << PhoneNumber << setw(10) << Attendance << setw(10) << CGPA << endl;
	}

};

void loginUser();
int mainMenu();
template <class anytype>
anytype getInputValue(string);
void displayAll();
void displayByProgram(string);
void addStudent();
void saveDataToFile(Student);
void searchStudentByID(string, int);
void modifyStudent(string, int);
void deleteStudent(string, int);


int main()
{
	char ch;
	int code;

	loginUser();

	do
	{
		code = mainMenu();
		if (code != -1)
		{
			cout << "Do you want to continue? (Y/N): ";
			cin >> ch;
		}
		else
			break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "\033[2J\033[1;1H"; // Clear the screen
	} while ((ch == 'Y' || ch == 'y') && code == 0);

	cout << "Thank you for using the Student Record Management System!" << endl;

	return 0;
}


void loginUser()
{
	// Display options to create an account or login
	int choice;
	string username, password;

	do
	{
		cout << "------------------------------------------------" << endl;
		cout << "|\t\tStudent Database Menu\t\t|" << endl;
		cout << "------------------------------------------------\n" << endl;
		cout << "1. Create an account" << endl;
		cout << "2. Login to an existing account\n" << endl;
		cout << "------------------------------------------------\n" << endl;

		cout << "Enter choice: ";
		cin >> choice;

		if (choice != 1 && choice != 2)
		{
			cout << "\nInvalid choice! Please try again!" << endl;
		}
	} while (choice != 1 && choice != 2);

	if (choice == 1)
	{
		bool isAvailable = false;
		do
		{
			cout << "Enter your one word username: ";
			cin >> username;

			isAvailable = checkUsernameAvailability(usr_file, username);

			if (!isAvailable)
			{
				cout << "\nUsername already exists! Please try again!\n" << endl;
			}
		} while (!isAvailable);

		cout << "Enter password: ";
		password = getPassword();

		// save data in the file in binary format
		ofstream fout(usr_file, ios::binary | ios::app);
		fout << username << " " << password << endl;
		fout.close();

		cout << "\n--> Account created successfully!\n" << endl;
	}

	do
	{
		cout << "Enter your one word username: ";
		cin >> username;
		cout << "Enter password: ";
		password = getPassword();
		if (!validateUser(usr_file, username, password))
		{
			cout << "\n\nInvalid username or password! Please try again!" << endl;
		}
	} while (!validateUser(usr_file, username, password));

	cout << "\n--> Logged in as " << username << "!\n\n" << endl;
}

int mainMenu()
{
	int choice;

	string Opt[] = { "List all students", "List students by program", "Add a new student", "Search a student using ID", "Modify data of a student", "Delete a student", "Exit" };
	menuTemplate(Opt, 7);

	cout << "Enter choice: ";
	choice = getInputValue<int>("Choice");

	switch (choice)
	{
	case 1:
		displayAll();
		break;
	case 2:
	{
		string program;
		cout << "Enter Program: ";
		cin >> program;
		displayByProgram(program);
		break;
	}
	case 3:
		addStudent();
		break;
	case 4:
		int id;
		cout << "Enter ID: ";
		cin >> id;
		searchStudentByID(filename, id);
		break;
	case 5:
		int id2;

		displayAll();

		cout << "Enter ID: ";
		cin >> id2;
		modifyStudent(filename, id2);
		break;
	case 6:
		int id3;

		displayAll();

		cout << "Enter ID: ";
		cin >> id3;
		deleteStudent(filename, id3);
		break;
	case 7:
		return -1;
		break;
	default:
		cout << "Invalid choice!" << endl;
	}

	return 0;
}


// Template function to use with multiple data types
template <class anytype>
anytype getInputValue(string name)
{
	anytype userInput;
	bool isValid = false;
	while (!isValid)
	{

		if (!(cin >> userInput))  // If cin bit fails
		{
			cout << "Invalid Input! Please try again!\n\n=>";
		}
		else if (userInput < 0)
		{
			cout << name << " cannot be less than 0. Please try again!\n\n=>";
		}
		else
		{
			isValid = true;
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return userInput;
}

void displayAll()
{
	// Display all students from the file separated by tab
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Error in opening file" << endl;
		// Create a new file if the file does not exist
		ofstream fout(filename);
		fout.close();
		return;
	}
	else
	{
		int id, att;
		string name, program, email, phone;
		float cgpa;
		cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Program" << setw(30) << "Email" << setw(15) << "Phone Number" << setw(12) << "Attendance" << setw(10) << "CGPA" << endl;
		while (fin >> id >> name >> program >> email >> phone >> att >> cgpa)
		{
			cout << setw(5) << id << setw(20) << name << setw(15) << program << setw(30) << email << setw(15) << phone << setw(12) << att << setw(10) << cgpa << endl;
		}
	}
}

void displayByProgram(string inp_program)
{
	cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Program" << setw(30) << "Email" << setw(15) << "Phone Number" << setw(12) << "Attendance" << setw(10) << "CGPA" << endl;

	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Error in opening file" << endl;
		// Create a new file if the file does not exist
		ofstream fout(filename);
		fout.close();
		return;
	}
	else
	{
		int id, att, cnt = 0;
		string name, program, email, phone;

		// convert string to lowercase
		for (int i = 0; i < strlen(inp_program.c_str()); i++)
			inp_program[i] = tolower(inp_program[i]);

		float cgpa;
		while (fin >> id >> name >> program >> email >> phone >> att >> cgpa)
		{
			if (program == inp_program)
			{
				cout << setw(5) << id << setw(20) << name << setw(15) << program << setw(30) << email << setw(15) << phone << setw(12) << att << setw(10) << cgpa << endl;
				cnt++;
			}
		}
		if (cnt == 0)
		{
			// Clear the screen
			cout << "\033[2J\033[1;1H";
			cout << "No students found in the program " << inp_program << endl;
		}
	}
}


void addStudent()
{
	int id;
	string name, program, email, phone;
	int att;
	float cgpa;

	do
	{
		cout << "Enter ID: ";
		id = getInputValue<int>("ID");
		if (!checkIDAvailability(usr_file, to_string(id)))
		{
			cout << "ID already exists! Please try again!" << endl;
		}
	} while (!checkIDAvailability(usr_file, to_string(id)));


	cout << "Enter Name: ";
	getline(cin, name);

	cout << "Enter Program: ";
	cin >> program;

	do
	{
		cout << "Enter Email: ";
		cin >> email;
		if (!validateEmail(email))
		{
			cout << "Invalid Email! Please try again!" << endl;
			continue;
		}
	} while (!validateEmail(email));

	do
	{
		cout << "Enter Phone Number: ";
		cin >> phone;
		if (!validatePhoneNumber(phone))
		{
			cout << "Invalid Phone Number! Please try again!" << endl;
			continue;
		}
	} while (!validatePhoneNumber(phone));


	cout << "Enter Attendance: ";
	att = getInputValue<int>("Attendance");

	do
	{
		cout << "Enter CGPA: ";
		cgpa = getInputValue<float>("CGPA");

		if (!validateCGPA(cgpa))
		{
			cout << "Invalid CGPA! Please try again!" << endl;
		}
	} while (!validateCGPA(cgpa));

	Student s(id, name, program, email, phone, att, cgpa);

	cout << "Student added successfully!" << endl;

	// Save the student data in the file with tab separation
	saveDataToFile(s);
}

void saveDataToFile(Student s)
{
	ofstream fout(filename, ios::app);
	string program = s.getProgram();

	for (int i = 0; i < strlen(program.c_str()); i++)
	{
		program[i] = tolower(program[i]);
	}

	fout << s.getID() << "\t" << s.getName() << "\t" << program << "\t" << s.getEmail() << "\t" << s.getPhoneNumber() << "\t" << s.getAttendance() << "\t" << s.getCGPA() << endl;
	fout.close();
}

void searchStudentByID(string filename, int id)
{
	// Search student by ID from the file
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Error in opening file" << endl;
		// Create a new file if the file does not exist
		ofstream fout(filename);
		fout.close();
		return;
	}
	else
	{
		int id2, att;
		string name, program, email, phone;
		float cgpa;
		while (fin >> id2 >> name >> program >> email >> phone >> att >> cgpa)
		{
			if (id2 == id)
			{
				cout << setw(5) << "ID" << setw(20) << "Name" << setw(15) << "Program" << setw(30) << "Email" << setw(15) << "Phone Number" << setw(12) << "Attendance" << setw(10) << "CGPA" << endl;
				cout << setw(5) << id2 << setw(20) << name << setw(15) << program << setw(30) << email << setw(15) << phone << setw(12) << att << setw(10) << cgpa << endl;
				return;
			}
		}
		cout << "Student not found!" << endl;
	}
	fin.close();
}

void modifyStudent(string filename, int id)
{
	int id2, att;
	string name, program, email, phone;
	float cgpa;
	bool found = false;

	// Modify student data by ID from the file by giving options to the user
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Error in opening file" << endl;
		// Create a new file if the file does not exist
		ofstream fout(filename);
		fout.close();
		return;
	}

	else
	{
		while (fin >> id2 >> name >> program >> email >> phone >> att >> cgpa)
		{
			if (id2 == id)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "Student not found! Please check ID and try again!" << endl;
			return;
		}
	}
	fin.close();

	int choice;
	do
	{
		string menuOpt[] = { "Modify Program", "Modify Email", "Modify Phone Number", "Modify Attendance", "Modify CGPA", "Exit" };
		menuTemplate(menuOpt, 6);
		std::cout << "Enter choice: ";
		cin >> choice;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (choice)
		{
		case 1:
		{
			std::cout << "Enter Program: ";
			cin >> program;
			break;
		}
		case 2:
		{
			do
			{
				cout << "Enter Email: ";
				cin >> email;
				if (!validateEmail(email))
				{
					cout << "Invalid Email! Please try again!" << endl;
					continue;
				}
			} while (!validateEmail(email));
			break;
		}
		case 3:
		{
			do
			{
				cout << "Enter Phone Number: ";
				cin >> phone;
				if (!validatePhoneNumber(phone))
				{
					cout << "Invalid Phone Number! Please try again!" << endl;
					continue;
				}
			} while (!validatePhoneNumber(phone));
			break;
		}
		case 4:
		{
			cout << "Enter Attendance: ";
			att = getInputValue<int>("Attendance");
			break;
		}
		case 5:
		{
			do
			{
				cout << "Enter CGPA: ";
				cgpa = getInputValue<float>("CGPA");

				if (!validateCGPA(cgpa))
				{
					cout << "Invalid CGPA! Please try again!" << endl;
				}
			} while (!validateCGPA(cgpa));
			break;
		}
		case 6:
		{
			break;
		}
		default:
		{
			cout << "Invalid choice!" << endl;
		}
		}

	} while (choice > 6 || choice < 1);

	Student s(id2, name, program, email, phone, att, cgpa);

	// Save the modified student data in the file with tab separation and save the other data that does not need to be modified
	ofstream file_out("temp.txt");
	ifstream file_in(filename);

	if (!file_out.is_open() || !file_in.is_open())
	{
		cout << "Error in opening file" << endl;
		// Create a new file if the file does not exist
		ofstream fout(filename);
		fout.close();
		return;
	}
	else
	{
		while (file_in >> id2 >> name >> program >> email >> phone >> att >> cgpa)
		{
			if (id2 == id)
			{
				file_out << s.getID() << "\t" << s.getName() << "\t" << s.getProgram() << "\t" << s.getEmail() << "\t" << s.getPhoneNumber() << "\t" << s.getAttendance() << "\t" << s.getCGPA() << endl;
			}
			else
			{
				file_out << id2 << "\t" << name << "\t" << program << "\t" << email << "\t" << phone << "\t" << att << "\t" << cgpa << endl;
			}
		}
	}
	file_out.close();
	file_in.close();

	if (found)
	{
		remove(filename.c_str());
		rename("temp.txt", filename.c_str());
		cout << "Student data modified successfully!" << endl;
	}
	else
	{
		remove("temp.txt");
	}

}


void deleteStudent(string filename, int id)
{
	// Delete student by ID from the file
	ifstream fin(filename);
	ofstream fout("temp.txt");

	if (!fin.is_open() || !fout.is_open())
	{
		cout << "Error in opening file" << endl;
		// Create a new file if the file does not exist
		ofstream fout(filename);
		fout.close();
		return;
	}
	else
	{
		int id2, att;
		string name, program, email, phone;
		float cgpa;
		bool found = false;
		while (fin >> id2 >> name >> program >> email >> phone >> att >> cgpa)
		{
			if (id2 == id)
			{
				found = true;
				continue;
			}
			fout << id2 << "\t" << name << "\t" << program << "\t" << email << "\t" << phone << "\t" << att << "\t" << cgpa << endl;
		}
		if (!found)
		{
			cout << "Student not found! Please check ID and try again!" << endl;
			return;
		}
	}
	fin.close();
	fout.close();

	remove(filename.c_str());
	rename("temp.txt", filename.c_str());

	cout << "Student deleted successfully!" << endl;
}