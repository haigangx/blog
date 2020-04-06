#include <iostream>
#include <fstream>
#include <vector>
#include <string>
 
using namespace std;
 
void swap(vector<string>& a, int m, int n)
{
    string temp = a[m];
    a[m] = a[n];
    a[n] = temp;
}
 
int charAt(const string& str, int d)
{
    if ( d < str.size() )
        return str[d];
    else 
        return -1;
}
 
void quick_3_string(vector<string>& sVec, int lo, int hi, int d)
{
    if (hi<=lo)
        return;
    int lt = lo, gt = hi;
    int v = charAt(sVec[lo], d);
    int i = lo + 1;
    while (i<=gt)
    {
        int t =  charAt(sVec[i], d);
        if (t < v) swap(sVec, lt++, i++);
        else if ( t > v) swap(sVec, i, gt--);
        else i++;
    }
 
    quick_3_string(sVec, lo, lt-1, d);
    if (v >=0 )
        quick_3_string(sVec, lt, gt, d+1);
    quick_3_string(sVec, gt+1, hi, d);
}