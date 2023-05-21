local scriptio = require 'scriptio'
scriptio.init()

local s = socket:tcp()

function socker_error()
    console:log('socket error')
end

s:add('error', socker_error)

function socket_recv()
    while true do
        local data, err = s:receive(4)
        if data then
            console:log('received len ' .. data:len())
            data = string.unpack('<I4', data)
            console:log('received ' .. data)
            scriptio.send(data)
        else
            if err ~= socket.ERRORS.AGAIN then
                console:error('socket error ' .. err)
            end
            return
        end
    end
end

s:add('received', socket_recv)

function scriptio_main()
    if scriptio.has_recv() then
        local t = scriptio.recv()
        s:send(string.pack('<I4', t))
    end
end

if s:connect('127.0.0.1', 9000) then
    console:log('connected')
else
    console:log('connection error')
end

callbacks:add('frame', scriptio_main)
