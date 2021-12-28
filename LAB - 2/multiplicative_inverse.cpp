#include <bits/stdc++.h>
using namespace std;


vector<int> extended_euclidean(int a, int n);
int multiplicative_inverse(int a, int n);


int main()
{

    while (1)
    {

        int a, n;
        cout << "Enter the value of a & n: ";
        cin >> a >> n;

        int a_inverse = multiplicative_inverse(a, n);

        if(a_inverse != -1) {
            cout << "\nMultiplicative inverse of a = " << a << " is: " << a_inverse << endl << endl;
            break;
        }
        cout << "Not Possible again enter the value of a and n!!!" << endl;
    }

    return 0;
}

vector<int> extended_euclidean(int a, int n)
{

    int r1 = n, r2 = a, t1 = 0, t2 = 1, q, r, t;

    while (r2 > 0)
    {
        q = r1 / r2;
        r = r1 - (q * r2);
        r1 = r2;
        r2 = r;
        t = t1 - (q * t2);
        t1 = t2;
        t2 = t;
    }

    vector<int> res(2);
    res[0] = r1;
    res[1] = t1;
    // return gcd
    return res;
}

int multiplicative_inverse(int a, int n)
{
    vector<int> res = extended_euclidean(a, n);
    int a_inverse;

    if (res[0] == 1)
    {
        if (res[1] < 0)
        {
            a_inverse = res[1] + 26;
        }
        else
        {
            a_inverse = res[1];
        }

        return a_inverse;
    }

    return -1;
}