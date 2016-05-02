//#include "gr2hi.C"



void  eff_dz_bef(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);

 
// TFile *fH= new TFile("testRefTriggerFile.root");

// TFile *f= new TFile("Efficiency1.root");
   TFile *fdatadz= new TFile("../originalHisto/TnP_MuonID_data_all_Dz_pt_eta.root");
   TFile *fMCdz= new TFile("../TnP_MuonID_signal_mc_Dz_pt_eta.root");


//////////////// ----------ISR/FSR----------//////////////////

 Double_t norm=1. ;
 Double_t  scale ;

 TCanvas *c = new TCanvas("c","The Ntuple canvas",200,10,700,780);
  c->SetFillColor(10); 



    c->Divide(2,3); 
   
   
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

//----------------------------------------

///////////////////////////////////////////

// TCanvas *c2 = new TCanvas("c2","The Ntuple canvas",200,10,700,780);
//  c->SetFillColor(10); 
//  c->Divide(2,1);


   c_1 -> cd();
   c->cd(1); 
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
fdatadz->cd("tpTree/Dz_pt_eta/fit_eff_plots");
//fdatadz->cd();
//fdatadz -> ls();

//TH1F  *2deff = (TH1F*)tag_abseta_abseta_PLOT_pt_bin0_&_tag_pt_bin0_&_DenomMu17Eff_pass_&_Tight2012_pass  -> Clone(); 
//TH1F  *2deff = (TH1F*)Dz_pt_eta_abseta_PLOT_tag_abseta_bin0_&_DenomMu17Eff_pass_&_Tight2012_pass -> Clone
//TH1F  *histo1D = (TH1F*) fdatadz->Get("abseta_PLOT_tag_abseta_bin0_&_DenomMu17Eff_pass_&_Tight2012_pass");

//histo1D -> Sumw2();

//gStyle->SetPalette(1);
//histo1D->Draw("E1");


fMCdz->cd();
fMCdz->ls();
//  tag_abseta_bin0
TGraphAsymmErrors  *histo1D = (TGraphAsymmErrors*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin0_&_DenomMu17Eff_pass_&_Tight2012_pass");
  Double_t *yg = histo1D->GetY();
  Double_t *erryg = histo1D->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("yg[%d] = %g\n", i,yg[i]);
    printf("erryg[%d] = %g\n", i,erryg[i]);
  }
cout << "--------------" << "\n";
//  tag_abseta_bin1
TGraphAsymmErrors  *histo1Db1 = (TGraphAsymmErrors*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin1_&_DenomMu17Eff_pass_&_Tight2012_pass");
  Double_t *ygb1 = histo1Db1->GetY();
  Double_t *errygb1 = histo1Db1->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("ygb1[%d] = %g\n", i,ygb1[i]);
    printf("errygb1[%d] = %g\n", i,errygb1[i]);
  }
cout << "--------------" << "\n";
//  tag_abseta_bin2
TGraphAsymmErrors  *histo1Db2 = (TGraphAsymmErrors*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin2_&_DenomMu17Eff_pass_&_Tight2012_pass");
  Double_t *ygb2 = histo1Db2->GetY();
  Double_t *errygb2 = histo1Db2->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("ygb2[%d] = %g\n", i,ygb2[i]);
    printf("errygb2[%d] = %g\n", i,errygb2[i]);
  }
cout << "--------------" << "\n";
//  tag_abseta_bin3
TGraphAsymmErrors  *histo1Db3 = (TGraphAsymmErrors*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin3_&_DenomMu17Eff_pass_&_Tight2012_pass");
  Double_t *ygb3 = histo1Db3->GetY();
  Double_t *errygb3 = histo1Db3->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("ygb3[%d] = %g\n", i,ygb3[i]);
    printf("errygb3[%d] = %g\n", i,errygb3[i]);
  }


