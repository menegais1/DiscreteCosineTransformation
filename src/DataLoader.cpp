//
// Created by menegais1 on 14/06/2020.
//

#include <iostream>
#include "DataLoader.h"

std::vector<int> DataLoader::readData(std::string file) {
    FILE *f = fopen(file.c_str(), "rb");

    uint length;
    fread(&length, sizeof(uint), 1, f);
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

    uint length = data.size();
    fwrite(&length, sizeof(uint), 1, f);
    for (int i = 0; i < length; ++i) {
        char value = (char) data[i];
        fwrite(&value,1,1,f);
    }
    fclose(f);
}

