#include <bits/stdc++.h>
using namespace std;

bool miller_rabin(int n);
int square_multiply(int a, int b, int n);
vector<int> extended_euclidean(int a, int n);
void rsa(int p, int q, int m);
int multiplicative_inverse(int a, int n);

int main()
{

    int p, q;

    while (1)
    {
        cout << "Enter the first large prime number: ";
        cin >> p;
        if (!miller_rabin(p))
        {
            cout << p << " is not a prime number...." << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    while (1)
    {
        cout << "Enter the second large prime number: ";
        cin >> q;
        if (!miller_rabin(q))
        {
            cout << q << " is not a prime number...." << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    int m;
    cout << "Enter the number that you want to send: ";
    cin >> m;

    rsa(p, q, m);

    return 0;
}

void rsa(int p, int q, int m)
{

    int n = p * q;

    int fi_n = (p - 1) * (q - 1);

    // find e
    int e;

    for (int i = 2; i < fi_n; i++)
    {
        vector<int> res = extended_euclidean(i, fi_n);

        if (res[0] == 1)
        {
            e = i;
            break;
        }
    }

    // cout << e  << endl;

    // find d

    int d = multiplicative_inverse(e, fi_n);

    // cout << d << endl;

    // do encryption

    int c = square_multiply(m, e, n);

    cout << "\nEncrypted Text: " << c << endl;

    // do decryption

    int decrypt_value = square_multiply(c, d, n);

    cout << "Decrypted Text: " << decrypt_value << endl
         << endl;
    ;
}

// function for primality test
bool miller_rabin(int n)
{
    int temp = n - 1, k = 0, m = 1;

    bool flag = false;

    for (int i = 3; i <= n; i += 2)
    {
        // cout << "i is: " << i << endl;
        if (temp % i == 0)
        {
            // cout << " yes" << endl;
            int power_k = temp / i;
            k = log2(power_k);
            m = i;
            flag = true;
            // cout << power_k << " " << k << " " << m << endl;
            break;
        }
    }

    if (!flag)
    {
        m = 1;
        k = log2(temp);
    }

    // cout << k << " " << m << endl;

    // choose random number lower = 2, upper = n - 2;

    int lower = 2, upper = n - 2;

    srand(time(0));
    int a = 1 + lower + (rand() % (upper - lower + 1));

    // cout << a << endl;

    int b = square_multiply(a, m, n);
    // cout << b << endl;
    // square_multiply(19, 5, 119);

    if (b % n == 1)
    {
        return true;
    }

    for (int i = 0; i <= k - 1; i++)
    {
        if (b % n == n - 1)
        {
            return true;
        }
        else
        {
            b = (b * b) % n;
        }
    }

    return false;
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
            a_inverse = res[1] + n;
        }
        else
        {
            a_inverse = res[1];
        }

        return a_inverse;
    }

    return -1;
}
