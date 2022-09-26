#include "Board.h"
#include "TextureManager.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;
struct MineSweeper {
    map<string,int> myMapSTOI;
    Board minesSweeper;
    string entryBoard = "boards/", setGame,W = "\"win\"",  work ="\"working\"", f = "\"fail\"";
    bool setDebug = false;
    int remainsMines=0, sizeOfT  = 32, cien = 100;
    MineSweeper();
    bool IfWWW();
    void GetFile(string name);
    void Renew();
    void Fail();
    void SetuptTest(int test_num);

void BeginS() {    //_________________________ BEGIN GAME __________________________________________________
    RenderWindow window(VideoMode(myMapSTOI["cols"]*sizeOfT, myMapSTOI["filas"]*sizeOfT + cien), "MineSweeper!");
    Vector2f tSize(myMapSTOI["cols"]*sizeOfT,myMapSTOI["filas"]*sizeOfT + cien);
    setGame = work;
    RectangleShape background( tSize );
    background.setFillColor(Color::Black);

    Sprite debug(TextureManager::GetTexture("debug"));
    Sprite digits(TextureManager::GetTexture("digits"));
    Sprite face_happy(TextureManager::GetTexture("face_happy"));
    Sprite face_lose(TextureManager::GetTexture("face_lose"));
    Sprite t1(TextureManager::GetTexture("test_1"));
    Sprite t2(TextureManager::GetTexture("test_2"));
    Sprite t3(TextureManager::GetTexture("test_3"));
    Sprite face_win(TextureManager::GetTexture("face_win"));
    Sprite flag(TextureManager::GetTexture("flag"));
    Sprite mine(TextureManager::GetTexture("mine"));
    Sprite tile_revealed(TextureManager::GetTexture("tile_revealed"));
    Sprite tile_hidden(TextureManager::GetTexture("tile_hidden"));
    Sprite num1(TextureManager::GetTexture("number_1"));
    Sprite num2(TextureManager::GetTexture("number_2"));
    Sprite num3(TextureManager::GetTexture("number_3"));
    Sprite num4(TextureManager::GetTexture("number_4"));
    Sprite num5(TextureManager::GetTexture("number_5"));
    Sprite num6(TextureManager::GetTexture("number_6"));
    Sprite num7(TextureManager::GetTexture("number_7"));
    Sprite num8(TextureManager::GetTexture("number_8"));

    string number = "number";

    map<int,Sprite> numbers;
    numbers.emplace(1,num1);
    numbers.emplace(2,num2);
    numbers.emplace(3,num3);
    numbers.emplace(4,num4);
    numbers.emplace(5,num5);
    numbers.emplace(6,num6);
    numbers.emplace(7,num7);
    numbers.emplace(8,num8);
    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();}
        window.clear();
        window.draw(background);
        IfWWW();
        for( auto& i : minesSweeper.GetBoard()) {
            for( auto& j : i) {
                tile_hidden.setPosition(j.GetLocations().x, j.GetLocations().y);
                window.draw(tile_hidden);
            }
        }
        for( auto & i : minesSweeper.GetBoard()) {
            for( auto & j : i) {

                if(j.GetClk() && !j.GetFlag()){
                    tile_revealed.setPosition(j.GetLocations().x, j.GetLocations().y);
                    window.draw(tile_revealed);
                    if(j.GetADjMines()>0) {
                        numbers[j.GetADjMines()].setPosition(j.GetLocations().x, j.GetLocations().y);
                        window.draw(numbers[j.GetADjMines()]);
                    }
                }
                if(setGame==f && j.GetMinesDply()){
                    tile_revealed.setPosition(j.GetLocations().x, j.GetLocations().y);
                    window.draw(tile_revealed); }
                if(setGame!=W &&j.GetMinesDply() ){
                    mine.setPosition(j.GetLocations().x, j.GetLocations().y);
                    window.draw(mine);}
                if(j.GetFlag()){
                    flag.setPosition(j.GetLocations().x, j.GetLocations().y);
                    window.draw(flag);}
            }
        }
        if(setGame==work) {
            face_happy.setPosition((myMapSTOI["cols"] * 32) / 2 - 32, myMapSTOI["filas"] * sizeOfT);
            window.draw(face_happy);
        }
        else if(setGame==W) {
            face_win.setPosition((myMapSTOI["cols"] * 32) / 2 - 32, myMapSTOI["filas"] * sizeOfT);
            window.draw(face_win);
        }
        else if(setGame==f) {
            face_lose.setPosition((myMapSTOI["cols"] * 32) / 2 - 32, myMapSTOI["filas"] * sizeOfT);
            window.draw(face_lose);
        }
        debug.setPosition((myMapSTOI["cols"]*32)/2 + sizeOfT+64, myMapSTOI["filas"]*sizeOfT);
        window.draw(debug);

