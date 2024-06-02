#include<windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#define OMINO 2
#define PI 3.1415
GLint i=0;
GLfloat t=4;

struct Point
{
    float x, y;
    unsigned char r, g, b, a;
};
std::vector< Point > points;

// Rotazione scena
GLfloat y_rot = 0;
GLfloat x_rot = 0;

// Luce ambientale globale
GLfloat global_ambient[] = {0.8f,0.8f,0.8f,1.0f};

// Luce direzionale
GLfloat dir_ambient[] = {5.6f,0.6f,0.6f,1.0f};
GLfloat dir_diffuse[] = {0.7f,0.7f,0.7f,1.0f};
GLfloat dir_specular[] = {1.0f,1.0f,1.0f,1.0f};

// Posizione luce
GLfloat dir_position[] = {1.0f,0.0f,1.0f,0.0f};

// Color Material - Specular
GLfloat mat_specular[] = {5.6,0.6,0.6,1.0};

// Distanza radiale
GLfloat rad_dist = 17.0f;

// Numero omini
GLint n_omini = 12;

// Raggio
GLfloat raggio =10;

// Nebbia
bool fog = false;
GLint fog_mode;
GLfloat fog_color[] = {1.5,0.5,1.5,1.0};


void init()
 {
    glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightfv(GL_LIGHT0,GL_AMBIENT, dir_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, dir_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR, dir_specular);

	glLightfv(GL_LIGHT0,GL_POSITION,dir_position);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMateriali(GL_FRONT,GL_SHININESS,30);

	fog_mode = GL_LINEAR;
    glFogi (GL_FOG_MODE, fog_mode);
    glFogfv (GL_FOG_COLOR, fog_color);
    glFogf (GL_FOG_DENSITY, 3);
    glHint (GL_FOG_HINT, GL_DONT_CARE);
    glFogf (GL_FOG_START,30);
    glFogf (GL_FOG_END, 90);

    glClearColor(0,0,0,0);

	glNewList(OMINO,GL_COMPILE);
		// SFERA
		glColor3f(0.72,0.45,0.20);

        glPushMatrix();

   //draw the cylinder body
        glTranslated( 0,-3,0);
        glRotated(0, -1.0, 0.0, 0.0);

        glBegin(GL_POLYGON);
        GLUquadricObj *obj = gluNewQuadric();

       gluCylinder(obj, .09, .09, 20, 8, 20);

        glPopMatrix();

       glColor3f(0.8,.49,0.19);
        glPushMatrix();
        glTranslated(0.0,0.2,0);
        glRotated(65, -1.0, 0.0, 0.0);
        glutSolidCone(1.5, 2, 50, 50);
    glPopMatrix();
        glColor3f(0.85,.53,0.10);
     glPushMatrix();
        glTranslated(0.5,2,0);
        glRotated(90, -1.0, 0.0, 0.0);
        glutWireCone(t,2, 16, 16);
    glPopMatrix();
        glColor3f(0.65,.50,0.39);
        glPushMatrix();

   //draw the cylinder body
        glTranslated( .4,1,0);
        glRotated(90, -1.0, 0.0, 0.0);

        glBegin(GL_POLYGON);
        //GLUquadricObj *obj = gluNewQuadric();

        gluCylinder(obj, .09, .09, 3, 8, 20);

        glPopMatrix();

        glColor3f(0.3,0,0);

		glutSolidSphere(1,50,50);

		//TRONCO
		glColor3f(0,0.2,0);


			//Base Superiore
			glBegin(GL_TRIANGLES);
				glVertex3f(0,-5,-1); // v1
				glVertex3f(-sqrt(5)/2,-1,0.5f); // v2
				glVertex3f(sqrt(5)/2,-1,0.5f); // v3

			glEnd();
			glBegin(GL_LINES);
				glVertex3f(0,5,1); // v1
				glVertex3f(-sqrt(5)/2,-1,0.5f); // v2
				glVertex3f(sqrt(5)/2,-1,0.5f); // v3

			glEnd();


			// Base inferiore
			glBegin(GL_TRIANGLES);
				glVertex3f(0,-4,-2); // v4
				glVertex3f(sqrt(5),-4,1.0f); // v5
				glVertex3f(-sqrt(5),-4,1.0f); // v6

			glEnd();

			// Faccia sx
			glBegin(GL_QUADS);
				glVertex3f(0,-2,-1); // v1
				glVertex3f(0,-4,-2); // v4
				glVertex3f(-sqrt(5),-4,1.0f); // v6
				glVertex3f(-sqrt(5)/2,-1,0.5f); // v2

			glEnd();

			// Faccia dx
			glBegin(GL_QUADS);
				glVertex3f(sqrt(5)/2,-1,0.5f); // v3
				glVertex3f(sqrt(5),-4,1.0f); // v5
				glVertex3f(0,-4,-2); // v4
				glVertex3f(0,-4,-1); // v1
			glEnd();

			// Faccia cx
			glBegin(GL_QUADS);
				glVertex3f(-sqrt(5)/2,-1,0.5f); // v2
				glVertex3f(-sqrt(5),-4,1.0f); // v6
				glVertex3f(sqrt(5),-4,1.0f); // v5
				glVertex3f(sqrt(5)/2,-1,0.5f); // v3
			glEnd();
			glBegin(GL_QUADS);
				glVertex3f(-sqrt(5)/2,-1,0.5f); // v2
				glVertex3f(-sqrt(5),-4,1.0f); // v6
				glVertex3f(sqrt(5),-4,1.0f); // v5
				glVertex3f(sqrt(5)/2,-1,0.5f); // v3
			glEnd();



	glEndList();
}



