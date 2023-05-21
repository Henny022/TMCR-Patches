local scriptio = require 'scriptio'
scriptio.init()

function scriptio_main()
    if scriptio.has_recv() then
        local t = scriptio.recv()
        local cmd = t>>24
        local flag = t&0xffffff
        if cmd == 1 then
            -- peek item
            console:log('peek ' .. flag)
            scriptio.send((2<<24) | 22)
        elseif cmd == 3 then
            -- get item
            console:log('get ' .. flag)
            scriptio.send((4<<24) | 22)
        else
            console:log('unknown command ' .. cmd .. ' ' .. flag)
        end
    end
end

callbacks:add('frame', scriptio_main)
