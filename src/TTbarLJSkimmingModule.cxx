#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

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
#include <UHH2/common/include/Utils.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>

#include <UHH2/common/include/LuminosityHists.h>

class TTbarLJSkimmingModule : public ModuleBASE {

 public:
  explicit TTbarLJSkimmingModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // cleaners
  std::unique_ptr<MuonCleaner>     muoSR_cleaner;
  std::unique_ptr<ElectronCleaner> eleSR_cleaner;
  std::unique_ptr<JetCleaner>           jet_IDcleaner;
  std::unique_ptr<JetCorrector>         jet_corrector;
//!!  std::unique_ptr<JetResolutionSmearer> jetER_smearer;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> jetlepton_cleaner;
  std::unique_ptr<JetCleaner>           jet_cleaner1;
  std::unique_ptr<JetCleaner>           jet_cleaner2;
  std::unique_ptr<JetCleaner>                 topjet_IDcleaner;
  std::unique_ptr<TopJetCorrector>            topjet_corrector;
//!!  std::unique_ptr<TopJetResolutionSmearer>    topjetER_smearer;
  std::unique_ptr<TopJetLeptonDeltaRCleaner>  topjetlepton_cleaner;
  std::unique_ptr<TopJetCleaner>              topjet_cleaner;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::Selection> genflavor_sel;

  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> twodcut_sel;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  Event::Handle<float> tt_TMVA_response;// response of TMVA method, dummy value at this step

};

TTbarLJSkimmingModule::TTbarLJSkimmingModule(uhh2::Context& ctx){

  //// CONFIGURATION

  const bool isMC = (ctx.get("dataset_type") == "MC");

//!!  const std::string& channel = ctx.get("channel", "");
//!!  if     (channel == "muon") channel_ = muon;
//!!  else if(channel == "elec") channel_ = elec;
//!!  else throw std::runtime_error("TTbarLJSkimmingModule::TTbarLJSkimmingModule -- undefined argument for 'channel' key in xml file (must be 'muon' or 'elec'): "+channel);
  //

  const std::string& keyword = ctx.get("keyword");

  ElectronId eleID;
  float ele_pt(-1.), jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool use_miniiso(false);

  if(keyword == "v01"){

    ele_pt = 50.;
    // ele_pt = 40.;
    //    eleID  = ElectronID_Spring15_25ns_tight_noIso;
    //  eleID  = ElectronID_HEEP_RunII_25ns;
    eleID = ElectronID_MVAnotrig_Spring15_25ns_loose;
    use_miniiso = false;

    jet1_pt = 200.;
    jet2_pt =  50.;

    MET     =  0.;
    HT_lep  =   0.;
  }
  else throw std::runtime_error("TTbarLJSkimmingModule::TTbarLJSkimmingModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  //

  ////

  //// COMMON MODULES

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));


  /* MET filters */
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
  metfilters_sel->add<TriggerSelection>("eeBadSc"   , "Flag_eeBadScFilter");
  /***************/



  /* GEN M-ttbar selection [TTbar MC "0.<M^{gen}_{ttbar}(GeV)<700.] */
  const std::string ttbar_gen_label ("ttbargen");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  if(ctx.get("dataset_version") == "TTbar_Mtt0000to0700") genmttbar_sel.reset(new GenMttbarCut(ctx, 0., 700., ttbar_gen_label));
  else                                                    genmttbar_sel.reset(new uhh2::AndSelection(ctx));
  /******************************************************************/

  /* GEN Flavor selection [W+jets flavor-splitting] */
  if(ctx.get("dataset_version").find("WJets") != std::string::npos){

    if     (ctx.get("dataset_version").find("__B") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("b"));
    else if(ctx.get("dataset_version").find("__C") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("c"));
    else if(ctx.get("dataset_version").find("__L") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("l"));

    else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  }
  else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  /**************************************************/

  ////

  //// OBJ CLEANING
  const     MuonId muoSR(AndId<Muon>    (PtEtaCut  (50.   , 2.1), MuonIDMedium()));
  const ElectronId eleSR(AndId<Electron>(PtEtaSCCut(ele_pt, 2.5), eleID));
  //  const ElectronId eleSR(PtEtaSCCut(ele_pt,2.5)); //TEST: ID methods study

  if(use_miniiso){

    const     MuonId muoMINIIso(    Muon_MINIIso(0.05, "delta-beta"));
    const ElectronId eleMINIIso(Electron_MINIIso(0.05, "delta-beta"));

    muoSR_cleaner.reset(new     MuonCleaner(AndId<Muon>    (muoSR, muoMINIIso)));
    eleSR_cleaner.reset(new ElectronCleaner(AndId<Electron>(eleSR, eleMINIIso)));
  }
  else{

    muoSR_cleaner.reset(new     MuonCleaner(muoSR));
    eleSR_cleaner.reset(new ElectronCleaner(eleSR));
  }
  //

  const JetId jetID(JetPFID(JetPFID::WP_LOOSE));

  std::vector<std::string> JEC_AK4, JEC_AK8;
  if(isMC){

    // JEC_AK4 = JERFiles::Summer15_25ns_L123_AK4PFchs_MC;
    // JEC_AK8 = JERFiles::Summer15_25ns_L123_AK8PFchs_MC;
    JEC_AK4 = JERFiles::Fall15_25ns_L123_AK4PFchs_MC;
    JEC_AK8 = JERFiles::Fall15_25ns_L123_AK8PFchs_MC;
  }
  else {

    // JEC_AK4 = JERFiles::Summer15_25ns_L123_AK4PFchs_DATA;
    // JEC_AK8 = JERFiles::Summer15_25ns_L123_AK8PFchs_DATA;
    JEC_AK4 = JERFiles::Fall15_25ns_L123_AK4PFchs_DATA;
    JEC_AK8 = JERFiles::Fall15_25ns_L123_AK8PFchs_DATA;
  }

  jet_IDcleaner.reset(new JetCleaner(ctx,jetID,"jets"));
  jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
