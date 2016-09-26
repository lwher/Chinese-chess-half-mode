#include <ctime>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define time_limit 1.000

#include "classes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

const int H = 4;
const int W = 8;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int easy_id, Num;
int AI_map[H][W], Left[16], Have[16];
int Value[2][7] = {{256, 128, 64, 20, 4, 20, 8}, {256, 128, 64, 20, 4, 20, 8}};
int Rank[7] = {6,5,4,3,1,3,2};
long long Mi[25];
double T_S;

int pre_Value[2][7] = {{256, 128, 64, 20, 4, 20, 8}, {256, 128, 64, 20, 4, 20, 8}};
int pre_Rank[7] = {6,5,4,3,1,3,2};

bool exist(int x, int y) {
    return 0 <= x && x < H && 0 <= y && y < W;
}

void Change_Value(){
    Value[easy_id][6] = 2; Value[easy_id][4] = 8;
}

void AI_change(int x, int y, int xx, int yy, int col, int kind) {//col 0:red, 1:black
    //int x, y, xx, yy, col, kind;
    //cin >> x >> y >> xx >> yy >> col >> kind;
    int tar = col * 7 + kind;
    if (x == xx && y == yy){
        AI_map[x][y] = tar;
        Have[tar]--;
    }
    else {
        if(AI_map[xx][yy] != -2){
            Left[AI_map[xx][yy]]--;
            if(!Left[(easy_id ^ 1) * 7]) Change_Value();
        }
        AI_map[x][y] = -2;
        AI_map[xx][yy] = tar;
    }
}

struct node{
    int Kill, Dead;
    long long fk;
    node(int kill = 0, int dead = 0, long long FK = 0){
        Kill = kill; Dead = dead; fk = FK;
    }
    bool operator > (const node &b) const {
        if(Kill - Dead == b.Kill - b.Dead && fk == b.fk) return Kill > b.Kill;
        if(Kill - Dead == b.Kill - b.Dead) return fk > b.fk;
        else return Kill - Dead > b.Kill - b.Dead;
    }
    bool operator < (const node &b) const {
        if(Kill - Dead == b.Kill - b.Dead && fk == b.fk) return Kill < b.Kill;
        if(Kill - Dead == b.Kill - b.Dead) return fk < b.fk;
        else return Kill - Dead < b.Kill - b.Dead;
    }
};

struct Select{
    int Kill, Dead, x, y, tx, ty;
    long long fk;
    Select(int kill = 0, int dead = 0, int X = 0, int Y = 0, int TX = 0, int TY = 0, long long FirstKill = 0){
        Kill = kill; Dead = dead; x = X; y = Y; tx = TX; ty = TY; fk = FirstKill;
    }
    bool operator > (const Select &b) const{
        if(Kill - Dead == b.Kill - b.Dead && fk == b.fk) return Kill > b.Kill; else
        if(Kill - Dead == b.Kill - b.Dead) return fk > b.fk;
        return Kill - Dead > b.Kill - b.Dead;
    }
}De[325];

inline bool comp(const Select &a, const Select &b){
    if(a.Kill - a.Dead == b.Kill - b.Dead && a.fk == b.fk) return a.Kill > b.Kill; else
    if(a.Kill - a.Dead == b.Kill - b.Dead) return a.fk > b.fk;
    return a.Kill - a.Dead > b.Kill - b.Dead;
}

int top, Step, now[H][W];

void Map_copy(){
    for(int i = 0; i < H; i++)
        for(int j = 0; j < W; j++)
            now[i][j] = AI_map[i][j];
}

bool CanEat(int x, int y, int nx, int ny){
    if(now[x][y] == -2 || now[x][y] == -1) return 0;
    if(now[x][y] % 7 == 0 && now[nx][ny] % 7 == 6) return 0;
    if(now[x][y] % 7 <= now[nx][ny] % 7 || (now[x][y] % 7 == 6 && now[nx][ny] % 7 == 0)) return 1;
    else return 0;
}

