/**
 * Author: Avery Chisnall
 * This file contains the 'main' function. Program execution begins and ends there.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    // Declaring variables
    string line, filename;
    double variance, overAllVariance;
    int rowCount = 0;
    double budgetsum = 0;
    vector<vector<string>> storage;
    while (true)
    {
        // Getting the user to input the name of their .csv file
        cout << "Please enter the name of the file.\n";
        cin >> filename;
        // Checking that the file is in the correct format
        if (!(filename.length() >= 3 && filename.substr(filename.length() - 3) == "csv"))
        {
            cout << "File not found. Make sure you input the correct filename with the.csv extension.\n ";
        }
        else
        {
            break;
        }
    }
    // Opening the original file and the new file
    ifstream myfile(filename);
    ofstream newfile("newFile.csv");
    // Checking that the file has been successfully opened
    if (!myfile.good())
    {
        cout << "File does not exist. Check that the file is correctly named.\n";
        return 1;
    }
    else
    {
        cout << "File opening successful!\n";
    }
    // Reading the first line of the csv file (containing the headers for each column, simplifies the program later)
    getline(myfile, line);
    // Readds the headers to the new file
    newfile << line << ",Variance,Overall variance,\n";
    // Reading the data from the csv file. First reads whole lines/rows at a time.
    while (getline(myfile, line))
    {
        // Declaring variables to store the results of splitting the line/row into its component parts
        vector<string> split;
        stringstream ssin(line);
        string splitValue;
        // Splits the current row of the csv file into each individual item
        while (getline(ssin, splitValue, ','))
        {
            // Pushes the current item into its own vector, one vector for each row
            split.push_back(splitValue);
        }
        // Once each row has been defined by a vector, pushes that vector into another vector
        storage.push_back(split);
        // Counting how many rows have been analysed, for use later
        rowCount++;
    }
    // Error handling for calculating the new data
    try
    {
        // Calculating the variance of each department
        for (int i = 0; i < storage.size(); i++)
        {
            // Accesses the data stored in each vector and uses it in a calculation, then pushes it back into the vector that it came from
            variance = (1 - ((stod(storage[i][1]) - stod(storage[i][2])) /
                             stod(storage[i][1]))) *
                       100;
            storage[i].push_back(to_string(variance).append("%"));
            // Adding the sum of each department to a "budgetsum" value, used  to calculate the total budget of the whole company
            budgetsum = budgetsum + stod(storage[i][1]);
        }
        // Calculating the overall variance
        for (int i = 0; i < storage.size(); i++)
        {
            // Using the same method as the departmental variance, using the total budget instead of the department's budget
            overAllVariance = (1 - (budgetsum - stod(storage[i][2])) /
                                       budgetsum) *
                              100;
            storage[i].push_back(to_string(overAllVariance).append("%"));
        }
    }
    catch (invalid_argument)
    {
        cout << "Data not in correct format. Make sure the spreadsheet has only numbers in the budget / expenditure columns.";
                    return 1;
    }
    // Iterating through the 2D vector, one item at a time and readding them to a
    new.csv file for (int i = 0; i < storage.size(); i++)
    {
        for (int j = 0; j <= rowCount; j++)
        {
            newfile << storage[i][j] << ',';
            if (j == rowCount)
            {
                // Entering a new row once the final column of the current
                row has been added to the new file
                        newfile
                    << '\n';
            }
        }
    }
    // Closing the files
    myfile.close();
    newfile.close();
    return 0;
}
