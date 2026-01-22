//
// Created by sam on 20/01/2026.
//

#ifndef INC_4DDESKTOPSWITCHER_FOURDVECTOR_H
#define INC_4DDESKTOPSWITCHER_FOURDVECTOR_H
#include <string>
#include <vector>
using namespace std;

class DesktopPosition {
private:
public:
    vector<int> pos;

    explicit DesktopPosition(vector<int> &pos);

    int hash() const;

    void changeIndex(int i, int delta);

    string toString() const;

    int move();

    int save() const;

};


#endif //INC_4DDESKTOPSWITCHER_FOURDVECTOR_H