#define BORDER_FOND 5
#define FENETRE_XTAILLE 250
#define FENETRE_YTAILLE 50
#define SCORE_TAILLE 25

#include "score.h"

score::score()
{
    app.create(VideoMode(FENETRE_XTAILLE, FENETRE_YTAILLE, 32), "SCORE");
    app.setPosition(sf::Vector2i(app.getPosition().x+FENETRE_XTAILLE*2.5, app.getPosition().y-FENETRE_YTAILLE*3));
    score_v=0;
    reloadScore();
}

score::~score()
{
    //dtor
}

void score::reloadScore()
{
    app.clear();
    Font fontNum;
    if (!fontNum.loadFromFile("Super Mario Bros.ttf"))
        fontNum.loadFromFile("arial.ttf");
    score_t.setFont(fontNum);
    score_t.setCharacterSize(SCORE_TAILLE);
    score_t.setPosition(BORDER_FOND,BORDER_FOND*2);
    score_t.setFillColor(Color(247,135,48));
    score_t.setString("Score : " + to_string(score_v));
    app.draw(score_t);
    app.display();
}
