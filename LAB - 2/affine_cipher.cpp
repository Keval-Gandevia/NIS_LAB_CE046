#include <bits/stdc++.h>
using namespace std;

vector<int> find_Z_star(int n);
vector<int> extended_euclidean(int a, int n);
string encryption(string original_msg, int k1, int k2);
void print_values(vector<int> arr);
vector<int> text_mapping(string s, bool isCapital);
string decryption(string cipher_text, int k1, int k2);
int multiplicative_inverse(int a, int n);

int main()
{

    string original_msg;
    cout << "Enter the original message: ";
    cin >> original_msg;

    // find Z26*
    vector<int> z_star = find_Z_star(26);

    // choose random element from z_star
    srand(time(NULL));
    int k1 = z_star[rand() % z_star.size()];

    // choose random key for k2 for addtive cipher
    int k2 = (rand() + 1) % 26;

    // cout << k1 << " " << k2 << endl;

    cout << "\nEncryption Table is below: ";
    cout << "\n---------------------------------------------------------";
    cout << endl;

    cout << setw(35) << "Plain Text| ";
    for (int i = 0; i < original_msg.length(); i++)
    {
        cout << original_msg[i] << " ";
    }
    cout << endl;

    string cipher_text = encryption(original_msg, k1, k2);
    cout << "\n---------------------------------------------------------";

    cout << "\n\nDescryption Table is below: ";
    cout << "\n---------------------------------------------------------";
    cout << endl;

    cout << setw(45) << "Cipher Text| ";
    for (int i = 0; i < cipher_text.length(); i++)
    {
        cout << cipher_text[i] << " ";
    }
    cout << endl;
    decryption(cipher_text, k1, k2);

    cout << "---------------------------------------------------------";

    return 0;
}

// encryption algo
string encryption(string original_msg, int k1, int k2)
{
    int length = original_msg.length();
    vector<int> plain_text_mapping = text_mapping(original_msg, false);

    cout << setw(35) << "Plain Text Mapping| ";
    print_values(plain_text_mapping);

    cout << endl
         << setw(35)
         << "K1| ";
    for (int i = 0; i < length; i++)
    {
        cout << k1 << " ";
    }

    cout << endl
         << setw(35)
         << "K2| ";
    for (int i = 0; i < length; i++)
    {
        cout << k2 << " ";
    }

    cout << endl;

    // plin text + key
    for (int i = 0; i < length; i++)
    {
        plain_text_mapping[i] = (plain_text_mapping[i] * k1) + k2;
    }

    cout << setw(35) << "(Plain Text * K1) + K2| ";
    print_values(plain_text_mapping);
    cout << endl;

    // (plain text + key) % 26
    for (int i = 0; i < length; i++)
    {
        plain_text_mapping[i] = plain_text_mapping[i] % 26;
    }

    cout << setw(35) << "((Plain Text * K1) + K2) % 26| ";
    print_values(plain_text_mapping);
    cout << endl;

    string cipher_text(length, ' ');

    for (int i = 0; i < length; i++)
    {
        cipher_text[i] = char(plain_text_mapping[i] + 'A');
    }

    cout << setw(35) << "Cipher Text| ";

    for (int i = 0; i < length; i++)
    {
        cout << cipher_text[i] << " ";
    }

    return cipher_text;
}

// Decryption algorithm
string decryption(string cipher_text, int k1, int k2)
{
    int length = cipher_text.length();
    vector<int> cipher_text_mapping = text_mapping(cipher_text, true);

    // find the multiplicative inverse
    int k1_inverse = multiplicative_inverse(k1, 26);
    int k2_inverse = ((k2) * (-1)) + 26;

    cout << setw(45) << "Cipher Text Mapping| ";
    print_values(cipher_text_mapping);

    cout << endl
         << setw(45)
         << "Multiplicative Inverse| ";
    for (int i = 0; i < length; i++)
    {
        cout << k1_inverse << " ";
    }

    cout << endl
         << setw(45)
         << "Additive Inverse| ";
    for (int i = 0; i < length; i++)
    {
        cout << k2_inverse << " ";
    }

    // cipher_text - key
    for (int i = 0; i < length; i++)
    {
        cipher_text_mapping[i] = (cipher_text_mapping[i] + k2_inverse) * k1_inverse;
    }

    cout << endl;
    cout << setw(45) << "(Cipher Text - K2) * K1_Inverse| ";
    print_values(cipher_text_mapping);
    cout << endl;

    // (cipher_text - key) % 26
    for (int i = 0; i < length; i++)
    {
        if (cipher_text_mapping[i] < 0)
        {
            cipher_text_mapping[i] += 26;
            continue;
        }
        cipher_text_mapping[i] = cipher_text_mapping[i] % 26;
    }

    string plain_text(length, ' ');

    for (int i = 0; i < length; i++)
    {
        plain_text[i] = char(cipher_text_mapping[i] + 'a');
    }

    cout << setw(45) << "((Cipher Text - K2) * K1_Inverse) % 26| ";
    print_values(cipher_text_mapping);
    cout << endl;
    cout << setw(45) << "Plain Text| ";

    for (int i = 0; i < length; i++)
    {
        cout << plain_text[i] << " ";
    }
    cout << endl;

    return plain_text;
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

// function used to do mapping
// isCaptital = true -> maps to uppercase
// isCaptital = false -> maps to lowercase
vector<int> text_mapping(string s, bool isCapital)
{
    int length = s.length();
    vector<int> mapping(length);

    // check if isCaptital true then do mapping in uppercase
    if (isCapital)
    {
        for (int i = 0; i < length; i++)
        {
            mapping[i] = s[i] - 'A';
        }
    }
    // celse do mapping in uppercase
    else
    {
        for (int i = 0; i < length; i++)
        {
            mapping[i] = s[i] - 'a';
        }
    }

    return mapping;
}

// function that print values of the character
void print_values(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
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
