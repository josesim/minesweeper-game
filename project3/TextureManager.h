//
// Created by User on 4/16/2022.
//

#ifndef PROJECT3_TEXTUREMANAGER_H
#define PROJECT3_TEXTUREMANAGER_H
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;


class TextureManager {

    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
    static string imagesDirectory;
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear();



};


#endif //PROJECT3_TEXTUREMANAGER_H
