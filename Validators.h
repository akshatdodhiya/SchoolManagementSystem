#ifndef Validators
#define Validators

#include <string>

using namespace std;

// Function prototypes
string getPassword();
void menuTemplate(string menuOpt[], int);
bool validateEmail(string email);
bool validatePhoneNumber(string phone);
bool validateCGPA(float cgpa);
bool checkIDAvailability(string usr_file, string id);
bool validateUser(string usr_file, string user, string pass);
bool checkUsernameAvailability(string usr_file, string user);


#endif // Validators