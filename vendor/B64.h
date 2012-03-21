#pragma  once
#ifndef _B64_H 
#include "stdafx.h"
//#include <inttypes.h>
#include <string>
#include <vector>
const static TCHAR encodeLookup[] = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
const static TCHAR padCharacter = TEXT('=');
std::basic_string<TCHAR> base64Encode(std::vector<BYTE> inputBuffer)
{
	std::basic_string<TCHAR> encodedString;
	encodedString.reserve(((inputBuffer.size()/3) + (inputBuffer.size() % 3 > 0)) * 4);
	DWORD temp;
	std::vector<BYTE>::iterator cursor = inputBuffer.begin();
	for(size_t idx = 0; idx < inputBuffer.size()/3; idx++)
	{
		temp  = (*cursor++) << 16; //Convert to big endian
		temp += (*cursor++) << 8;
		temp += (*cursor++);
		encodedString.append(1,encodeLookup[(temp & 0x00FC0000) >> 18]);
		encodedString.append(1,encodeLookup[(temp & 0x0003F000) >> 12]);
		encodedString.append(1,encodeLookup[(temp & 0x00000FC0) >> 6 ]);
		encodedString.append(1,encodeLookup[(temp & 0x0000003F)      ]);
	}
	switch(inputBuffer.size() % 3)
	{
	case 1:
		temp  = (*cursor++) << 16; //Convert to big endian
		encodedString.append(1,encodeLookup[(temp & 0x00FC0000) >> 18]);
		encodedString.append(1,encodeLookup[(temp & 0x0003F000) >> 12]);
		encodedString.append(2,padCharacter);
		break;
	case 2:
		temp  = (*cursor++) << 16; //Convert to big endian
		temp += (*cursor++) << 8;
		encodedString.append(1,encodeLookup[(temp & 0x00FC0000) >> 18]);
		encodedString.append(1,encodeLookup[(temp & 0x0003F000) >> 12]);
		encodedString.append(1,encodeLookup[(temp & 0x00000FC0) >> 6 ]);
		encodedString.append(1,padCharacter);
		break;
	}
	return encodedString;
}

//const static TCHAR padCharacter = TEXT('=');
std::vector<BYTE> base64Decode(const std::basic_string<TCHAR>& input)
{
	if (input.length() % 4) //Sanity check
		throw std::runtime_error("Non-Valid base64!");
	size_t padding = 0;
	if (input.length())
	{
		if (input[input.length()-1] == padCharacter)
			padding++;
		if (input[input.length()-2] == padCharacter)
			padding++;
	}
	//Setup a vector to hold the result
	std::vector<BYTE> decodedBytes;
	decodedBytes.reserve(((input.length()/4)*3) - padding);
	DWORD temp=0; //Holds decoded quanta
	std::basic_string<TCHAR>::const_iterator cursor = input.begin();
	while (cursor < input.end())
	{
		for (size_t quantumPosition = 0; quantumPosition < 4; quantumPosition++)
		{
			temp <<= 6;
			if       (*cursor >= 0x41 && *cursor <= 0x5A) // This area will need tweaking if
				temp |= *cursor - 0x41;                       // you are using an alternate alphabet
			else if  (*cursor >= 0x61 && *cursor <= 0x7A)
				temp |= *cursor - 0x47;
			else if  (*cursor >= 0x30 && *cursor <= 0x39)
				temp |= *cursor + 0x04;
			else if  (*cursor == 0x2B)
				temp |= 0x3E; //change to 0x2D for URL alphabet
			else if  (*cursor == 0x2F)
				temp |= 0x3F; //change to 0x5F for URL alphabet
			else if  (*cursor == padCharacter) //pad
			{
				switch( input.end() - cursor )
				{
				case 1: //One pad character
					decodedBytes.push_back((temp >> 16) & 0x000000FF);
					decodedBytes.push_back((temp >> 8 ) & 0x000000FF);
					return decodedBytes;
				case 2: //Two pad characters
					decodedBytes.push_back((temp >> 10) & 0x000000FF);
					return decodedBytes;
				default:
					throw std::runtime_error("Invalid Padding in Base 64!");
				}
			}  else
				throw std::runtime_error("Non-Valid Character in Base 64!");
			cursor++;
		}
		decodedBytes.push_back((temp >> 16) & 0x000000FF);
		decodedBytes.push_back((temp >> 8 ) & 0x000000FF);
		decodedBytes.push_back((temp      ) & 0x000000FF);
	}
	return decodedBytes;
}
int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize)
{
	const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const uint8_t *data = (const uint8_t *)data_buf;
	size_t resultIndex = 0;
	size_t x;
	uint32_t n = 0;
	int padCount = dataLength % 3;
	uint8_t n0, n1, n2, n3;

	/* increment over the length of the string, three characters at a time */
	for (x = 0; x < dataLength; x += 3) 
	{
		/* these three 8-bit (ASCII) characters become one 24-bit number */
		n = data[x] << 16;

		if((x+1) < dataLength)
			n += data[x+1] << 8;

		if((x+2) < dataLength)
			n += data[x+2];

		/* this 24-bit number gets separated into four 6-bit numbers */
		n0 = (uint8_t)(n >> 18) & 63;
		n1 = (uint8_t)(n >> 12) & 63;
		n2 = (uint8_t)(n >> 6) & 63;
		n3 = (uint8_t)n & 63;

		/*
		* if we have one byte available, then its encoding is spread
		* out over two characters
		*/
		if(resultIndex >= resultSize) return 0;   /* indicate failure: buffer too small */
		result[resultIndex++] = base64chars[n0];
		if(resultIndex >= resultSize) return 0;   /* indicate failure: buffer too small */
		result[resultIndex++] = base64chars[n1];

		/*
		* if we have only two bytes available, then their encoding is
		* spread out over three chars
		*/
		if((x+1) < dataLength)
		{
			if(resultIndex >= resultSize) return 0;   /* indicate failure: buffer too small */
			result[resultIndex++] = base64chars[n2];
		}

		/*
		* if we have all three bytes available, then their encoding is spread
		* out over four characters
		*/
		if((x+2) < dataLength)
		{
			if(resultIndex >= resultSize) return 0;   /* indicate failure: buffer too small */
			result[resultIndex++] = base64chars[n3];
		}
	}  

	/*
	* create and add padding that is required if we did not have a multiple of 3
	* number of characters available
	*/
	if (padCount > 0) 
	{ 
		for (; padCount < 3; padCount++) 
		{ 
			if(resultIndex >= resultSize) return 0;   /* indicate failure: buffer too small */
			result[resultIndex++] = '=';
		} 
	}
	if(resultIndex >= resultSize) return 0;   /* indicate failure: buffer too small */
	result[resultIndex] = 0;
	return 1;   /* indicate success */
}

#endif