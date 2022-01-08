#include <bits/stdc++.h>
using namespace std;

int square_multiply(int a, int b, int n);

int main()
{

    int a, b, n;
    cout << "Enter the value of a, b, and n: ";
    cin >> a >> b >> n;

    int z = square_multiply(a, b, n);

    cout << endl
         << a << " ^ " << b << " mod " << n << ": " << z << endl
         << endl;
    ;

    return 0;
}

// function for finding a^b mod n
int square_multiply(int a, int b, int n)
{
    vector<int> binary;
    int temp = b;
    for (int i = 0; temp > 0; i++)
    {
        binary.push_back(temp % 2);
        temp /= 2;
    }

    reverse(binary.begin(), binary.end());

    long long z = 1;

    for (int i = 0; i < binary.size(); i++)
    {
        z = (z * z) % n;

        if (binary[i] == 1)
        {
            z = (z * a) % n;
        }
    }

    // for(int i = 0; i < binary.size(); i++) {
    //     cout << binary[i] << " ";
    // }

    // cout << endl;

    // cout << z << endl;

    return z;
}