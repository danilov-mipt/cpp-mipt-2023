/*
 * Converts decimal numbers to hexadecimal.
 */
#include <iostream>

void PrintHex(uint32_t n){
	bool first_hex = false;
	const char chars[17] = "0123456789ABCDEF";

	for (int32_t i = 31 - 3; i >= 0; i -= 4) {
                // Each hex digit is 4 bits, hence 4 bit mask
		uint32_t mask = 0xF << i;
		uint32_t place = (n & mask) >> i;
		if (place){
			std::cout << chars[place];
			first_hex = true;
		}
                // if we get a zero digit
		else if (first_hex){
			std::cout << 0;
		}
	}
	
        // if we get a zero
        // and conditional branches with printing dont execute
	if (n == 0) {
		std::cout << 0;
	}

	std::cout << "\n";
}

int main(){
	uint32_t n = 0;
	std::cin >> n;

	PrintHex(n);
	return 0;
}
