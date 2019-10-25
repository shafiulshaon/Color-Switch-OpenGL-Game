#include <iostream>
#include <stdlib.h>
#include <math.h>
#include<GL/gl.h>
#include <GL/glut.h>

#include <stdio.h>
#include <windows.h>
#include <string.h>
#pragma region
using namespace std;
float roundVanish12rgb=1,roundVanish14r=1,roundVanish04b=1,roundVanish01r=1,roundVanish01g=1,roundVanish02g=1,roundVanish06r=1,roundVanish06b=1,roundVanish08r=1,roundVanish08g=1,roundVanish08b=0.7,roundVanish10g=1,roundVanish10b=1;
float gravityVanish00r=1,gravityVanish02r=1,gravityVanish04r=1,gravityVanish06r=1,gravityVanish08r=1,gravityVanish00g=1,gravityVanish02g=1,gravityVanish04g=1,gravityVanish06g=1,gravityVanish08g=1,    gravityVanish00b=1,gravityVanish02b=1,gravityVanish04b=1,gravityVanish06b=1,gravityVanish08b=1;
float punchVanish01rgb=1,punchVanish02r=1,punchVanish03r=1,punchVanish03g=1,punchVanish04g=1,punchVanish05b=1,punchVanish06r=1,punchVanish06b=1,punchVanish07g=1,punchVanish07b=1;
float angleRound=0.0;  float roundCollisionStore,rR=1,gR=1,bR=1;
float angleGravity=0.0; float gravityCollisionStore,rG=0,gG=0,bG=1;
float anglePunch=1.0;  float punchCollisionStore,rP=1,gP=1,bP=1;
float _angle = 0.0, _shoot_angle=140.0, _shoot=0.0; float punchfire=0.0, fire=7, r=1,g=1,b=1;
float _cameraAngle = 0.0, _ang_tri = 0.0;
char roundScore='0'; char gravityScore='0'; char punchScore='0',roundClickCount='8',gravityDownCount='3',punchClickCount='7'; int countGravity=0;
float _circle_object_move=0, _circle_move = 1.0, _circle_move1 = 1.0; bool zeroShowGravity=true,zeroShowRound=true,zeroShowPunch=true,punchGoBack,_circle_move_1,_circle_move_,shootControl,scores, Rclick,Gclick,Pclick,showRoundScore,showGravityScore,showPunchScore;

bool roundUpdate, gravityUpdate, punchUpdate, navigation; ///for speed rolling in update function
bool backToMainMenu, inMainManu=true;
void drawScene_Round();
void handleResize(int w, int h);
void update(int value);
void drawScene();
char quote[6][80]; int numberOfQuotes = 0, i; ///for text
bool fullScreen=false;
int leftRight=1; ///gravity left right move object
int selectedGame=2;      ///round 2, gravity 1, punch 0

void initRendering() {
	glEnable(GL_DEPTH_TEST);
}
void myMouse(int b, int s, int x, int y)
{      // mouse click callback
	if (s == GLUT_DOWN)
    {
        Beep(600,60);
        if (b == GLUT_LEFT_BUTTON)
        {
            if(roundUpdate)
                {
                    Rclick=true;
                    if(roundClickCount=='8')
                        roundClickCount='7';
                    else if(roundClickCount=='7')
                        roundClickCount='6';
                    else if(roundClickCount=='6')
                        roundClickCount='5';
                    else if(roundClickCount=='5')
                        roundClickCount='4';
                    else if(roundClickCount=='4')
                        roundClickCount='3';
                    else if(roundClickCount=='3')
                        roundClickCount='2';
                    else if(roundClickCount=='2')
                        roundClickCount='1';
                    else if(roundClickCount=='1')
                        roundClickCount='0';
                }
            else if(gravityUpdate)
                {
                    Gclick=true;
                }
            if(punchUpdate)
                {
                    Pclick=true;
                    if(punchClickCount=='7')
                        punchClickCount='6';
                    else if(punchClickCount=='6')
                        punchClickCount='5';
                    else if(punchClickCount=='5')
                        punchClickCount='4';
                    else if(punchClickCount=='4')
                        punchClickCount='3';
                    else if(punchClickCount=='3')
                        punchClickCount='2';
                    else if(punchClickCount=='2')
                        punchClickCount='1';
                    else if(punchClickCount=='1')
                        punchClickCount='0';
                }
		}
	}
}
void keyboardown(int key, int x, int y) ///selecting game modes and others
{
	Beep(500,60);
	switch (key){
	case GLUT_KEY_F1:
        scores=true;
            backToMainMenu=false;
            inMainManu=false;
            roundUpdate=false;
            gravityUpdate=false;
            punchUpdate=false;
            navigation=false;
		break;

	case GLUT_KEY_F11:
		if(!fullScreen)
        {
            glutFullScreen();
            fullScreen=true;
		}
		else
        {
            glutReshapeWindow(600,600);
            glutPositionWindow(400,50);
            fullScreen=false;

        }
		glutPostRedisplay();

		break;
	case GLUT_KEY_RIGHT:
	    if(gravityUpdate)
        {
            if(leftRight==2)
            {
                leftRight=1;
                _shoot=0.0;
            }
            else if(leftRight==1)
            {
                leftRight=0;
                _shoot=1.5;
            }
        }
	    else
	    {
            if(selectedGame==2)
            {
                selectedGame=1;
                _shoot_angle=180;
            }
            else if(selectedGame==1)
            {
                selectedGame=0;
                _shoot_angle=220;
            }
            else if(selectedGame==0)
            {
                selectedGame=3;
                _shoot_angle=2;
                shootControl=true;
            }
	    }

	    break;

	case GLUT_KEY_LEFT:
        if(gravityUpdate)
        {
            if(leftRight==0)
            {
                leftRight=1;
                _shoot=0.0;
            }
            else if(leftRight==1)
            {
                leftRight=2;
                _shoot=-1.5;
            }
        }
        else
        {
            if(selectedGame==3)
            {
                selectedGame=0;
                shootControl=false;
                _shoot_angle=220;
            }
            else if(selectedGame==0)
            {
                selectedGame=1;
                _shoot_angle=180;
            }
            else if(selectedGame==1)
            {
                selectedGame=2;
                _shoot_angle=140;
            }
        }
        break;

	case GLUT_KEY_DOWN:
	    if(selectedGame==2 || selectedGame==1 || selectedGame==0)
        {
            selectedGame=3;
            shootControl=true;
            _shoot_angle=2;
        }
        break;

	case GLUT_KEY_UP:
	    if(selectedGame==3)
        {
            selectedGame=1;
            shootControl=false;
            _shoot_angle=180;
        }
        break;
	default:
		break;
	}

}

