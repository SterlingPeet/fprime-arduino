// ======================================================================
// \title  LoopbackBlinkerComponent.hpp
// \author Sterling Peet <sterling.peet@ae.gatech.edu>
// \brief  Example component to support Serial Loopback Demo deployment.
// ======================================================================

#ifndef LoopbackBlinkerComponent_HPP
#define LoopbackBlinkerComponent_HPP

#include "ATmega/examples/SerialLoopback/LoopbackBlinker/LoopbackBlinkerComponentAc.hpp"

namespace example {

  class LoopbackBlinkerComponent :
    public LoopbackBlinkerComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object LoopbackBlinkerComponent
      //!
      LoopbackBlinkerComponent(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object LoopbackBlinkerComponent
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object LoopbackBlinkerComponent
      //!
      ~LoopbackBlinkerComponent(void);

    PRIVATE:
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
      bool m_state;
      Fw::Buffer m_staticBuf;
      char m_data[9] = "blink!\r\n";
      Fw::Buffer m_loopBuf;
      char m_loop[64];
    };

} // end namespace example

#endif // end LoopbackBlinkerComponent_HPP
