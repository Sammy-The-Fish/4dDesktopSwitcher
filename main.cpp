#include <fstream>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "DesktopPosition.h"

using namespace  std;

int gui(int argc, char** argv) {
    QFont font ("Jetbrains Mono");
    QApplication a(argc, argv);

    const int columns = 4;


    QWidget window;
    window.setFixedSize(500,150);

    QGridLayout layout = QGridLayout();

    QLabel title = QLabel("Desktop Switcher");

    layout.addWidget(&title, 0, 0, 1, columns, Qt::AlignHCenter);

    int values[columns] = {0};


    for (int i =0; i< columns; i++) {
        QPushButton *plusButton = new QPushButton("+");
        QLabel *label = new QLabel("0");
        QPushButton *minusButton = new QPushButton("-");

        QObject::connect(plusButton, &QPushButton::clicked, [label, i, &values]() {
            values[i] += 1;
            QString test = QString::number(values[i]);
            label->setText(test);
        } );


        QObject::connect(minusButton, &QPushButton::clicked, [label, i, &values]() {
            values[i] -= 1;
            label->setText(QString::number(values[i]));
        });

        layout.addWidget(plusButton, 1, i);
        layout.addWidget(label, 2, i, Qt::AlignCenter);
        layout.addWidget(minusButton, 3, i);
    }




    window.setLayout(&layout);
    window.show();
    return QApplication::exec();
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
    return DesktopPosition(pos);


}



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
            cout << "";


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
