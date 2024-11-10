// COMSC-210 | Lab 31 | Mira Anand
// Module 11, Lesson: Software Development Life Cycle, Assignment: Beta Release
// IDE used: Visual Studio Code for Mac

// Add a comment ("meets requirement") next to lines of code that meet the requirements listed in the "Requirements Analysis"
// All changes to the program will happen in this file "Lab29MiraAnand.cpp", but different branches will be utilized
// To see the original pseudocode from start to finish, please see these GitHub commits in the "main" branch: "Initial commit - Starting pseudocode" to "Commit - end of pseudocode. Final edits were made"
// To see the original mockup/wireframe code from start to finish, please see these GitHub commits in the "main" branch: "Commit - Starting mockup/wireframe code" to "Commit - End of mockup/wireframe code. Final edits were made"
// To see the original Alpha Release code from start to finish, please see these GitHub commits in the "alpha" branch: "Commit - Starting Alpha Release" to "Commit - end of Alpha Release. Final edits were made"
// To see the coding progression of Beta Release and "bugs.txt", please see all GitHub commits in the "beta" branch

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
// these variables will be primarily used to assist with randomization in main() + they make reading the code easier and can be easily changed/added to in the future to accomodate any coding updates
// for department index
const int ELECTRONICS_DEPT_INDEX = 0; // electronics department accessed by [0] in array of std::lists
const int CLOTHING_DEPT_INDEX = 1; // clothing department accessed by [1] in array of std::lists
const int GROCERIES_DEPT_INDEX = 2; // groceries department accessed by [2] in array of std::lists

// #  of event types, seasons, departments + their indexes
const int EVENT_TYPE_NUM = 3;
const int SEASON_NUM = 4;
const int DEPARTMENT_NAME_INDEX_NUM = 3;

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

// for the product to be delivered as replenishment when a delivery event is triggered for a department that is completely out of stock
// this product may also be delivered to "top off" an existing product's stock, even if the department is not completely out of stock
const string STOCK_REFILL_PRODUCT = "StockRefill";

// function prototypes
// creating 3 functions - meets requirement
// 1. to output the contents of the inventory - initially (after input file reading) and then after each time period occurs
void displayInventory(const map<string, array<list<string>, 3>> inventory);
// 2. to handle the actual inventory simulation (when inventory-related events occur)
void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string, string, string, int);
// 3. a helper function to assist inventorySimulation() (so it isn't too complex/cluttered)
bool checkUpdateInventoryStock(list<string>&, string);

