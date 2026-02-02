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
#include <QSizePolicy>

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

    QVector<QWidget *> *adjustors = new QVector<QWidget *>;


    QWidget window;
    window.setFixedSize(500, 150);

    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *innerLayout = new QHBoxLayout;


    QLabel *title = new QLabel("Desktop Switcher");
    QPushButton *reset = new QPushButton("reset");

    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    layout->addLayout(innerLayout, Qt::AlignCenter);

    reset->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);



    layout->addWidget(reset,0, Qt::AlignCenter);


    int values[columns];
    for (int i = 0; i < columns; i++) {
        values[i] = 0;
    }

    QLabel *labels[columns];


    QObject::connect(reset, &QPushButton::clicked, [layout, &pos, &adjustors, &labels, &columns, innerLayout]() {
        QDialog *resetDialogue = new QDialog();
        QGridLayout *dialogueLayout = new QGridLayout();
        resetDialogue->setAttribute(Qt::WA_DeleteOnClose);

        resetDialogue->setWindowTitle("reset dialogue");
        resetDialogue->setFixedSize(250, 100);

        QLabel *popupTitle = new QLabel("How many dimensions?", resetDialogue);

        dialogueLayout->addWidget(popupTitle, 0, 0);

        QLineEdit *edit = new QLineEdit(resetDialogue);
        edit->setValidator(new QIntValidator(1, 25, edit));

        dialogueLayout->addWidget(edit, 1, 0);


        QPushButton *submit = new QPushButton("submit");

        dialogueLayout->addWidget(submit, 2, 0);

        QObject::connect(submit, &QPushButton::pressed,
                         [resetDialogue, edit, layout, &pos, &adjustors, &labels, &columns, innerLayout]() {
                             int input = edit->text().toInt();
                             if (input > 1 && input < 25) {
                                 resetDialogue->close();
                                 vector<int> *newPos = new vector(edit->text().toInt(), 1);
                                 pos = DesktopPosition(*newPos);
                                 columns = pos.size;
                                 addAdjustors(adjustors, innerLayout, columns, labels, &pos);
                                 pos.save();
                                 pos.move();
                                 updateLabels(labels, pos);
                             }
                         });
        QObject::connect(edit, &QLineEdit::returnPressed, submit, &QPushButton::click);

        resetDialogue->setLayout(dialogueLayout);
        resetDialogue->show();
    });

    QObject::connect(watcher, &QFileSystemWatcher::fileChanged, [&labels]() {
        DesktopPosition pos = load();
        updateLabels(labels, pos);
        pos.move();
    });


    addAdjustors(adjustors, innerLayout, columns, labels, &pos);


    updateLabels(labels, pos);
    pos.move();

    window.setLayout(layout);
    window.show();
    return QApplication::exec();
}

void addAdjustors(QVector<QWidget *> *adjustors, QHBoxLayout *layout, int columns, QLabel *labels[],
                  DesktopPosition *pos) {
    for (QWidget *a: *adjustors) {
        layout->removeWidget(a);
        a->deleteLater();
    }


    adjustors->clear();

    for (int i = 0; i < columns; i++) {
        QVBoxLayout *innerLayout = new QVBoxLayout;
        innerLayout->setAlignment(Qt::AlignCenter);

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
            label->setText(QString::number(pos->getIndex(i)));
        });
        QObject::connect(minusButton, &QPushButton::clicked, [label, i, pos]() {
            pos->changeIndex(i, -1);
            pos->save();
            label->setText(QString::number(pos->getIndex(i)));
        });
        innerLayout->addWidget(plusButton);
        label->setAlignment(Qt::AlignHCenter);
        innerLayout->addWidget(label);

        innerLayout->addWidget(minusButton);
        layout->addLayout(innerLayout);
    }
}
