#include "Texture.h"
#include <stb_image.h>
#include <iostream>

// Constructor
Texture::Texture(const std::string& path, GLenum textureType, GLenum format, GLenum internalFormat, bool flip)
    : type(textureType) {
    loadTexture(path, format, internalFormat, flip);
}

// Load the texture
void Texture::loadTexture(const std::string& path, GLenum format, GLenum internalFormat, bool flip) {
    stbi_set_flip_vertically_on_load(flip);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &ID);
        glBindTexture(type, ID);

        // Set texture parameters
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Load texture data
        glTexImage2D(type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(type);

        glBindTexture(type, 0); // Unbind texture
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }

    stbi_image_free(data);
}

// Bind the texture
void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

// Unbind the texture
void Texture::unbind() const {
    glBindTexture(type, 0);
}

// Destructor
Texture::~Texture() {
    glDeleteTextures(1, &ID);
}