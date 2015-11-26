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
 *    root -l ./Zprime_vs_QCD_TMVAClassification.C\(\"BDT,RuleFit,MLP,Fisher,Cuts\"\)  *
 *    root -l ./Zprime_vs_QCD_TMVAClassification.C\(\"BDT\"\)  *
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

void Zprime_vs_QCD_TMVAClassification( TString myMethodList = "" )
{
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc

   // methods to be processed can be given as an argument; use format:
   //
   // mylinux~> root -l Zprime_vs_QCD_TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)
   //
   // if you like to use a method via the plugin mechanism, we recommend using
   //
   // mylinux~> root -l Zprime_vs_QCD_TMVAClassification.C\(\"P_myMethod\"\)
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

   // --- Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 1;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // --- 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 1;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 1;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 1; // k-nearest neighbour method
   //
   // --- Linear Discriminant Analysis
   Use["LD"]              = 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   //
   // --- Support Vector Machine 
   Use["SVM"]             = 1;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 1;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start Zprime_vs_QCD_TMVAClassification" << std::endl;

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
   TMVA::Factory *factory = new TMVA::Factory( "Zprime_vs_QCD_TMVAClassification", outputFile,
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
   // //smooth here
   // factory->AddVariable("ljet_pt","lead jet p_{T}","GeV/c", 'F' );
   // factory->AddVariable("met_pt","missing E_{T}","GeV/c^{2}", 'F' );
   // factory->AddVariable("lep_pt_ljet","p_{T, rel}(lep, lead jet)","GeV/c", 'F' );
   factory->AddVariable("log(ljet_pt)","log(lead jet p_{T})","", 'F' );
   factory->AddVariable("log(met_pt)","log(missing E_{T})","", 'F' );
   factory->AddVariable("log(lep_pt_ljet)","log(p_{T, rel}(lep, lead jet))","", 'F' );
   //factory->AddVariable("dR_cljet_ljet","#Delta R(close jet, lead jet)","", 'F' );
   //factory->AddVariable("dR_lep_cljet","#Delta R(lep, close jet)","", 'F' );
   factory->AddVariable("log(fabs((dR_cljet_ljet-3.14)/3.14))","log(|#Delta R(close jet, lead jet)-#pi|/#pi)","", 'F' );
   factory->AddVariable("log(dR_lep_cljet)","log(#Delta R(lep, close jet))","", 'F' );
   
   factory->SetSignalWeightExpression("weight");
   factory->SetBackgroundWeightExpression("weight");

   // //  factory->AddVariable("dPhi_met_lep","#Delta#phi(MET, lep)","rad", 'F' ); //Correleated with MwT
   // factory->AddVariable("log(dR_lep_cljet)","log(#Delta R(lep, close jet))","", 'F' );

   //   factory->AddVariable("exp(dR_cljet_ljet)","exp(#Delta R(close jet, lead jet))","", 'F' );

   //   factory->AddVariable("lep_xy","lep vtx #sqrt{x^{2}+y^{2}}","cm", 'F' );
   //   factory->AddVariable("lep_eta","lepton #eta","", 'F' );
   //   factory->AddVariable("dPhi_met_lep","#Delta#phi(MET, lep)","rad", 'F' ); //Correleated with MwT
  
   factory->AddSpectator("dPhi_lep_cljet","#Delta #phi(lep, close jet)","rad", 'F' );




   TString fname_sig_1 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w0500.root";
   TFile *input_sig_1 = TFile::Open( fname_sig_1 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_1->GetName() << std::endl;

 TString fname_sig_2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w1000.root";
 TFile *input_sig_2 = TFile::Open( fname_sig_2 );
 std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_2->GetName() << std::endl;

TString fname_sig_3 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w1500.root";
   TFile *input_sig_3 = TFile::Open( fname_sig_3 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_3->GetName() << std::endl;

TString fname_sig_4 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w2000.root";
   TFile *input_sig_4 = TFile::Open( fname_sig_4 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_3->GetName() << std::endl;

TString fname_sig_5 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp01w3000.root";
   TFile *input_sig_5 = TFile::Open( fname_sig_5 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_5->GetName() << std::endl;

// TString fname_sig_5 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w0500.root";
//    TFile *input_sig_5 = TFile::Open( fname_sig_5 );
//    std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_5->GetName() << std::endl;

// TString fname_sig_6 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w1000.root";
//    TFile *input_sig_6 = TFile::Open( fname_sig_6 );
//    std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_6->GetName() << std::endl;

// TString fname_sig_7 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w2000.root";
//    TFile *input_sig_7 = TFile::Open( fname_sig_7 );
//    std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_7->GetName() << std::endl;

// TString fname_sig_8 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w3000.root";
//    TFile *input_sig_8 = TFile::Open( fname_sig_8 );
//    std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_8->GetName() << std::endl;


   // TString fname_sig_2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.Zp10w3000.root";

   // TFile *input_sig_2 = TFile::Open( fname_sig_2 );
   // std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input SIGNAL file: " << input_sig_2->GetName() << std::endl;

   TString fname_bkg_1 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0080to0120.root";
   TFile *input_bkg_1 = TFile::Open( fname_bkg_1 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input BACKGROUND file: " << input_bkg_1->GetName() << std::endl;
   TString fname_bkg_2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0120to0170.root";
   TFile *input_bkg_2 = TFile::Open( fname_bkg_2 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input BACKGROUND file: " << input_bkg_2->GetName() << std::endl;
   TString fname_bkg_3 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_EMEnriched_Pt0170to0300.root";
   TFile *input_bkg_3 = TFile::Open( fname_bkg_3 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input BACKGROUND file: " << input_bkg_3->GetName() << std::endl;
   TString fname_bkg_4 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_25ns_v1/test_03/NOCUTS/uhh2.AnalysisModuleRunner.MC.QCD_bcToE_Pt0250toINF.root";
   TFile *input_bkg_4 = TFile::Open( fname_bkg_4 );
   std::cout << "--- Zprime_vs_QCD_TMVAClassification       : Using input BACKGROUND file: " << input_bkg_4->GetName() << std::endl;

   // --- Register the training and test trees

   TTree *signal_1     = (TTree*)input_sig_1->Get("AnalysisTree");
   TTree *signal_2     = (TTree*)input_sig_2->Get("AnalysisTree");
   TTree *signal_3     = (TTree*)input_sig_3->Get("AnalysisTree");
   TTree *signal_4     = (TTree*)input_sig_4->Get("AnalysisTree");
   TTree *signal_5     = (TTree*)input_sig_5->Get("AnalysisTree");
   // TTree *signal_6     = (TTree*)input_sig_6->Get("AnalysisTree");
   // TTree *signal_7     = (TTree*)input_sig_7->Get("AnalysisTree"); 
   // TTree *signal_8     = (TTree*)input_sig_8->Get("AnalysisTree"); 
   TTree *background_1 = (TTree*)input_bkg_1->Get("AnalysisTree");
   TTree *background_2 = (TTree*)input_bkg_2->Get("AnalysisTree");
   TTree *background_3 = (TTree*)input_bkg_3->Get("AnalysisTree");
   TTree *background_4 = (TTree*)input_bkg_4->Get("AnalysisTree");
   
   /*
   // global event weights per tree (see below for setting event-wise weights)
   Double_t LumiData = 552.67;
   Double_t SF_QCD_1 = 2.04;
   Double_t signalWeight     = 1.0;
   Double_t signalWeight_2     = 10*LumiData/5374.;
   Double_t signalWeight_4     = 10*LumiData/18587.;
   Double_t signalWeight_5     = 10*LumiData/11331.;
   Double_t backgroundWeight_1 = SF_QCD_1*LumiData/23.18;
   Double_t backgroundWeight_2 = SF_QCD_1*LumiData/134.7;
   Double_t backgroundWeight_3 = SF_QCD_1*LumiData/304.3;
   Double_t backgroundWeight_4 = SF_QCD_1*LumiData/2732.4;

   // Double_t backgroundWeight_2 = LumiData/(149.56+1212.55+4595.67);
   
   // You can add an arbitrary number of signal or background trees
   // factory->AddSignalTree    ( signal_1,     signalWeight     );
   factory->AddSignalTree    ( signal_2,     signalWeight_2     );
   //  factory->AddSignalTree    ( signal_3,     signalWeight     );
   factory->AddSignalTree    ( signal_4,     signalWeight_4     );
   factory->AddSignalTree    ( signal_5,     signalWeight_5     );
   // factory->AddSignalTree    ( signal_6,     signalWeight     );
   // factory->AddSignalTree    ( signal_7,     signalWeight     );
   // factory->AddSignalTree    ( signal_8,     signalWeight     );

   factory->AddBackgroundTree( background_1, backgroundWeight_1);
   factory->AddBackgroundTree( background_2, backgroundWeight_2);
   factory->AddBackgroundTree( background_3, backgroundWeight_3);
   factory->AddBackgroundTree( background_4, backgroundWeight_4); */
   /*
 Double_t signalWeight_2     = 2000/(LumiData*5374.);
 Double_t signalWeight_4     = 2000/(LumiData*18587.);
 Double_t signalWeight_5     = 2000/(LumiData*11331.);*/
   Double_t LumiData = 552.67;
   Double_t signalWeight_2     = 4000/(LumiData*5374.);
   Double_t signalWeight_4     = 4000/(LumiData*18587.);
   Double_t signalWeight_5     = 4000/(LumiData*11331.);
   // Double_t signalWeight_2     = 20./(LumiData*5374.);
   // Double_t signalWeight_4     = 20./(LumiData*18587.);
   // Double_t signalWeight_5     = 20.0/(LumiData*11331.);
//Double_t signalWeight_2     = 1./LumiData;    Double_t signalWeight_4     = 1./LumiData;    Double_t signalWeight_5     = 1./LumiData;
   factory->AddSignalTree    ( signal_2,signalWeight_2);
   factory->AddSignalTree    ( signal_4,signalWeight_4);
   factory->AddSignalTree    ( signal_5,signalWeight_5);
   factory->AddBackgroundTree( background_1, 2.04);
   factory->AddBackgroundTree( background_2, 2.04);
   factory->AddBackgroundTree( background_3, 2.04);
   factory->AddBackgroundTree( background_4, 2.04);
   // factory->AddBackgroundTree( background_1, 2.04/(7.));
   // factory->AddBackgroundTree( background_2, 2.04/(260.));
   // factory->AddBackgroundTree( background_3, 2.04/(2199.));
   // factory->AddBackgroundTree( background_4, 2.04/(6501.));

   // --- end of tree registration 


   // Apply additional cuts on the signal and background samples (can be different)
    TCut mycuts = "";
   TCut mycutb = "";
   // TCut mycuts = "dPhi_lep_cljet>1.5";
   // TCut mycutb = "dPhi_lep_cljet>1.5";
   // TCut mycutb = "dR_lep_cljet<1.";
   // TCut mycuts = "lep_pt_cljet<500.";
   // TCut mycutb = "lep_pt_cljet<500.";

   /*TCut mycuts = "dR_lep_cljet<0.1";
     TCut mycutb = "dR_lep_cljet<0.1"; */
   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //    factory->PrepareTrainingAndTestTree( mycut,
   //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   factory->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );

   // ---- Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
      factory->BookMethod( TMVA::Types::kPDERS, "PDERS",
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

   if (Use["PDERSD"])
      factory->BookMethod( TMVA::Types::kPDERS, "PDERSD",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
      factory->BookMethod( TMVA::Types::kPDERS, "PDERSPCA",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
      factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam",
                           "!H:!V:SigBgSeparate=F:TailCut=0.01:VolFrac=0.0001:nActiveCells=10:nSampl=5:nBin=5:Nmin=2:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
      factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoamBoost",
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
      factory->BookMethod( TMVA::Types::kKNN, "KNN",
                           "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
      factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );

   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
      factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher", 
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

   if (Use["MLPBFGS"])
      factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod( TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.2:C=3:Tol=0.01:VarTransform=Norm" );

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=100:BoostType=AdaBoost:AdaBoostBeta=0.5:Shrinkage=0.10:nCuts=20:MaxDepth=3" );
   //SUDA
   if (Use["BDT"])  // Adaptive Boost
     //     factory->BookMethod( TMVA::Types::kBDT, "BDT",
     //               "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" ); //SeparationType=MisClassificationError UseNvars=100 :Boost_Num=1 :PruneMethod=NoPruning
     factory->BookMethod(TMVA::Types::kBDT, "BDT",
			 "!H:!V:CreateMVAPdfs:NTrees=200:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.05:SeparationType=MisClassificationError:UseRandomisedTrees=True");

   if (Use["BDTB"]) // Bagging
      factory->BookMethod( TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher",
                           "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
      factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.01:RuleMinDist=0.1:NTrees=100:fEventsMin=0.2:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=1000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: Zprime_vs_QCD_TMVAClassificationCategory
   
   /*
   
   // --- Categorised classifier                                                                                                       
   TMVA::MethodCategory* mcatBDT = 0;  
   TMVA::MethodCategory* mcatSVM = 0;                                                                                                   
    // The variable sets               
                                                                                                 
   TString theCat1Vars = "lep_pt:lep_fbrem:MwT:log(ljet_pt):log(met_pt):log(lep_pt_ljet):log(dR_lep_cljet):log(fabs((dR_cljet_ljet-3.14)/3.14))";
   TString theCat2Vars = "lep_pt:lep_fbrem:MwT:log(ljet_pt):log(met_pt):log(lep_pt_ljet):dR_lep_cljet:log(fabs((dR_cljet_ljet-3.14)/3.14))";                              

   // BDT with categories                                                                                                           
   TMVA::MethodBase* SVMCat = factory->BookMethod( TMVA::Types::kCategory, "SVMCat","" );                                            
   mcatSVM = dynamic_cast<TMVA::MethodCategory*>(SVMCat);                                                                                  
   mcatSVM->AddMethod( "dPhi_lep_cljet<=1.5", theCat1Vars, TMVA::Types::kSVM, "Category_SVM_1", "Gamma=0.5:C=100:Tol=0.01:VarTransform=Norm");
   mcatSVM->AddMethod( "dPhi_lep_cljet>1.5", theCat2Vars, TMVA::Types::kSVM, "Category_SVM_2", "Gamma=1:C=1:Tol=0.01:VarTransform=Norm");

   TMVA::MethodBase* BDTCat = factory->BookMethod( TMVA::Types::kCategory, "BDTCat","" );                                            
   mcatBDT = dynamic_cast<TMVA::MethodCategory*>(BDTCat);                                                                                  
   mcatBDT->AddMethod( "dPhi_lep_cljet<=1.5", theCat1Vars, TMVA::Types::kBDT, "Category_BDT_1", "!H:!V:CreateMVAPdfs:NTrees=200:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.1:PruneMethod=NoPruning:SeparationType=MisClassificationError:DoBoostMonitor=True:UseRandomisedTrees=True");                          
   mcatBDT->AddMethod( "dPhi_lep_cljet>1.5",  theCat2Vars, TMVA::Types::kBDT, "Category_BDT_2", "!H:!V:CreateMVAPdfs:NTrees=100:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.1:PruneMethod=NoPruning:SeparationType=MisClassificationError:DoBoostMonitor=True:UseRandomisedTrees=True"); 

   // --------------------------------------------------------------------------------------------------
   */
   
   /*
   mcat->AddMethod( "dR_lep_cljet<0.1", theCatAllVars, TMVA::Types::kBDT, "Category_BDT_1", "!H:!V:CreateMVAPdfs:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.1:PruneMethod=NoPruning:SeparationType=MisClassificationError:DoBoostMonitor=True:UseRandomisedTrees=True");                          
   mcat->AddMethod( "dR_lep_cljet>0.1 && dR_lep_cljet<0.4",  theCatAllVars, TMVA::Types::kBDT, "Category_BDT_2", "!H:!V:CreateMVAPdfs:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.1:PruneMethod=NoPruning:SeparationType=MisClassificationError:DoBoostMonitor=True:UseRandomisedTrees=True");                          
   mcat->AddMethod( "dR_lep_cljet>0.4",  theCatAllVars, TMVA::Types::kBDT, "Category_BDT_3", "!H:!V:CreateMVAPdfs:NTrees=200:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.1:PruneMethod=NoPruning:SeparationType=MisClassificationError:DoBoostMonitor=True:UseRandomisedTrees=True");                    
   */
  

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
   std::cout << "==> Zprime_vs_QCD_TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   TString thisdir = "/afs/desy.de/user/k/karavdia/CMSSW_7_4_9/UHH2/ZprimeSemiLeptonic/qcd_rejection/tmva/test";
   cout<<"this dir = "<<thisdir<<endl;
   gROOT->SetMacroPath(thisdir);
   gROOT->ProcessLine(".L TMVAGui.C");
   if (!gROOT->IsBatch()) TMVAGui( outfileName );
}
