#ifndef AGG_H
#define AGG_H

#include <limits>

namespace agg{
    template <class T>
    class Sum{
    private:
        constexpr Sum(T inp=0): _val(inp){};
        T _val=0;
        inline void aggregate(T inp){_val+=inp;};
    };


    template <class T>
    class Min{
    private:
        T _val;
    public:
        constexpr Min(T inp=0): _val(inp){};
        inline void aggregate(T val = std::numeric_limits<T>::min()){
            if(inp<_val) _val=inp;
            }
        inline T get_val() const{return _val};
    };

    template <class T>
    class Max{
    private:
        T _val = std::numeric_limits<T>::max();
    public:
        constexpr Max(T val=std::numeric_limits<T>::max()): _val(inp){};
        inline void aggregate(T inp){if(inp<_val) _val=inp;}
        inline T get_val() const{return _val};

    };

    template<class T>
    class Count{
    private:
        unsigned int _val;
    public:
        constexpr Count(T inp=0): _val(inp){};
        inline void aggregate(const T& inp){if(inp) _val++;};
        inline unsigned int get_val() const{return _val};
    };

    template<class T>
    class Avg{
    private:
        double _sum;
        unsigned int _count;
    public:
        constexpr Avg(T _sum=0, unsigned int _count=0): sum(_sum), count(_count){};
        inline void aggregate(const T& inp){sum += inp; count++;};
        inline float get_val() const{return sum/count};
    };



    template <class Agg, class AggType>
    Agg merge(Agg* aggs, unsigned short count);

    template <class T>

    template <class T>
    T max__val();
    
};

#endif