
local light = require "light"

function main ()
    system("move_system", light.type.EcsOnAdd, "pos")
    entity("mover", "pos")
end
