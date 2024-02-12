//
// Created by Roguebook on 08/02/2024.
//

#include "iostream"
#include "cstring"

using namespace std;

void extractString (FILE* fileName, size_t fileSize, size_t lines) {
    char* resultString = (char*) calloc(fileSize + 5, sizeof (char));
    fread (resultString, sizeof (char), fileSize + 5, fileName);
}

size_t sizeOfFIle (FILE* fileName) {
    fseek (fileName, 0, SEEK_END);
    size_t fileSize = ftell (fileName);
    fseek (fileName, 0, SEEK_SET);
    return fileSize;
}


