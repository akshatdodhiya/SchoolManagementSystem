
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Validators.h"

using namespace std;

// Function to get the password from the user
string getPassword()
{
	// get the password, but replace it with *
	string password = "";
	char ch;
	ch = _getch();
	// handle enter key and backspace key
	while (ch != 13)
	{
		if (ch == 8)
		{
			if (password.length() > 0)
			{
				cout << "\b \b";
				password = password.substr(0, password.length() - 1);
			}
		}
		else
		{
			cout << "*";
			password += ch;
		}
		ch = _getch();
	}
	return password;
}

void menuTemplate(string menuOpt[], int arr_size)
{
	cout << "---------------------------------------------------------" << endl;
	cout << "|\t\t\t  Menu  \t\t\t|" << endl;
	cout << "---------------------------------------------------------\n|" << endl;
	for (int i = 0; i < arr_size; i++)
	{
		cout << "| " << i + 1 << ". " << menuOpt[i] << endl;
	}
	cout << "---------------------------------------------------------" << endl;
}

// Function to validate email
bool validateEmail(string email)
{
	int at = 0, dot = 0;
	for (int i = 0; i < email.length(); i++)
	{
		if (email[i] == '@')
		{
			at++;
		}
		else if (email[i] == '.')
		{
			dot++;
		}
	}
	if (at == 1 && dot >= 1)
	{
		return true;
	}
	return false;
}

// Function to validate phone number
bool validatePhoneNumber(string phone)
{
	if (phone.length() == 11)
	{
		return true;
	}
	return false;
}

// Function to validate CGPA
bool validateCGPA(float cgpa)
{
	if (cgpa >= 0 && cgpa <= 4)
	{
		return true;
	}
	return false;
}

// Function to validate ID
bool checkIDAvailability(string usr_file, string id)
{
	// Open the file in binary to find ID and then check if the parameterized ID is same as the ones in the file
	ifstream file(usr_file, ios::in);
	if (!file)
	{
		cout << "Error in opening file" << endl;
		return false;
	}
	string ID, name, email, phone, cgpa;
	while (file >> ID >> name >> email >> phone >> cgpa)
	{
		if (ID == id)
		{
			file.close();
			return false;
		}
	}
	file.close();
	return true;
}

// Function to validate user
bool validateUser(string usr_file, string user, string pass)
{
	// Open the file in binary to find username and password separated by tab space and then check if the parameterized username and password are same as the ones in the file
	ifstream file(usr_file, ios::binary);
	if (!file)
	{
		cout << "Error in opening file" << endl;
		return false;
	}
	string username, password;
	while (file >> username >> password)
	{
		if (username == user && password == pass)
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

// Function to check username availability
bool checkUsernameAvailability(string usr_file, string user)
{
	// Open the file in binary to find username and password separated by tab space and then check if the parameterized username is same as the ones in the file
	ifstream file(usr_file, ios::binary);
	if (!file)
	{
		// Create a new file if the file does not exist
		ofstream newFile(usr_file, ios::binary);
		newFile.close();
		ifstream file(usr_file, ios::binary);
	}

	if (!file)
	{
		cout << "Error in opening file" << endl;
		return false;
	}

	string username, password;
	while (file >> username >> password)
	{
		if (username == user)
		{
			file.close();
			return false;
		}
	}
	file.close();
	return true;
}

