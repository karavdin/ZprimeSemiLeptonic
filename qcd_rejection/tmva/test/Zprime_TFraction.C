void Zprime_TFraction(){
 TString fname_data = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/e_eta_below_0_8/uhh2.AnalysisModuleRunner.DATA.SingleEG_2015D_v3.root"; 
 TFile *input_data = TFile::Open( fname_data );
 TH1F *data = (TH1F*)input_data->Get("chi2/ele1__eta");

 TString fname_QCD_EMEnriched = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/e_eta_below_0_8/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched.root";
 TFile *input_QCD_EMEnriched = TFile::Open( fname_QCD_EMEnriched );
 TH1F *QCD_EMEnriched = (TH1F*)input_QCD_EMEnriched->Get("chi2/ele1__eta");

 TString fname_QCD_bcToE = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/e_eta_below_0_8/uhh2.AnalysisModuleRunner.MC.QCD_bcToE.root";
 TFile *input_QCD_bcToE = TFile::Open( fname_QCD_bcToE );
 TH1F *QCD_bcToE = (TH1F*)input_QCD_bcToE->Get("chi2/ele1__eta");

 // TString fname_TTbar = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/uhh2.AnalysisModuleRunner.MC.TTbar.root";
 // TFile *input_TTbar = TFile::Open( fname_TTbar );
 // TH1F *TTbar = (TH1F*)input_TTbar->Get("chi2/ele1__eta");

 // TString fname_ST = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/uhh2.AnalysisModuleRunner.MC.ST.root";
 // TFile *input_ST = TFile::Open( fname_ST);
 // TH1F *ST = (TH1F*)input_ST->Get("chi2/ele1__eta");

 // TString fname_WJets = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/uhh2.AnalysisModuleRunner.MC.WJetsToLNu.root";
 // TFile *input_WJets = TFile::Open( fname_WJets);
 // TH1F *WJets = (TH1F*)input_ST->Get("chi2/ele1__eta");

 TString fname_allButQCD = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/e_eta_below_0_8/uhh2.AnalysisModuleRunner.MC.All_But_QCD.root";
 TFile *input_allButQCD = TFile::Open( fname_allButQCD);
 TH1F *allButQCD = (TH1F*)input_allButQCD->Get("chi2/ele1__eta");
 TObjArray *mc = new TObjArray(3); 
 mc->Add(allButQCD);
 mc->Add(QCD_EMEnriched);
 mc->Add(QCD_bcToE);

 // mc->Add(TTbar);
 // mc->Add(ST);
 // mc->Add(WJets);

 TFractionFitter* fit = new TFractionFitter(data, mc, "V"); // initialise
 // fit->SetRangeX(0,20);                    // skip bins with negative weight
  // fit->Constrain(0,0.9,1.1);               // constrain fraction 1 to be between 0 and 1
  // fit->Constrain(1,0.9,1.1);               // fix fraction 2
  // fit->Constrain(2,0.99,1.01);               // fix fraction 2
 fit->Constrain(0,0.332,0.334);     
 // fit->Constrain(1,0.,1.);     
 fit->Constrain(2,0.,1.);     

//fit->Constrain(0,0.0,1.0);     

 //frction 2

  TVirtualFitter* vFit = (TVirtualFitter*)fit->GetFitter();
  //vFit->FixParameter(0);
 // vFit->FixParameter(3);
 // vFit->PrintResults(10,0);

 Int_t status = fit->Fit();               // perform the fit
 //vFit->SetMaxIterations(1000);
 
 // vFit->FixParameter(1);

 // fit->SetRangeX(10,90);                    // skip bins w/o data
 // fit->SetRangeX(100,400);                    // skip bins w/o data

 
 // Int_t status = vFit->Fit();
 std::cout << "fit status: " << status << std::endl;
 if (status == 0) {                       // check on fit status
   TH1F* result = (TH1F*) fit->GetPlot();
   data->Draw("Ep");
   result->Draw("same");
 }
}
