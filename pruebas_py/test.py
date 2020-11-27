def substring(str, start, end):
    length = len(str)
    if(start < 0):
        start = 0
    if(end > length):
        end = length
    if(start > length or start > end):
        return ""
    return str[start:end+1]

string = "Hola mundo papa"
print(substring(string, -5, -2))

print(pow(2.1, 3.5))