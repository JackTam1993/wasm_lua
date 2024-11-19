
local function decode(json)
    local position = 1

    local function skipWhitespace()
        while position <= #json and json:sub(position, position):match("%s") do
            position = position + 1
        end
    end
    local function parseString()
        local start = position + 1 -- 跳过 '"'
        position = start
        while position <= #json and json:sub(position, position) ~= "\"" do
            if json:sub(position, position) == "\\" then
                position = position + 1 -- 跳过转义字符
            end
            position = position + 1
        end
        if position > #json then
            error("Unterminated string at position " .. start)
        end
        local str = json:sub(start, position - 1)
        position = position + 1 -- 跳过 '"'
        return str
    end

    local function parseNumber()
        local start = position
        while position <= #json and json:sub(position, position):match("[%d%.%-eE%+]") do
            position = position + 1
        end
        local numStr = json:sub(start, position - 1)
        local number = tonumber(numStr)
        if not number then
            error("Invalid number at position " .. start)
        end
        return number
    end

    local function parseValue() end

    local function parseObject()
        local obj = {}
        position = position + 1 -- 跳过 '{'
        skipWhitespace()
        while json:sub(position, position) ~= "}" do
            local key = parseString()
            skipWhitespace()
            if json:sub(position, position) ~= ":" then
                error("Expected ':' at position " .. position)
            end
            position = position + 1 -- 跳过 ':'
            local value = parseValue()
            obj[key] = value
            skipWhitespace()
            if json:sub(position, position) == "," then
                position = position + 1 -- 跳过 ','
                skipWhitespace()
            elseif json:sub(position, position) ~= "}" then
                error("Expected '}' or ',' at position " .. position)
            end
        end
        position = position + 1 -- 跳过 '}'
        return obj
    end
    local function parseArray()
        local arr = {}
        position = position + 1 -- 跳过 '['
        skipWhitespace()
        while json:sub(position, position) ~= "]" do
            local value = parseValue()
            table.insert(arr, value)
            skipWhitespace()
            if json:sub(position, position) == "," then
                position = position + 1 -- 跳过 ','
                skipWhitespace()
            elseif json:sub(position, position) ~= "]" then
                error("Expected ']' or ',' at position " .. position)
            end
        end
        position = position + 1 -- 跳过 ']'
        return arr
    end
    function parseValue()
        skipWhitespace()
        local char = json:sub(position, position)
        if char == "{" then
            return parseObject()
        elseif char == "[" then
            return parseArray()
        elseif char == "\"" then
            return parseString()
        elseif char:match("[%d%-]") then
            return parseNumber()
        elseif json:sub(position, position + 3) == "true" then
            position = position + 4
            return true
        elseif json:sub(position, position + 4) == "false" then
            position = position + 5
            return false
        elseif json:sub(position, position + 3) == "null" then
            position = position + 4
            return nil
        else
            error("Invalid JSON value at position " .. position)
        end
    end
    return parseValue()
end

local function encode(sourceTab)
    local function escape_str(s)
        s = s:gsub("\\", "\\\\")
        s = s:gsub("\"", "\\\"")
        s = s:gsub("\b", "\\b")
        s = s:gsub("\f", "\\f")
        s = s:gsub("\n", "\\n")
        s = s:gsub("\r", "\\r")
        s = s:gsub("\t", "\\t")
        return s
    end
    local function json_encode(value) end

    function json_encode(value)
        local t = type(value)
        if t == "nil" then
            return "null"
        elseif t == "boolean" then
            return value and "true" or "false"
        elseif t == "number" then
            return tostring(value)
        elseif t == "string" then
            return "\"" .. escape_str(value) .. "\""
        elseif t == "table" then
            local is_array = true
            local max_index = 0
            for k, v in pairs(value) do
                if type(k) ~= "number" or k <= 0 or math.floor(k) ~= k then
                    is_array = false
                    break
                end
                if k > max_index then
                    max_index = k
                end
            end

            local result = {}
            if is_array then
                for i = 1, max_index do
                    table.insert(result, json_encode(value[i]))
                end
                return "[" .. table.concat(result, ",") .. "]"
            else
                for k, v in pairs(value) do
                    table.insert(result, "\"" .. escape_str(tostring(k)) .. "\":" .. json_encode(v))
                end
                return "{" .. table.concat(result, ",") .. "}"
            end
        else
            error("unsupported type: " .. t)
        end
    end

    return json_encode(sourceTab)

end

function jsonToData(jsonStr)

    local _jsonArray={}
    _jsonArray[1]=8
    _jsonArray[2]=9
    _jsonArray[3]=11
    _jsonArray[4]=14
    _jsonArray[5]=25
 
    local _arrayFlagKey={}
    _arrayFlagKey["array"]=_jsonArray

    local tab = {}
    tab["Himi"]="himigame.com"
    tab["testArray"]=_arrayFlagKey
    tab["age"]="23"
    return encode(tab)
end

function dataToJson(jsonStr)

    local _jsonArray={}
    _jsonArray[1]=8
    _jsonArray[2]=9
    _jsonArray[3]=11
    _jsonArray[4]=14
    _jsonArray[5]=25
 
    local _arrayFlagKey={}
    _arrayFlagKey["array"]=_jsonArray

    local tab = {}
    tab["Himi"]="himigame.com"
    tab["testArray"]=_arrayFlagKey
    tab["age"]="23"

    local jsonData = encode(tab);
    local data = decode(jsonData)

    local a = data.age
    local b = data.testArray.array[2]
    local c = data.Himi

    return "a:"..a.."  b:"..b.."  c:"..c;
end