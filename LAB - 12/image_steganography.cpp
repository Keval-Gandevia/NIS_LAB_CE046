#include <bits/stdc++.h>
using namespace std;
#define DIM 8
#define MSG_SIZE 64

// function definitions
vector<vector<int>> embed(vector<vector<int>> cover_image, vector<int> binary_message);
vector<int> extract(vector<vector<int>> stego);
float MSE(vector<vector<int>> cover_image, vector<vector<int>> stego);
float PSNR(float mse, int R);

int main()
{

    vector<vector<int>> cover_image(DIM, vector<int>(DIM));

    cout << "\nEnter the cover image....." << endl;
    for(int i = 0; i < DIM; i++)
    {
        for(int j = 0; j < DIM; j++)
        {
            cin >> cover_image[i][j];
        }
    }

    vector<int> binary_message(MSG_SIZE);

    cout << "\nEnter the binary message with each bit separated by space....." << endl;

    for(int i = 0; i < MSG_SIZE; i++)
    {
        cin >> binary_message[i];
    }

    cout << "\nStego obejct....." << endl;
    vector<vector<int>> stego = embed(cover_image, binary_message);

    cout << "\nExtracted message....." << endl;
    vector<int> extracted_msg = extract(stego);

    float mse = MSE(cover_image, stego);
    cout << "\nMSE: " << mse << endl << endl;

    float psnr_value = PSNR(mse, 255);

    cout << "PSNR: " << psnr_value << endl << endl;

    return 0;
}

// embed function
vector<vector<int>> embed(vector<vector<int>> cover_image, vector<int> binary_message)
{

    vector<vector<int>> stego = cover_image;
    int count = 0;
    

    for(int i = 0; i < DIM; i++)
    {
        for(int j = 0; j < DIM; j++)
        {
            if(cover_image[i][j] % 2 == 0 && binary_message[count] % 2 == 1)
            {
                stego[i][j] += 1;
            }
            else if(cover_image[i][j] % 2 == 1 && binary_message[count] % 2 == 0)
            {
                stego[i][j] -= 1;
            }
            count++;
            cout << stego[i][j] << " ";
        }
        cout << endl;
    }

    return stego;
}

// extract function
vector<int> extract(vector<vector<int>> stego)
{
    vector<int> msg;

    for(int i = 0; i < DIM; i++)
    {
        for(int j = 0; j < DIM; j++)
        {
            if(stego[i][j] % 2 == 0)
            {
                msg.push_back(0);
            }
            else
            {
                msg.push_back(1);
            }
        }
    }
    for(int i = 0; i < msg.size(); i++)
    {
        cout << msg[i] << " ";
    }
    cout << endl;

    return msg;
}

// MSE function
float MSE(vector<vector<int>> cover_image, vector<vector<int>> stego)
{
    float sum = 0;

    for(int i = 0; i < DIM; i++)
    {
        for(int j = 0; j < DIM; j++)
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