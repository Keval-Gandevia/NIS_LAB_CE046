#include <bits/stdc++.h>
using namespace std;
#define MAX 100


vector<int> extended_euclidean(int a, int n);
int multiplicative_inverse(int a, int n);
vector<int> convert_to_binary(int b);
vector<int> generate_decrypt_text(vector<int> private_key, int s);
void decryption(vector<int> private_key, int w, int m, int s);
int encryption(vector<int> public_key, int plain_text);
void knapsack_cryptosystem(vector<int> a, int m, int plain_text);



int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    cout << "Enter the elements in super-increasing order: ";

    vector<int> a(n);
    bool flag = false;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
        if (i != 0 && a[i] < a[i - 1])
        {
            flag = true;
        }
    }

    if (flag)
    {
        cout << "\nEntered elements are not in super-increasing order....\n"
             << endl;
             exit(1);
    }

    int plain_text;
    cout << "Enter the number that you want to send: ";
    cin >> plain_text;

    cout << endl;
    knapsack_cryptosystem(a, sum, plain_text);

    return 0;
}

void knapsack_cryptosystem(vector<int> a, int m, int plain_text)
{
    // key generation starts
    int n = a.size();

    cout << "Value of m: " << m << endl;

    int w;
    for (int i = 3; i < MAX; i++)
    {
        vector<int> res = extended_euclidean(i, m);

        if (res[0] == 1)
        {
            w = i;
            break;
        }
    }

    cout << "Value of w: " << w << endl;

    cout << "Public key: ";

    vector<int> public_key(n);
    for (int i = 0; i < n; i++)
    {
        public_key[i] = (a[i] * w) % m;
        cout << public_key[i] << " ";
    }

    cout << endl;

    // key generation ends

    // encryption
    int s = encryption(public_key, plain_text);

    // decryption
    decryption(a, w, m, s);
}

// Encryption Algorithm
int encryption(vector<int> public_key, int plain_text)
{
    int n = public_key.size();
    vector<int> binary_plain_text = convert_to_binary(plain_text);

    // binary number bits should be same as the size of the public key

    if (n != binary_plain_text.size())
    {
        cout << "Public key size is not same as number of bits in the plain text...." << endl
             << endl;
             exit(1);
    }

    cout << "Binary equivalent of plain text: ";

    for (int i = 0; i < binary_plain_text.size(); i++)
    {
        cout << binary_plain_text[i] << " ";
    }

    cout << endl;

    int s = 0;

    for (int i = 0; i < n; i++)
    {
        s = s + (public_key[i] * binary_plain_text[i]);
    }

    cout << "Cipher Text: " << s << endl;

    return s;
}

// decryption algorithm
void decryption(vector<int> private_key, int w, int m, int s)
{
    int w_inverse = multiplicative_inverse(w, m);

    cout << "W inverse: " << w_inverse << endl;

    int required_sum = (w_inverse * s) % m;

    cout << "(W_Inverse * s) mod m: " << required_sum << endl;

    vector<int> binary_decrypted_text = generate_decrypt_text(private_key, required_sum);

    cout << "Binary Decrypted Text: ";

    for(int i = 0; i < binary_decrypted_text.size(); i++) {
        cout << binary_decrypted_text[i] << " ";
    }

    cout << endl;

    int decrypt_text = 0;

    for(int i = binary_decrypted_text.size() - 1; i >= 0 ; i--) {
        decrypt_text = decrypt_text + (pow(2,i) * binary_decrypted_text[binary_decrypted_text.size() - 1 - i]);
    }

    cout << "Decrypted Text: " << decrypt_text << endl << endl;;
}

vector<int> generate_decrypt_text(vector<int> private_key, int s)
{
    int n = private_key.size();
    vector<int> binary_decrypted_text(n);

    for(int i = n - 1; i >= 0; i--) {
        if(s >= private_key[i]) {
            binary_decrypted_text[i] = 1;
            s = s - private_key[i];
        }
        else {
            binary_decrypted_text[i] = 0;
        }
    }

    if(s != 0) {
        cout << "No solution exists!!!!"; 
    }

    return binary_decrypted_text;
}

// function used to convert number to corresponding binary
vector<int> convert_to_binary(int b)
{
    vector<int> binary;
    int temp = b;
    for (int i = 0; temp > 0; i++)
    {
        binary.push_back(temp % 2);
        temp /= 2;
    }

    reverse(binary.begin(), binary.end());

    return binary;
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