#pragma once
#include "MyString.h"
#include "User.h"
#include "Driver.h"
#include "Client.h"

const size_t MAX_PHONE_NUMBER = 10;
const size_t MAX_CAR_NUMBER = 8;
const size_t BUFF_SIZE = 1024;

void toLower(MyString& buff);

int getNumSize(size_t num);

MyString convertToStr(size_t num);

bool isNumberF(char ch);

bool isCapitalLetter(char ch);

bool isValidNumber(const MyString& arr);

bool isValidCarNumber(const MyString& carNumber);

bool isValidPhoneNumber(const MyString& phoneNumber);

double convertToLeva(size_t amount);

int convertToCoins(double amount);

int numbersAfterComa(const char* str);

double stringToDouble(const char* str);

unsigned getCharCountFromFile(std::ifstream& ifs, char ch);

unsigned getLinesCount(std::ifstream& ifs);

int getSizeOfStr(const MyString& str);

int fromStringToInt(const MyString& number);

Client* findClient(Vector<Client>& users, const MyString& str);

Driver* findDriver(Vector<Driver>& users, const MyString& str);
