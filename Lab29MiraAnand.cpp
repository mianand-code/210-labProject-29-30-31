// include my program header here
// COMSC-210 | Lab 29 | Mira Anand
// Module 11, Lesson: Software Development Life Cycle, Assignment: Project Proposal, Pseudocode, & Mockup
// IDE used: Visual Studio Code for Mac

// Add a comment "meets requirement" next to lines of code that meet the requirements listed in the "Requirements Analysis"
// As the project develops, more detailed comments will be added to the program + pseudocode comments may be removed/modified
// To see the original pseudocode from start to finish, please see these GitHub commits in the "main" branch: "Initial commit - Starting pseudocode" to "Commit - end of pseudocode. Final edits were made"
// To see the original mockup/wireframe code from start to finish, please see these GitHub commits in the "main" branch: "Commit - Starting mockup/wireframe code" to "Commit - end of mockup/wireframe code. Final edits were made"
// For mockup/wireframe code, not all pseudocode comments will have code to go with it yet. I want to establish a basic structure first
// Creation of a retail store inventory simulation (in life) - meets requirement

// include the necessary headers here
#include <array> // to use std::array
#include <cstdlib> // for randomization
#include <ctime> // for randomization
#include <iostream>
#include <list> // to use std::list
#include <map> // to use std::map
#include <string>
// define namespace (using namespace std;) after including the headers
using namespace std;

// include any global const variables here
    // so far, for mockup/wireframe purposes, I am planning on creating a global const dummy variable to use to represent the name of each product
    // I will actually create 1 for each season's department, for clarity in each season/department
const string dummyVariable1E = "spring_electronics";
const string dummyVariable2E = "summer_electronics";
const string dummyVariable3E = "fall_electronics";
const string dummyVariable4E = "winter_electronics";

const string dummyVariable1C = "spring_clothing";
const string dummyVariable2C = "summer_clothing";
const string dummyVariable3C = "fall_clothing";
const string dummyVariable4C = "winter_clothing";

const string dummyVariable1G = "spring_groceries";
const string dummyVariable2G = "summer_groceries";
const string dummyVariable3G = "fall_groceries";
const string dummyVariable4G = "winter_groceries";
    // adding 4 more global const variables for mockup/wireframe purposes, to represent each of the 4 seasons when manually initializing the inventory for now
const string season1 = "Spring";
const string season2 = "Summer";
const string season3 = "Fall";
const string season4 = "Winter";

// define function prototypes here
    // planning on having 3 functions
    // 1. to output the contents of the inventory - initially (after input file reading) and then after each time period occurs
void displayInventory(const map<string, array<list<string>, 3>>& inventory);
    // 2. to perform the actual inventory simulation (when inventory-related events occur)
void inventorySimulation(map<string, array<list<string>, 3>>& inventory, string, string, string, int);
    // 3. a helper function to assist the inventory simulation function (so the inventory simulation function isn't too complex/cluttered)
bool checkUpdateInventoryStock(list<string>&, string);

