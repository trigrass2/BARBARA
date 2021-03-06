/**
 * \file
 * \brief Header of J2B2 Demo class.
 * \author Antti Maula <antti.maula@tkk.fi>
 */
#ifndef _J2B2_DEMO_HPP_
#define _J2B2_DEMO_HPP_

#include "thread.hpp"
#include "sync.hpp"
#include "J2B2-API.hpp"

class CJ2B2Demo : private gim::CSync, 
                  private gim::CThread
{
public:
  CJ2B2Demo(CJ2B2Client &aClient);
  ~CJ2B2Demo();

  /** Execute hard-co(re|ded) demonstration.
   */
  void Execute(void);

  
  /** Terminate demonstration.
   */
  void Terminate(void);

private:
  /** Types describing current thread handlers.
   */
  enum EThreadImplementation { 
    KThreadSensorsDemo = 0,   ///< Sensors demo
    KThreadInfoDemo    = 1,   ///< Info demo
    KThreadMotionDemo  = 2,   ///< Motion demo
    KThreadCameraDemo  = 3,   ///< Camera demo
    KThreadSDLDemo     = 4    ///< SDL demo
  };


  /** Types describing event types.
   */
  enum ESensorEvent {
    KSensorEventAllClear = 0,       ///< No active sensor events.
    KSensorEventForwardBlocked = 1  ///< Forward dir. blocked.
  };

  CJ2B2Client &iInterface;
  int ThreadFunction(const int aThreadNumber); ///< Incoming data handler function
  int RunSensorsDemo(int aIterations = 1);
  int RunInfoDemo(int aIterations = 1);
  int RunCameraDemo(int aIterations = 1);
  int RunMotionDemo(int aIterations = 1);
  int RunSDLDemo(int aIterations = 1);

  volatile bool iDemoActive;
  volatile bool iPTUDemoActive;

  volatile bool iSensorsThreadActive;
  volatile bool iInfoThreadActive;
  volatile bool iMotionThreadActive;
  volatile bool iCameraThreadActive;
  volatile bool iSDLThreadActive;

  ESensorEvent iCurrentSensorEvent;
  MaCI::Ranging::TDistance iSmallestDistanceToObject;

  MaCI::Image::CImageContainer iLastCameraImage;
  MaCI::Ranging::TDistanceArray iLastLaserDistanceArray;
  
};

#endif
