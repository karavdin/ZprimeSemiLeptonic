/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: PlotDecisionBoundary                                               *
 *                                                                                *
 * Plots decision boundary for simple cases in 2 (3?) dimensions                  *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TH3F.h"

#include "tmvaglob.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "TMVA/SeparationBase.h"
#include "TMVA/GiniIndex.h"
#include "TMVA/MisClassificationError.h"
#endif

using namespace TMVA;


void plot(TH2D *sig, TH2D *bkg, TH2F *MVA, TString v0="var0", TString v1="var1",Float_t mvaCut=0){

   TCanvas *c = new TCanvas(Form("DecisionBoundary%s",MVA->GetTitle()),MVA->GetTitle(),800,800);
   c->cd();
   cout <<  "MVACut = "<<mvaCut << endl;
   gStyle->SetPalette(1);
   MVA->SetXTitle(v0);
   MVA->SetYTitle(v1);
   MVA->SetStats(0);
   Double_t contours[1];
   contours[0]=mvaCut;
   MVA->SetLineWidth(7);
   MVA->SetLineStyle(1);
   MVA->SetMarkerColor(1);
   MVA->SetLineColor(1);
   MVA->SetContour(1, contours);
   sig->SetMarkerColor(4);
   bkg->SetMarkerColor(2);
   sig->SetMarkerStyle(20);
   bkg->SetMarkerStyle(20);
   sig->SetMarkerSize(.2);
   bkg->SetMarkerSize(.2);
   sig->Draw();
   bkg->Draw("same");
   MVA->Draw("CONT2 same");
}


