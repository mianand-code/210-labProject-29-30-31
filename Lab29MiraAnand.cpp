// COMSC-210 | Lab 31 | Mira Anand
// Module 11, Lesson: Software Development Life Cycle, Assignment: Beta Release
// IDE used: Visual Studio Code for Mac

// Add a comment ("meets requirement") next to lines of code that meet the requirements listed in the "Requirements Analysis"
// All changes to the program will happen in this file "Lab29MiraAnand.cpp", but different branches will be utilized
// To see the original pseudocode from start to finish, please see these GitHub commits in the "main" branch: "Initial commit - Starting pseudocode" to "Commit - end of pseudocode. Final edits were made"
// To see the original mockup/wireframe code from start to finish, please see these GitHub commits in the "main" branch: "Commit - Starting mockup/wireframe code" to "Commit - End of mockup/wireframe code. Final edits were made"
// To see the original Alpha Release code from start to finish, please see these GitHub commits in the "alpha" branch: "Commit - Starting Alpha Release" to "Commit - end of Alpha Release. Final edits were made"
// To see the progression of Beta Release and "bugs.txt", please see all GitHub commits in the "beta" branch

// Creation of a retail store inventory simulation (in life) - meets requirement

#include <array> // to use std::array
#include <cstdlib> // for randomization
#include <ctime> // for randomization
#include <fstream> // for file operations
#include <iostream>
#include <list> // to use std::list
#include <map> // to use std::map
#include <string>
using namespace std;

// declaration and initialization of global const variables
// these variables will be used to assist with randomization in main() + they make reading the code easier and can be easily changed/added to in the future to accomodate any coding updates
// for department index
const int ELECTRONICS_DEPT_INDEX = 0; // accessed by [0] in array of std::lists
const int CLOTHING_DEPT_INDEX = 1; // accessed by [1] in array of std::lists
const int GROCERIES_DEPT_INDEX = 2; // accessed by [2] in array of std::lists

// for department name
const string ELECTRONICS_DEPT_NAME = "electronics"; 
const string CLOTHING_DEPT_NAME = "clothing"; 
const string GROCERIES_DEPT_NAME = "groceries"; 

// for event type
const string DELIVERY_EVENT = "delivery";
const string PURCHASE_EVENT = "purchase";
const string THEFT_EVENT = "theft";

// for season name
const string SEASON_1 = "Spring";
const string SEASON_2 = "Summer";
const string SEASON_3 = "Fall";
const string SEASON_4 = "Winter";

// the product to be delivered as replenishment when a delivery event is triggered for a department that is completely out of stock
const string REPLENISHMENT_PRODUCT = "replenishment";

// function prototypes
// creating 3 functions - meets requirement
// 1. to output the contents of the inventory - initially (after input file reading) and then after each time period occurs
void displayInventory(const map<string, array<list<string>, 3>> inventory);
// 2. to perform the actual inventory simulation (when inventory-related events occur)
void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string, string, string, int);
// 3. a helper function to assist the inventory simulation function (so the inventory simulation function isn't too complex/cluttered)
bool checkUpdateInventoryStock(list<string>&, string);

