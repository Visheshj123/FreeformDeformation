// standard
#include <assert.h>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <Eigen/Dense>
#include <vector>
#include <utility>
#include <iomanip>
#include <vector>
#include <string>
#include <regex>
#include <sstream>
#include "readShape.hpp"
#include "euler.hpp"
#include "BezierVolume.hpp"
#include "vertices.hpp"
#include "cp.hpp"
#include <GLUT/GLUT.h>

//================================
// global variables
//================================
// screen size
int g_screenWidth  = 0;
int g_screenHeight = 0;
//int g_angle = 0;

// frame index
int g_frameIndex = 0;

// angle for rotation
float eAngles[3] = {0,0,0}; //z,y,x angles to rotate
GLfloat lAngles[3] = {0,0,0};



//points for translation
double angleX = 0;
double angleY = 0;
double angleZ = 0.0;


//vectors for local coordiante space
Eigen::Vector3f S;
Eigen::Vector3f T;
Eigen::Vector3f U;
Eigen::Vector3f p0;


double x = 0;
double y = 0;
double z = -15;

//control points
std::vector<Eigen::Vector3f> cp;
Eigen::Matrix4f translations[64]; //store all transltions done to each cp

//verticies vector to create our imported model
 std::vector<std::vector<double> > vertices;
 std::vector<std::vector<double> > tVertices;
 std::vector<Eigen::Vector3f> localVerts;
std::vector<std::vector<int> > vertptrs;


void setTranslations(){
    for(int i=0;i<64; i++){
        Eigen::Matrix4f translate;
        translate << 1,0,0,0,
                     0,1,0,0,
                     0,0,1,0,
                     0,0,0,1;
        translations[i] = translate;
    }
}



void init( void ) {
    initializeShape("knight.d");
    setTranslations(); //initializes all translation vectors
    eAngles[2] = 273;
    Eigen::Matrix4f transform = rotateEuler(eAngles, 0, -2, -20);
    setP0(transform);
    
    //length of local gird space in x,y,z direction
    S << 3.34652,0,0;
    T << 0,6.508,0;
    U << 0,0,-3.2331;
    //p0 << -1.67326, -2.08253, -18.3607;
    
    //apply transformation to each vertice
    applyTransform(transform);

    //generate local coordiantes for all verticies
    setLocalCoord(S,T,U,p0);

    //set control point location in world-coordinates
    setControlPoints(S,T,U,p0);

}
//================================
// update
//================================
void update( void ) {
   

}

void display(){
 
    
    glPushMatrix(); //works because the stack below this is the identity
          glBegin(GL_TRIANGLES);
    for(int i=1;i<vertptrs.size();i++){
             
             for(int j=1;j<vertptrs[i].size();j++){
                 int ptr = vertptrs[i][j]-1;
                 //std::cout << "ptr: " << ptr << vertices[ptr][0] << ", " << vertices[ptr][1] << ", " << vertices[ptr][2] << std::endl;
                 
                 Eigen::Vector3f m (tVertices[ptr][0], tVertices[ptr][1], tVertices[ptr][2]);
                 GLfloat length = sqrt(m.dot(m));
                 glNormal3f(tVertices[ptr][0]/length, tVertices[ptr][1]/length, tVertices[ptr][2]/length); //unit vector
                 
                  glVertex3f(tVertices[ptr][0], tVertices[ptr][1], tVertices[ptr][2]);

             }
            

         }
      glEnd();
    glPopMatrix();
    
    
}

