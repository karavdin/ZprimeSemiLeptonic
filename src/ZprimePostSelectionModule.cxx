#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/MCWeight.h>

#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/HypothesisHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimePostSelectionHists.h>


#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

//using namespace TMVA;
/** \brief module to produce "PostSelection" output for the Z'->ttbar semileptonic analysis
 *
 * -- ITEMS TO BE IMPLEMENTED:
 *   * systematic uncertainties
 *
 */
class ZprimePostSelectionModule : public uhh2::AnalysisModule {

 public:
  explicit ZprimePostSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  bool FillMistagTop(uhh2::Event&);
 private:
  enum lepton { muon, elec };
  lepton channel_;
  // enum source {DATA, MC};
  // source Type_;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;

  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;

  uhh2::Event::Handle<int> h_flag_toptagevent;

  // selections
  std::unique_ptr<uhh2::Selection> btagAK4_sel;
  std::unique_ptr<uhh2::Selection> topleppt_sel;
  std::unique_ptr<uhh2::Selection> chi2_sel;
  std::unique_ptr<uhh2::Selection> chi2_lep_sel;

  std::unique_ptr<uhh2::Selection> CutA_sel;
  std::unique_ptr<uhh2::Selection> CutB_sel;
  std::unique_ptr<uhh2::Selection> CutC_sel;
  std::unique_ptr<uhh2::Selection> CutD_sel;

  // hists
  std::unique_ptr<uhh2::Hists> hi_input;
  std::unique_ptr<uhh2::Hists> hi_input__hyp;
  std::unique_ptr<uhh2::Hists> hi_topleppt;
  std::unique_ptr<uhh2::Hists> hi_topleppt__hyp;
  std::unique_ptr<uhh2::Hists> hi_chi2;
  std::unique_ptr<uhh2::Hists> hi_chi2__hyp;
  std::unique_ptr<uhh2::Hists> hi_t0b0;
  std::unique_ptr<uhh2::Hists> hi_t0b0__hyp;
  std::unique_ptr<uhh2::Hists> hi_t0b1;
  std::unique_ptr<uhh2::Hists> hi_t0b1__hyp;
  std::unique_ptr<uhh2::Hists> hi_t1;
  std::unique_ptr<uhh2::Hists> hi_t1__hyp;
  std::unique_ptr<uhh2::Hists> hi_mist;

  // vars in TTree for MVA, fill in each event
  //ToDo: add errors of reconstructed vars!
  Event::Handle<float> tt_met_pt;//MET pt
  Event::Handle<float> tt_lep_pt;//lepton pt
  Event::Handle<float> tt_met_phi;//MET phi
  Event::Handle<float> tt_lep_eta;//lepton eta
  Event::Handle<float> tt_lep_phi;//lepton phi
  Event::Handle<float> tt_dPhi_met_lep;//angle between MET and lepton
  Event::Handle<float> tt_cljet_pt;//jet pt (for the closest jet to lepton!)
  Event::Handle<float> tt_cljet_eta;//jet eta (for the closest jet to lepton!)
  Event::Handle<float> tt_dPhi_met_cljet;//angle between MET and jet (for the closest jet to lepton!)
  Event::Handle<float> tt_dPhi_lep_cljet;//angle between lepton and jet (for the closest jet to lepton!)

  Event::Handle<float> tt_ljet_pt;//jet pt (for the leading jet)
  Event::Handle<float> tt_ljet_eta;//jet eta (for the leading jet)
  Event::Handle<float> tt_ljet_phi;//jet phi (for the leading jet)
  Event::Handle<float> tt_dPhi_met_ljet;//angle between MET and jet (for the leading jet)
  Event::Handle<float> tt_dPhi_lep_ljet;//angle between lepton and jet (for the leading jet)
  Event::Handle<float> tt_dR_lep_cljet_2D;// distance between lepton and the closest jet in eta-phi
  Event::Handle<float> tt_dR_lep_cljet;// distance between lepton and the closest not leading jet in eta-phi
  Event::Handle<float> tt_lep_pt_cljet_2D;// lepton Pt to the closest jet axis as in 2D cut

  Event::Handle<float> tt_dR_lep_ljet;//distance in eta-phi between lepton and jet (for the leading jet)    

  Event::Handle<float> tt_dR_cljet_ljet;//distance in eta-phi between close jet  and leading jet
  Event::Handle<float> tt_dPhi_cljet_ljet;//angle between close jet  and leading jet

