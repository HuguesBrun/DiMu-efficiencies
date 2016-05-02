#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include "TRandom.h" 
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>


//   (data)  /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/DoubleMuon/treesJson9thOctober/TnP_data_doubleMuonPart3.root
//   root -b -q -l theOldTree.C cleanPairs.cxx++
//   root -b -q -l fine.root cleanPairs.cxx++
//   root -b -q -l /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/DoubleMuon/treesJson9thOctober/TnP_data_doubleMuonPart3.root cleanPairs.cxx++ 
//   /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp
//   root -b -q -l  /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/test_WithWeights_smallMCstat.root cleanPairs.cxx++  
// 
//root -b -q -l /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/test_WithWeights_new.root
// /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/agrebeny/totalData.root

void cleanPairs_21Feb(){
    using namespace std;
    TTree *tIn  = (TTree *) gFile->Get("tpTree/fitter_tree");
    Float_t pt, abseta, tag_pt, tag_eta;
    Int_t DenomDz, Dz, DzTkM8, DenomMu17Eff, Mu17Eff, DenomMu17TkMu8Eff, EffMu17Mu8, EffMu17TkMu8, pathOr, pathOrMu20, EffMu17Mu8nodz, EffMu17TkMu8nodz, pathOrnodz;
    Int_t tag_DoubleIsoMu17Mu8_Mu17leg, DoubleIsoMu17Mu8_Mu8leg, DoubleIsoMu17Mu8_Mu17leg, tag_DoubleIsoMu17Mu8_Mu8leg, tag_DoubleIsoMu17Mu8dZ_Mu17leg,   DoubleIsoMu17Mu8dZ_Mu17leg, Mu17_IsoTrkVVL, tag_Mu17_IsoTrkVVL, tag_IsoMu20, IsoMu20, tag_IsoTkMu20, IsoTkMu20 ;

    Int_t tag_DoubleIsoMu17TkMu8_Mu17leg, DoubleIsoMu17TkMu8_TkMu8leg, DoubleIsoMu17TkMu8_Mu17leg, tag_DoubleIsoMu17TkMu8_TkMu8leg, tag_DoubleIsoMu17TkMu8dZ_Mu17,   DoubleIsoMu17TkMu8dZ_Mu17;

    UInt_t event;

  
    
    tIn->SetBranchAddress("pt", &pt);
    tIn->SetBranchAddress("abseta", &abseta);
    tIn->SetBranchAddress("tag_pt", &tag_pt);
    tIn->SetBranchAddress("tag_eta", &tag_eta);
    tIn->SetBranchAddress("event", &event);

    tIn->SetBranchAddress("tag_DoubleIsoMu17Mu8_Mu17leg", &tag_DoubleIsoMu17Mu8_Mu17leg);
    tIn->SetBranchAddress("DoubleIsoMu17Mu8_Mu8leg", &DoubleIsoMu17Mu8_Mu8leg);

    tIn->SetBranchAddress("DoubleIsoMu17Mu8_Mu17leg", &DoubleIsoMu17Mu8_Mu17leg);
    tIn->SetBranchAddress("tag_DoubleIsoMu17Mu8_Mu8leg", &tag_DoubleIsoMu17Mu8_Mu8leg);

    tIn->SetBranchAddress("DoubleIsoMu17TkMu8_Mu17leg", &DoubleIsoMu17TkMu8_Mu17leg);
    tIn->SetBranchAddress("tag_DoubleIsoMu17TkMu8_TkMu8leg", &tag_DoubleIsoMu17TkMu8_TkMu8leg);

    tIn->SetBranchAddress("DoubleIsoMu17Mu8dZ_Mu17leg", &DoubleIsoMu17Mu8dZ_Mu17leg);
    tIn->SetBranchAddress("tag_DoubleIsoMu17Mu8dZ_Mu17leg", &tag_DoubleIsoMu17Mu8dZ_Mu17leg);

    tIn->SetBranchAddress("DoubleIsoMu17TkMu8dZ_Mu17", &DoubleIsoMu17TkMu8dZ_Mu17);
    tIn->SetBranchAddress("tag_DoubleIsoMu17TkMu8dZ_Mu17", &tag_DoubleIsoMu17TkMu8dZ_Mu17);

    tIn->SetBranchAddress("Mu17_IsoTrkVVL", &Mu17_IsoTrkVVL);
    tIn->SetBranchAddress("tag_Mu17_IsoTrkVVL", &tag_Mu17_IsoTrkVVL);


    // TFile *fOut = new TFile("/tmp/hbrun/tnpZ_theTreeCleaned.root", "RECREATE");
  //  TFile *fOut = new TFile("~/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/tnpZ_theTreeCleaned_MCsmallstat_eff_nodz.root", "RECREATE");

   TFile *fOut = new TFile("~/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/tnpZ_theTreeCleaned_MC_eff_new_test.root", "RECREATE");

  //  TFile *fOut = new TFile("~/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/tnpZ_theTreeCleaned_data_eff_nodz.root", "RECREATE");


    fOut->mkdir("tpTree")->cd();
    TTree *tOut = tIn->CloneTree(0);
    // here we add branches
    tOut->Branch("DenomDz", &DenomDz, "DenomDz/I)");
    tOut->Branch("Dz", &Dz, "Dz/I)");
    tOut->Branch("DzTkM8", &DzTkM8, "DzTkM8/I)");

    tOut->Branch("EffMu17Mu8", &EffMu17Mu8, "EffMu17Mu8/I)");
    tOut->Branch("EffMu17TkMu8", &EffMu17TkMu8, "EffMu17TkMu8/I)");
    tOut->Branch("pathOr", &pathOr, "pathOr/I)");
    tOut->Branch("pathOrMu20", &pathOrMu20, "pathOrMu20/I)");

// nodz 
    tOut->Branch("EffMu17Mu8nodz", &EffMu17Mu8nodz, "EffMu17Mu8nodz/I)");
    tOut->Branch("EffMu17TkMu8nodz", &EffMu17TkMu8nodz, "EffMu17TkMu8nodz/I)");
    tOut->Branch("pathOrnodz", &pathOrnodz, "pathOrnodz/I)");


    tOut->Branch("DenomMu17Eff", &DenomMu17Eff, "DenomMu17Eff/I)");
    tOut->Branch("Mu17Eff", &Mu17Eff, "Mu17Eff/I)");
    tOut->Branch("DenomMu17TkMu8Eff", &DenomMu17TkMu8Eff, "DenomMu17TkMu8Eff/I)");

    
    int step = tIn->GetEntries()/100;
    double evDenom = 100.0/double(tIn->GetEntries());
    TStopwatch timer; timer.Start();
	float ptNow, tagPtNow;
    float ptNext, tagPtNext;
    TRandom *rando = new TRandom();
    for (int i = 0, n = tIn->GetEntries(); i < n; ++i) {
   // for (int i = 0, n = 100; i < n; ++i) {
        tIn->GetEntry(i);
        
        if ((i+1) % step == 0) {
            double totalTime = timer.RealTime()/60.; timer.Continue();
            double fraction = double(i+1)/double(n+1), remaining = totalTime*(1-fraction)/fraction;
            printf("Done %9d/%9d   %5.1f%%   (elapsed %5.1f min, remaining %5.1f min)\n", i, n, i*evDenom, totalTime, remaining);
            fflush(stdout);
        }
       
        ptNow = pt;
        tagPtNow = tag_pt;
        
        tIn->GetEntry(i+1);
        ptNext = pt;
        tagPtNext = tag_pt;
  
      
        if ((ptNext==tagPtNow)&&(tagPtNext==ptNow)){
        //   printf("found a double pair ! \n");
            float theRand = rando->Uniform(0,2);
            if (theRand>=1) tIn->GetEntry(i); else tIn->GetEntry(i+1);
            i++;
        }
        else tIn->GetEntry(i);

        // add branches
       // cout << tag_DoubleIsoMu17Mu8_Mu17leg << "\n";
       //


        DenomDz = 0;
        if((tag_DoubleIsoMu17Mu8_Mu17leg&&DoubleIsoMu17Mu8_Mu8leg)||(DoubleIsoMu17Mu8_Mu17leg&&tag_DoubleIsoMu17Mu8_Mu8leg))
        DenomDz = 1;

        Dz = 0;
        if(DoubleIsoMu17Mu8dZ_Mu17leg||tag_DoubleIsoMu17Mu8dZ_Mu17leg) 
        Dz = 1;
//----------------------with dz -----------------------------
        EffMu17Mu8 = 0;
        if((tag_DoubleIsoMu17Mu8dZ_Mu17leg&&DoubleIsoMu17Mu8_Mu8leg)||(DoubleIsoMu17Mu8dZ_Mu17leg&&tag_DoubleIsoMu17Mu8_Mu8leg))
        EffMu17Mu8 = 1;

        EffMu17TkMu8 = 0;
        if((tag_DoubleIsoMu17TkMu8dZ_Mu17&&DoubleIsoMu17TkMu8_TkMu8leg)||(DoubleIsoMu17TkMu8dZ_Mu17&&tag_DoubleIsoMu17TkMu8_TkMu8leg))
        EffMu17TkMu8 = 1;

        pathOr=0;
        if(EffMu17Mu8||EffMu17TkMu8)
        pathOr=1;

        pathOrMu20=0;
        if(EffMu17Mu8||EffMu17TkMu8||tag_IsoMu20||IsoMu20||tag_IsoTkMu20||IsoTkMu20)
        pathOrMu20=1;

//----------------------no dz -----------------------------
        EffMu17Mu8nodz = 0;
        if((tag_DoubleIsoMu17Mu8_Mu17leg&&DoubleIsoMu17Mu8_Mu8leg)||(DoubleIsoMu17Mu8_Mu17leg&&tag_DoubleIsoMu17Mu8_Mu8leg))
        EffMu17Mu8nodz = 1;

        EffMu17TkMu8nodz = 0;
        if((tag_DoubleIsoMu17TkMu8_Mu17leg&&DoubleIsoMu17TkMu8_TkMu8leg)||(DoubleIsoMu17TkMu8_Mu17leg&&tag_DoubleIsoMu17TkMu8_TkMu8leg))
        EffMu17TkMu8nodz = 1;

        pathOrnodz=0;
        if(EffMu17Mu8nodz||EffMu17TkMu8nodz)
        pathOrnodz=1;
//-----------------------------------------------------------------------
        DzTkM8 = 0;
        if(DoubleIsoMu17TkMu8dZ_Mu17||tag_DoubleIsoMu17TkMu8dZ_Mu17) 
        DzTkM8 = 1;

        // ----------- new Dz eff (require Mu17_IsoTrkVVL to be on)

        DenomMu17Eff=0;
        //if(((tag_DoubleIsoMu17Mu8_Mu17leg&&DoubleIsoMu17Mu8_Mu8leg)||(DoubleIsoMu17Mu8_Mu17leg&&tag_DoubleIsoMu17Mu8_Mu8leg))&&(DoubleIsoMu17Mu8dZ_Mu17leg||tag_DoubleIsoMu17Mu8dZ_Mu17leg))
        if((Mu17_IsoTrkVVL||tag_Mu17_IsoTrkVVL)&&((tag_DoubleIsoMu17Mu8_Mu17leg&&DoubleIsoMu17Mu8_Mu8leg)||(DoubleIsoMu17Mu8_Mu17leg&&tag_DoubleIsoMu17Mu8_Mu8leg)))
        DenomMu17Eff=1;

        DenomMu17TkMu8Eff=0;
        if((Mu17_IsoTrkVVL||tag_Mu17_IsoTrkVVL)&&((tag_DoubleIsoMu17TkMu8_Mu17leg&&DoubleIsoMu17TkMu8_TkMu8leg)||(DoubleIsoMu17TkMu8_Mu17leg&&tag_DoubleIsoMu17TkMu8_TkMu8leg)))
        DenomMu17TkMu8Eff=1;


// HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL

       // ----------- ref trigger Mu 17

        Mu17Eff = 0;
        if(Mu17_IsoTrkVVL||tag_Mu17_IsoTrkVVL)
        Mu17Eff = 1;





        // cout << "DenomDz  " <<  DenomDz << "\n";
        // cout << Dz << "\n";
        // cout << DenomMu17Eff << " , " << Mu17Eff << "\n";

        tOut->Fill();

        
       // printf("event=%i, pt=%f, abseta=%f, tag_pt=%f, tag_eta=%f \n", event, pt, abseta, tag_pt, tag_eta);
        
    }
    
    tOut->AutoSave(); // according to root tutorial this is the right thing to do
    fOut->Close();
}