node Dfs_Calc(int step_last, int ty, long long fk){
    if(!step_last){
        return node(0, 0, fk);
    }
    int kill, xt, nt, nx, ny;
    long long nfk;
    node res = node(-1e8, 0, fk), tmp;
    if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return tmp;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(now[i][j] >=0 && now[i][j] / 7 == ty){
                if(now[i][j] % 7 == 5){
                    for(int k = 0; k < 4; k++){
                        nx = i + dx[k];
                        ny = j + dy[k];
                        if(!exist(nx, ny)) continue;
                        if(now[nx][ny] == -2){
                            nt = now[nx][ny]; xt = now[i][j];
                            kill = 0;
                            now[nx][ny] = now[i][j]; now[i][j] = -2;
                            nfk = fk;
                            tmp = Dfs_Calc(step_last - 1, ty ^ 1, nfk);
                            if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return tmp;
                            swap(tmp.Kill, tmp.Dead);
                            tmp.Kill += kill;
                            if(tmp > res) res = tmp;
                            now[nx][ny] = nt; now[i][j] = xt;
                        }
                        else{
                            nx = nx + dx[k];
                            ny = ny + dy[k];
                            if(!exist(nx, ny)) continue;
                            if(now[nx][ny] >= 0 && now[nx][ny] / 7 == (ty ^ 1)){
                                kill = Value[ty ^ 1][now[nx][ny] % 7];
                                nt = now[nx][ny]; xt = now[i][j];
                                nfk = fk;
                                if(ty == easy_id){
                                    nfk += Mi[(step_last - 1)/2] * Rank[now[nx][ny] % 7];
                                }
                                now[nx][ny] = now[i][j]; now[i][j] = -2;
                                tmp = Dfs_Calc(step_last - 1, ty ^ 1, nfk);
                                if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return tmp;
                                swap(tmp.Kill, tmp.Dead);
                                tmp.Kill += kill;
                                if(tmp > res) res = tmp;
                                now[nx][ny] = nt; now[i][j] = xt;
                            }
                        }
                    }
                }
                else{
                    for(int k = 0; k < 4; k++){
                        nx = i + dx[k];
                        ny = j + dy[k];
                        if(!exist(nx, ny) || AI_map[nx][ny] == -1) continue;
                        if(now[nx][ny] == -2 || ((now[nx][ny] / 7 == (ty ^ 1)) && CanEat(i, j, nx, ny))){
                            if(now[nx][ny] != -2) kill = Value[ty ^ 1][now[nx][ny] % 7];
                            else kill = 0;
                            nt = now[nx][ny]; xt = now[i][j];
                            nfk = fk;
                            if(ty == easy_id){
                                if(now[nx][ny] != -2) nfk += Mi[(step_last - 1)/2] * Rank[now[nx][ny] % 7];
                            }
                            now[nx][ny] = now[i][j]; now[i][j] = -2;
                            tmp = Dfs_Calc(step_last - 1, ty ^ 1, nfk);
                            if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return tmp;
                            swap(tmp.Kill, tmp.Dead);
                            tmp.Kill += kill;
                            if(tmp > res) res = tmp;
                            now[nx][ny] = nt; now[i][j] = xt;
                        }
                    }
                }
            }
        }
    }
    if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return tmp;
    if(res.Kill == -1e8) res.Kill = 0;
    return res;
}

