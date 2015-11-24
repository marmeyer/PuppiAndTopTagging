#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingGenHistsBackground.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/AnalysisModule.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

PuppiAndTopTaggingGenHistsBackground::PuppiAndTopTaggingGenHistsBackground(Context & ctx, const string & dirname, const std::string & name_handletopjets): Hists(ctx, dirname){
   
   DeltaR_genp_topjet = book<TH1F>( "DeltaR_genp_topjet", "min #DeltaR(genp, topjet)", 100, 0,5);
   DeltaEta_genp_topjet = book<TH1F>( "DeltaEta_genp_topjet", "min #Delta#eta(genp, topjet)", 100, -5,5);
   DeltaPhi_genp_topjet = book<TH1F>( "DeltaPhi_genp_topjet", "min #Delta#Phi(genp, topjet)", 100, -5 ,5);
   
   h_matchedgenparts = ctx.get_handle<vector<GenParticle>>("matchedgenparts");
   h_topjets = ctx.get_handle<std::vector<TopJet> >(name_handletopjets);   
}


void PuppiAndTopTaggingGenHistsBackground::fill(const Event & event){
   
   double weight = event.weight;
   vector<TopJet> matchedtopjets =event.get(h_topjets);
   
   vector<GenParticle> matchedgenparts = event.get(h_matchedgenparts);
   
   int index =100;
   double deltaRmin = 100;
   if (matchedgenparts.size()>0) 
      {
         GenParticle genp = matchedgenparts.at(0);
         for (unsigned int i=0; i<matchedtopjets.size(); i++)
            {
               TopJet tp = matchedtopjets.at(i);
               double DeltaR = deltaR(genp,tp);
               if (deltaRmin>DeltaR) 
                  {
                     deltaRmin = DeltaR;
                     index = i;
                  }
            }
      }
   if (index!=100) DeltaR_genp_topjet -> Fill(deltaRmin, weight);
   if (index!=100) DeltaEta_genp_topjet ->Fill(matchedtopjets.at(index).eta()-matchedgenparts.at(0).eta(),weight);
   if (index!=100) DeltaPhi_genp_topjet ->Fill(matchedtopjets.at(index).phi()-matchedgenparts.at(0).phi(),weight);

   
   
}