int main()
{
    srand(time(0)); // needed as the first line in main() for randomization - so the inventory simulation is more realistic

    // creation of the foundational data structure - meets requirement
    // - creation of an std::map named "inventory"
    // - the key is a string variable that represents a season: Spring, Summer, Fall, Winter
    // - the value is an std::array of 3 std::lists. These std::lists represent different store departments: electronics, clothing, groceries
    // - string values that represent product names will be held within each of these std::lists
    map<string, array<list<string>, 3>> inventory;

    // declaration of variables that will be used to read/hold data from the input file
    string season; // to hold season name
    string department; // to hold department name
    string product; // to hold product name

    // declaration and initialization of arrays that will assist with selecting random events, seasons, and departments
    const string events[] = {DELIVERY_EVENT, PURCHASE_EVENT, THEFT_EVENT}; // for events
    const string seasons[] = {SEASON_1, SEASON_2, SEASON_3, SEASON_4}; // for seasons
    const string departments[] {ELECTRONICS_DEPT_NAME, CLOTHING_DEPT_NAME, GROCERIES_DEPT_NAME}; // for departments

    // input file reading code block - meets requirement
    // in my project/design proposal, I originally stated that I would have the season, department, & product name on 1 line in the input file, separated by commas
    // I am deciding to change this format, just to make reading from the input file easier
    // each season, department, and product name will now have its own line in the input file. No spaces allowed, department name is case sensitive
    // the input file I am using is named "inventoryFinal.txt" and it contains more than 100 lines of input - meets requirement
    // note: the input file should be structured exactly the way I have it in order for the program to operate successfully. Please open "inventoryFinal.txt" to see exact structure

    ifstream inputFile("inventoryFinal.txt"); // creating an ifstream object to open the input file
    if (!inputFile) // if the input file does not open
    {
        cout << "ERROR: Could not open input file. Please make sure the file exists in the correct location and try running the program again." << endl; // report the error
        cout << "Program will now exit..." << endl; // exit the program since we do not have data to work with
        return 1; // exit and return an error state
    }

    while (getline(inputFile, season)) // as long as the season is being read/extracted from the input file (season is the key/very first line of the input file)
    {
        // the input file reads/extracts according to the order of season, department, and then product
        if (!getline(inputFile, department)) break; // break out of the loop if the department cannot be read/extracted
        if (!getline(inputFile, product)) break; // break out of the loop if the product cannot be read/extracted

        // insert the product into its corresponding list (electronics, clothing, groceries) in the array for their season
        if (department == ELECTRONICS_DEPT_NAME) // if the department name is electronics
        {
            inventory[season][ELECTRONICS_DEPT_INDEX].push_back(product); // add the product to the end of the list, according to its season and associated index
        }
        else if (department == CLOTHING_DEPT_NAME) // if the department name is clothing
        {
            inventory[season][CLOTHING_DEPT_INDEX].push_back(product); // add the product to the end of the list, according to its season and associated index
        }
        else if (department == GROCERIES_DEPT_NAME) // if the department name is groceries
        {
            inventory[season][GROCERIES_DEPT_INDEX].push_back(product); // add the product to the end of the list, according to its season and associated index
        }
    }

    inputFile.close(); // close the input file after reading

    // after initializing the inventory, we need to display the initial state of the inventory (environment) - meets requirement
    // we will call our output function to accomplish this
    cout << "*** Starting/Initial inventory ***" << endl;
    displayInventory(inventory); // displayInventory() function call, to display the current inventory

    // create a for loop to perform the inventory simulation over 25 time periods (which represent days) - meets requirement
    for (int days = 1; days <= 25; days++)
    {
        cout << endl << "*** Day #" << days << " ***" << endl;

        // within the for loop, we need to randomly select a # of inventory-related events to occur
        int randomEventNum = rand() % 3 + 1; // choosing a random # of events between 1-3

        // based on this # of random events (create another for loop), we need to randomly select a season, department, product, and type of inventory-related event to occur
        for (int i = 0; i < randomEventNum; i++)
        {
            // random season
            string randomSeason = seasons[rand() % 4]; // choose from the seasons array we created
            // random department - choose a random department index and associate it with a name
            int randomDepartmentIndex = rand() % 3; // 0-2 index
            string randomDepartment = departments[randomDepartmentIndex]; // access department name
            // random event
            string randomEvent = events[rand() % 3]; // choose from the events array we created
            
            // choose a random product from the department that was randomly chosen
            list<string> chosenDepartment = inventory[randomSeason][randomDepartmentIndex]; // access the associated std::list

            auto it = chosenDepartment.begin(); // creation of an iterator to traverse the std::list
            advance(it, rand() % chosenDepartment.size()); // advance the iterator to a random position (product) within the list. .size() used to ensure iterator does not go out of bounds
            string randomProduct = *it; // de-reference the iterator (*) to access the product name at the iterator

            // call our function that performs the inventory simulation within this second for loop
            inventorySimulation(inventory, randomSeason, randomEvent, randomProduct, randomDepartmentIndex);
        }

        // within the 1st for loop, call our output function that will display the current inventory for the current time period after the simulation occurs - meets requirement
        // output the current inventory after calling the inventorySimulation() function
        displayInventory(inventory);
    }

    return 0;
}

// void displayInventory(const map<string, array<list<string>, 3>> inventory) function header
// DESCRIPTION: this function outputs/displays the contents of the foundational data structure created in main(). This data structure holds all data that corresponds to the current inventory state. This data will be neatly displayed.
// ARGUMENTS: const map<string, array<list<string>, 3>> inventory, an std::map in which the key is a string variable that represents a certain season
// - and the value is an std::array of 3 std::lists, that each hold string values - represents different departments
// - using const to signify that the data structure should not be modified
// RETURNS: nothing, void function
void displayInventory(const map<string, array<list<string>, 3>> inventory)
{
    cout << endl;
    cout << "Current inventory:" << endl;
    
    // create a range-based for loop to access each season (key)
    for (auto season : inventory)
    {
        cout << "Season: " << season.first << endl; // access the season (key) using .first

        // create a for loop within this range-based for loop to output each department name (according to its index)
        for (int d = 0; d < 3; d++)
        {
            string name; // to hold the name of a department
            // associate each department name with an index
            if (d == ELECTRONICS_DEPT_INDEX) 
            {
                name = ELECTRONICS_DEPT_NAME;
            }
            else if (d == CLOTHING_DEPT_INDEX)
            {
                name = CLOTHING_DEPT_NAME;
            }
            else
            {
                name = GROCERIES_DEPT_NAME;
            }

            cout <<  "    Department - " << name << ": "; // output the name of the department

        // output the products in each department
        // ensure there is a message that prints if a department has no products (out of stock)
            if (season.second[d].empty()) // .second accesses the value of the map, if a certain department is empty
                cout << "* department out of stock *"; // out of stock is displayed
            else
                for (string product : season.second[d]) // display the products in the department
                {
                    cout << product << " ";
                }

                cout << endl;
        }
    }
}

