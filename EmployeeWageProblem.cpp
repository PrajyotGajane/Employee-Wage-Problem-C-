#include <iostream>
#include <time.h>
using namespace std;
int checkAttendance();
int wageCalculator(int);
int wagePerHour = 20;
int totalWorkingDays = 20;

int main()
{
    srand(time(NULL));
    int fullDayHour = 8;
    int partDayHour = 4;
    int isPresent = 1;
    int isAbsent = 2;
    int isPartTime = 1;
    int isFullTime = 2;
    int totalWorkingDays = 20;
    int employeeWage;
    cout << "\n\n\n------------------------------------\n\n";
    cout << "\nWelcome to Employee Wage Problem\n" << endl;
    for (int days = 0; days < totalWorkingDays; days++)
    {
        int decideAttendance = ((rand() % 2) + 1);
        int decideTypeHours = ((rand() % 2) + 1);
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
            cout << "Employees wage for today : " << employeeWage << "\n"
                 << endl;
        }
        else
            cout << "Employee is absent\n"
                 << endl;
    }
    return 0;
}

int wageCalculator(int hoursPassed)
{
    return wagePerHour * hoursPassed;
}
