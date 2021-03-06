---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by k.
--- DateTime: 10/10/19 22:02
---

local light = require "light"

light.define [[
    typedef struct pos {
        int x;
        int y;
    } pos;
]]

function init ()
    component("pos", light.sizeof("pos"))
    return "pos"
end

function update(rows)
    local data, count = light.column_v(rows, "pos", 1)
    for i = 0, count - 1 do
        local pos = light.cast("pos", data)[i]
        print(pos.x, pos.y, count)
    end
end