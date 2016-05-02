import FWCore.ParameterSet.Config as cms
### USAGE:
###    cmsRun fitMuonID.py <scenario> [ <id> [ <binning1> ... <binningN> ] ]
###
### scenarios:
###   - data_all (default)  
###   - signal_mc; mc_weight

import sys
args = sys.argv[1:]
if (sys.argv[0] == "cmsRun"): args =sys.argv[2:]
scenario = "data_all"
if len(args) > 0: scenario = args[0]
print "Will run scenario ", scenario 

process = cms.Process("TagProbe")

process.load('FWCore.MessageService.MessageLogger_cfi')

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

Template = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    NumCPU = cms.uint32(1),
    SaveWorkspace = cms.bool(False),

    Variables = cms.PSet(
        mass = cms.vstring("Tag-muon Mass", "76", "125", "GeV/c^{2}"),
        pt = cms.vstring("muon p_{T}", "0", "1000", "GeV/c"),
        phi = cms.vstring("muon #phi", "-3.14", "3.14", ""),
        tag_pt = cms.vstring("tag muon p_{T}", "0", "1000", "GeV/c"),
        eta    = cms.vstring("muon #eta", "-2.5", "2.5", ""),
        abseta = cms.vstring("muon |#eta|", "0", "2.5", ""),
        tag_nVertices = cms.vstring("Number of vertices", "0", "999", ""),
        pfCombRelIso04EACorr = cms.vstring("Number of vertices", "0", "999", ""),
        SIP = cms.vstring("Number of vertices", "0", "999", ""),
        run = cms.vstring("Number of vertices", "-999", "999999", ""),
        HLT_Mu8  = cms.vstring("Mu8 leg",  "-1", "2", ""),
        HLT_Mu17 = cms.vstring("Mu17 leg", "-1", "2", ""),
    ),

    Categories = cms.PSet(
        Glb   = cms.vstring("Global", "dummy[pass=1,fail=0]"),
        PF    = cms.vstring("PF Muon", "dummy[pass=1,fail=0]"),
        TM    = cms.vstring("Tracker Muon", "dummy[pass=1,fail=0]"),
        mvaIsoCut = cms.vstring("MC true", "dummy[pass=1,fail=0]"),
        mcTrue = cms.vstring("MC true", "dummy[true=1,false=0]"),
        Tight2012 = cms.vstring("Tight2012", "dummy[pass=1,fail=0]"),

        tag_IsoMu20 = cms.vstring("tag_IsoMu20", "dummy[pass=1,fail=0]"),
     #  tag_Mu17_TkIso = cms.vstring("tag_Mu17_TkIso", "dummy[pass=1,fail=0]"), # new
        IsoMu20 = cms.vstring("IsoMu20", "dummy[pass=1,fail=0]"),  # new

        Mu17_IsoTrkVVL = cms.vstring("Mu17_IsoTrkVVL", "dummy[pass=1,fail=0]"), # new
        tag_Mu17_IsoTrkVVL = cms.vstring("tag_Mu17_IsoTrkVVL", "dummy[pass=1,fail=0]"), # new

        Mu17 = cms.vstring("Mu17", "dummy[pass=1,fail=0]"), # new
        tag_Mu17 = cms.vstring("tag_Mu17", "dummy[pass=1,fail=0]"), # new

        DoubleIsoMu17Mu8_IsoMu17leg = cms.vstring("DoubleIsoMu17Mu8_IsoMu17leg", "dummy[pass=1,fail=0]"), # new
        tag_DoubleIsoMu17Mu8_IsoMu17leg = cms.vstring("tag_DoubleIsoMu17Mu8_IsoMu17leg", "dummy[pass=1,fail=0]"), # new

        IsoMu17_eta2p1 = cms.vstring("IsoMu17_eta2p1", "dummy[pass=1,fail=0]"),
     #  Mu17_TkIso = cms.vstring("Mu17_TkIso", "dummy[pass=1,fail=0]"),   # new
        IsoTkMu20 = cms.vstring("IsoTkMu20", "dummy[pass=1,fail=0]"),
        L1sMu16 = cms.vstring("L1sMu16", "dummy[pass=1,fail=0]"),
        Mu20 = cms.vstring("Mu20", "dummy[pass=1,fail=0]"),
        Mu50 = cms.vstring("Mu50", "dummy[pass=1,fail=0]"),
        tag_Mu20 = cms.vstring("tag_Mu20", "dummy[pass=1,fail=0]"),
        L2fL1sMu16L1f0L2Filtered10Q = cms.vstring("L2fL1sMu16L1f0L2Filtered10Q", "dummy[pass=1,fail=0]"),


    ),
    Cuts = cms.PSet(),
    PDFs = cms.PSet(
        voigtPlusExpo = cms.vstring(
            "Voigtian::signal(mass, mean[90,80,100], width[2.495], sigma[3,1,20])",
            "Exponential::backgroundPass(mass, lp[0,-5,5])",
            "Exponential::backgroundFail(mass, lf[0,-5,5])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpo = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,2,10])",
            "SUM::signal(vFrac[0.8,0,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0,1]",
            "signalFractionInPassing[0.9]"
        ),
        vpvPlusExpoMin70 = cms.vstring(
            "Voigtian::signal1(mass, mean1[90,80,100], width[2.495], sigma1[2,1,3])",
            "Voigtian::signal2(mass, mean2[90,80,100], width,        sigma2[4,3,10])",
            "SUM::signal(vFrac[0.8,0.5,1]*signal1, signal2)",
            "Exponential::backgroundPass(mass, lp[-0.1,-1,0.1])",
            "Exponential::backgroundFail(mass, lf[-0.1,-1,0.1])",
            "efficiency[0.9,0.7,1]",
            "signalFractionInPassing[0.9]"
        )
    ),

    binnedFit = cms.bool(False),
    binsForFit = cms.uint32(40),
    saveDistributionsPlot = cms.bool(False),

    Efficiencies = cms.PSet(), # will be filled later
)






