#ifndef SBND_FLASHMATCH_FLASHPREDICT_HH
#define SBND_FLASHMATCH_FLASHPREDICT_HH


#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"
#include "art_root_io/TFileService.h"
//#include "art/Framework/Services/Optional/TFileService.h"
#include "lardata/Utilities/AssociationUtil.h"
#include "larpandora/LArPandoraInterface/LArPandoraHelper.h"
//#include "larpandora/LArPandoraEventBuilding/LArPandoraSliceIdHelper.h"
//#include "larpandora/LArPandoraEventBuilding/SliceIdBaseTool.h"
//#include "larpandora/LArPandoraEventBuilding/Slice.h"
#include "lardataobj/RecoBase/PFParticle.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "lardataobj/RecoBase/PFParticleMetadata.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/RecoBase/SpacePoint.h"
#include "lardataobj/RecoBase/OpHit.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "lardataobj/AnalysisBase/T0.h"
#include "lardata/Utilities/AssociationUtil.h"
#include "larcore/Geometry/Geometry.h"
#include "larcorealg/Geometry/GeometryCore.h"
#include "larcorealg/Geometry/WireGeo.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Common/PtrVector.h"
#include "canvas/Persistency/Common/Assns.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "canvas/Persistency/Provenance/ProductID.h"
#include "art/Persistency/Common/PtrMaker.h"
#include "sbndcode/OpDetSim/OpT0FinderTypes.h"
#include "sbndcode/OpDetSim/sbndPDMapAlg.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TH1.h"

#include <memory>
#include <string>
#include <algorithm>

class FlashPredict;
class FlashPredict : public art::EDProducer {

public:
  explicit FlashPredict(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.
  // Plugins should not be copied or assigned.
  FlashPredict(FlashPredict const&) = delete;
  FlashPredict(FlashPredict&&) = delete;
  FlashPredict& operator=(FlashPredict const&) = delete;
  FlashPredict& operator=(FlashPredict&&) = delete;
  // Required functions.
  void produce(art::Event& e) override;
  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:
  // Declare member data here.
  //  ::flashana::FlashMatchManager m_flashMatchManager; ///< The flash match manager
  // art::InputTag fFlashProducer;
  // art::InputTag fT0Producer; // producer for ACPT in-time anab::T0 <-> recob::Track assocaition
  std::string fPandoraProducer, fSpacePointProducer, fOpHitProducer, fInputFilename, fCaloProducer, fTrackProducer;
  float fBeamWindowEnd, fBeamWindowStart;
  float fLightWindowEnd, fLightWindowStart;
  float fMinFlashPE;
  float fPEscale;
  float fChargeToNPhotonsShower, fChargeToNPhotonsTrack;
  std::string fDetector; // SBND or ICARUS
  int fCryostat;  // =0 or =1 to match ICARUS reco chain selection
  bool fMakeTree, fSelectNeutrino, fUseUncoatedPMT, fUseCalo;
  float fTermThreshold;
  std::vector<float> fPMTChannelCorrection;
  // geometry service
  static const size_t nMaxTPCs = 2; // ICARUS has 4 TPCs, however they need to be run independently
  std::array<flashana::QCluster_t, nMaxTPCs> qClusterInTPC;

  void computeFlashMetrics(size_t idtpc, std::vector<recob::OpHit> const& OpHitSubset);
  ::flashana::Flash_t GetFlashPESpectrum(const recob::OpFlash& opflash);
  void CollectDownstreamPFParticles(const lar_pandora::PFParticleMap &pfParticleMap,
                                    const art::Ptr<recob::PFParticle> &particle,
                                    lar_pandora::PFParticleVector &downstreamPFParticles) const;
  void CollectDownstreamPFParticles(const lar_pandora::PFParticleMap &pfParticleMap,
                                    const lar_pandora::PFParticleVector &parentPFParticles,
                                    lar_pandora::PFParticleVector &downstreamPFParticles) const;
  void AddDaughters(const art::Ptr<recob::PFParticle>& pfp_ptr,
                    const art::ValidHandle<std::vector<recob::PFParticle> >& pfp_h,
                    std::vector<art::Ptr<recob::PFParticle> > &pfp_v);
  bool isPDInCryoTPC(double pd_x, int icryo, size_t itpc, std::string detector);
  bool isPDInCryoTPC(int pdChannel, int icryo, size_t itpc, std::string detector);
  bool isChargeInCryoTPC(float qp_x, int icryo, int itpc, std::string detector);

  int icountPE = 0;
  const art::ServiceHandle<geo::Geometry> geometry;
// SBND map for light detector type labels (pmt, barepmt, arapuca, xarapuca)
  opdet::sbndPDMapAlg pdMap;

  // root stuff
  TTree* _flashmatch_acpt_tree;
  TTree* _flashmatch_nuslice_tree;
  TH1F *ophittime;
  TH1F *ophittime2;

  // Tree variables
  std::vector<float> _pe_reco_v, _pe_hypo_v;
  float _trk_vtx_x, _trk_vtx_y, _trk_vtx_z, _trk_end_x, _trk_end_y, _trk_end_z;
  float _nuvtx_x, _nuvtx_y, _nuvtx_z, _nuvtx_q;
  float _flash_x, _flash_y, _flash_z, _flash_pe, _flash_unpe;
  float _flash_r, _score;
  int _evt, _run, _sub;
  float _flashtime;
  float _flashpe;
  // PFP map
  std::map<unsigned int, unsigned int> _pfpmap;

  std::vector<float> dysp, dzsp, rrsp, pesp, dymean, dzmean, rrmean, pemean;
  int rr_nbins, dy_nbins, dz_nbins, pe_nbins;

};


#endif //SBND_FLASHMATCH_FLASHPREDICT_HH