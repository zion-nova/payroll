#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
double readNumber(const std::string& prompt, double maximum) {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            return -1.0;
        }

        istringstream stream(input);
        double value;
        char extra;
        if ((stream >> value) && !(stream >> extra) && std::isfinite(value) &&
            value >= 0.0 && value <= maximum) {
            return value;
        }

        std::cout << "Enter a number from 0 to " << maximum << ".\n";
    }
}

int main() {
    std::cout << "=== Weekly Payroll Calculator ===\n";

    cout << "Employee name: ";
    string employeeName;
    if (!getline(std::cin, employeeName)) {
        cerr << "Could not read employee name.\n";
        return 1;
    }
    if (employeeName.empty()) {
        cerr << "Employee name cannot be empty.\n";
        return 1;
    }

    const double hoursWorked = readNumber("Hours worked: ", 1000000.0);
    if (hoursWorked < 0.0) {
        cerr << "Could not read hours worked.\n";
        return 1;
    }

    const double hourlyRate = readNumber("Hourly rate: $", 1000000.0);
    if (hourlyRate < 0.0) {
        cerr << "Could not read hourly rate.\n";
        return 1;
    }

    const double taxRate = readNumber("Withholding percentage (0-100): ", 100.0);
    if (taxRate < 0.0) {
        std::cerr << "Could not read withholding percentage.\n";
        return 1;
    }

    constexpr double regularHoursLimit = 40.0;
    constexpr double overtimeMultiplier = 1.5;
    const double regularHours = std::min(hoursWorked, regularHoursLimit);
    const double overtimeHours = std::max(hoursWorked - regularHoursLimit, 0.0);
    const double regularPay = regularHours * hourlyRate;
    const double overtimePay = overtimeHours * hourlyRate * overtimeMultiplier;
    const double grossPay = regularPay + overtimePay;
    const double tax = grossPay * taxRate / 100.0;

    std::cout << std::fixed << std::setprecision(2)
              << "\n--- Payroll Summary ---\n"
              << "Employee:        " << employeeName << '\n'
              << "Regular hours:   " << regularHours << '\n'
              << "Overtime hours:  " << overtimeHours << '\n'
              << "Regular pay:     $" << regularPay << '\n'
              << "Overtime pay:    $" << overtimePay << '\n'
              << "Gross pay:       $" << grossPay << '\n'
              << "Withholding (" << taxRate << "%): $" << tax << '\n'
              << "Net pay:         $" << grossPay - tax << '\n';
    return 0;
}
