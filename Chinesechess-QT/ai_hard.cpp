// id = Misaka20001
#include <bits/stdc++.h>

#include "classes.h"

#define rep(i, n) for (int i = 0; i < (n); ++ i)

using namespace std;

const int H = 4, W = 8, HWB = 128;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const int init_cnt[7] = {1, 2, 2, 2, 2, 2, 5};
const bool online = 1;
const int SPACE_BOUNUS = 150000, BADLUCK = 300000;

const int MOD7[14] = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
const int DIV7[14] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1};

int TLE;
int TIME1 = 300, TIME2 = 300;
int init_val[7] = {6400000, 3200000, 2000000, 600000, 400000, 750000, 250000};
int val[7];

int pre_init_val[7] = {6400000, 3200000, 2000000, 600000, 400000, 750000, 250000};

string NAME = "Misaka20001";

struct pos
{
    int x, y, ex;
    inline pos(int x = -1, int y = -1, int ex = 0) : x(x), y(y), ex(ex) {}
    inline bool avaliable() {return x >= 0 && y >= 0 && x < H && y < W;}
    inline bool operator < (const pos &a) {return ex < a.ex;}
    inline bool equal(const pos &a) {return a.x == x && a.y == y;}
    inline void go(int d) {x += dx[d]; y += dy[d];}
    inline pos(const pos &a, int d, int ex = 0) : ex(ex) {x = a.x + dx[d]; y = a.y + dy[d];}
};

struct board
{
    int a[H][W], cnt[2][7], uscnt[2][7];
    unsigned int fast_id[H][W];
    vector<pos> unshown, tomove[2];
    vector<tuple<pos, pos, int> > moves;
    inline int& aa(const pos &p) {return a[p.x][p.y];}
    inline unsigned int& fid(const pos &p) {return fast_id[p.x][p.y];}
    board()
    {
        memset(a, -1, sizeof(a));
        memcpy(cnt[0], init_cnt, sizeof(cnt[0]));
        memcpy(cnt[1], init_cnt, sizeof(cnt[1]));
        memcpy(uscnt[0], init_cnt, sizeof(uscnt[0]));
        memcpy(uscnt[1], init_cnt, sizeof(uscnt[1]));
        unshown.clear();
        rep(i, 2)
        {
            tomove[i].clear();
            tomove[i].reserve(32);
        }
        unshown.reserve(64);
        rep(i, H) rep(j, W)
        {
            fast_id[i][j] = unshown.size();
            unshown.push_back(pos(i, j));
        }
    }
    void delv(vector<pos> &x, const pos &p)
    {
        unsigned int i = fid(p);
        swap(x[i], x[(int) x.size() - 1]);
        fid(x[i]) = i;
        x.pop_back();
    }
    void show(const pos &p, int color, int kind)
    {
        moves.push_back(make_tuple(p, p, color * 7 + kind));
        delv(unshown, p);
        fid(p) = tomove[color].size();
        tomove[color].push_back(p);
        aa(p) = color * 7 + kind;
        uscnt[color][kind] --;
    }
    void makemove(const pos &p1, const pos &p2)
    {
        moves.push_back(make_tuple(p1, p2, aa(p2)));
        if (aa(p2) != -2)
        {
            cnt[DIV7[aa(p2)]][MOD7[aa(p2)]] --;
            delv(tomove[DIV7[aa(p2)]], p2);
        }
        delv(tomove[DIV7[aa(p1)]], p1);
        fid(p2) = tomove[DIV7[aa(p1)]].size();
        tomove[DIV7[aa(p1)]].push_back(p2);
        aa(p2) = aa(p1);
        aa(p1) = -2;
    }
    void cancelmove()
    {
        pos p1, p2;
        int las;
        tie(p1, p2, las) = moves[(int) moves.size() - 1];
        moves.pop_back();
        if (p1.equal(p2))
        {
            uscnt[DIV7[las]][MOD7[las]] ++;
            delv(tomove[DIV7[aa(p1)]], p1);
            aa(p1) = -1;
            fid(p1) = unshown.size();
            unshown.push_back(p1);
            return;
        }
        aa(p1) = aa(p2);
        aa(p2) = las;
        delv(tomove[DIV7[aa(p1)]], p2);
        fid(p1) = tomove[DIV7[aa(p1)]].size();
        tomove[DIV7[aa(p1)]].push_back(p1);
        if (las != -2)
        {
            fid(p2) = tomove[DIV7[las]].size();
            tomove[DIV7[las]].push_back(p2);
            cnt[DIV7[las]][MOD7[las]] ++;
        }
    }
    bool go(const pos &p1, pos &p2, int d)
    {
        int tar = MOD7[aa(p1)], id = DIV7[aa(p1)];
        p2 = pos(p1, d);
        if (!p2.avaliable()) return false;
        if (aa(p2) == -2) return true;
        if (tar != 5)
        {
            if (aa(p2) == -1 || DIV7[aa(p2)] == id) return false;
            int opp = MOD7[aa(p2)];
            if (tar != 6)
            {
                if ((tar == 0 && opp != 6) || (tar != 0 && tar <= opp)) return true;
                return false;
            }
            if (opp == 0 || opp == 6) return true;
            return false;
        }
        p2.go(d);
        if (p2.avaliable() && aa(p2) >= 0 && DIV7[aa(p2)] != id) return true;
        return false;
    }
    bitset<HWB> hash()
    {
        bitset<HWB> b;
        rep(i, H) rep(j, W)
        {
            int x = a[i][j] + 2, d = (i * W + j) << 2;
            b[d] = x & 1;
            b[d + 1] = x & 2;
            b[d + 2] = x & 4;
            b[d + 3] = x & 8;
        }
        return b;
    }
};

