#include<stdio.h>
#include<math.h>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>       /* cos */
#include "RGBpixmap.cpp"
#define PI 3.14159265

RGBpixmap pix[10];
int w,h;
static int slices = 16;
static int stacks = 16;
double xx=0,yy=0,zz=0;
double translate_x=0,translate_y=0,translate_z=0;
double rot_x=0,rot_y=0,rot_z=0;
double zoom_x=0,zoom_y=0,zoom_z=0;
double eye_x = 0;
double eye_y = 0;
double eye_z = 25;
double cx=0,cy=0,cz=0;
double rott_x,rott_y,rott_z;
int flag=0;
static GLdouble CameraRad = 10;
static GLdouble CameraTheta = 0;
static GLdouble camHeight = 0;
static GLdouble camRoll = 90;
static GLdouble CameraCenterX = 0;
static GLdouble CameraCenterY = 0;
static GLdouble CameraCenterZ = 0;
void ownscal(double x,double y,double z)
{
    GLfloat mat[]=
    {
        x,0,0,0,
        0,y,0,0,
        0,0,z,0,
        0,0,0,1


    };
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(mat);


}
float vertexCoords[24] =    // Coordinates for the vertices of a cube.
{
    0,0,0,
    1,0,1,
    0,0,1,
    0,1,1,
    1,1,1,
    1,0,0,
    0,1,0,
    1,1,0
};
float vertexColors[24] =    // An RGB color value for each vertex
{
    0.098, 0.054, 0.403,   0.098, 0.054, 0.403,   0.098, 0.054, 0.403,   0.098, 0.054, 0.403,
    0.098, 0.054, 0.403,   0.098, 0.054, 0.403,   0.098, 0.054, 0.403,   0.098, 0.054, 0.403
};
int elementArray[24] =    // Vertex number for the six faces.
{
    2,3,4,1,
    4,7,5,1,
    0,6,3,2,
    7,6,0,5,
    3,6,7,4,
    5,0,2,1
};
static void LookAtView()
{
    GLdouble AngleRad = CameraTheta * PI / 180.0;

    GLdouble cosAngle = cos(AngleRad);
    GLdouble sinAngle = sin(AngleRad);
    GLdouble CameraZ = CameraRad * cosAngle;
    GLdouble CameraX = CameraRad * sinAngle;
    GLdouble CameraY = camHeight;


    GLdouble upX = 1, upY = 0, upZ = 0;
    GLdouble tX, tY, tZ;

    GLdouble rollInRadians = camRoll * PI / 180.0;
    tX = cos(rollInRadians) * upX - sin(rollInRadians) * upY;
    tY = sin(rollInRadians) * upX + cos(rollInRadians) * upY;
    upX = tX, upY = tY;
    tX = cosAngle * upX + sinAngle * upZ;
    tZ = -sinAngle * upX + cosAngle * upZ;
    upX = tX, upZ = tZ;
    gluLookAt(CameraX, CameraY, CameraZ, CameraCenterX, CameraCenterY, CameraCenterZ, upX, upY, upZ);
}


void draw_cube()
{

    glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertexCoords );
    //glColorPointer( 3, GL_FLOAT, 0, vertexColors );
    glEnable(GL_POLYGON_OFFSET_FILL);
    glDrawElements( GL_QUADS, 24, GL_UNSIGNED_INT, elementArray );
    glDisable(GL_POLYGON_OFFSET_FILL);
    //glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState(GL_VERTEX_ARRAY);

}
static void cube()
{
    glEnableClientState( GL_VERTEX_ARRAY );
    //glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertexCoords );
    //glColorPointer( 3, GL_FLOAT, 0, vertexColors );
    glEnable(GL_POLYGON_OFFSET_FILL);
    glDrawElements( GL_QUADS, 24, GL_UNSIGNED_INT, elementArray );
    glDisable(GL_POLYGON_OFFSET_FILL);
    //glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState(GL_VERTEX_ARRAY);
}

