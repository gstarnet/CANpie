//============================================================================//
// File:          test:qcan_frame.cpp                                         //
// Description:   QCAN classes - Test QCan frame                              //
//                                                                            //
// Copyright (C) MicroControl GmbH & Co. KG                                   //
// 53842 Troisdorf - Germany                                                  //
// www.microcontrol.net                                                       //
//                                                                            //
//----------------------------------------------------------------------------//
// Redistribution and use in source and binary forms, with or without         //
// modification, are permitted provided that the following conditions         //
// are met:                                                                   //
// 1. Redistributions of source code must retain the above copyright          //
//    notice, this list of conditions, the following disclaimer and           //
//    the referenced file 'COPYING'.                                          //
// 2. Redistributions in binary form must reproduce the above copyright       //
//    notice, this list of conditions and the following disclaimer in the     //
//    documentation and/or other materials provided with the distribution.    //
// 3. Neither the name of MicroControl nor the names of its contributors      //
//    may be used to endorse or promote products derived from this software   //
//    without specific prior written permission.                              //
//                                                                            //
// Provided that this notice is retained in full, this software may be        //
// distributed under the terms of the GNU Lesser General Public License       //
// ("LGPL") version 3 as distributed in the 'COPYING' file.                   //
//                                                                            //
//============================================================================//


#include "test_qcan_frame.hpp"


TestQCanFrame::TestQCanFrame()
{

}


TestQCanFrame::~TestQCanFrame()
{

}


//----------------------------------------------------------------------------//
// initTestCase()                                                             //
// prepare test cases                                                         //
//----------------------------------------------------------------------------//
void TestQCanFrame::initTestCase()
{
   pclCanStdP = new QCanFrame(QCanFrame::eTYPE_CAN_STD);
   pclCanExtP = new QCanFrame(QCanFrame::eTYPE_CAN_EXT);
   pclFdStdP  = new QCanFrame(QCanFrame::eTYPE_FD_STD);
   pclFdExtP  = new QCanFrame(QCanFrame::eTYPE_FD_EXT);

   pclFrameP  = new QCanFrame();
}


//----------------------------------------------------------------------------//
// checkFrameType()                                                           //
// check frame types                                                          //
//----------------------------------------------------------------------------//
void TestQCanFrame::checkFrameType()
{
   QVERIFY(pclCanStdP->frameType() == QCanFrame::eTYPE_CAN_STD);
   QVERIFY(pclCanExtP->frameType() == QCanFrame::eTYPE_CAN_EXT);
   QVERIFY(pclFdStdP->frameType()  == QCanFrame::eTYPE_FD_STD);
   QVERIFY(pclFdExtP->frameType()  == QCanFrame::eTYPE_FD_EXT);
}


//----------------------------------------------------------------------------//
// checkFrameId()                                                             //
// check frame identifier                                                     //
//----------------------------------------------------------------------------//
void TestQCanFrame::checkFrameId()
{
   uint32_t ulIdValueT;

   for(ulIdValueT = 0; ulIdValueT <= 0x0000FFFF; ulIdValueT++)
   {
      pclCanStdP->setStdId((uint16_t)ulIdValueT);
      pclCanExtP->setExtId(ulIdValueT);

      *pclFrameP = *pclCanStdP;
      if(ulIdValueT <= 0x07FF)
      {
         QVERIFY(pclCanStdP->identifier() == ulIdValueT);
         QVERIFY(pclFrameP->identifier()  == ulIdValueT);
      }
      else
      {
         QVERIFY(pclCanStdP->identifier() == (ulIdValueT & 0x07FF));
         QVERIFY(pclFrameP->identifier()  == (ulIdValueT & 0x07FF));
      }
      QVERIFY(pclCanExtP->identifier() == ulIdValueT);

      QVERIFY(pclCanStdP->isExtended() == 0);
      QVERIFY(pclFrameP->isExtended()  == 0);
   }
}


//----------------------------------------------------------------------------//
// checkFrameDlc()                                                            //
// check frame DLC                                                            //
//----------------------------------------------------------------------------//
void TestQCanFrame::checkFrameDlc()
{

}


//----------------------------------------------------------------------------//
// checkFrameData()                                                           //
// check frame data                                                           //
//----------------------------------------------------------------------------//
void TestQCanFrame::checkFrameData()
{
   pclCanStdP->setDlc(4);
   pclCanStdP->setData(0, 0x12);
   pclCanStdP->setData(1, 0x34);
   pclCanStdP->setData(2, 0x56);
   pclCanStdP->setData(3, 0x78);
   
   QVERIFY(pclCanStdP->dataUInt16(0, 1) == 0x1234);
   QVERIFY(pclCanStdP->dataUInt16(1, 1) == 0x3456);
   QVERIFY(pclCanStdP->dataUInt16(2, 1) == 0x5678);
   QVERIFY(pclCanStdP->dataUInt16(3, 1) == 0x0000);

   QVERIFY(pclCanStdP->dataUInt32(0, 1) == 0x12345678);

   pclCanStdP->setDataUInt16(0, 0xAABB);
   QVERIFY(pclCanStdP->data(0) == 0xBB);
   QVERIFY(pclCanStdP->data(1) == 0xAA);
   QVERIFY(pclCanStdP->dataUInt16(0, 0) == 0xAABB);

}


void TestQCanFrame::checkFrameRemote()
{

}

void TestQCanFrame::checkByteArray()
{
   QByteArray  clByteArrayT;

   for(uint8_t ubCntT = 0; ubCntT < 9; ubCntT++)
   {
      pclCanStdP->setStdId(0x301 + ubCntT);
      pclCanStdP->setDlc(ubCntT);
      pclCanStdP->setData(0, ubCntT);
      pclCanStdP->setData(1, 0x10 + ubCntT);
      pclCanStdP->setData(2, 0x20 + ubCntT);
      pclCanStdP->setData(3, 0x30 + ubCntT);
      pclCanStdP->setData(4, 0x40 + ubCntT);
      pclCanStdP->setData(5, 0x50 + ubCntT);
      pclCanStdP->setData(6, 0x60 + ubCntT);
      pclCanStdP->setData(7, 0x70 + ubCntT);

      pclCanStdP->setMarker(0x223344);
      pclCanStdP->setUser(0xAB1023);

      clByteArrayT = pclCanStdP->toByteArray();

      QVERIFY(pclFrameP->fromByteArray(clByteArrayT) == true);

      QVERIFY(pclFrameP->identifier() == (0x301 + ubCntT));
      QVERIFY(pclFrameP->dlc()   == (ubCntT));
      if(ubCntT == 4)
      {
         QVERIFY(pclFrameP->data(0) == (ubCntT));
         QVERIFY(pclFrameP->data(1) == (0x10 + ubCntT));
         QVERIFY(pclFrameP->data(2) == (0x20 + ubCntT));
         QVERIFY(pclFrameP->data(3) == (0x30 + ubCntT));
         QVERIFY(pclFrameP->data(4) == 0);
      }

   }
}

//----------------------------------------------------------------------------//
// cleanupTestCase()                                                          //
// cleanup test cases                                                         //
//----------------------------------------------------------------------------//

void TestQCanFrame::cleanupTestCase()
{
   delete(pclCanStdP);
   delete(pclCanExtP);
   delete(pclFdStdP);
   delete(pclFdExtP);

   delete(pclFrameP);
}

