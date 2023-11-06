#pragma once
#include "Vertex.h"
#include <vector>
struct ModelPart
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};