int rounds = 0, WIN = 0, EROUND;
board cb = board();
long long stt;

bool already_tle;
bool timeout()
{
    if (already_tle) return 1;
    return already_tle = ((clock() - stt) * 1000LL / CLOCKS_PER_SEC >= TLE);
}

int calc(int id)
{
    int res = 0;
    rep(i, 7) res += val[i] * cb.cnt[id][i];
    for (pos p : cb.tomove[id]) rep(d, 4)
    {
        pos q;
        if (!cb.go(p, q, d)) continue;
        res += SPACE_BOUNUS;
    }
    return res;
}

int evaluate(int id)
{
    int M1 = calc(id), M2 = calc(id ^ 1);
    if (M1 == 0) return -WIN;
    if (M2 == 0) return WIN;
    return M1 - M2;
}

int naive(int id, int alpha, int beta, int deep)
{
    if (deep <= 0) return evaluate(id);
    int tmp = evaluate(id);
    if (tmp >= beta) return tmp;
    alpha = max(alpha, tmp);
    vector<pos> tm(cb.tomove[id]);
    bool nomove = 1;
    for (pos q1 : tm) rep(d, 4)
    {
        pos q2;
        if (!cb.go(q1, q2, d)) continue;
        if (cb.aa(q2) == -2) continue;
        nomove = 0;
        cb.makemove(q1, q2);
        pos w1, w2;
        int tmp1 = -naive(id ^ 1, -beta, -alpha,  deep - 1);
        cb.cancelmove();
        alpha = max(tmp1, alpha);
        if (beta <= tmp1) return tmp1;
    }
    if (nomove) return evaluate(id);
    return alpha;
}

struct choice
{
    pos p;
    int d, ab;
    choice(pos p, int d, int ab) : p(p), d(d), ab(ab) {}
};
bool operator < (const choice &a, const choice &b) {return a.ab > b.ab;}

const char EXACT = 0, LOWER_BOUND = 1, UPPER_BOUND = 2;
struct piece
{
    int res, deep;
    char type;
    piece(int res = 0, int deep = 0, char type = 0) : res(res), deep(deep), type(type) {}
};

unordered_map<bitset<HWB>, piece> MEM2[2];
const int R = 2;
bool mem_off = 0, check_mode = 0;
int edge_id;

int dfs(pos &p1, pos &p2, int id, int alpha, int beta, int deep, bool fb);

int generate_unshown(pos &p1, int id, int alpha, int beta, int deep)
{
    p1 = pos();
    if (cb.unshown.size())
    {
        vector<pos> tm(cb.unshown);
        for (pos q1 : tm)
        {
            double tmp = 0;
            rep(c, 2) rep(k, 7)
            {
                if (!cb.uscnt[c][k]) continue;
                double p = cb.uscnt[c][k];
                cb.show(q1, c, k);
                pos w1, w2;
                tmp += p * -dfs(w1, w2, id ^ 1, -WIN, WIN, deep - 1, 0);
                cb.cancelmove();
                if (timeout()) return alpha;
            }
            tmp /= cb.unshown.size();
            if (p1.x < 0) p1 = q1;
            if (tmp > alpha)
            {
                alpha = tmp;
                p1 = q1;
            }
            if (tmp > beta) return tmp;
        }
    }
    return alpha;
}

