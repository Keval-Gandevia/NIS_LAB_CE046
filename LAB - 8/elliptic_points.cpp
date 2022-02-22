#include <bits/stdc++.h>
using namespace std;

int square_multiply(int a, int b, int n);
vector<pair<int,int>> ellptic_curve_points(int a, int b, int p);
int convert_to_positive_mod(int a, int n);

int main()
{
    int a, b, p;
    cout << "Enter the values of a, b, and p: ";
    cin >> a >> b >> p;

    // check for non-singularity condition
    if((4 * a * a * a) + (27 * b * b) == 0)
    {
        cout << "Curve must be non-singular!!!";
    }

    vector<pair<int,int>> points = ellptic_curve_points(a, b, p);

    cout << "\nPoints on the E" << p << "(" << a << ", " << b << ")" << "............." << endl;

    for(auto i : points)
    {
        cout << "(" << i.first << ", " << i.second << ")" << endl; 
    }
    cout << endl;
    return 0;
}

// used to find elliptic points
vector<pair<int,int>> ellptic_curve_points(int a, int b, int p)
{
    int x = 0;

    vector<pair<int,int>> points;

    while(x < p)
    {
        int x_3 = square_multiply(x, 3, p);
        int w = (x_3 + (a * x) + b) % p;

        if(w == 0)
        {
            points.push_back(make_pair(x, 0));
        }

        int QR_value = square_multiply(w, (p - 1) / 2, p);

        //  qr == 1
        if(QR_value == 1)
        {
            int sqrt_y = sqrt(w);

            // check for perfect square
            while(sqrt_y * sqrt_y != w)
            {
                if((w + p) <= (p * p))
                {
                    w += p;
                    sqrt_y = sqrt(w);
                }
            }

            // for +ve
            int y_root1 = convert_to_positive_mod(sqrt_y, p);

            // for -ve;
            int y_root2 = convert_to_positive_mod(-sqrt_y, p);

            points.push_back(make_pair(x, y_root1));
            points.push_back(make_pair(x, y_root2));
        }

        // cout << QR_value << endl;
        x++;
    }

    return points;
}

// function that convert -ve mod to +ve
int convert_to_positive_mod(int a, int n)
{
    int res = a % n;
    if(res < 0)
    {
        res += n;
    }

    return res;
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