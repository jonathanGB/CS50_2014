//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of the paddle & its y-coordinate
#define pWIDTH 50
#define pHEIGHT 10
#define yPADDLE HEIGHT-75

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// space between bricks
#define SPACE 5

// height and width of the bricks
#define bWIDTH 35
#define bHEIGHT 12

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// y-velocity
#define yVELOCITY 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
    
    // set the x-velocity & y-velocity
    double xVelocity = 0;
    do
    {
        xVelocity += drand48();
    }
    while (xVelocity <= 0.6);
    
    double yVelocity = yVELOCITY;

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for the first click to start
    int start = 0;

    // keep playing until game over
    while (lives > 0 && points != 50)
    {        
        if (start == 0)
        {
            waitForClick();
            start++;
        }
                
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_CLICKED)
            {
                waitForClick();
            }
        
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - (pWIDTH/2);
                
                if (x < 0)
                {
                    setLocation(paddle, 0, yPADDLE);
                }
                else if (x + pWIDTH > WIDTH)
                {
                    setLocation(paddle, WIDTH - pWIDTH, yPADDLE);
                }
                else
                {
                    setLocation(paddle, x, yPADDLE);
                }
            }
        }
        
    
        move(ball, xVelocity, yVelocity);
        
        float xBall = getX(ball);
        float yBall = getY(ball);
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle)
            {
                yVelocity = -yVelocity;
            }
            else if (strcmp(getType(object), "GRect") == 0)
            {
                points++;
                yVelocity = -yVelocity;
                removeGWindow(window,object);
            }
        }

        
        if (xBall + (2*RADIUS) >= WIDTH || xBall <= 0)
        {
            xVelocity = -xVelocity;
        }
        else if(yBall <= 0)
        {
            yVelocity = -yVelocity;
        }
        else if (yBall+ (2*RADIUS) >= HEIGHT)
        {
            lives--;
            if (lives != 0)
            {
                setLocation(ball, (WIDTH/2) - RADIUS  , (HEIGHT/2) - RADIUS); 
                waitForClick();
                removeGWindow(window,ball); 
                yVelocity = yVELOCITY;
                ball = initBall(window);
            }
            else
            {
                removeGWindow(window,ball);
            }
        }
        
        updateScoreboard(window,label,points);
        // linger before moving again
        pause(5);    
    }        
    
    waitForClick();
    
    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{  
    string colour;
    int xBrick = 2;
    int yBrick = 100;
    
    for (int i = 0; i < ROWS; i++)
    {
        for ( int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(xBrick, yBrick, bWIDTH, bHEIGHT);
            
            switch(i)
            {
                case 0: 
                colour = "RED";
                break;
                
                case 1: 
                colour = "ORANGE";
                break;
                
                case 2: 
                colour = "YELLOW";
                break;
                
                case 3: 
                colour = "GREEN";
                break;
                
                case 4: 
                colour = "BLUE";
                break;
            }
            
            setColor(brick, colour);
            setFilled(brick, true);
            add(window, brick);
            
            xBrick += bWIDTH + SPACE;
        }
        xBrick = 2;
        yBrick += bHEIGHT + SPACE;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval((WIDTH/2) - RADIUS  , (HEIGHT/2) - RADIUS, RADIUS, RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball); 
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect((WIDTH/2) - (pWIDTH/2)  , yPADDLE, pWIDTH, pHEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle); 
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-18");
    add(window, label); 
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
