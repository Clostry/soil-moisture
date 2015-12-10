void read(char *file)
{
  TFile *f = new TFile(file);
  if (!f)
  {
    cout << "Errore apertura file\n";
    return;
  }
  TCanvas *c1 = new TCanvas("c1","Neutroni primari");
  TCanvas *c2 = new TCanvas("c2","Neutroni scatterati");
  
  double x,y,z,e;
  int n;

  TTree *t1 = (TTree*)f->Get("Ntuple1");
  n = t1->GetEntries();
  t1->SetBranchAddress("x",&x);
  t1->SetBranchAddress("y",&y);
  t1->SetBranchAddress("Ekin",&e);
  TH2D *h_pos1 = new TH2D("h_pos1","posizioni",20,-5000,5000,20,-5000,5000);
  TH1D *h_ene1 =  new TH1D("h_ene1","energie eV",1000,0,1);
  for(int i=0;i<n;i++)
  {
    t1->GetEntry(i);
    h_pos1->Fill(x,y);
    h_ene1->Fill(e*1.0e+6);
  }

  TTree *t2 = (TTree*)f->Get("Ntuple2");
  n = t2->GetEntries();
  t2->SetBranchAddress("x",&x);
  t2->SetBranchAddress("y",&y);
  t2->SetBranchAddress("z",&z);
  t2->SetBranchAddress("Ekin",&e);
  TH2D *h_pos2 = new TH2D("h_pos2","posizioni",20,-5000,5000,20,-5000,5000);
  TH1D *h_ene2 =  new TH1D("h_ene2","energie eV",1000,0,1);

  for(int i=0;i<n;i++)
  {
    t2->GetEntry(i);
    h_pos2->Fill(x,y);
    h_ene2->Fill(e*1.0e+6);
  }

  c1->Divide(1,2);
  c1->cd(1);
  h_pos1->Draw("COLZ");
  c1->cd(2);
  h_ene1->Draw();

  c2->Divide(1,2);
  c2->cd(1);
  h_pos2->Draw("COLZ");
  c2->cd(2);
  h_ene2->Draw();

}
