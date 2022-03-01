#pragma once

#include "graphics/text/fontLocations.h"
#include "font.h"
#include <unordered_map>

class FontManager{

    private:
        static FT_Library library;

        static FT_Face loadedFaces[NUMBER_OF_FONTS];
        static std::unordered_map<int, Font*> loadedFonts[NUMBER_OF_FONTS];
        static char* fontPaths[NUMBER_OF_FONTS];

        FontManager();
        ~FontManager();

    public:
        
        static void init();
        static void terminate();
        static bool loadFont(FontLocation fontIndex, int size);
        static void unloadFont(FontLocation fontIndex, int size);
        static Font* getFont(FontLocation fontIndex, int size);
        static bool loadFontPaths(const char* indicesFilePath);
        
};