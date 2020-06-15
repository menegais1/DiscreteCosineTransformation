//
// Created by menegais1 on 14/06/2020.
//

#ifndef DISCRETECOSINETRANSFORMATION_DATALOADER_H
#define DISCRETECOSINETRANSFORMATION_DATALOADER_H


#include <string>
#include <vector>

class DataLoader {
public:
    static std::vector<int> readData(std::string file);

    static void saveData(std::string file, std::vector<int> data);
};


#endif //DISCRETECOSINETRANSFORMATION_DATALOADER_H
