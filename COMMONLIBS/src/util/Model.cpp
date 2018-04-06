//
//  Created by Carlos Arauz on 06.04.18.
//

#include <util/Model.hpp>




Model::Model( const GLchar * model_path )
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    if ( load_obj( model_path, vertices, uvs, normals) )
    {
        size = vertices.size();
        if ( VAO == 0)
        {
            glGenVertexArrays( 1, &VAO );
            glBindVertexArray( VAO );
            
            glGenBuffers( 1, &vertexbuffer );
            glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
            glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW );
            glEnableVertexAttribArray( 0 );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
            
            glGenBuffers( 1, &uvbuffer );
            glBindBuffer( GL_ARRAY_BUFFER, uvbuffer );
            glBufferData( GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2),      &uvs[0],      GL_STATIC_DRAW );
            glEnableVertexAttribArray( 1 );
            glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, nullptr );
            
            glGenBuffers( 1, &normalbuffer);
            glBindBuffer( GL_ARRAY_BUFFER, normalbuffer );
            glBufferData( GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),  &normals[0],  GL_STATIC_DRAW );
            glEnableVertexAttribArray( 2 );
            glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
        }
    }
}
// Model::Model( const std::string & ) //////////////////////////////////////////////////////////////



void Model::render()
{
    glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLES, 0, size );
    glBindVertexArray( 0 );
}



bool Model::load_obj( const GLchar * model_path,
                      std::vector<glm::vec3> & out_vertices,
                      std::vector<glm::vec2> & out_uvs,
                      std::vector<glm::vec3> & out_normals )
{
    std::vector<GLuint>    vertex_indices, uv_indices, normal_indices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    
    // retrieve model file /////////////////////////////////////////////////////////////////////////
    std::ios_base::iostate  exception_mask;
    std::ifstream           input;
    
    exception_mask = input.exceptions( ) | std::ios::failbit;
    input.exceptions( exception_mask );
    
    try
    {
        input.open( model_path );
        std::string line;
        std::string lineheader;
        while (std::getline(input, line))
        {
            std::stringstream ssin(line);
            ssin >> lineheader;
            
            if ( std::strcmp( lineheader.c_str(), "v" ) == 0 )
            {
                glm::vec3 vertex;
                ssin >> vertex.x >> vertex.y >> vertex.z;
                temp_vertices.push_back(vertex);
            }
            else if ( std::strcmp( lineheader.c_str(), "vt" ) == 0 )
            {
                glm::vec2 uv;
                ssin >> uv.x >> uv.y;
                temp_uvs.push_back(uv);
            }
            else if ( std::strcmp( lineheader.c_str(), "vn" ) == 0 )
            {
                glm::vec3 normal;
                ssin >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            }
            else if ( std::strcmp( lineheader.c_str(), "f" ) == 0 )
            {
                std::string vertex[3];
                ssin >> vertex[0] >> vertex[1] >> vertex[2];
    
                for ( int i = 0; i < 3; i++ )
                {
                    std::vector<GLuint> fs;
                    split_face(vertex[i], '/', fs);
                    GLuint vertex_index( fs[0] ), uv_index( fs[1] ), normal_index( fs[2] );
                    
                    vertex_indices.push_back(vertex_index);
                    uv_indices.push_back(uv_index);
                    normal_indices.push_back(normal_index);
                }
            }
            
            for ( GLuint i = 0; i < vertex_indices.size(); i++ )
            {
                GLuint vertex_index = vertex_indices[i];
                glm::vec3 vertex    = temp_vertices[vertex_index-1];
                out_vertices.push_back(vertex);
                
                GLuint uv_index = uv_indices[i];
                glm::vec2 uv    = temp_uvs[uv_index-1];
                out_uvs.push_back(uv);
                
                GLuint normal_index = normal_indices[i];
                glm::vec3 normal    = temp_normals[normal_index-1];
                out_normals.push_back(normal);
            }
        }
    }
    catch ( const std::ifstream::failure & e )
    {
        std::cerr << "Cannot open file \042" << model_path << "\042" << std::endl;
        return false;
    }
    
    input.close();
    return true;
}

void Model::split_face( const std::string & line, GLchar delim, std::vector<GLuint> & out )
{
    std::stringstream ss( line );
    std::string item;
    
    while ( getline(ss, item, delim) )
    {
        out.push_back( static_cast<GLuint>(std::stoi(item)) );
    }
}
