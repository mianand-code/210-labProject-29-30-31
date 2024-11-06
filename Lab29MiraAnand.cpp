// include my program header here
// COMSC-210 | Lab 29 | Mira Anand
// Module 11, Lesson: Software Development Life Cycle, Assignment: Project Proposal, Pseudocode, & Mockup
// IDE used: Visual Studio Code for Mac

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

    // creation of the foundational data structure
    // I need to include detailed comments that explain this data structure piece by piece

    // external input file reading should happen here
    // I can either create a function for this process or I can handle it in main()
    // the input file name should be "inventory.txt"
    // should check for & report any errors when opening the input file
    // a comment should be included in the code to ensure the user understands that the input file should be structured exactly the way I have it in order for the program to operate successfully
    // for each line of the input file, extract the key (season) and the product name
    // insert the product into its corresponding list (Clothing, Electronics, Groceries) in the array for their season

    // for mockup/wireframe purposes, I am initializing the inventory manually
    // later on, I will add code as explained in the block above to read inventory data from the input file instead
    // when I add code to read from the input file, this code to manually initialize the inventory will be removed
    // to manually initialize - for each of the 4 seasons, each of the 3 departments will start off with 2 products
    // for product name - I will be using my global const dummy variable to set the name of all products

    // after manually initializing the inventory, we need to display the initial state of the inventory (environment)
    // we will call our output function to accomplish this

    // create a for loop to perform the inventory simulation over 25 time periods (which represent days)
        // within the for loop, we need to randomly select a # of inventory-related events to occur
        // based on this # of random events (create another for loop), we need to randomly select a season, department, and type of inventory-related event to occur 
        // call our function that performs the inventory simulation within this second for loop
        // within the 1st for loop, call our output function that will display the current inventory for the time period after the simulation occurs

    // make sure to add return 0; at the end of main()

// int main() function ends here

// create a function that displays/outputs the current inventory
    // make sure to include function header comments
    // the parameter for the function should be the
    // create a range-based for loop 