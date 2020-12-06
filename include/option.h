#ifndef OPTION_H
#define OPTION_H

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

class option
{
    public:
        option();
        virtual ~option();
        void option1();
        void changeNbCase(int u=0);

    protected:

    private:
        RenderWindow app;
        RenderWindow appOpt1;
};

#endif // OPTION_H
