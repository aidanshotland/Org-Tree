#ifndef ORGTREE_H
#define ORGTREE_H
#include <ctype.h> // character manipualtion, e.g. tolower()
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>
using namespace std;
// An employee class to store an organization chart (tree) node
class Employee {
private:
    int employeeID;
    vector<Employee*> directReports; // children - direct reports
public:
// -1 employee ID indicate an empty Employee ID
    static const int EMPTY_EMPLOYEEID = -1;
// -1 indicate NOT found
    static const int NOT_FOUND = -1;
// default constructor
    Employee() {
        this -> employeeID = EMPTY_EMPLOYEEID;
    }
// Constructor for instantiating an employee instance with an employee id.
// Assume employee ID argument is unique among all employee IDs.
    Employee(int id) {
        this -> employeeID = id;
    }
// Constructor for instantiating an employee instance with an employee id
// and all direct reports to this employee.
    Employee(int id, vector<int> dReports) {
        this -> employeeID = id;
        for (int d : dReports) {
            this -> directReports.push_back(new Employee(d));
        }
    }
//Add a direct report to the employee
//Assume employee ID argument is unique among all employee IDs.
    void addDirectReport(int e_id) {
        this -> directReports.push_back(new Employee(e_id));
    }
//Add a group of direct reports to the employee
    void addDirectReports(vector<int> dReports) {
        for (int d : dReports) {
            this -> directReports.push_back(new Employee(d));
        }
    }
// Getters
    int getEmployeeID() {
        return this -> employeeID;
    }
    vector<Employee*> getDirectReports() {
        return this -> directReports;
    }
// No destructor here
// Use a recursive function to delete the org tree
// See below
};
class Orgtree {
public:
/**
* Check if an employee is present in an organization chart.
*
* @param head the head / root Employee of the organization chart
* @param e_id the employee id being searched
* @return true or false
* @see
*/
    static bool isEmployeePresentInOrg(Employee* head, int e_id);
/**
* Find all managers of an employee.
*
* @param head the head / root Employee of the organization chart
* @param e_id the employee id being searched
* @param managers a vector of ids of all managers in the ascending order
* of their tree height
* i.e., managers starting from direct manager node to the root
node
* If the org chart is empty, or e_id is the head, or
* e_id is not in the chart, managers should be empty after the
search.
* @return is employee found
* @see
*/
    static bool findManagersOfEmployee(Employee* head, int e_id, vector<int>
    &managers);
/**
* Find the level of an employee in an organization chart / tree.
*
* <p>
* The head / root of the org chart has a level of 0, children of the head have
* a level of head plus 1, and so on and so forth...
*
* <p>
* Assumption: e_id is unique among all employee IDs
*
* @param head the head / root Employee of the organization chart
* @param e_id the employee id being searched
* @param headLevel the level of the head employee of the organization
* @return level of the employee in the org chart
* returns Employee::NOT_FOUND if e_id is not present
* @see
*/
    static int findEmployeeLevel(Employee* head, int e_id, int headLevel);
/**
* Find the closest shared manager of two employees e1 and e2.
*
* <p>
* There are two possible organizational relationships between two employees in
the org chart:
* case 1: e1 or e2 is a manager of the other employee;
* case 2: e1 or e2 is not a manager of the other employee, they have at least
one shared manager
*
* Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee
2 in the organization chart
*
* <p>
* Assumption: e1_id and e2_id are unique among all employee IDs
*
* @param head the head / root Employee of the organization chart
* @param e1_id id of employee 1 being searched
* @param e2_id id of employee 2 being searched
* @return closest shared manager in the org chart between employee e1 and
employee e2
* if head is nullptr, returns nullptr
* if neither e1 or e2 is present, returns empty employee
* if e1 is present and e2 is not, returns e1
* if e2 is present and e1 is not, returns e2
* if e1 and e2 both are present, returns their closest shared manager
* if e1 is a manager (ancestor) of e2, returns e1
* else if e2 is a manager (ancestor) of e1, returns e2
* else returns the closest shared manager of e1 and e2
* @see
*/
    static Employee* findClosestSharedManager(Employee* head, int e1_id, int e2_id);
/**
* Calculate the number of managers between employee e1 and employee e2.
*
* <p>
* The number of managers between employee e1 and employee e2 can be calculated
by:
* number of edges between employee 1 and closest shared manager +
* number of edges between employee 2 and closest shared manager - 1
*
* <p>
* Assumption: e1_id and e2_id are unique among all employee IDs
*
* @param head the head / root Employee of the organization chart
* @param e1_id id of employee 1 being searched
* @param e2_id id of employee 2 being searched
* @return number of managers between employee e1 and employee e2
* returns Employee::NOT_FOUND if either e1 or e2 is not present in the
chart
* @see
*/
    static int findNumOfManagersBetween(Employee* head, int e1_id, int e2_id);
/** Recursively delete a tree
* The proper implementation of this function is also needed for
* passing the valgrind memory leaking test.
*
* <p>
* Traversing from the head / root node, recursively deallocate
* the memory of the descendants from the leaf node level.
*
* DO NOT worry about removing them from the vector directReports
*
* Use post order traversal:
* Delete / deallocate the children recursively
* Delete / deallocate the current node after deleting its children
* Before deleting the current node, print its employee ID and a new line
* The print here is for verifying the order of the deletion
* This part will be autograded as well as manually inspected for grading
*
* For example, with the following org chart, the post order traversal
* order would be 5 6 2 7 8 3 1, and the nodes should be deleted in that order
* 1
* / \
* 2 3
* / \ / \
* 5 6 7 8
*
* @param head the head / root Employee of the organization chart
* @return None
*
* @see
*/
    static void deleteOrgtree(Employee* head);
};
#endif
