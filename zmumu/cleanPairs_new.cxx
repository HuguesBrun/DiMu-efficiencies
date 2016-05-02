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


void cleanPairs(){
    using namespace std;
    TTree *tIn  = (TTree *) gFile->Get("tpTree/fitter_tree");
    Float_t pt, abseta, tag_pt, tag_eta;
    Int_t DenomDz, Dz;
    Int_t tag_DoubleIsoMu17Mu8_Mu17leg, DoubleIsoMu17Mu8_Mu8leg, DoubleIsoMu17Mu8_Mu17leg, tag_DoubleIsoMu17Mu8_Mu8leg, tag_DoubleIsoMu17Mu8dZ_Mu17leg,   DoubleIsoMu17Mu8dZ_Mu17leg;

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

    tIn->SetBranchAddress("DoubleIsoMu17Mu8dZ_Mu17leg", &DoubleIsoMu17Mu8dZ_Mu17leg);
    tIn->SetBranchAddress("tag_DoubleIsoMu17Mu8dZ_Mu17leg", &tag_DoubleIsoMu17Mu8dZ_Mu17leg);

    // TFile *fOut = new TFile("/tmp/hbrun/tnpZ_theTreeCleaned.root", "RECREATE");
    TFile *fOut = new TFile("~/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/tnpZ_theTreeCleaned.root", "RECREATE");
    fOut->mkdir("tpTree")->cd();
    TTree *tOut = tIn->CloneTree(0);
    // here we add branches
    tOut->Branch("DenomDz", &DenomDz, "DenomDz/I)");
    tOut->Branch("Dz", &Dz, "Dz/I)");

    
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

        DenomDz = 0;
        if((tag_DoubleIsoMu17Mu8_Mu17leg&&DoubleIsoMu17Mu8_Mu8leg)||(DoubleIsoMu17Mu8_Mu17leg&&tag_DoubleIsoMu17Mu8_Mu8leg))
        DenomDz = 1;

        Dz = 0;
        if(DoubleIsoMu17Mu8dZ_Mu17leg||tag_DoubleIsoMu17Mu8dZ_Mu17leg) 
        Dz = 1;

        // cout << "DenomDz  " <<  DenomDz << "\n";
       // cout << Dz << "\n";

        tOut->Fill();

        
       // printf("event=%i, pt=%f, abseta=%f, tag_pt=%f, tag_eta=%f \n", event, pt, abseta, tag_pt, tag_eta);
        
    }
    
    tOut->AutoSave(); // according to root tutorial this is the right thing to do
    fOut->Close();
}
