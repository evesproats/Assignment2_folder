// assignment2.cpp
// Assignment 2 - Books Database (PHYS30762)
// Eve Sproats, 11018744, 29/01/2024
// This code reads in book data from a database and prints it. It asks the user whether they would like a list of book data
// selected by subject or not, and whether they would like the list sorted by author surname or not. It then outputs the relevant
// book data along with the mean, standard deviation and standard error on the mean for the book prices. 
#include<iostream>
#include<fstream>  // Allows reading from a file
#include<sstream>  // Allows use of std::stringstream for processing strings
#include<string>
#include<vector>
#include<regex>  // Regular expressions for splitting lines 
#include<limits>
#include<cmath>
#include<iomanip>  // To use std::setprecision for rounding

std::string get_author_name(const std::string& str)
{
    std::istringstream iss(str);
    std::string names, last_name;
    while(iss>>names)
    {
      last_name = names;
    }
    return last_name;
}

double mean_function(const std::vector<double>& prices)
{
  double sum{0};
  for(int i{}; i<prices.size(); i++)
  {
    sum+=prices[i];
  }
  return sum / prices.size();
}

double standard_deviation_function(const std::vector<double>& prices, double mean)
{
  double sum{0};
  for(int i{}; i<prices.size(); i++)
  {
    sum+=pow((prices[i]-mean), 2);
  }
  return sqrt(1.0/(prices.size()-1.0)*sum);
}

double standard_error_function(const std::vector<double>& prices, double std_dev)
{
  return std_dev/sqrt(prices.size());
}

