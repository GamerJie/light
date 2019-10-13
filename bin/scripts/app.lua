
local light = require "light"

light.define [[
    typedef struct pos {
        int x;
        int y;
    } pos;
]]

function main ()
    system("move_system", light.type.EcsOnSet)
    local ent = light.entity("pos")
    local ent_2 = light.entity("pos", {x = 3, y = 5})
    print("create entity:", ent, ent_2)
end
