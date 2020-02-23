#include <iostream>
#include <graphics.h>
#include <winbgim.h>

using namespace std;

int ok, dimTabla, dimensiunepatrat, raza;
int inalecran, latecran, mijloclatime, mijlocinaltime;
int rezultat;
int dx[]={-1, 0, 1, 0};
int dy[]={0, 1, 0, -1};

struct piesa
{
    int stare; // 0 daca nu este piesa, dar se afla pe tabla, 1 daca este piesa si se afla pe tabla, -1 determina forma tablei
    int x; // pozitia pe axa Ox
    int y; // pozitia pe axa Oy
} Matrice[30][30];

void patrat(int x, int y, int lat)
{
    line(x-lat/2,y-lat/2,x-lat/2,y+lat/2);
    line(x-lat/2,y+lat/2,x+lat/2,y+lat/2);
    line(x+lat/2,y+lat/2,x+lat/2,y-lat/2);
    line(x+lat/2,y-lat/2,x-lat/2,y-lat/2);
}

void deseneazatabla (int nivel)
{
    dimTabla = nivel*7+(nivel-1)*2;

    int centru = dimTabla/2+1;
    int spatiupanalatabla = dimTabla + 2;

    dimensiunepatrat=(min(inalecran,latecran))/spatiupanalatabla;  //dmin este dimensiunea minima

    mijloclatime=latecran/2;
    mijlocinaltime=inalecran/2;

    for(int i=0; i<=dimTabla+1; i++)
    {

        for (int j = 0; j<=dimTabla+1; j++)
        {
            if(i==0 || i==dimTabla+1 || j==0 || j==dimTabla+1)
                Matrice[i][j].stare = -1;
            else
                if ((i<dimTabla/3+1&&j<dimTabla/3+1) ||
                     (i<dimTabla/3+1&&j>dimTabla-dimTabla/3))
                        Matrice[i][j].stare = -1;
                else
                {
                    if((i>dimTabla-dimTabla/3&&j<dimTabla/3+1)||(i>dimTabla-dimTabla/3&&j>dimTabla-dimTabla/3))
                        Matrice[i][j].stare = -1;
                    else
                        Matrice[i][j].stare = 1;
                }

            Matrice[i][j].x = mijloclatime + (j-centru)*dimensiunepatrat;
            Matrice[i][j].y = mijlocinaltime + (i-centru)*dimensiunepatrat;
        }
    }

    Matrice[dimTabla/2+1][dimTabla/2+1].stare = 0;
}

void deseneaza(int niv, int& culoarePiese)
{
    setbkcolor(COLOR(228,168,178));
    cleardevice();
    raza=dimensiunepatrat/3;

    for(int i = 1; i<=dimTabla; i++)
        for(int j = 1; j<=dimTabla; j++)
            if(Matrice[i][j].stare == 1)
            {
                setcolor(0);
                patrat(Matrice[i][j].x, Matrice[i][j].y, dimensiunepatrat);
            }

    setcolor(culoarePiese);
    setfillstyle(SOLID_FILL, culoarePiese);

    for(int i = 1; i<=dimTabla; i++)
        for(int j = 1; j<=dimTabla; j++)
            if(Matrice[i][j].stare == 1)
                fillellipse (Matrice[i][j].x, Matrice[i][j].y,raza, raza);

}


int conditiemutare(int i1, int j1, int i2, int j2) //x si y sunt centrul piesei
{
    setfillstyle(SOLID_FILL, COLOR(228,168,178));
    setcolor(COLOR(228,168,178));

    if(i1==i2)
        if(j2==j1+2)
            if(Matrice[i1][j1+1].stare == 1)
            {
                fillellipse (Matrice[i1][j1+1].x, Matrice[i1][j1+1].y, raza, raza);
                Matrice[i1][j1+1].stare = 0;
                return 1;
            }

    if(i1 == i2)
        if(j1 == j2+2)
            if(Matrice[i1][j2+1].stare == 1)
            {
                fillellipse (Matrice[i2][j2+1].x, Matrice[i2][j2+1].y, raza, raza);
                Matrice[i2][j2+1].stare = 0;
                return 1;
            }

    if(j1 == j2)
        if(i2 == i1+2)
            if(Matrice[i1+1][j1].stare == 1)
            {
                fillellipse (Matrice[i1+1][j2].x, Matrice[i1+1][j2].y, raza, raza);
                Matrice[i1+1][j2].stare = 0;
                return 1;
            }

    if(j1 == j2)
        if(i1 == i2+2)
            if(Matrice[i2+1][j1].stare == 1)
            {
                fillellipse (Matrice[i2+1][j2].x, Matrice[i2+1][j2].y, raza, raza);
                Matrice[i2+1][j2].stare = 0;
                return 1;
            }

    return 0;
}

