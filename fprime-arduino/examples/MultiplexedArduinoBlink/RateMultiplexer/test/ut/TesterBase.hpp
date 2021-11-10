// ======================================================================
// \title  RateMultiplexer/test/ut/TesterBase.hpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  base tester class
// ======================================================================

#ifndef RateMultiplexer_TESTER_BASE_HPP
#define RateMultiplexer_TESTER_BASE_HPP

#include <ATmega/examples/MultiplexedArduinoBlink/RateMultiplexer/RateMultiplexerComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <stdio.h>
#include <Fw/Port/InputSerializePort.hpp>

namespace Arduino {

  //! \class RateMultiplexerTesterBase
  //! \brief Auto-generated base class for RateMultiplexer component test harness
  //!
  class RateMultiplexerTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object RateMultiplexerTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect Input10Hz to to_Input10Hz[portNum]
      //!
      void connect_to_Input10Hz(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const Input10Hz /*!< The port*/
      );

      //! Connect ChangeRatePort to to_ChangeRatePort[portNum]
      //!
      void connect_to_ChangeRatePort(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Arduino::InputChangeTimerPort *const ChangeRatePort /*!< The port*/
      );

      //! Connect CmdDisp to to_CmdDisp[portNum]
      //!
      void connect_to_CmdDisp(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::InputCmdPort *const CmdDisp /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from OutputLedBlinker
      //!
      //! \return from_OutputLedBlinker[portNum]
      //!
      Svc::InputSchedPort* get_from_OutputLedBlinker(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from CmdStatus
      //!
      //! \return from_CmdStatus[portNum]
      //!
      Fw::InputCmdResponsePort* get_from_CmdStatus(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from CmdReg
      //!
      //! \return from_CmdReg[portNum]
      //!
      Fw::InputCmdRegPort* get_from_CmdReg(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from ParamGet
      //!
      //! \return from_ParamGet[portNum]
      //!
      Fw::InputPrmGetPort* get_from_ParamGet(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from ParamSet
      //!
      //! \return from_ParamSet[portNum]
      //!
      Fw::InputPrmSetPort* get_from_ParamSet(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from Time
      //!
      //! \return from_Time[portNum]
      //!
      Fw::InputTimePort* get_from_Time(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from Log
      //!
      //! \return from_Log[portNum]
      //!
      Fw::InputLogPort* get_from_Log(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the port that receives input from LogText
      //!
      //! \return from_LogText[portNum]
      //!
      Fw::InputLogTextPort* get_from_LogText(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );
#endif

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object RateMultiplexerTesterBase
      //!
      RateMultiplexerTesterBase(
#if FW_OBJECT_NAMES == 1
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
#else
          const U32 maxHistorySize /*!< The maximum size of each history*/
#endif
      );

      //! Destroy object RateMultiplexerTesterBase
      //!
      virtual ~RateMultiplexerTesterBase(void);

      // ----------------------------------------------------------------------
      // Test history
      // ----------------------------------------------------------------------

    protected:

      //! \class History
      //! \brief A history of port inputs
      //!
      template <typename T> class History {

        public:

          //! Create a History
          //!
          History(
              const U32 maxSize /*!< The maximum history size*/
          ) :
              numEntries(0),
              maxSize(maxSize)
          {
            this->entries = new T[maxSize];
          }

          //! Destroy a History
          //!
          ~History() {
            delete[] this->entries;
          }

          //! Clear the history
          //!
          void clear() { this->numEntries = 0; }

          //! Push an item onto the history
          //!
          void push_back(
              T entry /*!< The item*/
          ) {
            FW_ASSERT(this->numEntries < this->maxSize);
            entries[this->numEntries++] = entry;
          }

          //! Get an item at an index
          //!
          //! \return The item at index i
          //!
          T at(
              const U32 i /*!< The index*/
          ) const {
            FW_ASSERT(i < this->numEntries);
            return entries[i];
          }

          //! Get the number of entries in the history
          //!
          //! \return The number of entries in the history
          //!
          U32 size(void) const { return this->numEntries; }

        private:

          //! The number of entries in the history
          //!
          U32 numEntries;

          //! The maximum history size
          //!
          const U32 maxSize;

          //! The entries
          //!
          T *entries;

      };

      //! Clear all history
      //!
      void clearHistory(void);

    protected:

      // ----------------------------------------------------------------------
      // Handler prototypes for typed from ports
      // ----------------------------------------------------------------------

      //! Handler prototype for from_OutputLedBlinker
      //!
      virtual void from_OutputLedBlinker_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      ) = 0;

      //! Handler base function for from_OutputLedBlinker
      //!
      void from_OutputLedBlinker_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Histories for typed from ports
      // ----------------------------------------------------------------------

      //! Clear from port history
      //!
      void clearFromPortHistory(void);

      //! The total number of from port entries
      //!
      U32 fromPortHistorySize;

      //! Push an entry on the history for from_OutputLedBlinker
      void pushFromPortEntry_OutputLedBlinker(
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! A history entry for from_OutputLedBlinker
      //!
      typedef struct {
        NATIVE_UINT_TYPE context;
      } FromPortEntry_OutputLedBlinker;

      //! The history for from_OutputLedBlinker
      //!
      History<FromPortEntry_OutputLedBlinker>
        *fromPortHistory_OutputLedBlinker;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to Input10Hz
      //!
      void invoke_to_Input10Hz(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Invoke the to port connected to ChangeRatePort
      //!
      void invoke_to_ChangeRatePort(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          RateGroup InputRate, 
          Component TargetComponent 
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of to_Input10Hz ports
      //!
      //! \return The number of to_Input10Hz ports
      //!
      NATIVE_INT_TYPE getNum_to_Input10Hz(void) const;

      //! Get the number of from_OutputLedBlinker ports
      //!
      //! \return The number of from_OutputLedBlinker ports
      //!
      NATIVE_INT_TYPE getNum_from_OutputLedBlinker(void) const;

      //! Get the number of to_ChangeRatePort ports
      //!
      //! \return The number of to_ChangeRatePort ports
      //!
      NATIVE_INT_TYPE getNum_to_ChangeRatePort(void) const;

      //! Get the number of to_CmdDisp ports
      //!
      //! \return The number of to_CmdDisp ports
      //!
      NATIVE_INT_TYPE getNum_to_CmdDisp(void) const;

      //! Get the number of from_CmdStatus ports
      //!
      //! \return The number of from_CmdStatus ports
      //!
      NATIVE_INT_TYPE getNum_from_CmdStatus(void) const;

      //! Get the number of from_CmdReg ports
      //!
      //! \return The number of from_CmdReg ports
      //!
      NATIVE_INT_TYPE getNum_from_CmdReg(void) const;

      //! Get the number of from_ParamGet ports
      //!
      //! \return The number of from_ParamGet ports
      //!
      NATIVE_INT_TYPE getNum_from_ParamGet(void) const;

      //! Get the number of from_ParamSet ports
      //!
      //! \return The number of from_ParamSet ports
      //!
      NATIVE_INT_TYPE getNum_from_ParamSet(void) const;

      //! Get the number of from_Time ports
      //!
      //! \return The number of from_Time ports
      //!
      NATIVE_INT_TYPE getNum_from_Time(void) const;

      //! Get the number of from_Log ports
      //!
      //! \return The number of from_Log ports
      //!
      NATIVE_INT_TYPE getNum_from_Log(void) const;

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Get the number of from_LogText ports
      //!
      //! \return The number of from_LogText ports
      //!
      NATIVE_INT_TYPE getNum_from_LogText(void) const;
#endif

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_Input10Hz[portNum] is connected
      //!
      bool isConnected_to_Input10Hz(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_ChangeRatePort[portNum] is connected
      //!
      bool isConnected_to_ChangeRatePort(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_CmdDisp[portNum] is connected
      //!
      bool isConnected_to_CmdDisp(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      // ----------------------------------------------------------------------
      // Functions for sending commands
      // ----------------------------------------------------------------------

    protected:

      // send command buffers directly - used for intentional command encoding errors
      void sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args);

      //! Send a change_rate command
      //!
      void sendCmd_change_rate(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq, /*!< The command sequence number*/
          Component TargetComponent_comm, /*!< Target Component Changing Rates*/
          RateGroup TargetRateGroup_comm /*!< Target Component Changing Rates*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Command response handling
      // ----------------------------------------------------------------------

      //! Handle a command response
      //!
      virtual void cmdResponseIn(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CommandResponse response /*!< The command response*/
      );

      //! A type representing a command response
      //!
      typedef struct {
        FwOpcodeType opCode;
        U32 cmdSeq;
        Fw::CommandResponse response;
      } CmdResponse;

      //! The command response history
      //!
      History<CmdResponse> *cmdResponseHistory;

    protected:

      // ----------------------------------------------------------------------
      // Event dispatch
      // ----------------------------------------------------------------------

      //! Dispatch an event
      //!
      void dispatchEvents(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::LogSeverity severity, /*!< The severity*/
          Fw::LogBuffer& args /*!< The serialized arguments*/
      );

      //! Clear event history
      //!
      void clearEvents(void);

      //! The total number of events seen
      //!
      U32 eventsSize;

#if FW_ENABLE_TEXT_LOGGING

    protected:

      // ----------------------------------------------------------------------
      // Text events
      // ----------------------------------------------------------------------

      //! Handle a text event
      //!
      virtual void textLogIn(
          const FwEventIdType id, /*!< The event ID*/
          Fw::Time& timeTag, /*!< The time*/
          const Fw::TextLogSeverity severity, /*!< The severity*/
          const Fw::TextLogString& text /*!< The event string*/
      );

      //! A history entry for the text log
      //!
      typedef struct {
        U32 id;
        Fw::Time timeTag;
        Fw::TextLogSeverity severity;
        Fw::TextLogString text;
      } TextLogEntry;

      //! The history of text log events
      //!
      History<TextLogEntry> *textLogHistory;

      //! Print a text log history entry
      //!
      static void printTextLogHistoryEntry(
          const TextLogEntry& e,
          FILE* file
      );

      //! Print the text log history
      //!
      void printTextLogHistory(FILE *const file);

#endif

    protected:

      // ----------------------------------------------------------------------
      // Event: RATE_CHANGE
      // ----------------------------------------------------------------------

      //! Handle event RATE_CHANGE
      //!
      virtual void logIn_ACTIVITY_LO_RATE_CHANGE(
          Component TargetComponent_evt, /*!< Target Component Changing Rates*/
          RateGroup TargetRateGroup_evt /*!< Target Component Changing Rates*/
      );

      //! A history entry for event RATE_CHANGE
      //!
      typedef struct {
        Component TargetComponent_evt;
        RateGroup TargetRateGroup_evt;
      } EventEntry_RATE_CHANGE;

      //! The history of RATE_CHANGE events
      //!
      History<EventEntry_RATE_CHANGE>
        *eventHistory_RATE_CHANGE;

    protected:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Set the test time for events and telemetry
      //!
      void setTestTime(
          const Fw::Time& timeTag /*!< The time*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Parameter: LedBlinkComponentGroup
      // ----------------------------------------------------------------------

      void paramSet_LedBlinkComponentGroup(
          const RateGroup& val, /*!< The parameter value*/
          Fw::ParamValid valid /*!< The parameter valid flag*/
      );

      void paramSend_LedBlinkComponentGroup(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

      void paramSave_LedBlinkComponentGroup(
          const NATIVE_INT_TYPE instance, /*!< The instance number*/
          const U32 cmdSeq /*!< The command sequence number*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to Input10Hz
      //!
      Svc::OutputSchedPort m_to_Input10Hz[1];

      //! To port connected to ChangeRatePort
      //!
      Arduino::OutputChangeTimerPort m_to_ChangeRatePort[1];

      //! To port connected to CmdDisp
      //!
      Fw::OutputCmdPort m_to_CmdDisp[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to OutputLedBlinker
      //!
      Svc::InputSchedPort m_from_OutputLedBlinker[1];

      //! From port connected to CmdStatus
      //!
      Fw::InputCmdResponsePort m_from_CmdStatus[1];

      //! From port connected to CmdReg
      //!
      Fw::InputCmdRegPort m_from_CmdReg[1];

      //! From port connected to ParamGet
      //!
      Fw::InputPrmGetPort m_from_ParamGet[1];

      //! From port connected to ParamSet
      //!
      Fw::InputPrmSetPort m_from_ParamSet[1];

      //! From port connected to Time
      //!
      Fw::InputTimePort m_from_Time[1];

      //! From port connected to Log
      //!
      Fw::InputLogPort m_from_Log[1];

#if FW_ENABLE_TEXT_LOGGING == 1
      //! From port connected to LogText
      //!
      Fw::InputLogTextPort m_from_LogText[1];
#endif

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_OutputLedBlinker
      //!
      static void from_OutputLedBlinker_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! Static function for port from_CmdStatus
      //!
      static void from_CmdStatus_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode, /*!< Command Op Code*/
          U32 cmdSeq, /*!< Command Sequence*/
          Fw::CommandResponse response /*!< The command response argument*/
      );

      //! Static function for port from_CmdReg
      //!
      static void from_CmdReg_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwOpcodeType opCode /*!< Command Op Code*/
      );

      //! Static function for port from_ParamGet
      //!
      static Fw::ParamValid from_ParamGet_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwPrmIdType id, /*!< Parameter ID*/
          Fw::ParamBuffer &val /*!< Buffer containing serialized parameter value*/
      );

      //! Static function for port from_ParamSet
      //!
      static void from_ParamSet_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwPrmIdType id, /*!< Parameter ID*/
          Fw::ParamBuffer &val /*!< Buffer containing serialized parameter value*/
      );

      //! Static function for port from_Time
      //!
      static void from_Time_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< The U32 cmd argument*/
      );

      //! Static function for port from_Log
      //!
      static void from_Log_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::LogSeverity severity, /*!< The severity argument*/
          Fw::LogBuffer &args /*!< Buffer containing serialized log entry*/
      );

#if FW_ENABLE_TEXT_LOGGING == 1
      //! Static function for port from_LogText
      //!
      static void from_LogText_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwEventIdType id, /*!< Log ID*/
          Fw::Time &timeTag, /*!< Time Tag*/
          Fw::TextLogSeverity severity, /*!< The severity argument*/
          Fw::TextLogString &text /*!< Text of log message*/
      );
#endif

    private:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Test time stamp
      //!
      Fw::Time m_testTime;

    private:

      // ----------------------------------------------------------------------
      // Parameter validity flags
      // ----------------------------------------------------------------------

      //! True if parameter LedBlinkComponentGroup was successfully received
      //!
      Fw::ParamValid m_param_LedBlinkComponentGroup_valid;

    private:

      // ----------------------------------------------------------------------
      // Parameter variables
      // ----------------------------------------------------------------------

      //! Parameter LedBlinkComponentGroup
      //!
      RateGroup m_param_LedBlinkComponentGroup;

  };

} // end namespace Arduino

#endif
