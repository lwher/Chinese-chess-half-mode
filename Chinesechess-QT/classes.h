#ifndef CLASSES
#define CLASSES

#include <QMainWindow>
#include <cstring>
#include <QMessageBox>

extern QApplication *inPro;

class Record{
public:
    int lastx, lasty, nx, ny, lastp, np;
    // (lastx, lasty) --> (nx, ny)
    // Map[lastx][lasty] = lastp;  Map[nx][ny] = np;
    Record(int _lastx = 0, int _lasty = 0, int _nx = 0, int _ny = 0, int _lastp = 0, int _np = 0):
        lastx(_lastx), lasty(_lasty), nx(_nx), ny(_ny), lastp(_lastp), np(_np) {}
};
extern Record record[];
extern int rtop;

extern void swap(int &A, int &B);
extern int abs(int &A);
extern bool mode; // 0:P vs P 1:P vs AI
extern bool AI_id; // 0: red, 1: black
extern bool AI_kind; // 0: easy 1: hard
extern bool over; // 0: no 1: yes
extern bool nowturn;// is whose turn 0:red 1:black
extern bool status;// 0:first click 1:second click
extern bool is_back[5][9];
extern int Map[5][9]; // show the chessboard
extern int lastX, lastY;//choose by first click

extern std::string ui_change(int id, int ty);
extern bool is_over();
extern bool belong(int x);
extern bool Can_move(int x, int y, int nx, int ny); //check (x, y) --> (nx, ny)

extern void set_start();

extern void AI_change(int x, int y, int xx, int yy, int col, int kind);
extern void AI_make_decision(int &x, int &y, int &xx, int &yy);
extern void AI_start(bool Id);

extern void AI_hard_change(int x, int y, int xx, int yy, int col, int kind);
extern void AI_hard_make_decision(int &x, int &y, int &xx, int &yy, int id);
extern void AI_hard_start();

#endif // CLASSES

