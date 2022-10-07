// ======================================================================
// \title  GpioDriver.hpp
// \author lestarch
// \brief  hpp file for GpioDriver component implementation class
// ======================================================================

#ifndef ARDUINO_DRV_GpioDriver_HPP
#define ARDUINO_DRV_GpioDriver_HPP

#include "Arduino/Drv/GpioDriver/GpioDriverComponentAc.hpp"

namespace Drv {

class GpioDriver : public GpioDriverComponentBase {
    //! configure GPIO
    enum GpioDirection {
        IN,   //!< input
        OUT,  //!< output
    };

  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object GpioDriver
    //!
    GpioDriver(const char* const compName /*!< The component name*/
    );

    //! Initialize object GpioDriver
    //!
    void init(const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object GpioDriver
    //!
    ~GpioDriver();

    //! open GPIO
    bool open(NATIVE_INT_TYPE gpio, GpioDirection direction);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for gpioRead
    //!
    void gpioRead_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                          Fw::Logic& state);

    //! Handler implementation for gpioWrite
    //!
    void gpioWrite_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                           const Fw::Logic& state);

    //! device direction
    PlatformIntType m_pin;
};

}  // end namespace Drv

#endif
