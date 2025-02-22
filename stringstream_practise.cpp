// PL3/cppstringstream.cpp
// Demonstration a string stream in the modern syntax
// Source: Prof. Niels Walet's code repository
// Last updated: Charanjit Kaur, 07/02/24
#include<iostream>
#include<string>
#include<sstream> 
#include<fstream>  // Allows reading from a file
#include<vector>
#include<regex>  // Regular expressions for splitting lines 

int main() 
{
  std::string file_index="dat";
  std::ostringstream output_stream;
  output_stream << "books_data." << file_index;
  std::string output_filename{output_stream.str()};
  std::cout<<output_filename<<std::endl;

  std::ifstream inputFile(output_filename);  // Open the books data file 

  // Create a 2D vector called "matrix" to fill with the lines of the dataset
  std::vector<std::string> data_vector;
  std::string line; 
  int line_index{1};

  int no_data_entries{0};  // To count the number of data entries

  // Go through the dataset adding each line to the matrix
  while(std::getline(inputFile, line))
  {
    std::ostringstream line_stream;
    line_stream << line_index << ")" << line;
    data_vector.push_back(line_stream);



  // trying to create a vector of string streams different to a matrix but idk if this is the right direction...






    std::vector<std::string> temp_row;  // Temporary vector for the current row - needs splitting into components
    std::regex space_delimiter(" {4}|\\t");  // Setting the delimiter to be 4 spaces or a tab character

    // Use regex to split the line by multiple spaces and extract the element before it
    std::sregex_token_iterator it(line.begin(), line.end(), space_delimiter, -1);
    std::sregex_token_iterator end;  

    while (it != end) 
    {  // Loop through the tokens
      temp_row.push_back(*it); // Adds the value the iterator is pointing to and moves it onto the next token
      no_data_entries+=1;
      it++;
    }
    matrix.push_back(temp_row);  // Add each row to the matrix

    // put something here that is able to add each temp_row to a string stream of unique index?
  }
  inputFile.close();  // Close the file
}