/*
   Copyright 2011 Tobii Technology AB

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <cmath>
#include <cassert>
#include <QString>
#include <QDebug>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class SpaceVector
{
public:
    SpaceVector() :
        x(0.0), y(0.0), z(0.0)
    {

    }

    SpaceVector(double x_, double y_, double z_) :
        x(x_), y(y_), z(z_)
    {

    }


    double x;
    double y;
    double z;
};

inline QDebug operator<<(QDebug dbg, const SpaceVector &v)
{
    dbg.nospace() << "[" << v.x << ", " << v.y << ", " << v.z << " )";

    return dbg.space();
}

inline SpaceVector operator * (const SpaceVector& vec, const double& s)
{
        SpaceVector c;
        c.x = vec.x * s;
        c.y = vec.y * s;
        c.z = vec.z * s;

        return c;
}

inline SpaceVector operator * (const double& s, const SpaceVector& vec)
{
        return vec * s;
}

inline SpaceVector operator + (const SpaceVector& a, const SpaceVector& b)
{
        SpaceVector c;
        c.x = a.x + b.x;
        c.y = a.y + b.y;
        c.z = a.z + b.z;

        return c;
}

inline SpaceVector operator - (const SpaceVector& a, const SpaceVector& b)
{
        SpaceVector c;
        c.x = a.x - b.x;
        c.y = a.y - b.y;
        c.z = a.z - b.z;

        return c;
}

inline bool operator == (const SpaceVector& a, const SpaceVector& b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}


template <class T>
class Matrix
{
public:

        Matrix(unsigned rows, unsigned cols)
                :r(rows), c(cols)
        {
        }

        template <class U, unsigned rows, unsigned cols>
        Matrix(const Matrix<U>& copy) : data(copy.data) {}


        unsigned Cols() const
        {
                return c;
        }

        unsigned Rows() const
        {
                return r;
        }

        T operator ()(unsigned row, unsigned col) const
        {
                assert(row <= r);
                assert(col <= c);

                return data[row-1][col-1];
        }

        T& operator ()(unsigned row, unsigned col)
        {
                assert(row <= r);
                assert(col <= c);

                return data[row-1][col-1];
        }

        Matrix Trans()
        {
                Matrix<T> t(c,r);
                for(unsigned i = 1; i <= r; i++)
                {
                        for(unsigned j = 1; j <= c; j++)
                                t(j,i) = (*this)(i,j);

                }
                return t;
        }

        void Invert()
        {
                assert(r == c);

                Matrix<T> inv(r,c);

                if(r == 3)
                {
                        // Maple generated 3x3 matrix inversion
                        T t4 =  (*this)(1,1)*(*this)(2,2);
                        T t6 =  (*this)(1,1)*(*this)(2,3);
                        T t8 =  (*this)(1,2)*(*this)(2,1);
                        T t10 = (*this)(1,3)*(*this)(2,1);
                        T t12 = (*this)(1,2)*(*this)(3,1);
                        T t14 = (*this)(1,3)*(*this)(3,1);

                        // Determinant
                        T det = (t4*(*this)(3,3)-t6*(*this)(3,2)-t8*(*this)(3,3)+t10*(*this)(3,2)+t12*(*this)(2,3)-t14*(*this)(2,2));

                        // If Determinant == 0, matrix is singular, use SVD generalized inversion
                        if(det == 0.0)
                        {
                                Sweep(1, r);
                        }
                        else
                        {
                                T t17 = 1/det;

                                inv(1,1) =  ((*this)(2,2)*(*this)(3,3)-(*this)(2,3)*(*this)(3,2))*t17;
                                inv(1,2) = -((*this)(1,2)*(*this)(3,3)-(*this)(1,3)*(*this)(3,2))*t17;
                                inv(1,3) =  ((*this)(1,2)*(*this)(2,3)-(*this)(1,3)*(*this)(2,2))*t17;
                                inv(2,1) = -((*this)(2,1)*(*this)(3,3)-(*this)(2,3)*(*this)(3,1))*t17;
                                inv(2,2) =  ((*this)(1,1)*(*this)(3,3)-t14)*t17;
                                inv(2,3) = -(t6-t10)*t17;
                                inv(3,1) =  ((*this)(2,1)*(*this)(3,2)-(*this)(2,2)*(*this)(3,1))*t17;
                                inv(3,2) = -((*this)(1,1)*(*this)(3,2)-t12)*t17;
                                inv(3,3) =  (t4-t8)*t17;

                                (*this) = inv;
                        }
                }
                else
                {
                        // non 3x3 matrix, use SVD generalized inversion for now
                        Sweep(1, r);
                }
        }

        void Make_Unit()
        {
                for(unsigned i = 1; i <= r; i++)
                {
                        for(unsigned j = 1; j <= c; j++)
                                if(i == j)
                                        (*this)(i,j) = 1.0;
                                else
                                        (*this)(i,j) = 0.0;
                }
        }

        void Make_Rotation_Matrix(const double& omega,
                                                          const double& phi,
                                                          const double& kappa)
        {
                assert(r == 3 && c == 3);

                (*this)(1,1) = cos(phi)*cos(kappa);
                (*this)(1,2) = -cos(phi)*sin(kappa);
                (*this)(1,3) = sin(phi);
                (*this)(2,1) = cos(omega)*sin(kappa) + sin(omega)*sin(phi)*cos(kappa);
                (*this)(2,2) = cos(omega)*cos(kappa) - sin(omega)*sin(phi)*sin(kappa);
                (*this)(2,3) = -sin(omega)*cos(phi);
                (*this)(3,1) = sin(omega)*sin(kappa) - cos(omega)*sin(phi)*cos(kappa);
                (*this)(3,2) = sin(omega)*cos(kappa) + cos(omega)*sin(phi)*sin(kappa);
                (*this)(3,3) = cos(omega)*cos(phi);
        }

        SpaceVector operator * (const SpaceVector& vec) const
        {
                assert(r == 3 && c == 3);

                SpaceVector out;

                out.x = (*this)(1,1) * vec.x + (*this)(2,1) * vec.y + (*this)(3,1) * vec.z;
                out.y = (*this)(1,2) * vec.x + (*this)(2,2) * vec.y + (*this)(3,2) * vec.z;
                out.z = (*this)(1,3) * vec.x + (*this)(2,3) * vec.y + (*this)(3,3) * vec.z;

                return out;
        }

        void operator += (const Matrix<T>& a)
        {
                assert(a.Rows() == r && a.Cols() == c);

                for(unsigned i = 1; i <= r; i++)
                {
                        for(unsigned j = 1; j <= c; j++)
                                (*this)(i,j) += a(i,j);
                }

        }
private:
        //sweep out rows k1 through k2
        void Sweep(int k1, int k2)
        {
                double eps = 1.0e-8;
                T d;
                int i, j, k, n, it;

                assert(c == r);

                n = r;
                if (k2 < k1)
                {
                        k = k1;
                        k1 = k2;
                        k2 = k;
                }

                for (k = k1; k <= k2; k++)
                {
                        if (fabs( (*this)(k, k) ) < eps)
                        {
                                for (it = 1; it <= n; it++)
                                {
                                        (*this)(it, k) = 0.0;
                                        (*this)(k, it) = 0.0;
                                }
                        }
                        else
                        {
                                d = 1.0 / (*this)(k, k);
                                (*this)(k, k) = d;
                                for (i = 1; i <= n; i++)
                                {
                                        if (i != k)
                                        {
                                                (*this)(i, k) *= - d;
                                        }
                                }
                                for (j = 1; j <= n; j++)
                                {
                                        if (j != k)
                                        {
                                                (*this)(k, j) *= d;
                                        }
                                }
                                for (i = 1; i <= n; i++)
                                {
                                        if (i != k)
                                        {
                                                for (j = 1; j <= n; j++)
                                                {
                                                        if (j != k)
                                                        {
                                                                (*this)(i, j) += (*this)(i, k) *(*this)(k, j) / d;
                                                        }
                                                } // end for j
                                        } // end for i != k
                                } // end for i
                        } // end else
                } // end for k

        }


        T data[4][4];
        unsigned r;
        unsigned c;
};


template <class T>
Matrix<T> operator * (const Matrix<T>& a, const Matrix<T>& b)
{
        assert(a.Cols() == b.Rows());

        Matrix<T> c(a.Rows(),b.Cols());
        T sum;

        for (unsigned i = 1; i <= a.Rows(); i++)
        {
                for (unsigned j = 1; j <= b.Cols(); j++)
                {
             sum = 0;
             for (unsigned k = 1; k <= a.Cols(); k++)
                         {
                 sum += a(i, k) * b(k, j);
                         }
                         c(i, j) = sum;
                }
    }

        return c;
}

template <class T>
Matrix<T> operator + (const Matrix<T>& a, const Matrix<T>& b)
{
        assert(a.Rows() == b.Rows() && a.Cols() == b.Cols());

        Matrix<T> c(a.Rows(), a.Cols());

        for (unsigned i = 1; i <= a.Rows(); i++)
        {
                for (unsigned j = 1; j <= a.Cols(); j++)
                {
             c(i,j) = a(i,j) + b(i,j);
                }
    }

        return c;
}

template <class T>
Matrix<T> operator - (const Matrix<T>& a, const Matrix<T>& b)
{
        assert(a.Rows() == b.Rows() && a.Cols() == b.Cols());

        Matrix<T> c(a.Rows(), a.Cols());

        for (unsigned i = 1; i <= a.Rows(); i++)
        {
                for (unsigned j = 1; j <= a.Cols(); j++)
                {
             c(i,j) = a(i,j) - b(i,j);
                }
    }

        return c;
}

inline double deg_to_rad(double deg)
{
        return deg * M_PI / 180;
}



#endif // MATH_TYPES_H
