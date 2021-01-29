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

      SRTrueParticleFSP();
      ~SRTrueParticleFSP(){  }

      int pdg;
      float energy;
      float momentum;
      float start; 
      genie_status_ status_code;
      int rescatter;
      bool is_primary;

    };

} // end namespace

#endif // SRTRUEPARTICLEFSP_H
//////////////////////////////////////////////////////////////////////////////
