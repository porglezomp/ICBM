SDIR := src
ODIR := bin
SRCS := $(wildcard ${SDIR}/*.c)
SRCS := $(filter-out ${SDIR}/main.c ${SDIR}/lib.c, ${SRCS})
OBJS := $(SRCS:${SDIR}/%.c=${ODIR}/%.o)
DEPS := $(SRCS:${SDIR}/%.c=${ODIR}/%.d)

LIB := ${ODIR}/libmissile.so
APP := MissileGame.out

CFLAGS := -Wall -Werror -Wextra -pedantic -std=c11 -g $(shell pkg-config sdl2 --cflags)
CPPFLAGS :=
LDFLAGS := $(shell pkg-config sdl2 --libs) -lGLEW -lGL

DUMMY := $(shell mkdir -p ${ODIR})

all: ${LIB} ${APP}

${APP}: ${SDIR}/main.c
	gcc -o $@ $< ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} -ldl -L${ODIR} -Wl,-rpath=${ODIR} \
	-MMD

${LIB}: ${SDIR}/lib.c ${OBJS}
	@echo ${OBJS}
	gcc -o ${ODIR}/lib.o -c $< -fpic -MMD ${CPPFLAGS} ${CFLAGS} ${LDFLAGS}
	gcc -shared -o $@ ${ODIR}/lib.o ${OBJS} ${CPPFLAGS} ${CFLAGS} ${LDFLAGS}
	pkill ${APP} --signal SIGUSR1 || true

${ODIR}/%.o : ${SDIR}/common/%.c
	${CC} -o $@ $< -c ${CPPFLAGS} ${CFLAGS} -MMD

clean:
	rm -f ${ODIR}/*.o
	rm -f ${ODIR}/*.d
	rm -f ${APP}
	rm -f ${LIB}
	rmdir ${ODIR}

-include ${DEPS}
