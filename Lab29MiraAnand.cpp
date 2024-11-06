// include my program header here
// COMSC-210 | Lab 29 | Mira Anand
// Module 11, Lesson: Software Development Life Cycle, Assignment: Project Proposal, Pseudocode, & Mockup
// IDE used: Visual Studio Code for Mac

// add a comment "meets requirement" next to lines of code that meet the requirements listed in the "Requirements Analysis"

// Creation of a retail store inventory simulation (in life) - meets requirement

// include the necessary headers here
// define namespace (using namespace std;) after including the headers

// include any global const variables here
    // so far, for mockup/wireframe purposes, I am planning on creating a global const dummy variable to use for the name of each product

// define function prototypes here
    // planning on having 3 functions
    // 1. to output the contents of the inventory initially and then after each time period occurs
    // 2. to perform the actual inventory simulation
    // 3. a helper function to assist the inventory simulation function (so the inventory simulation function isn't too complex/cluttered)

// int main() function starts here

    // srand(time(0)); needed as first line in main() for randomization - so inventory simulation is more realistic

    // creation of the foundational data structure - meets requirement
    // I need to include detailed comments that explain this data structure piece by piece

    // external input file reading should happen here - meets requirement
    // I can either create a function for this process or I can handle it in main()
    // the input file name should be "inventory.txt" and must contain at least 100 lines of input - meets requirement
    // should check for & report any errors when opening the input file. Program should not proceed unless input file is successfully opened
    // a comment should be included in the code to ensure the user understands that the input file should be structured exactly the way I have it in order for the program to operate successfully
    // for each line of the input file, extract the key (season) and the product name
    // insert the product into its corresponding list (Clothing, Electronics, Groceries) in the array for their season

    // for mockup/wireframe purposes, I am initializing the inventory manually
    // later on, I will add code as explained in the block above to read inventory data from the input file instead
    // when I add code to read from the input file, this code to manually initialize the inventory will be removed
    // to manually initialize - for each of the 4 seasons, each of the 3 departments will start off with 2 products
    // for product name - I will be using my global const dummy variable to set the name of all products

    // after manually initializing the inventory, we need to display the initial state of the inventory (environment) - meets requirement
    // we will call our output function to accomplish this

    // create a for loop to perform the inventory simulation over 25 time periods (which represent days) - meets requirement
        // within the for loop, we need to randomly select a # of inventory-related events to occur
            // based on this # of random events (create another for loop), we need to randomly select a season, department, and type of inventory-related event to occur 
            // call our function that performs the inventory simulation within this second for loop
        // within the 1st for loop, call our output function that will display the current inventory for the time period after the simulation occurs - meets requirement

    // make sure to add return 0; at the end of main()

// int main() function ends here

// make sure to include function header comments here
// DESCRIPTION:
// ARGUMENTS: the parameter for the function should be our foundational data structure
// RETURNS:
// create a function that displays/outputs the current inventory - meets requirement
    // create a range-based for loop to access each season (key)
        // create a for loop within this range-based for loop to access each department (according to their index)
        // output the products in each department
        // ensure there is a message that prints if a department has no products (out of stock)

// make sure to include function header comments here
// DESCRIPTION:
// ARGUMENTS:
    // this function will include various parameters:
    // 1. our foundational data structure
    // 2. the season
    // 3. the department
    // 4. the type of inventory-related event
    // 5. the name of the product
// RETURNS: 
// create a function that performs the actual inventory simulation - meets requirement
    // write code (similar to/same as the code in the output function) that associates a department with an index (#)
    // output the event data - display that an event is happening, and its associated season, type of event, department, and product name
    // now that we have outputted that an event has occurred, we have to update the inventory accordingly
    // write code to update the inventory. Inventory will be updated based on any of the 3 event types
    // this function our helper function will be utilized here to ensure that a purchase or theft cannot happen if a department has no products (is out of stock)
// points to consider when coding this function:
    // purchases or thefts should not be allowed when a department has no stock (helper function)
    // if a product is stolen or purchased, only 1 product should be removed from the inventory if there is multiple stock of the same product (helper function)
    // products should/can be delivered to departments that have no stock
    // if a duplicate product is being delivered (to "top off" the inventory), the product's name should show more than once
    // products delivered to a department should be related/belong to their specific department

// make sure to include function header comments here
// DESCRIPTION:
// ARGUMENTS:
    // the parameters for the function should include:
    // 1. the list that holds the string values that represent the names of the departments
    // 2. the product name (in order to be removed from inventory)
// RETURNS:
// create a helper function that works with the inventory simulation function - meets requirement
// creating this as a function to ensure that the inventory simulation function isn't too complex
// this function will help ensure that a theft or purchase only occurs within a department that has products, and is not out of stock
// if the department + product is in stock, a theft or purchase can happen at any time, and if it happens, the product will be removed from the department's inventory