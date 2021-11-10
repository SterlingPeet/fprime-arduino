# Parameter Driven LED Blinker Component

## 1. Introduction

Example component to support Parameter Usage LED Blink Demonstration deployment.

## 2. Requirements

The requirements for `ParamBlinkDemo::PrmBlinkComponent` are as follows:

Requirement | Description | Verification Method
----------- | ----------- | -------------------
PB-001 | The `ParamBlinkDemo::PrmBlinkComponent` will blink an LED at a rate set by the ground station | Inspection
PB-002 | The `ParamBlinkDemo::PrmBlinkComponent` will save the current blink rate to a parameter database, and use that saved rate at startup | Inspection

## 3. Design

### 3.1 Context

#### 3.1.1 Component Diagram

The `ParamBlinkDemo::PrmBlinkComponent` component has the following component diagram:

![`ParamBlinkDemo::PrmBlinkComponent` Diagram](img/PrmBlinkComponentBDD.jpg "ParamBlinkDemo::PrmBlinkComponent")

#### 3.1.2 Ports

The `ParamBlinkDemo::PrmBlinkComponent` component uses the following port types:

| Port Data Type | Name | Direction | Kind | Usage |
| --- | --- | --- | --- | --- |
| [`Svc::Sched`](../../../../../Svc/Sched/docs/sdd.md) | schedIn | Input | Sync |   |
| [`Drv::GpioWrite`](../../../../../Drv/GpioDriverPorts/docs/sdd.md) | gpio | Output | Output |   |

### 3.2 Functional Description

This component loads a parameter from the database to set the blink time interval.  If the database does not contain the parameter, it will load the default value.  The ground can set a new value for use, and separately save that value to the database for retrieval at boot time.

### 3.3 Scenarios

#### 3.3.1 FATAL Notification

The `ParamBlinkDemo::PrmBlinkComponent` handles FATAL notifications:

![FATAL Notification](img/FatalNotification.jpg)

### 3.4 State

`ParamBlinkDemo::PrmBlinkComponent` has no state machines (or does it?).

### 3.5 Algorithms

`ParamBlinkDemo::PrmBlinkComponent` has no significant algorithms.

## 4. Dictionary

Dictionaries: [HTML](PrmBlinkComponent.html) [MD](PrmBlink.md)

## 4. Module Checklists

Document | Link
-------- | ----
Design Checklist | [Link](Checklist_Design.xlsx)
Code Checklist | [Link](Checklist_Code.xlsx)
Unit Test Checklist | [Link](Checklist_Unit_Test.xls)

## 5. Unit Testing

[Unit Test Output](../test/ut/output/test.txt)

[Coverage Summary](../test/ut/output/ParamBlinkDemoPrmBlinkComponent_gcov.txt)

[Coverage Output - `ParamBlinkDemo::PrmBlinkComponent.cpp`](../test/ut/output/PrmBlinkComponent.cpp.gcov)

[Coverage Output - `PrmBlinkComponentAc.cpp`](../test/ut/output/PrmBlinkComponentAc.cpp.gcov)

## 6. Change Log

Date       | Description
---------- | -----------
09/25/2020 | Initial Component Design



