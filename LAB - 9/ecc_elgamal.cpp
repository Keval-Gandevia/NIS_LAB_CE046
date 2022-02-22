#include <bits/stdc++.h>
using namespace std;

// function defintion
vector<int> extended_euclidean(int a, int n);
int multiplicative_inverse(int a, int n);
int square_multiply(int a, int b, int n);
vector<pair<int, int>> elliptic_curve_points(int a, int b, int p);
int convert_to_positive_mod(int a, int n);
void ecc_elgamal(int a, int b, int p);
pair<int, int> find_R(pair<int, int> P, pair<int, int> Q, int a, int p);
vector<pair<int, int>> encryption(pair<int, int> e1, pair<int, int> e2, pair<int, int> message, int a, int p, vector<pair<int, int>> points);
void decryption(vector<pair<int, int>> cipher_text, int a, int p, int d);

int main()
{

    int a, b, p;
    cout << "Enter the value of a, b, and p: ";
    cin >> a >> b >> p;

    // check for non-singularity condition
    if ((4 * a * a * a) + (27 * b * b) == 0)
    {
        cout << "\nCurve must be non-singular!!!" << endl << endl;
        exit(1);
    }

    ecc_elgamal(a, b, p);

    return 0;
}

// ECC - Elgamal Algorithm
void ecc_elgamal(int a, int b, int p)
{
    // generate points
    vector<pair<int, int>> points = elliptic_curve_points(a, b, p);

    cout << "\nPoints on the E" << p << "(" << a << ", " << b << ")"
         << "............." << endl;

    for (auto i : points)
    {
        cout << "(" << i.first << ", " << i.second << ")" << endl;
    }
    cout << endl;

    // key generation starts
    cout << "Key generation" << endl;
    cout << "-------------------------------------------" << endl;
    // select e1 from Ep(a,b)
    pair<int, int> e1 = points[2];
    cout << "Value of e1: (" << e1.first << ", " << e1.second << ")" << endl;

    // select d
    int d = 4;
    cout << "Value of d: " << d << endl;

    // select e2 = d X e1
    pair<int, int> temp = e1;
    for (int i = 1; i < d; i++)
    {
        temp = find_R(temp, e1, a, p);
    }

    pair<int, int> e2 = temp;
    cout << "Value of e2: (" << e2.first << ", " << e2.second << ")" << endl;
    cout << "-------------------------------------------" << endl
         << endl;
    // key generation ends

    // encryption
    // take a message from the user
    pair<int, int> message;
    cout << "Enter the point you want to send: ";
    cin >> message.first >> message.second;

    cout << "\nEncryption" << endl;
    cout << "-------------------------------------------" << endl;

    vector<pair<int, int>> cipher_text = encryption(e1, e2, message, a, p, points);
    cout << "-------------------------------------------" << endl;

    // decryption
    cout << "\nDecrption" << endl;
    cout << "-------------------------------------------" << endl;
    decryption(cipher_text, a, p, d);
    cout << "-------------------------------------------" << endl
         << endl;
}

// decryption
void decryption(vector<pair<int, int>> cipher_text, int a, int p, int d)
{
    pair<int, int> c1 = cipher_text[0];
    pair<int, int> c2 = cipher_text[1];

    // find the d X c1
    pair<int, int> temp = c1;

    for (int i = 1; i < d; i++)
    {
        temp = find_R(temp, c1, a, p);
    }

    temp.second = temp.second * (-1);

    // c2 - d X c1
    pair<int, int> decrypted_message = find_R(c2, temp, a, p);

    cout << "Decrypted text: (" << decrypted_message.first << ", " << decrypted_message.second << ")" << endl;
}

// encryption
vector<pair<int, int>> encryption(pair<int, int> e1, pair<int, int> e2, pair<int, int> message, int a, int p, vector<pair<int, int>> points)
{
    // check whether message is belongs to Ep(a, b)
    bool flag = false;
    for (int i = 0; i < points.size(); i++)
    {
        if ((message.first == points[i].first) && (message.second == points[i].second))
        {
            flag = true;
            break;
        }
    }

    if (!flag)
    {
        cout << "\nMessage must belongs to the curve points....\n\n";
        exit(1);
    }

    vector<pair<int, int>> cipher_text;

    // select r
    int r = 1;
    cout << "Value of the r: " << r << endl;

    // generate cipher text c1
    pair<int, int> temp = e1;
    for (int i = 1; i < r; i++)
    {
        temp = find_R(temp, e1, a, p);
    }

    pair<int, int> c1 = temp;

    cout << "Cipher text - 1: (" << c1.first << ", " << c1.second << ")" << endl;

    // find the cipher text 2
    temp = e2;

    for (int i = 1; i < r; i++)
    {
        temp = find_R(temp, e2, a, p);
    }

    pair<int, int> c2 = find_R(message, temp, a, p);

    cout << "Cipher text - 2: (" << c2.first << ", " << c2.second << ")" << endl;

    cipher_text.push_back(c1);
    cipher_text.push_back(c2);

    return cipher_text;
}

pair<int, int> find_R(pair<int, int> P, pair<int, int> Q, int a, int p)
{
    int x1 = P.first;
    int y1 = P.second;
    int x2 = Q.first;
    int y2 = Q.second;

    // case - 1: P != Q
    if ((x1 != x2) || (y1 != y2))
    {
        int y2_y1 = y2 - y1;
        int x2_x1 = x2 - x1;

        if (x2_x1 < 0)
        {
            x2_x1 += p;
        }

        // find multiplicative inverse
        int x2_x1_inverse = multiplicative_inverse(x2_x1, p);

        int slope = (y2_y1 * x2_x1_inverse) % p;

        if (slope < 0)
        {
            slope += p;
        }

        // cout << "Slope: " << slope << endl;
        int x3 = ((slope * slope) - x1 - x2) % p;
        int y3 = (slope * (x1 - x3) - y1) % p;

        if (x3 < 0)
        {
            x3 += p;
        }
        if (y3 < 0)
        {
            y3 += p;
        }
        return make_pair(x3, y3);
    }

    // Case - 2: P == Q
    if ((x1 == x2) && (y1 == y2))
    {
        int numerator = (3 * x1 * x1) + a;
        int denominator = (2 * y1);

        if (denominator < 0)
        {
            denominator += p;
        }

        int denominator_inverse = multiplicative_inverse(denominator, p);

        int slope = (numerator * denominator_inverse) % p;

        if (slope < 0)
        {
            slope += p;
        }

        // cout << "Slope: " << slope << endl;
        int x3 = ((slope * slope) - x1 - x2) % p;
        int y3 = (slope * (x1 - x3) - y1) % p;

        if (x3 < 0)
        {
            x3 += p;
        }
        if (y3 < 0)
        {
            y3 += p;
        }
        return make_pair(x3, y3);
    }

    return make_pair(-1, -1);
}

// used to find elliptic points
vector<pair<int, int>> elliptic_curve_points(int a, int b, int p)
{
    int x = 0;

    vector<pair<int, int>> points;

    while (x < p)
    {
        int x_3 = square_multiply(x, 3, p);
        int w = (x_3 + (a * x) + b) % p;

        if (w == 0)
        {
            points.push_back(make_pair(x, 0));
        }

        int QR_value = square_multiply(w, (p - 1) / 2, p);

        //  qr == 1
        if (QR_value == 1)
        {
            int sqrt_y = sqrt(w);

            // check for perfect square
            while (sqrt_y * sqrt_y != w)
            {
                if ((w + p) <= (p * p))
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
    if (res < 0)
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

// extended euclidian algo
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