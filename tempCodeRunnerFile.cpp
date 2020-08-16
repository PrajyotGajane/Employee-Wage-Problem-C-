int days = 0;
    for (const int &wages : employeeWageMonth)
    {
        days++;
        std::cout << "Day " << days << " - Wage : " << wages << "\n";
    }