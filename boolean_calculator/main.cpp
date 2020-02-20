#include <cstdlib>
#include <iostream>
#include <string>
#include "tnode.h"
#include "calculator.h"

using namespace std;

int main() {
    calculator a = calculator();
    string userstring;
    cout << "ask at your own peril: ";  //do while loop but a stupider version
    getline(cin, userstring);
    while(userstring.compare("enough") != 0) {
        string ans;
        for(int i = 0; i < userstring.length(); ++i) {
            userstring[i] = toupper(userstring[i]);
        }
        if(a.solve(userstring)) {
            ans = "true";
        } else {
            ans = "false";
        }
        cout << "apparently the answer is " << ans << " but don't quote me on that" << endl;
        cout << "you can give another equation but i can't guarantee it's gonna work again: ";
        getline(cin, userstring);
    }
}