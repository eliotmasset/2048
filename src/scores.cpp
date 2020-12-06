#define BORDER_FOND 5
#define FENETRE_XTAILLE 700
#define FENETRE_YTAILLE 1000
#define SCORE_TAILLE 25
#define TITLE_TAILLE 140

#include "scores.h"

scores::scores()
{
    app.create(VideoMode(FENETRE_XTAILLE, FENETRE_YTAILLE, 32), "Scores - 2048");
    string const nomFichier("scores.txt");
    string Pseudo = "";
    string Score = "";

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
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
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
                        default :
                            break;
                    }
                }
                break;

                default :
                    break;
            }
        }
        tri();
        app.clear();
        sf::Text titre;
        titre.setFont(fontPrincipal); // Font
        titre.setString("2048");
        titre.setCharacterSize(TITLE_TAILLE); // Taille de police
        titre.setPosition(FENETRE_XTAILLE/2-titre.getCharacterSize()*1.5,FENETRE_YTAILLE/10); // Positionnement
        titre.setFillColor(Color(40, 136, 238)); // Coloration
        app.draw(titre);

        ifstream monFlux;
        monFlux.open(nomFichier.c_str());
        int taille = 0;
        if(monFlux)
        {
            std::string ligne;
            while(std::getline(monFlux, ligne))
            {
                taille++;
            }
            monFlux.close();
            monFlux.open(nomFichier.c_str());
            for(int i=0;i<taille;i++)
            {
                monFlux >> Pseudo ;
                monFlux >> Score ;
                sf::Text ligne;
                ligne.setFont(fontSecondaire);
                ligne.setString("Pseudo : " + Pseudo + "   ->   " + Score);
                ligne.setCharacterSize(15);
                ligne.setPosition(FENETRE_XTAILLE/2-titre.getCharacterSize()*2,FENETRE_YTAILLE/15*(i*0.5+4.5));
                ligne.setFillColor(Color(214,40,238));
                app.draw(ligne);
            }
        }
        else
        {
            cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
        }
        app.display();
    }
}

scores::~scores()
{
    //dtor
}

void scores::tri()
{
    ifstream monFlux;
    string const nomFichier("scores.txt");
    vector<string> v_pseudos;
    vector<string> v_score;
    string Pseudo="";
    string Score="";
    monFlux.open(nomFichier.c_str());
    int taille=0;

    if(monFlux)
    {
        std::string ligne;
        while(std::getline(monFlux, ligne))
        {
            taille++;
        }
        monFlux.close();
        monFlux.open(nomFichier.c_str());
        for(int i=0;i<taille;i++)
        {
            monFlux >> Pseudo;
            monFlux >> Score;
            v_pseudos.push_back(Pseudo);
            v_score.push_back(Score);
            for(int j=0;j<v_pseudos.size();j++)
            {
                if(v_pseudos[i]==v_pseudos[j] && j != v_pseudos.size()-1)
                {
                    if(stoi(v_score[i]) >= stoi(v_score[j]))
                    {
                        v_score.erase(v_score.begin()+j);
                        v_pseudos.erase(v_pseudos.begin()+j);
                        taille--;
                    }
                    else
                    {
                        v_score.erase(v_score.begin()+i);
                        v_pseudos.erase(v_pseudos.begin()+i);
                        taille--;
                    }
                }
                if(stoi(v_score[i]) >= stoi(v_score[j]))
                {
                    string s_score = v_score[i];
                    v_score[i] = v_score[j];
                    v_score[j] = s_score;
                    string s_pseudo = v_pseudos[i];
                    v_pseudos[i] = v_pseudos[j];
                    v_pseudos[j] = s_pseudo;
                }
            }
        }
    }
    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
    }
    ofstream secondFlux;
    secondFlux.open(nomFichier.c_str());
    if(secondFlux)
    {
        for(int i=0;i<v_score.size();i++)
        {
            secondFlux << v_pseudos[i] << " " << v_score[i] << endl;
        }
    }
    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
    }
}
