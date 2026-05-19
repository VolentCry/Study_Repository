#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    char chars[5];
    
    for (int i = 0; i < 5; ++i) {
        cin >> chars[i];
    }
    
    reverse(begin(chars), end(chars));
    
    for (char c : chars) {
        cout << c << " ";
    }
    
    return 0;
}
