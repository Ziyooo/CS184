// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include<cstdio>
#include<iostream>
using namespace std;
// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	vec3 a = glm::normalize(axis);
	float d = degrees / 180 * pi;

	float x = a.x;
	float y = a.y;
	float z = a.z;

	mat3 I(1.0);

	mat3 M2(x*x, x*y, x*z,
		x*y, y*y, y*z,
		x*z, y*z, z*z);

	mat3 M3(0, z, -y,
		-z, 0, x,
		y, -x, 0);
	// YOUR CODE FOR HW2 HERE
	// Please implement this.  Likely the same as in HW 1. 
	return cos(d)*I + (1 - cos(d))*M2 + sin(d)*M3;
}


mat4 Transform::_rotate(const float degrees, const vec3& axis)
{
	mat3 _rotate = rotate(degrees, axis);

	//mat3 x = mat3(_rotate[0][0], _rotate[1][0], _rotate[2][0],
	//	_rotate[0][1], _rotate[1][1], _rotate[1][2],
	//	_rotate[0][2], _rotate[2][1], _rotate[2][2]);

	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		printf("%f ", x[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("\n");
	//for (int i = 0; i < 3; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		printf("%f ", _rotate[i][j]);
	//	}
	//	printf("\n");
	//}

	return mat4(_rotate[0][0], _rotate[0][1], _rotate[0][2], 0,
		_rotate[1][0], _rotate[1][1], _rotate[1][2], 0,
		_rotate[2][0], _rotate[2][1], _rotate[2][2], 0,
		0, 0, 0, 1);
}


void Transform::left(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.  
	up = glm::normalize(up);
	eye = rotate(degrees, up) * eye;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

void Transform::up(float degrees, vec3& eye, vec3& up)
{
	// YOUR CODE FOR HW2 HERE 
	// Likely the same as in HW 1.  
	vec3 axis = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, axis) * eye;
	up = glm::normalize(rotate(degrees, axis) * up);
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
	// YOUR CODE FOR HW2 HERE
	// Likely the same as in HW 1.
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 R(u.x, v.x, w.x, 0,
		u.y, v.y, w.y, 0,
		u.z, v.z, w.z, 0,
		0, 0, 0, 1);

	mat4 T(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1);

	vec4 x1 = vec4(1.5, 1.5, 2, 2);
	vec4 x2 = vec4(2, 2, 2, 2);

	vec4 x3 = x1 * x2;
	cout << x3[0] << " " << x3[1] << " " << x3[2] << " " << x3[3] << endl;

	return R * T;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4 ret;
	fovy = fovy * pi / 180;
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well. 
	float a = -(zFar + zNear) / (zFar - zNear);
	float b = -(2 * zFar*zNear) / (zFar - zNear);
	float d = cos(fovy / 2.0) / sin(fovy / 2.0);
	  
	ret = mat4(d / aspect, 0, 0, 0,
		0, d, 0, 0,
		0, 0, a, -1,
		0, 0, b, 0);
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret = mat4(sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1);
	// YOUR CODE FOR HW2 HERE
	// Implement scaling 
	return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret= mat4(1, 0, 0, 0,
				0, 1, 0, 0, 
				0, 0, 1, 0,
				tx, ty, tz, 1);
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
	vec3 x = glm::cross(up, zvec);
	vec3 y = glm::cross(zvec, x);
	vec3 ret = glm::normalize(y);
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
