#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string>
#include <sstream>
#include <conio.h>
using namespace std;

#define ESC             27
#define RACKETUP1           'W' //TOP MOVE
#define RACKETUP2           'w'
#define RACKETDOWN1          'S' //BOTTOM MOVE
#define RACKETDOWN2           's'
#define MOVE_UP       -1
#define MOVE_DOWN      +1

#define RACKETUP1_2           72 //TOP MOVE keyup

#define RACKETDOWN1_2         80 //BOTTOM MOVE






#define MAX_X           640
#define MAX_Y           480
#define BCKCOLOR        BLUE

#define RACKET_W        10
#define RACKET_H        60
#define RACKET_L        50
#define RACKET_T        240
#define RACKET_R        (RACKET_L+RACKET_W)
#define RACKET_B        (RACKET_T+RACKET_H)
#define RACKET_CLR      GREEN
#define RACKET_XMOVE    0
#define RACKET_YMOVE    5

#define RACKET2_W        10
#define RACKET2_H        60
#define RACKET2_L        590
#define RACKET2_T        240
#define RACKET2_R        (RACKET2_L+RACKET2_W)
#define RACKET2_B        (RACKET2_T+RACKET2_H)
#define RACKET2_CLR      WHITE
#define RACKET2_XMOVE    0
#define RACKET2_YMOVE    5



#define BALL_X          240
#define BALL_Y          240
#define BALL_R          10
#define BALL_CLR        RED
#define BALL_XMOVE      3
#define BALL_YMOVE      3

// typedef enum { false, true } bool;

char score1;
char score2;

typedef struct {
    int max_x;
    int max_y;
    int bckcolor;
} gamewindow_t;

typedef struct {
    int left;
    int top;
    int right;
    int bottom;
    int color;
    int xmove;
    int ymove;
} racket_t;

typedef struct {
    int left;
    int top;
    int right;
    int bottom;
    int color;
    int xmove;
    int ymove;
} racket_t1;

typedef struct {
    int centerx;
    int centery;
    int radius;
    int color;
    int xmove;
    int ymove;
} ball_t;

void initGraphics(gamewindow_t* gw)
{
    int GraphDriver = 0, GraphMode = 0, errorcode;

    initgraph(&GraphDriver, &GraphMode, "");
    errorcode = graphresult();
    if (errorcode != grOk) {  /* an error occurred */
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);               /* terminate with an error code */
    }
}

void initGameWindow(gamewindow_t* gw, int max_x, int max_y, int bckcolor)
{
    gw->max_x = max_x;
    gw->max_y = max_y;
    gw->bckcolor = bckcolor;
}

void drawFilledRectangle(int left, int top, int right, int bottom, int color)
{
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    bar(left, top, right, bottom);
}

void drawFilledCircle(int centerx, int centery, int radius, int color)
{
    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(centerx, centery, radius, radius);
}

void setBackGroundColor(gamewindow_t* gw)
{
    drawFilledRectangle(0, 0, gw->max_x, gw->max_y, gw->bckcolor);
}

void initRacket(racket_t* r, int left, int top, int right, int bottom, int color, int xmove, int ymove)
{
    r->left = left;
    r->right = right;
    r->top = top;
    r->bottom = bottom;
    r->color = color;
    r->xmove = xmove;
    r->ymove = ymove;

    drawFilledRectangle(left, top, right, bottom, color);
}

void initRacket2(racket_t1* r, int left, int top, int right, int bottom, int color, int xmove, int ymove)
{
    r->left = left;
    r->right = right;
    r->top = top;
    r->bottom = bottom;
    r->color = color;
    r->xmove = xmove;
    r->ymove = ymove;

    drawFilledRectangle(left, top, right, bottom, color);
}


void initBall(ball_t* b, int centerx, int centery, int radius, int color, int xmove, int ymove)
{
    b->centerx = centerx;
    b->centery = centery;
    b->radius = radius;
    b->color = color;
    b->xmove = xmove;
    b->ymove = ymove;

    drawFilledCircle(centerx, centery, radius, color);
}

void initText()
{
	 /*std::string tmp = std::to_string(number);
    char *num_char = tmp.c_str()
	char* str2 = (char*) score2.c_str();
	char* str3= (char*)"Score"+str1+"-"+str2;*/
    setcolor(CYAN);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    outtextxy(300, 30, "THE PONG GAME");

    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 1);
	
	char arr[50] ;
	sprintf(arr , "Score: %d - %d",score1,score2);
	setcolor(LIGHTBLUE);
	outtextxy(365, 0, arr);
    
  	
   

}

void startGame(gamewindow_t* gw, racket_t* r, racket_t1* r1, ball_t* b)
{
    initGameWindow(gw, MAX_X, MAX_Y, BCKCOLOR);
    initGraphics(gw);
    setBackGroundColor(gw);
    initRacket(r, RACKET_L, RACKET_T, RACKET_R, RACKET_B, RACKET_CLR, RACKET_XMOVE, RACKET_YMOVE);
    initRacket2(r1, RACKET2_L, RACKET2_T, RACKET2_R, RACKET2_B, RACKET2_CLR, RACKET2_XMOVE, RACKET2_YMOVE);
    initBall(b, BALL_X, BALL_Y, BALL_R, BALL_CLR, BALL_XMOVE, BALL_YMOVE);
    initText();
    rectangle(10,80,630,410);
}

