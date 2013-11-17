ofxGammatoneFilterbank
======================

Gammatone filterbank from Ning Ma's code. Load a file and see the gammatone's response as it plays


copy the emptyExample OF project and get rid of the src file.

Drag the NingMaSrc and the src folders in.

Copy the AubioFullOSX library in (or use your own version of the FFTW library). This  is only required for doing the FFT.

Compile


comments etc to andrew.robertson@eecs.qmul.ac.uk

The way it works is to load a file and analyse a set portion - typically 20 seconds so the computation time is not too large. It roughly the same as real time for a hundred gammatones, so a minute long file would take a minute to appear.
Change the frequency range, number of filters, length to analyse in the code.