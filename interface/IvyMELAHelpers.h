#ifndef IVYMELAHELPERS_H
#define IVYMELAHELPERS_H

#include <MelaAnalytics/GenericMEComputer/interface/GMECHelperFunctions.h>
#include <MelaAnalytics/EventContainer/interface/MELAEvent.h>
#include "VerbosityLevel.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "TTree.h"
#include "TVar.hh"


// Global helpers
namespace IvyMELAHelpers{
  extern std::shared_ptr<Mela> melaHandle;

  TVar::VerbosityLevel convertVerbosity_IvyToMELA(MiscUtils::VerbosityLevel verb_);
  MiscUtils::VerbosityLevel convertVerbosity_MELAToIvy(TVar::VerbosityLevel verb_);

  double getSqrts(int year);
  void setupMela(int year, float mh, TVar::VerbosityLevel verbosity);
  void setupMela(int year, float mh, MiscUtils::VerbosityLevel verbosity){ setupMela(year, mh, convertVerbosity_IvyToMELA(verbosity)); }
  void clearMela();

  using namespace BranchHelpers;
  class GMECBlock{
  protected:
    std::vector<MELAOptionParser*> lheme_originalopts; // Be careful: Only for reading
    std::vector<MELAOptionParser*> lheme_copyopts;
    std::vector<MELAHypothesis*> lheme_units;
    std::vector<MELAHypothesis*> lheme_aliased_units;
    std::vector<MELAComputation*> lheme_computers;
    std::vector<MELACluster*> lheme_clusters;
    std::vector<MELABranch*> lheme_branches;

    std::vector<MELAOptionParser*> recome_originalopts; // Be careful: Only for reading
    std::vector<MELAOptionParser*> recome_copyopts;
    std::vector<MELAHypothesis*> recome_units;
    std::vector<MELAHypothesis*> recome_aliased_units;
    std::vector<MELAComputation*> recome_computers;
    std::vector<MELACluster*> recome_clusters;
    std::vector<MELABranch*> recome_branches;

    std::vector<TTree*> reftrees;

  public:
    GMECBlock();
    virtual ~GMECBlock();

    void addRefTree(TTree* reftree_);
    void setRefTrees(std::vector<TTree*> const& reftrees_);

    void buildMELABranches(std::vector<std::string> const& MElist, bool isGen);
    void clearMELABranches();

    void computeMELABranches(bool isGen);
    void computeMELABranches();

    void pushMELABranches(bool isGen);
    void pushMELABranches();

    void getBranchValues(std::unordered_map<std::string, float>& io_rcd, bool isGen);
    void getBranchValues(std::unordered_map<std::string, float>& io_rcd);

  protected:
    void bookMELABranches(MELAOptionParser* me_opt, MELAComputation* computer, bool doCopy);
    void clearMELABranches(bool isGen);

    // The user can change the default update functions and their order if they override the function below.
    virtual void computeMELABranches_Ordered(bool isGen, bool isForward);

    void updateMELAClusters_Common(std::string const& clustertype, bool isGen);
    void updateMELAClusters_J1JECJER(std::string const& clustertype, bool isGen);
    void updateMELAClusters_J2JECJER(std::string const& clustertype, bool isGen);
    void updateMELAClusters_LepWH(std::string const& clustertype, bool isGen);
    void updateMELAClusters_LepZH(std::string const& clustertype, bool isGen);
    void updateMELAClusters_NoInitialQ(std::string const& clustertype, bool isGen);
    void updateMELAClusters_NoInitialG(std::string const& clustertype, bool isGen);
    void updateMELAClusters_NoAssociatedG(std::string const& clustertype, bool isGen);
    void updateMELAClusters_NoInitialGNoAssociatedG(std::string const& clustertype, bool isGen);
    void updateMELAClusters_BestLOAssociatedZ(std::string const& clustertype, bool isGen);
    void updateMELAClusters_BestLOAssociatedW(std::string const& clustertype, bool isGen);
    void updateMELAClusters_BestLOAssociatedVBF(std::string const& clustertype, bool isGen);
    void updateMELAClusters_BestNLOVHApproximation(std::string const& clustertype, bool isGen);
    void updateMELAClusters_BestNLOVBFApproximation(std::string const& clustertype, bool isGen);
  };

}


#endif
