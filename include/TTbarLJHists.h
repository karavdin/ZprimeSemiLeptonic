#pragma once

#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/TopJetIds.h>

#include <string>

class TTbarLJHists : public HistsBASE {

 public:
  explicit TTbarLJHists(uhh2::Context&, const std::string&);
  explicit TTbarLJHists(uhh2::Context&, const std::string&, const TopJetId&, const float);

  virtual void fill(const uhh2::Event&) override;

 protected:
  TopJetId tjet_ID_;
  float    tjet_minDR_jet_;

  virtual void init() override;

 private:
  //Variables used in MVA for QCD suppression
  TH1F* lep__fbrem;
  TH1F* lep__DR_jet0;
  TH1F* jet0__DR_jet1;
  TH1F* met__DPhi_lep;
  TH1F* lep__pTrel_jet1;
  TH1F* lep__vtxXY;
  TH1F* lep__vtxXY_trans;
  TH1F* Mt__lep_met;
  //Let's make things more smooth
  TH1F* logmet__pt;
  TH1F* logjet1__pt;
  TH1F* logele1__pt;
  TH1F* log_lep__DR_jet0;
  TH1F* trans_jet0__DR_jet1;
  TH1F* log_lep__pTrel_jet1;
  TH1F* abs_lep__eta;
  TH1F* log_met_pt_to_ljet_pt;
  TH1F* lep_pt_ljet_to_lep_pt;

  TH1F* log_jets_pt_lep_pt;
  TH1F* TMVA_response;
  TH1F* log_jets_pt_ljet_pt;
  TH1F* log_ljet_CSV_ljet_pt;

  uhh2::Event::Handle<float> tt_tmva_response;
};
