#include <bits/stdc++.h>
using namespace std;

vector<int> text_mapping(string s, bool isCapital);
void print_values(vector<int> arr);
string encryption(string plain_text, vector<int> key_stream);
string decryption(string cipher_text, vector<int> key_stream);

int main()
{

    string plain_text;
    cout << "Enter the plain text: ";
    cin >> plain_text;
    int plain_text_length = plain_text.length();

    int cipher_key;
    cout << "Enter the cipher key: ";
    cin >> cipher_key;

    // find the key stream
    vector<int> key_stream(plain_text_length);
    vector<int> plain_text_mapping = text_mapping(plain_text, false);
    key_stream[0] = cipher_key;

    for (int i = 1; i < plain_text_length; i++)
    {
        key_stream[i] = plain_text_mapping[i - 1];
    }
    
    cout << "\nEncryption Table is below: ";
    cout << "\n---------------------------------------------------------";
    cout << endl;

    cout << setw(35) << "Plain Text| ";
    for (int i = 0; i < plain_text.length(); i++)
    {
        cout << plain_text[i] << " ";
    }
    cout << endl;

    string cipher_text = encryption(plain_text, key_stream);
    cout << "\n---------------------------------------------------------";

    cout << "\n\nDescryption Table is below: ";
    cout << "\n---------------------------------------------------------";
    cout << endl;

    cout << setw(35) << "Cipher Text| ";
    for (int i = 0; i < cipher_text.length(); i++)
    {
        cout << cipher_text[i] << " ";
    }
    cout << endl;
    decryption(cipher_text, key_stream);

    cout << "---------------------------------------------------------";

    return 0;
}

// encryption algo
string encryption(string plain_text, vector<int> key_stream)
{
    int length = plain_text.length();
    vector<int> plain_text_mapping = text_mapping(plain_text, false);

    cout << setw(35) << "Plain Text Mapping| ";
    print_values(plain_text_mapping);

    cout << setw(35) << "Key stream| ";
    print_values(key_stream);

    // plin text + key_stream
    for (int i = 0; i < length; i++)
    {
        plain_text_mapping[i] += key_stream[i];
    }

    cout << setw(35) << "(Plain Text + Key_Stream)| ";
    print_values(plain_text_mapping);

    // (plain text + key_stream) % 26
    for (int i = 0; i < length; i++)
    {
        plain_text_mapping[i] = plain_text_mapping[i] % 26;
    }

    cout << setw(35) << "(Plain Text * Key_Stream) % 26| ";
    print_values(plain_text_mapping);

    string cipher_text(length, ' ');
    cout << setw(35) << "Cipher Text| ";

    for (int i = 0; i < length; i++)
    {
        cipher_text[i] = char(plain_text_mapping[i] + 'A');
        cout << cipher_text[i] << " ";
    }

    return cipher_text;
}

// Decryption algorithm
string decryption(string cipher_text, vector<int> key_stream) {

    int length = cipher_text.length();
    vector<int> cipher_text_mapping = text_mapping(cipher_text, true);

    cout << setw(35) << "Cipher Text Mapping| ";
    print_values(cipher_text_mapping);

    cout << setw(35) << "Key Stream| ";
    print_values(key_stream);

    // cipher_text - key_stream
    for (int i = 0; i < length; i++)
    {
        cipher_text_mapping[i] -= key_stream[i];
    }

    cout << setw(35) << "(Cipher Text - Key_Stream)| ";
    print_values(cipher_text_mapping);

    // (cipher_text - key_stream) % 26
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

    cout << setw(35) << "(Cipher Text - K_Inverse) % 26| ";
    print_values(cipher_text_mapping);
    cout << setw(35) << "Plain Text| ";

    for (int i = 0; i < length; i++)
    {
        plain_text[i] = char(cipher_text_mapping[i] + 'a');
        cout << plain_text[i] << " ";
    }
    cout << endl;
    return plain_text;

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
    cout << endl;
}