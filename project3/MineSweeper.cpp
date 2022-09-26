#include "MineSweeper.h"
#include <iomanip>
#include "SFML/Graphics.hpp"
MineSweeper::MineSweeper() {
    GetFile(entryBoard + "config.cfg");
    int c   = myMapSTOI["cols"], r   = myMapSTOI["filas"], nM  =  myMapSTOI["mines"];
    remainsMines = nM;
    minesSweeper = Board(c, r, nM);
}
void MineSweeper::GetFile(string name) {
    ifstream file(name);
    string line;
    int cols, rows, numOfMines;
    file >> cols;
    file >> rows;
    file >> numOfMines;
    myMapSTOI.emplace("cols", cols);
    myMapSTOI.emplace("filas", rows);
    myMapSTOI.emplace("mines", numOfMines);
}
void MineSweeper::SetuptTest(int num) {
    setDebug = false;
    setGame = work;
    string n;
    n=entryBoard;
   if(num == 1)
       n += "testboard1.brd";
   if(num == 2)
       n += "testboard2.brd";
   if(num == 3)
       n += "testboard3.brd";
   if(num == 4)
       n += "recursion_test.brd";
   if(num == 5)
       n += "lots_o_mines.brd";
   else
       cout << "?\n";
   minesSweeper = Board(n);
   GetFile(entryBoard+ "config.cfg");

   remainsMines = minesSweeper.GetMineCount();
}
void MineSweeper::Renew() {
    setGame = work;
    int c = myMapSTOI["cols"], r = myMapSTOI["filas"], nM = myMapSTOI["mines"];
    remainsMines = nM;
    minesSweeper = Board(c, r, nM);
}
void MineSweeper::Fail() {
    setGame = f;
    if(!setDebug)
        minesSweeper.GetMinesDply();
    else
        setDebug = false;
}
bool MineSweeper::IfWWW() {
    if( remainsMines >= 0  &&  minesSweeper.winning() ){
        setGame = W;
        if(remainsMines >0)
            remainsMines = 0;
        minesSweeper.Mflaggs();
        return true;
    }
    return false;
}