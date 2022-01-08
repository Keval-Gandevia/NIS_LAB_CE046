#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> prepare_matrix(string keyword);
vector<string> prepare_groups(string plain_text);
vector<int> find_position(string s, vector<vector<char>> allocation);
string encryption(string plain_text, vector<vector<char>> allocation);
string decryption(string cipher_text, vector<vector<char>> allocation);

int main()
{

    string plain_text;
    cout << "Enter the plain text: ";
    cin >> plain_text;

    string keyword;
    cout << "Enter the key word (In capital letter): ";
    cin >> keyword;

    vector<vector<char>> allocation = prepare_matrix(keyword);

    string cipher_text = encryption(plain_text, allocation);

    decryption(cipher_text, allocation);

    return 0;
}

// decryption algorithm
string decryption(string cipher_text, vector<vector<char>> allocation)
{
    int length = cipher_text.length();

    string plain_text = "";

    for (int i = 0; i < length; i += 2)
    {
        string temp = "";
        temp += cipher_text[i];
        temp += cipher_text[i + 1];

        vector<int> res = find_position(temp, allocation);

        // check for same row
        if (res[0] == res[2])
        {
            int col1, col2;
            if ((res[1] - 1) % 5 < 0)
            {
                col1 = ((res[1] - 1) % 5) + 5;
                plain_text += allocation[res[0]][col1];
            }
            else
            {
                plain_text += allocation[res[0]][(res[1] - 1) % 5];
            }
            if ((res[3] - 1) % 5 < 0)
            {
                col2 = ((res[3] - 1) % 5) + 5;
                plain_text += allocation[res[2]][col2];
            }
            else
            {
                plain_text += allocation[res[2]][(res[3] - 1) % 5];
            }
        }

        // check for same column
        else if (res[1] == res[3])
        {
            int col1, col2;
            if ((res[0] - 1) % 5 < 0)
            {
                col1 = ((res[0] - 1) % 5) + 5;
                plain_text += allocation[col1][res[1]];
            }
            else
            {
                plain_text += allocation[(res[0] - 1) % 5][res[1]];
            }
            if ((res[2] - 1) % 5 < 0)
            {
                col2 = ((res[2] - 1) % 5) + 5;
                plain_text += allocation[col2][res[3]];
            }
            else
            {
                plain_text += allocation[(res[2] - 1) % 5][res[3]];
            }
            
            
        }

        // check if both are not in same row or col
        else
        {
            plain_text += allocation[res[0]][res[3]];
            plain_text += allocation[res[2]][res[1]];
        }
    }

    // convert to lowercase
    transform(plain_text.begin(), plain_text.end(), plain_text.begin(), ::tolower);

    // remove the extra added characters

    string updated_plain_text = "";

    for (int i = 0; i < plain_text.length(); i++)
    {
        if (plain_text[i] == 'x')
        {
            if (plain_text[i - 1] == plain_text[i + 1] || i == plain_text.length())
            {
                // remove x
                continue;
            }
        }
        // if (i == plain_text.length() - 1 && plain_text[i] == 'x')
        // {
        //     continue;
        // }

        updated_plain_text += plain_text[i];
    }

    cout << "Updated plain text: " << updated_plain_text << endl;

    return updated_plain_text;
}

// encryption algorithm
string encryption(string plain_text, vector<vector<char>> allocation)
{
    int length = plain_text.length();
    string cipher_text = "";
    vector<string> groups = prepare_groups(plain_text);

    for (int i = 0; i < groups.size(); i++)
    {
        vector<int> res = find_position(groups[i], allocation);

        // check for same row
        if (res[0] == res[2])
        {
            cipher_text += allocation[res[0]][(res[1] + 1) % 5];
            cipher_text += allocation[res[2]][(res[3] + 1) % 5];
        }

        // check for same column
        else if (res[1] == res[3])
        {
            cipher_text += allocation[(res[0] + 1) % 5][res[1]];
            cipher_text += allocation[(res[2] + 1) % 5][res[3]];
        }

        // check if both are not in same row or col
        else
        {
            cipher_text += allocation[res[0]][res[3]];
            cipher_text += allocation[res[2]][res[1]];
        }
    }

    cout << "\nCipher Text is: " << cipher_text << endl;

    return cipher_text;
}

// find the position of the character in the matrix
// res[0] & res[1] are the position of the first character
// res[2] & res[3] are the position of the second character
vector<int> find_position(string s, vector<vector<char>> allocation)
{

    vector<int> res(4);

    // cout << s[0] << " " << s[1] << endl;

    if (s[0] == 'j')
    {
        s[0] = 'i';
    }
    else if (s[1] == 'i')
    {
        s[1] == 'j';
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (allocation[i][j] == toupper(s[0]))
            {
                // cout << "allocation is: " << i << " " << j << endl;
                res[0] = i;
                res[1] = j;
            }
            else if (allocation[i][j] == toupper(s[1]))
            {
                // cout << "allocation is: " << i << " " << j << endl;
                res[2] = i;
                res[3] = j;
            }
        }
    }

    // for (int i = 0; i < res.size(); i++)
    // {
    //     cout << res[i] << " ";
    // }

    // cout << endl;

    return res;
}

// function used to make a groups of 2 characters
vector<string> prepare_groups(string plain_text)
{
    int length = plain_text.length();
    vector<string> groups;

    for (int i = 0; i < length;)
    {
        string str = "";
        if (i + 1 < length)
        {
            if (plain_text[i] == plain_text[i + 1])
            {

                str += plain_text[i];
                str += 'x';
                groups.push_back(str);
                i++;
                continue;
            }

            str += plain_text[i];
            str += plain_text[i + 1];
            groups.push_back(str);
            i += 2;
        }
        else
        {
            str += plain_text[i];
            str += 'x';
            i++;
            groups.push_back(str);
        }
    }

    cout << "\nGroups are: " << endl;
    cout << "------------\n";
    for (int i = 0; i < groups.size(); i++)
    {
        cout << groups[i][0] << " " << groups[i][1] << endl;
    }
    cout << "------------\n";
    return groups;
}

// function used to make 5 X 5 matrix
vector<vector<char>> prepare_matrix(string keyword)
{
    vector<vector<char>> allocation(5, vector<char>(5));
    vector<bool> isRepeat(26, false);

    int i, j, k = 0;
    for (i = 0, k = 0; i < 5 && k < keyword.length(); i++)
    {

        for (j = 0; j < 5 && k < keyword.length();)
        {

            // if not repeated
            if (!isRepeat[keyword[k] - 'A'])
            {
                allocation[i][j] = keyword[k];
                isRepeat[keyword[k] - 'A'] = true;
                j++;
            }
            k++;
        }
    }

    int start_row = i - 1;
    int start_col = j;

    for (int i = start_row, k = 0; i < 5; i++)
    {

        for (int j = i == start_row ? start_col : 0; j < 5;)
        {
            if (!isRepeat[k] && k != 9)
            {
                allocation[i][j] = char(k + 'A');
                j++;
                isRepeat[k] = true;
            }
            k++;
        }
    }

    cout << "\nAllocation matrix is: " << endl;
    cout << "------------\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << allocation[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------\n";
    return allocation;
}