int castig()
{
    int nrpiese=0;

    for(int i=1; i<=dimTabla; i++)
        for(int j=1; j<=dimTabla; j++)
            if(Matrice[i][j].stare == 1)
                nrpiese++;
    if(nrpiese == 1 && Matrice[mijloclatime][mijlocinaltime].stare == 1)
        return 1;
    return 0;
}

void youWon()
{
    int midx, midy;

    Sleep(2000);

    midx = getmaxx()/2;
    midy = getmaxy()/2;

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(midx-300, midy-150, midx+300, midy+150);

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,7);
    setcolor(GREEN);
    outtextxy(midx,midy, "YOU WON!");

    Sleep(2000);

    return;
}

void youLost()
{
    int midx, midy;

    Sleep(2000);

    midx = getmaxx()/2;
    midy = getmaxy()/2;

    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(midx-300, midy-150, midx+300, midy+150);

    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(BOLD_FONT,HORIZ_DIR,7);
    setcolor(GREEN);
    outtextxy(midx,midy, "YOU LOST!");

    Sleep(2000);

    return;
}

bool amMutari()
{
     for(int i=1; i<=dimTabla; i++)
        for(int j=1; j<=dimTabla; j++)
            if(Matrice[i][j].stare == 1)
                for(int k=0; k<4; k++)
                    {
                        if(Matrice[i+dx[k]][j+dy[k]].stare == 1)
                            if(Matrice[i+2*dx[k]][j+2*dy[k]].stare == 0)
                                return true;
                    }
    return false;
}

void play(int niv, int& culoarePiese)
{
    int x1,y1,DA1=0,DA2=0,i1,i2,j1,j2,bila=1;

    while(amMutari())
    {
        getmouseclick(WM_LBUTTONDOWN, x1, y1);
        if(bila == 1)
        {
            for(int i=1; i<=dimTabla; i++)
                for(int j=1; j<=dimTabla; j++)
                    if(x1 >= Matrice[i][j].x-raza && x1 <= Matrice[i][j].x+raza)
                        if(y1 >= Matrice[i][j].y-raza && y1 <= Matrice[i][j].y+raza)
                        {
                            if(Matrice[i][j].stare == 1)
                            {
                                DA1=1;//inseamna ca este piesa pe primul click
                                i1=i;
                                j1=j;
                                bila=2;

                            }
                        }
        }
        if(bila == 2)
        {
            for(int i=1; i<=dimTabla; i++)
                for(int j=1; j<=dimTabla; j++)
                    if(x1 >= Matrice[i][j].x-raza && x1 <= Matrice[i][j].x+raza)
                        if(y1 >= Matrice[i][j].y-raza && y1 <= Matrice[i][j].y+raza)
                        {
                            if(Matrice[i][j].stare == 0)
                            {
                                DA2=1; //NU este piesa pe al doilea click
                                i2=i;
                                j2=j;
                                bila=1;
                            }
                        }
        }

        if(DA1 == 1 && DA2 == 1 && conditiemutare(i1,j1,i2,j2) == 1)
        {
            DA1=0; //restabilim ca sa nu fie piesa pe primul click
            DA2=0;
            bila=1;
            Matrice[i1][j1].stare=0;
            Matrice[i2][j2].stare=1;

            setfillstyle(SOLID_FILL, COLOR(228,168,178));
            setcolor(COLOR(228,168,178));
            fillellipse(Matrice[i1][j1].x, Matrice[i1][j1].y, raza, raza);

            setfillstyle(SOLID_FILL, culoarePiese);
            setcolor(culoarePiese);
            fillellipse(Matrice[i2][j2].x, Matrice[i2][j2].y, raza, raza);
        }
        if(DA1 == 0 && DA2 == 1)
        {
            DA1=0;
            DA2=0;
            bila=1;
        }
        if(DA1 == 1 && DA2 == 1 && conditiemutare(i1,j1,i2,j2) == 0)
        {
            bila=1;
            DA2=0;
            DA1=0;
        }

    }
    return;
}

void jocul(int niv, int& culoareOptiune)
{

    inalecran=getmaxheight();
    latecran=getmaxwidth();
    int fereastraNoua = initwindow(latecran,inalecran);
    deseneazatabla(niv);
    deseneaza(niv, culoareOptiune);

    play(niv, culoareOptiune);
    rezultat=castig();
    if(rezultat)
        youWon();
    else
        youLost();

    //getch();
    closegraph(fereastraNoua);
}
