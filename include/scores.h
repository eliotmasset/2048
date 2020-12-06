#ifndef SCORES_H
#define SCORES_H

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace sf;
using namespace std;


class scores
{
    public:
        scores();
        virtual ~scores();

    protected:

    private:
        RenderWindow app;
        void tri();
};

#endif // SCORES_H
