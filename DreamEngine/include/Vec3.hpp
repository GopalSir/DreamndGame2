#pragma once

template<typename T>
struct Vec4
{
    // Declares three variables of template type T
    public:
    T x,y,z,w;
    Vec4(T _x, T _y, T _z, T _w): x(_x), y(_y), z(_z), w(_w){};
    Vec4(){};
	// Helper function to compute the dot product of two Vec4<T>
	static T dot(const Vec4<T>& v1, const Vec4<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	//Negation operator overlaod
	Vec4 operator-() const {
		return Vec4(-x, -y, -z, -w);
	}

	//Addition operator overload to add two Vec4<T>
	Vec4 operator+(const Vec4& other) const {
		return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	//Minus operator overload to subtract two Vec4<T>
	Vec4 operator-(const Vec4& other) const {
		return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	//Multiplication operator overload to multiply a Vec4<T> by a scalar
	Vec4 operator*(const T scalar) const {
		return Vec4(x * scalar, y * scalar, z * scalar, w );
	}


};

template<typename T>
struct Vec3
{
    // Declares three variables of template type T
    public:
    T x,y,z;
	Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
	static T dot(const Vec3<T>& v1, const Vec3<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	//Negation operator overlaod
	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}

	static Vec3<T> normalize(const Vec3<T>& v) {
		T length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		if (length == 0) return Vec3<T>(0, 0, 0); // Avoid division by zero
		return Vec3<T>(v.x / length, v.y / length, v.z / length);
	}

	// Addition operator overload to add two Vec3<T>
	Vec3 operator+(const Vec3& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	// Minus operator overload to subtract two Vec3<T>
	Vec3 operator-(const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	// Multiplication operator overload to multiply a Vec3<T> by a scalar
	Vec3 operator*(const T scalar) const {
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

};

template<typename T>
struct Vec2
{
    // Declares three variables of template type T
    public:
    T x,y;
};

template<typename T>
struct Mat3
{
public:
	Vec3<T> r1, r2, r3;
	Mat3() {}; // Default constructor
	// Constructor to initialize rows
	Mat3(Vec3<T> _r1, Vec3<T> _r2, Vec3<T> _r3)
		: r1(_r1), r2(_r2), r3(_r3) {
	}
	// Overload * operator for matrix multiplication
	Mat3 operator*(const Mat3& other) const {
		return Mat3(
			Vec3<T>(
				dot(r1, Vec3<T>(other.r1.x, other.r2.x, other.r3.x)),
				dot(r1, Vec3<T>(other.r1.y, other.r2.y, other.r3.y)),
				dot(r1, Vec3<T>(other.r1.z, other.r2.z, other.r3.z))
			),
			Vec3<T>(
				dot(r2, Vec3<T>(other.r1.x, other.r2.x, other.r3.x)),
				dot(r2, Vec3<T>(other.r1.y, other.r2.y, other.r3.y)),
				dot(r2, Vec3<T>(other.r1.z, other.r2.z, other.r3.z))
			),
			Vec3<T>(
				dot(r3, Vec3<T>(other.r1.x, other.r2.x, other.r3.x)),
				dot(r3, Vec3<T>(other.r1.y, other.r2.y, other.r3.y)),
				dot(r3, Vec3<T>(other.r1.z, other.r2.z, other.r3.z))
			)
		);
	}

	


	// Helper function to compute the dot product of two Vec4<T>
	static Mat3<T> transpose(const Mat3<T>& matrix) {
		return Mat3<T>(
			Vec3<T>(matrix.r1.x, matrix.r2.x, matrix.r3.x),
			Vec3<T>(matrix.r1.y, matrix.r2.y, matrix.r3.y),
			Vec3<T>(matrix.r1.z, matrix.r2.z, matrix.r3.z)
		);
	}



	//Negation Operator Overlaod
	Mat3 operator-() const {
		return Mat3(-r1.x, -r1.y, -r1.z,
			-r2.x, -r2.y, -r2.z,
			-r3.x, -r3.y, -r3.z);
	}

};


template<typename T>
struct Mat4
{
public:
	Vec4<T> r1, r2, r3, r4;

	Mat4() {};
	// Constructor to initialize rows
	Mat4(Vec4<T> _r1, Vec4<T> _r2, Vec4<T> _r3, Vec4<T> _r4)
		: r1(_r1), r2(_r2), r3(_r3), r4(_r4) {
	}
	Mat4(Mat3<T> _rotation, Vec3<T> _translation)
		: r1(_rotation.r1.x, _rotation.r1.y, _rotation.r1.z, _translation.x),
		r2(_rotation.r2.x, _rotation.r2.y, _rotation.r2.z, _translation.y),
		r3(_rotation.r3.x, _rotation.r3.y, _rotation.r3.z, _translation.z),
		r4(0, 0, 0, 1) {
	} // Assuming the last row is [0, 0, 0, 1] for homogeneous coordinates


	// Overload * operator for matrix multiplication
	Mat4 operator*(const Mat4& other) const {
		// Compute each row of the resulting matrix
		return Mat4(
			Vec4<T>(
				Vec4<T>::dot(r1, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
				Vec4<T>::dot(r1, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
				Vec4<T>::dot(r1, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
				Vec4<T>::dot(r1, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
			),
			Vec4<T>(
				Vec4<T>::dot(r2, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
				Vec4<T>::dot(r2, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
				Vec4<T>::dot(r2, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
				Vec4<T>::dot(r2, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
			),
			Vec4<T>(
				Vec4<T>::dot(r3, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
				Vec4<T>::dot(r3, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
				Vec4<T>::dot(r3, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
				Vec4<T>::dot(r3, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
			),
			Vec4<T>(
				Vec4<T>::dot(r4, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
				Vec4<T>::dot(r4, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
				Vec4<T>::dot(r4, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
				Vec4<T>::dot(r4, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
			)
		);
	}

	static Mat4<T> identity;
};



template<typename T>
Mat4<T> Mat4<T>::identity = Mat4<T>(
	Vec4<T>(1, 0, 0, 0),
	Vec4<T>(0, 1, 0, 0),
	Vec4<T>(0, 0, 1, 0),
	Vec4<T>(0, 0, 0, 1)
);


   




