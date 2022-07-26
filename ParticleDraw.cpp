#include "Common.h"
#include <GL/glut.h>

void Chaos::Particle::GlDrawFunc(void)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &this->GlMaterialAmbient[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &this->GlMaterialDiffuse[0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &this->GlMaterialSpecular[0]);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->GlMaterialShine);

	//Draw particle
	glPushMatrix();
	glTranslatef(Coords[x] / MaxSize,
				 Coords[y] / MaxSize,
				 Coords[z] / MaxSize);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();

	//Draw Trace
	if (this->Trace.size() > 1)
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);

		glColor3f(this->GlMaterialAmbient[0],
				  this->GlMaterialAmbient[1],
				  this->GlMaterialAmbient[2]);
		glBegin(GL_LINE_STRIP);
		for (size_t i = 0; i < this->Trace.size(); i++)
		{
			glVertex3f(Trace[i][x] / MaxSize,
					   Trace[i][y] / MaxSize,
					   Trace[i][z] / MaxSize);
		}
		glEnd();

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
}