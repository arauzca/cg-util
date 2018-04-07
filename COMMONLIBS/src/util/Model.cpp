//
//  Created by Carlos Arauz on 06.04.18.
//

#include <util/Model.hpp>




Model::Model( const GLchar * model_path )
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    std::vector<GLfloat> data;
    
    if ( load_obj( model_path, data ) )
    {
        if ( VAO == 0)
        {
            glGenVertexArrays( 1, &VAO );
            glGenBuffers( 1, &VBO );
            
            glBindVertexArray( VAO );
            glBindBuffer( GL_ARRAY_BUFFER, VBO );
            glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), &data[0], GL_STATIC_DRAW );
            
            GLsizei stride = ( 3 + 2 + 3 ) * sizeof( GLfloat );
            glEnableVertexAttribArray( 0 );
            glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, stride, nullptr );
            glEnableVertexAttribArray( 1 );
            glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, stride, (void *)( 3 * sizeof( GLfloat ) ) );
            glEnableVertexAttribArray( 2 );
            glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, stride, (void *)( 5 * sizeof( GLfloat ) ) );
        }
    }
}
// Model::Model( const std::string & ) //////////////////////////////////////////////////////////////



void Model::render()
{
    glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLES, 0, size );
    // glBindVertexArray( 0 );
}



bool Model::load_obj( const GLchar * model_path,
                      std::vector<GLfloat> & out_data )
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
                temp_vertices.emplace_back(vertex);
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
                temp_normals.emplace_back(normal);
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
                    
                    vertex_indices.emplace_back(vertex_index);
                    uv_indices.emplace_back(uv_index);
                    normal_indices.emplace_back(normal_index);
                }
            }
            
            for ( GLuint i = 0; i < vertex_indices.size(); i++ )
            {
                GLuint vertex_index = vertex_indices[i];
                glm::vec3 vertex    = temp_vertices[vertex_index-1];
                out_data.emplace_back( vertex.x );
                out_data.emplace_back( vertex.y );
                out_data.emplace_back( vertex.z );
                
                if ( !uv_indices.empty() )
                {
                    GLuint uv_index = uv_indices[i];
                    glm::vec2 uv    = temp_uvs[uv_index-1];
                    out_data.emplace_back( uv.x );
                    out_data.emplace_back( uv.y );
                }
                
                if ( !normal_indices.empty() )
                {
                    GLuint normal_index = normal_indices[i];
                    glm::vec3 normal    = temp_normals[normal_index-1];
                    out_data.emplace_back( normal.x );
                    out_data.emplace_back( normal.y );
                    out_data.emplace_back( normal.z );
                }
            }
        }
    }
    catch ( const std::ifstream::failure & e )
    {
        std::cerr << "Cannot open file \042" << model_path << "\042" << std::endl;
        return false;
    }
    
    size = vertex_indices.size();
    input.close();
    return true;
}

void Model::split_face( const std::string & line, GLchar delim, std::vector<GLuint> & out )
{
    std::stringstream ss( line );
    std::string item;
    
    while ( getline(ss, item, delim) )
    {
        out.emplace_back( static_cast<GLuint>(std::stoi(item)) );
    }
}
