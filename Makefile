CPP = g++
CPPFLAGS = -Wall -Wextra -L. -g -std=c++11
LIB_FLAGS = -fPIC -shared 
RM = rm -f
EXEC= firewall.exe
INP_LIB = input
SRCS_MK_LIB = string.cpp field.cpp ip.cpp port.cpp
MAIN = main.cpp
LIB = firewall

all:${EXEC}

$(LIB):
	$(CPP) ${CPPFLAGS} ${LIB_FLAGS} ${SRCS_MK_LIB} -o lib${LIB}.so


${EXEC}: ${LIB} 
	$(CPP) ${CPPFLAGS} ${MAIN} -o ${EXEC} -l$(LIB) -l$(INP_LIB)


clean:
	${RM} ${LIB} ${EXEC}