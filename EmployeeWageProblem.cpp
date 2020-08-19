#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;
int checkAttendance();
int wageCalculator(int);
void addEmployeeDataCSV();
int wagePerHour = 20;
const int totalWorkingDays = 20;
const int totalWorkingHours = 100;
vector<int> employeeWageMonth;

int main()
{
    srand(time(NULL));
    int fullDayHour = 8;
    int partDayHour = 4;
    int noWorkDay = 0;
    int isPresent = 1;
    int isAbsent = 2;
    int isPartTime = 1;
    int isFullTime = 2;
    int totalWorkingDays = 20;
    int employeeWage;
    cout << "\n\n\n------------------------------------\n\n";
    cout << "\nWelcome to Employee Wage Problem\n"
         << endl;
    int workedDays = 0;
    int workedHours = 0;
    while (workedDays < totalWorkingDays && workedHours < totalWorkingHours)
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
                workedHours += partDayHour;
            }
            else
            {
                cout << "Full Time wage\n";
                employeeWage = wageCalculator(fullDayHour);
                workedHours += fullDayHour;
            }
            cout << "Employees wage for today : " << employeeWage << "\n"
                 << endl;
        }
        else
        {
            employeeWage = wageCalculator(noWorkDay);
            cout << "Employee is absent\n"
                 << endl;
        }
        employeeWageMonth.push_back(employeeWage);
        workedDays++;
    }
    int days = 0;
    for (int &wages : employeeWageMonth)
    {
        days++;
        std::cout << "Day " << days << " - Wage : " << wages << "\n";
    }
    addEmployeeDataCSV();
    return 0;
}

int wageCalculator(int hoursPassed)
{
    return wagePerHour * hoursPassed;
}

void addEmployeeDataCSV() {
    ofstream employeeFile;
    employeeFile.open("EmployeeData.csv", ios::out | ios::app);
    employeeFile << "Day" << ", " << "Wage" << endl;
    for (int i = 0; i < employeeWageMonth.size(); i++){
        employeeFile << (i + 1) << ", " << employeeWageMonth[i] << endl;
    }
}