pos second_choice_p1, second_choice_p2;

int dfs(pos &p1, pos &p2, int id, int alpha, int beta, int deep, bool fb = 0)
{
    p1 = p2 = pos();
    if (deep <= 0 || timeout()) return naive(id, alpha, beta, EROUND);
    auto H = cb.hash();
    auto &MEM = MEM2[id];
    if (!mem_off && !check_mode && !fb && MEM.count(H) && MEM[H].deep >= deep)
    {
        auto &x = MEM[H];
        if (x.type == EXACT) return x.res;
        if (x.type == LOWER_BOUND && x.res >= beta) return beta;
        if (x.type == UPPER_BOUND && x.res <= alpha) return alpha;
    }
    pos w1, w2;
    if (!mem_off && !check_mode)
    {
        int tmp = -dfs(w1, w2, id ^ 1, -beta, -alpha, deep - R - 1);
        if (tmp >= beta) return beta;
    }
    vector<pos> tm(cb.tomove[id]);
    vector<choice> all;
    for (pos q1 : tm) rep(d, 4)
    {
        pos q2;
        if (!cb.go(q1, q2, d)) continue;
        cb.makemove(q1, q2);
        all.push_back(choice(q1, d, -naive(id ^ 1, -beta, -alpha, EROUND)));
        cb.cancelmove();
    }
    sort(all.begin(), all.end());
    bool exact_flag = 0;
    int cnt = 0;
    for (auto qc : all)
    {
        pos q1, q2, w1, w2;
        q1 = qc.p;
        cb.go(q1, q2, qc.d);
        cb.makemove(q1, q2);
        int tmp1 = -dfs(w1, w2, id ^ 1, -beta, -alpha, deep - 1);
        cb.cancelmove();
        if (tmp1 == alpha) exact_flag = 1;
        if (tmp1 > alpha)
        {
            alpha = tmp1;
            if (fb) second_choice_p1 = p1, second_choice_p2 = p2;
            p1 = q1, p2 = q2;
            exact_flag = 1;
        }
        if (beta <= tmp1)
        {
            auto &x = MEM[H];
            x.type = LOWER_BOUND;
            x.res = tmp1;
            x.deep = deep;
            return tmp1;
        }
        cnt ++;
        if (timeout()) return alpha;
    }
    if ((int) all.size() < 2)
    {
        pos q1;
        int tmp1 = generate_unshown(q1, id, alpha, beta, deep);
        if (tmp1 == alpha) exact_flag = 1;
        if (tmp1 > alpha)
        {
            alpha = tmp1;
            if (fb) second_choice_p1 = p1, second_choice_p2 = p2;
            p1 = p2 = q1;
            exact_flag = 1;
        }
        if (beta <= tmp1)
        {
            auto &x = MEM[H];
            x.type = LOWER_BOUND;
            x.res = tmp1;
            x.deep = deep;
            return tmp1;
        }
    }
    if (exact_flag)
    {
        auto &x = MEM[H];
        x.type = EXACT;
        x.res = alpha;
        x.deep = deep;
    }
    else
    {
        auto &x = MEM[H];
        x.type = UPPER_BOUND;
        x.res = alpha;
        x.deep = deep;
    }
    return alpha;
}

void fight_for_draw(pos &p1, pos &p2, int id)
{
    vector<pos> tm(cb.tomove[id]);
    vector<choice> all;
    p1 = p2 = pos();
    for (pos q1 : tm) rep(d, 4)
    {
        pos q2;
        if (!cb.go(q1, q2, d)) continue;
        cb.makemove(q1, q2);
        all.push_back(choice(q1, d, -naive(id ^ 1, -WIN, WIN, EROUND)));
        cb.cancelmove();
    }
    sort(all.begin(), all.end());
    p1 = all[0].p;
    cb.go(p1, p2, all[0].d);
    return;
}

unordered_map<bitset<HWB>, int> HIS;
bool small_loop = 0, big_loop = 0;

