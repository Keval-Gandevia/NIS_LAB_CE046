#include <bits/stdc++.h>
using namespace std;

// bool arr[26] = {false};
vector<bool> isRepeat(26, false) ;
char alphabets[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'};

// char alternative_assignment[26];
vector<char> alternative_assignment(26);

void generate_random_string()
{
    int count = 0;
    while (1)
    {
        // cout << count << endl;
        if (count == 26)
        {
            break;
        }
        srand(time(0));
        int seed = (rand() + 5) % 26;
        // cout << "Seed is: " << seed << endl;
        int temp = isRepeat[seed];
        if (temp == false)
        {
            isRepeat[seed] = true;
            
            alternative_assignment[count] = alphabets[seed];
            count++;
        }
    }

    cout << "\nPrinting alternative assignment..................." << endl;

    for(int i = 0; i < 26; i++) {
        cout << alphabets[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 26; i++)
    {
        cout << alternative_assignment[i] << " ";
    }

    cout << endl;
}

int index_of_alternative_assignment(char ch) {

    for(int i = 0; i < 26; i++) {
        if(ch == alternative_assignment[i]) {
            return i;
        }
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

// Decryption algorithm
// isPrint = true -> print table
// isPrint = false -> don't print table
string decryption(string cipher_text, int cipher_key, bool isPrint)
{
    int length = cipher_text.length();
    vector<int> cipher_text_mapping = text_mapping(cipher_text, true);

    if (isPrint)
    {
        cout << setw(27) << "Cipher Text Mapping| ";
        print_values(cipher_text_mapping);

        cout << endl
             << setw(27)
             << "Key| ";
        for (int i = 0; i < length; i++)
        {
            cout << cipher_key << " ";
        }

        cout << endl;
    }

    // cipher_text - key
    for (int i = 0; i < length; i++)
    {
        cipher_text_mapping[i] -= cipher_key;
    }

    if (isPrint)
    {
        cout << setw(27) << "(Cipher Text - Key)| ";
        print_values(cipher_text_mapping);
        cout << endl;
    }

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

    string substitute_text(length, ' '), plain_text(length, ' ');

    for (int i = 0; i < length; i++)
    {
        substitute_text[i] = char(cipher_text_mapping[i] + 'a');
        plain_text[i] = char(index_of_alternative_assignment(substitute_text[i]) + 'a');
    }

    if (isPrint)
    {
        cout << setw(27) << "(Cipher Text - Key) % 26| ";
        print_values(cipher_text_mapping);
        cout << endl;
        cout << setw(27) << "Substitute Text| ";

        for (int i = 0; i < length; i++)
        {
            cout << substitute_text[i] << " ";
        }
        cout << endl;

        cout << setw(27) << "Plain Text| ";

        for (int i = 0; i < length; i++)
        {
            cout << plain_text[i] << " ";
        }
        cout << endl;
    }


    return plain_text;
}

// cryptanalysis
void cryptanalysis(string cipher_text, string plain_text)
{
    for (int i = 1; i <= 26; i++)
    {
        string res = decryption(cipher_text, i, false);
        if (res == plain_text)
        {
            cout << "\n\nIn CryptAnalysis Key value is: " << i << endl << endl;
            break;
        }
    }
}

// encryption algorithm
string encryption(string original_msg, int cipher_key)
{
    int length = original_msg.length();
    vector<int> plain_text_mapping = text_mapping(original_msg, false);

    cout << setw(25) << "Plain Text Mapping| ";
    print_values(plain_text_mapping);

    cout << endl
         << setw(25)
         << "Key| ";
    for (int i = 0; i < length; i++)
    {
        cout << cipher_key << " ";
    }

    cout << endl;

    // plin text + key
    for (int i = 0; i < length; i++)
    {
        plain_text_mapping[i] += cipher_key;
    }

    cout << setw(25) << "(Plain Text + Key)| ";
    print_values(plain_text_mapping);
    cout << endl;

    // (plain text + key) % 26
    for (int i = 0; i < length; i++)
    {
        plain_text_mapping[i] = plain_text_mapping[i] % 26;
    }

    cout << setw(25) << "(Plain Text + Key) % 26| ";
    print_values(plain_text_mapping);
    cout << endl;

    string cipher_text(length, ' ');

    for (int i = 0; i < length; i++)
    {
        cipher_text[i] = char(plain_text_mapping[i] + 'A');
    }

    cout << setw(25) << "Cipher Text| ";

    for (int i = 0; i < length; i++)
    {
        cout << cipher_text[i] << " ";
    }

    return cipher_text;
}

int main()
{

    string original_msg;
    cout << "Enter the original message: ";
    cin >> original_msg;

    int cipher_key;
    cout << "Enter the cipher key: ";
    cin >> cipher_key;

    generate_random_string();

    cout << "\nEncryption Table is below: ";
    cout << "\n---------------------------------------------------------";
    cout << endl;

    cout << setw(25) << "Plain Text| ";
    for (int i = 0; i < original_msg.length(); i++)
    {
        cout << original_msg[i] << " ";
    }
    cout << endl;

    

    string substituted_msg(original_msg.length(), ' ');
    cout << setw(25) << "Substituted Text| ";
    for(int i = 0; i < original_msg.length(); i++) 
    {
        substituted_msg[i] = alternative_assignment[original_msg[i] - 'a'];
        cout << substituted_msg[i] << " ";  
    }    

    cout << endl;

    string cipher_text = encryption(substituted_msg, cipher_key);
    cout << "\n---------------------------------------------------------";

    cout << "\n\nDescryption Table is below: ";
    cout << "\n---------------------------------------------------------";
    cout << endl;

    cout << setw(27) << "Cipher Text| ";
    for (int i = 0; i < cipher_text.length(); i++)
    {
        cout << cipher_text[i] << " ";
    }
    cout << endl;
    decryption(cipher_text, cipher_key, true);

    cout << "---------------------------------------------------------";

    // cryptanalysis(cipher_text, original_msg);

    return 0;
}