#include <iostream>
#include <string>

using namespace std;

int main() {
    char s[150000];
    char pattern[] = {'E', 'D', 'G', 'N', 'B'};
    cin >> s;
    int i = 0, next = 0, count = 0;
    while('\0' != s[i]) {
        if(pattern[next] == s[i]) {
            next++;
        } else if(pattern[0] == s[i]) {
            next = 1;
        } else {
            next = 0;
        }
        if(next == 5) {
            count++;
            next = 0;
        }
        i++;
    }
    cout << count;

    return 0;
}