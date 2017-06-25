#include "Matrix.h"
#include "Exception.h"

int main(int argc, char *argv[])
{
	// Exemplos de uso da classe de Matrizes
	try
	{
		// cria uma matriz inicial (matriz identidade)
		int cols = 3;
		int rows = 3;
		Matrix A = Matrix(cols, rows);
		cout << "Matriz A inicial (identidade) " << endl;
		A.Print();
		cout << endl;

		// adiciona valores quaisquer na matriz A
		int count = 0;
		for (int r = 1; r <= rows; r++)
		{
			for (int c = 1; c <= cols; c++)
			{
				count++;
				A(r, c) = count;
			}
		}
		cout << "Matriz A com valores " << endl;
		A.Print();
		cout << endl;

		// ajusta um valor específico da Matriz A
		A(2, 1) = 1.23;
		cout << "Matriz A com valor A(2,1) " << endl;
		A.Print();
		cout << endl;

		// lendo um valor da matriz A
		float centervalue = A(2, 2);
		cout << "valor do centro = " << centervalue << endl;
		cout << endl;

		// criando uma matriz B
		Matrix B = Ones(rows, cols) + Diag(rows);
		cout << "B = " << endl;
		B.Print();
		cout << endl;

		// criando uma matriz B2 com apenas 1 coluna
		Matrix B2 = Matrix(rows, 1);   
		count = 1;
		for (int r = 1; r <= rows; r++)
		{
			count++;
			B2(r, 1) = count * 2;
		}
		cout << "B2 = " << endl ;
		B2.Print();
		cout << endl;

		// criando uma matriz C que será a soma de A + B
		Matrix C;
		C = A + B;
		cout << "A + B = " << endl;
		C.Print();
		cout << endl;

		// fazendo C ser agora a subtração de A - B
		C = A - B;
		cout << "A - B = " << endl;
		C.Print();
		cout << endl;

		// fazendo C ser agora a multiplicação de A * B2
		C = A * B2;
		cout << "A * B2 = " << endl;
		C.Print();
		cout << endl;

		// criando uma matriz diagonal E
		Matrix E = Diag(B2);
		cout << "E = " << endl;
		E.Print();
		cout << endl;

		// Calculando o Determinante de uma Matriz 2x2 D
		Matrix D = Matrix(2, 2);
		D(1, 1) = 2;
		D(1, 2) = 4;
		D(2, 1) = 1;
		D(2, 2) = -2;
		cout << "D = " << endl;
		D.Print();
		cout << "Det(D) = " << Det(D) << endl << endl;

		// Calculando o Determinante da Matriz A
		cout << "A = " << endl;
		A.Print();
		cout << endl;
		cout << "Det(A) = " << Det(A) << endl << endl;

		// Calculando um valor menos uma Matriz
		Matrix F;
		F = 3 - A;
		cout << "3 - A = " << endl;
		F.Print();
		cout << endl;

		// Calculando a inversa de uma Matriz G 2x2
		Matrix G = Matrix(2, 2);
		G(1, 1) = 1;
		G(1, 2) = 2;
		G(2, 1) = 3;
		G(2, 2) = 4;
		cout << "G = " << endl;
		G.Print();
		cout << endl;
		Matrix G_inv = Inv(G);
		cout << "Inv(G) = " << endl;
		G_inv.Print();
		cout << endl;

		// Calculando a inversa da Matriz A
		A.Print();
		cout << endl;
		Matrix A_inv = Inv(A);
		cout << "Inv(A) = " << endl;
		A_inv.Print();
		cout << endl;

		// Matriz A * Inv(A)
		Matrix A_A_inv = A * Inv(A);
		cout << "A * Inv(A) = " << endl;
		A_A_inv.Print();
		cout << endl;

		// Matriz B / A;
		Matrix B_A = B / A;
		cout << "B / A = " << endl;
		B_A.Print();
		cout << endl;

		// Matriz A / 3;
		Matrix A_3 = A / 3;
		cout << "A / 3 = " << endl;
		A_3.Print();
		cout << endl;

		// criando uma Matriz H 2x5
		rows = 2;
		cols = 5;
		Matrix H = Matrix(rows, cols);
		for (int r = 1; r <= rows; r++)
		{
			for (int c = 1; c <= cols; c++)
			{
				count++;
				H(r, c) = count;
			}
		}
		cout << "H = " << endl;
		H.Print();
		cout << endl;

		// criando uma Matriz transposta de H, a matriz W
		Matrix W = Transposed(H);
		cout << "W = translated" << endl;
		W.Print();
		cout << endl;

		// criando uma Matriz Y e acessando seus valores pelos métodos diretos de uma matriz 3x3
		rows = 3;
		cols = 3;
		Matrix Y = Matrix(rows, cols);

		cout << "Y = rows x coluns directed" << endl;
		cout << "a : " << Y.a() << " ";
		cout << "b : " << Y.b() << " ";
		cout << "c : " << Y.c() << endl;
		cout << "d : " << Y.d() << " ";
		cout << "e : " << Y.e() << " ";
		cout << "f : " << Y.f() << endl;
		cout << "g : " << Y.g() << " ";
		cout << "h : " << Y.h() << " ";
		cout << "k : " << Y.k() << endl;
		cout << endl;

        // teste de multiplicação de matrizes quadradas 2x2		  
		Matrix a1 = Matrix(2, 2);
		Matrix a2 = Matrix(2, 2);
		a1(1, 1) = 34;
		a1(1, 2) = 35;
		a1(2, 1) = 36;
		a1(2, 2) = 37;
		cout << "a1 = " << endl;
		a1.Print();
		cout << endl;
		a2(1, 1) = 34;
		a2(1, 2) = 35;
		a2(2, 1) = 36;
		a2(2, 2) = 37;
		cout << "a2 = " << endl;
		a2.Print();
		cout << endl;

		a1 = a1*a2;
		cout << "a1 * a2 = " << endl;
		a1.Print();
		cout << endl;

		// criando uma matriz TT 3x3 para calcular matrizes de transformação
		rows = 3;
		cols = 3;
		Matrix TT = Matrix(rows, cols);

		// Escala 2,2
		TT = Scale3X3(TT, 2, 2);
		cout << "TT = Scale3X3 de SX=2 e SY=2" << endl;
		TT.Print();
		cout << endl;

        // Rotação 90 graus
		TT = Rotate3X3(TT, (90*3.14 / 180));
		cout << "TT = Rotate3X3 90 graus" << endl;
		TT.Print();
		cout << endl;

		// Transladação de X=15 e Y=-5
		TT = Translate3X3(TT, 15, -5);
		cout << "TT = Translate3X3" << endl;
		TT.Print();
		cout << endl;

		// Matriz de Transformação para os pontos X=0 e Y=0
		TT = Transform(TT, 0,0);
		cout << "TT = Transformed (0,0)" << endl;
		TT.Print();
		cout << endl;

	}
	catch (Exception err)
	{
		cout << "ERRO: " << err.msg << endl;
	}
	catch (...)
	{
		cout << "Ocorreu um erro..." << endl;
	}

	cout << endl;

	system("pause");

	return EXIT_SUCCESS;
}
