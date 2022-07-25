#pragma once

#include "graphics/text/fontLocations.h"
#include "font.h"
#include <unordered_map>

//Handles the loading and unloading of multiple fonts and sizes
class FontManager{

    private:
        static FT_Library library;

        static FT_Face loadedFaces[NUMBER_OF_FONTS];

        //An array of maps. Every loadable font should a map for different loaded sizes.
        static std::unordered_map<int, Font*> loadedFonts[NUMBER_OF_FONTS];
        static char* fontPaths[NUMBER_OF_FONTS];

        FontManager();
        ~FontManager();

    public:
        
        static void init();
        static void terminate();

        static bool loadFont(FontLocation fontIndex, int size);
        static void unloadFont(FontLocation fontIndex, int size);

        //A font must be loaded before being requested by this function.
        static Font* getFont(FontLocation fontIndex, int size);

        //Loads font paths to the fontPaths vector. The association between fonts and FontLocation indices happen here.
        static bool loadFontPaths(const char* indicesFilePath);
        
};