//!!  jetER_smearer.reset(new JetResolutionSmearer(ctx));
  jetlepton_cleaner.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4));
  jet_cleaner1.reset(new JetCleaner(ctx,15., 3.0, "jets"));
  jet_cleaner2.reset(new JetCleaner(ctx,30., 2.4, "jets"));

  topjet_IDcleaner.reset(new JetCleaner(ctx,jetID,"jets"));
  topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
//!!  topjetER_smearer.reset(new TopJetResolutionSmearer(ctx));
  topjetlepton_cleaner.reset(new TopJetLeptonDeltaRCleaner(.8));
  topjet_cleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(500., 2.4)),"topjets"));
  ////

  //// EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(use_miniiso) twodcut_sel.reset(new TwoDCut1(-1, 20.));
  else            twodcut_sel.reset(new TwoDCut1(.4, 20.));
  ////

  //// HISTS
  std::vector<std::string> htags_1({

    "lep1",
    "jet2",
    "jet1",
    "met",
    "htlep",
    "twodcut",
  });

  for(const auto& tag : htags_1){

    book_HFolder(tag, new TTbarLJHists(ctx, tag));
  }
  ////

  tt_TMVA_response = ctx.declare_event_output<float>("TMVA_response");

  book_HFolder("LuminosityHists", new LuminosityHists(ctx,"LuminosityHists"));
  book_HFolder("LuminosityHists_metfilter", new LuminosityHists(ctx,"LuminosityHists_metfilter"));
  book_HFolder("LuminosityHists_lepsel", new LuminosityHists(ctx,"LuminosityHists_lepsel"));
}

