#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TTbarGen.h"

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class PuppiAndTopTaggingGenHistsBackground: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
   PuppiAndTopTaggingGenHistsBackground(uhh2::Context & ctx, const std::string & dirname,const std::string & collection = "");
   
   virtual void fill(const uhh2::Event & ev) override;
   

protected:
   TH1F *DeltaR_genp_topjet, *DeltaEta_genp_topjet, *DeltaPhi_genp_topjet;
   uhh2::Event::Handle<std::vector<TopJet> > h_topjets;
   uhh2::Event::Handle<std::vector<GenParticle> > h_matchedgenparts;
   
};


