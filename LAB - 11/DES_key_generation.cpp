#include <bits/stdc++.h>
using namespace std;

vector<int> HexToBinary(string hexdec);
vector<string> DES_key_generation(string cipher_key);
string convertVectoStr(vector<int> arr);
void shiftLeft(vector<int> &arr, int round);
string BinaryToHex(string binary);

vector<int> parity_drop_table{
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

vector<int> compression_p_box
{
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

int main()
{
    string cipher_key;
    cout << "Enter the 16-bit cipher key: ";
    cin >> cipher_key;

    vector<string> keys = DES_key_generation(cipher_key);
    for(int i = 0; i < keys.size(); i++)
    {
        cout << keys[i] << endl;
    }

    return 0;
}

vector<string> DES_key_generation(string cipher_key)
{

    vector<string> keys;
    vector<int> key_binary = HexToBinary(cipher_key);
    vector<int> parity_drop(56);

    for (int i = 0; i < 56; i++)
    {
        parity_drop[i] = key_binary[parity_drop_table[i] - 1];
        cout << parity_drop[i] << " ";
    }
    cout << endl;
    vector<int> left_key, right_key;
    left_key.assign(parity_drop.begin(), parity_drop.begin() + 28);
    right_key.assign(parity_drop.begin() + 28, parity_drop.begin() + 56);

    for (int i = 0; i < 16; i++)
    {
        shiftLeft(left_key, i + 1);
        shiftLeft(right_key, i + 1);

        cout << "Left and right key...." << endl;
        for(int b = 0; b < left_key.size(); b++)
        {
            cout << left_key[b] << " ";
        }
        for(int b = 0; b < right_key.size(); b++)
        {
            cout << right_key[b] << " ";
        }
        cout << endl;
        vector<int> combined_key(left_key);
        combined_key.insert(combined_key.end(), right_key.begin(), right_key.end());
        cout << "Combined key...." << endl;
        cout << combined_key.size() << endl;
        for(int b = 0; b < combined_key.size(); b++)
        {
            cout << combined_key[b] << " ";
        }

        cout << endl;

        vector<int> compressed_key(48);
        cout << "Compressed key...." << endl;
        for(int j = 0; j < compressed_key.size(); j++)
        {
            compressed_key[j] = combined_key[compression_p_box[j] - 1];
            cout << compressed_key[j] << " ";
        }
        cout << endl;
        string key = BinaryToHex(convertVectoStr(compressed_key));
        cout << "Key: " << key << endl;
        keys.push_back(BinaryToHex(convertVectoStr(compressed_key)));
    }

    return keys;
}

string convertVectoStr(vector<int> arr)
{
    string str = "";
    for (int i = 0; i < arr.size(); i++)
    {
        stringstream ss;
        ss << arr[i];

        string s;
        ss >> s;

        str += s;
    }

    return str;
}

void shiftLeft(vector<int> &arr, int round)
{
    // cout << "Round: " << round << endl;
    int no_of_shifts = 2;
    if (round == 1 || round == 2 || round == 9 || round == 16)
    {
        no_of_shifts = 1;
    }
    while (no_of_shifts--)
    {
        int first = arr[0];
        for (int i = 0; i < arr.size() - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[arr.size() - 1] = first;
    }
}


string BinaryToHex(string binary)
{
    map<string, char> mapping;
    mapping["0000"] = '0';
    mapping["0001"] = '1';
    mapping["0010"] = '2';
    mapping["0011"] = '3';
    mapping["0100"] = '4';
    mapping["0101"] = '5';
    mapping["0110"] = '6';
    mapping["0111"] = '7';
    mapping["1000"] = '8';
    mapping["1001"] = '9';
    mapping["1010"] = 'A';
    mapping["1011"] = 'B';
    mapping["1100"] = 'C';
    mapping["1101"] = 'D';
    mapping["1110"] = 'E';
    mapping["1111"] = 'F';
    string res = "", temp = "";

    for (int i = 0; i < binary.length(); i += 1)
    {
        temp += binary[i];
        if ((i + 1) % 4 == 0)
        {
            res += mapping[temp];
            temp = "";
        }
    }

    return res;
}

vector<int> HexToBinary(string hexdec)
{
    long int i = 0;

    vector<int> binary;

    while (hexdec[i])
    {

        switch (hexdec[i])
        {
        case '0':
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            break;
        case '1':
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);

            break;
        case '2':
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
            break;
        case '3':
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
            break;
        case '4':
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
            break;
        case '5':
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
            break;
        case '6':
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
            break;
        case '7':
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
            break;
        case '8':
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            break;
        case '9':
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(1);
            break;
        case 'A':
        case 'a':
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(0);
            break;
        case 'B':
        case 'b':
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
            binary.push_back(1);
            break;
        case 'C':
        case 'c':
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(0);
            break;
        case 'D':
        case 'd':
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
            binary.push_back(1);
            break;
        case 'E':
        case 'e':
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(0);
            break;
        case 'F':
        case 'f':
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
            binary.push_back(1);
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                 << hexdec[i];
        }
        i++;
    }
    return binary;
}