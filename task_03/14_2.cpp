#include<iostream>
#include<algorithm>
#include<vector>
#include<array>
#include<type_traits>
#include <typeinfo>
using namespace std;



/*template<typename T, int N>
auto create_temp_buffer()
{
    if constexpr(N*sizeof(T)>4000)
    {
        return vector<T>(N);
    }
    else
    {
        return array<T, N>{};
    }
}*/

/*template <typename T, int N>
std::enable_if_t< !(N*sizeof(T)<4 * 1024), vector<T> >
create_temp_buffer()
{
    return vector<T>(N);
}

template <typename T, int N>
std::enable_if_t< N*sizeof(T)<4 * 1024, array<T,N> >
create_temp_buffer()
{
    return array<T, N>{};
}*/
struct ArrCreator
{
    template <class T, int N>
    auto operator()()
    {
        return array<T, N>{};
    }
};

struct VecCreator
{
    template <class T, int N>
    auto operator()()
    {
        return vector<T>(N);
    }
};


template <typename T, int N>
auto create_temp_buffer()
{
    
    return std::conditional_t<  (N * sizeof(T) <= 4 * 1024), ArrCreator, VecCreator >{}.operator()<T, N>();

}


int main()
{


    auto lbi = create_temp_buffer<int, 1000>();

    auto lbd = create_temp_buffer<double, 3000>();


    //fill(begin(lbi), end(lbi), -1);
    //fill(begin(lbd), end(lbd), 3.14159);
    

    return 0;
}
