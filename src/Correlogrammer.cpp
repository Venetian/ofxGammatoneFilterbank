/*
 *  Correlogrammer.cpp
 *  GammattoneFilterbankOffline
 *
 *  Created by Andrew on 06/11/2013.
 *  Copyright 2013 QMUL. All rights reserved.
 *
 */

//we don;t necessarily want to load ALL the samples and process - will take too long for music files
//maybe a few seconds enough
//so need a limit on the loading mechanism
//either iterating through samples or
//which are loaded into _data in the auxiliary.cpp class




#include "Correlogrammer.h"

Correlogrammer::Correlogrammer(){
	outputData = false;
	
	////////////////////////////////////////////////////////////////////////
	AcgParam param;
	param.lowCF = 50.0;    // lowest centre frequency in Hz
	param.highCF = 1000.0;//4000.0; // highest centre frequency in Hz
	param.nchans = 64;     // the number of gammatone filters
	param.winSize = 30;    // ACG window size in millisecond
	param.frmShift = 10;   // frame shift in ms
	////////////////////////////////////////////////////////////////////////
	
	acg.set_param(param);
	
	maxVal = 1.0;
	
	loadedSamplesSize = 0;
	wavSize = 0;
	

}

int Correlogrammer::openFile(std::string filepath, std::string datapath, double secondsToLoad){
	
	// Read wav data
	
	std::cout << "seconds to load " << secondsToLoad << std::endl;

	AudioWav wav;
	
	int numSamples = 44100*secondsToLoad;
	if (numSamples > 0){
		if (wav.read(filepath.c_str(), 'l', numSamples) < 1){
			std::cout << "something wrong in reading file" << std::cout;
			return 0;
		}
	} else {
		if (wav.read(filepath.c_str()) < 1){
			std::cout << "something wrong in reading file" << std::cout;
			return 0;
		}
	}
	std::cout << wav.size() << " samples loaded. Sampling rate = " << wav.fsHz() << std::endl;
	loadedSamplesSize = wav.size();
	
	std::cout << "full wav file size is " << wav.fileSize() << std::endl;
	wavSize = wav.fileSize();
	
//	std::string makeDirName = "../bin/data/gammatoneTestData";
//	int status = mkdir(makeDirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//	std::cout << "status: " << status << std::endl; 
	
	//wav.anrPrint();
	
	clock_t start = clock ();
	
	// Compute 3D correlogram
//	AcgModel acg(param);
	acg.compute(wav.data(), wav.fsHz());
	
	std::cout << std::endl << "Autocorrelogram computed in " << (clock() - start)/(double)CLOCKS_PER_SEC << " seconds" << std::endl;
	
	// Output the correlogram
	if (outputData)	
		acg.output(datapath.c_str());
	
	// Print out some information about the correlogram
	std::cout << "  maximum delay =\t" << acg.maxdelay() << std::endl;
	std::cout << "  number of channels =\t" << acg.nchans() << std::endl;
	std::cout << "  number of frames =\t" << acg.nframes() << std::endl;
	
	std::cout << "\nFrame\tChannel\tlag\tValue\n";
	// To access the lag 0 value in the 16th channel in the 11th frame
	std::cout << "11\t16\t0\t" << acg.get(10, 15, 0) << std::endl;
	// To access the lag 20 value of the 16th channel in the 11th frame
	std::cout << "11\t16\t20\t" << acg.get(10, 15, 20) << std::endl;
	// To access the lag 0 vaule of the 20th channel in the 36th frame
	std::cout << "36\t20\t0\t" << acg.get(35, 19, 0) << std::endl;
	
}

void Correlogrammer::drawFrame(int frameIndex){
	if (frameIndex < acg.nframes()){
		int numChannels =  acg.nchans();
		int numLags = acg.maxdelay();
		
		
		
		float heightBin = (float)ofGetHeight()/numChannels;
		float widthbin = (float)ofGetWidth()/numLags;
		int screenHeight = ofGetHeight();
		
		for (int channel = 0; channel < acg.nchans(); channel++){
			for (int lagVal = 0; lagVal < acg.maxdelay(); lagVal++){
				float val = acg.get(frameIndex, channel, lagVal);
				if (val > maxVal)
					maxVal = val;
				val *= 255.0/maxVal;
				ofSetColor(0,val,0);
				ofRect(lagVal*widthbin, screenHeight - (channel+1)*heightBin, widthbin, heightBin);
				//std::cout << "lag val " << lagVal << std::endl; - 660 lags
			}
			//std::cout << "channel " << channel << std::endl;//32 channels
		}
	}
}

void Correlogrammer::drawFrameAtPosition(const double& position){
	//position is song position element of [0,1]
	int frameNumber = 0;
	double currentSample = position * wavSize;//in samples
	//need this as ratio of how many were actually loaded
	if (loadedSamplesSize > 0)
		frameNumber = round(acg.nframes()*currentSample/loadedSamplesSize);
	
	drawFrame(frameNumber);
}

