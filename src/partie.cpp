#include "partie.h"

#define BORDER_FOND 5
#define FENETRE_XTAILLE 900
#define FENETRE_YTAILLE 900
#define TITLE_TAILLE 140
#define SUBTITLE_TAILLE 60

using namespace sf;
using namespace std;

partie::partie()
{
    app.create(VideoMode(FENETRE_XTAILLE, FENETRE_YTAILLE, 32), "2048");
    calculeOptions();
    initiatePartie();
    sc=new score();
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
                        case sf::Keyboard::Up :
                            moveUp();
                            break;
                        case sf::Keyboard::Down :
                            moveDown();
                            break;
                        case sf::Keyboard::Left :
                            moveLeft();
                            break;
                        case sf::Keyboard::Right :
                            moveRight();
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

        initiateFond();

        ReloadApparences();

        // Affichage du contenu de la fenêtre à l'écran
        app.display();

    }
}

partie::~partie()
{
    delete sc, ew;
}

void partie::initiateFond()
{
    RectangleShape fond;
    fond.setSize(sf::Vector2f(FENETRE_XTAILLE-BORDER_FOND*2, FENETRE_YTAILLE-BORDER_FOND*2));
    fond.setPosition(BORDER_FOND,BORDER_FOND);
    fond.setFillColor(Color(240, 138, 79));
    fond.setOutlineColor(Color(201,176,162));
    fond.setOutlineThickness(BORDER_FOND);
    app.draw(fond);
}

