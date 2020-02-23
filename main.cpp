#include <winbgim.h>
#include <stdlib.h>
#include <graphics.h>
#include <iostream>
#include <cmath>
#include <mmsystem.h>
#include "fisier.hpp"

using namespace std;

///------------Pictures Variables----------------------------------------------------------
const char *img1 = "mainScreen.jpg"   ;
const char *img2 = "instructions.jpg" ;
const char *img3 = "settings.jpg"     ;
///-----------------------------------------------------------------------------------------

///------------Pages Variables--------------------------------------------------------------
int mainPage     ;
int instructions ;
int settingsPage ;
int gamePage     ;
///------------------------------------------------------------------------------------------


int culoareOptiune  = 4  ;
int backAFostApasat = 0  ;
int muzicaEInchisa  = 0  ;

void Menu()
{
    readimagefile(img1,0,0,800,600);
}

void desenareChoise(int& culoareaAleasa)
{
    setcolor(culoareaAleasa);
    setfillstyle(SOLID_FILL, culoareaAleasa);
    bar(672, 222, 760, 310);
}

void optiuneCuloare(int& culoare)
{
    int soundOff = 0;
    backAFostApasat = 0;
    while(!backAFostApasat)
    {
        int x,y;
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x==-1 && y==-1)
            continue;

        if(x >= 696 && x <= 789 && y >= 571 && y <= 593 && getcurrentwindow() == settingsPage)
        {
            int currentWindow = getcurrentwindow();
            backAFostApasat = 1;

            if(soundOff)
                muzicaEInchisa=1;

            mainPage = initwindow(800, 600, "Solitarul");
            setcurrentwindow(mainPage);
            closegraph(currentWindow);
            Menu();
            break;
        }

        ///-----------pentru culorile pieselor ----------------------------------------------
        if(x >= 103 && x <= 173 && y >= 187 && y <= 256)
        {
            culoare = 0;
            desenareChoise(culoare);
        }

        if(x >= 180 && x <= 246 && y >= 187 && y <= 256)
        {
            culoare = 1;
            desenareChoise(culoare);
        }

        if(x >= 250 && x <= 318 && y >= 187 && y <= 256)
        {
            culoare = 2;
            desenareChoise(culoare);
        }

        if(x >= 324 && x <= 391 && y >= 187 && y <= 256)
        {
            culoare = 3;
            desenareChoise(culoare);
        }

        if(x >= 396 && x <= 462 && y >= 187 && y <= 256)
        {
            culoare = 4;
            desenareChoise(culoare);
        }

        if(x >= 469  && x <= 535 && y >= 187 && y <= 256)
        {
            culoare = 6;
            desenareChoise(culoare);
        }

        if(x >= 540 && x <= 608 && y >= 187 && y <= 256)
        {
            culoare = 7;
            desenareChoise(culoare);
        }

        if(x >= 103 && x <= 173 && y >= 277 && y <= 343)
        {
            culoare = 8;
            desenareChoise(culoare);
        }

        if(x >= 180 && x <= 246 && y >= 277 && y <= 343)
        {
            culoare = 9;
            desenareChoise(culoare);
        }

        if(x >= 251 && x <= 318 && y >= 277 && y <= 343)
        {
            culoare = 10;
            desenareChoise(culoare);
        }

        if(x >= 324 && x <= 396 && y >= 277 && y <= 343)
        {
            culoare = 11;
            desenareChoise(culoare);
        }

        if(x >= 397 && x <= 463 && y >= 277 && y <= 343)
        {
            culoare = 12;
            desenareChoise(culoare);
        }

        if(x >= 469 && x <= 536 && y >= 277 && y <= 343)
        {
            culoare = 14;
            desenareChoise(culoare);
        }

        if(x >= 542 && x <= 608 && y >= 277 && y <= 343)
        {
            culoare = 15;
            desenareChoise(culoare);
        }

        if(x >= 396 && x <= 534 && y >= 444 && y <= 510)
        {
            PlaySound((LPCSTR)NULL, NULL, SND_ASYNC|SND_LOOP);
            soundOff = 1;
        }

        if(x >= 252 && x <= 391 && y >= 444 && y <= 510 && (soundOff != 0 || muzicaEInchisa == 1))
        {
            PlaySound((LPCSTR)"music.wav", NULL, SND_ASYNC|SND_LOOP);
            soundOff=0;
        }
    }
}

void Instructions()
{
    readimagefile(img2,0,0,800,600);
}

void settingsPageWindow()
{
    readimagefile(img3,0,0,800,600);
    optiuneCuloare(culoareOptiune);
}

void StartGame()
{
    jocul(1, culoareOptiune);
}

///--------------Main Function ----------------------------------------------------------------
int main()
{
    PlaySound((LPCSTR)"music.wav", NULL, SND_ASYNC|SND_LOOP);

    mainPage=initwindow(800, 600, "Solitarul");
    Menu();


    while(true)
    {
        int x,y;
        getmouseclick(WM_LBUTTONDOWN, x, y);
        if(x==-1 && y==-1)
            continue;

        ///-----------pentru butonul de instructiuni de la pagina principala---------------------
        if(x >= 250 && x <= 608 && y >= 230 && y <= 274 && getcurrentwindow() == mainPage)
        {
            int currentWindow = getcurrentwindow();

            instructions = initwindow(800, 600, "Instructions");
            setcurrentwindow(instructions);
            closegraph(currentWindow);
            Instructions();
        }

        ///------------pentru butonul Back de la pagina Instructiuni-----------------------------
        if(x >= 670 && x <= 860 && y >= 560 && y <= 591 && getcurrentwindow() == instructions)
        {
            int currentWindow = getcurrentwindow();

            mainPage = initwindow(800, 600, "Solitarul");
            setcurrentwindow(mainPage);
            closegraph(currentWindow);
            Menu();
        }

        ///------------pentru butonul de setari de la pagina principala-----------------------
        if(x >= 300 && x <= 502 && y >= 339 && y <= 375 && getcurrentwindow() == mainPage)
        {
            int currentWindow = getcurrentwindow();

            settingsPage = initwindow(800, 600, "Settings Page");
            setcurrentwindow(settingsPage);
            closegraph(currentWindow);
            settingsPageWindow();
            continue;
        }

        ///------------pentru butonul de play de la pagina principala------------------------
        if(x >= 350 && x <= 504 && y >= 435 && y <= 472 && getcurrentwindow() == mainPage)
        {
            int currentWindow = getcurrentwindow();

            //gamePage = initwindow(800, 600, "Play");
            //setcurrentwindow(gamePage);
            //closegraph(currentWindow);
            StartGame();
            setcurrentwindow(currentWindow);
            continue;
        }

        ///------------pentru butonul de exit de la pagina principala----------------------
        if(x >= 348 && x <= 456 && y >= 525 && y <= 562 && getcurrentwindow() == mainPage)
        {
            int currentWindow = getcurrentwindow();
            cout<< "Goodbye!" <<'\n';
            closegraph(currentWindow);

            return 0;
        }
    }

    getch();
    closegraph();

    return 0;
}
///------------------------------------------------------------------------------------------------
