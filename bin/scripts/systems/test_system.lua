---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by k.
--- DateTime: 10/10/19 14:21
---

local light = require "light"

function init ()
    print("test system init")
    return "TestCom"
end

function update (rows)
    print("test system update data: ", rows)
end
