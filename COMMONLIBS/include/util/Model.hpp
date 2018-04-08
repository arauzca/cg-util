///////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *      that if you confess with your mouth the Lord Yeshua and believe in your heart that God has
 *      raised Him from the dead, you will be saved. For with the heart one believes unto
 *      righteousness, and with the mouth confession is made unto salvation.
 *                                                                                 - Romans 10:9-10
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *      Berner Fachhochschule / Bern University of Applied Sciences
 *
 *      Bachelor Thesis: Physically-based rendering ind Real-Time / Image-based lighting
 *               Author: Carlos Arauz
 *                 File: Model.hpp
 *          Description: Header file of the Model class, which loads model from files using the
 *                       protable library ASSIMP.
 *                 Date: 08.04.2018
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <util/Mesh.hpp>


class Model
{
public:
    /*  Functions  */
    inline explicit Model( const GLchar * path )
    {
        this->load_model( path );
    }
    
    void render( Shader );
    
private:
    /*  Model Data  */
    std::vector<Mesh> meshes;
    std::string directory;
    
    /* Functions  */
    // Loads a model with supported ASSIMP extensions from the file and stores the resulting meshes in
    // the meshes vector.
    void load_model( const std::string & path )
    {
        // Read file using ASSIMP
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate | aiProcess_FlipUVs );
        
        // Checking errors
        if ( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
            return;
        }
        
        // Get directory path from the filepath
        this->directory = path.substr( 0, path.find_last_of( '/' ) );
        
        // Process root node recursively
        this->process_node( scene->mRootNode, scene );
    }
    
    void process_node( aiNode *, const aiScene * );
    Mesh process_mesh( aiMesh *, const aiScene * );
};
