//
// Created by menegais1 on 02/05/2020.
//

#ifndef BEZIERCURVES_FATORIAL_H
#define BEZIERCURVES_FATORIAL_H

class Fatorial {
private:
    Fatorial();
    double fat_lookUpTable[100];
public:
    static double fatorial(int n);

};

#endif //BEZIERCURVES_FATORIAL_H
