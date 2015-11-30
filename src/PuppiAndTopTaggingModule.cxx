
#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/common/include/CollectionProducer.h"
#include "UHH2/common/include/MCWeight.h"

#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingSelections.h"
#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingHists.h"
#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingGenHistsBackground.h"
#include "UHH2/PuppiAndTopTagging/include/PuppiAndTopTaggingGenHists.h"
#include "UHH2/PuppiAndTopTagging/include/MatchingSignal.h"
#include "UHH2/PuppiAndTopTagging/include/MatchingBackground.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/common/include/JetHists.h"

using namespace std;
using namespace uhh2;

class PuppiAndTopTaggingModule: public AnalysisModule {
public:
   
   explicit PuppiAndTopTaggingModule(Context & ctx);
   virtual bool process(Event & event) override;
   
private:
   bool is_signal;
   
   uhh2::Event::Handle<std::vector<TopJet> > h_heptopjetsCHS;
   uhh2::Event::Handle<std::vector<TopJet> > h_heptopjetsPuppi;
   uhh2::Event::Handle<std::vector<TopJet> > h_Ak8SoftDropCHS;
   uhh2::Event::Handle<std::vector<TopJet> > h_Ak8SoftDropPuppi;

   std::unique_ptr<TopJetCleaner> topjet_cleaner;
   std::unique_ptr<TopJetCorrector> topjet_corrector;
   std::unique_ptr<GenericTopJetCorrector> topjetPuppi_corrector;
   std::unique_ptr<GenericTopJetCorrector> heptopjetCHS_corrector;
   std::unique_ptr<GenericTopJetCorrector> heptopjetPuppi_corrector;
   std::unique_ptr<GenericTopJetCorrector> Ak8SoftDropCHS_corrector;
   std::unique_ptr<GenericTopJetCorrector> Ak8SoftDropPuppi_corrector;
   std::unique_ptr<AnalysisModule> ttgenprod;
   std::unique_ptr<AnalysisModule> match_signal_hepttPuppi;
   std::unique_ptr<AnalysisModule> match_signal_hepttCHS;
   std::unique_ptr<AnalysisModule> match_bg_hepttPuppi;
   std::unique_ptr<AnalysisModule> match_bg_hepttCHS;
   std::unique_ptr<AnalysisModule> match_signal_Ak8SoftDropPuppi;
   std::unique_ptr<AnalysisModule> match_signal_Ak8SoftDropCHS;
   std::unique_ptr<AnalysisModule> match_bg_Ak8SoftDropPuppi;
   std::unique_ptr<AnalysisModule> match_bg_Ak8SoftDropCHS;
   std::unique_ptr<AnalysisModule> match_bg;
   