void PlotDecisionBoundary( TString weightFile = "weights/Zprime_vs_QCD_TMVAClassification_BDT.weights.xml",TString v0="lep_pt_ljet", TString v1="met_pt", TString dataFileNameS = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/uhh2.AnalysisModuleRunner.MC.Zp01w3000.root", TString dataFileNameB = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched.root") 
{   
   //---------------------------------------------------------------
   // default MVA methods to be trained + tested

   // this loads the library
   TMVA::Tools::Instance();

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;


   //
   // create the Reader object
   //
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   // create a set of variables and declare them to the reader
   // - the variable names must corresponds in name and type to 
   // those given in the weight file(s) that you use
   // Float_t var0, var1;
   // reader->AddVariable( v0,                &var0 );
   // reader->AddVariable( v1,                &var1 );
   Float_t lep_pt, lep_fbrem, MwT;
   Float_t log_ljet_pt, log_met_pt, log_lep_pt_ljet;
   Float_t log_dR_lep_cljet, log_dR_cljet_ljet;
   Float_t dPhi_lep_cljet;
   reader->AddVariable("lep_pt", &lep_pt);
   reader->AddVariable("lep_fbrem", & lep_fbrem);
   reader->AddVariable("MwT", &MwT);
   reader->AddVariable("log(ljet_pt)", &log_ljet_pt);
   reader->AddVariable("log(met_pt)",&log_met_pt);
   reader->AddVariable("log(lep_pt_ljet)",&log_lep_pt_ljet);
   reader->AddVariable("log(dR_lep_cljet)",&log_dR_lep_cljet_trans);
   reader->AddVariable("log(fabs((dR_cljet_ljet-3.14)/3.14))", &log_dR_cljet_ljet);
   reader->AddSpectator("dPhi_lep_cljet", &dPhi_lep_cljet);
   //
   // book the MVA method
   //
   reader->BookMVA( "BDT", weightFile ); 
   
   TFile *fS = new TFile(dataFileNameS);
   TTree *signal     = (TTree*)fS->Get("AnalysisTree");
   TFile *fB = new TFile(dataFileNameS);
   TTree *background = (TTree*)fB->Get("AnalysisTree");


//Declaration of leaves types
   Float_t         svar0;
   Float_t         svar1;
   Float_t         bvar0;
   Float_t         bvar1;
   Float_t         sWeight=1.0; // just in case you have weight defined, also set these branchaddresses
   Float_t         bWeight=1.0*signal->GetEntries()/background->GetEntries(); // just in case you have weight defined, also set these branchaddresses

   // Set branch addresses.
   signal->SetBranchAddress(v0,&svar0);
   signal->SetBranchAddress(v1,&svar1);
   background->SetBranchAddress(v0,&bvar0);
   background->SetBranchAddress(v1,&bvar1);






   UInt_t nbin = 50;
   Float_t xmax = signal->GetMaximum(v0.Data());
   Float_t xmin = signal->GetMinimum(v0.Data());
   Float_t ymax = signal->GetMaximum(v1.Data());
   Float_t ymin = signal->GetMinimum(v1.Data());
 
   xmax = TMath::Max(xmax,(Float_t)background->GetMaximum(v0.Data()));  
   xmin = TMath::Min(xmin,(Float_t)background->GetMinimum(v0.Data()));
   ymax = TMath::Max(ymax,(Float_t)background->GetMaximum(v1.Data()));
   ymin = TMath::Min(ymin,(Float_t)background->GetMinimum(v1.Data()));


   TH2D *hs=new TH2D("hs","",nbin,xmin,xmax,nbin,ymin,ymax);   
   TH2D *hb=new TH2D("hb","",nbin,xmin,xmax,nbin,ymin,ymax);   
   hs->SetXTitle(v0);
   hs->SetYTitle(v1);
   hb->SetXTitle(v0);
   hb->SetYTitle(v1);
   hs->SetMarkerColor(4);
   hb->SetMarkerColor(2);


   TH2F * hist = new TH2F( "MVA",    "MVA",    nbin,xmin,xmax,nbin,ymin,ymax);

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.

   Float_t MinMVA=10000, MaxMVA=-100000;
   for (UInt_t ibin=1; ibin<nbin+1; ibin++){
      for (UInt_t jbin=1; jbin<nbin+1; jbin++){
         var0 = hs->GetXaxis()->GetBinCenter(ibin);
         var1 = hs->GetYaxis()->GetBinCenter(jbin);
         Float_t mvaVal=reader->EvaluateMVA( "BDT" ) ;
         if (MinMVA>mvaVal) MinMVA=mvaVal;
         if (MaxMVA<mvaVal) MaxMVA=mvaVal;
         hist->SetBinContent(ibin,jbin, mvaVal);
      }
   }


   // now you need to try to find the MVA-value at which you cut for the plotting of the decision boundary
   // (Use the smallest number of misclassifications as criterion)
   const Int_t nValBins=100;
   Double_t    sum = 0.;
   TH1F *mvaS= new TH1F("mvaS","",nValBins,MinMVA,MaxMVA); mvaS->SetXTitle("MVA-ouput"); mvaS->SetYTitle("#entries");
   TH1F *mvaB= new TH1F("mvaB","",nValBins,MinMVA,MaxMVA); mvaB->SetXTitle("MVA-ouput"); mvaB->SetYTitle("#entries");
   TH1F *mvaSC= new TH1F("mvaSC","",nValBins,MinMVA,MaxMVA); mvaSC->SetXTitle("MVA-ouput"); mvaSC->SetYTitle("cummulation");
   TH1F *mvaBC= new TH1F("mvaBC","",nValBins,MinMVA,MaxMVA); mvaBC->SetXTitle("MVA-ouput"); mvaBC->SetYTitle("cummulation");

   Long64_t nentries;
   nentries = signal->GetEntries();
   for (Long64_t is=0; is<nentries;is++) {
      signal->GetEntry(is);
      sum +=sWeight;
      var0 = svar0;
      var1 = svar1;
      Float_t mvaVal=reader->EvaluateMVA( "BDT" ) ;
      hs->Fill(svar0,svar1);
      mvaS->Fill(mvaVal,sWeight);
   }
   nentries = background->GetEntries();
   for (Long64_t ib=0; ib<nentries;ib++) {
      background->GetEntry(ib);
      sum +=bWeight;
      var0 = bvar0;
      var1 = bvar1;
      Float_t mvaVal=reader->EvaluateMVA( "BDT" ) ;
      hb->Fill(bvar0,bvar1);
      mvaB->Fill(mvaVal,bWeight);
   }

   SeparationBase *sepGain = new MisClassificationError();
   //SeparationBase *sepGain = new GiniIndex();
   //SeparationBase *sepGain = new CrossEntropy();

   Double_t sTot = mvaS->GetSum();
   Double_t bTot = mvaB->GetSum();

   mvaSC->SetBinContent(1,mvaS->GetBinContent(1));
   mvaBC->SetBinContent(1,mvaB->GetBinContent(1));
   Double_t sSel=mvaSC->GetBinContent(1);
   Double_t bSel=mvaBC->GetBinContent(1);
   Double_t sSelBest=0;
   Double_t bSelBest=0;
   Double_t separationGain=sepGain->GetSeparationGain(sSel,bSel,sTot,bTot);
   Double_t mvaCut=mvaSC->GetBinCenter(1);
   Double_t mvaCutOrientation=1; // 1 if mva > mvaCut --> Signal and -1 if mva < mvaCut (i.e. mva*-1 > mvaCut*-1) --> Signal
   for (UInt_t ibin=2;ibin<nValBins;ibin++){ 
      mvaSC->SetBinContent(ibin,mvaS->GetBinContent(ibin)+mvaSC->GetBinContent(ibin-1));
      mvaBC->SetBinContent(ibin,mvaB->GetBinContent(ibin)+mvaBC->GetBinContent(ibin-1));
    
      sSel=mvaSC->GetBinContent(ibin);
      bSel=mvaBC->GetBinContent(ibin);

      if (separationGain < sepGain->GetSeparationGain(sSel,bSel,sTot,bTot)){
         separationGain = sepGain->GetSeparationGain(sSel,bSel,sTot,bTot);
         mvaCut=mvaSC->GetBinCenter(ibin);
         if (sSel/bSel > (sTot-sSel)/(bTot-bSel)) mvaCutOrientation=-1;
         else                                     mvaCutOrientation=1;
         sSelBest=sSel;
         bSelBest=bSel;
     }
   }
   

   cout << "Min="<<MinMVA << " Max=" << MaxMVA 
        << " sTot=" << sTot
        << " bTot=" << bTot
        << " sSel=" << sSelBest
        << " bSel=" << bSelBest
        << " sepGain="<<separationGain
        << " cut=" << mvaCut
        << " cutOrientation="<<mvaCutOrientation
        << endl;


   delete reader;

   gStyle->SetPalette(1);

  
   plot(hs,hb,hist     ,v0,v1,mvaCut);


   TCanvas *cm=new TCanvas ("cm","",900,1200);
   cm->cd();
   cm->Divide(1,2);
   cm->cd(1);
   mvaS->SetLineColor(4);
   mvaB->SetLineColor(2);
   mvaS->Draw();
   mvaB->Draw("same");

   cm->cd(2);
   mvaSC->SetLineColor(4);
   mvaBC->SetLineColor(2);
   mvaBC->Draw();
   mvaSC->Draw("same");

   // TH1F *add=(TH1F*)mvaBC->Clone("add");
   // add->Add(mvaSC);

   // add->Draw();

   // errh->Draw("same");

   //
   // write histograms
   //
   TFile *target  = new TFile( "TMVAPlotDecisionBoundary.root","RECREATE" );

   hs->Write();
   hb->Write();

   hist->Write();

   target->Close();

} 

