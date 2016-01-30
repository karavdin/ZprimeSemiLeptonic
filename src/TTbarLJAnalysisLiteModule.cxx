#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/Utils.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/DileptonHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/SF_pileup.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_btagging.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_ttagging.h>


#include <TMVA/Tools.h>
#include <TMVA/Reader.h>
#include <TMVA/MethodCuts.h>

class TTbarLJAnalysisLiteModule : public ModuleBASE {

 public:
  explicit TTbarLJAnalysisLiteModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // selections
  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  std::unique_ptr<uhh2::Selection> ttagevt_sel;
  std::unique_ptr<uhh2::Selection> topleppt_sel;
  std::unique_ptr<uhh2::Selection> chi2_sel;

  // ttbar reconstruction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::AnalysisModule> reco_primlep;
  std::unique_ptr<uhh2::AnalysisModule> ttbar_reco__ttag0, ttbar_reco__ttag1;
  std::unique_ptr<uhh2::AnalysisModule> ttbar_chi2__ttag0, ttbar_chi2__ttag1;

  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;

  JetId btag_ID_;

  bool use_ttagging_;
  TopJetId ttag_ID_;
  float    ttag_minDR_jet_;

  bool blind_DATA_;

  //// Data/MC scale factors
  std::unique_ptr<weightcalc_pileup> pileupSF_ct;
  std::unique_ptr<weightcalc_pileup> pileupSF_up;
  std::unique_ptr<weightcalc_pileup> pileupSF_dn;

  std::unique_ptr<weightcalc_btagging> btagSF_ct;
  std::unique_ptr<weightcalc_btagging> btagSF_upL;
  std::unique_ptr<weightcalc_btagging> btagSF_dnL;
  std::unique_ptr<weightcalc_btagging> btagSF_upB;
  std::unique_ptr<weightcalc_btagging> btagSF_dnB;

  std::unique_ptr<weightcalc_ttagging> ttagSF_ct;
  std::unique_ptr<weightcalc_ttagging> ttagSF_upL;
  std::unique_ptr<weightcalc_ttagging> ttagSF_dnL;
  std::unique_ptr<weightcalc_ttagging> ttagSF_upT;
  std::unique_ptr<weightcalc_ttagging> ttagSF_dnT;

  std::unique_ptr<MCVarReweight> varvariation;
  ////

  //// VARS

  // event
  Event::Handle<int>   h_run;
  Event::Handle<int>   h_lumi_block;
  Event::Handle<int>   h_event;
  Event::Handle<int>   h_pvN;
  Event::Handle<int>   h_muoN;
  Event::Handle<int>   h_eleN;
  Event::Handle<int>   h_btagN;
  Event::Handle<int>   h_ttagN;
  Event::Handle<bool>  h_ttagevt;
  //

  // lepton
  Event::Handle<TLorentzVector> h_lep1;
  Event::Handle<int>            h_lep1__pdgID;
  Event::Handle<int>            h_lep1__charge;
  Event::Handle<float>          h_lep1__minDR_jet;
  Event::Handle<float>          h_lep1__pTrel_jet;

  Event::Handle<TLorentzVector> h_lep2;
  Event::Handle<int>            h_lep2__pdgID;
  Event::Handle<int>            h_lep2__charge;
  Event::Handle<float>          h_lep2__minDR_jet;
  Event::Handle<float>          h_lep2__pTrel_jet;
  //

  // MET
  Event::Handle<TLorentzVector> h_MET;
  Event::Handle<float>          h_MET__pz;
  //

  // ttbar reco hyp
  Event::Handle<float>          h_rec_chi2;
  Event::Handle<TLorentzVector> h_rec_tlep;
  Event::Handle<TLorentzVector> h_rec_thad;
  //

  // weight
  Event::Handle<float> h_wgtMC__GEN;

  Event::Handle<float> h_wgtMC__pileupSF_ct;
  Event::Handle<float> h_wgtMC__pileupSF_up;
  Event::Handle<float> h_wgtMC__pileupSF_dn;

  Event::Handle<float> h_wgtMC__btagSF_ct;
  Event::Handle<float> h_wgtMC__btagSF_upL;
  Event::Handle<float> h_wgtMC__btagSF_dnL;
  Event::Handle<float> h_wgtMC__btagSF_upB;
  Event::Handle<float> h_wgtMC__btagSF_dnB;

  Event::Handle<float> h_wgtMC__ttagSF_ct;
  Event::Handle<float> h_wgtMC__ttagSF_upL;
  Event::Handle<float> h_wgtMC__ttagSF_dnL;
  Event::Handle<float> h_wgtMC__ttagSF_upT;
  Event::Handle<float> h_wgtMC__ttagSF_dnT;

  Event::Handle<float> h_wgtMC__muR_ct__muF_up;
  Event::Handle<float> h_wgtMC__muR_ct__muF_dn;
  Event::Handle<float> h_wgtMC__muR_up__muF_ct;
  Event::Handle<float> h_wgtMC__muR_up__muF_up;
  Event::Handle<float> h_wgtMC__muR_dn__muF_ct;
  Event::Handle<float> h_wgtMC__muR_dn__muF_dn;
  //

  ////

  // vars in TTree for Homemade ttbar MVA
  //ToDo: add errors of reconstructed vars!
  Event::Handle<float> tt_lep_pt;//lepton pt
  Event::Handle<float> tt_lep_eta;//lepton eta
  Event::Handle<float> tt_lep_xy;// x^2+y^2 vertex of the lepton 
  Event::Handle<float> tt_MwT;// Transversal mass
  Event::Handle<float> tt_lep_fbrem;//fraction of energy loss due to bremsstrahlung. !cation: in 8TeV was well modeled only for |eta|<1.44
  Event::Handle<float> tt_met_pt;//MET pt
  Event::Handle<float> tt_ljet_pt;//jet pt (for the leading jet)
  Event::Handle<float> tt_lep_pt_ljet;// lepton Pt to the leading jet axis
  Event::Handle<float> tt_dR_cljet_ljet;//distance in eta-phi between close jet  and leading jet
  Event::Handle<float> tt_dR_lep_cljet;// distance between lepton and the closest not leading jet in eta-phi
  Event::Handle<int> tt_lep_class;// rec.electron classification
  Event::Handle<float> tt_ljet_CSV;//btagging: CombinedSecondaryVertex
  Event::Handle<float> tt_nJets;//number of jets
  Event::Handle<float> tt_jets_pt;//sum of jets pt

  Event::Handle<float> tt_ev_weight;// event weight
  Event::Handle<float> tt_mttbar;//ttbar inv. mass

  float met_pt;//MET
  float lep_pt, lep_eta, fabs_lep_eta;//lepton
  float ljet_pt;//leading jet 
  float lep_xy; //x^2+y^2 vertex of the lepton
  float lep_fbrem; 
  float MwT;// Transversal mass
  float lep_pt_ljet;// lepton Pt to the leading jet axis
  float dR_cljet_ljet;//distance in eta-phi between the closest jet and the leading jet 
  float dR_lep_cljet;//distance in eta-phi for the closest not leading jet to lepton  
  int lep_class;// rec.electron classification
  float ljet_CSV;//btag: combinedSecondaryVertex
  float nJets;//number of jets
  float jets_pt;//sum of jets pt
  float ev_weight;

