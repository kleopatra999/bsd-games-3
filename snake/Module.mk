################ Source files ##########################################

snake/NAME	:= snake
snake/EXE	:= $Osnake/${snake/NAME}
snake/EXE2	:= $Osnake/snscore
snake/SRCS	:= $(wildcard snake/*.c)
snake/OBJS	:= $(addprefix $O,$(snake/SRCS:.c=.o))
snake/DEPS	:= $(snake/OBJS:.o=.d)
snake/LIBS	:= ${CURSES_LIBS} ${MATH_LIBS}

################ Compilation ###########################################

.PHONY:	snake/all snake/clean snake/run snake/install snake/uninstall

all:		snake/all
snake/all:	${snake/EXE} ${snake/EXE2}
snake/run:	${snake/EXE}
	@${snake/EXE}

${snake/EXE}:	$Osnake/snake.o
	@echo "Linking $@ ..."
	@${CC} ${LDFLAGS} -o $@ $Osnake/snake.o ${snake/LIBS}

${snake/EXE2}:	$Osnake/snscore.o
	@echo "Linking $@ ..."
	@${CC} ${LDFLAGS} -o $@ $Osnake/snscore.o

################ Installation ##########################################

ifdef BINDIR
snake/EXEI	:= ${BINDIR}/${snake/NAME}
snake/EXE2I	:= ${BINDIR}/snscore
snake/MANI	:= ${MANDIR}/man6/${snake/NAME}.6.gz
snake/SCOREI	:= ${STATEDIR}/snakerawscores ${STATEDIR}/snake.log

install:		snake/install
snake/install:	${snake/EXEI} ${snake/EXE2I} ${snake/MANI} ${snake/SCOREI}
${snake/EXEI}:	${snake/EXE}
	@echo "Installing $@ ..."
	@${INSTALLEXE} $< $@
${snake/EXE2I}:	${snake/EXE2}
	@echo "Installing $@ ..."
	@${INSTALLEXE} $< $@
${snake/MANI}:	snake/${snake/NAME}.6
	@echo "Installing $@ ..."
	@gzip -9 -c $< > $@ && chmod 644 $@
${snake/SCOREI}:
	@echo "Creating initial score file $@ ..."
	@${INSTALLSCORE} /dev/null $@

uninstall:		snake/uninstall
snake/uninstall:
	@if [ -f ${snake/EXEI} ]; then\
	    echo "Removing ${snake/EXEI} ...";\
	    rm -f ${snake/EXEI} ${snake/EXE2I} ${snake/MANI} ${snake/SCOREI};\
	fi
endif

################ Maintenance ###########################################

clean:	snake/clean
snake/clean:
	@if [ -d $O/snake ]; then\
	    rm -f ${snake/EXE} ${snake/EXE2} ${snake/OBJS} ${snake/DEPS} $Osnake/.d;\
	    rmdir $O/snake;\
	fi

$Osnake/.d:	$O.d
	@[ -d $Osnake ] || mkdir $Osnake && touch $Osnake/.d

${snake/OBJS}: ${CONFS} snake/Module.mk $Osnake/.d

-include ${snake/DEPS}
