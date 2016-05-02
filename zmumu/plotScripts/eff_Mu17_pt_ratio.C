
void  eff_Mu17_pt_ratio(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);
  // TFile *fdataeff= new TFile("output_data_iso025.root");
 TFile *fdataeff= new TFile("output_data_dimu_pt.root");
 TFile *fmceff= new TFile("output_mc_dimu_pt.root");


 TCanvas *c = new TCanvas("c","The Ntuple canvas",200,10,700,780);
  c->SetFillColor(10); 

    c->Divide(1,1); 
   
   
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
   c_1 ->SetLogx();
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   

fdataeff -> cd();

TGraphAsymmErrors *histo1Da = (TGraphAsymmErrors*) fdataeff->Get("Mu17_IsoTrkVVL_pt_eta_pt_PLOT_Tight2012_pass_&_tag_Mu17_IsoTrkVVL_pass_&_tag_Tight2012_pass");

   histo1Da->SetMinimum(0.);
   histo1Da->SetMaximum(1.);
// histo1Da ->Draw("ap");

  Double_t *yg = histo1Da->GetY();
  Double_t *erryg = histo1Da->GetEYhigh() ;


//float Bins[5]={0, 0.9, 1.2, 2.1, 2.4};
float Bins[7]= {12, 17, 20, 24, 30, 60, 100};
TH1D *hr1DTot    = new TH1D("hr1DTot",  "", 6, Bins);

  for (int i = 0; i<6; i++) {
   // printf("yg[%d] = %g\n", i,yg[i]);
   // printf("erryg[%d] = %g\n", i,erryg[i]);

    hr1DTot -> SetBinContent(i+1, yg[i])  ;
    hr1DTot -> SetBinError(i+1, erryg[i])  ;

  }

// hr1DTot -> Draw("E1");

fmceff -> cd();

TGraphAsymmErrors *histo1Da = (TGraphAsymmErrors*) fmceff->Get("Mu17_IsoTrkVVL_pt_eta_pt_PLOT_Tight2012_pass_&_tag_Mu17_IsoTrkVVL_pass_&_tag_Tight2012_pass");

   histo1Da->SetMinimum(0.);
   histo1Da->SetMaximum(1.);
// histo1Da ->Draw("ap same");

  Double_t *yg = histo1Da->GetY();
  Double_t *erryg = histo1Da->GetEYhigh() ;


//float Bins[5]={0, 0.9, 1.2, 2.1, 2.4};
float Bins[7]= {12, 17, 20, 24, 30, 60, 100};
TH1D *hr1DTot1    = new TH1D("hr1DTot1",  "", 6, Bins);

  for (int i = 0; i<6; i++) {
   // printf("yg[%d] = %g\n", i,yg[i]);
  //  printf("erryg[%d] = %g\n", i,erryg[i]);

    hr1DTot1 -> SetBinContent(i+1, yg[i])  ;
    hr1DTot1 -> SetBinError(i+1, erryg[i])  ;

  }

// hr1DTot1 -> Draw("E1 same");
hr1DTot -> Divide(hr1DTot1);
hr1DTot -> SetMarkerStyle(20);
hr1DTot -> SetMarkerSize(0.9);

hr1DTot  -> GetYaxis()->SetRangeUser(0.9, 1.6);
hr1DTot -> Draw("E1");

 for (int i = 0; i<7; i++) {

cout << hr1DTot -> GetBinContent(i) << " ,  " <<  hr1DTot -> GetBinError(i) << "\n";
  }
/////////////////////////////////////////////////////////////
 

   c-> Print("eff_Mu17_pt_ratio.pdf"); 


   c->cd();
   c->Update();

}