int main()
{
    srand(time(0)); // needed as the first line in main() for randomization - so the inventory simulation is more realistic

    // creation of my foundational data structure - meets requirement
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
    // in my project/design proposal, I originally stated that I would have the season, department name, & product name on 1 line in the input file, separated by commas
    // I am deciding to change this format, just to make reading from the input file easier
    // each season, department name, and product name will now have its own line in the input file. No spaces allowed, department name and seasons are case sensitive
    // the input file I am using is named "inventoryFinal.txt" and it contains more than 100 lines of input - meets requirement
    // note: the input file should be structured exactly the way I have it in order for the program to operate successfully. Please open "inventoryFinal.txt" to see the exact structure

    ifstream inputFile("inventoryFinal.txt"); // creating an ifstream object to open the input file
    if (!inputFile) // if the input file does not open
    {
        cout << "ERROR: Could not open input file. Please make sure the file exists in the correct location and try running the program again." << endl; // report the error
        cout << "Program will now exit..." << endl; // exit the program since we do not have data to work with
        return 1; // exit and return an error state
    }

    while (getline(inputFile, season)) // as long as the season is being read/extracted from the input file... (season is the key/very first line of the input file)
    {
        // the input file reads/extracts according to the order of season, department name, and then product name
        if (!getline(inputFile, department)) break; // break out of the loop if the department name cannot be read/extracted
        if (!getline(inputFile, product)) break; // break out of the loop if the product name cannot be read/extracted

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
    cout << "*** Starting/Initial inventory ***" << endl;
    displayInventory(inventory); // displayInventory() function call, to display the initial inventory

    // create a for loop to perform the inventory simulation over 25 time periods (which represent days) - meets requirement
    for (int days = 1; days <= 25; days++)
    {
        cout << endl << "*** Day #" << days << " ***" << endl;

        // within the for loop, randomly select a # of inventory-related events to occur
        int randomEventNum = rand() % 10 + 1; // choosing a random # of events between 1-10

        // based on this # of random events, randomly select a season, department, product, and type of inventory-related event to occur
        for (int i = 0; i < randomEventNum; i++)
        {
            // random season
            string randomSeason = seasons[rand() % SEASON_NUM]; // choose from the seasons array we created
            // random department - choose a random department index and associate it with its name
            int randomDepartmentIndex = rand() % DEPARTMENT_NAME_INDEX_NUM; // choose from 0-2 index
            string randomDepartment = departments[randomDepartmentIndex]; // access department name and store it
            // random event
            string randomEvent = events[rand() % EVENT_TYPE_NUM]; // choose from the events array we created
            
            // now, choose a random product from the department that was randomly chosen
            list<string> chosenDepartment = inventory[randomSeason][randomDepartmentIndex]; // access the randomly chosen department's std::list in order to choose a product

            // check if the randomly chosen department is completely empty (out of stock)
            if (chosenDepartment.empty())
            {
                if (randomEvent == DELIVERY_EVENT) // if a delivery event is triggered when the department/list is completely empty
                {
                    inventorySimulation(inventory, randomSeason, DELIVERY_EVENT, STOCK_REFILL_PRODUCT, randomDepartmentIndex); // inventorySimulation() function call, will deliver the StockRefill product to the department
                    cout << "    Replenishment is being delivered since department has no stock..." << endl; // department is now replenished
                }
                else if (randomEvent == PURCHASE_EVENT || randomEvent == THEFT_EVENT) // if a purchase or theft event is triggered when the department/list is completely empty
                {
                    // still notify the user that the event was attempted, even though the inventory will not be changed
                    cout << endl << "Attempted " << randomEvent << " event! ";
                    cout << "Season: " << randomSeason << ", ";
                    cout << "Department: " << randomDepartment << endl;
                }
            }
            else // if the chosen department is not completely out of stock, we can continue and choose a random product
            {
                auto it = chosenDepartment.begin(); // creation of an iterator to traverse the std::list of the chosen department
                advance(it, rand() % chosenDepartment.size()); // advance the iterator to a random position (product) within the list. .size() is used to ensure that the iterator does not go out of bounds
                string randomProduct = *it; // de-reference the iterator (*) to access the product name and store it

                // inventorySimulation() function call, using parameters that were all chosen by random
                inventorySimulation(inventory, randomSeason, randomEvent, randomProduct, randomDepartmentIndex);
            }
        }

        // displayInventory() function call, will display the current inventory for the current time period after the simulation occurs - meets requirement
        displayInventory(inventory);
    }

    return 0;
}

// void displayInventory(const map<string, array<list<string>, 3>> inventory) function header
// DESCRIPTION: this function outputs/displays the contents of the foundational data structure created in main(). This data structure holds all data that corresponds to the current inventory state. This data will be neatly displayed.
// ARGUMENTS: const map<string, array<list<string>, 3>> inventory, an std::map in which the key is a string variable that represents a certain season
// - and the value is an std::array of 3 std::lists, that each hold string values - represents different departments, each with product names
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

        // create another range-based for loop to output each department name (according to its index)
        for (auto departments : season.second) // season.second accesses the value in the std::map
        {
            string name; // to hold the name of a department

            // associate each department name with its index
            if (departments == season.second[ELECTRONICS_DEPT_INDEX]) 
            {
                name = ELECTRONICS_DEPT_NAME;
            }
            else if (departments == season.second[CLOTHING_DEPT_INDEX])
            {
                name = CLOTHING_DEPT_NAME;
            }
            else
            {
                name = GROCERIES_DEPT_NAME;
            }

            cout <<  "    Department - " << name << ": "; // output the name of the department

        // output the products in each department (list)
            if (departments.empty()) // if a certain department is empty
                cout << "* department out of stock *"; // out of stock is displayed
            else
                for (auto product : departments) // display the products in the department using another range-based for loop
                {
                    cout << product << " ";
                }

                cout << endl;
        }
    }
}

