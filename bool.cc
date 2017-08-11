#include <cstdio>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>
#include <readline/readline.h>
using namespace std;

using VS = vector <string>;

int const MAX_LEN = 512;

VS f[MAX_LEN][MAX_LEN];      // f[i][j] - all solutions s.t. s[i..j] evals to false
VS t[MAX_LEN][MAX_LEN];      // t[i][j] - all solutions s.t. t[i..j] evals to true

inline bool is_op(char const c) { return '&' == c || '|' == c || '^' == c; }

// x = a x b
void combine(VS &x, char const op, VS &a, VS &b) {
    if (a.empty() || b.empty()) return;
    string l, r;
    for (auto &_l: a) {
        l = _l.size() > 1 ?"(" + _l + ")" : _l;
        for (auto &_r: b) {
            r = _r.size() > 1 ?"(" + _r + ")" : _r;
            x.push_back(l + op + r);
        }
    }
}

void init(int len=MAX_LEN) {
    for (int i=0; i<len; ++i) for (int j=0; j<len; ++j) {
        f[i][j].clear();
        t[i][j].clear();
    }
}

// assume `s` always has correct format
//   S = Term | Term Operator S
//   Term = 'T' | 'F'
//   Operator = '&' | '|' | '^'
void gao(char *s, int len) {
    init(len);

    for (int i=0; i<len; ++i) if (!is_op(s[i])) {
        if ('T' == s[i]) t[i][i] = {"T"};
        else f[i][i] = {"F"};
    }

    for (int l=3; l<=len; l+=2) {
        for (int i=0; i+l<=len; i+=2) {
            int j = i + l - 1;
            for (int k=i+1; k<=j; k+=2) {
                assert(is_op(s[k]));
                if ('&' == s[k]) {
                    combine(t[i][j], s[k], t[i][k-1], t[k+1][j]);
                    combine(f[i][j], s[k], t[i][k-1], f[k+1][j]);
                    combine(f[i][j], s[k], f[i][k-1], t[k+1][j]);
                    combine(f[i][j], s[k], f[i][k-1], f[k+1][j]);
                } else if ('|' == s[k]) {
                    combine(t[i][j], s[k], t[i][k-1], t[k+1][j]);
                    combine(t[i][j], s[k], f[i][k-1], t[k+1][j]);
                    combine(t[i][j], s[k], t[i][k-1], f[k+1][j]);
                    combine(f[i][j], s[k], f[i][k-1], f[k+1][j]);
                } else if ('^' == s[k]) {
                    combine(t[i][j], s[k], t[i][k-1], f[k+1][j]);
                    combine(t[i][j], s[k], f[i][k-1], t[k+1][j]);
                    combine(f[i][j], s[k], t[i][k-1], t[k+1][j]);
                    combine(f[i][j], s[k], f[i][k-1], f[k+1][j]);
                } else {
                    throw ">_<";
                }
            }
        }
    }
}

int main() {
    printf("must provide a valid boolean expression\n");
    printf("press c-c to quit\n\n");
    while (true) {
        char *s = readline("> ");
        int len = strlen(s);
        gao(s, len);
        if (t[0][len-1].empty()) printf("there is no way to make %s true!\n", s);
        else for (auto &r: t[0][len-1]) puts(r.c_str());
    }
    return 0;
}