  float rec_ttbar_M_;
  float log_ljet_pt, log_dR_cljet_ljet, log_dR_lep_cljet, log_lep_pt, jets_pt_to_lep_pt, lep_pt_ljet_to_lep_pt, log_met_pt_to_ljet_pt;
  float jets_pt_to_ljet_pt,  log_lep_xy_corr, log_ljet_CSV_ljet_pt;
  std::unique_ptr<TMVA::Reader> reader;
  //  TMVA::Reader *reader;
  TString methodName;
  float TMVA_response;
  Event::Handle<float> tt_TMVA_response;// response of TMVA method
};

TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule(uhh2::Context& ctx){

  //// CONFIGURATION

  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);

  use_ttagging_ = true;
  blind_DATA_ = false;
  if     (ctx.get("blind_DATA") == "true")  blind_DATA_ = true && !isMC;
  else if(ctx.get("blind_DATA") == "false") blind_DATA_ = false;
  else throw std::runtime_error("undefined argument for 'blind_DATA' key in xml file (must be 'true' or 'false')");
  //blind_DATA_ = ((ctx.get("dataset_version").find("BLINDED") != std::string::npos) && (ctx.get("dataset_type") == "DATA") && !isMC);
  //
  if(blind_DATA_) std::cout<<"BLIND DATA!"<<std::endl;

  const std::string& keyword = ctx.get("keyword");

  float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool triangul_cut(false);
  bool topleppt_cut(false);

  //  if(keyword == "T0_v01" || keyword == "T1_v01"){
  if(keyword == "T0_v01" || keyword == "T1_v01" || keyword == "v01"){//TEST for QCD studies which does not care about t-tagging

    if     (keyword == "T0_v01") use_ttagging_ = false;
    else if(keyword == "T1_v01") use_ttagging_ = true;
    else if(keyword == "v01") use_ttagging_ = true;//TEST for QCD studies which does not care about t-tagging

    if(channel_ == muon){

      jet1_pt = 150.;
      jet2_pt =  50.;

      MET    =  50.;
      HT_lep = 150.;

      triangul_cut = false;
      topleppt_cut = false;
    }
    else if(channel_ == elec){

      // jet1_pt = 250.;
      // jet2_pt =  70.;
      //   MET    = 120.;      
     
      jet1_pt = 200.; //TEST for QCD supprestion studies
      jet2_pt = 50.; //TEST for QCD supprestion studies
      MET    = 0.; //TEST for QCD supprestion studies
      //      MET    = 30.; //TEST for QCD supprestion studies

      HT_lep =   0.;

      triangul_cut = false;
      topleppt_cut = false;
    }
  }
  else throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  //

  ////

  //// COMMON MODULES
  ////

  //// OBJ CLEANING
  ////

  //// EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

  const std::string& trigger = ctx.get("trigger", "NULL");
  if(trigger != "NULL") trigger_sel.reset(new TriggerSelection(trigger));
  else                  trigger_sel.reset(new uhh2::AndSelection(ctx));

  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  //  met_sel  .reset(new METCut  (0,MET)); //TEST: QCD sideband
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(triangul_cut){

    if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(M_PI/2., (M_PI/2.)/75.));
    else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx));
  }
  else triangc_sel.reset(new uhh2::AndSelection(ctx));
  ////

  /* b-tagging */
  const std::string& btag_wp = ctx.get("btag_wp");

  if     (btag_wp == "CSVL") btag_ID_ = CSVBTag(CSVBTag::WP_LOOSE);
  else if(btag_wp == "CSVM") btag_ID_ = CSVBTag(CSVBTag::WP_MEDIUM);
  else if(btag_wp == "CSVT") btag_ID_ = CSVBTag(CSVBTag::WP_TIGHT);
  else throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- invalid key for b-tagging working point: "+btag_wp);
  /*************/

  /* t-tagging */
  const std::string& ttag_wp = ctx.get("ttag_wp");

  ttag_ID_ = TopTagID_SoftDrop(ttag_wp);
  ttag_minDR_jet_ = 1.2;

  ttagevt_sel.reset(new TopTagEventSelection(ttag_ID_, ttag_minDR_jet_));
  /*************/

  //// TTBAR KINEMATICAL RECO

  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  reco_primlep.reset(new PrimaryLepton(ctx));

  ttbar_reco__ttag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
  ttbar_reco__ttag1.reset(new        TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, ttag_ID_, ttag_minDR_jet_));

  ttbar_chi2__ttag0.reset(new Chi2Discriminator    (ctx, ttbar_hyps_label));
  ttbar_chi2__ttag1.reset(new Chi2DiscriminatorTTAG(ctx, ttbar_hyps_label));

  h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis>>(ttbar_hyps_label);
  ////

  if(topleppt_cut){

    if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
    else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));
  }
  else topleppt_sel.reset(new uhh2::AndSelection(ctx));

  //  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., 30., ttbar_hyps_label, ttbar_chi2_label));
  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., 1e6, ttbar_hyps_label, ttbar_chi2_label)); //No cut for QCD studies

  //// HISTS

  std::vector<std::string> htags_1({

    "jet2",
    "jet1",
    "trigger",
    "met",
    "htlep",
    "triangc",
    "topleppt",
  });

  for(const auto& tag : htags_1){

    book_HFolder(tag, new TTbarLJHists(ctx, tag, ttag_ID_, ttag_minDR_jet_));
  }
  //

  std::vector<std::string> htags_2({

    "kine",
    "kine__t0b0",
    "kine__t0b1",
    "kine__t0b2",
    "kine__t1b0",
    "kine__t1b1",
    "kine__t1b2",

    "antichi2",
    "antichi2__t0b0",
    "antichi2__t0b1",
    "antichi2__t0b2",
    "antichi2__t1b0",
    "antichi2__t1b1",
    "antichi2__t1b2",

    "chi2",
    "chi2__t0b0",
    "chi2__t0b1",
    "chi2__t0b2",
    "chi2__t1b0",
    "chi2__t1b1",
    "chi2__t1b2",
  });

  for(const auto& tag : htags_2){

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }
  //

  std::vector<std::string> htags_3({

    "chi2_L2",
    "chi2_L2__t0b0",
    "chi2_L2__t0b1",
    "chi2_L2__t0b2",
    "chi2_L2__t1b0",
    "chi2_L2__t1b1",
    "chi2_L2__t1b2",
  });

  for(const auto& tag : htags_3){

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(tag+"__dilep", new DileptonHists     (ctx, tag+"__dilep"));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }
  //

 std::vector<std::string> htags_4({

    "REWEIGHTED",
  });

  for(const auto& tag : htags_4){

    // book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    // book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar"));
  }
  //

  ////

  //// Data/MC scale factors

  // pileup
  const std::string& pileup_MC      = ctx.get("pileup_MC");
  const std::string& pileup_DATA_ct = ctx.get("pileup_DATA_ct");
  const std::string& pileup_DATA_up = ctx.get("pileup_DATA_up");
  const std::string& pileup_DATA_dn = ctx.get("pileup_DATA_dn");

  pileupSF_ct.reset(new weightcalc_pileup(pileup_DATA_ct, pileup_MC, "pileup", "pileup"));
  pileupSF_up.reset(new weightcalc_pileup(pileup_DATA_up, pileup_MC, "pileup", "pileup"));
  pileupSF_dn.reset(new weightcalc_pileup(pileup_DATA_dn, pileup_MC, "pileup", "pileup"));
  //

  // b-tagging
  const std::string& btag_SFac_file = ctx.get("btag_SFs");
  const std::string& btag_effy_file = ctx.get("btag_eff");
  const std::string& btag_effyL     = ctx.get("btag_eff__jetL");
  const std::string& btag_effyC     = ctx.get("btag_eff__jetC");
  const std::string& btag_effyB     = ctx.get("btag_eff__jetB");

  btagSF_ct .reset(new weightcalc_btagging(btag_SFac_file, btag_wp, "comb", "mujets", "mujets", "CT", "CT", "CT", btag_effy_file, btag_effyL, btag_effyC, btag_effyB));

  btagSF_upL.reset(new weightcalc_btagging(btag_SFac_file, btag_wp, "comb", "mujets", "mujets", "UP", "CT", "CT", btag_effy_file, btag_effyL, btag_effyC, btag_effyB));
  btagSF_dnL.reset(new weightcalc_btagging(btag_SFac_file, btag_wp, "comb", "mujets", "mujets", "DN", "CT", "CT", btag_effy_file, btag_effyL, btag_effyC, btag_effyB));

  btagSF_upB.reset(new weightcalc_btagging(btag_SFac_file, btag_wp, "comb", "mujets", "mujets", "CT", "UP", "UP", btag_effy_file, btag_effyL, btag_effyC, btag_effyB));
  btagSF_dnB.reset(new weightcalc_btagging(btag_SFac_file, btag_wp, "comb", "mujets", "mujets", "CT", "DN", "DN", btag_effy_file, btag_effyL, btag_effyC, btag_effyB));
  //

  // t-tagging
  const std::string& ttag_SFac_file = ctx.get("ttag_SFs");
  const std::string& ttag_effy_file = ctx.get("ttag_eff");
  const std::string& ttag_effyL     = ctx.get("ttag_eff__jetL");
  const std::string& ttag_effyT     = ctx.get("ttag_eff__jetT");

  ttagSF_ct .reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));

  ttagSF_upL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "UP", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));
  ttagSF_dnL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "DN", "CT", ttag_effy_file, ttag_effyL, ttag_effyT));

  ttagSF_upT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "UP", ttag_effy_file, ttag_effyL, ttag_effyT));
  ttagSF_dnT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "DN", ttag_effy_file, ttag_effyL, ttag_effyT));
  //

  // MVA vars variations
  const std::string& reweight_MC_file = ctx.get("reweight_file");

  varvariation.reset(new MCVarReweight(ctx));
  ////

  //// VARS
  ctx.undeclare_all_event_output();

  // event
  h_run                = ctx.declare_event_output<int>("run");
  h_lumi_block         = ctx.declare_event_output<int>("lumi_block");
  h_event              = ctx.declare_event_output<int>("event");

  h_pvN                = ctx.declare_event_output<int>("pvN");

  h_muoN               = ctx.declare_event_output<int>("muoN");
  h_eleN               = ctx.declare_event_output<int>("eleN");

  h_btagN              = ctx.declare_event_output<int>("btagN");
  h_ttagN              = ctx.declare_event_output<int>("ttagN");

  h_ttagevt            = ctx.declare_event_output<bool>("ttagevt");
  //

  // lepton
  h_lep1               = ctx.declare_event_output<TLorentzVector>("lep1");
  h_lep1__pdgID        = ctx.declare_event_output<int>           ("lep1__pdgID");
  h_lep1__charge       = ctx.declare_event_output<int>           ("lep1__charge");
  h_lep1__minDR_jet    = ctx.declare_event_output<float>         ("lep1__minDR_jet");
  h_lep1__pTrel_jet    = ctx.declare_event_output<float>         ("lep1__pTrel_jet");

  h_lep2               = ctx.declare_event_output<TLorentzVector>("lep2");
  h_lep2__pdgID        = ctx.declare_event_output<int>           ("lep2__pdgID");
  h_lep2__charge       = ctx.declare_event_output<int>           ("lep2__charge");
  h_lep2__minDR_jet    = ctx.declare_event_output<float>         ("lep2__minDR_jet");
  h_lep2__pTrel_jet    = ctx.declare_event_output<float>         ("lep2__pTrel_jet");
  //

  // MET
  h_MET                = ctx.declare_event_output<TLorentzVector>("MET");
  h_MET__pz            = ctx.declare_event_output<float>         ("MET__pz");
  //

  // ttbar reco hyp
  h_rec_chi2           = ctx.declare_event_output<float>         ("rec_chi2");
  h_rec_tlep           = ctx.declare_event_output<TLorentzVector>("rec_tlep");
  h_rec_thad           = ctx.declare_event_output<TLorentzVector>("rec_thad");
  //

  // weight
  h_wgtMC__GEN         = ctx.declare_event_output<float>("wgtMC__GEN");

  h_wgtMC__pileupSF_ct = ctx.declare_event_output<float>("wgtMC__pileupSF_ct");
  h_wgtMC__pileupSF_up = ctx.declare_event_output<float>("wgtMC__pileupSF_up");
  h_wgtMC__pileupSF_dn = ctx.declare_event_output<float>("wgtMC__pileupSF_dn");

  h_wgtMC__btagSF_ct   = ctx.declare_event_output<float>("wgtMC__btagSF_ct");
  h_wgtMC__btagSF_upL  = ctx.declare_event_output<float>("wgtMC__btagSF_upL");
  h_wgtMC__btagSF_dnL  = ctx.declare_event_output<float>("wgtMC__btagSF_dnL");
  h_wgtMC__btagSF_upB  = ctx.declare_event_output<float>("wgtMC__btagSF_upB");
  h_wgtMC__btagSF_dnB  = ctx.declare_event_output<float>("wgtMC__btagSF_dnB");

  h_wgtMC__ttagSF_ct   = ctx.declare_event_output<float>("wgtMC__ttagSF_ct");
  h_wgtMC__ttagSF_upL  = ctx.declare_event_output<float>("wgtMC__ttagSF_upL");
  h_wgtMC__ttagSF_dnL  = ctx.declare_event_output<float>("wgtMC__ttagSF_dnL");
  h_wgtMC__ttagSF_upT  = ctx.declare_event_output<float>("wgtMC__ttagSF_upT");
  h_wgtMC__ttagSF_dnT  = ctx.declare_event_output<float>("wgtMC__ttagSF_dnT");

  h_wgtMC__muR_ct__muF_up = ctx.declare_event_output<float>("wgtMC__muR_ct__muF_up");
  h_wgtMC__muR_ct__muF_dn = ctx.declare_event_output<float>("wgtMC__muR_ct__muF_dn");
  h_wgtMC__muR_up__muF_ct = ctx.declare_event_output<float>("wgtMC__muR_up__muF_ct");
  h_wgtMC__muR_up__muF_up = ctx.declare_event_output<float>("wgtMC__muR_up__muF_up");
  h_wgtMC__muR_dn__muF_ct = ctx.declare_event_output<float>("wgtMC__muR_dn__muF_ct");
  h_wgtMC__muR_dn__muF_dn = ctx.declare_event_output<float>("wgtMC__muR_dn__muF_dn");
  //

  ////

  ///Homemade ttbar MVA input
  met_pt = 0; ljet_pt = 0;
  lep_pt = 0; lep_eta = 0; fabs_lep_eta = 0;
  lep_xy = 0; lep_fbrem = 0;
  MwT = 0; lep_pt_ljet = 0;
  dR_cljet_ljet = 0; dR_lep_cljet = 0;
  lep_class = -10;
  ev_weight = 0;
  //  mttbar = 0;
  log_ljet_pt = 0; log_dR_cljet_ljet = 0; log_dR_lep_cljet = 0; log_lep_pt = 0;
  jets_pt = 0;
  jets_pt_to_lep_pt = 0; lep_pt_ljet_to_lep_pt=0; log_met_pt_to_ljet_pt = 0;
  jets_pt_to_ljet_pt = 0;  log_lep_xy_corr = 0;  log_ljet_CSV_ljet_pt = 0;


  tt_met_pt = ctx.declare_event_output<float>("met_pt");
  tt_lep_pt = ctx.declare_event_output<float>("lep_pt");
  tt_lep_eta = ctx.declare_event_output<float>("lep_eta");
  tt_ljet_pt = ctx.declare_event_output<float>("ljet_pt");
  tt_lep_xy = ctx.declare_event_output<float>("lep_xy");
  tt_lep_fbrem = ctx.declare_event_output<float>("lep_fbrem");
  tt_MwT = ctx.declare_event_output<float>("MwT");
  tt_lep_pt_ljet = ctx.declare_event_output<float>("lep_pt_ljet");
  tt_dR_cljet_ljet = ctx.declare_event_output<float>("dR_cljet_ljet");
  tt_dR_lep_cljet = ctx.declare_event_output<float>("dR_lep_cljet");
  tt_lep_class = ctx.declare_event_output<int>("lep_class");
  tt_ljet_CSV = ctx.declare_event_output<float>("ljet_CSV");
  tt_ev_weight = ctx.declare_event_output<float>("weight");
  tt_mttbar = ctx.declare_event_output<float>("Mttbar");
  tt_nJets= ctx.declare_event_output<float>("nJets");
  tt_jets_pt = ctx.declare_event_output<float>("jets_pt");
  /// Homemade ttbar MVA output
  TMVA_response = 0;
  tt_TMVA_response = ctx.declare_event_output<float>("TMVA_response");
  // --- Create the Reader object
  //reader = new TMVA::Reader( "!Color:!Silent" );  

 

  reader.reset(new TMVA::Reader( "!Color:!Silent" ));
  // //Categories ------------------------------
  // reader->AddVariable("fabs(lep_eta)", &fabs_lep_eta);
  // reader->AddVariable("log(met_pt/ljet_pt)", &log_met_pt_to_ljet_pt);
  // reader->AddVariable("jets_pt/ljet_pt",&jets_pt_to_ljet_pt);
  // reader->AddVariable("log(fabs(lep_xy-0.1216))",&log_lep_xy_corr);
  // reader->AddVariable("log(ljet_CSV/ljet_pt)",&log_ljet_CSV_ljet_pt);
  // reader->AddVariable("MwT", &MwT);
  // reader->AddVariable("nJets", &nJets);
  // reader->AddVariable("lep_pt_ljet/lep_pt",&lep_pt_ljet_to_lep_pt);
  // //[END]Categories -------------------------

  //Golden Set -------------------------------
  reader->AddVariable("fabs(lep_eta)", &fabs_lep_eta);
  reader->AddVariable("MwT", &MwT);
  reader->AddVariable("met_pt", &met_pt);
  reader->AddVariable("ljet_CSV", &ljet_CSV);
  //  reader->AddVariable("log(ljet_pt)", &log_ljet_pt); 
  reader->AddVariable("log(lep_pt)",&log_lep_pt);
  reader->AddVariable("log(dR_lep_cljet)", &log_dR_lep_cljet);
  reader->AddVariable("log(fabs((dR_cljet_ljet-3.14)/3.14))", &log_dR_cljet_ljet);
  //[END] Golden Set -------------------------
  reader->AddVariable("jets_pt",&jets_pt);

  reader->AddSpectator("Mttbar",&rec_ttbar_M_);

  //  reader->AddVariable("log(lep_pt)",&log_lep_pt);
  // 
  //  reader->AddVariable("ljet_CSV", &ljet_CSV);
  //  reader->AddVariable("log(ljet_pt)", &log_ljet_pt); //TEST
  //  reader->AddVariable("log(fabs((dR_cljet_ljet-3.14)/3.14))", &log_dR_cljet_ljet);

  // --- book the MVA methods
  //  TString dir    = "../TMVA_weights/";
  TString dir    = "/afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_7_4_15_patch1/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/"; //ToDo: make it param in xml
  // //  TString dir    = "ZprimeSemiLeptonic/TMVA_weights/"; 
  //  methodName = "BDT::BDT method";
  //TString weightfile = dir + "Homemade_TTbarMVAClassification_BDT.weights.xml";
  //  TString weightfile = dir + "Homemade_TTbarMVAClassification_BDT_MET40.weights.xml";
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_BDT_2.weights.xml"; //w/t ljet_pt and Log($\Delta$R(lep, jet0))
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_BDT_6.weights.xml";
  //  TString weightfile = dir + "Homemade_TTbarMVAClassification_BDT_20160115.xml";

   methodName = "MLP::MLPBNN";
   //   TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_8vars.weights.xml";
  //  TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPCat.weights.xml";
   //   TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_Zp1to4TeV.weights.xml";
  //  TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_Zp2to4TeV.weights.xml";//TRY ME!
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_TTbarZp2to4TeV.weights.xml";

   //   TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_TTbar_X3_Zp2to4_X1_5_N-2N+0_newVars.weights.xml";
   //   TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_TTbar_X15_Zp2to4_X1_5_N-2N+4_newVars.weights.xml";
   TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_TTbar_X6_Zp2to4_X1_5_N-2N+4_newVars.weights.xml";

  // methodName = "Category::BDTCat";
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_BDTCat20160117.weights.xml";

  // methodName = "Category::MLPCat";
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPCat20160117.weights.xml";

  // methodName = "BDT::BDT";
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_BDT_20160117.xml";

  //methodName = "Category::MLPCat";
  // TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPCat20160121.weights.xml";
  //TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPCat_TTbarZp2to4.weights.xml";

  reader->BookMVA(methodName, weightfile);
  ////

}

