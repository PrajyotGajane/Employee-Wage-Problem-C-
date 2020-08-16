// UC2: Calculate Daily Employee Wage
// 	- Assume Wage per Hour is 20
// 	- Assume Full Day Hour is 8
#include <iostream>
#include <time.h>
using namespace std;
int checkAttendance();
int wageCalculator(int);
int wagePerHour = 20;
int main()
{
    srand(time(NULL));
    int fullDayHour = 8;
    int partDayHour = 4;
    int isPresent = 1;
    int isAbsent = 2;
    int isPartTime = 1;
    int isFullTime = 2;
    int decideAttendance = ((rand() % 2) + 1);
    int decideTypeHours = ((rand() % 2) + 1);
    int employeeWage;
    cout << "\n\n\n------------------------------------\n\n";
    cout << "\nWelcome to Employee Wage Problem\n"
         << endl;
    if (decideAttendance == isPresent)
    {
        cout << "Employee is present" << endl;
        if (decideTypeHours == isPartTime)
        {
            cout << "Part Time wage\n";
            employeeWage = wageCalculator(partDayHour);
        }
        else
        {
            cout << "Full Time wage\n";
            employeeWage = wageCalculator(fullDayHour);
        }
        cout << "Employees wage for today : " << employeeWage << endl;
    }
    else
        cout << "Employee is absent" << endl;
    return 0;
}

int wageCalculator(int hoursPassed)
{
    return wagePerHour * hoursPassed;
}