// void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string season, string event, string product, int department) function header
// DESCRIPTION: this function simulates a delivery, theft, or purchase event for a given season, department, and product
// - the user is first notified that an event is triggered
// - if the event is a delivery, a product is simply added to the inventory
// - a helper function is used to assist with theft and purchase events. This helper function assists with removing the product from the inventory (once) if it is stolen or purchased.
// ARGUMENTS: 1. map<string, array<list<string>, 3>>& inventory, an std::map in which the key is a string variable that represents a certain season
// - and the value is an std::array of 3 std::lists, that each hold string values - represents different departments, each with product names
// - passing by reference to indicate that the data structure will be modified
// - 2. string season, which represents a certain season
// - 3. string event, which represents the type of inventory-related event to occur
// - 4. string product, which represents the name of a certain product
// - 5. int department, which represents the index # of a certain department
// RETURNS: nothing, void function
void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string season, string event, string product, int department)
{
    string name; // to hold the name of a department

    // associate each department name with its index
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

    // output the event data - display that an event is happening, along with its associated season, event type, department, and product name
    cout << endl;
    cout << "Event! " << season << " " << event << ", " << "Department: " << name << ", " << "Product: " << product << endl;

    // now that an event has occurred, we have to update the inventory accordingly
        if (event == DELIVERY_EVENT) // if a delivery event occurs
        {
            inventory[season][department].push_back(product); // add the product to the end of the list using .push_back (for that specific season + department)
            cout <<  "    Updating inventory to reflect delivery..." << endl;
        }
        else if (event == PURCHASE_EVENT || event == THEFT_EVENT) // if a purchase or theft event occurs (which requires removal of a product from inventory)
        {
            // call our helper function here, checkUpdateInventoryStock()
            // this will check if a department (during a certain season) has a product in stock before it removes it
            // if the department has the product in stock (helper function returns true), the product will be removed once and the inventory will be updated
            if (checkUpdateInventoryStock(inventory[season][department], product))
            {
                // displays message based on event type
                cout <<  "    Updating inventory to reflect ";
                if (event == PURCHASE_EVENT)
                    cout << "purchase..." << endl;
                else
                    cout << "theft..." << endl;
            }
        }
}

// bool checkUpdateInventoryStock(list<string>& department, string product) function header
// DESCRIPTION: this function assists with purchase and theft events
// - when a purchase or theft event is triggered for a product in a department that is not empty, this function will attempt to find the product to be stolen/purchased and will remove it from the list once
// - this is a helper function for the inventorySimulation() function
// - creating this function to ensure that inventorySimulation() isn't too complex
// ARGUMENTS: list<string>& department, which is an std::list (representing a department) that holds string values that represent product names
// - passing by reference to indicate that the std::list will be modified
// RETURNS: true or false, since it is a bool function
// - true means a product was found and erased from the department
// - false means a product was not found and could not be erased from the department
bool checkUpdateInventoryStock(list<string>& department, string product)
{
    // create an iterator to start at the beginning of the std::list and continue until the end
    // using the .find member function to search for the product within the std::list
    auto it = find(department.begin(), department.end(), product); 

    if (it != department.end()) // as long as the iterator has not gone out of bounds, this means we found the product
    {
        department.erase(it); // erase the product at the position of the iterator
        return true;  // return true, meaning a product was removed from the department
    }
    else
        return false;  // return false, meaning no product could be removed from the department since the product was not found
}