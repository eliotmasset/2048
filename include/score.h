#ifndef SCORE_H
#define SCORE_H

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class score
{
    public:
        score();
        virtual ~score();
        inline int const getScore(){return score_v;};
        inline void setScore(int _score_v){score_v=_score_v;reloadScore();};
        void reloadScore();

    protected:

    private:
        RenderWindow app;
        int score_v=0;
        sf::Text score_t;
};

#endif // SCORE_H
