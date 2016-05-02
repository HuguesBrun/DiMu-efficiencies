
void  eff_Mu17Mu8(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);

 

 // TFile *fdataeff= new TFile("output_mc_iso025.root");
   TFile *fdataeff= new TFile("output_data1nodz.root");


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
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   

fdataeff -> cd();

TGraphAsymmErrors *histo1Da = (TGraphAsymmErrors*) fdataeff->Get("Mu17_IsoTrkVVL_pt_eta_abseta_PLOT_Tight2012_pass_&_tag_Mu17_IsoTrkVVL_pass_&_tag_Tight2012_pass");
histo1Da ->Draw("ap");

  Double_t *yg = histo1Da->GetY();
  Double_t *erryg = histo1Da->GetEYhigh() ;


float Bins[5]={0, 0.9, 1.2, 2.1, 2.4};
TH1D *hr1DTot    = new TH1D("hr1DTot",  "", 4, Bins);

  for (int i = 0; i<4; i++) {
    printf("yg[%d] = %g\n", i,yg[i]);
    printf("erryg[%d] = %g\n", i,erryg[i]);

    hr1DTot -> SetBinContent(i+1, yg[i])  ;
    hr1DTot -> SetBinError(i+1, erryg[i])  ;

  }

////////////////////////


 c_2 -> cd();
 c->cd(2); 
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
// f -> cd();

//TH1F  *hr2DRefRormula = (TH1F*)hr1DTot  -> Clone(); 
double etabin[5] = {0, 0.9, 1.2, 2.1, 2.4};
TH2F *hr2DRefRormula  = new TH2F("heta1eta2","", 4, etabin, 4, etabin);

     hr2DRefRormula -> Sumw2();

    int nBinsX = hr2DRefRormula->GetNbinsX();
    int nBinsY = hr2DRefRormula->GetNbinsY();
    double content, error, sigmaA, sigmaB, contA, contB, errorA, errorB;

  for (int i(1); i <= nBinsY ; i++) {
        for (int j(1); j <= nBinsX; j++) {

      content = 1. - (1. - (hr1DTot -> GetBinContent(i)))*(1. - (hr1DTot -> GetBinContent(j)));
     // sigmaA = hr1DTot -> GetBinError(j)/hr1DTot -> GetBinContent(j);
     // sigmaB = hr1DTot -> GetBinError(i)/hr1DTot -> GetBinContent(i);
     // error = content* sqrt( sigmaA*sigmaA + sigmaB*sigmaB );
       contA = 1. - hr1DTot -> GetBinContent(i);
       errorA = hr1DTot -> GetBinError(i) ;
       contB = 1. - hr1DTot -> GetBinContent(j);
       errorB = hr1DTot -> GetBinError(j) ;
     cout << "errorB : " << errorB << "\n"; 

       error= sqrt( contA*contA*errorB*errorB + contB*contB*errorA*errorA );
    //  error = contA*errorB + contB*errorA;
      if (i==j) error = 2.*(contA)*errorA;

    // cout<< "i,j = " << i << ","<< j << " , "<< hr1DLead -> GetBinContent(j) << " , " << hr1DTrail -> GetBinContent(i)  << " , content: " << content<< "\n";
      cout << "x(1),y(2) = " << j << ","<< i << " , " << content << " , " << error << "\n";
      hr2DRefRormula -> SetBinContent(j,i, content);
      hr2DRefRormula -> SetBinError(j,i, error);

        }
    } 

gStyle->SetPalette(1);
hr2DRefRormula->Draw("COLZ");

   hr2DRefRormula -> GetXaxis()->SetNdivisions(505);
   hr2DRefRormula -> GetYaxis()->SetNdivisions(505);
   hr2DRefRormula-> GetXaxis() -> SetTitleColor(1);
   hr2DRefRormula-> GetXaxis() -> SetTitleOffset(1.);
   hr2DRefRormula-> GetXaxis() -> SetTitleSize(0.06);
   hr2DRefRormula-> GetXaxis() -> SetTitle("#mu #eta");

   hr2DRefRormula-> GetYaxis() -> SetTitleColor(1);
   hr2DRefRormula-> GetYaxis() -> SetTitleOffset(1.);
   hr2DRefRormula-> GetYaxis() -> SetTitleSize(0.06);
   hr2DRefRormula-> GetYaxis() -> SetTitle("#mu #eta");


gStyle->SetPaintTextFormat("3.4f ");

hr2DRefRormula->SetMarkerSize(1.8);
hr2DRefRormula->Draw("TEXT E1 Same");

// TH1F  *hr2DFor = (TH1F*)hr2DRefRormula  -> Clone(); 
TH1F  *hrEffA = (TH1F*)hr2DRefRormula -> Clone();

   t->SetTextColor(1);
   t->SetTextSize(0.04);
 //  t->DrawLatex(0.33,0.95, "1 - (1 -#epsilon_{#mu 17 on #mu_1})*(1 -#epsilon_{#mu 17 on #mu_2}) " );
   t->DrawLatex(0.33,0.95, "1 - (1 -#epsilon_{i})*(1 -#epsilon_{k}) ;  (data) " );

/////////////////////////////////////////////////////////
   c_3 -> cd();
   c->cd(3); 
    
   gPad->SetTopMargin(0.08);
   gPad->SetLeftMargin(0.163);
   gPad->SetBottomMargin(0.16);
   gPad->SetRightMargin(0.143);


