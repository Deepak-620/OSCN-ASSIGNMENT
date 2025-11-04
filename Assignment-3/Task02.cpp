#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to perform CRC division and return remainder
string calculateCRC(string message, string generator) {
    string dividend = message;
    int genLength = generator.length();
    
    // Append zeros to the message equal to generator length-1
    for(int i = 0; i < genLength - 1; i++)
        dividend += "0";
    
    // Perform division
    for(int i = 0; i <= dividend.length() - genLength; i++) {
        if(dividend[i] == '1') {
            for(int j = 0; j < genLength; j++) {
                dividend[i + j] = dividend[i + j] == generator[j] ? '0' : '1';
            }
        }
    }
    
    // Return last genLength-1 bits as remainder
    return dividend.substr(dividend.length() - (genLength - 1));
}

// Function to check if received message has errors
bool hasErrors(string received, string generator) {
    string remainder = calculateCRC(received, generator);
    for(char bit : remainder) {
        if(bit == '1') return true;
    }
    return false;
}

int main() {
    string message = "10011101";
    string generator = "1001";  // x³ + 1
    
    cout << "Original Message: " << message << endl;
    cout << "Generator Polynomial (x³ + 1): " << generator << endl;
    
    // Calculate CRC
    string crc = calculateCRC(message, generator);
    string transmittedMessage = message + crc;
    
    cout << "\n1. Actual bit string transmitted:" << endl;
    cout << "CRC bits: " << crc << endl;
    cout << "Transmitted message: " << transmittedMessage << endl;
    
    // Simulate error by inverting third bit
    cout << "\n2. Error Detection:" << endl;
    cout << "Original transmitted message: " << transmittedMessage << endl;
    
    // Create corrupted message by inverting third bit
    string corruptedMessage = transmittedMessage;
    corruptedMessage[2] = corruptedMessage[2] == '0' ? '1' : '0';
    
    cout << "Message with error (third bit inverted): " << corruptedMessage << endl;
    
    // Check for errors
    if(hasErrors(corruptedMessage, generator)) {
        cout << "Error detected in the received message!" << endl;
    } else {
        cout << "No errors detected in the received message." << endl;
    }
    
    return 0;
}
