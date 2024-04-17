//**********************************************************************`
//* This is an include file generated by Message Compiler.             *`
//*                                                                    *`
//* Copyright (c) Microsoft Corporation. All Rights Reserved.          *`
//**********************************************************************`
#pragma once

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Provider "MyCompany-App" event count 2
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Provider GUID = 27957180-15d4-4ac3-a37a-0e539490f7bf
EXTERN_C __declspec(selectany) const GUID mko_sample = {0x27957180, 0x15d4, 0x4ac3, {0xa3, 0x7a, 0x0e, 0x53, 0x94, 0x90, 0xf7, 0xbf}};

#ifndef mko_sample_Traits
#define mko_sample_Traits NULL
#endif // mko_sample_Traits

//
// Channel
//
#define op 0x10
#define op_KEYWORD 0x8000000000000000
#define mko_sample_CHANNEL_Application 0x9
#define mko_sample_CHANNEL_Application_KEYWORD 0x4000000000000000
#define Diagnostics 0x11
#define Diagnostics_KEYWORD 0x2000000000000000

//
// Levels
//
#define l1 0x10

//
// Opcodes
//
#define baz 0xa

//
// Tasks
//
#define bar 0x1

//
// Keyword
//
#define foo 0x10

//
// Event Descriptors
//
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR EventInfo = {0x1, 0x1, 0x10, 0x4, 0xa, 0x1, 0x8000000000000010};
#define EventInfo_value 0x1
EXTERN_C __declspec(selectany) const EVENT_DESCRIPTOR EventError = {0x2, 0x1, 0x10, 0x2, 0x0, 0x0, 0x8000000000000000};
#define EventError_value 0x2

#define MSG_opcode_Info                      0x30000000L
#define MSG_level_Error                      0x50000002L
#define MSG_level_Informational              0x50000004L
#define MSG_task_None                        0x70000000L
#define MSG_channel_Application              0x90000001L
#define MSG_Michael_Koster_LoggingSample_event_1_message 0xB0010001L
#define MSG_Michael_Koster_LoggingSample_event_2_message 0xB0010002L