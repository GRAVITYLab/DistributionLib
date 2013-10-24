#include "ITL_distcomputer.h"

ITL_distcomputer::ITL_distcomputer()
{	
}// End constructor

float
ITL_distcomputer::computeL1( float *dist1, float *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	
	float dk = 0;
	float l1 = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		dk = dist1[iB]-dist2[iB];
		l1 += abs(dk);
	}

	return l1;	
}

float
ITL_distcomputer::computeL2( float *dist1, float *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	
	float dk = 0;
	float l2 = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		dk = dist1[iB]-dist2[iB];
		l2 += (dk*dk);
	}

	return sqrt(l2);		
}

float
ITL_distcomputer::computeHistIntersection( float *dist1, float *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	float l = 0;
	for( int iB=0; iB<nBin; iB++ )
	{
		l += std::min( dist1[iB], dist2[iB] );
	}

	return (1-l);
}

float
ITL_distcomputer::computeChiSquare( float *dist1, float *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	float l = 0;
	for( int iB=0; iB<nBin; iB++ )
	{
		l += ( ( dist1[iB] - dist2[iB] )*( dist1[iB] - dist2[iB] ) ) / ( ( dist1[iB] + dist2[iB] )/2.0f ) ;
	}

	return l;
}


float
ITL_distcomputer::computeKLD( float *dist1, float *dist2, int nBin )
{
	return 0.0f;	
}

float
ITL_distcomputer::computeJSD( float *dist1, float *dist2, int nBin )
{
	return 0.0f;
}

float
ITL_distcomputer::computeEMD1D( float *dist1, float *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	#if defined( _WIN32 ) || defined( _WIN64 )
		float* cDist1 = new float[nBin];
		float* cDist2 = new float[nBin];
	#else
		float cDist1[nBin];
		float cDist2[nBin];
	#endif

	float dk = 0;
	float l3 = 0;
	cDist1[0] = cDist2[0] = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		
		if( iB == 0 )		
		{
			cDist1[iB] = dist1[iB];
			cDist2[iB] = dist2[iB];
		}
		else
		{		
			cDist1[iB] = cDist1[iB-1] + dist1[iB];
			cDist2[iB] = cDist2[iB-1] + dist2[iB];
		}

		dk = cDist1[iB]-cDist2[iB];
		l3 += abs(dk);
		//printf( "l3: %g\n", l3 );
	}

	#if defined( _WIN32 ) || defined( _WIN64 )
		delete [] cDist1;
		delete [] cDist2;
	#endif

	return l3;		
}// End function

float
ITL_distcomputer::computeDistance_multilevel( float *dist1, float *dist2, int nBin, int nLevel, int type )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	// Array for storing emd of each level
	#if defined( _WIN32 ) || defined( _WIN64 )
		float* distLevelwise = new float[nLevel];
	#else
		float distLevelwise[nLevel];
	#endif


	// Compute EMD for each level
	// and keep combining
	int startId, endId, nBinLevel;
	float finalDist = 0;
	float weight = 0;
	for( int i=0; i<nLevel; i++ )
	{
		if( i == 0)	startId = 0;
		else		startId = endId+1;

		nBinLevel = (int)( (float)nBin / pow( 2.0f, i ) );
		endId = startId + nBinLevel-1;

		// Compute distance of this level
		if( type == 0 )
			distLevelwise[i] = computeL1( dist1+startId, dist2+startId, nBinLevel );
		else if( type == 1 )
			distLevelwise[i] = computeL2( dist1+startId, dist2+startId, nBinLevel );
		else if( type == 2 )
			distLevelwise[i] = computeKLD( dist1+startId, dist2+startId, nBinLevel );
		else if( type == 3 )
			distLevelwise[i] = computeEMD1D( dist1+startId, dist2+startId, nBinLevel );

		// Accumulate scores and weights
		finalDist += distLevelwise[i] * ( 1.0f / pow( 2.0f, i ) );
		weight += ( 1.0f / pow( 2.0f, i ) );
	}

	#if defined( _WIN32 ) || defined( _WIN64 )
		delete [] distLevelwise;
	#endif

	return (finalDist / weight);

}// End function

