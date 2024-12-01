#include "Texture.h"
#include <SOIL.h>
#include <iostream>

using namespace std;

int Texture::textureCount = 0;

Texture::Texture() {
    this->textureID = 0;

    this->textureType = GL_TEXTURE_2D;

    this->textureUnit = 0;
}

Texture::~Texture() {
    if (this->textureID) {
        glDeleteTextures(1, &this->textureID);
    }
}

bool Texture::Load2DTexture(const char* filePath, GLenum format) {

    this->textureCount++;
    
    this->textureUnit = this->textureCount;

    this->textureType = GL_TEXTURE_2D;

    glActiveTexture(GL_TEXTURE0 + textureUnit);

    this->textureID = SOIL_load_OGL_texture(filePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    if (this->textureID == 0) {
        cerr << "Failed to load texture: " << filePath << endl;
        
        return false;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, this->textureID);

    return true;
}

bool Texture::LoadCubemap(vector<string>& filePaths) {
    
    if (filePaths.size() != 6) {
        cerr << "Cubemap requires exactly 6 file paths." << endl;

        return false;
    }

	this->textureCount++;

    this->textureUnit = this->textureCount;

    this->textureType = GL_TEXTURE_CUBE_MAP;

	glActiveTexture(GL_TEXTURE0 + textureUnit);

    this->textureID = SOIL_load_OGL_cubemap(
        filePaths[0].c_str(),
        filePaths[1].c_str(),
        filePaths[2].c_str(),
        filePaths[3].c_str(),
        filePaths[4].c_str(),
        filePaths[5].c_str(),
        SOIL_LOAD_RGB,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS
    );

    if (!this->textureID) {
        cerr << "Failed to load cubemap textures." << endl;

        return false;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

    return true;
}


void Texture::ActivateTexture() {
    glActiveTexture(GL_TEXTURE0 + this->textureUnit);
}

void Texture::Unbind() {
    glBindTexture(this->textureType, 0);
}

GLuint Texture::GetID() {
    return this->textureID;
}

GLuint Texture::GetTextureUnit() {
    return this->textureUnit;
}

GLenum Texture::GetType() {
    return this->textureType;
}
