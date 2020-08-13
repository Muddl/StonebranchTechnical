#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cerrno>
#include <list>
#include <map>
#include <utility>
#include <stdexcept>

using namespace std;

std::vector<std::pair<std::string, std::vector<string>>> read_csv(std::string filename) {
    // Reads a CSV file into a vector of <string, vector<string>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, string vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<string>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    string val;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {

            // Initialize and add <colname, string vector> pairs to result
            result.push_back({ colname, std::vector<string> {} });
        }
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each word
        while (std::getline(ss, val, ',')) {

            // Add the current word to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);

            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<string>>> dataset) {
    // Make a CSV file with one or more columns of string values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<string>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream myFile(filename);

    // Send column names to the stream
    for (int j = 0; j < dataset.size(); j++)
    {
        myFile << noskipws << dataset.at(j).first;
        if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
}

std::vector<std::pair<std::string, std::vector<string>>> match_customer(
    std::vector<std::pair<std::string, std::vector<string>>> sampleData,
    std::vector<std::pair<std::string, std::vector<string>>> customerInData
) {
    std::vector<std::pair<std::string, std::vector<string>>> customerOutData;
    vector<string> ::iterator it;

    // Add column headers to customerOutData 
    for (int i = 0; i < customerInData.size(); i++) {
        customerOutData.push_back({ customerInData.at(i).first, vector<string> {10} });
    }

    // Iterate through sampleData CUSTOMER_CODEs
    for (int i = 0; i < sampleData.at(0).second.size(); ++i) {
        // Search customerInData for matching CUSTOMER_CODE in sampleData, saving iterator of found string
        it = find(customerInData.at(0).second.begin(), customerInData.at(0).second.end(), sampleData.at(0).second.at(i));

        // If there is a match
        if (it != customerInData.at(0).second.end()) {
            // Translate iterator into found index
            int index = distance(customerInData.at(0).second.begin(), it);

            for (int i = 0; i < customerInData.size(); i++) {
                customerOutData.at(i).second[index] = customerInData.at(i).second[index];
            }
        }
    }

    return customerOutData;
}

std::vector<std::pair<std::string, std::vector<string>>> match_invoice(
    std::vector<std::pair<std::string, std::vector<string>>> sampleData,
    std::vector<std::pair<std::string, std::vector<string>>> invoiceInData
) {
    std::vector<std::pair<std::string, std::vector<string>>> invoiceOutData;
    vector<string> ::iterator it;

    // Add column headers to invoiceOutData 
    for (int i = 0; i < invoiceInData.size(); i++) {
        invoiceOutData.push_back({ invoiceInData.at(i).first, vector<string> {10} });
    }

    // Iterate through sampleData CUSTOMER_CODEs
    for (int i = 0; i < sampleData.at(0).second.size(); ++i) {
        // Search invoiceInData for matching CUSTOMER_CODE in sampleData, saving iterator of found string
        it = find(invoiceInData.at(0).second.begin(), invoiceInData.at(0).second.end(), sampleData.at(0).second.at(i));

        // If there is a match
        if (it != invoiceInData.at(0).second.end()) {
            // Translate iterator into found index
            int index = distance(invoiceInData.at(0).second.begin(), it);

            for (int i = 0; i < invoiceInData.size(); i++) {
                invoiceOutData.at(i).second[index] = invoiceInData.at(i).second[index];
            }
        }
    }

    return invoiceOutData;
}

std::vector<std::pair<std::string, std::vector<string>>> match_invoice_item(
    std::vector<std::pair<std::string, std::vector<string>>> invoiceInData
) {
    std::vector<std::pair<std::string, std::vector<string>>> invoice_itemOutData;
    vector<string> ::iterator it;

    // Add column headers to invoice_itemOutData 
    for (int i = 0; i < invoiceInData.size(); i++) {
        invoice_itemOutData.push_back({ invoiceInData.at(i).first, vector<string> {10} });
    }

    // Iterate through sampleData CUSTOMER_CODEs
    for (int i = 0; i < invoiceInData.at(0).second.size(); ++i) {
        // Search invoiceInData for matching CUSTOMER_CODE in sampleData, saving iterator of found string
        it = find(invoiceInData.at(0).second.begin(), invoiceInData.at(0).second.end(), invoiceInData.at(0).second.at(i));

        // If there is a match
        if (it != invoiceInData.at(0).second.end()) {
            // Translate iterator into found index
            int index = distance(invoiceInData.at(0).second.begin(), it);

            for (int i = 0; i < invoiceInData.size(); i++) {
                invoice_itemOutData.at(i).second[index] = invoiceInData.at(i).second[index];
            }
        }
    }

    return invoice_itemOutData;
}

int main()
{
    // Read in all 4 datasheets
    std::vector<std::pair<std::string, std::vector<string>>> customerIn = read_csv("CUSTOMER.csv");
    std::vector<std::pair<std::string, std::vector<string>>> invoiceIn = read_csv("INVOICE.csv");
    std::vector<std::pair<std::string, std::vector<string>>> invoice_itemIn = read_csv("INVOICE_ITEM.csv");
    std::vector<std::pair<std::string, std::vector<string>>> sample = read_csv("SAMPLE.csv");

    // Initialize & fill output files
    std::vector<std::pair<std::string, std::vector<string>>> customerOut = match_customer(sample, customerIn);
    std::vector<std::pair<std::string, std::vector<string>>> invoiceOut = match_invoice(sample, invoiceIn);
    std::vector<std::pair<std::string, std::vector<string>>> invoice_itemOut = match_invoice_item(invoiceOut);

    // Write to output files
    write_csv("CUSTOMER-OUTPUT.csv", customerOut);
    write_csv("INVOICE-OUTPUT.csv", invoiceOut);
    write_csv("INVOICE_ITEM-OUTPUT.csv", invoice_itemOut);

	return 0;
}