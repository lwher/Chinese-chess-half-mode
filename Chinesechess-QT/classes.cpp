#include "classes.h"

QApplication *inPro;

bool mode;
bool over;
bool nowturn;
bool AI_id;
bool AI_kind;
bool status;
bool is_back[5][9];
int Map[5][9], lastX, lastY;

Record record[30010];
int rtop;

void swap(int &A, int &B){
    int t = A; A = B; B = t;
}

int abs(int &A){
    return A < 0 ? -A : A;
}
