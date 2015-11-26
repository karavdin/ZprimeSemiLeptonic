void DrawNicePlotsDiff(){
  //Signal
  TFile *_file2 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/SVM_2_chi2/Zprime_01w_SamplesSum.root", "READ");
  TH1D *hMttbarRec_Z01 = (TH1D*)_file2->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_Z01->GetXaxis()->SetTitle("M_{t#bar{t}, rec}, GeV");
  hMttbarRec_Z01->SetLineColor(4);
  hMttbarRec_Z01->SetLineWidth(2);
  hMttbarRec_Z01->SetMarkerStyle(20);
  hMttbarRec_Z01->SetMarkerSize(2.5);
  hMttbarRec_Z01->SetMarkerColor(4);

  TFile *_file3 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/SVM_2_chi2/Zprime_10w_SamplesSum.root", "READ");
  TH1D *hMttbarRec_Z10 = (TH1D*)_file3->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_Z10->SetLineColor(2);
  hMttbarRec_Z10->SetLineWidth(2);
  hMttbarRec_Z10->SetMarkerStyle(20);
  hMttbarRec_Z10->SetMarkerSize(2.5);
  hMttbarRec_Z10->SetMarkerColor(2);

 
  //QCD EMEnriched 
  TFile *_file01 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/SVM_2_chi2/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched.root", "READ");
  TH1D *hMttbarRec_QCD_1 = (TH1D*)_file01->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_QCD_1->SetLineColor(1);
  hMttbarRec_QCD_1->SetLineWidth(2);
  hMttbarRec_QCD_1->SetMarkerColor(1);
  hMttbarRec_QCD_1->SetMarkerStyle(20);
  hMttbarRec_QCD_1->SetMarkerSize(2.5);
  //QCD bcToE
  TFile *_file02 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/SVM_2_chi2/uhh2.AnalysisModuleRunner.MC.QCD_bcToE.root", "READ");
  TH1D *hMttbarRec_QCD_2 = (TH1D*)_file02->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_QCD_2->SetLineColor(14);
  hMttbarRec_QCD_2->SetLineWidth(2);
  hMttbarRec_QCD_2->SetMarkerColor(14);
  hMttbarRec_QCD_2->SetMarkerStyle(20);
  hMttbarRec_QCD_2->SetMarkerSize(2.5);

  TH1D *hMttbarRec_QCD = (TH1D*)hMttbarRec_QCD_1->Clone();
  hMttbarRec_QCD->Add(hMttbarRec_QCD_2);
  hMttbarRec_QCD->SetLineColor(1);
  hMttbarRec_QCD->SetLineWidth(2);
  hMttbarRec_QCD->SetMarkerColor(1);
  hMttbarRec_QCD->SetMarkerStyle(22);
  hMttbarRec_QCD->SetMarkerSize(2.5);

  //ttbar
  TFile *_file03 = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/SVM_2_chi2/uhh2.AnalysisModuleRunner.MC.TTbar.root", "READ");
  TH1D *hMttbarRec_ttbar = (TH1D*)_file03->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_ttbar->SetLineColor(kOrange+2);
  hMttbarRec_ttbar->SetLineWidth(2);
  hMttbarRec_ttbar->SetMarkerColor(kOrange+2);
  hMttbarRec_ttbar->SetMarkerStyle(20);
  hMttbarRec_ttbar->SetMarkerSize(2.5);



  //BEFORE
 //Signal
  TFile *_file2ref = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/Zprime_01w_SamplesSum.root", "READ");
  TH1D *hMttbarRec_Z01ref = (TH1D*)_file2ref->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_Z01ref->GetXaxis()->SetTitle("M_{t#bar{t}, rec}, GeV");
  hMttbarRec_Z01ref->SetLineColor(4);
  hMttbarRec_Z01ref->SetLineWidth(2);
  hMttbarRec_Z01ref->SetMarkerStyle(20);
  hMttbarRec_Z01ref->SetMarkerColor(4);

  TFile *_file3ref = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/Zprime_10w_SamplesSum.root", "READ");
  TH1D *hMttbarRec_Z10ref = (TH1D*)_file3ref->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_Z10ref->SetLineColor(2);
  hMttbarRec_Z10ref->SetLineWidth(2);
  hMttbarRec_Z10ref->SetMarkerStyle(20);
  hMttbarRec_Z10ref->SetMarkerColor(2);

 
  //QCD EMEnriched 
  TFile *_file01ref = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched.root", "READ");
  TH1D *hMttbarRec_QCDref_1 = (TH1D*)_file01ref->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_QCDref_1->SetLineColor(1);
  hMttbarRec_QCDref_1->SetLineWidth(2);
  hMttbarRec_QCDref_1->SetMarkerColor(1);
  hMttbarRec_QCDref_1->SetMarkerStyle(20);

  TFile *_file02ref = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_bcToE.root", "READ");
  TH1D *hMttbarRec_QCDref_2 = (TH1D*)_file02ref->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_QCDref_2->SetLineColor(1);
  hMttbarRec_QCDref_2->SetLineWidth(2);
  hMttbarRec_QCDref_2->SetMarkerColor(1);
  hMttbarRec_QCDref_2->SetMarkerStyle(20);

  TH1D *hMttbarRec_QCDref = (TH1D*)hMttbarRec_QCDref_1->Clone();
  hMttbarRec_QCDref->Add(hMttbarRec_QCDref_2);

  //ttbar
  TFile *_file03ref = new TFile("/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.TTbar.root", "READ");
  TH1D *hMttbarRec_ttbarref = (TH1D*)_file03ref->Get("chi2__hyp_chi2min/M_ttbar_rec");
  hMttbarRec_ttbarref->SetLineColor(kOrange+2);
  hMttbarRec_ttbarref->SetLineWidth(2);
  hMttbarRec_ttbarref->SetMarkerColor(kOrange+2);
  hMttbarRec_ttbarref->SetMarkerStyle(20);
  hMttbarRec_ttbarref->SetMarkerSize(2.5);



  //Now take the difference: (hist_after - hist_before)/hist_before
  hMttbarRec_Z01->Add(hMttbarRec_Z01ref,-1);
  hMttbarRec_Z01->Divide(hMttbarRec_Z01ref);
  hMttbarRec_Z10->Add(hMttbarRec_Z10ref,-1);
  hMttbarRec_Z10->Divide(hMttbarRec_Z10ref);
  hMttbarRec_QCD_1->Add(hMttbarRec_QCDref_1,-1);
  hMttbarRec_QCD_1->Divide(hMttbarRec_QCDref_1);
  hMttbarRec_QCD_2->Add(hMttbarRec_QCDref_2,-1);
  hMttbarRec_QCD_2->Divide(hMttbarRec_QCDref_2);
  hMttbarRec_ttbar->Add(hMttbarRec_ttbarref,-1);
  hMttbarRec_ttbar->Divide(hMttbarRec_ttbarref);

  hMttbarRec_QCD->Add(hMttbarRec_QCDref,-1);
  hMttbarRec_QCD->Divide(hMttbarRec_QCDref);

  //Draw
 TLegend *leg3 = new TLegend(0.65,0.65,0.97,0.95);
 leg3->SetFillColor(0);
 leg3->SetTextFont(42);
 leg3->SetTextSize(0.05);
 leg3->AddEntry(hMttbarRec_Z01,"Z' sum (1%)","lep");
 leg3->AddEntry(hMttbarRec_Z10,"Z' sum (10%)","lep");
 // leg3->AddEntry(hMttbarRec_QCD_1,"QCD EMEnriched","lep");
 // leg3->AddEntry(hMttbarRec_QCD_2,"QCD bcToE","lep");
 leg3->AddEntry(hMttbarRec_QCD,"QCD","lep");
 leg3->AddEntry(hMttbarRec_ttbar,"ttbar","lep");
 hMttbarRec_Z01->GetYaxis()->SetTitle("(N_{after}-N_{before})/N_{before}");
 hMttbarRec_Z01->GetYaxis()->SetRangeUser(-2.,2.);
 //  hMttbarRec_Z01->GetYaxis()->SetRangeUser(-0.35,0.15);
 // hMttbarRec_Z01->GetYaxis()->SetRangeUser(-0.5,0.15);
 hMttbarRec_Z01->GetXaxis()->SetRangeUser(0,3000);
 //hMttbarRec_Z01->GetXaxis()->SetRangeUser(500,4000);
 hMttbarRec_Z01->Draw();
 hMttbarRec_Z10->Draw("same");
 // // hMttbarRec_QCD_1->Draw("same");
 // // hMttbarRec_QCD_2->Draw("same");
 hMttbarRec_ttbar->Draw("same");
 hMttbarRec_QCD->Draw("same");
 leg3->Draw();
 // TLegend *leg4 = new TLegend(0.65,0.77,0.97,0.97);
 // leg4->SetFillColor(0);
 // leg4->SetTextFont(42);
 // leg4->SetTextSize(0.05);
 // leg4->AddEntry(hMttbarRec_Z01,"Z' sum (1%)","lep");
 // leg4->AddEntry(hMttbarRec_Z10,"Z' sum (10%)","lep");
 // leg4->Draw();
}
