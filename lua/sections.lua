local sections = {}

local section_table = 0

function sections.find_table()
    for address = 0x08000000, 0x08000000+emu:romSize(), 16 do
        if emu:readRange(address, 16) == 'SECTION_TABLE   ' then
            section_table = address+16
            console:log('found section table at ' .. section_table)
            return
        end
    end
end

function sections.get_header(name)
    if section_table == 0 then sections.find_table() end
    local entry = section_table
    while true do
        if emu:read32(entry) == 0 then return 0 end
        if emu:readRange(entry, 8) == name then return emu:read32(entry+8) end
    end
end

return sections
