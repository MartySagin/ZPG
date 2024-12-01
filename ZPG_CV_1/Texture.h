#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

using namespace std;

class Texture {

    private:
        GLuint textureID;
        GLenum textureType;
        GLuint textureUnit;

		static int textureCount;

    public:
        Texture();
        ~Texture();

        bool Load2DTexture(const char* filePath, GLenum format = GL_RGBA);
        bool LoadCubemap(vector<string>& filePaths);

        void ActivateTexture();
        void Unbind();

        GLuint GetID();
        GLuint GetTextureUnit();
        GLenum GetType();
};
