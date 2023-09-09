/*
 * Converts decimal numbers to binary.
 */
#include <iostream>

void PrintBinary(uint32_t n){

	bool first_bit = false;

	for (uint32_t mask_base = 32; mask_base > 0; mask_base--) {
		uint32_t mask = 1 << (mask_base - 1);

		if (n & mask) {
			first_bit = true;
			std::cout << "1";
		}
		else if (first_bit){
			std::cout << "0";
		}
	}
}

int main(){
        uint32_t n = 0;
	std::cin >> n;

	PrintBinary(n);
	return 0;
}