PT_ETA_BINS = cms.PSet(
                     #   pt     = cms.vdouble( 0, 10, 15,20,25,30, 40,60, 100 ),
                     #   pt     = cms.vdouble( 0, 10, 15, 20, 25, 60, 100 ),
                         pt     = cms.vdouble( 0, 5, 10, 12, 15, 17, 20, 25, 60, 100 ),
                     #  abseta = cms.vdouble(0.0, 0.9, 2.4),
                        abseta = cms.vdouble(0.0,  2.4),
                        Tight2012 = cms.vstring("pass"),
                        tag_Mu17_IsoTrkVVL = cms.vstring("pass"),
                     #  tag_Mu17 = cms.vstring("pass"),
                     #   tag_DoubleIsoMu17Mu8_IsoMu17leg = cms.vstring("pass"),                    
                     #  tag_IsoMu20 = cms.vstring("pass"),
                        tag_pt =  cms.vdouble(25,9999)
)

ETA_BINS = cms.PSet(
                       pt     = cms.vdouble( 20, 1000 ),
                       eta = cms.vdouble(-2.4,-2.1,-1.2,-0.9,0.0,0.9,1.2,2.1, 2.4),
                       Tight2012 = cms.vstring("pass"),
                      #  tag_Mu17_IsoTrkVVL = cms.vstring("pass"),
                       tag_IsoMu20 = cms.vstring("pass"),
                       tag_pt =  cms.vdouble(25,9999)
                       )

PHI_HIGHETA_BINS = cms.PSet(
                      pt     = cms.vdouble( 20, 1000 ),
                      phi     = cms.vdouble(-3.1,-2.7,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2,0.2,0.6,1.0,1.4,1.8,2.2,2.7,3.1),
                      eta = cms.vdouble(1.2,2.1, 2.4),
                      Tight2012 = cms.vstring("pass"),
                      #  tag_Mu17_IsoTrkVVL = cms.vstring("pass"),
                      tag_IsoMu20 = cms.vstring("pass"),
                      tag_pt =  cms.vdouble(25,9999)
                    )

PHI_BINS = cms.PSet(
                    phi     = cms.vdouble(-3.1,-2.7,-2.2,-1.8,-1.4,-1.0,-0.6,-0.2,0.2,0.6,1.0,1.4,1.8,2.2,2.7,3.1),
                       pt     = cms.vdouble( 20, 1000 ),
                       abseta = cms.vdouble(0.0, 2.4),
                       Tight2012 = cms.vstring("pass"),
                     # tag_Mu17_IsoTrkVVL = cms.vstring("pass"),
                       tag_IsoMu20 = cms.vstring("pass"),
                       tag_pt =  cms.vdouble(25,9999)
    
                       )

VTX_BINS  = cms.PSet(
    pt     = cms.vdouble(  25, 120 ),
    abseta = cms.vdouble(  0.0, 2.4),
    tag_nVertices = cms.vdouble(0.5,2.5,4.5,6.5,8.5,10.5,12.5,14.5,16.5,18.5,20.5,22.5)
                     #tag_nVertices = cms.vdouble(0.5,2.5,4.5,6.5,8.5,10.5,12.5,16.5,20.5,25,30,40)
)



process.TnP_MuonID = Template.clone(
    InputFileNames = cms.vstring(
                                # "root://eoscms//eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/tnpZ_withNVtxWeights.root"
                                # "root://eoscms//eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/tnpZDoubleMu_withNVtxWeightsRunBjson.root"
             #  "root://eoscms//eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/tnpZ_withNVtxWeights_fullBjson.root"
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_10.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_1.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_2.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_3.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_4.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_5.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_6.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_7.root',
'file:/afs/cern.ch/user/a/agrebeny/eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/DoubleMuSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/TnPtreesMCdoubleMuon25ns/150930_133759/0000/tnpZ_MC_8.root'


                                # "/tmp/hbrun/tnpZ_withNVtxWeightsFullStatDCS.root"
                                 ),
    InputTreeName = cms.string("fitter_tree"),
    InputDirectoryName = cms.string("tpTree"),
    OutputFileName = cms.string("TnP_MuonID_%s.root" % scenario),
    Efficiencies = cms.PSet(),
)
if "_weight" in scenario:
    process.TnP_MuonID.WeightVariable = cms.string("weight")
    process.TnP_MuonID.Variables.weight = cms.vstring("weight","0","10","")
