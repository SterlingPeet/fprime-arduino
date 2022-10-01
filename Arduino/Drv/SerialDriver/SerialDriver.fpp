module Arduino {

  passive component SerialDriver {

    sync input port write: [1] Fw.BufferSend

    sync input port readPoll: [1] Fw.BufferSend

    output port readCallback: [1] Fw.BufferSend

    sync input port schedIn: [1] Svc.Sched

  }

}
