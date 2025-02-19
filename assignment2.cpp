//assignment2.cpp
//Assignment 2 - Books Database (PHYS30762)
// For the provided books database (“books_data.dat” available on Blackboard), write a C++ program to store and print book 
// information, plus some statistical information.
// • This assignment is based on material covered in the first three weeks.
// • Please note that the total expected coding time is approx 6-7 hours.
// • You should submit the final code. The submission deadline is 11.59 pm, 22nd February 2025.
// Write a program to read the data and compute the mean, standard deviation, and standard error of the book prices.
// • The code should determine the number of data entries in the file. 

// Add the following functionality to the code:
// • Be efficient in storage. Use vectors for storage.
// • Use a string stream to create a string containing the book information 
// • Each of these strings should be stored in a single vector.
// • Print out the full book list using an iterator.
// • Your code should be able to print out a list of books for a particular subject including the mean, standard deviation, 
// and standard error for that subject.
// • For this, ask the user whether to print all books or for a specific subject and provide output accordingly.
// • Also, ask the user whether books should be sorted by author name or not.
//Eve Sproats, 11018744, 29/01/2024
#include<iostream>
#include<fstream>  // Allows reading from a file
#include<sstream>  // Allows use of std::stringstream for processing strings
#include<string>
#include<vector>
#include <regex>  // Regular expressions for splitting lines 

int main()
{

  std::ifstream inputFile("books_data.dat");  // Open the books data file 

  // Create a 2D vector called "matrix" to fill with the lines of the dataset
  std::vector<std::vector<std::string>> matrix;
  std::string line; 

  int no_data_entries{0};  // To count the number of data entries

  // Go through the dataset adding each line to the matrix
  while(std::getline(inputFile, line))
  {
    std::vector<std::string> temp_row;  // Temporary vector for the current row - needs splitting into components
    
    std::regex space_delimiter(" {4}|\\t");  // Setting the delimiter to be 4 spaces or a tab character

    // Use regex to split the line by multiple spaces and extract the element before it
    std::sregex_token_iterator it(line.begin(), line.end(), space_delimiter, -1);
    std::sregex_token_iterator end;  

    while (it != end) {  // Loop through the tokens
        std::cout << (*it) << std::endl;

        temp_row.push_back(*it); // Adds the value the iterator is pointing to and moves it onto the next token
        no_data_entries+=1;
        it++;
    }
    matrix.push_back(temp_row);  // Add each row to the matrix
  }
  inputFile.close();  // Close the file
  // Printing using an iterator
  std::vector<std::vector<std::string>>::iterator matrix_begin{matrix.begin()};
  std::vector<std::vector<std::string>>::iterator matrix_end{matrix.end()};

  std::cout<<"Full book list:"<<std::endl;
  // Iterate over the rows
  //  for(auto row_iterator=matrix_begin; row_iterator!=matrix_end; ++row_iterator)  
    for (int i=0; i<matrix.size(); i++)
    {

    std::cout << "Row contents: " << std::endl;

    //for (const auto &element : *row_iterator) 
    for (int j=0; j<matrix[i].size(); j++)
    {
      std::string element = matrix[i][j]; 
      std::cout << element << " | " << std::endl;
    }
    //std::cout << std::endl;
    
    // Iterate over the elements in the rows
    //for(auto element_iterator=row_iterator->begin(); element_iterator!=row_iterator->end(); ++element_iterator) 
      //{
       // std::cout<<*element_iterator<<" | "<<std::endl; 
      //}
  }

  std::cout<<"The number of data entries is "<<no_data_entries<<".";
  return 0;
}

