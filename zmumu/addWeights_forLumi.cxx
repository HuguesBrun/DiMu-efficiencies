#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include <vector>
#include <iostream>

//root.exe -b -l -q /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/TnP_MCDYNLO_tot123.root /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/DoubleMuon/treesJson9thOctober/TnP_data_doubleMuonPart3.root addWeights.cxx+


// root.exe -b -l -q  /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/tnpZ_MC_tot.root /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/DoubleMuon/treesJson9thOctober/TnP_data_doubleMuonPart1.root addWeights.cxx+

//root.exe -b -l -q  /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/agrebeny/muonPOGtnpTrees/DoubleMuon/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/TnPtreesMCmadgraphNLOdoubleMuon76/160201_151200/0000/totalMC.root  /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/agrebeny/muonPOGtnpTrees/DoubleMuon/DoubleMuon/tpTreeDataDoubleMureRECO/160131_155358/0000/totalData.root addWeights.cxx+

//root.exe -b -l -q /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/agrebeny/totalData.root /afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/agrebeny/singleMutotv41RunD.root addWeights.cxx+


void addWeights(TString treeName="tpTree", TString cut = "Mu17_IsoTrkVVL||tag_Mu17_IsoTrkVVL") { 
  // Example of cut string:  TString cut="(tag_IsoMu20_eta2p1 || tag_IsoMu20) && tag_combRelIso < 0.15")

    if (gROOT->GetListOfFiles()->GetSize() < 2) {
        std::cerr << "[addWeights]: USAGE: root.exe -b -l -q mcFile.root dataFile.root [more data files...] addWeights.cxx+" << std::endl;
        return;
    }

    std::cout << "[addWeights]: Gathering input trees ..." << std::endl;

    TTree  &tMC = * (TTree *) ((TFile*)gROOT->GetListOfFiles()->At(0))->Get(treeName+"/fitter_tree");

    TChain tData( treeName+"/fitter_tree" );
    for (int i = 1; i < gROOT->GetListOfFiles()->GetSize(); ++i) {
      tData.AddFile(((TFile*)gROOT->GetListOfFiles()->At(i))->GetName());
    }

    std::cout << "[addWeights]: Filling distributions of lumi ..." << std::endl;

  float Bins1[25]={1000., 1300., 1500.,1700.,2000.,2200.,2500., 2600., 2700., 2800., 2900.,3000., 3100., 3200., 3300., 3400.,3500., 3600., 3700., 4000., 4300., 4500., 4700., 5000., 5500.};

   TH1F* hLumiData = new TH1F("hLumiData", "", 24, Bins1);
   TH1F* hLumiMC = new TH1F("hLumiMC", "", 24, Bins1);
  

  // globTree ->Project("HistRB","tag_instLumi","1");

    //tData.Draw("tag_instLumi>>hLumiData(25,1000.,5500.)", "1"); // single-mu
    tData.Draw("tag_instLumi>>hLumiData", "1"); // single-mu
    tMC.Draw("tag_instLumi>>hLumiMC", cut);  // di-mu

    std::cout << "[addWeights]: Computing lumi weight vector ..." << std::endl;

    hLumiData = (TH1F*) gROOT->FindObject("hLumiData");
    hLumiMC = (TH1F*) gROOT->FindObject("hLumiMC");
    hLumiData->Scale(1.0/hLumiData->Integral());
    hLumiMC->Scale(1.0/hLumiMC->Integral());

    std::vector<double> lumiWeights(hLumiData->GetNbinsX()+1, 1.0);
    for (int i = 1, n = lumiWeights.size(); i < n; ++i) {
        double nMC = hLumiMC->GetBinContent(i), nData = hLumiData->GetBinContent(i);
        lumiWeights[i-1] = (nMC > 0 ? nData/nMC : 1.0);
         cout << " i = " << i  << " , MC =  " << hLumiMC->GetBinContent(i) << " , Data = " << hLumiData->GetBinContent(i) << " , weight = " << lumiWeights[i-1] << " , lumiMC = " << hLumiMC->GetBinContent(i)  << "\n";
    }

    std::cout << "[addWeights]: Adding weight column ..." << std::endl;

    Float_t nVtx, weight, genWeight, tag_instLumi ;
    tMC.SetBranchAddress("tag_instLumi", &tag_instLumi);
   // tMC.SetBranchAddress("pair_genWeight", &genWeight);

    TString mcFileName(gROOT->GetListOfFiles()->At(0)->GetName());
    // TString outFileName = (mcFileName.First(".") > 0 ? mcFileName(0,mcFileName.First(".")) : mcFileName)  + "_WithWeights.root";
    // TString outFileName =  "/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/test_WithWeights_new.root";
    TString outFileName =  "/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_smp/VJets/Bonzai13TeVoutput/tmp/test_data_lumirew.root";

    TFile *fOut = new TFile(outFileName, "RECREATE");
    fOut->mkdir("tpTree")->cd();
    TTree *tOut = tMC.CloneTree(0);
    tOut->Branch("weightLumi", &weight, "weight/F");
    int step = tMC.GetEntries()/100;
    double evDenom = 100.0/double(tMC.GetEntries());
    TStopwatch timer; timer.Start();

    for (int i = 0, n = tMC.GetEntries(); i < n; ++i) {
        tMC.GetEntry(i);
        // cout << hMC->GetXaxis()->FindBin(x) << "\n";
        // cout << hMC->GetBinContent(hMC->GetXaxis()->FindBin(x)) << "\n";
        // cout << " lumi = " << tag_instLumi << " , bin " << hLumiMC->GetXaxis()->FindBin(tag_instLumi)  << " , weight = " << lumiWeights[hLumiMC->GetXaxis()->FindBin(tag_instLumi)-1]  << "\n";
           weight = lumiWeights[hLumiMC->GetXaxis()->FindBin(tag_instLumi)-1];
        // weight = lumiWeights[int(nVtx)];
	// weight *= ( genWeight > 0 ? 1. : -1.);     
        if (i < 20) {
            printf("[addWeights]: Event with %d tag_instLumi gets a weight of %.4f\n", int(tag_instLumi), weight);
        }
        tOut->Fill();
        if ((i+1) % step == 0) { 
            double totalTime = timer.RealTime()/60.; timer.Continue();
            double fraction = double(i+1)/double(n+1), remaining = totalTime*(1-fraction)/fraction;
            printf("[addWeights]: Done %9d/%9d   %5.1f%%   (elapsed %5.1f min, remaining %5.1f min)\r", i, n, i*evDenom, totalTime, remaining); 
            fflush(stdout); 
        }
    }

    std::cout << std::endl;

    tOut->AutoSave(); // according to root tutorial this is the right thing to do

    TH1F* hLumiDATAReweight = new TH1F("hLumiDATAReweight", "", 24, Bins1);

    TString weightPlusCut = cut.Length() > 0 ? "weight*(" + cut + ")" : "weight";
    tOut->Draw("(tag_instLumi)>>hLumiDATAReweight", weightPlusCut);

    // hLumiDATAReweight = (TH1F*) gROOT->FindObject("hLumiDATAReweight");
    std::cout << "[addWeights]: Integral of Lumi distribution after applying weights : " << hLumiDATAReweight->Integral() << std::endl;
    hLumiDATAReweight->Scale(1.0/hLumiDATAReweight->Integral());

    TCanvas *cVtx = new TCanvas("cVtx","cVtx");
 
    hLumiData->SetLineColor(kOrange+7);
    hLumiData->SetLineStyle(7);
    hLumiMC->SetLineColor(kAzure+7);
    hLumiMC->SetLineStyle(9);
    hLumiDATAReweight->SetLineColor(kGreen+1);

    hLumiDATAReweight->GetXaxis()->SetTitle("tag_instLumi");

    hLumiDATAReweight->Draw("hist");
    hLumiData->Draw("same");
    hLumiMC->Draw("same");

    TLegend * legVtx = new TLegend(0.6,0.5,0.9,0.7);
    legVtx->AddEntry(hLumiData,"single-mu data","lep");   // single-mu
    legVtx->AddEntry(hLumiMC,"double-mu data before reweighting","lep");  // double-mu
    legVtx->AddEntry(hLumiDATAReweight,"double-mu data after reweighting","lep");
    legVtx->Draw(); 

    cVtx->Print("tagLumi.png");

    TString ptPlotCut("(tag_IsoMu20 && tag_combRelIso < 0.15 && pt > 20 && Tight2012)");

    tOut->Draw("pt>>hPtMCReweight(150,-0.5,199.5)", ptPlotCut + " * weight");
    tData.Draw("pt>>hPtData(150,-0.5,199.5)", ptPlotCut );
    tMC.Draw("pt>>hPtMC(150,-0.5,199.5)", ptPlotCut );

    TH1F *hPtMC = (TH1F*) gROOT->FindObject("hPtMC");
    TH1F *hPtData = (TH1F*) gROOT->FindObject("hPtData");
    TH1F *hPtMCReweight = (TH1F*) gROOT->FindObject("hPtMCReweight");

    hPtMC->Scale(1.0/hPtMC->Integral());
    hPtData->Scale(1.0/hPtData->Integral());
    hPtMCReweight->Scale(1.0/hPtMCReweight->Integral());

    TCanvas *cPt = new TCanvas("cPt","cPt");

    hPtData->SetLineColor(kOrange+7);
    hPtData->SetLineStyle(7);
    hPtMC->SetLineColor(kAzure+7);
    hPtMC->SetLineStyle(9);
    hPtMCReweight->SetLineColor(kGreen+1);

    hPtMCReweight->GetXaxis()->SetTitle("tight muon p_{T}");

    hPtMCReweight->Draw("hist");
    hPtData->Draw("same");
    hPtMC->Draw("same");

    TLegend * legPt = new TLegend(0.6,0.5,0.9,0.7);
    legPt->AddEntry(hPtData,"data distribution","lep");
    legPt->AddEntry(hPtMC,"MC distribution before reweighting","lep");
    legPt->AddEntry(hPtMCReweight,"MC distribution after reweighting","lep");
    legPt->Draw();

    cPt->Print("pt.png");

    std::cout << "[addWeights]: Wrote output to " << fOut->GetName() << std::endl;
    fOut->Close();
}

