#include <iostream>
using namespace std;
int main () 
{
int x,y;
cout << "Enter number x:";
cin >> x;
cout << "Enter number y:";
cin >> y;
if (x>y) cout << "x is larger than y";
if (x<y) cout << "y is larger than x";
if (x==y) cout << "x is equal to y";
return 0;
}