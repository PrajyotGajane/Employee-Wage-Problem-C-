#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

using namespace std;
void writeEmployeeDataCSV();
vector<int> monthlyWages;

void writeEmployeeDataCSV() {
    ofstream employeeFile;
    employeeFile.open("EmployeeData.csv", ios::out | ios::trunc);
    employeeFile << "ID" << ", " << "Montly_Wage" << endl;
    for (int i = 0; i < monthlyWages.size(); i++){
        employeeFile << "Emplyee_ID " << (i + 1) << ", " << monthlyWages[i] << endl;
    }
}

int getEmployeeHours() {
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    const int NUM_OF_WORKING_DAYS = 20;
    const int MAX_HRS_IN_MONTH = 100;
   
    int empHrs = 0;
    int totalEmpHrs = 0;
    int totalWorkingDays = 0;
    
    while(totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays <= NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        int empCheck = rand() % 3;
        switch(empCheck)
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
    cout << "\nEnter total number of employees. \n";
    cin >> totalEmployees;
    for (int i = 0; i < totalEmployees; i++)
    {
        int empWage = getEmployeeHours() * EMP_RATE_PER_HOUR;
        monthlyWages.push_back(empWage);
        cout << "Monthly Wage for Employee " << (i + 1) << " = " << monthlyWages[i] << endl;
    }
    writeEmployeeDataCSV();
    return 0;
}