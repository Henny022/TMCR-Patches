local scriptio = require 'scriptio'
scriptio.init()

local s = socket:tcp()

function socket_error()
    console:log('socket error')
end

s:add('error', socket_error)

function receive(n)
    while true do
        local data, err = s:receive(n)
        if data then
            return data
        else
            if err ~= socket.ERRORS.AGAIN then
                console:error('socket error '.. err)
            end
        end
    end
end

last_ids = {}

function socket_recv()
    local data, err = s:receive(1)
    if err then
        if err ~= socket.ERRORS.AGAIN then
            console:error('socket error ' .. err)
        end
        return
    end
    if data == 'D' then
        data = receive(7)
        local addr, port, id, length = string.unpack("<I1I1I4I1", data)
        last_ids[port] = id
        local payload = receive(length)
		console:log('>D' .. data .. payload)
        if not scriptio.can_send(port) then
            console:error('protocol error, buffer full ' .. port)
            return
        end
        scriptio.send(addr, port, length, payload)
        return
    end
    if data == 'A' then
        -- TODO check id
        data = receive(5)
		console:log('>A' .. data)
        scriptio.ack_recv()
        return
    end
    console:error('protocol error, unknown type ' .. data)
end

s:add('received', socket_recv)

send_id = 1

function scriptio_main()
    if scriptio.has_recv() then
        local addr, port, length, data = scriptio.recv()
        local id = send_id
        send_id = send_id + 1
        local packet = 'D' .. string.pack('<I1I1I4I1', addr, port, id, length) .. data
		console:log('<' .. packet)
        s:send(packet)
    end
    for i=0,3 do
        if scriptio.has_ack_send(i) then
            local id = last_ids[i]
            local packet = 'A' .. string.pack('<I1I4', i, id)
			console:log('<' .. packet)
            s:send(packet)
            scriptio.ack_send(i)
        end
    end
end

if s:connect('127.0.0.1', 9000) then
    console:log('connected')
    -- login
    local me = 0
    local packet = 'D' .. string.pack('<I1I1I4I1I1', 0xf, 2, 0, 1, me)
    s:send(packet)
else
    console:log('connection error')
end

callbacks:add('frame', scriptio_main)
