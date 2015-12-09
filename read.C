void read(char *file)
{
  TFile *f = new TFile(file);
  if (!f)
  {
    cout << "Errore apertura file\n";
    return;
  }
  TCanvas *c1 = new TCanvas();
  TCanvas *c2 = new TCanvas();
  
  TTree *t = (TTree*)f->Get("Ntuple1");
  if(!t)
  {
     cout << "Errore apertura tree\n";
     return;
  }
  int n = t->GetEntries();
  double x,y,z,e;
  t->SetBranchAddress("x",&x);
  t->SetBranchAddress("y",&y);
  t->SetBranchAddress("z",&z);
  t->SetBranchAddress("Ekin",&e);
  TH2D *h2 = new TH2D("h2","posizioni",20,-5000,5000,20,-5000,5000);
  TH1D *h =  new TH1D("h","energie eV",1000,0,1);

  for(int i=0;i<n;i++)
  {
    t->GetEntry(i);
    h2->Fill(x,y);
    h->Fill(e*1.0e+6);
  }
  c1->cd();
  h2->Draw("COLZ");
  c2->cd();
  h->Draw();

}