fdataeff->cd();
fdataeff->ls();
//  tag_abseta_bin0
TGraphAsymmErrors  *histo1D = (TGraphAsymmErrors*) fdataeff->Get("EffMu17Mu8nodz_pt_eta_abseta_PLOT_tag_abseta_bin0_&_Mu17Eff_pass_&_Tight2012_pass_&_tag_Tight2012_pass");
  Double_t *yg = histo1D->GetY();
  Double_t *erryg = histo1D->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("yg[%d] = %g\n", i,yg[i]);
    printf("erryg[%d] = %g\n", i,erryg[i]);
  }
cout << "--------------" << "\n";
//  tag_abseta_bin1
TGraphAsymmErrors  *histo1Db1 = (TGraphAsymmErrors*) fdataeff->Get("EffMu17Mu8nodz_pt_eta_abseta_PLOT_tag_abseta_bin1_&_Mu17Eff_pass_&_Tight2012_pass_&_tag_Tight2012_pass");
  Double_t *ygb1 = histo1Db1->GetY();
  Double_t *errygb1 = histo1Db1->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("ygb1[%d] = %g\n", i,ygb1[i]);
    printf("errygb1[%d] = %g\n", i,errygb1[i]);
  }
cout << "--------------" << "\n";
//  tag_abseta_bin2
TGraphAsymmErrors  *histo1Db2 = (TGraphAsymmErrors*) fdataeff->Get("EffMu17Mu8nodz_pt_eta_abseta_PLOT_tag_abseta_bin2_&_Mu17Eff_pass_&_Tight2012_pass_&_tag_Tight2012_pass");
  Double_t *ygb2 = histo1Db2->GetY();
  Double_t *errygb2 = histo1Db2->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("ygb2[%d] = %g\n", i,ygb2[i]);
    printf("errygb2[%d] = %g\n", i,errygb2[i]);
  }
cout << "--------------" << "\n";
//  tag_abseta_bin3
TGraphAsymmErrors  *histo1Db3 = (TGraphAsymmErrors*) fdataeff->Get("EffMu17Mu8nodz_pt_eta_abseta_PLOT_tag_abseta_bin3_&_Mu17Eff_pass_&_Tight2012_pass_&_tag_Tight2012_pass");
  Double_t *ygb3 = histo1Db3->GetY();
  Double_t *errygb3 = histo1Db3->GetEYhigh() ;
  for (int i = 0; i<4; i++) {
    printf("ygb3[%d] = %g\n", i,ygb3[i]);
    printf("errygb3[%d] = %g\n", i,errygb3[i]);
  }


double etabin[5] = {0, 0.9, 1.2, 2.1, 2.4};
TH2F *heta1eta2  = new TH2F("heta1eta2","", 4, etabin, 4, etabin);

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

}
}

heta1eta2 -> Draw("COLZ");
gStyle->SetPaintTextFormat("3.4f ");

heta1eta2->SetMarkerSize(1.8);
heta1eta2->Draw("TEXT E1 Same");

TH1F  *hrEffB = (TH1F*)heta1eta2 -> Clone(); 
   t->SetTextColor(1);
   t->SetTextSize(0.04);
   t->DrawLatex(0.02,0.95, "(HLT_Mu17_Mu8 && HLT_Mu17) /  HLT_Mu17" );


 // t->DrawLatex(0.02,1.2, "Mu17_Mu8;   MC" );
//////////////////////////////////////////////////

   c_4 -> cd();
   c->cd(4); 
    
   gPad->SetTopMargin(0.08);
   gPad->SetLeftMargin(0.163);
   gPad->SetBottomMargin(0.16);
   gPad->SetRightMargin(0.143);

   hrEffA -> Multiply(hrEffB);

   gStyle->SetPalette(1);
   hrEffA->Draw("COLZ");

   hrEffA -> GetXaxis()->SetNdivisions(505);
   hrEffA -> GetYaxis()->SetNdivisions(505);
   hrEffA-> GetXaxis() -> SetTitleColor(1);
   hrEffA-> GetXaxis() -> SetTitleOffset(1.);
   hrEffA-> GetXaxis() -> SetTitleSize(0.06);
   hrEffA-> GetXaxis() -> SetTitle("#mu_{1} #eta");

   hrEffA-> GetYaxis() -> SetTitleColor(1);
   hrEffA-> GetYaxis() -> SetTitleOffset(1.);
   hrEffA-> GetYaxis() -> SetTitleSize(0.06);
   hrEffA-> GetYaxis() -> SetTitle("#mu_{2} #eta");

gStyle->SetPaintTextFormat("3.4f ");

hrEffA->SetMarkerSize(1.8);
hrEffA->Draw("TEXT E1 Same");

TH1F  *hrEffFinFormula = (TH1F*)hrEffA -> Clone();


//TFile* file = new TFile("hrEffFinFormula_2030rew.root", "RECREATE");
//hrEffFinFormula -> SetName("hrEffFinFormula");
hrEffFinFormula -> Write();

   t->SetTextColor(1);
   t->SetTextSize(0.04);
   t->DrawLatex(0.1,0.95, "Eff_ref * Eff_soup|ref" );

/////////////////////////////////////////////////////////////
 

   c-> Print("eff_Mu17Mu8_data_new_nodz.pdf"); 


   c->cd();
   c->Update();

}
