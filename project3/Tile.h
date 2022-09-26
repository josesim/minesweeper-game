#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <numeric>
#include <map>
using namespace std;
using namespace sf;
struct Tile {
    Vector2f locations;
    int adjMines = 0, sizeT = 32;
    bool mines,flag = false, minesDply =  false, clk = false;
    int addX, addY;
    vector<Tile*> adjacent_tiles;
    int visto = 0;
    Tile();
    Tile( int locX, int locY, bool mineOn);
    bool GetMinesDply() const;
    void MminesDply();
    Vector2f GetLocations() const;
    bool GetClk() const;
    void MClk();
    bool GetFlag() const;
    void Mflag();
    bool GetMines() const;
    int GetADjMines() const;
};