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
 *                 File: Mesh.cpp
 *          Description: Definition file of the Mesh class, which loads meshes and let them draw
 *                       on the scene.
 *                 Date: 08.04.2018
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <util/Mesh.hpp>

void Mesh::render( Shader shader )
{
    // Draw mesh
    glBindVertexArray( this->VAO );
    glDrawElements( GL_TRIANGLES, static_cast<GLsizei>( this->indices.size() ), GL_UNSIGNED_INT, nullptr );
    glBindVertexArray( 0 );
}

void Mesh::setup_mesh()
{
    // Create buffers and arrays
    glGenVertexArrays( 1, &this->VAO );
    glGenBuffers( 1, &this->VBO );
    glGenBuffers( 1, &this->EBO );
    
    glBindVertexArray( this->VAO );
    
    // Load data into the vertex buffers
    glBindBuffer( GL_ARRAY_BUFFER, this->VBO );
    glBufferData( GL_ARRAY_BUFFER, this->vertices.size() * sizeof( Vertex ), &this->vertices[0], GL_STATIC_DRAW );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof( GLuint ), &this->indices[0], GL_STATIC_DRAW );
    
    // Set the vertex attribute pointers
    // Vertex positions
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), nullptr );
    // Texture coordinates
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )offsetof( Vertex, uv ) );
    // Normal vectors
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( GLvoid * )offsetof( Vertex, normal ) );
    
    glBindVertexArray( 0 );
}

