#include "Employee.h"

int main() {
    EmployeeSystem sys;
    int ch;

    while (true) {
        cout << "\n----- EMPLOYEE LEAVE MANAGEMENT SYSTEM -----\n";
        cout << "1. Apply Leave\n2. Reset Leave\n3. Search Leave\n4. Display All Leaves\n";
        cout << "5. Add User\n6. Modify User\n7. Display All Users\n8. Exit\n";
        cout << "Choose: ";
        cin >> ch;

        switch (ch) {
            case 1: sys.applyLeave(); break;
            case 2: sys.resetLeave(); break;
            case 3: sys.searchLeave(); break;
            case 4: sys.displayLeaves(); break;
            case 5: sys.addUser(); break;
            case 6: sys.modifyUser(); break;
            case 7: sys.displayUsers(); break;
            case 8: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice!\n"; break;
        }
    }
}