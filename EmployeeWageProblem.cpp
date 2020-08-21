#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

using namespace std;
void writeEmployeeDataCSV();
vector<vector<int>> monthlyWage;

void writeEmployeeDataCSV(int totalMonths)
{
    ofstream employeeFile;
    vector<int> wages;
    employeeFile.open("EmployeeData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        employeeFile << "ID"
                     << ", ";

        for (int month = 0; month < totalMonths; month++)
        {
            employeeFile << ", Month-" << (month + 1);
        }
        cout << endl;
        for (int employee = 0; employee < monthlyWage.size(); employee++)
        {
            employeeFile << "\nEmployee_" << (employee + 1);
            wages = monthlyWage[employee];
            for (int month = 0; month < totalMonths; month++)
            {
                employeeFile << ", " << wages[month];
            }
        }
    }
    employeeFile.close();
}

int getEmployeeHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    const int NUM_OF_WORKING_DAYS = 20;
    const int MAX_HRS_IN_MONTH = 100;

    int empHrs = 0;
    int totalEmpHrs = 0;
    int totalWorkingDays = 0;

    while (totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays <= NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        int empCheck = rand() % 3;
        switch (empCheck)
        {
        case IS_PART_TIME:
            empHrs = 4;
            break;
        case IS_FULL_TIME:
            empHrs = 8;
            break;
        default:
            empHrs = 0;
            break;
        }
        totalEmpHrs += empHrs;
    }
    return totalEmpHrs;
}

int main()
{
    srand(time(NULL));
    const int EMP_RATE_PER_HOUR = 20;
    int totalEmployees;
    int totalMonths;
    cout << "\nEnter total number of employees. \n";
    cin >> totalEmployees;
    cout << "\nEnter nunber of Months. \n";
    cin >> totalMonths;
    for (int i = 0; i < totalEmployees; i++)
    {
        vector<int> monthWages;
        for (int j = 0; j < totalMonths; j++)
        {
            int empWage = getEmployeeHours() * EMP_RATE_PER_HOUR;
            monthWages.push_back(empWage);
            cout << "Monthly Wage for Employee " << (i + 1) << " = " << empWage << endl;
        }
        monthlyWage.push_back(monthWages);
    }
    writeEmployeeDataCSV(totalMonths);
    return 0;
}