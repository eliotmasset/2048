#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

class endWindow
{
    public:
        endWindow(int _score = 0);
        virtual ~endWindow();
        void savePseudo(string _Pseudo = "");

    protected:

    private:
        RenderWindow app;
        string Pseudo = "";
        int score = 0;
};

#endif // ENDWINDOW_H
