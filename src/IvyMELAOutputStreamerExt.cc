#include "IvyMELAOutputStreamerExt.h"


// The routines below are adapted from JHUGenMELA/MELA/src/MELAOutputStreamer.cc in the MELA package.


using namespace std;


template<> IvyOutputStreamer& IvyOutputStreamer::operator<< <MELAParticle>(MELAParticle const& val){
  *this << "MELAParticle [id]=" << val.id << " [X,Y,Z,T,M]=" << val.p4;
  return *this;
}
template<> IvyOutputStreamer& IvyOutputStreamer::operator<< <MELAThreeBodyDecayCandidate>(MELAThreeBodyDecayCandidate const& val){
  *this << "MELAThreeBodyDecayCandidate [id]=" << val.id << " [X,Y,Z,T,M]=" << val.p4 << endl;

  int ip=0;
  *this << "\tHas " << val.getNMothers() << " mothers" << endl;
  for (auto const& part:val.getMothers()){
    *this << "\t\tV" << ip << ' ' << *part << endl;
    ip++;
  }

  *this << "\tHas " << val.getNDaughters() << " daughters" << endl;
  *this << "\t\tPartner particle "; if (val.getPartnerParticle()) *this << *(val.getPartnerParticle()); else *this << "N/A"; *this << endl;
  *this << "\t\tW fermion "; if (val.getWFermion()) *this << *(val.getWFermion()); else *this << "N/A"; *this << endl;
  *this << "\t\tW antifermion "; if (val.getWAntifermion()) *this << *(val.getWAntifermion()); else *this << "N/A"; *this << endl;

  return *this;
}
template<> IvyOutputStreamer& IvyOutputStreamer::operator<< <MELACandidate>(MELACandidate const& val){
  *this << "MELACandidate [id]=" << val.id << " [X,Y,Z,T,M]=" << val.p4 << endl;

  int ip=0;
  *this << "\tHas " << val.getNMothers() << " mothers" << endl;
  for (auto const& part:val.getMothers()){
    *this << "\t\tV" << ip << ' ' << *part << endl;
    ip++;
  }

  *this << "\tHas " << val.getNSortedVs() << " sorted Vs" << endl;
  ip=0;
  for (auto const& part:val.getSortedVs()){
    *this << "\t\tV" << ip << ' ' << *part << endl;
    unsigned int ivd=0;
    for (auto const& dau:part->getDaughters()){
      *this << "\t\t- V" << ip << ivd << ' ' << *dau << endl;
      ivd++;
    }
    ip++;
  }

  *this << "\tHas " << val.getNAssociatedLeptons() << " leptons or neutrinos" << endl;
  ip=0;
  for (auto const& part:val.getAssociatedLeptons()){
    *this << "\t\tV" << ip << ' ' << *part << endl;
    ip++;
  }

  *this << "\tHas " << val.getNAssociatedPhotons() << " photons" << endl;
  ip=0;
  for (auto const& part:val.getAssociatedPhotons()){
    *this << "\t\tV" << ip << ' ' << *part << endl;
    ip++;
  }

  *this << "\tHas " << val.getNAssociatedJets() << " jets" << endl;
  ip=0;
  for (auto const& part:val.getAssociatedJets()){
    *this << "\t\tV" << ip << ' ' << *part << endl;
    ip++;
  }

  *this << "\tHas " << val.getNAssociatedTops() << " tops" << endl;
  ip=0;
  for (auto const& part:val.getAssociatedTops()){
    *this << "\t\tTop" << ip << ' ' << static_cast<MELAParticle const>(*part) << endl;
    { MELAParticle* bottom=part->getPartnerParticle(); if (bottom) *this << "\t\t- Top" << ip << " b " <<  ' ' << *bottom << endl; }
    { MELAParticle* Wf=part->getWFermion(); if (Wf) *this << "\t\t- Top" << ip << " Wf " << ' ' << *Wf << endl; }
    { MELAParticle* Wfb=part->getWAntifermion(); if (Wfb) *this << "\t\t- Top" << ip << " Wfb " <<  ' ' << *Wfb << endl; }
    ip++;
  }

  return *this;
}