Select Dfs_GetValue(){
    int nx, ny;
    node tmp;
    top = 0;
    if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return Select();
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(AI_map[i][j] >= 0 && AI_map[i][j] / 7 == easy_id){
                if(AI_map[i][j] % 7 == 5){
                    for(int k = 0; k < 4; k++){
                        nx = i + dx[k];
                        ny = j + dy[k];
                        if(!exist(nx, ny)) continue;
                        if(AI_map[nx][ny] == -2){
                            Map_copy();
                            De[++top] = Select(0, 0, i, j, nx, ny);
                            now[nx][ny] = now[i][j]; now[i][j] = -2;
                            tmp = Dfs_Calc(Step - 1, easy_id ^ 1, 0);
                            if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return Select();
                            swap(tmp.Kill, tmp.Dead);
                            De[top].Kill += tmp.Kill;
                            De[top].Dead += tmp.Dead;
                            De[top].fk = tmp.fk;
                        }
                        else{
                            nx = nx + dx[k];
                            ny = ny + dy[k];
                            if(!exist(nx, ny)) continue;
                            if(AI_map[nx][ny] >= 0 && AI_map[nx][ny] / 7 == (easy_id ^ 1)){
                                Map_copy();
                                De[++top] = Select(0, 0, i, j, nx, ny);
                                De[top].Kill += Value[easy_id ^ 1][now[nx][ny] % 7];
                                long long T = Mi[(Step - 1)/2] * Rank[now[nx][ny] % 7];
                                now[nx][ny] = now[i][j]; now[i][j] = -2;
                                tmp = Dfs_Calc(Step - 1, easy_id ^ 1, T);
                                if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return Select();
                                swap(tmp.Kill, tmp.Dead);
                                De[top].Kill += tmp.Kill;
                                De[top].Dead += tmp.Dead;
                                De[top].fk = tmp.fk;
                            }
                        }
                    }
                }
                else{
                    for(int k = 0; k < 4; k++){
                        nx = i + dx[k];
                        ny = j + dy[k];
                        if(!exist(nx, ny) || AI_map[nx][ny] == -1) continue;
                        Map_copy();
                        if(AI_map[nx][ny] == -2 || ((AI_map[nx][ny] / 7 == (easy_id ^ 1)) && CanEat(i, j, nx, ny))){
                            De[++top] = Select(0, 0, i, j, nx, ny);
                            if(now[nx][ny] != -2){
                                De[top].Kill += Value[easy_id ^ 1][now[nx][ny] % 7];
                                De[top].fk = Mi[(Step - 1)/2] * Rank[now[nx][ny] % 7];
                            }
                            now[nx][ny] = now[i][j]; now[i][j] = -2;
                            tmp = Dfs_Calc(Step - 1, easy_id ^ 1, De[top].fk);
                            if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) return Select();
                            swap(tmp.Kill, tmp.Dead);
                            De[top].Kill += tmp.Kill;
                            De[top].Dead += tmp.Dead;
                            De[top].fk = tmp.fk;
                        }
                    }
                }
            }
        }
    }
    if(double(clock() - T_S)/CLOCKS_PER_SEC >=time_limit) return Select();
    sort(De + 1, De + 1 + top, comp);
    int p = 1;
    while(p < top && (De[p + 1].Kill - De[p + 1].Dead == De[1].Kill - De[1].Dead && De[p + 1].Kill == De[1].Kill) && De[p + 1].fk == De[1].fk) p++;
    if(!top) return Select(-1e8, 0, 0, 0, 0, 0);
    else {
        int w = rand() % p + 1;
        return De[w];
    }
}

struct Updata{
    double Val;
    int x, y, tx, ty;
    Updata(double val = 0.0, int X = 0, int Y = 0, int XX = 0, int YY = 0){
        Val = val; x = X; y = Y; tx = XX; ty = YY;
    }
}Up[325];

inline bool cmp(const Updata &a, const Updata &b){
    return a.Val > b.Val;
}

