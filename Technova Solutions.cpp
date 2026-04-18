#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------
//  FUNCTION PROTOTYPES
// ---------------------------------------------
double calculateAllowance(double basicSalary);
double calculateGross(double basicSalary, double allowance);
double calculateTax(double grossSalary);
double calculateBonus(char rating);
double calculateNetSalary(double gross, double tax, double bonus);
void   displayEmployeeReport(string name, string id, double basic,
                              double allowance, double gross,
                              double tax, double bonus, double net);
void   displaySummaryReport(string names[], double netSalaries[], int n);

// ---------------------------------------------
//  MAIN
// ---------------------------------------------
int main() {
    cout << "============================================" << endl;
    cout << "   TechNova Solutions - Salary Management   " << endl;
    cout << "============================================" << endl;

    int n;
    cout << "\nEnter number of employees: ";
    cin >> n;
    cin.ignore();

    // Arrays to store employee data
    string names[100], ids[100];
    double basicSalaries[100], netSalaries[100];
    char   ratings[100];

    // -- INPUT LOOP ------------------------------
    for (int i = 0; i < n; i++) {
        cout << "\n--- Employee " << (i + 1) << " ---" << endl;

        cout << "Enter Name   : ";
        getline(cin, names[i]);

        cout << "Enter ID     : ";
        getline(cin, ids[i]);

        // Validate salary (must not be negative)
        do {
            cout << "Enter Basic Salary : ";
            cin >> basicSalaries[i];
            if (basicSalaries[i] < 0)
                cout << "  [Error] Salary cannot be negative. Try again." << endl;
        } while (basicSalaries[i] < 0);

        // Validate rating (must be A, B, C, or D)
        do {
            cout << "Enter Performance Rating (A/B/C/D): ";
            cin >> ratings[i];
            ratings[i] = toupper(ratings[i]);
            if (ratings[i] != 'A' && ratings[i] != 'B' &&
                ratings[i] != 'C' && ratings[i] != 'D')
                cout << "  [Error] Invalid rating. Enter A, B, C, or D." << endl;
        } while (ratings[i] != 'A' && ratings[i] != 'B' &&
                 ratings[i] != 'C' && ratings[i] != 'D');

        cin.ignore();
    }

    // -- PROCESSING & OUTPUT LOOP -----------------
    cout << "\n\n============================================" << endl;
    cout << "         INDIVIDUAL SALARY REPORTS          " << endl;
    cout << "============================================" << endl;

    for (int i = 0; i < n; i++) {
        double allowance = calculateAllowance(basicSalaries[i]);
        double gross     = calculateGross(basicSalaries[i], allowance);
        double tax       = calculateTax(gross);
        double bonus     = calculateBonus(ratings[i]);
        double net       = calculateNetSalary(gross, tax, bonus);

        netSalaries[i] = net;

        displayEmployeeReport(names[i], ids[i], basicSalaries[i],
                               allowance, gross, tax, bonus, net);
    }

    // -- SUMMARY REPORT --------------------------
    displaySummaryReport(names, netSalaries, n);

    return 0;
}

// ---------------------------------------------
//  FUNCTION DEFINITIONS
// ---------------------------------------------

// Calculate allowance based on basic salary
double calculateAllowance(double basicSalary) {
    double rate;
    if (basicSalary < 30000)
        rate = 0.20;
    else if (basicSalary <= 59999)
        rate = 0.15;
    else
        rate = 0.10;
    return basicSalary * rate;
}

// Calculate gross salary
double calculateGross(double basicSalary, double allowance) {
    return basicSalary + allowance;
}

// Calculate tax based on gross salary
double calculateTax(double grossSalary) {
    double rate;
    if (grossSalary < 40000)
        rate = 0.00;
    else if (grossSalary <= 69999)
        rate = 0.05;
    else
        rate = 0.10;
    return grossSalary * rate;
}

// Calculate performance bonus based on rating
double calculateBonus(char rating) {
    switch (rating) {
        case 'A': return 10000;
        case 'B': return 5000;
        case 'C': return 2000;
        default:  return 0;     // D
    }
}

// Calculate net salary
double calculateNetSalary(double gross, double tax, double bonus) {
    return gross - tax + bonus;
}

// Display individual employee salary report
void displayEmployeeReport(string name, string id, double basic,
                            double allowance, double gross,
                            double tax, double bonus, double net) {
    cout << "\n--------------------------------------------" << endl;
    cout << "  Employee Name   : " << name      << endl;
    cout << "  Employee ID     : " << id        << endl;
    cout << "--------------------------------------------" << endl;
    cout << "  Basic Salary    : Rs. " << basic     << endl;
    cout << "  Allowance       : Rs. " << allowance << endl;
    cout << "  Gross Salary    : Rs. " << gross     << endl;
    cout << "  Tax Deducted    : Rs. " << tax       << endl;
    cout << "  Performance Bon : Rs. " << bonus     << endl;
    cout << "  ----------------------------------------" << endl;
    cout << "  Net Salary      : Rs. " << net       << endl;
    cout << "--------------------------------------------" << endl;
}

// Display summary report for management
void displaySummaryReport(string names[], double netSalaries[], int n) {
    double totalSalary = 0;
    double highestNet  = netSalaries[0];
    int    highestIdx  = 0;

    for (int i = 0; i < n; i++) {
        totalSalary += netSalaries[i];
        if (netSalaries[i] > highestNet) {
            highestNet = netSalaries[i];
            highestIdx = i;
        }
    }

    double avgNet = totalSalary / n;

    cout << "\n\n============================================" << endl;
    cout << "         MANAGEMENT SUMMARY REPORT          " << endl;
    cout << "============================================" << endl;
    cout << "  Total Salary Paid    : Rs. " << totalSalary          << endl;
    cout << "  Average Net Salary   : Rs. " << avgNet               << endl;
    cout << "  Highest Net Salary   : Rs. " << highestNet           << endl;
    cout << "  Top Earner           : "     << names[highestIdx]    << endl;
    cout << "============================================" << endl;
    cout << "         End of Report - TechNova Solutions " << endl;
    cout << "============================================" << endl;
}