void AI_hard_make_decision(int &x, int &y, int &xx, int &yy, int id)
{
    EROUND = 10;
    already_tle = 0;
    if (!cb.unshown.size()) TIME1 += TIME2, TIME2 = 0;
    TLE = TIME1;
    rounds ++;
    bitset<HWB> tmp = cb.hash();
    int ccnt = ++ HIS[tmp];
    if (ccnt >= 22) mem_off = 1;
    if (ccnt >= 12) big_loop = 1;
    if (ccnt >= 10) small_loop = 1;
    if (ccnt < 10) small_loop = big_loop = mem_off = 0;
    pos p1 = pos(), p2 = pos();
    stt = clock();
    MEM2[0].clear();
    MEM2[1].clear();
    memcpy(val, init_val, sizeof(val));
    if ((int) cb.tomove[id ^ 1].size() <= 2 && (int) cb.unshown.size() == 0) check_mode = 1;
    if (check_mode && (int) cb.tomove[id].size() > 4)
    {
        int useless = -5 * SPACE_BOUNUS;
        if (cb.cnt[id ^ 1][0] == 0 && cb.cnt[id ^ 1][6] == 0) val[6] = useless;
        int least;
        for (least = 6; least >= 0 && !cb.cnt[id ^ 1][least]; -- least);
        for (int i = 5; i > least; -- i) val[i] = useless;
    }
    int M = naive(id, -WIN, WIN, EROUND), E = M;
    pos pp1, pp2;
    pp1 = pp2 = pos();
    int las_it = -1;
    for (int it = 1; it <= 50; ++ it)
    {
        pos q1, q2;
        int MM;
        second_choice_p1 = second_choice_p2 = pos();
        MM = dfs(q1, q2, id, -WIN, WIN, it, 1);
        if (timeout())
        {
            las_it = it;
            break;
        }
        p1 = q1, p2 = q2;
        pp1 = second_choice_p1, pp2 = second_choice_p2;
        M = MM;
        if (check_mode && M == WIN) break;
    }
    if (big_loop && M > BADLUCK)
    {
        p1 = pp1, p2 = pp2;
    }
    if (cb.unshown.size())
    {
        pos pp1 = cb.unshown[rand() % (int) cb.unshown.size()];
        stt = clock();
        already_tle = 0;
        TLE = TIME2;
        for (int it = 1; it <= 50; ++ it)
        {
            pos q1;
            int EE = generate_unshown(q1, id, -WIN, WIN, it);
            if (timeout() || it == las_it) break;
            pp1 = q1;
            E = EE;
        }
        int Mo = -naive(id ^ 1, -WIN, WIN, EROUND);
        int Mi = naive(id, -WIN, WIN, EROUND);
        if (((big_loop && E > 0) || M < E - BADLUCK || (small_loop && Mo > Mi) || p1.x < 0) && cb.unshown.size())
        {
            p1 = p2 = pp1;
            small_loop = big_loop = 0;
            M = E;
        }
    }
    x = p1.x, y = p1.y;
    xx = p2.x, yy = p2.y;
    if (x < 0)
    {
        fight_for_draw(p1, p2, id);
        x = p1.x, y = p1.y;
        xx = p2.x, yy = p2.y;
    }
}

void AI_hard_change(int x, int y, int xx, int yy, int col, int kind)
{
    //int x, y, xx, yy, col, kind;
    //cin >> x >> y >> xx >> yy >> col >> kind;
    if (x == xx && y == yy)
    {
        cb.show(pos(x, y), col, kind);
    }
    else
    {
        cb.makemove(pos(x, y), pos(xx, yy));
    }
}

inline void end() {std::cout << "END\n" << std::flush;}

void AI_hard_start()
{
    rounds = 0; WIN = 0; EROUND = 0;
    TLE = 0; TIME1 = 300; TIME2 = 300;
    for (int i = 0; i < 7; ++ i) WIN += init_cnt[i] * (init_val[i] + 4 * SPACE_BOUNUS);
    for (int i = 0; i < 7; ++ i) init_val[i] = pre_init_val[i];
    memset(val, 0, sizeof(val));
    cb = board();
    stt = 0;
    already_tle = false;
    mem_off = 0; check_mode = 0; edge_id = 0;
    second_choice_p1 = pos(); second_choice_p2 = pos();
    HIS.clear();
    small_loop = 0; big_loop = 0;
    /*while (true)
    {
        cin >> op;
        if (op == "id")
        {
            cin >> id;
            if (online)
            {
                cout << NAME << endl;
                end();
            }
        }
        else if (op == "message")
        {
            change();
        }
        else if (op == "action")
        {
            int x, y, xx, yy;
            make_decision(x, y, xx, yy, id);
            cout << x << " " << y << " " << xx << " " << yy << endl;
            end();
        }
    }*/
}
