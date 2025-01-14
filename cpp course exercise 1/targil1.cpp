//question 1
#include <iostream>
using namespace std;

int* maxSequenceIndex(int arr[], int size, int num = 0);

int main() {
    int arr[] = { 3, 3, 3,1, 45, 3, 3, 25, 3, 3, 3 ,3 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int* result = maxSequenceIndex(arr, size, 3);
    cout << "Function running witout default settings : " << endl;
    cout << "Value of max index sequence is " << result[0] << endl;
    cout << "Value of count Max is " << result[1] << endl;
    cout << endl;
    int arrD[] = { 3, 3, 3,1, 0 };
    int sizeD = sizeof(arrD) / sizeof(arrD[0]);
    int* resultDefault = maxSequenceIndex(arrD, sizeD);
    cout << "Function running with default settings : " << endl;
    cout << "Value of max index sequence is " << resultDefault[0] << endl;
    cout << "Value of count Max is " << resultDefault[1] << endl;
    delete[] result;

    return 0;
}

int* maxSequenceIndex(int arr[], int size, int num) {
    int* result = new int[2];
    result[0] = 0;
    result[1] = 0;
    int maxSequenceIndex = 0;
    int count = 0;
    int countMax = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == num) {
            count++;
            if (countMax <= count) {
                countMax = count;
            }
            maxSequenceIndex = i + 1 - countMax;
        }
        else {
            count = 0;
        }
    }
    result[0] = maxSequenceIndex;
    result[1] = countMax;
    return result;

}

//question 3


#include <iostream>
using namespace std;
#include <cstring>

char** separateString(const char* input, int& numUpper, int& numLower, int& num) {
    numUpper = 0;
    numLower = 0;
    num = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (isupper(input[i])) {
            numUpper++;
        }
        else if (islower(input[i])) {
            numLower++;
        }
        else if (isdigit(input[i])) {
            num++;
        }
    }

    char** result = new char* [3];
    result[0] = new char[numUpper + 1];
    result[1] = new char[numLower + 1];
    result[2] = new char[num + 1];

    int upperIndex = 0, lowerIndex = 0, digitIndex = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (isupper(input[i])) {
            result[0][upperIndex++] = input[i];
        }
        else if (islower(input[i])) {
            result[1][lowerIndex++] = input[i];
        }
        else if (isdigit(input[i])) {
            result[2][digitIndex++] = input[i];
        }
    }

    result[0][upperIndex] = '\0';
    result[1][lowerIndex] = '\0';
    result[2][digitIndex] = '\0';

    return result;
}

int main() {
    const char* input = "Mo34!zTcsl0#1";
    int numUpper, numLower, num;

    char** result = separateString(input, numUpper, numLower, num);

    cout << "Uppercase letters: " << result[0] << endl;
    cout << "Lowercase letters: " << result[1] << endl;
    cout << "Digit letters: " << result[2] << endl;

    // Free allocated memory
    delete[] result[0];
    delete[] result[1];
    delete[] result[2];
    delete[] result;

    return 0;
}

//question 2


#include <iostream>
#include <cstring> // For strlen and strcpy
#pragma warning(disable:4996)
using namespace std;

const int SIZE = 5;
const int MAX_WORD_LENGTH = 100; // Define a maximum length for each word

void initData(char* words[], int* numbers[], int size) {
    for (int i = 0; i < size; ++i) {
        words[i] = new char[MAX_WORD_LENGTH];

        cout << "Enter a word: ";
        cin >> words[i];

        cout << "Enter a positive number: ";
        int num;
        cin >> num;

        // Handle invalid input for numbers
        if (num < 0) {
            cout << "Invalid number. Must be positive." << endl;
            --i; // Retry the current index
            delete[] words[i];
            continue;
        }

        int numDigits = 0;
        int tempNum = num;
        while (tempNum > 0) {
            tempNum /= 10;
            numDigits++;
        }
        numDigits = max(numDigits, 1); // Ensure at least one digit

        numbers[i] = new int[numDigits + 1];
        tempNum = num;
        for (int j = numDigits - 1; j >= 0; --j) {
            numbers[i][j] = tempNum % 10;
            tempNum /= 10;
        }
        numbers[i][numDigits] = -1; // End marker
    }
}

void printMostCommon(char* words[], int* numbers[], int size) {
    // Initialize word frequency
    pair<char*, int> wordFreq[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        wordFreq[i].first = nullptr;
        wordFreq[i].second = 0;
    }

    for (int i = 0; i < size; ++i) {
        bool found = false;
        for (int j = 0; j < SIZE; ++j) {
            if (wordFreq[j].first != nullptr && strcmp(wordFreq[j].first, words[i]) == 0) {
                wordFreq[j].second++;
                found = true;
                break;
            }
        }
        if (!found) {
            for (int j = 0; j < SIZE; ++j) {
                if (wordFreq[j].second == 0) {
                    wordFreq[j].first = new char[strlen(words[i]) + 1];
                    strcpy(wordFreq[j].first, words[i]);
                    wordFreq[j].second = 1;
                    break;
                }
            }
        }
    }

    char* mostCommonWord = nullptr;
    int maxWordFreq = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (wordFreq[i].second > maxWordFreq) {
            maxWordFreq = wordFreq[i].second;
            mostCommonWord = wordFreq[i].first;
        }
    }

    int digitFreq[10] = { 0 };
    for (int i = 0; i < size; ++i) {
        int j = 0;
        while (numbers[i][j] != -1) {
            digitFreq[numbers[i][j]]++;
            j++;
        }
    }

    int mostCommonDigit = 0;
    int maxDigitFreq = 0;
    for (int i = 0; i < 10; ++i) {
        if (digitFreq[i] > maxDigitFreq) {
            maxDigitFreq = digitFreq[i];
            mostCommonDigit = i;
        }
    }

    if (mostCommonWord != nullptr) {
        cout << "Most common word: " << mostCommonWord << endl;
    }
    else {
        cout << "No common word found." << endl;
    }
    cout << "Most common digit: " << mostCommonDigit << endl;
}

void releaseMemory(char* words[], int* numbers[], int size) {
    for (int i = 0; i < size; ++i) {
        delete[] words[i];
        delete[] numbers[i];
    }
}

int main() {
    char* words[SIZE];
    int* numbers[SIZE] = { nullptr };

    initData(words, numbers, SIZE);
    printMostCommon(words, numbers, SIZE);
    releaseMemory(words, numbers, SIZE);

    return 0;
}