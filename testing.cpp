// COMSC-210 | Lab 30 | Mira Anand
// Module 11, Lesson: Software Development Life Cycle, Assignment: Alpha Release
// IDE used: Visual Studio Code for Mac

// Creating a separate .cpp file named "testing.cpp" to track 10 minute commits when writing my short driver program for unit testing
// When I finish, this program will still be pasted below my testing description write-up in my "testing.txt" file
// To see the driver program code from start to finish, please see these GitHub commits in the "alpha" branch: "Commit - Starting driver program" to "Commit - End of driver program. Final edits were made"
// I will be starting with my pseudocode + mockup/wireframe code and I will revise it to create the driver program

// Add a comment ("meets requirement") next to lines of code that meet the requirements listed in the "Requirements Analysis"
// As the project develops, more detailed comments will be added to the program + pseudocode comments may be removed/modified as needed
// Not all pseudocode comments will have code to go with it yet. I want to establish a basic structure first

// Creation of a retail store inventory simulation (in life) - meets requirement

// include the necessary headers here
#include <array> // to use std::array
#include <cstdlib> // for randomization - not using this yet 
#include <ctime> // for randomization - not using this yet
#include <fstream> // for file operations
#include <iostream>
#include <list> // to use std::list
#include <map> // to use std::map
#include <string>
// define namespace (using namespace std;) after including the headers
using namespace std;

// declaration and initialization of global const variables (for driver program purposes as of now)
// for department name
const int ELECTRONICS_DEPT = 0; // accessed by [0] in array of std::lists
const int CLOTHING_DEPT = 1; // accessed by [1] in array of std::lists
const int GROCERIES_DEPT = 2; // accessed by [2] in array of std::lists

// for event type
const string DELIVERY_EVENT = "delivery";
const string PURCHASE_EVENT = "purchase";
const string THEFT_EVENT = "theft";

// for season name
const string SEASON_1 = "Spring";
const string SEASON_2 = "Summer";
const string SEASON_3 = "Fall";
const string SEASON_4 = "Winter";

// function prototypes
// 3 functions:
// 1. to output the contents of the inventory - initially (after input file reading) and then after each time period occurs
void displayInventory(const map<string, array<list<string>, 3>> inventory);
// 2. to perform the actual inventory simulation (when inventory-related events occur)
void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string, string, string, int);
// 3. a helper function to assist the inventory simulation function (so the inventory simulation function isn't too complex/cluttered)
bool checkUpdateInventoryStock(list<string>&, string);

