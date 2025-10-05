#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct EmployeeRecord {
    string id, name, age, salary, exp;
};

struct LeaveRecord {
    string id, name;
    int casual, sick, study, parental, extra;
    float salary;
    string startDate, endDate;
};

class EmployeeSystem {
public:
    void addUser();
    void modifyUser();
    void displayUsers();

    void applyLeave();
    void resetLeave();
    void searchLeave();
    void modifyLeave();
    void displayLeaves();

private:
    int hashIndex(char, char);
    void replaceFile(const string&, const string&);
    float getSalary(const string& id);
};

#endif