#include "Tile.h"
#include "stack"
#include "SFML/Graphics.hpp"
#include "Random.h"
#include <fstream>
using namespace std;
using namespace sf;
struct Board {
    vector<vector<int>> lowBoard;
    vector<vector<Tile>> tileBoard2d;
    int mineCount = 0, numGames = 0;
    Board();
    Board(string name);
    Board(int addX, int addY, int minesNum);
    const vector<vector<Tile>>& GetBoard() const;
    int GetMineCount();
    void GetMinesHidden();
    bool MtileFlag(int x, int y);
    void ShowTileRevealed(int x, int y);
    bool GetClk(int x, int y);
    bool winning();
    void GetMinesDply();
    bool IfAllClk();
    bool GetMine_(int x, int y);
    bool GetFlagged_(int x, int y);
    void GetFillAdjBombs();
    void Mflaggs();

};