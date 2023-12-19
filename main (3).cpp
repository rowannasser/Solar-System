#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int width, height; // Size of the OpenGL window.
static float angle = 0.0; // Angle of the spacecraft.
static float xVal = 0, zVal = 30; // Co-ordinates of the spacecraft.
static int isCollision = 0; // Is there collision between the spacecraft and an asteroid?
static unsigned int spacecraft; // Display lists base index.
static int frameCount = 0; // Number of frames
float Moon_rotate=0.0, Earth_rotate=0.0,Astroid_rotate=0.0,Mars_rotate=0.0,Mercury_rotate=0.0,Venus_rotate=0.0,Jupiter_rotate=0.0,Saturn_rotate=0.0,Uranus_rotate=0.0,Neptune_rotate=0.0;
static int isAnimate = 0; // Animated?
static int animationPeriod = 20;
static float latAngle = 0.0; // Latitudinal angle.
static float longAngle = 0.0; // Longitudinal angle.
int font;

GLfloat scale_array[8]={3.8 , 5.0,7.0,9.8,12.4,15.5,17.9,  20.0};
double rotation_deg=2*(3.14)/50;
double rotation_deg1=2*(3.14)/300;
GLfloat Ambient_color[]={0.1,0.1,0.1,1.0};
GLfloat Diffuse_color[]={1.0,1.0,1.0,1.0};
GLfloat Specular_color[]={.50,.50,.50,.10};
GLfloat Yellow_color[]={0.7f,0.2f,0.0f,1.0f};
GLfloat temp_color1[]={0,0,0,0.1};
GLfloat Black_color[]={0.0f,0.0f,0.0f,1.0f};

// Planet class.
class Planet
{
public:
    Planet();
    Planet(float x, float y, float z, float r,double s, double c1,
             double c2, double c3);
    float getCenterX() { return centerX; }
    float getCenterY() { return centerY; }
    float getCenterZ() { return centerZ; }
    float getRadius() { return radius; }
    void draw(float ang, bool m);

private:
    float centerX, centerY, centerZ, radius;
    double s,c1,c2,c3;
};

// Planet default constructor.
Planet::Planet()
{
    centerX = 0.0;
    centerY = 0.0;
    centerZ = 0.0;
    radius = 0.0;
    s=0.0;
    c1 = 0;
    c2 = 0;
    c3 = 0;
}

// Planet constructor.
Planet::Planet(float x, float y, float z, float r, double scale,double colorR,
                   double colorG,  double colorB)
{
    centerX = x;
    centerY = y;
    centerZ = z;
    s=scale;
    radius = r;
    c1 = colorR;
    c2 = colorG;
    c3 = colorB;
}

// Function to draw asteroid.
void Planet::draw(float ang, bool m)
{
    if( radius > 0){
    if (m)
    {
        glPushMatrix();
        glRotatef(ang,0.0,1.0,0);
        glTranslatef(centerX, centerY, centerZ);
        glColor3d(c1,c2,c3);
        glScalef(s,s,s);
        glutSolidSphere(radius,50,50);

        glRotatef(Moon_rotate,0,1,0.5);
        glTranslatef(centerX-5.5, centerY, centerZ);
        glColor3d(1,1,1);
        glScalef(0.35,0.35,0.35);
        glutSolidSphere(0.8,50,50);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glRotatef(ang,0.0,1.0,0);
        glTranslatef(centerX, centerY, centerZ);
        glColor3d(c1,c2,c3);
        glScalef(s,s,s);
        glutSolidSphere(radius,50,50);
        glPopMatrix();
    }}
}

Planet arrayOfPlanets[8];

// Routine to count the number of frames drawn every second.
void frameCounter(int value)
{
    if (value != 0) // No output the first time frameCounter() is called (from main()).
        std::cout << "FPS = " << frameCount << std::endl;
    frameCount = 0;
    glutTimerFunc(1000, frameCounter, 1);
}

void Light_initialize()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT7);
    glLightfv(GL_LIGHT7,GL_AMBIENT,Ambient_color);
    glLightfv(GL_LIGHT7,GL_DIFFUSE,Diffuse_color);
    glLightfv(GL_LIGHT7,GL_SPECULAR,Specular_color);
}

