# PrmBlink Component Dictionary


## Command List

| Mnemonic | ID | Description | Arg Name | Arg Type | Comment |
| --- | --- | --- | --- | --- | --- |
| downlinkParams | 0 (0x0) | Command to telemeter the current parameter values in use. |   |   |   |

## Telemetry Channel List

| Channel | ID | Type | Description |
| --- | --- | --- | --- |
| numBlinks | 0 (0x0) | U32 | Number of blinks since startup |
| blinkDecimate | 1 (0x1) | U8 | Current setting of the blinkDecimate parameter. |
| parameter1 | 2 (0x2) | I16 | Current setting of the parameter1 parameter. |
| parameter2 | 3 (0x3) | U32 | Current setting of the parameter2 parameter. |

## Event List

| Event Name | ID | Description | Arg Name | Arg Type | Arg Size | Comment |
| --- | --- | --- | --- | --- | --- | --- |
| PrmBlinkParameterUpdated | 0 (0x0) | Report parameter update |   |   |   |   |
