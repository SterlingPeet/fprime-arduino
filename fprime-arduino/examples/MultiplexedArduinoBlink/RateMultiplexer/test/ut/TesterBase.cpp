// ======================================================================
// \title  RateMultiplexer/test/ut/TesterBase.cpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  base tester class
// ======================================================================

#include <stdlib.h>
#include <string.h>
#include "TesterBase.hpp"

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  RateMultiplexerTesterBase ::
    RateMultiplexerTesterBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) :
#if FW_OBJECT_NAMES == 1
      Fw::PassiveComponentBase(compName)
#else
      Fw::PassiveComponentBase()
#endif
  {
    // Initialize command history
    this->cmdResponseHistory = new History<CmdResponse>(maxHistorySize);
    // Initialize event histories
#if FW_ENABLE_TEXT_LOGGING
    this->textLogHistory = new History<TextLogEntry>(maxHistorySize);
#endif
    this->eventHistory_RATE_CHANGE =
      new History<EventEntry_RATE_CHANGE>(maxHistorySize);
    // Initialize histories for typed user output ports
    this->fromPortHistory_OutputLedBlinker =
      new History<FromPortEntry_OutputLedBlinker>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  RateMultiplexerTesterBase ::
    ~RateMultiplexerTesterBase(void)
  {
    // Destroy command history
    delete this->cmdResponseHistory;
    // Destroy event histories
#if FW_ENABLE_TEXT_LOGGING
    delete this->textLogHistory;
#endif
    delete this->eventHistory_RATE_CHANGE;
  }

  void RateMultiplexerTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    this->m_param_LedBlinkComponentGroup_valid = Fw::PARAM_UNINIT;

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port OutputLedBlinker

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_OutputLedBlinker();
        ++_port
    ) {

      this->m_from_OutputLedBlinker[_port].init();
      this->m_from_OutputLedBlinker[_port].addCallComp(
          this,
          from_OutputLedBlinker_static
      );
      this->m_from_OutputLedBlinker[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_OutputLedBlinker[%d]",
          this->m_objName,
          _port
      );
      this->m_from_OutputLedBlinker[_port].setObjName(_portName);
#endif

    }

    // Attach input port CmdStatus

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_CmdStatus();
        ++_port
    ) {

      this->m_from_CmdStatus[_port].init();
      this->m_from_CmdStatus[_port].addCallComp(
          this,
          from_CmdStatus_static
      );
      this->m_from_CmdStatus[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_CmdStatus[%d]",
          this->m_objName,
          _port
      );
      this->m_from_CmdStatus[_port].setObjName(_portName);
#endif

    }

    // Attach input port CmdReg

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_CmdReg();
        ++_port
    ) {

      this->m_from_CmdReg[_port].init();
      this->m_from_CmdReg[_port].addCallComp(
          this,
          from_CmdReg_static
      );
      this->m_from_CmdReg[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_CmdReg[%d]",
          this->m_objName,
          _port
      );
      this->m_from_CmdReg[_port].setObjName(_portName);
#endif

    }

    // Attach input port ParamGet

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_ParamGet();
        ++_port
    ) {

      this->m_from_ParamGet[_port].init();
      this->m_from_ParamGet[_port].addCallComp(
          this,
          from_ParamGet_static
      );
      this->m_from_ParamGet[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_ParamGet[%d]",
          this->m_objName,
          _port
      );
      this->m_from_ParamGet[_port].setObjName(_portName);
#endif

    }

    // Attach input port ParamSet

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_ParamSet();
        ++_port
    ) {

      this->m_from_ParamSet[_port].init();
      this->m_from_ParamSet[_port].addCallComp(
          this,
          from_ParamSet_static
      );
      this->m_from_ParamSet[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_ParamSet[%d]",
          this->m_objName,
          _port
      );
      this->m_from_ParamSet[_port].setObjName(_portName);
#endif

    }

    // Attach input port Time

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_Time();
        ++_port
    ) {

      this->m_from_Time[_port].init();
      this->m_from_Time[_port].addCallComp(
          this,
          from_Time_static
      );
      this->m_from_Time[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_Time[%d]",
          this->m_objName,
          _port
      );
      this->m_from_Time[_port].setObjName(_portName);
#endif

    }

    // Attach input port Log

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_Log();
        ++_port
    ) {

      this->m_from_Log[_port].init();
      this->m_from_Log[_port].addCallComp(
          this,
          from_Log_static
      );
      this->m_from_Log[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_Log[%d]",
          this->m_objName,
          _port
      );
      this->m_from_Log[_port].setObjName(_portName);
#endif

    }

    // Attach input port LogText

