#include "agg.h"

using namespace agg;


template <class T>
Sum<T> merge(Sum<T>* aggs, unsigned short count){
    T newval;
    for(unsigned short i=0; i<count; i++){
        newval += aggs[i].get_val();
    }
    return Sum<T>(newval);
};

template <class T>
Min<T> merge(Min<T>* aggs, unsigned short count){
    Min<T> newagg;
    for(unsigned short i=0; i<count; i++){
        newagg.aggregate(aggs[i].get_val());
    }
    return newagg;
};

template <class T>
Max<T> merge(Max<T>* aggs, unsigned short count){
    Max<T> newagg;
    for(unsigned short i=0; i<count; i++){
        newagg.aggregate(aggs[i].get_val());
    }
    return newagg;
};

template <class T>
Count<T> merge(Count<T>* aggs, unsigned short count){
    unsigned int newval;
    for(unsigned short i=0; i<count; i++){
        newval += aggs[i].get_val();
    }
    return Count<T>(newval);
};

template <class T>
Avg<T> merge(Avg<T>* aggs, unsigned short Avg){
    unsigned int newcount;
    double newsum;
    for(unsigned short i=0; i<Avg; i++){
        newsum =+ aggs[i].sum; 
        newcount += aggs[i].count;
    }
    return {newsum, newcount};
};