bool TTbarLJAnalysisLiteModule::process(uhh2::Event& event){
  // std::cout<<" "<<std::endl;
  // std::cout<<"New Event! "<<std::endl;
  event.set(tt_TMVA_response, TMVA_response);//fill 1st hists with default value
  if(!event.isRealData){

    ttgenprod->process(event);
  }

  //// Data/MC scale factors

  float w_GEN(1.);
  float w_pileupSF_ct(1.), w_pileupSF_up(1.), w_pileupSF_dn(1.);
  float w_btagSF_ct(1.), w_btagSF_upL(1.), w_btagSF_dnL(1.), w_btagSF_upB(1.), w_btagSF_dnB(1.);
  float w_ttagSF_ct(1.), w_ttagSF_upL(1.), w_ttagSF_dnL(1.), w_ttagSF_upT(1.), w_ttagSF_dnT(1.);
  float w_muR_ct__muF_up(1.), w_muR_ct__muF_dn(1.), w_muR_up__muF_ct(1.), w_muR_up__muF_up(1.), w_muR_dn__muF_ct(1.), w_muR_dn__muF_dn(1.);

  if(!event.isRealData){

    w_GEN = event.weight;
    //    std::cout<<"event.weight = "<<event.weight<<std::endl;
    // pileup
    w_pileupSF_ct = pileupSF_ct->weight(event);
    w_pileupSF_up = pileupSF_up->weight(event);
    w_pileupSF_dn = pileupSF_dn->weight(event);
    //

    // b-tagging
    w_btagSF_ct  = btagSF_ct ->weight(event);

    w_btagSF_upL = btagSF_upL->weight(event);
    w_btagSF_dnL = btagSF_dnL->weight(event);

    w_btagSF_upB = btagSF_upB->weight(event);
    w_btagSF_dnB = btagSF_dnB->weight(event);
    //

    // t-tagging
    w_ttagSF_ct  = ttagSF_ct ->weight(event);

    w_ttagSF_upL = ttagSF_upL->weight(event);
    w_ttagSF_dnL = ttagSF_dnL->weight(event);

    w_ttagSF_upT = ttagSF_upT->weight(event);
    w_ttagSF_dnT = ttagSF_dnT->weight(event);
    //

    // Renormalization/Factorization scales
    if(event.genInfo){

      if(event.genInfo->systweights().size() >= 9){

        if(event.genInfo->originalXWGTUP()){

          w_muR_ct__muF_up = (event.genInfo->systweights().at(1) / event.genInfo->originalXWGTUP());
          w_muR_ct__muF_dn = (event.genInfo->systweights().at(2) / event.genInfo->originalXWGTUP());
          w_muR_up__muF_ct = (event.genInfo->systweights().at(3) / event.genInfo->originalXWGTUP());
          w_muR_up__muF_up = (event.genInfo->systweights().at(4) / event.genInfo->originalXWGTUP());
          w_muR_dn__muF_ct = (event.genInfo->systweights().at(6) / event.genInfo->originalXWGTUP());
          w_muR_dn__muF_dn = (event.genInfo->systweights().at(8) / event.genInfo->originalXWGTUP());
        }
      }
    }

    // central weight (histograms)
    event.weight  = w_GEN;
    event.weight *= w_pileupSF_ct;
    event.weight *= w_btagSF_ct;
    event.weight *= w_ttagSF_ct;
    //
  }
  //
  //  std::cout<<"Now let's go to lepton selection "<<std::endl;
  ////

  //// LEPTON SELECTION

  // OF lepton veto
  bool pass_lepV(0);
  if     (channel_ == muon) pass_lepV = ((event.electrons->size() == 0));
  else if(channel_ == elec) pass_lepV = ((event.muons    ->size() == 0));
  if(!pass_lepV) return false;
  //

  int lepN(-1);
  if     (channel_ == muon) lepN = int(event.muons    ->size());
  else if(channel_ == elec) lepN = int(event.electrons->size());
  if(!(lepN >= 1)) return false;

  ////


  //TEST: Check classification vs chi2 for QCD studies
  //if((event.electrons->at(0)).Class()!=2) return false;//2 = BadTrk
  // if((event.electrons->at(0)).Class()!=3) return false;//3 = Shower

  //  std::cout<<"Now let's go to jet selection "<<std::endl;
  //// JET selection

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  if(lepN == 1) HFolder("jet2")->fill(event);

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  if(lepN == 1) HFolder("jet1")->fill(event);

  ////

  //// HLT selection
  const bool pass_trigger = trigger_sel->passes(event);
  if(!pass_trigger) return false;
  if(lepN == 1) HFolder("trigger")->fill(event);
  ////

  //  std::cout<<"Now let's go to MET selection "<<std::endl;
  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  if(lepN == 1) HFolder("met")->fill(event);
  ////

  //  std::cout<<"Now let's go to HT_lep selection "<<std::endl;
  //// HT_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  if(lepN == 1) HFolder("htlep")->fill(event);
  ////



  //TEST: no TRIANGULAR-CUTS for QCD suppression studies!
  // //// TRIANGULAR-CUTS selection
  // const bool pass_triangc = triangc_sel->passes(event);
  // if(!pass_triangc) return false;
  // if(lepN == 1) HFolder("triangc")->fill(event);
  // ////

  //// TTBAR KIN RECO

  /* TOPTAG-EVENT boolean */
  const bool pass_ttagevt = ttagevt_sel->passes(event) && use_ttagging_;

  const std::string ttag_posx = (pass_ttagevt ? "t1" : "t0");

  //  std::cout<<"Now let's go to reco_primlep "<<std::endl;
  /************************/

  reco_primlep->process(event);

  if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
  else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }

  std::vector<ReconstructionHypothesis>& ttbar_hyps = event.get(h_ttbar_hyps);

  /* DATA blinding */
  if(blind_DATA_){

    if(lepN == 1){

      const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");

      const float rec_ttbar_M((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());

      if(!( rec_ttbar_M < 2000. )) return false;
    }
  }
  /*****************/

  ////

  //  std::cout<<"Now let's go to LEPTONIC-TOP pt selection "<<std::endl;
  //// LEPTONIC-TOP pt selection
  const bool pass_topleppt = topleppt_sel->passes(event);
  if(!pass_topleppt) return false;
  if(lepN == 1) HFolder("topleppt")->fill(event);
  ////

  /* btagN counters */
  int jetbtagN(0), subjbtagN(0);

  if(!pass_ttagevt){

    for(const auto& j : *event.jets) if(btag_ID_(j, event)) ++jetbtagN;
  }
  else {

    const ReconstructionHypothesis* ttbar_hyp = get_best_hypothesis(ttbar_hyps, "Chi2");

    const TopJet* thad = ttbar_hyp->tophad_topjet_ptr();

    for(const auto& j : thad->subjets()) if(btag_ID_(j, event)) ++subjbtagN;

    for(const auto& j : *event.jets){

      if(!(uhh2::deltaR(*thad, j) > ttag_minDR_jet_)) continue;
      if(btag_ID_(j, event)) ++jetbtagN;
    }
  }

  const int btagN = jetbtagN + subjbtagN;

  const std::string btag_posx = (btagN >= 2 ? "b2" : (btagN >= 1 ? "b1" : "b0"));
  /******************/

  //  std::cout<<"Now let's go to FINAL KINEMATIC selection "<<std::endl;
  //// FINAL KINEMATIC selection
  if(lepN == 1){

    HFolder("kine")       ->fill(event);
    HFolder("kine__ttbar")->fill(event);

    HFolder("kine__"+ttag_posx+btag_posx)          ->fill(event);
    HFolder("kine__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
  }
  ////

//!!  //// inverted CHI2(top-lep) selection
//!!  const bool pass_antichi2tlep = antichi2tlep_sel->passes(event);
//!!  if(pass_antichi2tlep){
//!!
//!!    if(lepN == 1){
//!!
//!!      HFolder("antichi2tlep")       ->fill(event);
//!!      HFolder("antichi2tlep__BTAG") ->fill(event);
//!!      HFolder("antichi2tlep__TTAG") ->fill(event);
//!!      HFolder("antichi2tlep__ttbar")->fill(event);
//!!
//!!      HFolder("antichi2tlep__"+ttag_posx+btag_posx)          ->fill(event);
//!!      HFolder("antichi2tlep__"+ttag_posx+btag_posx+"__BTAG") ->fill(event);
//!!      HFolder("antichi2tlep__"+ttag_posx+btag_posx+"__TTAG") ->fill(event);
//!!      HFolder("antichi2tlep__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
//!!    }
//!!  }
//!!  ////

//  std::cout<<"Now let's go to CHI2 selection "<<std::endl;
  //// CHI2 selection
   const bool pass_chi2 = chi2_sel->passes(event);
  // const bool pass_chi2 = true; //TEST for QCD studies

  const std::string chi2_posx = pass_chi2 ? "chi2" : "antichi2";

  if(lepN == 1){

    HFolder(chi2_posx)          ->fill(event);
    HFolder(chi2_posx+"__ttbar")->fill(event);

    HFolder(chi2_posx+"__"+ttag_posx+btag_posx)          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
  }
  else if(lepN == 2){

    bool l2_ossf(false);
    if     (channel_ == muon) l2_ossf = ((event.muons    ->at(0).charge() * event.muons    ->at(1).charge()) == -1);
    else if(channel_ == elec) l2_ossf = ((event.electrons->at(0).charge() * event.electrons->at(1).charge()) == -1);

    if(l2_ossf && chi2_posx == "chi2"){

      HFolder(chi2_posx+"_L2")          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__ttbar")->fill(event);

      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx)          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
    }
  }
  ////

  //  std::cout<<"Now let's set VARS "<<std::endl;

  //// VARS

  // event
  event.set(h_run       , event.run);
  event.set(h_lumi_block, event.luminosityBlock);
  event.set(h_event     , event.event);

  event.set(h_pvN  , event.pvs->size());

  event.set(h_muoN , event.muons    ->size());
  event.set(h_eleN , event.electrons->size());

  // std::cout<<"Now let's set tags! "<<std::endl;

  int ttagN(0);
  for(const auto& tj : *event.topjets) if(ttag_ID_(tj, event)) ++ttagN;

  event.set(h_btagN, btagN);
  event.set(h_ttagN, ttagN);

  event.set(h_ttagevt, pass_ttagevt);
  //

  // std::cout<<"Now let's set leptons! "<<std::endl;

  // lepton
  const Particle* lep1 = leading_lepton(event);
  const Particle* lep2(0);
  if(lepN == 2){

    if     (channel_ == muon) lep2 = &((lep1 == &event.muons    ->at(0)) ? event.muons    ->at(1) : event.muons    ->at(0));
    else if(channel_ == elec) lep2 = &((lep1 == &event.electrons->at(0)) ? event.electrons->at(1) : event.electrons->at(0));
  }

  TLorentzVector lep1__p4(0.,0.,0.,0.), lep2__p4(0.,0.,0.,0.);
  int   lep1__pdgID(0), lep1__charge(0), lep2__pdgID(0), lep2__charge(0);
  float lep1__minDR_jet(-1.), lep1__pTrel_jet(-1.), lep2__minDR_jet(-1.), lep2__pTrel_jet(-1.);
  if(channel_ == muon){

    lep1__pdgID     = lep1->charge() * -13;
    lep1__charge    = lep1->charge();
    lep1__minDR_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_dRmin);
    lep1__pTrel_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_pTrel);
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    if(lep2){

      lep2__pdgID     = lep2->charge() * -13;
      lep2__charge    = lep2->charge();
      lep2__minDR_jet = ((Muon*) lep2)->get_tag(Muon::twodcut_dRmin);
      lep2__pTrel_jet = ((Muon*) lep2)->get_tag(Muon::twodcut_pTrel);
      lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
    }
  }
  else if(channel_ == elec){
    //    std::cout<<"... I mean electrons ;)"<<std::endl;
    lep1__pdgID     = lep1->charge() * -11;
    lep1__charge    = lep1->charge();
    //     std::cout<<"... I mean all tags and stuff... "<<Electron::twodcut_dRmin<<" "<<Electron::twodcut_pTrel<<std::endl;
    lep1__minDR_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_dRmin);
    lep1__pTrel_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_pTrel);

    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    if(lep2){
      lep2__pdgID     = lep2->charge() * -11;
      lep2__charge    = lep2->charge();
      lep2__minDR_jet = ((Electron*) lep2)->get_tag(Electron::twodcut_dRmin);
      lep2__pTrel_jet = ((Electron*) lep2)->get_tag(Electron::twodcut_pTrel);
      lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
    }
  }

  event.set(h_lep1           , lep1__p4);
  event.set(h_lep1__pdgID    , lep1__pdgID);
  event.set(h_lep1__charge   , lep1__charge);
  event.set(h_lep1__minDR_jet, lep1__minDR_jet);
  event.set(h_lep1__pTrel_jet, lep1__pTrel_jet);

  event.set(h_lep2           , lep2__p4);
  event.set(h_lep2__pdgID    , lep2__pdgID);
  event.set(h_lep2__charge   , lep2__charge);
  event.set(h_lep2__minDR_jet, lep2__minDR_jet);
  event.set(h_lep2__pTrel_jet, lep2__pTrel_jet);
  //

  //  std::cout<<"Now let's set MET "<<std::endl;
  // MET
  event.set(h_MET, TLorentzVector(event.met->v4().Px(), event.met->v4().Py(), event.met->v4().Pz(), event.met->v4().P()));
  //

  //  std::cout<<"Now let's set ttbar "<<std::endl;
  // ttbar reco hyp
  const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");
  if(!rec_ttbar) throw std::runtime_error("TTbarLJAnalysisLiteModule::process -- logic error: ttbar reconstruction hypothesis (\"get_best_hypothesis\", discr=Chi2) not found");

  const float MET__pz = rec_ttbar->neutrino_v4().Pz();
  event.set(h_MET__pz, MET__pz);

  const float rec_chi2 = rec_ttbar->discriminator("Chi2");
  event.set(h_rec_chi2, rec_chi2);

  const LorentzVector tlep(rec_ttbar->toplep_v4());
  const LorentzVector thad(rec_ttbar->tophad_v4());

  event.set(h_rec_tlep, TLorentzVector(tlep.Px(), tlep.Py(), tlep.Pz(), tlep.E()));
  event.set(h_rec_thad, TLorentzVector(thad.Px(), thad.Py(), thad.Pz(), thad.E()));
  //

  // weight
  event.set(h_wgtMC__GEN        , w_GEN);

  event.set(h_wgtMC__pileupSF_ct, w_pileupSF_ct);
  event.set(h_wgtMC__pileupSF_up, w_pileupSF_up);
  event.set(h_wgtMC__pileupSF_dn, w_pileupSF_dn);

  event.set(h_wgtMC__btagSF_ct  , w_btagSF_ct );
  event.set(h_wgtMC__btagSF_upL , w_btagSF_upL);
  event.set(h_wgtMC__btagSF_dnL , w_btagSF_dnL);
  event.set(h_wgtMC__btagSF_upB , w_btagSF_upB);
  event.set(h_wgtMC__btagSF_dnB , w_btagSF_dnB);

  event.set(h_wgtMC__ttagSF_ct  , w_ttagSF_ct );
  event.set(h_wgtMC__ttagSF_upL , w_ttagSF_upL);
  event.set(h_wgtMC__ttagSF_dnL , w_ttagSF_dnL);
  event.set(h_wgtMC__ttagSF_upT , w_ttagSF_upT);
  event.set(h_wgtMC__ttagSF_dnT , w_ttagSF_dnT);

  event.set(h_wgtMC__muR_ct__muF_up, w_muR_ct__muF_up);
  event.set(h_wgtMC__muR_ct__muF_dn, w_muR_ct__muF_dn);
  event.set(h_wgtMC__muR_up__muF_ct, w_muR_up__muF_ct);
  event.set(h_wgtMC__muR_up__muF_up, w_muR_up__muF_up);
  event.set(h_wgtMC__muR_dn__muF_ct, w_muR_dn__muF_ct);
  event.set(h_wgtMC__muR_dn__muF_dn, w_muR_dn__muF_dn);
  //

  ////


  //Fill vars for Homemade ttbar MVA
 const int jet_n = event.jets->size();
 nJets = jet_n;
 event.set(tt_nJets,nJets);
  if(channel_ == elec){ //ToDo: extend for case with muon(s)
    const Electron *lep = &event.electrons->at(0);
    lep_class = lep->Class();
    event.set(tt_lep_class, lep_class);

    met_pt = event.met->pt();
    event.set(tt_met_pt, met_pt); 
    lep_pt = lep->pt(); lep_eta = lep->eta(); fabs_lep_eta = fabs(lep_eta);
    event.set(tt_lep_pt, lep_pt);   event.set(tt_lep_eta, lep_eta);
    if(!event.isRealData) 
      //    lep_xy = hypot(lep->gsfTrack_vx()+0.045,lep->gsfTrack_vy()+0.095); //TEST: shift for agreement with DATA (RunII, 0.6 pb^-1)
    lep_xy = hypot(lep->gsfTrack_vx(),lep->gsfTrack_vy())+0.121540; //TEST: shift for agreement with DATA (RunII, 2.5 pb^-1)
    else
      lep_xy = hypot(lep->gsfTrack_vx(),lep->gsfTrack_vy());
    event.set(tt_lep_xy,lep_xy);
    log_lep_xy_corr = log(lep_xy-0.121540);
    lep_fbrem = lep->fbrem();
    event.set(tt_lep_fbrem,lep_fbrem);
   

    //the closest to lepton jet
    // find jet with smallest angle to lepton (the closest jet to lepton)
    int jet_pos = 0;
    dR_lep_cljet = 1e7;
    jets_pt = (&event.jets->at(0))->pt();
    //for(int i=0; i<jet_n; i++){
    for(int i=1; i<jet_n; i++){//skip leading jet
      const Particle* jeti =  &event.jets->at(i);
      jets_pt += jeti->pt();
      float dR_current = uhh2::deltaR(*lep, *jeti);
      if(dR_lep_cljet>dR_current){// min distance in eta-phi
	dR_lep_cljet = dR_current;      
	jet_pos = i;
      }
    }
    event.set(tt_dR_lep_cljet, dR_lep_cljet); 
    event.set(tt_jets_pt,jets_pt);
    jets_pt_to_lep_pt = log(jets_pt/lep_pt);
    const Particle*  jet0 =  &event.jets->at(jet_pos); 
    //leading jet
    const Jet* jet1 = &event.jets->at(0);
    ljet_pt = jet1->pt();
    jets_pt_to_ljet_pt = jets_pt/ljet_pt;
    log_met_pt_to_ljet_pt = log(met_pt/ljet_pt);
    event.set(tt_ljet_pt, ljet_pt);
    ljet_CSV = jet1->btag_combinedSecondaryVertex();
    if(fabs(ljet_CSV)>1.5) return false;
    event.set(tt_ljet_CSV,ljet_CSV);
    log_ljet_CSV_ljet_pt = log(ljet_CSV/ljet_pt);
    lep_pt_ljet = pTrel(*lep, jet1);
    event.set(tt_lep_pt_ljet, lep_pt_ljet);
    dR_cljet_ljet = uhh2::deltaR(*jet0, *jet1);
    lep_pt_ljet_to_lep_pt = lep_pt_ljet/lep_pt;
    event.set(tt_dR_cljet_ljet, dR_cljet_ljet);
    float dPhi_met_lep = fabs(uhh2::deltaPhi(*event.met, *lep));
    MwT = sqrt(2*fabs(lep_pt*met_pt*(1-cos(dPhi_met_lep))));
    event.set(tt_MwT,MwT);
  }


 
  const ReconstructionHypothesis* rec_ttbar_ = get_best_hypothesis(ttbar_hyps, "Chi2");
  rec_ttbar_M_ = ((rec_ttbar_->top_v4()+rec_ttbar_->antitop_v4()).M());
  event.set(tt_mttbar,rec_ttbar_M_);


  log_ljet_pt = log(ljet_pt);
  log_dR_cljet_ljet = log(fabs((dR_cljet_ljet-3.14)/3.14));
  log_dR_lep_cljet = log(dR_lep_cljet);
  log_lep_pt = log(lep_pt);

  TMVA_response = reader->EvaluateMVA(methodName);
  event.set(tt_TMVA_response, TMVA_response);

  //Study TMVA response: reweight variables according to DATA/MC descripency
  // if(!event.isRealData){