// make sure to include function header comments here
// DESCRIPTION: create a function that performs the actual inventory simulation - meets requirement
// ARGUMENTS:
    // this function will include various parameters:
    // 1. our foundational data structure
    // 2. the season
    // 3. the department
    // 4. the type of inventory-related event
    // 5. the name of the product
// RETURNS: nothing, void function
// points to consider when coding this function:
    // purchases or thefts should not be allowed when a department has no stock (helper function)
    // if a product is stolen or purchased, only 1 product should be removed from the inventory if there is multiple stock of the same product (helper function)
    // products should/can be delivered to departments that have no stock
    // if a duplicate product is being delivered (to "top off" the inventory), the product's name should show more than once
    // products delivered to a department should be related/belong to their specific department
void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string season, string event, string product, int department)
{
    // write code (similar to/same as the code in the output function) that associates a department with an index #
    string name; // to hold the name of a department
    // associate each department name with an index
    if (department == ELECTRONICS_DEPT_INDEX) 
    {
        name = ELECTRONICS_DEPT_NAME;
    }
    else if (department == CLOTHING_DEPT_INDEX)
    {
        name = CLOTHING_DEPT_NAME;
    }
    else
    {
        name = GROCERIES_DEPT_NAME;
    }

    // output the event data - display that an event is happening, along with its associated season, type of event, department, and product name
    cout << endl;
    cout << "Event! " << season << " " << event << ", " << "Department: " << name << ", " << "Product: " << product << endl;

    // now that an event has occurred, we have to update the inventory accordingly
    // write code to update the inventory. Inventory will be updated based on any of the 3 event types
    // our helper function will be utilized here to ensure that a purchase or theft cannot happen if a department has no products (is out of stock)
        if (event == DELIVERY_EVENT) // if a delivery event occurs
        {
            inventory[season][department].push_back(product); // add the product delivered to the end of the list (for that specific season + department)
            cout <<  "    Updating inventory to reflect delivery..." << endl;
        }
        else if (event == PURCHASE_EVENT || event == THEFT_EVENT) // if a purchase or theft event occurs (which requires removal of a product from inventory)
        {
            // call our helper function here, checkUpdateInventoryStock()
            // this will check if a department (during a certain season) has a product in stock before it removes it
            // if department has stock, product will be removed once
            // if department has no stock, user will be notified that theft or purchase could not occur
            if (checkUpdateInventoryStock(inventory[season][department], product))
            {
                // if department has stock
                // displays message based on event type
                cout <<  "    Updating inventory to reflect ";
                if (event == PURCHASE_EVENT)
                    cout << "purchase..." << endl;
                else
                    cout << "theft..." << endl;
            }
            else
            {
                // if department has no stock
                // displays message based on event type
                cout <<  "    No stock to ";
                if (event == PURCHASE_EVENT)
                    cout << "purchase." << endl;
                else
                    cout << "steal." << endl;
            }
        }
}

// make sure to include function header comments here
// DESCRIPTION: create a helper function that works with the inventory simulation function - meets requirement
// ARGUMENTS:
    // the parameters for the function should include:
    // 1. the std::list that holds the products of a certain department
    // 2. the product name (in order to be removed from inventory)
// RETURNS: true or false, since it is a bool function
// creating this as a function to ensure that the inventory simulation function isn't too complex
// this function will help ensure that a theft or purchase only occurs within a department that has product, and is not out of stock
// if the department + product is in stock, a theft or purchase can happen at any time, and if it happens, the product will be removed from the department's inventory once
bool checkUpdateInventoryStock(list<string>& department, string product)
{
    // create a for loop that uses an iterator to start at the beginning of the std::list and continue until the end
    for (auto it = department.begin(); it != department.end(); it++) 
    {
        if (*it == product) // using * with the iterator to de-reference it, to access product name
        {
            department.erase(it); // erase the product at the position of the iterator if the product exists
            return true;  // true means a product was removed from the department
        }
    }
    return false;  // false means no product could be removed from the department since it had no stock and product was not found
}