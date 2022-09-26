#include "SFML/Graphics.hpp"
#include "Tile.h"
using namespace sf;
using namespace std;
Tile::Tile() = default;
Tile::Tile(int locX, int locY, bool mineOn) {
    addX = locX;
    addY = locY;
    mines = mineOn;
    locations.y = addY*sizeT;
    locations.x = addX*sizeT;
}
bool Tile::GetMinesDply() const {
    return minesDply;
}
void Tile::MminesDply() {
    if(minesDply)
        minesDply = false;
    else
        minesDply = true;
}
bool Tile::GetMines() const {
    return mines;
}
Vector2f Tile::GetLocations() const{
    return locations;
}
int Tile::GetADjMines() const {
    return adjMines;
}
bool Tile::GetClk() const {
    return clk;
}
bool Tile::GetFlag() const {
    return flag;
}
void Tile::Mflag() {
    if(flag == true)
        flag = false;
    else
        flag = true;
}
void Tile::MClk() {
    if(clk = true)
        clk=true;
}