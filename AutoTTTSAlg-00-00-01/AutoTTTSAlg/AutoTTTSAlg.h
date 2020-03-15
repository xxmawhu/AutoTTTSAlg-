/* <===<===<===<===<===<===<===<===<===~===>===>===>===>===>===>===>===>===>
 * File Name:    AutoTTTSAlg.hpp
 * Author:       Xin-Xin MA, Hao-Kai SUN
 * Created:      2019-09-25 Wed 19:32:12 CST
 * <<=====================================>>
 * Last Updated: 2020-01-06 Mon 19:41:23 CST
 *           By: Hao-Kai SUN
 *     Update #: 231
 * <<======== COPYRIGHT && LICENSE =======>>
 *
 * Copyright © 2019 SUN Hao-Kai <spin.hk@outlook.com>. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ============================== CODES ==============================>>> */
#ifndef AutoTTTSAlg_HPP
#define AutoTTTSAlg_HPP

#include "BesDChain/CDChargedKaonList.h"
#include "BesDChain/CDChargedPionList.h"
#include "BesDChain/CDDecayList.h"
#include "BesDChain/CDElectronList.h"
#include "BesDChain/CDEtaList.h"
#include "BesDChain/CDKsList.h"
#include "BesDChain/CDLambdaList.h"
#include "BesDChain/CDPhotonList.h"
#include "BesDChain/CDPi0List.h"
#include "BesDChain/CDProtonList.h"

#include "GaudiKernel/Algorithm.h"
#include "MCTruthMatchSvc/MCTruthMatchSvc.h"
#include "McDecayModeSvc/McDecayModeSvc.h"
#include "ParticleID/ParticleID.h"
#include "VertexFit/WTrackParameter.h"
#include "TupleSvc/DecayTree.h"
#include "TupleSvc/TupleSvc.h"
#include "TupleSvc/DecayChainSvc.h"
#include "MCTruthInfo/MCTruthInfo.h"
#include "BeamInfoSvc/BeamInfoSvc.h"
#include "PhotonConverSvc/PhotonConverSvc.h"
#include "DCListSvc/DCListSvc.h"

// already include in "GaudiKernel/Algorithm.h"
// #include <string>
// #include <vector>

class AutoTTTSAlg : public Algorithm {
   public:
    AutoTTTSAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual ~ AutoTTTSAlg();
    StatusCode initialize();
    StatusCode execute();
    StatusCode finalize();
    StatusCode LoadSvc(MsgStream &);

   private:
    int m_benchMarkLevel;
    bool m_useMatch;
    int m_Mother;
    unsigned m_MothersN;
    double m_Ecm;
    bool m_readBeamE;
    bool m_fillMCInfo;
    bool m_fillMCParA;
    int m_minTrks, m_maxTrks, m_minShowers, m_maxShowers;
    bool m_useKinematicFit;
    bool m_debug;
    int m_InfoLvl;
    int m_tagCCID;
    bool m_inclCC;
    std::vector<int> getChannelCC(const std::vector<int> &fid);

    std::vector<int>  m_tagFid, m_sigFid;
    McDecayModeSvc *m_McDecayModeSvc;
    MCTruthMatchSvc *m_matchSvc;
    MCTruthInfo *gMCTruthInfoSvc;
    BeamInfoSvc *gBeamInfoSvc;
    PhotonConverSvc *gPhotonConverSvc;
    DCListSvc *m_DCListSvc;
    
    void FillInfo(const CDCandidate &tag, const DecayTree&, TupleSvc&);
    NTuple::Tuple* BookTuple(const string& name, const string& comment="...");

    void SearchSignal(int, const DecayTree&, TupleSvc&);
    
    int getTagCharge(const CDCandidate &sig, std::vector<int> fid, const int &cctag);

    // Information to store in ROOT file.
    NTuple::Tuple *tp, *mctp, *m_sigTuple[20];
    NTuple::Item<int> *m_findSignal;
    NTuple::Item<double> m_recMass[20];
    DecayChainSvc gDecayChainSvc;
    DecayTree m_decayTree, m_tagTree;
    vector<DecayTree> m_decayTreeList;
    int m_tagmodes;
    TupleSvc m_SigTupleSvc[20];
    TupleSvc m_mcTupleSvc;
    void InitTuple();
};

#endif /* PHYS_ANA_OMEGAXIKALG_HPP */
/* ===================================================================<<< */
/* ===================== AutoTTTSAlg.hpp ends here ====================== */
