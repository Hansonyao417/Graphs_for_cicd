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
#include "Node.h"

using namespace std;

class Map{
private:
    vector<vector<Node>> Matrix;
public:
    Map(){}
    void set_row(int row, int col, string &s){
        for (int column = 0; column < col; column++){
            Matrix[row][column] = Node(make_pair(row, column), s[column]);
        }
    }
    void print_map(ofstream &fout){
        int row_num = int(Matrix.size());
        int col_num = int(Matrix[0].size());
        for (int i = 0; i < row_num; i++){
            for (int j = 0; j < col_num; j++){
                fout << Matrix[i][j].get_color() << ' ';
            }
            fout << '\n';
        }
    }
    Node& at(int row, int col){
        return Matrix[row][col];
    }
    void resize(int row, int col){
        Matrix.resize(row, vector<Node>(col));
    }
    bool BFS_find_path(pair<int, int> start, pair<int, int> end){
        queue<Node*> Q;
        vector<pair<int, int>> directions = {
            make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0), make_pair(0, -1)
        };
        Q.push(&Matrix[start.first][start.second]);
        while(!Q.empty()){
            Node* cur = Q.front();
            for (int i = 0; i < directions.size(); i++){
                pair<int, int> node_position = make_pair(
                    cur->get_coordinate().first + directions[i].first,
                    cur->get_coordinate().second + directions[i].second);
                if (node_position.first > Matrix.size() - 1 || node_position.first < 0
                    || node_position.second > Matrix[0].size() - 1 || node_position.second < 0){
                    continue;
                }
                if (Matrix[node_position.first][node_position.second].get_color() != '0'){
                    continue;
                }
                if (Matrix[node_position.first][node_position.second].is_visited()){
                    continue;
                }
                if (node_position.first == end.first && node_position.second == end.second){
                    Matrix[node_position.first][node_position.second].set_parent(cur);
                    return true;
                }
                Q.push(&Matrix[node_position.first][node_position.second]);
                Matrix[node_position.first][node_position.second].set_parent(cur);
            }
            cur->visit();
            Q.pop();
        }
        return false;
    }
    
    
    bool Astar_shortest_path(pair<int, int> start, pair<int, int> end){
        Node *start_node = &Matrix[start.first][start.second];
        Node *end_node = &Matrix[end.first][end.second];
        start_node->set_parent(nullptr);
        vector<Node*> open_list;
        vector<Node*> close_list;
        open_list.push_back(start_node);
        while(open_list.size() > 0){
            Node *current_node = open_list[0];
            int current_index = 0;
            for (int i = 0; i < open_list.size(); i++){
                if (open_list[i]->get_f() < current_node->get_f()){
                    current_node = open_list[i];
                    current_index = i;
                }
            }
            open_list.erase(open_list.begin() + current_index);
            close_list.push_back(current_node);

            if (current_node == end_node){
                cout << "Found" << endl;
                vector<pair<int, int>> path;
                while (current_node != start_node){
                    path.push_back(current_node->get_coordinate());
                    current_node = current_node->get_parent();
                }
                for (int i = 0; i < path.size(); i++){
                    cout << path[i].first << " " << path[i].second << endl;
                }
                return true;
            }

            vector<Node*> children;
            vector<pair<int, int>> new_position = {
                make_pair(-1, 0), make_pair(-1, 1),
                make_pair(0, 1), make_pair(1, 1),
                make_pair(1, 0), make_pair(1, -1),
                make_pair(0, -1), make_pair(-1, -1)
            };

            for (int i = 0; i < new_position.size(); i++){
                pair<int, int> node_position = make_pair(
                    current_node->get_coordinate().first + new_position[i].first,
                    current_node->get_coordinate().second + new_position[i].second);

                if (node_position.first > Matrix.size() - 1 || node_position.first < 0
                    || node_position.second > Matrix[0].size() - 1 || node_position.second < 0){
                    continue;
                }
                if (Matrix[node_position.first][node_position.second].get_color() != '0'){
                    continue;
                }
                Matrix[node_position.first][node_position.second].set_parent(current_node);
                children.push_back(&Matrix[node_position.first][node_position.second]);
            }
            for (int i = 0; i < children.size(); i++){
                for (int j = 0; j < close_list.size(); j++){
                    if (children[i] == close_list[j]){
                        continue;
                    }
                }
                children[i]->set_g(current_node->get_g() + 1);
                children[i]->set_h(pow((children[i]->get_coordinate().first - end_node->get_coordinate().first), 2) +
                                  pow((children[i]->get_coordinate().second - end_node->get_coordinate().second), 2));
                children[i]->set_f(children[i]->get_g() + children[i]->get_h());

                for (int i = 0; i < open_list.size(); i++){
                    if (children[i] == open_list[i] && children[i]->get_g() >= open_list[i]->get_g()){
                        continue;
                    }
                }
                open_list.push_back(children[i]);
            }
        }
        return false;
    }
    
    
    vector<pair<int, int>> back_trace(pair<int, int> end, vector<pair<int, int>>p){
        Node* cur = &Matrix[end.first][end.second];
        vector<pair<int, int>> path;
        while (cur){
            path.push_back(cur->get_coordinate());
            cur = cur->get_parent();
        }
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++){
            cout << "(" << path[i].first << ","  << path[i].second << ")" << endl;
        }
        return path;
    }
};