void keyboard(unsigned char key, int x, int y)  ///enter in games mode and escape
    {
        Beep(500,60);
        switch (key) {
        case 13:

            if(selectedGame==2)
            {
                roundUpdate=true;
                inMainManu=false;
            }


            else if(selectedGame==1)
            {
                gravityUpdate=true;
                inMainManu=false;
            }

            else if(selectedGame==0)
            {
                punchUpdate=true;
                inMainManu=false;
            }
            else if(selectedGame==3)
            {
                navigation=true;
                inMainManu=false;

            }

            break;
         case 27:
            backToMainMenu=true;
            roundUpdate=false;
            gravityUpdate=false;
            punchUpdate=false;
            navigation=false;
            scores=false;
            break;
        default:
            break;
        }
    }

void RenderToDisplay() ///for text
{
	int l, lenghOfQuote, i;
	glTranslatef(14, -5, -60);
	glScalef(0.02, 0.02, 0.09);

    if(scores)
    {
             for (l = 12; l<20; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==12)
                    glTranslatef(-1200, 4900-(l*300), 0.0);
                else
                    glTranslatef(-1680, 4800-(l*300), 0.0);
                if (l==16 || l==17 || l==18)
                    glTranslatef(700, 900, 0.0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                if(l==16 || l==18)
                {
                     for (i = 0; i < 1; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }

                glPopMatrix();
            }
    }

    else if(navigation)
    {
             for (l = 5; l<12; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==5)
                    glTranslatef(-1200, 2800-(l*300), 0.0);
                else
                    glTranslatef(-1680, 3000-(l*300), 0.0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                for (i = 0; i < lenghOfQuote; i++)
                {
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                }
                glPopMatrix();
            }
    }
    else if(showRoundScore)
    {
             for (l = 20; l<24; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==20)
                    glTranslatef(-1400, -400, 0);
                else if(l==21)
                    glTranslatef(-1400, -600, 0);
                else if(l==22)
                    glTranslatef(-800, -600, 0);
                else if (l==23)
                    glTranslatef(-1400, -800, 0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                if(l==22)
                {
                    for (i = 0; i < 1; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                glPopMatrix();

            }
    }

    else if(showPunchScore)
    {
             for (l = 32; l<36; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==32)
                    glTranslatef(-1400, -400, 0);
                else if(l==33)
                    glTranslatef(-1400, -600, 0);
                else if(l==34)
                    glTranslatef(-800, -600, 0);
                else if (l==35)
                    glTranslatef(-1400, -800, 0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                if(l==34)
                {
                    for (i = 0; i < 1; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                glPopMatrix();

            }
    }

    else if(showGravityScore)
    {
             for (l = 26; l<30; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==26)
                    glTranslatef(-1400, -400, 0);
                else if(l==27)
                    glTranslatef(-1400, -600, 0);
                else if(l==28)
                    glTranslatef(-800, -600, 0);
                else if (l==29)
                    glTranslatef(-1400, -800, 0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                if(l==28)
                {
                    for (i = 0; i < 2; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                glPopMatrix();

            }
    }

    else if(roundUpdate)
    {
             for (l = 24; l<26; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==24)
                    glTranslatef(-2000, 1450, 0);
                else if(l==25)
                    glTranslatef(-1400, 1450, 0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                glScalef(.7,.7,.7);
                if(l==25)
                {
                    for (i = 0; i < 1; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                glPopMatrix();
            }
    }

    else if(gravityUpdate)
    {
             for (l = 30; l<32; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==30)
                    glTranslatef(-2000, 1450, 0);
                else if(l==31)
                    glTranslatef(-1400, 1450, 0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                glScalef(.7,.7,.7);
                if(l==31)
                {
                    for (i = 0; i < 1; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                glPopMatrix();
            }
    }
    else if(punchUpdate)
    {
             for (l = 36; l<38; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==36)
                    glTranslatef(-2000, 1450, 0);
                else if(l==37)
                    glTranslatef(-1400, 1450, 0);
                glLineWidth(1);
                glColor3f(0, 1, 0);
                glScalef(.7,.7,.7);
                if(l==37)
                {
                    for (i = 0; i < 1; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                else
                {
                    for (i = 0; i < lenghOfQuote; i++)
                    {
                        glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                    }
                }
                glPopMatrix();
            }
    }

    else if(inMainManu)
        {
            for (l = 0; l<5; l++)
            {
                lenghOfQuote = (int)strlen(quote[l]);
                glPushMatrix();
                if(l==3)
                    glTranslatef(-330*l, -900, 0.0);
                else if(l==4)
                    glTranslatef(-330*l, 1300, 0.0);
                else
                    glTranslatef(-900*l, 0, 0.0);

                glLineWidth(1);
                glColor3f(0, 1, 0);
                if(selectedGame==l)
                {
                    glColor3f(1, 1, 1); ///hover color
                }
                for (i = 0; i < lenghOfQuote; i++)
                {
                    glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
                }
                glPopMatrix();
            }
    }
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawRound()
{
            glPushMatrix(); //Save the current state of transformations
            glTranslatef(0, 1, 0.0); //Move to the center of the triangle
            glRotatef(-angleRound, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)
            glScalef(2,2,0);
            //glEnable(GL_LINE_SMOOTH);
            glLineWidth(10.0f);
            glBegin(GL_LINES);
            for(int i=0;i<=15;i++)
            {
                if(i == 0)
                {
                    glColor3f(roundVanish01r, roundVanish01g, 0);
                }else if(i == 2)
                {
                    glColor3f(0, roundVanish02g, 0);
                }else if(i == 4)
                {
                    glColor3f(0, 0, roundVanish04b);
                }else if(i == 6)
                {
                    glColor3f(roundVanish06r, 0, roundVanish06b);
                }else if(i == 8)
                {
                    glColor3f(roundVanish08r, roundVanish08g, roundVanish08b);
                }else if(i == 10)
                {
                    glColor3f(0, roundVanish10g, roundVanish10b);
                }else if(i == 12)
                {
                    glColor3f(roundVanish12rgb, roundVanish12rgb, roundVanish12rgb);
                }else if(i == 14)
                {
                    glColor3f(roundVanish14r, 0, 0);
                }

                float pi=3.1416;
                float A=(i*2*pi)/16;
                float r=.6;
                float x = r * cos(A);
                float y = r * sin(A);
                //cout<<x<<" "<<y<<endl;
                glVertex2f(x,y );
            }

            glEnd();
            glPopMatrix(); //Undo the move to the center of the triangle

            /////////////////////////// Shotting Object
            if(!showRoundScore)
            {
            glPushMatrix();
                glScalef(.6,.6,0);
                glTranslatef(0, -3.5, 0.0);
                glColor3f(rR,gR,bR);
                glBegin(GL_POLYGON);
                for(int i=0;i<=15;i++)
                {
                    float pi=3.1416;
                    float A=(i*2*pi)/16;
                    float r=.2;
                    float x = r * cos(A);
                    float y = r * sin(A);
                    glVertex2f(x,y );
                }
                glEnd();
            glPopMatrix();


            glPushMatrix();
                glScalef(.3,.3,0);
                        glTranslatef(0, -7, 0.0); //Move to the object
                glRotatef(-180, 0.0, 0.0, 1.0); //shooting angle fixed
                glTranslatef(0, -1.5, 0.0); //moving circle radius
                glColor3f(rR,gR,bR);
                glBegin(GL_TRIANGLES);
                    glVertex2f(-.5,0);
                    glVertex2f(.5,0);
                    glVertex2f(0,-.5);
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glScalef(.3,.3,0);
                        glTranslatef(0, -fire, 0.0); //Move to the object //fire value 3 for collision
                glRotatef(-180, 0.0, 0.0, 1.0); //shooting angle fixed
                glTranslatef(0, -1.5, 0.0); //moving circle radius
                glColor3f(rR,gR,bR);

                glBegin(GL_TRIANGLES);
                    glVertex2f(-.5,0);
                    glVertex2f(.5,0);
                    glVertex2f(0,-.5);
                glEnd();
            glPopMatrix();
            }
}
void drawPunch()
{
                glPushMatrix();
            glScalef(.3,.3,0);
            glRotatef(-60, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)
            glTranslatef(-1.0, -5, 0.0); //Move forward 5 units
            glTranslatef(0.0, anglePunch, 0.0); //Move to the center of the triangle

                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, -9, 0.0); //Move to the center of the triangle
                    glColor3f(punchVanish01rgb,punchVanish01rgb,punchVanish01rgb);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, -6, 0.0); //Move to the center of the triangle
                    glColor3f(punchVanish02r,0,0);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, -3, 0.0); //Move to the center of the triangle
                    glColor3f(punchVanish03r,punchVanish03g,0);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, 0.0, 0.0); //Move to the center of the triangle
                    glColor3f(0,punchVanish04g,0);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();


                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, 3, 0.0); //Move to the center of the triangle
                    glColor3f(0,0,punchVanish05b);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, 6, 0.0); //Move to the center of the triangle
                    glColor3f(punchVanish06r,0,punchVanish06b);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                    glTranslatef(0.0, 9, 1.0); //Move to the center of the triangle
                    glColor3f(0,punchVanish07g,punchVanish07b);
                    glBegin(GL_POLYGON);
                    for(int i=0;i<200;i++)
                    {
                        float pi=3.1416;
                        float A=(i*2*pi)/100;
                        float r=0.95;
                        float x = r * cos(A);
                        float y = r * sin(A);
                        glVertex2f(x,y );
                    }
                    glEnd();
                glPopMatrix();

            glPopMatrix();


            /////////////////////////// Shotting Object
            if(!showPunchScore)
            {
            glPushMatrix();
            glColor3f(rP,gP,bP);
            glRotatef(-32, 0.0, 0.0, -1.0);
            glPushMatrix();
            glTranslatef(0, -2, 0.0);
            glBegin(GL_POLYGON);
            for(int i=0;i<=16;i++)
            {
                float pi=3.1416;
                float A=(i*2*pi)/16;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );
            }
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, -1.6, 0.0); //Move to the center of the triangle
            glBegin(GL_POLYGON);
            for(int i=0;i<=16;i++)
            {
                float pi=3.1416;
                float A=(i*2*pi)/16;
                float r=.12;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );
            }
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, -punchfire, 0.0);
           glPushMatrix();
            glTranslatef(0, -1.3, 0.0); //Move to the center of the triangle
            glBegin(GL_POLYGON);
            for(int i=0;i<=16;i++)
            {
                float pi=3.1416;
                float A=(i*2*pi)/16;
                float r=.1;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );
            }
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glScalef(.4,.4,0);
            glTranslatef(0, -2.8, 0.0); //Move to the center of the triangle
            glBegin(GL_TRIANGLES);
            glVertex2f(-.5,0);
            glVertex2f(.5,0);
            glVertex2f(0,.5);
            glEnd();
            glPopMatrix();
            glPopMatrix();



            glPopMatrix();
            }

}

void drawGravity()
{
            glPushMatrix();
            if(!showGravityScore)
                glTranslatef(0,_circle_object_move,0);
            else
                glTranslatef(0,0,0);
            glPushMatrix();
            glTranslatef(0, 2, 0.0);
            glRotatef(-angleGravity, 0.0, 0.0, 1.0);
            glScalef(2.5,2.5,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(8.0f);
            //glColor3f(1,0,0);
            glBegin(GL_LINES);
            for(int i=0;i<=9;i++)
            {
                if(i==0)                  ///0 for 0,1 color.... 2 for 2,3 point color and so on..
                    glColor3f(gravityVanish00r,0,0);
                else if(i==2)
                    glColor3f(gravityVanish02r,0,0);
                else if(i==4)
                    glColor3f(gravityVanish04r,0,0);
                else if(i==6)
                    glColor3f(gravityVanish06r,0,0);
                else if(i==8)
                    glColor3f(gravityVanish08r,0,0);
                float pi=3.1416;
                float A=(i*2*pi)/10;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );

            }

            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.5, 1.5, 0.0);
            glRotatef(-angleGravity, 0.0, 0.0, 1.0);
            glScalef(2.5,2.5,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(8.0f);
            //glColor3f(0,1,0);
            glBegin(GL_LINES);
            for(int i=0;i<=10;i++)
            {
                if(i==0)                  ///0 for 0,1 color.... 2 for 2,3 point color and so on..
                    glColor3f(0,gravityVanish00g,0);
                else if(i==2)
                    glColor3f(0,gravityVanish02g,0);
                else if(i==4)
                    glColor3f(0,gravityVanish04g,0);
                else if(i==6)
                    glColor3f(0,gravityVanish06g,0);
                else if(i==8)
                    glColor3f(0,gravityVanish08g,0);
                float pi=3.1416;
                float A=(i*2*pi)/10;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );

            }

            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1.5, 1.5, 0.0);
            glRotatef(-angleGravity, 0.0, 0.0, 1.0);
            glScalef(2.5,2.5,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(8.0f);
            //glColor3f(0,0,1);
            glBegin(GL_LINES);
            for(int i=0;i<=10;i++)
            {
                if(i==0)                  ///0 for 0,1 color.... 2 for 2,3 point color and so on..
                    glColor3f(0,0,gravityVanish00b);
                else if(i==2)
                    glColor3f(0,0,gravityVanish02b);
                else if(i==4)
                    glColor3f(0,0,gravityVanish04b);
                else if(i==6)
                    glColor3f(0,0,gravityVanish06b);
                else if(i==8)
                    glColor3f(0,0,gravityVanish08b);
                float pi=3.1416;
                float A=(i*2*pi)/10;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );

            }

            glEnd();
            glPopMatrix();
            glPopMatrix();

            /////////////////////////// Shotting Object
            if(!showGravityScore)
            {
                glPushMatrix();
                glTranslatef(_shoot, 0.0, 0.0);
                glPushMatrix();
                glScalef(.6,.6,0);
                glTranslatef(0, -3.5, 0.0);
                glColor3f(rG,gG,bG);
                glBegin(GL_POLYGON);
                for(int i=0;i<=16;i++)
                {
                    float pi=3.1416;
                    float A=(i*2*pi)/16;
                    float r=.2;
                    float x = r * cos(A);
                    float y = r * sin(A);
                    glVertex2f(x,y );
                }
                glEnd();
                glPopMatrix();


                glPushMatrix();
                    glScalef(.3,.3,0);
                            glTranslatef(0.0, -7, 0.0); //Move to the object
                    glRotatef(-180, 0.0, 0.0, 1.0);
                    glTranslatef(0, -1.5, 0.0); //moving circle radius
                    glColor3f(rG,gG,bG);
                    glBegin(GL_TRIANGLES);
                        glVertex2f(-.5,0);
                        glVertex2f(.5,0);
                        glVertex2f(0,-.5);
                    glEnd();
                glPopMatrix();
                glPushMatrix();
                    glScalef(.3,.3,0);
                            glTranslatef(0.0, -fire, 0.0); //Move to the object //fire value 3 for collision
                    glRotatef(-180, 0.0, 0.0, 1.0); //shooting angle fixed
                    glTranslatef(0, -1.5, 0.0); //moving circle radius
                    glColor3f(rG,gG,bG);
                    glBegin(GL_TRIANGLES);
                        glVertex2f(-.5,0);
                        glVertex2f(.5,0);
                        glVertex2f(0,-.5);
                    glEnd();
                glPopMatrix();
                glPopMatrix();

            }
}
void drawNavigation()
{
        strcpy(quote[5], "Color Switch Game");
        strcpy(quote[7], "Move : Left, Right, Up, Down");
        strcpy(quote[8], "Select : Enter");
        strcpy(quote[9], "Full Screen : F11");
        strcpy(quote[10], "Back : Esc");
        strcpy(quote[11], "Scores : F1");
        numberOfQuotes = 12;
        RenderToDisplay();
}
void drawScores()
{
        strcpy(quote[12], "Game Scores");
        strcpy(quote[13], "Round : ");
        strcpy(quote[14], "Gravity : ");
        strcpy(quote[15], "Punch : ");
        strcpy(quote[16], &roundScore);
        if(zeroShowGravity==true)
            strcpy(quote[17], "0");
        strcpy(quote[18], &punchScore);
        strcpy(quote[19], "Esc : Back to main menu");
        numberOfQuotes = 20;
        RenderToDisplay();
}
void drawMainMenu()
{
                ///round
            glPushMatrix(); //Save the current state of transformations
            glTranslatef(-1.9, 0.8, 0.0); //Move to the center of the triangle
            glRotatef(_angle, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)
            glScalef(0.8,0.8,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(10.0f);
            glBegin(GL_LINES);
            glTranslatef(0, 1, 0.0); //Move to the center of the triangle
            glRotatef(_angle, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)
            glScalef(2,2,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(10.0f);
            glBegin(GL_LINES);
            for(int i=0;i<=16;i++)
            {

                if(i == 2)
                {
                    glColor3ub(255, 0, 0);
                }else if(i == 4)
                {
                    glColor3ub(0, 255, 0);
                }else if(i == 6)
                {
                    glColor3ub(0, 0, 255);
                }else if(i == 8)
                {
                    glColor3ub(255, 0, 255);
                }else if(i == 10)
                {
                    glColor3ub(255, 255, 255);
                }else if(i == 12)
                {
                    glColor3ub(255, 255, 0);
                }else if(i == 14)
                {
                    glColor3ub(127, 0, 127);
                }else if(i == 16)
                {
                    glColor3ub(0, 127, 255);
                }

                float pi=3.1416;
                float A=(i*2*pi)/16;
                float r=.6;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );
            }
            glEnd();
            glPopMatrix(); //Undo the move to the center of the triangle
            ///round end


            ///punch start
                glPushMatrix();
                glScalef(.12,.12,0);
                glRotatef(-60, 0.0, 0.0, 1.0); //Rotate about the the vector (1, 2, 3)
                glTranslatef(3, 10, 0.0); //Move forward 5 units
                glTranslatef(0.0, _circle_move, 0.0); //Move to the center of the triangle

                glPushMatrix(); //Save the current state of transformations
                glTranslatef(0.0, 0.0, 0.0); //Move to the center of the triangle
                glColor3f(0,0.5,0.5);
                glBegin(GL_POLYGON);
                for(int i=0;i<200;i++)
                {
                    float pi=3.1416;
                    float A=(i*2*pi)/100;
                    float r=0.95;
                    float x = r * cos(A);
                    float y = r * sin(A);
                    glVertex2f(x,y );
                }
                glEnd();
                glPopMatrix();


                glPushMatrix(); //Save the current state of transformations
                glTranslatef(0.0, 3, 0.0); //Move to the center of the triangle
                glColor3f(1,.2,.7);
                glBegin(GL_POLYGON);
                for(int i=0;i<200;i++)
                {
                    float pi=3.1416;
                    float A=(i*2*pi)/100;
                    float r=0.95;
                    float x = r * cos(A);
                    float y = r * sin(A);
                    glVertex2f(x,y );
                }
                glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                glTranslatef(0.0, 6, 0.0); //Move to the center of the triangle
                glColor3f(.2,.95,.5);
                glBegin(GL_POLYGON);
                for(int i=0;i<200;i++)
                {
                    float pi=3.1416;
                    float A=(i*2*pi)/100;
                    float r=0.95;
                    float x = r * cos(A);
                    float y = r * sin(A);
                    glVertex2f(x,y );
                }
                glEnd();
                glPopMatrix();

                glPushMatrix(); //Save the current state of transformations
                glTranslatef(0.0, 9, 1.0); //Move to the center of the triangle
                glColor3f(.8,0,.35);
                glBegin(GL_POLYGON);
                for(int i=0;i<200;i++)
                {
                    float pi=3.1416;
                    float A=(i*2*pi)/100;
                    float r=0.95;
                    float x = r * cos(A);
                    float y = r * sin(A);
                    glVertex2f(x,y );
                }
                glEnd();
                glPopMatrix();
                glPopMatrix();
            ///punch end



            ///gravity start
            glPushMatrix();
            glScalef(.5,.5,0);

            glPushMatrix();
            glTranslatef(-0.1, 2.5, 0.0);
            glRotatef(_angle, 0.0, 0.0, 1.0);
            glScalef(2.5,2.5,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(8.0f);
            glColor3f(1,0,0);
            glBegin(GL_LINES);
            for(int i=0;i<=10;i++)
            {
                float pi=3.1416;
                float A=(i*2*pi)/10;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );
            }
            glEnd();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(0.9, 1.1, 0.0);
            glRotatef(_angle, 0.0, 0.0, 1.0);
            glScalef(2.5,2.5,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(8.0f);
            glColor3f(0,1,0);
            glBegin(GL_LINES);
            for(int i=0;i<=10;i++)
            {
                float pi=3.1416;
                float A=(i*2*pi)/10;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );
            }
            glEnd();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(-0.9, 1.1, 0.0);
            glRotatef(_angle, 0.0, 0.0, 1.0);
            glScalef(2.5,2.5,0);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(8.0f);
            glColor3f(0,0,1);
            glBegin(GL_LINES);
            for(int i=0;i<=10;i++)
            {
                float pi=3.1416;
                float A=(i*2*pi)/10;
                float r=.2;
                float x = r * cos(A);
                float y = r * sin(A);
                glVertex2f(x,y );

            }

            glEnd();
            glPopMatrix();


            glPopMatrix();
            ///gravity end


            /////////////////////////// Shotting Object
            glPushMatrix();
            glScalef(.3,.3,0);
            if(!shootControl)
                glTranslatef(0, -6.5, 0.0); //Move to the object
            else
                glTranslatef(0, -4, 0.0); //Move to the object
            glRotatef(-_shoot_angle, 0.0, 0.0, 1.0);
            glTranslatef(0, -1.5, 0.0); //moving circle radius
            glColor3f(1,1,1);
            glBegin(GL_TRIANGLES);
            glVertex2f(-.5,0);
            glVertex2f(.5,0);
            glVertex2f(0,-.5);
            glEnd();
            glPopMatrix();

            RenderToDisplay(); ///for text

            showRoundScore=false;
            backToMainMenu=false;
            inMainManu=true;
            rR=gR=bR=1;
            roundVanish12rgb=1;roundVanish14r=1;roundVanish04b=1;roundVanish01r=1;roundVanish01g=1;roundVanish02g=1;roundVanish06r=1;roundVanish06b=1;roundVanish08r=1;roundVanish08g=1;roundVanish08b=0.7;roundVanish10g=1;roundVanish10b=1;
            roundClickCount='8';

            _circle_object_move=0.0;
            showGravityScore=false;
            gravityDownCount='3';
            countGravity=0;
            gravityVanish00r=1;gravityVanish02r=1;gravityVanish04r=1;gravityVanish06r=1;gravityVanish08r=1;gravityVanish00g=1;gravityVanish02g=1;gravityVanish04g=1;gravityVanish06g=1;gravityVanish08g=1;gravityVanish00b=1;gravityVanish02b=1;gravityVanish04b=1;gravityVanish06b=1;gravityVanish08b=1;

            showPunchScore=false;
            rP=gP=bP=1;
            anglePunch=1.0;
            punchClickCount='7';
            punchVanish01rgb=1;punchVanish02r=1;punchVanish03r=1;punchVanish03g=1;punchVanish04g=1;punchVanish05b=1;punchVanish06r=1;punchVanish06b=1;punchVanish07g=1;punchVanish07b=1;
}
//Draws the 3D scene
void drawScene()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0, 0);
        glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
        glLoadIdentity(); //Reset the drawing perspective
        glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
        glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units

        if(roundUpdate)
            {
                if(showRoundScore)
                {
                    strcpy(quote[20], "Game over");
                    strcpy(quote[21], "Score : ");
                    strcpy(quote[22], &roundScore);
                    strcpy(quote[23], "Esc : Back to main menu");
                    numberOfQuotes = 26;
                }
                drawRound();
                strcpy(quote[24], "Click Left : ");
                strcpy(quote[25], &roundClickCount);
                RenderToDisplay();
            }
        else if(punchUpdate)
            {
                if(showPunchScore)
                {
                    strcpy(quote[32], "Game over");
                    strcpy(quote[33], "Score : ");
                    strcpy(quote[34], &punchScore);
                    strcpy(quote[35], "Esc : Back to main menu");
                    numberOfQuotes = 38;
                }
                drawPunch();
                strcpy(quote[36], "Click Left : ");
                strcpy(quote[37], &punchClickCount);
                RenderToDisplay();
            }
        else if(gravityUpdate)
            {
                if(showGravityScore)
                {
                    strcpy(quote[26], "Game over");
                    strcpy(quote[27], "Score : ");
                    if(countGravity==0) strcpy(quote[28], "0");else if(countGravity==1)strcpy(quote[28], "1");else if(countGravity==2)strcpy(quote[28], "2");
                    else if(countGravity==3)strcpy(quote[28], "3");else if(countGravity==4)strcpy(quote[28], "4"); else if(countGravity==5)strcpy(quote[28], "5");
                    else if(countGravity==6)strcpy(quote[28], "6");else if(countGravity==7)strcpy(quote[28], "7"); else if(countGravity==8)strcpy(quote[28], "8");
                    else if(countGravity==9)strcpy(quote[28], "9");else if(countGravity==10)strcpy(quote[28], "10"); else if(countGravity==11)strcpy(quote[28], "11");
                    else if(countGravity==12)strcpy(quote[28], "12");else if(countGravity==13)strcpy(quote[28], "13"); else if(countGravity==14)strcpy(quote[28], "14");else if(countGravity==15)strcpy(quote[28], "15");
                    if(quote[17]<quote[28])
                        strcpy(quote[17], quote[28]);
                    strcpy(quote[29], "Esc : Back to main menu");
                    numberOfQuotes = 32;
                    zeroShowGravity=false;
                    //countGravity=0;
                }
                drawGravity();
                strcpy(quote[30], "Round Left : ");
                strcpy(quote[31], &gravityDownCount);
                RenderToDisplay();
            }
        else if(navigation)
            {
                drawNavigation();
            }
        else if(scores)
            {
                drawScores();
            }
        else if(backToMainMenu==true || inMainManu==true)
            {
                drawMainMenu();
            }


        glutSwapBuffers();
 }
