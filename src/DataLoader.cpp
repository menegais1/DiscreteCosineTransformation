//
// Created by menegais1 on 14/06/2020.
//

#include <iostream>
#include "DataLoader.h"

std::vector<int> DataLoader::readData(std::string file) {
    FILE *f = fopen(file.c_str(), "rb");
    if (f == nullptr) {
        std::cout << "File not found, generating random values" << std::endl;
        std::vector<int> v(8);
        for (int i = 0; i < 8; ++i) {
            v[i] = rand() % 255 - 128;
        }
        return v;
    }
    unsigned int length;
    fread(&length, sizeof(unsigned int), 1, f);
    char *values = new char[length];
    fread(values, 1, length, f);
    fclose(f);
    std::vector<int> v(length);
    for (int i = 0; i < length; ++i) {
        v[i] = (int) values[i];
    }
    return v;
}

void DataLoader::saveData(std::string file, std::vector<int> data) {
    FILE *f = fopen(file.c_str(), "wb");
    if (f == nullptr) {
        std::cout << "Could not save file" << std::endl;

    }
    unsigned int length = data.size();
    fwrite(&length, sizeof(unsigned int), 1, f);
    for (int i = 0; i < length; ++i) {
        char value = (char) data[i];
        fwrite(&value, 1, 1, f);
    }
    fclose(f);
}