#if FW_ENABLE_TEXT_LOGGING == 1
    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_from_LogText();
        ++_port
    ) {

      this->m_from_LogText[_port].init();
      this->m_from_LogText[_port].addCallComp(
          this,
          from_LogText_static
      );
      this->m_from_LogText[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_LogText[%d]",
          this->m_objName,
          _port
      );
      this->m_from_LogText[_port].setObjName(_portName);
#endif

    }
#endif

    // Initialize output port Input10Hz

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_Input10Hz();
        ++_port
    ) {
      this->m_to_Input10Hz[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_Input10Hz[%d]",
          this->m_objName,
          _port
      );
      this->m_to_Input10Hz[_port].setObjName(_portName);
#endif

    }

    // Initialize output port ChangeRatePort

    for (
        NATIVE_INT_TYPE _port = 0;
        _port < this->getNum_to_ChangeRatePort();
        ++_port
    ) {
      this->m_to_ChangeRatePort[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_ChangeRatePort[%d]",
          this->m_objName,
          _port
      );
      this->m_to_ChangeRatePort[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_to_Input10Hz(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_Input10Hz);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_OutputLedBlinker(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_OutputLedBlinker);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_to_ChangeRatePort(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_ChangeRatePort);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_to_CmdDisp(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_to_CmdDisp);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_CmdStatus(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_CmdStatus);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_CmdReg(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_CmdReg);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_ParamGet(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_ParamGet);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_ParamSet(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_ParamSet);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_Time(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Time);
  }

  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_Log(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_Log);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  NATIVE_INT_TYPE RateMultiplexerTesterBase ::
    getNum_from_LogText(void) const
  {
    return (NATIVE_INT_TYPE) FW_NUM_ARRAY_ELEMENTS(this->m_from_LogText);
  }
#endif

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    connect_to_Input10Hz(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const Input10Hz
    )
  {
    FW_ASSERT(portNum < this->getNum_to_Input10Hz(),static_cast<AssertArg>(portNum));
    this->m_to_Input10Hz[portNum].addCallPort(Input10Hz);
  }

  void RateMultiplexerTesterBase ::
    connect_to_ChangeRatePort(
        const NATIVE_INT_TYPE portNum,
        Arduino::InputChangeTimerPort *const ChangeRatePort
    )
  {
    FW_ASSERT(portNum < this->getNum_to_ChangeRatePort(),static_cast<AssertArg>(portNum));
    this->m_to_ChangeRatePort[portNum].addCallPort(ChangeRatePort);
  }

  void RateMultiplexerTesterBase ::
    connect_to_CmdDisp(
        const NATIVE_INT_TYPE portNum,
        Fw::InputCmdPort *const CmdDisp
    )
  {
    FW_ASSERT(portNum < this->getNum_to_CmdDisp(),static_cast<AssertArg>(portNum));
    this->m_to_CmdDisp[portNum].addCallPort(CmdDisp);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    invoke_to_Input10Hz(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(portNum < this->getNum_to_Input10Hz(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_Input10Hz(),static_cast<AssertArg>(portNum));
    this->m_to_Input10Hz[portNum].invoke(
        context
    );
  }

  void RateMultiplexerTesterBase ::
    invoke_to_ChangeRatePort(
        const NATIVE_INT_TYPE portNum,
        RateGroup InputRate,
        Component TargetComponent
    )
  {
    FW_ASSERT(portNum < this->getNum_to_ChangeRatePort(),static_cast<AssertArg>(portNum));
    FW_ASSERT(portNum < this->getNum_to_ChangeRatePort(),static_cast<AssertArg>(portNum));
    this->m_to_ChangeRatePort[portNum].invoke(
        InputRate, TargetComponent
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool RateMultiplexerTesterBase ::
    isConnected_to_Input10Hz(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_Input10Hz(), static_cast<AssertArg>(portNum));
    return this->m_to_Input10Hz[portNum].isConnected();
  }

  bool RateMultiplexerTesterBase ::
    isConnected_to_ChangeRatePort(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_ChangeRatePort(), static_cast<AssertArg>(portNum));
    return this->m_to_ChangeRatePort[portNum].isConnected();
  }

  bool RateMultiplexerTesterBase ::
    isConnected_to_CmdDisp(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_CmdDisp(), static_cast<AssertArg>(portNum));
    return this->m_to_CmdDisp[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Svc::InputSchedPort *RateMultiplexerTesterBase ::
    get_from_OutputLedBlinker(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_OutputLedBlinker(),static_cast<AssertArg>(portNum));
    return &this->m_from_OutputLedBlinker[portNum];
  }

  Fw::InputCmdResponsePort *RateMultiplexerTesterBase ::
    get_from_CmdStatus(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_CmdStatus(),static_cast<AssertArg>(portNum));
    return &this->m_from_CmdStatus[portNum];
  }

  Fw::InputCmdRegPort *RateMultiplexerTesterBase ::
    get_from_CmdReg(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_CmdReg(),static_cast<AssertArg>(portNum));
    return &this->m_from_CmdReg[portNum];
  }

  Fw::InputPrmGetPort *RateMultiplexerTesterBase ::
    get_from_ParamGet(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_ParamGet(),static_cast<AssertArg>(portNum));
    return &this->m_from_ParamGet[portNum];
  }

  Fw::InputPrmSetPort *RateMultiplexerTesterBase ::
    get_from_ParamSet(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_ParamSet(),static_cast<AssertArg>(portNum));
    return &this->m_from_ParamSet[portNum];
  }

  Fw::InputTimePort *RateMultiplexerTesterBase ::
    get_from_Time(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Time(),static_cast<AssertArg>(portNum));
    return &this->m_from_Time[portNum];
  }

  Fw::InputLogPort *RateMultiplexerTesterBase ::
    get_from_Log(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_Log(),static_cast<AssertArg>(portNum));
    return &this->m_from_Log[portNum];
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  Fw::InputLogTextPort *RateMultiplexerTesterBase ::
    get_from_LogText(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_LogText(),static_cast<AssertArg>(portNum));
    return &this->m_from_LogText[portNum];
  }