// int main() function starts here
int main()
{
    // srand(time(0)); needed as first line in main() for randomization - so inventory simulation is more realistic
    srand(time(0));

    // creation of the foundational data structure - meets requirement
    // this is the data structure I will be using - map<string, array<list<string>, 3>> inventory;
    // I need to include detailed comments that explain this data structure piece by piece
    // - creation of an std::map named "inventory"
    // - the key is a string variable that represents a season: Spring, Summer, Fall, Winter
    // - the value is an std::array of 3 std::lists. These std::lists represent different store departments: electronics, clothing, groceries
    // - string values of product names will be held within each of these std::lists
    map<string, array<list<string>, 3>> inventory;

    // external input file reading should happen here - meets requirement
    // I can either create a function for this process or I can handle it in main()
    // the name of the input file should be "inventory.txt" and it must contain at least 100 lines of input - meets requirement
    // should check for & report any errors when opening the input file. Program should not proceed unless input file is successfully opened
    // a comment should be included in this code block to ensure that the user understands that the input file should be structured exactly the way I have it in order for the program to operate successfully
    // for each line in the input file, extract the key (season) and the product name
    // insert the product into its corresponding list (Clothing, Electronics, Groceries) in the array for their season

    // for mockup/wireframe purposes, I will be initializing the inventory manually
    // later on, I will add code as explained in the block above to read inventory data from the input file instead
    // when I add code that will read from the input file, this code block will be removed
    // to manually initialize - for each of the 4 seasons, each of the 3 departments will start off with 2 products
    // for product name - I will be using my global const dummy variables to set the universal name for products
    // [0] = electronics, [1] = clothing, [2] = groceries
    inventory[season1][0] = {dummyVariable1E, dummyVariable1E}; // Spring, electronics
    inventory[season1][1] = {dummyVariable1C, dummyVariable1C}; // Spring, clothing
    inventory[season1][2] = {dummyVariable1G, dummyVariable1G}; // Spring, groceries

    inventory[season2][0] = {dummyVariable2E, dummyVariable2E}; // Summer, electronics
    inventory[season2][1] = {dummyVariable2C, dummyVariable2C}; // Summer, clothing
    inventory[season2][2] = {dummyVariable2G, dummyVariable2G}; // Summer, groceries

    inventory[season3][0] = {dummyVariable3E, dummyVariable3E}; // Fall, electronics
    inventory[season3][1] = {dummyVariable3C, dummyVariable3C}; // Fall, clothing
    inventory[season3][2] = {dummyVariable3G, dummyVariable3G}; // Fall, groceries

    inventory[season4][0] = {dummyVariable4E, dummyVariable4E}; // Winter, electronics
    inventory[season4][1] = {dummyVariable4C, dummyVariable4C}; // Winter, clothing
    inventory[season4][2] = {dummyVariable4G, dummyVariable4G}; // Winter, groceries

    // after manually initializing the inventory, we need to display the initial state of the inventory (environment) - meets requirement
    // we will call our output function to accomplish this
    cout << "Starting/"

    // create a for loop to perform the inventory simulation over 25 time periods (which represent days) - meets requirement
        // within the for loop, we need to randomly select a # of inventory-related events to occur
            // based on this # of random events (create another for loop), we need to randomly select a season, department, and type of inventory-related event to occur 
            // call our function that performs the inventory simulation within this second for loop
        // within the 1st for loop, call our output function that will display the current inventory for the current time period after the simulation occurs - meets requirement

    // make sure to add return 0; at the end of main()
    return 0;

} // int main() function ends here

// make sure to include function header comments here
// create a function that displays/outputs the contents of our foundational data structure (current inventory) - meets requirement
// DESCRIPTION:
// ARGUMENTS: the parameter for the function should be our foundational data structure
// RETURNS:
    // create a range-based for loop to access each season (key)
        // create a for loop within this range-based for loop to access each department (according to its index)
        // output the products in each department
        // ensure there is a message that prints if a department has no products (out of stock)

// make sure to include function header comments here
// create a function that performs the actual inventory simulation - meets requirement
// DESCRIPTION:
// ARGUMENTS:
    // this function will include various parameters:
    // 1. our foundational data structure
    // 2. the season
    // 3. the department
    // 4. the type of inventory-related event
    // 5. the name of the product
// RETURNS: 
    // write code (similar to/same as the code in the output function) that associates a department with an index (#)
    // output the event data - display that an event is happening, along with its associated season, type of event, department, and product name
    // now that an event has occurred, we have to update the inventory accordingly
    // write code to update the inventory. Inventory will be updated based on any of the 3 event types
    // our helper function will be utilized here to ensure that a purchase or theft cannot happen if a department has no products (is out of stock)
// points to consider when coding this function:
    // purchases or thefts should not be allowed when a department has no stock (helper function)
    // if a product is stolen or purchased, only 1 product should be removed from the inventory if there is multiple stock of the same product (helper function)
    // products should/can be delivered to departments that have no stock
    // if a duplicate product is being delivered (to "top off" the inventory), the product's name should show more than once
    // products delivered to a department should be related/belong to their specific department

// make sure to include function header comments here
// create a helper function that works with the inventory simulation function - meets requirement
// DESCRIPTION:
// ARGUMENTS:
    // the parameters for the function should include:
    // 1. the std::list that holds the values that represent the names of each department
    // 2. the product name (in order to be removed from inventory)
// RETURNS:
// creating this as a function to ensure that the inventory simulation function isn't too complex
// this function will help ensure that a theft or purchase only occurs within a department that has products, and is not out of stock
// if the department + product is in stock, a theft or purchase can happen at any time, and if it happens, the product will be removed from the department's inventory once