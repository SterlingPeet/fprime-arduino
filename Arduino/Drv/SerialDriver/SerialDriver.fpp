module Arduino {

  passive component SerialDriver {

    @ Indicates the driver has connected to the UART device
    output port ready: Drv.ByteStreamReady

    @ Produces data received via the UART device on the receive task
    output port $recv: Drv.ByteStreamRecv

    @return for the recv buffer
    guarded input port recvReturn: Fw.BufferSend

    @return the allocated buffer
    output port deallocate: Fw.BufferSend

    @ Takes data to transmit out the UART device
    guarded input port send: Drv.ByteStreamSend

    @ Takes data to transmit out the UART device
    guarded input port poll: Drv.ByteStreamPoll
  }
}
