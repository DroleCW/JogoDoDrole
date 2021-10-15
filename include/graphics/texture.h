#pragma once

class Texture{
    private:

        unsigned int textureObject;

        //texture properties
        int width;
        int height;
        int channels;

        unsigned char* data;

    public:
        Texture(const char* path = nullptr);
        ~Texture();

        bool loadFromFile(const char* path);

        int getWidth() const;
        int getHeight() const;
        int getChannels() const;

        void bind(int slot) const;

};
