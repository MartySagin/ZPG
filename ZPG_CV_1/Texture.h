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

public:
    Texture();
    ~Texture();

    bool Load2DTexture(string& filePath, GLuint textureUnit = 0, GLenum format = GL_RGBA);
    bool LoadCubemap(vector<string>& filePaths);
    void Bind();
    void Unbind();

    GLuint GetID();
    GLuint GetTextureUnit();
    GLenum GetType();
};
