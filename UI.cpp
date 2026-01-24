//
// Created by sam on 22/01/2026.
//
#include "UI.h"
#include <fstream>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QFileSystemWatcher>
#include <QDialog>
#include "DesktopPosition.h"
#include <QLineEdit>
#include <QIntValidator>


void updateLabels(QLabel *labels[], DesktopPosition pos) {
    for (int i = 0; i < pos.size; i++) {
        labels[i]->setText(QString::number(pos.getIndex(i)));
    }
}

int gui(int argc, char **argv) {
    QFont font("Jetbrains Mono");
    QApplication a(argc, argv);

    string path = getenv("HOME");

    path = path + "/pos";

    QFileSystemWatcher *watcher = new QFileSystemWatcher();
    watcher->addPath(path.data());


    DesktopPosition pos = load();

    int columns = pos.size;

    QVector<QWidget*> adjustors;


    QWidget window;
    window.setFixedSize(500, 150);

    QGridLayout *layout = new QGridLayout();

    QLabel *title = new QLabel("Desktop Switcher");
    layout->addWidget(title, 0, 0, 1, columns, Qt::AlignHCenter);


    QPushButton reset = QPushButton("reset");
    layout->addWidget(&reset, 4, 0, 1, columns, Qt::AlignCenter);


    int values[columns];
    for (int i = 0; i < columns; i++) {
        values[i] = 0;
    }

    QLabel *labels[columns];


    QObject::connect(&reset, &QPushButton::clicked, [layout, title, &pos, &adjustors, &labels, &columns]() {
        QDialog *resetDialogue = new QDialog();
        QGridLayout dialogueLayout = QGridLayout();

        resetDialogue->setWindowTitle("reset dialogue");
        resetDialogue->setFixedSize(250, 100);

        QLabel *popupTitle = new QLabel("How many dimensions?", resetDialogue);

        dialogueLayout.addWidget(popupTitle, 0, 0);

        QLineEdit *edit = new QLineEdit(resetDialogue);
        edit->setValidator(new QIntValidator(1, 25, edit));

        dialogueLayout.addWidget(edit, 1, 0);


        QPushButton *submit = new QPushButton("submit");

        dialogueLayout.addWidget(submit, 2, 0);

        QObject::connect(submit, &QPushButton::pressed, [resetDialogue, edit, layout, title, &pos, &adjustors, &labels, &columns]() {
            int input = edit->text().toInt();
            if (input > 0 && input < 25) {
                resetDialogue->close();
                cout << edit->text().toInt() << endl;
                vector newPos(edit->text().toInt(), 1);
                pos = DesktopPosition(newPos);
                columns = pos.size;
                addAdjustors(&adjustors, layout, columns, labels, &pos);
                updateLabels(labels, pos);
            }
        });
        QObject::connect(edit, &QLineEdit::returnPressed, submit, &QPushButton::click);

        resetDialogue->setLayout(&dialogueLayout);
        resetDialogue->show();
    });

    QObject::connect(watcher, &QFileSystemWatcher::fileChanged, [&labels]() {
        DesktopPosition pos = load();
        updateLabels(labels, pos);
        pos.move();
    });


    addAdjustors(&adjustors, layout, columns, labels, &pos);


    updateLabels(labels, pos);
    pos.move();

    window.setLayout(layout);
    window.show();
    return QApplication::exec();
}

void addAdjustors(QVector<QWidget *> *adjustors, QGridLayout *layout, int columns, QLabel *labels[],
                  DesktopPosition *pos) {
    cout << "test 1" << endl;
    for (QWidget *a: *adjustors) {
        cout << "is this running" << endl;
        layout->removeWidget(a);
        a->deleteLater();
    }

    cout << columns << endl;
    //CHANGE THIS AT SOME POINT!!!!!!
    for (int i = 0; i < columns; i++) {
        QPushButton *plusButton = new QPushButton("+");
        QLabel *label = new QLabel("0");
        QPushButton *minusButton = new QPushButton("-");
        adjustors->append(plusButton);
        adjustors->append(label);
        adjustors->append(minusButton);
        labels[i] = label;
        QObject::connect(plusButton, &QPushButton::clicked, [label, i, pos]() {
            pos->changeIndex(i, 1);
            pos->save();
            QString test = QString::number(pos->getIndex(i));
            label->setText(test);
        });
        QObject::connect(minusButton, &QPushButton::clicked, [label, i, pos]() {
            pos->changeIndex(i, -1);
            cout << "testin"<< endl;
            pos->save();
            label->setText(QString::number(pos->getIndex(i)));
        });
        layout->addWidget(plusButton, 1, i);
        layout->addWidget(label, 2, i, Qt::AlignCenter);
        layout->addWidget(minusButton, 3, i);
    }


}
