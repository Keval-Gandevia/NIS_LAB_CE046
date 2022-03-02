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

// function definitions
string DES_round_function(string plain_text, string round_key);
vector<int> HexToBinary(string hexdec);
vector<int> S_boxes(vector<int> arr);
vector<int> decToBinary(int n);
string BinaryToHex(string binary);

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

    string round_key;
    cout << "Enter the 48-bit round key: ";
    cin >> round_key;

    // check valid key
    if (round_key.length() != 12)
    {
        cout << "\nPlease enter 48-bit round key!!!" << endl
             << endl;
        exit(1);
    }

    DES_round_function(plain_text, round_key);

    return 0;
}

// round function
// return -> new text of 64 - bit
string DES_round_function(string plain_text, string round_key)
{
    // divide the 64 bit plain text into left and right of 32 bits
    string left = plain_text.substr(0, 8);
    string right = plain_text.substr(8, 15);

    // convert from hex to binary
    vector<int> left_bianry = HexToBinary(left);
    vector<int> right_binary = HexToBinary(right);
    vector<int> round_key_binary = HexToBinary(round_key);

    cout << "\nRound key binary";
    cout << "\n-----------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < round_key_binary.size(); i++)
    {
        cout << round_key_binary[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------------------------------------" << endl
         << endl;

    // expansion p-box
    cout << "Expansion of P-Box";
    cout << "\n-----------------------------------------------------------------------------------------------" << endl;
    vector<int> expanded_value(48);
    for (int i = 0; i < 48; i++)
    {
        expanded_value[i] = right_binary[expansion_p_box[i] - 1];
        cout << expanded_value[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------------------------------------" << endl
         << endl;

    // perform xor operation
    cout << "XOR";
    cout << "\n-----------------------------------------------------------------------------------------------" << endl;
    vector<int> xor_result(48);
    for (int i = 0; i < 48; i++)
    {
        xor_result[i] = expanded_value[i] ^ round_key_binary[i];
        cout << xor_result[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------------------------------------" << endl
         << endl;

    // S- box (48-bit to 32-bit)
    cout << "S-Box";
    cout << "\n-----------------------------------------------------------------------------------------------" << endl;
    vector<int> s_box_result = S_boxes(xor_result);
    for (int i = 0; i < s_box_result.size(); i++)
    {
        cout << s_box_result[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------------------------------------" << endl
         << endl;

    // straight permutation
    cout << "Straight Permutation";
    cout << "\n-----------------------------------------------------------------------------------------------" << endl;
    vector<int> straight_p(32);
    for (int i = 0; i < 32; i++)
    {
        straight_p[i] = s_box_result[straight_permutation[i] - 1];
        cout << straight_p[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------------------------------------" << endl
         << endl;

    // L[i] = R[i - 1] and R[i] = L[i - 1] ^ res

    vector<int> int_new_right(32);
    for (int i = 0; i < 32; i++)
    {
        int_new_right[i] = left_bianry[i] ^ straight_p[i];
    }


    // convert left and right to hexadecimal
    string final_left = "", final_right = "";

    for (int i = 0; i < 32; i++)
    {
        stringstream ss1, ss2;
        ss1 << right_binary[i];
        ss2 << int_new_right[i];

        string s1, s2;
        ss1 >> s1;
        ss2 >> s2;
        final_left += s1;
        final_right += s2;
    }

    string str_new_left = BinaryToHex(final_left);
    string str_new_right = BinaryToHex(final_right);
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "Result: " << str_new_left << str_new_right;
    cout << "\n-----------------------------------------------------------------------------------------------" << endl << endl;

    return str_new_left + str_new_right;
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