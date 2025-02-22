#include<iostream>
#include<fstream>  // Allows reading from a file
#include<sstream>  // Allows use of std::stringstream for processing strings
#include<string>
#include<vector>
#include<regex>  // Regular expressions for splitting lines 
#include<limits>
#include<cmath>
#include<iomanip>  // To use std::setprecision for rounding
#include<algorithm> // sort and reverse

std::string get_last_word(const std::string& str)
{
    std::istringstream iss(str);
    std::string names, last_name;
    while(iss>>names)
    {
      last_name = names;
    }
    return last_name;
}

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

    while (it != end) 
    {  // Loop through the tokens
      temp_row.push_back(*it); // Adds the value the iterator is pointing to and moves it onto the next token
      no_data_entries+=1;
      it++;
    }
    matrix.push_back(temp_row);  // Add each row to the matrix
  }
  inputFile.close();  // Close the file

  std::vector<std::vector<std::string>>::iterator matrix_begin{matrix.begin()};
  std::vector<std::vector<std::string>>::iterator matrix_end{matrix.end()};
  std::vector<std::vector<std::string>>::iterator matrix_iterator;
  
  // Sort data in ascending order
  sort(matrix_begin, matrix_end, [](const std::vector<std::string>& a, const std::vector<std::string>& b)
  {
    return get_last_word(a[2]) < get_last_word(b[2]);
  }); 
  std::cout<<"Sorted data:"<<std::endl;

  std::vector<std::string> row_vector;

  std::cout<<"Full book list:"<<std::endl;
  std::ostringstream output_stream; 
  for(matrix_iterator=matrix_begin; matrix_iterator<matrix_end; ++matrix_iterator)
  { // Iterates through the rows of the books data file
    row_vector = *matrix_iterator;
    std::vector<std::string>::iterator row_begin{row_vector.begin()};
    std::vector<std::string>::iterator row_end{row_vector.end()};
    std::vector<std::string>::iterator row_iterator;
    for(row_iterator=row_begin; row_iterator<row_end; ++row_iterator)
    { 
    // Iterates through the elements of the row to add the individual data entries to the stringstream
      output_stream << " " << *row_iterator;
    }
    // Print stringstream
    std::string output_line{output_stream.str()};
    std::cout<<output_line<<std::endl;
    output_stream.str(""); // Clear stream content
    output_stream.clear(); // Reset the stream state
  }

  return 0;
}