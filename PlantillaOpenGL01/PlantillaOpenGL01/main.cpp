#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>


using namespace std;
#define DEF_floorGridScale	1.0f
#define DEF_floorGridXSteps	15.0f
#define DEF_floorGridZSteps	15.0f
#define rotation_alpha 10.0f

struct figure
{
	int selected_joint [6];
	int white_colored [6];
	float rotation_torso;
	float rotation_right_arm;
	float rotation_left_arm;
	float rotation_right_forearm;
	float rotation_left_forearm;
	float rotation_right_hand;
	float rotation_left_hand;
	float rotation_right_leg;
	float rotation_left_leg;
	float rotation_right_calve;
	float rotation_left_calve;
	float rotation_right_foot;
	float rotation_left_foot;
	float rotation_head;
}figure;

void init(){
	figure.rotation_torso = 0;
	figure.rotation_right_arm = 0;
	figure.rotation_left_arm = 0;
	figure.rotation_right_forearm = 0;
	figure.rotation_left_forearm = 0;
	figure.rotation_right_hand = 0;
	figure.rotation_left_hand = 0;
	figure.rotation_right_leg = 0;
	figure.rotation_left_leg = 0;
	figure.rotation_right_calve = 0;
	figure.rotation_left_calve = 0;
	figure.rotation_right_foot = 0;
	figure.rotation_left_foot = 0;
	figure.rotation_head = 0;
}

void ejesCoordenada(float w) {
	
	glLineWidth(w);
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(0,10);
		glVertex2f(0,-10);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(10,0);
		glVertex2f(-10,0);
	glEnd();

	glLineWidth(w-1.0);
	int i;
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		for(i = -10; i <=10; i++){
			if (i!=0) {		
				if ((i%2)==0){	
					glVertex2f(i,0.4);
					glVertex2f(i,-0.4);

					glVertex2f(0.4,i);
					glVertex2f(-0.4,i);
				}else{
					glVertex2f(i,0.2);
					glVertex2f(i,-0.2);

					glVertex2f(0.2,i);
					glVertex2f(-0.2,i);

				}
			}
		}
		
	glEnd();

	glLineWidth(1.0);
}

void checkSelectedJoint(int joint_num, float r, float g, float b){
	if (figure.white_colored[joint_num-1] == 1 && joint_num != 6)  glColor3f(1,1,1);
	else if (figure.white_colored[joint_num-1] == 1 && joint_num == 6) {
		figure.white_colored[2] = 1;
		figure.white_colored[3] = 1;
		figure.white_colored[4] = 1;
		glColor3f(1,1,1);
	}
	else glColor3f(r,g,b);
};

void drawPoint (int x, int y, int size,int joint_num, float r,float g, float b){ 
	checkSelectedJoint(joint_num,r,g,b);
	glPointSize(size);
	glBegin(GL_POINTS);
		glVertex2f(x,y);
	glEnd();
}

