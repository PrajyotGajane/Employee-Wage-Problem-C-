#include <iostream>
#include <time.h>
#include <ctime>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int totalEmpHrs;

struct CompanyDetails
{
    string companyName;
    int wagePerHour;
    int workingDays;
    int maxHours;
};

struct EmpDailyDetails
{
    string empName;
    int dayNo;
    int wagePerHour;
    int hours;
    int wage;
    int monthNo;
    int totalWage;
    string companyName;
};

struct EmpMonthlyDetails
{
    string empName;
    int wagePerHour;
    int totalHours;
    int monthlyWage;
    int monthNo;
    string companyName;
};

vector<EmpMonthlyDetails *> monthlyEmpList;
vector<EmpDailyDetails *> dailyEmpList;
vector<CompanyDetails *> companyList;

void writeEmployeeDataDailyCSV()
{
    fstream employeeFile;
    employeeFile.open("EmpDailyData.csv", ios::out | ios::trunc);
    if (employeeFile.is_open())
    {
        employeeFile << "Name"
                     << ", "
                     << "Day"
                     << ", "
                     << "Wage-Per-Hour"
                     << ", "
                     << "Hours"
                     << ", "
                     << "Wage"
                     << ","
                     << "Month"
                     << ","
                     << "Total-Wage"
                     << ","
                     << "Company-Name"
                     << endl;
        for (auto i = dailyEmpList.begin(); i != dailyEmpList.end(); ++i)
        {
            employeeFile << (*i)->empName;
            employeeFile << ", " << (*i)->dayNo;
            employeeFile << ", " << (*i)->wagePerHour;
            employeeFile << ", " << (*i)->hours;
            employeeFile << ", " << (*i)->wage;
            employeeFile << ", " << (*i)->monthNo;
            employeeFile << ", " << (*i)->totalWage;
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
                     << endl;
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

void employeeMonthly(CompanyDetails company, string empName)
{
    EmpMonthlyDetails *emp;
    emp = new EmpMonthlyDetails;
    emp->empName = empName;
    emp->totalHours = getMonthlyEmployeeHours();
    emp->monthlyWage = emp->totalHours * company.wagePerHour;
    emp->wagePerHour = company.wagePerHour;
    emp->companyName = company.companyName;

    monthlyEmpList.push_back(emp);
    writeEmployeeDataCSV();
}

void employeeDaily(CompanyDetails company)
{
    string empName;
    cout << "Enter Employee name " << endl;
    cin >> empName;

    int NUM_OF_WORKING_DAYS = company.workingDays;
    int MAX_HRS_IN_MONTH = company.maxHours;
    totalEmpHrs = 0;
    int totalWorkingDays = 0;
    int totalWage = 0;

    while (totalEmpHrs <= MAX_HRS_IN_MONTH && totalWorkingDays < NUM_OF_WORKING_DAYS)
    {
        totalWorkingDays++;
        EmpDailyDetails *empDaily;
        empDaily = new EmpDailyDetails;
        empDaily->empName = empName;
        empDaily->dayNo = totalWorkingDays;
        empDaily->hours = getDailyEmployeeHours();
        empDaily->wage = empDaily->hours * company.wagePerHour;
        empDaily->wagePerHour = company.wagePerHour;
        empDaily->monthNo = 1;
        empDaily->companyName = company.companyName;
        totalWage += empDaily->hours * company.wagePerHour;
        empDaily->totalWage = totalWage;
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

void setCompanyObjectDetails(CompanyDetails *company)
{
    bool endKey = true;

    while (endKey)
    {
        int choice;
        cout << "\n1) Enter employee name  2) Display  4) Exit : ";
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

void getTotalWageCompany(string companyName)
{
    int totalWage = 0;
    for (auto *itr : monthlyEmpList)
    {
        if (itr->companyName == companyName)
        {
            totalWage += itr->monthlyWage;
        }
    }
    cout << "Total Wage of Company : " << companyName << " is : " << totalWage << endl;
}

CompanyDetails *checkCompanyExist(string companyName)
{
    for (auto *itr : companyList)
    {
        if (itr->companyName == companyName)
        {
            return itr;
        }
    }
    return NULL;
}

bool compareMonthlyWage(EmpMonthlyDetails *addressOne, EmpMonthlyDetails *addressTwo)
{
    return (addressOne->monthlyWage < addressTwo->monthlyWage);
}

void sortByMontlyWage()
{
    sort(monthlyEmpList.begin(), monthlyEmpList.end(), compareMonthlyWage);

    for (auto address = monthlyEmpList.begin(); address != monthlyEmpList.end(); ++address)
    {
        cout << "Name : " << (*address)->empName << endl;
        cout << "Montly-Wage : " << (*address)->monthlyWage << endl;
        cout << "Company-Name :" << (*address)->companyName << endl;
        cout << "\n"
             << endl;
    }
}

void getCompanyDetails()
{
    string companyName;
    int rate;
    int workingDays;
    int maxHours;
    cout << "Enter the details of the company\n"
         << endl;
    cout << "Enter the name of company" << endl;
    cin >> companyName;

    if (checkCompanyExist(companyName) != NULL)
    {
        cout << "Company already present\n"
             << endl;
        return;
    }

    cout << "Enter the wage per hours of company" << endl;
    cin >> rate;
    cout << "Enter the working day of company" << endl;
    cin >> workingDays;
    cout << "Enter the max hours of company" << endl;
    cin >> maxHours;

    CompanyDetails *company;
    company = new CompanyDetails;
    company->companyName = companyName;
    company->wagePerHour = rate;
    company->workingDays = workingDays;
    company->maxHours = maxHours;

    if (checkCompanyExist(companyName) == NULL)
    {
        setCompanyObjectDetails(company);
        companyList.push_back(company);
    }
    else
    {
        setCompanyObjectDetails(checkCompanyExist(companyName));
    }
}

int main()
{
    string companyName;
    bool endKey = true;
    while (endKey)
    {
        int choice;
        cout << "1: Enter new company details  2: Sort by montly wage  3: Employee wage per hour=50  4: Exit  5: View Company Total Wage" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            getCompanyDetails();
            break;
        case 2:
            sortByMontlyWage();
            break;
        case 4:
            endKey = false;
            break;
        case 5:
            cout << "Enter company name " << endl;
            cin >> companyName;
            getTotalWageCompany(companyName);
            break;
        default:
            cout << "Invalid Input" << endl;
            break;
        }
    }
    return 0;
}