void animate(int value)
{
    if (isAnimate)
    {
        latAngle += 5.0;
        if (latAngle > 360.0) latAngle -= 360.0;
        longAngle += 1.0;
        if (longAngle > 360.0) longAngle -= 360.0;

        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 0);
    }
}
// Initialization routine.
void setup(void)
{
    spacecraft = glGenLists(1);
    glNewList(spacecraft, GL_COMPILE);
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
    glColor3f(1.0, 1.0, 1.0);
    glutWireCone(2.0, 3.0, 10, 10);
    glPopMatrix();
    glEndList();

    // Initialize global arrayOfPlanets.
    //Mercury
    Planet Mercury(3.8, 0.0, 0,  0.3, 1.0, 1.0,0.9,0.0);  arrayOfPlanets[0] = Mercury;
    //Venus
    Planet Venus( 5.0,0.0, 0, 0.5,1.0 , 0.9,0.1,0.0);     arrayOfPlanets[1] = Venus;
    //Earth
    Planet Earth( 7.0,0.0, 0, 1.0,1.0 , 0.0,0.1,0.7);     arrayOfPlanets[2] = Earth;
    //Mars
    Planet Mars( 9.8,0.0, 0, 0.7,1.0,  0.6,0.2,0.3);      arrayOfPlanets[3] = Mars;
    //Jupiter
    Planet Jupiter( 12.4,0.0,0,  1.2, 1.0, 0.6,0.7,0.3);  arrayOfPlanets[4] = Jupiter;
    //Saturn
    Planet Saturn( 15.5, 0.0,0,  1.0,1.0,  0.9,0.0,0.0);   arrayOfPlanets[5] = Saturn;
    //Uranus
    Planet Uranus( 17.9,0.0,0, 0.7,0.7,  0.2,0.5,0.7);     arrayOfPlanets[6] = Uranus;
    //Neptune
    Planet Neptune(20,0.0, 0,  0.6, 0.9, 0.2,0.8,0.5);     arrayOfPlanets[7] = Neptune;

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutTimerFunc(0, frameCounter, 0); // Initial call of frameCounter().
}

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Function to check if two spheres centered at (x1,y1,z1) and (x2,y2,z2) with
// radius r1 and r2 intersect.
int checkSpheresIntersection(float x1, float y1, float z1, float r1, float x2, float y2, float z2, float r2)
{
    return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2) + (z1 - z2)*(z1 - z2) <= (r1 + r2)*(r1 + r2));
}

// Function to check if the spacecraft collides with an asteroid when the center of the base
// of the craft is at (x, 0, z) and it is aligned at an angle a to to the -z direction.
// Collision detection is approximate as instead of the spacecraft we use a bounding sphere.
int asteroidCraftCollision(float x, float z, float a)
{
    int i;
    // Check for collision with each asteroid.
        for (i = 0; i<8; i++)
            if (arrayOfPlanets[i].getRadius() > 0) // If asteroid exists.
                if (checkSpheresIntersection(x - 5 * sin((M_PI / 180.0) * a), 0.0,
                                             z - 5* cos((M_PI / 180.0) * a), 7.072,
                                             arrayOfPlanets[i].getCenterX(), arrayOfPlanets[i].getCenterY(),
                                             arrayOfPlanets[i].getCenterZ(), arrayOfPlanets[i].getRadius()))
                    return 1;
    return 0;
}

void display_orbit()
{
    glColor3f(0.5,0.5,0.5);

    int i=0;
    for(i=0;i<8;i++){
        glPushMatrix();
        glRotatef(90,1.0,0.0,0.0);
        glScalef(scale_array[i],scale_array[i],scale_array[i]);
        glBegin(GL_POINTS);

        double rotation_deg2=0.0;
        int i;
        for(i=0;i<300;i++)
        {
            glVertex2d(cos(rotation_deg2),sin(rotation_deg2));
            rotation_deg2+=rotation_deg1;
        }

        glEnd();
        glPopMatrix();
    }
}

// Drawing routine.
void drawScene(void)
{
    frameCount++; // Increment number of frames every redraw.
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Beg	in left viewport.
    glViewport(500, 0, 300, height/3);//demo
    glLoadIdentity();

  // Write text in isolated (i.e., before gluLookAt) translate block.
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos3f(-28.0, 25.0, -30.0);
    if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
    glPopMatrix();

    // Fixed camera.
    gluLookAt(0.0, 22.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    display_orbit();

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glColor3f(0.7,0.5,0.0);
    glTranslatef(0.0,0.0,0.0);
    glLightfv(GL_LIGHT7,GL_POSITION,temp_color1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Yellow_color);
    glutSolidSphere(3,50,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Black_color);
    glPopMatrix();

    float ang=0;
    // Draw all the asteroids in arrayAsteroids.
   for (i = 0; i<8; i++) { bool m= false;
       if(i==0){ang =Mercury_rotate ;}
       else if(i==1){ang = Venus_rotate;}
       else if(i==2){ang =Earth_rotate ;m = true;}
       else if(i==3){ang =Mars_rotate ;}
       else if(i==4){ang =Jupiter_rotate ;}
       else if(i==5){ang = Saturn_rotate;}
       else if(i==6){ang = Uranus_rotate;}
       else if(i==7){ang = Neptune_rotate;}

       arrayOfPlanets[i].draw(ang,m);
   }
    // Draw spacecraft.
    glPushMatrix();
    glTranslatef(xVal-3, 0.0, zVal-5);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glCallList(spacecraft);
    glPopMatrix();
    // End left viewport.

    // Begin right viewport.
    glViewport(0, 0, width, height);
    glLoadIdentity();

    // Write text in isolated (i.e., before gluLookAt) translate block.
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos3f(-28.0, 25.0, -30.0);
    if (isCollision) writeBitmapString((void*)font, "Cannot - will crash!");
    glPopMatrix();

    // Draw a vertical line on the left of the viewport to separate the two viewports
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex3f(1.2, -5.0, -5.0);
    glVertex3f(1.2, -1.8, -5.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(1.2, -1.8, -5.0);
    glVertex3f(5, -1.8, -5.0);
    glEnd();
    glLineWidth(1.0);

    gluLookAt(xVal - 10 * sin((M_PI / 180.0) * angle),
              0.0,
              zVal -4 * cos((M_PI / 180.0) * angle),
              xVal - 11 * sin((M_PI / 180.0) * angle),
              0.0,
              zVal - 11 * cos((M_PI / 180.0) * angle),
              0.0,
              1.0,
              0.0);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    glColor3f(0.7,0.5,0.0);
    glTranslatef(0.0,0.0,0.0);
    glLightfv(GL_LIGHT7,GL_POSITION,temp_color1);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Yellow_color);
    glutSolidSphere(3,50,50);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Black_color);
    glPopMatrix();
    // Draw all the asteroids in arrayAsteroids.
    for (i = 0; i<8; i++) {bool m = false;
        if(i==0){ang =Mercury_rotate ;}
        else if(i==1){ang = Venus_rotate;}
        else if(i==2){ang =Earth_rotate ; m = true;}
        else if(i==3){ang =Mars_rotate ;}
        else if(i==4){ang =Jupiter_rotate ;}
        else if(i==5){ang = Saturn_rotate;}
        else if(i==6){ang = Uranus_rotate;}
        else if(i==7){ang = Neptune_rotate;}

        arrayOfPlanets[i].draw(ang,m);
    } // End right viewport.

    glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
    glMatrixMode(GL_MODELVIEW);

    // Pass the size of the OpenGL window.
    width = w;
    height = h;
}

