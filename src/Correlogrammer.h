/*
 *  Correlogrammer.h
 *  GammattoneFilterbankOffline
 *
 *  Created by Andrew on 06/11/2013.
 *  Copyright 2013 QMUL. All rights reserved.
 *
 */

#ifndef CORRELOGRAMMER_H
#define CORRELOGRAMMER_h

#include <iostream>
#include <time.h>
#include "acgmodel.h"
//#include "sys/stat.h"

#include "ofMain.h"

class Correlogrammer{
public:
	Correlogrammer();
	int openFile(std::string filepath, std::string datapath, double secondsToLoad = 6.2);
	void setParams();
	void drawFrame(int frameIndex);
	void drawFrameAtPosition(const double& position);
	
	AcgModel acg;
	double maxVal;
	
	int wavSize;
	int loadedSamplesSize;
	
	bool outputData;
};
#endif