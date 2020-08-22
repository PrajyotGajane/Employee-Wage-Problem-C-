#include <iostream>
#include <time.h>
#include <ctime>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm> 

using namespace std;

int static totalEmpHrs = 0;

struct Company
{
    string companyName;
    int wagePerHour;
    int workingDays;
    int maxHours;
};

struct EmployeeDaily
{
    string empName;
    int dayNo;
    int wagePerHour;
    int hours;
    int wage;
    int monthNo;
    string companyName;
};

struct EmployeeMonthly
{
    string empName;
    int wagePerHour;
    int totalHours;
    int monthlyWage;
    int monthNo;
    string companyName;
};

vector<EmployeeMonthly *> monthlyEmpList;
vector<EmployeeDaily *> dailyEmpList;
vector<Company *> companyList;

void writeEmployeeDataDailyCSV()
{
    fstream employeeFile;
    employeeFile.open("EmpDailyData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        for (auto i = dailyEmpList.begin(); i != dailyEmpList.end(); ++i)
        {
            employeeFile << (*i)->empName;
            employeeFile << ", " << (*i)->dayNo;
            employeeFile << ", " << (*i)->wagePerHour;
            employeeFile << ", " << (*i)->hours;
            employeeFile << ", " << (*i)->wage;
            employeeFile << ", " << (*i)->monthNo;
            employeeFile << ", " << (*i)->companyName << endl;
        }
        cout << endl;
    }
    employeeFile.close();
}

void writeEmployeeDataCSV()
{
    fstream employeeFile;
    employeeFile.open("EmpMonthlyData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        employeeFile << "Name"
                     << ", "
                     << "Total-Hours"
                     << ", "
                     << "Montly-Wage"
                     << ", "
                     << "Wage-Per-Hour"
                     << ", "
                     << "Company-Name"
                     << ", " << endl;
        for (auto address = monthlyEmpList.begin(); address != monthlyEmpList.end(); ++address)
        {
            employeeFile << (*address)->empName;
            employeeFile << ", " << (*address)->totalHours;
            employeeFile << ", " << (*address)->monthlyWage;
            employeeFile << ", " << (*address)->wagePerHour;
            employeeFile << ", " << (*address)->companyName << endl;
        }
        cout << endl;
    }
    employeeFile.close();
}

int getMonthlyEmployeeHours()
{
    return totalEmpHrs;
}

int getDailyEmployeeHours()
{
    const int IS_PART_TIME = 1;
    const int IS_FULL_TIME = 2;
    int empHrs = 0;
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
    return empHrs;
}

void employeeMonthly(Company company, string empName)
{
    EmployeeMonthly *emp;
    emp = new EmployeeMonthly;
    emp->empName = empName;
    emp->totalHours = getMonthlyEmployeeHours();
    emp->monthlyWage = emp->totalHours * company.wagePerHour;
    emp->wagePerHour = company.wagePerHour;
    emp->companyName = company.companyName;

    monthlyEmpList.push_back(emp);
    writeEmployeeDataCSV();
}

void employeeDaily(Company company)
{
    string empName;
    cout << "Enter Employee name " << endl;
    cin >> empName;

    int NUM_OF_WORKING_DAYS = company.workingDays;
    int MAX_HRS_IN_MONTH = company.maxHours;
    totalEmpHrs = 0;
    int totalWorkingDays = 0;

    while (totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays < NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        EmployeeDaily *empDaily;
        empDaily = new EmployeeDaily;
        empDaily->empName = empName;
        empDaily->dayNo = totalWorkingDays;
        empDaily->hours = getDailyEmployeeHours();
        empDaily->wage = empDaily->hours * company.wagePerHour;
        empDaily->wagePerHour = company.wagePerHour;
        empDaily->monthNo = 1;
        empDaily->companyName = company.companyName;

        dailyEmpList.push_back(empDaily);
        totalEmpHrs += empDaily->hours;
    }
    employeeMonthly(company, empName);
    writeEmployeeDataDailyCSV();
}

void display()
{
    cout << "Name  Total-Hours  Montly-Wage  Wage-Per-Hour  Company-Name " << endl;
    for (auto address = monthlyEmpList.begin(); address != monthlyEmpList.end(); ++address)
    {
        cout << (*address)->empName << "       " << (*address)->totalHours << "          " << (*address)->monthlyWage << "         " << (*address)->wagePerHour << "          " << (*address)->companyName << endl;
    }
}

void setCompanyObjectDetails(Company *company)
{
    bool endKey = true;

    while (endKey)
    {
        int choice;
        cout << "\n1) Enter employee name 2) Display 4) Exit : ";
        cin >> choice;
        switch (choice)
        {
        case 1:

            employeeDaily(*company);
            break;
        case 2:
            display();
            break;
        case 4:
            endKey = false;
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
}

Company * checkCompanyExist(string companyName) {
    for (auto *itr : companyList){
        if (itr->companyName == companyName) {
            return itr;
        }
    }
    return NULL;
}

bool compareMonthlyWage(EmployeeMonthly* addressOne, EmployeeMonthly* addressTwo) 
{ 
    return ( addressOne->monthlyWage < addressTwo->monthlyWage ); 
}

void sortByMontlyWage()
{
    sort(monthlyEmpList.begin(), monthlyEmpList.end(), compareMonthlyWage);

    for (auto address = monthlyEmpList.begin(); address != monthlyEmpList.end(); ++address){
        cout << "Name : " << (*address)->empName <<endl;
        cout << "Montly-Wage : " << (*address)->monthlyWage <<endl;
        cout << "Company-Name :" << (*address)->companyName << endl;
        cout << "\n" << endl;
    }
}

void searchEmpolyee() {    
    int wage = 50;
    for (auto address = monthlyEmpList.begin(); address !=monthlyEmpList.end(); ++address) {
        if ((*address)->wagePerHour == wage) {
            cout << "Name: " << (*address)->empName << endl;
            cout << "Wage per hour" << (*address)->wagePerHour << endl;
            cout << "\n" << endl;
        }
    }
}

int main()
{
    string companyName;
    int rate;
    int workingDays;
    int maxHours;
    bool endKey = true;
    while (endKey)
    {
        int choice;
        cout << "1: Enter new company details 2: Sort by montly wage 3: Employee wage per hour=50 4: Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the details of the company" << endl;
            cout << "Enter the name of company" << endl;
            cin >> companyName;
            
            if(checkCompanyExist(companyName) != NULL) {
                cout << "Company already present" << endl;
                break;
            } 
            
            cout << "Enter the wage per hours of company" << endl;
            cin >> rate;
            cout << "Enter the working day of company" << endl;
            cin >> workingDays;
            cout << "Enter the max hours of company" << endl;
            cin >> maxHours;
            
            Company *company;
            company = new Company;
            company->companyName = companyName;
            company->wagePerHour = rate;
            company->workingDays = workingDays;
            company->maxHours = maxHours;
            
            if(checkCompanyExist(companyName) == NULL) {
                setCompanyObjectDetails(company);
                companyList.push_back(company);
            }
            else {
                setCompanyObjectDetails(checkCompanyExist(companyName));
            }    
            break;
        case 2:   
            cout << "Sorted by montly wage" << endl;
            sortByMontlyWage();
            break;
        case 3:
            cout << "Employee's with wage per hour = 50\n" << endl;
            searchEmpolyee();
            break;
        case 4:
            endKey = false;
            break;
        default :
            cout << "Invalid Input" << endl;
            break;
        }
    }
    return 0;
}