#endif

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    from_OutputLedBlinker_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(callComp);
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(callComp);
    _testerBase->from_OutputLedBlinker_handlerBase(
        portNum,
        context
    );
  }

  void RateMultiplexerTesterBase ::
    from_CmdStatus_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        const Fw::CommandResponse response
    )
  {
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(component);
    _testerBase->cmdResponseIn(opCode, cmdSeq, response);
  }

  void RateMultiplexerTesterBase ::
    from_CmdReg_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        const FwOpcodeType opCode
    )
  {

  }

  void RateMultiplexerTesterBase ::
    from_Log_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(component);
    _testerBase->dispatchEvents(id, timeTag, severity, args);
  }

#if FW_ENABLE_TEXT_LOGGING == 1
  void RateMultiplexerTesterBase ::
    from_LogText_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        FwEventIdType id,
        Fw::Time &timeTag,
        Fw::TextLogSeverity severity,
        Fw::TextLogString &text
    )
  {
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(component);
    _testerBase->textLogIn(id,timeTag,severity,text);
  }
#endif

  void RateMultiplexerTesterBase ::
    from_Time_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(component);
    time = _testerBase->m_testTime;
  }


  Fw::ParamValid RateMultiplexerTesterBase ::
    from_ParamGet_static(
        Fw::PassiveComponentBase* component,
        NATIVE_INT_TYPE portNum,
        FwPrmIdType id,
        Fw::ParamBuffer &val
    )
  {
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(component);

    Fw::SerializeStatus _status;
    Fw::ParamValid _ret = Fw::PARAM_VALID;
    val.resetSer();

    const U32 idBase = _testerBase->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);

    switch (id - idBase) {
      case 0:
      {
        _status = val.serialize(_testerBase->m_param_LedBlinkComponentGroup);
        _ret = _testerBase->m_param_LedBlinkComponentGroup_valid;
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );
      }
        break;
      default:
        FW_ASSERT(id);
        break;
    }

    return _ret;
  }

  void RateMultiplexerTesterBase ::
    from_ParamSet_static(
        Fw::PassiveComponentBase* component,
        NATIVE_INT_TYPE portNum,
        FwPrmIdType id,
        Fw::ParamBuffer &val
    )
  {
    RateMultiplexerTesterBase* _testerBase =
      static_cast<RateMultiplexerTesterBase*>(component);

    Fw::SerializeStatus _status;
    val.resetDeser();

    // This is exercised completely in autocode,
    // so just verify that it works. If it doesn't
    // it probably is an autocoder error.

    const U32 idBase = _testerBase->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);

    switch (id - idBase) {
      case 0:
      {
        RateGroup LedBlinkComponentGroupVal;
        _status = val.deserialize(LedBlinkComponentGroupVal);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );
        FW_ASSERT(
            LedBlinkComponentGroupVal ==
            _testerBase->m_param_LedBlinkComponentGroup
        );
        break;
      }

      default: {
        FW_ASSERT(id);
        break;
      }

    }
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    clearFromPortHistory(void)
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_OutputLedBlinker->clear();
  }

  // ----------------------------------------------------------------------
  // From port: OutputLedBlinker
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    pushFromPortEntry_OutputLedBlinker(
        NATIVE_UINT_TYPE context
    )
  {
    FromPortEntry_OutputLedBlinker _e = {
      context
    };
    this->fromPortHistory_OutputLedBlinker->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    from_OutputLedBlinker_handlerBase(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(portNum < this->getNum_from_OutputLedBlinker(),static_cast<AssertArg>(portNum));
    this->from_OutputLedBlinker_handler(
        portNum,
        context
    );
  }

  // ----------------------------------------------------------------------
  // Command response handling
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    cmdResponseIn(
        const FwOpcodeType opCode,
        const U32 seq,
        const Fw::CommandResponse response
    )
  {
    CmdResponse e = { opCode, seq, response };
    this->cmdResponseHistory->push_back(e);
  }

  // ----------------------------------------------------------------------
  // Command: change_rate
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    sendCmd_change_rate(
        const NATIVE_INT_TYPE instance,
        const U32 cmdSeq,
        Component TargetComponent_comm,
        RateGroup TargetRateGroup_comm
    )
  {

    // Serialize arguments

    Fw::CmdArgBuffer buff;
    Fw::SerializeStatus _status;
    _status = buff.serialize(TargetComponent_comm);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));
    _status = buff.serialize(TargetRateGroup_comm);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK,static_cast<AssertArg>(_status));

    // Call output command port

    FwOpcodeType _opcode;
    const U32 idBase = this->getIdBase();
    _opcode = RateMultiplexerComponentBase::OPCODE_CHANGE_RATE + idBase;

    if (this->m_to_CmdDisp[0].isConnected()) {
      this->m_to_CmdDisp[0].invoke(
          _opcode,
          cmdSeq,
          buff
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }


  void RateMultiplexerTesterBase ::
    sendRawCmd(FwOpcodeType opcode, U32 cmdSeq, Fw::CmdArgBuffer& args) {

    const U32 idBase = this->getIdBase();
    FwOpcodeType _opcode = opcode + idBase;
    if (this->m_to_CmdDisp[0].isConnected()) {
      this->m_to_CmdDisp[0].invoke(
          _opcode,
          cmdSeq,
          args
      );
    }
    else {
      printf("Test Command Output port not connected!\n");
    }

  }

  // ----------------------------------------------------------------------
  // History
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    clearHistory()
  {
    this->cmdResponseHistory->clear();
    this->textLogHistory->clear();
    this->clearEvents();
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

  // ----------------------------------------------------------------------
  // Event dispatch
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    dispatchEvents(
        const FwEventIdType id,
        Fw::Time &timeTag,
        const Fw::LogSeverity severity,
        Fw::LogBuffer &args
    )
  {

    args.resetDeser();

    const U32 idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);
    switch (id - idBase) {

      case RateMultiplexerComponentBase::EVENTID_RATE_CHANGE:
      {

        Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;
#if FW_AMPCS_COMPATIBLE
        // Deserialize the number of arguments.
        U8 _numArgs;
        _status = args.deserialize(_numArgs);
        FW_ASSERT(
          _status == Fw::FW_SERIALIZE_OK,
          static_cast<AssertArg>(_status)
        );
        // verify they match expected.
        FW_ASSERT(_numArgs == 2,_numArgs,2);

#endif
        Component TargetComponent_evt;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(Component),_argSize,sizeof(Component));
        }
#endif
        _status = args.deserialize(TargetComponent_evt);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        RateGroup TargetRateGroup_evt;
#if FW_AMPCS_COMPATIBLE
        {
          // Deserialize the argument size
          U8 _argSize;
          _status = args.deserialize(_argSize);
          FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
          );
          FW_ASSERT(_argSize == sizeof(RateGroup),_argSize,sizeof(RateGroup));
        }
#endif
        _status = args.deserialize(TargetRateGroup_evt);
        FW_ASSERT(
            _status == Fw::FW_SERIALIZE_OK,
            static_cast<AssertArg>(_status)
        );

        this->logIn_ACTIVITY_LO_RATE_CHANGE(TargetComponent_evt, TargetRateGroup_evt);

        break;

      }

      default: {
        FW_ASSERT(0, id);
        break;
      }

    }

  }

  void RateMultiplexerTesterBase ::
    clearEvents(void)
  {
    this->eventsSize = 0;
    this->eventHistory_RATE_CHANGE->clear();
  }

