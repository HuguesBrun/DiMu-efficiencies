
void  eff_Mu17_pt_SF(){

 gROOT->SetStyle("Plain");
 gStyle -> SetErrorX(0);


//  TFile *fdataeff= new TFile("effDatapathor_new.root");
//   TFile *fMCeff= new TFile("effMCpathor_new.root");

//   TFile *fdataeff= new TFile("reftrigger_data_mu17_pt.root");
//   TFile *fMCeff= new TFile("reftrigger_mc_mu17_pt.root");

  TFile *fdataeff= new TFile("effDatapathOr_pt.root");
  TFile *fMCeff= new TFile("effMCpathOr_pt.root");


 TCanvas *c = new TCanvas("c","The Ntuple canvas",200,10,700,780);
  c->SetFillColor(10); 

    c->Divide(1,1); 
 //   c_1 ->SetLogy();
  //  c_1 ->SetLogx();
   
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
    c_1 ->SetLogy();
    c_1 ->SetLogx();
     
 gPad->SetTopMargin(0.08);
 gPad->SetLeftMargin(0.163);
 gPad->SetBottomMargin(0.16);
 gPad->SetRightMargin(0.143);
   

fdataeff -> cd();
TH1F  *hrEffData1 = (TH1F*)hrEffData -> Clone();

fMCeff -> cd();
TH1F  *hrEffMC1 = (TH1F*)hrEffMC -> Clone();

hrEffData1 -> Divide(hrEffMC1);

gStyle->SetPalette(1);
hrEffData1->Draw("COLZ");

gStyle->SetPaintTextFormat("3.3f ");

hrEffData1->SetMarkerSize(1.8);
hrEffData1->Draw("TEXT E1 Same");


//cout << hrEffData1 -> GetXaxis() ->  
    int nBinsX = hrEffData1 -> GetNbinsX();
    int nBinsY = hrEffData1 -> GetNbinsY();

  for (int i(1); i <= nBinsY ; i++) {
        for (int j(1); j <= nBinsX; j++) {

        cout << "i=" << i << " j=" << j << ",  "<< hrEffData1  -> GetBinLowEdge(i) << " -  " << hrEffData1  -> GetBinLowEdge(i+1) << ",  " <<  hrEffData1 -> GetBinContent(j,i) << "\n";
// << " ,  " << hrEffData1 -> GetBinContent(j,i)
        }
    } 


/////////////////////////////////////////////////////////////
 

  //  c-> Print("eff_Mu17_pt_SF.pdf"); 
  c-> Print("eff_pathor_pt_SF.pdf"); 


   c->cd();
   c->Update();

}
