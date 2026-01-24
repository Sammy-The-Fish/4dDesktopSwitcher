//
// Created by sam on 20/01/2026.
//

#include "DesktopPosition.h"

#include <fstream>
#include <iostream>
#include <utility>


DesktopPosition::DesktopPosition(vector<int> &pos) {
    this->pos = pos;
    this->size = pos.size();
}

int DesktopPosition::hash() const {
    int num = 0;
    for(int x : pos) {
        num = (num * 101 + x) % 1000000; // 101 = base, 1,000,000 = limit
    }
    return num;
}

void DesktopPosition::changeIndex(int i, int delta) {
    cout << "test" <<endl;
    if (pos[i] + delta <= 100 && pos[i] + delta >= 1) {
        pos[i] += delta;
    }
}

string DesktopPosition::toString() const {
    string out = "";
    for (const int x : pos) {
        out += to_string(x) + " ";
    }

    return out;
}
int DesktopPosition::save() const {
    string path = getenv("HOME");
    path += "/pos";


    ofstream outFile(path);
    if (!outFile) {
        return 1;
    }
    outFile << toString();
    outFile.close();
    return 0;
}


int DesktopPosition::getIndex(int i) {
    return pos[i];
}


int DesktopPosition::move() {
    const string command = "hyprctl dispatch workspace " + to_string(hash());
    return system(command.c_str());
}


DesktopPosition load() {
    string path = getenv("HOME");
    path+= "/pos";
    vector<int> pos;
    ifstream inFile(path);
    int x;
    while (inFile >> x) {
        pos.push_back(x);
    }
    inFile.close();
    return DesktopPosition(pos);
}