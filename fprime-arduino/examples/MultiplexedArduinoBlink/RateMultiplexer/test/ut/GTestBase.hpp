// ======================================================================
// \title  RateMultiplexer/test/ut/GTestBase.hpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  base tester class for the rate multiplexer
// ======================================================================

#ifndef RateMultiplexer_GTEST_BASE_HPP
#define RateMultiplexer_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for command history assertions
// ----------------------------------------------------------------------

#define ASSERT_CMD_RESPONSE_SIZE(size) \
  this->assertCmdResponse_size(__FILE__, __LINE__, size)

#define ASSERT_CMD_RESPONSE(index, opCode, cmdSeq, response) \
  this->assertCmdResponse(__FILE__, __LINE__, index, opCode, cmdSeq, response)

// ----------------------------------------------------------------------
// Macros for event history assertions
// ----------------------------------------------------------------------

#define ASSERT_EVENTS_SIZE(size) \
  this->assertEvents_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_RATE_CHANGE_SIZE(size) \
  this->assertEvents_RATE_CHANGE_size(__FILE__, __LINE__, size)

#define ASSERT_EVENTS_RATE_CHANGE(index, _TargetComponent_evt, _TargetRateGroup_evt) \
  this->assertEvents_RATE_CHANGE(__FILE__, __LINE__, index, _TargetComponent_evt, _TargetRateGroup_evt)

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_OutputLedBlinker_SIZE(size) \
  this->assert_from_OutputLedBlinker_size(__FILE__, __LINE__, size)

#define ASSERT_from_OutputLedBlinker(index, _context) \
  { \
    ASSERT_GT(this->fromPortHistory_OutputLedBlinker->size(), static_cast<U32>(index)) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Index into history of from_OutputLedBlinker\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_OutputLedBlinker->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_OutputLedBlinker& _e = \
      this->fromPortHistory_OutputLedBlinker->at(index); \
    ASSERT_EQ(_context, _e.context) \
    << "\n" \
    << "  File:     " << __FILE__ << "\n" \
    << "  Line:     " << __LINE__ << "\n" \
    << "  Value:    Value of argument context at index " \
    << index \
    << " in history of from_OutputLedBlinker\n" \
    << "  Expected: " << _context << "\n" \
    << "  Actual:   " << _e.context << "\n"; \
  }

namespace Arduino {

  //! \class RateMultiplexerGTestBase
  //! \brief Auto-generated base class for RateMultiplexer component Google Test harness
  //!
  class RateMultiplexerGTestBase :
    public RateMultiplexerTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object RateMultiplexerGTestBase
      //!
      RateMultiplexerGTestBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object RateMultiplexerGTestBase
      //!
      virtual ~RateMultiplexerGTestBase(void);

    protected:

      // ----------------------------------------------------------------------
      // Commands
      // ----------------------------------------------------------------------

      //! Assert size of command response history
      //!
      void assertCmdResponse_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      //! Assert command response in history at index
      //!
      void assertCmdResponse(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Events
      // ----------------------------------------------------------------------

      void assertEvents_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Event: RATE_CHANGE
      // ----------------------------------------------------------------------

      void assertEvents_RATE_CHANGE_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

      void assertEvents_RATE_CHANGE(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 __index, /*!< The index*/
          const Component TargetComponent_evt, /*!< Target Component Changing Rates*/
          const RateGroup TargetRateGroup_evt /*!< Target Component Changing Rates*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      void assertFromPortHistory_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: OutputLedBlinker
      // ----------------------------------------------------------------------

      void assert_from_OutputLedBlinker_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace Arduino

#endif
