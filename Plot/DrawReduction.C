//This macro plots 2D plots to illustrate reduction after different ID methods/cuts

void DrawReduction(){


  TString pathRef("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/NoElecID/");
  //  TString pathHEEP("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/HEEP/");
  //  TString pathHEEP("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/CutID_tight/");
  TString pathHEEP("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/MVAnotrig_loose/");


  TString fileName_QCD = "uhh2.AnalysisModuleRunner.MC.QCD.root";
  TFile *_fileRef_QCD = new TFile(pathRef+fileName_QCD,"READ");
  TFile *_fileHEEP_QCD = new TFile(pathHEEP+fileName_QCD,"READ");

  TH2F *h_ele1__pt_eta_Ref_QCD = (TH2F*)_fileRef_QCD->Get("chi2/ele1__pt_eta");
  TH2F *h_ele1__pt_eta_HEEP_QCD = (TH2F*)_fileHEEP_QCD->Get("chi2/ele1__pt_eta");

 TString fileName_TTbar = "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt1000toINFT.root";
  TFile *_fileRef_TTbar = new TFile(pathRef+fileName_TTbar,"READ");
  TFile *_fileHEEP_TTbar = new TFile(pathHEEP+fileName_TTbar,"READ");

  TH2F *h_ele1__pt_eta_Ref_TTbar = (TH2F*)_fileRef_TTbar->Get("chi2/ele1__pt_eta");
  TH2F *h_ele1__pt_eta_HEEP_TTbar = (TH2F*)_fileHEEP_TTbar->Get("chi2/ele1__pt_eta");


  TString fileName_Zp = "uhh2.AnalysisModuleRunner.MC.ZpM3000W01.root";
  TFile *_fileRef_Zp = new TFile(pathRef+fileName_Zp,"READ");
  TFile *_fileHEEP_Zp = new TFile(pathHEEP+fileName_Zp,"READ");

  TH2F *h_ele1__pt_eta_Ref_Zp = (TH2F*)_fileRef_Zp->Get("chi2/ele1__pt_eta");
  TH2F *h_ele1__pt_eta_HEEP_Zp = (TH2F*)_fileHEEP_Zp->Get("chi2/ele1__pt_eta");

  //Draw
  TCanvas * c1 = new TCanvas("ele1__pt_eta", "ele1__pt_eta", 1600, 1200);
  c1->Divide(3,2);
  c1->cd(1);
  h_ele1__pt_eta_Ref_QCD->SetTitle("QCD");
  h_ele1__pt_eta_Ref_QCD->GetYaxis()->SetTitle("#eta");
  h_ele1__pt_eta_Ref_QCD->GetXaxis()->SetTitle("p_{T}, GeV");
  h_ele1__pt_eta_Ref_QCD->Draw("colz");
  c1->cd(2);
  h_ele1__pt_eta_Ref_TTbar->SetTitle("TTbar, Mtt>1TeV");
  h_ele1__pt_eta_Ref_TTbar->GetYaxis()->SetTitle("#eta");
  h_ele1__pt_eta_Ref_TTbar->GetXaxis()->SetTitle("p_{T}, GeV");
  h_ele1__pt_eta_Ref_TTbar->Draw("colz");
  c1->cd(3);
  h_ele1__pt_eta_Ref_Zp->SetTitle("Zp (3TeV,1%)");
  h_ele1__pt_eta_Ref_Zp->GetYaxis()->SetTitle("#eta");
  h_ele1__pt_eta_Ref_Zp->GetXaxis()->SetTitle("p_{T}, GeV");
  h_ele1__pt_eta_Ref_Zp->Draw("colz");
  c1->cd(4);
  h_ele1__pt_eta_HEEP_QCD->SetTitle("QCD");
  h_ele1__pt_eta_HEEP_QCD->Divide(h_ele1__pt_eta_Ref_QCD);
  h_ele1__pt_eta_HEEP_QCD->GetYaxis()->SetTitle("#eta");
  h_ele1__pt_eta_HEEP_QCD->GetXaxis()->SetTitle("p_{T}, GeV");
  h_ele1__pt_eta_HEEP_QCD->GetZaxis()->SetRangeUser(0,1);
  h_ele1__pt_eta_HEEP_QCD->Draw("colz");
  c1->cd(5);
  h_ele1__pt_eta_HEEP_TTbar->SetTitle("TTbar, Mtt>1TeV");
  h_ele1__pt_eta_HEEP_TTbar->Divide(h_ele1__pt_eta_Ref_TTbar);
  h_ele1__pt_eta_HEEP_TTbar->GetYaxis()->SetTitle("#eta");
  h_ele1__pt_eta_HEEP_TTbar->GetXaxis()->SetTitle("p_{T}, GeV");
  h_ele1__pt_eta_HEEP_TTbar->GetZaxis()->SetRangeUser(0,1);
  h_ele1__pt_eta_HEEP_TTbar->Draw("colz");

  c1->cd(6);
  h_ele1__pt_eta_HEEP_Zp->SetTitle("Zp (3TeV,1%)");
  h_ele1__pt_eta_HEEP_Zp->Divide(h_ele1__pt_eta_Ref_Zp);
  h_ele1__pt_eta_HEEP_Zp->GetYaxis()->SetTitle("#eta");
  h_ele1__pt_eta_HEEP_Zp->GetXaxis()->SetTitle("p_{T}, GeV");
  h_ele1__pt_eta_HEEP_Zp->GetZaxis()->SetRangeUser(0,1);
  h_ele1__pt_eta_HEEP_Zp->Draw("colz");

  // c1->Divide(2,1);
  // c1->cd(1);
  // h_ele1__pt_eta_Ref->Draw("colz");
  // c1->cd(2);
  // h_ele1__pt_eta_HEEP->Draw("colz");
}
