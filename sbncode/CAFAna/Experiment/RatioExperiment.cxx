#include "CAFAna/Experiment/RatioExperiment.h"

#include "CAFAna/Core/LoadFromFile.h"
#include "CAFAna/Core/Ratio.h"
#include "CAFAna/Core/HistCache.h"

#include "CAFAna/Prediction/IPrediction.h"

#include "TDirectory.h"
#include "TObjString.h"

#include "TH1.h"

#include <cassert>

namespace ana
{
  //----------------------------------------------------------------------
  double RatioExperiment::ChiSq(osc::IOscCalculatorAdjustable* osc,
                                const SystShifts& syst) const
  {
    osc->SetL(kBaselineSBND);
    Spectrum predND = fPredND->PredictSyst(osc, syst);
    osc->SetL(kBaselineIcarus);
    Spectrum predFD = fPredFD->PredictSyst(osc, syst);
    
    predFD *= Ratio(fSpectND, predND);

    TH1D* hpred = predFD.ToTH1(fSpectFD.POT());
    TH1D* hdata = fSpectFD.ToTH1(fSpectFD.POT());

    const double ret = LogLikelihood(hpred, hdata);

    HistCache::Delete(hpred);
    HistCache::Delete(hdata);

    return ret;
  }

  // //----------------------------------------------------------------------
  // void RatioExperiment::SaveTo(TDirectory* dir) const
  // {
  //   bool hasCorr = false;
  //   for(auto it: fSystCorrelations) if(!it.empty()) hasCorr = true;

  //   if(hasCorr){
  //     std::cerr << "Warning in RatioExperiment: systematic correlations are set and will not be serialized by this call to SaveTo(). You will have to re-set them once you load the experiment back in." << std::endl;
  //   }

  //   TDirectory* tmp = dir;

  //   dir->cd();
  //   TObjString("RatioExperiment").Write("type");

  //   for(unsigned int i = 0; i < fExpts.size(); ++i){
  //     fExpts[i]->SaveTo(dir->mkdir(TString::Format("expt%d", i)));
  //   }

  //   tmp->cd();
  // }

  // //----------------------------------------------------------------------
  // std::unique_ptr<RatioExperiment> RatioExperiment::LoadFrom(TDirectory* dir)
  // {
  //   TObjString* ptag = (TObjString*)dir->Get("type");
  //   assert(ptag);
  //   assert(ptag->GetString() == "RatioExperiment");

  //   std::vector<const IExperiment*> expts;

  //   for(int i = 0; ; ++i){
  //     TDirectory* subdir = dir->GetDirectory(TString::Format("expt%d", i));
  //     if(!subdir) break;

  //     expts.push_back(ana::LoadFrom<IExperiment>(subdir).release());
  //   }

  //   assert(!expts.empty());

  //   return std::unique_ptr<RatioExperiment>(new RatioExperiment(expts));
  // }
}
