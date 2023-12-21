#include "orgtree.h"
#include <iostream>
/**
*I the undersigned promise that the submitted assignment is my own work. While I was
free to discuss ideas with others, the work contained is my own. I recognize that
should this not be the case; I will be subject to penalties as outlined in the course
syllabus.
Name: Aidan Shotland
Red ID: 826087269

* Check if an employee is present in an organization chart.
*
* @param head the head / root Employee of the organization chart
* @param e_id the employee id being searched
* @return true or false
* returns false if head is nullptr
* @see
*/
bool Orgtree::isEmployeePresentInOrg(Employee* head, int e_id) {
// Write your recursive implementation here
// Important: Your implementation MUST use the recursive approach
// as required in the assignment 3 prompt to avoid penalties.
// base case 1: empty organization chart, return false
// base case 2: if the employee is found, return true
// search employee in each subtree of the head
// return true if the employee is found in one of the child subtree
// if not found, return false

    //base case 1
    if(head == nullptr) {
        return false;
    }
    //base case2
    else if(head->getEmployeeID()==e_id){
        return true;
    }
    //children of head
    vector<Employee*> reports = head->getDirectReports();

    int i = 0;
    //iterate until vector size at level is met
    while(i<reports.size()) {
        //use child node as head to recurse to next level
        if(isEmployeePresentInOrg(reports.at(i),e_id)){
            //return true if found
            return true;
        }
        i++;
    }
    //not found
    return false;

}
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
bool Orgtree::findManagersOfEmployee(Employee* head, int e_id, vector<int>
&managers) {
// The implementation should be similar to isEmployeePresentInOrg
// Search subtrees from the head, after all subtrees are searched,
// if employee e_id is found:
// the head should be inserted to the managers vector along
// the backtracking process of recursive calls
// Note:
// do NOT add the employee's own e_id to the passed-in managers vector
// return false if employee is not found
    //base case 1
    if(head == nullptr) {
        return false;
    }
    //base case 2
    else if(head->getEmployeeID()==e_id){
        return true;
    }
    //children of head
    vector<Employee*> reports = head->getDirectReports();
    int i = 0;
    //iterate through tree level
    while(i<reports.size()) {
        //recurse to next level of tree
        if(findManagersOfEmployee(reports.at(i),e_id,managers)){
            //if ID is found push back all managers recursively until vector is complete
            managers.push_back(head->getEmployeeID());
            //return true if found
            return true;
        }
        i++;
    }
    //employee not found
    return false;


}
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
* returns Employee::NOT_FOUND if e_id is not present or head is nullptr
* @see
*/
int Orgtree::findEmployeeLevel(Employee* head, int e_id, int headLevel) {
// Write your recursive implementation here.
// Important: Your implementation MUST use the recursive approach
// as required in the assignment 3 prompt to avoid penalties.
// base case 1: empty organization chart
// base case 2: the employee is found, returns the employee level
// search employee from each child of the head
// if not found

    //base case 1
    if(head == nullptr) {
        return Employee::NOT_FOUND;
    }
    //base case 2
    else if(head->getEmployeeID()==e_id){
        return headLevel;
    }
    //vector for children of head
    vector<Employee*> reports = head->getDirectReports();
    //for each loop to recurse through level
    for(Employee* child: reports){
        //store level in level variable
        //each time increment level by 1 as we go deeper into tree
        //recurse until base case
        int level= findEmployeeLevel(child,e_id, headLevel+1);
        //if level is NOT -1 employee found
        if(level>=0){
            return level;
        }
    }
    //employee not found
    return Employee::NOT_FOUND;
}
/**
* Find the closest shared manager of two employees e1 and e2.
*
* <p>
* There are two possible organizational relationships between two employees in the
org chart:
* case 1: e1 or e2 is a manager of the other employee;
* case 2: e1 or e2 is not a manager of the other employee, they have at least one
shared manager
*
* Employee 1 is a manager of employee 2 if employee 1 is an ancestor of employee 2
in the organization chart
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
* if neither e1 or e2 is present, returns nullptr
* if e1 is present and e2 is not, returns e1
* if e2 is present and e1 is not, returns e2
* if e1 and e2 both are present, returns their shared manager
* if e1 is a manager (ancestor) of e2, returns e1
* else if e2 is a manager (ancestor) of e1, returns e2
* else returns the shared manager of e1 and e2
* @see
*/
Employee* Orgtree::findClosestSharedManager(Employee* head, int e1_id, int e2_id) {
// Write your recursive implementation here
// Important: Your implementation MUST use the recursive approach
// as required in the assignment 3 prompt to avoid penalties.
// base case 1: empty organization chart
// base case 2: either e1_id or e2_id is the same as the head / root
// Recursively traverse through direct reports of the head to find
// where e1 and e2 are
/*
For each recursive call (starting from the root), you need to handle three
possible scenarios:
1) if e1 is found in one subtree, and e2 is found from another subtree;
the head at that recursive step would be the closest shared manager of e1
and e2. you can use the returned pointer (being NOT NULL) from
findClosestSharedManager to see if e1 or e2 is found from a subtree (one of the base cases).
2) if either e1 or e2 is first found in one subtree (following one subtree),
but the other employee is NOT found from any other subtree, then the found
employee must either be the manager of the other employee, or the other
employee is NOT in the org chart; in either case, the first found employee should be
returned as the shared manager.
3) if neither e1 or e2 is found in the org chart, return nullptr
*/
    //base case 1
   if(head== nullptr){
       return nullptr;
   }
   //base case 2
   if(head->getEmployeeID()==e1_id|| head->getEmployeeID()==e2_id){
       return head;
   }
    //initialize pointers e1 and e2
   Employee* e1 = nullptr;
   Employee* e2 = nullptr;

    //vector for children of head
   vector<Employee*> reports = head->getDirectReports();
   //for each to iterate through each tree level
   for(Employee * child : reports){
       //recursive statement stored into sharedManager pointer
       //pointer will either be null or a matching employee
       Employee * sharedManager = findClosestSharedManager(child, e1_id, e2_id);
       //pointer is not null, employee found!
       if(sharedManager!= nullptr){
           //sharedManager ID matches e1 ID, set equal
           if(sharedManager->getEmployeeID()==e1_id){
               e1 = sharedManager;
           }
           //if not e1 has to be e2 ID
           else{
               e2 = sharedManager;
           }
       }
   }
   //scenario 1, both employee ID's in different subtrees.
    if(e2!= nullptr&&e1!= nullptr){
        return head;
    }
    //scenario 2. only one ID is found
    else if(e1 != nullptr){
        return e1;
    }
    else if(e2!= nullptr){
        return e2;
    }
    //scenario 3, neither employees exist in tree
    else {
        return nullptr;
    }
}
/**
* Calculate the number of managers between employee e1 and employee e2.
*
* <p>
* The number of managers between employee e1 and employee e2 can be calculated by:
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
chart or head is nullptr
* @see
*/
int Orgtree::findNumOfManagersBetween(Employee* head, int e1_id, int e2_id) {
// Write your implementation here. You do NOT need to use recursive approach here.
// Use the above functions wherever you need to implement this function.
// Continue only if both employee nodes e1_id and e2_id are in the org chart tree
// otherwise, return Employee::NOT_FOUND

    //if head is null not found
    if(head == nullptr) {
        return Employee:: NOT_FOUND;
    }
    //if an ID cannot be found, return not found
    if(!(isEmployeePresentInOrg(head,e1_id) && isEmployeePresentInOrg(head,e2_id))){
        return Employee:: NOT_FOUND;
    }

    //find closest manager using above function
    Employee* closest = findClosestSharedManager(head, e1_id, e2_id);
    //edge1 and edge2 are the distance away each child is away from closest manager
    int edge1 = findEmployeeLevel(closest, e1_id, 0);
    int edge2 = findEmployeeLevel(closest, e2_id, 0);
    //implement calculation
    return edge1 +edge2 -1;


// The number of managers between employee e1 and employee e2 can be calculated by:
// number of edges between e1_id and closest shared manager +
// number of edges between e2_id and closest shared manager - 1

}
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
void Orgtree::deleteOrgtree(Employee* head) {
// Write your recursive implementation here
// Important: Your implementation MUST use the recursive approach
// as required in the assignment 3 prompt to avoid penalties.
// base case: empty tree or organization chart
// delete children recursively
// print current node's employee ID and a new line
// delete the current node after deleting its children

    // only works if list is not empty
    if(head!=nullptr){
        //children of head node
        vector<Employee*> reports = head->getDirectReports();
        //iterate through node at level
        for(Employee *child : reports){
            //recursive function that uses the child value as new head
            deleteOrgtree(child);
        }
        //print each ID that is deleted
        std::cout << "Employee ID: " << head->getEmployeeID() << endl;
        delete head;
    }

}