void shootingColorChangeRound()
{
         if(rR==1 && gR==1 && bR==1)    { rR=gR=0; bR=1; }
    else if(rR==0 && gR==0 && bR==1)    { gR=bR=0; rR=1; }
    else if(rR==1 && gR==0 && bR==0)    { rR=bR=0; gR=1; }
    else if(rR==0 && gR==1 && bR==0)    { rR=gR=1; bR=0; }
    else if(rR==1 && gR==1 && bR==0)    { rR=bR=1; gR=0; }
    else if(rR==1 && gR==0 && bR==1)    { rR=gR=1; bR=0.7f; }
    else if(rR==1 && gR==1 && bR==0.7f) { gR=bR=1; rR=0; }
    else if(rR==0 && gR==1 && bR==1)    { rR=gR=bR=0;    showRoundScore=true;}
}
void roundCollisionCheck()
{
    if((roundCollisionStore<=0 && roundCollisionStore>=-22) && (rR==1 && gR==1 && bR==1))
    {
        roundVanish12rgb=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';

    }
    else if((roundCollisionStore<=-44 && roundCollisionStore>=-67) && (rR==1 && gR==0 && bR==0))
    {
        roundVanish14r=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    else if((roundCollisionStore<=-179 && roundCollisionStore>=-202) && (rR==0 && gR==0 && bR==1))
    {
        roundVanish04b=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    else if((roundCollisionStore<=-89 && roundCollisionStore>=-112) && (rR==1 && gR==1 && bR==0))
    {
        roundVanish01r=0;roundVanish01g=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    else if((roundCollisionStore<=-134 && roundCollisionStore>=-157) && (rR==0 && gR==1 && bR==0))
    {
        roundVanish02g=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    else if((roundCollisionStore<=-224 && roundCollisionStore>=-247) && (rR==1 && gR==0 && bR==1))
    {
        roundVanish06r=0;roundVanish06b=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    else if((roundCollisionStore<=-269 && roundCollisionStore>=-292) && (rR==1 && gR==1 && bR==0.7f))
    {
        roundVanish08r=0;roundVanish08g=0;roundVanish08b=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    else if((roundCollisionStore<=-314 && roundCollisionStore>=-337) && (rR==0 && gR==1 && bR==1))
    {
        roundVanish10g=0;roundVanish10b=0;
        if(roundScore=='0')
            roundScore='1';
        else if(roundScore=='1')
            roundScore='2';
        else if(roundScore=='2')
            roundScore='3';
        else if(roundScore=='3')
            roundScore='4';
        else if(roundScore=='4')
            roundScore='5';
        else if(roundScore=='5')
            roundScore='6';
        else if(roundScore=='6')
            roundScore='7';
        else if(roundScore=='7')
            roundScore='8';
    }
    shootingColorChangeRound();
}
void shootingColorChangeGravity()
{
         if(rG==0 && gG==0 && bG==1)
            {
                float ran = rand() % 2;
                if(ran==0)
                    {rG=bG=0; gG=1;}
                else
                    {bG=gG=0; rG=1;}
            }
    else if(rG==0 && gG==1 && bG==0)
        {
            float ran = rand() % 2;
            if(ran==0)
                {gG=bG=0; rG=1;}
            else
                {rG=gG=0; bG=1;}
        }
    else if(rG==1 && gG==0 && bG==0)
        {
            float ran = rand() % 2;
            if(ran==0)
                {rG=bG=0; gG=1;}
            else
                {rG=gG=0; bG=1;}
        }

}
void gravityCollisionCheck()
{
    if(((gravityCollisionStore<=-15 && gravityCollisionStore>=-55) || (gravityCollisionStore<=-195 && gravityCollisionStore>=-235)) && leftRight==1 && (rG==1))
        {gravityVanish08r=0; countGravity++;}
    if(((gravityCollisionStore<=-95 && gravityCollisionStore>=-130) || (gravityCollisionStore<=-265 && gravityCollisionStore>=-305)) && leftRight==1 && (rG==1))
        {gravityVanish00r=0; countGravity++;}
    if(((gravityCollisionStore<=-160 && gravityCollisionStore>=-200) || (gravityCollisionStore<=-340 && gravityCollisionStore>=-360) || (gravityCollisionStore<=-0 && gravityCollisionStore>=-20)) && leftRight==1 && (rG==1))
        {gravityVanish02r=0; countGravity++;}
    if(((gravityCollisionStore<=-50 && gravityCollisionStore>=-90) || (gravityCollisionStore<=-230 && gravityCollisionStore>=-270)) && leftRight==1 && (rG==1))
        {gravityVanish04r=0; countGravity++;}
    if(((gravityCollisionStore<=-125 && gravityCollisionStore>=-160) || (gravityCollisionStore<=-305 && gravityCollisionStore>=-345)) && leftRight==1 && (rG==1))
        {gravityVanish06r=0; countGravity++;}

    if(((gravityCollisionStore<=-15 && gravityCollisionStore>=-55) || (gravityCollisionStore<=-195 && gravityCollisionStore>=-235)) && leftRight==0 && (gG==1))
        {gravityVanish08g=0; countGravity++;}
    if(((gravityCollisionStore<=-95 && gravityCollisionStore>=-130) || (gravityCollisionStore<=-265 && gravityCollisionStore>=-305)) && leftRight==0 && (gG==1))
        {gravityVanish00g=0; countGravity++;}
    if(((gravityCollisionStore<=-160 && gravityCollisionStore>=-200) || (gravityCollisionStore<=-340 && gravityCollisionStore>=-360) || (gravityCollisionStore<=-0 && gravityCollisionStore>=-20)) && leftRight==0 && (gG==1))
        {gravityVanish02g=0; countGravity++;}
    if(((gravityCollisionStore<=-50 && gravityCollisionStore>=-90) || (gravityCollisionStore<=-230 && gravityCollisionStore>=-270)) && leftRight==0 && (gG==1))
        {gravityVanish04g=0; countGravity++;}
    if(((gravityCollisionStore<=-125 && gravityCollisionStore>=-160) || (gravityCollisionStore<=-305 && gravityCollisionStore>=-345)) && leftRight==0 && (gG==1))
        {gravityVanish06g=0; countGravity++;}

    if(((gravityCollisionStore<=-15 && gravityCollisionStore>=-55) || (gravityCollisionStore<=-195 && gravityCollisionStore>=-235)) && leftRight==2 && (bG==1))
        {gravityVanish08b=0; countGravity++;}
    if(((gravityCollisionStore<=-95 && gravityCollisionStore>=-130) || (gravityCollisionStore<=-265 && gravityCollisionStore>=-305)) && leftRight==2 && (bG==1))
        {gravityVanish00b=0; countGravity++;}
    if(((gravityCollisionStore<=-160 && gravityCollisionStore>=-200) || (gravityCollisionStore<=-340 && gravityCollisionStore>=-360) || (gravityCollisionStore<=-0 && gravityCollisionStore>=-20)) && leftRight==2 && (bG==1))
        {gravityVanish02b=0; countGravity++;}
    if(((gravityCollisionStore<=-50 && gravityCollisionStore>=-90) || (gravityCollisionStore<=-230 && gravityCollisionStore>=-270)) && leftRight==2 && (bG==1))
        {gravityVanish04b=0; countGravity++;}
    if(((gravityCollisionStore<=-125 && gravityCollisionStore>=-160) || (gravityCollisionStore<=-305 && gravityCollisionStore>=-345)) && leftRight==2 && (bG==1))
        {gravityVanish06b=0; countGravity++;}

    //shootingColorChangeGravity();
}
void shootingColorChangePunch()
{
         if(rP==1 && gP==1 && bP==1)    { rP=gP=0; bP=1; }
    else if(rP==0 && gP==0 && bP==1)    { gP=bP=0; rP=1; }
    else if(rP==1 && gP==0 && bP==0)    { rP=bP=0; gP=1; }
    else if(rP==0 && gP==1 && bP==0)    { rP=gP=1; bP=0; }
    else if(rP==1 && gP==1 && bP==0)    { rP=bP=1; gP=0; }
    else if(rP==1 && gP==0 && bP==1)    { bP=gP=1; rP=0; }
    else if(rP==0 && gP==1 && bP==1)    { rP=gP=bP=0;       showPunchScore=true;}
}
void punchCollisionCheck()
{

    if((punchCollisionStore<=15 && punchCollisionStore>=13) && (rP==1 && gP==1 && bP==1))
    {
        punchVanish01rgb=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';

    }
    else if((punchCollisionStore<=11.8 && punchCollisionStore>=10.1) && (rP==1 && gP==0 && bP==0))
    {
        punchVanish02r=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';
    }
    else if((punchCollisionStore<=2.9 && punchCollisionStore>1.1) && (rP==0 && gP==0 && bP==1))
    {
        punchVanish05b=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';
    }
    else if((punchCollisionStore<=8.9 && punchCollisionStore>=7.1) && (rP==1 && gP==1 && bP==0))
    {
        punchVanish03g=0;punchVanish03r=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';
    }
    else if((punchCollisionStore<=5.9 && punchCollisionStore>=4.1) && (rP==0 && gP==1 && bP==0))
    {
        punchVanish04g=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';
    }
    else if((punchCollisionStore<=-0.1 && punchCollisionStore>=-1.9) && (rP==1 && gP==0 && bP==1))
    {
        punchVanish06r=0;punchVanish06b=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';
    }
    else if((punchCollisionStore<=-3.1 && punchCollisionStore>=-4.9) && (rP==0 && gP==1 && bP==1))
    {
        punchVanish07g=0;punchVanish07b=0;
        if(punchScore=='0')
            punchScore='1';
        else if(punchScore=='1')
            punchScore='2';
        else if(punchScore=='2')
            punchScore='3';
        else if(punchScore=='3')
            punchScore='4';
        else if(punchScore=='4')
            punchScore='5';
        else if(punchScore=='5')
            punchScore='6';
        else if(punchScore=='6')
            punchScore='7';
    }

    shootingColorChangePunch();
}
//float firstTime=true;
void update(int value)
{
	if(roundUpdate)
        {
            if(fire>3 && Rclick)
                {fire-=0.4;}
            else if(Rclick)
            {
                roundCollisionStore=-(angleRound);
                roundCollisionCheck();
                fire=7;
                Rclick=false;

            }
            if(roundUpdate)
            {
                angleRound+=1.0f;
                if (angleRound > 360)
                {
                    angleRound -= 360;
                }

            }
        }
    else if(gravityUpdate)
        {
            _circle_object_move -= 0.01f; //speed
            if (_circle_object_move < -2.5)
            {
                if(gravityDownCount=='3')
                    gravityDownCount='2';
                else if(gravityDownCount=='2')
                    gravityDownCount='1';
                else if(gravityDownCount=='1')
                    gravityDownCount='0';
                if(gravityDownCount=='0')
                    showGravityScore=true;

                _circle_object_move =0;
            }
            if(fire>-5 && Gclick)
                {
                    fire-=0.4;
                    if(fire==-2 || fire==1)
                        gravityCollisionCheck();
                }
            else if(Gclick)
            {
                gravityCollisionStore=-(angleGravity);
                gravityCollisionCheck();
                shootingColorChangeGravity();
                fire=7;
                Gclick=false;
            }
            if(gravityUpdate)
            {
                angleGravity+=1.0f;
                if (angleGravity > 360)
                {
                    angleGravity -= 360;
                }

            }
        }
    else if(punchUpdate)
        {
            if(punchfire>=-1.2 && Pclick)
                {punchfire-=0.2;}
            else if(Pclick)
            {
                punchCollisionStore=anglePunch;
                punchCollisionCheck();
                punchfire=0;
                Pclick=false;

            }
            if(punchUpdate)
            {
                if (!punchGoBack)
                    {
                    anglePunch +=0.15f;
                    if(anglePunch>16)
                        punchGoBack=true;
                    }
                if(punchGoBack)
                    {
                    anglePunch -=0.15f;
                        if(anglePunch<-7)
                            punchGoBack=false;
                    }

            }
        }
    else
        _angle += 2.0f;

	if (_angle > 360) {
		_angle -= 360;
	}

		if (!_circle_move_)
        {
		_circle_move +=0.08f;
		if(_circle_move>4)
            _circle_move_=true;
        }
        if(_circle_move_)
        {
        _circle_move -=0.08f;
            if(_circle_move<1)
                _circle_move_=false;
        }


	/*if (!_circle_move_1)
        {
		_circle_move1 +=0.15f;
		if(_circle_move1>16)
            _circle_move_1=true;
        }
    if(_circle_move_1)
        {
        _circle_move1 -=0.15f;
            if(_circle_move1<-7)
                _circle_move_1=false;
        }*/
	glutPostRedisplay();
	glutTimerFunc(35, update, 0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(400,50);

	glutCreateWindow("Color Switch Game");
	initRendering();
    glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
glutMouseFunc(myMouse);
glutSpecialFunc(keyboardown);
glutKeyboardFunc(keyboard);

	strcpy(quote[0], "Punch");
	strcpy(quote[1], "Gravity");
	strcpy(quote[2], "Round");
	strcpy(quote[3], "Navigation");
	strcpy(quote[4], "Color Switch Game");

	numberOfQuotes = 23;

	glutMainLoop();

	return 0;
}
