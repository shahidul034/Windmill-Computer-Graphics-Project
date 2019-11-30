
#include<stdio.h>
#include <GL/glut.h>
#include <map>
using namespace std;
int flag=0;
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

static GLdouble CameraRad = 10;
static GLdouble CameraTheta = 0;
static GLdouble camHeight = 0;
static GLdouble camRoll = 90;
static GLdouble CameraCenterX = 0;
static GLdouble CameraCenterY = 0;
static GLdouble CameraCenterZ = 0;
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

