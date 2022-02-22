#include <bits/stdc++.h>
using namespace std;

vector<int> extended_euclidean(int a, int n);
int multiplicative_inverse(int a, int n);
vector<int> text_mapping(string s, bool isCapital);
vector<string> make_groups(string text, int key_matrix_size);
vector<vector<int>> matrix_multiplication(vector<vector<int>> plain_text_matrix, vector<vector<int>> key_matrix);
int determinant(vector<vector<int>> matrix, int n);
vector<vector<int>> get_CoFactor(vector<vector<int>> matrix, int p, int q, int n);
vector<vector<int>> adjoint(vector<vector<int>> matrix);
string encryption(string plain_text, vector<vector<int>> key_matrix);
string decryption(string cipher_text, vector<vector<int>> key_matrix);

int main()
{

    string plain_text;
    cout << "Enter the plain text: ";
    cin >> plain_text;

    int key_matrix_size;
    cout << "Enter the size of the key matrix: ";
    cin >> key_matrix_size;

    vector<vector<int>> key_matrix(key_matrix_size, vector<int>(key_matrix_size));
    cout << "Enter the elements of the key matrix........" << endl;
    for (int i = 0; i < key_matrix_size; i++)
    {
        for (int j = 0; j < key_matrix_size; j++)
        {
            cin >> key_matrix[i][j];
        }
    }

    string cipher_text = encryption(plain_text, key_matrix);

    decryption(cipher_text, key_matrix);

    return 0;
}

