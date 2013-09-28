#include "dg_room.h"


DGRoom::DGRoom(void)
{
}


DGRoom::~DGRoom(void)
{
}

void readLine(FILE* file, char* lineBuffer, int bufSize) {
	do {
		fgets(lineBuffer, bufSize, file);
	} while(lineBuffer[0] == '\r' || lineBuffer[0]=='\n');
}

void DGRoom::start(){
	if (!loadGLTexture("Assets/Data/model/room/texture_wall.bmp", &texture[0])) {
		throw new DGException("room texture load faild!");
	}

	FILE* file = fopen("Assets/Data/model/room/data.txt", "r");

	int numtriangles;
	char oneline[256];

	readLine(file, oneline, 256);
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);

	sector.numTriangles = numtriangles;
	sector.triangle = new TRIANGLE[numtriangles];

	float x, y, z, u, v;

	for (int loop = 0; loop < numtriangles; loop++) {
		for (int vert = 0; vert < 3; vert++) {

			readLine(file, oneline, 256);
			sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);

			sector.triangle[loop].vertexs[vert].x = x;
			sector.triangle[loop].vertexs[vert].y = y;
			sector.triangle[loop].vertexs[vert].z = z;
			sector.triangle[loop].vertexs[vert].u = u;
			sector.triangle[loop].vertexs[vert].v = v;
		}
	}

	fclose(file);
}

void DGRoom::draw(DGContext* ctx){
	glTranslatef(0.0f, 0.0f, -16.0f);

	GLfloat x_m, y_m, z_m, u_m, v_m;
	int numtriangles = sector.numTriangles;

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Process Each Triangle
	for (int loop_m = 0; loop_m < numtriangles; loop_m++) {
		glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 0.0f, 1.0f);
			x_m = sector.triangle[loop_m].vertexs[0].x;
			y_m = sector.triangle[loop_m].vertexs[0].y;
			z_m = sector.triangle[loop_m].vertexs[0].z;
			u_m = sector.triangle[loop_m].vertexs[0].u;
			v_m = sector.triangle[loop_m].vertexs[0].v;
			glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);
			
			x_m = sector.triangle[loop_m].vertexs[1].x;
			y_m = sector.triangle[loop_m].vertexs[1].y;
			z_m = sector.triangle[loop_m].vertexs[1].z;
			u_m = sector.triangle[loop_m].vertexs[1].u;
			v_m = sector.triangle[loop_m].vertexs[1].v;
			glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);
			
			x_m = sector.triangle[loop_m].vertexs[2].x;
			y_m = sector.triangle[loop_m].vertexs[2].y;
			z_m = sector.triangle[loop_m].vertexs[2].z;
			u_m = sector.triangle[loop_m].vertexs[2].u;
			v_m = sector.triangle[loop_m].vertexs[2].v;
			glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);
		glEnd();
	}
}

void DGRoom::update(DGContext* ctx){

}
