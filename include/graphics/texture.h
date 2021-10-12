#pragma once

class Texture{
    private:
        const int id;

        unsigned int textureObject;

        //texture properties
        int width;
        int height;
        int channels;

        unsigned char* data;

    public:
        Texture();
        Texture(int id);
        Texture(int id, const char* path);
        ~Texture();

        bool loadFromFile(const char* path);

        int getId() const;
        int getWidth() const;
        int getHeight() const;
        int getChannels() const;

        void bind(int slot) const;

};
