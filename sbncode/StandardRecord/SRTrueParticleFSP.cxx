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
    pdg(-999),
    energy(std::numeric_limits<float>::signaling_NaN()),
    momentum(std::numeric_limits<float>::signaling_NaN()),
    start(std::numeric_limits<float>::signaling_NaN()),
    status_code(kIStUndefined),
    rescatter(-999)
  {  }

} // end namespace caf
////////////////////////////////////////////////////////////////////////