if scenario=="data":
    process.TnP_MuonID.InputFileNames = cms.vstring(
                                                    #  "root://eoscms//eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/theDataTnP.root",
                                                    #"/tmp/hbrun/theDataTnP_fullStatDCS.root"
                                                    "root://eoscms//eos/cms/store/group/phys_muon/hbrun/dataCommissioning/TnPtrees/dataDoubleMu_TnPfullStatJson.root"
                                                    )

#IDS = [ "IsoMu20","Mu20","L2fL1sMu16L1f0L2Filtered10Q","IsoTkMu20","L1sMu16"]
#IDS = [ "IsoMu20"]
#IDS = [ "IsoMu20_eta2p1"]
#IDS = [ "Mu17"]
#IDS = ["DoubleIsoMu17Mu8_IsoMu17leg"]
IDS = ["DoubleIsoMu17Mu8_Mu17"]
#IDS = [ "Mu17_IsoTrkVVL"]
#IDS = [ "IsoMu17_eta2p1"]
# IDS = [ "Mu50"]  # Mu20 Mu50 #

#ALLBINS = [("pt_eta",PT_ETA_BINS),("phi",PHI_BINS),("eta",ETA_BINS),("vtx",VTX_BINS), ("phiHighEta",PHI_HIGHETA_BINS)]
ALLBINS = [("pt_eta",PT_ETA_BINS)]

if len(args) > 1 and args[1] not in IDS: IDS += [ args[1] ]
for ID in IDS:
    print "now doing ",ID
    if len(args) > 1 and ID != args[1]: continue
    for X,B in ALLBINS:
        if len(args) > 2 and X not in args[2:]: continue
        module = process.TnP_MuonID.clone(OutputFileName = cms.string("TnP_MuonID_%s_%s_%s.root" % (scenario, ID, X)))
        shape = "vpvPlusExpo"
        #if "eta" in X and not "abseta" in X: shape = "voigtPlusExpo"
        #if "pt_abseta" in X: shape = "voigtPlusExpo"
        # if "Mu17" in ID and "pt_abseta" in X: B = PT_ETA_BINS_MU17
        if "Mu8" in ID and "pt_abseta" in X: B = PT_ETA_BINS_MU8
        DEN = B.clone(); num = ID; numstate = "pass"
        if ID=="Mu20":
            setattr(DEN,"tag_Mu20",cms.vstring("pass"))
        if "_from_" in ID:
            parts = ID.split("_from_")
            num = parts[0]
            for D in parts[1].split("_and_"):
                if D == "SIP4":      DEN.SIP = cms.vdouble(0,4.0)
                elif D == "PFIso25": DEN.pfCombRelIso04EACorr  = cms.vdouble(0,0.25)
                elif D == "PFIso40": DEN.pfCombRelIso04EACorr  = cms.vdouble(0,0.40)
                else: setattr(DEN, D, cms.vstring("pass"))
        numString = cms.vstring()
        for N in num.split("_and_"):
            if N == "SIP4":
                module.Cuts.SIP4 = cms.vstring("SIP4","SIP", "4.0") 
                numString += [N, "below"]
            elif N == "PFIso25":
                module.Cuts.PFIso25 = cms.vstring("PFIso","pfCombRelIso04EACorr", "0.25") 
                numString += [N, "below"]
            elif N == "PFIso40":
                module.Cuts.PFIso40 = cms.vstring("PFIso","pfCombRelIso04EACorr", "0.40") 
                numString += [N, "below"]
            elif N in [ "HLT_Mu17", "HLT_Mu8" ]:
                setattr(module.Cuts, N+"_Pass", cms.vstring(N+"_Pass", N, "0.5")) 
                numString += [N+"_Pass", "above"]
            else:
                numString += [N, "pass"]
        setattr(module.Efficiencies, ID+"_"+X, cms.PSet(
            EfficiencyCategoryAndState = numString,
            UnbinnedVariables = cms.vstring("mass"),
            BinnedVariables = DEN,
            BinToPDFmap = cms.vstring(shape)
        ))
        if scenario.find("mc") != -1:
            setattr(module.Efficiencies, ID+"_"+X+"_mcTrue", cms.PSet(
                EfficiencyCategoryAndState = numString,
                UnbinnedVariables = cms.vstring("mass"),
                BinnedVariables = DEN.clone(mcTrue = cms.vstring("true"))
            ))
            if "_weight" in scenario:
                getattr(module.Efficiencies, ID+"_"+X          ).UnbinnedVariables.append("weight")
                getattr(module.Efficiencies, ID+"_"+X+"_mcTrue").UnbinnedVariables.append("weight")
        setattr(process, "TnP_MuonID_"+ID+"_"+X, module)        
        setattr(process, "run_"+ID+"_"+X, cms.Path(module))


