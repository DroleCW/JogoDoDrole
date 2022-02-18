#pragma once

#include "graphics/text/fontLocations.h"
#include "font.h"
#include <unordered_map>

class FontManager{

    private:
        FT_Library library;

        FT_Face loadedFaces[NUMBER_OF_FONTS];
        std::unordered_map<int, Font*> loadedFonts[NUMBER_OF_FONTS];
        char* fontPaths[NUMBER_OF_FONTS];

    public:
        FontManager();
        ~FontManager();

        bool loadFont(FontLocation fontIndex, int size);
        void unloadFont(FontLocation fontIndex, int size);
        Font* getFont(FontLocation fontIndex, int size);
        bool loadFontPaths(const char* indicesFilePath);
        
};