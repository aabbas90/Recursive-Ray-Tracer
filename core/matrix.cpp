#include <core/matrix.h>

namespace rt {
	Matrix::Matrix(const Float4 & r1, const Float4 & r2, const Float4 & r3, const Float4 & r4)
	{
		this->r1 = r1;
		this->r2 = r2;
		this->r3 = r3;
		this->r4 = r4;
	}

	Float4 & Matrix::operator[](int idx)
	{
		switch (idx)
		{
		case 0:
			return this->r1;
		case 1:
			return this->r2;
		case 2:
			return this->r3;
		case 3:
			return this->r4;
		default:
			break;
		}
	}

	Float4 Matrix::operator[](int idx) const
	{
		switch (idx)
		{
		case 0:
			return this->r1;
		case 1:
			return this->r2;
		case 2:
			return this->r3;
		case 3:
			return this->r4;
		default:
			break;
		}
	}

	Matrix Matrix::operator+(const Matrix & b) const
	{
		return Matrix(this->r1 + b.r1, this->r2 + b.r2, this->r3 + b.r3, this->r4 + b.r4);
	}

	Matrix Matrix::operator-(const Matrix & b) const
	{
		return Matrix(this->r1 - b.r1, this->r2 - b.r2, this->r3 - b.r3, this->r4 - b.r4);
	}

	Matrix Matrix::transpose() const
	{
		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			for (int colIndex = rowIndex + 1; colIndex < 4; colIndex++)
			{
				if (rowIndex == colIndex)
					continue;
				
				float originalValue = this->operator[](rowIndex).operator[](colIndex);
				this->operator[](rowIndex).operator[](colIndex) = this->operator[](colIndex).operator[](rowIndex);
				this->operator[](colIndex).operator[](rowIndex) = originalValue;
			}
		}
		return *this;
	}

	Matrix Matrix::invert() const {
		Matrix result;
		const Matrix& m = *this;

		//Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
		result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
		result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
		result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
		result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

		float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
		if (det == 0)
			return Matrix::zero();

		result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
		result[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
		result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
		result[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
		result[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
		result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
		result[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
		result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
		result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
		result[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
		result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
		result[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

		result = result*(1.0f / det);
		return result;
	}

	bool Matrix::operator==(const Matrix & b) const
	{
		return this->r1 == b.r1 &&
			   this->r2 == b.r2 &&
			   this->r3 == b.r3 &&
			   this->r4 == b.r4;
	}

	bool Matrix::operator!=(const Matrix & b) const
	{
		return !(*this == b);
	}

	Float4 Matrix::operator*(const Float4 & b) const
	{
		return Float4(dot(this->r1, b),
					  dot(this->r2, b),
					  dot(this->r3, b),
					  dot(this->r4, b));

	}

	//Vector Matrix::operator*(const Vector & b) const
	//{
	//	return Vector();
	//}

	Matrix Matrix::zero()
	{
		return Matrix(Float4(0, 0, 0, 0), 
			  		  Float4(0, 0, 0, 0), 
					  Float4(0, 0, 0, 0), 
					  Float4(0, 0, 0, 0));
	}

	Matrix Matrix::identity()
	{
		return Matrix(Float4(1, 0, 0, 0),
					  Float4(0, 1, 0, 0),
					  Float4(0, 0, 1, 0),
					  Float4(0, 0, 0, 1));
	}

	Matrix product(const Matrix & a, const Matrix & b)
	{
		Matrix output;
		for (int outputRowIndex = 0; outputRowIndex < 4; outputRowIndex++)
		{
			for (int outputColumnIndex = 0; outputColumnIndex < 4; outputColumnIndex++)
			{
				output[outputRowIndex][outputColumnIndex] = dot(a[outputRowIndex], b[outputColumnIndex]);
			}
		}
	}

	Matrix operator*(const Matrix & a, float scalar)
	{
		return Matrix(a.r1 * scalar, a.r2 * scalar, a.r3 * scalar, a.r4 * scalar);
	}

	Matrix operator*(float scalar, const Matrix & a)
	{
		return Matrix(a * scalar);
	}

}

