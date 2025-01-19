#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:
    unsigned int ID;
    GLenum type;

    // Constructor
    Texture(const std::string& path, GLenum textureType = GL_TEXTURE_2D, GLenum format = GL_RGB, GLenum internalFormat = GL_RGB, bool flip = true);

    // Bind the texture
    void bind(unsigned int unit) const;

    // Unbind the texture
    void unbind() const;

    // Destructor
    ~Texture();

private:
    void loadTexture(const std::string& path, GLenum format, GLenum internalFormat, bool flip);
};