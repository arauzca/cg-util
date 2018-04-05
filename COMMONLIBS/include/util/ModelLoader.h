/*******************************************************************************
********************************************************************************
Denn wenn du mit deinem Mund bekennst: »Jesus ist der Herr!«, und wenn du von
ganzem Herzen glaubst, dass Gott ihn von den Toten auferweckt hat, dann wirst du
gerettet werden.
                                                                    - Römer 10:9
********************************************************************************
*******************************************************************************/
#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <util/Shader.h>

using namespace std;

struct Vertex
{
    glm::vec3 position;         // Position
    glm::vec3 normal;           // Normal
    glm::vec2 uv;               // TexCoords
};

class Mesh
{
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<GLuint> indices;
    
    /*  Functions  */
    explicit Mesh( const string & mesh_path )
    {
        
    }
};