Updata Dfs_CalcUp(int step_last, int ty){
    if(!step_last){
        return Updata(0.0);
    }
    int kill, xt, nt, nx, ny;
    Updata res = Updata(-1e8), tmp;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(now[i][j] == -1 && ty == easy_id){
                double E = 0;
                for(int k = 0 ; k < 14; k++) if(Have[k]){
                    now[i][j] = k; Have[k]--;
                    tmp = Dfs_CalcUp(step_last - 1, (ty ^ 1));
                    Have[k]++;
                    tmp.Val *= -1;
                    E += (1.000 * Have[k] * tmp.Val) / Num;
                    now[i][j] = -1;
                }
                if(E > res.Val) res.Val = E;
            }

            if(now[i][j] >=0 && now[i][j] / 7 == ty){
                if(now[i][j] % 7 == 5){
                    for(int k = 0; k < 4; k++){
                        nx = i + dx[k];
                        ny = j + dy[k];
                        if(!exist(nx, ny)) continue;
                        if(now[nx][ny] == -2){
                            nt = now[nx][ny]; xt = now[i][j];
                            now[nx][ny] = now[i][j]; now[i][j] = -2;
                            kill = 0;
                            tmp = Dfs_CalcUp(step_last - 1, ty ^ 1);
                            tmp.Val *= -1;
                            tmp.Val += kill;
                            if(tmp.Val > res.Val) res = tmp;
                            now[nx][ny] = nt; now[i][j] = xt;
                        }
                        else{
                            nx = nx + dx[k];
                            ny = ny + dy[k];
                            if(!exist(nx, ny)) continue;
                            if(now[nx][ny] >= 0 && now[nx][ny] / 7 == (ty ^ 1)){
                                kill = Value[ty ^ 1][now[nx][ny] % 7];
                                nt = now[nx][ny]; xt = now[i][j];
                                now[nx][ny] = now[i][j]; now[i][j] = -2;
                                tmp = Dfs_CalcUp(step_last - 1, ty ^ 1);
                                tmp.Val *= -1;
                                if(ty != easy_id) kill *= 2;
                                tmp.Val += kill;
                                if(tmp.Val > res.Val) res = tmp;
                                now[nx][ny] = nt; now[i][j] = xt;
                            }
                        }
                    }
                }
                else{
                    for(int k = 0; k < 4; k++){
                        nx = i + dx[k];
                        ny = j + dy[k];
                        if(!exist(nx, ny) || AI_map[nx][ny] == -1) continue;
                        if(now[nx][ny] == -2 || ((now[nx][ny] / 7 == (ty ^ 1)) && CanEat(i, j, nx, ny))){
                            if(now[nx][ny] != -2) kill = Value[ty ^ 1][now[nx][ny] % 7];
                            else kill = 0;
                            nt = now[nx][ny]; xt = now[i][j];
                            now[nx][ny] = now[i][j]; now[i][j] = -2;
                            tmp = Dfs_CalcUp(step_last - 1, ty ^ 1);
                            tmp.Val *= -1;
                            if(ty != easy_id) kill *= 2;
                            tmp.Val += kill;
                            if(tmp.Val > res.Val) res = tmp;
                            now[nx][ny] = nt; now[i][j] = xt;
                        }
                    }
                }
            }
        }
    }
    if(res.Val < -1e7) res.Val = 0;
    return res;
}

Updata Dfs_UpValue(){
    Updata p;
    top = 0;
    Num = 0;
    for(int i = 0; i < 14; i++)	Num += Have[i];
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(AI_map[i][j] != -1) continue;
            double E = 0;
            for(int k = 0 ; k < 14; k++) if(Have[k]){
                Map_copy();
                now[i][j] = k; Have[k]--;
                p = Dfs_CalcUp(3, (easy_id ^ 1));
                Have[k]++;
                p.Val *= -1;
                E += (1.000 * Have[k] * p.Val) / Num;
            }
            Up[++top] = Updata(E, i, j, i, j);
        }
    }
    sort(Up + 1, Up + 1 + top, cmp);
    int q = 1;
    while(q < top && fabs(Up[q + 1].Val - Up[q].Val) < (1e-6)) q++;
    if(!top) return Updata(-1e8, 0, 0, 0, 0);
    return Up[rand() % q + 1];
}


bool Check_CanKill(){
    bool flag;
    for(int i = 0; i < 7; i++) if(Left[easy_id * 7 + i]){
        flag = 0;
        if(i == 6){
            for(int j = 1; j < 7; j++){
                if(Left[(easy_id ^ 1) * 7 + j]){
                    flag = 1;
                }
            }
        }
        else{
            for(int j = 0; j < 7; j++){
                if(j != 5 && Left[(easy_id ^ 1) * 7 + j]){
                    if(j <= i || (!i && j == 6)) flag = 1;
                }
            }
        }
        if(!flag) return 1;
    }
    return 0;
}

