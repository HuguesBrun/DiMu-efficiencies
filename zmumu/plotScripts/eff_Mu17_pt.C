
void  eff_Mu17_pt(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);
  // TFile *fdataeff= new TFile("output_data_iso025.root");
 TFile *fdataeff= new TFile("output_data_Mu17_pt.root");


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
/*
   c_1 -> cd();
   c->cd(1); 
*/     
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
    printf("yg[%d] = %g\n", i,yg[i]);
    printf("erryg[%d] = %g\n", i,erryg[i]);

    hr1DTot -> SetBinContent(i+1, yg[i])  ;
    hr1DTot -> SetBinError(i+1, erryg[i])  ;

  }

////////////////////////


 c_1 -> cd();
 c->cd(1); 
 c_1 ->SetLogy();
 c_1 ->SetLogx();
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
// f -> cd();

//TH1F  *hr2DRefRormula = (TH1F*)hr1DTot  -> Clone(); 
//double etabin[5] = {0, 0.9, 1.2, 2.1, 2.4};
double ptbin[7]= {12, 17, 20, 24, 30, 60, 100};
TH2F *hr2DRefRormula  = new TH2F("heta1eta2","", 6, ptbin, 6, ptbin);

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
   hr2DRefRormula-> GetXaxis() -> SetTitle("#mu p_{T}");

   hr2DRefRormula-> GetYaxis() -> SetTitleColor(1);
   hr2DRefRormula-> GetYaxis() -> SetTitleOffset(1.);
   hr2DRefRormula-> GetYaxis() -> SetTitleSize(0.06);
   hr2DRefRormula-> GetYaxis() -> SetTitle("#mu p_{T}");


gStyle->SetPaintTextFormat("3.3f "); //3.4f
 
hr2DRefRormula->SetMarkerSize(1.8);
hr2DRefRormula->Draw("TEXT E1 Same");


TFile g("reftrigger_data_mu17_pt.root", "RECREATE"); //create file
   hr2DRefRormula -> SetName("hrEffData");
   hr2DRefRormula -> Write();



// TH1F  *hr2DFor = (TH1F*)hr2DRefRormula  -> Clone(); 
TH1F  *hrEffA = (TH1F*)hr2DRefRormula -> Clone();

   t->SetTextColor(1);
   t->SetTextSize(0.04);
 //  t->DrawLatex(0.33,0.95, "1 - (1 -#epsilon_{#mu 17 on #mu_1})*(1 -#epsilon_{#mu 17 on #mu_2}) " );
   t->DrawLatex(0.33,0.95, "1 - (1 -#epsilon_{i})*(1 -#epsilon_{k}) ; (data)" );

/////////////////////////////////////////////////////////


   c-> Print("eff_Mu17_pt_data.pdf"); 


   c->cd();
   c->Update();

}
