#pragma once
#include "MyString.h"

const size_t MAX_PHONE_NUMBER = 10;
const size_t MAX_CAR_NUMBER = 8;

bool isNumberF(char ch);

bool isCapitalLetter(char ch);

bool isValidNumber(const MyString& arr);

bool isValidCarNumber(const MyString& carNumber);

bool isValidPhoneNumber(const MyString& phoneNumber);

double convertToLeva(size_t amount);

size_t convertToCoins(double amount);

int numbersAfterComa(const char* str);

double stringToDouble(const char* str);

unsigned getCharCountFromFile(std::ifstream& ifs, char ch);

unsigned getLinesCount(std::ifstream& ifs);

int getSizeOfStr(const MyString& str);

int fromStringToInt(const MyString& number);