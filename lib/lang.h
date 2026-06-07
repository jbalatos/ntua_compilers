#pragma once

#if !defined(BITS)
#	error no integer bit width provided (-DBITS=)
#endif

#if defined(PCL)
/* I/O */
#	define readChar     readChar
#	define readString   readString
#	define readByte     readByte
#	define readInteger  readInteger
#	define readBoolean  readBoolean
#	define writeChar    writeChar
#	define writeString  writeString
#	define writeByte    writeByte
#	define writeInteger writeInteger
#	define writeBoolean writeBoolean
/* math */
#	define abs    abs
#	define fabs   fabs
#	define sqrt   sqrt
#	define sin    sin
#	define cos    cos
#	define tan    tan
#	define arctan arctan
#	define exp    exp
#	define ln     ln
#	define pi     pi
/* type coersion */
#	define trunc trunc
#	define round round
#	define ord   ord
#	define chr   chr
#elif defined(DANA)
/* I/O */
#	define readChar     readChar
#	define readString   readString
#	define readByte     readByte
#	define readInteger  readInteger
#	define writeChar    writeChar
#	define writeString  writeString
#	define writeByte    writeByte
#	define writeInteger writeInteger
/* type coersion */
#	define extend extend
#	define shrink shrink
/* string manipulation */
#	define strlen strlen
#	define strcmp strcmp
#	define strcpy strcpy
#	define strcat strcat
#else
#	error no supported language selected (-D[LANG])
#endif


