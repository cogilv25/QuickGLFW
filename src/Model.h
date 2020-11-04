#pragma once
#include <vector>

class Model
{
public:
	unsigned int id;
	Model();
	Model(std::vector<unsigned int> & ebo, std::vector<float> & vbo);
};

