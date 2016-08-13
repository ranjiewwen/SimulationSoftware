#include "stdafx.h"
#include "CommandResult.h"


// CommandResult
CommandResult::CommandResult()
: dataLength_(0)
, status_(0) {
	dataBuffer_ = staticBuffer_;
}

CommandResult::~CommandResult() {
	if (dataBuffer_ != staticBuffer_) {
		delete[] dataBuffer_;
	}
}

bool CommandResult::IsOk() const {
	return status_ == 0;
}

int CommandResult::GetStatus() const {
	return status_;
}

int CommandResult::GetDataLength() const {
	return dataLength_;
}

const void *CommandResult::GetData() const {
	return dataBuffer_;
}

int CommandResult::GetData(void *buffer, int size) {
	if (size > dataLength_) {
		size = dataLength_;
	}
	if (size > 0) {
		memcpy(buffer, dataBuffer_, size);
	}
	return size;
}

void *CommandResult::GetDataBuffer(int length) {
	if (dataBuffer_ != staticBuffer_) {
		delete[] dataBuffer_;
	}
	if (length > STATIC_BUFFER_SIZE) {
		dataBuffer_ = new char[length];
	}
	else {
		dataBuffer_ = staticBuffer_;
	}
	dataLength_ = length;

	return dataBuffer_;
}

void CommandResult::SetStatus(int code) {
	status_ = code;
}
