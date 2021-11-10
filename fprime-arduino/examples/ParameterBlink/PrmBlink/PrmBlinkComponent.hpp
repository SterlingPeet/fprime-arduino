// ======================================================================
// \title  PrmBlinkComponent.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Parameter Usage LED Blink Demonstration deployment.
// ======================================================================

#ifndef PrmBlinkComponent_HPP
#define PrmBlinkComponent_HPP

#include "ATmega/examples/ParameterBlink/PrmBlink/PrmBlinkComponentAc.hpp"

namespace ParamBlinkDemo {

  class PrmBlinkComponent :
    public PrmBlinkComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object PrmBlinkComponent
      //!
      PrmBlinkComponent(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object PrmBlinkComponent
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object PrmBlinkComponent
      //!
      ~PrmBlinkComponent(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for downlinkParams command handler
      //! Command to telemeter the current parameter values in use.
      void downlinkParams_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


      //! Blink a given pin
      void blink();
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      //! parameter update notification
      //!
      void parameterUpdated(FwPrmIdType id);

      bool m_state;
      bool m_paramsLoaded;
      U32 m_blinks;
      U32 m_blinkDecimCtr;
    };

} // end namespace ParamBlinkDemo

#endif // end PrmBlinkComponent_HPP