  Event::Handle<float> tt_lep_pt_cljet;// lepton Pt to the closest jet axis
  Event::Handle<float> tt_lep_pt_ljet;// lepton Pt to the leading jet axis
  Event::Handle<float> tt_ljet_pt_cljet;// leading jet Pt to the closest jet axis
  Event::Handle<float> tt_cljet_pt_ljet;// closet jet Pt to the leading jet axis
  Event::Handle<int> tt_jet_n;//number of jets in event
  Event::Handle<float> tt_lep_xy;// x^2+y^2 vertex of the lepton 
  Event::Handle<float> tt_lep_fbrem;//fraction of energy loss due to bremsstrahlung. !cation: in 8TeV was well modeled only for |eta|<1.44
  Event::Handle<float> tt_MwT;// Transversal mass
  Event::Handle<float> tt_TMVA_response;// TMVA response for cross check
  Event::Handle<float> tt_ev_weight;// event weight
  // int nParticles;
  float met_pt, met_phi;//MET
  float lep_pt, lep_eta, lep_phi;//lepton
  float dPhi_met_lep;//angle between MET and lepton
  float cljet_pt, cljet_eta;//jet (the closest jet to lepton)
  float dPhi_lep_cljet;//angle between lepton and jet (for the closest jet to lepton!)
  float dPhi_met_cljet;//angle between MET and jet (for the closest jet to lepton!)
  float ljet_pt, ljet_eta, ljet_phi;//leading jet 
  float dPhi_lep_ljet;//angle between lepton and jet (for the leading jet)
  float dPhi_met_ljet;//angle between MET and jet (for the leading jet)
  float dR_lep_cljet;//distance in eta-phi for the closest not leading jet to lepton  
  float dR_lep_cljet_2D;//distance in eta-phi as in 2D cut
  float lep_pt_cljet_2D;// lepton Pt to the closest jet axis as in 2D cut
  float dR_lep_ljet;//distance in eta-phi between the leading jet and lepton  
  float dR_cljet_ljet;//distance in eta-phi between the closest jet and the leading jet 
  float dPhi_cljet_ljet;//angle between the closest jet and the leading jet

  float lep_pt_cljet;// lepton Pt to the closest jet axis 
  float lep_pt_ljet;// lepton Pt to the leading jet axis
  float ljet_pt_cljet;// lepton Pt to the closest jet axis 
  float cljet_pt_ljet;// lepton Pt to the leading jet axis 

  float lep_xy; //x^2+y^2 vertex of the lepton
  float lep_fbrem;
  float ev_weight;
  Float_t log_ljet_pt, log_met_pt, log_lep_pt_ljet;
  Float_t log_dR_lep_cljet, log_dR_cljet_ljet;

  int jet_n;//number of jets
  TMVA::Reader *reader;
  //TMVA::Reader *reader_lep;   TMVA::Reader *reader_had;
  TString methodName;
  float TMVA_response;
  float MwT;
  //  float dis_pt;

  // Data/MC scale factors
  std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
};