// int main() function starts here
// driver program for unit testing starts here
int main()
{
    // srand(time(0)); needed as first line in main() for randomization - so inventory simulation is more realistic
    srand(time(0));

    // declaration of variables that will be used to read/hold data from the input file
    string season;
    string department;
    string product;

    // creation of the foundational data structure - meets requirement
    // this is the data structure I will be using - map<string, array<list<string>, 3>> inventory;
    // - creation of an std::map named "inventory"
    // - the key is a string variable that represents a season: Spring, Summer, Fall, Winter
    // - the value is an std::array of 3 std::lists. These std::lists represent different store departments: electronics, clothing, groceries
    // - string values that represent product names will be held within each of these std::lists
    map<string, array<list<string>, 3>> inventory;

    // external input file reading code block - meets requirement
    // the name of the input file is "inventory.txt" and it must contain at least 100 lines of input - meets requirement
    // note: the input file should be structured exactly the way I have it in order for the program to operate successfully
    // will check for & report any errors when opening the input file. Program will not proceed unless input file is successfully opened
    // for each line in the input file, extract the key (season) and the product name
    // insert the product into its corresponding list (electronics, clothing, groceries) in the array for their season
    ifstream inputFile("inventory.txt"); // creating an ifstream object to open the input file
    if (!inputFile) // if the input file does not open
    {
        cout << "ERROR: Could not open input file. Please make sure the file exists in the correct location and try running the program again." << endl;
        cout << "Program will now exit..." << endl;
        return 1; // exit and return an error state
    }

    cout << "Input file successfully opened. Now reading data..." << endl << endl; // to test input file functionality, part of test #1 as stated in "testing.txt"

    while (getline(inputFile, season)) // as long as the season is being read from the input file
    {
        // break out of the loop if the department or product cannot be read
        if (!getline(inputFile, department)) break;
        if (!getline(inputFile, product)) break;

        if (department == "electronics") // if the department name is electronics
        {
            inventory[season][ELECTRONICS_DEPT].push_back(product); // add the product to the end of the list, according to its season and associated index
        }
        else if (department == "clothing") // if the department name is clothing
        {
            inventory[season][CLOTHING_DEPT].push_back(product); // add the product to the end of the list, according to its season and associated index
        }
        else if (department == "groceries") // if the department name is groceries
        {
            inventory[season][GROCERIES_DEPT].push_back(product); // add the product to the end of the list, according to its season and associated index
        }
    }

    inputFile.close(); // close the input file after reading

    // after manually initializing the inventory, we need to display the initial state of the inventory (environment) - meets requirement
    // we will call our output function to accomplish this
    // performing test #1, as stated in "testing.txt"
    cout << "Testing if the input file data was correctly read & if the inventory has been correctly initialized..." << endl;
    displayInventory(inventory); // displayInventory() function call, to display the current inventory

    // create a for loop to perform the inventory simulation over 25 time periods (which represent days) - meets requirement
        // within the for loop, we need to randomly select a # of inventory-related events to occur
            // based on this # of random events (create another for loop), we need to randomly select a season, department, and type of inventory-related event to occur 
            // call our function that performs the inventory simulation within this second for loop
        // within the 1st for loop, call our output function that will display the current inventory for the current time period after the simulation occurs - meets requirement

    // when performing tests for void inventorySimulation() & bool checkUpdateInventoryStock(), the function parameters (when calling the functions) will be hardcoded
    // this is just for simplicity when conducting unit testing and so we have direct control of the functions/situations we are testing
    // performing test #2 and test #6, as stated in "testing.txt"
    cout << "Simulating a delivery + ensuring a duplicate product being delivered is shown twice to indicate multiple quantities..." << endl << endl;
    inventorySimulation(inventory, SEASON_1, DELIVERY_EVENT, "phone", ELECTRONICS_DEPT);
    cout << "Simulating a purchase..." << endl << endl;
    inventorySimulation(inventory, SEASON_2, PURCHASE_EVENT, "t-shirt", CLOTHING_DEPT);
    cout << "Simulating a theft..." << endl << endl;
    inventorySimulation(inventory, SEASON_3, THEFT_EVENT, "apple", GROCERIES_DEPT);
    cout << "Here is the updated inventory after the simulated delivery, purchase, and theft..." << endl;
    displayInventory(inventory);

    // performing test #3, as stated in "testing.txt"
    cout << "Trying to purchase & steal from a department that has no stock..." << endl << endl;
    inventorySimulation(inventory, SEASON_2, PURCHASE_EVENT, "t-shirt", CLOTHING_DEPT);
    inventorySimulation(inventory, SEASON_3, THEFT_EVENT, "apple", GROCERIES_DEPT);
    cout << "Here is the updated inventory after attempting to purchase & steal from a department that has no stock..." << endl;
    displayInventory(inventory);

    // performing test #4, as stated in "testing.txt"
    cout << "Purchasing from a department that has multiple quantities in stock to ensure that only 1 product is removed..." << endl << endl;
    inventorySimulation(inventory, SEASON_1, PURCHASE_EVENT, "phone", ELECTRONICS_DEPT);
    cout << "Here is the updated inventory after purchasing from a department that has multiple quantities in stock..." << endl;
    displayInventory(inventory);

    // performing test #5, as stated in "testing.txt"
    cout << "Delivering to departments that are out of stock to ensure that they can be replenished if needed..." << endl << endl;
    inventorySimulation(inventory, SEASON_2, DELIVERY_EVENT, "t-shirt", CLOTHING_DEPT);
    inventorySimulation(inventory, SEASON_3, DELIVERY_EVENT, "apple", GROCERIES_DEPT);
    cout << "Here is the updated inventory after the delivery to out of stock departments..." << endl;
    displayInventory(inventory);

    // testing 3rd function, bool checkUpdateInventoryStock, on its own
    // performing test #3 and test #4, as stated in "testing.txt"
    list<string> groceriesTest = { "apple", "apple", "banana", "orange" }; // creating a sample std::list to work with for purposes of unit testing
    bool test = checkUpdateInventoryStock(groceriesTest, "apple"); // create a bool, since it is a bool function
    if (test) // if product was found in list
        cout << "apple was purchased." << endl;
    else // if product was not found in list
        cout << "apple not in stock." << endl;
    
    cout << "Here is the updated department (std::list) after purchasing an apple. Only one should be purchased/removed..." << endl << endl;
    for (string product : groceriesTest) // range-based for loop to traverse through the list
        cout << product << " ";
    
    cout << endl;

    return 0; // make sure to add return 0; at the end of main()

} // int main() function ends here
// driver program for unit testing ends here

// make sure to include function header comments here
// void displayInventory(const map<string, array<list<string>, 3>> inventory) function header
// DESCRIPTION: create a function that displays/outputs the contents of our foundational data structure (current inventory) - meets requirement
// ARGUMENTS: the parameter for the function should be our foundational data structure - const map<string, array<list<string>, 3>> inventory
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
            if (d == 0) 
            {
                name = "electronics";
            }
            else if (d == 1)
            {
                name = "clothing";
            }
            else
            {
                name = "groceries";
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
    if (department == 0) 
    {
        name = "electronics";
    }
    else if (department == 1)
    {
        name = "clothing";
    }
    else
    {
        name = "groceries";
    }

    // output the event data - display that an event is happening, along with its associated season, type of event, department, and product name
    cout << endl;
    cout << "Event! " << season << " " << event << ", " << "Department: " << name << ", " << "Product: " << product << endl;

    // now that an event has occurred, we have to update the inventory accordingly
    // write code to update the inventory. Inventory will be updated based on any of the 3 event types
    // our helper function will be utilized here to ensure that a purchase or theft cannot happen if a department has no products (is out of stock)
        if (event == "delivery") // if a delivery event occurs
        {
            inventory[season][department].push_back(product); // add the product delivered to the end of the list (for that specific season + department)
            cout <<  "    Updating inventory to reflect delivery..." << endl;
        }
        else if (event == "purchase" || event == "theft") // if a purchase or theft event occurs (which requires removal of a product from inventory)
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
                if (event == "purchase")
                    cout << "purchase..." << endl;
                else
                    cout << "theft..." << endl;
            }
            else
            {
                // if department has no stock
                // displays message based on event type
                cout <<  "    No stock to ";
                if (event == "purchase")
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