/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 08.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __FILTER_H__
#define __FILTER_H__

class Filter {
    protected:
        float*      _data;

    public:         Filter(int size);
        virtual     ~Filter();

        float       filter(float input);
};

class MeanFilter : public Filter {
    public:
                    MeanFilter(int size);
        virtual     ~MeanFilter();

        float       filter(float input);
};

class MedianFilter : public Filter {
    public:
                    MedianFilter(int size);
        virtual     ~MedianFilter();

        float       filter(float input);
};

#endif

