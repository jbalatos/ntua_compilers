#include <unistd.h>
#include <stdint.h>

#if !defined(BITS)
#	error no integer bit width provided
#endif

#define CAT(x, y, z)  CAT_(x, y, z)
#define CAT_(x, y, z) x ## y ## z

typedef uint8_t       byte;
#define langint       CAT(int, BITS, _t)
typedef double        real;
typedef uint8_t       boolean;

#define trim(c) do (c) = readChar(); while (c == ' ' || c == '\t' || c == '\r' || c == '\n')
#define DIGITS(b) (      \
	(b) == 8  ? 3  : \
	(b) == 16 ? 6  : \
	(b) == 32 ? 9  : \
	(b) == 64 ? 18 : \
-1)

/* -- I/O primitives -- */
char readChar (void)
{
    char c;
    read(0, &c, 1);
    return c;
}

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

unsigned char readByte(void)
{
    byte result = 0;
    char c;

    trim(c);
    for (; c > '/' && c <= '9'; c = readChar())
        result = result * 10 + (c - '0');
    return result;
}

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

boolean readBoolean (void)
{
	char buf[6];
	buf[0] = readChar();
	readString(buf[0] == 't' ? 4 : 5, buf);
	return buf[0] == 't';
}

void writeChar (char c)
{
    write(1, &c, 1);
}

void writeString (char *s)
{
    while (*s)
        writeChar(*s++);
}

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

void writeBoolean (boolean b)
{
	if (b) writeString("true");
	else   writeString("false");
}

/* -- math functions -- */

langint abs (langint n)
{
	return __builtin_labs(n);
}

real fabs (real r)
{
	return __builtin_fabs(r);
}

real sqrt (real r)
{
	return __builtin_sqrt(r);
}

real sin (real r)
{
	return __builtin_sinl(r);
}

real cos (real r)
{
	return __builtin_cosl(r);
}

real tan (real r)
{
	return __builtin_tanl(r);
}

real arctan (real r)
{
	return __builtin_atanl(r);
}

real exp (real r)
{
	return __builtin_exp(r);
}

real ln (real r)
{
	return __builtin_log(r);
}

real pi (void)
{
	return __builtin_acos(-1.0);
}


/* -- Type conversion helpers -- */

langint trunc (real r)
{
	return __builtin_trunc(r);
}

langint round (real r)
{
	return __builtin_llround(r);
}

langint ord (char c)
{
	return (langint)(c);
}

char chr (langint n)
{
	return (char)(n);
}

/* -- String manipulation -- */

long strlen(char *s)
{
    long len = 0;
    while (*s++)
        len++;
    return len;
}

langint strcmp(char *s1, char *s2)
{
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return (byte)*s1 - (byte)*s2;
        s1++;
        s2++;
    }
    return (byte)*s1 - (byte)*s2;
}

void strcpy(char *dst, char *src)
{
    while (*src)
        *dst++ = *src++;
}

void strcat(char *dst, char *src)
{
    /* advance dst to its null terminator */
    while (*dst)
        dst++;
    /* append src */
    while (*src)
        *dst++ = *src++;
}

