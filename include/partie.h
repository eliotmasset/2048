#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "case.h"
#include "score.h"
#include "endWindow.h"

#ifndef PARTIE_H
#define PARTIE_H

using namespace sf;
using namespace std;


class partie
{
    public:
        partie();
        virtual ~partie();

    protected:

    private:
        RenderWindow app;
        score *sc;
        endWindow *ew;
        int NB_CASE = 4;
        void initiateFond();
        void initiatePartie();
        void ReloadApparences();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void ajouteNb();
        void calculeOptions();
        vector<Case*> quadrillage;
};

#endif // PARTIE_H