   std::unique_ptr<AnalysisModule> HepTTPuppicollectionprod;
   std::unique_ptr<AnalysisModule> HepTTCHScollectionprod;
   std::unique_ptr<AnalysisModule> Ak8SoftDropPuppicollectionprod;
   std::unique_ptr<AnalysisModule> Ak8SoftDropCHScollectionprod;
   std::unique_ptr<AnalysisModule> lumi_weight; 
   
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_hepttPuppi_hists;
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_hepttCHS_hists;
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_hepttRunIPuppi_hists;
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_hepttRunICHS_hists;
   std::unique_ptr<TopJetHists> hepttCHS_hists;
   std::unique_ptr<TopJetHists> hepttPuppi_hists;
   std::unique_ptr<TopJetHists> hepttCHS_beforecuts_hists;
   std::unique_ptr<TopJetHists> hepttPuppi_beforecuts_hists;
   std::unique_ptr<TopJetHists> hepttCHS_corr_hists;
   std::unique_ptr<TopJetHists> hepttPuppi_corr_hists;
   std::unique_ptr<PuppiAndTopTaggingGenHists> genhists_Puppi;
   std::unique_ptr<PuppiAndTopTaggingGenHists> genhists_CHS;
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_Ak8SoftDropPuppi_hists;
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_Ak8SoftDropCHS_hists;
   std::unique_ptr<PuppiAndTopTaggingHists> efficiency_heptt_highpT_01_Puppi_hists,  efficiency_heptt_highpT_01_CHS_hists, efficiency_heptt_highpT_03_Puppi_hists, efficiency_heptt_highpT_03_CHS_hists, efficiency_heptt_highpT_1_Puppi_hists,efficiency_heptt_highpT_1_CHS_hists,efficiency_heptt_highpT_3_Puppi_hists,efficiency_heptt_highpT_3_CHS_hists,efficiency_heptt_highpT_10_Puppi_hists,efficiency_heptt_highpT_10_CHS_hists,efficiency_heptt_lowpT_01_Puppi_hists,efficiency_heptt_lowpT_01_CHS_hists,efficiency_heptt_lowpT_03_Puppi_hists,efficiency_heptt_lowpT_03_CHS_hists,efficiency_heptt_lowpT_1_Puppi_hists,efficiency_heptt_lowpT_1_CHS_hists,efficiency_heptt_lowpT_3_Puppi_hists,efficiency_heptt_lowpT_3_CHS_hists,efficiency_heptt_lowpT_10_Puppi_hists,efficiency_heptt_lowpT_10_CHS_hists;
   std::unique_ptr<TopJetHists> Ak8SoftDropCHS_hists;
   std::unique_ptr<TopJetHists> Ak8SoftDropPuppi_hists;
   std::unique_ptr<PuppiAndTopTaggingGenHistsBackground> genhist_bg_CHS;
};