#if FW_ENABLE_TEXT_LOGGING

  // ----------------------------------------------------------------------
  // Text events
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    textLogIn(
        const U32 id,
        Fw::Time &timeTag,
        const Fw::TextLogSeverity severity,
        const Fw::TextLogString &text
    )
  {
    TextLogEntry e = { id, timeTag, severity, text };
    textLogHistory->push_back(e);
  }

  void RateMultiplexerTesterBase ::
    printTextLogHistoryEntry(
        const TextLogEntry& e,
        FILE* file
    )
  {
    const char *severityString = "UNKNOWN";
    switch (e.severity) {
      case Fw::TEXT_LOG_FATAL:
        severityString = "FATAL";
        break;
      case Fw::TEXT_LOG_WARNING_HI:
        severityString = "WARNING_HI";
        break;
      case Fw::TEXT_LOG_WARNING_LO:
        severityString = "WARNING_LO";
        break;
      case Fw::TEXT_LOG_COMMAND:
        severityString = "COMMAND";
        break;
      case Fw::TEXT_LOG_ACTIVITY_HI:
        severityString = "ACTIVITY_HI";
        break;
      case Fw::TEXT_LOG_ACTIVITY_LO:
        severityString = "ACTIVITY_LO";
        break;
      case Fw::TEXT_LOG_DIAGNOSTIC:
       severityString = "DIAGNOSTIC";
        break;
      default:
        severityString = "SEVERITY ERROR";
        break;
    }

    fprintf(
        file,
        "EVENT: (%d) (%d:%d,%d) %s: %s\n",
        e.id,
        const_cast<TextLogEntry&>(e).timeTag.getTimeBase(),
        const_cast<TextLogEntry&>(e).timeTag.getSeconds(),
        const_cast<TextLogEntry&>(e).timeTag.getUSeconds(),
        severityString,
        e.text.toChar()
    );

  }

  void RateMultiplexerTesterBase ::
    printTextLogHistory(FILE *file)
  {
    for (U32 i = 0; i < this->textLogHistory->size(); ++i) {
      this->printTextLogHistoryEntry(
          this->textLogHistory->at(i),
          file
      );
    }
  }

