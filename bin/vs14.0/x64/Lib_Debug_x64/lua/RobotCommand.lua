--���ļ��ǻ����˵������ļ�

local robotCommand = RobotCommand()
local robotParam = RobotParams()

--�����������Ҫ��C++�����Ӧ,������˵ֻ֧��double,Խ��Խ��.Ĭ��ҲΪdouble
local ROBOT_TYPE_DOUBLE = 0
local ROBOT_TYPE_STRING = 1

RobotTypes = {}
RobotTypes[ROBOT_TYPE_DOUBLE] = "double"
RobotTypes[ROBOT_TYPE_STRING] = "std::string" 

RobotCommands = {}
robotCommand.command = "��������" 
	robotParam.type = ROBOT_TYPE_DOUBLE
	robotParam.default = "1 "
	robotParam.note = "����1" 
robotCommand:SetParams(0 , robotParam)
	robotParam.type = ROBOT_TYPE_STRING
	robotParam.default = "-2"
	robotParam.note = "����1"
robotCommand:SetParams(1 , robotParam)
RobotCommands[0] = robotCommand

local robotCommand = RobotCommand()
local robotParam = RobotParams()
robotCommand.command = "��������2"
	robotParam.type = ROBOT_TYPE_STRING
	robotParam.default = "45345"
	robotParam.note = "����1"
robotCommand:SetParams(0 , robotParam)
RobotCommands[1] = robotCommand