// ======================================================================
// \title  RateMultiplexer/test/ut/Tester.hpp
// \author Aaron McDaniel <amcdaniel39@gatech.edu>
// \brief  main tester class for the rate multiplexer
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "ATmega/examples/MultiplexedArduinoBlink/RateMultiplexer/RateMultiplexerComponentImpl.hpp"

namespace Arduino {

  class Tester :
    public RateMultiplexerGTestBase
  {

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:

      //! Construct object Tester
      //!
      Tester(void);

      //! Destroy object Tester
      //!
      ~Tester(void);

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

     void testFwdSched(void);
     void testRateControlPorts(void);
     void testTopologyInit(void);

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_OutputLedBlinker
      //!
      void from_OutputLedBlinker_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts(void);

      //! Initialize components
      //!
      void initComponents(void);

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      RateMultiplexerComponentImpl component;

  };

} // end namespace Arduino

#endif
