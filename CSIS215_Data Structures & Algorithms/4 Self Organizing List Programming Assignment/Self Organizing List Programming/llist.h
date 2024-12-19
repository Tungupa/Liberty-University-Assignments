//Citations:
//In reseaching how to do this I used the following sources :
//1. Data Structures and Algorithm Analysis Edition 3.2 (C++ Version)Clifford A.Shaffer
//2. Youtube : Did a bunch or tutorials on self organizing list
//3. Stackoverflow : Looked up how count move-to-front and transpose works
//4. ChatGPT : Give examples and base class to build my code.
//5. Google : did a lot of searches on link-list, count move-to-front and transpose.
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "CountList.h"
#include "MoveToFrontList.h"
#include "TransposeList.h"

using namespace std;

// Function to read from test.txt and return a list of words
void readFileAndProcess(const string& filename, SelfOrderedListADT<string>& list, const string& heuristicType) {
    ifstream inputFile(filename);
    string word;

    if (!inputFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    while (inputFile >> word) {
        list.find(word);
    }

    cout << heuristicType << " Heuristic: Size of list: " << list.size() << endl;
    cout << "Number of Compares: " << list.getCompares() << endl;
    list.printlist(10);  // Print the first 10 elements
}

int main() {
    // For char input (Test 1)
    cout << "Count Heuristic:" << endl;
    CountList<char> countList;  // For count heuristic
    countList.add('A');
    countList.add('B');
    countList.add('C');
    countList.add('D');
    countList.add('E');
    countList.add('F');
    countList.add('G');
    countList.add('H');
    
    // Perform the find() operations as specified in the prompt
    countList.find('F');
    countList.find('D');
    countList.find('F');
    countList.find('G');
    countList.find('E');
    countList.find('G');
    countList.find('F');
    countList.find('A');
    countList.find('D');
    countList.find('F');
    countList.find('G');
    countList.find('E');
    countList.find('H');
    countList.find('I');  // I is not in the list initially

    cout << "Size of list: " << countList.size() << endl;
    cout << "Number of Compares: " << countList.getCompares() << endl;
    countList.printlist();  // Print entire list

    // Now for MoveToFront heuristic
    cout << "\nMove to Front Heuristic:" << endl;
    MoveToFrontList<char> mtfList;
    mtfList.add('A');
    mtfList.add('B');
    mtfList.add('C');
    mtfList.add('D');
    mtfList.add('E');
    mtfList.add('F');
    mtfList.add('G');
    mtfList.add('H');
    
    mtfList.find('F');
    mtfList.find('D');
    mtfList.find('F');
    mtfList.find('G');
    mtfList.find('E');
    mtfList.find('G');
    mtfList.find('F');
    mtfList.find('A');
    mtfList.find('D');
    mtfList.find('F');
    mtfList.find('G');
    mtfList.find('E');
    mtfList.find('H');
    mtfList.find('I');  // I is not in the list initially

    cout << "Size of list: " << mtfList.size() << endl;
    cout << "Number of Compares: " << mtfList.getCompares() << endl;
    mtfList.printlist();

    // Now for Transpose heuristic
    cout << "\nTranspose Heuristic:" << endl;
    TransposeList<char> transposeList;
    transposeList.add('A');
    transposeList.add('B');
    transposeList.add('C');
    transposeList.add('D');
    transposeList.add('E');
    transposeList.add('F');
    transposeList.add('G');
    transposeList.add('H');
    transposeList.find('F');
    transposeList.find('D');
    transposeList.find('F');
    transposeList.find('G');
    transposeList.find('E');
    transposeList.find('G');
    transposeList.find('F');
    transposeList.find('A');
    transposeList.find('D');
    transposeList.find('F');
    transposeList.find('G');
    transposeList.find('E');
    transposeList.find('H');
    transposeList.find('I');  // I is not in the list initially

    cout << "Size of list: " << transposeList.size() << endl;
    cout << "Number of Compares: " << transposeList.getCompares() << endl;
    transposeList.printlist();

    // Now read the input from "test.txt" and process it using the three heuristics
    string filename = "test.txt";

    std::cout << std::endl << std::endl;
    CountList<std::string> countListWords;
    readFileAndProcess(filename, countListWords, "Count");

    std::cout << std::endl << std::endl;
    MoveToFrontList<string> mtfListWords;
    readFileAndProcess(filename, mtfListWords, "Move to Front");

    std::cout << std::endl << std::endl;
    // Create the TransposeList object
    TransposeList<std::string> transposeListWords;
    readFileAndProcess(filename, transposeListWords, "Transpose");

    return 0;
}
