//
// Created by sam on 22/01/2026.
//

#ifndef INC_4DDESKTOPSWITCHER_UI_H
#define INC_4DDESKTOPSWITCHER_UI_H
#include <QGridLayout>
#include <QLabel>

#include "DesktopPosition.h"


int gui(int argc, char **argv);
void addAdjustors(QVector<QWidget*> *adjustors, QGridLayout *layout, int columns, QLabel* labels[], DesktopPosition *pos);



#endif //INC_4DDESKTOPSWITCHER_UI_H