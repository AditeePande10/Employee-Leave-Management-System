#include "Employee.h"

int EmployeeSystem::hashIndex(char c1, char c2) {
    int hash = (c1 + c2) % 100;
    cout << "\tHash index used: " << hash << endl;
    return hash;
}

void EmployeeSystem::replaceFile(const string& oldFile, const string& newFile) {
    remove(oldFile.c_str());
    rename(newFile.c_str(), oldFile.c_str());
}

float EmployeeSystem::getSalary(const string& id) {
    ifstream file("salary.csv");
    string line, empId;
    float sal = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, empId, ',');
        if (empId == id) {
            ss >> sal;
            break;
        }
    }
    file.close();
    return sal;
}

// ---------- USER MANAGEMENT ----------
void EmployeeSystem::addUser() {
    EmployeeRecord e;
    cout << "Enter ID: "; cin >> e.id;
    cout << "Enter Name: "; cin >> e.name;
    cout << "Enter Age: "; cin >> e.age;
    cout << "Enter Salary: "; cin >> e.salary;
    cout << "Enter Experience: "; cin >> e.exp;

    ofstream emp("emp.csv", ios::app);
    ofstream sal("salary.csv", ios::app);
    ofstream leave("leave.csv", ios::app);

    emp << e.id << "," << e.name << "," << e.age << "," << e.salary << "," << e.exp << "\n";
    sal << e.id << "," << e.salary << "\n";
    leave << e.id << "," << e.name << ",20,15,10,40,0," << e.salary << ",-,-\n";

    emp.close(); sal.close(); leave.close();

    hashIndex(e.id[0], e.id[1]);
    cout << "✅ Employee added successfully!\n\n";
}

void EmployeeSystem::modifyUser() {
    string id;
    cout << "Enter Employee ID to modify: ";
    cin >> id;

    ifstream fin("emp.csv");
    ofstream fout("temp.csv");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        string empId, name, age, sal, exp;
        getline(ss, empId, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, sal, ',');
        getline(ss, exp, ',');

        if (empId == id) {
            found = true;
            cout << "1. Edit Age\n2. Edit Salary\n3. Edit Experience\nEnter choice: ";
            int ch; cin >> ch;
            string newVal;
            cout << "Enter new value: "; cin >> newVal;
            if (ch == 1) age = newVal;
            else if (ch == 2) sal = newVal;
            else if (ch == 3) exp = newVal;
        }
        fout << empId << "," << name << "," << age << "," << sal << "," << exp << "\n";
    }

    fin.close(); fout.close();
    replaceFile("emp.csv", "temp.csv");

    if (found) cout << "✅ Employee updated!\n\n";
    else cout << "❌ Employee not found!\n\n";
}

void EmployeeSystem::displayUsers() {
    ifstream file("emp.csv");
    string line;
    cout << "\nID\tName\tAge\tSalary\tExperience\n";
    cout << "-------------------------------------------\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, age, sal, exp;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, age, ',');
        getline(ss, sal, ',');
        getline(ss, exp, ',');
        cout << id << "\t" << name << "\t" << age << "\t" << sal << "\t" << exp << endl;
    }
    cout << endl;
}

// ---------- LEAVE MANAGEMENT ----------
void EmployeeSystem::applyLeave() {
    string id;
    cout << "Enter Employee ID: ";
    cin >> id;

    ifstream fin("leave.csv");
    ofstream fout("temp.csv");
    string line;
    bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        LeaveRecord l;
        getline(ss, l.id, ',');
        getline(ss, l.name, ',');
        ss >> l.casual; ss.ignore();
        ss >> l.sick; ss.ignore();
        ss >> l.study; ss.ignore();
        ss >> l.parental; ss.ignore();
        ss >> l.extra; ss.ignore();
        ss >> l.salary; ss.ignore();
        getline(ss, l.startDate, ',');
        getline(ss, l.endDate, ',');

        if (l.id == id) {
            found = true;
            cout << "1. Casual\n2. Sick\n3. Study\n4. Parental\nChoose leave type: ";
            int ch; cin >> ch;
            cout << "Enter number of leaves: ";
            int n; cin >> n;

            int* leavePtr = nullptr;
            if (ch == 1) leavePtr = &l.casual;
            else if (ch == 2) leavePtr = &l.sick;
            else if (ch == 3) leavePtr = &l.study;
            else if (ch == 4) leavePtr = &l.parental;

            if (*leavePtr - n < 0) {
                cout << "⚠ Extra leaves applied!\n";
                l.extra += abs(*leavePtr - n);
                *leavePtr = 0;
                l.salary -= l.salary * 0.025 * l.extra;
            } else {
                *leavePtr -= n;
            }

            cout << "Enter Start Date (dd/mm/yyyy): ";
            cin >> l.startDate;
            cout << "Enter End Date (dd/mm/yyyy): ";
            cin >> l.endDate;
        }

        fout << l.id << "," << l.name << "," << l.casual << "," << l.sick << ","
             << l.study << "," << l.parental << "," << l.extra << ","
             << l.salary << "," << l.startDate << "," << l.endDate << "\n";
    }

    fin.close(); fout.close();
    replaceFile("leave.csv", "temp.csv");
    if (found) cout << "✅ Leave updated!\n\n";
    else cout << "❌ Employee not found!\n\n";
}