void drawLine(int x1, int y1, int x2, int y2, int size,int joint_num, float r,float g, float b){
	checkSelectedJoint(joint_num,r,g,b);
	glLineWidth(size);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

void drawCircle(int x, int y, int radius, int size,int joint_num, float r,float g, float b){
	int i;
	int lineAmount = 500;
	checkSelectedJoint(joint_num,r,g,b);
	GLfloat twicePi = 2.0f * 3.141592;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.141592;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

void resetSelected(){
	for (int i = 0; i < 6;i++){
		figure.selected_joint[i]=0;
		figure.white_colored[i]=0;
	}
}

void rotationHandler(unsigned char key){
	if (figure.selected_joint[5] == 1){
		if (key == 'z') figure.rotation_torso += rotation_alpha;
		else if (key == 'a') figure.rotation_torso -= rotation_alpha;
	}
	if (figure.selected_joint[4] == 1){
		if (key == 'z') figure.rotation_head += rotation_alpha;
		else if (key == 'a') figure.rotation_head -= rotation_alpha;
	}
	if (figure.selected_joint[3] == 1){
		if (key == 'z') figure.rotation_left_arm += rotation_alpha;
		else if (key == 'a') figure.rotation_left_arm -= rotation_alpha;
		else if (key == 's') figure.rotation_left_forearm -= rotation_alpha;
		else if (key == 'x') figure.rotation_left_forearm += rotation_alpha;
		else if (key == 'd') figure.rotation_left_hand -= rotation_alpha;
		else if (key == 'c') figure.rotation_left_hand += rotation_alpha;
	}
	if (figure.selected_joint[2] == 1){
		if (key == 'z') figure.rotation_right_arm += rotation_alpha;
		else if (key == 'a') figure.rotation_right_arm -= rotation_alpha;
		else if (key == 's') figure.rotation_right_forearm -= rotation_alpha;
		else if (key == 'x') figure.rotation_right_forearm += rotation_alpha;
		else if (key == 'd') figure.rotation_right_hand -= rotation_alpha;
		else if (key == 'c') figure.rotation_right_hand += rotation_alpha;
	}
	if (figure.selected_joint[1] == 1){
		if (key == 'z') figure.rotation_left_leg += rotation_alpha;
		else if (key == 'a') figure.rotation_left_leg -= rotation_alpha;
		else if (key == 's') figure.rotation_left_calve -= rotation_alpha;
		else if (key == 'x') figure.rotation_left_calve += rotation_alpha;
		else if (key == 'd') figure.rotation_left_foot -= rotation_alpha;
		else if (key == 'c') figure.rotation_left_foot += rotation_alpha;
	}
	if (figure.selected_joint[0] == 1){
		if (key == 'z') figure.rotation_right_leg += rotation_alpha;
		else if (key == 'a') figure.rotation_right_leg -= rotation_alpha;
		else if (key == 's') figure.rotation_right_calve -= rotation_alpha;
		else if (key == 'x') figure.rotation_right_calve += rotation_alpha;
		else if (key == 'd') figure.rotation_right_foot -= rotation_alpha;
		else if (key == 'c') figure.rotation_right_foot += rotation_alpha;
	}

}


void keyPressed (unsigned char key, int x, int y) {  
	switch (key)
	{
		case '1':
			resetSelected();
			figure.selected_joint[0] = 1;
			figure.white_colored[0] = 1;
			break;
		case '2':
			resetSelected();
			figure.selected_joint[1] = 1;
			figure.white_colored[1] = 1;
			break;
		case '3':
			resetSelected();
			figure.selected_joint[2] = 1;
			figure.white_colored[2] = 1;
			break;
		case '4':
			resetSelected();
			figure.selected_joint[3] = 1;
			figure.white_colored[3] = 1;
			break;
		case '5':
			resetSelected();
			figure.selected_joint[4] = 1;
			figure.white_colored[4] = 1;
			break;
		case '6':
			resetSelected();
			figure.selected_joint[5] = 1;
			figure.white_colored[5] = 1;
			break;
		case 'a':
		case 'z':
		case 's':
		case 'x':
		case 'd':
		case 'c':
			rotationHandler(key);
			break;
		default:
			resetSelected();
	}
	
	glutPostRedisplay();
}  

void changeViewport(int w, int h) {
	glViewport(0,0,w,h);
	float aspectratio;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectratio = (float) w / (float) h;
	if (w<=h)
		glOrtho(-10,10,10/aspectratio,-10/aspectratio,1.0,-1.0);
	else
		glOrtho(-10*aspectratio,10*aspectratio,10,-10,1.0,-1.0);
}

void renderGrid(){
	GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

	glPushMatrix();
    glColor3f( 0.0f, 0.7f, 0.7f );
	glLineWidth(3);
    glBegin( GL_LINES );
    zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	{
	xLocal = DEF_floorGridScale * loopX;
	glVertex3f( xLocal, -zExtent, 0.0f );
	glVertex3f( xLocal, zExtent,  0.0f );
	}
    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	{
	zLocal = DEF_floorGridScale * loopZ;
	glVertex3f( -xExtent, zLocal, 0.0f );
	glVertex3f(  xExtent, zLocal, 0.0f );
	}
    glEnd();
    glPopMatrix();
}



void render(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(-0.8f, -0.8f, 1.f);

	//renderGrid();
	
	/* ============================= Proyect 1 ====================*/
	
	int line_size = 20;
	int point_size = 20;
	
	glPushMatrix();
	
	/* ============================= Pose's Kamehameha ====================*/
	/*glColor3f(0.8,0.8,0.8);
	drawFilledCircle(3.5,0.9,1.15);
	glColor3f(0,0,0.3);
	drawFilledCircle(3.5,0.9,1.1);
	glColor3f(0,0,0.6);
	drawFilledCircle(3.5,0.9,0.9);
	glColor3f(0,0,1);
	drawFilledCircle(3.5,0.9,0.5);
	glColor3f(1,1,1);
	drawFilledCircle(3.5,0.9,0.2);*/

		

		/* ============================= Upper Boddy ====================*/
	
		glPushMatrix();
			glRotatef(figure.rotation_torso,0,0,1);
	
			drawLine(0,0,0,6,line_size,6,0.3,1,1);//upper torso line
			drawLine(-3,4,3,4,line_size,6,0.5,0.5,0);//shoulder line
			drawPoint(0,0,point_size,6,1,0,0); //middle torso point

			/* ============================= Head ====================*/
	
			glPushMatrix();
				glTranslatef(0,6,0);
				glRotatef(figure.rotation_head,0,0,1);
				drawCircle(0,3,3,5,5,0.5,0.5,0.5);//head circle
				drawPoint(0,0,point_size,5,1,0,0); //head point
			glPopMatrix();


			/* ============================= Left Arm ====================*/
	
			glPushMatrix();
				glTranslatef(-3,4,0);
				glRotatef(figure.rotation_left_arm,0,0,1);
				drawLine(0,0,-3,0,line_size,4,0,1,0);//arm line L
				drawPoint(0,0,point_size,4,1,0,0); //shoulder point L
				
				glPushMatrix();
					glTranslatef(-3,0,0);
					glRotatef(figure.rotation_left_forearm,0,0,1);
					drawLine(0,0,-3,0,line_size,4,1,1,0);//forearm line L
					drawPoint(0,0,point_size,4,1,0,0); //arm point L
					
					glPushMatrix();
						glTranslatef(-3,0,0);
						glRotatef(figure.rotation_left_hand,0,0,1);
						drawLine(0,0,0,2,line_size,4,0,1,1);// hand line L
						drawPoint(0,0,point_size,4,1,0,0); //hand  point L
					glPopMatrix();
				
				glPopMatrix();
				
				
			glPopMatrix();

			/* ============================= Right Arm ====================*/
	
			glPushMatrix();
				glTranslatef(3,4,0);
				glRotatef(figure.rotation_right_arm,0,0,1);
				drawLine(0,0,3,0,line_size,3,0,1,0);//arm line R
				drawPoint(0,0,point_size,3,1,0,0); //shoulder point R
				
				glPushMatrix();
					glTranslatef(3,0,0);
					glRotatef(figure.rotation_right_forearm,0,0,1);
					drawLine(0,0,3,0,line_size,3,1,1,0);//forearm line R
					drawPoint(0,0,point_size,3,1,0,0); //arm point R
					
					glPushMatrix();	
						glTranslatef(3,0,0);
						glRotatef(figure.rotation_right_hand,0,0,1);
						drawLine(0,0,0,2,line_size,3,0,1,1);// hand line R
						drawPoint(0,0,point_size,3,1,0,0); //hand point R
					glPopMatrix();
				
				glPopMatrix();
			
			glPopMatrix();
			
		glPopMatrix();

		/* ============================= Lower Body ====================*/
	
		glPushMatrix();
			drawLine(-2,-4,2,-4,line_size,7,0.5,0,1);//hip line
			drawLine(0,0,0,-4,line_size,7,0.3,1,1);//lower torso line

			/* ============================= Left Leg ====================*/
			glPushMatrix();
				glTranslatef(-2,-4,0);
				glRotatef(figure.rotation_left_leg,0,0,1);
				drawLine(0,0,0,-3,line_size,2,1,1,0);//femur line L
				drawPoint(0,0,point_size,2,1,0,0); //hip point L
				
				glPushMatrix();
					glTranslatef(0,-3,0);
					glRotatef(figure.rotation_left_calve,0,0,1);
					drawLine(0,0,0,-3,line_size,2,0,1,0); //calve line L
					drawPoint(0,0,point_size,2,1,0,0); //knee point L
					
					glPushMatrix();
						glTranslatef(0,-3,0);
						glRotatef(figure.rotation_left_foot,0,0,1);
						drawLine(0,0,-2,0,line_size,2,0,1,1);//feet line L 
						drawPoint(0,0,point_size,2,1,0,0); //feet point L
					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

			/* ============================= Right Leg ====================*/
			glPushMatrix();
				glTranslatef(2,-4,0);
				glRotatef(figure.rotation_right_leg,0,0,1);
				drawLine(0,0,0,-3,line_size,1,1,1,0);//femur line R
				drawPoint(0,0,point_size,1,1,0,0); //hip point R 
				
				glPushMatrix();
					glTranslatef(0,-3,0);
					glRotatef(figure.rotation_right_calve,0,0,1);
					drawLine(0,0,0,-3,line_size,1,0,1,0); //calve line R
					drawPoint(0,0,point_size,1,1,0,0); //knee point R
					
					glPushMatrix();
						glTranslatef(0,-3,0);
						glRotatef(figure.rotation_right_foot,0,0,1);
						drawLine(0,0,2,0,line_size,1,0,1,1);//feet line R
						drawPoint(0,0,point_size,1,1,0,0); //feet point R
					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

		glPopMatrix(); 

	glPopMatrix();

	/* ============================= Proyect 1 ====================*/
	
	glutSwapBuffers();

}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,600);

	glutCreateWindow("Opengl");
	init();
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyPressed);

	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	

	glutMainLoop();
	return 0;

}