ZprimePostSelectionModule::ZprimePostSelectionModule(uhh2::Context& ctx){
 const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else throw std::runtime_error("ZprimePostSelectionModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);
// const std::string& Type = ctx.get("Type", "");
//  if(Type == "DATA") Type_ = DATA;
// else
//  if(Type == "MC") Type_ = MC;
//  else throw std::runtime_error("ZprimePostSelectionModule -- undefined argument for 'Type' key in xml file (must be 'MC' or 'DATA'): "+Type);


  // TTBAR RECO
  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");
  const std::string ttbar_chi2_lep_label("Chi2_lep");

  /* GEN */
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  h_ttbargen = ctx.get_handle<TTbarGen>(ttbar_gen_label);

  /* RECO */
  h_ttbar_hyps = ctx.declare_event_input<std::vector<ReconstructionHypothesis>>(ttbar_hyps_label);
  //

  // b-tagging
  btagAK4_sel.reset(new NJetSelection(1, -1, JetId(CSVBTag(CSVBTag::WP_MEDIUM))));

  // top-tagging flag (from ZprimeSelection ntuple)
  h_flag_toptagevent = ctx.declare_event_input<int>("flag_toptagevent");

  // SELECTION
  // if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
  if     (channel_ == elec) topleppt_sel.reset(new uhh2::AndSelection(ctx)); //TEST FOR QCD suppression do NOT use this cut
  else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));


  if(channel_ == elec) CutA_sel.reset(new CutA(0.03,1.,2.5));
  if(channel_ == elec) CutB_sel.reset(new CutB(100.,200.));
  if(channel_ == elec) CutC_sel.reset(new CutC(0.03,250.,1000.));
  if(channel_ == elec) CutD_sel.reset(new CutD(0.03,0.03));

  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx, 0., 30., ttbar_hyps_label, ttbar_chi2_label));
  chi2_lep_sel.reset(new HypothesisDiscriminatorCut(ctx, 0., 30., ttbar_hyps_label, ttbar_chi2_lep_label));


  // HISTS
  hi_input.reset(new ZprimePostSelectionHists(ctx, "input"));
  hi_input__hyp.reset(new HypothesisHists    (ctx, "input__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_topleppt.reset(new ZprimePostSelectionHists(ctx, "topleppt"));
  hi_topleppt__hyp.reset(new HypothesisHists    (ctx, "topleppt__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_chi2.reset(new ZprimePostSelectionHists(ctx, "chi2"));
  hi_chi2__hyp.reset(new HypothesisHists    (ctx, "chi2__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_t0b0.reset(new ZprimePostSelectionHists(ctx, "t0b0"));
  hi_t0b0__hyp.reset(new HypothesisHists    (ctx, "t0b0__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_t0b1.reset(new ZprimePostSelectionHists(ctx, "t0b1"));
  hi_t0b1__hyp.reset(new HypothesisHists    (ctx, "t0b1__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_t1.reset(new ZprimePostSelectionHists(ctx, "t1"));
  hi_t1__hyp.reset(new HypothesisHists    (ctx, "t1__hyp_chi2min", ttbar_hyps_label, ttbar_chi2_label));

  hi_mist.reset(new ZprimePostSelectionHists(ctx, "mist")); /// hists for mis-tag top-tagging rate

  //Declarate vars in TTree for MVA
  // nParticles = 0;
  met_pt = 0;  met_phi = 0;
  lep_pt = 0;  lep_eta = 0; lep_phi = 0;
  dPhi_met_lep = 0;
  cljet_pt = 0; cljet_eta = 0;
  ljet_pt = 0; ljet_eta = 0;   ljet_phi = 0;  
  dPhi_met_cljet = 0; dPhi_lep_cljet = 0;
  dPhi_met_ljet = 0; dPhi_lep_ljet = 0;
  dR_lep_cljet = 0;   dR_lep_cljet_2D = 0;
  dR_lep_ljet = 0;
  dPhi_cljet_ljet = 0;   dR_cljet_ljet = 0;
  lep_pt_cljet_2D = 0;
  lep_pt_cljet = 0;   lep_pt_ljet = 0;
  ljet_pt_cljet = 0;   cljet_pt_ljet = 0;
  jet_n = 0;
  lep_xy = 0;
  lep_fbrem = 0;
  TMVA_response = 0;
  MwT=0;
  //  dis_pt=0;
  // declare the output
  tt_met_pt = ctx.declare_event_output<float>("met_pt");
  tt_met_phi = ctx.declare_event_output<float>("met_phi");
  tt_dPhi_met_lep = ctx.declare_event_output<float>("dPhi_met_lep");
  tt_lep_pt = ctx.declare_event_output<float>("lep_pt");
  tt_lep_eta = ctx.declare_event_output<float>("lep_eta");
  tt_lep_phi = ctx.declare_event_output<float>("lep_phi");

  tt_cljet_pt = ctx.declare_event_output<float>("cljet_pt");
  tt_cljet_eta = ctx.declare_event_output<float>("cljet_eta");
  tt_dPhi_met_cljet = ctx.declare_event_output<float>("dPhi_met_cljet");
  tt_dPhi_lep_cljet = ctx.declare_event_output<float>("dPhi_lep_cljet");

  tt_ljet_pt = ctx.declare_event_output<float>("ljet_pt");
  tt_ljet_eta = ctx.declare_event_output<float>("ljet_eta");
  tt_ljet_phi = ctx.declare_event_output<float>("ljet_phi");
  tt_dPhi_met_ljet = ctx.declare_event_output<float>("dPhi_met_ljet");
  tt_dPhi_lep_ljet = ctx.declare_event_output<float>("dPhi_lep_ljet");
  tt_dR_lep_cljet_2D = ctx.declare_event_output<float>("dR_lep_cljet_2D");
  tt_dR_lep_cljet = ctx.declare_event_output<float>("dR_lep_cljet");
  tt_lep_pt_cljet_2D = ctx.declare_event_output<float>("lep_pt_cljet_2D");
  tt_jet_n = ctx.declare_event_output<int>("jet_n");
  tt_dR_lep_ljet = ctx.declare_event_output<float>("dR_lep_ljet");
  tt_dR_cljet_ljet = ctx.declare_event_output<float>("dR_cljet_ljet");
  tt_dPhi_cljet_ljet = ctx.declare_event_output<float>("dPhi_cljet_ljet");
  tt_lep_pt_cljet = ctx.declare_event_output<float>("lep_pt_cljet");
  tt_lep_pt_ljet = ctx.declare_event_output<float>("lep_pt_ljet");
  tt_ljet_pt_cljet = ctx.declare_event_output<float>("ljet_pt_cljet");
  tt_cljet_pt_ljet = ctx.declare_event_output<float>("cljet_pt_ljet");
  tt_cljet_pt_ljet = ctx.declare_event_output<float>("cljet_pt_ljet");
  tt_TMVA_response = ctx.declare_event_output<float>("TMVA_response");
  tt_lep_xy = ctx.declare_event_output<float>("lep_xy");
  tt_lep_fbrem = ctx.declare_event_output<float>("lep_fbrem");
  tt_MwT = ctx.declare_event_output<float>("MwT");
  tt_ev_weight = ctx.declare_event_output<float>("weight");

  // --- Create the Reader object
  //  TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );  
  reader = new TMVA::Reader( "!Color:!Silent" );  
  reader->AddVariable("lep_pt", &lep_pt);
  reader->AddVariable("lep_fbrem", & lep_fbrem);
  reader->AddVariable("MwT", &MwT);
  reader->AddVariable("log(ljet_pt)", &log_ljet_pt);
  reader->AddVariable("log(met_pt)",&log_met_pt);
  reader->AddVariable("log(lep_pt_ljet)",&log_lep_pt_ljet);
  reader->AddVariable("log(fabs((dR_cljet_ljet-3.14)/3.14))", &log_dR_cljet_ljet);
  reader->AddVariable("log(dR_lep_cljet)",&log_dR_lep_cljet);
  reader->AddSpectator("dPhi_lep_cljet", &dPhi_lep_cljet);
  //
  // book the MVA methods
  //
  TString dir    = "../qcd_rejection/tmva/test/weights_ref/";
  // methodName = "SVM::SVM method";
  // TString weightfile = dir + "Zprime_vs_QCD_TMVAClassification_SVMopt2.weights.xml";
  methodName = "BDT::BDT method";
  TString weightfile = dir + "Zprime_vs_QCD_TMVAClassification_BDT_transvars2.weights.xml";
  reader->BookMVA(methodName, weightfile);

 //  //  TString weightfile = dir + "Zprime_vs_QCD_TMVAClassification_BDT_oneShot.weights.xml";
 //  // TString weightfile = dir + "Zprime_vs_QCD_TMVAClassification_BDT_2TeV_oneShot.weights.xml";
 //  //  reader->BookMVA(methodName, weightfile);

 //  TString weightfile_lep = dir + "Zprime_vs_QCD_TMVAClassification_BDT_Lep.weights.xml";
 //  TString weightfile_had = dir + "Zprime_vs_QCD_TMVAClassification_BDT_Had.weights.xml";

 


 //// COMMON MODULES
 if(isMC) pileup_SF.reset(new MCPileupReweight(ctx));
 // else     lumi_sel.reset(new LumiSelection(ctx));
 
}

// bool ZprimePostSelectionModule::FillMistagTop(uhh2::Event& event){

//   return true;
// }

bool ZprimePostSelectionModule::process(uhh2::Event& event){
  //std::cout<<"ZprimePostSelectionModule::process "<<std::endl;
  //  if(Type_ == MC) ttgenprod->process(event);
  if(!event.isRealData) ttgenprod->process(event);
  /* pileup SF */
  if(!event.isRealData) pileup_SF->process(event);

  hi_input->fill(event);
  hi_input__hyp->fill(event);


  //// LEPTONIC-TOP pt selection //FOR QCD switch it OFF!!!
  bool pass_topleppt = topleppt_sel->passes(event);
  if(!pass_topleppt) return false;
  hi_topleppt->fill(event);
  hi_topleppt__hyp->fill(event);
  ////

  // bool pass_CutA = CutA_sel->passes(event);
  // if(!pass_CutA) return false;
 
  // bool pass_CutB = CutB_sel->passes(event);
  // if(!pass_CutB) return false;


  // bool pass_CutC = CutC_sel->passes(event);
  // if(!pass_CutC) return false;
 
  // bool pass_CutD = CutD_sel->passes(event);   
  // if(!pass_CutD) return false; 

  const bool btag(btagAK4_sel->passes(event));
  const bool toptag(event.get(h_flag_toptagevent));

  // /// selection for mis-tage top-tagging rate (on W+jets)
  // bool pass_chi2_lep = chi2_lep_sel->passes(event);
  // if(!pass_chi2_lep && !btag)
  //   hi_mist->fill(event);
  // //    FillMistagTop(event);

  if(!toptag){

    if(!btag){

      hi_t0b0->fill(event);
      hi_t0b0__hyp->fill(event);
    }
    else {

      hi_t0b1->fill(event);
      hi_t0b1__hyp->fill(event);
    }
  }
  else {

    hi_t1->fill(event);
    hi_t1__hyp->fill(event);
  }


  

  /// Fill tree for MVA ToDo: add weight
  const Particle *lep = &event.electrons->at(0);//ToDo: extend for case with muon(s)  in final state;
  lep_pt = lep->pt(); lep_eta = lep->eta(); lep_phi = lep->phi();
  // //TEST: work in certain electron eta region
  // if(fabs(lep_eta)>0.8) return false;//TEST

  event.set(tt_lep_pt, lep_pt);   event.set(tt_lep_eta, lep_eta); event.set(tt_lep_phi, lep_phi);
  dPhi_met_lep = fabs(uhh2::deltaPhi(*event.met, *lep));
  event.set(tt_dPhi_met_lep, dPhi_met_lep);

  //toDo: extend to muon case!
  met_pt = event.met->pt(); met_phi = event.met->phi();
  event.set(tt_met_pt, met_pt);  event.set(tt_met_phi, met_phi);
  

  if(channel_ == elec){
    //lep_xy = hypot((event.electrons->at(0)).gsfTrack_vx(),(event.electrons->at(0)).gsfTrack_vy());
    if(!event.isRealData) 
      lep_xy = hypot((event.electrons->at(0)).gsfTrack_vx()+0.045,(event.electrons->at(0)).gsfTrack_vy()+0.095); //TEST: shift for agreement with DATA (RunII, 0.6 pb^-1)
    else
      lep_xy = hypot((event.electrons->at(0)).gsfTrack_vx(),(event.electrons->at(0)).gsfTrack_vy());
  }
  event.set(tt_lep_xy,lep_xy);
  if(channel_ == elec) 
    lep_fbrem = (event.electrons->at(0)).fbrem();
  event.set(tt_lep_fbrem,lep_fbrem);

  jet_n = event.jets->size();
  event.set(tt_jet_n,jet_n);
  //the closest to lepton jet
  // find jet with smallest angle to lepton (the closest jet to lepton)
  double ang_min = 1e7;
  int jet_pos = 0;
  dR_lep_cljet = 1e7;
  //for(int i=0; i<jet_n; i++){
    for(int i=1; i<jet_n; i++){//skip leading jet
    const Particle* jeti =  &event.jets->at(i);
    float ang_current = fabs(uhh2::deltaPhi(*lep, *jeti));
    float dR_current = uhh2::deltaR(*lep, *jeti);
    //    if(ang_min>ang_current){
    if(dR_lep_cljet>dR_current){// min distance in eta-phi
      ang_min = ang_current;
      dPhi_lep_cljet = ang_min;
      dR_lep_cljet = dR_current;      
      jet_pos = i;
    }
  }
  
  event.set(tt_dPhi_lep_cljet, dPhi_lep_cljet);  
  const Particle*  jet =  &event.jets->at(jet_pos); 
  cljet_pt = jet->pt(); cljet_eta = jet->eta();
  event.set(tt_cljet_pt, cljet_pt);   event.set(tt_cljet_eta, cljet_eta);
  dPhi_met_cljet = fabs(uhh2::deltaPhi(*event.met, *jet));
  event.set(tt_dPhi_met_cljet, dPhi_met_cljet);
  event.set(tt_dR_lep_cljet, dR_lep_cljet); 

  //leading jet
  const Particle* jet1 = &event.jets->at(0);
  ljet_pt = jet1->pt(); ljet_eta = jet1->eta(); ljet_phi = jet1->phi();
  event.set(tt_ljet_pt, ljet_pt);   event.set(tt_ljet_eta, ljet_eta);  event.set(tt_ljet_phi, ljet_phi);
  dPhi_met_ljet = fabs(uhh2::deltaPhi(*event.met, *jet1));
  event.set(tt_dPhi_met_ljet, dPhi_met_ljet);
  dPhi_lep_ljet = fabs(uhh2::deltaPhi(*lep, *jet1));
  event.set(tt_dPhi_lep_ljet, dPhi_lep_ljet);
  dR_lep_ljet = uhh2::deltaR(*lep, *jet1);
  event.set(tt_dR_lep_ljet, dR_lep_ljet);


  std::tie(dR_lep_cljet_2D,lep_pt_cljet_2D) = drmin_pTrel(*lep, *event.jets);
  event.set(tt_dR_lep_cljet_2D, dR_lep_cljet_2D); 
  event.set(tt_lep_pt_cljet_2D, lep_pt_cljet_2D);

  dPhi_cljet_ljet = fabs(uhh2::deltaPhi(*jet, *jet1));
  dR_cljet_ljet = uhh2::deltaR(*jet, *jet1);
  event.set(tt_dR_cljet_ljet, dR_cljet_ljet);
  event.set(tt_dPhi_cljet_ljet, dPhi_cljet_ljet);

  //pTrel(p, nj) relative momentum of p on nj
  lep_pt_cljet = pTrel(*lep, jet);
  lep_pt_ljet = pTrel(*lep, jet1);
  ljet_pt_cljet = pTrel(*jet1, jet);
  cljet_pt_ljet = pTrel(*jet, jet1);
  event.set(tt_lep_pt_cljet, lep_pt_cljet);
  event.set(tt_lep_pt_ljet, lep_pt_ljet);
  event.set(tt_ljet_pt_cljet, ljet_pt_cljet);
  event.set(tt_cljet_pt_ljet, cljet_pt_ljet);
  MwT = sqrt(2*fabs(lep_pt)*fabs(met_pt)*(1-cos(dPhi_met_lep)));
  event.set(tt_MwT, MwT);

  //set event weight
  event.set(tt_ev_weight,event.weight);

  //Apply TMVA method ----------------------------
  // TMVA_response = 0.6*reader_lep->EvaluateMVA(methodName)+0.4*reader_had->EvaluateMVA(methodName); 
  
  log_ljet_pt = log(ljet_pt);
  log_met_pt = log(met_pt);
  log_lep_pt_ljet = log(lep_pt_ljet);
  log_dR_lep_cljet = log(dR_lep_cljet);
  log_dR_cljet_ljet = log(fabs((dR_cljet_ljet-3.14)/3.14));
  TMVA_response = reader->EvaluateMVA(methodName);
  //  dis_pt = fabs(ljet_pt-lep_pt-met_pt-cljet_pt)/ljet_pt;

  //TMVA_response = 0.0*reader_lep->EvaluateMVA(methodName)+1.0*reader_had->EvaluateMVA(methodName);
  // std::cout<<"TMVA_response = "<<TMVA_response<<" geo="<<reader_lep->EvaluateMVA(methodName)<<" kin="<<reader_had->EvaluateMVA(methodName)<<std::endl;
  //  TMVA_response = 0;//TEST place holder
  event.set(tt_TMVA_response, TMVA_response);
  //----------------------------------------------   
  //if(TMVA_response<0.6) return false;//TEST TMVA SVM cut
  // if(TMVA_response<0.2) return false;//TEST TMVA BDT cut

  // if(TMVA_response<-0.4) return false;//TEST TMVA cut
  if(TMVA_response<0.0) return false;//TEST TMVA cut

 //// CHI2 selection
  bool pass_chi2 = chi2_sel->passes(event); //TEST: FOR QCD switch it OFF!!!
  // /// signal selection
  if(!pass_chi2) return false; //TEST: FOR QCD switch it OFF!!!
  
 //  ////
  hi_chi2->fill(event);
  hi_chi2__hyp->fill(event);

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePostSelectionModule)
