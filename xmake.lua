-- global xmake.lua
--

-- set c++ standard
set_languages("c++20")
set_languages("c20")

if is_plat("debug") then
	add_cxflags("-g")
else
	add_cxflags("-O3")
end

local function LoadSubBuildScripts()
	local Scripts = {}

	local SubDirectory = os.dirs("*")
	for _, Dir in ipairs(SubDirectory) do
	end
end
