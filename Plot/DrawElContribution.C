//This macro plots contribution of electrons with different reconstructed types vs eta

void DrawElContribution(){
  //Input file
  //  TFile *_fileIN = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/CutID_tight/uhh2.AnalysisModuleRunner.MC.QCD.root", "READ");
  // TFile *_fileIN = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/CutID_tight/uhh2.AnalysisModuleRunner.MC.TTbar_Mtt1000toINFT.root", "READ");
  TFile *_fileIN = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v2/ttbarLJAnalysis/CutID_tight/uhh2.AnalysisModuleRunner.MC.ZpM3000W01.root", "READ");

  TH1F *hEl_Gold = (TH1F*)_fileIN->Get("chi2/ele1__eta_Gold");
  hEl_Gold->GetXaxis()->SetTitle("#eta");
  hEl_Gold->SetMarkerStyle(21);
  hEl_Gold->SetMarkerSize(2.0);
  hEl_Gold->SetMarkerColor(8);
  hEl_Gold->SetLineColor(8);
 

  TH1F *hEl_BigBrem = (TH1F*)_fileIN->Get("chi2/ele1__eta_BigBrem");
  hEl_BigBrem->GetXaxis()->SetTitle("#eta");
  hEl_BigBrem->SetMarkerStyle(21);
  hEl_BigBrem->SetMarkerSize(2.0);
  hEl_BigBrem->SetMarkerColor(5);
  hEl_BigBrem->SetLineColor(5);
 


  TH1F *hEl_Shower = (TH1F*)_fileIN->Get("chi2/ele1__eta_Shower");
  hEl_Shower->GetXaxis()->SetTitle("#eta");
  hEl_Shower->SetMarkerStyle(21);
  hEl_Shower->SetMarkerSize(2.0);
  hEl_Shower->SetMarkerColor(9);
  hEl_Shower->SetLineColor(9);
  

  TH1F *hEl_BadTrk = (TH1F*)_fileIN->Get("chi2/ele1__eta_BadTrk");
  hEl_BadTrk->GetXaxis()->SetTitle("#eta");
  hEl_BadTrk->SetMarkerStyle(21);
  hEl_BadTrk->SetMarkerSize(2.0);
  hEl_BadTrk->SetMarkerColor(kOrange+7);
  hEl_BadTrk->SetLineColor(kOrange+7);
  hEl_Shower->GetXaxis()->SetRangeUser(-2.5,2.5);
  hEl_Shower->GetYaxis()->SetRangeUser(0,1.5);
  //  hEl_Shower->GetXaxis()->SetRangeUser(0,2.5);


  TH1F *hEl_sum = (TH1F*)hEl_Gold->Clone();
  hEl_sum->Add(hEl_BigBrem);
  hEl_sum->Add(hEl_Shower);
  hEl_sum->Add(hEl_BadTrk);

  hEl_Gold->Divide(hEl_sum);
  hEl_BigBrem->Divide(hEl_sum);
  hEl_Shower->Divide(hEl_sum);
  hEl_BadTrk->Divide(hEl_sum);

  hEl_Shower->Draw();
  hEl_BadTrk->Draw("same");
  hEl_Gold->Draw("same");
  hEl_BigBrem->Draw("same");




  TLegend *leg = new TLegend(0.75,0.70,0.95,0.95);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->AddEntry(hEl_Gold,"Golden","lp");
  leg->AddEntry(hEl_Shower,"Shower","lp");
  leg->AddEntry(hEl_BigBrem,"Big Brem","lp");
  leg->AddEntry(hEl_BadTrk,"Bad Trk","lp");
  leg->Draw();

  // //Signal
//   TFile *_file2 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/Zprime_01w_SamplesSum.root", "READ");



//   TH1D *hBDT_Z01 = new TH1D("hBDT_Z01",";MVA response;",100,0,1);
//   tZ01->Project("hBDT_Z01","TMVA_response","");
//   hBDT_Z01->SetLineColor(4);
//   hBDT_Z01->SetLineWidth(2);
//   TH1D *hMttbarRec_Z01 = (TH1D*)_file2->Get("chi2__hyp_chi2min/M_ttbar_rec");
//   hMttbarRec_Z01->GetXaxis()->SetTitle("M_{t#bar{t}, rec}, GeV");
//   hMttbarRec_Z01->SetLineColor(4);
//   hMttbarRec_Z01->SetLineWidth(2);
//   hMttbarRec_Z01->SetMarkerStyle(20);
//   hMttbarRec_Z01->SetMarkerColor(4);
//   hMttbarRec_Z01->SetMarkerSize(1.5);

//  TFile *_file3 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/Zprime_10w_SamplesSum.root", "READ");
//   TTree *tZ10 = (TTree*)_file3->Get("AnalysisTree");
//   TH1D *hBDT_Z10 = new TH1D("hBDT_Z10",";MVA response;",100,0,1);
//   tZ10->Project("hBDT_Z10","TMVA_response","");
//   hBDT_Z10->SetLineColor(2);
//   hBDT_Z10->SetLineWidth(2);
// TH1D *hMttbarRec_Z10 = (TH1D*)_file3->Get("chi2__hyp_chi2min/M_ttbar_rec");
//   hMttbarRec_Z10->SetLineColor(2);
//   hMttbarRec_Z10->SetLineWidth(2);
//   hMttbarRec_Z10->SetMarkerStyle(20);
//   hMttbarRec_Z10->SetMarkerColor(2);
//   hMttbarRec_Z10->SetMarkerSize(1.5);

//  TFile *_file4 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w1000.root", "READ");
//   TTree *tZ10_1000 = (TTree*)_file4->Get("AnalysisTree");
//   TH1D *hBDT_Z10_1000 = new TH1D("hBDT_Z10_1000",";MVA response;",100,0,1);
//   tZ10_1000->Project("hBDT_Z10_1000","TMVA_response","");
//   hBDT_Z10_1000->SetLineColor(kOrange-4);
//   hBDT_Z10_1000->SetLineStyle(2);
//   hBDT_Z10_1000->SetFillColor(kOrange-4);
//   hBDT_Z10_1000->SetFillStyle(3335);
//   hBDT_Z10_1000->SetLineWidth(2);
 

//  TFile *_file5 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w2000.root", "READ");
//   TTree *tZ10_2000 = (TTree*)_file5->Get("AnalysisTree");
//   TH1D *hBDT_Z10_2000 = new TH1D("hBDT_Z10_2000",";MVA response;",100,0,1);
//   tZ10_2000->Project("hBDT_Z10_2000","TMVA_response","");
//   hBDT_Z10_2000->SetLineColor(kOrange+7);
//   hBDT_Z10_2000->SetLineStyle(2);
//   hBDT_Z10_2000->SetFillColor(kOrange+7);
//   hBDT_Z10_2000->SetFillStyle(3353);
//   hBDT_Z10_2000->SetLineWidth(2);

//   TFile *_file6 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w3500.root", "READ");
//   TTree *tZ10_3000 = (TTree*)_file6->Get("AnalysisTree");
//   TH1D *hBDT_Z10_3000 = new TH1D("hBDT_Z10_3000",";MVA response;",100,0,1);
//   tZ10_3000->Project("hBDT_Z10_3000","TMVA_response","");
//   hBDT_Z10_3000->SetLineColor(kPink-8);
//   //  hBDT_Z10_3000->SetFillColor(kPink-8);
//   hBDT_Z10_3000->SetLineStyle(2);
//   //  hBDT_Z10_3000->SetFillStyle(3353);
//   hBDT_Z10_3000->SetLineWidth(2);

//   //QCD
//   TFile *_file01 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched.root", "READ");
//   TTree *tQCD_1 = (TTree*)_file01->Get("AnalysisTree");
//   TH1D *hBDT_QCD_1 = new TH1D("hBDT_QCD_1",";MVA response;",100,0,1);
//   tQCD_1->Project("hBDT_QCD_1","TMVA_response","");
//   hBDT_QCD_1->SetLineColor(1);
//   hBDT_QCD_1->SetLineWidth(2);
//   TH1D *hMttbarRec_QCD_1 = (TH1D*)_file01->Get("chi2__hyp_chi2min/M_ttbar_rec");
//   hMttbarRec_QCD_1->SetLineColor(1);
//   hMttbarRec_QCD_1->SetLineWidth(2);

//   hMttbarRec_QCD_1->SetMarkerColor(1);
//   hMttbarRec_QCD_1->SetMarkerStyle(20);
//   hMttbarRec_QCD_1->SetMarkerSize(1.5);

//   TFile *_file02 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_bcToE.root", "READ");
//   TTree *tQCD_2 = (TTree*)_file02->Get("AnalysisTree");
//   TH1D *hBDT_QCD_2 = new TH1D("hBDT_QCD_2",";MVA response;",100,0,1);
//   tQCD_2->Project("hBDT_QCD_2","TMVA_response","");
//   hBDT_QCD_2->SetLineColor(14);
//   hBDT_QCD_2->SetLineWidth(2);
//   TH1D *hMttbarRec_QCD_2 = (TH1D*)_file02->Get("chi2__hyp_chi2min/M_ttbar_rec");
//   hMttbarRec_QCD_2->SetLineColor(14);
//   hMttbarRec_QCD_2->SetLineWidth(2);

//   hMttbarRec_QCD_2->SetMarkerColor(14);
//   hMttbarRec_QCD_2->SetMarkerStyle(20);
//   hMttbarRec_QCD_2->SetMarkerSize(1.5);



//   //Draw
// TLegend *leg = new TLegend(0.10,0.65,0.45,0.85);
//  leg->SetFillColor(0);
//  leg->SetTextFont(42);
//  leg->SetTextSize(0.05);
//  leg->AddEntry(hBDT_Z01,"Z' sum (1%)","l");
//  leg->AddEntry(hBDT_Z10,"Z' sum (10%)","l");
//  leg->AddEntry(hBDT_QCD_1,"QCD EMEnriched","l");
//  leg->AddEntry(hBDT_QCD_2,"QCD bcToE","l");


// TLegend *leg2 = new TLegend(0.47,0.65,0.8,0.85);
//  leg2->SetFillColor(0);
//  leg2->SetTextFont(42);
//  leg2->SetTextSize(0.05);
//  leg2->AddEntry(hBDT_Z10_1000,"Z' (1.0 TeV, 10%)","lf");
//  leg2->AddEntry(hBDT_Z10_2000,"Z' (2.0 TeV, 10%)","lf");
//  leg2->AddEntry(hBDT_Z10_3000,"Z' (3.5 TeV, 10%)","lf");


//   hBDT_Z01->Draw();
//  hBDT_Z10->Draw("same");
//  hBDT_Z10_3000->Draw("same");
//  hBDT_Z10_2000->Draw("same");
//  hBDT_Z10_1000->Draw("same");
//  hBDT_QCD_1->Draw("same");
//  hBDT_QCD_2->Draw("same");
//  leg->Draw();
//  leg2->Draw();
 
// // TLegend *leg3 = new TLegend(0.62,0.75,0.95,0.95);
// //  leg3->SetFillColor(0);
// //  leg3->SetTextFont(42);
// //  leg3->SetTextSize(0.05);
// //  leg3->AddEntry(hMttbarRec_Z01,"Z' sum (1%)","lep");
// //  leg3->AddEntry(hMttbarRec_Z10,"Z' sum (10%)","lep");
// //  leg3->AddEntry(hMttbarRec_QCD_1,"QCD EMEnriched","lep");
// //  leg3->AddEntry(hMttbarRec_QCD_2,"QCD bcToE","lep");
// //  hMttbarRec_Z01->Draw();
// //  hMttbarRec_Z10->Draw("same");
// //  hMttbarRec_QCD_1->Draw("same");
// //  hMttbarRec_QCD_2->Draw("same");
// //  leg3->Draw();
}