void EmployeeSystem::resetLeave() {
    cout << "Enter Employee ID to reset leaves: ";
    string id; cin >> id;
    ifstream fin("leave.csv");
    ofstream fout("temp.csv");
    string line; bool found = false;

    while (getline(fin, line)) {
        stringstream ss(line);
        LeaveRecord l;
        getline(ss, l.id, ',');
        getline(ss, l.name, ',');
        ss >> l.casual; ss.ignore();
        ss >> l.sick; ss.ignore();
        ss >> l.study; ss.ignore();
        ss >> l.parental; ss.ignore();
        ss >> l.extra; ss.ignore();
        ss >> l.salary; ss.ignore();
        getline(ss, l.startDate, ',');
        getline(ss, l.endDate, ',');

        if (l.id == id) {
            found = true;
            l.casual = 20; l.sick = 15; l.study = 10; l.parental = 40;
            l.extra = 0; l.startDate = l.endDate = "-";
        }

        fout << l.id << "," << l.name << "," << l.casual << "," << l.sick << ","
             << l.study << "," << l.parental << "," << l.extra << ","
             << l.salary << "," << l.startDate << "," << l.endDate << "\n";
    }

    fin.close(); fout.close();
    replaceFile("leave.csv", "temp.csv");
    if (found) cout << "✅ Leave reset successfully!\n\n";
    else cout << "❌ Employee not found!\n\n";
}

void EmployeeSystem::searchLeave() {
    string id;
    cout << "Enter Employee ID: ";
    cin >> id;

    ifstream file("leave.csv");
    string line;
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        LeaveRecord l;
        getline(ss, l.id, ',');
        if (l.id == id) {
            found = true;
            getline(ss, l.name, ',');
            ss >> l.casual; ss.ignore();
            ss >> l.sick; ss.ignore();
            ss >> l.study; ss.ignore();
            ss >> l.parental; ss.ignore();
            ss >> l.extra; ss.ignore();
            ss >> l.salary;
            cout << "\nID: " << l.id << "\nName: " << l.name
                 << "\nCasual: " << l.casual << "\nSick: " << l.sick
                 << "\nStudy: " << l.study << "\nParental: " << l.parental
                 << "\nExtra Leaves: " << l.extra
                 << "\nSalary: " << l.salary << "\n";
        }
    }
    if (!found) cout << "❌ Employee not found!\n\n";
}

void EmployeeSystem::displayLeaves() {
    ifstream file("leave.csv");
    string line;
    cout << "\nID\tName\tCL\tSL\tSTL\tPL\tExtra\tSalary\tStart\tEnd\n";
    cout << "-----------------------------------------------------------\n";
    while (getline(file, line)) {
        stringstream ss(line);
        LeaveRecord l;
        getline(ss, l.id, ',');
        getline(ss, l.name, ',');
        ss >> l.casual; ss.ignore();
        ss >> l.sick; ss.ignore();
        ss >> l.study; ss.ignore();
        ss >> l.parental; ss.ignore();
        ss >> l.extra; ss.ignore();
        ss >> l.salary; ss.ignore();
        getline(ss, l.startDate, ',');
        getline(ss, l.endDate, ',');
        cout << l.id << "\t" << l.name << "\t" << l.casual << "\t" << l.sick << "\t"
             << l.study << "\t" << l.parental << "\t" << l.extra << "\t"
             << l.salary << "\t" << l.startDate << "\t" << l.endDate << endl;
    }
}