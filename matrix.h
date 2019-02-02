/*******************************************************************
 * 行列演算ライブラリ
 *
 * Jan.31, 2019
 * Kazumichi INOUE <k.inoue@oyama-ct.ac.jp>
 *
 * Usage:
 * 	Matrix A;	// 空の行列の定義
 * 	Matrix B(3, 3); 	// 3x3行列の定義, 要素は0
 * 	A = B.inv(); 		// AにBの逆行列を代入
 * 	Matrix C = A * B;	// 行列の積
 * 	Matrix D(3, 3);
 * 	C = D.I() * A.t() * B + D; 	// D.I()は単位行列，A.t()は転置行列
 *
 * 	Special Thanks
 * 	Kazuharu Nakajima and 1SE Members
 * 	中嶋氏からは参照返し，const 修飾子について極めて重要な貢献があった
 *******************************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

class Matrix
{
	private:
		std::vector<std::vector<double>> m;

		// 行・列の入れ替え
		std::vector<std::vector<double>> pivot_r(std::vector<std::vector<double>> &a, int i, int j);
		std::vector<std::vector<double>> pivot_c(std::vector<std::vector<double>> &a, int i, int j);
		void pivot_c(Matrix &a, int i, int j);

	public:
		Matrix();
		Matrix(int r, int c);
		void resize(int r, int c);

		Matrix I(); 					// 成分を単位行列化
		Matrix t(); 				// 転置
		Matrix inv(); 				// 逆行列

		void show(); 				// 成分の表示

		int getRows();
		int getRows() const;
		int getCols();
		int getCols() const;

		double& operator()(int r, int c);
		const double& operator()(int r, int c) const;
};

Matrix::Matrix()
{
	;
}

Matrix::Matrix(int r, int c)
{
	m.resize(r);
	for (size_t i = 0; i < m.size(); i++) {
		m[i].resize(c);
	}

	for (size_t r = 0; r < m.size(); r++) {
		for (size_t c = 0; c < m[0].size(); c++) {
			m[r][c] = 0.0;
		}
	}
}

void Matrix::resize(int r, int c)
{
	m.resize(r);
	for (size_t i = 0; i < m.size(); i++) {
		m[i].resize(c);
	}

	for (size_t r = 0; r < m.size(); r++) {
		for (size_t c = 0; c < m[0].size(); c++) {
			m[r][c] = 0.0;
		}
	}
}

Matrix Matrix::I()
{
	for (int i = 0; i < getRows(); i++) {
		for (int j = 0; j < getCols(); j++) {
			if (i == j) {
				m[i][j] = 1.0;
			} else {
				m[i][j] = 0.0;
			}
		}
	}
	return *this;
}

Matrix Matrix::t()
{
	Matrix tmp(getCols(), getRows());
	for (int i = 0; i < getRows(); i++) {
		for (int j = 0; j < getCols(); j++) {
			tmp(j, i) = m[i][j];
		}
	}
	return tmp;
}

void Matrix::show()
{
	std::cout << std::fixed;
	for (size_t r = 0; r < m.size(); r++) {
		for (size_t c = 0; c < m[0].size(); c++) {
			std::cout << std::setprecision(2) << m[r][c] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::defaultfloat;
}

const double& Matrix::operator()(int r, int c) const
{
	return m[r][c];
}

double& Matrix::operator()(int r, int c)
{
	return m[r][c];
}


int Matrix::getRows()
{
	return m.size();
}

int Matrix::getRows() const
{
	return m.size();
}

int Matrix::getCols()
{
	return m[0].size();
}

int Matrix::getCols() const
{
	return m[0].size();
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
	int row = A.getRows();
	int col = A.getCols();
	Matrix C(row, col);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			C(r, c) = A(r, c) + B(r, c);
		}
	}
	return C;
}

Matrix operator-(const Matrix &A, const Matrix &B)
{
	int row = A.getRows();
	int col = A.getCols();
	Matrix C(row, col);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			C(r, c) = A(r, c) - B(r, c);
		}
	}
	return C;
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
	// サイズチェック
	int col = A.getCols();
	int row = B.getRows();
	if (row != col) exit(1);

	Matrix C(A.getRows(), B.getCols());
	for (int r = 0; r < A.getRows(); r++) {
		for (int c = 0; c < B.getCols(); c++) {
			for (int k = 0; k < col; k++) {
				C(r, c) += A(r, k) * B(k, c);
				//std::cout << "C("<<r<<","<<c<<")+="<< *(A(r, k)) << "*" << *(B(k,c)) << std::endl;
			}
			//std::cout << std::endl;
		}
	}
	return C;
}

Matrix operator*(const double &k, Matrix &A)
{
	int row = A.getRows();
	int col = A.getCols();
	Matrix C(row, col);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			C(r, c) = A(r, c) * k;
		}
	}
	return C;
}

Matrix operator*(Matrix &A, const double &k)
{
	int row = A.getRows();
	int col = A.getCols();
	Matrix C(row, col);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			C(r, c) = A(r, c) * k;
		}
	}
	return C;
}

std::vector<std::vector<double>> Matrix::pivot_r(std::vector<std::vector<double>> &a, int i, int j)
{
	// i, j行の入れ替え
	for (int k = 0; k < static_cast<int>(a.size()); ++k) {
		double tmp = 0.0;
		tmp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = tmp;
	}
	return a;
}

std::vector<std::vector<double>> Matrix::pivot_c(std::vector<std::vector<double>> &a, int i, int j)
{
	// i, j列の入れ替え
	for (int k = 0; k < static_cast<int>(a.size()); ++k) {
		double tmp = 0.0;
		tmp = a[k][i];
		a[k][i] = a[k][j];
		a[k][j] = tmp;
	}
	return a;
}

void Matrix::pivot_c(Matrix &a, int i, int j)
{
	// i, j列の入れ替え
	for (int k = 0; k < static_cast<int>(a.getRows()); ++k) {
		double tmp = 0.0;
		tmp = a(k,i);
		a(k,i) = a(k,j);
		a(k,j) = tmp;
	}
}

Matrix Matrix::inv()
{
	// m_inv を単位行列とする
	Matrix m_inv(getRows(), getCols());
	m_inv.I();

	// 作業用に元の行列をコピーする
	std::vector<std::vector<double>> tmp;
	tmp = m;

	int nrow = getRows();
	int ncol = getCols();

#if 1
	// 対角要素をチェックし，0がある行は入れ替える
	// 入れ替え情報は(i, j)の組としてデータを保持し，最後に入れ替え操作で戻す
	std::vector<std::vector<int>> pivot;
	for (int k = 0; k < (nrow - 1); ++k) {
		if (fabs(tmp[k][k]) < 1e-5) {
			pivot_r(tmp, k, k + 1);
			pivot.push_back({k, k + 1});
		}
	}

	// デバッグ情報
	if (pivot.size() > 0) {
		std::cout << "入れ替えの行番号のペア" << std::endl;
		for (int i = 0; i < static_cast<int>(pivot.size()); ++i) {
			std::cout << i << "\t" << pivot[i][0] << "\t" << pivot[i][1] << std::endl;
		}
	}
#endif

	for (int i = 0; i < ncol; ++i) {
		// はじめに，対角要素を１にする操作を行に対して行う
		double s = tmp[i][i];
		for (int k = 0; k < ncol; ++k) {
			tmp[i][k] /= s;
			m_inv(i, k) /= s;
		}

		for (int j = 0; j < nrow; ++j) {
			if (i != j) {
				double w = tmp[j][i];
				for (int k = i; k < ncol; ++k) {
					tmp[j][k] -= w * tmp[i][k];
				}
				for (int k = 0; k < ncol; ++k) {
					m_inv(j, k) -= w * m_inv(i, k);
				}
			}
		}

	}

	if (pivot.size() > 0) {
		for (int i = 0; i < static_cast<int>(pivot.size()); ++i) {
			pivot_c(m_inv, pivot[i][0], pivot[i][1]);
		}
	}
	return m_inv;
}

#endif