PuppiAndTopTaggingModule::PuppiAndTopTaggingModule(Context & ctx){
   
   is_signal = (ctx.get("dataset_version") == "MC_TT_Mtt-700to1000_Puppi") || (ctx.get("dataset_version") == "MC_TT_Mtt-1000toInf_Puppi"); 
   lumi_weight.reset(new MCLumiWeight(ctx));

   
   HepTTPuppicollectionprod.reset(new CollectionProducer<TopJet>(ctx, "patJetsHepTopTagPuppiPacked_daughters", "h_heptopjetsPuppi",TopJetId(PtEtaCut(150., 2.4))));
   HepTTCHScollectionprod.reset(new CollectionProducer<TopJet>(ctx, "patJetsHepTopTagCHSPacked_daughters", "h_heptopjetsCHS",TopJetId(PtEtaCut(150., 2.4))));

   Ak8SoftDropPuppicollectionprod.reset(new CollectionProducer<TopJet>(ctx, "patJetsAk8PuppiJetsSoftDropPacked_daughters", "h_ak8SoftDropPuppi",TopJetId(PtEtaCut(150., 2.4))));
   Ak8SoftDropCHScollectionprod.reset(new CollectionProducer<TopJet>(ctx, "patJetsAk8CHSJetsSoftDropPacked_daughters", "h_ak8SoftDropCHS",TopJetId(PtEtaCut(150., 2.4))));

   //Ca15PuppiJetsSoftDropcollectionprod.reset(new CollectionProducer<TopJet>(ctx, "patJetsCa15PuppiJetsSoftDropPacked_daughters", "h_ca15PuppiJetsSoftDrop",TopJetId(PtEtaCut(150., 2.4))));
  
 
 
   ttgenprod.reset(new TTbarGenProducer(ctx, "ttbargen", false));
   
   match_signal_hepttPuppi.reset(new MatchingSignal(ctx, "h_heptopjetsPuppi","patJetsHepTopTagPuppiPacked_daughters"));
   match_signal_hepttCHS.reset(new MatchingSignal(ctx, "h_heptopjetsCHS", "patJetsHepTopTagCHSPacked_daughters"));
   
   match_bg_hepttPuppi.reset(new MatchingBackground(ctx, "h_heptopjetsPuppi","patJetsHepTopTagPuppiPacked_daughters"));
   match_bg_hepttCHS.reset(new MatchingBackground(ctx, "h_heptopjetsCHS", "patJetsHepTopTagCHSPacked_daughters"));
   
   match_signal_Ak8SoftDropPuppi.reset(new MatchingSignal(ctx, "h_ak8SoftDropPuppi","patJetsAk8PuppiJetsSoftDropPacked_daughters"));
   match_signal_Ak8SoftDropCHS.reset(new MatchingSignal(ctx, "h_ak8SoftDropCHS", "patJetsAk8CHSJetsSoftDropPacked_daughters"));
   
   match_bg_Ak8SoftDropPuppi.reset(new MatchingBackground(ctx, "h_ak8SoftDropPuppi","patJetsAk8PuppiJetsSoftDropPacked_daughters"));
   match_bg_Ak8SoftDropCHS.reset(new MatchingBackground(ctx, "h_ak8SoftDropCHS", "patJetsAk8CHSJetsSoftDropPacked_daughters"));

   //match_signal_Ca15SoftDropPuppi.reset(new MatchingSignal(ctx, "h_ca15PuppiJetsSoftDrop", "patJetsCa15PuppiJetsSoftDropPacked_daughters");
   //match_bg_Ca15SoftDropPuppi.reset(new MatchingBackground(ctx, "h_ca15PuppiJetsSoftDrop", "patJetsCa15PuppiJetsSoftDropPacked_daughters");                                     
                                        

   topjet_cleaner.reset(new TopJetCleaner(TopJetId(PtEtaCut(150., 2.4)))); 
   topjet_corrector.reset(new TopJetCorrector(JERFiles::Summer15_50ns_L123_AK8PFPuppi_MC));  
   heptopjetCHS_corrector.reset(new GenericTopJetCorrector(ctx, JERFiles::Summer15_50ns_L123_AK8PFPuppi_MC,"h_heptopjetsCHS"));
   heptopjetPuppi_corrector.reset(new GenericTopJetCorrector(ctx,JERFiles::Summer15_50ns_L123_AK8PFPuppi_MC,"h_heptopjetsPuppi"));
   Ak8SoftDropCHS_corrector.reset(new GenericTopJetCorrector(ctx, JERFiles::Summer15_50ns_L123_AK8PFPuppi_MC,"h_ak8SoftDropCHS"));
   Ak8SoftDropPuppi_corrector.reset(new GenericTopJetCorrector(ctx,JERFiles::Summer15_50ns_L123_AK8PFPuppi_MC,"h_ak8SoftDropPuppi"));
   
   genhists_Puppi.reset( new PuppiAndTopTaggingGenHists(ctx, "genhists_Puppi", "patJetsHepTopTagPuppiPacked_daughters"));
   genhists_CHS.reset( new PuppiAndTopTaggingGenHists(ctx, "genhists_CHS", "patJetsHepTopTagCHSPacked_daughters"));

   const TopJetId HTTTopJetId = HEPTopTagV2(); 
   const TopJetId HTTTopJetIdRunI = HEPTopTag();

   const TopJetId HTTTopJetId_highpT_WP1_01 = AndId<TopJet>(HEPTopTagV2(80,170,0.16,-0.17,0.5), Tau32(0.48));
   const TopJetId HTTTopJetId_highpT_WP1_03 = AndId<TopJet>(HEPTopTagV2(120,180,0.18,-0.11,0.063), Tau32(0.59));
   const TopJetId HTTTopJetId_highpT_WP1_1 = AndId<TopJet>(HEPTopTagV2(80,190,0.47,-0.68,0.13), Tau32(0.6));
   const TopJetId HTTTopJetId_highpT_WP1_3 = AndId<TopJet>(HEPTopTagV2(100,180,0.26,-0.43,0.2), Tau32(0.77));
   const TopJetId HTTTopJetId_highpT_WP1_10 = AndId<TopJet>(HEPTopTagV2(60,200,0.5,-0.64,0.26), Tau32(0.92));

   const TopJetId HTTTopJetId_lowpT_WP1_01 = AndId<TopJet>(HEPTopTagV2(70,170,0.48,-0.32,0.79), Tau32(0.53));
   const TopJetId HTTTopJetId_lowpT_WP1_03= AndId<TopJet>(HEPTopTagV2(120,180,0.17,-0.56,0.17), Tau32(0.65));
   const TopJetId HTTTopJetId_lowpT_WP1_1= AndId<TopJet>(HEPTopTagV2(120,330,0.25,-0.76,0.24), Tau32(0.71));
   const TopJetId HTTTopJetId_lowpT_WP1_3= AndId<TopJet>(HEPTopTagV2(110,300,0.35,-0.78,0.26), Tau32(0.97));
   const TopJetId HTTTopJetId_lowpT_WP1_10= AndId<TopJet>(HEPTopTagV2(80,300,0.5,-0.67,0.71), Tau32(0.91));

   // const TopJetId HTTTopJetId_highpT_WP1_01 = HEPTopTagV2(80,170,0.16,-0.17,0.5);
   // const TopJetId HTTTopJetId_highpT_WP1_03 = HEPTopTagV2(120,180,0.18,-0.11,0.063);
   // const TopJetId HTTTopJetId_highpT_WP1_1 = HEPTopTagV2(80,190,0.47,-0.68,0.13);
   // const TopJetId HTTTopJetId_highpT_WP1_3 = HEPTopTagV2(100,180,0.26,-0.43,0.2);
   // const TopJetId HTTTopJetId_highpT_WP1_10 = HEPTopTagV2(60,200,0.5,-0.64,0.26);

   // const TopJetId HTTTopJetId_lowpT_WP1_01 = HEPTopTagV2(70,170,0.48,-0.32,0.79);
   // const TopJetId HTTTopJetId_lowpT_WP1_03= HEPTopTagV2(120,180,0.17,-0.56,0.17);
   // const TopJetId HTTTopJetId_lowpT_WP1_1= HEPTopTagV2(120,330,0.25,-0.76,0.24);
   // const TopJetId HTTTopJetId_lowpT_WP1_3= HEPTopTagV2(110,300,0.35,-0.78,0.26);
   // const TopJetId HTTTopJetId_lowpT_WP1_10= HEPTopTagV2(80,300,0.5,-0.67,0.71); 

   const TopJetId SoftDrop = Type2TopTag(110,210);
   
   // old WP
   efficiency_hepttPuppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_hepttPuppi_hists->set_TopJetId(HTTTopJetId); 
   efficiency_hepttCHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_hepttCHS_hists->set_TopJetId(HTTTopJetId); 
   
   //SoftDrop
   efficiency_Ak8SoftDropPuppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_Ak8SoftDropPuppi", "patJetsAk8PuppiJetsSoftDropPacked_daughters"));
   efficiency_Ak8SoftDropPuppi_hists->set_TopJetId(SoftDrop); 
   efficiency_Ak8SoftDropCHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_Ak8SoftDropCHS", "patJetsAk8CHSJetsSoftDropPacked_daughters"));
   efficiency_Ak8SoftDropCHS_hists->set_TopJetId(SoftDrop); 
   

   //high pT WPs
   efficiency_heptt_highpT_01_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_highpT_01", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_highpT_01_Puppi_hists->set_TopJetId(HTTTopJetId_highpT_WP1_01); 
   efficiency_heptt_highpT_01_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_highpT_01", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_highpT_01_CHS_hists->set_TopJetId(HTTTopJetId_highpT_WP1_01);

   efficiency_heptt_highpT_03_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_highpT_03", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_highpT_03_Puppi_hists->set_TopJetId(HTTTopJetId_highpT_WP1_03); 
   efficiency_heptt_highpT_03_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_highpT_03", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_highpT_03_CHS_hists->set_TopJetId(HTTTopJetId_highpT_WP1_03);

   efficiency_heptt_highpT_1_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_highpT_1", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_highpT_1_Puppi_hists->set_TopJetId(HTTTopJetId_highpT_WP1_1); 
   efficiency_heptt_highpT_1_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_highpT_1", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_highpT_1_CHS_hists->set_TopJetId(HTTTopJetId_highpT_WP1_1);

   efficiency_heptt_highpT_3_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_highpT_3", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_highpT_3_Puppi_hists->set_TopJetId(HTTTopJetId_highpT_WP1_3); 
   efficiency_heptt_highpT_3_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_highpT_3", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_highpT_3_CHS_hists->set_TopJetId(HTTTopJetId_highpT_WP1_3);

   efficiency_heptt_highpT_10_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_highpT_10", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_highpT_10_Puppi_hists->set_TopJetId(HTTTopJetId_highpT_WP1_10); 
   efficiency_heptt_highpT_10_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_highpT_10", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_highpT_10_CHS_hists->set_TopJetId(HTTTopJetId_highpT_WP1_10);


   //low pT WPs
   efficiency_heptt_lowpT_01_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_lowpT_01", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_lowpT_01_Puppi_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_01); 
   efficiency_heptt_lowpT_01_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_lowpT_01", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_lowpT_01_CHS_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_01);

   efficiency_heptt_lowpT_03_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_lowpT_03", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_lowpT_03_Puppi_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_03); 
   efficiency_heptt_lowpT_03_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_lowpT_03", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_lowpT_03_CHS_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_03);

   efficiency_heptt_lowpT_1_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_lowpT_1", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_lowpT_1_Puppi_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_1); 
   efficiency_heptt_lowpT_1_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_lowpT_1", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_lowpT_1_CHS_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_1);

   efficiency_heptt_lowpT_3_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_lowpT_3", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_lowpT_3_Puppi_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_3); 
   efficiency_heptt_lowpT_3_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_lowpT_3", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_lowpT_3_CHS_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_3);

   efficiency_heptt_lowpT_10_Puppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttPuppi_lowpT_10", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_heptt_lowpT_10_Puppi_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_10); 
   efficiency_heptt_lowpT_10_CHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttCHS_lowpT_10", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_heptt_lowpT_10_CHS_hists->set_TopJetId(HTTTopJetId_lowpT_WP1_10);


   //HepTT RunI
   efficiency_hepttRunIPuppi_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttRunIPuppi", "patJetsHepTopTagPuppiPacked_daughters"));
   efficiency_hepttRunIPuppi_hists->set_TopJetId(HTTTopJetIdRunI); 
   efficiency_hepttRunICHS_hists.reset(new PuppiAndTopTaggingHists(ctx,"efficiency_hepttRunICHS", "patJetsHepTopTagCHSPacked_daughters"));
   efficiency_hepttRunICHS_hists->set_TopJetId(HTTTopJetIdRunI); 

   //Control hists
   hepttCHS_hists.reset(new TopJetHists(ctx, "hepttCHS_matched",4,"matched_topjets_patJetsHepTopTagCHSPacked_daughters"));
   hepttPuppi_hists.reset(new TopJetHists(ctx, "hepttPuppi_matched",4,"matched_topjets_patJetsHepTopTagPuppiPacked_daughters"));
   hepttCHS_beforecuts_hists.reset(new TopJetHists(ctx, "h_heptopjetsCHS",4,"patJetsHepTopTagCHSPacked_daughters"));
   hepttPuppi_beforecuts_hists.reset(new TopJetHists(ctx, "h_heptopjetsPuppi",4,"patJetsHepTopTagPuppiPacked_daughters"));
   hepttCHS_corr_hists.reset(new TopJetHists(ctx, "h_heptopjetsCHS_corr",4,"patJetsHepTopTagCHSPacked_daughters"));
   hepttPuppi_corr_hists.reset(new TopJetHists(ctx, "h_heptopjetsPuppi_corr",4,"patJetsHepTopTagPuppiPacked_daughters"));
   Ak8SoftDropCHS_hists.reset(new TopJetHists(ctx, "Ak8SoftDropCHS_matched",4,"matched_topjets_patJetsAk8CHSJetsSoftDropPacked_daughters"));
   Ak8SoftDropPuppi_hists.reset(new TopJetHists(ctx, "Ak8SoftDropPuppi_matched",4,"matched_topjets_patJetsAk8PuppiJetsSoftDropPacked_daughters"));
   
   genhist_bg_CHS.reset(new PuppiAndTopTaggingGenHistsBackground(ctx, "genhist_bg_CHS","matched_topjets_patJetsHepTopTagCHSPacked_daughters"));
}                                                                                      