//  //  // //1) |lep eta|
// // //   // //|lep $\eta$|$\le$1.55 : y =  0.714706 + 1.56221$\cdot$x -4.63865$\cdot$x$^2$ + 4.88718$\cdot$x$^3$ -1.66262$\cdot$x$^4$
// // //   // //|lep $\eta$|>1.55: y = 189.101  -399.761$\cdot$x +317.191$\cdot$x$^2$ -111.334$\cdot$x$^3$ +14.5676$\cdot$x$^4$
// // //   // TF1 *fpol5_1 = new TF1("fpol5_1","pol4",0,1.55);
// // //   // fpol5_1->SetParameter(0,0.714706);fpol5_1->SetParameter(1,1.56221);fpol5_1->SetParameter(2,-4.63865);fpol5_1->SetParameter(3,4.88718);fpol5_1->SetParameter(4,-1.66262);
// // //   // TF1 *fpol5_2 = new TF1("fpol5_2","pol4",1.55,2.5);
// // //   // fpol5_2->SetParameter(0,189.101);fpol5_2->SetParameter(1,-399.761);fpol5_2->SetParameter(2,317.191);fpol5_2->SetParameter(3,-111.334);fpol5_2->SetParameter(4,14.5676);
// // //   // if(fabs_lep_eta<=1.55) event.weight*=fpol5_1->Eval(fabs_lep_eta);
// // //   // else event.weight*=fpol5_2->Eval(fabs_lep_eta);
// // // // |lep $\eta$|<0.8 : y = 0.750898   +  1.07869$\cdot$x  -3.07643$\cdot$x$^2$ +2.53171$\cdot$x$^3$  
// // // // 0.8<|lep $\eta$|<1.55: y = 4.21908 -11.6711$\cdot$x +12.3603$\cdot$x$^2$ -4.10007$\cdot$x$^3$ 
// // // // |lep $\eta$|>1.55: y = 189.101 -399.761$\cdot$x +317.191$\cdot$x$^2$ -111.334$\cdot$x$^3$ +14.5676$\cdot$x$^4$
// //     TF1 *fpol3_1 = new TF1("fpol3_1","pol3",0,0.8);
// //     fpol3_1->SetParameter(0,0.750898); fpol3_1->SetParameter(1,1.07869); fpol3_1->SetParameter(2,-3.07643); fpol3_1->SetParameter(3,2.53171);
// //     TF1 *fpol3_2 = new TF1("fpol3_2","pol3",0.8,1.55);
// //     fpol3_2->SetParameter(0,4.21908); fpol3_2->SetParameter(1,-11.6711); fpol3_2->SetParameter(2,+12.3603); fpol3_2->SetParameter(3,-4.10007);
// //     TF1 *fpol4 = new TF1("fpol4","pol4",1.55,3.);
// //     fpol4->SetParameter(0,189.101);  fpol4->SetParameter(1,-399.761);  fpol4->SetParameter(2,317.191);  fpol4->SetParameter(3,-111.334);  fpol4->SetParameter(4,+14.5676); 
// //     if(fabs_lep_eta<0.8) event.weight*=fpol3_1->Eval(fabs_lep_eta);
// //     else{ 
// //       if (fabs_lep_eta<1.55) event.weight*=fpol3_2->Eval(fabs_lep_eta);
// //       else event.weight*=fpol4->Eval(fabs_lep_eta);
// //     }

