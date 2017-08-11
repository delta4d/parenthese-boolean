#include <bits/stdc++.h>
using namespace std;

using VS = vector <string>;

int const MAX_LEN = 512;

char s[MAX_LEN];
VS f[MAX_LEN][MAX_LEN];      // f[i][j] - all solutions s.t. s[i..j] evals to false
VS t[MAX_LEN][MAX_LEN];      // t[i][j] - all solutions s.t. t[i..j] evals to true
bool fv[MAX_LEN][MAX_LEN];   // fv[i][j] - wether f[i][j] has been calculated
bool tv[MAX_LEN][MAX_LEN];   // tv[i][j] - wether t[i][j] has been calculated

void T(char *, int, int);
void F(char *, int, int);

inline bool is_op(char const c) { return '&' == c || '|' == c || '^' == c; }

// x = a x b
void combine(VS &x, char const op, VS &a, VS &b) {
    string l, r;
    for (auto &_l: a) {
        l = _l.size() > 1 ?"(" + _l + ")" : _l;
        for (auto &_r: b) {
            r = _r.size() > 1 ?"(" + _r + ")" : _r;
            x.push_back(l + op + r);
        }
    }
}

// find all solutions which make s[i..j] to true
// and stores it in f[i][j]
void F(char *s, int i, int j) {
    if (fv[i][j]) return;
    if (i == j) {
        if (s[i] == 'F') f[i][j].push_back("F");
        fv[i][j] = true;
        return;
    }
    for (int k=i; k<=j; ++k) if (is_op(s[k])) {
        T(s, i, k-1);
        T(s, k+1, j);
        F(s, i, k-1);
        F(s, k+1, j);
        if ('&' == s[k]) {
            combine(f[i][j], s[k], t[i][k-1], f[k+1][j]);
            combine(f[i][j], s[k], f[i][k-1], t[k+1][j]);
            combine(f[i][j], s[k], f[i][k-1], f[k+1][j]);
        } else if ('|' == s[k]) {
            combine(f[i][j], s[k], f[i][k-1], f[k+1][j]);
        } else if ('^' == s[k]) {
            combine(f[i][j], s[k], t[i][k-1], t[k+1][j]);
            combine(f[i][j], s[k], f[i][k-1], f[k+1][j]);
        } else {
            throw ">_<";
        }
    }
    fv[i][j] = true;
}

// find all solutions which make s[i..j] to true
// and stores it in t[i][j]
void T(char *s, int i, int j) {
    if (tv[i][j]) return;
    if (i == j) {
        if (s[i] == 'T') t[i][j].push_back("T");
        tv[i][j] = true;
        return;
    }
    for (int k=i; k<=j; ++k) if (is_op(s[k])) {
        T(s, i, k-1);
        T(s, k+1, j);
        F(s, i, k-1);
        F(s, k+1, j);
        if ('&' == s[k]) {
            combine(t[i][j], s[k], t[i][k-1], t[k+1][j]);
        } else if ('|' == s[k]) {
            combine(t[i][j], s[k], t[i][k-1], t[k+1][j]);
            combine(t[i][j], s[k], f[i][k-1], t[k+1][j]);
            combine(t[i][j], s[k], t[i][k-1], f[k+1][j]);
        } else if ('^' == s[k]) {
            combine(t[i][j], s[k], t[i][k-1], f[k+1][j]);
            combine(t[i][j], s[k], f[i][k-1], t[k+1][j]);
        } else {
            throw ">_<";
        }
    }
    tv[i][j] = true;
}

void init() {
    for (int i=0; i<MAX_LEN; ++i) for (int j=0; j<MAX_LEN; ++j) {
        f[i][j].clear();
        t[i][j].clear();
        fv[i][j] = false;
        tv[i][j] = false;
    }
}

int main() {
    printf("must provide a valid boolean expression\n");
    printf("press c-c to quit\n\n");
    while (true) {
        init();
        printf("> ");
        scanf("%s", s);
        int len = strlen(s);
        T(s, 0, len-1);
        if (t[0][len-1].empty()) printf("there is no way to make %s true!\n", s);
        else for (auto &r: t[0][len-1]) puts(r.c_str());
    }
    return 0;
}
