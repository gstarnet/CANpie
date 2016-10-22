//============================================================================//
// File:          qcan_frame.cpp                                              //
// Description:   QCAN classes - CAN frame                                    //
// Author:        Uwe Koppe                                                   //
// e-mail:        koppe@microcontrol.net                                      //
//                                                                            //
// Copyright (C) MicroControl GmbH & Co. KG                                   //
// Junkersring 23                                                             //
// 53844 Troisdorf                                                            //
// Germany                                                                    //
// Tel: +49-2241-25659-0                                                      //
// Fax: +49-2241-25659-11                                                     //
//                                                                            //
// The copyright to the computer program(s) herein is the property of         //
// MicroControl GmbH & Co. KG, Germany. The program(s) may be used            //
// and/or copied only with the written permission of MicroControl GmbH &      //
// Co. KG or in accordance with the terms and conditions stipulated in        //
// the agreement/contract under which the program(s) have been supplied.      //
//----------------------------------------------------------------------------//
//                                                                            //
// Date        History                                                        //
// ----------  -------------------------------------------------------------- //
// 20.05.2015  Initial version                                                //
//                                                                            //
//============================================================================//



#ifndef TEST_CANPIE_TIMESTAMP_HPP_
#define TEST_CANPIE_TIMESTAMP_HPP_


#include <QTest>
#include "canpie_timestamp.hpp"


//-----------------------------------------------------------------------------
/*!
** \class   TestCpTimestamp
** \brief   Test CANpie timestamp
** 
*/
class TestCpTimestamp : public QObject
{
   Q_OBJECT

public:
   
   TestCpTimestamp();
   
   
   ~TestCpTimestamp();

private:
   

private slots:

   void initTestCase();
   
   void checkValueRange();

   void cleanupTestCase();
};




#endif   // TEST_QCAN_FRAME_HPP_

