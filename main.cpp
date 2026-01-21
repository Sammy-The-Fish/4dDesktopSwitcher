#include <fstream>
#include <iostream>
#include "FourDVector.h"
using namespace  std;



FourDVector load() {
    string path = getenv("HOME");
    path+= "/pos";
    vector<int> pos;
    ifstream inFile(path);
    int x;
    while (inFile >> x) {
        pos.push_back(x);
    }
    return FourDVector(pos);


}

int change() {

}

int reset() {
    string path = getenv("HOME");

    path = path  + "/pos";

    ofstream outFile(path);

    if (!outFile) {
        return 1;
    }

    outFile << "1 1 1 1";
    outFile.close();
    return 0;
}




int main(int argc, char* argv[]) {

    if (argc > 1) {
        string arg = argv[1];
        if (arg == "-R" || arg == "--reset") {
            return reset();
        }
        else if (arg == "-H" || arg == "--help") {

        } else if (arg == "-C" || arg == "--change") {
            FourDVector pos = load();

            if (argc > 3) {
                const int index = stoi(argv[2]) - 1;
                const int delta = stoi(argv[3]);
                pos.changeIndex(index, delta);
                cout << pos.toString();
                pos.move();
                return pos.save();
            }else {
                cout << "provide delta and index";
            }


        }
    }





    return 0;

}
