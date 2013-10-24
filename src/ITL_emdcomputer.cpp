#include "ITL_emdcomputer.h"

ITL_emdcomputer::ITL_emdcomputer()
{	
}// End constructor

float
ITL_emdcomputer::computeEMD1D( float *dist1, float *dist2, int nBin )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	
	float dk = 0;
	float emd = 0;
	for(int iB=0; iB<nBin; iB++ )
	{
		//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		dk = dist1[iB]-dist2[iB];
		emd += abs(dk);
	}

	return emd;
}// End function

float
ITL_emdcomputer::computeEMD1D_multilevel( float *dist1, float *dist2, int nBin, int nLevel )
{
	assert( dist1 != NULL );
	assert( dist2 != NULL );
	
	// Array for storing emd of each level
	#if defined( _WIN32 ) || defined( _WIN64 )
		float* emdLevelwise = new float[nLevel];
	#else	
		float emdLevelwise[nLevel];
	#endif

	// Compute EMD for each level
	// and keep combining
	int startId, endId, nBinLevel;
	float finalEMD = 0;
	for( int i=0; i<nLevel; i++ )
	{
		if( i == 0)	startId = 0;
		else		startId = endId+1;
		
		nBinLevel = (int)( (float)nBin / pow( 2.0f, i ) ); 
		endId = startId + nBinLevel-1; 
		
		// Compute EMD of this level
		emdLevelwise[i] = computeEMD1D( dist1+startId, dist2+startId, nBinLevel );
		//emdLevelwise[i] = 0;
		//float dk = 0;
		//for(int iB=startId; iB<=endId; iB++ )
		//{
			//printf( "%d: %f %f\n", iB, dist1[iB], dist2[iB] );
		//	dk += dist1[iB]-dist2[iB];
		//	dk = dist1[iB]-dist2[iB];
		//	emdLevelwise[i] += abs(dk);
		//}	
				
		// Accumulate scores
		finalEMD += emdLevelwise[i] * ( 1.0f / pow( 2.0f, i ) );
	}

	#if defined( _WIN32 ) || defined( _WIN64 )
		delete [] emdLevelwise;
	#endif	

	return finalEMD;
	
}// End function


