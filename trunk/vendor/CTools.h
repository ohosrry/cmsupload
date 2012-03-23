#ifndef CTOOL_H
#define CTOOL_H 
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
namespace ctool
{

	typedef unsigned char BYTE;

	inline BYTE toHex(const BYTE &x)
	{
		return x > 9 ? x + 55: x + 48; 
	}

	inline string URLEncode(const string &sIn)
	{
		// cout << "size: " << sIn.size() << endl;
		string sOut;
		for( size_t ix = 0; ix < sIn.size(); ix++ )
		{       
			BYTE buf[4]; 
			memset( buf, 0, 4 ); 
			if( isalnum( (BYTE)sIn[ix] ) )
			{       
				buf[0] = sIn[ix];
			}
			else if ( isspace( (BYTE)sIn[ix] ) )
			{
				buf[0] = '+';
			}
			else
			{
				buf[0] = '%';
				buf[1] = toHex( (BYTE)sIn[ix] >> 4 );
				buf[2] = toHex( (BYTE)sIn[ix] % 16);
			}
			sOut += (char *)buf;
		}
		return sOut;
	};
}
#endif