////////////////////////////////////////////////////////////////////////
// \file    SRTrueParticle.h
////////////////////////////////////////////////////////////////////////
#ifndef SRTRUEPARTICLE_H
#define SRTRUEPARTICLE_H

#include <cstdint>

#include "sbncode/StandardRecord/SRVector3D.h"

#include "sbncode/StandardRecord/SREnums.h"

/* #include "SRVector3D.h" */

#include "sbncode/StandardRecord/SRTrueParticleFSP.h"

namespace caf
{
  /// Representation of a simb::MCParticle, knows energy, direction,
  // etc, but no hit information.
  class SRTrueParticle
    {
    public:

      float    planeVisE;   //!< Sum of energy deposited on each plane in the TPC (generically is =3*(startE-endE)). Helpful for truth matching. [GeV]
      float    genE;        //!< Energy at generation pt [GeV]
      float    startE;      //!< Energy at first pt in active TPC volume [GeV]
      float    endE;        //!< Energy at last pt in active TPC volume [GeV]
      float    genT;        //!< Start time of gen point [mus -- t=0 is spill time]
      float    startT;      //!< Start time of first TPC point [mus -- t=0 is spill time]
      float    endT;        //!< End time last point in the active [mus -- t=0 is spill time]
      float    length;      //!< Trajectory length in active TPC volume the particle first enters [cm]

      SRVector3D genp;        //!< Momentum at generation point [GeV/c]
      SRVector3D startp;      //!< Momentum at first point in the active TPC volume [GeV/c]
      SRVector3D endp;        //!< Momentum at last point in the active TPC volume [GeV/c]
      SRVector3D gen;         //!< Generation position [cm]
      SRVector3D start;       //!< Start position in the active TPC volume [cm]
      SRVector3D end;         //!< End position in the active TPC volume [cm]

      Wall_t   wallin;      //!< Wall of cryostat particle enters (wNone if starting in detector)
      Wall_t   wallout;     //!< Wall of cryostat particle exits (wNone if stopping in detector)

      bool     cont_tpc;    //!< Whether the particle is contained in a single TPC
      bool     crosses_tpc; //!< Whether the particle crosses a TPC boundary
      bool     contained;   //!< Whether the particle is contained in a single active volume

      int      pdg;          //!< Particle ID code
      int      G4ID;         //!< ID of the particle (taken from G4 -- -1 if this particle is not propogated by G4)
      int      interaction_id; //!< Neutrino interaction ID of the source of this particle (-1 if cosmic)

      std::vector<unsigned> daughters; //!< ID's of daughter particles from this particle
      unsigned parent; //!< ID's of parent particle from this particle

      generator_    generator;

      g4_process_   start_process; //!< Start G4 process of the particle
      g4_process_   end_process; //!< End G4 process of the particle

      genie_status_ gstatus; //!< Status of the particle as generated by genie


      // TO DO: Move functions to FillVars

      /// Whether this is a primary particle or generated by a secondary interaction
      bool IsPrimary() const;

      /// Whether this particle should have a bragg peak in the detector
      bool HasBraggPeak() const;

      /// Whether this particle was generated by genie (as opposed to geant or corsika)
      bool IsGenie() const;

      /// Whether this is a stable particle as generated by genie
      bool IsStable() const;

      int                                    nfsps; 
      std::vector<SRTrueParticleFSP> fsps; ///< other finalstate particles 

      SRTrueParticle();
      ~SRTrueParticle(){  };

    };

} // end namespace

#endif // SRTRUEPARTICLE_H
//////////////////////////////////////////////////////////////////////////////
