#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

using namespace std;
void writeEmployeeDataCSV(int, string, int, vector<int>);
vector<vector<int>> monthlyWage;
int getEmployeeHours(struct CompanyEmpWage);

void writeEmployeeDataCSV(int totalMonths, string companyName, int employee, vector<int> wages)
{
    fstream employeeFile;
    employeeFile.open("EmployeeData.csv", ios::out | ios::app);
    employeeFile.seekg(0, ios::end);
    if (employeeFile.is_open())
    {
        if (employeeFile.tellp() == 0)
        {
            employeeFile << "Company"
                         << ", "
                         << "ID"
                         << ", ";

            for (int month = 0; month < totalMonths; month++)
            {
                employeeFile << ", Month-" << (month + 1);
            }
        }
        employeeFile.seekg(0, ios::beg);

        employeeFile << "\n"
                     << companyName;
        employeeFile << ", Employee_" << (employee + 1);
        for (int month = 0; month < totalMonths; month++)
        {
            employeeFile << ", " << wages[month];
        }
        cout << endl;
    }
    employeeFile.close();
}

struct CompanyEmpWage
{
    string companyName;
    int numOfWorkingDays;
    int maxHoursMonth;
    int ratePerHour;

public:
    void setCompanyDetails(string companyName, int numOfWorkingDays, int maxHoursMonth, int ratePerHour)
    {
        this->companyName = companyName;
        this->numOfWorkingDays = numOfWorkingDays;
        this->maxHoursMonth = maxHoursMonth;
        this->ratePerHour = ratePerHour;
    }
};

void companyWageDetails(struct CompanyEmpWage companyDetails)
{
    int EMP_RATE_PER_HOUR = companyDetails.ratePerHour;
    int totalEmployees;
    int totalMonths;
    cout << "\nEnter total number of employees. \n";
    cin >> totalEmployees;
    cout << "\nEnter nunber of Months. \n";
    cin >> totalMonths;
    for (int employee = 0; employee < totalEmployees; employee++)
    {
        vector<int> monthWages;
        for (int j = 0; j < totalMonths; j++)
        {
            int empWage = getEmployeeHours(companyDetails) * EMP_RATE_PER_HOUR;
            monthWages.push_back(empWage);
            cout << "Monthly Wage for Employee " << (employee + 1) << " = " << empWage << endl;
        }
        monthlyWage.push_back(monthWages);
        writeEmployeeDataCSV(totalMonths, companyDetails.companyName, employee, monthWages);
    }
}

int getEmployeeHours(struct CompanyEmpWage company)
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    int NUM_OF_WORKING_DAYS = company.numOfWorkingDays;
    int MAX_HRS_IN_MONTH = company.ratePerHour;

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
    struct CompanyEmpWage companyDetails;
    string companyName;
    int numOfWorkingDays;
    int maxHoursMonth;
    int ratePerHour;
    bool endKey = true;
    while (endKey)
    {
        int choice;
        cout << "1: Enter company details 2: Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the name of the company " << endl;
            cin >> companyName;
            cout << "Number of working days" << endl;
            cin >> numOfWorkingDays;
            cout << "Enter maximum hours of work in a month " << endl;
            cin >> maxHoursMonth;
            cout << "Rate per hour" << endl;
            cin >> ratePerHour;
            companyDetails.setCompanyDetails(companyName, numOfWorkingDays, maxHoursMonth, ratePerHour);
            companyWageDetails(companyDetails);
            break;
        case 2:
            endKey = false;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
    return 0;
}