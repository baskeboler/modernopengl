#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
using namespace std;

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;

  glm::vec2 texCoords;

  glm::vec3 tangent;
  glm::vec3 bitangent;
};

struct Texture {
  unsigned int id;
  string type;
  string path;
};

class Mesh {
  void setupMesh();
  unsigned int VBO, EBO;

public:
  vector<Vertex> vertices;
  vector<unsigned int> indices;
  vector<Texture> textures;
  unsigned int VAO;
  Mesh(vector<Vertex> verts, vector<unsigned int> indices,
       vector<Texture> textures);

  void draw(Shader &shader);
};

#endif // MESH_H
