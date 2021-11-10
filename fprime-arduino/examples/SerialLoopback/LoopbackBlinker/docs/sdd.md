# Loopback Blinker Component

## 1. Introduction

Example component to support Serial Loopback Demo deployment.

## 2. Requirements

The requirements for `example::LoopbackBlinkerComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
LB-001 | The `example::LoopbackBlinkerComponent` component shall emit some regular serial data. | Inspection
LB-002 | The `example::LoopbackBlinkerComponent` component shall loop data read from serial back into the serial output. | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `example::LoopbackBlinkerComponent` component has the following component diagram:

![`example::LoopbackBlinkerComponent` Diagram](img/LoopbackBlinkerComponentBDD.jpg "example::LoopbackBlinkerComponent")

#### 3.1.2 Ports

The `example::LoopbackBlinkerComponent` component uses the following port types:

Port Data Type                                                       | Name       | Direction | Kind   | Usage
-------------------------------------------------------------------- | ---------- | --------- | ------ | -----
[`Svc::Sched`](../../../../../Svc/Sched/docs/sdd.html)               | schedIn    | Input     | Sync   | trigger the blink and serial functions
[`Drv::GpioWrite`](../../../../../Drv/GpioDriverPorts/docs/sdd.html) | gpio       | Output    | Output | set the LED pin state
[`Fw::BufferSend`](../../../../../Fw/Buffer/docs/sdd.html)           | serialSend | Output    | Sync   | outbound serial data
[`Fw::BufferSend`](../../../../../Fw/Buffer/docs/sdd.html)           | serialRecv | Output    | Sync   | poll for inbound serial data

### 3.2 Functional Description

Its pretty simple, demonstrate serial loopback and blink an LED.

### 3.3 Scenarios

The `example::LoopbackBlinkerComponent` has no scenarios.

### 3.4 State

`example::LoopbackBlinkerComponent` has no state machines.

### 3.5 Algorithms

`example::LoopbackBlinkerComponent` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](LoopbackBlinkerComponent.html) [MD](LoopbackBlinker.md)

## 4. Module Checklists

Document            | Link
------------------- | ----
Design Checklist    | [Link](Checklist_Design.xlsx)
Code Checklist      | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/exampleLoopbackBlinkerComponent_gcov.txt)

[Coverage Output - `example::LoopbackBlinkerComponent.cpp`](../test/ut/output/LoopbackBlinkerComponent.cpp.gcov)

[Coverage Output - `LoopbackBlinkerComponentAc.cpp`](../test/ut/output/LoopbackBlinkerComponentAc.cpp.gcov)

## 6. Change Log

Date       | Description
---------- | -----------
09/29/2020 | Initial Component Design



