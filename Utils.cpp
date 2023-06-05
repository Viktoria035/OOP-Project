#include <iostream>
#include "Utils.h"
#include <fstream>
#pragma warning (disable:4996)


bool isNumberF(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool isCapitalLetter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

bool isValidNumber(const MyString& arr)
{
	bool isNumber = true;
	for (size_t i = 0; i < arr.length(); i++)
	{
		if (!isNumberF(arr[i]))
		{
			isNumber = false;
		}
	}
	return isNumber;
}

bool isValidCarNumber(const MyString& carNumber)
{
	if (carNumber.length() != MAX_CAR_NUMBER || !isCapitalLetter(carNumber[0]) || !isCapitalLetter(carNumber[1]) ||
		!isCapitalLetter(carNumber[6]) || !isCapitalLetter(carNumber[7]))
		return false;

	for (size_t i = 2; i <= 5; i++)
	{
		if (!isNumberF(carNumber[i]))
			return false;
	}
	return true;
}

bool isValidPhoneNumber(const MyString& phoneNumber)
{
	if (phoneNumber.length() != MAX_PHONE_NUMBER || phoneNumber[0] != '0' || !isValidNumber(phoneNumber))
		return false;
	return true;
}

double convertToLeva(size_t amount)
{
	return amount / 100.0;
}

size_t convertToCoins(double amount)
{
	return amount * 100;
}

int numbersAfterComa(const char* str)
{
	int i = 0;
	if (str[0] == '-') {
		i++;
	}
	bool coma = false;
	int counter = 0;
	for (int j = i;str[j] != '\0';j++) {
		if (coma) {
			counter++;
		}
		if (str[j] == ',' || str[j] == '.') {
			coma = true;
		}
	}

	return  counter;
}

double stringToDouble(const char* str)
{
	double number = 0.0;
	int minus = 1;
	int i = 0;
	if (str[0] == '-') {
		minus = -1;
		i++;
	}
	for (int j = i;str[j] != '\0';j++) {
		if (str[j] == '.' || str[j] == ',') {
			continue;
		}
		number = number * 10 + (str[j] - '0') * 10 * minus;
	}
	int digitsAfterComa = numbersAfterComa(str);
	digitsAfterComa++;

	while (digitsAfterComa > 0) {
		number /= 10;
		digitsAfterComa--;
	}

	return number;
}

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
	size_t currentPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);

	if (!ifs.is_open())
		return 0;

	unsigned int count = 0;

	while (true)
	{
		char current = ifs.get();
		if (ifs.eof())
			break;

		if (current == ch)
			count++;
	}

	ifs.clear();
	ifs.seekg(currentPosition);
	return count;
}

unsigned getLinesCount(std::ifstream& ifs)
{
	return getCharCountFromFile(ifs, '\n') + 1;
}

int getSizeOfStr(const MyString& str)
{
	int count = 0;
	while (str[count++] != '\0');
	return count;
}

int fromStringToInt(const MyString& number)
{
	int num = 0;
	int len = getSizeOfStr(number);
	int j = 0;
	while (len != 0)
	{
		if (number[j] >= '0' && number[j] <= '9')
			num = num * 10 + (number[j] - '0');
		len--;
		j++;
	}
	return num;
}