void Start_Kill(){
    bool flag1, flag2;
    for(int i = 0; i < 7; i++) if(Left[easy_id * 7 + i]){
        flag1 = 0; flag2 = 0;
        for(int j = 0; j < 7; j++){
            if(j != 5 && Left[(easy_id ^ 1) * 7 + j]){
                if(j < i || (!i && j == 6)) flag1 = 1;
                if(j <= i || (!i && j == 6)) flag2 = 1;
            }
            if(!flag2) Value[easy_id][i] = 650;
            else if(!flag1) Value[easy_id][i] = 325;
            else Value[easy_id][i] = 0;
        }
    }
}

bool CanBeWill(){
    for(int i = 0; i < 6; i++){
        if(Left[easy_id * 7 + i] || Left[(easy_id ^ 1) * 7 + i]){
            if(Left[easy_id * 7 + i] <= Left[(easy_id ^ 1) * 7 + i] && Left[easy_id * 7 + i + 1] <= Left[(easy_id ^ 1) * 7 + i + 1]) return 0;
            if(Left[easy_id * 7 + i] > Left[(easy_id ^ 1) * 7 + i] || Left[easy_id * 7 + i + 1] > Left[(easy_id ^ 1) * 7 + i + 1]) return 1;
            else return 0;
        }
    }
    return 0;
}

bool Balance(){
    if(Left[easy_id * 7] < Left[(easy_id ^ 1) * 7]) return 0;
    if(Left[easy_id * 7 + 1] < Left[(easy_id ^ 1) * 7 + 1]) return 0;
    if(Left[easy_id * 7 + 2] < Left[(easy_id ^ 1) * 7 + 2]) return 0;
    return 1;
}

void AI_make_decision(int &x, int &y, int &xx, int &yy) {
    T_S = clock();
    if(Check_CanKill()){
        Start_Kill();
    }
    Updata Get = Dfs_UpValue();
    Select Go, nowGo;
    for(Step = 4; ; Step++){
        if(Step >= 50) break;
        nowGo = Dfs_GetValue();
        if(double(clock() - T_S)/CLOCKS_PER_SEC >= time_limit) break;
        Go = nowGo;
        x = Go.x; y = Go.y; xx = Go.tx; yy = Go.ty;
    }

    if(Go.Kill - Go.Dead <= -64){
        if(Get.Val > Go.Kill - Go.Dead|| (Go.Kill < -1e7)){
            x = Get.x; y = Get.y; xx = Get.tx; yy = Get.ty;
        }
    }
    if(Go.Kill - Go.Dead >= -40 && Go.Kill - Go.Dead <= 0 && rand() % 100 + 1 <= 5){
        if(Balance() && Get.Val > -(1e-6)){
            x = Get.x; y = Get.y; xx = Get.tx; yy = Get.ty;
        }
    }
    if(CanBeWill() && Go.Kill - Go.Dead >= -50 && rand() % 100 + 1 <= 5){
        if(Get.Val > -186){
            x = Get.x; y = Get.y; xx = Get.tx; yy = Get.ty;
        }
    }
}

void AI_start(bool Id) {
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            AI_map[i][j] = -1;
        }
    }
    Left[0] = 1; Left[7] = 1; Have[0] = 1; Have[7] = 1;
    for(int i = 1; i < 6; i++) Left[i] = 2, Left[i + 7] = 2, Have[i] = 2, Have[i + 7] = 2;
    Left[6] = Left[13] = 5; Have[6] = Have[13] = 5;
    Mi[0] = 1;
    for(int i = 1; i < 23; i++) Mi[i] = Mi[i - 1] * 7;
    easy_id = Id;
    for(int i = 0; i < 2; ++i) for(int j = 0; j < 7; ++j) Value[i][j] = pre_Value[i][j];
    for(int j = 0; j < 7; ++j) Rank[j] = pre_Rank[j];
}
