//
// Created by Roguebook on 12/02/2024.
//

#ifndef AKINATOR_SIMPLESTRING_H
#define AKINATOR_SIMPLESTRING_H

#include "string"

#define DEFAULT_SIZE 40

class simple_string {
private:

    char* simpleString = new char[DEFAULT_SIZE];
    unsigned long int length_of_string;


public:
    simple_string() {}

    // creates a string of a size supplied to the constructor
    explicit simple_string(int max)

    // creates a string that contains the string that we have input
    explicit simple_string(std::string input)
};

#endif //AKINATOR_SIMPLESTRING_H
