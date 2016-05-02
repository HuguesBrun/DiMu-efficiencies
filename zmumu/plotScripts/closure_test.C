
void  closure_test(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);
 // TFile *fdataeff= new TFile("output_data_iso025.root");
 // TFile *fdataeff= new TFile("output_data_dimu_pt.root");
 TFile *fmcTrue= new TFile("tnpZ_theTreeCleaned_MC_eff_new_test.root");
 TFile *fmc= new TFile("effMCpathor_new.root");



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
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
//TH1F  *hr2DMCTrue = (TH1F*)hr2DMCTrue  -> Clone(); 

fmcTrue -> cd("tpTree");
//fmceff -> ls();

TH1F  *hr2DMCTrue = (TH1F*)hr2DMCTrue  -> Clone(); 
TH1F  *hr2DMCTrue1 = (TH1F*)hr2DMCTrue1  -> Clone(); 
hr2DMCTrue -> Sumw2();
//hr2DMCTrue1 -> Sumw2();

    int nBinsX = hr2DMCTrue->GetNbinsX();
    int nBinsY = hr2DMCTrue1->GetNbinsY();
/*
    for (int i(1); i <= nBinsY ; i++) {
        for (int j(1); j <= nBinsX; j++) {
           
           hr2DMCTrue1 -> SetBinError(i,j,  1./(sqrt(hr2DMCTrue1 -> GetBinContent(i,j))) ) ;
           hr2DMCTrue -> SetBinError(i,j,  1./(sqrt(hr2DMCTrue -> GetBinContent(i,j))) ) ;
         

       }
    }
*/

 cout << hr2DMCTrue1 -> GetBinContent(1,1) << "  ,  " << hr2DMCTrue1 -> GetBinError(1,1) << "\n";
 cout << hr2DMCTrue -> GetBinContent(1,1) << "  ,  " << hr2DMCTrue -> GetBinError(1,1) << "\n";


TH1 *hrRatio = (TH1F*)hr2DMCTrue1 -> Clone(); 
hrRatio -> Divide(hr2DMCTrue1, hr2DMCTrue,1.,1.,"B");
// hr2DMCTrue1-> Divide(hr2DMCTrue);

// cout << hr2DMCTrue1 -> GetBinContent(1,1) << "  ,  " << hr2DMCTrue1 -> GetBinError(1,1) << "\n";
gStyle->SetPalette(1);
hrRatio->Draw("COLZ");

   hrRatio -> GetXaxis()->SetNdivisions(505);
   hrRatio -> GetYaxis()->SetNdivisions(505);
   hrRatio-> GetXaxis() -> SetTitleColor(1);
   hrRatio-> GetXaxis() -> SetTitleOffset(1.);
   hrRatio-> GetXaxis() -> SetTitleSize(0.06);
   hrRatio-> GetXaxis() -> SetTitle("#mu #eta");

   hrRatio-> GetYaxis() -> SetTitleColor(1);
   hrRatio-> GetYaxis() -> SetTitleOffset(1.);
   hrRatio-> GetYaxis() -> SetTitleSize(0.06);
   hrRatio-> GetYaxis() -> SetTitle("#mu #eta");



gStyle->SetPaintTextFormat("3.4f ");

hrRatio->SetMarkerSize(1.8);
hrRatio->Draw("TEXT E1 Same");

TH1F  *hr2DMCTrueMinus = (TH1F*)hrRatio -> Clone(); 


    int nBinsX = hr2DMCTrueMinus->GetNbinsX();
    int nBinsY = hr2DMCTrueMinus->GetNbinsY();
    // double content, error, sigmaA, sigmaB, contA, contB, errorA, errorB;

    for (int i(1); i <= nBinsY ; i++) {
        for (int j(1); j <= nBinsX; j++) {

        //   cout <<"i,j = " << i << ","<< j << " , "<<  1.-hrRatio->GetBinError(j, i) << "\n";
        //   hrRatio -> SetBinError(j,i,1.-hrRatio->GetBinError(j, i));
        //   cout <<"i,j = " << i << ","<< j << " , "<<  hrRatio->GetBinContent(j, i) << "\n";

         hr2DMCTrueMinus -> SetBinContent(j,i,-hrRatio->GetBinContent(j, i));
         hr2DMCTrueMinus -> SetBinError(j,i,hrRatio->GetBinError(j, i));
       // cout << hr2DMCTrue-> GetBinContent(1,1) << "\n";
        }
    }

   t->SetTextColor(1);
   t->SetTextSize(0.04);
   t->DrawLatex(0.1,0.95, "True" );


///////////////////////////////////////////

   c_2 -> cd();
   c->cd(2); 
   c_2 ->SetLogx(0);
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   
//TH1F  *hr2DMCTrue = (TH1F*)hr2DMCTrue  -> Clone(); 

fmc -> cd();

gStyle->SetPalette(1);
hrEffMC -> Draw("COLZ");
   hrEffMC -> GetXaxis()->SetNdivisions(505);
   hrEffMC -> GetYaxis()->SetNdivisions(505);
   hrEffMC-> GetXaxis() -> SetTitleColor(1);
   hrEffMC-> GetXaxis() -> SetTitleOffset(1.);
   hrEffMC-> GetXaxis() -> SetTitleSize(0.06);
   hrEffMC-> GetXaxis() -> SetTitle("#mu #eta");

   hrEffMC-> GetYaxis() -> SetTitleColor(1);
   hrEffMC-> GetYaxis() -> SetTitleOffset(1.);
   hrEffMC-> GetYaxis() -> SetTitleSize(0.06);
   hrEffMC-> GetYaxis() -> SetTitle("#mu #eta");


gStyle->SetPaintTextFormat("3.4f ");

hrEffMC->SetMarkerSize(1.8);
hrEffMC->Draw("TEXT E1 Same");

TH1F  *hrEffMCFormula = (TH1F*)hrEffMC -> Clone(); 

   t->SetTextColor(1);
   t->SetTextSize(0.04);
   t->DrawLatex(0.1,0.95, "MC with the method" );

///////////////////////////////////////////

   c_3 -> cd();
   c->cd(3); 
   c_3 ->SetLogx(0);
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);

//fmc -> cd();

hrEffMCFormula -> Add(hr2DMCTrueMinus);


gStyle->SetPalette(1);
hrEffMCFormula ->Draw("COLZ");  
gStyle->SetPaintTextFormat("3.4f ");

hrEffMCFormula ->SetMarkerSize(1.8);
hrEffMCFormula ->Draw("TEXT E1 Same");


   t->SetTextColor(1);
   t->SetTextSize(0.04);
   t->DrawLatex(0.05,0.95, "Diff=(Eff with method - True )" );

/////////////////////////////////////////////////////////////
 

   c-> Print("closure_test_difference_Berr.pdf"); 


   c->cd();
   c->Update();

}
