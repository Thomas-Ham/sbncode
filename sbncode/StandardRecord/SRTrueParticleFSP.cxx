////////////////////////////////////////////////////////////////////////
// \file    SRTrueParticleFSP.cxx
// \brief   An SRTrueParticleFSP is a high level true track object. It
//          knows true id, direction, length, but  no hit information.
////////////////////////////////////////////////////////////////////////
#include "sbncode/StandardRecord/SRTrueParticleFSP.h"
#include <climits>

namespace caf
{
  SRTrueParticleFSP::SRTrueParticleFSP():
    pdg(INT_MIN),
    energy(std::numeric_limits<float>::signaling_NaN()),
    gstatus(kIStUndefined),
    rescatter(INT_MIN)
  {  }

} // end namespace caf
////////////////////////////////////////////////////////////////////////
