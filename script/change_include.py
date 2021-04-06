import sys

def to_proper_name(name):
	new_name,start="",1
	if name[0] != "I" or name[1].islower():
        	new_name = name[0].lower()
	else:
		new_name,start = name[1].lower(), start + 1
	for ch in name[start:]:
		if ch.isupper():
			new_name += "_" + ch.lower()
		else:
			new_name += ch
	return new_name

path=sys.argv[1]
f = open(path,"r",encoding="utf-8")
lines = f.readlines()

for loc, line in enumerate(lines):
	if line.startswith("#include") and not "llvm" in line:
		new_line = line.strip().strip("#include ").strip("<").strip(">\n")
		strs = new_line.split("/")
		for i, str in enumerate(strs):
			strs[i] = to_proper_name(str)
		lines[loc] = "#include <" + "/".join(strs) + ">" + "\n"
f.close()

f = open(path,"w",encoding="utf-8")
for line in lines:
	f.write(line)
f.close()
	
		
			