void change_axis(int xc){
    if (isAnimate){
        Moon_rotate+=2;
        if(Moon_rotate>360){
            Moon_rotate-=360;
        }

        Earth_rotate+=0.7;
        if(Earth_rotate>360){
            Earth_rotate-=360;
        }

        Mercury_rotate+=2;
        if(Mercury_rotate>360){
            Mercury_rotate-=360;
        }

        Venus_rotate+=0.9;
        if(Venus_rotate>360){
            Venus_rotate-=360;
        }

        Mars_rotate+=0.5;
        if(Mars_rotate>360){
            Mars_rotate-=360;
        }

        Jupiter_rotate+=0.2;
        if(Jupiter_rotate>360){
            Jupiter_rotate-=360;
        }

        Saturn_rotate+=0.1;
        if(Saturn_rotate>360){
            Saturn_rotate-=360;
        }


        Uranus_rotate+=0.09;
        if(Uranus_rotate>360){
            Uranus_rotate-=360;
        }


        Neptune_rotate+=0.07;
        if(Neptune_rotate>360){
            Neptune_rotate-=360;
        }


        Astroid_rotate+=0.05;
        if(Astroid_rotate>360){
            Astroid_rotate-=360;
        }

        glutPostRedisplay();
        glutTimerFunc(animationPeriod,change_axis,1);

    }
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case ' ':
            if (isAnimate) isAnimate = 0;
            else
            {
                isAnimate = 1;
                change_axis(1);
            }
            break;
        case '-': animationPeriod += 5;
            break;
        case '+': if (animationPeriod > 5) animationPeriod -= 5;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    float tempxVal = xVal, tempzVal = zVal, tempAngle = angle;

    // Compute next position.
    if (key == GLUT_KEY_LEFT) tempAngle = angle + 5.0;
    if (key == GLUT_KEY_RIGHT) tempAngle = angle - 5.0;
    if (key == GLUT_KEY_UP)
    {
        tempxVal = xVal - sin(angle * M_PI / 180.0);
        tempzVal = zVal - cos(angle * M_PI / 180.0);
    }
    if (key == GLUT_KEY_DOWN)
    {
        tempxVal = xVal + sin(angle * M_PI / 180.0);
        tempzVal = zVal + cos(angle * M_PI / 180.0);
    }

    // Angle correction.
    if (tempAngle > 360.0) tempAngle -= 360.0;
    if (tempAngle < 0.0) tempAngle += 360.0;

    // Move spacecraft to next position only if there will not be collision with an asteroid.
    if (!asteroidCraftCollision(tempxVal, tempzVal, tempAngle))
    {
        isCollision = 0;
        xVal = tempxVal;
        zVal = tempzVal;
        angle = tempAngle;
    }
    else isCollision = 1;

    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    std::cout << "Interaction:" << std::endl;
    std::cout << "Press the left/right arrow keys to turn the craft." << std::endl
              << "Press the up/down arrow keys to move the craft." << std::endl
              << "Press the +/- keys to increase/decrease the speed of the system." << std::endl
              << "Press the space key to run and stop the system." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System Simulation.cpp");

    Light_initialize();
    glutDisplayFunc(drawScene);
    glutTimerFunc(25,change_axis,0);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}



