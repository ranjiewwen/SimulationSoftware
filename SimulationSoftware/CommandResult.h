#pragma once

// device control command IDs
#define COMMAND_GET_SN                      0x0001
#define COMMAND_SET_DEVICE_INFO             0x0002
#define COMMAND_UPDATE_DEBUG_STATE          0x0003
#define COMMAND_UPGRADE                     0x0004
#define COMMAND_UPGRADE_DATA                0x0005
#define COMMAND_RESTART                     0x0006
#define COMMAND_ECHO                        0x8181
//#define COMMAND_GET_IR_PARAMETERS           0x0003
#define COMMAND_GET_IR_VALUES               0x0007
#define COMMAND_SET_IR_PARAMETERS           0x0008
#define COMMAND_UPDATE_IR_PARAMETERS        0x0009
#define COMMAND_START_MASTER_SIGNAL_DETECT  0x0006
#define COMMAND_GET_CIS_PARAMETER           0x0009
#define COMMAND_TAKE_CIS_IMAGE              0x000a
#define COMMAND_SET_CIS_PARAMETER           0x000b
#define COMMAND_UPDATE_CIS_PARAMETER        0x000c
#define COMMAND_GET_CIS_CORRECTION_TABLE    0x000d
#define COMMAND_UPDATE_CIS_CORRECTION_TABLE 0x000e
#define COMMAND_GET_MAC						0x0011
#define COMMAND_GET_STUDY_COMPLETED_STATE   0x0012
#define COMMAND_SET_AGING_TIME              0x0013
#define COMMAND_START_TAPE_STUDY            0x0014
#define COMMAND_START_MOTOR                 0x0015
#define COMMAND_START_RUN_CASH_DETECT       0x8004
#define COMMAND_START_SIGNAL_COLLECT        0x0016
#define COMMAND_DISABLE_DEBUG               0x0017
#define COMMAND_SET_TIME                    0x0018
#define COMMAND_GET_TIME                    0x0019
#define COMMAND_LIGHT_CIS                   0x0020
#define COMMAND_SET_SN                      0x0021
#define COMMAND_TAPE_LEARNING				0x0022

// class CommandResult
class CommandResult {
public:
	CommandResult();
	virtual ~CommandResult();

	bool IsOk() const;
	int GetStatus() const;
	int GetDataLength() const;
	const void *GetData() const;
	int GetData(void *buffer, int size);
	void *GetDataBuffer(int length);
	void SetStatus(int code);

private:
	enum { STATIC_BUFFER_SIZE = 128 };

	int   status_;
	char  staticBuffer_[STATIC_BUFFER_SIZE];
	char  *dataBuffer_;
	int   dataLength_;
};
