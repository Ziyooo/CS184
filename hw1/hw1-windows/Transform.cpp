// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include<stdio.h>
//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	vec3 a = glm::normalize(axis);
	float d = degrees / 180 * pi;

	float x = a.x;
	float y = a.y;
	float z = a.z;

	mat3 I( 1.0 );

	mat3 M2(x*x, x*y, x*z,
			x*y, y*y, y*z,
			x*z, y*z, z*z);

	mat3 M3(0, z, -y,
			-z, 0, x,
			y, -x, 0);

  // You will change this return call
  return cos(d)*I + (1-cos(d))*M2 + sin(d)*M3;
}



mat4 Transform::_rotate(const float degrees, const vec3& axis)
{
	mat3 _rotate = rotate(degrees, axis);

	return mat4(_rotate[0][0], _rotate[0][1], _rotate[0][2], 0,
		_rotate[1][0], _rotate[1][1], _rotate[1][2], 0,
		_rotate[2][0], _rotate[2][1], _rotate[2][2], 0,
		0, 0, 0, 1);

}




// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE  
	up = glm::normalize(up);
	eye = rotate(degrees, up) * eye;
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, axis) * eye;
	up = glm::normalize(rotate(degrees, axis) * up);
	printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 R( u.x, v.x, w.x, 0, 
			u.y, v.y, w.y, 0,
			u.z, v.z, w.z, 0,
			0, 0, 0, 1);

	mat4 T(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1);

  // You will change this return call
  return R*T;
}


mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// New, to implement the perspective transform as well.  
	fovy = fovy * pi / 180;
	float a = -(zFar + zNear) / (zFar - zNear);
	float b = -(2 * zFar*zNear) / (zFar - zNear);
	float d = cos(fovy/2) / sin(fovy/2);

	ret = mat4(d/aspect, 0, 0, 0,
				0, d, 0, 0, 
				0, 0, a, -1, 
				0, 0, b, 0); 
	return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
	mat4 ret;
	// YOUR CODE FOR HW2 HERE
	// Implement scaling 
	return ret;
}


mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
	mat4 ret = mat4(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		tx, ty, tz, 1);
	// YOUR CODE FOR HW2 HERE
	// Implement translation 
	return ret;
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
