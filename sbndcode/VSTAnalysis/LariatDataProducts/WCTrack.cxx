////////////////////////////////////////////////////////////////////////
// $Id: WCTrack.cxx,v 1.00 2015/06/03 16:04:20 linehan3 Exp $
//
// WCTrack class
//
// rlinehan@stanford.edu
//
////////////////////////////////////////////////////////////////////////

#include "WCTrack.h"
#include "cetlib/exception.h"

namespace ldp{

  //----------------------------------------------------------------------
  WCTrack::WCTrack() 
  {
    std::vector<int> blank1;
    std::vector<float> blank2;
    fMomentum = 0;
    fMomentum2M = 0;
    fYKink = 0;
    for( int i = 0; i < 3 ; ++i )
      fDeltaDist[i] = 0;
    for( int i = 0; i < 2 ; ++i )
      fXYFace[i] = 0;
    fTheta = 0;
    fPhi = 0;
    fWC = blank1;
    fHitWire = blank2;
    //fHitTime = blank2;
  }

  //----------------------------------------------------------------------
  WCTrack::WCTrack(float momentum,
		   float yKink,
		   float xDist,
		   float yDist,
		   float zDist,
		   float xFace,
		   float yFace,
		   float theta,
		   float phi,
		   std::vector<int> wcVect,
		   std::vector<float> hitWireVect,
		   float hitPositionVect[4][3],
		   int WCMissed,
		   float residual)
		   //std::vector<float> hitTimeVect )
  { 
    fMomentum = momentum;
    fYKink = yKink;
    fDeltaDist[0] = xDist; fDeltaDist[1] = yDist; fDeltaDist[2] = zDist;
    fXYFace[0] = xFace; fXYFace[1] = yFace;
    fTheta = theta;
    fPhi = phi;
    fWC = wcVect;
    fHitWire = hitWireVect;
    for(int i=0; i<4; ++i){
      for(int j=0; j<3; ++j){
    fHitPosition[i][j]= hitPositionVect[i][j];
      }
    }
    fWCMissed=WCMissed;
    fResidual=residual;
    //fHitTime = hitTimeVect;
  }

  WCTrack::WCTrack(float momentum,
                   float momentum2m,
		   float yKink,
		   float xDist,
		   float yDist,
		   float zDist,
		   float xFace,
		   float yFace,
		   float theta,
		   float phi,
		   std::vector<int> wcVect,
		   std::vector<float> hitWireVect,
		   float hitPositionVect[4][3],
		   int WCMissed,
		   float residual)
		   //std::vector<float> hitTimeVect )
  { 
    fMomentum = momentum;
    fMomentum2M = momentum2m;
    fYKink = yKink;
    fDeltaDist[0] = xDist; fDeltaDist[1] = yDist; fDeltaDist[2] = zDist;
    fXYFace[0] = xFace; fXYFace[1] = yFace;
    fTheta = theta;
    fPhi = phi;
    fWC = wcVect;
    fHitWire = hitWireVect;
    for(int i=0; i<4; ++i){
      for(int j=0; j<3; ++j){
    fHitPosition[i][j]= hitPositionVect[i][j];
      }
    }
    fWCMissed=WCMissed;
    fResidual=residual;
    //fHitTime = hitTimeVect;
  }

  //--------------------------------------------------
float WCTrack::DeltaDist(size_t i) const
{
 if( i >= 3 || i < 0 ){
   throw cet::exception("WCTrack") << "illegal index requested for DeltaDist vector: "
<< i << "\n";
}
return fDeltaDist[i];
}
  
  //--------------------------------------------------
  float WCTrack::XYFace(size_t i) const
  {
    if( i >= 2 || i < 0 ){
      throw cet::exception("WCTrack") << "illegal index requested for XYFace vector: "
				      << i << "\n";
    }
    return fXYFace[i];
  }
 
  //--------------------------------------------------
  int WCTrack::WC(size_t iHit) const
  {
    if( iHit >= fWC.size() ){
      throw cet::exception("WCTrack") << "illegal index requested for WC vector: "
				      << iHit << "\n";
    }
    return fWC[iHit];
  }

  //--------------------------------------------------
  float WCTrack::HitWire(size_t iHit) const
  {
    if( iHit >= fHitWire.size() ){
      throw cet::exception("WCTrack") << "illegal index requested for HitWire vector: "
			 	      << iHit << "\n";
    }
    return fHitWire[iHit];
  }
//=====================================================  
  float WCTrack::HitPosition(int iWC, int iAx) const
  {
    if(iWC >3 ){
      throw cet::exception("WCTrack") <<"illegal WC index requested for HitPosition: "
      				      << iWC << "\n";
    }
    if(iAx >2){
      throw cet::exception("WCTrack") <<"illegal dimension index requested for HitPosition: "
      				      << iAx << "\n";
    }
    return fHitPosition[iWC][iAx];
  }

  //--------------------------------------------------
  //float WCTrack::HitTime(size_t iHit) const
 // {
   // if( iHit >= fHitTime.size() ){
     // throw cet::exception("WCTrack") << "illegal index requested for HitTime vector: "
				     // << iHit << "\n";
 //   }
  //  return fHitTime[iHit];
  //}


}
////////////////////////////////////////////////////////////////////////