//================================
// render
//================================
void render( void ) {
  
	// clear buffer
	glClearColor (0, 0.0, 0.0, 0.0);
	glClearDepth (1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

	// render state
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// light source attributes
	GLfloat LightAmbient[]	= { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightDiffuse[]	= { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat LightSpecular[]	= { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightPosition[] = { -5.0f, 0.0f, 0.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT , LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE , LightDiffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	// surface material attributes
	GLfloat material_Ka[]	= { 0.11f, 0.06f, 0.11f, 1.0f };
	GLfloat material_Kd[]	= { 0.43f, 0.47f, 0.54f, 1.0f };
	GLfloat material_Ks[]	= { 0.33f, 0.33f, 0.52f, 1.0f };
	GLfloat material_Ke[]	= { 0.1f , 0.0f , 0.1f , 1.0f };
	GLfloat material_Se		= 10;

	glMaterialfv(GL_FRONT, GL_AMBIENT	, material_Ka);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE	, material_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR	, material_Ks);
	glMaterialfv(GL_FRONT, GL_EMISSION	, material_Ke);
	glMaterialf (GL_FRONT, GL_SHININESS	, material_Se);
    
 
    
    
	// modelview matrix
	glMatrixMode( GL_MODELVIEW ); //the current matrix is the one we want to interact with
    float m[16];
    //m is now the 4x4 identity matrix
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    
    //glutWireCube(0.25);
    

    glPushMatrix();

	glLoadIdentity(); //gets modelview matrix to original state

    display();
    
    //displayP0();
   
    displayCP(); //displays the control points

    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(x, y, z);
    glutWireCube(0.2);
    glPopMatrix();
    

	// disable lighting
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	// swap back and front buffers
	glutSwapBuffers();
}

//================================
// keyboard input
//================================
void keyboard( unsigned char key, int x, int y ) {
    if(key == 27){
        exit(0);
    }
    
//
    if(key == 'w') ::y+=0.1;
    if(key == 'a')  ::x-=0.1;
    if(key == 's') ::y-=0.1;
    if(key == 'd') ::x+=0.1;
    std::cout << "x: " << ::x << " y: " << ::y << std::endl;
    
    //move different axis with mouse
    if(key == 'z'){
        eAngles[0] += 3;
        lAngles[0] += 3;
        std::cout << "angleZ is " << eAngles[0] << " degrees" << std::endl;
    }
    if(key == 'y'){
        eAngles[1] += 3;
        lAngles[1] += 3;
        std::cout << "angleY is " <<  eAngles[1] << " degrees" << std::endl;
    }
    if(key == 'x'){
        eAngles[2] += 3;
        lAngles[2] += 3;
        std::cout << "angleX is " << eAngles[2] << " degrees" << std::endl;
    }
    
    if(key == 32){
           deformObject();
           return;
    }
    
    
     Eigen::Matrix4f transform = rotateEuler(eAngles, 0, -2, -20);
     tVertices.clear();
     applyTransform(transform);
     setP0(transform);
    
    //set local dimensions
    Eigen::Matrix3f ltransform = rotatelocal(lAngles);


    Eigen::Vector3f S_2 = ltransform * S;
    Eigen::Vector3f U_2 = ltransform * U;
    Eigen::Vector3f T_2 = ltransform * T;

    localVerts.clear();
    setLocalCoord(S_2, T_2, U_2, p0);
    cp.clear();
    setControlPoints(S_2, T_2, U_2, p0);
    deformObject();

}

void specialKeyboard(int key, int x, int y){
    if(key == GLUT_KEY_UP) ::z+=0.25;
    if(key == GLUT_KEY_DOWN) ::z-=0.25;

    
}

void mouse(int x, int y){

    //convert to normalized coordiantes
    GLfloat y_w = y;
    GLfloat x_w = x;
    GLfloat x_nd = (15.8*(x_w)/700) - 7.9;
    GLfloat y_nd = -1*((15.8*(y_w)/700) - 7.9);
    isControlPoint(x_nd, y_nd);
    
}

//================================
// reshape : update viewport and projection matrix when the window is resized
//================================

void reshape( int w, int h ) {
	// screen size
	g_screenWidth  = w;
	g_screenHeight = h;


	// viewport
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
    //glViewport( 0, 0, w, h );

	// projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 2000.0);
}


//================================
// timer : triggered every 16ms ( about 60 frames per second )
//================================
void timer( int value ) {
	// increase frame index
	g_frameIndex++; //no functionality

	update();

	// render
	glutPostRedisplay(); //calls render function immadetely

	// reset timer
	// 16 ms per frame ( about 60 frames per second )
	//glutTimerFunc( 16, timer, 0 );
    glutTimerFunc( 16, timer, 0 ); //was 16
}

//================================
// main
//================================
int main( int argc, char** argv ) {
	// create opengL window
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH );
	glutInitWindowSize( 700, 700 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( argv[0] );
 //   glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	// init
	init();

	// set callback functions
	glutDisplayFunc( render );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
    glutSpecialFunc(specialKeyboard);
    glutMotionFunc(mouse);
    glutTimerFunc( 16, timer, 0 );
   
    
       

	// main loop
	glutMainLoop();
    
	return 0;
}