double
ITL_distcomputer::computeL1( double *dist1, double *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	double dk = 0;
	double l1 = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		dk = dist1[iB]-dist2[iB];
		l1 += abs(dk);
	}

	return l1;
}

double
ITL_distcomputer::computeL2( double *dist1, double *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	double dk = 0;
	double l2 = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		dk = dist1[iB]-dist2[iB];
		l2 += (dk*dk);
	}

	return sqrt(l2);
}

double
ITL_distcomputer::computeHistIntersection( double *dist1, double *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	double l = 0;
	for( int iB=0; iB<nBin; iB++ )
	{
		l += std::min( dist1[iB], dist2[iB] );
	}

	return (1-l);
}

double
ITL_distcomputer::computeChiSquare( double* dist1, double* dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );

	double l = 0;
	for( int iB=0; iB<nBin; iB++ )
	{
		if( dist1[iB] == 0 && dist2[iB] == 0 )
			continue;
		l += ( ( dist1[iB] - dist2[iB] )*( dist1[iB] - dist2[iB] ) ) / ( ( dist1[iB] + dist2[iB] )/2.0f ) ;
	}

	return l;
}

double
ITL_distcomputer::computeKLD( double *dist1, double *dist2, int nBin )
{
	return 0.0f;
}

double
ITL_distcomputer::computeJSD( double *dist1, double *dist2, int nBin )
{
	return 0.0f;
}

double
ITL_distcomputer::computeEMD1D( double *dist1, double *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	#if defined( _WIN32 ) || defined( _WIN64 )
		double* cDist1 = new double[nBin];
		double* cDist2 = new double[nBin];
	#else
		double cDist1[nBin];
		double cDist2[nBin];
	#endif

	double dk = 0;
	double l3 = 0;
	cDist1[0] = cDist2[0] = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );

		if( iB == 0 )
		{
			cDist1[iB] = dist1[iB];
			cDist2[iB] = dist2[iB];
		}
		else
		{
			cDist1[iB] = cDist1[iB-1] + dist1[iB];
			cDist2[iB] = cDist2[iB-1] + dist2[iB];
		}

		dk = cDist1[iB]-cDist2[iB];
		l3 += abs(dk);
		//printf( "l3: %g\n", l3 );
	}

	#if defined( _WIN32 ) || defined( _WIN64 )
		delete [] cDist1;
		delete [] cDist2;
	#endif

	return l3;
}// End function

double
ITL_distcomputer::computeDistance_multilevel( double *dist1, double *dist2, int nBin, int nLevel, int type )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	
	// Array for storing emd of each level
	#if defined( _WIN32 ) || defined( _WIN64 )
		double* distLevelwise = new double[nLevel];
	#else	
		double distLevelwise[nLevel];
	#endif

	
	// Compute EMD for each level
	// and keep combining
	int startId, endId, nBinLevel;
	double finalDist = 0;
	double weight = 0;
	for( int i=0; i<nLevel; i++ )
	{
		if( i == 0)	startId = 0;
		else		startId = endId+1;
		
		nBinLevel = (int)( (double)nBin / pow( 2.0f, i ) );
		endId = startId + nBinLevel-1; 
		
		// Compute distance of this level
		if( type == 0 )
			distLevelwise[i] = computeL1( dist1+startId, dist2+startId, nBinLevel );
		else if( type == 1 )
			distLevelwise[i] = computeL2( dist1+startId, dist2+startId, nBinLevel );
		else if( type == 2 )
			distLevelwise[i] = computeKLD( dist1+startId, dist2+startId, nBinLevel );
		else if( type == 3 )
			distLevelwise[i] = computeEMD1D( dist1+startId, dist2+startId, nBinLevel );	
				
		// Accumulate scores and weights
		finalDist += distLevelwise[i] * ( 1.0f / pow( 2.0f, i ) );
		weight += ( 1.0f / pow( 2.0f, i ) );
	}

	#if defined( _WIN32 ) || defined( _WIN64 )
		delete [] distLevelwise;
	#endif

	return (finalDist / weight);
	
}// End function