static void resize(int width, int height)
{
    w=width;
    h=height;
    const float ar = (float) (width/2) / (float) height;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ar2=1.8;
    glFrustum(-ar2, ar2, -ar2, ar2, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt(0, 0, 25, 0, 0, 0, 0, 1, 0);
}

static void blade(GLdouble scaley, GLdouble rot_angle, GLdouble rot_x, GLdouble rot_y, GLdouble rot_z)
{
    glPushMatrix();
    glRotated(rot_angle, rot_x, rot_y, rot_z);
    glRotated(20, 0, 1, 0);
    glScaled(-.20, -1, 3.50);
    glTranslated(0, 0, -1);
    draw_cube();
    glPopMatrix();
}
static void fan()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    blade(-3, 0+t*250, 0,1, 0);
    blade(-3, 120+t*250, 0, 1, 0);
    blade(-3, 240+t*250, 0, 1, 0);
}
void cube(double translate_x,double translate_y,double translate_z,double rotate_x,double rotate_y,double rotate_z,double scale_x,double scale_y,double scale_z)
{
    glPushMatrix();
    //glColor3d(0.325, 0.176, 0.823);
    glTranslated(translate_x,translate_y,translate_z);
    glRotated(rotate_x,1,0,0);
    glRotated(rotate_y,0,1,0);
    glRotated(rotate_z,0,0,1);
    ownscal(scale_x,scale_y,scale_z);
    draw_cube();
    glPopMatrix();

}
void circle()
{
   float theta=(22.0/7.0)/180.0;
    glTranslated(-.70,0,8);

    glRotated(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<360; i++)
    {
        //glColor3d(1,0,0);
        glVertex3f(cos(theta*i),+1,sin(theta*i));
        //glColor3d(1,0,0);
        glVertex3f(cos(theta*i),-1,sin(theta*i));
    }
    glEnd();
    float k=0;
    for(int i=1; i>=-1; i-=2)
    {
        glBegin(GL_TRIANGLE_FAN);

        glVertex3f(0,i,0);
        for(k=0; k<360; k++)
        {
            //glColor3d(1,0,0);
            glVertex3f(i*cos(k*theta),i+.01,sin(k*theta));
            glVertex3f(i*cos(k*theta),-i,sin(k*theta));

        }
        glEnd();
    }
}
void rod()
{

    glBindTexture(GL_TEXTURE_2D,2);
	glEnable(GL_TEXTURE_2D);

    const GLfloat mat_ambient[]    = { 0.0f, 0.0f, 0.5f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.078f, 0.062f, 0.717f, 1.0f };
    const GLfloat mat_specular[]   = { 0.0f, 0.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    cube(-.50,-3.80,4.40,0,0,0,1.30,.40,.40);
    cube(-.50,3.40,4.40,0,0,0,1.30,.40,.40);
    cube(.60,-4.40,4.40,0,0,0,.30, 9.10,0.40);
    cube(-.60,-4.40,4.40,0,0,0,.30, 9.10,0.40);

    cube( -0.50,-2.70,3.20,0,0,0,1.10,0.40,0.30);
    cube( -0.50,+2.70,3.20,0,0,0,1.10,0.40,0.30);

    cube( .20,-2.90,3.50,0,0,0,.40,5.70,-.20);
    cube( -.20,-2.90,3.50,0,0,0,.40,5.70,-.20);

    glDisable(GL_TEXTURE_2D);
}
void wall()
{


    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    cube(.80+1,3.10+0,2+0,0*20,2*20,0*20,.4-.60,+6.10-4.20,4.80-3.60);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,10);
	glEnable(GL_TEXTURE_2D);
    cube(-2.40,2.20,-3.20,0,-1*50,0,.4,6.10,4.80);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,9);
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    const GLfloat mat_ambient[]    = { 0.5f, 0.5f, 0.0f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.078f, 0.062f, 0.717f, 1.0f };
    const GLfloat mat_specular[]   = { 0.0f, 0.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);





    cube(0,0,0,0,-1*50,0,.4,6.10-3.50,4.80);
    cube(0,0,0,0,-1*50,0,.4,6.10,4.80-3.00);
    cube(0,5,0,0,-1*50,0,.4,6.10-5,4.80+0);
    cube(0-2.20,0+0,0+1.80,0,-1*50,0,.4,6.10,4.80-2.80);


    const GLfloat mat_ambient2[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat mat_diffuse2[]    = { 1.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat mat_specular2[]   = { 1.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat high_shininess2[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess2);

    cube(0,0,0,0*20,2*20,0*20,.4,+6.10,4.80);


    const GLfloat mat_ambient3[]    = { 1.0f, 1.0f, 0.0f, 1.0f };
    const GLfloat mat_diffuse3[]    = { 1.0f, 1.0f, 0.0f, 1.0f };
    const GLfloat mat_specular3[]   = { 1.0f, 1.0f, 0.0f, 1.0f };
    const GLfloat high_shininess3[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess3);
    cube(0,0,0,0*20,-2.50*20,-4.50*20,.4+.1,6.10-1.30,4.80);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);







}

void table()
{
    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);
    glPushMatrix();

     const GLfloat mat_ambient[]    = { 0.545, 0.349, 0.054, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.545, 0.349, 0.054, 1.0f };
    const GLfloat mat_specular[]   = { 0.545, 0.349, 0.054, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


	cube(0,0,0,0,0,0,.4-0.30,+6.10-3.50,4.80-4.70);

    cube(0,0,1.40,0,0,0,.4-0.30,+6.10-3.50,4.80-4.70);

    cube(1.40,0,0,0,0,0,.4-0.30,+6.10-3.50,4.80-4.70);

    cube(1.40,0,1.40,0,0,0,.4-0.30,+6.10-3.50,4.80-4.70);


    cube(-.90,2.40,-.10,0,0,0,  2.10+1, -.80+1 ,.70+1  );










    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void windmill()
{

    {
        ///Rod
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,7);
        glEnable(GL_TEXTURE_2D);
        const GLfloat mat_ambient[]    = { 0.0f, 0.0f, 0.5f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.078f, 0.062f, 0.717f, 1.0f };
        const GLfloat mat_specular[]   = { 0.0f, 0.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        cube(0,0,0,-5,0,-5,.50,13.80,.5);

        cube(0,0,-2.90,5,0,-5,.50,13.80,.5);

        cube(2.70,0,0,-5,0,5,.50,13.80,.5);

        cube(2.70,0,-2.90,5,0,5,.50,13.80,.5);

        glPopMatrix();

    }

    {
        ///chakti


        const GLfloat mat_ambient3[]    = { .5, 0.0f, 0.0f, 1.0f };
        const GLfloat mat_diffuse3[]    = { .8, 0.0f, 0.0f, 1.0f };
        const GLfloat mat_specular3[]   = { .5, 0.0f, 0.0f, 1.0f };
        const GLfloat high_shininess3[] = { 100.0f };

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess3);

        glTranslated(2.70,13.50,1.20);

        glScaled(1.8,2.50,-.30);

        circle();

    }

    glPushMatrix();
    glTranslated(0,-4.10,.30);
    fan();
    glPopMatrix();


    {
        glPushMatrix();
        glTranslated(.30,-.80,-1.30);
        glScaled(.30,4.1,.20);
        const GLfloat mat_ambient2[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat mat_diffuse2[]    = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat mat_specular2[]   = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat high_shininess2[] = { 100.0f };

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess2);
        circle();
        glPopMatrix();
    }


    rod();
    glDisable(GL_TEXTURE_2D);

}
void jack(){
    //First leg of jack

    glBindTexture(GL_TEXTURE_2D,4);
	glEnable(GL_TEXTURE_2D);
glPushMatrix();
    glPushMatrix();
        glTranslated(3,10,13.0);
        glScalef(.6,1.4,3.1);
        glutSolidSphere (1.0, 20, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslated(3,-4.5,-6.5);
        glScalef(.6,1.4,3.1);
        glutSolidSphere (1.0, 20, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslated(3,2.9,3.5);
        glRotated(55,1,0,0);
        glScalef(.5,11.5,3.0);
        glutSolidSphere (1.0, 20, 16);
    glPopMatrix();

//Second leg of jack

    glPushMatrix();
        glTranslated(1.2,10,-1.5);
        glScalef(.6,1.4,3.1);
        glutSolidSphere (1.0, 20, 16);
    glPopMatrix();

    glPushMatrix();

        //glColor3f(1,1,0);
        glTranslated(4.8,-4.5,8.5);
        glScalef(.6,1.4,3.1);
        glutSolidSphere (1.0, 20, 16);

    glPopMatrix();

    glPushMatrix();

        glTranslated(2.9,3.1,3.5);
        glRotated(14,0,0,1);
        glRotated(-40,1,0,0);
        glScalef(.7,8.6,3.1);
        glutSolidSphere (1.0, 20, 16);

    glPopMatrix();

//Third leg of jack

    glPushMatrix();


        glTranslated(4.8,10,-1.5);
        glScalef(.6,1.4,3.1);
        glutSolidSphere (1.0, 20, 16);

    glPopMatrix();

    glPushMatrix();


        glTranslated(1.2,-4.5,8.5);
        glScalef(.6,1.4,3.1);
        glutSolidSphere (1.0, 20, 16);

    glPopMatrix();

    glPushMatrix();

        glTranslated(3.0,2.9,3.5);
        glRotated(-14,0,0,1);
        glRotated(-40,1,0,0);
        glScalef(.7,8.6,3.1);
        glutSolidSphere (1.0, 20, 16);

        glPopMatrix();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

}

void rotated(int am,int bm,int cm){
    glRotated(am,1,0,0);
    glRotated(bm,0,1,0);
    glRotated(cm,0,0,1);
}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity() ;
    LookAtView();
    rotated(-15,0,0);
    glPushMatrix();
    glRotated(.80*20,1,0,0);
    glTranslated(-.70,-1.20,0);
    glPushMatrix();
    glTranslated(-.60,-.20,3.20);
    table();
    glPopMatrix();
    glPushMatrix();
    wall();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    rotated(10,10,0);
    glTranslated(0-.50, 0+.80,4+.30);
    glScaled(-.90+1,-.90+1,-.90+1);
    windmill();
    glPopMatrix();

    glPushMatrix();
    rotated(3+6,-3+0,3+0);
    glScaled(.10,.10,.10-.05);
    glTranslated(-12.50+0,8+6,79+0);
    jack();

    glPopMatrix();

    glPushMatrix();
    //cube(-3,3,4.20,0,0,0,-1.50+1,0+1,zz+1); //my test
    glPopMatrix();


    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    double translate=.1;
    double rotation=1;
    double scale2=.1,lookat=.1;
    double changef=.2;

    switch (key)
    {

    case 'p':
        glDisable( GL_LIGHT0);
        glEnable( GL_LIGHT1);

        break;
    case 'P':
        glEnable( GL_LIGHT0);
        glDisable( GL_LIGHT1);
        break;
    case 'o':
        glDisable( GL_LIGHT0);
        glDisable( GL_LIGHT1);
        break;
    case 't':
        if (flag==1)
        {
            CameraRad -= 1;///radius change

        }
        else
        {
            translate_x+=translate;
            printf("translate_x: %.2f ",translate_x);
        }

        break;
    case 'T':
        if (flag==1)
        {
            CameraRad += 1;

        }
        else
        {
            translate_x-=translate;
            printf("translate_x: %.2f ",xx);
        }


        break;
    case 'y':
        if (flag==1)
        {
            CameraTheta -= 5;///yaw

        }
        else
        {
            translate_y+=translate;
            printf("translate_y: %.2f ",translate_y);
        }

        break;
    case 'Y':
        if (flag==1)
        {
            CameraTheta += 5;

        }
        else
        {
            translate_y-=translate;
            printf("translate_y: %.2f ",translate_y);
        }

        break;
    case 'u':
        if (flag==1)
        {
            camHeight += 1;///pitch

        }
        else
        {
            translate_z+=translate;
            printf("translate_z: %.2f ",translate_z);
        }


        break;
    case 'U':
        if (flag==1)
        {
            camHeight -= 1;

        }
        else
        {
            translate_z-=translate;
            printf("translat.e_z: %.2f ",translate_z);
        }

        break;

    case 'r':
        if (flag==1)
        {
            CameraCenterX+=1;

        }
        else
        {
            rot_x+=rotation;
            printf("rot_x: %.2f ",rot_x);
        }


        break;
    case 'R':
        if (flag==1)
        {
            CameraCenterX-=1;

        }
        else
        {
            rot_x-=rotation;
            printf("rot_x: %.2f ",rot_x);
        }




        break;
    case 'e':
        if (flag==1)
        {
            CameraCenterY+=1;

        }
        else
        {
            rot_y+=rotation;
            printf("rot_y: %.2f ",rot_y);
        }

        break;
    case 'E':

        if (flag==1)
        {
            CameraCenterY-=1;

        }
        else
        {
            rot_y-=rotation;
            printf("rot_y: %.2f ",rot_y);
        }

        break;


    case 'w':
        if (flag==1)
        {
            CameraCenterZ+=1;

        }
        else
        {
            rot_z+=rotation;
            printf("rot_z: %.2f ",rot_z);
        }

        break;
    case 'W':
        if (flag==1)
        {
            CameraCenterZ-=1;

        }
        else
        {
            rot_z-=rotation;
            printf("rot_z: %.2f ",rot_z);
        }
        break;

    case 's':
        if (flag==1)
        {
            camRoll -= 5;///Roll

        }
        else
        {
            zoom_x+=scale2;
            printf("zoom_x: %.2f ",zoom_x);
        }


        break;
    case 'S':
        if (flag==1)
        {
            camRoll += 5;

        }
        else
        {
            zoom_x-=scale2;
            printf("zoom_x: %.2f ",zoom_x);
        }



        break;
    case 'd':
        zoom_y+=scale2;
        //printf("xx: %.2f ",zz);
        break;
    case 'D':
        zoom_y-=scale2;
        //printf("xx: %.2f ",zz);
        break;
    case 'f':
        zoom_z+=scale2;
        //printf("xx: %.2f ",zz);
        break;
    case 'F':
        zoom_z-=scale2;
        //printf("xx: %.2f ",zz);
        break;
    case 'j':
        eye_x+=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'J':
        eye_x-=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'k':
        eye_y+=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'K':
        eye_y-=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'l':
        eye_z+=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'L':
        eye_z-=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'b':
        cx+=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'B':
        cx-=lookat;
        //printf("xx: %.2f ",zz);
        break;

    case 'n':
        cy+=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'N':
        cy-=lookat;
        //printf("xx: %.2f ",zz);
        break;

    case 'm':
        cz+=lookat;
        //printf("xx: %.2f ",zz);
        break;
    case 'M':
        cz-=lookat;
        //printf("xx: %.2f ",zz);
        break;

    case '1':
        xx+=changef;
        //printf("xx: %.2f ",zz);
        break;
    case '4':
        xx-=changef;
        //printf("xx: %.2f ",zz);
        break;
    case '2':
        yy+=changef;
        //printf("xx: %.2f ",zz);
        break;
    case '5':
        yy-=changef;
        //printf("xx: %.2f ",zz);
        break;
    case '3':
        zz+=changef;
        //printf("xx: %.2f ",zz);
        break;
    case '6':
        zz-=changef;
        //printf("xx: %.2f ",zz);
        break;



    case 'q':
        printf("\nzoom_x: %.2f zoom_y: %.2f zoom_z: %.2f",zoom_x,zoom_y,zoom_z);
        printf("\ntranslate_x: %.2f translate_y: %.2f translate_z: %.2f",translate_x,translate_y,translate_z);
        printf("\nrotate_x: %.2f rotate_y: %.2f rotate_z: %.2f",rot_x,rot_y,rot_z);
        printf("\ncx: %.2f cy: %.2f cz: %.2f\n",cx,cy,cz);

        if (xx!=0.0)
            printf("\nxx: %.2f\n",xx);
        if (yy!=0.0)
            printf("yy: %.2f\n",yy);
        if (zz!=0.0)
            printf("zz: %.2f\n",zz);

        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices>3 && stacks>3)
        {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}
void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };
    GLfloat light_position[] = { 0.0, 200.0, 0.0, 1.0 };

    glEnable( GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 25.0);


    glEnable( GL_LIGHT1);
    GLfloat light_position2[] = { 0.0, 200.0, 0.0, 0.0 };
    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position2);
    GLfloat spot_direction2[] = { 0.0, -1.0, 0 };
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction2);
    glLightf( GL_LIGHT1, GL_SPOT_CUTOFF, 40.0);


}

void Init()
{


    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\teapot.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\jack.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\table.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\cone.bmp");
	pix[4].setTexture(5);

	pix[5].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\image\\img.bmp");
	pix[5].setTexture(6);

	pix[6].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\image\\img7.bmp");
	pix[6].setTexture(7);

	pix[7].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\image\\img6.bmp");
	pix[7].setTexture(8);

	pix[8].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\image\\img5.bmp");
	pix[8].setTexture(9);

	pix[9].readBMPFile("C:\\Users\\Inception\\Desktop\\New folder\\lab4 texturing\\image\\Polaris.bmp");
	pix[9].setTexture(10);


}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Windmill");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    light();
    Init();


    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    printf("Enter 1 for camera and 0 for object mode\n");
    scanf("%d",&flag);


    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
