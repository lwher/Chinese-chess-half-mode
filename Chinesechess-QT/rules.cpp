#include "classes.h"

//red   0:帅 1:士 2:相 3:车 4:马 5:炮 6:兵
//black 7:将 8:士 9:象 10:车 11:马 12:炮 13:卒
//14: 空 15: 背面
bool belong(int x){ // 0: red  1: black
    return ((x >= 0 && x <= 6) ^ 1);
}

bool Can_move(int x, int y, int nx, int ny){// check (x, y) --> (nx, ny)
    //if(x < 1 || x > 4 || y < 1 || y > 8 || nx < 1 || nx > 4 || ny < 1 || ny > 8) return false;
    if(Map[x][y] % 7 == 5){ // 炮
        if(abs(x - nx) + abs(y - ny) == 1){
            if(Map[nx][ny] == 14) return true;
            else return false;
        }
        else if((abs(x - nx) == 2 && y == ny) || (x == nx && abs(y - ny) == 2)){
            if(Map[x + (nx - x) / 2][y + (ny - y) / 2] == 14) return false;
            if(Map[nx][ny] == 14 || is_back[nx][ny]) return false;
            if(belong(Map[nx][ny]) != belong(Map[x][y])) return true;
            else return false;
        }
        else return false;
    }
    else{
        if(abs(x - nx) + abs(y - ny) > 1) return false;
        int A = Map[x][y], B = Map[nx][ny];
        if(A == 14 || is_back[x][y]) return false;
        else if(is_back[nx][ny]) return false;
        else if(B == 14) return true;
        else if(belong(A) == belong(B)) return false;
        else if(A % 7 == 0 && B % 7 == 6) return 0;
        else if(A % 7 <= B % 7 || (A % 7 == 6 && B % 7 == 0)) return true;
        else return false;
    }
}

bool is_over(){
    int cnt[2]; //0: red 1: black
    cnt[0] = 0; cnt[1] = 0;
    for(int i = 1; i <= 4; ++i)
        for(int j = 1; j <= 8; ++j)
            if(Map[i][j] != 14)
                ++cnt[belong(Map[i][j])];
    if(!cnt[0]) QMessageBox::about(NULL, "提示", "黑方获胜！");
    if(!cnt[1]) QMessageBox::about(NULL, "提示", "红方获胜！");
    return !cnt[0] || !cnt[1];
}

void set_start(){
    int rand_chess[32], top = 0;
    rand_chess[top++] = 0; rand_chess[top++] = 7;
    for(int i = 1; i <= 5; ++i){
        for(int j = 1; j <= 2; ++j)
            rand_chess[top++] = i;
    }
    for(int i = 8; i <= 12; ++i){
        for(int j = 1; j <= 2; ++j)
            rand_chess[top++] = i;
    }
    for(int i = 1; i <= 5; ++i){
        rand_chess[top++] = 6;
        rand_chess[top++] = 13;
    }
    for(int i = 1; i <= 200; ++i){
        swap(rand_chess[rand() % 32], rand_chess[rand() % 32]);
    }
    for(int i = 1; i <= 4; ++i){
        for(int j = 1; j <= 8; ++j){
            is_back[i][j] = true;
            Map[i][j] = rand_chess[(i - 1) * 8 + j - 1];
        }
    }
    over = false; status = false; nowturn = false;
    lastX = -1; lastY = -1; rtop = 0;
}
