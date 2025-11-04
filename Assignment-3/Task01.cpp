#include <iostream>
#include <string>
using namespace std;

// Function to perform modulo-2 division
string xor_division(string data, string generator) {
    int n = generator.size();
    string temp = data.substr(0, n);

    for (int i = 0; i < data.size() - n + 1; i++) {
        if (temp[0] == '1') {
            for (int j = 0; j < n; j++)
                temp[j] = (temp[j] == generator[j]) ? '0' : '1';
        }
        if (i + n < data.size())
            temp = temp.substr(1) + data[i + n];
        else
            temp = temp.substr(1);
    }
    return temp;
}

int main() {
    string data = "1101011011";
    string generator = "10011";
    int r = generator.size() - 1;

    // Append r zeros
    string data_appended = data + string(r, '0');

    // Get remainder
    string remainder = xor_division(data_appended, generator);

    // Transmitted frame
    string transmitted = data + remainder;

    cout << "Remainder (CRC): " << remainder << endl;
    cout << "Transmitted Frame: " << transmitted << endl;

    return 0;
}
