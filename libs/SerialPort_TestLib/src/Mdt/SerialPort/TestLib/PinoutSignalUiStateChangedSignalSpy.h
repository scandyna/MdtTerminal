// SPDX-License-Identifier: LGPL-3.0-or-later
/****************************************************************************************
 **
 ** MdtSerialPort
 ** Provides some functionality to configure and interact with serial ports.
 **
 ** Copyright (C) 2025-2025 Philippe Steinmann.
 **
 *****************************************************************************************/
#ifndef MDT_SERIAL_PORT_TEST_LIB_PINOUT_SIGNAL_UI_STATE_CHANGED_SIGNAL_SPY_H
#define MDT_SERIAL_PORT_TEST_LIB_PINOUT_SIGNAL_UI_STATE_CHANGED_SIGNAL_SPY_H

#include "Mdt/SerialPort/AbstractPinoutSignalsUiController.h"
#include "mdt_serialport_testlib_export.h"
#include <QObject>
#include <vector>
#include <cassert>

namespace Mdt{ namespace SerialPort{ namespace TestLib{

  /*! \brief Helper class to test an UI pinout signal state changed signal
   *
   * \code
   * TestPinoutSignalsUiController psc;
   * PinoutSignalUiStateChangedSignalSpy receiveDataChangedSpy(&psc, &TestPinoutSignalsUiController::receiveDataChanged);
   *
   * // Do stuff on psc ..
   *
   * REQUIRE( receiveDataChangedSpy.count() == 1 );
   * CHECK( receiveDataChangedSpy.stateAtIsOn(0) );
   * \endcode
   */
  class MDT_SERIALPORT_TESTLIB_EXPORT PinoutSignalUiStateChangedSignalSpy : public QObject
  {
    Q_OBJECT

   public:

    /*! \brief Constructor
     */
    template <typename PointerToMemberFunction>
    explicit
    PinoutSignalUiStateChangedSignalSpy(AbstractPinoutSignalsUiController *controller, PointerToMemberFunction sig, QObject *parent = nullptr)
     : QObject(parent)
    {
      assert(controller != nullptr);

      connect(controller, sig, this, &PinoutSignalUiStateChangedSignalSpy::appendStateIsOnChanged);
    }

    /*! \brief Get the count of signals this spy has collected
     */
    size_t count() const noexcept
    {
      return mStateList.size();
    }

    /*! \brief Get the state at given index
     *
     * \pre \a index must be in range
     */
    bool stateAtIsOn(size_t index) const noexcept
    {
      assert( index < count() );

      return mStateList[index];
    }

    /*! \brief Clear this spy
     */
    void clear() noexcept;

   private Q_SLOTS:

    void appendStateIsOnChanged(bool on);

   private:

    std::vector<bool> mStateList;
  };

}}} // namespace Mdt{ namespace SerialPort{ namespace TestLib{

#endif // #ifndef MDT_SERIAL_PORT_TEST_LIB_PINOUT_SIGNAL_UI_STATE_CHANGED_SIGNAL_SPY_H
