#pragma once

//m * n의 Matrix 클래스
template<size_t m, size_t n>
class Matrix final
{
    friend class Matrix;    //Private를 사용가능

public:
    //생성자
    template<typename... Type>
    Matrix(Type const &... element) : element { static_cast<float>(element)... }
    {
        //1 * 1일 경우, Matrix의 생성을 막습니다.
        static_assert(not (m == 1 and n == 1), "Matrix<1, 1> cannot be created.");
    }

    //+ 부호 표기
    auto operator +(void) const
    {
        return *this;
    }

    //Matrix의 덧셈 Matrix A 와 B를 더함
    auto operator +(Matrix<m, n> const & other) const
    {
        Matrix<m, n> product = *this;

        for(size_t u = 0; u < m; ++u)
            for(size_t v = 0; v < n; ++v)
                product.element[u][v] += other.element[u][v];

        return product;
    }

    //위의 덧셈 함수와 동일 +=에 대응
    auto & operator +=(Matrix<m, n> const & other)
    {
        return *this = *this + other;
    }

    //Matrix * 상수
    auto operator *(float const & other) const
    {
        Matrix<m, n> product = *this;

        for(size_t u = 0; u < m; ++u)
            for(size_t v = 0; v < n; ++v)
                product.element[u][v] *= other;

        return product;
    }

    //위의 곱셈과 동일
    auto & operator *=(float const & other)
    {
        return *this = *this * other;
    }

    //- 부호 표기
    auto operator -(void) const
    {
        return *this * -1;
    }

    //다른 매트릭스와의 뺄셈, 덧셈 함수 응용
    auto operator -(Matrix<m, n> const & other) const
    {
        return *this + (-other);
    }

    //위의 뺄셈과 동일
    auto & operator -=(Matrix<m, n> const & other)
    {
        return *this = *this - other;
    }

    //상수 나눗셈, 곱셈 함수 응용
    auto operator /(float const & other) const
    {
        return *this * (1 / other);
    }

    //위와 동일
    auto & operator /=(float const & other)
    {
        return *this = *this / other;
    }

    //다른 매트릭스와의 곱셈
    template<size_t l>
    auto operator *(Matrix<n, l> const & other) const
    {
        //1 * N 매트릭스와 N * 1의 매트릭스 곱일 경우 Float 반환
        if constexpr (m == 1 and l == 1)
        {
            float product = float();

            for(size_t u = 0; u < n; ++u)
                product += (*this).element[0][u] * other.element[u][0];

            return product;
        }
        else
        {
            //M * L의 크기를 가진 결과값의 Matrix 반환
            Matrix<m, l> product = Matrix<m, l>();

            for(size_t u = 0; u < m; ++u)
                for(size_t v = 0; v < l; ++v)
                    for(size_t w = 0; w < n; ++w)
                        product.element[u][v] += (*this).element[u][w] * other.element[w][v];

            return product;
        }
    }

    //위와 동일한 함수
    auto & operator *=(Matrix<n, n> const & other)
    {
        return *this = *this * other;
    }

    //Matrix의 Index에 해당하는 값을 반환, 상황에 맞추어 어떻게 반환될지 나타냄
    //1. M * 1 매트릭스 : element[index]의 포인터
    //2. 1 * N 매트릭스 : element의 포인터의 index 번째 배열
    //3. M * N 매트릭스 : element[index]
    auto & operator [](size_t const & index)
    {
             if constexpr (m != 1 and n == 1) return (*( element)[index]);
        else if constexpr (m == 1 and n != 1) return ( (*element)[index]);
        else if constexpr (m != 1 and n != 1) return ( ( element)[index]);
    }

    //const 형태의 Matrix에서 호출되는 [] operator, const 해제 후 위의 함수를 사용함
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

// * 혹은 / 가 상수 * Matrix 순으로 붙었을 경우 호출되는 함수
/*
template<unsigned m, unsigned n>
inline auto operator *(float const & one, Matrix<m, n> const & other)
{
    //기존 Matrix 곱셈 오버로딩
    return other * one;
}

template<unsigned m, unsigned n>
inline auto operator /(float const & one, Matrix<m, n> const & other)
{
    return other / one;
}*/
