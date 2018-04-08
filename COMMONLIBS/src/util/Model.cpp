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
 *          Description: Definition file of the Model class, which loads model from files using the
 *                       protable library ASSIMP.
 *                 Date: 08.04.2018
 */
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <util/Model.hpp>

// renders all meshes using the given shader
void Model::render( Shader shader )
{
    for ( auto mesh : this->meshes )
    {
        mesh.render( shader );
    }
}


// Processes a node recursively.
void Model::process_node( aiNode * node, const aiScene * scene )
{
    // Process each mesh located at the current node
    for ( GLuint i = 0; i < node->mNumMeshes; i++ )
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back( this->process_mesh( mesh, scene ) );
    }
    
    // Process recursivele each childer node
    for ( GLuint i = 0; i < node->mNumChildren; i++ )
    {
        this->process_node( node->mChildren[i], scene );
    }
}


Mesh Model::process_mesh( aiMesh * mesh, const aiScene * scene )
{
    // Data to fill
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    
    // Loop through each of the mesh's vertices
    for ( GLuint i = 0; i < mesh->mNumVertices; i++ )
    {
        Vertex vertex;
        glm::vec3 vector;
        
        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        
        // Texture coordinates
        if ( mesh->mTextureCoords[0] )
        {
            glm::vec2 uv;
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = uv;
        }
        else
        {
            vertex.uv = glm::vec2( 0.0f, 0.0f );
        }
        
        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        
        vertices.push_back( vertex );
    }
    
    // Loop through the faces of the mesh and retrieve the correspoding index of the vertex.
    for ( GLuint i = 0; i < mesh->mNumFaces; i++ )
    {
        aiFace face = mesh->mFaces[i];
        for ( GLuint j = 0; j < face.mNumIndices; j++ )
        {
            indices.push_back( face.mIndices[j] );
        }
    }
    
    return Mesh( vertices, indices );
}
































