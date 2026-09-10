#include "math.hpp"
#include <cmath>

namespace matrix {

Mat4
identity()
{
	Mat4 r;
	for (int i = 0; i < 4; ++i) {
		r.m[i][i] = 1.0f;
	}
	return r;
}

Mat4
translate(const Vec3& v)
{
	Mat4 r = identity();
	r.m[0][3] = v.x;
	r.m[1][3] = v.y;
	r.m[2][3] = v.z;
	return r;
}

Mat4
scale(const Vec3& v)
{

	Mat4 r = identity();
	r.m[0][0] = v.x;
	r.m[1][1] = v.y;
	r.m[2][2] = v.z;
	return r;
}

Mat4
rotate_x(float angle)
{
	Mat4 r = identity();
	float c = std::cos(angle);
	float s = std::sin(angle);

	r.m[1][1] = c;
	r.m[1][2] = -s;
	r.m[2][1] = s;
	r.m[2][2] = c;
	return r;
}

Mat4
rotate_y(float angle)
{
	Mat4 r = identity();
	float c = std::cos(angle);
	float s = std::sin(angle);

	r.m[0][0] = c;
	r.m[0][2] = s;
	r.m[2][0] = -s;
	r.m[2][2] = c;
	return r;
}

Mat4
rotate_z(float angle)
{
	Mat4 r = identity();
	float c = std::cos(angle);
	float s = std::sin(angle);

	r.m[0][0] = c;
	r.m[0][1] = -s;
	r.m[1][0] = s;
	r.m[1][1] = c;
	return r;
}

Mat4
rotate(const Vec3& angle)
{
	return rotate_z(angle.z) * rotate_y(angle.y) * rotate_x(angle.x);
}

Mat4
look_at(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	Vec3 f = vector::normalize(target - eye);
	Vec3 s = vector::normalize(vector::cross(f, up));
	Vec3 u = vector::cross(s, f);

	Mat4 r = identity();
	r.m[0][0] = s.x;
	r.m[0][1] = s.y;
	r.m[0][2] = s.z;
	r.m[1][0] = u.x;
	r.m[1][1] = u.y;
	r.m[1][2] = u.z;
	r.m[2][0] = -f.x;
	r.m[2][1] = -f.y;
	r.m[2][2] = -f.z;

	r.m[0][3] = -vector::dot(s, eye);
	r.m[1][3] = -vector::dot(u, eye);
	r.m[2][3] = vector::dot(f, eye);
	return r;
}

Mat4
perspective(float fov_y, float aspect, float near_z, float far_z)
{
	Mat4 r;
	float tan_half_fov = std::tan(fov_y * .5f);

	r.m[0][0] = 1.f / (aspect * tan_half_fov);
	r.m[1][1] = 1.f / tan_half_fov;
	r.m[2][2] = -(far_z + near_z) / (far_z - near_z);
	r.m[2][3] = -(2.f * far_z * near_z) / (far_z - near_z);
	r.m[3][2] = -1.f;
	return r;
}

}

namespace vector {

float
length(const Vec3& v)
{
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vec3
normalize(const Vec3& v)
{
	float len = length(v);
	return Vec3{ v.x / len, v.y / len, v.z / len };
}

float
dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3
cross(const Vec3& a, const Vec3& b)
{
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};
}

}