//   // //2)MwT
//   // //y = 0.686115 + 0.00098501$\cdot$x + 4.44785e-06$\cdot$x$^2$
//   // TF1 *fpol2 = new TF1("fpol2","pol2",0,1000);
//   // fpol2->SetParameter(0,0.686115);fpol2->SetParameter(1,0.00098501);fpol2->SetParameter(2,4.44785e-06);
//   // //  std::cout<<"fpol2->Eval("<<MwT<<") = "<<fpol2->Eval(MwT)<<" "<<event.weight<<std::endl;
//   // event.weight *=fpol2->Eval(MwT);
//   // //  std::cout<<"new weight "<<event.weight<<std::endl;

//   // //3)$\not E_{T}$
//   //   //MET$\le$400: y =     0.80563  + 0.0010969$\cdot$x -3.03445e-05$\cdot$x$^2$ + 2.38617e-07$\cdot$x$^3$ -6.37889e-10$\cdot$x$^4$ +4.72175e-13$\cdot$x$^5$
//   //   //MET>400:  y =    7268.53   -74.0394$\cdot$x +  0.300133$\cdot$x$^2$ -0.000605032$\cdot$x$^3$ + 6.06439e-07$\cdot$x$^4$ -2.4177e-10$\cdot$x$^5$
//   //   TF1 *fpol5_1 = new TF1("fpol5_1","pol5",0,400.);
//   //   fpol5_1->SetParameter(0,0.80563); fpol5_1->SetParameter(1,0.0010969); fpol5_1->SetParameter(2,-3.03445e-05); fpol5_1->SetParameter(3,2.38617e-07);
//   //   fpol5_1->SetParameter(4,-6.37889e-10); fpol5_1->SetParameter(5,4.72175e-13); 
//   //   TF1 *fpol5_2 = new TF1("fpol5_2","pol5",400.,4000.);
//   //   fpol5_2->SetParameter(0,7268.53);      fpol5_2->SetParameter(1,-74.0394);      fpol5_2->SetParameter(2,0.300133); 
//   //   fpol5_2->SetParameter(3,-0.000605032);      fpol5_2->SetParameter(4,6.06439e-07);      fpol5_2->SetParameter(5,-2.4177e-10); 
//   //   if(met_pt<400)
//   //     event.weight *=fpol5_1->Eval(met_pt);
//   //   else
//   //     event.weight *=fpol5_2->Eval(met_pt);

