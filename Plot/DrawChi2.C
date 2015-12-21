//This macro plots contribution of electrons with different reconstructed types vs eta

void DrawChi2(){
  //Input file
  TFile *_fileIN_QCD = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/NoElecID_BadTrk/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  TFile *_fileIN_TTbar = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/NoElecID_BadTrk/uhh2.AnalysisModuleRunner.MC.TTbar_Mtt1000toINFT.root", "READ");
  TFile *_fileIN_Zp = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/NoElecID_BadTrk/uhh2.AnalysisModuleRunner.MC.ZpM3000W01.root", "READ");

 
  TH1D *hchi2_QCD = new TH1D("hchi2_QCD","#chi^{2}",500,0,1000);
  TTree *t_QCD = (TTree*)_fileIN_QCD->Get("AnalysisTree");
  t_QCD->Project("hchi2_QCD","rec_chi2");
  hchi2_QCD->SetLineColor(3);
  hchi2_QCD->SetLineWidth(3);
  hchi2_QCD->Draw();



  TH1D *hchi2_TTbar = new TH1D("hchi2_TTbar","#chi^{2}",500,0,1000);
  TTree *t_TTbar = (TTree*)_fileIN_TTbar->Get("AnalysisTree");
  t_TTbar->Project("hchi2_TTbar","rec_chi2");
  hchi2_TTbar->SetLineColor(2);
  hchi2_TTbar->SetLineWidth(2);
  hchi2_TTbar->Draw("same");

TLegend *leg = new TLegend(0.65,0.75,0.98,0.95);
 leg->SetFillColor(0);
 leg->SetTextFont(42);
 leg->SetTextSize(0.05);
 leg->AddEntry(hchi2_QCD,"QCD","l");
 leg->AddEntry(hchi2_TTbar,"TTbar (Mtt>1TeV)","l");
 leg->Draw();
}
