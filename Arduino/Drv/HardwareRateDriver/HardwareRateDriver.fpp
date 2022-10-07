module Arduino {

  @ An interrupt based driver for Arduino rate groups.
  passive component HardwareRateDriver {

    @ The cycle outputs. Meant to be connected to rate group driver
    output port CycleOut: [1] Cycle

  }

}