//     //4)jet1 CSV
//     //y = 0.866675 -1.16956$\cdot$x +17.9903$\cdot$x$^2$ -83.4937$\cdot$x$^3$ + 158.49$\cdot$x$^4$ -133.086$\cdot$x$^5$ +41.0062$\cdot$x$^6$
//     TF1 *fpol6 = new TF1("fpol6","pol6",0.,1.1);
//     fpol6->SetParameter(0,0.866675);  fpol6->SetParameter(1,-1.16956);  fpol6->SetParameter(2,17.9903);  
//     fpol6->SetParameter(3,-83.4937);   
//     fpol6->SetParameter(4,158.49);  fpol6->SetParameter(5,-133.086);  fpol6->SetParameter(6,41.0062); 
//     event.weight *=fpol6->Eval(ljet_CSV);

//     // //5)$\sum$ jet$_{i}$ p$_{T}$
//     // //y =   1.485  -0.00378757$\cdot$x + 1.06641e-05$\cdot$x$^2$ -2.00092e-08$\cdot$x$^3$ +2.15771e-11$\cdot$x$^4$ -1.15388e-14$\cdot$x$^5$ +2.34261e-18$\cdot$x$^6$
//     // TF1 *fpol6 = new TF1("fpol6","pol6",0.,2000.);
//     // fpol6->SetParameter(0,1.485); fpol6->SetParameter(1,-0.00378757); fpol6->SetParameter(2,1.06641e-05);
//     // fpol6->SetParameter(3,-2.00092e-08); fpol6->SetParameter(4,+2.15771e-11); fpol6->SetParameter(5,-1.15388e-14); fpol6->SetParameter(6,+2.34261e-18); 
//     // event.weight *=fpol6->Eval(jets_pt);

