#include "option.h"

#define BORDER_FOND 5
#define FENETRE_XTAILLE 900
#define FENETRE_YTAILLE 900
#define FENETRE_OPT1_XTAILLE 300
#define FENETRE_OPT1_YTAILLE 100
#define TITLE_TAILLE 140
#define SUBTITLE_TAILLE 60

option::option()
{
    app.create(VideoMode(FENETRE_XTAILLE, FENETRE_YTAILLE, 32), "2048 - Options");
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            // Fenêtre fermée : on quitte
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
                            app.close();
                            break;
                        case sf::Keyboard::Numpad1 :
                            option1();
                            break;
                        case sf::Keyboard::Num1 :
                            option1();
                            break;

                        default :
                            break;
                    }
                }
                break;

                default :
                    break;
            }
        }

        // Efface l'écran (remplissage avec du noir)
        app.clear();

        Font fontPrincipal;
        if (!fontPrincipal.loadFromFile("FunSized.ttf"))
        {
            fontPrincipal.loadFromFile("arial.ttf");
        }

        Font fontSecondaire;
        if (!fontSecondaire.loadFromFile("Super Mario Bros.ttf"))
        {
            fontSecondaire.loadFromFile("arial.ttf");
        }

        sf::Text titre;
        titre.setFont(fontPrincipal); // Font
        titre.setString("2048");
        titre.setCharacterSize(TITLE_TAILLE); // Taille de police
        titre.setPosition(FENETRE_XTAILLE/2-titre.getCharacterSize()*1.5,FENETRE_YTAILLE/10); // Positionnement
        titre.setFillColor(Color(40, 136, 238)); // Coloration

        sf::Text option1;
        option1.setFont(fontSecondaire);
        option1.setString("1 - nombres de case");
        option1.setCharacterSize(SUBTITLE_TAILLE);
        option1.setPosition(FENETRE_XTAILLE/2-titre.getCharacterSize()*3,FENETRE_YTAILLE/10*4.5);
        option1.setFillColor(Color(214,40,238));
        app.draw(titre);
        app.draw(option1);

        // Affichage du contenu de la fenêtre à l'écran
        app.display();

    }
}

option::~option()
{
}

void option::option1()
{
    app.setVisible(false);
    appOpt1.create(VideoMode(FENETRE_OPT1_XTAILLE, FENETRE_OPT1_YTAILLE, 32), "2048 - Options");
    bool entree=false;
    Font font;
    if (!font.loadFromFile("Super Mario Bros.ttf"))
        font.loadFromFile("arial.ttf");
    sf::Text textSEnd;
    textSEnd.setFont(font);
    textSEnd.setPosition(BORDER_FOND, BORDER_FOND*5);
    textSEnd.setCharacterSize(15);
    textSEnd.setColor(Color(247,135,48));
    string m_saisie = "";
    while (appOpt1.isOpen() && !entree)
    {
        Event event;
        while (appOpt1.pollEvent(event))
        {
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode >= 48 && event.text.unicode < 57)
                {
                    m_saisie += static_cast<int>(event.text.unicode);
                }
            }
            switch (event.type) // Type de l'évènement
            {
                case Event::Closed : // Bouton de fermeture
                    appOpt1.close();
                    break;

                case Event::KeyPressed : // Appui sur une touche du clavier
                {
                    switch (event.key.code) // La touche qui a été appuyée
                    {
                        case sf::Keyboard::Escape : // Echap
                            entree=true;
                            changeNbCase(stoi(m_saisie));
                            appOpt1.close();
                            break;
                        case sf::Keyboard::Enter :
                            entree=true;
                            changeNbCase(stoi(m_saisie));
                            appOpt1.close();
                            break;
                        case sf::Keyboard::BackSpace :
                            if(m_saisie.length() > 0)
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
        appOpt1.clear();
        sf::Text textEnd;
        textEnd.setFont(font);
        textEnd.setString("Veuillez indiquer le nombre de case :");
        textEnd.setPosition(BORDER_FOND, BORDER_FOND*2);
        textEnd.setCharacterSize(13);
        textEnd.setColor(Color(247,135,48));
        appOpt1.draw(textEnd);
        appOpt1.draw(textSEnd);
        appOpt1.display();
    }
    app.setVisible(true);
}

void option::changeNbCase(int u)
{
    vector<string> options;
    string s_options="";
    string const nomFichier("options.txt");
    ifstream monFlux;
    monFlux.open(nomFichier.c_str());
    if(monFlux)
    {
        int taille = 0;
        std::string ligne;
        while(std::getline(monFlux, ligne))
        {
            taille++;
        }
        monFlux.close();
        monFlux.open(nomFichier.c_str());
        for(int i=0;i<taille;i++)
        {
            monFlux >> s_options;
            options.push_back(s_options);
        }
        options[0] = to_string(u);
    }
    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
    }
    monFlux.close();
    ofstream monFlux2;
    monFlux2.open(nomFichier.c_str());
    if(monFlux2)
    {
        for(int i=0;i<options.size();i++)
        {
            monFlux2 << options[i] << endl;
        }
    }
    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
    }
    monFlux2.close();
}
