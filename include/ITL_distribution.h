/**
 *  Histogram Class.
 *  A class that implements various space-partitioning algorithms.
 *  Created on: July 17, 2011.
 *  @author Abon
 *  @author Teng-Yok
 */
#ifndef ITL_DISTRIBUTION_H
#define ITL_DISTRIBUTION_H

#include <cstdio>
#include <cstring>
#include <cassert>
#include "ITL_util.h"

class ITL_distribution
{
private:
	
	int nBin;
	int nTime;
	double *freqList;

public:

	ITL_distribution();
	ITL_distribution( int nbin, int ntime = 1 );
	ITL_distribution( const ITL_distribution& that );

	ITL_distribution& operator= ( const ITL_distribution& that );
	
	~ITL_distribution();

	void initialize( int nbin, int ntime );

	void generateUniformDist();
	
	void setNumBin( int nbin );
	void setNumTimeStep( int ntime );
	void setFrequencies( const char* distFile, int t = 0 );
	void setFrequencies( int *fl, int t = 0 );
	void setFrequencies( double *fl, int t = 0 );
	void setDistribution( double *fl, int nbin, int ntime = 1 );

	int getNumBin();
	int getNumTimeStep();
	void getFrequencies( double *fl, int t = 0 );
	void getTimeVaryingFrequencies( double *fl );
	
	void printFrequencies( int t = 0 );
	void printTimeVaryingFrequencies();
};

#endif
