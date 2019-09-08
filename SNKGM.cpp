#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

using namespace std;

bool gameOver;
const int height=20;
const int width=20;
int x,y,fruitX,fruitY,score;
int tailX[width], tailY[height], nTail;
enum eDirection { STOP=0,LEFT,RIGHT,UP,DOWN };
eDirection dir;

void setup()
{
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    srand(time(0));
    int rr=0;
    while(!fruitX)
        fruitX=rand()%(width-1);
    fruitY=rand()%(height);
    score=0;
    nTail=0;
}

void draw()
{
    system("cls");

    for(int i=0;i<width;i++)
        cout<<"#";

    cout<<"\n";

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout<<"#";
            else if(j==width-1)
                cout<<"#";
            else if(i==y && j==x)
                cout<<"O";
            else if(i==fruitY && j==fruitX)
                cout<<"F";
            else
            {
                bool print=false;
                for(int k=0;k<nTail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
        }
        cout<<"\n";
    }

    for(int i=0;i<width;i++)
        cout<<"#";

    cout<<"\n\n";

    cout<<"SCORE: "<<score<<"\n";
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir=LEFT;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'x':
            gameOver=true;
            break;
        }
    }
}

void logic()
{
    /*int prevX=tailX[0],prevY=tailY[0];
    tailX[0]=x;
    tailY[0]=y;
    int curX,curY;
    for(int i=1; i<nTail; i++)
    {
        curX=tailX[i];
        curY=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=curX;
        prevY=curY;
    }*/

    for(int i=nTail-1;i>0;i--)
    {
        tailX[i]=tailX[i-1];
        tailY[i]=tailY[i-1];
    }
    tailX[0]=x;
    tailY[0]=y;

    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //if(x>=width-1 || x<=0 || y>=height || y<0)
    //    gameOver=true;

    if(x>=width-1)
        x=1;
    else if(x<=0)
        x=width-2;

    if(y>=height)
        y=0;
    else if(y<0)
        y=height-1;

    for(int i=0;i<nTail;i++)
    {
        if(tailX[i]==x && tailY[i]==y)
            gameOver=true;
    }

    if(x==fruitX && y==fruitY)
    {
        score=score+10;

        fruitX=0;
        while(!fruitX)
            fruitX=rand()%(width-1);

        fruitY=rand()%height;

        nTail++;
    }
}

int main()
{
    setup();

    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(50);
    }

    return 0;
}
