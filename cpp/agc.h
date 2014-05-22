/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this
 * source distribution.
 *
 * This file is part of REDHAWK Basic Components agc.
 *
 * REDHAWK Basic Components agc is free software: you can redistribute it and/or modify it under the terms of
 * the GNU Lesser General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * REDHAWK Basic Components agc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with this
 * program.  If not, see http://www.gnu.org/licenses/.
 */
#ifndef AGC_IMPL_H
#define AGC_IMPL_H

#include "agc_base.h"
#include "exp_agc.h"
#include <complex>
#include <valarray>

class AgcProcessor
{
public:
	AgcProcessor();
	~AgcProcessor();
    void processReal(std::vector<float>& input);
    void processComplex(std::vector<std::complex<float> >& input);
    void setup(float avgPower, float minPower, float  maxPower, float eps, float alpha, std::vector<float>& out);
private:
    template<typename T>
    void updateTheAGC(ExpAgc<float,T>*& agc, std::valarray<T>& in, std::valarray<T>&out);

    std::valarray<float> realIn;
    std::valarray<float> realOut;
    std::valarray<std::complex<float> > cmplxIn;
    std::valarray<std::complex<float> > cmplxOut;

    ExpAgc<float,float>* realAgc;
    ExpAgc<float,std::complex<float> >* cmplxAgc;
    std::vector<float>* output;
    float avgPower_;
    float minPower_;
    float maxPower_;
    float eps_;
    float alpha_;

};

class agc_i;

class agc_i : public agc_base
{
    ENABLE_LOGGING
    public:
        agc_i(const char *uuid, const char *label);
        ~agc_i();
        int serviceFunction();
    private:
		typedef std::map<std::string, AgcProcessor> map_type;
		void alphaChanged(const float *oldValue, const float *newValue);
		void avgPowerChanged(const float *oldValue, const float *newValue);
		void maxPowerChanged(const float *oldValue, const float *newValue);
		void minPowerChanged(const float *oldValue, const float *newValue);

        std::map<std::string, AgcProcessor> agcs;

		boost::mutex agcLock_;

        std::vector<float> outputData;
};

#endif
