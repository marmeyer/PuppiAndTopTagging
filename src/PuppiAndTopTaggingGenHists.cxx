#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingGenHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/AnalysisModule.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

PuppiAndTopTaggingGenHists::PuppiAndTopTaggingGenHists(Context & ctx, const string & dirname, const std::string & name_handletopjets): Hists(ctx, dirname){
   
   DeltaR_top_topjet = book<TH1F>( "DeltaR_top_topjet", "min #DeltaR(top, topjet)", 100, 0,5);
   
   h_topjets = ctx.get_handle<std::vector<TopJet> >(name_handletopjets);   
   h_ttbargen = ctx.get_handle<TTbarGen>("ttbargen");
}


void PuppiAndTopTaggingGenHists::fill(const Event & event){
   
   double weight = event.weight;
   const auto & ttbargen = event.get(h_ttbargen);
   vector<TopJet> topjets =event.get(h_topjets);
   
   double DeltaR_TopMin = 100;
   double DeltaR_AntitopMin = 100;
   double DeltaR_Top = 100;
   double DeltaR_Antitop = 100;
   
   for (unsigned int i=0; i<topjets.size();i++)
      {
         TopJet tp = topjets.at(i);
         DeltaR_Top = deltaR(ttbargen.Top(),tp);
         if (DeltaR_Top<DeltaR_TopMin) DeltaR_TopMin = DeltaR_Top;
         DeltaR_Antitop = deltaR(ttbargen.Antitop(),tp);
         if (DeltaR_Antitop<DeltaR_AntitopMin)  DeltaR_AntitopMin= DeltaR_Antitop;
      }
   DeltaR_top_topjet -> Fill(DeltaR_AntitopMin, weight);
   DeltaR_top_topjet -> Fill(DeltaR_TopMin, weight);
   
}





