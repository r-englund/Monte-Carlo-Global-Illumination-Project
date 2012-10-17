#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <assert.h>

template <typename T>
class Vector3
{
    protected :
        T v[3];

    public :
        ~Vector3(){};

        Vector3()
        {
            this->v[0] = this->v[1] = this->v[2] = T(0.0);
        }

        Vector3(T value)
        {
            this->v[0] = this->v[1] = this->v[2] = T(value);
        }

        template <typename T1, typename T2, typename T3>
        Vector3(T1 v0, T2 v1, T3 v2)
        {
            this->v[0] = T(v0);
            this->v[1] = T(v1);
            this->v[2] = T(v2);
        }

        // copy constructor
        template <typename T2>
        Vector3(const Vector3<T2>& vec3)
        {
            *this = vec3;
        }

        template <typename T2>
        const Vector3<T>& operator=(const Vector3<T2>& vec3)
        {
            if(this != &vec3)   // self assignment ?
            {
                this->v[0] = T(vec3[0]);
                this->v[1] = T(vec3[1]);
                this->v[2] = T(vec3[2]);
            }
            return *this;
        }

        template <typename T2>
        const Vector3<T>& operator=(const T2 value)
        {
            this->v[0] = T(value);
            this->v[1] = T(value);
            this->v[2] = T(value);
            return *this;
        }

        T& operator[](unsigned int i)
        {
            assert(i >= 0 && i <= 2);
            return v[i];
        }

        const T& operator[](unsigned int i) const
        {
            assert(i >= 0 && i <= 2);
            return v[i];
        }
        // Vector - Vector Operations -------------------------------------------------
        // vec + vec
        template <typename T2>
        Vector3<T> operator+(const Vector3<T2>& vec3) const
        {
            return Vector3<T>(v[0] + T(vec3[0]), v[1] + T(vec3[1]), v[2] + T(vec3[2]));
        }
        // vec - vec
        template <typename T2>
        Vector3<T> operator-(const Vector3<T2>& vec3) const
        {
            return Vector3<T>(v[0] - T(vec3[0]), v[1] - T(vec3[1]), v[2] - T(vec3[2]));
        }
        // vec * vec    :  not dot operator
        template <typename T2>
        Vector3<T> operator*(const Vector3<T2>& vec3) const
        {
            return Vector3<T>(v[0] * T(vec3[0]), v[1] * T(vec3[1]), v[2] * T(vec3[2]));
        }
        // vec += vec
        template <typename T2>
        Vector3<T>& operator+=(const Vector3<T2>& vec3)
        {
            this->v[0] += T(vec3[0]);
            this->v[1] += T(vec3[1]);
            this->v[2] += T(vec3[2]);
            return *this;
        }
        // vec -= vec
        template <typename T2>
        Vector3<T>& operator-=(const Vector3<T2>& vec3)
        {
            this->v[0] -= T(vec3[0]);
            this->v[1] -= T(vec3[1]);
            this->v[2] -= T(vec3[2]);
            return *this;
        }
        // vec *= vec
        template <typename T2>
        Vector3<T>& operator*=(const Vector3<T2>& vec3)
        {
            this->v[0] *= T(vec3[0]);
            this->v[1] *= T(vec3[1]);
            this->v[2] *= T(vec3[2]);
            return *this;
        }

        // Vector - Scalar Operations -------------------------------------------------
        // vec * scalar
        template <typename T2>
        const Vector3<T> operator*(T2 value) const
        {
            return Vector3<T>(v[0] * T(value), v[1] * T(value), v[2] * T(value));
        }
        // vec / scalar
        template <typename T2>
        const Vector3<T> operator/(T2 value) const
        {
            T div = 1/T(value);
            return Vector3<T>(v[0] * div, v[1] * div, v[2] * div);
        }
        // vec *= scalar
        template <typename T2>
        Vector3<T>& operator*=(T2 value)
        {
            this->v[0] *= T(value);
            this->v[1] *= T(value);
            this->v[2] *= T(value);
            return *this;
        }
        // vec /= scalar
        template <typename T2>
        Vector3<T>& operator/=(T2 value)
        {
            T div = 1/T(value);
            this->v[0] *= div;
            this->v[1] *= div;
            this->v[2] *= div;
            return *this;
        }

        template <typename T2>
        friend T Dot(const Vector3<T>& v1, const Vector3<T2>& v2)
        {
            T dot = v1[0]*T(v2[0]) + v1[1]*T(v2[1]) + v1[2]*T(v2[2]);
            return dot;
        }

        const T Length() const
        {
            T len = this->v[0]*this->v[0] + this->v[1]*this->v[1] + this->v[2]*this->v[2];
            return sqrt(len);
        }

        const T Length2() const
        {
            T len = this->v[0]*this->v[0] + this->v[1]*this->v[1] + this->v[2]*this->v[2];
            return len;
        }

        void Normalize()
        {
            T len = this->Length();
            (*this)/=len;
        }

        friend std::ostream& operator <<(std::ostream &os, const Vector3<T>& vec3)
        {
            os << "(" << vec3[0] << "," << vec3[1] << "," << vec3[2] << ")";
            return os;
        }

};

#endif
