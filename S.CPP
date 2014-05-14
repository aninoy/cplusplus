DATA SEGMENT
x dw ?
a dw ?
y dw ?
c dw ?
DATA ENDS
CODE SEGMENT
start:MOV ax,data
MOV data,dx

MOV ax,c
 MOV bx,a
 MUL bx
MOV temp,ax
MOV ax,temp
 MOV bx,y
 ADD ax,bx
MOV temp,ax
MOV ax,temp
MOV x,ax
CODE ENDS
