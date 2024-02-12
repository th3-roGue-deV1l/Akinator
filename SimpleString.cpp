//
// Created by Roguebook on 09/02/2024.
//

#include "SimpleString.h"

#define DEFAULT_SIZE 40

SimpleString::simple_string() {}

SimpleString:: simple_string(int max) {
    simpleString = new char[max];
    length_of_string = max;
}

SimpleString:: simple_string(std::string input) {
    strcpy(simpleString, input);
}