#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/TopJetIds.h>

TTbarLJHists::TTbarLJHists(uhh2::Context& ctx, const std::string& dirname):
  HistsBASE(ctx, dirname), tjet_ID_(TopTagID_NO()), tjet_minDR_jet_(0.){
  init();
  tt_tmva_response  = ctx.get_handle<float>("TMVA_response");
}

TTbarLJHists::TTbarLJHists(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float dr__ttag_jet):
  HistsBASE(ctx, dirname), tjet_ID_(ttag_id), tjet_minDR_jet_(dr__ttag_jet){
  init();
  tt_tmva_response  = ctx.get_handle<float>("TMVA_response");
}



void TTbarLJHists::init(){

  book_TH1F("wgt", 120, -6, 6);

  // PV
  book_TH1F("pvN", 120, 0, 120);

  // MUON
  book_TH1F("muoN"                 , 20, 0, 20);

  book_TH1F("muo1__charge"         , 5, -2, 3);
  book_TH1F("muo1__pt"             , 360, 0, 1800);
  book_TH1F("muo1__eta"            , 60, -3, 3);
  book_TH1F("muo1__phi"            , 60, -3.15, 3.15);
  book_TH1F("muo1__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("muo1__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("muo1__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("muo1__minDR_jet"      , 60, 0, 6);
  book_TH1F("muo1__pTrel_jet"      , 100, 0, 500);
  book_TH1F("muo1__minDR_topjet"   , 60, 0, 6);
  book_TH2F("muo1__minDR_jet__vs__muo1__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("muo1__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("muo1__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);

  book_TH1F("muo2__charge"         , 5, -2, 3);
  book_TH1F("muo2__pt"             , 240, 0, 1200);
  book_TH1F("muo2__eta"            , 60, -3, 3);
  book_TH1F("muo2__phi"            , 60, -3.15, 3.15);
  book_TH1F("muo2__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("muo2__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("muo2__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("muo2__minDR_jet"      , 60, 0, 6);
  book_TH1F("muo2__pTrel_jet"      , 100, 0, 500);
  book_TH1F("muo2__minDR_topjet"   , 60, 0, 6);
  book_TH2F("muo2__minDR_jet__vs__muo2__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("muo2__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("muo2__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);

  // ELECTRON
  book_TH1F("eleN"                 , 20, 0, 20);

  book_TH1F("ele1__charge"         , 5, -2, 3);
  book_TH1F("ele1__pt"             , 360, 0, 1800);
  book_TH1F("ele1__eta"            , 60, -3, 3);
  book_TH1F("ele1__etaSC"          , 60, -3, 3);
  book_TH1F("ele1__phi"            , 60, -3.15, 3.15);
  book_TH1F("ele1__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("ele1__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("ele1__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("ele1__minDR_jet"      , 60, 0, 6);
  book_TH1F("ele1__pTrel_jet"      , 100, 0, 500);
  book_TH1F("ele1__minDR_topjet"   , 60, 0, 6);
  book_TH2F("ele1__minDR_jet__vs__ele1__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("ele1__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("ele1__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);

  book_TH1F("ele2__charge"         , 5, -2, 3);
  book_TH1F("ele2__pt"             , 240, 0, 1200);
  book_TH1F("ele2__eta"            , 60, -3, 3);
  book_TH1F("ele2__etaSC"          , 60, -3, 3);
  book_TH1F("ele2__phi"            , 60, -3.15, 3.15);
  book_TH1F("ele2__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("ele2__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("ele2__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("ele2__minDR_jet"      , 60, 0, 6);
  book_TH1F("ele2__pTrel_jet"      , 100, 0, 500);
  book_TH1F("ele2__minDR_topjet"   , 60, 0, 6);
  book_TH2F("ele2__minDR_jet__vs__ele2__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("ele2__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("ele2__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);


  // //electrons classified according to CMS-EGM-13-001
  book_TH1F("ele1__eta_Gold",180,-3,3);
  book_TH1F("ele1__eta_BigBrem",180,-3,3);
  book_TH1F("ele1__eta_Shower",180,-3,3);
  book_TH1F("ele1__eta_BadTrk",180,-3,3);
  book_TH1F("ele1__eta_Gap",180,-3,3);
  book_TH1F("ele1__eta_Unknown",180,-3,3);

  book_TH1F("ele2__eta_Gold",180,-3,3);
  book_TH1F("ele2__eta_BigBrem",180,-3,3);
  book_TH1F("ele2__eta_Shower",180,-3,3);
  book_TH1F("ele2__eta_BadTrk",180,-3,3);
  book_TH1F("ele2__eta_Gap",180,-3,3);
  book_TH1F("ele2__eta_Unknown",180,-3,3);

  // book_TH1F("ele1__N_SCclusters",10,0,10);//Number of clusters in Super Cluster
  // book_TH1F("ele2__N_SCclusters",10,0,10);

  // //For MVA electron ID check
  // book_TH2F("ele1__eta_mvaNonTrigV0", 180, -3, 3, 20,0,1);
  // book_TH2F("ele1__pt_mvaNonTrigV0", 80, 0, 800, 20,0,1);
  // book_TH2F("ele1__eta_mvaTrigV0", 180, -3, 3, 20,0,1);
  // book_TH2F("ele1__pt_mvaTrigV0", 80, 0, 800, 20,0,1);

  // book_TH2F("ele2__eta_mvaNonTrigV0", 180, -3, 3, 20,0,1);
  // book_TH2F("ele2__pt_mvaNonTrigV0", 80, 0, 800, 20,0,1);
  // book_TH2F("ele2__eta_mvaTrigV0", 180, -3, 3, 20,0,1);
  // book_TH2F("ele2__pt_mvaTrigV0", 80, 0, 800, 20,0,1);

  // //For HEEP electron ID check
  // book_TH2F("ele1__eta_HEEP",180, -3, 3, 20,0,1); //standart HEEP tag (with isolation cuts)
  // book_TH2F("ele1__pt_HEEP",80, 0, 800, 20,0,1);//standart HEEP tag (with isolation cuts)

  // book_TH2F("ele2__eta_HEEP",180, -3, 3, 20,0,1); //standart HEEP tag (with isolation cuts)
  // book_TH2F("ele2__pt_HEEP",80, 0, 800, 20,0,1);//standart HEEP tag (with isolation cuts)

  // //VARs for HEEP electron ID w/t isolation cuts
  book_TH1F("ele1__isEcalDriven",3,0,2);
  book_TH1F("ele1__dxy",100,-10,10);
  book_TH1F("ele1__dEtaInSeed",180,-3,3);
  //ToDo: change to ratio of values as used in HEEP!
  book_TH1F("ele1__full5x5_e1x5",1000,0,1000);
  book_TH1F("ele1__full5x5_e5x5",1000,0,1000);
  book_TH1F("ele1__full5x5_e2x5Max",1000,0,1000);

  book_TH1F("ele2__isEcalDriven",3,0,2);
  book_TH1F("ele2__dxy",100,-10,10);
  book_TH1F("ele2__dEtaInSeed",180,-3,3);
  book_TH1F("ele2__full5x5_e1x5",1000,0,1000);
  book_TH1F("ele2__full5x5_e5x5",1000,0,1000);
  book_TH1F("ele2__full5x5_e2x5Max",1000,0,1000);

  book_TH2F("ele1__pt_eta",40, 0, 800,60, -3, 3);
  book_TH2F("ele2__pt_eta",40, 0, 800,60, -3, 3);


  //vars planned to be used in Homemade MVA for QCD suppression
  lep__fbrem = book<TH1F>("lep__fbrem", "lep fbrem;lep fbrem", 100, -2, 3);
  lep__DR_jet0 = book<TH1F>("ele__DR_jet0", "#DeltaR(e, jet0);#DeltaR(e, jet0)", 80, 0, 4.);
  log_lep__DR_jet0 = book<TH1F>("log_ele__DR_jet0", "Log(#DeltaR(e, jet0));Log(#DeltaR(e, jet0))", 50, -10, 10);
  jet0__DR_jet1 = book<TH1F>("jet0__DR_jet1", "#DeltaR(jet0, jet1);#DeltaR(jet0, jet1)", 80, 0, 4.);
  trans_jet0__DR_jet1 = book<TH1F>("trans_jet0__DR_jet1", "Log(|#Delta R(jet0, jet1)-#pi|/#pi); Log(|#Delta R(jet0, jet1)-#pi|/#pi)", 50, -10, 10.);
  met__DPhi_lep = book<TH1F>("met__DPhi_lep", "#Delta#phi(MET, lep);#Delta#phi(MET, lep)", 30, 0, 3.15);
  lep__pTrel_jet1 = book<TH1F>("lep__pTrel_jet1", "p_{T, rel}(lep, jet1);p_{T, rel}(lep, jet1)", 100, 0, 1000);
  log_lep__pTrel_jet1 = book<TH1F>("log_lep__pTrel_jet1", "Log(p_{T, rel}(lep, jet1));Log(p_{T, rel}(lep, jet1))", 60, -10, 20);
 
  Mt__lep_met = book<TH1F>("Mt__lep_met", "M_{T}(lep,MET) [GeV];M_{T}(lep,MET) [GeV]", 100, 0, 500);

  logmet__pt = book<TH1F>("logmet__pt", "Log(MET) ;Log(MET)", 50, -10, 10);
  logjet1__pt = book<TH1F>("logjet1__pt", "Log(jet1 p_{T}); Log(jet1 p_{T})", 50, 0, 10);
  logele1__pt = book<TH1F>("logele1__pt", "Log(electron p_{T});Log(electron p_{T})", 50, 0, 10);
  lep__vtxXY = book<TH1F>("lep__vtxXY", "lep vtx #sqrt{(x+x_{0})^{2}+(y+y_{0})^{2}} [cm];lep vtx #sqrt{x^{2}+y^{2}}[cm]", 80, 0, 0.2);
  lep__vtxXY_trans = book<TH1F>("lep__vtxXY_trans", "log(|#sqrt{(x+x_{0})^{2}+(y+y_{0})^{2}}-R_{0}|);log(|#sqrt{(x+x_{0})^{2}+(y+y_{0})^{2}}-R_{0}|)", 150, -10, 5);

  abs_lep__eta = book<TH1F>("abs_lep__eta", "|lep #eta|;|lep #eta|", 80, 0, 4.);
  log_met_pt_to_ljet_pt =  book<TH1F>("log_met_pt_to_ljet_pt", "log(MET/jet1 p_{T});log(MET/jet1 p_{T})", 100, -10, 10.);
  lep_pt_ljet_to_lep_pt = book<TH1F>("lep_pt_ljet_to_lep_pt", "p_{T, rel}(lep, jet 1)/lep p_{T};p_{T, rel}(lep, jet 1)/lep p_{T}", 100,0,10.);
  log_jets_pt_lep_pt = book<TH1F>("log_jets_pt_lep_pt", "(sum of jets p_{T})/lep p_{T};(sum of jets p_{T})/lep p_{T}", 100,-10,10.);
  log_jets_pt_ljet_pt = book<TH1F>("log_jets_pt_ljet_pt", "(sum of jets p_{T})/jet1 p_{T};(sum of jets p_{T})/jet1 p_{T}", 100,0,10.);
  log_ljet_CSV_ljet_pt = book<TH1F>("log_ljet_CSV_ljet_pt", "log(jet1 CSV/jet1 p_{T});log(jet1 CSV/jet1 p_{T})", 100,-12.,0.);

  TMVA_response = book<TH1F>("TMVA_response", "TMVA response", 50,-0.2,1.8);
  // JET
  book_TH1F("jetN"              , 20, 0, 20);
  book_TH1F("jetN__pt030_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt050_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt100_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt150_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt200_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt250_eta2p4", 20, 0, 20);
  book_TH1F("jetN__CSVL"        , 10, 0, 10);
  book_TH1F("jetN__CSVM"        , 10, 0, 10);
  book_TH1F("jetN__CSVT"        , 10, 0, 10);

  book_TH1F("jetA__maxCSV1", 120, 0, 1.2);
  book_TH1F("jetA__maxCSV2", 120, 0, 1.2);
  book_TH1F("jetA__maxCSV3", 120, 0, 1.2);

  book_TH1F("jet1__pt" , 90, 0, 1800);
  book_TH1F("jet1__eta", 60, -3, 3);
  book_TH1F("jet1__phi", 60, -3.15, 3.15);
  book_TH1F("jet1__M"  , 360, 0, 360);
  book_TH1F("jet1__CSV", 60, 0, 1.2);

  book_TH1F("jet2__pt" , 90, 0, 1800);
  book_TH1F("jet2__eta", 60, -3, 3);
  book_TH1F("jet2__phi", 60, -3.15, 3.15);
  book_TH1F("jet2__M"  , 360, 0, 360);
  book_TH1F("jet2__CSV", 60, 0, 1.2);

  book_TH1F("jet3__pt" , 90,  0, 1800);
  book_TH1F("jet3__eta", 60, -3, 3);
  book_TH1F("jet3__phi", 60, -3.15, 3.15);
  book_TH1F("jet3__M"  , 360, 0, 360);
  book_TH1F("jet3__CSV", 60, 0, 1.2);

  book_TH1F("jetN__pt" , 90, 0, 1800);

  // TOPJET
  book_TH1F("topjetN", 20, 0, 20);

  book_TH1F("topjet1__pt" , 90,  0, 1800);
  book_TH1F("topjet1__eta", 60, -3, 3);
  book_TH1F("topjet1__phi", 60, -3.15, 3.15);
  book_TH1F("topjet1__CSV", 120, 0, 1.2);
  book_TH1F("topjet2__pt" , 180,  0, 1800);
  book_TH1F("topjet2__eta", 60, -3, 3);
  book_TH1F("topjet2__phi", 60, -3.15, 3.15);
  book_TH1F("topjet2__CSV", 120, 0, 1.2);

  // TOPTAG
  book_TH1F("toptagN"              , 20, 0, 20);

  book_TH1F("toptag1__pt"          , 180, 0, 1800);
  book_TH1F("toptag1__eta"         , 60, -3, 3);
  book_TH1F("toptag1__phi"         , 60, -3.15, 3.15);
  book_TH1F("toptag1__M"           , 360, 90, 450);
  book_TH1F("toptag1__Mgro"        , 360, 90, 450);
  book_TH1F("toptag1__Mpru"        , 360, 90, 450);
  book_TH1F("toptag1__Msdp"        , 360, 90, 450);
  book_TH1F("toptag1__mmin"        , 40, 0, 200);
  book_TH1F("toptag1__tau2"        , 24, 0, 1.2);
  book_TH1F("toptag1__tau3"        , 24, 0, 1.2);
  book_TH1F("toptag1__tau32"       , 24, 0, 1.2);
  book_TH1F("toptag1__CSV"         , 120, 0, 1.2);
  book_TH1F("toptag1__subjN"       , 4, 2, 6);
  book_TH1F("toptag1__subj1__pt"   , 180, 0, 1800);
  book_TH1F("toptag1__subj1__eta"  , 60, -3, 3);
  book_TH1F("toptag1__subj2__pt"   , 180, 0, 900);
  book_TH1F("toptag1__subj2__eta"  , 60, -3, 3);
  book_TH1F("toptag1__subj3__pt"   , 180, 0, 900);
  book_TH1F("toptag1__subj3__eta"  , 60, -3, 3);
  book_TH1F("toptag1__subj_minDR"  , 20, 0, 2);
  book_TH1F("toptag1__subj_maxCSV1", 120, 0, 1.2);
  book_TH1F("toptag1__subj_maxCSV2", 120, 0, 1.2);
  book_TH1F("toptag1__subj_maxCSV3", 120, 0, 1.2);
  book_TH1F("toptag2__pt"          , 180, 0, 1800);
  book_TH1F("toptag2__eta"         , 60, -3, 3);
  book_TH1F("toptag2__phi"         , 60, -3.15, 3.15);
  book_TH1F("toptag2__M"           , 360, 90, 450);
  book_TH1F("toptag2__CSV"         , 120, 0, 1.2);

  // MET
  book_TH1F("met__pt" , 60, 0, 600);
  //  book_TH1F("met__pt" , 20, 0, 60); //TEST: for QCD sideband
  book_TH1F("met__phi", 60, -3.15, 3.15);
  book_TH1F("wlep__ht", 180, 0, 1800);
  book_TH1F("wlep__pt", 180, 0, 1800);
  book_TH1F("wlep__Mt", 180, 0,  360);
  book_TH2F("met__pt__vs__dphi_met_lep1", 180, 0, 1800, 60, 0, 3.15);
  book_TH2F("met__pt__vs__dphi_met_jet1", 180, 0, 1800, 60, 0, 3.15);

  return;
}

void TTbarLJHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.topjets && event.met);

  const float weight(event.weight);
  H1("wgt")->Fill(weight);
  //  std::cout<<"Message from Hist: weight="<<weight<<std::endl;
  // PV
  H1("pvN")->Fill(event.pvs->size(), weight);

   // MUON
  const int muoN(event.muons->size());
  H1("muoN")->Fill(muoN, weight);

  for(int i=0; i<std::min(2, muoN); ++i){

    const Muon& p = event.muons->at(i);

    H1("muo"+std::to_string(i+1)+"__charge")->Fill(p.charge(), weight);
    H1("muo"+std::to_string(i+1)+"__pt")    ->Fill(p.pt()    , weight);
    H1("muo"+std::to_string(i+1)+"__eta")   ->Fill(p.eta()   , weight);
    H1("muo"+std::to_string(i+1)+"__phi")   ->Fill(p.phi()   , weight);

    H2("muo"+std::to_string(i+1)+"__pt__vs__met__pt")->Fill(p.pt(), event.met->pt(), weight);

    const float pfR040Iso_dbeta = p.relIso();
    const float pfMINIIso_dbeta = util::pfMINIIso(p, "delta-beta");
    const float pfMINIIso_pfwgt = util::pfMINIIso(p, "pf-weight");

    H1("muo"+std::to_string(i+1)+"__pfIso_dbeta")    ->Fill(pfR040Iso_dbeta, weight);
    H1("muo"+std::to_string(i+1)+"__pfMINIIso_dbeta")->Fill(pfMINIIso_dbeta, weight);
    H1("muo"+std::to_string(i+1)+"__pfMINIIso_pfwgt")->Fill(pfMINIIso_pfwgt, weight);

    float minDR_jet(-1.), pTrel_jet(-1.);
    if(p.has_tag(Muon::twodcut_dRmin) && p.has_tag(Muon::twodcut_pTrel)){

      minDR_jet = p.get_tag(Muon::twodcut_dRmin);
      pTrel_jet = p.get_tag(Muon::twodcut_pTrel);
    }
    else std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    H1("muo"+std::to_string(i+1)+"__minDR_jet")->Fill(minDR_jet, weight);
    H1("muo"+std::to_string(i+1)+"__pTrel_jet")->Fill(pTrel_jet, weight);
    H2("muo"+std::to_string(i+1)+"__minDR_jet__vs__muo"+std::to_string(i+1)+"__pTrel_jet")->Fill(minDR_jet, pTrel_jet, weight);
    H2("muo"+std::to_string(i+1)+"__pTrel_jet__vs__met__pt")->Fill(pTrel_jet, event.met->pt(), weight);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets){
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);
    }

    H1("muo"+std::to_string(i+1)+"__minDR_topjet")->Fill(minDR_topjet, weight);
  }
  
  // ELECTRON
  const int eleN(event.electrons->size());
  H1("eleN")->Fill(eleN, weight);

  for(int i=0; i<std::min(2, eleN); ++i){

    const Electron& p = event.electrons->at(i);

    H1("ele"+std::to_string(i+1)+"__charge")->Fill(p.charge()          , weight);
    H1("ele"+std::to_string(i+1)+"__pt")    ->Fill(p.pt()              , weight);
    H1("ele"+std::to_string(i+1)+"__eta")   ->Fill(p.eta()             , weight);
    H1("ele"+std::to_string(i+1)+"__etaSC") ->Fill(p.supercluster_eta(), weight);
    H1("ele"+std::to_string(i+1)+"__phi")   ->Fill(p.phi()             , weight);
    if(i<1) abs_lep__eta->Fill(fabs(p.eta())             , weight);
    H2("ele"+std::to_string(i+1)+"__pt__vs__met__pt")->Fill(p.pt(), event.met->pt(), weight);
    H2("ele"+std::to_string(i+1)+"__pt_eta")->Fill(p.pt(), p.eta(), weight);

    const float pfR030Iso_dbeta = p.relIsodb();
    const float pfMINIIso_dbeta = util::pfMINIIso(p, "delta-beta");
    const float pfMINIIso_pfwgt = util::pfMINIIso(p, "pf-weight");

    H1("ele"+std::to_string(i+1)+"__pfIso_dbeta")    ->Fill(pfR030Iso_dbeta, weight);
    H1("ele"+std::to_string(i+1)+"__pfMINIIso_dbeta")->Fill(pfMINIIso_dbeta, weight);
    H1("ele"+std::to_string(i+1)+"__pfMINIIso_pfwgt")->Fill(pfMINIIso_pfwgt, weight);

    float minDR_jet(-1.), pTrel_jet(-1.);
    if(p.has_tag(Electron::twodcut_dRmin) && p.has_tag(Electron::twodcut_pTrel)){

      minDR_jet = p.get_tag(Electron::twodcut_dRmin);
      pTrel_jet = p.get_tag(Electron::twodcut_pTrel);
    }
    else std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    H1("ele"+std::to_string(i+1)+"__minDR_jet")->Fill(minDR_jet, weight);
    H1("ele"+std::to_string(i+1)+"__pTrel_jet")->Fill(pTrel_jet, weight);
    H2("ele"+std::to_string(i+1)+"__minDR_jet__vs__ele"+std::to_string(i+1)+"__pTrel_jet")->Fill(minDR_jet, pTrel_jet, weight);
    H2("ele"+std::to_string(i+1)+"__pTrel_jet__vs__met__pt")->Fill(pTrel_jet, event.met->pt(), weight);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets){
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);
    }

    H1("ele"+std::to_string(i+1)+"__minDR_topjet")->Fill(minDR_topjet, weight);

    // H2("ele"+std::to_string(i+1)+"__eta_mvaNonTrigV0")->Fill(p.eta(), p.mvaNonTrigV0(), weight);
    // H2("ele"+std::to_string(i+1)+"__pt_mvaNonTrigV0")->Fill(p.pt(), p.mvaNonTrigV0(), weight);
    // H2("ele"+std::to_string(i+1)+"__eta_mvaTrigV0")->Fill(p.eta(), p.mvaTrigV0(), weight);
    // H2("ele"+std::to_string(i+1)+"__pt_mvaTrigV0")->Fill(p.pt(), p.mvaTrigV0(), weight);

    // H2("ele"+std::to_string(i+1)+"__eta_HEEP")->Fill(p.eta(), p.get_tag(p.tagname2tag("heepElectronID_HEEPV60")), weight);
    // H2("ele"+std::to_string(i+1)+"__pt_HEEP")->Fill(p.pt(), p.get_tag(p.tagname2tag("heepElectronID_HEEPV60")), weight);

    // new vars in ntuples
    int EMclass= p.Class();
    if(EMclass==-1) H1("ele"+std::to_string(i+1)+"__eta_Unknown")->Fill(p.eta(), weight);
    if(EMclass==0) H1("ele"+std::to_string(i+1)+"__eta_Gold")->Fill(p.eta(), weight);
    if(EMclass==1) H1("ele"+std::to_string(i+1)+"__eta_BigBrem")->Fill(p.eta(), weight);
    if(EMclass==2) H1("ele"+std::to_string(i+1)+"__eta_BadTrk")->Fill(p.eta(), weight);
    if(EMclass==3) H1("ele"+std::to_string(i+1)+"__eta_Shower")->Fill(p.eta(), weight);
    if(EMclass==4) H1("ele"+std::to_string(i+1)+"__eta_Gap")->Fill(p.eta(), weight);
    H1("ele"+std::to_string(i+1)+"__N_SCclusters")->Fill(p.Nclusters(),weight);

    H1("ele"+std::to_string(i+1)+"__isEcalDriven")->Fill(p.isEcalDriven(),weight);
    H1("ele"+std::to_string(i+1)+"__dxy")->Fill(p.dxy(),weight);
    H1("ele"+std::to_string(i+1)+"__dEtaInSeed")->Fill(p.dEtaInSeed(),weight);
    H1("ele"+std::to_string(i+1)+"__full5x5_e1x5")->Fill(p.full5x5_e1x5(),weight);
    H1("ele"+std::to_string(i+1)+"__full5x5_e5x5")->Fill(p.full5x5_e5x5(),weight);
    H1("ele"+std::to_string(i+1)+"__full5x5_e2x5Max")->Fill(p.full5x5_e2x5Max(),weight); 
  }
  if(eleN>0){
    const Particle *lep = &event.electrons->at(0);//ToDo: extend for case with muon(s)  in final state;
   lep__fbrem->Fill((event.electrons->at(0)).fbrem(), weight);
   logele1__pt->Fill(log((event.electrons->at(0)).pt()),weight);
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
   int jet_n(event.jets->size());
   for(int i=1; i<jet_n; i++){//skip leading jet
     const Particle* jeti =  &event.jets->at(i);
     float dR_current = uhh2::deltaR(*lep, *jeti);
     if(dR_lep_cljet>dR_current){// min distance in eta-phi
       dR_lep_cljet = dR_current;      
       jet_pos = i;
     }
   }

   lep__DR_jet0->Fill(dR_lep_cljet, weight);
   log_lep__DR_jet0->Fill(log(dR_lep_cljet), weight);
   const Particle*  jet =  &event.jets->at(jet_pos);    
   const Particle*  jet1 =  &event.jets->at(0); 
   jet0__DR_jet1->Fill(uhh2::deltaR(*jet, *jet1), weight);
   trans_jet0__DR_jet1->Fill(log(fabs((uhh2::deltaR(*jet, *jet1)-3.14)/3.14)), weight);
   logjet1__pt->Fill(log(jet1->pt()),weight);
 
   float dPhi_met_lep = fabs(uhh2::deltaPhi(*event.met, *lep));
   met__DPhi_lep->Fill(dPhi_met_lep, weight);
   lep__pTrel_jet1->Fill(pTrel(*lep, jet1), weight);
   lep_pt_ljet_to_lep_pt->Fill((pTrel(*lep, jet1)/lep->pt()), weight);
   log_lep__pTrel_jet1->Fill(log(pTrel(*lep, jet1)), weight);
   log_met_pt_to_ljet_pt->Fill(log(event.met->pt()/jet1->pt()),weight);

   float MwT = sqrt(2*fabs(lep->pt())*fabs(event.met->pt())*(1-cos(dPhi_met_lep)));
   Mt__lep_met->Fill(MwT, weight);
  }

  //  std::cout<<"Message from Hist: jetN="<<event.jets->size()<<std::endl;
  // JET
  int jetN(event.jets->size());
  int jetN__pt030_eta2p4(0);
  int jetN__pt050_eta2p4(0);
  int jetN__pt100_eta2p4(0);
  int jetN__pt150_eta2p4(0);
  int jetN__pt200_eta2p4(0);
  int jetN__pt250_eta2p4(0);

  float jets_pt = 0;
  for(int i=0; i<jetN; ++i){

    const Jet& p = event.jets->at(i);
    jets_pt +=p.pt();
    if(p.pt() >  30. && fabs(p.eta()) < 2.4) ++jetN__pt030_eta2p4;
    if(p.pt() >  50. && fabs(p.eta()) < 2.4) ++jetN__pt050_eta2p4;
    if(p.pt() > 100. && fabs(p.eta()) < 2.4) ++jetN__pt100_eta2p4;
    if(p.pt() > 150. && fabs(p.eta()) < 2.4) ++jetN__pt150_eta2p4;
    if(p.pt() > 200. && fabs(p.eta()) < 2.4) ++jetN__pt200_eta2p4;
    if(p.pt() > 250. && fabs(p.eta()) < 2.4) ++jetN__pt250_eta2p4;

    if(i > 2) continue;

    H1("jet"+std::to_string(i+1)+"__pt") ->Fill(p.pt()                          , weight);
    H1("jet"+std::to_string(i+1)+"__eta")->Fill(p.eta()                         , weight);
    H1("jet"+std::to_string(i+1)+"__phi")->Fill(p.phi()                         , weight);
    H1("jet"+std::to_string(i+1)+"__M")  ->Fill(p.v4().M()                      , weight);
    H1("jet"+std::to_string(i+1)+"__CSV")->Fill(p.btag_combinedSecondaryVertex(), weight);
  }
  //  std::cout<<"Message from Hist: AGAIN jetN="<<jetN<<std::endl;
  H1("jetN")              ->Fill(jetN              , weight);
  H1("jetN__pt030_eta2p4")->Fill(jetN__pt030_eta2p4, weight);
  H1("jetN__pt050_eta2p4")->Fill(jetN__pt050_eta2p4, weight);
  H1("jetN__pt100_eta2p4")->Fill(jetN__pt100_eta2p4, weight);
  H1("jetN__pt150_eta2p4")->Fill(jetN__pt150_eta2p4, weight);
  H1("jetN__pt200_eta2p4")->Fill(jetN__pt200_eta2p4, weight);
  H1("jetN__pt250_eta2p4")->Fill(jetN__pt250_eta2p4, weight);
  H1("jetN__pt")->Fill(jets_pt,weight);
  if(eleN>0) log_jets_pt_lep_pt->Fill(log(jets_pt/(event.electrons->at(0)).pt()),weight);

  std::vector<float> jets_CSV;
  jets_CSV.reserve(event.jets->size());
  for(const auto& j : *event.jets){ 
  // for(int i=0; i<jetN; ++i){
  //   const Jet& j = event.jets->at(i);
    // std::cout<<"Message from Hist: j(i)"<<i<<std::endl;
    // std::cout<<"Message from Hist: j.btag_combinedSecondaryVertex()="<<j.btag_combinedSecondaryVertex()<<std::endl;
    jets_CSV.push_back(j.btag_combinedSecondaryVertex());
  }
  std::sort(jets_CSV.begin(), jets_CSV.end(), [](const float s1, const float s2){return s1 > s2;});

  //  std::cout<<"Message from Hist: jets_CSV="<<jets_CSV.size()<<std::endl;

  int jetN__CSVL(0), jetN__CSVM(0), jetN__CSVT(0);
  for(unsigned int i=0; i<jets_CSV.size(); ++i){

    const float& csv = jets_CSV.at(i);

    if(csv > 0.605) ++jetN__CSVL;
    if(csv > 0.890) ++jetN__CSVM;
    if(csv > 0.970) ++jetN__CSVT;

    if(i > 2) continue;

    H1("jetA__maxCSV"+std::to_string(i+1))->Fill(jets_CSV.at(i), weight);
  }

  H1("jetN__CSVL")->Fill(jetN__CSVL, weight);
  H1("jetN__CSVM")->Fill(jetN__CSVM, weight);
  H1("jetN__CSVT")->Fill(jetN__CSVT, weight);

  log_jets_pt_ljet_pt->Fill(log((event.jets->at(0)).btag_combinedSecondaryVertex()/(event.jets->at(0)).pt()),weight);
  //


  //  std::cout<<"Message from Hist: TopjetN="<<event.topjets->size()<<std::endl;
  // TOPJET
  const int topjetN(event.topjets->size());
  H1("topjetN")->Fill(topjetN, weight);

  for(int i=0; i<std::min(2, topjetN); ++i){

    const Jet& p = event.topjets->at(i);

    H1("topjet"+std::to_string(i+1)+"__pt") ->Fill(p.pt()                          , weight);
    H1("topjet"+std::to_string(i+1)+"__eta")->Fill(p.eta()                         , weight);
    H1("topjet"+std::to_string(i+1)+"__phi")->Fill(p.phi()                         , weight);
    H1("topjet"+std::to_string(i+1)+"__CSV")->Fill(p.btag_combinedSecondaryVertex(), weight);
  }

  // TOPTAG
  std::vector<TopJet> toptags;
  for(unsigned int i=0; i<event.topjets->size(); ++i){

    const TopJet& tjet = event.topjets->at(i);
    if(tjet_ID_(tjet, event)) toptags.push_back(tjet);
  }

  const int toptagN(toptags.size());
  H1("toptagN")->Fill(toptagN, weight);

  sort_by_pt<TopJet>(toptags);
  for(int i=0; i<std::min(2, toptagN); ++i){

    const TopJet& tj = toptags.at(i);

    H1("toptag"+std::to_string(i+1)+"__pt") ->Fill(tj.pt()                          , weight);
    H1("toptag"+std::to_string(i+1)+"__eta")->Fill(tj.eta()                         , weight);
    H1("toptag"+std::to_string(i+1)+"__phi")->Fill(tj.phi()                         , weight);
    H1("toptag"+std::to_string(i+1)+"__M")  ->Fill(tj.v4().M()                      , weight);
    H1("toptag"+std::to_string(i+1)+"__CSV")->Fill(tj.btag_combinedSecondaryVertex(), weight);

    // substructure
    if(i > 0) continue;

    H1("toptag"+std::to_string(i+1)+"__Mpru")->Fill(tj.prunedmass()   , weight);
    H1("toptag"+std::to_string(i+1)+"__Msdp")->Fill(tj.softdropmass() , weight);
    H1("toptag"+std::to_string(i+1)+"__mmin")->Fill(m_disubjet_min(tj), weight);
    H1("toptag"+std::to_string(i+1)+"__tau2")->Fill(tj.tau2()         , weight);
    H1("toptag"+std::to_string(i+1)+"__tau3")->Fill(tj.tau3()         , weight);
    if(tj.tau2()) H1("toptag"+std::to_string(i+1)+"__tau32")->Fill(tj.tau3()/tj.tau2(), weight);

    std::vector<Jet> subjets = tj.subjets();

    const int subjN(subjets.size());

    H1("toptag"+std::to_string(i+1)+"__subjN")->Fill(subjN, weight);

    float subj_minDR(-1.);
    LorentzVector sum_subj(0, 0, 0, 0);
    for  (int sj1=0    ; sj1<subjN; ++sj1){
      for(int sj2=sj1+1; sj2<subjN; ++sj2){

        const float dR = uhh2::deltaR(subjets.at(sj1), subjets.at(sj2));
        if(dR < subj_minDR || (sj1+sj2==1)) subj_minDR = dR;
      }

      sum_subj += subjets.at(sj1).v4();
    }
    H1("toptag"+std::to_string(i+1)+"__Mgro")      ->Fill(sum_subj.M(), weight);
    H1("toptag"+std::to_string(i+1)+"__subj_minDR")->Fill(subj_minDR  , weight);

    sort_by_pt<Jet>(subjets);
    for(int sj=0; sj<std::min(3, subjN); ++sj){

      const Jet& sjet = subjets.at(sj);

      H1("toptag"+std::to_string(i+1)+"__subj"+std::to_string(sj+1)+"__pt") ->Fill(sjet.pt() , weight);
      H1("toptag"+std::to_string(i+1)+"__subj"+std::to_string(sj+1)+"__eta")->Fill(sjet.eta(), weight);
    }

    std::sort(subjets.begin(), subjets.end(), [](const Jet& j1, const Jet& j2){return j1.btag_combinedSecondaryVertex() > j2.btag_combinedSecondaryVertex();});
    for(int sj=0; sj<std::min(3, subjN); ++sj){

      const Jet& sjet = subjets.at(sj);

      H1("toptag"+std::to_string(i+1)+"__subj_maxCSV"+std::to_string(sj+1))->Fill(sjet.btag_combinedSecondaryVertex(), weight);
    }
  }

  // MET
  H1("met__pt") ->Fill(event.met->pt() , weight);
  H1("met__phi")->Fill(event.met->phi(), weight);
  logmet__pt->Fill(log(event.met->pt()) , weight);
  const Particle* lep1(0);
  float max_lep_pt(0.);
  for(const auto& l : *event.muons)     if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  for(const auto& l : *event.electrons) if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }

  if(lep1){

    H1("wlep__ht")->Fill( event.met->pt()+lep1->pt()      , weight);
    H1("wlep__pt")->Fill((event.met->v4()+lep1->v4()).Pt(), weight);
    H1("wlep__Mt")->Fill(sqrt(2*event.met->pt()*lep1->pt()*(1.-cos(uhh2::deltaPhi(*event.met, *lep1)))), weight);
  }

  /* triangular cuts vars */
  if(lep1)               H2("met__pt__vs__dphi_met_lep1")->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, *lep1))            , weight);
  if(event.jets->size()) H2("met__pt__vs__dphi_met_jet1")->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, event.jets->at(0))), weight);

  TMVA_response->Fill(event.get(tt_tmva_response), weight);
  return;
}
