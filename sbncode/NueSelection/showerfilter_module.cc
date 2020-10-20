////////////////////////////////////////////////////////////////////////
// Class:       showerfilter
// Module Type: filter
// File:        showerfilter_module.cc
//
// Generated at Fri Sep  6 04:41:23 2019 by Dominic Barker using artmod
// from cetpkgsupport v1_14_01.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "larsim/MCCheater/ParticleInventoryService.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "larcorealg/Geometry/BoxBoundedGeo.h"

#include <memory>

namespace shower {
  class showerfilter;
}

class shower::showerfilter : public art::EDFilter {
public:
  explicit showerfilter(fhicl::ParameterSet const & p);
  // The destructor generated by the compiler is fine for classes
  // without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  showerfilter(showerfilter const &) = delete;
  showerfilter(showerfilter &&) = delete;
  showerfilter & operator = (showerfilter const &) = delete;
  showerfilter & operator = (showerfilter &&) = delete;

  // Required functions.
  bool filter(art::Event & e) override;


private:

  // Declare member data here.
  std::string fGenieGenModuleLabel;

  std::vector<geo::BoxBoundedGeo> fActiveVolume; //!< List of active volumes

  //Check if the point is in the Active volume.
  bool containedInAV(const TVector3 &v);

  double VertexDist(const art::Ptr<simb::MCTruth>& mc, const simb::MCParticle* &particle);

  const art::ServiceHandle<cheat::ParticleInventoryService> particleInventory;


};


shower::showerfilter::showerfilter(fhicl::ParameterSet const & pset): art::EDFilter{pset}
  // Initialize member data here.
{
  fGenieGenModuleLabel = pset.get<std::string>("GenieGenModuleLabel");

  // setup active volume bounding boxes
  std::vector<fhicl::ParameterSet> AVs =				\
    pset.get<std::vector<fhicl::ParameterSet> >("ActiveVolume");
  for (auto const& AV : AVs) {
    double xmin = AV.get<double>("xmin");
    double ymin = AV.get<double>("ymin");
    double zmin = AV.get<double>("zmin");
    double xmax = AV.get<double>("xmax");
    double ymax = AV.get<double>("ymax");
    double zmax = AV.get<double>("zmax");
    fActiveVolume.emplace_back(xmin, xmax, ymin, ymax, zmin, zmax);
  }

  
  // Call appropriate produces<>() functions here.
}

bool shower::showerfilter::filter(art::Event & evt)
{
  
  // * MC truth information
  art::Handle<std::vector<simb::MCTruth> > mctruthListHandle;
  std::vector<art::Ptr<simb::MCTruth> > mclist;
  if (evt.getByLabel(fGenieGenModuleLabel,mctruthListHandle))
    art::fill_ptr_vector(mclist, mctruthListHandle);


  //Check there is some vertex outside the active volume
  bool contained = true;
  for(auto const& mc: mclist){
    contained *= containedInAV(mc->GetNeutrino().Nu().Position().Vect());
  }

  if(contained){
    return false;
  }

  std::map<int,const simb::MCParticle*> mcparticles;
  auto const& mcparticle_list = *evt.getValidHandle<std::vector<simb::MCParticle>>("largeant");
  for(auto const &mcparticle:  mcparticle_list){
    mcparticles[mcparticle.TrackId()] = &mcparticle;
  }

  for(auto const &particle_pair:  mcparticles){

    const simb::MCParticle* particle = particle_pair.second;

    //Only keep showers
    if(particle->PdgCode() != 22 && particle->PdgCode() != 11 && particle->PdgCode() != -11){continue;}

    //Is it above 10 MeV. Remove any delta rays.
    if(particle->E()*1000 < 10){continue;}

    //    Is the shower in the active volume 
    if(!containedInAV(particle->Position().Vect())){continue;}

    //Was the vertex not in the active volume 
    int particle_temp = particle->TrackId();
    while(true){
      std::cout << "in loop" << std::endl;
      if(mcparticles.find(mcparticles[particle_temp]->Mother()) == mcparticles.end()){
	double mindist = 999;
	bool VertexContained = false;
	for(auto const& mc: mclist){    
	  if(mindist > VertexDist(mc,mcparticles[particle_temp])){
	    VertexContained = containedInAV(mc->GetNeutrino().Nu().Position().Vect());
	  }
	}
	if(VertexContained){break;}
	else{return true;}
      }

      particle_temp = mcparticles[mcparticles[particle_temp]->Mother()]->TrackId();
    }
  }

  return false;
}
		      

//Check if the point is in the Active volume.
bool shower::showerfilter::containedInAV(const TVector3 &v) {
  for (auto const& AV: fActiveVolume) {
    if (AV.ContainsPosition(v)) return true;
  }
  return false;
}

double shower::showerfilter::VertexDist(const art::Ptr<simb::MCTruth>& mc, const simb::MCParticle* &particle){
  
  TLorentzVector nuVtx     = mc->GetNeutrino().Nu().Trajectory().Position(0);
  TLorentzVector partstart = particle->Position();
  return TMath::Abs((partstart - nuVtx).Mag());
}



DEFINE_ART_MODULE(shower::showerfilter)
