#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/common/include/TopJetIds.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;

PuppiAndTopTaggingHists::PuppiAndTopTaggingHists(Context & ctx, const string & dirname, const std::string & collection): Hists(ctx, dirname){
   
   matched = book<TH1F>( "MatchedTopJets", "p_{T}", 100, 0,2000);
   tagged = book<TH1F>( "TaggedTopJets", "p_{T} (tagged)", 100, 0,2000);

   matched_genp = book<TH1F>( "MatchedTopJets_genp", "p_{T} gen", 100, 0,2000);
   tagged_genp = book<TH1F>( "TaggedTopJets_genp", "p_{T} gen (tagged)", 100, 0,2000);
   
   matched_eta = book<TH1F>( "MatchedTopJets_eta", "#eta", 50, -5,5);
   tagged_eta = book<TH1F>( "TaggedTopJets_eta", "#eta (tagged)", 50, -5,5);

   matched_phi = book<TH1F>( "MatchedTopJets_phi", "#phi", 50, -5,5);
   tagged_phi = book<TH1F>( "TaggedTopJets_phi", "#phi (tagged)", 50, -5,5);

   matched_npv = book<TH1F>( "MatchedTopJets_npv", "number of primary vertices", 100, 0,100);
   tagged_npv = book<TH1F>( "TaggedTopJets_npv", "number of primary vertices", 100, 0,100);

   std::string name_handle = "matched_topjets_" +collection;
   h_matchedtopjets = ctx.get_handle<vector<TopJet> >(name_handle);
   h_matchedgenparts = ctx.get_handle<vector<GenParticle>>("matchedgenparts");
}


void PuppiAndTopTaggingHists::fill(const Event & event){
   
   double weight = event.weight;
   vector<TopJet> matchedtopjets = event.get(h_matchedtopjets);
   vector<GenParticle> matchedgenparts = event.get(h_matchedgenparts);
   
   for (unsigned int i=0; i<matchedtopjets.size(); i++)
      {
         TopJet tp = matchedtopjets.at(i);
         double deltaRmin = 100;
         int index =100;
         
         for (unsigned int j=0; j<matchedgenparts.size(); j++)
             {
                GenParticle genp = matchedgenparts.at(j);
                double DeltaR = deltaR(genp,tp);
                if (deltaRmin>DeltaR) 
                   {
                      deltaRmin = DeltaR;
                      index = j;
                   }
             }
         if (index!=100) matched_genp->Fill(matchedgenparts.at(index).pt(),weight);
         matched->Fill(tp.pt(),weight);
         matched_phi->Fill(tp.phi(),weight);
         matched_eta->Fill(tp.eta(),weight);
         matched_npv->Fill(event.pvs->size(),weight);
         if (passes_id(tp, event, topjetid)) 
            {
               if (index!=100) tagged_genp->Fill(matchedgenparts.at(index).pt(), weight);
               tagged->Fill(tp.pt(),weight);
               tagged_eta->Fill(tp.eta(),weight);
               tagged_phi->Fill(tp.phi(),weight);
               tagged_npv ->Fill(event.pvs->size(),weight);
            }
      }
}


bool PuppiAndTopTaggingHists::passes_id(TopJet & TopJet, const uhh2::Event & event, TopJetId & object_id){
  if((object_id)(TopJet, event)) return true;
  return false;
}


