# ReadingDisplay Component

## 1. Introduction

Example component to display the readings from the internal adc channels to the Serial Monitor

## 2. Requirements

The requirements for `Arduino::ReadingDisplayComponentImpl` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
RD-001 | The `Arduino::ReadingDisplayComponentImpl` component receives adc counts | Functional Test

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `Arduino::ReadingDisplayComponentImpl` component has the following component diagram:

![`Arduino::ReadingDisplayComponentImpl` Diagram](img/ReadingDisplayComponentImplBDD.jpg "Arduino::ReadingDisplayComponentImpl")

#### 3.1.2 Ports

The `Arduino::ReadingDisplayComponentImpl` component uses the following port types:

| Port Data Type | Name | Direction | Kind | Usage |
| --- | --- | --- | --- | --- |
| [`Svc::Sched`]() | schedIn | Input | Sync |   |
| [`Drv::AdcRead`]() | getAdc | Output | Output |   |
| [`Drv::GpioWrite`]() | led | Output | Output |   |

### 3.2 Functional Description

The ReadingDisplay component regularly polls the internal adc channels, and upon receiving the response, converts them to a voltage to display on the Serial Monitor. If LEDs are connected to this component, it will also light up which channels are being actively polled.

### 3.4 State

`Arduino::ReadingDisplayComponentImpl` has no state machines.

### 3.5 Algorithms

`Arduino::ReadingDisplayComponentImpl` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](ReadingDisplayComponentImpl.html) [MD](ReadingDisplay.md)

## 4. Module Checklists

Document            | Link
------------------- | ----
Design Checklist    | [Link](Checklist_Design.xlsx)
Code Checklist      | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/ArduinoReadingDisplayComponentImpl_gcov.txt)

[Coverage Output - `Arduino::ReadingDisplayComponentImpl.cpp`](../test/ut/output/ReadingDisplayComponentImpl.cpp.gcov)

[Coverage Output - `ReadingDisplayComponentAc.cpp`](../test/ut/output/ReadingDisplayComponentAc.cpp.gcov)

## 6. Change Log

Date       | Description
---------- | -----------
11/15/2020 | Initial Component Design



