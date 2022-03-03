#include <bits/stdc++.h>
using namespace std;

// global metrices used in algorithm
vector<int> expansion_p_box{
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

vector<vector<int>> s_box_1{
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}};

vector<vector<int>> s_box_2{
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};

vector<vector<int>> s_box_3{
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}};

vector<vector<int>> s_box_4{
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}};

vector<vector<int>> s_box_5{
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}};

vector<vector<int>> s_box_6{
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}};

vector<vector<int>> s_box_7{
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
    {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
    {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}};

vector<vector<int>> s_box_8{
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

vector<int> straight_permutation{
    16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

vector<int> parity_drop_table{
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

vector<int> compression_p_box
{
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

// vector<string> keys{
//     "194CD072DE8C", "4568581ABCCE", "06EDA4ACF5B5", "DA2D032B6EE3", "69A629FEC913", "C1948E87475E", "708AD2DDB3C0", "34F822F0C66D", "84BB4473DCCC", "02765708B5BF", "6D5560AF7CA5", "C2C1E96A4BF3", "99C31397C91F", "251B8BC717D0", "3330C5D9A36D", "181C5D75C66D"};

// function definitions
vector<int> HexToBinary(string hexdec);
vector<int> S_boxes(vector<int> arr);
string BinaryToHex(string binary);
vector<int> DES_round_function(string right, string round_key);
void DES_cipher(string plain_text, vector<string> keys);
vector<string> swapper(vector<int> left, vector<int> right, vector<int> straight_p, int round);
vector<string> DES_key_generation(string cipher_key);
string convertVectoStr(vector<int> arr);
void shiftLeft(vector<int> &arr, int round);

int main()
{
    string plain_text;
    cout << "Enter the 64-bit plain text: ";
    cin >> plain_text;

    // check valid plain text
    if (plain_text.length() != 16)
    {
        cout << "\nPlease enter 64-bit plain text!!!" << endl
             << endl;
        exit(1);
    }

    string cipher_key;
    cout << "Enter the 64-bit cipher key: ";
    cin >> cipher_key;

    // check valid cipher key
    if (cipher_key.length() != 16)
    {
        cout << "\nPlease enter 64-bit cipher key!!!" << endl
             << endl;
        exit(1);
    }

    // generate keys
    vector<string> keys = DES_key_generation(cipher_key);

    DES_cipher(plain_text, keys);

    return 0;
}

// algorithm for DES cipher
void DES_cipher(string plain_text, vector<string> keys)
{
    // divide the 64 bit plain text into left and right of 32 bits
    string left = plain_text.substr(0, 8);
    string right = plain_text.substr(8, 15);

    // convert to binary
    vector<int> left_bianry = HexToBinary(left);
    vector<int> right_binary = HexToBinary(right);
    vector<string> res_swapper;

    cout << "\nEncryption....." << endl;

    cout << "-------------------------------------------------------------\n";
    cout << "Round" << setw(15) << "Left" << setw(15) << "Right" << setw(20) << "Round Key" << endl;
    cout << "-------------------------------------------------------------\n";
    //Encryption & 16 rounds 
    for (int i = 0; i < 16; i++)
    {
        vector<int> res_round = DES_round_function(right, keys[i]);

        res_swapper = swapper(left_bianry, right_binary, res_round, i + 1);

        left_bianry = HexToBinary(res_swapper[0]);
        right_binary = HexToBinary(res_swapper[1]);

        right = res_swapper[1];

        cout << i + 1 << setw(20) << res_swapper[0] << setw(15) << res_swapper[1] << setw(20) << keys[i] << endl;
    }

    cout << "-------------------------------------------------------------\n";
    string cipher_text = res_swapper[0] + res_swapper[1];
    cout << "Cipher Text: " << cipher_text << endl;
    cout << "-------------------------------------------------------------\n";


    // decryption

    string cipher_left = res_swapper[0];
    string cipher_right = res_swapper[1];

    vector<int> cipher_left_bianry = HexToBinary(cipher_left);
    vector<int> cipher_right_binary = HexToBinary(cipher_right);

    cout << "\nDecryption....." << endl;
    cout << "-------------------------------------------------------------\n";
    cout << "Round" << setw(15) << "Left" << setw(15) << "Right" << setw(20) << "Round Key" << endl;
    cout << "-------------------------------------------------------------\n";

    // 16 rounds
    for(int i = 0; i < 16; i++)
    {
        vector<int> res_round = DES_round_function(cipher_right, keys[16 - i - 1]);

        res_swapper = swapper(cipher_left_bianry, cipher_right_binary, res_round, i + 1);

        cipher_left_bianry = HexToBinary(res_swapper[0]);
        cipher_right_binary = HexToBinary(res_swapper[1]);

        cipher_right = res_swapper[1];

        cout << i + 1 << setw(20) << res_swapper[0] << setw(15) << res_swapper[1] << setw(20) << keys[16 - i - 1] << endl;
    }

    cout << "-------------------------------------------------------------\n";
    string decrypted_text = res_swapper[0] + res_swapper[1];
    cout << "Decrypted Text: " << decrypted_text << endl;
    cout << "-------------------------------------------------------------\n";
    cout << endl;
}

// round function
vector<int> DES_round_function(string right, string round_key)
{
    // convert from hex to binary
    vector<int> right_binary = HexToBinary(right);
    vector<int> round_key_binary = HexToBinary(round_key);

    // expansion p-box
    vector<int> expanded_value(48);
    for (int i = 0; i < 48; i++)
    {
        expanded_value[i] = right_binary[expansion_p_box[i] - 1];
    }

    // xor
    vector<int> xor_result(48);
    for (int i = 0; i < 48; i++)
    {
        xor_result[i] = expanded_value[i] ^ round_key_binary[i];
    }

    // S - boxes
    vector<int> s_box_result = S_boxes(xor_result);

    // straight permutation
    vector<int> straight_p(32);
    for (int i = 0; i < 32; i++)
    {
        straight_p[i] = s_box_result[straight_permutation[i] - 1];
    }

    return straight_p;
}

// swap the left and right at each round
vector<string> swapper(vector<int> left, vector<int> right, vector<int> straight_p, int round)
{

    // perform the xor or mixer
    vector<int> int_new_right(32);
    for (int i = 0; i < 32; i++)
    {
        int_new_right[i] = left[i] ^ straight_p[i];
    }

    // convert left and right to hexadecimal
    string final_left = "", final_right = "";

    for (int i = 0; i < 32; i++)
    {
        stringstream ss1, ss2;
        ss1 << right[i];
        ss2 << int_new_right[i];

        string s1, s2;
        ss1 >> s1;
        ss2 >> s2;

        if (round == 16)
        {
            final_left += s2;
            final_right += s1;
        }
        else
        {

            final_left += s1;
            final_right += s2;
        }
    }

    string str_new_left = BinaryToHex(final_left);
    string str_new_right = BinaryToHex(final_right);

    vector<string> str;

    str.push_back(str_new_left);
    str.push_back(str_new_right);

    return str;
}

// perform the key generation for each round
vector<string> DES_key_generation(string cipher_key)
{
    vector<string> keys;

    vector<int> key_binary = HexToBinary(cipher_key);

    // parity drop
    vector<int> parity_drop(56);
    for (int i = 0; i < 56; i++)
    {
        parity_drop[i] = key_binary[parity_drop_table[i] - 1];
    }

    vector<int> left_key, right_key;
    left_key.assign(parity_drop.begin(), parity_drop.begin() + 28);
    right_key.assign(parity_drop.begin() + 28, parity_drop.begin() + 56);

    for (int i = 0; i < 16; i++)
    {  

        // shift left
        shiftLeft(left_key, i + 1);
        shiftLeft(right_key, i + 1);

        vector<int> combined_key(left_key);
        combined_key.insert(combined_key.end(), right_key.begin(), right_key.end());
        
        // compression p-box
        vector<int> compressed_key(48);
        for(int j = 0; j < compressed_key.size(); j++)
        {
            compressed_key[j] = combined_key[compression_p_box[j] - 1];
        }

        keys.push_back(BinaryToHex(convertVectoStr(compressed_key)));
    }

    return keys;
}

// convert elements of vector to string
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

// perform the shift
void shiftLeft(vector<int> &arr, int round)
{
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

// covert 48-bit into 32-bit using s-boxes
vector<int> S_boxes(vector<int> arr)
{
    vector<int> res;

    for (int i = 0; i < 47; i += 6)
    {
        vector<int> binary;
        string str_row = to_string(arr[i]) + to_string(arr[i + 5]);

        string str_col = "";
        for (int j = i + 1; j <= i + 4; j++)
        {
            str_col += to_string(arr[j]);
        }

        int row = stoi(str_row, 0, 2);
        int col = stoi(str_col, 0, 2);

        if (i >= 0 && i <= 5)
        {
            // use s_box_1
            int number = s_box_1[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 6 && i <= 11)
        {
            // use s_box_2
            int number = s_box_2[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 12 && i <= 17)
        {
            // use s_box_3
            int number = s_box_3[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 18 && i <= 23)
        {
            // use s_box_4
            int number = s_box_4[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 24 && i <= 29)
        {
            // use s_box_5
            int number = s_box_5[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 30 && i <= 35)
        {
            // use s_box_6
            int number = s_box_6[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 36 && i <= 41)
        {
            // use s_box_7
            int number = s_box_7[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }
        else if (i >= 42 && i <= 47)
        {
            // use s_box_8
            int number = s_box_8[row][col];
            stringstream ss;
            ss << hex << number;
            string str_hex(ss.str());
            // cout << str_hex << endl;
            binary = HexToBinary(str_hex);
        }

        for (int b = 0; b < binary.size(); b++)
        {
            // cout << binary[b]
            res.push_back(binary[b]);
        }
    }

    return res;
}

// function binary to hex
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

// function to convert hex to bianry
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