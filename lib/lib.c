#include <unistd.h>
#include <stdint.h>

#define CAT(x, y, z)  CAT_(x, y, z)
#define CAT_(x, y, z) x ## y ## z

#define trim(c) do (c) = readChar(); while (c == ' ' || c == '\t' || c == '\r' || c == '\n')
#define DIGITS(b) (      \
	(b) == 8  ? 3  : \
	(b) == 16 ? 6  : \
	(b) == 32 ? 9  : \
	(b) == 64 ? 18 : \
-1)

/* -- data types -- */
#include "lang.h"

typedef uint8_t       byte;
#define langint       CAT(int, BITS, _t)
typedef double        real;
typedef uint8_t       boolean;

/* -- I/O primitives -- */
#if defined(readChar)
char readChar (void)
{
    char c;
    read(0, &c, 1);
    return c;
}
#endif

#if defined(readString)
void readString (langint maxLen, char buf[static maxLen])
{
    long i = 0;
    while (i < maxLen - 1)
{
        char c = readChar();
        buf[i] = c;
        if (buf[i] == '\n')
            break;
        i++;
    }
    buf[i] = '\0';
}
#endif

#if defined(char)
unsigned char readByte(void)
{
    byte result = 0;
    char c;

    trim(c);
    for (; c > '/' && c <= '9'; c = readChar())
        result = result * 10 + (c - '0');
    return result;
}
#endif

#if defined(readInteger)
langint readInteger (void)
{
    long value = 0;
    int8_t sign = 1;
    char c;

    trim(c);
    if (c == '-')
        sign = -1, c = readChar();
    for (; c >= '0' && c <= '9'; c = readChar())
        value = value * 10 + (c - '0');

    return sign * value;
}
#endif

#if defined(readBoolean)
boolean readBoolean (void)
{
	char buf[6];
	buf[0] = readChar();
	readString(buf[0] == 't' ? 4 : 5, buf);
	return buf[0] == 't';
}
#endif

#if defined(writeChar)
void writeChar (char c)
{
    write(1, &c, 1);
}
#endif

#if defined(writeString)
void writeString (char *s)
{
    while (*s)
        writeChar(*s++);
}
#endif

#if defined(writeByte)
void writeByte (byte n)
{
    char digits[DIGITS(8)];
    char count = 0;

    if (n == 0)
        return (void) writeChar('0');

    for (; n != 0; n /= 10)
        digits[count++] = n % 10;
    while (count--)
        writeChar(digits[count] + '0');
}
#endif

#if defined(writeInteger)
void writeInteger (langint n)
{
    char digits[DIGITS(BITS)];
    char count = 0;

    if (n < 0)
        writeChar('-'), n = -n;
    else if (n == 0)
        return (void) writeChar('0');

    for (; n != 0; n /= 10)
        digits[count++] = n % 10;
    while (count--)
        writeChar(digits[count] + '0');
}
#endif

#if defined(writeBoolean)
void writeBoolean (boolean b)
{
	if (b) writeString("true");
	else   writeString("false");
}
#endif

/* -- math functions -- */

#if defined(abs)
langint abs (langint n)
{
	return __builtin_labs(n);
}
#endif

#if defined(fabs)
real fabs (real r)
{
	return __builtin_fabs(r);
}
#endif

#if defined(sqrt)
real sqrt (real r)
{
	return __builtin_sqrt(r);
}
#endif

#if defined(sin)
real sin (real r)
{
	return __builtin_sinl(r);
}
#endif

#if defined(cos)
real cos (real r)
{
	return __builtin_cosl(r);
}
#endif

#if defined(tan)
real tan (real r)
{
	return __builtin_tanl(r);
}
#endif

#if defined(arctan)
real arctan (real r)
{
	return __builtin_atanl(r);
}
#endif

#if defined(exp)
real exp (real r)
{
	return __builtin_exp(r);
}
#endif

#if defined(ln)
real ln (real r)
{
	return __builtin_log(r);
}
#endif

#if defined(pi)
real pi (void)
{
	return __builtin_acos(-1.0);
}
#endif


/* -- Type conversion helpers -- */

#if defined(trunc)
langint trunc (real r)
{
	return __builtin_trunc(r);
}
#endif

#if defined(round)
langint round (real r)
{
	return __builtin_llround(r);
}
#endif

#if defined(ord)
langint ord (char c)
{
	return (langint)(c);
}
#endif

#if defined(chr)
char chr (langint n)
{
	return (char)(n);
}
#endif

#if defined(extend)
langint extend (byte b)
{
	return (langint)b;
}
#endif

#if defined(shrink)
byte shrink (langint n)
{
	return (byte)n;
}
#endif

/* -- String manipulation -- */

#if defined(strlen)
long strlen (char *s)
{
    long len = 0;
    while (*s++)
        len++;
    return len;
}
#endif

#if defined(strcmp)
langint strcmp (char *s1, char *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return (byte)*s1 - (byte)*s2;
        s1++;
        s2++;
    }
    return (byte)*s1 - (byte)*s2;
}
#endif

#if defined(strcpy)
void strcpy (char *dst, char *src)
{
    while (*src)
        *dst++ = *src++;
}
#endif

#if defined(strcat)
void strcat (char *dst, char *src)
{
    /* advance dst to its null terminator */
    while (*dst)
        dst++;
    /* append src */
    while (*src)
        *dst++ = *src++;
}
#endif