double etabin[5] = {0, 0.9, 1.2, 2.1, 2.4};
TH2F *heta1eta2  = new TH2F("heta1eta2","eta1 vs eta2", 4, etabin, 4, etabin);

  for (int i(1); i <= 4 ; i++) {  // y
        for (int j(1); j <= 4; j++) {  // x
        if(i==1){ heta1eta2 -> SetBinContent(j,i,yg[j-1]);
                  heta1eta2 -> SetBinError(j,i,erryg[j-1]); }
        if(i==2){ heta1eta2 -> SetBinContent(j,i,ygb1[j-1]);
                  heta1eta2 -> SetBinError(j,i,errygb1[j-1]); }
        if(i==3){ heta1eta2 -> SetBinContent(j,i,ygb2[j-1]);
                  heta1eta2 -> SetBinError(j,i,errygb2[j-1]); }
        if(i==4){ heta1eta2 -> SetBinContent(j,i,ygb3[j-1]);
                  heta1eta2 -> SetBinError(j,i,errygb3[j-1]); }

      //  else heta1eta2 -> SetBinContent(j,i,1.);
}
}

heta1eta2 -> Draw("COLZ");
gStyle->SetPaintTextFormat("3.4f ");

heta1eta2->SetMarkerSize(1.8);
heta1eta2->Draw("TEXT E1 Same");

 //  2deff -> GetXaxis()->SetNdivisions(505);
 //  2deff -> GetYaxis()->SetNdivisions(505);
 //  2deff-> GetXaxis() -> SetTitleColor(1);
 //  2deff-> GetXaxis() -> SetTitleOffset(1.);
 //  2deff-> GetXaxis() -> SetTitleSize(0.06);
  // 2deff-> GetXaxis() -> SetTitle("#mu #eta");

 //  2deff-> GetYaxis() -> SetTitleColor(1);
  // 2deff-> GetYaxis() -> SetTitleOffset(1.);
  // 2deff-> GetYaxis() -> SetTitleSize(0.06);
  // 2deff-> GetYaxis() -> SetTitle("#mu #eta");


//gStyle->SetPaintTextFormat("3.4f ");

//2deff->SetMarkerSize(1.8);
//2deff->Draw("E1");

//////////////////////////////////////////////////////////

   c_2 -> cd();
   c->cd(2); 
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
fdatadz->cd("tpTree/Dz_pt_eta/fit_eff_plots");

fMCdz->cd();
//fMCdz->ls();
TH1F  *histo1Da = (TH1F*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin0_&_DenomMu17Eff_pass_&_Tight2012_pass");
//histo1D->SetMarkerSize(1.8);
histo1Da ->Draw("ap");

//////////////////////////////////////////////////////////

   c_3 -> cd();
   c->cd(3); 
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
fdatadz->cd("tpTree/Dz_pt_eta/fit_eff_plots");

fMCdz->cd();
//fMCdz->ls();
TH1F  *histo1Da = (TH1F*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin1_&_DenomMu17Eff_pass_&_Tight2012_pass");
//histo1D->SetMarkerSize(1.8);
histo1Da ->Draw("ap");

//////////////////////////////////////////////////////////

   c_4 -> cd();
   c->cd(4); 
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
fdatadz->cd("tpTree/Dz_pt_eta/fit_eff_plots");

fMCdz->cd();
//fMCdz->ls();
TH1F  *histo1Da = (TH1F*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin2_&_DenomMu17Eff_pass_&_Tight2012_pass");
//histo1D->SetMarkerSize(1.8);
histo1Da ->Draw("ap");


//////////////////////////////////////////////////////////

   c_5 -> cd();
   c->cd(5); 
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
fdatadz->cd("tpTree/Dz_pt_eta/fit_eff_plots");

fMCdz->cd();
TH1F  *histo1Da = (TH1F*) fMCdz->Get("Dz_pt_eta_abseta_PLOT_tag_abseta_bin3_&_DenomMu17Eff_pass_&_Tight2012_pass");
//histo1D->SetMarkerSize(1.8);
histo1Da ->Draw("ap");

/////////////////////////////////////////////////////////////
 

   c-> Print("eff_dz.pdf"); 


   c->cd();
   c->Update();

}
