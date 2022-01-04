#pragma once

//m * n�� Matrix Ŭ����
template<size_t m, size_t n>
class Matrix final
{
    friend class Matrix;    //Private�� ��밡��

public:
    //������
    template<typename... Type>
    Matrix(Type const &... element) : element { static_cast<float>(element)... }
    {
        //1 * 1�� ���, Matrix�� ������ �����ϴ�.
        static_assert(not (m == 1 and n == 1), "Matrix<1, 1> cannot be created.");
    }

    //+ ��ȣ ǥ��
    auto operator +(void) const
    {
        return *this;
    }

    //Matrix�� ���� Matrix A �� B�� ����
    auto operator +(Matrix<m, n> const & other) const
    {
        Matrix<m, n> product = *this;

        for(size_t u = 0; u < m; ++u)
            for(size_t v = 0; v < n; ++v)
                product.element[u][v] += other.element[u][v];

        return product;
    }

    //���� ���� �Լ��� ���� +=�� ����
    auto & operator +=(Matrix<m, n> const & other)
    {
        return *this = *this + other;
    }

    //Matrix * ���
    auto operator *(float const & other) const
    {
        Matrix<m, n> product = *this;

        for(size_t u = 0; u < m; ++u)
            for(size_t v = 0; v < n; ++v)
                product.element[u][v] *= other;

        return product;
    }

    //���� ������ ����
    auto & operator *=(float const & other)
    {
        return *this = *this * other;
    }

    //- ��ȣ ǥ��
    auto operator -(void) const
    {
        return *this * -1;
    }

    //�ٸ� ��Ʈ�������� ����, ���� �Լ� ����
    auto operator -(Matrix<m, n> const & other) const
    {
        return *this + (-other);
    }

    //���� ������ ����
    auto & operator -=(Matrix<m, n> const & other)
    {
        return *this = *this - other;
    }

    //��� ������, ���� �Լ� ����
    auto operator /(float const & other) const
    {
        return *this * (1 / other);
    }

    //���� ����
    auto & operator /=(float const & other)
    {
        return *this = *this / other;
    }

    //�ٸ� ��Ʈ�������� ����
    template<size_t l>
    auto operator *(Matrix<n, l> const & other) const
    {
        //1 * N ��Ʈ������ N * 1�� ��Ʈ���� ���� ��� Float ��ȯ
        if constexpr (m == 1 and l == 1)
        {
            float product = float();

            for(size_t u = 0; u < n; ++u)
                product += (*this).element[0][u] * other.element[u][0];

            return product;
        }
        else
        {
            //M * L�� ũ�⸦ ���� ������� Matrix ��ȯ
            Matrix<m, l> product = Matrix<m, l>();

            for(size_t u = 0; u < m; ++u)
                for(size_t v = 0; v < l; ++v)
                    for(size_t w = 0; w < n; ++w)
                        product.element[u][v] += (*this).element[u][w] * other.element[w][v];

            return product;
        }
    }

    //���� ������ �Լ�
    auto & operator *=(Matrix<n, n> const & other)
    {
        return *this = *this * other;
    }

    //Matrix�� Index�� �ش��ϴ� ���� ��ȯ, ��Ȳ�� ���߾� ��� ��ȯ���� ��Ÿ��
    //1. M * 1 ��Ʈ���� : element[index]�� ������
    //2. 1 * N ��Ʈ���� : element�� �������� index ��° �迭
    //3. M * N ��Ʈ���� : element[index]
    auto & operator [](size_t const & index)
    {
             if constexpr (m != 1 and n == 1) return (*( element)[index]);
        else if constexpr (m == 1 and n != 1) return ( (*element)[index]);
        else if constexpr (m != 1 and n != 1) return ( ( element)[index]);
    }

    //const ������ Matrix���� ȣ��Ǵ� [] operator, const ���� �� ���� �Լ��� �����
    auto & operator [](size_t const & index) const
    {
        return (*const_cast<Matrix<m, n> *>(this))[index];
    }

private:
    float element[m][n];
};

template<size_t m, size_t n>
inline Matrix<n, m> const transpose(Matrix<m, n> const& other)
{
    if constexpr(m == 1 or n == 1)
        return reinterpret_cast<Matrix<n, m> const&>(other);
    else
    {
        Matrix<n, m> transposed = Matrix<n, m>();
        for (size_t u = 0; u < n; ++u)
            for (size_t v = 0; v < m; ++v)
                transposed[u][v] = other[v][u];
        return transposed;
    }
    
}

// * Ȥ�� / �� ��� * Matrix ������ �پ��� ��� ȣ��Ǵ� �Լ�
/*
template<unsigned m, unsigned n>
inline auto operator *(float const & one, Matrix<m, n> const & other)
{
    //���� Matrix ���� �����ε�
    return other * one;
}

template<unsigned m, unsigned n>
inline auto operator /(float const & one, Matrix<m, n> const & other)
{
    return other / one;
}*/
