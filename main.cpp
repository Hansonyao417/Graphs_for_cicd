#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "map.cpp"

using namespace std;


int main(){
    int row, col;
    Map MAP;
    
    std::ifstream fin;
    std::ofstream fout;

    std::string inFileName = "input1.txt";
    std::string outFileName = "out1.txt";

//    std::cout << "Please Enter Input File Name: ";
//    std::cin >> inFileName;
    fin.open(inFileName);
    if (fin.fail()){
        std::cout << "In file failed to open." << std::endl;
    }
//    std::cout << "Please Enter Output File Name: ";
//    std::cin >> outFileName;
    fout.open(outFileName);
    if (fout.fail()){
        std::cout << "Out file failed to open." << std::endl;
    }

    
    
    string line;
    fin >> row >> col;
    MAP.resize(row, col);
    int row_index = 0;
    while (fin >> line && row_index < row){
        for (int col_index = 0; col_index < col; col_index++){
            MAP.at(row_index, col_index) = Node(make_pair(row_index, col_index), line[col_index]);
        }
        row_index++;
    }
    
    
//    bool foo = MAP.Astar_shortest_path(make_pair(0, 0), make_pair(4, 4));
//    foo = false;
//    MAP.print_map(fout);
    
    
    bool foo = MAP.BFS_find_path(make_pair(0, 0), make_pair(5, 5));
    foo = false;
    vector<pair<int, int>> path;
    MAP.back_trace(make_pair(5, 5), path);
}

