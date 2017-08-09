import os
def bubble_sort(lists):
    count = len(lists)
    for i in range(0, count):
        for j in range(i + 1, count):
            if int(lists[i].split('_')[1]) > int(lists[j].split('_')[1]):
                lists[i], lists[j] = lists[j], lists[i]
    return lists
def bubble_sort1(lists):
    count = len(lists)
    for i in range(0, count):
        for j in range(i + 1, count):
            if int(lists[i].split('_')[0]) > int(lists[j].split('_')[0]) and int(lists[i].split('_')[1]) == int(lists[j].split('_')[1]):
                lists[i], lists[j] = lists[j], lists[i]
    return lists
def chuli(lists):
	cc=len(lists)
	for i in range(0,cc-1):
		if int(lists[i+1].split('_')[1]) - int(lists[i].split('_')[1])<50:
			lists[i+1]=lists[i+1].split('_')[0]+'_'+lists[i].split('_')[1]+'_'+lists[i+1].split('_')[2]
	return lists
a=open("bc.txt","r")
x=[]
y=[]
bc=[]
aa=a.readline()
while(aa):
        bc.append(aa)
        xx=int(aa.split('_')[0])
        yy=int(aa.split('_')[1])
        if xx not in x:
                x.append(xx)

        if yy not in y:
                y.append(yy)

        aa=a.readline()
bubble_sort(bc)
chuli(bc)
bubble_sort1(bc)
c=len(bc)
for i in range(0,c-1):
	if int(bc[i].split('_')[1]) == int(bc[i+1].split('_')[1]):
		print bc[i].split(' ')[2][:-1]+' '+bc[i].split(' ')[0],
	else:
	#	print bc[i].split(' ')[2][:-1]
		print bc[i].split(' ')[2][:-1]+' '+bc[i].split(' ')[0]
print bc[c-1].split(' ')[2][:-1]
print
print
for i in range(0,c-1):
	if int(bc[i].split('_')[1]) == int(bc[i+1].split('_')[1]):
		print bc[i].split(' ')[2][:-1],
	else:
		print bc[i].split(' ')[2][:-1]
print bc[c-1].split(' ')[2][:-1]


