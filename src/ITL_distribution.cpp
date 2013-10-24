#include "ITL_distribution.h"

ITL_distribution::ITL_distribution()
{
	nBin = -1;
	nTime = 0;
	freqList = NULL;

}// End constructor

ITL_distribution::ITL_distribution( int nbin, int ntime )
{
	nBin = nbin;
	nTime = ntime;
	freqList = new double[nbin*ntime];
	memset( freqList, 0, (nBin*nTime)*sizeof(double) );
}// End constructor

ITL_distribution::ITL_distribution( const ITL_distribution& that )
{
	this->nBin = that.nBin;
	this->nTime = that.nTime;
	this->freqList = NULL;

	if( that.freqList != NULL )
	{
		this->freqList = new double[nBin*nTime];
		memcpy( this->freqList, that.freqList, sizeof(double)*(nBin*nTime) );
	}

}

ITL_distribution&
ITL_distribution::operator= ( const ITL_distribution& that )
{
	if (this != &that ) // protect against invalid self-assignment
	{
		this->nBin = that.nBin;
		this->nTime = that.nTime;
		this->freqList = NULL;
		if( that.freqList != NULL )
		{
			this->freqList = new double[nBin*nTime];
			memcpy( this->freqList, that.freqList, sizeof(double)*(nBin*nTime) );
		}
	}
	// by convention, always return *this
	return *this;
}

ITL_distribution::~ITL_distribution()
{
	if( freqList != NULL )	delete [] freqList;
}// End destructor



void
ITL_distribution::generateUniformDist()
{
	assert( nBin > 0 );
	assert( nTime > 0 );
	assert( freqList != NULL );
	for( int i=0; i<(nBin*nTime); i++ )
		freqList[i] = 1.0f / (double)nBin;
}// End function

void
ITL_distribution::initialize( int nbin, int ntime )
{
	nBin = nbin;
	nTime = ntime;
	freqList = new double[nBin*nTime];
}

void
ITL_distribution::setNumTimeStep( int ntime )
{
	nTime = ntime;
	if( freqList != NULL ) delete [] freqList;

	assert( nBin > 0 );
	freqList = new double[nBin*nTime];

}// End function

void
ITL_distribution::setNumBin( int nbin )
{
	nBin = nbin;
	if( freqList != NULL ) delete [] freqList;

	assert( nTime > 0 );
	freqList = new double[nBin*nTime];

}// End function

void
ITL_distribution::setFrequencies( const char* distFileName, int t )
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
	for( int i=0; i<nBin; i++ )
	{
		fscanf( distFile, "%f\n", freqList+t*nBin+i );
	}
	
	// Close file
	fclose( distFile );
		
}// End function

void
ITL_distribution::setFrequencies( int *fl, int t )
{
	assert( freqList != NULL );
	double sumOfFrequencies = (double)ITL_util<int>::sum( fl, nBin );
	for( int i=0; i<nBin; i++ )
		freqList[t*nBin+i] = fl[t*nBin+i] / sumOfFrequencies;
}// End function

void
ITL_distribution::setFrequencies( double *fl, int t )
{
	assert( freqList != NULL );
	memcpy( freqList+t*nBin, fl, nBin*sizeof(double) );
}// End function

void
ITL_distribution::setDistribution( double *fl, int nbin, int ntime )
{
	nBin = nbin;
	nTime = ntime;
	if( freqList != NULL ) delete [] freqList;
	freqList = new double[nBin*nTime];
	memcpy( freqList, fl, sizeof(double)*(nBin*nTime) );

}// End function


int
ITL_distribution::getNumBin()
{
	return nBin;
}// End function

int
ITL_distribution::getNumTimeStep()
{
	return nTime;
}// End function


void
ITL_distribution::getFrequencies( double *fl, int t )
{
	assert( fl != NULL );
	memcpy( fl, freqList+t*nBin, sizeof(double)*nBin );
}// End function

void
ITL_distribution::getTimeVaryingFrequencies( double *fl )
{
	assert( fl != NULL );
	memcpy( fl, freqList, sizeof(double)*(nBin*nTime) );
}// End function

void
ITL_distribution::printFrequencies( int t )
{
	assert( freqList != NULL );
	for( int i=0; i<nBin; i++ )
		fprintf( stderr, "%g ", freqList[i] );
	fprintf( stderr, "\n" );
}// End function

void
ITL_distribution::printTimeVaryingFrequencies()
{
	assert( freqList != NULL );
	for( int t=0; t<nTime; t++ )
	{
		fprintf( stderr, "t = %d: ", t );
		for( int i=0; i<nBin; i++ )
		{
			fprintf( stderr, "%g ", freqList[t*nBin+i] );
		}
		fprintf( stderr, "\n" );
	}
	fprintf( stderr, "\n" );
}// End function