bool TTbarLJSkimmingModule::process(uhh2::Event& event){
  event.set(tt_TMVA_response,0);//fill with dummy value
  // std::cout<<""<<std::endl;
  // std::cout<<"New event! #"<<event.event<<std::endl;

  //// COMMON MODULES

  if(!event.isRealData){

    /* GEN M-ttbar selection */
    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;

    /* GEN ME quark-flavor selection */
    if(!genflavor_sel->passes(event)) return false;
  }


  /* luminosity sections from CMS JSON file */
  if(event.isRealData && !lumi_sel->passes(event)) return false;
  if(event.isRealData)
    HFolder("LuminosityHists")->fill(event);

  /* MET filters */
  if(!metfilters_sel->passes(event)) return false;

  ////

  HFolder("met")->fill(event);
  if(event.isRealData)
    HFolder("LuminosityHists_metfilter")->fill(event);
  //// LEPTON selection
  
  muoSR_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);
  // std::cout<<"event.muons->size() = "<<event.muons->size()<<std::endl;

  eleSR_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);
  // std::cout<<"event.electrons->size() = "<<event.electrons->size()<<std::endl;
  const bool pass_lep1 = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  if(!pass_lep1) return false;
  //  std::cout<<"Electrons are sorted!"<<std::endl;
  HFolder("lep1")->fill(event);
  if(event.isRealData)
    HFolder("LuminosityHists_lepsel")->fill(event);
  
  ////

  //// JET selection
  //std::cout<<"Jets are going to be cleaned!"<<std::endl;
  jet_IDcleaner->process(event);
  // std::cout<<"Jets are cleaned!"<<std::endl;
  jet_corrector->process(event);
//!!  jetER_smearer->process(event);
  jetlepton_cleaner->process(event);
  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);
  // std::cout<<"Jets are sorted!"<<std::endl;

  topjet_IDcleaner->process(event);
  topjet_corrector->process(event);
//!!  topjetER_smearer->process(event);
  topjetlepton_cleaner->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);
  // std::cout<<"TopJets are sorted!"<<std::endl;

 

  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);
  //  std::cout<<"Jets are sorted again! "<<event.jets->size()<<std::endl;

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  HFolder("jet2")->fill(event);
  //  std::cout<<"pass_jet2!"<<std::endl;

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  HFolder("jet1")->fill(event);
  ////
  //  std::cout<<"pass_jet1!"<<std::endl;

  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  HFolder("met")->fill(event);
  ////
  //  std::cout<<"PASS MET"<<std::endl;


  //// HT_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  HFolder("htlep")->fill(event);
  ////
  //  std::cout<<"PASS HT_lep"<<std::endl;


  /* lepton-2Dcut variables */
  const bool pass_twodcut = twodcut_sel->passes(event); {

    for(auto& muo : *event.muons){

      float    dRmin, pTrel;
      std::tie(dRmin, pTrel) = drmin_pTrel(muo, *event.jets);

      muo.set_tag(Muon::twodcut_dRmin, dRmin);
      muo.set_tag(Muon::twodcut_pTrel, pTrel);
    }

    
    for(auto& ele : *event.electrons){

      float    dRmin, pTrel;
      std::tie(dRmin, pTrel) = drmin_pTrel(ele, *event.jets);

      ele.set_tag(Electron::twodcut_dRmin, dRmin);
      ele.set_tag(Electron::twodcut_pTrel, pTrel);
    }
  }
  if(!pass_twodcut) std::cout<<"event did not pass 2D cut, but we don't care right now "<<std::endl;
  //   TEST: no 2D cut for QCD suppression studies
 //  //// LEPTON-2Dcut selection
 //  // if(!pass_twodcut) std::cout<<"XMMMM Not pass 2D cut"<<std::endl;
 //  if(!pass_twodcut) return false;
 //  // std::cout<<"AGA! pass 2D cut"<<std::endl;
 //  HFolder("twodcut")->fill(event);
 //  ////

  //  std::cout<<"We made it! =)"<<std::endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TTbarLJSkimmingModule)
