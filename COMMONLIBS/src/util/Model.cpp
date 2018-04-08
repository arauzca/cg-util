//
//  Created by Carlos Arauz on 06.04.18.
//

#include <util/Model.hpp>




Model::Model( const GLchar * model_path )
////////////////////////////////////////////////////////////////////////////////////////////////////
{
    std::vector<GLfloat>    data;
    std::vector<GLuint>     indices;
    
    if ( load_obj( model_path, data, indices ) )
    {
        if ( VAO == 0)
        {
            glBindVertexArray( VAO );
            glBindBuffer( GL_ARRAY_BUFFER, VBO );
            glBufferData( GL_ARRAY_BUFFER, data.size( ) * sizeof( GLfloat ), &data[0], GL_STATIC_DRAW );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size( ) * sizeof( GLuint ), &indices[0], GL_STATIC_DRAW );
            
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
    glDrawElements( GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, nullptr );
    // glBindVertexArray( 0 );
}



bool Model::load_obj( const GLchar * model_path,
                      std::vector<GLfloat> & data,
                      std::vector<GLuint>    & indices )
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    
    // retrieve model file /////////////////////////////////////////////////////////////////////////
    std::ios_base::iostate  exception_mask;
    std::ifstream           input;
    
    exception_mask = input.exceptions( ) | std::ios::failbit;
    input.exceptions( exception_mask );
    
    try
    {
        input.open( model_path, std::ios::in );
        std::string line;
        std::string lineheader;
        while (std::getline(input, line))
        {
            if ( line.substr(0,2) == "v " )
            {
                std::istringstream s( line.substr(2) );
                glm::vec3 position;
                s >> position.x >> position.y >> position.z;
                std::cout << "v " << position.x << "/" << position.y << "/" << position.z << std::endl;
                positions.push_back(position);
            }
            else if ( line.substr(0,3) == "vt " )
            {
                std::istringstream s( line.substr(3) );
                glm::vec2 uv;
                s >> uv.x >> uv.y;
                std::cout << "vt " << uv.x << "/" << uv.y << std::endl;
                uvs.push_back(uv);
            }
            else if ( line.substr(0,3) == "vn " )
            {
                std::istringstream s( line.substr(3) );
                glm::vec3 normal;
                s >> normal.x >> normal.y >> normal.z;
                std::cout << "vt " << normal.x << "/" << normal.y << "/" << normal.z << std::endl;
                normals.push_back(normal);
            }
            else if ( line.substr(0,2) == "f " )
            {
                std::istringstream s( line.substr(2) );
                GLuint a,b,c;
                s >> a >> b >> c;
                a--; b--; c--;
                std::cout << "f " << a<< "/" << b << "/" << c << std::endl;
                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(c);
            }
        }
    }
    catch ( const std::ifstream::failure & e )
    {
        std::cerr << "Cannot open file \042" << model_path << "\042" << std::endl;
        return false;
    }
    
    input.close();
    indexCount = static_cast<GLsizei>( indices.size( ) );
    
    for (GLint i = 0; i < positions.size(); ++i)
    {
        data.push_back( positions[i].x );
        data.push_back( positions[i].y );
        data.push_back( positions[i].z );
        
        if ( !uvs.empty( ) )
        {
            data.push_back( uvs[i].x );
            data.push_back( uvs[i].y );
        }
        
        if ( !normals.empty( ) )
        {
            data.push_back( normals[i].x );
            data.push_back( normals[i].y );
            data.push_back( normals[i].z );
        }
    }
    
    
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
