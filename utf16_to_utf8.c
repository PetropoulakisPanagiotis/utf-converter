#include <stdio.h>

int main(void){
	unsigned  int ch1 = 0 ,ch2 = 0,ch3 = 0,ch4 = 0;
	unsigned  int code;
	unsigned  int codeh1,codeh2;
	unsigned  int c,b ,b1,b2, a1, a2;
	
	
	
		ch1 = getchar();
		while (ch1 != EOF) {
			code = 0;
			codeh1 = 0;
			c = 0;
			b = 0;
			b1 = 0;
			b2 = 0;
			a1 = 0;
			a2 = 0;
			ch2 = getchar();
			code = (ch1 << 8) | ch2;
			if (!((code >= 0x0000 && code <= 0xD7FF) | (code >= 0xE000 && code <= 0xFFFF))) {
				code = 0;
				ch3 = getchar();
				ch4 = getchar();
				a1 = (ch1 << 8) | ch2;
				a2 = (ch3 << 8) | ch4;
				if ((a1 >= 0xD800 && a1 <= 0xDBFF) & (a2 >= 0xDC00 && a2 <= 0xDFFF)) { // Is a  4 bytes in  Utf-16.
					b1 = a1 - 0xD800;
					b2 = a2 - 0xDC00;
					b = (b1 << 10) | b2;
					c = b + 0x010000;
					code = c;
				}
				else {
					printf("ERROR\n");
				}

			}

			///// now we check code and make it utf-8 

			if (code >= 0x0000 && code <= 0x007F) { // we must make it 1 byte utf-8
				codeh1 |= code;
				putchar(codeh1);
			}
			else if (code >= 0x0080 && code <= 0x07FF) { // we must make it 2 byte utf-8
				codeh1 = (code >> 6) | 0xC0;
				codeh2 = code << 26;
				codeh2 >>= 26;
				codeh2 |= 0x80;
				putchar(codeh1);
				putchar(codeh2);
			}
			else if (code >= 0x0800 && code <= 0xFFFF) {	// we must make it 3 byte utf-8   
				codeh1 = (code >> 12) | 0xE0;
				codeh2 = code << 20;
				codeh2 >>= 26;
				codeh2 |= 0x80;
				putchar(codeh1);
				putchar(codeh2);
				codeh1 = code << 26;
				codeh1 >>= 26;
				codeh1 |= 0x80;
				putchar(codeh1);
			}
			else if (code >= 0x10000 && code <= 0x10FFFF) {	// we must make it 4 byte utf-8		
				codeh1 = (code >> 11);
				codeh1 |= 0xF0;
				codeh2 = code << 14;
				codeh2 >>= 26;
				codeh2 |= 0x80;
				putchar(codeh1);
				putchar(codeh2);
				codeh1 = code << 20;
				codeh1 >>= 26;
				codeh1 |= 0x80;
				codeh2 = code << 26;
				codeh2 >>= 26;
				codeh2 |= 0x80;
				putchar(codeh1);
				putchar(codeh2);
			}

			ch1 = getchar();
			}
  

	return 0;
}
// sdi1500129
// Editor : Panagiotis Petropoulakis
