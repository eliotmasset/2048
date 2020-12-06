#include "endWindow.h"

#define FENETRE_XTAILLE 300
#define FENETRE_YTAILLE 150
#define BORDER_FOND 5

endWindow::endWindow(int _score)
{
    score = _score;
    app.create(VideoMode(FENETRE_XTAILLE, FENETRE_YTAILLE, 32), "2048 FIN");
    bool pseudoEntree = false;
    Font font;
    if (!font.loadFromFile("Super Mario Bros.ttf"))
        font.loadFromFile("arial.ttf");
    sf::Text textSEnd;
    textSEnd.setFont(font);
    textSEnd.setPosition(BORDER_FOND, BORDER_FOND*5);
    textSEnd.setCharacterSize(15);
    textSEnd.setColor(Color(247,135,48));
    string m_saisie("");
    while (app.isOpen() || pseudoEntree)
    {
        Event event;
        while (app.pollEvent(event))
        {

            if (event.type == sf::Event::TextEntered)
            {
                if((event.text.unicode > 30 && (event.text.unicode < 128 || event.text.unicode > 159)))
                {
                    m_saisie += static_cast<char>(event.text.unicode);
                }
            }
            switch (event.type) // Type de l'évènement
            {
                case Event::Closed : // Bouton de fermeture
                    app.close();
                    break;

                case Event::KeyPressed : // Appui sur une touche du clavier
                {
                    switch (event.key.code) // La touche qui a été appuyée
                    {
                        case sf::Keyboard::Escape : // Echap
                            savePseudo(m_saisie);
                            app.close();
                            break;
                        case sf::Keyboard::Enter :
                            savePseudo(m_saisie);
                            app.close();
                            break;
                        case sf::Keyboard::BackSpace :
                            m_saisie.pop_back();
                            break;
                        default :
                            break;
                    }
                }
                break;

                default :
                    break;
            }
            textSEnd.setString(m_saisie);
        }
        app.clear();
        sf::Text textEnd;
        textEnd.setFont(font);
        textEnd.setString("Veuillez indiquer votre pseudo :");
        textEnd.setPosition(BORDER_FOND, BORDER_FOND*2);
        textEnd.setCharacterSize(13);
        textEnd.setColor(Color(247,135,48));
        app.draw(textEnd);
        app.draw(textSEnd);
        app.display();
    }
}

endWindow::~endWindow()
{

}

void endWindow::savePseudo(string _Pseudo)
{
    Pseudo = _Pseudo;
    string const nomFichier("scores.txt");
    ofstream monFlux;
    monFlux.open(nomFichier.c_str(), ios::app);
    if(monFlux)
    {
        monFlux << Pseudo << " " << score << endl;
    }
    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
    }
}