void partie::initiatePartie()
{
    int case_aleat = 0;
    int dOUq = 0;
	case_aleat = rand()%(NB_CASE*NB_CASE)+1;
	dOUq = rand()%3+1;
    for(int i=0;i<NB_CASE;i++)
    {
        for(int j=0;j<NB_CASE;j++)
        {
            quadrillage.push_back(new Case(BORDER_FOND+(FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE*i, BORDER_FOND+(FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE*j));
        }
    }
    if(dOUq == 1 )
    {
        quadrillage[case_aleat-1]->setValue(4);
    }
    else
    {
        quadrillage[case_aleat-1]->setValue(2);
    }
}

void partie::ReloadApparences()
{
    for(int i=0;i<NB_CASE*NB_CASE;i++)
    {
        RectangleShape c;
        c.setSize(sf::Vector2f((FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE-BORDER_FOND*2, (FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE-BORDER_FOND*2));
        c.setPosition(quadrillage[i]->getCoordX()+BORDER_FOND,quadrillage[i]->getCoordY()+BORDER_FOND);
        c.setFillColor(quadrillage[i]->getCouleurCase());
        c.setOutlineColor(Color(255,255,255));
        c.setOutlineThickness(BORDER_FOND);
        app.draw(c);

        if(quadrillage[i]->getValue() != 1)
        {
            Font fontNum;
            if (!fontNum.loadFromFile("Super Mario Bros.ttf"))
                fontNum.loadFromFile("arial.ttf");
            sf::Text numero;
            numero.setString(to_string(quadrillage[i]->getValue()));
            numero.setFont(fontNum);
            numero.setCharacterSize(SUBTITLE_TAILLE/(NB_CASE)/(0.25));
            if(quadrillage[i]->getValue()>=1)
                numero.setPosition(quadrillage[i]->getCoordX()+((FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.2 + BORDER_FOND,
                               quadrillage[i]->getCoordY()+((FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.7 + BORDER_FOND);
            if(quadrillage[i]->getValue()>=10)
                numero.setPosition(quadrillage[i]->getCoordX()+((FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.3 + BORDER_FOND,
                               quadrillage[i]->getCoordY()+((FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.7 + BORDER_FOND);
            if(quadrillage[i]->getValue()>=100)
                numero.setPosition(quadrillage[i]->getCoordX()+((FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.8 + BORDER_FOND,
                               quadrillage[i]->getCoordY()+((FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.7 + BORDER_FOND);
            if(quadrillage[i]->getValue()>=1000)
                numero.setPosition(quadrillage[i]->getCoordX()+((FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*1.3 + BORDER_FOND,
                               quadrillage[i]->getCoordY()+((FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.7 + BORDER_FOND);
            if(quadrillage[i]->getValue()>=10000)
                numero.setPosition(quadrillage[i]->getCoordX()+((FENETRE_XTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*1.7 + BORDER_FOND,
                               quadrillage[i]->getCoordY()+((FENETRE_YTAILLE-BORDER_FOND*2)/NB_CASE)/2-numero.getCharacterSize()*0.7 + BORDER_FOND);
            numero.setFillColor(Color(50,50,50));
            app.draw(numero);
        }
    }
}

void partie::moveLeft()
{
    int j=0;
    bool deplacer = false;
    bool UnDeplacement = false;
    for(int i=0;i<NB_CASE*NB_CASE;i++)
    {
        if(quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)]->getValue()!=1)
        {
            deplacer=false;
            int save_value=quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)]->getValue();
            quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)]->setValue(1);
            int u = NB_CASE;
            while(deplacer == false && u>=0)
            {
                if(j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u >= 0 && j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u < NB_CASE*NB_CASE)
                {
                    bool PasDeNombreEntre=true;
                    bool nombrePlacableEntre=false;
                    bool v=true;
                    if(save_value == quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u]->getValue())
                    {
                        PasDeNombreEntre=true;
                        nombrePlacableEntre=false;
                        v=false;
                        for(int e=0;e<u;e++)
                        {
                            if(v)
                                nombrePlacableEntre=true;
                            v=false;
                            if(quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*(u-e-1)]->getValue()!=1)
                            {
                                PasDeNombreEntre=false;
                                nombrePlacableEntre=false;
                                v=true;
                            }
                            if(nombrePlacableEntre && !PasDeNombreEntre)
                            {
                                quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u]->setValue(save_value);
                                if(u!=0)
                                    UnDeplacement=true;
                            }
                        }
                        if(PasDeNombreEntre)
                        {
                            quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u]->setValue(save_value*2);
                            if(u!=0)
                                UnDeplacement=true;
                            sc->setScore(sc->getScore()+(save_value*2));
                            deplacer = true;
                        }
                    }
                    else if(quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u]->getValue()==1)
                    {
                        quadrillage[j+(i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE)-NB_CASE*u]->setValue(save_value);
                        if(u!=0)
                            UnDeplacement=true;
                        deplacer = true;
                    }
                }
                u--;
            }
        }
        if((i+1)%NB_CASE==0)
            j++;
    }
    ReloadApparences();
    if(UnDeplacement)
        ajouteNb();
}

void partie::moveRight()
{
    int j=0;
    bool deplacer = false;
    bool UnDeplacement = false;
    for(int i=0;i<NB_CASE*NB_CASE;i++)
    {
        if(quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))]->getValue()!=1)
        {
            deplacer=false;
            int save_value=quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))]->getValue();
            quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))]->setValue(1);
            int u = NB_CASE;
            while(deplacer == false && u>=0)
            {
                if(j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u >= 0 && j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u < NB_CASE*NB_CASE)
                {
                    bool PasDeNombreEntre=true;
                    bool nombrePlacableEntre=false;
                    bool v=true;
                    if(save_value == quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u]->getValue())
                    {
                        PasDeNombreEntre=true;
                        nombrePlacableEntre=false;
                        v=false;
                        for(int e=0;e<u;e++)
                        {
                            if(v)
                                nombrePlacableEntre=true;
                            v=false;
                            if(quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*(u-e-1)]->getValue()!=1)
                            {
                                PasDeNombreEntre=false;
                                nombrePlacableEntre=false;
                                v=true;
                            }
                            if(nombrePlacableEntre && !PasDeNombreEntre)
                            {
                                quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u]->setValue(save_value);
                                if(u!=0)
                                    UnDeplacement=true;
                            }
                        }
                        if(PasDeNombreEntre)
                        {
                            quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u]->setValue(save_value*2);
                            if(u!=0)
                                UnDeplacement=true;
                            sc->setScore(sc->getScore()+(save_value*2));
                            deplacer = true;
                        }

                    }
                    else if(quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u]->getValue()==1)
                    {
                        quadrillage[j+(NB_CASE*(NB_CASE-1))-((i%NB_CASE)+(NB_CASE-1)*(i%NB_CASE))+NB_CASE*u]->setValue(save_value);
                        if(u!=0)
                            UnDeplacement=true;
                        deplacer = true;
                    }
                }
                u--;
            }
        }
        if((i+1)%NB_CASE==0)
            j++;
    }
    ReloadApparences();
    if(UnDeplacement)
        ajouteNb();
}

void partie::moveUp()
{
    int j=0;
    bool deplacer = false;
    bool UnDeplacement = false;
    for(int i=0;i<NB_CASE*NB_CASE;i++)
    {
        if(quadrillage[i]->getValue()!=1)
        {
            deplacer=false;
            int save_value=quadrillage[i]->getValue();
            quadrillage[i]->setValue(1);
            int u = NB_CASE;
            while(deplacer == false && u>=0)
            {
                if(i-u >= 0 && i-u < NB_CASE*NB_CASE && u<=i%NB_CASE)
                {
                    bool PasDeNombreEntre=true;
                    bool nombrePlacableEntre=false;
                    bool v=true;
                    if(save_value == quadrillage[i-u]->getValue())
                    {
                        PasDeNombreEntre=true;
                        nombrePlacableEntre=false;
                        v=false;
                        for(int e=0;e<u;e++)
                        {
                            if(v)
                                nombrePlacableEntre=true;
                            v=false;
                            if(quadrillage[i-(u-e-1)]->getValue()!=1)
                            {
                                PasDeNombreEntre=false;
                                nombrePlacableEntre=false;
                                v=true;
                            }
                            if(nombrePlacableEntre && !PasDeNombreEntre)
                            {
                                quadrillage[i-u]->setValue(save_value);
                            }
                        }
                        if(PasDeNombreEntre)
                        {
                            quadrillage[i-u]->setValue(save_value*2);
                            if(u!=0)
                                UnDeplacement=true;
                            sc->setScore(sc->getScore()+(save_value*2));
                            deplacer = true;
                        }

                    }
                    else if(quadrillage[i-u]->getValue()==1)
                    {
                        quadrillage[i-u]->setValue(save_value);
                        if(u!=0)
                            UnDeplacement=true;
                        deplacer = true;
                    }
                }
                u--;
            }
        }
        if((i+1)%NB_CASE==0)
            j++;
    }
    ReloadApparences();
    if(UnDeplacement)
        ajouteNb();
}

