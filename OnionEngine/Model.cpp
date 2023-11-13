#include "Model.h"
#include <tiny_obj_loader.h>
#include <iostream>

using namespace std;

Model::Model(string path, string name) {
	loadModel(path, name);
}

Model::~Model() {
	for (Texture* t : textures) {
		delete t;
	}
}

void Model::loadModel(string path, string name) {
	cout << "Loading Model: " << name << endl;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> objMaterials;
	std::string warn, err;

	string objPath = path + "/" + name + ".fbx";
	string mtlPath = path;

	if (!tinyobj::LoadObj(&attrib, &shapes, &objMaterials, &warn, &err, objPath.c_str(), mtlPath.c_str())) {
		throw std::runtime_error(warn + err);
	}

	if (!warn.empty()) {
		cout << warn << endl;
	}

	if (!err.empty()) {
		cout << err << endl;
	}

	cout << "Num materials: " << objMaterials.size() << endl;
	for (const auto& objMaterial : objMaterials) {
		if (objMaterial.diffuse_texname != "") {
			string texturePath = path + "/" + objMaterial.diffuse_texname;
			Texture* texture = new Texture(texturePath.c_str());
			textures.push_back(texture);
		}
	}

	for (const auto& shape : shapes) {
		vector<Vertex> vertices;
		vector<unsigned int> indices;

		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.position = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.normal = {
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};

			vertex.color = { 1.0f, 1.0f, 1.0f };

			vertices.push_back(vertex);
			indices.push_back(indices.size());
		}

		ModelPart part;
		part.indices = indices;
		part.vertices = vertices;

		parts.push_back(part);
	}
}

void Model::drawGeometry() {
	int shapeIndex = 0;
	for (ModelPart p : parts) {
		if (shapeIndex < textures.size()) {
			textures[shapeIndex]->use();
		}

		glBegin(GL_TRIANGLES); {
			for (int i = 0; i < p.indices.size(); i++) {
				Vertex v = p.vertices[i];

				glColor3f(v.color.x, v.color.y, v.color.z);
				glNormal3f(v.normal.x, v.normal.y, v.normal.z);
				glTexCoord2f(v.texCoord.x, v.texCoord.y);
				glVertex3f(v.position.x, v.position.y, v.position.z);
			}
		}
		glEnd();

		shapeIndex++;
	}
}
