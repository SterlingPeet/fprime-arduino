// ======================================================================
// \title  ReadingDisplayComponentImpl.hpp
// \author Kaushik Manchikanti <kmanchikanti6@gatech.edu>
// \brief  Example component to display the readings from the internal adc channels to the Serial Monitor
// ======================================================================

#ifndef ReadingDisplayComponent_HPP
#define ReadingDisplayComponent_HPP

#include "ATmega/examples/ATmegaReadInternalAdc/ReadingDisplay/ReadingDisplayComponentAc.hpp"

namespace Arduino {

  class ReadingDisplayComponentImpl :
    public ReadingDisplayComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object ReadingDisplayComponentImpl
      //!
      ReadingDisplayComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object ReadingDisplayComponentImpl
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object ReadingDisplayComponentImpl
      //!
      ~ReadingDisplayComponentImpl(void);

    PRIVATE:
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

      U8 m_channels;
      U16 m_counts;
      F32 m_voltage, m_maxCounts = 1024.0, m_reference_voltage = 3.3;
    };

} // end namespace Arduino

#endif // end ReadingDisplayComponent_HPP
