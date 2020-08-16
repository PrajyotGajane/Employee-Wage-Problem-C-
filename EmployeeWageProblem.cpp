#include <iostream>
#include <time.h>
using namespace std;
int checkAttendance();
int main() {
    int isPresent = 1;
    int isAbsent = 2;
    cout << "\n\n\n------------------------------------\n\n";
    cout << "\nWelcome to Employee Wage Problem\n" << endl;
    int attendance = checkAttendance();
    if (attendance == isPresent) 
        cout << "Employee is present" << endl;
    else 
        cout << "Employee is absent" << endl;
    return 0;
}

int checkAttendance(){
    srand(time(NULL));
	return ((rand() % 2) + 1);
}