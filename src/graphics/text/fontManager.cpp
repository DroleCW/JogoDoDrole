#include "graphics/text/fontManager.h"
#include <fstream>
        
FontManager::FontManager(){

    for(int i = 1; i < NUMBER_OF_FONTS; i++)
        loadedFaces[i] = nullptr;

    loadFontPaths(FONT_INDEX_FILE);

    FT_Init_FreeType(&library);
}
FontManager::~FontManager(){

    for(int i = 1; i < NUMBER_OF_FONTS; i++)
        if(loadedFaces[i])
            FT_Done_Face(loadedFaces[i]);

    for(int i = 1; i < NUMBER_OF_FONTS; i++)
        if(fontPaths[i])
            delete[] fontPaths[i];

    FT_Done_FreeType(library);
}

bool FontManager::loadFont(FontLocation fontIndex, int size){
    if(!loadedFonts[fontIndex].count(size)){
        if(loadedFaces[fontIndex] == nullptr){
            FT_New_Face(library, fontPaths[fontIndex], 0, &loadedFaces[fontIndex]);
        }
        loadedFonts[fontIndex][size] = new Font(loadedFaces[fontIndex], size);
        return true;
    }
    
    return false;
}

void FontManager::unloadFont(FontLocation fontIndex, int size){

    if(loadedFonts[fontIndex].count(size)){
        delete loadedFonts[fontIndex][size];
        loadedFonts[fontIndex].erase(size);
        if(!loadedFonts[fontIndex].size()){
            FT_Done_Face(loadedFaces[fontIndex]);
            loadedFaces[fontIndex] = nullptr;
        }
    }

}

Font* FontManager::getFont(FontLocation fontIndex, int size){
    return loadedFonts[fontIndex][size];
}

bool FontManager::loadFontPaths(const char* indicesFilePath){

    std::ifstream fontIndicesFile;

    fontIndicesFile.open(indicesFilePath);

    for(int i = 1; i < NUMBER_OF_FONTS; i++)
        fontPaths[i] = new char[MAX_FONT_PATH_SIZE];


    if(fontIndicesFile.is_open()){
        int index = 1;
        while (fontIndicesFile.peek() != EOF && index < NUMBER_OF_FONTS){
            fontIndicesFile.ignore(5, ' ');
            fontIndicesFile.getline(fontPaths[index], 40);
            index++;
        }
        if(index == NUMBER_OF_FONTS)
            return true;
        else{
            printf("ERROR: Failure to load all font files\n");
            return false; 
        }
    }
    else{
        printf("ERROR: Could not load font paths.\n");
        return false;
    }
}