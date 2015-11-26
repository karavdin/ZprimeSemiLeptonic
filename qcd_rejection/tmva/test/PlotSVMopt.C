void PlotSVMopt(){

 //  // TString FileData = "SVMoptData.dat";
//   TFile *f = new TFile("SVMoptTree.root","RECREATE");
//   TTree *T = new TTree("SVMoptTree","data from ascii file");
//   Long64_t nlines = T->ReadFile("SVMoptData.dat","Gamma:C:ROCint:SigAt1Bkg_test:SigAt1Bkg_train");
//   printf(" found %lld pointsn",nlines);
//   T->Write();

// TGraph2D *grROCint = new TGraph2D();
//  for(int i=0;i<nlines;i++){

//    grROCint->SetPoint(i,);
//  }

  TGraph2D *grROCint = new TGraph2D();
  

TGraph2D *grSigAt1Bkg_test = new TGraph2D();
TGraph2D *grOverTrain = new TGraph2D();

 TString dir = gSystem->UnixPathName(__FILE__);
 dir.ReplaceAll("PlotSVMopt.C","");
 dir.ReplaceAll("/./","/");
 ifstream in;
 // in.open(Form("%sSVMoptData.dat",dir.Data()));
 in.open(Form("%sSVMoptData_NEW2.dat",dir.Data()));

 Float_t Gamma,C,ROCint, SigAt1Bkg_test, SigAt1Bkg_train;
 Int_t nlines = 0;
 while (1) {
   in >> Gamma >> C >> ROCint >> SigAt1Bkg_test >> SigAt1Bkg_train;
   if (!in.good()) break;
   // if (in.good()){
      if (nlines < 5) printf("Gamma=%8f, C=%8f, ROCint=%8f\n",Gamma, C, ROCint);
      grROCint->SetPoint(nlines,Gamma,C,ROCint);
      grSigAt1Bkg_test->SetPoint(nlines,Gamma,C,SigAt1Bkg_test);
      grOverTrain->SetPoint(nlines,Gamma,C,fabs(SigAt1Bkg_train-SigAt1Bkg_test));
      nlines++;
      //   }
   }
   printf(" found %d points\n",nlines);
   in.close();
   TCanvas *cSVMopt = new TCanvas("cSVMopt","SVM model choice",600,600);
   cSVMopt->Divide(2,2);
   cSVMopt->cd(1);
   cSVMopt_1->SetLogx();
   cSVMopt_1->SetLogy();
   grROCint->GetXaxis()->SetLabelSize(0.04);
   grROCint->GetYaxis()->SetLabelSize(0.04);
   grROCint->GetZaxis()->SetLabelSize(0.04);
   grROCint->GetXaxis()->SetTitle("#gamma");
   grROCint->GetYaxis()->SetTitle("C");
   grROCint->GetZaxis()->SetTitle("ROC integral");
   grROCint->SetTitle("ROC integral");
   grROCint->SetMaximum(1.0);
   grROCint->SetMinimum(0.9);
   grROCint->Draw("COLZ");
   cSVMopt->cd(2);
   cSVMopt_2->SetLogx();
   cSVMopt_2->SetLogy();
   grSigAt1Bkg_test->SetTitle("Signal at 1% Bkg level (test)");
   //   grSigAt1Bkg_test->Draw("surf1");
   grSigAt1Bkg_test->Draw("COLZ");
   cSVMopt->cd(3);
   cSVMopt_3->SetLogx();
   cSVMopt_3->SetLogy();
   grOverTrain->SetTitle("Overtraining");
   grOverTrain->Draw("COLZ");
   //cSVMopt->SaveAs("SVMoptC1.root");
}
