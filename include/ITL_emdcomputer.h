#ifndef ITL_EMDCOMPUTER_H
#define ITL_EMDCOMPUTER_H

#include "ITL_header.h"

class ITL_emdcomputer
{
public:	
	
	ITL_emdcomputer();
	
	static float computeEMD1D( float *dist1, float *dist2, int nBin );
	static float computeEMD1D_multilevel( float *dist1, float *dist2, int nBin, int nLevel );
};

#endif