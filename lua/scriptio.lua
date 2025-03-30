local scriptio = {}
local sections = require "sections"

local gScriptIO = 0

function scriptio.init()
    local header = sections.get_header('SCRIPTIO')
    gScriptIO = emu:read32(header)
    console:log('found gScriptIO at ' .. gScriptIO)
end

function scriptio.can_send(port)
    return emu:read8(gScriptIO + (port + 1) * 36) == 0
end

function scriptio.has_ack_send(port)
    return emu:read8(gScriptIO + (port + 1) * 36) == 2
end

function scriptio.ack_send(port)
    emu:write8(gScriptIO + (port + 1) * 36, 0)
end

function scriptio.has_recv()
    return emu:read8(gScriptIO) == 1
end

function scriptio.send(addr, port, length, data)
    -- TODO check max port
    emu:write8(gScriptIO + (port + 1) * 36 + 1, addr)
    emu:write8(gScriptIO + (port + 1) * 36 + 2, port)
    emu:write8(gScriptIO + (port + 1) * 36 + 3, length)
    for i=0,(length-1) do
        emu:write8(gScriptIO + (port + 1) * 36 + 4 + i, string.byte(data, i+1))
    end
    --emu:writeRange(gScriptIO + (port + 1) * 36 + 4, data)
	emu:write8(gScriptIO + (port + 1) * 36, 1)
end

function scriptio.recv()
    local addr = emu:read8(gScriptIO + 1)
    local port = emu:read8(gScriptIO + 2)
    local length = emu:read8(gScriptIO + 3)
    local data = emu:readRange(gScriptIO + 4, length)
    emu:write8(gScriptIO, 2)
    return addr, port, length, data
end

function scriptio.ack_recv()
    emu:write8(gScriptIO, 0)
end

return scriptio
