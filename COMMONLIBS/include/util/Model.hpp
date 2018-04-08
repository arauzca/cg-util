/*******************************************************************************
********************************************************************************
Denn wenn du mit deinem Mund bekennst: »Jesus ist der Herr!«, und wenn du von
ganzem Herzen glaubst, dass Gott ihn von den Toten auferweckt hat, dann wirst du
gerettet werden.
                                                                    - Römer 10:9
********************************************************************************
*******************************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <util/Shader.h>



class Model
{
private:
    GLsizei indexCount;
    GLuint  VAO = 0;
    GLuint  VBO, EBO;
public:
    /*  Functions  */
    // Constructor
    explicit Model( const GLchar * );
    void render();
private:
    bool load_obj( const GLchar *, std::vector<GLfloat> &, std::vector<GLuint> & );
    void split_face( const std::string &, GLchar, std::vector<GLuint> & );
};
