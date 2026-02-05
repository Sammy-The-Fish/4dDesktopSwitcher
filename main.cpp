#include <fstream>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QFileSystemWatcher>
#include "DesktopPosition.h"
#include "UI.h"


using namespace  std;




int reset(int dimensions = 4) {
    string path = getenv("HOME");

    path = path  + "/pos";

    ofstream outFile(path);

    vector coords(dimensions, 4);

    DesktopPosition pos = DesktopPosition(coords);

    if (!outFile) {
        return 1;
    }

    pos.move();

    outFile << pos.toString();
    outFile.close();
    return 0;
}




int main(int argc, char* argv[]) {

    if (argc == 1) {
        return gui(argc, argv);
    }


    if (argc > 1) {
        const string arg = argv[1];
        if (arg == "-R" || arg == "--reset") {
            const int size = argc > 2 ? stoi(argv[2]) : 4;
            return reset(size);
        }
        if (arg == "-H" || arg == "--help") {
            cout << "Help:\n"
            << "run without argument to launch GUI\n"
            << "-H --help: show this argument\n"
            << "-R --reset {x}: reset program with x dimensions\n"
            << "-C --change {x} {d}: change dimension x by delta d\n" <<endl;
        } else if (arg == "-C" || arg == "--change") {
            DesktopPosition pos = load();

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
