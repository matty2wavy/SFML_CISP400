#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;
		a.resize(rows, vector<double>(cols, 0));
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				os << setw(9) << a(i, j) << " ";
			}
			os << endl;
		}
		return os;
	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), b.getCols());
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int k = 0; k < b.getCols(); k++)
			{
				for (int j = 0; j < b.getRows(); j++)
				{
					c(i, k) += a(i, j) * b(j, k);
				}
			}
		}
	}

	bool operator==(const Matrix& a, const Matrix& b)
	{
		bool found = false;
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
		{
			return false;
		}
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < a.getCols(); j++)
			{
				if (fabs(a(i, j) - b(i, j)) < 0.001)
				{
					found = true;
				}
				else
				{
					return false;
				}
			}
		}
		if (found == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		return !(a == b);
	}

	RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
	{
		///Call the parent constructor to create a 2x2 matrix
		///Then assign each element as follows:
			/*
			cos(theta)  -sin(theta)
			sin(theta)   cos(theta)
			*/
		///theta represents the angle of rotation in radians, counter-clockwise
		(*this)(0, 0) = cos(theta);
		(*this)(0, 1) = -sin(theta);
		(*this)(1, 0) = sin(theta);
		(*this)(1, 1) = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
	{
		///Call the parent constructor to create a 2x2 matrix
			///Then assign each element as follows:
			/*
			scale   0
			0       scale
			*/
		///scale represents the size multiplier
		(*this)(0, 0) = scale;
		(*this)(1, 1) = scale;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix (2, nCols)
	{
		///Call the parent constructor to create a 2xn matrix
			///Then assign each element as follows:
			/*
			xShift  xShift  xShift  ...
			yShift  yShift  yShift  ...
			*/
			///paramaters are xShift, yShift, and nCols
			///nCols represents the number of columns in the matrix
			///where each column contains one (x,y) coordinate pair
		for (int i = 0; i < nCols; i++)
		{
			(*this)(0, i) = xShift;
			(*this)(1, i) = yShift;
		}
	}


}