/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 08.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "Filter.h"


/******************************************************************************
 * Filter
 */

Filter::Filter(int size)
{
    _data = new float[size];
}


Filter::~Filter()
{
    delete[] _data;
}

float
Filter::filter(float input)
{
    return input;
}

/******************************************************************************
 * Mean Filter
 */

MeanFilter::MeanFilter(int size)
: Filter(size)
{

}

MeanFilter::~MeanFilter()
{

}

float
MeanFilter::filter(float input)
{
    return input;
}


/******************************************************************************
 * Median Filter
 */

MedianFilter::MedianFilter(int size)
: Filter(size)
{

}

MedianFilter::~MedianFilter()
{

}

float
MedianFilter::filter(float input)
{
    return input;
}
