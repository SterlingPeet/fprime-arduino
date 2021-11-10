// ======================================================================
// \title  RateMultiplexer/test/ut/GTestBase.cpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  base tester class for the rate multiplexer
// ======================================================================

#include "GTestBase.hpp"

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  RateMultiplexerGTestBase ::
    RateMultiplexerGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
        RateMultiplexerTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  RateMultiplexerGTestBase ::
    ~RateMultiplexerGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // Commands
  // ----------------------------------------------------------------------

  void RateMultiplexerGTestBase ::
    assertCmdResponse_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ((unsigned long) size, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of command response history\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->cmdResponseHistory->size() << "\n";
  }

  void RateMultiplexerGTestBase ::
    assertCmdResponse(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
    const
  {
    ASSERT_LT(__index, this->cmdResponseHistory->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into command response history\n"
      << "  Expected: Less than size of command response history ("
      << this->cmdResponseHistory->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const CmdResponse& e = this->cmdResponseHistory->at(__index);
    ASSERT_EQ(opCode, e.opCode)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Opcode at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << opCode << "\n"
      << "  Actual:   " << e.opCode << "\n";
    ASSERT_EQ(cmdSeq, e.cmdSeq)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Command sequence number at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << cmdSeq << "\n"
      << "  Actual:   " << e.cmdSeq << "\n";
    ASSERT_EQ(response, e.response)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Command response at index "
      << __index
      << " in command response history\n"
      << "  Expected: " << response << "\n"
      << "  Actual:   " << e.response << "\n";
  }

  // ----------------------------------------------------------------------
  // Events
  // ----------------------------------------------------------------------

  void RateMultiplexerGTestBase ::
    assertEvents_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventsSize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all event histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventsSize << "\n";
  }

  // ----------------------------------------------------------------------
  // Event: RATE_CHANGE
  // ----------------------------------------------------------------------

  void RateMultiplexerGTestBase ::
    assertEvents_RATE_CHANGE_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->eventHistory_RATE_CHANGE->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for event RATE_CHANGE\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->eventHistory_RATE_CHANGE->size() << "\n";
  }

  void RateMultiplexerGTestBase ::
    assertEvents_RATE_CHANGE(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 __index,
        const Component TargetComponent_evt,
        const RateGroup TargetRateGroup_evt
    ) const
  {
    ASSERT_GT(this->eventHistory_RATE_CHANGE->size(), __index)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Index into history of event RATE_CHANGE\n"
      << "  Expected: Less than size of history ("
      << this->eventHistory_RATE_CHANGE->size() << ")\n"
      << "  Actual:   " << __index << "\n";
    const EventEntry_RATE_CHANGE& e =
      this->eventHistory_RATE_CHANGE->at(__index);
    ASSERT_EQ(TargetComponent_evt, e.TargetComponent_evt)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument TargetComponent_evt at index "
      << __index
      << " in history of event RATE_CHANGE\n"
      << "  Expected: " << TargetComponent_evt << "\n"
      << "  Actual:   " << e.TargetComponent_evt << "\n";
    ASSERT_EQ(TargetRateGroup_evt, e.TargetRateGroup_evt)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Value of argument TargetRateGroup_evt at index "
      << __index
      << " in history of event RATE_CHANGE\n"
      << "  Expected: " << TargetRateGroup_evt << "\n"
      << "  Actual:   " << e.TargetRateGroup_evt << "\n";
  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void RateMultiplexerGTestBase ::
    assertFromPortHistory_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize)
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all from port histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: OutputLedBlinker
  // ----------------------------------------------------------------------

  void RateMultiplexerGTestBase ::
    assert_from_OutputLedBlinker_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_OutputLedBlinker->size())
      << "\n"
      << "  File:     " << __callSiteFileName << "\n"
      << "  Line:     " << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_OutputLedBlinker\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_OutputLedBlinker->size() << "\n";
  }

} // end namespace Arduino