// decryption algorithm
string decryption(string cipher_text, vector<vector<int>> key_matrix)
{
    // int length = cipher_text.length();
    int key_matrix_size = key_matrix.size();

    vector<string> groups = make_groups(cipher_text, key_matrix_size);
    int no_of_groups = groups.size();

    // find the cipher text matrix
    vector<vector<int>> cipher_text_matrix(no_of_groups, vector<int>(key_matrix_size));

    cout << "\n\nCipher text matrix.........." << endl;

    for (int i = 0; i < no_of_groups; i++)
    {
        cipher_text_matrix[i] = text_mapping(groups[i], true);

        for (int j = 0; j < key_matrix_size; j++)
        {
            cout << cipher_text_matrix[i][j] << "\t";
        }

        cout << endl;
    }

    cout << endl;

    // cout << "\n\nCipher text matrix.........." << endl;

    // for (int i = 0; i < no_of_groups; i++)
    // {
    //     for (int j = 0; j < key_matrix_size; j++)
    //     {
    //         cout << cipher_text_matrix[i][j] << "\t";
    //     }

    //     cout << endl;
    // }
    // cout << endl;

    // find determinant of k
    int det = determinant(key_matrix, key_matrix_size);

    cout << "Determinant of the key matrix: " << det << endl;

    vector<vector<int>> adj = adjoint(key_matrix);

    cout << "\nAdjoint of k..........." << endl;
    for (int i = 0; i < key_matrix_size; i++)
    {
        for (int j = 0; j < key_matrix_size; j++)
        {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    // find the determinant inverse;

    int det_inverse = multiplicative_inverse(det, 26);

    cout << "Determinant inverse: " << det_inverse << endl;

    vector<vector<int>> k_inverse(key_matrix_size, vector<int>(key_matrix_size));

    cout << "\nK inverse........." << endl;

    for (int i = 0; i < key_matrix_size; i++)
    {
        for (int j = 0; j < key_matrix_size; j++)
        {
            k_inverse[i][j] = (det_inverse * adj[i][j]) % 26;

            cout << k_inverse[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    // c X k_inverse
    cout << "Result of C X K_Inverse............." << endl;
    vector<vector<int>> c_x_k_inverse = matrix_multiplication(cipher_text_matrix, k_inverse);

    string plain_text = "";
    for (int i = 0; i < no_of_groups; i++)
    {
        for (int j = 0; j < key_matrix_size; j++)
        {
            plain_text += char(c_x_k_inverse[i][j] + 'a');
        }
    }

    cout << "\nPlain Text: " << plain_text << endl;

    return plain_text;
}

// Encryption Algorithm
string encryption(string plain_text, vector<vector<int>> key_matrix)
{

    // int length = plain_text.length();
    int key_matrix_size = key_matrix.size();

    // make gropus
    vector<string> groups = make_groups(plain_text, key_matrix_size);

    int no_of_groups = groups.size();

    if (groups[no_of_groups - 1].length() != key_matrix_size)
    {
        int n = groups[no_of_groups - 1].length();
        for (int i = n; i < key_matrix_size; i++)
        {
            groups[no_of_groups - 1] += 'z';
        }
    }

    cout << "\nCreated groups are: ";
    for (int i = 0; i < no_of_groups; i++)
    {
        cout << groups[i] << "  ";
    }

    // do text mapping
    vector<vector<int>> plain_text_matrix(no_of_groups, vector<int>(key_matrix_size));

    cout << "\n\nPlain text matrix.........." << endl;

    for (int i = 0; i < no_of_groups; i++)
    {
        plain_text_matrix[i] = text_mapping(groups[i], false);
        for (int j = 0; j < key_matrix_size; j++)
        {
            cout << plain_text_matrix[i][j] << "\t";
        }

        cout << endl;
    }

    cout << endl;

    // P X K result
    cout << "Result of P X K..........." << endl;
    vector<vector<int>> p_x_k = matrix_multiplication(plain_text_matrix, key_matrix);

    string cipher_text = "";
    for (int i = 0; i < no_of_groups; i++)
    {
        for (int j = 0; j < key_matrix_size; j++)
        {
            cipher_text += char(p_x_k[i][j] + 'A');
        }
    }

    cout << "\nCipher Text: " << cipher_text << endl;

    return cipher_text;
}

vector<string> make_groups(string text, int key_matrix_size)
{

    int length = text.length();
    vector<string> groups;

    for (int i = 0; i < length; i += key_matrix_size)
    {
        string temp = "";
        for (int j = 0; j < key_matrix_size; j++)
        {
            if (i + j < length)
            {
                temp += text[i + j];
            }
        }

        // cout << "Temp: " << temp << endl;
        groups.push_back(temp);
    }

    return groups;
}

// function used to perform the P X K
vector<vector<int>> matrix_multiplication(vector<vector<int>> plain_text_matrix, vector<vector<int>> key_matrix)
{
    int res_row = plain_text_matrix.size();
    int res_col = key_matrix[0].size();
    vector<vector<int>> res(res_row, vector<int>(res_col));

    for (int i = 0; i < res_row; i++)
    {
        for (int j = 0; j < res_col; j++)
        {
            res[i][j] = 0;

            for (int k = 0; k < res_col; k++)
            {
                res[i][j] = (res[i][j] +
                             (plain_text_matrix[i][k] * key_matrix[k][j])) %
                            26;
            }

            cout << res[i][j] << "\t";
        }

        cout << endl;
    }

    return res;
}

vector<vector<int>> adjoint(vector<vector<int>> matrix)
{
    int sign = 1;
    int n = matrix.size();

    vector<vector<int>> adj(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            vector<vector<int>> temp = get_CoFactor(matrix, i, j, n);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj[j][i] = ((sign) * (determinant(temp, n - 1))) % 26;

            if (adj[j][i] < 0)
            {
                adj[j][i] += 26;
            }
        }
    }

    return adj;
}

// function used to find determinant
int determinant(vector<vector<int>> matrix, int n)
{
    // int n = matrix.size();
    int res = 0;

    if (n == 1)
    {
        return matrix[0][0];
    }

    int sign = 1;

    for (int i = 0; i < n; i++)
    {
        // get the cofactor
        vector<vector<int>> temp = get_CoFactor(matrix, 0, i, n);
        res += sign * matrix[0][i] * determinant(temp, n - 1);
        // cout << "res: " << res << endl;
        sign = -sign;
    }

    res = res % 26;

    if (res < 0)
    {
        res += 26;
    }

    return res;
}

// function used to find the cofactor
vector<vector<int>> get_CoFactor(vector<vector<int>> matrix, int p, int q, int n)
{
    int i = 0, j = 0;

    vector<vector<int>> temp(n, vector<int>(n));

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = matrix[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }

    return temp;
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