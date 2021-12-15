#include <stack>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    string str;
    cin >> str;
    stack<char> steck;
    int i;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            steck.push(str[i]);
            continue;
        }
        else if (steck.empty()) {
            steck.push(str[i]);
            break;
        }
        else if (str[i] == ')' && (steck.top() == '[' || steck.top() == '{')) {
            break;
        }
        else if (str[i] == '}' && (steck.top() == '(' || steck.top() == '[')) {
            break;
        }
        else if (str[i] == ']' && (steck.top() == '{' || steck.top() == '(')) {
            break;
        }
        steck.pop();
    }
    if (steck.empty()) {
        cout << "balanced" << endl;
    }
    else {
        cout << "not balanced" << endl;
        cout << i << endl;
    }
    return 0;
}
