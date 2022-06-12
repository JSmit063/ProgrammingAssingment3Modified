// Programming Assignment 3
// Justin Smith

#include <iostream> // This program uses I/O streams
#include <string> // Using string objects
#include <fstream> // Need to output data to external txt file
#include <iomanip> // Needed to use format manipulators
#include <algorithm> // For changing case in strings 

using namespace std;

const double FRAGILE_FEE = 2.00; // Constants

// Program resides entirely within main function
int main()
{
    // Variable declarations
    string itemName;
    string destinationName;
    double orderTotal;
    double shippingCost;
    double totalWithShipping;
    string fragile;

    // initialize file stream variable to output data to at the end of program
    ofstream fs;
    fs.open("Output.txt"); // Open file stream
    /*
    If-statement below is to verify that the file is open. When I tested this, I could not get
    the fail condition to work and the program to exit such as when changing the file name to be incorrect to see if
    this control structure works. I thought that maybe the below control structure
    may need to be commented out when the program was in "production" but I left it as is.
    I did not include a ifstream variable as this assignment only requires output to the file.
    */
    if (!fs.is_open())
    {
        cout << "Could not open file. Program is exiting" << endl;
        system("pause");
        return -1;
    }

    cout << "*******************************************************************************" << endl;
    cout << "******************** ITCS 2530 -- Programming Assignment 3 ********************" << endl;
    cout << "*******************************************************************************" << endl << endl;

    // Need to gather input from the user to find the name, fragility of the item, order total, and destination
    cout << setw(78) << left << setfill('.') << "Please enter the item name to be shipped (no spaces)" << ":";
    cin >> itemName;
    // Promt the user to ask if the item is fragile
    cout << setw(78) << left << setfill('.') << "Is the item fragile? (y=yes/n=no)" << ":";
    cin >> fragile;
    transform(fragile.begin(), fragile.end(), fragile.begin(), ::toupper); // Changes the string to lowercase to accept all cases
    if (!(fragile == "Y" || fragile == "N")) // If incorrect value entered, exit program
    {
        cout << "Invalid entry, exiting" << endl;
        return 1;
    }
    // Prompt the user for their order total
    cout << setw(78) << left << setfill('.') << "Please enter your order total" << ":";
    cin >> orderTotal;
    // Prompt the user to enter the destination of the order
    cout << setw(78) << left << setfill('.') << "Please enter destination (usa/can/aus)" << ":";
    cin >> destinationName;
    transform(destinationName.begin(), destinationName.end(), destinationName.begin(), ::toupper); // Changes the string to lowercase to accept all cases
    if (!(destinationName == "USA" || destinationName == "CAN" || destinationName == "AUS" || destinationName == "JUPITER")) // If incorrect value entered, exit program
    {
        cout << "Invalid entry, exiting" << endl;
        return 1;
    }
    cout << endl;

    /*
    We need to find the shipping cost accounting for the destination. There are 4 tiers of shipping costs and
    each tier is a different amount for each destination. The following code uses selection structures (if/else)
    to resolve the shipping cost and new total. I explored using a switch structure here instead but due to either
    the expression being logical or not numerical like in the instance of looking at the usa/can/aus strings, I thought
    that this was my best course for a selection structure.
    */
    if (orderTotal < 50.00)
        if (destinationName == "USA")
        {
            shippingCost = 6.00;
            totalWithShipping = shippingCost + orderTotal;
        }
        else if (destinationName == "CAN")
        {
            shippingCost = 8.00;
            totalWithShipping = shippingCost + orderTotal;
        }
        else if (destinationName == "JUPITER")
        {
            cout << "We cannot ship to other planets" << endl;
            system("pause");
            return 1;
        }
        else
        {
            shippingCost = 10.00;
            totalWithShipping = shippingCost + orderTotal;
        }
    // Check for shipping cost if price between 50.01 and 100.00
    else if (orderTotal >= 50.01 && orderTotal <= 100.00)
        if (destinationName == "USA")
        {
            shippingCost = 9.00;
            totalWithShipping = shippingCost + orderTotal;
        }
        else if (destinationName == "CAN")
        {
            shippingCost = 12.00;
            totalWithShipping = shippingCost + orderTotal;
        }
        else if (destinationName == "JUPITER")
        {
            cout << "We cannot ship to other planets" << endl;
            system("pause");
            return 1;
        }
        else
        {
            shippingCost = 14.00;
            totalWithShipping = shippingCost + orderTotal;
        }
    // check for shipping cost if order total between 100.01 and 150.0        
    else if (orderTotal >= 100.01 && orderTotal < 150.00)
        if (destinationName == "USA")
        {
            shippingCost = 12.00;
            totalWithShipping = shippingCost + orderTotal;
        }
        else if (destinationName == "CAN")
        {
            shippingCost = 15.00;
            totalWithShipping = shippingCost + orderTotal;
        }
        else if (destinationName == "JUPITER")
        {
            cout << "We cannot ship to other planets" << endl;
            system("pause");
            return 1;
        }
        else
        {
            shippingCost = 17.00;
            totalWithShipping = shippingCost + orderTotal;
        }
    // There is no shipping cost for larger than 150.00 orders. Order total then equals order total
    else
    {
        shippingCost = 0;
        totalWithShipping = orderTotal;
    }


    // Need to finally add the fragile fee to our new total if applicable
    if (fragile == "Y")
    {
        shippingCost += FRAGILE_FEE;
        totalWithShipping += FRAGILE_FEE;
    }


    // Output to the user
    cout << setw(78) << left << setfill('.') << "Your item is" << itemName << endl;
    cout << setw(78) << left << setfill('.') << "Your shipping cost is" << '$' << fixed << setprecision(2) << shippingCost << endl;
    cout << setw(78) << left << setfill('.') << "You are shipping to" << destinationName << endl;
    cout << setw(78) << left << setfill('.') << "Your total shipping costs are" << '$' << fixed << setprecision(2) << totalWithShipping << endl << endl;
    cout << setw(88) << right << setfill('.') << "Thank You!" << endl << endl;
    // Output data to Output.txt
    fs << itemName << '\t';
    fs << shippingCost << '\t';
    fs << destinationName << '\t';
    fs << totalWithShipping << '\t';

    // Close the file
    fs.close();

    system("pause");

    return 0;
}