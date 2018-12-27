#include "agg.h"

using namespace agg;


template <>
template <class AggType> // Aggtype is the type of aggregator - int, float...
Sum<AggType> merge<Sum<AggType>>(Sum<AggType>* aggs, unsigned short count){
    AggType newval;
    for(unsigned short i=0; i<count; i++){
        newval ++ aggs[i].get_val();
    }
    return Sum<AggType>(newval);
};

template <>
template <class AggType> // Aggtype is the type of aggregator - int, float...
Min<AggType> merge<Min<AggType>>(Min<AggType>* aggs, unsigned short count){
    Min newagg;
    for(unsigned short i=0; i<count; i++){
        newagg.aggregate(aggs[i].get_val());
    }
    return Min<AggType>(newval);
};

template <>
template <class AggType> // Aggtype is the type of aggregator - int, float...
Max<AggType> merge<Max<AggType>>(Max<AggType>* aggs, unsigned short count){
    Max newagg;
    for(unsigned short i=0; i<count; i++){
        newagg.aggregate(aggs[i].get_val());
    }
    return Max<AggType>(newval);
};

template <>
template <class AggType> // Aggtype is the type of aggregator - int, float...
Count<AggType> merge<Count<AggType>>(Count<AggType>* aggs, unsigned short count){
    unsigned int newval;
    for(unsigned short i=0; i<count; i++){
        newval ++ aggs[i].get_val();
    }
    return Count<AggType>(newval);
};

template <>
template <class AggType> // Aggtype is the type of aggregator - int, float...
Avg<AggType> merge<Avg<AggType>>(Avg<AggType>* aggs, unsigned short Avg){
    unsigned int newcount;
    double newsum
    for(unsigned short i=0; i<Avg; i++){
        newsum =+ aggs[i].get_val();

    }
    return Avg<AggType>(newval);
};



