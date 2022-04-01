#include <bits/stdc++.h>
using namespace std;

// global variable
const int DIM = 4;
int MSG_SIZE;

// function definitions
vector<int> convert_to_binary(int b);
int binaryToDecimal(vector<int> n);
vector<vector<int>> embed_2bit(vector<vector<int>> cover_image, vector<int> binary_message);
vector<vector<int>> embed_3bit(vector<vector<int>> cover_image, vector<int> binary_message);
vector<int> extract_2bit(vector<vector<int>> stego);
vector<int> extract_3bit(vector<vector<int>> stego);
float MSE(vector<vector<int>> cover_image, vector<vector<int>> stego);
float PSNR(float mse, int R);

int main()
{
    // initialize the number of bits to 1
    int no_of_bits = 1;
    cout << "\nEnter the number of bits you want to hide: ";
    cin >> no_of_bits;

    // check error condition
    if (no_of_bits > 3)
    {
        cout << "\nValue of the number of bits can be only 2 or 3!!!" << endl
             << endl;
        exit(1);
    }

    // set the length of the message
    MSG_SIZE = DIM * DIM * no_of_bits;

    vector<vector<int>> cover_image(DIM, vector<int>(DIM));

    cout << "\nEnter the cover image....." << endl;
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            cin >> cover_image[i][j];
        }
    }

    vector<int> binary_message(MSG_SIZE);

    cout << "\nEnter the binary message with each bit separated by space....." << endl;

    for (int i = 0; i < MSG_SIZE; i++)
    {
        cin >> binary_message[i];
    }

    vector<vector<int>> stego;
    vector<int> extracted_msg;
    if (no_of_bits == 2)
    {
        cout << "\nStego obejct....." << endl;
        stego = embed_2bit(cover_image, binary_message);

        cout << "\nExtracted message....." << endl;
        extracted_msg = extract_2bit(stego);
    }
    else if (no_of_bits == 3)
    {
        cout << "\nStego obejct....." << endl;
        stego = embed_3bit(cover_image, binary_message);

        cout << "\nExtracted message....." << endl;
        extracted_msg = extract_3bit(stego);
    }

    float mse = MSE(cover_image, stego);
    cout << "\nMSE: " << mse << endl
         << endl;

    float psnr_value = PSNR(mse, 255);
    cout << "PSNR: " << psnr_value << endl
         << endl;

    return 0;
}

// extract function for 2 bits
vector<int> extract_2bit(vector<vector<int>> stego)
{
    vector<int> msg;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            vector<int> binary = convert_to_binary(stego[i][j]);
            msg.push_back(binary[binary.size() - 1]);
            msg.push_back(binary[binary.size() - 2]);
        }
    }
    for (int i = 0; i < msg.size(); i++)
    {
        cout << msg[i] << " ";
    }
    cout << endl;

    return msg;
}

// extract function for 3 bits
vector<int> extract_3bit(vector<vector<int>> stego)
{
    vector<int> msg;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            vector<int> binary = convert_to_binary(stego[i][j]);
            msg.push_back(binary[binary.size() - 1]);
            msg.push_back(binary[binary.size() - 2]);
            msg.push_back(binary[binary.size() - 3]);
        }
    }
    for (int i = 0; i < msg.size(); i++)
    {
        cout << msg[i] << " ";
    }
    cout << endl;

    return msg;
}

// embed function for 2 bits
vector<vector<int>> embed_2bit(vector<vector<int>> cover_image, vector<int> binary_message)
{

    vector<vector<int>> stego = cover_image;
    int count = 0;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            vector<int> binary = convert_to_binary(cover_image[i][j]);
            // change last 2 bits
            binary[binary.size() - 1] = binary_message[count++];
            binary[binary.size() - 2] = binary_message[count++];
            stego[i][j] = binaryToDecimal(binary);

            cout << stego[i][j] << " ";
        }
        cout << endl;
    }

    return stego;
}

// embed function for 3 bits
vector<vector<int>> embed_3bit(vector<vector<int>> cover_image, vector<int> binary_message)
{

    vector<vector<int>> stego = cover_image;
    int count = 0;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            vector<int> binary = convert_to_binary(cover_image[i][j]);
            // change last 2 bits
            binary[binary.size() - 1] = binary_message[count++];
            binary[binary.size() - 2] = binary_message[count++];
            binary[binary.size() - 3] = binary_message[count++];
            stego[i][j] = binaryToDecimal(binary);

            cout << stego[i][j] << " ";
        }
        cout << endl;
    }

    return stego;
}

// MSE function
float MSE(vector<vector<int>> cover_image, vector<vector<int>> stego)
{
    float sum = 0;

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            int temp = cover_image[i][j] - stego[i][j];
            sum = sum + (temp * temp);
        }
    }

    return sum / (DIM * DIM);
}

// PSNR function
float PSNR(float mse, int R)
{
    float res = (R * R) / mse;
    return log10(res) * 10;
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

int binaryToDecimal(vector<int> n)
{

    int dec_value = 0;
    int base = 1;

    int len = n.size();
    for (int i = len - 1; i >= 0; i--)
    {
        if (n[i] == 1)
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}