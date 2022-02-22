#include <bits/stdc++.h>
using namespace std;

bool miller_rabin(int n);
int square_multiply(int a, int b, int n);
vector<int> find_Z_star(int n);
void print_values(vector<int> arr);
int multiplicative_inverse(int a, int n);
vector<int> find_primitive_roots(vector<int> z_star, int n);
vector<int> extended_euclidean(int a, int n);
void elgamal_cryptosystem(int prime_no, int message);
vector<int> encryption(vector<int> z_star, int message, int prime_no, int e1, int e2);
int decryption(vector<int> c1_c2, int d, int prime_no);

int main()
{

    int prime_no;
    while (1)
    {
        cout << "Enter the large prime number: ";
        cin >> prime_no;

        if (!miller_rabin(prime_no))
        {
            cout << endl
                 << prime_no << " is not a prime number...." << endl
                 << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    int message;
    cout << "Enter the number you want to send: ";
    cin >> message;

    elgamal_cryptosystem(prime_no, message);

    return 0;
}

// elgamal cryptosystem algorithm
void elgamal_cryptosystem(int prime_no, int message)
{

    // ---- key generation starts

    // find z_star
    vector<int> z_star = find_Z_star(prime_no);

    // cout << "\nElements of z_star: ";
    // print_values(z_star);
    // cout << endl;
    // find primitive root
    vector<int> primitive_roots = find_primitive_roots(z_star, prime_no);

    cout << "\nPrimitive roots are: ";
    print_values(primitive_roots);
    cout << endl;
    // select one of the primitive root
    int e1 = primitive_roots[0];

    cout << "Value of e1: " << e1 << endl;

    // generate d from 1 <= d <= p - 2
    // srand(time(0));
    // int d = 1 + (rand() % ((prime_no - 2)));

    // I have d = 3, because we are p as a prime number so d will always fall into range of 1 <= d <= p - 2.

    // I have not taken big value for d because if we take value of d bigger then we are not able to store power values in even unsigned long long int.
    int d = 3;

    cout << "Value of d: " << d << endl;

    int e2 = square_multiply(e1, d, prime_no);

    cout << "Value of (e1 ^ d) mod p: " << e2 << endl;

    // ----key generation ends

    // encryption
    vector<int> c1_c2 = encryption(z_star, message, prime_no, e1, e2);

    // decryption
    int decrypted_text = decryption(c1_c2, d, prime_no);

    cout << "Decrypted Text: " << decrypted_text << endl
         << endl;
}

// decryption algorithm
int decryption(vector<int> c1_c2, int d, int prime_no)
{
    int c1 = c1_c2[0];
    int c2 = c1_c2[1];

    int c1_pow_d = square_multiply(c1, d, prime_no);

    int c1_inverse = multiplicative_inverse(c1_pow_d, prime_no);

    int decrypted_text = (c2 * c1_inverse) % prime_no;

    return decrypted_text;
}

// encryption algorithm
vector<int> encryption(vector<int> z_star, int message, int prime_no, int e1, int e2)
{
    // select r randomly
    // srand(time(0));
    // int r = z_star[rand() % z_star.size()];
    int r = z_star[1];
    cout << "Value of r: " << r << endl;

    vector<int> res(2);

    // store c1
    res[0] = square_multiply(e1, r, prime_no);

    // store c2;
    res[1] = (square_multiply(e2, r, prime_no) * message) % prime_no;

    cout << "Values of cipher text: ";

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }

    cout << endl;

    return res;
}

// function used to find the primitive roots
vector<int> find_primitive_roots(vector<int> z_star, int n)
{

    vector<int> primitive_roots;

    for (int i = 0; i < z_star.size(); i++)
    {
        int count = 0;
        for (int j = 1; j <= z_star.size(); j++)
        {
            int res = square_multiply(z_star[i], j, n);

            if (res == 1)
            {
                if (j != z_star.size())
                {
                    break;
                }
                else
                {
                    primitive_roots.push_back(z_star[i]);
                }
            }
        }
    }
    return primitive_roots;
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

vector<int> find_Z_star(int n)
{
    vector<int> res;

    for (int i = 0; i < n; i++)
    {
        vector<int> r1_t1 = extended_euclidean(i, n);
        if (r1_t1[0] == 1)
        {
            res.push_back(i);
        }
    }

    return res;
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

// function that print values of the character
void print_values(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}