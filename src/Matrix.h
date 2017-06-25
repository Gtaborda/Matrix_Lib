#pragma once
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>
#include "Exception.h"

using namespace std;

// Declara��es
class Matrix;
float Det(const Matrix& a);
Matrix Diag(const int n);
Matrix Diag(const Matrix& v);
Matrix Inv(const Matrix& a);
Matrix Ones(const int rows, const int cols);
int Size(const Matrix& a, const int i);
Matrix Zeros(const int rows, const int cols);
Matrix Transposed(const Matrix& a);
Matrix Translate3X3(const Matrix& a, const float X, const float Y);
Matrix Scale3X3 (const Matrix& a, const float SX, const float SY);
Matrix Rotate3X3(const Matrix& a, const float degrees);
Matrix Transform(const Matrix&, const float X, const float Y);

class Matrix
{
public:
	// constructor
	Matrix()
	{
		// cria um objeto Matriz sem conte�do
		p = NULL;
		rows = 0;
		cols = 0;
	}

	// constructor (por default criar uma matriz identidade)
	Matrix(const int row_count, const int column_count)
	{
		// cria um objeto Matriz com um n�mero dado de linhas e colunas
		p = NULL;

		if (row_count > 0 && column_count > 0)
		{
			rows = row_count;
			cols = column_count;

			p = new float*[rows];
			for (int r = 0; r < rows; r++)
			{
				p[r] = new float[cols];

				// inicialmente preenche com zeros todos os campos da matriz
				for (int c = 0; c < cols; c++)
				{
					if (r == c)
						p[r][c] = 1;
					else
					    p[r][c] = 0;
				}
			}
		}
	}

	// operador de atribui��o
	Matrix(const Matrix& a)
	{
		rows = a.rows;
		cols = a.cols;
		p = new float*[a.rows];
		for (int r = 0; r < a.rows; r++)
		{
			p[r] = new float[a.cols];

			// copia os valores da matriz a
			for (int c = 0; c < a.cols; c++)
			{
				p[r][c] = a.p[r][c];
			}
		}
	}

	// operador de �ndice. voc� pode usar a classe como minhaMatriz(linha, coluna)
	// os �ndices s�o baseados em 1 e n�o em zero
	float& operator()(const int r, const int c)
	{
		if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
		{
			return p[r - 1][c - 1];
		}
		else
		{
			throw Exception("Indice fora do intervalo");
		}
	}

	// operador de indice myMatrix.get(row, col)
	// os indices s�o baseados (iniciados) com 1 e n�o com zero
	// use essa fun��o se quiser ler de uma matriz const
	float get(const int r, const int c) const
	{
		if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
		{
			return p[r - 1][c - 1];
		}
		else
		{
			throw Exception("Indice fora do intervalo");
		}
	}

	// operador de atribui��o
	Matrix& operator= (const Matrix& a)
	{
		rows = a.rows;
		cols = a.cols;
		p = new float*[a.rows];
		for (int r = 0; r < a.rows; r++)
		{
			p[r] = new float[a.cols];

			// copy the values from the matrix a
			for (int c = 0; c < a.cols; c++)
			{
				p[r][c] = a.p[r][c];
			}
		}
		return *this;
	}