void partie::moveDown()
{
    int j=0;
    bool deplacer = false;
    bool UnDeplacement = false;
    for(int i=0;i<NB_CASE*NB_CASE;i++)
    {
        if(quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)]->getValue()!=1)
        {
            deplacer=false;
            int save_value=quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)]->getValue();
            quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)]->setValue(1);
            int u = NB_CASE;
            while(deplacer == false && u>=0)
            {
                if((NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u >= 0 && (NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u < NB_CASE*NB_CASE && u<=i%NB_CASE)
                {
                    bool PasDeNombreEntre=true;
                    bool nombrePlacableEntre=false;
                    bool v=true;
                    if(save_value == quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u]->getValue())
                    {
                        PasDeNombreEntre=true;
                        nombrePlacableEntre=false;
                        v=false;
                        for(int e=0;e<u;e++)
                        {
                            if(v)
                                nombrePlacableEntre=true;
                            v=false;
                            if(quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+(u-e-1)]->getValue()!=1)
                            {
                                PasDeNombreEntre=false;
                                nombrePlacableEntre=false;
                                v=true;
                            }
                            if(nombrePlacableEntre && !PasDeNombreEntre)
                            {
                                quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u]->setValue(save_value);
                            }
                        }
                        if(PasDeNombreEntre)
                        {
                            quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u]->setValue(save_value*2);
                            if(u!=0)
                                UnDeplacement=true;
                            sc->setScore(sc->getScore()+(save_value*2));
                            deplacer = true;
                        }

                    }
                    else if(quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u]->getValue()==1)
                    {
                        quadrillage[(NB_CASE-1)+(NB_CASE*j)-(i%NB_CASE)+u]->setValue(save_value);
                        if(u!=0)
                            UnDeplacement=true;
                        deplacer = true;
                    }
                }
                u--;
            }
        }
        if((i+1)%NB_CASE==0)
            j++;
    }
    ReloadApparences();
    if(UnDeplacement)
        ajouteNb();
}

void partie::ajouteNb()
{
    int case_aleat = 0;
    int dOUq = 0;
    bool isValide=false;
    for(int i=0;i<NB_CASE*NB_CASE;i++)
    {
        if(quadrillage[i]->getValue()==1)
            isValide=true;
    }
    if(!isValide)
    {
        bool playable = false;
        for(int i=0;i<NB_CASE*NB_CASE;i++)
        {
            if(i%NB_CASE != 0)
            {
                if(quadrillage[i]->getValue()==quadrillage[i-1]->getValue())
                    playable=true;
            }
            if(i%NB_CASE != NB_CASE-1)
            {
                if(quadrillage[i]->getValue()==quadrillage[i+1]->getValue())
                    playable=true;
            }
            if(i >= NB_CASE)
            {
                if(quadrillage[i]->getValue()==quadrillage[i-NB_CASE]->getValue())
                    playable=true;
            }
            if(i < NB_CASE*NB_CASE-NB_CASE)
            {
                if(quadrillage[i]->getValue()==quadrillage[i+NB_CASE]->getValue())
                    playable=true;
            }
        }
        if(!playable)
        {
            app.close();
            ew = new endWindow(sc->getScore());
        }
    }
    else
    {
        do
        {
            case_aleat = rand()%(NB_CASE*NB_CASE)+1;
        }while(quadrillage[case_aleat-1]->getValue()!=1);
        dOUq = rand()%3+1;
        if(dOUq == 1 )
        {
            quadrillage[case_aleat-1]->setValue(4);
        }
        else
        {
            quadrillage[case_aleat-1]->setValue(2);
        }
    }
}
void partie::calculeOptions()
{
    string const nomFichier("options.txt");
    string s_options = "";
    vector<string> options;
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
        NB_CASE = stoi(options[0]);

    }
    else
    {
        cerr << "ERREUR: Impossible d'ouvrir le fichier de sauvegarde" << endl;
    }
    monFlux.close();
}

