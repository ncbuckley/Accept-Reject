#include "file2.h"
#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
#include <TLeaf.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TBrowser.h>
using namespace std;

int main(){

  clock_t start = clock();
  double x = 0;
  double y = 0;
  double N = 10e5;
  int bins = 50;
  int accepted = 0;
  int rejected = 0;
  
  //Create a new TFile with TTree ar containing double values acc
  TFile *a = new TFile("accept_reject.root","recreate");
  TTree *ar = new TTree("ar", "Tree with generated values");
  Double_t acc;

  ar ->Branch("acc",&acc);

  //Create a 1d histogram 
  TFile* oFile = TFile::Open("Hist_ar.root","recreate");
  TH1D* Hist_acc = new TH1D("acc","Accepted Numbers", bins, 0, 8);

  //Generate random values x and y N times, if y value is below or on e^(-x/2) fill to acc
  for(Int_t i = 1; i <= N; i++){
    x = RandomReal(0,8);
    y = RandomReal(0,1);

    if( y <=  exp(x*-0.5) ){
      acc = x;
      ar-> Fill();
      
      accepted++;
      continue;
    }
    
    else;
      rejected++;
      continue;
  }

  //Take accepted x values from TTree ar and fill histogram
  for(Int_t j=0; j<N; j++){
    ar->GetEntry(j);
    Double_t entry = ar->GetLeaf("acc")->GetValue(0);
    Hist_acc->Fill(entry);
  }

  oFile->Write();
  oFile->Close();

  //Stop clock and calculate time to run
  clock_t end = clock();
  double run_time = ((end - start) / double(CLOCKS_PER_SEC));

  std::cout << std::fixed;
  std::cout << std::setprecision(5);
  std::cout <<"Time: "<< run_time <<" " << accepted <<" "<< rejected <<  endl;
  
  return 0;

  /* From the fit parameters: exp(c + mx)
     c =  1.00082e+01
     m = -0.52529e+00

     Time to run: 12.29397 s
  */
  
}
