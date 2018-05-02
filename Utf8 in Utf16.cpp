#include <stdio.h>

int main(void) {

	unsigned   int ch1 = 0, ch2 = 0, ch3 = 0, ch4 = 0;
	unsigned   int code = 0;
	unsigned   int codeh1 = 0, codeh2 = 0;
	unsigned   int c = 0, b = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;

	ch1 = getchar();
	while (ch1 != EOF) {

		if ((ch1 >> 7) == 0b0) { // We are in 1 bytes to take normall code form Utf-8. -->0xxxxxxx 
			ch1 = ch1 << 1;
			ch1 >>= 1;
			code = ch1;

		}
		else if ((ch1 >> 5) == 0b110) { // We are in 2 bytes to take normall code form Utf-8. --> 110xxxxx,10xxxxxx
			ch1 <<= 27;
			ch1 >>= 27;
			ch2 = getchar();
			ch2 <<= 26;
			ch2 >>= 26;
			code = (ch1 << 6) | ch2;

		}
		else if ((ch1 >> 4) == 0b1110) { // We are in 3 bytes to take normall code form Utf-8. --> 1110xxxx,10xxxxxx,10xxxxxx 
			ch1 <<= 28;
			ch1 >>= 28;
			ch2 = getchar();
			ch2 <<= 26;
			ch2 >>= 26;
			ch3 = getchar();
			ch3 <<= 26;
			ch3 >>= 26;
			code = (ch1 << 12) | (ch2 << 6) | ch3;

		}
		else if ((ch1 >> 3) == 0b11110) { // We are in 4 bytes to take normall code form Utf-8. --> 11110xxx,10xxxxxx,10xxxxxx,10xxxxxx
			ch1 <<= 29;
			ch1 >>= 29;
			ch2 = getchar();
			ch2 <<= 26;
			ch2 >>= 26;
			ch3 = getchar();
			ch3 <<= 26;
			ch3 >>= 26;
			ch4 = getchar();
			ch4 <<= 26;
			ch4 >>= 26;
			code = (ch1 << 18) | (ch2 << 12) | (ch3 << 6) | ch4;

		}
		else { // we are not given right Utf-8 code.
			printf("ERROR\n");
			return 1;
		}

		if ((code >= 0x0000 && code <= 0xD7FF) || (code >= 0xE000 && code <= 0xFFFF)) { // We have a code up tp 2 bytes to make it  in Utf-16.
			if (code <= 0x007F) { // We have  up to 7 digit code.
				codeh1 = 0;
				putchar(codeh1);
				codeh2 = code;
				putchar(codeh2);
			}

			else if (code >= 0x0080 && code <= 0x07FF) { // We have up to 11 digit code.
				codeh1 = code >> 8;
				putchar(codeh1);
				codeh2 = code << 24;
				codeh2 >>= 24;
				putchar(codeh2);

			}
			else if (code >= 0x0800 && code <= 0xFFFF) { // We have up to 16 digit code.
				codeh1 = code >> 8;
				putchar(codeh1);
				codeh2 = code << 24;
				codeh2 >>= 24;
				putchar(codeh2);
			}
		}
		else { // We have a code 4 bytes to make it  in Utf-16.
			c = code;
			b = c - 0x010000;
			b1 = b >> 10;
			b2 = b << 22;
			b2 >>= 22;
			a1 = b1 + 0xD800;
			a2 = b2 + 0xDC00;
			codeh1 = a1 >> 8;
			putchar(codeh1);
			codeh2 = a1 << 24;
			codeh2 >>= 24;
			putchar(codeh2);
			codeh1 = a2 >> 8;
			putchar(codeh1);
			codeh2 = a2 << 24;
			codeh2 >>= 24;
			putchar(codeh2);

		}
		ch1 = getchar(); //For our next loop.
	} // We have finished file convert  if not return 1;

	return 0;
}
// sdi1500129
// Editor : Panagiotis Petropoulakis