local scriptio = require 'scriptio'
scriptio.init()

function scriptio_main()
    if scriptio.has_recv() then
        local t = scriptio.recv()
        local cmd = t>>24
        local flag = t&0xffffff
        console:log('cmd ' .. cmd .. ' ' .. flag)
        if cmd == 1 then
            -- get item
            scriptio.send(6)
        elseif cmd == 2 then
            -- set flag
            console:log('got ' .. flag)
        end
    else
        scriptio.send(3<<24|4)
    end
end

callbacks:add('frame', scriptio_main)