	// adiciona um valor float
	Matrix& Add(const float v)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				p[r][c] += v;
			}
		}
		return *this;
	}

	// subtrai um valor float
	Matrix& Subtract(const float v)
	{
		return Add(-v);
	}

	// multiplica um valor float
	Matrix& Multiply(const float v)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				p[r][c] *= v;
			}
		}
		return *this;
	}

	// divide um valor float
	Matrix& Divide(const float v)
	{
		return Multiply(1 / v);
	}

	// adi��o de matrizes
	friend Matrix operator+(const Matrix& a, const Matrix& b)
	{
		// verifica se as dimens�es batem
		if (a.rows == b.rows && a.cols == b.cols)
		{
			Matrix res(a.rows, a.cols);

			for (int r = 0; r < a.rows; r++)
			{
				for (int c = 0; c < a.cols; c++)
				{
					res.p[r][c] = a.p[r][c] + b.p[r][c];
				}
			}
			return res;
		}
		else
		{
			// erro
			throw Exception("ERRO: as dimensoes sao diferentes");
		}
	}

	// adi��o de matriz com um float
	friend Matrix operator+ (const Matrix& a, const float b)
	{
		Matrix res = a;
		res.Add(b);
		return res;
	}
	// adi��o de float com uma matriz
	friend Matrix operator+ (const float b, const Matrix& a)
	{
		Matrix res = a;
		res.Add(b);
		return res;
	}

	// subtra��o de matrizes
	friend Matrix operator- (const Matrix& a, const Matrix& b)
	{
		// verifica se as dimens�es batem
		if (a.rows == b.rows && a.cols == b.cols)
		{
			Matrix res(a.rows, a.cols);

			for (int r = 0; r < a.rows; r++)
			{
				for (int c = 0; c < a.cols; c++)
				{
					res.p[r][c] = a.p[r][c] - b.p[r][c];
				}
			}
			return res;
		}
		else
		{
			// erro
			throw Exception("ERRO: as dimensoes sao diferentes");
		}
	}

	// subtra��o de matriz com float
	friend Matrix operator- (const Matrix& a, const float b)
	{
		Matrix res = a;
		res.Subtract(b);
		return res;
	}
	// subtra��o de float com matriz
	friend Matrix operator- (const float b, const Matrix& a)
	{
		Matrix res = -a;
		res.Add(b);
		return res;
	}

	// operador unin�rio menos
	friend Matrix operator- (const Matrix& a)
	{
		Matrix res(a.rows, a.cols);

		for (int r = 0; r < a.rows; r++)
		{
			for (int c = 0; c < a.cols; c++)
			{
				res.p[r][c] = -a.p[r][c];
			}
		}
		return res;
	}

	// operador multiplica��o
	friend Matrix operator* (const Matrix& a, const Matrix& b)
	{
		// verifica se as dimens�es batem
		if (a.cols == b.rows)
		{
			Matrix res(a.rows, b.cols);

			for (int r = 0; r < a.rows; r++)
			{
				for (int c_res = 0; c_res < b.cols; c_res++)
				{
					res.p[r][c_res] = 0;
					for (int c = 0; c < a.cols; c++)
					{
						res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
					}
				}
			}
			return res;
		}
		else
		{
			// erro
			throw Exception("ERRO: as dimensoes sao diferentes");
		}
	}

	// multiplica��o de matriz com um float
	friend Matrix operator* (const Matrix& a, const float b)
	{
		Matrix res = a;
		res.Multiply(b);
		return res;
	}
	// multiplica��o de um float com uma matriz
	friend Matrix operator* (const float b, const Matrix& a)
	{
		Matrix res = a;
		res.Multiply(b);
		return res;
	}

	// divis�o de uma matriz com outra matriz
	friend Matrix operator/ (const Matrix& a, const Matrix& b)
	{
		// verifica se as dimens�es batem
		if (a.rows == a.cols && a.rows == a.cols && b.rows == b.cols)
		{
			Matrix res(a.rows, a.cols);

			res = a * Inv(b);

			return res;
		}
		else
		{
			// erro
			throw Exception("ERRO: as dimensoes sao diferentes");
		}
	}

	// divis�o de uma matriz com float
	friend Matrix operator/ (const Matrix& a, const float b)
	{
		Matrix res = a;
		res.Divide(b);
		return res;
	}
	// divis�o de um float com uma matriz
	friend Matrix operator/ (const float b, const Matrix& a)
	{
		Matrix b_matrix(1, 1);
		b_matrix(1, 1) = b;

		Matrix res = b_matrix / a;
		return res;
	}

	/**
	* retorna o Menor de uma Matriz (c�lculo de co-fatores retirando uma linha e uma coluna)
	* determinantes de uma matriz quadrada
	*/
	Matrix Minor(const int row, const int col) const
	{
		Matrix res;
		if (row > 0 && row <= rows && col > 0 && col <= cols)
		{
			res = Matrix(rows - 1, cols - 1);

			// copia o conte�do da matriz para o menor, exceto o que foi selecionado
			for (int r = 1; r <= (rows - (row >= rows)); r++)
			{
				for (int c = 1; c <= (cols - (col >= cols)); c++)
				{
					res(r - (r > row), c - (c > col)) = p[r - 1][c - 1];
				}
			}
		}
		else
		{
			throw Exception("ERRO: indice do menor fora do intervalo");
		}

		return res;
	}

	/*
	* retorna a dimens�o da matriz
	* para i=1 retorna o n�mero de linhas
	* para i-2 retorna o n�mero de colunas
	* sen�o retorna 0
	*/
	int Size(const int i) const
	{
		if (i == 1)
		{
			return rows;
		}
		else if (i == 2)
		{
			return cols;
		}
		return 0;
	}

	// retorna o n�mero de linhas
	int GetRows() const
	{
		return rows;
	}

	// retorna o n�mero de colunas
	int GetCols() const
	{
		return cols;
	}

	// imprime o cont�udo da matriz
	void Print() const
	{
		if (p != NULL)
		{
			cout << "[";
			for (int r = 0; r < rows; r++)
			{
				if (r > 0)
				{
					cout << " ";
				}
				for (int c = 0; c < cols - 1; c++)
				{
					cout << p[r][c] << " ";
				}
				if (r < rows - 1)
				{
					cout << p[r][cols - 1] << endl;
				}
				else
				{
					cout << p[r][cols - 1] << "]" << endl;
				}
			}
		}
		else
		{
			// matriz vazia
			cout << "[ ]" << endl;
		}
	}

	// m�todo a para uma matrix 3x3
	float a() const
	{
		return get(1,1);
	}

	// m�todo b para uma matrix 3x3
	float b() const
	{
		return get(1, 2);
	}

	// m�todo c para uma matrix 3x3
	float c() const
	{
		return get(1, 3);
	}

	// m�todo d para uma matrix 3x3
	float d() const
	{
		return get(2, 1);
	}

	// m�todo e para uma matrix 3x3
	float e() const
	{
		return get(2, 2);
	}

	// m�todo f para uma matrix 3x3
	float f() const
	{
		return get(2, 3);
	}

	// m�todo g para uma matrix 3x3
	float g() const
	{
		return get(3, 1);
	}

	// m�todo h para uma matrix 3x3
	float h() const
	{
		return get(3, 2);
	}

	// m�todo k para uma matrix 3x3
	float k() const
	{
		return get(3, 3);
	}

public:
	// destructor
	~Matrix()
	{
		// limpar mem�ria alocada
		for (int r = 0; r < rows; r++)
		{
			delete p[r];
		}
		delete p;
		p = NULL;
	}

private:
	int rows;
	int cols;
	float** p;
};