bool PuppiAndTopTaggingModule::process(Event & event) {  
   
   lumi_weight->process(event); 

   HepTTPuppicollectionprod->process(event);
   HepTTCHScollectionprod->process(event);

   Ak8SoftDropPuppicollectionprod->process(event);
   Ak8SoftDropCHScollectionprod->process(event);
   
   hepttCHS_beforecuts_hists->fill(event);
   hepttPuppi_beforecuts_hists->fill(event);   

   topjet_corrector->process(event);
   heptopjetCHS_corrector->process(event);
   heptopjetPuppi_corrector->process(event);
   Ak8SoftDropCHS_corrector->process(event);
   Ak8SoftDropPuppi_corrector->process(event);
   
   topjet_cleaner->process(event);
   sort_by_pt<TopJet>(*event.topjets);
 
   hepttCHS_corr_hists->fill(event);
   hepttPuppi_corr_hists->fill(event);
   
   if(!is_signal) {
      match_bg_hepttPuppi->process(event);
      match_bg_hepttCHS->process(event);
      match_bg_Ak8SoftDropPuppi->process(event);
      match_bg_Ak8SoftDropCHS->process(event);
      genhist_bg_CHS->fill(event);
   }
   else 
      {
         ttgenprod->process(event);
         genhists_Puppi ->fill(event);
         genhists_CHS ->fill(event);
         match_signal_hepttPuppi->process(event);
         match_signal_hepttCHS->process(event);
         match_signal_Ak8SoftDropPuppi->process(event);
         match_signal_Ak8SoftDropCHS->process(event);
      }
   
   hepttCHS_hists->fill(event);  
   hepttPuppi_hists->fill(event);

   Ak8SoftDropCHS_hists->fill(event);  
   Ak8SoftDropPuppi_hists->fill(event);

   efficiency_hepttPuppi_hists->fill(event);
   efficiency_hepttCHS_hists->fill(event);

   efficiency_Ak8SoftDropPuppi_hists->fill(event);
   efficiency_Ak8SoftDropCHS_hists->fill(event);

   efficiency_hepttRunIPuppi_hists->fill(event);
   efficiency_hepttRunICHS_hists->fill(event);

   efficiency_heptt_highpT_01_Puppi_hists->fill(event);
   efficiency_heptt_highpT_01_CHS_hists->fill(event);
   

   efficiency_heptt_highpT_03_Puppi_hists->fill(event);
   efficiency_heptt_highpT_03_CHS_hists->fill(event);
   
   efficiency_heptt_highpT_1_Puppi_hists->fill(event);
   efficiency_heptt_highpT_1_CHS_hists->fill(event);
   
   efficiency_heptt_highpT_3_Puppi_hists->fill(event);
   efficiency_heptt_highpT_3_CHS_hists->fill(event);
   
   efficiency_heptt_highpT_10_Puppi_hists->fill(event);
   efficiency_heptt_highpT_10_CHS_hists->fill(event);
   
   efficiency_heptt_lowpT_01_Puppi_hists->fill(event);
   efficiency_heptt_lowpT_01_CHS_hists->fill(event);
   
   efficiency_heptt_lowpT_03_Puppi_hists->fill(event);
   efficiency_heptt_lowpT_03_CHS_hists->fill(event);
   
   efficiency_heptt_lowpT_1_Puppi_hists->fill(event);
   efficiency_heptt_lowpT_1_CHS_hists->fill(event);
   
   efficiency_heptt_lowpT_3_Puppi_hists->fill(event);
   efficiency_heptt_lowpT_3_CHS_hists->fill(event);
   
   efficiency_heptt_lowpT_10_Puppi_hists->fill(event);
   efficiency_heptt_lowpT_10_CHS_hists->fill(event);
      
   return true;

}
UHH2_REGISTER_ANALYSIS_MODULE(PuppiAndTopTaggingModule)

