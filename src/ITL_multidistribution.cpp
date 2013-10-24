#include "ITL_multidistribution.h"

ITL_multidistribution::ITL_multidistribution( int *nbin, int nlevel )
{
	nResolution = nlevel;
	nBinAllLevels = 0;
	for( int i=0; i<nResolution; i++ )
	{
		nBin[i] = nbin[i];
		nBinAllLevels += nBin[i];
	}
	
	freqList = new float[nBinAllLevels];
	memset( freqList, 0, nBinAllLevels*sizeof(float) );

}// End constructor

void
ITL_multidistribution::generateUniformDist()
{
	assert( nBinAllLevels > 0 );
	assert( freqList != NULL );
	int startId, endId;

	for( int i=0; i<nResolution; i++ )
	{	
		if( i== 0)	startId = 0;
		else		startId = endId+1;
		endId = startId + nBin[i]-1;
		
		for( int j=startId; j<=endId; j++ )
			freqList[j] = 1.0f / (float)nBin[i];		
	}// end for
	
}// End function

void
ITL_multidistribution::setFrequencies( const char* distFileName )
{
	FILE* distFile = NULL;
	
	// Open file
	#if defined( _WIN32 ) || defined( _WIN64 )
	errno_t err;
	if( (err  = fopen_s( &distFile, distFileName, "r" )) !=0 )
		printf( "The distribution file was not opened for reading\n" );
	#else
		assert( (distFile = fopen( distFileName, "r" ) ) != NULL );
	#endif
		
	// Read data from file
	assert( freqList != NULL );
	for( int i=0; i<nBinAllLevels; i++ )
	{
		fscanf( distFile, "%f\n", freqList+i );
	}
	
	// Close file
	fclose( distFile );
		
}// End function

void
ITL_multidistribution::setFrequencies( int *fl )
{
	assert( freqList != NULL );
	float sumOfFrequencies = (float)ITL_util<int>::sum( fl, nBin[0] );
	for( int i=0; i<nBinAllLevels; i++ )
		freqList[i] = fl[i] / sumOfFrequencies;
}// End function

void
ITL_multidistribution::setFrequencies( float *fl )
{
	assert( freqList != NULL );
	memcpy( freqList, fl, nBinAllLevels*sizeof(float) );
	
}// End function

void
ITL_multidistribution::getNumBin( int *nb )
{
	assert( nBin != NULL );
	memcpy( nb, nBin, sizeof(float)*nResolution );
	
}// End function

void
ITL_multidistribution::getFrequencies( float *fl )
{
	assert( fl != NULL );
	memcpy( fl, freqList, sizeof(float)*nBinAllLevels );	
	
}// End function

void
ITL_multidistribution::printFrequencies()
{
	assert( freqList != NULL );
	for( int i=0; i<nBinAllLevels; i++ )
		fprintf( stderr, "%f ", freqList[i] );
	fprintf( stderr, "\n" );	
}// End function