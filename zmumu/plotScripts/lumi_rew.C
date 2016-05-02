
void  lumi_rew(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);

 
// TFile *fsingleMu = new TFile("/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/TagAndProbe/76XtreeProduction/v41/TnPTree_v41_76X_RunD_part1.root");


  TCanvas *c = new TCanvas("c","The Ntuple canvas",200,10,700,780);
  c->SetFillColor(10); 
  c->Divide(2,2); 


   
   gStyle->SetStatW(0.30);
   gStyle->SetStatH(0.20);
   gStyle->SetStatColor(42);
   gStyle->SetOptStat(""); //em
   gStyle->SetLabelSize(0.048,"xy");
   gStyle->SetLabelOffset(0.013,"x");
   gStyle->SetLabelOffset(0.013,"y");
   gStyle->SetPadBorderMode(0);
   gStyle->SetFillColor(0);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);

  TLatex *t = new TLatex();
   t->SetNDC();
   t->SetTextFont(62);
   t->SetTextColor(36);
   t->SetTextSize(0.08);
   t->SetTextAlign(12);

///////////////////////////////////////////

   c_1 -> cd();
   c->cd(1); 
   c_1 ->SetLogx(0);

     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.12);
   
//----------------------
  //  fsingleMu -> cd("tpTree");
  // fsingleMu -> ls();
   
  float Bins1[23]={0.1,0.8,1.6,2.4,3.2,4,4.8,5.6,6.4,7.2,8.,9.,10.,11.,12.,13.,14.,15.,20.,25.,30.,35.,40.};
   TH1F* HistRB = new TH1F("HistRB", "",22, Bins1);
   HistRB -> Sumw2();

//   fitter_tree ->Project("HistRB","lumi","1");

//    double dpti1, content1, error1;
    
//      for (int ibin=1; ibin < 24  ; ibin++){         
//       dpti1 = Bins1[ibin]-Bins1[ibin-1] ;
//       content1 = (HistRB -> GetBinContent(ibin))/dpti1;
//       HistRB -> SetBinContent(ibin,content1);
//       error1 = (HistRB -> GetBinError(ibin))/dpti1;
//       HistRB -> SetBinError(ibin,error1);  
//  }
 

//TH1F* HistNorm = new TH1F("HistNorm", "",28, BinsNorm);
//h10 ->Project("HistNorm","pT_B","WT00");

//cout << HistNorm->Integral() << "\n";
 //double SumWeithedEv = HistNorm->Integral();
 //  scale = 19.584*1151.6*1000./SumWeithedEv;  // 3048
  //  cout << "scale = " << scale << "\n";
  // UU: TOTAL CROSS SECTION =    554.1065      PB +/-   0.1166597
  // DD: TOTAL CROSS SECTION =    597.4988      PB +/-   0.1094628
 //  if(norm1)  scale = 1./(HistRB->Integral());
  // HistRB ->Scale(scale); 

 //  HistRB -> SetLineColor(4);  
  // HistRB -> SetMarkerColor(4); 
  // HistRB -> SetMarkerStyle(21); 
  // HistRB -> SetMarkerSize(0.7);
   HistRB -> Draw("E1 same");

// -------------------------------------------------------------
   c-> Print("lumi_rew.pdf"); 

   c->cd();
   c->Update();

}
