//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <iostream>
#include "TestWindows.hpp"

int main(int ac, char **av) {

    TestWindows toto;
    
    std::string tmp = "Hello world";
    
    toto.DisplayText(tmp);

    std::cout << "Hello world i'm back after 2 years" << std::endl;

    return (0);
}