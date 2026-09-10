#pragma once

struct Vec2
{
	float x = 0;
	float y = 0;
};

struct Vec2i
{
	int x = 0;
	int y = 0;
};

struct Vec3
{
	float x = 0;
	float y = 0;
	float z = 0;
};

inline Vec3
operator-(const Vec3& v)
{
	return { -v.x, -v.y, -v.z };
}

inline Vec3
operator+(const Vec3& a, const Vec3& b)
{
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline Vec3
operator-(const Vec3& a, const Vec3& b)
{
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vec3
operator*(const Vec3& a, const Vec3& b)
{
	return { a.x * b.x, a.y * b.y, a.z * b.z };
}

inline Vec3
operator*(const Vec3& a, float x)
{
	return a * Vec3{ x, x, x };
}

inline Vec3
operator/(const Vec3& a, const Vec3& b)
{
	return { a.x / b.x, a.y / b.y, a.z / b.z };
}

inline Vec3
operator/(const Vec3& a, float x)
{
	return a / Vec3{ x, x, x };
}

inline Vec3&
operator+=(Vec3& a, const Vec3& b)
{
	a = a + b;
	return a;
}

inline Vec3&
operator-=(Vec3& a, const Vec3& b)
{
	a = a - b;
	return a;
}

inline Vec3&
operator*=(Vec3& a, const Vec3& b)
{
	a = a * b;
	return a;
}

inline Vec3&
operator*=(Vec3& a, float b)
{
	a = a * b;
	return a;
}

inline Vec3&
operator/=(Vec3& a, const Vec3& b)
{
	a = a / b;
	return a;
}

inline Vec3&
operator/=(Vec3& a, float b)
{
	a = a / b;
	return a;
}

struct Vec4
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
};

struct Mat4
{
	float m[4][4] = {};
};

inline Mat4
operator*(const Mat4& a, const Mat4& b)
{
	Mat4 r;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				r.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}

	return r;
}

inline Vec4
operator*(const Mat4& m, const Vec4& v)
{
	return Vec4{
		m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w,
		m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w,
		m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w,
		m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w,
	};
}

namespace matrix {

Mat4
identity();
Mat4
translate(const Vec3& v);
Mat4
scale(const Vec3& v);
Mat4
rotate_x(float angle);
Mat4
rotate_y(float angle);
Mat4
rotate_z(float angle);
Mat4
rotate(const Vec3& angle);
Mat4
look_at(const Vec3& eye, const Vec3& target, const Vec3& up);
Mat4
perspective(float fov_y, float aspect, float near_z, float far_z);

}

namespace vector {

float
length(const Vec3& v);
Vec3
normalize(const Vec3& v);
float
dot(const Vec3& a, const Vec3& b);
Vec3
cross(const Vec3& a, const Vec3& b);

}