#endif

  // ----------------------------------------------------------------------
  // Event: RATE_CHANGE
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    logIn_ACTIVITY_LO_RATE_CHANGE(
        Component TargetComponent_evt,
        RateGroup TargetRateGroup_evt
    )
  {
    EventEntry_RATE_CHANGE e = {
      TargetComponent_evt, TargetRateGroup_evt
    };
    eventHistory_RATE_CHANGE->push_back(e);
    ++this->eventsSize;
  }

  // ----------------------------------------------------------------------
  // Parameter LedBlinkComponentGroup
  // ----------------------------------------------------------------------

  void RateMultiplexerTesterBase ::
    paramSet_LedBlinkComponentGroup(
        const RateGroup& val,
        Fw::ParamValid valid
    )
  {
    this->m_param_LedBlinkComponentGroup = val;
    this->m_param_LedBlinkComponentGroup_valid = valid;
  }

  void RateMultiplexerTesterBase ::
    paramSend_LedBlinkComponentGroup(
        NATIVE_INT_TYPE instance,
        U32 cmdSeq
    )
  {

    // Build command for parameter set

    Fw::CmdArgBuffer args;
    FW_ASSERT(
        args.serialize(
            this->m_param_LedBlinkComponentGroup
        ) == Fw::FW_SERIALIZE_OK
    );
    const U32 idBase = this->getIdBase();
    FwOpcodeType _prmOpcode;
    _prmOpcode =  RateMultiplexerComponentBase::OPCODE_LEDBLINKCOMPONENTGROUP_SET + idBase;
    if (not this->m_to_CmdDisp[0].isConnected()) {
      printf("Test Command Output port not connected!\n");
    }
    else {
      this->m_to_CmdDisp[0].invoke(
          _prmOpcode,
          cmdSeq,
          args
      );
    }

  }

  void RateMultiplexerTesterBase ::
    paramSave_LedBlinkComponentGroup (
        NATIVE_INT_TYPE instance,
        U32 cmdSeq
    )

  {
    Fw::CmdArgBuffer args;
    FwOpcodeType _prmOpcode;
    const U32 idBase = this->getIdBase();
    _prmOpcode = RateMultiplexerComponentBase::OPCODE_LEDBLINKCOMPONENTGROUP_SAVE + idBase;
    if (not this->m_to_CmdDisp[0].isConnected()) {
      printf("Test Command Output port not connected!\n");
    }
    else {
      this->m_to_CmdDisp[0].invoke(
          _prmOpcode,
          cmdSeq,
          args
      );
    }
  }

} // end namespace Arduino
