#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

#include "matrix.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello, Matirix lib samples.\n";

	std::cout << "行列A(3, 3) を定義する(要素は0)\n";
	Matrix A(3, 3);
	A.show();
	std::cout << "\n";

	std::cout << "行列Aを単位行列にする\n";
	A.I();
	A.show();
	std::cout << "\n";

	std::cout << "A(0, 1), A(1, 0) に2を代入する\n";
	A(0, 1) = 2.0;
	A(1, 0) = 2.0;
	A.show();
	std::cout << "\n";

	std::cout << "Aの逆行列を求め，Bとする\n";
	Matrix B = A.inv();
	B.show_gorgeous();
	std::cout << "\n";

	std::cout << "A*Bを計算する．結果は単位行列\n";
	Matrix C = A * B;
	C.show();
	std::cout << "\n";

	std::cout << "A - A, 結果はゼロ行列\n";
	Matrix D = A - A;
	D.show();
	std::cout << "\n";

	std::cout << "A + A\n";
	Matrix E = A + A;
	E.show();
	std::cout << "\n";

	std::cout << "B * (A + A), 結果は対角成分が2の行列\n";
	Matrix F = B * (A + A);
	F.show_gorgeous();
	std::cout << "\n";

	std::cout << "V(3) 三次元ベクトルを定義する\n";
	Matrix V(3);
	for (size_t i = 0; i < V.getRows(); i++) {
		V(i) = 1.0;
	}
	V.show_gorgeous();
	std::cout << "Vの転置(横ベクトル)\n";
	Matrix Vt = V.t();
	Vt(2) = 2.0;
	Vt.show_gorgeous();

	std::cout << "Vt * V 内積(スカラーだが，戻り値は1x1のMatrix型)\n";
	Matrix VVt = Vt * V;
	VVt.show_gorgeous();

	std::cout << "Bye!\n";
	return 0;
}
