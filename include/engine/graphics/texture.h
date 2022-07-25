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
        void setData(unsigned char* data);

        int getWidth() const;
        int getHeight() const;
        int getChannels() const;

        inline void setWidth(int width){this->width = width;}
        inline void setHeight(int height){this->height = height;}
        inline void setChannels(int channels){this->channels = channels;}

        void bind(int slot) const;

};