void endGame()
{
    closegraph();
}

void moveRacket(gamewindow_t* gw, racket_t* r, int dir)
{
    drawFilledRectangle(r->left, r->top, r->right, r->bottom, gw->bckcolor);
    r->top = r->top + (dir * r->ymove);
    r->bottom = r->bottom + (dir * r->ymove);
    drawFilledRectangle(r->left, r->top, r->right, r->bottom, r->color);
}

void moveRacket2(gamewindow_t* gw, racket_t1* r, int dir)
{
    drawFilledRectangle(r->left, r->top, r->right, r->bottom, gw->bckcolor);
    r->top = r->top + (dir * r->ymove);
    r->bottom = r->bottom + (dir * r->ymove);
    drawFilledRectangle(r->left, r->top, r->right, r->bottom, r->color);
}

void resetGame(gamewindow_t* gw, ball_t* b ,racket_t* r, racket_t1* r1){
	

	
	drawFilledRectangle(r->left, r->top, r->right, r->bottom, gw->bckcolor);
	drawFilledRectangle(r1->left, r1->top, r1->right, r1->bottom, gw->bckcolor);
	drawFilledCircle(b->centerx, b->centery, b->radius, gw->bckcolor);
	
	char arr[50] ;
	sprintf(arr , "Score: %d - %d",score1,score2);
	setcolor(LIGHTBLUE);
	outtextxy(365, 0, arr);
	
	initRacket(r, RACKET_L, RACKET_T, RACKET_R, RACKET_B, RACKET_CLR, RACKET_XMOVE, RACKET_YMOVE);
    initRacket2(r1, RACKET2_L, RACKET2_T, RACKET2_R, RACKET2_B, RACKET2_CLR, RACKET2_XMOVE, RACKET2_YMOVE);
    initBall(b, BALL_X, BALL_Y, BALL_R, BALL_CLR, BALL_XMOVE, BALL_YMOVE);
    
    
}

void moveBall(gamewindow_t* gw, ball_t* b ,racket_t* r, racket_t1* r1)
{
    drawFilledCircle(b->centerx, b->centery, b->radius, gw->bckcolor);

    // Bounch off left/right walls
    if (b->centerx > 620 || b->centerx < 20 || (b->centerx<r->right+15 && (b->centery>=r->top &&b->centery<=r->bottom )) || 
	 (b->centerx>r1->left-15 && (b->centery>=r1->top &&b->centery<=r1->bottom ))) {
	 	if(b->centerx >=10 && b->centerx<=30){
	 		score2+=1;
	 		resetGame(gw, b, r, r1);
	 		outtextxy(240,240, "Right got point");
	 		delay(1000);
	 		drawFilledRectangle(240,200, 500, 360, gw->bckcolor);
	 		return;
		 }
		if(b->centerx >=590){
	 		score1+=1;
	 		resetGame(gw, b, r, r1);
	 		outtextxy(240,240, "Left got point");
	 		delay(1000);
	 		drawFilledRectangle(240,200, 500, 360, gw->bckcolor);
	 		return;
		}
        b->xmove *= -1.0;
    }

    // Bounch off top/bottom walls
    if (b->centery > 395 || b->centery < 95 || ((b->centery+5<r1->bottom && b->centery>r1->top) && b->centerx>r1->left-3) 
	||((b->centery+5<r->bottom && b->centery+5>r->top) && b->centerx>r1->right+3) ) {
        b->ymove *= -1.0;
    }

    b->centerx += b->xmove;
    b->centery += b->ymove;

    drawFilledCircle(b->centerx, b->centery, b->radius, b->color);
   
}

bool manageGame(gamewindow_t* gw, racket_t* r, racket_t1* r1, ball_t* b)
{
    int keyPressed;

    delay(0.5);

    if (kbhit()) {
        keyPressed = getch();
        if (keyPressed == ESC) {
            return true;
        }
        if(keyPressed == RACKETUP1 || keyPressed == RACKETUP2){
        	if(r->top>90 && r->bottom<410){
        		moveRacket(gw, r, MOVE_UP);
			}
        	
		}
		if(keyPressed==RACKETUP1_2){
			if(r1->top>90 && r1->bottom<410){
        		moveRacket2(gw, r1, MOVE_UP);
			}
			
		}
		if(keyPressed == RACKETDOWN1 || keyPressed == RACKETDOWN2){
			if(r->top>80 && r->bottom<400){
        		moveRacket(gw, r, MOVE_DOWN);
			}
		
		}
		if(keyPressed==RACKETDOWN1_2){
			if(r1->top>80 && r1->bottom<400){
        		moveRacket2(gw, r1, MOVE_DOWN);
			}
			
		}
      
       

    }
    moveBall(gw, b, r ,r1);
    return false;
}

void playGame(gamewindow_t* gw, racket_t* r, racket_t1* r1 , ball_t* b)
{
    int gameOver;

    gameOver = false;
    while (!gameOver) {
        gameOver = manageGame(gw, r, r1, b);
    }
}


int main()
{
    gamewindow_t    gamew;
    racket_t        racket1;
    racket_t1       racket2;
    ball_t          ball1;
	score1=0;
	score2=0;
    startGame(&gamew, &racket1, &racket2, &ball1);
	
    playGame(&gamew, &racket1,  &racket2, &ball1);

    endGame();
}
