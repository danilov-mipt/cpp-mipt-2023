#include <iostream>
#include "cugms_utilities.hpp"


int main() {
    cugms::TokenizedStringConverter converter;
    
    std::string input = "";
    std::getline(std::cin, input);

    std::cout << converter._ConvertStringToUnix(input) << std::endl;
}
