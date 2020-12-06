#ifndef CASE_H
#define CASE_H

#include <cstdlib>
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

using namespace sf;
using namespace std;

class Case
{
    public:
        Case(int x, int y);
        virtual ~Case();
        inline int getCoordX(){return coord_x;};
        inline int getCoordY(){return coord_y;};
        inline int getValue(){return value;};
        Color getCouleurCase();
        inline void setCoordX(int _coord_x){coord_x=_coord_x;};
        inline void setCoordY(int _coord_y){coord_y=_coord_y;};
        inline void setValue(int _value){value=_value;};

    protected:

    private:
        int coord_x=0;
        int coord_y=0;
        int value = 1;
};

#endif // CASE_H
