#define BOOST_TEST_MODULE boost_test_macro_overview
#include <boost/test/included/unit_test.hpp>

#include <vector>
#include <algorithm>    
#include <string>
#include "../../functions.h"


BOOST_AUTO_TEST_CASE( test_macro_overview )
{
    std::vector <std::string> expected {"this is a test",
                                        "this is another test", 
                                        "khaleesi is marrying jack sparrow"};
    
    std::vector <std::string> results;
    std::vector <std::string> file_names;
    file_names = retrieve_files("input");

    for (auto x : file_names){
        std::string message = read_file(x, "./input/");
        results.push_back(message);           
    }

    std::sort (expected.begin(), expected.end());
    std::sort (results.begin(), results.end());


    BOOST_CHECK_EQUAL_COLLECTIONS(results.begin(), results.end(), 
                              expected.begin(), expected.end());
  
}