//     // //6)Log(lep p$_{T}$)
//     // //y =    -387.37   + 405.032$\cdot$x -167.445$\cdot$x$^2$ +34.225$\cdot$x$^3$ -3.45604$\cdot$x$^4$ +0.137984$\cdot$x$^5$
//     // TF1 *fpol5 = new TF1("fpol5","pol5",0.,10.);
//     // fpol5->SetParameter(0,-387.37); fpol5->SetParameter(1,405.032); fpol5->SetParameter(2,-167.445);
//     // fpol5->SetParameter(3,34.225); fpol5->SetParameter(4,-3.45604); fpol5->SetParameter(5,0.137984);
//     // event.weight *=fpol5->Eval(log_lep_pt);

//     //7)
//   }
//   //------------------------------------------------------------------------


  // if(TMVA_response<0.9) return false;
  // if(!event.isRealData)
  //   if(log_dR_lep_cljet<=-1.8) event.weight*=1.5; //TEST for disagrement between data and QCD MC

  varvariation->process(event);
  event.set(tt_ev_weight,event.weight);

  //  HFolder("REWEIGHTED")->fill(event);
  HFolder("REWEIGHTED")->fill(event);
  HFolder("REWEIGHTED__ttbar")->fill(event);
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TTbarLJAnalysisLiteModule)
