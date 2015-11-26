void CalcEff(){
  TString path_before="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/";
  TString path_after="/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/SVM_2_chi2/";

  TString file_Zp01w1000 ="uhh2.AnalysisModuleRunner.MC.Zp01w1000.root";
  TString file_Zp01w2000="uhh2.AnalysisModuleRunner.MC.Zp01w2000.root";
  TString file_Zp01w3000="uhh2.AnalysisModuleRunner.MC.Zp01w3000.root";
  TString file_Zp10w0500="uhh2.AnalysisModuleRunner.MC.Zp10w0500.root";
  TString file_Zp10w2500="uhh2.AnalysisModuleRunner.MC.Zp10w2500.root";
  TString file_Zp30w4000="uhh2.AnalysisModuleRunner.MC.Zp30w4000.root";
  TString file_QCD_Pt0080to0120_EMEnriched="uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0080to0120.root";
  TString file_QCD_Pt0120to0170_EMEnriched="uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0120to0170.root";
  TString file_QCD_Pt0170to0300_EMEnriched="uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0170to0300.root";
  TString file_QCD_Pt0300toINF_EMEnriched="uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0300toINF.root";
  TString file_QCD_Pt0080to0170bcToE="uhh2.AnalysisModuleRunner.MC.QCD_bcToE_Pt0080to0170.root";
  TString file_QCD_Pt0170to0250bcToE="uhh2.AnalysisModuleRunner.MC.QCD_bcToE_Pt0170to0250.root";
  TString file_QCD_Pt0250toINFbcToE="uhh2.AnalysisModuleRunner.MC.QCD_bcToE_Pt0250toINF.root";

  TFile *_file_Zp01w1000_b = new TFile(path_before+file_Zp01w1000,"READ");
  TH1D *hMttbarRec_Zp01w1000_b = (TH1D*)_file_Zp01w1000_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_Zp01w1000_a = new TFile(path_after+file_Zp01w1000,"READ");
  TH1D *hMttbarRec_Zp01w1000_a = (TH1D*)_file_Zp01w1000_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"Zp01w1000: "<<100.*(hMttbarRec_Zp01w1000_a->GetEntries()/hMttbarRec_Zp01w1000_b->GetEntries())<<endl;

  TFile *_file_Zp01w2000_b = new TFile(path_before+file_Zp01w2000,"READ");
  TH1D *hMttbarRec_Zp01w2000_b = (TH1D*)_file_Zp01w2000_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_Zp01w2000_a = new TFile(path_after+file_Zp01w2000,"READ");
  TH1D *hMttbarRec_Zp01w2000_a = (TH1D*)_file_Zp01w2000_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"Zp01w2000: "<<100.*(hMttbarRec_Zp01w2000_a->GetEntries()/hMttbarRec_Zp01w2000_b->GetEntries())<<endl;

  TFile *_file_Zp01w3000_b = new TFile(path_before+file_Zp01w3000,"READ");
  TH1D *hMttbarRec_Zp01w3000_b = (TH1D*)_file_Zp01w3000_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_Zp01w3000_a = new TFile(path_after+file_Zp01w3000,"READ");
  TH1D *hMttbarRec_Zp01w3000_a = (TH1D*)_file_Zp01w3000_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"Zp01w3000: "<<100.*(hMttbarRec_Zp01w3000_a->GetEntries()/hMttbarRec_Zp01w3000_b->GetEntries())<<endl;

  TFile *_file_Zp10w0500_b = new TFile(path_before+file_Zp10w0500,"READ");
  TH1D *hMttbarRec_Zp10w0500_b = (TH1D*)_file_Zp10w0500_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_Zp10w0500_a = new TFile(path_after+file_Zp10w0500,"READ");
  TH1D *hMttbarRec_Zp10w0500_a = (TH1D*)_file_Zp10w0500_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"Zp10w0500: "<<100.*(hMttbarRec_Zp10w0500_a->GetEntries()/hMttbarRec_Zp10w0500_b->GetEntries())<<endl;

  TFile *_file_Zp10w2500_b = new TFile(path_before+file_Zp10w2500,"READ");
  TH1D *hMttbarRec_Zp10w2500_b = (TH1D*)_file_Zp10w2500_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_Zp10w2500_a = new TFile(path_after+file_Zp10w2500,"READ");
  TH1D *hMttbarRec_Zp10w2500_a = (TH1D*)_file_Zp10w2500_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"Zp10w2500: "<<100.*(hMttbarRec_Zp10w2500_a->GetEntries()/hMttbarRec_Zp10w2500_b->GetEntries())<<endl;

  TFile *_file_Zp30w4000_b = new TFile(path_before+file_Zp30w4000,"READ");
  TH1D *hMttbarRec_Zp30w4000_b = (TH1D*)_file_Zp30w4000_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_Zp30w4000_a = new TFile(path_after+file_Zp30w4000,"READ");
  TH1D *hMttbarRec_Zp30w4000_a = (TH1D*)_file_Zp30w4000_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"Zp30w4000: "<<100.*(hMttbarRec_Zp30w4000_a->GetEntries()/hMttbarRec_Zp30w4000_b->GetEntries())<<endl;

  TFile *_file_QCD_Pt0080to0120_EMEnriched_b = new TFile(path_before+file_QCD_Pt0080to0120_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0080to0120_EMEnriched_b = (TH1D*)_file_QCD_Pt0080to0120_EMEnriched_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0080to0120_EMEnriched_a = new TFile(path_after+file_QCD_Pt0080to0120_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0080to0120_EMEnriched_a = (TH1D*)_file_QCD_Pt0080to0120_EMEnriched_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0080to0120_EMEnriched: "<<100.*(hMttbarRec_QCD_Pt0080to0120_EMEnriched_a->GetEntries()/hMttbarRec_QCD_Pt0080to0120_EMEnriched_b->GetEntries())<<endl;

  TFile *_file_QCD_Pt0120to0170_EMEnriched_b = new TFile(path_before+file_QCD_Pt0120to0170_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0120to0170_EMEnriched_b = (TH1D*)_file_QCD_Pt0120to0170_EMEnriched_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0120to0170_EMEnriched_a = new TFile(path_after+file_QCD_Pt0120to0170_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0120to0170_EMEnriched_a = (TH1D*)_file_QCD_Pt0120to0170_EMEnriched_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0120to0170_EMEnriched: "<<100.*(hMttbarRec_QCD_Pt0120to0170_EMEnriched_a->GetEntries()/hMttbarRec_QCD_Pt0120to0170_EMEnriched_b->GetEntries())<<endl;

  TFile *_file_QCD_Pt0170to0300_EMEnriched_b = new TFile(path_before+file_QCD_Pt0170to0300_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0170to0300_EMEnriched_b = (TH1D*)_file_QCD_Pt0170to0300_EMEnriched_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0170to0300_EMEnriched_a = new TFile(path_after+file_QCD_Pt0170to0300_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0170to0300_EMEnriched_a = (TH1D*)_file_QCD_Pt0170to0300_EMEnriched_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0170to0300_EMEnriched: "<<100.*(hMttbarRec_QCD_Pt0170to0300_EMEnriched_a->GetEntries()/hMttbarRec_QCD_Pt0170to0300_EMEnriched_b->GetEntries())<<endl;

  TFile *_file_QCD_Pt0300toINF_EMEnriched_b = new TFile(path_before+file_QCD_Pt0300toINF_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0300toINF_EMEnriched_b = (TH1D*)_file_QCD_Pt0300toINF_EMEnriched_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0300toINF_EMEnriched_a = new TFile(path_after+file_QCD_Pt0300toINF_EMEnriched,"READ");
  TH1D *hMttbarRec_QCD_Pt0300toINF_EMEnriched_a = (TH1D*)_file_QCD_Pt0300toINF_EMEnriched_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0300toINF_EMEnriched: "<<100.*(hMttbarRec_QCD_Pt0300toINF_EMEnriched_a->GetEntries()/hMttbarRec_QCD_Pt0300toINF_EMEnriched_b->GetEntries())<<endl;

  TFile *_file_QCD_Pt0080to0170bcToE_b = new TFile(path_before+file_QCD_Pt0080to0170bcToE,"READ");
  TH1D *hMttbarRec_QCD_Pt0080to0170bcToE_b = (TH1D*)_file_QCD_Pt0080to0170bcToE_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0080to0170bcToE_a = new TFile(path_after+file_QCD_Pt0080to0170bcToE,"READ");
  TH1D *hMttbarRec_QCD_Pt0080to0170bcToE_a = (TH1D*)_file_QCD_Pt0080to0170bcToE_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0080to0170bcToE: "<<100.*(hMttbarRec_QCD_Pt0080to0170bcToE_a->GetEntries()/hMttbarRec_QCD_Pt0080to0170bcToE_b->GetEntries())<<endl;

  TFile *_file_QCD_Pt0170to0250bcToE_b = new TFile(path_before+file_QCD_Pt0170to0250bcToE,"READ");
  TH1D *hMttbarRec_QCD_Pt0170to0250bcToE_b = (TH1D*)_file_QCD_Pt0170to0250bcToE_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0170to0250bcToE_a = new TFile(path_after+file_QCD_Pt0170to0250bcToE,"READ");
  TH1D *hMttbarRec_QCD_Pt0170to0250bcToE_a = (TH1D*)_file_QCD_Pt0170to0250bcToE_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0170to0250bcToE: "<<100.*(hMttbarRec_QCD_Pt0170to0250bcToE_a->GetEntries()/hMttbarRec_QCD_Pt0170to0250bcToE_b->GetEntries())<<endl;

TFile *_file_QCD_Pt0250toINFbcToE_b = new TFile(path_before+file_QCD_Pt0250toINFbcToE,"READ");
  TH1D *hMttbarRec_QCD_Pt0250toINFbcToE_b = (TH1D*)_file_QCD_Pt0250toINFbcToE_b->Get("chi2__hyp_chi2min/M_ttbar_rec");
  TFile *_file_QCD_Pt0250toINFbcToE_a = new TFile(path_after+file_QCD_Pt0250toINFbcToE,"READ");
  TH1D *hMttbarRec_QCD_Pt0250toINFbcToE_a = (TH1D*)_file_QCD_Pt0250toINFbcToE_a->Get("chi2__hyp_chi2min/M_ttbar_rec");
  cout<<"QCD_Pt0250toINFbcToE: "<<100.*(hMttbarRec_QCD_Pt0250toINFbcToE_a->GetEntries()/hMttbarRec_QCD_Pt0250toINFbcToE_b->GetEntries())<<endl;
}
