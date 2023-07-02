#include <iostream>
#include <vector>

// Function to perform byte stuffing
std::vector<unsigned char> byteStuffing(const std::vector<unsigned char>& data, unsigned char flag, unsigned char escape) {
    std::vector<unsigned char> stuffedData;

    // Start with the flag character
    stuffedData.push_back(flag);

    // Iterate through each byte in the data
    for (unsigned char byte : data) {
        // If the byte is the same as the flag or escape character, add an escape character before it
        if (byte == flag || byte == escape) {
            stuffedData.push_back(escape);
        }

        // Add the byte to the stuffed data
        stuffedData.push_back(byte);
    }

    // End with the flag character
    stuffedData.push_back(flag);

    return stuffedData;
}

// Function to remove byte stuffing
std::vector<unsigned char> byteUnstuffing(const std::vector<unsigned char>& stuffedData, unsigned char flag, unsigned char escape) {
    std::vector<unsigned char> data;
    
    // Skip the first flag character
    auto it = stuffedData.begin() + 1;

    // Iterate until the second flag character
    while (*it != flag) {
        // If the current byte is an escape character
        if (*it == escape) {
            ++it;  // Move to the next byte

            // If the next byte is the escape character or flag character, add it without the escape character
            if (*it == escape || *it == flag) {
                data.push_back(*it);
            }
        } else {
            // Add the byte to the data vector
            data.push_back(*it);
        }

        ++it;  // Move to the next byte
    }

    return data;
}

int main() {
    // Example data
    std::vector<unsigned char> data = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE };

    // Define flag and escape characters
    unsigned char flag = 0xFF;
    unsigned char escape = 0x00;

    // Perform byte stuffing on the data
    std::vector<unsigned char> stuffedData = byteStuffing(data, flag, escape);

    // Print the stuffed data
    std::cout << "Stuffed Data: ";
    for (unsigned char byte : stuffedData) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    // Perform byte unstuffing on the stuffed data
    std::vector<unsigned char> unstuffedData = byteUnstuffing(stuffedData, flag, escape);

    // Print the unstuffed data
    std::cout << "Unstuffed Data: ";
    for (unsigned char byte : unstuffedData) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    return 0;
}
