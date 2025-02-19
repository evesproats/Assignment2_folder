// PL3/cppstringstream.cpp
// Demonstration a string stream in the modern syntax
// Source: Prof. Niels Walet's code repository
// Last updated: Charanjit Kaur, 07/02/24
#include<iostream>
#include<string>
#include<sstream> 
int main() 
{
  std::string file_index="dat";
  std::ostringstream output_stream;
  output_stream << "books_data." << file_index;
  std::string output_filename{output_stream.str()};
  std::cout<<output_filename<<std::endl;
  output_stream.str(""); //clear stream content
  return 0;
}