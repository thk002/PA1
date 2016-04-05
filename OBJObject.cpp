#include "OBJObject.h"

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
}

void OBJObject::parse(const char *filepath) 
{
	//TODO parse the OBJ file
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data

	FILE *fp;

	float x, y, z;
	float r, g, b;
	int c1, c2;

	glm::vec3 vectorTemp;

	string line, name;

	// Open file
	fp = fopen(filepath, "rb");

	// File cannot be found
	if (fp == NULL) {
		cerr << "err loading file" << endl;
		exit(-1);
	}

	//Skip comment lines
	while (getline(filepath, line)) {
		if (line == ' ' || line == '#')
			continue;
	}

	c1 = fgetc(fp);
	c2 = fgetc(fp);

	//Read normal data accordingly
	while (Nread = (fscanf(fp, "%f %f %f", &x, &y, &z)) != EOF) {
		if (c1 == 'v') && (c2 == ' ') {
			vectorTemp = fscanf(fp, "%f %f %f", &x, &y, &z);
			vertices = vectorTemp;
		}

		else if (c1 == 'v') && (c2 == 'n') {
			vectorTemp = fscanf(fp, "%f %f %f", &x, &y, &z);
			normals = vectorTemp;
		}
	}
	
	//Close file when done
	fclose(fp);
}

void OBJObject::draw() 
{
	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}