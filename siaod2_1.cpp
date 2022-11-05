#include <iostream>
#include <bitset>
#include <cstdlib>
#include <string>


void z1_1() {
	setlocale(0, "rus");
	unsigned char x = 255;
	unsigned char maska = 1;
	x = x & (~(maska << 4));
	std::cout << (int)x << std::endl;
}

void z1_2() {
	unsigned long x;
	std::cin >> x;
	std::cout << "X: " << x << std::endl;
	x |= (1 << 24);
	std::cout << "new X: " << x << std::endl;
}

void z1_3() {
	unsigned int x = 25;
	const int n = sizeof(int) * 8; //32
	unsigned maska = (1 << n - 1);
	std::cout << "Начальный вид маски: " << std::bitset<n>(maska) << std::endl;
	std::cout << "Результат: ";
	for (int i = 1; i <= n; ++i) {
		std::cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
	}
	std::cout << std::endl;
}

void z2_1() {
	
}

void z2_2() {

}

void z2_3() {

}

void z3_1() {

}

void z3_2() {

}

void z3_3() {

}

int main() {
	z1_1();
	z1_2();
	z1_3();
}