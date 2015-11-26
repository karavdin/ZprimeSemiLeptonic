#include <UHH2/ZprimeSemiLeptonic/include/ZprimePostSelectionHists.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>

ZprimePostSelectionHists::ZprimePostSelectionHists(uhh2::Context& ctx, const std::string& dirname): uhh2::Hists(ctx, dirname){

  // wgt = book<TH1F>("weight", "event weight;event weight", 120, -6, 6);
 wgt = book<TH1F>("weight", "event weight;event weight", 1000, -2, 2);

  // PV
  pvN = book<TH1F>("pvN", "# of primary vertices;# of primary vertices", 60, 0, 60);

  // MUON
  muoN = book<TH1F>("muoN", "# of muons;# of muons", 20, 0, 20);
  muo1__pt = book<TH1F>("muo1__pt", "muon p_{T} [GeV];muon p_{T} [GeV]", 240, 0, 1200);
  muo1__eta = book<TH1F>("muo1__eta", "muon #eta;muon #eta", 60, -3, 3);
  muo1__minDR_jet = book<TH1F>("muo1__minDR_jet", "#DeltaR_{min}(#mu, jet);#DeltaR_{min}(#mu, jet)", 60, 0, 6);
  muo1__pTrel_jet = book<TH1F>("muo1__pTrel_jet", "p_{T, rel}(#mu, jet);p_{T, rel}(#mu, jet)", 180, 0, 180);
  muo1__minDR_topjet = book<TH1F>("muo1__minDR_topjet", "#DeltaR_{min}(#mu, topjet);#DeltaR_{min}(#mu, topjet)", 60, 0, 6);

  // ELECTRON
  eleN = book<TH1F>("eleN", "# of electrons;# of electrons", 20, 0, 20);
  ele1__pt = book<TH1F>("ele1__pt", "electron p_{T} [GeV];electron p_{T} [GeV]", 80, 0, 800);
  ele1__eta = book<TH1F>("ele1__eta", "electron #eta;electron #eta", 90, -3, 3);
  ele1__minDR_jet = book<TH1F>("ele1__minDR_jet", "#DeltaR_{min}(e, jet);#DeltaR_{min}(e, jet)", 60, 0, 6);
  ele1__pTrel_jet = book<TH1F>("ele1__pTrel_jet", "p_{T, rel}(e, jet);p_{T, rel}(e, jet)", 180, 0, 360);
  ele1__minDR_topjet = book<TH1F>("ele1__minDR_topjet", "#DeltaR_{min}(e, topjet);#DeltaR_{min}(e, topjet)", 60, 0, 6);
  ele1_mvaNonTrigV0 = book<TH1F>("ele1__mvaNonTrigV0", "mvaNonTrig; mvaNonTrig", 50,0,1);
  ele1_gsfTrack_trackerExpectedHitsInner_numberOfLostHits = book<TH1F>("ele1_gsfTrack_trackerExpectedHitsInner_numberOfLostHits","TrackerExpectedHitsInner_numberOfLostHits",10,0,10);
  ele1_dB = book<TH1F>("ele1_dB","Impact parameter dB; dB;",25,0,0.5);
  ele1_vx = book<TH1F>("ele1_vx","lepton vtx x;lepton vtx x;",50,0,0.2);
  ele1_vy = book<TH1F>("ele1_vy","lepton vtx y;lepton vtx y;",100,-0.2,0.2);
  lep__vtxXY = book<TH1F>("lep__vtxXY", "lep vtx #sqrt{(x+x_{0})^{2}+(y+y_{0})^{2}} [cm];lep vtx #sqrt{x^{2}+y^{2}}[cm]", 80, 0, 0.2);
  lep__vtxXY_trans = book<TH1F>("lep__vtxXY_trans", "log(|#sqrt{(x+x_{0})^{2}+(y+y_{0})^{2}}-R_{0}|);log(|#sqrt{(x+x_{0})^{2}+(y+y_{0})^{2}}-R_{0}|)", 150, -10, 5);
  ele1_vz = book<TH1F>("ele1_vz","lepton vtx z;lepton vtx z;",100,-20,20);
  ele1_effArea = book<TH1F>("ele1_effArea","lep effArea; eff Area",10,0,1.);
  ele1_HoverE = book<TH1F>("ele1_HoverE","H/E; H/E",100,0,0.3);
  ell1_EcalEnergy = book<TH1F>("ell1_EcalEnergy","Ecal energy; Ecal energy",100,0,3000);

  ele1__eta_mvaNonTrigV0 = book<TH2F>("ele1__eta_mvaNonTrigV0", " ;electron #eta; mvaNonTrigV0 ", 90, -3, 3, 20,0,1);

  ele1__pt_mvaNonTrigV0 = book<TH2F>("ele1__pt_mvaNonTrigV0", " ;electron p_{T} [GeV]; mvaNonTrigV0 ", 80, 0, 800, 20,0,1);


  // JET
  jetN = book<TH1F>("jetN", "# of jets;# of jets", 20, 0, 20);
  //  jet1__pt = book<TH1F>("jet1__pt", "jet p_{T} [GeV]; jet p_{T} [GeV]", 180, 0, 1800);
  jet1__pt = book<TH1F>("jet1__pt", "jet1 p_{T} [GeV]; jet1 p_{T} [GeV]", 50, 0, 1000);
  jet1__eta = book<TH1F>("jet1__eta", "jet1 #eta; jet1 #eta", 60, -3, 3);
  //  jet2__pt = book<TH1F>("jet2__pt", "jet p_{T} [GeV]; jet p_{T} [GeV]", 180, 0, 1800);
  jet2__pt = book<TH1F>("jet2__pt", "jet2 p_{T} [GeV]; jet2 p_{T} [GeV]", 50, 0, 1000);
  jet2__eta = book<TH1F>("jet2__eta", "jet2 #eta; jet2 #eta", 60, -3, 3);
  //  jet3__pt = book<TH1F>("jet3__pt", "jet p_{T} [GeV]; jet p_{T} [GeV]", 180, 0, 1800);
  jet3__pt = book<TH1F>("jet3__pt", "jet3 p_{T} [GeV]; jet3 p_{T} [GeV]", 50, 0, 1000);
  jet3__eta = book<TH1F>("jet3__eta", "jet3 #eta;jet3 #eta", 60, -3, 3);

  // TOPJET
  topjetN = book<TH1F>("topjetN", "# of topjets;# of topjets", 20, 0, 20);
  topjet1__pt = book<TH1F>("topjet1__pt", "topjet p_{T} [GeV];topjet p_{T} [GeV]", 180, 0, 1800);
  topjet1__eta = book<TH1F>("topjet1__eta", "topjet #eta;topjet #eta", 60, -3, 3);
  topjet2__pt = book<TH1F>("topjet2__pt", "topjet p_{T} [GeV]; topjet p_{T} [GeV]", 180, 0, 1800);
  topjet2__eta = book<TH1F>("topjet2__eta", "topjet #eta; topjet #eta", 60, -3, 3);

  // MET
  //  met__pt = book<TH1F>("met__pt", "MET [GeV];MET [GeV]", 100, 0, 1800);
  //  met__pt = book<TH1F>("met__pt", "MET [GeV];MET [GeV]", 7, 50, 550);
  met__pt = book<TH1F>("met__pt", "MET [GeV];MET [GeV]", 100, 50, 1050);
  met__phi = book<TH1F>("met__phi", "MET #phi;MET #phi", 72, -3.6, 3.6);
  htlep__pt = book<TH1F>("htlep__pt", "H_{T}^{lep} [GeV];H_{T}^{lep} [GeV]", 60, 0, 1200);
  met_VS_dphi_lep1 = book<TH2F>("met_VS_dphi_lep1", ";MET [GeV];#Delta#phi(MET, l1)", 180, 0, 1800, 60, 0, 3.6);
  met_VS_dphi_jet1 = book<TH2F>("met_VS_dphi_jet1", ";MET [GeV];#Delta#phi(MET, l1)", 180, 0, 1800, 60, 0, 3.6);
  met__sig = book<TH1F>("met__sig","MET significance; MET significance;",100,0,20);

  //Variables used in MVA for QCD suppression
  lep__fbrem = book<TH1F>("lep__fbrem", "lep fbrem;lep fbrem", 40, -1, 1);
  lep__DR_jet0 = book<TH1F>("ele__DR_jet0", "#DeltaR(e, jet0);#DeltaR(e, jet0)", 80, 0, 4.);
  jet0__DR_jet1 = book<TH1F>("jet0__DR_jet1", "#DeltaR(jet0, jet1);#DeltaR(jet0, jet1)", 80, 0, 4.);
  met__DPhi_lep = book<TH1F>("met__DPhi_lep", "#Delta#phi(MET, lep);#Delta#phi(MET, lep)", 30, 0, 3.15);
  lep__pTrel_jet1 = book<TH1F>("lep__pTrel_jet1", "p_{T, rel}(lep, jet1);p_{T, rel}(lep, jet1)", 50, 0, 100);
 
  Mt__lep_met = book<TH1F>("Mt__lep_met", "M_{T}(lep,MET) [GeV];M_{T}(lep,MET) [GeV]", 50, 0, 1000);

  logmet__pt = book<TH1F>("logmet__pt", "Log(MET) ;Log(MET)", 50, 0, 10);
  // acosmet__pt = book<TH1F>("acosmet__pt", "acos((MET-50)/950) ;acos((MET-50)/950)", 50, 0, 10);
  logjet1__pt = book<TH1F>("logjet1__pt", "Log(jet1 p_{T}); Log(jet1 p_{T})", 50, 0, 10);
  logele1__pt = book<TH1F>("logele1__pt", "Log(electron p_{T});Log(electron p_{T})", 50, 0, 10);
}

void ZprimePostSelectionHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.topjets && event.met);

  const double weight = event.weight;
  // std::cout<<"weight = "<<weight<<std::endl;
  wgt->Fill(weight);

  // PV
  pvN->Fill(event.pvs->size(), weight);

  // MUON
  const int muo_n(event.muons->size());
  muoN->Fill(muo_n, weight);
  // std::cout<<"Number of muons = "<<muo_n<<std::endl;
  if(muo_n>0){

    const Particle& p = event.muons->at(0);

    float minDR_jet(-1.), pTrel_jet(-1.);
    std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets)
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);

    muo1__pt->Fill(p.pt(), weight);
    muo1__eta->Fill(p.eta(), weight);
    muo1__minDR_jet->Fill(minDR_jet, weight);
    muo1__pTrel_jet->Fill(pTrel_jet, weight);
    muo1__minDR_topjet->Fill(minDR_topjet, weight);
  }

  // ELECTRON
  const int ele_n(event.electrons->size());
  eleN->Fill(ele_n, weight);
  // std::cout<<"Number of electrons = "<<ele_n<<std::endl;
  //  std::cout<<"Number of jets = "<<event.jets->size()<<std::endl;
  if(ele_n>0){

    //const Particle& p = event.electrons->at(0);
const Electron& p = event.electrons->at(0);
    //    std::cout<<"Number of jets = "<<event.jets->size()<<std::endl;
    float minDR_jet(-1.), pTrel_jet(-1.);
    std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets)
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);

    ele1__pt->Fill(p.pt(), weight);
    logele1__pt->Fill(log(p.pt()), weight);
    ele1__eta->Fill(p.eta(), weight);
    ele1__minDR_jet->Fill(minDR_jet, weight);
    ele1__pTrel_jet->Fill(pTrel_jet, weight);
    ele1__minDR_topjet->Fill(minDR_topjet, weight);
    ele1_mvaNonTrigV0->Fill(p.mvaNonTrigV0(), weight);
    ele1_gsfTrack_trackerExpectedHitsInner_numberOfLostHits->Fill(p.gsfTrack_trackerExpectedHitsInner_numberOfLostHits(), weight);
    ele1_dB->Fill(p.dB(), weight);
    ele1_HoverE->Fill(p.HoverE(), weight);
    ell1_EcalEnergy->Fill(p.EcalEnergy(), weight);

    if(!event.isRealData){
      ele1_vx->Fill(p.gsfTrack_vx()+0.04309,weight);
      ele1_vy->Fill(p.gsfTrack_vy()+0.09364,weight);
      // ele1_vx->Fill(p.gsfTrack_vx(),weight);
      // ele1_vy->Fill(p.gsfTrack_vy(),weight);
    }
    else{
    ele1_vx->Fill(p.gsfTrack_vx(),weight);
    ele1_vy->Fill(p.gsfTrack_vy(),weight);
    }
    ele1_vz->Fill(p.gsfTrack_vz(),weight);
    ele1_effArea->Fill(p.effArea(),weight);
    ele1__eta_mvaNonTrigV0->Fill(p.eta(),p.mvaNonTrigV0(), weight);
    ele1__pt_mvaNonTrigV0->Fill(p.pt(),p.mvaNonTrigV0(), weight);
  }

  // JET
  const int jet_n(event.jets->size());
  jetN->Fill(jet_n, weight);

  for(int i=0; i<std::min(3, jet_n); ++i){
    const Particle& p = event.jets->at(i);

    if(i == 0){

      jet1__pt ->Fill(p.pt() , weight);
      logjet1__pt->Fill(log(p.pt()) , weight);
      jet1__eta->Fill(p.eta(), weight);
    }
    else if(i == 1){

      jet2__pt ->Fill(p.pt() , weight);
      jet2__eta->Fill(p.eta(), weight);
    }
    else if(i == 2){

      jet3__pt ->Fill(p.pt() , weight);
      jet3__eta->Fill(p.eta(), weight);
    }
  }

  // TOPJET
  const int topjet_n(event.topjets->size());
  topjetN->Fill(topjet_n, weight);

  for(int i=0; i<std::min(2, topjet_n); ++i){
    const Particle& p = event.topjets->at(i);

    if(i == 0){

      topjet1__pt ->Fill(p.pt() , weight);
      topjet1__eta->Fill(p.eta(), weight);
    }
    else if(i == 1){

      topjet2__pt ->Fill(p.pt() , weight);
      topjet2__eta->Fill(p.eta(), weight);
    }
  }

  // MET
  met__pt ->Fill(event.met->pt() , weight);
  met__phi->Fill(event.met->phi(), weight);
  logmet__pt->Fill(log(event.met->pt()), weight);
  met__sig->Fill(event.met->mEtSig(),weight);

  //  acosmet__pt->Fill(acos((event.met->pt()-50.)/950.), weight);
  const Particle* lep1(0);
  float max_lep_pt(0.);
  for(const auto& l : *event.muons)     if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  for(const auto& l : *event.electrons) if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  if(lep1) htlep__pt->Fill(event.met->pt()+lep1->pt(), weight);

  /* triangular cuts vars */
  if(lep1)               met_VS_dphi_lep1->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, *lep1))            , weight);
  if(event.jets->size()) met_VS_dphi_jet1->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, event.jets->at(0))), weight);



  //Variables used in MVA for QCD suppression
 if(ele_n>0){

   const Particle *lep = &event.electrons->at(0);//ToDo: extend for case with muon(s)  in final state;
   lep__fbrem->Fill((event.electrons->at(0)).fbrem(), weight);
   //lep__vtxXY->Fill(hypot((event.electrons->at(0)).gsfTrack_vx(),(event.electrons->at(0)).gsfTrack_vy()), weight);
   if(!event.isRealData){ 
 //TEST: shift for agreement with DATA (RunII, 0.6 pb^-1)
      lep__vtxXY->Fill(hypot((event.electrons->at(0)).gsfTrack_vx()+0.04309,(event.electrons->at(0)).gsfTrack_vy()+0.09364),weight); 
      // acos_lep__vtxXY->Fill((((event.electrons->at(0)).gsfTrack_vx()+0.046)/hypot((event.electrons->at(0)).gsfTrack_vx()+0.046,(event.electrons->at(0)).gsfTrack_vy()+0.094)),weight); 
      lep__vtxXY_trans->Fill(log(fabs(hypot((event.electrons->at(0)).gsfTrack_vx()+0.04309,(event.electrons->at(0)).gsfTrack_vy()+0.09364)-0.1216)), weight);
    }
    else{
      lep__vtxXY->Fill(hypot((event.electrons->at(0)).gsfTrack_vx(),(event.electrons->at(0)).gsfTrack_vy()), weight);
      lep__vtxXY_trans->Fill(log(fabs(hypot((event.electrons->at(0)).gsfTrack_vx(),(event.electrons->at(0)).gsfTrack_vy())-0.1216)), weight);
      
   }
   //the closest to lepton jet
   // find jet with smallest angle to lepton (the closest jet to lepton)
   int jet_pos = 0;
   double dR_lep_cljet = 1e7;
   for(int i=1; i<jet_n; i++){//skip leading jet
     const Particle* jeti =  &event.jets->at(i);
     float dR_current = uhh2::deltaR(*lep, *jeti);
     if(dR_lep_cljet>dR_current){// min distance in eta-phi
       dR_lep_cljet = dR_current;      
       jet_pos = i;
     }
   }

   lep__DR_jet0->Fill(dR_lep_cljet, weight);
   const Particle*  jet =  &event.jets->at(jet_pos);    
   const Particle*  jet1 =  &event.jets->at(0); 
   jet0__DR_jet1->Fill(uhh2::deltaR(*jet, *jet1), weight);

 
   float dPhi_met_lep = fabs(uhh2::deltaPhi(*event.met, *lep));
   met__DPhi_lep->Fill(dPhi_met_lep, weight);
   lep__pTrel_jet1->Fill(pTrel(*lep, jet1), weight);
   
   float MwT = sqrt(2*fabs(lep->pt())*fabs(event.met->pt())*(1-cos(dPhi_met_lep)));
   Mt__lep_met->Fill(MwT, weight);
 }
  return;
}
