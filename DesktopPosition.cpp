//
// Created by sam on 20/01/2026.
//

#include "DesktopPosition.h"

#include <fstream>
#include <iostream>
#include <utility>


DesktopPosition::DesktopPosition(vector<int> &pos) {
    this->pos = pos;
}

int DesktopPosition::hash() const {
    int total = 0;
    for (int x : pos) {
        total += x * 101;
    }
    return total;
}

void DesktopPosition::changeIndex(int i, int delta) {
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


int DesktopPosition::move() {
    const string command = "hyprctl dispatch workspace " + to_string(hash());
    return system(command.c_str());
}
