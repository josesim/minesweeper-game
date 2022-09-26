#include "Board.h"
#include "SFML/Graphics.hpp"

Board::Board() = default;
Board::Board(string name) {
    ifstream file(name);
    string sentence;
    if (file.is_open()) {
        int q1 = 0;
        while (getline(file, sentence)) {
            vector<Tile> myTiletempVect;
            vector<int> myTempVect;
            myTiletempVect.reserve(sentence.length());
            for(int i=0; i < sentence.length(); i++){
                int num = sentence[i] - '0';
                if(num)
                    mineCount++;
                Tile tile = Tile(i,q1,num);
                myTiletempVect.push_back(tile);
                myTempVect.push_back(num);
            }
            tileBoard2d.push_back(myTiletempVect);
            lowBoard.push_back(myTempVect);
            q1++;
        }
    }
    GetFillAdjBombs();
}
const vector<vector<Tile>> &Board::GetBoard() const {
    return tileBoard2d;
}
int Board::GetMineCount() {
    return mineCount;
}
bool Board::GetFlagged_(int x, int y) {
    return tileBoard2d[y][x].GetFlag();
}

Board::Board(int addX, int addY, int minesNum) {
    int l = minesNum;
    mineCount = minesNum;
    int var = 0;
    for(int j = 0; j<addY ; j++){
        vector<int> myTempVect;
        for(int i = 0 ; i<addX ; i++){
            myTempVect.push_back(var);
        }
        lowBoard.push_back(myTempVect);
    }
    while(l) {
        int yy = Random::Int(0, addY-2);
        int xx = Random::Int(0, addX-2);

        if(lowBoard[yy][xx] == 0){
            lowBoard[yy][xx] = 1;
            l--;
        }
    }
    for(int j = 0;j<addY;j++){
        vector<Tile> temp;
        for(int i = 0 ; i < addX ; i++){
            int num = lowBoard[j][i];
            Tile tile = Tile(i,j,num);
            temp.push_back(tile);
        }
        tileBoard2d.push_back(temp);
    }
    GetFillAdjBombs();
}
bool Board::MtileFlag(int x, int y) {
    tileBoard2d[y][x].Mflag();
    return tileBoard2d[y][x].GetFlag();
}
bool Board::GetClk(int x, int y) {
    return tileBoard2d[y][x].GetClk();
}

void Board::GetFillAdjBombs() {
    for (int j = 0;  j < tileBoard2d.size(); j++) {
        for (int i=0; i < tileBoard2d[j].size(); i++) {
            if(j-1 >= 0){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j-1][i]);
                if(tileBoard2d[j-1][i].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(j-1>=0 && i-1>=0){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j-1][i-1]);
                if(tileBoard2d[j-1][i-1].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(j-1>=0 && i+1<tileBoard2d[j].size()){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j-1][i+1]);
                if(tileBoard2d[j-1][i+1].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(i-1>=0){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j][i-1]);
                if(tileBoard2d[j][i-1].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(i+1<tileBoard2d[j].size()){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j][i+1]);
                if(tileBoard2d[j][i+1].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(i-1>=0 && j+1<tileBoard2d.size()){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j+1][i-1]);
                if(tileBoard2d[j+1][i-1].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(j+1<tileBoard2d.size()){
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j+1][i]);
                if(tileBoard2d[j+1][i].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
            if(i+1<tileBoard2d[j].size() && j+1<tileBoard2d.size()){ // (j+1,i+1)
                tileBoard2d[j][i].adjacent_tiles.push_back(&tileBoard2d[j+1][i+1]);
                if(tileBoard2d[j+1][i+1].GetMines())
                    tileBoard2d[j][i].adjMines++;
            }
        }
    }
}
void Board::Mflaggs() {
    for(int j = 0; j <= tileBoard2d.size()-1; j++) {
        for (int i = 0; i <= tileBoard2d[j].size()-1; i++) {
            if (!tileBoard2d[j][i].GetFlag() && tileBoard2d[j][i].GetMines())
                tileBoard2d[j][i].Mflag();
        }
    }
}
bool Board::GetMine_(int x, int y) {
    return tileBoard2d[y][x].GetMines();
}
bool Board::winning() {
    if(IfAllClk() == true)
        return true;
    else
        return false;
}
void Board::ShowTileRevealed(int x, int y) {
    stack<Tile*> tiles;
    tiles.push(&tileBoard2d[y][x]);

    while(!tiles.empty()){
        Tile* pp = tiles.top();
        tiles.pop();
        if(pp->GetFlag() == false) {
            pp->visto++; pp->MClk();
        }
        if(pp->adjMines == 0) {
            for (auto &adjacent_tile: pp->adjacent_tiles) {
                if (!adjacent_tile->GetFlag())
                    adjacent_tile->MClk();
                if (!adjacent_tile->visto && adjacent_tile->adjMines == 0) {
                    tiles.push(adjacent_tile);   } } } } }

void Board::GetMinesDply() {
    for(int j = 0; j<tileBoard2d.size();j++){
        for(int i = 0; i<tileBoard2d[j].size();i++){
            if(tileBoard2d[j][i].GetMines()){
                tileBoard2d[j][i].MminesDply();
            }
        }
    }
}
void Board::GetMinesHidden() {
    for(int j = 0; j<tileBoard2d.size();j++){
        for(int i = 0; i<tileBoard2d[j].size();i++){
            if(tileBoard2d[j][i].GetMines()){
                tileBoard2d[j][i].MminesDply();
            }
        }
    }
}
bool Board::IfAllClk() {
    for(int j = 0; j<tileBoard2d.size();j++){
        for(int i = 0; i<tileBoard2d[j].size();i++){
            if((tileBoard2d[j][i].GetFlag() || !tileBoard2d[j][i].GetClk()) && !tileBoard2d[j][i].GetMines()){
                return false;
            }
        }
    }
    return true;}
