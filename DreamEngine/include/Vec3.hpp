#pragma once

template<typename T>
struct Vec4
{
    // Declares three variables of template type T
    public:
    T x,y,z,w;
    Vec4(T _x, T _y, T _z, T _w): x(_x), y(_y), z(_z), w(_w){};
    Vec4(){};
};

template<typename T>
struct Vec3
{
    // Declares three variables of template type T
    public:
    T x,y,z;
};

template<typename T>
struct Vec2
{
    // Declares three variables of template type T
    public:
    T x,y;
};


template<typename T>
struct Mat4
{
    public:
    Vec4<T> r1, r2, r3, r4;

    Mat4(){};
    // Constructor to initialize rows
    Mat4(Vec4<T> _r1, Vec4<T> _r2, Vec4<T> _r3, Vec4<T> _r4)
        : r1(_r1), r2(_r2), r3(_r3), r4(_r4) {}

    // Overload * operator for matrix multiplication
    Mat4 operator*(const Mat4& other) const {
        // Compute each row of the resulting matrix
        return Mat4(
            Vec4<T>(
                dot(r1, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
                dot(r1, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
                dot(r1, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
                dot(r1, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
            ),
            Vec4<T>(
                dot(r2, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
                dot(r2, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
                dot(r2, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
                dot(r2, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
            ),
            Vec4<T>(
                dot(r3, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
                dot(r3, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
                dot(r3, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
                dot(r3, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
            ),
            Vec4<T>(
                dot(r4, Vec4<T>(other.r1.x, other.r2.x, other.r3.x, other.r4.x)),
                dot(r4, Vec4<T>(other.r1.y, other.r2.y, other.r3.y, other.r4.y)),
                dot(r4, Vec4<T>(other.r1.z, other.r2.z, other.r3.z, other.r4.z)),
                dot(r4, Vec4<T>(other.r1.w, other.r2.w, other.r3.w, other.r4.w))
            )
        );
    }

    // Helper function to compute the dot product of two Vec4<T>
    static T dot(const Vec4<T>& v1, const Vec4<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
    }
};



