////////////////////////////////////////////////////////////////////////
// \file    SRTrueParticleFSP.h
////////////////////////////////////////////////////////////////////////
#ifndef SRTRUEPARTICLEFSP_H
#define SRTRUEPARTICLEFSP_H

#include <cstdint>

#include "sbncode/StandardRecord/SRVector3D.h"

#include "sbncode/StandardRecord/SREnums.h"

/* #include "SRVector3D.h" */

namespace caf
{
  /// Representation of a simb::MCParticle, knows energy, direction,
  // etc, but no hit information.
  class SRTrueParticleFSP
    {
    public:
      
      int pdg;
      float energy;
      SRVector3D momentum;
      SRVector3D start; 
      SRVector3D end; 
      genie_status_ status_code;
      int rescatter;
      bool is_primary;
        
      SRTrueParticleFSP();
      ~SRTrueParticleFSP(){  }

    };

} // end namespace

#endif // SRTRUEPARTICLEFSP_H
//////////////////////////////////////////////////////////////////////////////
