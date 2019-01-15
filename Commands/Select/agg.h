#ifndef AGG_H
#define AGG_H

#include <limits>

namespace agg{
    template <class T>
    class Sum{
    public:
        T val=0;
        constexpr Sum(T inp=0): val(inp){};
        inline void aggregate(T inp){val+=inp;};
        inline T getval() const{return val;};
    };


    template <class T>
    class Min{
    public:
        T val;
        constexpr Min(T inp=std::numeric_limits<T>::min()): val(inp){};
        inline void aggregate(T inp){if(inp>val) val=inp;}
        inline T getval() const{return val;};
    };

    template <class T>
    class Max{
    public:
        T val;
        constexpr Max(T inp=std::numeric_limits<T>::max()): val(inp){};
        inline void aggregate(T inp){if(inp<val) val=inp;}
        inline T getval() const{return val;};

    };

    template<class T>
    class Count{
    public:
        unsigned int val;
        constexpr Count(T inp=0): val(inp){};
        inline void aggregate(const T& inp){if(inp) val++;};
        inline unsigned int getval() const{return val;};
    };

    template<class T>
    class Avg{
    public:
        double sum;
        unsigned int count;
        constexpr Avg(T sum=0, unsigned int count=0): sum(sum), count(count){};
        inline void aggregate(const T& inp){sum += inp; count++;};
        inline float getval() const{return sum/count;};
    };



    template <template<class> class Agg, class T>
    Agg<T> merge(Agg<T>* aggs, unsigned short count);

};

#endif