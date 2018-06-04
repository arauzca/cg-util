#pragma once

// GL Includes
#define GLEW_STATIC
#include <GL/glew.h>

// OpenCV Includes
#include <opencv2/photo.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


#include <vector>

class TextureLoading
{
public:
    static GLuint LoadTexture( GLchar *path )
    {
        //Generate texture ID and load texture data
        GLuint textureID;
        glGenTextures( 1, &textureID );
        
        cv::Mat image = cv::imread( path );
        cv::cvtColor( image, image, CV_BGR2RGB );
        
        int imageWidth  = image.cols;
        int imageHeight = image.rows;
        
        // Assign texture to ID
        glBindTexture( GL_TEXTURE_2D, textureID );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)image.data );
        glGenerateMipmap( GL_TEXTURE_2D );
        
        // Parameters
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glBindTexture( GL_TEXTURE_2D,  0);
        
        return textureID;
    }
    
    static GLuint LoadCubemap( std::vector<const GLchar * > faces)
    {
        GLuint textureID;
        glGenTextures( 1, &textureID );
        
        cv::Mat image;
        int imageWidth, imageHeight;
        
        glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );
        
        for ( GLuint i = 0; i < faces.size( ); i++ )
        {
            cv::Mat image = cv::imread( faces[i] );
            cv::cvtColor(image, image, CV_BGR2RGB);
            
            imageWidth  = image.cols;
            imageHeight = image.rows;
            
            glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)image.data );
        }
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        glBindTexture( GL_TEXTURE_CUBE_MAP, 0);
        
        return textureID;
    }
};
