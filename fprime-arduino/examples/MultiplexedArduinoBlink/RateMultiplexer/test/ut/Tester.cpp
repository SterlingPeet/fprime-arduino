// ====================================================================== 
// \title  RateMultiplexer.hpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  main tester class for the rate multiplexer
// ====================================================================== 

#include <ATmega/examples/MultiplexedArduinoBlink/LedBlinker/LedBlinker.hpp>
#include "Tester.hpp"

#define INSTANCE 0
#define MAX_HISTORY_SIZE 10

namespace Arduino {

  // ----------------------------------------------------------------------
  // Construction and destruction 
  // ----------------------------------------------------------------------

  Tester ::
    Tester(void) : 
#if FW_OBJECT_NAMES == 1
      RateMultiplexerGTestBase("Tester", MAX_HISTORY_SIZE),
      component("RateMultiplexer")
#else
      RateMultiplexerGTestBase(MAX_HISTORY_SIZE),
      component()
#endif
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester(void) 
  {
    
  }

  // ----------------------------------------------------------------------
  // Tests 
  // ----------------------------------------------------------------------

  void Tester ::
    testFwdSched(void) {
    // load params for default behavior
    this->component.loadParameters();
    Fw::ParamValid valid;
    // check default behavior
    ASSERT_EQ(component.paramGet_LedBlinkComponentGroup(valid), component.get_LedBlinkComponentGroup());
    ASSERT_EQ(Fw::ParamValid::PARAM_DEFAULT, valid);
    //rateMultiplexer.set_OutputLedBlinker_OutputPort(1, ledBlinker.get_schedIn_InputPort(0));
    int numMessagesSent = 0;

    // check sched forwarding
    ASSERT_from_OutputLedBlinker_SIZE(numMessagesSent);
    // send in a sched
    this->invoke_to_Input10Hz(0,0);
    numMessagesSent++;
    // sched should be routed to ArduinoBlink port
    ASSERT_from_OutputLedBlinker_SIZE( numMessagesSent);
    // values should be what was passed in
    ASSERT_from_OutputLedBlinker(0,0);

  }

  void Tester ::
  testTopologyInit(void)
  {
    ASSERT_EQ(1,1);
    Arduino::LedBlinkerComponentImpl ledBlinker("Blinker");

    //init
    ledBlinker.init(0);
    this->component.init(0);
    // params
    this->component.loadParameters();

    ASSERT_EQ(ledBlinker.m_state, true);
    /*ASSERT_from_OutputLedBlinker_SIZE(0);

    // ports
    this->component.set_OutputLedBlinker_OutputPort(1, ledBlinker.get_schedIn_InputPort(0)); // hangs in normal test


    Fw::ParamValid valid;
    ASSERT_EQ(component.paramGet_LedBlinkComponentGroup(valid), component.get_LedBlinkComponentGroup());//*/
  }

  void Tester ::
    testRateControlPorts(void)
  {
    //ASSERT_EQ(1,2);
    // init component for default behavior
    this->component.loadParameters();
    Fw::ParamValid valid;
    ASSERT_EQ(component.paramGet_LedBlinkComponentGroup(valid), component.get_LedBlinkComponentGroup());
    ASSERT_EQ(Fw::ParamValid::PARAM_DEFAULT, valid);
    //rateMultiplexer.set_OutputLedBlinker_OutputPort(1, ledBlinker.get_schedIn_InputPort(0));
    // How can I test this line??
    // check assumptions
    ASSERT_from_OutputLedBlinker_SIZE(0);
    // send in a sched
    this->invoke_to_Input10Hz(0,0);
    // sched should be routed to ArduinoBlink port
    ASSERT_from_OutputLedBlinker_SIZE(1); // this fails
    // values should be what was passed in
    ASSERT_from_OutputLedBlinker(0,0);

    // Turn off LedBlinker
    ASSERT_from_OutputLedBlinker_SIZE(1);
    this->invoke_to_ChangeRatePort(0, RateGroup(Hz0), Component(LedBlinker));
    this->invoke_to_Input10Hz(0,0);
    ASSERT_from_OutputLedBlinker_SIZE(1);

    // Turn to other rate group
    ASSERT_from_OutputLedBlinker_SIZE(1);
    this->invoke_to_ChangeRatePort(0, RateGroup(Hz1), Component(LedBlinker));
    this->invoke_to_Input10Hz(0,0);
    ASSERT_from_OutputLedBlinker_SIZE(1);

    // Turn blinker on again
    ASSERT_from_OutputLedBlinker_SIZE(1);
    this->invoke_to_ChangeRatePort(0, RateGroup(Hz10), Component(LedBlinker));
    this->invoke_to_Input10Hz(0,0);
    ASSERT_from_OutputLedBlinker_SIZE(2);//*/
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_OutputLedBlinker_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    this->pushFromPortEntry_OutputLedBlinker(context);
  }

  // ----------------------------------------------------------------------
  // Helper methods 
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts(void) 
  {

    // Input10Hz
    this->connect_to_Input10Hz(
        0,
        this->component.get_Input10Hz_InputPort(0)
    );

    // ChangeRatePort
    this->connect_to_ChangeRatePort(
        0,
        this->component.get_ChangeRatePort_InputPort(0)
    );

    // CmdDisp
    this->connect_to_CmdDisp(
        0,
        this->component.get_CmdDisp_InputPort(0)
    );

    // OutputLedBlinker
    this->component.set_OutputLedBlinker_OutputPort(
        0, 
        this->get_from_OutputLedBlinker(0)
    );

    // CmdStatus
    this->component.set_CmdStatus_OutputPort(
        0, 
        this->get_from_CmdStatus(0)
    );

    // CmdReg
    this->component.set_CmdReg_OutputPort(
        0, 
        this->get_from_CmdReg(0)
    );

    // ParamGet
    this->component.set_ParamGet_OutputPort(
        0, 
        this->get_from_ParamGet(0)
    );

    // ParamSet
    this->component.set_ParamSet_OutputPort(
        0, 
        this->get_from_ParamSet(0)
    );

    // Time
    this->component.set_Time_OutputPort(
        0, 
        this->get_from_Time(0)
    );

    // Log
    this->component.set_Log_OutputPort(
        0, 
        this->get_from_Log(0)
    );

    // LogText
    this->component.set_LogText_OutputPort(
        0, 
        this->get_from_LogText(0)
    );




  }

  void Tester ::
    initComponents(void) 
  {
    this->init();
    this->component.init(
        INSTANCE
    );
  }

} // end namespace Arduino
