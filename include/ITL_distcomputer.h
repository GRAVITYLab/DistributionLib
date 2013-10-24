#ifndef ITL_DISTCOMPUTER_H
#define ITL_DISTCOMPUTER_H

#include <cassert>
#include <cstdlib>
#include <cmath>

#include "ITL_header.h"
#include "emd.h"

class ITL_distcomputer
{
public:	
	
	ITL_distcomputer();
	
	static float computeL1( float *dist1, float *dist2, int nBin );
	static double computeL1( double *dist1, double *dist2, int nBin );
	//static float computeL1_multilevel( float *dist1, float *dist2, int nBin );
	static float computeL2( float *dist1, float *dist2, int nBin );
	static double computeL2( double *dist1, double *dist2, int nBin );
	//static float computeL2_multilevel( float *dist1, float *dist2, int nBin );
	static float computeHistIntersection( float *dist1, float *dist2, int nBin );
	static double computeHistIntersection( double *dist1, double *dist2, int nBin );
	//static float computeHistIntersection_multilevel( float *dist1, float *dist2, int nBin );
	static float computeChiSquare( float *dist1, float *dist2, int nBin );
	static double computeChiSquare( double *dist1, double *dist2, int nBin );
	//static float computeChiSquare_multilevel( float *dist1, float *dist2, int nBin );
	static float computeKLD( float *dist1, float *dist2, int nBin );
	static double computeKLD( double *dist1, double *dist2, int nBin );
	//static float computeKDL_multilevel( float *dist1, float *dist2, int nBin );
	static float computeJSD( float *dist1, float *dist2, int nBin );
	static double computeJSD( double *dist1, double *dist2, int nBin );
	//static float computeJSD_multilevel( float *dist1, float *dist2, int nBin );
	static float computeEMD1D( float *dist1, float *dist2, int nBin );
	static double computeEMD1D( double *dist1, double *dist2, int nBin );
	//static float computeEMD1D_multilevel( float *dist1, float *dist2, int nBin, int nLevel );
	
	static float computeDistance_multilevel( float *dist1, float *dist2, int nBin, int nLevel, int type );
	static double computeDistance_multilevel( double *dist1, double *dist2, int nBin, int nLevel, int type );
};

#endif
