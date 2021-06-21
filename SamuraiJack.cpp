#include <fstream.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <dos.h>
#include<stdlib.h>
////////////////////////////////////////////////////////////////////////////////////
int height = 47, noene[10], firestat = 0, health = 10, life = 3, nogem[10], noruby[10], stat, rpass[10], lpass[10], door[10];
int curmov, eltime, noscore, nobase[10] = { 0 }, level =1, curbase = 0, chhealth, lifeup;
int gdir, throughr, throughl, throughdoor, ofnog[10], ofnor[10], ofnoe[10], ofnogem[10], ofnoruby[10];
int ofnoene[10], stage, post = 1, hdir = 1, blano, tcont, bullx, bully, excuse = 1, gameloaded = 0, recordno = 0;
char filedir[] = "c:\\samurai.dat"; //save file directory
char curtime[10]; //store the current time
time_t ctim, otim; //time variables to perform time operations
///////////////////////////////////////////////////////////////////////////////
//prototypes
void save(int);
void hithero(int, int, int, int);
void heroclose(int,int);
void drawruby(int, int, int, int, int);
void enemyclose(int, int, int);
void drawgem(int, int, int, int, int);
void redrawplats();
void drawhero(int, int, int, int);
void erasehero(int, int, int, int);
int gameover(int);
void thgenemy(int, int, int, int, int);
void txtAnim(int, int, char*);
void success(int);
void logo();
void drawdoor(int);
void drawene(int, int, int);
void menuAnim(int, int, int, int);
void mainmenu();
void start();
void highscore();
void help();
void border(int);
void name();
void loadninja();
void plat(int, int, int, int);
int quit();
////////////////////////////////////////////////////////////////////////////////
//class declarations
struct score {
    char name[30];
    int score, stage, level;
} scr;
struct base {
    int x1;
    int y1;
    int x2;
    int y2;
} base[10][20];
struct thg_gem {
    int x;
    int y;
    int flag;
    int scope;
} gems[10][20];
struct ruby {
    int x;
    int y;
    int flag;
    int scope;
} rubys[10][20];
struct enemy {
    int x;
    int y;
    int bullx;
    int bully;
    int bulldir;
    int stat;
    int firestat;
    int jumpstat;
    int bullfired;
    int dirchange;
    int scope;
    int blano;
} ens[10][20];
//////////////////////////////////////////////////////////////////////////////
void main()
{
    int gdriv = DETECT, gmode;
    initgraph(&gdriv, &gmode, "C:\\TURBOC3\\BGI");
    setgraphbufsize(2000);
    logo();
    mainmenu();
}
///////////////////////////////////////////////////////////////////////////////
void menuAnim(int x, int y, int s, int menu)
{
    if (s) {
	setlinestyle(0,0,THICK_WIDTH);
	bar(x + 72, y - 15, x + 265, y - 10);
	bar(x + 69, y - 14, x + 75, y + 18);
	bar(x + 70, y + 19, x + 265, y + 23);
	bar(x + 265, y - 14, x + 271, y + 22);

	setfillstyle(1,WHITE);
	bar(x + 72, y - 15, x + 265, y - 10);
	bar(x + 69, y - 14, x + 75, y + 18);
	bar(x + 70, y + 19, x + 265, y + 23);
	bar(x + 265, y - 14, x + 271, y + 22);
	for (int i = 300;;) {
	    delay(5);
	    if (kbhit())
		break;
	    setfillstyle(1,YELLOW);
	    bar(x + 75, y - 10, x + 265, y + 18);
	    i--;
	    setcolor(RED);
	    if (menu == 1) {
		if (y == 250) {
		    outtextxy(i, y, "START");
		    if (i <= 283)
			break;
		}
		else if (y == 300) {
		    outtextxy(i, y, "HIGHSCORE");
		    if (i <= 290)
			break;
		}
		else if (y == 350) {
		    outtextxy(i, y, "HELP");
		    if (i <= 290)
			break;
		}
		else if (y == 400) {
		    outtextxy(i, y, "EXIT");
		    if (i <= 280)
			break;
		}
	    }

	}
	if (kbhit()) {
	    setfillstyle(1,LIGHTCYAN);
	    bar(x + 75, y - 10, x + 265, y + 18);
	    setcolor(RED);
	    if (menu == 1) {
		if (y == 250)
		    outtextxy(300, y, "START");
		else if (y == 300)
		    outtextxy(300, y, "HIGHSCORE");
		else if (y == 350)
		    outtextxy(300, y, "HELP");
		else if (y == 400)
		    outtextxy(300, y, "EXIT");
	    }
	}
    }
    else {
	setfillstyle(1,LIGHTCYAN);
	bar(x + 70, y - 15, x + 265, y - 10);
	bar(x + 69, y - 14, x + 75, y + 18);
	bar(x + 70, y + 18, x + 265, y + 23);
	bar(x + 265, y - 14, x + 271, y + 22);
    }
}
//////////////////////////////////////////////////////////////////////////////////
void erasehero(int x, int y, int a, int dir) //erasing hero
{
    setfillstyle(1, BLACK);
    setcolor(BLACK);
    if (dir) {
	int cap[] = { x + 0, y + 10, x + 9, y + 7, x + 14, y + 0, x + 9, y + 3, x + 7, y + 0, x + 4, y + 5, x + 0, y + 10 };
	int headr[] = { x + 4, y + 8, x + 4, y + 15, x + 8, y + 18, x + 8, y + 14, x + 10, y + 13, x + 10, y + 5 };
	int sca[] = { x + 8, y + 18, x + 4, y + 20, x + 8, y + 19, x + 10, y + 20, x + 9, y + 19 };
	int lha[] = { x + 5, y + 21, x + 5, y + 25, x + 10, y + 30, x + 12, y + 29, x + 8, y + 25, x + 8, y + 20 };
	int rleg[] = { x + 5, y + 47, x + 8, y + 48, x + 9, y + 35, x + 5, y + 47 };
	int lleg[] = { x + 9, y + 35, x + 13, y + 47, x + 15, y + 46, x + 12, y + 35, x + 9, y + 35 };
	int body[] = { x + 6, y + 25, x + 7, y + 35, x + 10, y + 35, x + 10, y + 21, x + 6, y + 25 };
	int lh2[] = { x + 5, y + 21, x + 5, y + 25, x + 6, y + 39, x + 5, y + 29, x + 6, y + 25, x + 6, y + 20 };
	int rl2[] = { x + 7, y + 35, x + 7, y + 45, x + 9, y + 49, x + 8, y + 35, x + 7, y + 35 };
	int ll2[] = { x + 9, y + 35, x + 10, y + 47, x + 12, y + 46, x + 10, y + 35, x + 9, y + 35 };
	int mskr[] = { x + 4, y + 9, x + 11, y + 7, x + 11, y + 12, x + 4, y + 12 };
	if (a % 7 < 4) {
	    fillpoly(7, cap);
	    fillpoly(6, headr);
	    fillpoly(5, body);
	    fillpoly(6, lha);
	    fillpoly(4, rleg);
	    fillpoly(5, lleg);
	    fillpoly(5, sca);
	    fillpoly(4, mskr);
	}
	else {
	    fillpoly(7, cap);
	    fillpoly(6, headr);
	    fillpoly(5, body);
	    fillpoly(6, lh2);
	    fillpoly(5, rl2);
	    fillpoly(5, ll2);
	    fillpoly(5, sca);
	    fillpoly(4, mskr);
	}
    }
    else {
	int cap[] = { x + 5, y + 10, x + 0, y + 0, x + 5, y + 5, x + 10, y + 0, x + 10, y + 5, x + 15, y + 10, x + 10, y + 10, x + 5, y + 7 };
	int headr[] = { x + 4, y + 5, x + 4, y + 14, x + 7, y + 16, x + 7, y + 18, x + 10, y + 13, x + 10, y + 5 };
	int sca[] = { x + 8, y 	+ 18, x + 4, y + 20, x + 8, y + 19, x + 10, y + 20, x + 9, y + 19 };
	int lha[] = { x + 10, y + 21, x + 10, y + 25, x + 5, y + 30, x + 3, y + 29, x + 7, y + 25, x + 7, y + 20 };
	int rleg[] = { x + 5, y + 47, x + 8, y + 48, x + 9, y + 35, x + 5, y + 47 };
	int lleg[] = { x + 8, y + 35, x + 12, y + 47, x + 14, y + 46, x + 11, y + 35, x + 8, y + 35 };
	int body[] = { x + 5, y + 25, x + 6, y + 35, x + 9, y + 35, x + 9, y + 21, x + 5, y + 25 };
	int lh2[] = { x + 5, y + 21, x + 5, y + 25, x + 6, y + 39, x + 5, y + 29, x + 6, y + 25, x + 6, y + 20 };
	int rl2[] = { x + 6, y + 35, x + 5, y + 45, x + 7, y + 49, x + 8, y + 35, x + 5, y + 35 };
	int ll2[] = { x + 9, y + 35, x + 9, y + 47, x + 11, y + 46, x + 9, y + 35, x + 9, y + 35 };
	int mskl[] = { x + 11, y + 9, x + 4, y + 7, x + 4, y + 12, x + 11, y + 12 };
	if (a % 7 < 4) {
	    fillpoly(6, headr);
	    fillpoly(8, cap);
	    fillpoly(5, body);
	    fillpoly(6, lha);
	    fillpoly(4, rleg);
	    fillpoly(5, lleg);
	    fillpoly(5, sca);
	    fillpoly(4, mskl);
	}
	else {
	    fillpoly(6, headr);
	    fillpoly(8, cap);
	    fillpoly(5, body);
	    fillpoly(6, lh2);
	    fillpoly(5, rl2);
	    fillpoly(5, ll2);
	    fillpoly(5, sca);
	    fillpoly(4, mskl);
	}
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void drawhero(int x, int y, int a, int dir) //drawing the hero
{
    if (dir) {
	int cap[] = { x + 0, y + 10, x + 9, y + 7, x + 14, y + 0, x + 9, y + 3, x + 7, y + 0, x + 4, y + 5, x + 0, y + 10 };
	int headr[] = { x + 4, y + 8, x + 4, y + 15, x + 8, y + 18, x + 8, y + 14, x + 10, y + 13, x + 10, y + 5 };
	int sca[] = { x + 8, y + 18, x + 4, y + 20, x + 8, y + 19, x + 10, y + 20, x + 9, y + 19 };
	int lha[] = { x + 5, y + 21, x + 5, y + 25, x + 10, y + 30, x + 12, y + 29, x + 8, y + 25, x + 8, y + 20 };
	int rleg[] = { x + 5, y + 47, x + 8, y + 48, x + 9, y + 35, x + 5, y + 47 };
	int lleg[] = { x + 9, y + 35, x + 13, y + 47, x + 15, y + 46, x + 12, y + 35, x + 9, y + 35 };
	int body[] = { x + 6, y + 25, x + 7, y + 35, x + 10, y + 35, x + 10, y + 21, x + 6, y + 25 };
	int lh2[] = { x + 5, y + 21, x + 5, y + 25, x + 6, y + 39, x + 5, y + 29, x + 6, y + 25, x + 6, y + 20 };
	int rl2[] = { x + 7, y + 35, x + 7, y + 45, x + 9, y + 49, x + 8, y + 35, x + 7, y + 35 };
	int ll2[] = { x + 9, y + 35, x + 10, y + 47, x + 12, y + 46, x + 10, y + 35, x + 9, y + 35 };
	int mskr[] = { x + 4, y + 9, x + 11, y + 7, x + 11, y + 12, x + 4, y + 12 };
	if (a % 7 < 4) {
	    setfillstyle(1, 8);
	    fillpoly(7, cap);
	    setfillstyle(1, 7);
	    fillpoly(6, headr);
	    fillpoly(5, body);
	    setfillstyle(6, 8);
	    fillpoly(6, lha);
	    fillpoly(4, rleg);
	    fillpoly(5, lleg);
	    setfillstyle(1, RED);
	    fillpoly(5, sca);
	    setfillstyle(6, 8);
	    fillpoly(4, mskr);
	}
	else {
	    setfillstyle(1, 8);
	    fillpoly(7, cap);
	    setfillstyle(1, 7);
	    fillpoly(6, headr);
	    fillpoly(5, body);
	    setfillstyle(6, 8);
	    fillpoly(6, lh2);
	    fillpoly(5, rl2);
	    fillpoly(5, ll2);
	    setfillstyle(1, RED);
	    fillpoly(5, sca);
	    setfillstyle(6, 8);
	    fillpoly(4, mskr);
	}
    }
    else {
	int cap[] = { x + 5, y + 10, x + 0, y + 0, x + 5, y + 5, x + 10, y + 0, x + 10, y + 5, x + 15, y + 10, x + 10, y + 10, x + 5, y + 7 };
	int headr[] = { x + 4, y + 5, x + 4, y + 14, x + 7, y + 16, x + 7, y + 18, x + 10, y + 13, x + 10, y + 5 };
	int sca[] = { x + 8, y + 18, x + 4, y + 20, x + 8, y + 19, x + 10, y + 20, x + 9, y + 19 };
	int lha[] = { x + 10, y + 21, x + 10, y + 25, x + 5, y + 30, x + 3, y + 29, x + 7, y + 25, x + 7, y + 20 };
	int rleg[] = { x + 5, y + 47, x + 8, y + 48, x + 9, y + 35, x + 5, y + 47 };
	int lleg[] = { x + 8, y + 35, x + 12, y + 47, x + 14, y + 46, x + 11, y + 35, x + 8, y + 35 };
	int body[] = { x + 5, y + 25, x + 6, y + 35, x + 9, y + 35, x + 9, y + 21, x + 5, y + 25 };
	int lh2[] = { x + 5, y + 21, x + 5, y + 25, x + 6, y + 39, x + 5, y + 29, x + 6, y + 25, x + 6, y + 20 };
	int rl2[] = { x + 6, y + 35, x + 5, y + 45, x + 7, y + 49, x + 8, y + 35, x + 5, y + 35 };
	int ll2[] = { x + 9, y + 35, x + 9, y + 47, x + 11, y + 46, x + 9, y + 35, x + 9, y + 35 };
	int mskl[] = { x + 11, y + 9, x + 4, y + 7, x + 4, y + 12, x + 11, y + 12 };
	if (a % 7 < 4) {
	    setfillstyle(1, 8);
	    fillpoly(8, cap);
	    setfillstyle(1, 7);
	    fillpoly(6, headr);
	    fillpoly(5, body);
	    setfillstyle(6, 8);
	    fillpoly(6, lha);
	    fillpoly(4, rleg);
	    fillpoly(5, lleg);
	    setfillstyle(1, RED);
	    fillpoly(5, sca);
	    setfillstyle(6, 8);
	    fillpoly(4, mskl);
	}
	else {
	    setfillstyle(1, 8);
	    fillpoly(8, cap);
	    setfillstyle(1, 7);
	    fillpoly(6, headr);
	    fillpoly(5, body);
	    setfillstyle(6, 8);
	    fillpoly(6, lh2);
	    fillpoly(5, rl2);
	    fillpoly(5, ll2);
	    setfillstyle(1, RED);
	    fillpoly(5, sca);
	    setfillstyle(6, 8);
	    fillpoly(4, mskl);
	}
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
void drawene(int x, int y, int dir) //drawing the enemy
{
    setcolor(BLACK);
    if (dir) {
	int cap[] = { x + 0, y + 10, x + 9, y + 7, x + 14, y + 0, x + 9, y + 3, x + 7, y + 0, x + 4, y + 5, x + 0, y + 10 };
	int headr[] = { x + 4, y + 8, x + 4, y + 15, x + 8, y + 18, x + 8, y + 14, x + 10, y + 13, x + 10, y + 5 };
	int sca[] = { x + 8, y + 18, x + 4, y + 20, x + 8, y + 19, x + 10, y + 20, x + 9, y + 19 };
	int lha[] = { x + 5, y + 21, x + 5, y + 25, x + 10, y + 30, x + 12, y + 29, x + 8, y + 25, x + 8, y + 20 };
	int rleg[] = { x + 5, y + 47, x + 8, y + 48, x + 9, y + 35, x + 5, y + 47 };
	int lleg[] = { x + 9, y + 35, x + 13, y + 47, x + 15, y + 46, x + 12, y + 35, x + 9, y + 35 };
	int body[] = { x + 6, y + 25, x + 7, y + 35, x + 10, y + 35, x + 10, y + 21, x + 6, y + 25 };
	setfillstyle(1, 8);
	fillpoly(7, cap);
	setfillstyle(1, 7);
	fillpoly(6, headr);
	fillpoly(5, body);
	setfillstyle(6, 8);
	fillpoly(6, lha);
	fillpoly(4, rleg);
	fillpoly(5, lleg);
	setfillstyle(1, RED);
	fillpoly(5, sca);
    }
    else {
	int cap[] = { x + 5, y + 10, x + 0, y + 0, x + 5, y + 5, x + 10, y + 0, x + 10, y + 5, x + 15, y + 10, x + 10, y + 10, x + 5, y + 7 };
	int headr[] = { x + 4, y + 5, x + 4, y + 14, x + 7, y + 16, x + 7, y + 18, x + 10, y + 13, x + 10, y + 5 };
	int sca[] = { x + 8, y + 18, x + 4, y + 20, x + 8, y + 19, x + 10, y + 20, x + 9, y + 19 };
	int lha[] = { x + 10, y + 21, x + 10, y + 25, x + 5, y + 30, x + 3, y + 29, x + 7, y + 25, x + 7, y + 20 };
	int rleg[] = { x + 5, y + 47, x + 8, y + 48, x + 9, y + 35, x + 5, y + 47 };
	int lleg[] = { x + 8, y + 35, x + 12, y + 47, x + 14, y + 46, x + 11, y + 35, x + 8, y + 35 };
	int body[] = { x + 5, y + 25, x + 6, y + 35, x + 9, y + 35, x + 9, y + 21, x + 5, y + 25 };
	setfillstyle(1, 8);
	fillpoly(6, headr);
	setfillstyle(1, 7);
	fillpoly(8, cap);
	fillpoly(5, body);
	setfillstyle(6, 8);
	fillpoly(6, lha);
	fillpoly(4, rleg);
	fillpoly(5, lleg);
	setfillstyle(1, RED);
	fillpoly(5, sca);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
void txtAnim(int x, int y, char* a) //to create a txt efect at x,y
{
    int col = getcolor(), t = 0;
    int width = textwidth("A"), height = textheight("A");
    char buf[2] = " \n";
    for (int i = 0; a[i]; i++) {
	buf[0] = a[i];
	if (buf[0] == 'i')
	    t = width / 3;
	else if (buf[0] == 'I')
	    t = width / 4.0;
	else
	    t = 0;
	for (int tx = x + width * i + width / 2.0 + t, ty = y - 2 * height; tx > x + width * i + t && ty < y + height;) {
	    setcolor(BLACK);
	    outtextxy(tx, ty, buf);
	    tx -= 2;
	    ty += 2;
	    setcolor(col);
	    outtextxy(tx, ty, buf);
	    delay(10);
	}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void border(int j)
{
	setfillstyle(1,j);
    bar(0, 0, getmaxx(), getmaxy());
    for (int i = 0; i < getmaxy(); i++)
	{
	setfillstyle(1, WHITE);
	setlinestyle(0,0,THICK_WIDTH);
	bar(0, i, 5, i + 4);
	bar(getmaxx() - 5, i, getmaxx(), i + 4);
	bar(i + 2, 0, i + 5, 5);
	bar(getmaxx() - i, 0, getmaxx() - i - 5, 5);
	bar(i + 2, getmaxy(), i + 5, getmaxy() - 5);
	bar(getmaxx() - i, getmaxy(), getmaxx() - i - 5, getmaxy() - 5);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
void logo()
{
    cleardevice();

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    outtextxy(getmaxx()/2-30,getmaxy()/2 - 90,"BY");

    for(int i = 0;; i++)
    {
	time_t t;
	time(&t);
	srand(i^(i+(t%10)));
	setcolor(random(16));
	if(i % 10 == 0)
	    setcolor(BLACK);
	int r = random(2), s = random(2);
	settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
	outtextxy(70-s+r,getmaxy()/2-30,".A S H U T O S H.");
	outtextxy(72-s+r,getmaxy()/2-30,".A S H U T O S H.");
	outtextxy(120-s+r,getmaxy()/2+70,".Y U V R A J.");
	outtextxy(122-s+r,getmaxy()/2+70,".Y U V R A J.");
	outtextxy(140-s+r,getmaxy()/2+20,".A M E Y A.");
	outtextxy(142-s+r,getmaxy()/2+20,".A M E Y A.");
	if(kbhit())
	{
	    clearviewport();
	    break;
	}
    }
    if(getch() == 0)
    {
	getch();
    }
    setcolor(WHITE);
    rectangle(0,0,getmaxx(),getmaxy()-1);
    settextstyle(2, HORIZ_DIR, 4);
    outtextxy(105,getmaxy() - 50, "Copyright 2018. Samrai Jack");
    outtextxy(275,getmaxy() - 50, "is a registered trademark of AFSH Studios.");
    settextstyle(2, HORIZ_DIR, 1);
    outtextxy(263,getmaxy() - 50, "(R)");
    outtextxy(519,getmaxy() - 49, "(C )");
    settextstyle(DEFAULT_FONT,HORIZ_DIR,5);
    outtextxy(18,getmaxy()/2-180," Loading");
    outtextxy(213,getmaxy()/2-70,"  Game...");
    int R = 150;
    for(i = 0;; i++)
    {
	time_t t;
	time(&t);
	srand(i^(i+(t%10)));
	int k = random(10);
	if(R + k < 500)
	    R += k;
	else
	    R = 499;
	setcolor(WHITE);
	rectangle(150,260,500,280);
	setfillstyle(1,LIGHTCYAN);
	bar(151,261,R,279);
	if(getpixel(499,270) == LIGHTCYAN)
	    break;
	settextstyle(2, HORIZ_DIR, 4);
	if(R < 260)
	    outtextxy(60,300," Starting the Game engine, Setting up Compiler, Interpreting Code, Decrypting User Data...");
	else if(R > 260 && R < 410)
	    outtextxy(55,300," Processor Overclocked, RAM Overclocked (Optimum = 8GB), Graphics card absent (Optimum = 4GB)");
	else if(R > 410 && R < 500)
	    outtextxy(35,300," OS Detected - MS-DOS (Optimum - Mac OS X 10.10.2). Optimizing game to run on DOS (May have glitches)");
	if(R > 260 && R < 270 || R > 410 && R < 420)
	{
	    setcolor(BLACK);
	    setfillstyle(1,BLACK);
	    bar(1,290,getmaxx()-1,330);
	}
	if(kbhit())
	{
	    int c = getch();
	    if(c == 13)
	    {
		bar(151,261,499,279);
		break;
	    }
	}
	delay(random(100));
    }
    R = 0;
    for(i = 0;; i++)
    {
	settextstyle(1, HORIZ_DIR, 4);
	if(R == 0)
	{
	    setcolor(WHITE);
	    R = 1;
	}
	else if(R == 1)
	{
	    setcolor(LIGHTGRAY);
	    R = 2;
	}
	else if(R == 2)
	{
	    setcolor(DARKGRAY);
	    R = 3;
	}
	else if(R == 3)
	{
	    setcolor(BLACK);
	    R = 0;
	}
	outtextxy(220,350,"Enter to Start");
	if(kbhit())
	{
	    int c = getch();
	    if(c == 0)
		getch();
	    else if(c == 13)
		break;
	}
	delay(100);
    }
     cleardevice();
}
///////////////////////////////////////////////////////////////////////////////////////////////
void bullet(int x, int y, int p)
{
    if (p) {
	setfillstyle(1, 6);
	setcolor(6);
    }
    else {
	setfillstyle(1, BLACK);
	setcolor(BLACK);
    }
    bar(x + 0, y + 5, x + 3, y + 15);
    pieslice(x + 2, y + 4, 0, 180, 1);
}
////////////////////////////////////////////////////////////////////////////////////////////
void mainmenu()
{
    fflush(stdin);
    int y = 250;
first:
    border(11);
    setcolor(RED);
    settextstyle(7,HORIZ_DIR,9);
    settextjustify(1, 1);
    outtextxy(330,50, "SAMURAI");
    outtextxy(330,140,"JACK");
    settextstyle(7,HORIZ_DIR,1);
    outtextxy(470,130,"(R)");
    settextstyle(2,HORIZ_DIR,9);
    settextjustify(1,1);
    outtextxy(300, 250, "START");
    outtextxy(300, 300, "HIGHSCORE");
    outtextxy(300, 350, "HELP");
    outtextxy(300, 400, "EXIT");
    char key;
    do {
	settextstyle(2,HORIZ_DIR, 9);
	menuAnim(130, y, 1, 1);
	key = getch();
	menuAnim(130, y, 0, 1);
	if (key == 80) //down
	{
	    if (y < 400)
		y += 50;
	    else
		y = 250;
	}
	else if (key == 72) //UP
	{
	    if (y > 250)
		y -= 50;
	    else
		y = 400;
	}
	else if (key == 13) //Enter key
	{
	    if (y == 250) {
		tcont = 0;
		if (!gameloaded)
		    name();
		life = 3;
		start();
		goto first;
	    }
	    else if (y == 300) {
		highscore();
		goto first;
	    }
	    else if (y == 350) {
		help();
		goto first;
	    }
	    else if (y == 400) {
		if (quit())
		    exit(0);
		goto first;
	    }
	}
    } while (1);
}
//////////////////////////////////////////////////////////////////////////////////
int quit()
{
    if (gameover(0))
	return 0;
    return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////
void plat(int x1, int y1, int l, int w)
{
    base[level][curbase].x1 = x1;
    base[level][curbase].y1 = y1;
    base[level][curbase].x2 = x1 + l;
    base[level][curbase].y2 = y1 + w;
    curbase++;
    nobase[level]++;
}
//////////////////////////////////////////////////////////////////////////////////////////////
void redrawplats()
{
    setfillstyle(1, 8);
    setcolor(BLACK);
    for (int i = 0; i < nobase[level]; i++) {
	if (i != nobase[level] - 1 && i != nobase[level] - 2) {
	    setfillstyle(1, BROWN);
	    bar(base[level][i].x1, base[level][i].y1, base[level][i].x2, base[level][i].y2);
	}
	char patt[] = { 0x95765, 0xabc214, 0x34723, 0xa3456 };
	setfillpattern(patt, GREEN);
	if (i == nobase[level] - 1 || i == nobase[level] - 2)
	    setfillpattern(patt, 6);
       bar(base[level][i].x1, base[level][i].y1, base[level][i].x2, base[level][i].y2 - (base[level][i].y2 - base[level][i].y1) / 3);
    }
    for (i = 0; i < noene[level]; i++) {
	if (ens[level][i].stat)
	    drawene(ens[level][i].x, ens[level][i].y, ens[level][i].bulldir);
    }
    if (door[level] && !stat)
	drawdoor(door[level]);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void thgenemy(int x, int y, int dir, int level, int no)
{
    if (!ens[level][no].scope || ens[level][no].scope && ens[level][no].stat) {
	drawene(x, y, dir);
	ens[level][no].x = x;
	ens[level][no].y = y;
	ens[level][no].bulldir = dir;
	ens[level][no].firestat = 0;
	ens[level][no].stat = 1;
	ens[level][no].scope = 1;
	noene[level]++;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
int gameover(int a)
{
    setcolor(WHITE);
    //rectangle(0,0,getmaxx(),getmaxy()-1);
    setcolor(BLACK);
    setfillstyle(0, WHITE);
    //bar(getmaxx() / 2 - 120, getmaxy() / 2 - 50, getmaxx() / 2 + 120, getmaxy() / 2 + 50);
    setcolor(YELLOW);
    setfillstyle(8, BLACK);
    bar(getmaxx() / 2 - 110, getmaxy() / 2 - 40, getmaxx() / 2 + 110, getmaxy() / 2 + 40);
    setcolor(RED);
    settextstyle(1, 0, 2);
    if (a)
	outtextxy(getmaxx() / 2 - 46, getmaxy() / 2 - 35, "GAME OVER!");
    settextstyle(2, 0, 6);
    setcolor(WHITE);
    if (a) {
	outtextxy(getmaxx() / 2, getmaxy() / 2, "Go to Menu(Y/N)");
	int i = 0;
	setcolor(BLACK);
	setfillstyle(1, BLACK);
	for (int xa = getmaxx() - 110, ya = 10; i < 9; i++, xa += 6) {
	    bar(xa + 0, ya + 0, xa + 5, ya + 10);
	    bar(xa + 0, ya + 0, xa + 4, ya + 9);
	}
    }
    else
    outtextxy(getmaxx() / 2, getmaxy() / 2, "Want to Quit(Y/N)");
    strcpy(scr.name, scr.name);
    while (1) {
	char key = getch();
	if (key == 'Y' || key == 'y') {
	    return 0;
	}
	if (key == 'n' || key == 'N')
	    break;
    }
    return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawgem(int x, int y, int level, int no, int p) //Drawing the GEM
{
    if (!gems[level][no].scope || gems[level][no].scope && gems[level][no].flag) {
	gems[level][no].scope = 1;
	int poly[10] = { x + 5, y + 0, x + 10, y + 5, x + 5, y + 15, x + 0, y + 5, x + 5, y + 0 };
	if (p == 7) {
	    setcolor(BLACK);
	    setfillstyle(1,3);
	    fillpoly(5, poly);
	    return;
	}
	if (p == 8) {
	    setcolor(BLACK);
	    setfillstyle(1,12);
	    fillpoly(5,poly);
	    return;
	}
	if (!p) {
	    gems[level][no].flag = 0;
	    setcolor(BLACK);
	    setfillstyle(1,0);
	    fillpoly(5, poly);
	    ofnog[stage]++;
	    scr.score += 5;
	    return;
	}
	gems[level][nogem[level]].x = x;
	gems[level][nogem[level]].y = y;
	gems[level][nogem[level]].flag = 1;
	nogem[level]++;
	setfillstyle(1, YELLOW);
	fillpoly(5, poly);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawruby(int x, int y, int level, int no, int p) //Drawing Ruby
{
    if (!rubys[level][no].scope || rubys[level][no].scope && rubys[level][no].flag) {
	rubys[level][no].scope = 1;
	int poly[10] = { x + 5, y + 0, x + 10, y + 5, x + 5, y + 15, x + 0, y + 5, x + 5, y + 0 };
	if (p == 7) {
	    setcolor(BLACK);
	    setfillstyle(1,BLACK);
	    fillpoly(5, poly);
	    return;
	}
	else if (p == 8) {
	    setcolor(BLACK);
	    setfillstyle(1,RED);
	    fillpoly(5, poly);
	    return;
	}
	if (!p) {
	    rubys[level][no].flag = 0;
	    setcolor(BLACK);
	    setfillstyle(1,BLACK);
	    fillpoly(5, poly);
	    ofnor[stage]++;
	    scr.score += 5;
	    return;
	}
	rubys[level][noruby[level]].x = x;
	rubys[level][noruby[level]].y = y;
	rubys[level][noruby[level]].flag = 1;
	noruby[level]++;
	setcolor(BLACK);
	setfillstyle(1, RED);
	fillpoly(5, poly);
    }
}
///////////////////////////////////////////////////////////////////////////////////////
void enemyclose(int level, int no, int x) //when enemy is hit
{
    scr.score += 10;
    for (int t = 0; t < 10; t++) {
	delay(10);
	erasehero(ens[level][no].x, ens[level][no].y, 9, ens[level][no].bulldir);
	if (ens[level][no].x < x)
	    ens[level][no].x -= 5;
	else
	    ens[level][no].x += 5;
	drawene(ens[level][no].x, ens[level][no].y, ens[level][no].bulldir);
    }
    for (int i = 50; i > 0;) {
	setcolor(RED);
	setfillstyle(1, RED);
	pieslice(ens[level][no].x, ens[level][no].y, 0, 360, i);
	delay(5);
	setfillstyle(1, BLACK);
	setcolor(BLACK);
	pieslice(ens[level][no].x, ens[level][no].y, 0, 360, i);
	i--;
    }
    firestat = 0;
    ens[level][no].stat = 0;
    setcolor(BLACK);
    setfillstyle(1, BLACK);
    int blaze[][8] = { { ens[level][no].bullx + 0, ens[level][no].bully + 4,
			   ens[level][no].bullx + 4, ens[level][no].bully + 0, ens[level][no].bullx + 8,
			   ens[level][no].bully + 4, ens[level][no].bullx + 4, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 1, ens[level][no].bully + 2, ens[level][no].bullx + 4,
	    ens[level][no].bully + 0, ens[level][no].bullx + 8, ens[level][no].bully + 6,
	    ens[level][no].bullx + 5, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 0, ens[level][no].bully + 0, ens[level][no].bullx + 5,
	    ens[level][no].bully + 4, ens[level][no].bullx + 3, ens[level][no].bully + 8,
	    ens[level][no].bullx + 3, ens[level][no].bully + 4 },
	{ ens[level][no].bullx + 6, ens[level][no].bully + 0, ens[level][no].bullx + 4,
	    ens[level][no].bully + 5, ens[level][no].bullx + 0, ens[level][no].bully + 5,
	    ens[level][no].bullx + 3, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 7, ens[level][no].bully + 0, ens[level][no].bullx + 4,
	    ens[level][no].bully + 4, ens[level][no].bullx + 0, ens[level][no].bully + 1,
	    ens[level][no].bullx + 3, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 3, ens[level][no].bully + 0, ens[level][no].bullx + 0,
	    ens[level][no].bully + 4, ens[level][no].bullx + 3, ens[level][no].bully + 7,
	    ens[level][no].bullx + 2, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 7, ens[level][no].bully + 3, ens[level][no].bullx + 4,
	    ens[level][no].bully + 0, ens[level][no].bullx + 0, ens[level][no].bully + 5,
	    ens[level][no].bullx + 2, ens[level][no].bully + 2 } };
    fillpoly(4, blaze[ens[level][no].blano]);
    int blaz[][8] = { { bullx + 0, bully + 4, bullx + 4, bully + 0, bullx + 8, bully + 4, bullx + 4,
			  bully + 3 },
	{ bullx + 1, bully + 2, bullx + 4, bully + 0, bullx + 8, bully + 6, bullx + 5, bully + 3 },
	{ bullx + 0, bully + 0, bullx + 5, bully + 4, bullx + 3, bully + 8, bullx + 3, bully + 4 },
	{ bullx + 6, bully + 0, bullx + 4, bully + 5, bullx + 0, bully + 5, bullx + 3, bully + 3 },
	{ bullx + 7, bully + 0, bullx + 4, bully + 4, bullx + 0, bully + 1, bullx + 3, bully + 3 },
	{ bullx + 3, bully + 0, bullx + 0, bully + 4, bullx + 3, bully + 7, bullx + 2, bully + 3 },
	{ bullx + 7, bully + 3, bullx + 4, bully + 0, bullx + 0, bully + 5, bullx + 2, bully + 2 } };
    setcolor(BLACK);
    setfillstyle(1, BLACK);
    fillpoly(4, blaz[blano]);
}
///////////////////////////////////////////////////////////////////////////////////////
void heroclose(int x,int y) //when hero dies
{
    for (int i = 50; i > 0;) {
	setcolor(i % 50);
	setfillstyle(1, RED);
	pieslice(x, y, 0, 360, i);
	delay(5);
	setfillstyle(1, BLACK);
	setcolor(BLACK);
	pieslice(x, y, 0, 360, i);
	i--;
    }
    firestat = 0;
    setcolor(BLACK);
    setfillstyle(1, BLACK);
    int blaz[][8] = { { bullx + 0, bully + 4, bullx + 4, bully + 0, bullx + 8, bully + 4, bullx + 4,
			  bully + 3 },
	{ bullx + 1, bully + 2, bullx + 4, bully + 0, bullx + 8, bully + 6, bullx + 5, bully + 3 },
	{ bullx + 0, bully + 0, bullx + 5, bully + 4, bullx + 3, bully + 8, bullx + 3, bully + 4 },
	{ bullx + 6, bully + 0, bullx + 4, bully + 5, bullx + 0, bully + 5, bullx + 3, bully + 3 },
	{ bullx + 7, bully + 0, bullx + 4, bully + 4, bullx + 0, bully + 1, bullx + 3, bully + 3 },
	{ bullx + 3, bully + 0, bullx + 0, bully + 4, bullx + 3, bully + 7, bullx + 2, bully + 3 },
	{ bullx + 7, bully + 3, bullx + 4, bully + 0, bullx + 0, bully + 5, bullx + 2, bully + 2 } };
    fillpoly(4, blaz[blano]);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void hithero(int level, int no, int x, int y) //when hero is hit
{
    setcolor(BLACK);
    setfillstyle(1, BLACK);
    int blaze[][8] = { { ens[level][no].bullx + 0, ens[level][no].bully + 4,
			   ens[level][no].bullx + 4, ens[level][no].bully + 0, ens[level][no].bullx + 8,
			   ens[level][no].bully + 4, ens[level][no].bullx + 4, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 1, ens[level][no].bully + 2, ens[level][no].bullx + 4,
	    ens[level][no].bully + 0, ens[level][no].bullx + 8, ens[level][no].bully + 6,
	    ens[level][no].bullx + 5, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 0, ens[level][no].bully + 0, ens[level][no].bullx + 5,
	    ens[level][no].bully + 4, ens[level][no].bullx + 3, ens[level][no].bully + 8,
	    ens[level][no].bullx + 3, ens[level][no].bully + 4 },
	{ ens[level][no].bullx + 6, ens[level][no].bully + 0, ens[level][no].bullx + 4,
	    ens[level][no].bully + 5, ens[level][no].bullx + 0, ens[level][no].bully + 5,
	    ens[level][no].bullx + 3, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 7, ens[level][no].bully + 0, ens[level][no].bullx + 4,
	    ens[level][no].bully + 4, ens[level][no].bullx + 0, ens[level][no].bully + 1,
	    ens[level][no].bullx + 3, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 3, ens[level][no].bully + 0, ens[level][no].bullx + 0,
	    ens[level][no].bully + 4, ens[level][no].bullx + 3, ens[level][no].bully + 7,
	    ens[level][no].bullx + 2, ens[level][no].bully + 3 },
	{ ens[level][no].bullx + 7, ens[level][no].bully + 3, ens[level][no].bullx + 4,
	    ens[level][no].bully + 0, ens[level][no].bullx + 0, ens[level][no].bully + 5,
	    ens[level][no].bullx + 2, ens[level][no].bully + 2 } };
    fillpoly(4, blaze[ens[level][no].blano]);
    ens[level][no].firestat = 0;
    int xa = getmaxx() - 110, ya = 10;
    for (int i = 0; i < health; i++, xa += 6) {
	setcolor(BLACK);
	setfillstyle(1, BLACK);
	bar(xa + 0, ya + 0, xa + 5, ya + 10);
	bar(xa + 0, ya + 0, xa + 4, ya + 9);
    }
    xa = getmaxx() - 300, ya = 0;
    health -= chhealth;
    chhealth = 0;
    if (health <= 0) {
	life--;
	health = 9;
	heroclose(x,y);
	excuse = 1;
    }
    for (i = 0, xa = getmaxx() - 110, ya = 10; i < health; i++, xa += 6) //Health Logo
	{
	setcolor(WHITE);
	setfillstyle(1, 9);
	bar(xa + 0, ya + 0, xa + 5, ya + 10);
	setfillstyle(1, 12);
	bar(xa + 0, ya + 0, xa + 4, ya + 9);
    }
    setcolor(BLACK);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawdoor(int a) //drawing the door
{
    if (a)
	door[level] = a;
    if (a == 1) {
	setcolor(BLACK);
	setfillstyle(1,WHITE);
	bar(0, getmaxy() - 60, 5, getmaxy());
	setfillstyle(1,LIGHTRED);
	setcolor(LIGHTRED);
	fillellipse(3, getmaxy() - 35, 2, 3);
    }
    else if (a == 2) {
	setcolor(BLACK);
	setfillstyle(1, WHITE);
	bar(getmaxx() - 5, getmaxy() - 60, getmaxx(), getmaxy()-11);
	setfillstyle(1,LIGHTRED);
	setcolor(LIGHTRED);
	fillellipse(getmaxx() - 3, getmaxy() - 35, 2, 3);
    }
    else {
	setcolor(BLACK);
	setfillstyle(1,BLACK);
	if (door[level] == 1) {
	    bar(0, getmaxy() - 60, 5, getmaxy());
	    fillellipse(1, getmaxy() - 30, 2, 4);
	}
	else {
	    bar(getmaxx() - 6, getmaxy() - 60, getmaxx(), getmaxy());
	    fillellipse(1, getmaxy() - 30, 2, 4);
	}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void start()//Main Game Function
{ //initiallizing
    for (int clr = 0; clr < 10; clr++)
	for (int cl = 0; cl < 10; cl++) {
	    ens[clr][cl].scope = 0;
	    gems[clr][cl].scope = 0;
	    rubys[clr][cl].scope = 0;
	    ofnog[clr] = 0;
	    ofnor[clr] = 0;
	    ofnoe[clr] = 0;
	}
    int x = 100, y = 300, wlkdir = 1, excnt = 0;
    excuse = 1;
    do {
	cleardevice();
	if (level == 1) {
	    stat = 0;
	    nobase[level] = 1;
	    nogem[level] = 0;
	    noruby[level] = 0;
	    curbase = 0;
	    plat(300, 240, 100, 10);//plat3
	    plat(80, 250, 120, 10);//gemplat
	    plat(250, 320, 100, 10);//plat1
	    plat(350, 400, 100, 20);//groundplat
	    plat(200, 170, 100, 10);//plat2
	    plat(460, 200, 100, 10);//rubyplat
	    plat(0, getmaxy() - 10, getmaxx(), getmaxy());//ground
	    drawgem(130, 220, level, 0, 1);
	    drawgem(240, 140, level, 0, 1);
	    drawruby(500, 165, level, 0, 1);
	    drawdoor(2);
	    if (!tcont)
		eltime= 60;
	    ofnoruby[stage] = 1;
	    ofnogem[stage] = 2;
	}
	if (level == 2) {
	    stat = 0;
	    nobase[level] = 1;
		nogem[level] = 0;
		noruby[level] = 0;
	    curbase = 0;
	    plat(300, 200, 100, 10);
	    plat(70, 280, 100, 10);
	    plat(300, 350, 130, 15);
	    plat(200, 400, 100, 20);
	    plat(400, 270, 100, 20);
	    plat(530, 190, 50, 10);
	    plat(0, getmaxy() - 10, getmaxx(), getmaxy());
	    drawgem(120, 195, level, 0, 1);
	    thgenemy(540, 190 - height, 0, level, 0);
	    drawdoor(2);
	    if (!tcont)
	    eltime = 120;
	    ofnoene[stage] = 1;
	    ofnogem[stage] = 1;
	}
	if (level == 3) {
	    stat = 0;
	    nobase[level] = 1;
		nogem[level] = 0;
	    noruby[level] = 0;
	    curbase = 0;
	    plat(100, 100, 400, 10);
	    plat(400, 480, 100, 10);
	    plat(300, 350, 130, 15);
	    plat(200, 400, 100, 20);
	    plat(400, 270, 100, 20);
	    plat(530, 190, 50, 10);
	    plat(10, 300, 30, 10);
	    plat(0, getmaxy() - 10, getmaxx(), getmaxy());
	    drawgem(120, 195, level, 0, 1);
		drawgem(100,150,level,0,1);
	    drawgem(220, 275, level, 0, 1);
	    thgenemy(540, 190 - height, 0, level, 0);
	    thgenemy(20, 300 - height, 1, level, 1);
		drawruby(140,215,level,0,1);
		drawdoor(2);
	    if (!tcont)
		eltime = 120;
	    ofnoene[stage] = 2;
	    ofnogem[stage] = 3;
	    ofnoruby[stage] = 1;
	}
	
	char ch;
	int jumpflag = 0, jumpcnt = 0, jumpup = 0, bulldir, b = 0, statchange = 1, bflag = 0;
	hithero(level, 0, x, y);
	//game loop
	do {
	    ctim = time(NULL);
	    if (statchange) //display the player name etc
	    {
		setcolor(BLACK);
		setfillstyle(1, BLACK);
		bar(getmaxx() - 240, 8, getmaxx() - 190, 30);
		bar(getmaxx() - 360, 8, getmaxx() - 280, 30);
		char buf[20] = "Life : ";
		buf[7] = life + 48;
		buf[8] = '\0';
		setcolor(CYAN);
		settextstyle(2, 0, 6);
		outtextxy(getmaxx() - 240, 15, buf);
		outtextxy(getmaxx() - 150, 15, "Health");
		outtextxy(getmaxx() - 360, 15, "Score :");
		sprintf(buf, "%d", scr.score);
		outtextxy(getmaxx() - 310, 15, buf);
		int xa = getmaxx() - 110, ya = 10;
		for (int i = 0; i < health; i++, xa += 6) {
		    setcolor(BLACK);
		    setfillstyle(1, BLACK);
		    bar(xa + 0, ya + 0, xa + 5, ya + 10);
		    bar(xa + 0, ya + 0, xa + 4, ya + 9);
		}
		health -= chhealth;
		chhealth = 0;
		if (health <= 0) {
		    life--;
		    health = 9;
		    lifeup = 1;
		    heroclose(x,y);
		    excuse = 1;
		    break;
		}
		/////////////////////////////////////////////////
		for (i = 0, xa = getmaxx() - 110, ya = 10; i < health; i++, xa += 6) {
		    setcolor(BLACK);
		    setfillstyle(1, 9);
		    bar(xa + 0, ya + 0, xa + 5, ya + 10);
		    setfillstyle(1, 4);
		    bar(xa + 0, ya + 0, xa + 4, ya + 9);
		}
		setfillstyle(1, BLACK);
		setcolor(YELLOW);
		settextstyle(2, 0, 6);
		bar(5, 5, getmaxx() - 400, 100);
		if (ofnogem[stage] == ofnog[stage] && ofnoruby[stage] == ofnor[stage]) {
		    setfillstyle(1, BLACK);
		    setcolor(RED);
		    settextstyle(2, 0, 6);
		    bar(5, 5, getmaxx() - 400, 100);
		    stat = 1;
		    outtextxy(160, 15, "Level Clear!");
		    drawdoor(0);
		}
		else {
		    sprintf(buf, "Level :0%d", stage + 1);
		    outtextxy(174, 15, buf);
		}
		setcolor(BLACK);
		setfillstyle(1, BLACK);
		bar(10, 10, 100, 29);
		setcolor(WHITE);
		setfillstyle(1, WHITE);
		settextstyle(2, 0, 6);
		outtextxy(50, 15, scr.name);
		statchange = 0;
	    }
	    delay(20);
	    redrawplats();
	    for ( int t = 0; t < noene[level]; t++)//when colliding
		{
		if (!ens[level][t].stat)
		    continue;
		if (x + 20 > ens[level][t].x && x < ens[level][t].x + 20 && y > ens[level][t].y
		    && y < ens[level][t].y + height) {
		    life--;
		    health = 9;
		    statchange = 1;
		    chhealth = 0;
		    heroclose(x,y);
		    enemyclose(level, t, x);
		    excuse = 1;
		    ens[level][t].stat = 0;
		}
	    }
	    if (y > getmaxy()) {
		erasehero(x, y, post, hdir);
		heroclose(x,y);
		excuse = 1;
	    } //hero out
	    if (excuse) {
		if (excnt == 0) {
		    erasehero(x, y, post, hdir);
		    x = 10;
		    y = getmaxy() - 100;
		    post = 0;
		    hdir = 1;
		}
		if (excnt % 5 == 0)
		    erasehero(x, y, post, hdir);
		if (excnt % 5 == 10)
		    drawhero(x, y, post, hdir);
		excnt++;
		if (excnt > 2) {
		    excuse = 0;
		    excnt = 0;
		}
	    }
	    for (t = 0; t < nogem[level]; t++)//for hero taking the ruby and gems 
		{
		if (gems[level][t].flag)
		    if (x > gems[level][t].x - 20 && x < gems[level][t].x + 20 && gems[level][t].y < y + height
			&& gems[level][t].y + 5 > y) {
			drawgem(gems[level][t].x, gems[level][t].y, level, t, 0);
			statchange = 1;
			scr.score += 5;
		    }
	    }
	    for (t = 0; t < noruby[level]; t++) 
		{
		if (rubys[level][t].flag)
		    if (x > rubys[level][t].x - 20 && x < rubys[level][t].x + 20 && rubys[level][t].y < y + height && rubys[level][t].y > y) {
			drawruby(rubys[level][t].x, rubys[level][t].y, level, t, 0);
			statchange = 1;
			scr.score += 10;
		    }
	    }
	    for (t = 0; t < noene[level]; t++)//for detecting hero by the enemy 
		{
		if (!ens[level][t].stat)
		    continue;
		if (y < ens[level][t].y + height + 20 && y > ens[level][t].y - 20) //vertically near
		{ ///////change dir of ene
		    if (x < ens[level][t].x && ens[level][t].bulldir || x > ens[level][t].x && !ens[level][t].bulldir) {
			erasehero(ens[level][t].x, ens[level][t].y, 9, ens[level][t].bulldir);
			ens[level][t].bulldir = !ens[level][t].bulldir;
			drawene(ens[level][t].x, ens[level][t].y, ens[level][t].bulldir);
		    }
		    ///////fire
		    if (!ens[level][t].firestat) {
			ens[level][t].bully = ens[level][t].y + height / 2;
			ens[level][t].bullx = ens[level][t].x;
			if (x < ens[level][t].x)
			    ens[level][t].bullfired = 0;
			else
			    ens[level][t].bullfired = 1;
		    }
		    ens[level][t].firestat = 1;
		}
	    } //end of do
	    //for firing bullet of the hero
	    if (firestat) {
		{
		    int blaz[][8] = { { bullx + 0, bully + 4, bullx + 4, bully + 0, bullx + 8, bully + 4,
					  bullx + 4, bully + 3 },
			{ bullx + 1, bully + 2, bullx + 4, bully + 0, bullx + 8, bully + 6,
			    bullx + 5, bully + 3 },
			{ bullx + 0, bully + 0, bullx + 5, bully + 4, bullx + 3, bully + 8,
			    bullx + 3, bully + 4 },
			{ bullx + 6, bully + 0, bullx + 4, bully + 5, bullx + 0, bully + 5,
			    bullx + 3, bully + 3 },
			{ bullx + 7, bully + 0, bullx + 4, bully + 4, bullx + 0, bully + 1,
			    bullx + 3, bully + 3 },
			{ bullx + 3, bully + 0, bullx + 0, bully + 4, bullx + 3, bully + 7,
			    bullx + 2, bully + 3 },
			{ bullx + 7, bully + 3, bullx + 4, bully + 0, bullx + 0, bully + 5,
			    bullx + 2, bully + 2 } };
		    setcolor(BLACK);
		    setfillstyle(1, BLACK);
		    fillpoly(4, blaz[blano]);
		}
		if (bulldir)
		    bullx += 8;
		else
		    bullx -= 8;
		setfillstyle(1, WHITE);
		blano++;
		if (blano == 6)
		    blano = 0;
		{
		    int blaz[][8] = { { bullx + 0, bully + 4, bullx + 4, bully + 0, bullx + 8, bully + 4,
					  bullx + 4, bully + 3 },
			{ bullx + 1, bully + 2, bullx + 4, bully + 0, bullx + 8, bully + 6,
			    bullx + 5, bully + 3 },
			{ bullx + 0, bully + 0, bullx + 5, bully + 4, bullx + 3, bully + 8,
			    bullx + 3, bully + 4 },
			{ bullx + 6, bully + 0, bullx + 4, bully + 5, bullx + 0, bully + 5,
			    bullx + 3, bully + 3 },
			{ bullx + 7, bully + 0, bullx + 4, bully + 4, bullx + 0, bully + 1,
			    bullx + 3, bully + 3 },
			{ bullx + 3, bully + 0, bullx + 0, bully + 4, bullx + 3, bully + 7,
			    bullx + 2, bully + 3 },
			{ bullx + 7, bully + 3, bullx + 4, bully + 0, bullx + 0, bully + 5,
			    bullx + 2, bully + 2 } };
		    fillpoly(4, blaz[blano]);
		}
		if (bullx > getmaxx() + 3 || bullx < -3)
		    firestat = 0;
		//if the bullet hits the enemy
		for (t = 0; t < noene[level]; t++) {
		    if (!ens[level][t].stat)
			continue;
		    if (bullx > ens[level][t].x && bullx < ens[level][t].x + 20
			&& bully > ens[level][t].y && bully < ens[level][t].y + height) {
			enemyclose(level, t, x);
			statchange = 1;
		    }
		}
	    }
	    //Checking the landing plat
	    if (jumpflag) {
		for (int t = 0; t < nobase[level]; t++) {
		    if (jumpup) //when the hero hits his head in the plat
			if (y - 3 < base[level][t].y2 && y + 3 > base[level][t].y2
			    && x + 10 > base[level][t].x1 && x + 12 < base[level][t].x2)
			    jumpup = 0;
		    if (y + height < base[level][t].y1 + 3 && y + height > base[level][t].y1 - 3
			&& x + 10 > base[level][t].x1 && x + 3 < base[level][t].x2 && !jumpup) //landed on base
		    {
			jumpflag = 0;
			curbase = t;
		    }
		}
	    }
	    else if (x + 12 < base[level][curbase].x1 || x + 4 > base[level][curbase].x2 && curbase >= 0) //when d hero steps out of d plat
	    {
		jumpflag = 1;
		jumpup = 0;
		if (curmov >= 0)
		    curmov = -1;
	    }
	    //for firing bullet of the enemy
	    for (t = 0; t < noene[level]; t++) {
		if (!ens[level][t].stat)
		    continue;
		if (ens[level][t].firestat) {
		    setcolor(BLACK);
		    setfillstyle(1, BLACK);
		    {
			int blaze[][8] = { { ens[level][t].bullx + 0, ens[level][t].bully + 4,
					       ens[level][t].bullx + 4, ens[level][t].bully + 0, ens[level][t].bullx + 8,
					       ens[level][t].bully + 4, ens[level][t].bullx + 4, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 1, ens[level][t].bully + 2, ens[level][t].bullx + 4,
				ens[level][t].bully + 0, ens[level][t].bullx + 8, ens[level][t].bully + 6,
				ens[level][t].bullx + 5, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 0,
				ens[level][t].bully + 0, ens[level][t].bullx + 5, ens[level][t].bully + 4,
				ens[level][t].bullx + 3, ens[level][t].bully + 8, ens[level][t].bullx + 3,
				ens[level][t].bully + 4 },
			    { ens[level][t].bullx + 6, ens[level][t].bully + 0,
				ens[level][t].bullx + 4, ens[level][t].bully + 5, ens[level][t].bullx + 0,
				ens[level][t].bully + 5, ens[level][t].bullx + 3, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 7, ens[level][t].bully + 0, ens[level][t].bullx + 4,
				ens[level][t].bully + 4, ens[level][t].bullx + 0, ens[level][t].bully + 1,
				ens[level][t].bullx + 3, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 3,
				ens[level][t].bully + 0, ens[level][t].bullx + 0, ens[level][t].bully + 4,
				ens[level][t].bullx + 3, ens[level][t].bully + 7, ens[level][t].bullx + 2,
				ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 7, ens[level][t].bully + 3,
				ens[level][t].bullx + 4, ens[level][t].bully + 0, ens[level][t].bullx + 0,
				ens[level][t].bully + 5, ens[level][t].bullx + 2, ens[level][t].bully + 2 } };
			fillpoly(4, blaze[ens[level][t].blano]);
		    }
		    if (ens[level][t].bullfired)
			ens[level][t].bullx += 8;
		    else
			ens[level][t].bullx -= 8;
		    setfillstyle(1, 8);
		    ens[level][t].blano++;
		    if (ens[level][t].blano == 6)
			ens[level][t].blano = 0;
		    {
			int blaze[][8] = { { ens[level][t].bullx + 0, ens[level][t].bully + 4,
					       ens[level][t].bullx + 4, ens[level][t].bully + 0, ens[level][t].bullx + 8,
					       ens[level][t].bully + 4, ens[level][t].bullx + 4, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 1, ens[level][t].bully + 2, ens[level][t].bullx + 4,
				ens[level][t].bully + 0, ens[level][t].bullx + 8, ens[level][t].bully + 6,
				ens[level][t].bullx + 5, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 0, ens[level][t].bully + 0,
				ens[level][t].bullx + 5, ens[level][t].bully + 4, ens[level][t].bullx + 3,
				ens[level][t].bully + 8, ens[level][t].bullx + 3, ens[level][t].bully + 4 },
			    { ens[level][t].bullx + 6, ens[level][t].bully + 0, ens[level][t].bullx + 4,
				ens[level][t].bully + 5, ens[level][t].bullx + 0, ens[level][t].bully + 5,
				ens[level][t].bullx + 3, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 7, ens[level][t].bully + 0, ens[level][t].bullx + 4,
				ens[level][t].bully + 4, ens[level][t].bullx + 0, ens[level][t].bully + 1,
				ens[level][t].bullx + 3, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 3, ens[level][t].bully + 0, ens[level][t].bullx + 0,
				ens[level][t].bully + 4, ens[level][t].bullx + 3, ens[level][t].bully + 7,
				ens[level][t].bullx + 2, ens[level][t].bully + 3 },
			    { ens[level][t].bullx + 7, ens[level][t].bully + 3, ens[level][t].bullx + 4,
				ens[level][t].bully + 0, ens[level][t].bullx + 0, ens[level][t].bully + 5,
				ens[level][t].bullx + 2, ens[level][t].bully + 2 } };
			fillpoly(4, blaze[ens[level][t].blano]);
		    }
		    if (ens[level][t].bullx > getmaxx() + 3 || ens[level][t].bullx < 0)
			ens[level][t].firestat = 0;
		    //if d bullet hits the hero
		    if (ens[level][t].bullx > x && ens[level][t].bullx < x + 20
			&& ens[level][t].bully > y && ens[level][t].bully < y + height) {
			jumpflag = 1;
			jumpup = 1;
			erasehero(x, y, post, hdir);
			y -= 20;
			if (x > ens[level][t].x) {
			    hdir = 1;
			    wlkdir = 1;
			}
			else {
			    hdir = 0;
			    wlkdir = 0;
			}
			drawhero(x, y, post, hdir);
			chhealth = 4;
			statchange = 1;
			hithero(level, t, x, y);
			statchange = 1;
		    }
		}
	    }
	    if (jumpflag)//Jumping
		{
		if (lpass[level] && x < 3) {
		    throughl = 1;
		    break;
		}
		if (rpass[level] && x + 30 > getmaxx()) {
		    throughr = 1;
		    break;
		}
		erasehero(x, y, post, hdir);
		if (!lpass[level] && x < 3) {
		    wlkdir = 1;
		    hdir = 1;
		}
		if (!rpass[level] && x + 30 > getmaxx()) {
		    wlkdir = 0;
		    hdir = 0;
		}
		setcolor(BLACK);
		jumpcnt++;
		if (jumpcnt > 20)
		    jumpup = 0;
		if (jumpup) {
		    y -= 5;
		    if (wlkdir)
			x += 3;
		    else
			x -= 3;
		    drawhero(x, y, post, hdir);
		}
		else {
		    y += 5;
		    if (wlkdir)
			x += 3;
		    else
			x -= 3;
		    drawhero(x, y, post, hdir);
		}
	    }
	    if (kbhit() && !excuse) {
		ch = getch();
		if (ch == ' ' && !firestat) {
		    firestat = 1;
		    bulldir = hdir;
		    bully = y + height / 2;
		    if (hdir)
			bullx = x + 20;
		    else
			bullx = x;
		}
		if (ch == 27) {
		    if (quit()) {
			bflag = 1;
			level = 1;
			stage = 0;
			tcont = 0;
			gameloaded = 0;
			scr.score = 0;
			return;
		    }
		    setcolor(BLACK);
		    setfillstyle(1, BLACK);
		    bar(getmaxx() / 2 - 120, getmaxy() / 2 - 50, getmaxx() / 2 + 120, getmaxy() / 2 + 50);
		}
		if (ch == 75) //LEFT
		{
		    if (door[level] == 1 && x <= 3 && y > getmaxy() - 70) {
			if (stat) {
			    b = 1;
			    throughdoor = 1;
			    y = getmaxy() - 100;
			    break;
			}
			else
			    continue;
		    }
		    if (!lpass[level] && x <= 10)
			continue;
		    else if (x < 3 && lpass[level]) {
			b = 1;
			throughl = 1;
		    }
		    if (hdir) //if the hero turns back
			erasehero(x, y, post, hdir);
		    hdir = 0;
		    wlkdir = 0;
		    if (!jumpflag) {
			erasehero(x, y, post, hdir);
			x -= 10;
			post += 1;
			drawhero(x, y, post, hdir);
		    }
		}
		if (ch == 77) //RIGHT
		{
		    if (door[level] == 2 && x + 25 > getmaxx() && y > getmaxy() - 70) {
			if (stat) {
			    b = 1;
			    throughdoor = 1;
			    y = getmaxy() - 100;
			    break;
			}
			else
			    continue;
		    }
		    if (x + 25 > getmaxx() && !rpass[level])
			continue;
		    else if (x + 25 > getmaxx() && rpass[level]) {
			b = 1;
			throughr = 1;
		    }
		    if (hdir == 0) //if the hero turns back
			erasehero(x, y, post, hdir);
		    hdir = 1;
		    wlkdir = 1;
		    if (!jumpflag) {
			erasehero(x, y, post, hdir);
			x += 10;
			post += 1;
			drawhero(x, y, post, hdir);
		    }
		}
		if (ch == 72) //UP
		{
		    if (!lpass[level] && x < 3)
			continue;
		    if (!rpass[level] && x + 25 > getmaxx())
			continue;
		    if (!jumpflag) {
			curmov = -1;
			jumpcnt = 0;
			jumpflag = 1;
			jumpup = 1;
		    }
		}
	    }
	    if (b) {
		b = 0;
		break;
	    }
	    if (difftime(ctim, otim) >= 1) {
		eltime--;
		setcolor(RED);
		otim = ctim;
		sprintf(curtime, "%d", eltime);
		setcolor(BLACK);
		setfillstyle(1, BLACK);
		bar(getmaxx() - 10, 10, getmaxx() - 50, 30);
		setcolor(WHITE);
		outtextxy(getmaxx() - 30, 15, curtime);
		if (eltime <= 0 || life == 0)
		    if (gameover(1)) {
			life = 3;
			bflag = 0;
			level = 1;
			stage = 0;
			y = getmaxy() - 100;
			x = 100;
			tcont = 0;
			for (int clr = 0; clr < 10; clr++)
			    for (int cl = 0; cl < 10; cl++) {
				ens[clr][cl].scope = 0;
				gems[clr][cl].scope = 0;
				rubys[clr][cl].scope = 0;
				ofnog[clr] = 0;
				ofnor[clr] = 0;
				ofnoe[clr] = 0;
			    }
			break;
		    }
		    else {
			life = 3;
			bflag = 1;
			level = 1;
			stage = 0;
			tcont = 0;
			break;
		    }
	    }
	} while (1);
	if (bflag) {
	    tcont = 0;
	    return;
	}
	if (throughdoor) {
	    level++;
	    x = 20;
	    y = getmaxy() - 100;
	    stat = 0;
	    success(stage);
	    stage++;
	    tcont = 0;
	    save(stage);
	}
	else if (throughr) {
	    level++;
	    x = 20;
	    y -= 10;
	    tcont = 1;
	}
	else if (throughl) {
	    y -= 10;
	    level--;
	    x = getmaxx() - 50;
	    tcont = 1;
	}
	throughr = 0;
	throughl = 0;
	throughdoor = 0;
    } while (1);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void name()
{
    cleardevice();
    border(0);
    setcolor(CYAN);
    outtextxy(getmaxx() / 2, 200, "Enter Your Name.");
    char key, name[100] = "";
     int j = 0, x = getmaxx() / 2 - 100, y = 300;
    setfillstyle(1, WHITE);
    setcolor(WHITE);
    while (1) {
	key = getch();
	if (key == 8 && j > 0) {
	    setcolor(BLACK);
	    setfillstyle(1, BLACK);
	    bar(x - 30, y - 30, x, y + 30);
	    x -= 20;
	    setcolor(WHITE);
	    setfillstyle(1, WHITE);
	}
	char buf[3];
	buf[0] = key;
	buf[1] = '\0';
	if (key != 8 && j >= 0) {
	    outtextxy(x, y, buf);
	    x += 20;
	}
	if (isalnum(key)) {
	    name[j] = key;
	    name[j + 1] = '\0';
	    j++;
	}
	else if (key == 13)
	    break;
	if (key == 8 && j > 0)
	    j--;
    }
    strcpy(scr.name, name);
    scr.name[0] = toupper(scr.name[0]);
    scr.name[14] = '\0';
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void success(int a)
{
    cleardevice();
    border(0);
    settextstyle(2, 0, 8);
    setcolor(CYAN);
    outtextxy(310,200, "CONGRATULATIONS");
    setcolor(WHITE);
    char buf[50] = "YOU HAVE SUCCESSFULLY COMPLETED LEVEL ";
    buf[38] = a + 49;
    buf[39] = '\0';
    settextstyle(2, 0, 7);
    if (stage == 5){
	 outtextxy(310, getmaxy() / 2 + 20, "||YOU WON THE GAME||");
	 delay(2000);
	}
    else
	outtextxy(getmaxx() / 2, getmaxy() / 2 + 20, buf);
    delay(3000);
    cleardevice();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void highscore()
{
    cleardevice();
    border(0);
    setcolor(WHITE);
	settextstyle(2,HORIZ_DIR,9);
    ifstream fin(filedir, ios::binary);
    score tmp[7], t;
    int i = 0;
    if (!fin) {
	outtextxy(300, 200, "File NOT Found!");
	getch();
	fin.close();
	return;
    }
    while (fin.read((char*)&tmp[i], sizeof(tmp[0]))) {
	i++;
	if (i >= 7)
	    break;
    }
    for (int k = 0; k < i - 1; k++)
	for (int j = 0; j < i - k - 1; j++)
	    if (tmp[j].score < tmp[j + 1].score) {
		t = tmp[j];
		tmp[j] = tmp[j + 1];
		tmp[j + 1] = t;
	    }
    txtAnim(210, 100, "HIGH SCORES");
    setcolor(WHITE);
	txtAnim(100, 200, "NAME");
    txtAnim(400, 200, "SCORE");
    int y = 210;
    setcolor(LIGHTCYAN);
    for (k = 0; k < i; k++) {
	txtAnim(100, y += 35, tmp[k].name);
	char buff[5];
	sprintf(buff, "%i", tmp[k].score);
	txtAnim(400, y, buff);
    }
    fin.close();
    getch();
    cleardevice();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void help()
{
    cleardevice();
    border(0);
    char a[20][100] = { "HELP", "Collect all the items present in each level ",
	"to proceed to the next level.", "Kill all the enemies to gain extra points.",
	"CONTROLS", "Move Left: LEFT ARROW", "Move Right: RIGHT ARROW",
	"Jump: UP ARROW", "Shoot: SPACE BAR", "QUIT: ESC", "ALL THE BEST" };
    settextjustify(1, 1);
    settextstyle(2, 0, 9);
    setcolor(7);
    txtAnim(275, 100, a[0]);
    settextstyle(2, 0, 6);
    setcolor(YELLOW);
    outtextxy(getmaxx() / 2, 100, a[1]);
    delay(100);
    outtextxy(getmaxx() / 2, 130, a[2]);
    delay(50);
    outtextxy(getmaxx() / 2, 160, a[3]);
    delay(200);
    settextstyle(2, 0, 9);
    setcolor(7);
    txtAnim(240, 270, a[4]);
    setcolor(LIGHTRED);
    settextstyle(2, 0, 6);
    outtextxy(getmaxx() / 2+6, 270, a[5]);
    delay(50); //left
    outtextxy(getmaxx() / 2+4, 300, a[6]);
    delay(50); //right
    outtextxy(getmaxx() / 2+18, 330, a[7]);
    delay(50); //jump
    outtextxy(getmaxx() / 2+18, 360, a[8]);
    delay(50); //shoot
    outtextxy(getmaxx() / 2-8, 390, a[9]);
    delay(50); //quit
    settextstyle(2, 0, 5);
    setcolor(3);
    txtAnim(150 + 220, 450, a[10]);
    getch();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void save(int a)
{
    fflush(stdin);
    char ch;
    a=stage;
    cleardevice();
    txtAnim(50, 100, "Press Enter");
    do {
	ch = getch();
    } while (ch != 13);
    cleardevice();
    border(0);
    settextstyle(2, 0, 8);
    txtAnim(80, 200, "Do you want to save the game(Y/N)?");
    ch = getch();
    ofstream fout(filedir, ios::binary | ios::ate);
    fout.clear();
    scr.stage = stage;
    scr.level = level;
    if (ch == 'y' || ch == 'Y') {
	outtextxy(300, 250, "Y");
	if (gameloaded)
	    fout.seekp((int)((recordno - 1) * sizeof(score)));
	else
	    fout.seekp(0, ios::end);
	fout.write((char*)&scr, sizeof(scr));
	cleardevice();
	border(0);
	outtextxy(300, 200, "Saved Successfully!");
    }
    else
	outtextxy(200, 250, "N");
    getch();
    fout.close();
	if (a == 3)
		mainmenu();
}
