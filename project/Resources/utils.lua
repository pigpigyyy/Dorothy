local string = string
local table = table

local oContent = require("oContent")


function string.findlast(s, pattern, plain)
    local curr = 0
    repeat
        local next = s:find(pattern, curr + 1, plain)
        if next then curr = next end
    until (not next)

    if curr > 0 then
        return curr
    end
end

function string.split(input, delimiter)
    input = tostring(input)
    delimiter = tostring(delimiter)
    if (delimiter=='') then return false end
    local pos,arr = 0, {}
    -- for each divider found
    for st,sp in function() return string.find(input, delimiter, pos, true) end do
        table.insert(arr, string.sub(input, pos, st - 1))
        pos = sp + 1
    end
    table.insert(arr, string.sub(input, pos))
    return arr
end






path = path or {}

function path.normalize(p)
    return (string.gsub(p, '\\', '/'))
end

function path.hasext(fname, exts)
    local fext = path.getext(fname):lower()
    if type(exts) == "table" then
        for _, ext in pairs(exts) do
            if fext == ext then
                return true
            end
        end
        return false
    else
        return (fext == exts)
    end
end

function path.isfile(f)
    local ff = io.open(f, 'r')
    if not ff then
        return false
    else
        ff:close()
    end

    return true
end

function path.isdir(d)
    return oContent:isdir(d)
end

function path.getname(p)
    local i = p:findlast("[/\\]")
    if i then
        return p:sub(i + 1)
    else
        return p
    end
end

function path.getext(p)
    local i = p:findlast(".", true)
    if i then
        return p:sub(i)
    else
        return ""
    end
end

function path.getdir(p)
    local i = p:findlast("[/\\]")
    if i then
        if i > 1 then i = i - 1 end
        return p:sub(1, i)
    else
        return "."
    end
end

function path.getbasename(p)
    local name = path.getname(p)
    local i = name:findlast(".", true)
    if i then
        return name:sub(1, i - 1)
    else
        return name
    end
end

function path.join(p1, p2, ...)
    if not p2 then return p1 end
    if #p1 == 0 then return p2 end

    local s = string.char(string.byte(p1, #p1))

    if s == '/' or s == '\\' then
        return path.join(p1 .. p2, ...)
    else
        return path.join(p1..'/'..p2, ...)
    end
end

function path.listfile(d, r, exts)
    local add = table.insert
    if exts then
        add = function(ret, f)
            if path.hasext(f, exts) then
                table.insert(ret, f)
            end
        end
    end

    local ret = {}
    local function do_list(d)

        local files = oContent:getEntries(d, false)
        for i, file in ipairs(files) do
            add(ret, path.join(d, file))
        end

        if r then
            local dirs = oContent:getEntries(d, true)
            for i, dir in ipairs(dirs) do
                if dir ~= "." and dir ~= ".." then
                    do_list(path.join(d, dir))
                end
            end
       end
    end
    do_list(d)
    return ret
end

function path.rmdir(d)
    local files = path.listfile(d, true)
    
    for i, v in ipairs(files) do
        os.remove(v)
    end

    local dirs = path.listdir(d, true)

    table.sort(dirs, function(a, b) return #a > #b end)

    for i, v in ipairs(dirs) do
        lfs.rmdir(v)
    end

    lfs.rmdir(d)
end

function path.mkdir(p)
    return oContent:mkdir(p)
end

local function copy_file(from, to, override)

    if path.isfile(to) and not override then
        return false
    end

    local f_from = io.open(from, 'rb')
    local f_to = io.open(to, 'wb')

    if not f_from or not f_to then
        return false
    end

    local noteof = true

    while true do
        local data = f_from:read(4096)
        if not data then
            break
        end
        f_to:write(data)
    end

    f_to:close()
    f_from:close()
end

function path.copy(from, to, override)
    if path.isfile(from) then
        copy_file(from, to, override)
    else
        print('not imp')
    end
end

function path.mkdirs(dir)
    local pattern = "[\\/]"
    local pos = 0

    for st, sp in function() return dir:find(pattern, pos, plain) end do
        local d = dir:sub(0, st-1)
        if not path.isdir(d) then
            path.mkdir(d)
        end
        pos = sp + 1
    end

    if not path.isdir(dir) then
        path.mkdir(dir)
    end
end
