#include <iostream>
#include <string>
#define C41 4
#define C42 6

using namespace std;

int main() {
    char card[27];
    cin >> card;
    int m[9] = {0};
    int p[9] = {0};
    int s[9] = {0};
    int z[7] = {0};
    long long comb[14] = {483774556165488000, 46243156104054000, 4110502764804800, 337429331439200, 25370626424000, 1729815438000, 105637584000, 5688177600, 264566400, 10334625, 325500, 7750, 124, 1};

    int len = 0, i = 1;
    long long res = 1;

    while('\0' != card[i - 1]) {
        switch(card[i]) {
            case 'm':
                m[card[i - 1] - '1']++;
                break;
            case 'p':
                p[card[i - 1] - '1']++;
                break;
            case 's':
                s[card[i - 1] - '1']++;
                break;
            case 'z':
                z[card[i - 1] - '1']++;
                break;
            default:
                break;
        }
        i += 2;
    }
    len = i / 2;

    for(int j = 0; j < 9; ++j) {
        switch(m[j]) {
            case 1:
            case 3:
                res *= 4;
                break;
            case 2:
                res *= 6;
                break;
            default:
                break;
        }
    }

    for(int j = 0; j < 9; ++j) {
        switch(p[j]) {
            case 1:
            case 3:
                res *= 4;
                break;
            case 2:
                res *= 6;
                break;
            default:
                break;
        }
    }

    for(int j = 0; j < 9; ++j) {
        switch(s[j]) {
            case 1:
            case 3:
                res *= 4;
                break;
            case 2:
                res *= 6;
                break;
            default:
                break;
        }
    }

    for(int j = 0; j < 7; ++j) {
        switch(z[j]) {
            case 1:
            case 3:
                res *= 4;
                break;
            case 2:
                res *= 6;
                break;
            default:
                break;
        }
    }

    res *= comb[len];
    cout << res;


    return 0;
}