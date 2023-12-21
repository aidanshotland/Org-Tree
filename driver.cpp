/**
 * Start of a driver file to test orgtree.cpp
 * CS 210 Summer 2023
 * @Aidan Shotland
 * @27 Jun 2023
 */

#include "orgtree.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * THIS DRIVER FILE IS ONLY A START!
 * IT IS CRITICAL THAT YOU ADD YOUR
 * OWN TEST CASES. MOST CASES ARE
 * HIDDEN ON GRADESCOPE.
 */

/**
 * Print whether the given test case passed or failed
 * @param didPass - The test condition (true to pass, false to fail)
 * @param message - Description of what is being tested
 */
void asserts(bool didPass, string message) {
    if (didPass) {
        cout << "Passed: " << message << endl;
    } else {
        cout << "FAILED: " << message << endl;
        // Halts execution, comment out to
        // continue testing other parts
        // If you do comment this out, ignore the
        // "All test cases passed!" printout
        exit(EXIT_FAILURE);
    }
}

//TODO
int main(int argc, char **argv) {
    /*
     * Construct the following organization chart for testing
     *                1
     *           /    \    \
     *           2    3    4
     *          / \  / \   \
     *          5 6  7 8   9
     *         /   \       \
     *         10  11      12
     */

    Employee *head = new Employee(1, vector<int>{2, 3, 4});
    Employee *e2 = head->getDirectReports().at(0);
    Employee *e3 = head->getDirectReports().at(1);
    Employee *e4 = head->getDirectReports().at(2);

    e2->addDirectReports(vector<int>{5, 6});
    e3->addDirectReports(vector<int>{7, 8});
    e4->addDirectReport(9);

    Employee *e5 = e2->getDirectReports().at(0);
    Employee *e6 = e2->getDirectReports().at(1);
    Employee *e9 = e4->getDirectReports().at(0);

    e5->addDirectReport(10);
    e6->addDirectReport(11);
    e9->addDirectReport(12);

    Employee *Lebron = new Employee(23, vector<int>{24, 45});
    Employee *Kobe = Lebron->getDirectReports().at(0);
    Employee *Jordan = Lebron->getDirectReports().at(1);

    Kobe->addDirectReports(vector<int>{35, 2});
    Jordan->addDirectReport(10);

    Employee * Durant = Kobe->getDirectReports().at(0);
    Employee * Irving = Kobe->getDirectReports().at(0);
    Employee * Derozan = Jordan->getDirectReports().at(0);

    Employee * alone = new Employee(69);



    // Begin Testing
    // A few sample testing code are provided below

    // TODO Test all Orgtree functions
    //      according to the specifications in the comment section ABOVE each function signature.

    // IMPORTANT: You should also construct at least one different chart
    // Also make sure to check edge cases, such as empty chart, or one employee chart.

    // Test isEmployeePresentInOrg function
    bool employeePresent = Orgtree::isEmployeePresentInOrg(head, 6);
    asserts(employeePresent, "ID 6 Present in tree, your code returned false");
    employeePresent = Orgtree::isEmployeePresentInOrg(head, -2);
    asserts(employeePresent == false, "ID -2 Not present in tree");

    employeePresent = Orgtree::isEmployeePresentInOrg(Lebron, 2);
    asserts(employeePresent == true, "ID 2 is present in tree");

    employeePresent = Orgtree::isEmployeePresentInOrg(alone, -69);
    asserts(employeePresent == false, "ID -69 Not present in tree");



    //TODO...

    // Test findManagersOfEmployee function
    vector<int> manager_ids;
    employeePresent = Orgtree::findManagersOfEmployee(head, 11, manager_ids);
    asserts(employeePresent, "ID 11 Present in tree, your code returned false");
    vector<int> expected_manager_ids{ 6, 2, 1 };
    asserts(manager_ids == expected_manager_ids,
            "Your code should return (6, 2, 1) as managers of employee 11");
    manager_ids.clear();
    employeePresent = Orgtree::findManagersOfEmployee(head, -2, manager_ids);
    asserts(manager_ids.size() == 0, "ID -2 is not present in tree, its manager ids should be empty");

    manager_ids.clear();
    expected_manager_ids.clear();
    expected_manager_ids.push_back(45);
    expected_manager_ids.push_back(23);
    employeePresent = Orgtree::findManagersOfEmployee(Lebron, 10, manager_ids);
    asserts(manager_ids == expected_manager_ids,"Your code should return (45,23) as managers of employee 11");

    //TODO...

    // Test findEmployeeLevel function
    int employeeLevel = Orgtree::findEmployeeLevel(head, 4, 0);
    asserts(employeeLevel == 1, "Level of ID 4 returns " + to_string(employeeLevel) + ", expected 1");

    int employeeLevel2 = Orgtree::findEmployeeLevel(Lebron, 45, 0);
    asserts(employeeLevel2 == 1, "Level of ID 45 returns " + to_string(employeeLevel2) + ", expected 1");

    //TODO...

    // Test findClosestSharedManager function
    // Call the function with certain combination of the arguments
    // Assert / verify the returned Employee* has the expected Employee ID
    Employee * close = Orgtree::findClosestSharedManager(head, 10, 11);
    asserts(close->getEmployeeID() == 2, "Closest Shared Manager " + to_string(close->getEmployeeID())+ ", expected 2");

   close = Orgtree::findClosestSharedManager(Lebron, 10, 24);
    asserts(close->getEmployeeID() == 23, "Closest Shared Manager " + to_string(close->getEmployeeID())+ ", expected 23");

    //TODO...

    // Test findNumOfManagersBetween function
    int numManagers = Orgtree::findNumOfManagersBetween(head, 10, 11);
    asserts(numManagers == 3, "Managers between 10 and 11 returns " +
                              to_string(numManagers) + ", expected 3");

    numManagers = Orgtree::findNumOfManagersBetween(Lebron, 2, 10);
    asserts(numManagers == 3, "Managers between 2 and 10 returns " +
                              to_string(numManagers) + ", expected 3");

    // TODO numManagers = ...

    // Test deleteOrgtree function
    // VERY IMPORTANT: Related to valgrind memory leaking detection testing,
    // You MUST call your deleteOrgtree function at the end of this driver testing code
    // to delete all the allocated memory for the tree.

    Orgtree::deleteOrgtree(head);
    Orgtree::deleteOrgtree(Lebron);

    // Use the printed employee ID along the sequence of deletion to verify your implementation
    // This part will be autograded as well as manually inspected for grading

    cout << endl << "All test cases passed!" << endl;

    // Return EXIT_SUCCESS exit code
    exit(EXIT_SUCCESS);
}