void draw_scene()
 {

	glShadeModel(GL_SMOOTH);
	for(int i=1; i < n_omini; i++)
        {
		raggio = (360.0/n_omini)*i;
			glPushMatrix();
				glRotatef(raggio,0,1,0);
				glTranslatef(rad_dist,0,0);
				glRotatef(-90,0,1,0);
				glCallList(OMINO);
			glPopMatrix();
	}
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
		glRotatef(x_rot,1,0,0);
		glRotatef(y_rot,0,1,0);
		draw_scene();
	glPopMatrix();

	glPushMatrix();
	glColor3f(.90,.91,.98);
        glTranslated(22,12.2,0);
        glRotated(65, -1.0, 0.0, 0.0);
        glutSolidSphere(1,50,50);
    glPopMatrix();

   glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, sizeof(Point), &points[0].x );
    glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(Point), &points[0].r );
    glPointSize( 3.0 );
    glDrawArrays( GL_POINTS, 0, points.size() );
    glDisableClientState( GL_VERTEX_ARRAY );

    glFlush();

     glPushMatrix();

   //draw the cylinder body
        glTranslated( 0,-3,0);
        glRotated(90, -1.0, 0.0, 0.0);

        glBegin(GL_POLYGON);
        GLUquadricObj *obj = gluNewQuadric();

        gluCylinder(obj, .09, .09, 17, 8, 20);

        glPopMatrix();

        glColor3f(0.85,.53,0.10);
     glPushMatrix();
        glTranslated(0,9.5,0);
        glRotated(90, -1.0, 0.0, 0.0);
        glutWireCone(18,5, 16, 50);
    glPopMatrix();



	glutSwapBuffers();
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
		case 'z':
					y_rot -= 2.0f;
					break;
		case 'x': 	y_rot += 2.0f;
					break;
		case 'c':
					x_rot += 2.0f;
					break;
		case 'v':
					x_rot -= 2.0f;
					break;
		case '+':
					rad_dist += 0.1f;
					break;
		case '-':
					rad_dist -= 0.1f;
					break;
		case 'w':
					if(n_omini < 12)
						n_omini++;
					break;
		case 's':
					if(n_omini > 2)
						n_omini--;
					break;
		case 'b':
					if(fog)
						glDisable(GL_FOG);
					else
						glEnable(GL_FOG);
					fog = !fog;
					break;
        case 'g':
					//glRotatef(x_rot,.5,.5,.5);
                    //glRotatef(y_rot,0,1,0);
					y_rot -= 2000.0f;
					break;
        case 'h':
					//glRotatef(x_rot,.5,.5,.5);
                    //glRotatef(y_rot,0,1,0);
					y_rot += 2000.0f;
					break;
         case 'i': t+=0.2f;
                        init();
                    break;
        case 'o': t-=0.2f;
                        init();
                    break;

        case 'd':  while(i<1100)
        {
					y_rot -= 2.0f+i;
					i++;
					break;
        }




	}

	glutPostRedisplay();
}




void reshape(int w, int h)
{
	GLfloat fAspect;
    if(h == 0) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, fAspect, 1.0f, 800.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-40.0f);
}

int main(int argc, char** argv)
 {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200,100);
	glutInitWindowSize(1000,600);
	glutCreateWindow("Scena");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	init();

	for( size_t i = 0; i < 1000; ++i )
    {
        Point pt;
        pt.x = -50 + (rand() % 100);
        pt.y = -50 + (rand() % 100);
        points.push_back(pt);
    }
	glutMainLoop();
	return 0;
}
