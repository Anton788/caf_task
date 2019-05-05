#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct State{
    vector<int> position;
    bool player = true;
};

int gethash(vector<int>& positions){
    int hash = 0;
    int k = 3;
    for (int i = 0; i < positions.size(); ++i){
        hash += positions[i] * k;
        k *= 3;
    }
    return hash;
}

bool is_win(vector<int>& positions){
    vector<int> strs(3, 0);
    vector<int> colls(3, 0);
    vector<int> diag(2, 0);
    for (int k = 0; k < positions.size(); ++k){
        if (positions[k] == 0) {
            strs[k / 3] = -1;
            //cout << strs[k / 3] << k / 3;
            colls[k % 3] = -1;
            if (k % 4 == 0){
                diag[0] = -1;
            }
            if (k == 2 || k == 4 || k == 6){
                diag[1] = -1;
            }
            continue;
        }
        if (strs[k / 3] != -1){
            strs[k / 3] += positions[k];
        }
        if (colls[k % 3] != -1){
            colls[k % 3] += positions[k];
        }
        if (k % 4 == 0 && diag[0] != -1){
            diag[0] += positions[k];
        }
        if ((k == 2 || k == 4 || k == 6) && diag[1] != -1){
            diag[1] += positions[k];
        }
    }
    /*for (int i = 0; i < colls.size(); ++i){
        cout << colls[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < diag.size(); ++i){
        cout << diag[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < strs.size(); ++i){
        cout << strs[i] << " ";
    }
    cout << endl;*/
    for (int i = 0; i < colls.size(); ++i){
        if (colls[i] % 3 == 0 && colls[i] != -1){
            return true;
        }
    }

    for (int i = 0; i < diag.size(); ++i){
        if (diag[i] % 3 == 0 && diag[i] != -1){
            return true;
        }
    }

    for (int i = 0; i < strs.size(); ++i) {
        if (strs[i] % 3 == 0 && strs[i] != -1) {
            return true;
        }
    }
    return false;
}



void Algorithm(){
    vector<int> hashes(100000, 0);
    vector<int> start_position(9, 0);
    hashes[0] = 1;
    queue<State> states;
    State first;
    first.position = start_position;
    first.player = true;
    states.push(std::move(first));
    long long count = 0;
    while(!states.empty()){
        State cur_state = std::move(states.front());
        states.pop();
        if (is_win(cur_state.position)){
            continue;
        }
        int symbol;
        if (cur_state.player){
            symbol = 1;
        } else {
            symbol = 2;
        }
        for (int i = 0; i < cur_state.position.size(); ++i){
            if (cur_state.position[i] == 0) {
                State new_state = cur_state;
                new_state.position[i] = symbol;
                new_state.player = !cur_state.player;
                if (!hashes[gethash(new_state.position)]) {
                    states.push(new_state);
                    hashes[gethash(new_state.position)] = 1;
                    ++count;
                }
            }
        }

    }
    cout << ++count;
}

int main() {
    Algorithm();
    return 0;
}