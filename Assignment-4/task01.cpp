#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Function to calculate number of redundant bits required
int calculateRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < (m + r + 1)) {
        r++;
    }
    return r;
}

// Function to generate Hamming Code
vector<int> generateHammingCode(vector<int> data) {
    int m = data.size();
    int r = calculateRedundantBits(m);
    int total = m + r;

    vector<int> code(total + 1, 0); // 1-indexed

    // Insert data bits into the codeword (skip parity positions)
    int j = 0;
    for (int i = 1; i <= total; i++) {
        if ((i & (i - 1)) != 0) { // not a power of 2 → data bit
            code[i] = data[j++];
        }
    }

    // Calculate parity bits (even parity)
    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;

        for (int k = pos; k <= total; k += 2 * pos) {
            for (int x = k; x < k + pos && x <= total; x++) {
                parity ^= code[x];
            }
        }

        code[pos] = parity;
    }

    return code;
}

// Function to detect and correct error at receiver side
int detectError(vector<int> code) {
    int total = code.size() - 1;
    int r = 0;

    while (pow(2, r) <= total)
        r++;

    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;

        for (int k = pos; k <= total; k += 2 * pos) {
            for (int x = k; x < k + pos && x <= total; x++) {
                parity ^= code[x];
            }
        }

        if (parity != 0)
            errorPos += pos;
    }

    return errorPos;
}

int main() {
    string input;
    cout << "Enter binary data: ";
    cin >> input;

    vector<int> data;
    for (char c : input)
        data.push_back(c - '0');

    // Generate Hamming Code
    vector<int> hamming = generateHammingCode(data);

    cout << "\nThe data packet to be sent is: ";
    for (int i = 1; i < hamming.size(); i++)
        cout << hamming[i] << " ";
    cout << endl;

    // Simulate receiving side
    vector<int> received = hamming;

    cout << "\nSimulating transmission...\n";

    // Uncomment this line to force an error for testing:
    // received[3] ^= 1;  // Flip bit 3

    int error = detectError(received);

    if (error == 0) {
        cout << "Correct data packet received." << endl;
    } else {
        cout << "Error detected at bit position: " << error << endl;
        received[error] ^= 1; // Correcting the bit
        cout << "Corrected data packet: ";
        for (int i = 1; i < received.size(); i++)
            cout << received[i] << " ";
        cout << endl;
    }

    return 0;
}
