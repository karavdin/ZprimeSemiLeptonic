// @(#)root/tmva $Id$
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *    module use -a /afs/desy.de/group/cms/modulefiles/                           *
 *    module load root/5.34                                                       *
 *    root -l ./Zprime_vs_QCD_TMVAClassification_SVMoptimisation.C\(\"SVM\",\"1\",\"1\"\)  *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"


#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void Zprime_vs_QCD_TMVAClassification_SVMoptimisation( TString myMethodList = "", TString sG="1", TString sC="1")
{
TStopwatch t;
t.Start(); 

   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc

   // methods to be processed can be given as an argument; use format:
   //
   // mylinux~> root -l Zprime_vs_QCD_TMVAClassification_SVMoptimisation.C\(\"myMethod1,myMethod2,myMethod3\"\)
   //
   // if you like to use a method via the plugin mechanism, we recommend using
   //
   // mylinux~> root -l Zprime_vs_QCD_TMVAClassification_SVMoptimisation.C\(\"P_myMethod\"\)
   // (an example is given for using the BDT as plugin (see below),
   // but of course the real application is when you write your own
   // method based)

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // to get access to the GUI and all tmva macros
   //   TString thisdir = gSystem->DirName(gInterpreter->GetCurrentMacroName());
   ///  gROOT->SetMacroPath(thisdir + ":" + gROOT->GetMacroPath());
  

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

  
   // --- Support Vector Machine 
   Use["SVM"]             = 1;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start Zprime_vs_QCD_TMVAClassification_SVMoptimisation" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "Zprime_vs_QCD_TMVAClassification_SVMoptimisation", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   (TMVA::gConfig().GetVariablePlotting()).fNbins2D = 100; //binning of 2D hists
   (TMVA::gConfig().GetVariablePlotting()).fNbins1D = 50; //binning of 1D hists

   // // If you wish to modify default settings
   // // (please check "src/Config.h" to see all available global options)
   // //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   // //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

 

   factory->AddVariable("lep_pt","lepton p_{T}","GeV/c", 'F' );
   factory->AddVariable("lep_fbrem","lep f_{brem}","", 'F' );
   factory->AddVariable("MwT","M^{W}_{T}","GeV", 'F' );
   factory->AddVariable("log(ljet_pt)","log(lead jet p_{T})","", 'F' );
   factory->AddVariable("log(met_pt)","log(missing E_{T})","", 'F' );
   factory->AddVariable("log(lep_pt_ljet)","log(p_{T, rel}(lep, lead jet))","", 'F' );
   factory->AddVariable("log(fabs((dR_cljet_ljet-3.14)/3.14))","log(|#Delta R(close jet, lead jet)-#pi|/#pi)","", 'F' );
   factory->AddVariable("log(dR_lep_cljet)","log(#Delta R(lep, close jet))","", 'F' );
   
   factory->SetSignalWeightExpression("weight");
   factory->SetBackgroundWeightExpression("weight");
  
   factory->AddSpectator("dPhi_lep_cljet","#Delta #phi(lep, close jet)","rad", 'F' );


   TString fname_sig_1 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w0500.root";
   TFile *input_sig_1 = TFile::Open( fname_sig_1 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input SIGNAL file: " << input_sig_1->GetName() << std::endl;

   TString fname_sig_2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w1000.root";
   TFile *input_sig_2 = TFile::Open( fname_sig_2 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input SIGNAL file: " << input_sig_2->GetName() << std::endl;

   TString fname_sig_3 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w1500.root";
   TFile *input_sig_3 = TFile::Open( fname_sig_3 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input SIGNAL file: " << input_sig_3->GetName() << std::endl;

TString fname_sig_4 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w2000.root";
   TFile *input_sig_4 = TFile::Open( fname_sig_4 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input SIGNAL file: " << input_sig_3->GetName() << std::endl;

TString fname_sig_5 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w3000.root";
   TFile *input_sig_5 = TFile::Open( fname_sig_5 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input SIGNAL file: " << input_sig_5->GetName() << std::endl;

   TString fname_bkg_1 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0080to0120.root";
   TFile *input_bkg_1 = TFile::Open( fname_bkg_1 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input BACKGROUND file: " << input_bkg_1->GetName() << std::endl;
   TString fname_bkg_2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0120to0170.root";
   TFile *input_bkg_2 = TFile::Open( fname_bkg_2 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input BACKGROUND file: " << input_bkg_2->GetName() << std::endl;
   TString fname_bkg_3 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0170to0300.root";
   TFile *input_bkg_3 = TFile::Open( fname_bkg_3 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input BACKGROUND file: " << input_bkg_3->GetName() << std::endl;
   TString fname_bkg_4 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_bcToE_Pt0250toINF.root";
   TFile *input_bkg_4 = TFile::Open( fname_bkg_4 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification_SVMoptimisation       : Using input BACKGROUND file: " << input_bkg_4->GetName() << std::endl;

   // --- Register the training and test trees

   TTree *signal_1     = (TTree*)input_sig_1->Get("AnalysisTree");
   TTree *signal_2     = (TTree*)input_sig_2->Get("AnalysisTree");
   TTree *signal_3     = (TTree*)input_sig_3->Get("AnalysisTree");
   TTree *signal_4     = (TTree*)input_sig_4->Get("AnalysisTree");
   TTree *signal_5     = (TTree*)input_sig_5->Get("AnalysisTree");
   TTree *background_1 = (TTree*)input_bkg_1->Get("AnalysisTree");
   TTree *background_2 = (TTree*)input_bkg_2->Get("AnalysisTree");
   TTree *background_3 = (TTree*)input_bkg_3->Get("AnalysisTree");
   TTree *background_4 = (TTree*)input_bkg_4->Get("AnalysisTree");
   
   
   // Double_t LumiData = 3*552.67;
   // Double_t signalWeight_2     = 1./LumiData;    Double_t signalWeight_4     = 1./LumiData;    Double_t signalWeight_5     = 1./LumiData;
   Double_t LumiData = 552.67;
   Double_t signalWeight_2     = 4000/(LumiData*5374.);
   Double_t signalWeight_4     = 4000/(LumiData*18587.);
   Double_t signalWeight_5     = 4000/(LumiData*11331.);
   factory->AddSignalTree    ( signal_2,signalWeight_2);
   factory->AddSignalTree    ( signal_4,signalWeight_4);
   factory->AddSignalTree    ( signal_5,signalWeight_5);
   factory->AddBackgroundTree( background_1, 2.04);
   factory->AddBackgroundTree( background_2, 2.04);
   factory->AddBackgroundTree( background_3, 2.04);
   factory->AddBackgroundTree( background_4, 2.04);

   // --- end of tree registration 


   // Apply additional cuts on the signal and background samples (can be different)
    TCut mycuts = "";
    TCut mycutb = "";
   
   factory->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

   // ---- Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

  
   TString sSVM_options = "Gamma=";
   sSVM_options+=sG;
   sSVM_options+=":C=";
   sSVM_options+=sC;
   sSVM_options+=":Tol=0.01:VarTransform=Norm";
   
   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( TMVA::Types::kSVM, "SVM", sSVM_options );

   

   // For an example of the category classifier usage, see: Zprime_vs_QCD_TMVAClassification_SVMoptimisationCategory
   
   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

   // ---- STILL EXPERIMENTAL and only implemented for BDT's ! 
   // factory->OptimizeAllMethods("SigEffAt001","Scan");
   // factory->OptimizeAllMethods("ROCIntegral","FitGA");

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> Zprime_vs_QCD_TMVAClassification_SVMoptimisation is done!" << std::endl;

   delete factory;
   /*
   // Launch the GUI for the root macros
   TString thisdir = "/afs/desy.de/user/k/karavdia/CMSSW_7_4_9/UHH2/ZprimeSemiLeptonic/qcd_rejection/tmva/test";
   cout<<"this dir = "<<thisdir<<endl;
   gROOT->SetMacroPath(thisdir);
   gROOT->ProcessLine(".L TMVAGui.C");
   if (!gROOT->IsBatch()) TMVAGui( outfileName );*/
   cout<<"sSVM_options: "<<sSVM_options<<endl;
   t.Stop();
   t.Print(); 
}
