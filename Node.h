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


using namespace std;

class Node{
private:
    char color;
    pair <int, int> coordinate;
    double g;
    double h;
    double f;
    bool visited;
    Node *parent = nullptr;
public:
    Node(): color(' '), coordinate(-1, -1), g(0), h(0), f(0){};
    Node(pair<int, int> coord, char c){
        coordinate = coord;
        color = c;
        g = h = f = 0;
        visited = false;
    }
    double get_g(){ return g; }
    double get_h(){ return h; }
    double get_f(){ return f; }
    void set_g(double in){
        g = in;
    }
    void set_h(double in){
        h = in;
    }
    void set_f(double in){
        f = in;
    }
    
    char get_color(){
        return color;
    }
    void set_parent(Node* parent_in){
        parent = parent_in;
    }
    bool operator == (Node rhs){
        return (color == rhs.color
                && coordinate.first == rhs.coordinate.first
                && coordinate.second == rhs.coordinate.second);
    }
    bool is_visited(){
        return visited;
    }
    void visit(){
        visited = true;
    }
    Node* get_parent(){
        return parent;
    }
    pair <int, int> get_coordinate(){
        return coordinate;
    }
};