int main()
{
  std::ifstream inputFile("books_data.dat");  // Open the books data file 

  // Create a 2D vector called "matrix" to fill with the lines of the dataset
  std::vector<std::vector<std::string>> matrix;
  std::string line; 

  // Make counter for the number of data entries
  int no_file_entries{0};

  // Go through the dataset adding each line to the matrix
  while(std::getline(inputFile, line))
  {
    no_file_entries+=1;
    std::vector<std::string> temp_row;
    // Set delimiter to be 4 spaces or a tab character
    std::regex space_delimiter(" {4}|\\t");  
    // Use regex to split the line by multiple spaces and extract the element before it
    std::sregex_token_iterator it(line.begin(), line.end(), space_delimiter, -1);
    std::sregex_token_iterator end;  
    while (it != end) 
    {  
      temp_row.push_back(*it);
      it++;
    }
    matrix.push_back(temp_row); 
  }
  inputFile.close();

  // Printing using an iterator and stringstreams
  std::vector<std::vector<std::string>>::iterator matrix_begin{matrix.begin()};
  std::vector<std::vector<std::string>>::iterator matrix_end{matrix.end()};
  std::vector<std::vector<std::string>>::iterator matrix_iterator;
  std::vector<std::string> row_vector;
  std::cout<<"Full book list:"<<std::endl;
  for(matrix_iterator=matrix_begin; matrix_iterator<matrix_end; ++matrix_iterator)
  { // Iterates through the rows of the books data file
    row_vector = *matrix_iterator;
    // Create stringstream from row_vector
    std::ostringstream output_stream; 
    std::vector<std::string>::iterator row_begin{row_vector.begin()};
    std::vector<std::string>::iterator row_end{row_vector.end()};
    std::vector<std::string>::iterator row_iterator;
    for(row_iterator=row_begin; row_iterator<row_end; ++row_iterator)
    { 
      // Iterates through the elements of the row to add the individual elements to the stringstream
      output_stream << " | " << *row_iterator;
    }
    // Print stringstream
    std::string output_line{output_stream.str()};
    std::cout<<output_line<<std::endl;
    // Clear stream content and reset stream state
    output_stream.str("");
    output_stream.clear();
  }
  std::cout<<"The number of files entries is "<<no_file_entries<<"."<<std::endl;

  // Asking the user whether to select books by subject or not
  std::string all_or_subject;
  std::cout<<"This programme will now find the mean, standard deviation and standard error in the prices of a "
             "selection of books. If you would like to sort for a particular subject, please type 'subject'. Otherwise,"
             "please type 'all': "<<std::endl;
  std::cin>>all_or_subject;
  while(all_or_subject!="subject" && all_or_subject!="all")
  {
    std::cout<<"Sorry, that was not one of the options, please input either 'subject' or 'all': "<<std::endl;
    // Clear fail bit and ignore bad input
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; 
    std::cin>>all_or_subject;
  }
  std::string subject = "all";
  if(all_or_subject=="subject")
  {
    std::cout<<"What subject would you like to search for? You can choose from Mathematics, Physics or Chemistry: "<<std::endl;
    std::cin>>subject;
    // Sort for selected subjects
    while(subject!="Mathematics" && subject!="Physics" && subject!="Chemistry")
    {
      std::cout<<"Sorry, you have not typed that in correctly, please try again: "; 
      // Clear fail bit and ignore bad input
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; 
      std::cin>>subject;
    }
  }
  else
  {
    all_or_subject = "all";
  }

  // Asking the user whether to sort books by author surname or not
  std::string author_sort;
  std::cout<<"This programme can sort by author name. If you would like it to sort the results by author name, type 'y', "
             "otherwise, type 'n': "<<std::endl;
  std::cin>>author_sort;
  while(author_sort!="y" && author_sort!="n")
  {
    std::cout<<"Sorry, that was not one of the options, please input either 'y' or 'n': "<<std::endl;
    // Clear fail bit and ignore bad input
    std::cin.clear(); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; 
    std::cin>>author_sort;
  }
  if(author_sort=="y")
  {
    sort(matrix_begin, matrix_end, [](const std::vector<std::string>& a, const std::vector<std::string>& b)
    {
      return get_author_name(a[2]) < get_author_name(b[2]);
    }); 
  }

  // Create vector to store prices for chosen subject
  std::vector<double> prices;

  // Create counter for selected books data entries
  int no_file_entries_selected{0};

  // Extract rows based on subject
  for(matrix_iterator=matrix_begin; matrix_iterator<matrix_end; ++matrix_iterator)
  { 
    // Iterates through the rows of the books data file
    row_vector = *matrix_iterator;
    std::ostringstream output_stream; 
    if((all_or_subject=="subject" && row_vector[1]==subject) || (all_or_subject=="all"))
    {
      no_file_entries_selected += 1;
      // Create stringstream from row_vector
      std::vector<std::string>::iterator row_begin{row_vector.begin()};
      std::vector<std::string>::iterator row_end{row_vector.end()};
      std::vector<std::string>::iterator row_iterator;
      for(row_iterator=row_begin; row_iterator<row_end; ++row_iterator)
      { 
        // Iterates through the elements of the row to add the individual elements to the stringstream
        output_stream << " | " << *row_iterator;
      }
      // Print stringstream
      std::string output_line{output_stream.str()};
      std::cout<<output_line<<std::endl;
      // Clear stream content and reset stream state
      output_stream.str("");
      output_stream.clear();
      // Add price to list of prices for this subject
      std::string book_price_string = row_vector[0];
      double book_price = std::stod(book_price_string);
      prices.push_back(book_price);
    }
  }

  // Print number of selected file entries, and final mean, standard deviation and standard error on prices
  std::cout<<"The number of files entries for "<<subject<<" books is "<<no_file_entries_selected<<"."<<std::endl;
  double mean_price = mean_function(prices);
  std::cout<<"The mean price for "<<subject<<" books is: £"<<std::fixed<<std::setprecision(2)<<mean_price<<std::endl;
  double std_dev_price = standard_deviation_function(prices, mean_price);
  std::cout<<"The standard deviation for the price for "<<subject<<" books is: £"<<std::fixed<<std::setprecision(2)
           <<std_dev_price<<std::endl;
  double std_error_price = standard_error_function(prices, std_dev_price);
  std::cout<<"The standard error on the mean for the price for "<<subject<<" books is: £"<<std::fixed<<std::setprecision(2)
           <<std_error_price<<std::endl;

  return 0;
}