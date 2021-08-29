#ifndef IVYMELAOUTPUTSTREAMEREXT_H
#define IVYMELAOUTPUTSTREAMEREXT_H


#include "IvyOutputStreamer.h"
#include "MELAParticle.h"
#include "MELAThreeBodyDecayCandidate.h"
#include "MELACandidate.h"


template<> IvyOutputStreamer& IvyOutputStreamer::operator<< <MELAParticle>(MELAParticle const& val);
template<> IvyOutputStreamer& IvyOutputStreamer::operator<< <MELAThreeBodyDecayCandidate>(MELAThreeBodyDecayCandidate const& val);
template<> IvyOutputStreamer& IvyOutputStreamer::operator<< <MELACandidate>(MELACandidate const& val);


#endif
