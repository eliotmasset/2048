#include "case.h"

Case::Case(int x, int y) : coord_x(x), coord_y(y)
{
}

Case::~Case()
{
    //dtor
}

Color Case::getCouleurCase()
{
    switch(value)
        {
        case 1:
            return Color(0,0,0);
            break;
        case 2:
            return Color(250,243,223);
            break;
        case 4:
            return Color(244,194,147);
            break;
        case 8:
            return Color(242,159,114);
            break;
        case 16:
            return Color(253,146,88);
            break;
        case 32:
            return Color(255,103,128);
            break;
        case 64:
            return Color(255,44,79);
            break;
        case 128:
            return Color(255,245,140);
            break;
        case 256:
            return Color(255,241,73);
            break;
        case 512:
            return Color(255,238,73);
            break;
        case 1024:
            return Color(255,236,45);
            break;
        case 2048:
            return Color(255,233,12);
            break;
        case 4096:
            return Color(0,89,155);
            break;
        case 8192:
            return Color(0,67,116);
            break;
        case 16384:
            return Color(0,29,50);
            break;
        default :
                cerr << "Erreur : apparence inexistante" << endl;
            break;
        }
}
