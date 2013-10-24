/**
 *  Multiresolution Histogram Class.
 *  A class that implements various space-partitioning algorithms.
 *  Created on: July 17, 2011.
 *  @author Abon
 *  @author Teng-Yok
 */
#ifndef ITL_MULTIDISTRIBUTION_H
#define ITL_MULTIDISTRIBUTION_H

#include <cstdio>
#include <cstring>
#include <cassert>
#include "ITL_util.h"

class ITL_multidistribution
{
private:
	
	int nResolution;
	int nBin[5];
	int nBinAllLevels;
	float *freqList;

public:
	ITL_multidistribution( int *nbin, int nlevel );
	
	void generateUniformDist();
	
	void setNumBin();
	void setFrequencies( const char* distFile );
	void setFrequencies( int *fl );
	void setFrequencies( float *fl );
	void getNumBin( int *nb );
	void getFrequencies( float *fl );
	
	void printFrequencies();
};

#endif