SDIR := src
ODIR := bin
SRCS := $(shell echo ${SDIR}/*.c)
OBJS := $(SRCS:${SDIR}/%.c=${ODIR}/%.o)
DEPS := $(SRCS:${SDIR}/%.c=${ODIR}/%.d)

APP := MissileGame.out

CFLAGS := -Wall -Werror -Wextra -pedantic -std=c11 -g
CPPFLAGS :=
LDFLAGS :=

DUMMY := $(shell mkdir -p ${ODIR})

${APP}: ${OBJS}
	gcc -o $@ ${OBJS} ${CPPFLAGS} ${CFLAGS} ${LDFLAGS}

${ODIR}/%.o : ${SDIR}/%.c
	${CC} -o $@ $< -c ${CPPFLAGS} ${CFLAGS} -MMD

clean:
	rm -f ${OBJS}
	rm -f ${APP}
	rmdir ${ODIR}

-include ${DEPS}