        t1.setPosition((myMapSTOI["cols"]*32)/2 + (sizeOfT*3) + (64*1), myMapSTOI["filas"]*sizeOfT);
        window.draw(t1);
        t2.setPosition((myMapSTOI["cols"]*32)/2 +(sizeOfT*3) + (64*2), myMapSTOI["filas"]*sizeOfT);
        window.draw(t2);
        t3.setPosition((myMapSTOI["cols"]*32)/2 +(sizeOfT*3) + (64*3), myMapSTOI["filas"]*sizeOfT);
        window.draw(t3);

        int p = remainsMines / cien, r = (remainsMines%cien) / 10,b = remainsMines%10;
        digits.setTextureRect(IntRect(21*p,0,21,sizeOfT));
        digits.setPosition(21, myMapSTOI["filas"]*sizeOfT);
        window.draw(digits);
        digits.setTextureRect(IntRect(21*r,0,21,sizeOfT));
        digits.setPosition(21*2, myMapSTOI["filas"]*sizeOfT);
        window.draw(digits);
        digits.setTextureRect(IntRect(21*b,0,21,sizeOfT));
        digits.setPosition(21*3, myMapSTOI["filas"]*sizeOfT);
        window.draw(digits);
        window.display();

        if(setGame==work) {
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Right) {
                    if (event.mouseButton.y < myMapSTOI["filas"] * 32) {
                        if(!minesSweeper.GetClk(event.mouseButton.x / 32,
                                                event.mouseButton.y / 32) || minesSweeper.GetFlagged_(event.mouseButton.x / 32,
                                                                                                      event.mouseButton.y / 32)){
                            bool changed = minesSweeper.MtileFlag(event.mouseButton.x / 32,
                                                                  event.mouseButton.y / 32);
                            if (changed)
                                remainsMines--;
                            else
                                remainsMines++;}} }}}

        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                if(event.mouseButton.y < myMapSTOI["filas"]*32){
                    if(setGame==work && !minesSweeper.GetFlagged_(event.mouseButton.x / 32, event.mouseButton.y / 32)) {
                        if (minesSweeper.GetMine_(event.mouseButton.x / 32, event.mouseButton.y / 32)) {
                            Fail();
                        } else if (!minesSweeper.GetClk(event.mouseButton.x / 32, event.mouseButton.y / 32)) {
                            minesSweeper.ShowTileRevealed(event.mouseButton.x / 32, event.mouseButton.y / 32);} }}

                else if(event.mouseButton.y < myMapSTOI["filas"]*sizeOfT+64) {
                    if(event.mouseButton.x > ((myMapSTOI["cols"]*32)/2 - 32) && event.mouseButton.x < ((myMapSTOI["cols"]*32))/2 + 32){
                        Renew();
                    }
                    else if(event.mouseButton.x > ((myMapSTOI["cols"]*32)/2 + (32*3) + (64*3)) && event.mouseButton.x < ((myMapSTOI["cols"]*32)/2 + (32*3) + (64*1) + 64*3)){
                        SetuptTest(3);
                    }
                    else if( event.mouseButton.x > ((myMapSTOI["cols"]*32)/2 + (32*3) + (64*2)) && event.mouseButton.x < ((myMapSTOI["cols"]*32)/2 + (32*3) + (64*1) + 64*2)){
                        SetuptTest(2);
                    }
                    else if( event.mouseButton.x > ((myMapSTOI["cols"]*32)/2 + (32*3) + (64*1)) && event.mouseButton.x < ((myMapSTOI["cols"]*32)/2 + (32*3) + (64*1) + 64)){
                        SetuptTest(1);
                    }
                    else if(setGame==work && event.mouseButton.x > ((myMapSTOI["cols"]*32)/2 + 32+64) && event.mouseButton.x < ((myMapSTOI["cols"]*32)/2 + 32+64)+ 64){
                        if(setDebug){
                            setDebug = false;
                            minesSweeper.GetMinesHidden();
                        }
                        else{
                            setDebug = true;
                            minesSweeper.GetMinesDply();  } } } }} }
}};