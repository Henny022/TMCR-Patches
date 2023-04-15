local scriptio = {}

local gScriptIO = 0

function scriptio.init()
    local sections = require "lua/sections"
    local header = sections.get_header('SCRIPTIO')
    gScriptIO = emu:read32(header)
    console:log('found gScriptIO at ' .. gScriptIO)
end

function scriptio.can_send()
    return emu:read32(gScriptIO+12) == 0
end

function scriptio.has_recv()
    return emu:read32(gScriptIO+4) ~= 0
end

function scriptio.send(value)
    emu:write32(gScriptIO+8, value)
    emu:write32(gScriptIO+12, 1)
end

function scriptio.recv()
    local t = emu:read32(gScriptIO)
    emu:write32(gScriptIO+4, 0)
    return t
end

return scriptio
