#pragma once

#include <string>

#include <TH1F.h>
#include <TH2F.h>

#include <UHH2/core/include/Hists.h>
#include <UHH2/core/include/Event.h>

class ZprimePostSelectionHists : public uhh2::Hists {

 public:
  explicit ZprimePostSelectionHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

 private:
  TH1F* wgt;

  // PV 
  TH1F* pvN;

  // MUON
  TH1F* muoN;
  TH1F* muo1__pt;
  TH1F* muo1__eta;
  TH1F* muo1__minDR_jet;
  TH1F* muo1__pTrel_jet;
  TH1F* muo1__minDR_topjet;

  // ELECTRON
  TH1F* eleN;
  TH1F* ele1__pt;
  TH1F* ele1__eta;
  TH1F* ele1__minDR_jet;
  TH1F* ele1__pTrel_jet;
  TH1F* ele1__minDR_topjet;
  TH1F* ele1_mvaNonTrigV0;
  TH1F* ele1_gsfTrack_trackerExpectedHitsInner_numberOfLostHits;
  TH1F* ele1_dB;
  TH1F* ele1_vx;   TH1F* ele1_vy;   TH1F* ele1_vz;
  TH1F* ele1_effArea;
  TH1F* ele1_HoverE;
  TH1F* ell1_EcalEnergy;
  TH2F* ele1__eta_mvaNonTrigV0;   
  TH2F* ele1__pt_mvaNonTrigV0;
  // JET
  TH1F* jetN;
  TH1F* jet1__pt;
  TH1F* jet1__eta;
  TH1F* jet2__pt;
  TH1F* jet2__eta;
  TH1F* jet3__pt;
  TH1F* jet3__eta;

  // TOPJET
  TH1F* topjetN;
  TH1F* topjet1__pt;
  TH1F* topjet1__eta;
  TH1F* topjet2__pt;
  TH1F* topjet2__eta;

  // MET
  TH1F* met__pt;
  TH1F* met__phi;
  TH1F* htlep__pt;
  TH2F* met_VS_dphi_lep1;
  TH2F* met_VS_dphi_jet1;
  TH1F* met__sig;

  //Variables used in MVA for QCD suppression
  TH1F* lep__fbrem;
  TH1F* lep__DR_jet0;
  TH1F* jet0__DR_jet1;
  TH1F* met__DPhi_lep;
  TH1F* lep__pTrel_jet1;
  TH1F* lep__vtxXY;
  TH1F* acos_lep__vtxXY;
  TH1F* lep__vtxXY_trans;
  TH1F* Mt__lep_met;
  //Let's make things more smooth
  TH1F* logmet__pt;
  //  TH1F* acosmet__pt;
  TH1F* logjet1__pt;
  TH1F* logele1__pt;

};
