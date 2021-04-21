#pragma once
#include <string>
uint8_t char_to_int8(unsigned char a) {
	return uint8_t(int(a));
}
uint16_t char_to_int16(unsigned char a, unsigned char b) {
	return uint16_t((a << 8) | b);
}
uint32_t char_to_long(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
	return uint32_t((int)(a << 24)
		| (int)(b << 16)
		| (int)(c << 8)
		| (int)(d));
}
char getCharPos(unsigned int value, uint8_t Byte) {
	unsigned char buff[4];

	for (int i = 0; i < 4; i++)
	{
		buff[i] = (value & 0xff);
		value >>= 8;
	}
	return buff[Byte];
}
