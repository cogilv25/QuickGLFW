#include "ModelBuilder.h"


float planeVertices[] = {
	// positions		// texture coords
	 0.5f,  0.5f, 1.0f,		1.0f, 1.0f,		// top right		
	 0.5f, -0.5f, 1.0f,		1.0f, 0.0f,		// bottom right
	-0.5f, -0.5f, 1.0f,		0.0f, 0.0f,		// bottom left
	-0.5f,  0.5f, 1.0f,		0.0f, 1.0f		// top left 
};
unsigned int planeIndices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

Model* ModelBuilder::buildPlane(float xScale, float yScale, float zPosition)
{
	float mask[] = { xScale, yScale, zPosition };
	std::vector<float> vert;
	std::vector<unsigned int> ind;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
			vert.push_back(planeVertices[i * 5 + j] * mask[j]);

		vert.push_back(planeVertices[i * 5 + 3]);
		vert.push_back(planeVertices[i * 5 + 4]);

	}

	for (int i = 0; i < 6; i++)
	{
		ind.push_back(planeIndices[i]);
	}

	

	Model* plane = new Model(ind, vert);

	return plane;
}
