
#include <os.h>



/*
 * Convertit un nombre en chaine de caractére
 */
extern "C" {
	void itoa(char *buf, unsigned long int n, int base)
	{
		unsigned long int tmp;
		int i, j;

		tmp = n;
		i = 0;

		do {
			tmp = n % base;
			buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
		} while (n /= base);
		buf[i--] = 0;

		for (j = 0; j < i; j++, i--) {
			tmp = buf[j];
			buf[j] = buf[i];
			buf[i] = tmp;
		}
	}
}

