#include <iostream>
using namespace std;
int main()
{
    string tmp;
    cin >> tmp;
    char c[1024];
    bool st = 0;
    for (int i = 0; i < 1024; i++) {
        c[i] = tmp[i];
    }
    for (int x = 0; x < 1024; x += 4) {
        if (x < 960 || x>=984) {
            if (x >= 896 && x <= 952 - 8) {
                //   cout << " four ";
                cout << c[x + 6];
                cout << c[x + 7];
                cout << " ";
                cout << c[x + 4];
                cout << c[x + 5];
                cout << " ";
                st = 1;
            }
            cout << c[x + 2];
            cout << c[x + 3];
            cout << " ";
            cout << c[x];
            cout << c[x + 1];
            cout << " ";
            if (st) { st = 0; x += 4; } //cout << " end of four "; }
        }
        else {
            cout << c[x + 2];
            cout << c[x + 3];
            cout << " ";
            cout << c[x + 4];
            cout << c[x + 5];
            cout << " ";
        cout << c[x + 6];
        cout << c[x + 7];
        cout << " ";
        cout << c[x];
        cout << c[x + 1];
        cout << " ";
        x += 4;
        }
    }
    return 0;
}