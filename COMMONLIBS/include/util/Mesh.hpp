///////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *      Yeshua said to her, "I am the resurrection and the life. He who believes in Me, though he
 *      may die, he shall live. And whoever lives and believes in Me shall never die. Do you
 *      Do you believe this?"
 *                                                                                  - John 11:25-26
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *      Berner Fachhochschule / Bern University of Applied Sciences
 *
 *      Bachelor Thesis: Physically-based rendering ind Real-Time / Image-based lighting
 *               Author: Carlos Arauz
 *                 File: Mesh.hpp
 *          Description: Header file of the Mesh class, which loads meshes and let them draw on the
 *                       scene.
 *                 Date: 08.04.2018
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#define MESH_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <util/Shader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct Vertex
{
    glm::vec3 position;     // vertex position
    glm::vec2 uv;           // texture coordinates
    glm::vec3 normal;       // normal vector
};


class Mesh
{
public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    
    
    /*  Functions  */
    inline explicit Mesh( std::vector<Vertex> vertices, std::vector<GLuint> indices ) : vertices( std::move( vertices ) ), indices( std::move( indices ) )
    {
        this->setup_mesh();
    }
    
    void render( Shader );
    
    
private:
    /*  Render Data  */
    GLuint VAO = 0, VBO = 0, EBO = 0;
    
    
    /*  Functions  */
    void setup_mesh();
};


