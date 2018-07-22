#include <core/matrix.h>
#include<core/assert.h>
#include<math.h>
#include<core/scalar.h>

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
			return this->r1;
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
			return this->r1;
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
		Matrix result;

		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			for (int colIndex = 0; colIndex < 4; colIndex++)
			{
				result[rowIndex][colIndex] = (*this)[colIndex][rowIndex];
			}
		}
		return result;
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

	Vector Matrix::operator*(const Vector & b) const
	{
		return Vector(this->operator*(Float4(b)));
	}

	Point Matrix::operator*(const Point & b) const
	{
		return Point(this->operator*(Float4(b)));
	}

	float Matrix::det() const
	{
		Matrix result;
		const Matrix& m = *this;

		//Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
		result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
		result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
		result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
		result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

		return m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
	}

	Matrix Matrix::zero()
	{
		return Matrix(Float4(0.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	Matrix Matrix::identity()
	{
		return Matrix(Float4(1.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 1.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 1.0f, 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	Matrix Matrix::system(const Vector & e1, const Vector & e2, const Vector & e3)
	{
		Float4 row1(e1.x, e2.x, e3.x, 0);
		Float4 row2(e1.y, e2.y, e3.y, 0);
		Float4 row3(e1.z, e2.z, e3.z, 0);
		Float4 row4(0, 0, 0, 1);
		return Matrix(row1, row2, row3, row4);
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
		return output;
	}

	Matrix operator*(const Matrix & a, float scalar)
	{
		return Matrix(a.r1 * scalar, a.r2 * scalar, a.r3 * scalar, a.r4 * scalar);
	}

	Matrix operator*(float scalar, const Matrix & a)
	{
		return a * scalar;
	}

	Matrix translation(Point& t)
	{
		return Matrix(Float4(1.0f, 0.0f, 0.0f, t.x),
			Float4(0.0f, 1.0f, 0.0f, t.y),
			Float4(0.0f, 0.0f, 1.0f, t.z),
			Float4(0.0f, 0.0f, 0.0f, 1.0f));
	}


	Matrix getRotationAboutX(float angle)
	{
		return Matrix(
			Float4(1.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, cos(angle), -sin(angle), 0.0f),
			Float4(0.0f, sin(angle), cos(angle), 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	Matrix getRotationAboutY(float angle)
	{
		return Matrix(
			Float4(cos(angle), 0.0f, sin(angle), 0.0f),
			Float4(0.0f, 1.0f, 0.0f, 0.0f),
			Float4(-sin(angle), 0.0f, cos(angle), 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	Matrix getRotationAboutZ(float angle)
	{
		return Matrix(
			Float4(cos(angle), -sin(angle), 0.0f, 0.0f),
			Float4(sin(angle), cos(angle), 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 1.0f, 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 1.0f));
	}
	Matrix getRotationMatrix(float angleX, float angleY, float angleZ)
	{
		Matrix xMatrix = getRotationAboutX(angleX * 2 * pi / 360);
		Matrix yMatrix = getRotationAboutY(-angleY * 2 * pi / 360);
		Matrix zMatrix = getRotationAboutZ(-angleZ * 2 * pi / 360);

		return product(product(xMatrix, yMatrix), zMatrix);
	}

}

