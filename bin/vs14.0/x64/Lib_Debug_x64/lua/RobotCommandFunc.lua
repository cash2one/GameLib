--���ļ��Ǹ��ݻ����˵�����ִ����Ӧ�Ĳ���



--����������ص�ǰlua�ļ���·��,����Lua�����ļ���.
function getLocalPath()
	local debug = require"debug"
	local tmp_path=debug.getinfo (1, "S").source
	
	--ȥ��@
	tmp_path=string.sub(tmp_path,2)
	local tmp_path_len=#tmp_path
	local real_path={}
	local last_pos=0

	local step=0
	for i=1,tmp_path_len do
		local charset=string.sub(tmp_path,i,i)
		if charset=="\\" then
			real_path[#real_path+1]="\\\\"
			last_pos=i
			--���step ������2��'\'
			step=step+1
		else
			real_path[#real_path+1]=charset
		end
	end
	real_path=table.concat(real_path,"")
	real_path=real_path.."\\"
	return real_path.sub(real_path,1,last_pos+step) 
end
local obj=io.popen("cd")
SYS_PATH = obj:read("*all"):sub(1,-2) .. "/lua"
print(SYS_PATH)
package.path=SYS_PATH..'/msg/?.lua;'..SYS_PATH..'/msg/protobuf/?.lua;'..SYS_PATH..'/msg/PB/?.lua;'..SYS_PATH..'/msg/google/protobuf/?.lua;'..SYS_PATH.."/?.lua;"..package.path..';'   --����package��path 
print(package.path)

require "protobuf.protobuf"	--��ǰ���أ���Ϊ���� module

local net_common = require "PB.net_common"

function ProcessMsg(robot ,unMsgID, pBuffer, unLength)
	print("unMsgID" .. unMsgID )
	print("pBuffer " .. pBuffer)
	print("unLength" .. unLength)
end

function HandleRobotCommand(robot ,command_type , params)
	if type(params) ~= "table" then
		print("err params not table." .. type(params))
	else
		for i,v in pairs(params) do
			print("i" .. i)
			print("type" .. v.type)
			print("default" .. v.default)
			print("note" .. v.note)
			print("value" .. v.value)
			
		end
	end	
	
	if command_type == 1 then
	
		local test_data = net_common.test_data
		local msg = test_data()
		msg.params = 10
		msg.param2 = 101
		buf = msg:SerializeToString()
		size = msg:ByteSize()
		robot:SendMsg(buf , size)
	end
end